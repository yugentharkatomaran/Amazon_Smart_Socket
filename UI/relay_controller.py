#!/usr/bin/env python3
"""STM32 four-socket controller. Python 3.9+, Tkinter, optional pyserial."""
import queue
import re
import socket
import threading
import time
import tkinter as tk
from tkinter import ttk, messagebox

BG, INK, BLUE, GREEN = '#eef4fb', '#122d50', '#2285eb', '#18a34a'


def make_frame(mode, relay, state):
    if mode not in ('USB', 'Ethernet') or relay not in range(1, 5) or state not in (0, 1):
        raise ValueError('Invalid relay command')
    return bytes((0x55, 0xAA if mode == 'USB' else 0xBB, relay, state, 0xDD))


class Transport:
    """One outstanding command at a time; timeout never triggers an automatic retry."""
    def __init__(self, mode, port='', host='', tcp_port=5000):
        self.mode = mode
        self.io = None
        if mode == 'USB':
            try:
                import serial
            except ImportError as exc:
                raise RuntimeError('Install pyserial: python3 -m pip install pyserial') from exc
            # CDC requires a line-coding value in the API, but has no UART baud UI.
            self.io = serial.Serial(port, baudrate=115200, timeout=0.1, write_timeout=2)
        else:
            self.io = socket.create_connection((host, tcp_port), timeout=3)
            self.io.settimeout(0.1)

    def close(self):
        if self.io is not None:
            self.io.close()
            self.io = None

    def command(self, relay, state, log, cancel):
        frame = make_frame(self.mode, relay, state)
        if self.mode == 'USB':
            self.io.reset_input_buffer()
            if self.io.write(frame) != len(frame):
                raise OSError('Incomplete USB write')
        else:
            self.io.sendall(frame)
        log('TX  ' + frame.hex(' ').upper())
        expected = f'RELAY{relay} {"ON" if state else "OFF"}'.encode()
        received = bytearray()
        deadline = time.monotonic() + 3
        while time.monotonic() < deadline and not cancel.is_set():
            try:
                data = self.io.read(256) if self.mode == 'USB' else self.io.recv(256)
            except socket.timeout:
                continue
            if not data:
                if self.mode == 'Ethernet':
                    raise ConnectionError('Board closed TCP connection; reconnect before the next command')
                continue
            log('RX  ' + data.decode('ascii', errors='replace').strip())
            received.extend(data)
            # Handles fragmented replies and replies without a newline.
            replies = re.findall(rb'RELAY[1-4] (?:ON|OFF)', received)
            if expected in replies:
                return
            if len(received) > 8192:
                del received[:-128]
        if cancel.is_set():
            raise RuntimeError('Operation cancelled')
        raise TimeoutError('No matching relay reply within 3 seconds; socket state is unconfirmed')


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('4-Socket Controller')
        self.geometry('1100x780')
        self.minsize(950, 720)
        self.configure(bg=BG)
        self.mode = tk.StringVar(value='USB')
        self.port = tk.StringVar(value='/dev/ttyACM0')
        self.host = tk.StringVar(value='192.168.1.10')
        self.tcp_port = tk.StringVar(value='5000')
        self.events = queue.Queue()
        self.cancel = threading.Event()
        self.transport = None
        self.busy = False
        self.closing = False
        self.states = [None] * 4
        self.buttons, self.statuses, self.icons = [], [], []
        style = ttk.Style(self)
        style.theme_use('clam')
        style.configure('TCombobox', padding=7)
        self.option_add('*Font', 'Sans 11')
        self.build_ui()
        self.refresh_ports()
        self.render()
        self.after(60, self.poll)
        self.protocol('WM_DELETE_WINDOW', self.shutdown)

    def label(self, parent, text, size=11, bold=False, color=INK):
        return tk.Label(parent, text=text, font=('Sans', size, 'bold' if bold else 'normal'),
                        bg=parent.cget('bg'), fg=color)

    def button(self, parent, text, command, color=BLUE):
        return tk.Button(parent, text=text, command=command, bg=color, fg='white',
                         activebackground=color, activeforeground='white', relief='flat',
                         bd=0, padx=18, pady=9, cursor='hand2', disabledforeground='#a2b2c4')

    def card(self, parent):
        return tk.Frame(parent, bg='white', highlightthickness=1, highlightbackground='#d6e1ed')

    def build_ui(self):
        header = tk.Frame(self, bg=BG)
        header.pack(fill='x', padx=26, pady=(20, 12))
        self.label(header, '4-Socket Controller', 26, True).pack(anchor='w')
        self.label(header, 'USB & Ethernet control', 12, color='#627a98').pack(anchor='w')
        panel = self.card(self)
        panel.pack(fill='x', padx=26, pady=5)
        self.label(panel, 'Connection settings', 16, True).pack(anchor='w', padx=18, pady=(12, 8))
        modes = tk.Frame(panel, bg='white')
        modes.pack(anchor='w', padx=18)
        self.mode_buttons = []
        for name in ('USB', 'Ethernet'):
            b = self.button(modes, name, lambda n=name: self.set_mode(n))
            b.pack(side='left', padx=(0, 5))
            self.mode_buttons.append(b)
        fields = tk.Frame(panel, bg='white')
        fields.pack(fill='x', padx=18, pady=14)
        for i, name in enumerate(('COM Port', 'IP Address', 'TCP Port')):
            self.label(fields, name).grid(row=0, column=i, sticky='w', pady=(0, 5))
        usb = tk.Frame(fields, bg='white')
        usb.grid(row=1, column=0, sticky='w', padx=(0, 20))
        self.port_box = ttk.Combobox(usb, textvariable=self.port, width=18)
        self.port_box.pack(side='left')
        self.refresh_button = self.button(usb, 'Refresh', self.refresh_ports, '#637f9f')
        self.refresh_button.pack(side='left', padx=6)
        self.ip_entry = tk.Entry(fields, textvariable=self.host, width=17, relief='solid', bd=1)
        self.ip_entry.grid(row=1, column=1, ipady=9, padx=(0, 18))
        self.tcp_entry = tk.Entry(fields, textvariable=self.tcp_port, width=7, relief='solid', bd=1)
        self.tcp_entry.grid(row=1, column=2, ipady=9, padx=(0, 18))
        self.connect_button = self.button(fields, 'Connect', self.connection_click)
        self.connect_button.grid(row=1, column=3)
        self.connection_label = self.label(panel, 'Disconnected', color='#637f9f')
        self.connection_label.pack(anchor='w', padx=18, pady=(0, 12))
        self.label(self, 'Socket control', 17, True).pack(anchor='w', padx=26, pady=(15, 8))
        master = self.card(self)
        master.pack(fill='x', padx=26, pady=12)
        description = tk.Frame(master, bg='white')
        description.pack(side='left', padx=18, pady=10)
        self.label(description, 'All Sockets', 16, True).pack(anchor='w')
        self.master_status = self.label(description, 'Control all four sockets', color='#637f9f')
        self.master_status.pack(anchor='w')
        self.master = self.button(master, 'Turn all ON  ○', lambda: self.switch(None))
        self.master.pack(side='right', padx=18, pady=12)
        sockets = tk.Frame(self, bg=BG)
        sockets.pack(fill='x', padx=26)
        for i in range(4):
            sockets.columnconfigure(i, weight=1, uniform='socket')
            c = self.card(sockets)
            c.grid(row=0, column=i, sticky='nsew', padx=(0 if i == 0 else 6, 0 if i == 3 else 6))
            self.label(c, f'Socket {i+1}', 16, True).pack(pady=(12, 2))
            icon = self.label(c, '⏻', 36, color='#8b9db0')
            icon.pack()
            status = self.label(c, 'UNKNOWN', 11, True, '#637f9f')
            status.pack(pady=3)
            b = self.button(c, 'Turn ON  ○', lambda r=i+1: self.switch(r))
            b.pack(pady=(6, 14))
            self.icons.append(icon)
            self.statuses.append(status)
            self.buttons.append(b)
        logs = self.card(self)
        logs.pack(fill='both', expand=True, padx=26, pady=(0, 18))
        self.label(logs, 'Communication log', 15, True).pack(anchor='w', padx=15, pady=8)
        self.logbox = tk.Text(logs, height=6, bg='#f7faff', fg=INK, font=('Monospace', 10),
                              relief='flat', state='disabled', wrap='word')
        self.logbox.pack(fill='both', expand=True, padx=14, pady=(0, 12))

    def log(self, text):
        self.events.put(('log', text))

    def refresh_ports(self):
        try:
            from serial.tools import list_ports
            ports = [p.device for p in list_ports.comports()]
            self.port_box['values'] = ports
            if ports and self.port.get() not in ports:
                self.port.set(ports[0])
        except ImportError:
            self.log('USB requires pyserial. Ethernet is available without it.')

    def set_mode(self, mode):
        if not self.transport and not self.busy:
            self.mode.set(mode)
            self.states = [None] * 4
            self.render()

    def render(self):
        connected = self.transport is not None
        editable = not connected and not self.busy
        usb = self.mode.get() == 'USB'
        for name, b in zip(('USB', 'Ethernet'), self.mode_buttons):
            b.config(state='normal' if editable else 'disabled', bg=BLUE if name == self.mode.get() else '#637f9f')
        self.port_box.config(state='normal' if editable and usb else 'disabled')
        self.refresh_button.config(state='normal' if editable and usb else 'disabled')
        for entry in (self.ip_entry, self.tcp_entry):
            entry.config(state='normal' if editable and not usb else 'disabled')
        self.connect_button.config(text='Disconnect' if connected else 'Connect', state='disabled' if self.busy else 'normal')
        enabled = 'normal' if connected and not self.busy else 'disabled'
        for i, state in enumerate(self.states):
            color = GREEN if state == 1 else '#637f9f'
            self.statuses[i].config(text='UNKNOWN' if state is None else ('ON' if state else 'OFF'), fg=color)
            self.icons[i].config(fg=color)
            self.buttons[i].config(text='ON  ●  → OFF' if state == 1 else 'Turn ON  ○', bg=GREEN if state == 1 else BLUE, state=enabled)
        all_on = all(s == 1 for s in self.states)
        self.master.config(text='All ON  ●  → OFF' if all_on else 'Turn all ON  ○', bg=GREEN if all_on else BLUE, state=enabled)
        summary = 'All ON' if all_on else 'All OFF' if all(s == 0 for s in self.states) else 'Unknown / mixed state'
        self.master_status.config(text=summary + ' • Sends four commands in sequence')

    def connection_click(self):
        if self.transport:
            self.transport.close()
            self.transport = None
            self.states = [None] * 4
            self.connection_label.config(text='Disconnected', fg='#637f9f')
            self.log('Disconnected. No relay commands sent.')
            self.render()
            return
        mode, port, host = self.mode.get(), self.port.get().strip(), self.host.get().strip()
        try:
            number = int(self.tcp_port.get()) if mode == 'Ethernet' else 5000
            if mode == 'Ethernet' and (not host or not 1 <= number <= 65535):
                raise ValueError('Enter a valid host and TCP port (1–65535)')
            if mode == 'USB' and not port:
                raise ValueError('Select a COM port')
        except ValueError as exc:
            messagebox.showerror('Connection settings', str(exc))
            return
        self.busy = True
        self.connection_label.config(text='Connecting…', fg=BLUE)
        self.render()
        def work():
            try:
                link = Transport(mode, port, host, number)
                if self.cancel.is_set():
                    link.close()
                else:
                    self.events.put(('connected', link))
            except Exception as exc:
                self.events.put(('error', str(exc)))
        threading.Thread(target=work, daemon=True).start()

    def switch(self, relay):
        if self.busy or not self.transport:
            return
        target = 0 if (all(s == 1 for s in self.states) if relay is None else self.states[relay-1] == 1) else 1
        relays = list(range(1, 5)) if relay is None else [relay]
        link = self.transport
        self.busy = True
        for r in relays:
            self.states[r-1] = None
        self.connection_label.config(text='Waiting for device confirmation…', fg=BLUE)
        self.render()
        def work():
            try:
                for r in relays:
                    link.command(r, target, self.log, self.cancel)
                    self.events.put(('state', (r, target)))
                self.events.put(('done', None))
            except Exception as exc:
                link.close()
                self.events.put(('error', str(exc)))
        threading.Thread(target=work, daemon=True).start()

    def poll(self):
        try:
            while True:
                kind, data = self.events.get_nowait()
                if kind == 'log':
                    self.logbox.config(state='normal')
                    self.logbox.insert('end', time.strftime('%H:%M:%S') + '  ' + data + '\n')
                    if int(self.logbox.index('end-1c').split('.')[0]) > 500:
                        self.logbox.delete('1.0', '101.0')
                    self.logbox.see('end')
                    self.logbox.config(state='disabled')
                elif kind == 'state':
                    r, state = data
                    self.states[r-1] = state
                elif kind in ('connected', 'done'):
                    if kind == 'connected':
                        self.transport = data
                    self.busy = False
                    self.connection_label.config(text='Connected via ' + self.mode.get(), fg=GREEN)
                elif kind == 'error':
                    if self.transport:
                        self.transport.close()
                    self.transport = None
                    self.busy = False
                    self.states = [None] * 4
                    self.connection_label.config(text='Disconnected • ' + data, fg='#b34236', wraplength=950)
                    self.log('ERROR  ' + data)
                self.render()
        except queue.Empty:
            pass
        if not self.closing:
            self.after(60, self.poll)

    def shutdown(self):
        self.closing = True
        self.cancel.set()
        if self.transport and not self.busy:
            self.transport.close()
        # A worker owns any active transaction; daemon exits with this process.
        self.destroy()


if __name__ == '__main__':
    App().mainloop()

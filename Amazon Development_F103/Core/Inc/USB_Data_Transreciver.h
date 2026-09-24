/*
 * USB_Data_Transreciver.h
 *
 *  Created on: 08-Sept-2026
 *      Author: yugi
 */

#ifndef INC_USB_DATA_TRANSRECIVER_H_
#define INC_USB_DATA_TRANSRECIVER_H_

#include "usbd_cdc_if.h"
#include "string.h"
#include "AC_Socket_Control.h"
class USB_Data_Transreciver{


	private:

	int myNum = 2024; // Integer (whole number)
	float myFloatNum = 5.98; // Floating point number
	char myLetter = 'D';
	uint8_t myUint = 21; // Same way for uint16_t or uint32_t
	uint8_t myArray[20] = { 0 };
	char charData[100]; // Data holder

	AC_Socket_Control *ACsocketControl;

	public:
	USB_Data_Transreciver(AC_Socket_Control *acSocket)
	{
		ACsocketControl = acSocket;
	}

	void usb_transmit();
	void usb_receive();
	void Relay_Command_Handler(uint8_t *command);
    void usb_print(const char *text);

};



#endif /* INC_USB_DATA_TRANSRECIVER_H_ */

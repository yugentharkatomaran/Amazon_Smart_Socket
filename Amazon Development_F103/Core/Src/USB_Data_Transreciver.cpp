/*
 * USB_Data_Transreciver.cpp
 *
 *  Created on: 08-Sept-2026
 *      Author: yugi
 */

#include "USB_Data_Transreciver.h"


void USB_Data_Transreciver::usb_transmit()
{
//    auto usb_send_text = [](const char *text)
//    {
//        const uint16_t USB_CHUNK_SIZE = 128;
//
//        size_t total_len = strlen(text);
//        size_t offset = 0;
//
//        while (offset < total_len)
//        {
//            uint16_t chunk_len =
//                (uint16_t)((total_len - offset) > USB_CHUNK_SIZE
//                               ? USB_CHUNK_SIZE
//                               : (total_len - offset));
//
//            while (CDC_Transmit_FS(
//                       (uint8_t *)&text[offset],
//                       chunk_len) != USBD_OK)
//            {
//                HAL_Delay(1);
//            }
//
//            offset += chunk_len;
//
//            HAL_Delay(2);
//        }
//    };
//
//
//    /* =========================================================
//     * SYSTEM STARTUP
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "============================================================\r\n"
//        " ARM-BASED INTELLIGENT TRAFFIC SIGNAL CONTROLLER\r\n"
//        " STM32F407VGT6 + W5500 Ethernet\r\n"
//        " COMPLETE SYSTEM LOG\r\n"
//        "============================================================\r\n"
//    );
//
//    HAL_Delay(1000);
//
//
//    usb_send_text(
//        "------------------------------------------------------------\r\n"
//        "[SYSTEM] SYSTEM STARTUP\r\n"
//        "------------------------------------------------------------\r\n"
//        "[BOOT] System Reset\r\n"
//        "[BOOT] STM32F407VGT6 detected\r\n"
//        "[BOOT] ARM Cortex-M4 controller\r\n"
//        "[BOOT] System Clock        : 168 MHz\r\n"
//    );
//
//    HAL_Delay(500);
//
//
//    usb_send_text(
//        "[INIT] System initialization started\r\n"
//        "[INIT] GPIO                : OK\r\n"
//        "[INIT] TIMER               : OK\r\n"
//        "[INIT] SYSTICK             : OK\r\n"
//        "[INIT] NVIC                : OK\r\n"
//        "[INIT] UART                : OK\r\n"
//        "[INIT] SPI                 : OK\r\n"
//        "[INIT] Traffic outputs     : CONFIGURED\r\n"
//        "[INIT] Emergency input     : CONFIGURED\r\n"
//    );
//
//    HAL_Delay(500);
//
//
//    /* =========================================================
//     * W5500
//     * ========================================================= */
//
//    usb_send_text(
//        "------------------------------------------------------------\r\n"
//        "[W5500] INITIALIZATION\r\n"
//        "------------------------------------------------------------\r\n"
//        "[W5500] SPI interface       : INITIALIZING\r\n"
//    );
//
//    HAL_Delay(300);
//
//    usb_send_text(
//        "[W5500] SPI communication   : OK\r\n"
//        "[W5500] Chip detected       : YES\r\n"
//        "[W5500] Ethernet Link       : UP\r\n"
//        "[W5500] Socket Status       : LISTENING\r\n"
//        "[W5500] Status              : READY\r\n"
//    );
//
//    HAL_Delay(500);
//
//
//    /* =========================================================
//     * SYSTEM READY
//     * ========================================================= */
//
//    usb_send_text(
//        "------------------------------------------------------------\r\n"
//        "[SYSTEM] SYSTEM READY\r\n"
//        "------------------------------------------------------------\r\n"
//        "[STATUS] Traffic Controller : READY\r\n"
//        "[STATUS] LPU Connection     : WAITING\r\n"
//        "[STATUS] Traffic Outputs    : SAFE\r\n"
//        "[STATUS] Controller Mode    : AUTO\r\n"
//    );
//
//    HAL_Delay(1000);
//
//
//    /* =========================================================
//     * LPU MESSAGE RECEIVED
//     * ========================================================= */
//
//    usb_send_text(
//        "============================================================\r\n"
//        " LPU COMMUNICATION\r\n"
//        "============================================================\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    usb_send_text(
//        "[W5500] TCP connection request received\r\n"
//        "[W5500] LPU connection accepted\r\n"
//        "[LPU] Connection status     : CONNECTED\r\n"
//    );
//
//    HAL_Delay(500);
//
//
//    /*
//     * This is the actual message that the controller
//     * is assumed to have received from LPU.
//     */
//
//    usb_send_text(
//        "[LPU] Message received\r\n"
//        "[RX] Raw Data               : PLAN,2,30,25,20,15,3,2,5\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    usb_send_text(
//        "[RX] PLAN ID                : 02\r\n"
//        "[RX] ARM1 GREEN             : 30 sec\r\n"
//        "[RX] ARM2 GREEN             : 25 sec\r\n"
//        "[RX] ARM3 GREEN             : 20 sec\r\n"
//        "[RX] ARM4 GREEN             : 15 sec\r\n"
//        "[RX] ORANGE TIME            : 3 sec\r\n"
//        "[RX] ALL RED TIME           : 2 sec\r\n"
//        "[RX] COMMUNICATION TIMEOUT  : 5 sec\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    usb_send_text(
//        "[PLAN] Packet received      : PASS\r\n"
//        "[PLAN] Format validation    : PASS\r\n"
//        "[PLAN] Range validation     : PASS\r\n"
//        "[PLAN] Plan ID validation   : PASS\r\n"
//        "[PLAN] Traffic plan accepted: YES\r\n"
//    );
//
//    HAL_Delay(500);
//
//
//    /* =========================================================
//     * TRAFFIC CYCLE
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "============================================================\r\n"
//        " TRAFFIC CYCLE 001\r\n"
//        "============================================================\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * ALL RED
//     * ========================================================= */
//
//    usb_send_text(
//        "[PHASE] ALL RED\r\n"
//        "[ARM1] RED                 : ON\r\n"
//        "[ARM2] RED                 : ON\r\n"
//        "[ARM3] RED                 : ON\r\n"
//        "[ARM4] RED                 : ON\r\n"
//        "[TIMER] All Red Time       : 2 sec\r\n"
//    );
//
//    /*
//     * Actual 2 second delay
//     */
//    HAL_Delay(2000);
//
//
//    /* =========================================================
//     * ARM1 GREEN
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ARM1 GREEN\r\n"
//        "[ARM1] RED                 : OFF\r\n"
//        "[ARM1] GREEN               : ON\r\n"
//        "[ARM2] RED                 : ON\r\n"
//        "[ARM3] RED                 : ON\r\n"
//        "[ARM4] RED                 : ON\r\n"
//        "[TIMER] ARM1 Green Time    : 30 sec\r\n"
//    );
//
//
//    /*
//     * 30 second actual timing
//     *
//     * Print countdown every 5 seconds.
//     */
//
//    usb_send_text("[TIMER] Remaining          : 30 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 25 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 20 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 15 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 10 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 5 sec\r\n");
//    HAL_Delay(5000);
//
//
//    usb_send_text(
//        "[PHASE] ARM1 GREEN COMPLETED\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * ARM1 ORANGE
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ARM1 ORANGE\r\n"
//        "[ARM1] GREEN               : OFF\r\n"
//        "[ARM1] ORANGE              : ON\r\n"
//        "[TIMER] ARM1 Orange Time   : 3 sec\r\n"
//    );
//
//    HAL_Delay(3000);
//
//
//    usb_send_text(
//        "[PHASE] ARM1 ORANGE COMPLETED\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * ALL RED
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ALL RED\r\n"
//        "[ARM1] RED                 : ON\r\n"
//        "[ARM2] RED                 : ON\r\n"
//        "[ARM3] RED                 : ON\r\n"
//        "[ARM4] RED                 : ON\r\n"
//        "[TIMER] All Red Time       : 2 sec\r\n"
//    );
//
//    HAL_Delay(2000);
//
//
//    /* =========================================================
//     * ARM2 GREEN
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ARM2 GREEN\r\n"
//        "[ARM1] RED                 : ON\r\n"
//        "[ARM2] RED                 : OFF\r\n"
//        "[ARM2] GREEN               : ON\r\n"
//        "[ARM3] RED                 : ON\r\n"
//        "[ARM4] RED                 : ON\r\n"
//        "[TIMER] ARM2 Green Time    : 25 sec\r\n"
//    );
//
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 20 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 15 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 10 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 5 sec\r\n");
//    HAL_Delay(5000);
//
//
//    usb_send_text(
//        "[PHASE] ARM2 GREEN COMPLETED\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * ARM2 ORANGE
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ARM2 ORANGE\r\n"
//        "[ARM2] GREEN               : OFF\r\n"
//        "[ARM2] ORANGE              : ON\r\n"
//        "[TIMER] ARM2 Orange Time   : 3 sec\r\n"
//    );
//
//    HAL_Delay(3000);
//
//
//    usb_send_text(
//        "[PHASE] ARM2 ORANGE COMPLETED\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * ALL RED
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ALL RED\r\n"
//        "[ARM1] RED                 : ON\r\n"
//        "[ARM2] RED                 : ON\r\n"
//        "[ARM3] RED                 : ON\r\n"
//        "[ARM4] RED                 : ON\r\n"
//        "[TIMER] All Red Time       : 2 sec\r\n"
//    );
//
//    HAL_Delay(2000);
//
//
//    /* =========================================================
//     * ARM3 GREEN
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ARM3 GREEN\r\n"
//        "[ARM1] RED                 : ON\r\n"
//        "[ARM2] RED                 : ON\r\n"
//        "[ARM3] RED                 : OFF\r\n"
//        "[ARM3] GREEN               : ON\r\n"
//        "[ARM4] RED                 : ON\r\n"
//        "[TIMER] ARM3 Green Time    : 20 sec\r\n"
//    );
//
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 15 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 10 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 5 sec\r\n");
//    HAL_Delay(5000);
//
//
//    usb_send_text(
//        "[PHASE] ARM3 GREEN COMPLETED\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * ARM3 ORANGE
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ARM3 ORANGE\r\n"
//        "[ARM3] GREEN               : OFF\r\n"
//        "[ARM3] ORANGE              : ON\r\n"
//        "[TIMER] ARM3 Orange Time   : 3 sec\r\n"
//    );
//
//    HAL_Delay(3000);
//
//
//    usb_send_text(
//        "[PHASE] ARM3 ORANGE COMPLETED\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * ALL RED
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ALL RED\r\n"
//        "[ARM1] RED                 : ON\r\n"
//        "[ARM2] RED                 : ON\r\n"
//        "[ARM3] RED                 : ON\r\n"
//        "[ARM4] RED                 : ON\r\n"
//        "[TIMER] All Red Time       : 2 sec\r\n"
//    );
//
//    HAL_Delay(2000);
//
//
//    /* =========================================================
//     * ARM4 GREEN
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ARM4 GREEN\r\n"
//        "[ARM1] RED                 : ON\r\n"
//        "[ARM2] RED                 : ON\r\n"
//        "[ARM3] RED                 : ON\r\n"
//        "[ARM4] RED                 : OFF\r\n"
//        "[ARM4] GREEN               : ON\r\n"
//        "[TIMER] ARM4 Green Time    : 15 sec\r\n"
//    );
//
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 10 sec\r\n");
//    HAL_Delay(5000);
//
//    usb_send_text("[TIMER] Remaining          : 5 sec\r\n");
//    HAL_Delay(5000);
//
//
//    usb_send_text(
//        "[PHASE] ARM4 GREEN COMPLETED\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * ARM4 ORANGE
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ARM4 ORANGE\r\n"
//        "[ARM4] GREEN               : OFF\r\n"
//        "[ARM4] ORANGE              : ON\r\n"
//        "[TIMER] ARM4 Orange Time   : 3 sec\r\n"
//    );
//
//    HAL_Delay(3000);
//
//
//    usb_send_text(
//        "[PHASE] ARM4 ORANGE COMPLETED\r\n"
//    );
//
//    HAL_Delay(300);
//
//
//    /* =========================================================
//     * FINAL ALL RED
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "[PHASE] ALL RED\r\n"
//        "[ARM1] RED                 : ON\r\n"
//        "[ARM2] RED                 : ON\r\n"
//        "[ARM3] RED                 : ON\r\n"
//        "[ARM4] RED                 : ON\r\n"
//        "[TIMER] All Red Time       : 2 sec\r\n"
//    );
//
//    HAL_Delay(2000);
//
//
//    /* =========================================================
//     * CYCLE COMPLETE
//     * ========================================================= */
//
//    usb_send_text(
//        "\r\n"
//        "============================================================\r\n"
//        " TRAFFIC CYCLE 001 COMPLETED\r\n"
//        "============================================================\r\n"
//    );
//
//    HAL_Delay(1000);
//
//
//    usb_send_text(
//        "[CTRL] Current Plan         : 02\r\n"
//        "[CTRL] Traffic sequence     : COMPLETED\r\n"
//        "[CTRL] Next cycle           : READY\r\n"
//    );
}

void USB_Data_Transreciver::Relay_Command_Handler(uint8_t *command)
{
    // --------------------------------
    // Frame format:
    //
    // [0] = START
    // [1] = SOURCE
    // [2] = RELAY
    // [3] = STATE
    // [4] = STOP
    //
    // 55 AA 01 01 DD
    // --------------------------------


    // Check START byte
    if (command[0] != 0x55)
    {
        return;
    }


    // Check STOP byte
    if (command[4] != 0xDD)
    {
        return;
    }


    // Check SOURCE
    // 0xAA = USB
    // 0xBB = Ethernet

    if (command[1] != 0xAA)
    {
        return;
    }


    // Check STATE
    // 0x00 = OFF
    // 0x01 = ON

    if ((command[3] != 0x00) &&
        (command[3] != 0x01))
    {
        return;
    }


    // Relay selection
    switch (command[2])
    {

        // -------------------------
        // RELAY 1
        // -------------------------
        case 0x01:

            if (command[3] == 0x01)
            {
                ACsocketControl->relay_1(GPIO_PIN_RESET);

                char msg[] = "RELAY1 ON\r\n";

                CDC_Transmit_FS(
                    (uint8_t *)msg,
                    strlen(msg)
                );
            }
            else
            {
                ACsocketControl->relay_1(GPIO_PIN_SET);

                char msg[] = "RELAY1 OFF\r\n";

                CDC_Transmit_FS(
                    (uint8_t *)msg,
                    strlen(msg)
                );
            }

            break;


        // -------------------------
        // RELAY 2
        // -------------------------
        case 0x02:

            if (command[3] == 0x01)
            {
                ACsocketControl->relay_2(GPIO_PIN_RESET);

                char msg[] = "RELAY2 ON\r\n";

                CDC_Transmit_FS(
                    (uint8_t *)msg,
                    strlen(msg)
                );
            }
            else
            {
                ACsocketControl->relay_2(GPIO_PIN_SET);

                char msg[] = "RELAY2 OFF\r\n";

                CDC_Transmit_FS(
                    (uint8_t *)msg,
                    strlen(msg)
                );
            }

            break;


        // -------------------------
        // RELAY 3
        // -------------------------
        case 0x03:

            if (command[3] == 0x01)
            {
                ACsocketControl->relay_3(GPIO_PIN_RESET);

                char msg[] = "RELAY3 ON\r\n";

                CDC_Transmit_FS(
                    (uint8_t *)msg,
                    strlen(msg)
                );
            }
            else
            {
                ACsocketControl->relay_3(GPIO_PIN_SET);

                char msg[] = "RELAY3 OFF\r\n";

                CDC_Transmit_FS(
                    (uint8_t *)msg,
                    strlen(msg)
                );
            }

            break;


        // -------------------------
        // RELAY 4
        // -------------------------
        case 0x04:

            if (command[3] == 0x01)
            {
                ACsocketControl->relay_4(GPIO_PIN_RESET);

                char msg[] = "RELAY4 ON\r\n";

                CDC_Transmit_FS(
                    (uint8_t *)msg,
                    strlen(msg)
                );
            }
            else
            {
                ACsocketControl->relay_4(GPIO_PIN_SET);

                char msg[] = "RELAY4 OFF\r\n";

                CDC_Transmit_FS(
                    (uint8_t *)msg,
                    strlen(msg)
                );
            }

            break;


        // -------------------------
        // INVALID RELAY
        // -------------------------
        default:
        {
            char msg[] = "INVALID RELAY\r\n";

            CDC_Transmit_FS(
                (uint8_t *)msg,
                strlen(msg)
            );

            break;
        }
    }
}


void USB_Data_Transreciver::usb_receive()
{

    if(usb_rx_flag == 1)
    {


        usb_rx_flag = 0;

        // Process command

        Relay_Command_Handler(usb_rx_buffer);


    }

}

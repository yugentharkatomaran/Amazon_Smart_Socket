/*
 * Ethernet.cpp
 *
 * Created on: 08-Sept-2026
 * Author: yugi
 */

#include "Ethernet.h"
#include "socket.h"
#include <string.h>


/*----------------------------------------------------------
 * Constructor
 *----------------------------------------------------------*/

Ethernet::Ethernet(AC_Socket_Control *acSocket)
{
    ACsocketControl = acSocket;
}


/*----------------------------------------------------------
 * W5500 Initialization Check
 *----------------------------------------------------------*/

void Ethernet::W5500Init_check()
{
    if (W5500_Init() != 0)
    {
        // W5500 initialization failed
    }
    else
    {
        // W5500 initialization successful
    }
}


/*----------------------------------------------------------
 * Relay Command Handler
 *
 * Frame:
 *
 * Byte 0 : 0x55       START
 * Byte 1 : 0xBB       ETHERNET
 * Byte 2 : 0x01-0x04  RELAY
 * Byte 3 : 0x00/0x01  OFF/ON
 * Byte 4 : 0xDD       STOP
 *
 * Example:
 *
 * 55 BB 01 01 DD
 *
 * Ethernet -> Relay 1 -> ON
 *
 *----------------------------------------------------------*/

void Ethernet::Relay_Command_Handler(uint8_t *command)
{
    /* Check START byte */

    if (command[0] != 0x55)
    {
        return;
    }


    /* Check STOP byte */

    if (command[4] != 0xDD)
    {
        return;
    }


    /* Check SOURCE */

    /*
     * 0xBB = Ethernet
     */

    if (command[1] != 0xBB)
    {
        return;
    }


    /* Check STATE */

    /*
     * 0x00 = OFF
     * 0x01 = ON
     */

    if ((command[3] != 0x00) &&
        (command[3] != 0x01))
    {
        return;
    }


    /* Relay selection */

    switch (command[2])
    {

        /*--------------------------------------------------
         * Relay 1
         *--------------------------------------------------*/

        case 0x01:

            if (command[3] == 0x01)
            {
                ACsocketControl->relay_1(GPIO_PIN_RESET);
                const char ack[] = "RELAY1 ON";
                        send(
                            W5500_SOCKET,
                            (uint8_t *)ack,
                            strlen(ack)
                        );

            }
            else
            {
                ACsocketControl->relay_1(GPIO_PIN_SET);
                const char ack[] = "RELAY1 OFF";
                        send(
                            W5500_SOCKET,
                            (uint8_t *)ack,
                            strlen(ack)
                        );
            }
//            disconnect(W5500_SOCKET);
//            close(W5500_SOCKET);
            break;


        /*--------------------------------------------------
         * Relay 2
         *--------------------------------------------------*/

        case 0x02:

            if (command[3] == 0x01)
            {
                ACsocketControl->relay_2(GPIO_PIN_RESET);
                const char ack[] = "RELAY2 ON";
                        send(
                            W5500_SOCKET,
                            (uint8_t *)ack,
                            strlen(ack)
                        );
            }
            else
            {
                ACsocketControl->relay_2(GPIO_PIN_SET);

                const char ack[] = "RELAY2 OFF";
                        send(
                            W5500_SOCKET,
                            (uint8_t *)ack,
                            strlen(ack)
                        );
            }
//            disconnect(W5500_SOCKET);
//            close(W5500_SOCKET);
            break;


        /*--------------------------------------------------
         * Relay 3
         *--------------------------------------------------*/

        case 0x03:

            if (command[3] == 0x01)
            {
                ACsocketControl->relay_3(GPIO_PIN_RESET);
                const char ack[] = "RELAY3 ON";
				send(
					W5500_SOCKET,
					(uint8_t *)ack,
					strlen(ack)
				);
            }
            else
            {
                ACsocketControl->relay_3(GPIO_PIN_SET);
                const char ack[] = "RELAY3 OFF";
				send(
					W5500_SOCKET,
					(uint8_t *)ack,
					strlen(ack)
				);
            }
//            disconnect(W5500_SOCKET);
//            close(W5500_SOCKET);
            break;


        /*--------------------------------------------------
         * Relay 4
         *--------------------------------------------------*/

        case 0x04:

            if (command[3] == 0x01)
            {
                ACsocketControl->relay_4(GPIO_PIN_RESET);
                const char ack[] = "RELAY4 ON";
				send(
					W5500_SOCKET,
					(uint8_t *)ack,
					strlen(ack)
				);
            }
            else
            {
                ACsocketControl->relay_4(GPIO_PIN_SET);
                const char ack[] = "RELAY4 OFF";
				send(
					W5500_SOCKET,
					(uint8_t *)ack,
					strlen(ack)
				);
            }
//            disconnect(W5500_SOCKET);
//            close(W5500_SOCKET);
            break;


        /*--------------------------------------------------
         * Invalid relay
         *--------------------------------------------------*/

        default:
        	const char ack[] = "INVALED COMMAND";
        					send(
        						W5500_SOCKET,
        						(uint8_t *)ack,
        						strlen(ack)
        					);
//        	disconnect(W5500_SOCKET);
//        	close(W5500_SOCKET);
            break;

    }
}


/*----------------------------------------------------------
 * Ethernet Receive
 *
 * Receives 5-byte relay frame from W5500 TCP socket.
 *----------------------------------------------------------*/

void Ethernet::ethernet_receive()
{
    uint8_t socketStatus;

    socketStatus = getSn_SR(W5500_SOCKET);

    switch (socketStatus)
    {
        /*--------------------------------------------
         * Socket closed
         *--------------------------------------------*/
        case SOCK_CLOSED:
        {
            rxCount = 0;

            socket(
                W5500_SOCKET,
                Sn_MR_TCP,
                W5500_TCP_PORT,
                0
            );

            break;
        }


        /*--------------------------------------------
         * Socket created
         *--------------------------------------------*/
        case SOCK_INIT:
        {
            listen(W5500_SOCKET);

            break;
        }


        /*--------------------------------------------
         * Waiting for PC/client
         *--------------------------------------------*/
        case SOCK_LISTEN:
        {
            break;
        }


        /*--------------------------------------------
         * TCP client connected
         *--------------------------------------------*/
        case SOCK_ESTABLISHED:
        {
            /*
             * Clear connection interrupt
             */
            if (getSn_IR(W5500_SOCKET) & Sn_IR_CON)
            {
                setSn_IR(
                    W5500_SOCKET,
                    Sn_IR_CON
                );
            }


            /*
             * Check whether Ethernet data exists.
             *
             * Very important:
             * Do not call recv() when there is
             * no data because Process::process()
             * must continue servicing USB.
             */
            uint16_t available;

            available = getSn_RX_RSR(W5500_SOCKET);


            if (available > 0)
            {
                uint16_t required;

                required = 5U - rxCount;

                if (available < required)
                {
                    required = available;
                }


                int32_t received;

                received = recv(
                    W5500_SOCKET,
                    &rxBuffer[rxCount],
                    required
                );


                if (received > 0)
                {
                    rxCount += received;


                    /*
                     * Complete 5-byte frame received
                     */
                    if (rxCount == 5)
                    {
                        Relay_Command_Handler(
                            rxBuffer
                        );

                        rxCount = 0;
                    }
                }
            }

            break;
        }


        /*--------------------------------------------
         * Client disconnected
         *--------------------------------------------*/
        case SOCK_CLOSE_WAIT:
        {
            rxCount = 0;

            disconnect(W5500_SOCKET);

            close(W5500_SOCKET);

            break;
        }


        /*--------------------------------------------
         * Unexpected socket condition
         *--------------------------------------------*/
        default:
        {
            rxCount = 0;

            close(W5500_SOCKET);

            break;
        }
    }
}

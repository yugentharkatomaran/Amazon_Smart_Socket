/*
 * Process.cpp
 *
 *  Created on: 08-Sept-2026
 *      Author: yugi
 */
#include "Process.h"




AC_Socket_Control AC_socketControl;

USB_Data_Transreciver USB_Data_TransReceive(&AC_socketControl);

Ethernet EthernetTransReceiver(&AC_socketControl);

ACS712 acs712;

INA219 ins219;

void Process::Init()
{

	AC_socketControl.relay_1(GPIO_PIN_SET);
	AC_socketControl.relay_2(GPIO_PIN_SET);
	AC_socketControl.relay_3(GPIO_PIN_SET);
	AC_socketControl.relay_4(GPIO_PIN_SET);

	EthernetTransReceiver.W5500Init_check();

	acs712.adcInit();

	ins219.ina_status = ins219.INA219_Init();

}

void Process::process()
{

	EthernetTransReceiver.ethernet_receive();

    USB_Data_TransReceive.usb_receive();

    acs712.adcRead();
    ins219.ina_status = ins219.INA219_ReadMeasurements();

    if (ins219.ina_status == HAL_OK)
    {
        /* New measurement available in ina_current_mA, etc. */
    }
    else
    {
        /* Values are stale: ina_valid is 0.
           Inspect ina_status and ina_overflow. */
    }
//	USB_Data_TransReceive.usb_transmit();
}





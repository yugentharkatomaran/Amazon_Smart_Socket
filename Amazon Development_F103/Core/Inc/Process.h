/*
 * Process.h
 *
 *  Created on: 08-Sept-2026
 *      Author: yugi
 */

#ifndef INC_PROCESS_H_
#define INC_PROCESS_H_
#include "USB_Data_Transreciver.h"
#include "Ethernet.h"
#include "AC_Socket_Control.h"
#include "ACS712.h"
#include "INA219.h"

class Process{

public:
	void Init();
	void process();

};


#endif /* INC_PROCESS_H_ */

/*
 * ACS712.h
 *
 *  Created on: 22-Sept-2026
 *      Author: yugi
 */

#ifndef INC_ACS712_H_
#define INC_ACS712_H_


#include "adc.h"




class ACS712{


private:

	uint16_t readValue;
	float sensitivity = 0.1; // 0.1 for 20A Model
	float rawVoltage;
	float current;


public:

	void adcInit();
	void adcRead();



};




#endif /* INC_ACS712_H_ */

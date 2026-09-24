/*
 * AC_Socket_Control.cpp
 *
 *  Created on: 08-Sept-2026
 *      Author: yugi
 */



#include "AC_Socket_Control.h"


 void AC_Socket_Control::relay_1(GPIO_PinState Turn_1)
 {

	 HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, Turn_1);

 }
 void AC_Socket_Control::relay_2(GPIO_PinState Turn_2)
 {

	 HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, Turn_2);

 }
 void AC_Socket_Control::relay_3(GPIO_PinState Turn_3)
 {

	 HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, Turn_3);

 }
 void AC_Socket_Control::relay_4(GPIO_PinState Turn_4)
 {

	 HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, Turn_4);

 }
 void AC_Socket_Control::relay_5(GPIO_PinState Turn_5)
 {

	 HAL_GPIO_WritePin(RELAY_5_GPIO_Port, RELAY_5_Pin, Turn_5);

 }
 void AC_Socket_Control::relay_6(GPIO_PinState Turn_6)
 {

	 HAL_GPIO_WritePin(RELAY_6_GPIO_Port, RELAY_6_Pin, Turn_6);

 }

 void AC_Socket_Control::relay_7(GPIO_PinState Turn_7)
 {

	 HAL_GPIO_WritePin(RELAY_7_GPIO_Port, RELAY_7_Pin, Turn_7);

 }
 void AC_Socket_Control::relay_8(GPIO_PinState Turn_8)
 {

	 HAL_GPIO_WritePin(RELAY_8_GPIO_Port, RELAY_8_Pin, Turn_8);

 }

 void AC_Socket_Control::relay_9(GPIO_PinState Turn_9)
 {

	 HAL_GPIO_WritePin(RELAY_9_GPIO_Port, RELAY_9_Pin, Turn_9);

 }
 void AC_Socket_Control::relay_10(GPIO_PinState Turn_10)
 {

	 HAL_GPIO_WritePin(RELAY_10_GPIO_Port, RELAY_10_Pin, Turn_10);

 }

/*
 * AC_Socket_Control.h
 *
 *  Created on: 08-Sept-2026
 *      Author: yugi
 */

#ifndef INC_AC_SOCKET_CONTROL_H_
#define INC_AC_SOCKET_CONTROL_H_
#include "main.h"
#include "gpio.h"

class AC_Socket_Control{


private:



public:

    void relay_1(GPIO_PinState Turn_1);

    void relay_2(GPIO_PinState Turn_2);

    void relay_3(GPIO_PinState Turn_3);

    void relay_4(GPIO_PinState Turn_4);

    void relay_5(GPIO_PinState Turn_5);

	void relay_6(GPIO_PinState Turn_6);

	void relay_7(GPIO_PinState Turn_7);

	void relay_8(GPIO_PinState Turn_8);

	void relay_9(GPIO_PinState Turn_9);

	void relay_10(GPIO_PinState Turn_10);

};


#endif /* INC_AC_SOCKET_CONTROL_H_ */

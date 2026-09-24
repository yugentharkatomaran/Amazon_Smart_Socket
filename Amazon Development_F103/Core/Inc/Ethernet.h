#ifndef INC_ETHERNET_H_
#define INC_ETHERNET_H_

#include "main.h"
#include "AC_Socket_Control.h"

#define W5500_SOCKET 0

#define W5500_TCP_PORT   5000

#ifdef __cplusplus
extern "C" {
#endif

int W5500_Init(void);

#ifdef __cplusplus
}
#endif


class Ethernet
{
private:

    uint8_t rxBuffer[5];

    uint8_t rxCount = 0;

    AC_Socket_Control *ACsocketControl;

public:

    Ethernet(AC_Socket_Control *acSocket);

    void W5500Init_check();

    void Relay_Command_Handler(uint8_t *command);

    void ethernet_receive();
};

#endif /* INC_ETHERNET_H_ */

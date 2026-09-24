################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Ethernet_W550/DHCP/dhcp.c 

C_DEPS += \
./Drivers/Ethernet_W550/DHCP/dhcp.d 

OBJS += \
./Drivers/Ethernet_W550/DHCP/dhcp.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Ethernet_W550/DHCP/%.o Drivers/Ethernet_W550/DHCP/%.su Drivers/Ethernet_W550/DHCP/%.cyclo: ../Drivers/Ethernet_W550/DHCP/%.c Drivers/Ethernet_W550/DHCP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"/home/yugi/Projects-2026/Amazon development USB HUB/Software/Amazon Development_F103/Drivers/Ethernet_W550/W5500" -I"/home/yugi/Projects-2026/Amazon development USB HUB/Software/Amazon Development_F103/Drivers/Ethernet_W550" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Ethernet_W550-2f-DHCP

clean-Drivers-2f-Ethernet_W550-2f-DHCP:
	-$(RM) ./Drivers/Ethernet_W550/DHCP/dhcp.cyclo ./Drivers/Ethernet_W550/DHCP/dhcp.d ./Drivers/Ethernet_W550/DHCP/dhcp.o ./Drivers/Ethernet_W550/DHCP/dhcp.su

.PHONY: clean-Drivers-2f-Ethernet_W550-2f-DHCP


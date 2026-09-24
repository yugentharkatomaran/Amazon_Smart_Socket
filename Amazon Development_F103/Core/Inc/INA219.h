/*
 * INA219.h
 *
 *  Created on: 24-Sept-2026
 *      Author: yugi
 */

#ifndef INC_INA219_H_
#define INC_INA219_H_

#include "main.h"
#include "i2c.h"
#include "gpio.h"


/* USER CODE BEGIN PD */

#define INA219_ADDR         (0x40U << 1) /* HAL uses shifted address */

#define INA219_REG_CONFIG   0x00U
#define INA219_REG_SHUNT    0x01U
#define INA219_REG_BUS      0x02U
#define INA219_REG_POWER    0x03U
#define INA219_REG_CURRENT  0x04U
#define INA219_REG_CAL      0x05U

/* Valid only for a 0.1-ohm shunt and 0.1 mA current LSB. */
#define INA219_CAL_VALUE    4096U

/*
 * 32 V register range, +/-320 mV shunt range,
 * 12-bit bus and shunt conversion.
 * Physical input limit remains 26 V.
 */
#define INA219_CONFIG_IDLE     0x3998U
#define INA219_CONFIG_TRIGGER  0x399BU

class INA219{


private:



public:


	    volatile float ina_bus_voltage_V   = 0.0f;
		volatile float ina_shunt_voltage_mV = 0.0f;
		volatile float ina_current_mA      = 0.0f;
		volatile float ina_power_mW        = 0.0f;

		/* HAL_OK=0, HAL_ERROR=1, HAL_BUSY=2, HAL_TIMEOUT=3 */
		volatile HAL_StatusTypeDef ina_status = HAL_ERROR;

		/* Valid is cleared if the latest measurement fails. */
		volatile uint8_t ina_valid = 0;
		volatile uint8_t ina_overflow = 0;


	HAL_StatusTypeDef INA219_WriteRegister(uint8_t reg,
	                                              uint16_t value);

	HAL_StatusTypeDef INA219_ReadRegister(uint8_t reg,
	                                             uint16_t *value);


	HAL_StatusTypeDef INA219_Init(void);

	HAL_StatusTypeDef INA219_ReadMeasurements(void);






};



#endif /* INC_INA219_H_ */

/*
 * INA219.cpp
 *
 *  Created on: 24-Sept-2026
 *      Author: yugi
 */


#include "INA219.h"


HAL_StatusTypeDef INA219::INA219_WriteRegister(uint8_t reg,uint16_t value)
{
	uint8_t data[2];

	data[0] = (uint8_t)(value >> 8);
	data[1] = (uint8_t)(value & 0xFFU);

	return HAL_I2C_Mem_Write(&hi2c1,
	INA219_ADDR,
	reg,
	I2C_MEMADD_SIZE_8BIT,
	data,
	2,
	100);
}

HAL_StatusTypeDef INA219::INA219_ReadRegister(uint8_t reg,
                                             uint16_t *value)
{
    uint8_t data[2];

    HAL_StatusTypeDef status =
        HAL_I2C_Mem_Read(&hi2c1,
                         INA219_ADDR,
                         reg,
                         I2C_MEMADD_SIZE_8BIT,
                         data,
                         2,
                         100);

    if (status == HAL_OK)
    {
        *value = ((uint16_t)data[0] << 8) | data[1];
    }

    return status;
}

HAL_StatusTypeDef INA219::INA219_Init(void)
{
    HAL_StatusTypeDef status;

    status = HAL_I2C_IsDeviceReady(&hi2c1,
                                   INA219_ADDR,
                                   3,
                                   100);
    if (status != HAL_OK)
        return status;

    status = INA219_WriteRegister(INA219_REG_CONFIG,
                                   INA219_CONFIG_IDLE);
    if (status != HAL_OK)
        return status;

    return INA219_WriteRegister(INA219_REG_CAL,
                                 INA219_CAL_VALUE);
}



HAL_StatusTypeDef INA219::INA219_ReadMeasurements(void)
{
    uint16_t bus_raw;
    uint16_t shunt_raw;
    uint16_t current_raw;
    uint16_t power_raw;
    uint32_t start;
    HAL_StatusTypeDef status;

    ina_valid = 0;
    ina_overflow = 0;

    /* Restore calibration in case the sensor lost power. */
    status = INA219_WriteRegister(INA219_REG_CAL,
                                   INA219_CAL_VALUE);
    if (status != HAL_OK)
        return status;

    /* Trigger one complete shunt + bus measurement.
       Registers remain stable after conversion completes. */
    status = INA219_WriteRegister(INA219_REG_CONFIG,
                                   INA219_CONFIG_TRIGGER);
    if (status != HAL_OK)
        return status;

    start = HAL_GetTick();

    do
    {
        status = INA219_ReadRegister(INA219_REG_BUS, &bus_raw);
        if (status != HAL_OK)
            return status;

        /* CNVR: conversion ready */
        if ((bus_raw & 0x0002U) != 0U)
            break;

        if ((HAL_GetTick() - start) >= 100U)
            return HAL_TIMEOUT;

        HAL_Delay(1);
    } while (1);

    /* OVF: current/power arithmetic overflow */
    if ((bus_raw & 0x0001U) != 0U)
    {
        ina_overflow = 1;
        return HAL_ERROR;
    }

    status = INA219_ReadRegister(INA219_REG_SHUNT, &shunt_raw);
    if (status != HAL_OK)
        return status;

    status = INA219_ReadRegister(INA219_REG_CURRENT, &current_raw);
    if (status != HAL_OK)
        return status;

    status = INA219_ReadRegister(INA219_REG_POWER, &power_raw);
    if (status != HAL_OK)
        return status;

    /* Bus voltage is measured at VIN- relative to GND. */
    ina_bus_voltage_V = (float)(bus_raw >> 3) * 0.004f;

    /* Shunt and current registers are signed. */
    ina_shunt_voltage_mV = (float)(int16_t)shunt_raw * 0.01f;
    ina_current_mA = (float)(int16_t)current_raw * 0.1f;

    /* Power LSB = 20 x current LSB = 2 mW. */
    ina_power_mW = (float)power_raw * 2.0f;

    ina_valid = 1;
    return HAL_OK;
}


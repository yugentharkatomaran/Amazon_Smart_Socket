/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define HEART_BEAT_Pin GPIO_PIN_13
#define HEART_BEAT_GPIO_Port GPIOC
#define RELAY_9_Pin GPIO_PIN_14
#define RELAY_9_GPIO_Port GPIOC
#define RELAY_10_Pin GPIO_PIN_15
#define RELAY_10_GPIO_Port GPIOC
#define SPI1_RESET_Pin GPIO_PIN_3
#define SPI1_RESET_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define INPUT_2_Pin GPIO_PIN_1
#define INPUT_2_GPIO_Port GPIOB
#define INPUT_1_Pin GPIO_PIN_2
#define INPUT_1_GPIO_Port GPIOB
#define LOG_TX_Pin GPIO_PIN_10
#define LOG_TX_GPIO_Port GPIOB
#define LOG_RX_Pin GPIO_PIN_11
#define LOG_RX_GPIO_Port GPIOB
#define RELAY_12_Pin GPIO_PIN_12
#define RELAY_12_GPIO_Port GPIOB
#define RELAY_11_Pin GPIO_PIN_13
#define RELAY_11_GPIO_Port GPIOB
#define RELAY_7_Pin GPIO_PIN_14
#define RELAY_7_GPIO_Port GPIOB
#define RELAY_8_Pin GPIO_PIN_15
#define RELAY_8_GPIO_Port GPIOB
#define RELAY_6_Pin GPIO_PIN_15
#define RELAY_6_GPIO_Port GPIOA
#define RELAY_5_Pin GPIO_PIN_3
#define RELAY_5_GPIO_Port GPIOB
#define RELAY_4_Pin GPIO_PIN_4
#define RELAY_4_GPIO_Port GPIOB
#define RELAY_3_Pin GPIO_PIN_5
#define RELAY_3_GPIO_Port GPIOB
#define RELAY_2_Pin GPIO_PIN_6
#define RELAY_2_GPIO_Port GPIOB
#define RELAY_1_Pin GPIO_PIN_7
#define RELAY_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

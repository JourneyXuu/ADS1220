/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
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
#define Beep_Pin GPIO_PIN_13
#define Beep_GPIO_Port GPIOC
#define Flash_NSS_Pin GPIO_PIN_4
#define Flash_NSS_GPIO_Port GPIOA
#define Flash_SCK_Pin GPIO_PIN_5
#define Flash_SCK_GPIO_Port GPIOA
#define Flash_MISO_Pin GPIO_PIN_6
#define Flash_MISO_GPIO_Port GPIOA
#define Flash_MOSI_Pin GPIO_PIN_7
#define Flash_MOSI_GPIO_Port GPIOA
#define LED_Board_Pin GPIO_PIN_2
#define LED_Board_GPIO_Port GPIOB
#define Magnet_Pin GPIO_PIN_11
#define Magnet_GPIO_Port GPIOE
#define LED_1_Pin GPIO_PIN_13
#define LED_1_GPIO_Port GPIOD
#define LED_2_Pin GPIO_PIN_14
#define LED_2_GPIO_Port GPIOD
#define LED_3_Pin GPIO_PIN_15
#define LED_3_GPIO_Port GPIOD
#define ADS_DRDY_Pin GPIO_PIN_8
#define ADS_DRDY_GPIO_Port GPIOC
#define ADS_DRDY_EXTI_IRQn EXTI9_5_IRQn
#define ADS_CS_Pin GPIO_PIN_9
#define ADS_CS_GPIO_Port GPIOC
#define ADS_SCK_Pin GPIO_PIN_10
#define ADS_SCK_GPIO_Port GPIOC
#define ADS_MISO_Pin GPIO_PIN_11
#define ADS_MISO_GPIO_Port GPIOC
#define ADS_MOSI_Pin GPIO_PIN_12
#define ADS_MOSI_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

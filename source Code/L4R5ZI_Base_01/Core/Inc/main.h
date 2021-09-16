/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l4xx_hal.h"

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
#define WIND_DIR_INT_Pin GPIO_PIN_5
#define WIND_DIR_INT_GPIO_Port GPIOE
#define WIND_DIR_INT_EXTI_IRQn EXTI9_5_IRQn
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define USER_BUTTON_EXTI_IRQn EXTI15_10_IRQn
#define SPI_CLK_Pin GPIO_PIN_0
#define SPI_CLK_GPIO_Port GPIOA
#define SPI_OUT_Pin GPIO_PIN_0
#define SPI_OUT_GPIO_Port GPIOB
#define DATA_CMD_LCD_Pin GPIO_PIN_10
#define DATA_CMD_LCD_GPIO_Port GPIOE
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOE
#define RED_LED_Pin GPIO_PIN_14
#define RED_LED_GPIO_Port GPIOB
#define GREEN_LED_Pin GPIO_PIN_7
#define GREEN_LED_GPIO_Port GPIOC
#define BLUE_LED_Pin GPIO_PIN_7
#define BLUE_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

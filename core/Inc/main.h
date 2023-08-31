/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

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
#define PF0_zegar_in_Pin GPIO_PIN_0
#define PF0_zegar_in_GPIO_Port GPIOF
#define PF1_zegar_out_Pin GPIO_PIN_1
#define PF1_zegar_out_GPIO_Port GPIOF
#define PC0_czujnik_Pin GPIO_PIN_0
#define PC0_czujnik_GPIO_Port GPIOC
#define PC1_pompa_Pin GPIO_PIN_1
#define PC1_pompa_GPIO_Port GPIOC
#define Btn_OK_Pin GPIO_PIN_0
#define Btn_OK_GPIO_Port GPIOB
#define Btn_Up_Pin GPIO_PIN_1
#define Btn_Up_GPIO_Port GPIOB
#define Btn_Down_Pin GPIO_PIN_2
#define Btn_Down_GPIO_Port GPIOB
#define D4_PIN_Pin GPIO_PIN_12
#define D4_PIN_GPIO_Port GPIOB
#define D5_PIN_Pin GPIO_PIN_13
#define D5_PIN_GPIO_Port GPIOB
#define D6_PIN_Pin GPIO_PIN_14
#define D6_PIN_GPIO_Port GPIOB
#define D7_PIN_Pin GPIO_PIN_15
#define D7_PIN_GPIO_Port GPIOB
#define LD4_Pin GPIO_PIN_8
#define LD4_GPIO_Port GPIOC
#define LD3_Pin GPIO_PIN_9
#define LD3_GPIO_Port GPIOC
#define TEST_clock_Pin GPIO_PIN_10
#define TEST_clock_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define EN_PIN_Pin GPIO_PIN_3
#define EN_PIN_GPIO_Port GPIOB
#define RS_PIN_Pin GPIO_PIN_4
#define RS_PIN_GPIO_Port GPIOB
#define USART1_RX_Pin GPIO_PIN_7
#define USART1_RX_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

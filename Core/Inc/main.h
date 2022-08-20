/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "defines.h"
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
#define PITCH_ENC1_Pin GPIO_PIN_0
#define PITCH_ENC1_GPIO_Port GPIOC
#define PITCH_ENC2_Pin GPIO_PIN_1
#define PITCH_ENC2_GPIO_Port GPIOC
#define YAW_ENC1_Pin GPIO_PIN_0
#define YAW_ENC1_GPIO_Port GPIOA
#define YAW_ENC2_Pin GPIO_PIN_1
#define YAW_ENC2_GPIO_Port GPIOA
#define PITCH_PWM_Pin GPIO_PIN_4
#define PITCH_PWM_GPIO_Port GPIOA
#define YAW_PWM_Pin GPIO_PIN_6
#define YAW_PWM_GPIO_Port GPIOA
#define ROLLER2_DIR_Pin GPIO_PIN_7
#define ROLLER2_DIR_GPIO_Port GPIOA
#define ROLLER1_PWM_Pin GPIO_PIN_0
#define ROLLER1_PWM_GPIO_Port GPIOB
#define ROLLER2_PWM_Pin GPIO_PIN_1
#define ROLLER2_PWM_GPIO_Port GPIOB
#define PNEU_1_Pin GPIO_PIN_2
#define PNEU_1_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_10
#define SW1_GPIO_Port GPIOB
#define PNEU_3_Pin GPIO_PIN_14
#define PNEU_3_GPIO_Port GPIOB
#define PNEU_2_Pin GPIO_PIN_15
#define PNEU_2_GPIO_Port GPIOB
#define YAW_DIR_Pin GPIO_PIN_7
#define YAW_DIR_GPIO_Port GPIOC
#define PITCH_DIR_Pin GPIO_PIN_9
#define PITCH_DIR_GPIO_Port GPIOA
#define GPIO2_Pin GPIO_PIN_10
#define GPIO2_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_4
#define SW2_GPIO_Port GPIOB
#define GPIO1_Pin GPIO_PIN_5
#define GPIO1_GPIO_Port GPIOB
#define ROLLER1_DIR_Pin GPIO_PIN_6
#define ROLLER1_DIR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

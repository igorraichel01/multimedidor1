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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

void MX_GPIO_InterruptInit(void);
void MX_DMA_Init(void);
void MX_ADC1_Init(void);

extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;




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
#define Led_Pin GPIO_PIN_13
#define Led_GPIO_Port GPIOC
#define Sensor1_Pin GPIO_PIN_1
#define Sensor1_GPIO_Port GPIOA
#define Sensor1  Sensor1_GPIO_Port,Sensor1_Pin 
#define Sensor1_EXTI_IRQn EXTI1_IRQn
#define Sensor2_Pin GPIO_PIN_4
#define Sensor2_GPIO_Port GPIOA
#define Sensor2  Sensor2_GPIO_Port,Sensor2_Pin 
#define Sensor2_EXTI_IRQn EXTI4_IRQn
#define Sensor3_Pin GPIO_PIN_5
#define Sensor3_GPIO_Port GPIOA
#define Sensor3  Sensor3_GPIO_Port,Sensor3_Pin 
#define Sensor3_EXTI_IRQn EXTI9_5_IRQn
#define Sensor0_Pin GPIO_PIN_7
#define Sensor0_GPIO_Port GPIOA
#define Sensor0  Sensor0_GPIO_Port,Sensor0_Pin 
#define Sensor0_EXTI_IRQn EXTI9_5_IRQn
#define Sensor4_Pin GPIO_PIN_0
#define Sensor4_GPIO_Port GPIOB
#define Sensor4  Sensor4_GPIO_Port,Sensor4_Pin 
#define Sensor14 Sensor4_GPIO_Port,Sensor4_Pin 
#define Sensor4_EXTI_IRQn EXTI0_IRQn
#define Coluna1_Pin GPIO_PIN_1
#define Coluna1_GPIO_Port GPIOB
#define Coluna2_Pin GPIO_PIN_2
#define Coluna2_GPIO_Port GPIOB
#define Coluna3_Pin GPIO_PIN_10
#define Coluna3_GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_13
#define D5_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_14
#define D6_GPIO_Port GPIOB
#define D7_Pin GPIO_PIN_15
#define D7_GPIO_Port GPIOB
#define Enable_Pin GPIO_PIN_8
#define Enable_GPIO_Port GPIOA
#define R_W_Pin GPIO_PIN_9
#define R_W_GPIO_Port GPIOA
#define R_S_Pin GPIO_PIN_10
#define R_S_GPIO_Port GPIOA
#define Linha1_Pin GPIO_PIN_7
#define Linha1_GPIO_Port GPIOB
#define Linha2_Pin GPIO_PIN_8
#define Linha2_GPIO_Port GPIOB
#define Coluna4_Pin GPIO_PIN_9
#define Coluna4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

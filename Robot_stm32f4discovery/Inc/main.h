/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define ID_0_Pin GPIO_PIN_4
#define ID_0_GPIO_Port GPIOE
#define ID_1_Pin GPIO_PIN_5
#define ID_1_GPIO_Port GPIOE
#define ID_2_Pin GPIO_PIN_6
#define ID_2_GPIO_Port GPIOE
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define NRF_CE_DELTA_Pin GPIO_PIN_1
#define NRF_CE_DELTA_GPIO_Port GPIOC
#define NRF_MISO_Pin GPIO_PIN_2
#define NRF_MISO_GPIO_Port GPIOC
#define NRF_IRQ_Pin GPIO_PIN_3
#define NRF_IRQ_GPIO_Port GPIOC
#define NRF_IRQ_EXTI_IRQn EXTI3_IRQn
#define MOTOR1_PWM_Pin GPIO_PIN_0
#define MOTOR1_PWM_GPIO_Port GPIOA
#define MOTOR2_ENCB_Pin GPIO_PIN_1
#define MOTOR2_ENCB_GPIO_Port GPIOA
#define MOTOR3_PWM_Pin GPIO_PIN_2
#define MOTOR3_PWM_GPIO_Port GPIOA
#define MOTOR4_PWM_Pin GPIO_PIN_3
#define MOTOR4_PWM_GPIO_Port GPIOA
#define MOTOR2_ENCA_Pin GPIO_PIN_5
#define MOTOR2_ENCA_GPIO_Port GPIOA
#define MOTOR3_ENCA_Pin GPIO_PIN_6
#define MOTOR3_ENCA_GPIO_Port GPIOA
#define MOTOR3_ENCB_Pin GPIO_PIN_7
#define MOTOR3_ENCB_GPIO_Port GPIOA
#define POSITION_SENSOR1_Pin GPIO_PIN_4
#define POSITION_SENSOR1_GPIO_Port GPIOC
#define POSITION_SENSOR2_Pin GPIO_PIN_5
#define POSITION_SENSOR2_GPIO_Port GPIOC
#define MOTOR3_DIR_Pin GPIO_PIN_0
#define MOTOR3_DIR_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define IMU_IRQ_Pin GPIO_PIN_8
#define IMU_IRQ_GPIO_Port GPIOE
#define MOTOR1_ENCA_Pin GPIO_PIN_9
#define MOTOR1_ENCA_GPIO_Port GPIOE
#define MOTOR1_ENCB_Pin GPIO_PIN_11
#define MOTOR1_ENCB_GPIO_Port GPIOE
#define MOTOR1_DIR_Pin GPIO_PIN_13
#define MOTOR1_DIR_GPIO_Port GPIOE
#define MOTOR2_DIR_Pin GPIO_PIN_15
#define MOTOR2_DIR_GPIO_Port GPIOE
#define NRF_CS_Pin GPIO_PIN_12
#define NRF_CS_GPIO_Port GPIOB
#define NRF_SCK_Pin GPIO_PIN_13
#define NRF_SCK_GPIO_Port GPIOB
#define DRIBBLER_PWM_Pin GPIO_PIN_14
#define DRIBBLER_PWM_GPIO_Port GPIOB
#define NRF_MOSI_Pin GPIO_PIN_15
#define NRF_MOSI_GPIO_Port GPIOB
#define BANK_FULL_Pin GPIO_PIN_8
#define BANK_FULL_GPIO_Port GPIOD
#define CHARGE_BANK_Pin GPIO_PIN_9
#define CHARGE_BANK_GPIO_Port GPIOD
#define KICK_Pin GPIO_PIN_10
#define KICK_GPIO_Port GPIOD
#define KICKER_SELECT_Pin GPIO_PIN_11
#define KICKER_SELECT_GPIO_Port GPIOD
#define LD4_GPIO5_Pin GPIO_PIN_12
#define LD4_GPIO5_GPIO_Port GPIOD
#define LD3_GPIO4_Pin GPIO_PIN_13
#define LD3_GPIO4_GPIO_Port GPIOD
#define LD5_GPIO3_Pin GPIO_PIN_14
#define LD5_GPIO3_GPIO_Port GPIOD
#define LD6_GPIO2_Pin GPIO_PIN_15
#define LD6_GPIO2_GPIO_Port GPIOD
#define NRF_CE_GAMMA_Pin GPIO_PIN_6
#define NRF_CE_GAMMA_GPIO_Port GPIOC
#define EN_POWER_Pin GPIO_PIN_7
#define EN_POWER_GPIO_Port GPIOC
#define MOTOR2_PWM_Pin GPIO_PIN_8
#define MOTOR2_PWM_GPIO_Port GPIOC
#define SWITCH_INPUT_Pin GPIO_PIN_9
#define SWITCH_INPUT_GPIO_Port GPIOC
#define DEBUG_SWITCH_Pin GPIO_PIN_8
#define DEBUG_SWITCH_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define NRF_IRQC11_Pin GPIO_PIN_11
#define NRF_IRQC11_GPIO_Port GPIOC
#define NRF_IRQC11_EXTI_IRQn EXTI15_10_IRQn
#define Audio_RST_Pin GPIO_PIN_4
#define Audio_RST_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define MOTOR4_ENCA_Pin GPIO_PIN_6
#define MOTOR4_ENCA_GPIO_Port GPIOB
#define MOTOR4_ENCB_Pin GPIO_PIN_7
#define MOTOR4_ENCB_GPIO_Port GPIOB
#define MOTOR4_DIR_Pin GPIO_PIN_8
#define MOTOR4_DIR_GPIO_Port GPIOB
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * File Name          : bsp_led.h
  * Description        : This file provides code for the configuration
  *                      of all LED GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_LED_H
#define __BSP_LED_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

 /* Exported constants --------------------------------------------------------*/
 /**
  * @brief LED GPIO Definition
  */
#define LED_RED_Pin         GPIO_PIN_14
#define LED_RED_GPIO_Port   GPIOB

#define LED_GREEN_Pin       GPIO_PIN_0
#define LED_GREEN_GPIO_Port GPIOB

#define LED_BLUE_Pin        GPIO_PIN_7
#define LED_BLUE_GPIO_Port  GPIOB

 /**
  * @brief Unqualified shortcuts for use in On, Off, Toggle
  */
#define LED_RED             LED_RED_Pin
#define LED_GREEN           LED_GREEN_Pin
#define LED_BLUE            LED_BLUE_Pin


 /* Exported functions ------------------------------------------------------- */
void BSP_LED_Init(void);
void BSP_LED_On(uint16_t Led);
void BSP_LED_Off(uint16_t Led);
void BSP_LED_Toggle(uint16_t Led);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_LED_H */

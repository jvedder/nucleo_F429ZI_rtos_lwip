/**
  ******************************************************************************
  * @file       : bsp_button.h
  * @brief      : This file provides code for the configuration
  *               of the Button GPIO pin.
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
#ifndef __BUTTON_H
#define __BUTTON_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported constants --------------------------------------------------------*/
/**
 * @brief User Button GPIO Definition
 */
#define BUTTON_USER_Pin         GPIO_PIN_13
#define BUTTON_USER_GPIO_Port   GPIOC

/* Exported functions ------------------------------------------------------- */
void BSP_Button_Init(void);
uint32_t BSP_Button_GetState(void);


#ifdef __cplusplus
}
#endif

#endif /* __BUTTON_H */

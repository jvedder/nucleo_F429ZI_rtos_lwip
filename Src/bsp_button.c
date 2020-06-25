/**
  ******************************************************************************
  * @file       : bsp_button.c
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
  
/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/**
  * @brief  Configures Button GPIO pin.
  *
  */
void BSP_Button_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* Enable the User Button GPIO Clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  
  /*Configure User Button GPIO pin  */
  GPIO_InitStruct.Pin = BUTTON_USER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(BUTTON_USER_GPIO_Port, &GPIO_InitStruct);
  
}

/**
  * @brief  Returns the User Button state.
  * @retval The Button GPIO pin value.
  *
  */
uint32_t BSP_Button_GetState(void)
{
  return HAL_GPIO_ReadPin(BUTTON_USER_GPIO_Port, BUTTON_USER_Pin);
}


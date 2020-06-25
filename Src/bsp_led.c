/**
  ******************************************************************************
  * File Name          : bsp_led.c
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

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

/**
  * @brief  Configures LED GPIO pins as outputs and turns off all LEDs.
  */
void BSP_LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Enable the LED GPIO Clock */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_GREEN_Pin | LED_RED_Pin | LED_BLUE_Pin, GPIO_PIN_RESET);

  /*Configure LED GPIO pins */
  GPIO_InitStruct.Pin = LED_GREEN_Pin | LED_RED_Pin | LED_BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *   RED, GREEN, BLUE
  */
void BSP_LED_On(uint16_t Led)
{
  HAL_GPIO_WritePin(GPIOB, Led, GPIO_PIN_SET);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *   RED, GREEN, BLUE
  */
void BSP_LED_Off(uint16_t Led)
{
  HAL_GPIO_WritePin(GPIOB, Led, GPIO_PIN_RESET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *   RED, GREEN, BLUE
  */
void BSP_LED_Toggle(uint16_t Led)
{
  HAL_GPIO_TogglePin(GPIOB, Led);
}

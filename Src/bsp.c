/**
  ******************************************************************************
  * File Name          : bsp.c
  * Description        : This file provides configuration for the
  *                      STM32F429ZI on the Nucleo-f429zi board
  *                      made my ST Microelectronics.
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bsp.h"


/**
  * @brief  Configures the peripherals for this board.
  */
void BSP_Init(void)
{
    /* Configure all 3 LEDs */
    BSP_LED_Init( );

    /* Configure the User Push Button */
    BSP_Button_Init( );

    /* Configure UART3 -- used as the ST-LINK serial port */
    BSP_UART_Init();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void BSP_Error_Handler(void)
{
    /* Wait here for the debugger to find us */
    while(1);
}

/**
  ******************************************************************************
  * File Name          : bsp.h
  * Description        : This file provides configuration for the
  *                      STM32F429ZI on the Nucleo-f429zi board
  *                      made my ST Microelectronics.
  ******************************************************************************
  */

  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H
#define __BSP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "bsp_led.h"
#include "bsp_button.h"
#include "bsp_uart.h"
   
/* Exported functions ------------------------------------------------------- */
void BSP_Init(void);
void BSP_Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_H */

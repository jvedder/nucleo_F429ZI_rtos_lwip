/**
  ******************************************************************************
  * File Name          : UART.h
  * Description        : This file provides code for the configuration
  *                      of the USART / UART instances.
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
#ifndef __BSP_UART_H
#define __BSP_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

 /* Exported constants --------------------------------------------------------*/
 /**
  * @brief UART to SL-Link GPIO Definition
  */
#define STLINK_RX_Pin       GPIO_PIN_8
#define STLINK_RX_GPIO_Port GPIOD
#define STLINK_TX_Pin       GPIO_PIN_9
#define STLINK_TX_GPIO_Port GPIOD

 /* Exported variables -------------------------------------------------------*/
extern UART_HandleTypeDef huart3;


/* Exported functions ------------------------------------------------------- */
void BSP_UART_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_UART_H */

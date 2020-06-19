/**
  ******************************************************************************
  * @file           : UART3_stdout.c
  * @brief          : Utilities make stdout point to UART3, which is the ST-Link
  *                   serial port.
  ******************************************************************************
  *
  ******************************************************************************
  */

#include "main.h"

int __io_putchar(int ch)
{
    //TODO: Move this to _write(..) in syscalls.c

    /* Write a character to the UART and block until transmitted */
    HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 1000);
    return ch;
}

int __io_getchar(void)
{
    //TODO: Move this to _read(..) in syscalls.c

    int ch;
    /* Read a character from UART and block until received */
    HAL_UART_Receive(&huart3, (uint8_t *)&ch, 1, 1000);
    return ch;
}


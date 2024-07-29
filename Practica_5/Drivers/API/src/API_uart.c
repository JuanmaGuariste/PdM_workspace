/*
 * API_uart.c
 *
 *  Created on: Jul 25, 2024
 *      Author: juanma
 */


#include "API_uart.h"

#define UART_TIME_OUT		0xFFFF

static void uartError_Handler();


UART_HandleTypeDef UartHandle;

bool_t uartInit() {
  UartHandle.Instance        = USARTx;
  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_ODD;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&UartHandle) != HAL_OK)
  {
	/* Initialization Error */
	  uartError_Handler();
	  return false;
  }
  return true;
}

void uartSendString(uint8_t *pstring){
	HAL_UART_Transmit(&UartHandle, (uint8_t *)pstring, strlen((char*)pstring), UART_TIME_OUT);
}

static void uartError_Handler() {
	BSP_LED_On(LED2);
	while (1) {
	}
}



/*
 * API_uart.h
 *
 *  Created on: Jul 25, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3


typedef bool bool_t;

bool_t uartInit();

void uartSendString(uint8_t * pstring);

void uartSendStringSize(uint8_t * pstring, uint16_t size);

void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */

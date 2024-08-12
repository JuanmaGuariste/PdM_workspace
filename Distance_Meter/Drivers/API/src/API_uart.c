/*
 * API_uart.c
 *
 *  Created on: Jul 25, 2024
 *      Author: juanma
 */
#include "API_uart.h"

static void uartErrorHandler(void);
static void displaySuccessUartConfig(void);
static UART_HandleTypeDef UartHandle;

/**
 * @brief Initializes the UART with the specified parameters.
 *
 * Configures the UART with the baud rate, word length, stop bits, parity,
 * flow control, and operation mode specified. If the initialization is successful,
 * `displaySuccessUartConfig()` is called to show the configuration parameters.
 * If an error occurs during initialization, `uartErrorHandler()` are called to handle the error.
 *
 * @retval True if the initialization is successful.
 * @retval False if the initialization fails.
 */
bool_t
uartInit (void)
{
  UartHandle.Instance        = USARTx;
  UartHandle.Init.BaudRate   = BOUD_RATE;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_ODD;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&UartHandle) != HAL_OK)
  {
	/* Initialization Error */
	  uartErrorHandler();
	  return (false);
  }
  displaySuccessUartConfig();
  return (true);
}

/**
 * @brief Sends a string of characters through UART.
 *
 * This function sends a complete string (up to the null character '\0') through UART.
 * It checks that the pointer to the string is not NULL and that the buffer length
 * does not exceed the allowed size. It uses the HAL function `HAL_UART_Transmit()`
 * to transmit the data.
 *
 * @param pstring Pointer to the string to be sent.
 */
void
uartSendString (uint8_t *pstring)
{
	if (pstring == NULL) return;
	uint8_t uartBufferLength = strlen((char*) pstring);
	if (uartBufferLength > UART_BUFFER_SIZE) return;
	if (HAL_OK != HAL_UART_Transmit(&UartHandle, (uint8_t*) pstring, strlen((char*) pstring), UART_TIME_OUT))
	{
		uartErrorHandler();
	}
}

/**
 * @brief Sends a specific number of characters through UART.
 *
 * This function sends a specified number of characters from the provided pointer.
 * It checks that the pointer is not NULL and that the size does not exceed the maximum allowed size.
 * It uses the HAL function `HAL_UART_Transmit()` to transmit the data.
 *
 * @param pstring Pointer to the string to be sent.
 * @param size Number of characters to be sent.
 */
void
uartSendStringSize (uint8_t *pstring, uint16_t size)
{
	if (pstring == NULL || size > UART_BUFFER_SIZE)
	{
		return;
	}
	if (HAL_OK != HAL_UART_Transmit(&UartHandle, pstring, size, UART_TIME_OUT))
	{
		uartErrorHandler();
	}
}

/**
 * @brief Receives a specific number of characters through UART.
 *
 * This function receives a specified number of characters and stores them in the provided pointer.
 * It checks that the pointer is not NULL, that the size is reasonable, and that the size is greater than zero.
 * It uses the HAL function `HAL_UART_Receive()` to receive the data.
 *
 * @param pstring Pointer to the buffer where the received data will be stored.
 * @param size Number of characters to be received.
 */
void
uartReceiveStringSize (uint8_t *pstring, uint16_t size)
{
	if (pstring == NULL || size > UART_BUFFER_SIZE || 0 < size)
	{
		return;
	}
	if (HAL_OK != HAL_UART_Receive(&UartHandle, pstring, size, UART_TIME_OUT))
	{
		uartErrorHandler();
	}
}

/**
 * @brief Displays a message indicating successful UART configuration.
 *
 * This function creates a formatted string that contains the UART configuration parameters
 * and sends it through UART. The message includes baud rate, word length, stop bits, parity,
 * and flow control settings.
 *
 * @param None
 * @retval None
 */
static void
displaySuccessUartConfig(void)
{
    char buffer[UART_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer),
    		 "\nUART Initialization Successful:\r\n"
			 "------------------------------\r\n"
			 "Baud Rate    : 9600\r\n"
			 "Word Length  : 8 bits\r\n"
			 "Stop Bits    : 1\r\n"
			 "Parity       : Odd\r\n"
			 "Flow Control : None\r\n");
    uartSendString((uint8_t *) buffer);
}

/**
 * @brief Handles UART errors by entering an infinite loop with an LED indicator.
 *
 * This function is called when a UART error occurs. It enters an infinite loop
 * and continuously turns on an LED (LED2) to indicate the error state.
 *
 * @param None
 * @retval None
 */
static void
uartErrorHandler(void)
{
	while (1)
	{
	}
}


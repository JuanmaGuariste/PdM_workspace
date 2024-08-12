/*
 * API_ledmatrix_port.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_ledmatrix_port.h"
#include "stm32f4xx_hal.h"

static SPI_HandleTypeDef SPI_HANDLE;
static bool_t port_spiInit(void);
static void initCsGPIO(void);

/**
 * @brief Initializes the port used by the  LED MATRIX.
 *
 * @param void
 * @return bool_t Returns true if the initialization was successful, otherwise false.
 */
bool_t
port_initSPI ()
{
	initCsGPIO();
	return (port_spiInit());
}

/**
 * @brief Initializes the SPI1 interface.
 *
 * @return bool_t Returns true if the initialization was successful, otherwise false.
 */
static bool_t
port_spiInit (void)
{
  /* SPI1 parameter configuration*/
  SPI_HANDLE.Instance = SPI1;
  SPI_HANDLE.Init.Mode = SPI_MODE_MASTER;
  SPI_HANDLE.Init.Direction = SPI_DIRECTION_2LINES;
  SPI_HANDLE.Init.DataSize = SPI_DATASIZE_8BIT;
  SPI_HANDLE.Init.CLKPolarity = SPI_POLARITY_LOW;
  SPI_HANDLE.Init.CLKPhase = SPI_PHASE_1EDGE;
  SPI_HANDLE.Init.NSS = SPI_NSS_SOFT;
  SPI_HANDLE.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  SPI_HANDLE.Init.FirstBit = SPI_FIRSTBIT_MSB;
  SPI_HANDLE.Init.TIMode = SPI_TIMODE_DISABLE;
  SPI_HANDLE.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  SPI_HANDLE.Init.CRCPolynomial = 10;
  bool_t estado = false;
  if (HAL_SPI_Init(&SPI_HANDLE) == HAL_OK)
  {
      estado = true;
  }
  return (estado);
}

/**
 * @brief Initializes the GPIO pin used for chip select (CS) for the LED matrix.
 *
 * @return void
 */
static void
initCsGPIO (void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOD_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_LED_MATRIX_GPIO_Port, CS_LED_MATRIX_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin : CS_LED_MATRIX_Pin */
  GPIO_InitStruct.Pin = CS_LED_MATRIX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_LED_MATRIX_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief Sends a message to the LED matrix via the SPI port.
 *
 * @param reg The register address to write to.
 * @param data The data to write to the register.
 */
void
MATRIXLED_portSendMsg (uint8_t reg, uint8_t data)
{
	HAL_GPIO_WritePin(CS_LED_MATRIX_GPIO_Port, CS_LED_MATRIX_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI_HANDLE, &reg, 1, SPI_TIMEOUT);
	while(HAL_SPI_GetState(&SPI_HANDLE) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&SPI_HANDLE, &data, 1, SPI_TIMEOUT);
	while(HAL_SPI_GetState(&SPI_HANDLE) != HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(CS_LED_MATRIX_GPIO_Port, CS_LED_MATRIX_Pin, GPIO_PIN_SET);
}

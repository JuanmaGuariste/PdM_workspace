/*
 * API_lcd_port.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_lcd_port.h"

static I2C_HandleTypeDef I2C_HANDLE;

static bool_t port_i2cInit(void);

/**
 * @brief Initializes the port used by the LCD.
 *
 * @param void
 * @return bool_t Returns true if the initialization was successful, otherwise false.
 */
bool_t
port_init (void)
{
	return (port_i2cInit());
}

/**
 * @brief Initializes the I2C port with configured parameters.
 *
 * @param void
 * @return bool_t Returns true if the initialization was successful, otherwise false.
 */
static bool_t
port_i2cInit (void)
{
	I2C_HANDLE.Instance = I2C_INSTANCE;
	I2C_HANDLE.Init.ClockSpeed = I2C_CLOCK_SPEED;
	I2C_HANDLE.Init.DutyCycle = I2C_DUTYCYCLE_2;
	I2C_HANDLE.Init.OwnAddress1 = 0;
	I2C_HANDLE.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C_HANDLE.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2C_HANDLE.Init.OwnAddress2 = 0;
	I2C_HANDLE.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C_HANDLE.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	bool_t estado = false;

	if (HAL_I2C_Init(&I2C_HANDLE) == HAL_OK)
	{
		estado = true;
	}

	return (estado);
}

/**
 * @brief Introduces a delay.
 *
 * @param delay Amount of time to delay in milliseconds.
 * @return void
 */
void
LCD_portDelay (uint32_t delay)
{
	  HAL_Delay(delay);
}

/**
 * @brief Writes a byte to the I2C port.
 *
 * @param byte Byte to write.
 * @return bool_t Returns true if the write was successful, otherwise false.
 */
bool_t
LCD_portWriteByte (uint8_t byte)
{
	if (HAL_I2C_Master_Transmit(&I2C_HANDLE, LCD_ADDRESS << 1, &byte, 1, 100) == HAL_OK)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

/*
 * API_delay_port.c
 *
 *  Created on: Aug 12, 2024
 *      Author: juanma
 */
#include "API_delay_port.h"
#include "stm32f4xx_hal.h"

/**
 * @brief Retrieves the current tick value from the HAL library.

 * @param void This function does not take any parameters.
 * @return tick_t The current tick value in milliseconds.
 */
tick_t
DELAY_portGetTick ()
{
	return (HAL_GetTick());
}

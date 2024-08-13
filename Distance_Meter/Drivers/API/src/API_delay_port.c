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

/**
 * @brief Implements a blocking delay at the port level.
 *
 * This function uses the HAL library's `HAL_Delay()` function to create a blocking delay
 * of the specified duration. The delay prevents the execution of any further instructions
 * until the specified time has elapsed.
 *
 * @param delay Duration of the delay in milliseconds.
 * @retval None
 */
void
DELAY_portBlockingDelay (uint32_t delay)
{
	HAL_Delay(delay);
}

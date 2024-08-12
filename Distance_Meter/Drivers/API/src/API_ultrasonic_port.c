/*
 * API_ultrasonic_port.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_ultrasonic_port.h"

#define TRIGGER_DELAY			10

static usDelay_t triggerDelay;
static void initTriggerGPIO(void);

/**
 * @brief Initializes the GPIO used for triggering the ultrasonic sensor.
 *
 * This function configures the GPIO pin connected to the ultrasonic sensor's trigger.
 *
 * @param None
 * @retval None
 */
static void
initTriggerGPIO (void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
	  /*Configure GPIO pin : TRIGGER_Pin */
	  GPIO_InitStruct.Pin = TRIGGER_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(TRIGGER_GPIO_Port, &GPIO_InitStruct);
}
/**
 * @brief Initializes the ultrasonic sensor port.
 * @param None
 * @retval None
 */
bool_t
ULTRASONIC_portInit (void)
{
	initTriggerGPIO();
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
	TIMER_StartInterrupt();
	usDelayInit(&triggerDelay, TRIGGER_DELAY);
	return (false);
}

/**
 * @brief Generates a non-blocking trigger pulse for the ultrasonic sensor.
 *
 * This function sets the trigger pin high to start the ultrasonic sensor's trigger pulse,
 * then waits for a specified non-blocking delay using `usDelayRead`. After the delay has
 * elapsed, the trigger pin is set low to complete the pulse. The function returns `true`
 * if the pulse has been successfully generated, otherwise it returns `false` to indicate
 * the pulse is still in progress. *
 *
 * @param None
 * @return true if the trigger pulse has been successfully generated, false otherwise.
 */
bool_t
ULTRASONIC_portTriggerSignal (void)
{
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_SET);
	if (usDelayRead(&triggerDelay))
	{
		return (false);
	}
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
	return (true);
}

/**
 * @brief Reads the echo signal from the ultrasonic sensor.
 * @param None
 * @retval Pulse duration in microseconds.
 */
float
ULTRASONIC_portReadEchoSignal (void)
{
	TIMER_enableInterrupt();
	return (TIMER_getPulse());
}

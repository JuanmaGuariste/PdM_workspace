/*
 * API_ultrasonic_port.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_ultrasonic_port.h"

#define TRIGGER_DELAY			10

static usDelay_t triggerDelay;
/**
 * @brief Initializes the ultrasonic sensor port.
 * @param None
 * @retval None
 */
void ULTRASONIC_portInit() {
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
	TIMER_StartInterrupt();
	usDelayInit(&triggerDelay, TRIGGER_DELAY);
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
bool_t ULTRASONIC_portTriggerSignal() {
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_SET);
	if (usDelayRead(&triggerDelay)) {
		return false;
	}
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
	return true;
}

/**
 * @brief Reads the echo signal from the ultrasonic sensor.
 * @param None
 * @retval Pulse duration in microseconds.
 */
float ULTRASONIC_portReadEchoSignal() {
	TIMER_enableInterrupt();
	return TIMER_getPulse();
}

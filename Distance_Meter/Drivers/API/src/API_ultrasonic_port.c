/*
 * API_ultrasonic_port.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_ultrasonic_port.h"
/**
 * @brief Initializes the ultrasonic sensor port.
 * @param None
 * @retval None
 */
void ULTRASONIC_portInit() {
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
	TIMER_StartInterrupt();
}

/**
 * @brief Sends a trigger signal to the ultrasonic sensor.
 * @param None
 * @retval None
 */
void ULTRASONIC_portTriggerSignal() {
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_SET);
	TIMER_usDelay(10);
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
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

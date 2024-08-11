/*
 * API_ultrasonic.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_ultrasonic.h"

/**
 * @brief Initializes the ultrasonic sensor.
 *
 * This function sets up the necessary configurations for the ultrasonic sensor.
 *
 * @param None
 * @retval None
 */
void ULTRASONIC_init() {
	ULTRASONIC_portInit();
}

/**
 * @brief Reads the echo signal duration from the ultrasonic sensor.
 *
 * @param None
 * @return float The duration of the echo signal in microseconds.
 */
float ULTRASONIC_readEchoSignal(){
	return ULTRASONIC_portReadEchoSignal();
}

/**
 * @brief Triggers the ultrasonic sensor to send a pulse.
 *
 * This function generates a trigger pulse for the ultrasonic sensor.
 *
 * @param None
 * @return bool_t `true` if the trigger pulse has been successfully generated, `false` otherwise.
 */
bool_t ULTRASONIC_triggerSignal(){
	return ULTRASONIC_portTriggerSignal();
}

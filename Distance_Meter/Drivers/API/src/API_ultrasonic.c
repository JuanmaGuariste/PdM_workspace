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
 * This function sets up the necessary configurations for the ultrasonic sensor by calling
 * the `ULTRASONIC_portInit()` function. It returns a status indicating whether the initialization
 * was successful.
 *
 * @param void This function does not take any parameters.
 * @return ULTRASONIC_StatusTypedef Returns ULTRASONIC_OK if the sensor was initialized correctly,
 *         otherwise ULTRASONIC_FAIL.
 */
ULTRASONIC_StatusTypedef
ULTRASONIC_init (void)
{
	return (ULTRASONIC_portInit());
}

/**
 * @brief Reads the echo signal duration from the ultrasonic sensor.
 *
 * @param None
 * @return float The duration of the echo signal in microseconds.
 */
float
ULTRASONIC_readEchoSignal ()
{
	return (ULTRASONIC_portReadEchoSignal());
}

/**
 * @brief Triggers the ultrasonic sensor to send a pulse.
 *
 * This function generates a trigger pulse for the ultrasonic sensor.
 *
 * @param None
 * @return bool_t `true` if the trigger pulse has been successfully generated, `false` otherwise.
 */
ULTRASONIC_StatusTypedef
ULTRASONIC_triggerSignal ()
{
	return (ULTRASONIC_portTriggerSignal());
}

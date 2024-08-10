/*
 * API_ultrasonic.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_ultrasonic.h"

static float dist = 0;
static float time = 0;
static const float speedOfSound = 0.0343 / 2;

static float timeToDistanceConvertion(float time);

/**
 * @brief Initializes the ultrasonic sensor.
 * @param None
 * @retval None
 */
void ULTRASONIC_init() {
	ULTRASONIC_portInit();
}

/**
 * @brief Gets the distance measured by the ultrasonic sensor.
 * @param None
 * @retval Distance measured in centimeters.
 */
float ULTRASONIC_getDistance() {
	ULTRASONIC_portTriggerSignal();
	time = ULTRASONIC_portReadEchoSignal();
	dist = timeToDistanceConvertion(time);
	return dist;
}

/**
 * @brief Converts time to distance.
 * @param time: Time duration in microseconds.
 * @retval Distance in centimeters.
 */
static float timeToDistanceConvertion(float time) {
	return (time * speedOfSound);
}

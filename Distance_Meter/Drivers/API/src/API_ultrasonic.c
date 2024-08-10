/*
 * API_ultrasonic.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_ultrasonic.h"

/**
 * @brief Initializes the ultrasonic sensor.
 * @param None
 * @retval None
 */
void ULTRASONIC_init() {
	ULTRASONIC_portInit();
}

void ULTRASONIC_triggerSignal(){
	ULTRASONIC_portTriggerSignal();
}

float ULTRASONIC_readEchoSignal(){
	return ULTRASONIC_portReadEchoSignal();
}



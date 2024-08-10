/*
 * API_ultrasonic.h
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_ULTRASONIC_H_
#define API_INC_API_ULTRASONIC_H_
#include "stm32f4xx_hal.h"
#include "API_ultrasonic_port.h"


void ULTRASONIC_init();
void ULTRASONIC_triggerSignal();
float ULTRASONIC_readEchoSignal();
float ULTRASONIC_portReadEchoSignal();

#endif /* API_INC_API_ULTRASONIC_H_ */

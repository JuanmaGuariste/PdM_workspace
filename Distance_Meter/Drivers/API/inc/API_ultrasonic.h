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

typedef bool bool_t;

void ULTRASONIC_init(void);
bool_t ULTRASONIC_triggerSignal(void);
float ULTRASONIC_readEchoSignal(void);
float ULTRASONIC_portReadEchoSignal(void);

#endif /* API_INC_API_ULTRASONIC_H_ */

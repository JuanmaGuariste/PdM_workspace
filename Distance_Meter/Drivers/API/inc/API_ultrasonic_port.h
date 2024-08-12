/*
 * API_ultrasonic_port.h
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_ULTRASONIC_PORT_H_
#define API_INC_API_ULTRASONIC_PORT_H_
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "API_timer.h"
#include "stdbool.h"

#define TRIGGER_Pin GPIO_PIN_12
#define TRIGGER_GPIO_Port GPIOF

void ULTRASONIC_portInit(void);
bool_t ULTRASONIC_portTriggerSignal(void);

#endif /* API_INC_API_ULTRASONIC_PORT_H_ */

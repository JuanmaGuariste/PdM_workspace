/*//		BSP_LED_On(LED2);
 *
 * API_timer_port.h
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_TIMER_PORT_H_
#define API_INC_API_TIMER_PORT_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_tim.h"
#include "main.h"


void TIMER_portStart();
void TIMER_portInit(void);
void TIMER_portDelay(uint32_t time);
void TIMER_captureEdges(void);
void TIMER_portEnableInterrupt();
float TIMER_getPulseDuration(void);
void TIMER_portStartInterrupt();
uint32_t TIMER_portGetTimerCounter();

#endif /* API_INC_API_TIMER_PORT_H_ */

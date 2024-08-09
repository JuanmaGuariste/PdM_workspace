/*
 * API_timer.h
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_TIMER_H_
#define API_INC_API_TIMER_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "API_timer_port.h"

typedef bool bool_t;

void MX_TIM2_Init(void);
void TIMER_usDelay(uint32_t time);
void TIMER_start();
void TIMER_init();
#endif /* API_INC_API_TIMER_H_ */

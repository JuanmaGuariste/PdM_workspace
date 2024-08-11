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

typedef uint32_t tick_t;

typedef struct{
   tick_t usStartTime;
   tick_t usDuration;
   bool_t usRunning;
} usDelay_t;


void usDelayInit( usDelay_t * delay, tick_t duration );

bool_t usDelayRead( usDelay_t * delay );


void MX_TIM2_Init(void);
void TIMER_usDelay(uint32_t time);
void TIMER_start();
void TIMER_init();
uint32_t TIMER_getRisingEdge(void);
uint32_t TIMER_getFallingEdge(void);
float TIMER_getPulse();
void TIMER_enableInterrupt();
void TIMER_StartInterrupt(void);

#endif /* API_INC_API_TIMER_H_ */

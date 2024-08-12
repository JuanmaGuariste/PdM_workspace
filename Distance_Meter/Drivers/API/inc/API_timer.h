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
typedef struct
{
   tick_t usStartTime;
   tick_t usDuration;
   bool_t usRunning;
} usDelay_t;

typedef enum
{
	TIMER_OK,
	TIMER_FAIL
} TIMER_StatusTypedef;

bool_t usDelayRead(usDelay_t * delay);
void usDelayInit(usDelay_t * delay, tick_t duration);
void MX_TIM2_Init(void);
void TIMER_usDelay(uint32_t time);
TIMER_StatusTypedef TIMER_start(void);
TIMER_StatusTypedef TIMER_init(void);
void TIMER_enableInterrupt(void);
void TIMER_StartInterrupt(void);
float TIMER_getPulse(void);
uint32_t TIMER_getRisingEdge(void);
uint32_t TIMER_getFallingEdge(void);

#endif /* API_INC_API_TIMER_H_ */

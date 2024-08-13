/*
 * API_delay.h
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "API_delay_port.h"

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct
{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

typedef enum
{
	DELAY_OK,
	DELAY_FAIL
} DELAY_StatusTypedef;

DELAY_StatusTypedef delayInit(delay_t * delay, tick_t duration);

bool_t delayRead(delay_t * delay );

void delayWrite(delay_t * delay, tick_t duration);

bool_t delayIsRunning(delay_t * delay);

void DELAY_blockingDelay (uint32_t delay);

#endif /* API_INC_API_DELAY_H_ */

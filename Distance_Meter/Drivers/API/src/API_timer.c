/*
 * API_timer.c
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */

#include "API_timer.h"
#include "stm32f4xx_hal_tim.h"

void TIMER_usDelay(uint32_t time){
	TIMER_portDelay(time);
}

void TIMER_start(){
	TIMER_portStart();
}

void TIMER_init(){
	TIMER_portInit();
}

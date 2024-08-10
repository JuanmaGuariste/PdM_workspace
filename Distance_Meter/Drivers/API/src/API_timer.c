/*
 * API_timer.c
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */

#include "API_timer.h"

/**
 * @brief Introduces a delay in microseconds.
 * @param time: Time in microseconds to wait.
 * @retval None
 */
void TIMER_usDelay(uint32_t time){
	TIMER_portDelay(time);
}


/**
 * @brief Starts the timer.
 * @param None
 * @retval None
 */
void TIMER_start(){
	TIMER_portStart();
}

/**
 * @brief Initializes the timer.
 * @param None
 * @retval None
 */
void TIMER_init(){
	TIMER_portInit();
}

/**
 * @brief Enables timer interrupts.
 * @param None
 * @retval None
 */
void TIMER_enableInterrupt(){
	TIMER_portEnableInterrupt();
}

/**
 * @brief Gets the captured pulse duration.
 * @param None
 * @retval Pulse duration in microseconds.
 */
float TIMER_getPulse(void){
	return TIMER_getPulseDuration();
}

/**
 * @brief Starts the timer interrupt capture.
 * @param None
 * @retval None
 */
void TIMER_StartInterrupt(void){
	TIMER_portStartInterrupt();
}

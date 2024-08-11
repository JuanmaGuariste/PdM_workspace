/*
 * API_timer.c
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */

#include "API_timer.h"

#define	MAX_DELAY_US	60000
#define	MIN_DELAY_US	1

static void usDelayErrorHandler(void);


void usDelayInit(usDelay_t *delay, tick_t duration) {
	if (delay == NULL) { //Verify that pointer is not null
		usDelayErrorHandler();
	}
	if (((duration > MAX_DELAY_US) || (duration < MIN_DELAY_US))) { // Check if the duration is within the valid range
		usDelayErrorHandler();
	}
	delay->usDuration = duration;
	delay->usRunning = false;
}

bool_t usDelayRead(usDelay_t *delay) {
	if (delay == NULL) { //Verify that pointer is not null
		usDelayErrorHandler();
	}
	if (((delay->usDuration > MAX_DELAY_US) || (delay->usDuration < MIN_DELAY_US))) { // Check if the duration is within the valid range
		usDelayErrorHandler();
	}
	tick_t currentTime =  TIMER_portGetTimerCounter();
	bool_t timerState = false;
	if (!(delay->usRunning)) {
		delay->usStartTime = currentTime;
		delay->usRunning = true;
		timerState = true;
	} else {
		if ((currentTime - delay->usStartTime) >= delay->usDuration) {
			timerState = false;
			delay->usRunning = false;
		} else {
			timerState = true;
			delay->usRunning = true;
		}
	}

	return timerState;
}

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

static void usDelayErrorHandler(){
	while(1){}
}

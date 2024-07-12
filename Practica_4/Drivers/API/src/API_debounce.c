/*
 * API_debounce.c
 *
 *  Created on: Jul 11, 2024
 *      Author: juanma
 */

/* Includes ------------------------------------------------------------------*/
#include "API_debounce.h"
#include "API_delay.h"
#include "main.h"

#define DEBOUNCEtIME 40

static void buttonPressed(void);
static void buttonReleased(void);

typedef enum {
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

debounceState_t estadoActual;

delay_t debounceDelay;

void debounceFSM_init() {
	estadoActual = BUTTON_UP;
	delayInit(&debounceDelay, DEBOUNCEtIME);
	BSP_LED_On(LED1);
}

void debounceFSM_update() {
	switch (estadoActual) {
		case BUTTON_UP:
			if(!BSP_PB_GetState(BUTTON_USER)){
				estadoActual = BUTTON_FALLING;
			}
		break;
		case BUTTON_FALLING:
			if(!delayRead(&debounceDelay)){
				if(!BSP_PB_GetState(BUTTON_USER)){
					buttonPressed();
					estadoActual = BUTTON_DOWN;
				}
			}
		break;
		case BUTTON_DOWN:
			if (BSP_PB_GetState(BUTTON_USER)) {
				estadoActual = BUTTON_RAISING;
			}
		break;
		case BUTTON_RAISING:
			if (!delayRead(&debounceDelay)) {
				if (BSP_PB_GetState(BUTTON_USER)) {
					buttonReleased();
					estadoActual = BUTTON_UP;
				}
			}
		break;
		default:
			debounceFSM_init();
		break;
		}
}

static void buttonPressed(){
	BSP_LED_Off(LED1);
}

static void buttonReleased(){
	BSP_LED_On(LED1);
}

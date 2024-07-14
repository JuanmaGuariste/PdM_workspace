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

/**
 * @brief  Initialize the debounce finite state machine.
 *
 * This function initializes the debounce state machine by setting the initial
 * state to BUTTON_UP, initializing the debounce delay timer with a predefined
 * debounce time, and turning on the LED1 as initial state.
 *
 * @param  None
 * @retval None
 */
void debounceFSM_init() {
	estadoActual = BUTTON_UP;
	delayInit(&debounceDelay, DEBOUNCEtIME);
	BSP_LED_On(LED1);
}

/**
 * @brief  Update the debounce finite state machine.
 *
 * This function updates the state of the debounce state machine based on the
 * current state and the state of the user button. It handles state transitions
 * and debounce timing to ensure reliable button press and release detection.
 *
 * @param  None
 * @retval None
 */
void debounceFSM_update() {
	switch (estadoActual) {
		case BUTTON_UP:
			if(BSP_PB_GetState(BUTTON_USER)){
				estadoActual = BUTTON_FALLING;
			}
		break;
		case BUTTON_FALLING:
			if(!delayRead(&debounceDelay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					buttonPressed();
					estadoActual = BUTTON_DOWN;
				}
			}
		break;
		case BUTTON_DOWN:
			if (!BSP_PB_GetState(BUTTON_USER)) {
				estadoActual = BUTTON_RAISING;
			}
		break;
		case BUTTON_RAISING:
			if (!delayRead(&debounceDelay)) {
				if (!BSP_PB_GetState(BUTTON_USER)) {
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

/**
 * @brief  Handle button press event.
 *
 * This static function is called when the button is pressed. It turns off LED1
 * to indicate the button press event.
 *
 * @param  None
 * @retval None
 */
static void buttonPressed(){
	BSP_LED_Off(LED1);
}

/**
 * @brief  Handle button release event.
 *
 * This static function is called when the button is released. It turns on LED1
 * to indicate the button release event.
 *
 * @param  None
 * @retval None
 */
static void buttonReleased(){
	BSP_LED_On(LED1);
}

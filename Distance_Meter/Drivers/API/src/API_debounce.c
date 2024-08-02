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
#include "API_uart.h"

#define DEBOUNCE_TIME 40

static void setKey(void);
static void buttonPressed();
static void buttonReleased();

static debounceState_t estadoActual;
static delay_t debounceDelay;
static bool_t fallingEdge = true;

/**
 * @brief  Initialize the debounce finite state machine.
 *
 * Initializes the debounce state machine by setting the initial
 * state to BUTTON_UP, initializing the debounce delay timer with a predefined
 * debounce time, and turning on the LED1 as initial state.
 *
 * @param  None
 * @retval None
 */
void debounceFSM_init() {
	estadoActual = BUTTON_UP;
	delayInit(&debounceDelay, DEBOUNCE_TIME);
	BSP_LED_On(LED1);
}

/**
 * @brief  Update the debounce finite state machine.
 *
 * Udate the state of the debounce state machine based on the
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
					estadoActual = BUTTON_UP;
					buttonReleased();
				}
			}
		break;
		default:
			debounceFSM_init();
		break;
		}
}

/**
 * @brief  Read the key state.
 *
 * Returns the current state of the falling edge flag, which
 * indicates whether a falling edge (button press) has been detected. It also
 * resets the falling edge flag to false after reading.
 *
 * @param  None
 * @retval bool_t - The current state of the falling edge flag.
 */
bool_t readKey(void){
	bool_t aux = fallingEdge;
	fallingEdge = false;
	return aux;
}

/**
 * @brief  Set the key state.
 *
 * Sets the falling edge flag to true, indicating that a
 * falling edge (button press) has been detected.
 *
 * @param  None
 * @retval None
 */
static void setKey(void){
	fallingEdge = true;
	return;
}

/**
 * @brief Handles the button pressed event.
 *
 * This function is called when the button press event is detected.
 * It sends a message through UART indicating that a falling edge (button press) has been detected.
 * It also calls `setKey()` to set the key state.
 *
 * @param  None
 * @retval None
 */
static void buttonPressed() {
	uartSendString((uint8_t*) "\nFlanco descendente detectado\n\r");
	setKey();
}

/**
 * @brief Handles the button released event.
 *
 * This function is called when the button release event is detected.
 * It sends a message through UART indicating that a rising edge (button release) has been detected.
 *
 * @param  None
 * @retval None
 */
static void buttonReleased(){
	uartSendString((uint8_t*)"\nFlanco ascendente detectado\n\r");
}


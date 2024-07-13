/*
 * API_debounce.c
 *
 *  Created on: Jul 11, 2024
 *      Author: juanma
 */
#ifndef API_API_DEBOUNCE_H_
#define API_API_DEBOUNCE_H_

#include "API_delay.h"

typedef enum {
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

void debounceFSM_init();
void debounceFSM_update();

bool_t readKey(void);

#endif /* API_API_DEBOUNCE_H_ */

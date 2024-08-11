/*
 * APP_distanceMeter.h
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef INC_APP_DISTANCEMETER_H_
#define INC_APP_DISTANCEMETER_H_
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "API_lcd.h"
#include "API_ledmatrix.h"
#include "API_ultrasonic.h"
#include "API_timer.h"
#include "API_delay.h"

#define MEASUREMENT_DELAY		1000

typedef enum {
	INIT,
	TRIGGER_SENSOR,
	WAIT_FOR_ECHO,
	MEASURE_DISTANCE,
	DISPLAY_DISTANCE,
	UPDATE_LEDS,
	WAIT_TIME
} distanceMeterState_t;

typedef enum {
	APP_OK,
	APP_FAIL
} APP_statusTypedef;

APP_statusTypedef distanceMeter_FSM_init();

APP_statusTypedef distanceMeter_FSM_update();


#endif /* INC_APP_DISTANCEMETER_H_ */

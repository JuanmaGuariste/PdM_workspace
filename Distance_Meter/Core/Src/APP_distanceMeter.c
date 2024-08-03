/*
 * APP_distanceMeter.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "APP_distanceMeter.h"
#include "API_lcd.h"
#include "API_ledmatrix.h"
#include "API_ultrasonic.h"

static distanceMeterState_t currentState;

static distanceMeterState_t handler_trigerSensor();

static distanceMeterState_t handler_measureDistance();

static distanceMeterState_t handler_displayDistance();

static distanceMeterState_t handler_updateLeds();

static distanceMeterState_t handler_waitTime();


APP_statusTypedef distanceMeter_FSM_init(){
	currentState = TRIGGER_SENSOR;
	return APP_OK;
}

APP_statusTypedef distanceMeter_FSM_update() {
	switch (currentState) {
		case TRIGGER_SENSOR:
			currentState = handler_trigerSensor();
			break;

		case MEASURE_DISTANCE:
			currentState = handler_measureDistance();
			break;

		case DISPLAY_DISTANCE:
			currentState = handler_displayDistance();
			break;

		case UPDATE_LEDS:
			currentState = handler_updateLeds();
			break;

		case WAIT_TIME:
			currentState = handler_waitTime();
			break;
		default:
			currentState = distanceMeter_FSM_init();
			break;
	}
	return APP_OK;
}


static distanceMeterState_t handler_trigerSensor(){
	return APP_OK;
}

static distanceMeterState_t handler_measureDistance(){
	return APP_OK;

}

static distanceMeterState_t handler_displayDistance(){
	return APP_OK;

}

static distanceMeterState_t handler_updateLeds(){
	return APP_OK;

}

static distanceMeterState_t handler_waitTime(){
	return APP_OK;

}



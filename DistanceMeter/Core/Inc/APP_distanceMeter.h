/*
 * APP_distanceMeter.h
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef INC_APP_DISTANCEMETER_H_
#define INC_APP_DISTANCEMETER_H_

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

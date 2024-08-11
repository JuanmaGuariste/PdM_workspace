/*
 * APP_distanceMeter.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "APP_distanceMeter.h"

static distanceMeterState_t currentState;
static distanceMeterState_t handler_trigerSensor();
static distanceMeterState_t handler_waitForEcho();
static distanceMeterState_t handler_measureDistance();
static distanceMeterState_t handler_displayDistance();
static distanceMeterState_t handler_updateLeds();
static distanceMeterState_t handler_waitTime();

static void setTimeUltrasonicData(float time);
static float getTimeUltrasonicData();
static void setDistanceUltrasonicData(float distance);
static float getDistanceUltrasonicData();
static float timeToDistanceConvertion(float time);

typedef struct {
	float time;
	float distance;
} UltrasonicSensorData;

static UltrasonicSensorData ultrasonicSensorData = { 0.0, 0.0};

static const float speedOfSound = 0.0343 / 2;

static delay_t measurementDelay;
static usDelay_t triggerDelay;

APP_statusTypedef distanceMeter_FSM_init() {
	BSP_LED_Init(LED1);
	TIMER_init();
	TIMER_start();
	LCD_init();
	LCD_clear();
	ULTRASONIC_init();
	currentState = TRIGGER_SENSOR;
	delayInit(&measurementDelay, MEASUREMENT_DELAY);
	usDelayInit(&triggerDelay, TRIGGER_DELAY);
	return APP_OK;
}

APP_statusTypedef distanceMeter_FSM_update() {
	switch (currentState) {
	case TRIGGER_SENSOR:
		currentState = handler_trigerSensor();
		break;

	case WAIT_FOR_ECHO:
		currentState = handler_waitForEcho();
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
	TRIGGER_GPIO_Port->BSRR = TRIGGER_Pin;  // Set the pin high
//	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_SET);
	if (usDelayRead(&triggerDelay)) {
		return TRIGGER_SENSOR;
	}
//	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
	TRIGGER_GPIO_Port->BSRR = (uint32_t)TRIGGER_Pin << 16U;

//	ULTRASONIC_triggerSignal();
	return WAIT_FOR_ECHO;
}

static distanceMeterState_t handler_waitForEcho(){
	setTimeUltrasonicData(ULTRASONIC_readEchoSignal());
	return MEASURE_DISTANCE;
}
static distanceMeterState_t handler_measureDistance(){
	float time = getTimeUltrasonicData();
	float distance = timeToDistanceConvertion(time);
	setDistanceUltrasonicData(distance);
	return DISPLAY_DISTANCE;
}

static distanceMeterState_t handler_displayDistance(){
	float distance = getDistanceUltrasonicData();
	LCD_clear();
	if (distance < 100) {
		LCD_printFormattedText("DISTANCIA: %d.%02d", distance);
	} else {
		LCD_printText("Sin obstaculos");
	}
	return UPDATE_LEDS;
}

static distanceMeterState_t handler_updateLeds(){
	return WAIT_TIME;
}

static distanceMeterState_t handler_waitTime() {
	if (delayRead(&measurementDelay)) {
		return WAIT_TIME;
	}
	return TRIGGER_SENSOR;
}

static void setTimeUltrasonicData(float time){
	ultrasonicSensorData.time = time;
}

static float getTimeUltrasonicData(){
	return ultrasonicSensorData.time;
}

static void setDistanceUltrasonicData(float distance){
	ultrasonicSensorData.distance = distance;
}

static float getDistanceUltrasonicData(){
	return ultrasonicSensorData.distance;
}

/**
 * @brief Converts time to distance.
 * @param time: Time duration in microseconds.
 * @retval Distance in centimeters.
 */
static float timeToDistanceConvertion(float time) {
	return (time * speedOfSound);
}


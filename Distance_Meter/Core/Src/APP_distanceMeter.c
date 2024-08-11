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

/**
 * @brief Initializes the distance meter FSM.
 *
 * Sets up the LEDs, timers, LCD, and ultrasonic sensor.
 * Initializes the state machine to start from the TRIGGER_SENSOR state.
 *
 * @param None
 * @retval APP_statusTypedef Status of the initialization.
 */
APP_statusTypedef distanceMeter_FSM_init() {
	TIMER_init();
	TIMER_start();
	LCD_init();
	LCD_clear();
	ULTRASONIC_init();
	LEDMATRIX_init();
	currentState = TRIGGER_SENSOR;
	delayInit(&measurementDelay, MEASUREMENT_DELAY);
	return APP_OK;
}

/**
 * @brief Updates the distance meter FSM.
 *
 * Handles the transitions and actions between different states of the FSM.
 *
 * @param None
 * @retval APP_statusTypedef Status of the update.
 */
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

/**
 * @brief Handler for the TRIGGER_SENSOR state.
 *
 * Triggers the ultrasonic sensor to send a pulse.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t handler_trigerSensor(){
	if (!ULTRASONIC_triggerSignal()){
		return TRIGGER_SENSOR;
	}
	return WAIT_FOR_ECHO;
}

/**
 * @brief Handler for the WAIT_FOR_ECHO state.
 *
 * Reads the echo signal duration from the ultrasonic sensor.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t handler_waitForEcho(){
	setTimeUltrasonicData(ULTRASONIC_readEchoSignal());
	return MEASURE_DISTANCE;
}

/**
 * @brief Handler for the MEASURE_DISTANCE state.
 *
 * Converts the echo signal duration to distance.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t handler_measureDistance(){
	float time = getTimeUltrasonicData();
	float distance = timeToDistanceConvertion(time);
	setDistanceUltrasonicData(distance);
	return DISPLAY_DISTANCE;
}

/**
 * @brief Handler for the DISPLAY_DISTANCE state.
 *
 * Displays the measured distance on the LCD.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
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

/**
 * @brief Handler for the UPDATE_LEDS state.
 *
 * Updates the matrix LEDs based on the measured distance.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t handler_updateLeds(){
	float distance = getDistanceUltrasonicData();
	    if (distance < 5) {
	    	MATRIXLED_display(DISTANCE_VERY_CLOSE);
	    } else if (distance < 10) {
	    	MATRIXLED_display(DISTANCE_CLOSE);
	    } else if (distance < 15) {
	    	MATRIXLED_display(DISTANCE_FAR);
	    } else if (distance < 20) {
	    	MATRIXLED_display(DISTANCE_VERY_FAR);
	    } else {
	    	MATRIXLED_display(NO_OBSTACLE_DETECTED);
	    }
	return WAIT_TIME;
}

/**
 * @brief Handler for the WAIT_TIME state.
 *
 * Waits for a specified delay before triggering the next measurement.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t handler_waitTime() {
	if (delayRead(&measurementDelay)) {
		return WAIT_TIME;
	}
	return TRIGGER_SENSOR;
}

/**
 * @brief Sets the measured time.
 *
 * @param time Measured time in microseconds.
 * @retval None
 */
static void setTimeUltrasonicData(float time){
	ultrasonicSensorData.time = time;
}

/**
 * @brief Gets the measured time.
 *
 * @param None
 * @retval float Measured time in microseconds.
 */
static float getTimeUltrasonicData(){
	return ultrasonicSensorData.time;
}

/**
 * @brief Sets the measured distance.
 *
 * @param distance Measured distance in centimeters.
 * @retval None
 */
static void setDistanceUltrasonicData(float distance){
	ultrasonicSensorData.distance = distance;
}

/**
 * @brief Gets the measured distance.
 *
 * @param None
 * @retval float Measured distance in centimeters.
 */
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


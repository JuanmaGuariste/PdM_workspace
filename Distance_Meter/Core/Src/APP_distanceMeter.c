/*
 * APP_distanceMeter.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "APP_distanceMeter.h"

static distanceMeterState_t handler_trigerSensor(void);
static distanceMeterState_t handler_waitForEcho(void);
static distanceMeterState_t handler_measureDistance(void);
static distanceMeterState_t handler_displayDistance(void);
static distanceMeterState_t handler_updateLeds(void);
static distanceMeterState_t handler_waitTime(void);
static void setTimeUltrasonicData(float time);
static float getTimeUltrasonicData(void);
static void setDistanceUltrasonicData(float distance);
static float getDistanceUltrasonicData(void);
static float timeToDistanceConvertion(float time);
static distanceMeterState_t currentState; //Global private variable to store the current state of the MSF.

typedef struct
{
	float time;
	float distance;
} UltrasonicSensorData;

static const bool_t FAIL = 1;
static UltrasonicSensorData ultrasonicSensorData = { 0.0, 0.0};
static const float speedOfSound = 0.0343 / 2;
static delay_t measurementDelay;
static void MSF_errorHandler(void);
static APP_statusTypedef initializeStateMachine(void);

/**
 * @brief Initializes the state machine with retry logic.
 *
 * This function attempts to initialize the state machine up to a maximum
 * number of retries (`MAX_RETRIES`). If the initialization fails, it waits
 * for a defined delay (`RETRY_DELAY_MS`) before trying again. If the
 * initialization is successful, it breaks out of the retry loop.
 *  * If all attempts fail, the error is handled by an error handler.
 *
 * @param void No parameters.
 * @return void No return value.
 */
void
distanceMeter_FSM_init (void)
{
    uint8_t attempt = 0;
    bool initializationSuccessful = false;

    while (attempt < MAX_RETRIES)
    {
        if (initializeStateMachine() == APP_FAIL)
        {
            attempt++;
            HAL_Delay(RETRY_DELAY_MS);
        }
        else
        {
            initializationSuccessful = true;
            break;
        }
    }

    if (!initializationSuccessful)
    {
    	MSF_errorHandler();
    }
}

/**
 * @brief Initializes the distance meter FSM.
 *
 * Sets up the LEDs, timers, LCD, and ultrasonic sensor.
 * Initializes the state machine to start from the TRIGGER_SENSOR state.
 *
 * @param None
 * @retval APP_statusTypedef Status of the initialization.
 */
static APP_statusTypedef
initializeStateMachine ()
{
	if (TIMER_init() == FAIL) return (APP_FAIL);
	if (TIMER_start() == FAIL) return (APP_FAIL);
	if (LCD_init() == FAIL) return (APP_FAIL);
	if (LCD_clear() == FAIL) return (APP_FAIL);
	if (ULTRASONIC_init() == FAIL) return (APP_FAIL);
	if (LEDMATRIX_init() == FAIL) return (APP_FAIL);
	if (delayInit(&measurementDelay, MEASUREMENT_DELAY) == FAIL) return (APP_FAIL);
	currentState = TRIGGER_SENSOR;
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
APP_statusTypedef
distanceMeter_FSM_update (void)
{
	switch (currentState)
	{
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
			currentState = initializeStateMachine();
		break;
	}
	return (APP_OK);
}

/**
 * @brief Handler for the TRIGGER_SENSOR state.
 *
 * Triggers the ultrasonic sensor to send a pulse.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t
handler_trigerSensor (void)
{
	if (!ULTRASONIC_triggerSignal())
	{
		return (TRIGGER_SENSOR);
	}
	return (WAIT_FOR_ECHO);
}

/**
 * @brief Handler for the WAIT_FOR_ECHO state.
 *
 * Reads the echo signal duration from the ultrasonic sensor.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t
handler_waitForEcho (void)
{
	setTimeUltrasonicData(ULTRASONIC_readEchoSignal());
	return (MEASURE_DISTANCE);
}

/**
 * @brief Handler for the MEASURE_DISTANCE state.
 *
 * Converts the echo signal duration to distance.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t
handler_measureDistance (void)
{
	float time = getTimeUltrasonicData();
	float distance = timeToDistanceConvertion(time);
	setDistanceUltrasonicData(distance);
	return (DISPLAY_DISTANCE);
}

/**
 * @brief Handler for the DISPLAY_DISTANCE state.
 *
 * Displays the measured distance on the LCD.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t
handler_displayDistance (void)
{
	float distance = getDistanceUltrasonicData();
	LCD_clear();
	if (distance < 100)
	{
		LCD_printFormattedText("DISTANCIA: %d.%02d", distance);
	}
	else
	{
		LCD_printText("Sin obstaculos");
	}
	return (UPDATE_LEDS);
}

/**
 * @brief Handler for the UPDATE_LEDS state.
 *
 * Updates the matrix LEDs based on the measured distance.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t
handler_updateLeds (void)
{
    float distance = getDistanceUltrasonicData();
    displayMatrixState_t ledState;

    // Determine the LED matrix state based on the distance
    switch ((int)(distance / 5))
    {
        case 0:  // 0 <= distance < 5
            ledState = DISTANCE_VERY_CLOSE;
            break;
        case 1:  // 5 <= distance < 10
            ledState = DISTANCE_CLOSE;
            break;
        case 2:  // 10 <= distance < 15
            ledState = DISTANCE_FAR;
            break;
        case 3:  // 15 <= distance < 20
            ledState = DISTANCE_VERY_FAR;
            break;
        default: // distance >= 20
            ledState = NO_OBSTACLE_DETECTED;
            break;
    }
    MATRIXLED_display(ledState);
    return (WAIT_TIME);
}

/**
 * @brief Handler for the WAIT_TIME state.
 *
 * Waits for a specified delay before triggering the next measurement.
 *
 * @param None
 * @retval distanceMeterState_t Next state.
 */
static distanceMeterState_t
handler_waitTime (void)
{
	if (delayRead(&measurementDelay))
	{
		return (WAIT_TIME);
	}
	return (TRIGGER_SENSOR);
}

/**
 * @brief Sets the measured time.
 *
 * @param time Measured time in microseconds.
 * @retval None
 */
static void
setTimeUltrasonicData (float time)
{
	ultrasonicSensorData.time = time;
}

/**
 * @brief Gets the measured time.
 *
 * @param None
 * @retval float Measured time in microseconds.
 */
static float
getTimeUltrasonicData (void)
{
	return (ultrasonicSensorData.time);
}

/**
 * @brief Sets the measured distance.
 *
 * @param distance Measured distance in centimeters.
 * @retval None
 */
static void
setDistanceUltrasonicData (float distance)
{
	ultrasonicSensorData.distance = distance;
}

/**
 * @brief Gets the measured distance.
 *
 * @param None
 * @retval float Measured distance in centimeters.
 */
static float
getDistanceUltrasonicData (void)
{
	return ultrasonicSensorData.distance;
}

/**
 * @brief Converts time to distance.
 * @param time: Time duration in microseconds.
 * @retval Distance in centimeters.
 */
static float
timeToDistanceConvertion (float time)
{
	return (time * speedOfSound);
}

static
void MSF_errorHandler (void)
{
    while (1)//TODO: implement a MSF error handler
    {

    }
}


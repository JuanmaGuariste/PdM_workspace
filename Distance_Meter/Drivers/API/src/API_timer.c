/*
 * API_timer.c
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */

#include "API_timer.h"

static void usDelayErrorHandler(void);

/**
 * @brief Initializes the microsecond delay structure.
 *
 * Sets up the delay structure with a specified duration.
 *
 * @param delay Pointer to the usDelay_t structure.
 * @param duration Duration of the delay in microseconds.
 * @retval None
 */
void
usDelayInit (usDelay_t *delay, tick_t duration)
{
	if (delay == NULL)
	{
		usDelayErrorHandler();
	}
	if (((duration > MAX_DELAY_US) || (duration < MIN_DELAY_US)))
	{
		usDelayErrorHandler();
	}
	delay->usDuration = duration;
	delay->usRunning = false;
}

/**
 * @brief Reads the microsecond delay status.
 *
 * Checks if the specified delay time has elapsed.
 *
 * @param delay Pointer to the usDelay_t structure.
 * @retval bool_t `true` if the delay is still running, `false` if the delay has elapsed.
 */
bool_t
usDelayRead (usDelay_t *delay)
{
	if (delay == NULL)
	{
		usDelayErrorHandler();
	}
	if (((delay->usDuration > MAX_DELAY_US) || (delay->usDuration < MIN_DELAY_US)))
	{
		usDelayErrorHandler();
	}
	tick_t currentTime =  TIMER_portGetTimerCounter();
	bool_t timerState = false;
	if (!(delay->usRunning))
	{
		delay->usStartTime = currentTime;
		delay->usRunning = true;
		timerState = true;
	}
	else
	{
		if ((currentTime - delay->usStartTime) >= delay->usDuration)
		{
			timerState = false;
			delay->usRunning = false;
		}
		else
		{
			timerState = true;
			delay->usRunning = true;
		}
	}
	return (timerState);
}

/**
 * @brief Introduces a delay in microseconds.
 *
 * @param time Time in microseconds to wait.
 * @retval None
 */
void
TIMER_usDelay (uint32_t time)
{
	TIMER_portDelay(time);
}

/**
 * @brief Starts the timer.
 *
 * This function initiates the timer operation by calling the TIMER_portStart() function.
 * It returns a status indicating whether the timer start was successful.
 *
 * @param void This function does not take any parameters.
 * @return TIMER_StatusTypedef Returns TIMER_OK if the timer started successfully, otherwise TIMER_FAIL.
 */
TIMER_StatusTypedef
TIMER_start (void)
{
	return (TIMER_portStart());
}

/**
 * @brief Initializes the timer.
 *
 * This function sets up the timer by calling the TIMER_portInit() function.
 * It returns a status indicating whether the initialization was successful.
 *
 * @param void This function does not take any parameters.
 * @return TIMER_StatusTypedef Returns TIMER_OK if initialization was successful, otherwise TIMER_FAIL.
 */
TIMER_StatusTypedef
TIMER_init(void)
{
	return (!TIMER_portInit());
}

/**
 * @brief Enables timer interrupts.
 *
 * Allows the timer to generate interrupts.
 *
 * @param None
 * @retval None
 */
void
TIMER_enableInterrupt ()
{
	TIMER_portEnableInterrupt();
}

/**
 * @brief Gets the captured pulse duration.
 *
 * Retrieves the duration of the pulse measured by the timer.
 *
 * @param None
 * @retval float Pulse duration in microseconds.
 */
float
TIMER_getPulse (void)
{
	return (TIMER_getPulseDuration());
}

/**
 * @brief Starts the timer interrupt capture.
 *
 * Enables the timer to start capturing interrupts.
 *
 * @param None
 * @retval None
 */
void
TIMER_StartInterrupt (void)
{
	TIMER_portStartInterrupt();
}

/**
 * @brief Error handler for microsecond delay functions.
 *
 * Handles errors in the microsecond delay functions.
 *
 * @param None
 * @retval None
 */
static void
usDelayErrorHandler()
{
	while(1) //TODO: implement a usDelay error handler
	{
	}
}

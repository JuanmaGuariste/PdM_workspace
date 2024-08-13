/*
 * API_delay.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_delay.h"

#define	MAX_DELAY	60000
#define	MIN_DELAY	1

static void delayErrorHandler(void);
static tick_t DELAY_getTick(void);

/**
 * @brief Initializes the delay structure with the specified duration.
 *
 * This function sets up the `delay` structure with the given duration.
 *
 * @param delay Pointer to the delay structure to be initialized.
 * @param duration Duration of the delay in ticks. Must be within the valid range.
 * @retval DELAY_StatusTypedef Returns `DELAY_OK` if the initialization was successful,
 *         otherwise returns `DELAY_FAIL`.
 */
DELAY_StatusTypedef
delayInit (delay_t *delay, tick_t duration)
{
	if (delay == NULL)
	{
		return (DELAY_FAIL);
	}
	if (((duration > MAX_DELAY) || (duration < MIN_DELAY)))
	{
		return (DELAY_FAIL);
	}
	delay->duration = duration;
	delay->running = false;
	return (DELAY_OK);
}

/**
 * @brief  Reads the delay status and updates the running state.
 * @param  delay: Pointer to the delay structure.
 * @retval bool_t: True if the delay is still running, false if the delay has elapsed.
 */
bool_t
delayRead (delay_t *delay)
{
	if (delay == NULL)
	{
		delayErrorHandler();
	}
	if (((delay->duration > MAX_DELAY) || (delay->duration < MIN_DELAY)))
	{
		delayErrorHandler();
	}
	tick_t currentTime = DELAY_getTick();
	bool_t timerState = false;
	if (!(delay->running))
	{
		delay->startTime = currentTime;
		delay->running = true;
		timerState = true;
	}
	else
	{
		if ((currentTime - delay->startTime) >= delay->duration)
		{
			timerState = false;
			delay->running = false;
		}
		else
		{
			timerState = true;
			delay->running = true;
		}
	}

	return (timerState);
}

/**
 * @brief  Updates the duration of the delay.
 * @param  delay: Pointer to the delay structure.
 * @param  duration: New duration of the delay in ticks.
 * @retval None
 */
void
delayWrite (delay_t *delay, tick_t duration)
{
	if (delay == NULL)
	{
		delayErrorHandler();
	}
	if (((duration > MAX_DELAY) || (duration < MIN_DELAY)))
	{
		delayErrorHandler();
	}
	delay->duration = duration;
}
/**
 * @brief  Check if a non-blocking delay is running.
 * @param  delay: Pointer to the delay structure.
 * @retval bool_t: Returns true if the delay is running, false otherwise.
 */
bool_t
delayIsRunning (delay_t * delay)
{
	if (delay == NULL)
	{
		delayErrorHandler();
	}
	return (delay->running);
}

/**
 * @brief Retrieves the current tick value.
 *
 * This function wraps the DELAY_portGetTick() function to provide the current
 * tick value, which represents the number of milliseconds that have
 * elapsed since the system started.
 *
 * @param void This function does not take any parameters.
 * @return tick_t The current tick value in milliseconds.
 */
static tick_t
DELAY_getTick ()
{
	return (DELAY_portGetTick());
}

/**
 * @brief Implements a blocking delay.
 *
 * @param delay Duration of the delay in milliseconds.
 * @retval None
 */
void
DELAY_blockingDelay (uint32_t delay)
{
	DELAY_portBlockingDelay(delay);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void
delayErrorHandler (void)
{
  while (1) //TODO: implement a delay error handler
  {
  }
}


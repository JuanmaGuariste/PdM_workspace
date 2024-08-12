/*
 * API_delay.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_delay.h"
#include "main.h"

#define	MAX_DELAY	60000
#define	MIN_DELAY	1

static void delayErrorHandler(void);

/**
 * @brief  Initializes the delay structure with the specified duration.
 * @param  delay: Pointer to the delay structure.
 * @param  duration: Duration of the delay in ticks.
 * @retval None
 */
void
delayInit (delay_t *delay, tick_t duration)
{
	if (delay == NULL) //Verify that pointer is not null
	{
		delayErrorHandler();
	}
	if (((duration > MAX_DELAY) || (duration < MIN_DELAY))) // Check if the duration is within the valid range
	{
		delayErrorHandler();
	}
	delay->duration = duration;
	delay->running = false;
}

/**
 * @brief  Reads the delay status and updates the running state.
 * @param  delay: Pointer to the delay structure.
 * @retval bool_t: True if the delay is still running, false if the delay has elapsed.
 */
bool_t
delayRead (delay_t *delay)
{
	if (delay == NULL) //Verify that pointer is not null
	{
		delayErrorHandler();
	}
	if (((delay->duration > MAX_DELAY) || (delay->duration < MIN_DELAY))) // Check if the duration is within the valid range
	{
		delayErrorHandler();
	}
	tick_t currentTime = HAL_GetTick();
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
	if (delay == NULL) //Verify that pointer is not null
	{
		delayErrorHandler();
	}
	if (((duration > MAX_DELAY) || (duration < MIN_DELAY))) // Check if the duration is within the valid range
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
	if (delay == NULL)  //Verify that pointer is not null
	{
		delayErrorHandler();
	}
	return (delay->running);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void
delayErrorHandler (void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}


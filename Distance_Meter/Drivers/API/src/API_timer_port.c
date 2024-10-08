/*
 * API_timer_port.c
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */
#include "API_timer_port.h"

#define FIRST_EDGE		0
#define SECOND_EDGE		1

static uint8_t TIMER_getCaptureIdx(void);
static void TIMER_setCaptureIdx(uint8_t idx);
static uint32_t TIMER_getSecondEdgeTime(void);
static void TIMER_setFirstEdgeTime(uint32_t time);
static uint32_t TIMER_getFirstEdgeTime(void);
static void TIMER_setSecondEdgeTime(uint32_t time);
static void TIMER_portReStartTimerCounter(void);

static uint32_t firstEdgeAux = 0;
static uint32_t secondEdgeAux = 0;

static TIM_HandleTypeDef TIM2_HANDLE;

typedef struct
{
	uint8_t captureIdx;
	uint32_t firstEdgeTime;
	uint32_t secondEdgeTime;
} TimerCaptureData;

static TimerCaptureData timerCaptureData = { 0, 0, 0 };

/**
 * @brief Starts the TIM2 timer.
 *
 * This function starts the TIM2 timer by calling the HAL_TIM_Base_Start() function from the HAL library.
 * It returns a boolean value indicating whether the timer start operation was successful.
 *
 * @param void This function does not take any parameters.
 * @retval bool_t Returns true if the timer was started successfully, otherwise false.
 */
bool_t
TIMER_portStart (void)
{
	return (HAL_TIM_Base_Start(&TIM2_HANDLE));
}

/**
 * @brief Initializes the TIM2 timer.
 *
 * This function sets up the TIM2 timer with specific configurations for the clock source,
 * master configuration, and input capture channel. It returns a boolean status indicating
 * whether the initialization was successful.
 *
 * @param void This function does not take any parameters.
 * @return bool_t Returns true if initialization was successful, otherwise false.
 */
bool_t
TIMER_portInit (void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_IC_InitTypeDef sConfigIC = { 0 };

	TIM2_HANDLE.Instance = TIM2;
	TIM2_HANDLE.Init.Prescaler = 84 - 1;
	TIM2_HANDLE.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM2_HANDLE.Init.Period = 4294967295;
	TIM2_HANDLE.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM2_HANDLE.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&TIM2_HANDLE) != HAL_OK)
	{
		return (false);
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&TIM2_HANDLE, &sClockSourceConfig) != HAL_OK)
	{
		return (false);
	}
	if (HAL_TIM_IC_Init(&TIM2_HANDLE) != HAL_OK)
	{
		return (false);
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&TIM2_HANDLE, &sMasterConfig) != HAL_OK)
	{
		return (false);
	}
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 4;
	if (HAL_TIM_IC_ConfigChannel(&TIM2_HANDLE, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	{
		return (false);
	}
	return (true);
}

/**
 * @brief Enables timer capture interrupts.
 * @param None
 * @retval None
 */
void
TIMER_portEnableInterrupt (void)
{
	__HAL_TIM_ENABLE_IT(&TIM2_HANDLE, TIM_IT_CC1);
}

/**
 * @brief Disables timer capture interrupts.
 * @param None
 * @retval None
 */
void
TIMER_portDisableInterrupt (void)
{
	__HAL_TIM_DISABLE_IT(&TIM2_HANDLE, TIM_IT_CC1);
}

/**
 * @brief Starts the timer interrupt capture.
 * @param None
 * @retval None
 */
void
TIMER_portStartInterrupt (void)
{
	HAL_TIM_IC_Start_IT(&TIM2_HANDLE, TIM_CHANNEL_1);
}

/**
 * @brief Resets the timer counter to zero.
 * @param None
 * @retval None
 */
static void
TIMER_portReStartTimerCounter (void)
{
	__HAL_TIM_SET_COUNTER(&TIM2_HANDLE, 0);
}

/**
 * @brief Restarts the timer counter and returns its value.
 * @param None
 * @retval uint32_t The value of the timer counter after restarting (typically 0).
 */
uint32_t
TIMER_portGetTimerCounter (void)
{
	return (__HAL_TIM_GET_COUNTER(&TIM2_HANDLE));
}

/**
 * @brief Timer capture interrupt callback.
 * @param TIM2_HANDLE: TIM2 timer handle.
 * @retval None
 */
void
HAL_TIM_IC_CaptureCallback (TIM_HandleTypeDef *TIM2_HANDLE)
{
	if ((TIM2_HANDLE->Channel == HAL_TIM_ACTIVE_CHANNEL_1) && (TIM2_HANDLE != NULL))
	{
		if (TIMER_getCaptureIdx() == FIRST_EDGE)
		{
			firstEdgeAux = HAL_TIM_ReadCapturedValue(TIM2_HANDLE, TIM_CHANNEL_1);
			TIMER_setFirstEdgeTime(firstEdgeAux);
			TIMER_setCaptureIdx(SECOND_EDGE);
		}
		else if (TIMER_getCaptureIdx() == SECOND_EDGE)
		{
			secondEdgeAux = HAL_TIM_ReadCapturedValue(TIM2_HANDLE, TIM_CHANNEL_1);
			TIMER_setSecondEdgeTime(secondEdgeAux);
			TIMER_portReStartTimerCounter();
			TIMER_setCaptureIdx(FIRST_EDGE);
			TIMER_portDisableInterrupt();
		}
	}
}

/**
 * @brief Handles TIM2 global interrupt.
 * @param None
 * @retval None
 */
void
TIM2_IRQHandler (void)
{
	HAL_TIM_IRQHandler(&TIM2_HANDLE);
}

/**
 * @brief Introduces a delay using the timer.
 * @param time: Time in microseconds to wait.
 * @retval None
 */
void
TIMER_portDelay (uint32_t time)
{
	TIMER_portReStartTimerCounter();
	while (TIMER_portGetTimerCounter() < time);
}

/**
 * @brief Gets the capture index.
 * @param None
 * @retval Capture index.
 */
static uint8_t
TIMER_getCaptureIdx (void)
{
	return (timerCaptureData.captureIdx);
}

/**
 * @brief Sets the capture index.
 * @param idx: Capture index.
 * @retval None
 */
static void
TIMER_setCaptureIdx (uint8_t idx)
{
	timerCaptureData.captureIdx = idx;
}

/**
 * @brief Gets the first capture time.
 * @param None
 * @retval First capture time.
 */
static uint32_t
TIMER_getFirstEdgeTime (void)
{
	return (timerCaptureData.firstEdgeTime);
}

/**
 * @brief Sets the first capture time.
 * @param time: First capture time.
 * @retval None
 */
static void
TIMER_setFirstEdgeTime (uint32_t time)
{
	timerCaptureData.firstEdgeTime = time;
}

/**
 * @brief Gets the second capture time.
 * @param None
 * @retval Second capture time.
 */
static uint32_t
TIMER_getSecondEdgeTime (void)
{
	return timerCaptureData.secondEdgeTime;
}

/**
 * @brief Sets the second capture time.
 * @param time: Second capture time.
 * @retval None
 */
static void
TIMER_setSecondEdgeTime (uint32_t time)
{
	timerCaptureData.secondEdgeTime = time;
}

/**
 * @brief Gets the captured pulse duration.
 * @param None
 * @retval Pulse duration in microseconds.
 */
float
TIMER_getPulseDuration (void)
{
	float pulseDuration = 0;
	if (TIMER_getSecondEdgeTime() > TIMER_getFirstEdgeTime())
		{
		 	pulseDuration = (TIMER_getSecondEdgeTime() - TIMER_getFirstEdgeTime());
		}
	return (pulseDuration);
}

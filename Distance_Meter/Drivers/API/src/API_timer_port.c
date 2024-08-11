/*
 * API_timer_port.c
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */
#include "API_timer_port.h"

static uint8_t TIMER_getCaptureIdx(void);
static void TIMER_setCaptureIdx(uint8_t idx);
static uint32_t TIMER_getSecondEdgeTime(void);
static void TIMER_setFirstEdgeTime(uint32_t time);
static uint32_t TIMER_getFirstEdgeTime(void);
static void TIMER_setSecondEdgeTime(uint32_t time);
static void TIMER_setPulseDuration(float duration);
static void TIMER_errorHandler(void);
static void TIMER_portReStartTimerCounter();

TIM_HandleTypeDef TIM2_HANDLE;

typedef struct {
	uint8_t captureIdx;
	uint32_t firstEdgeTime;
	uint32_t secondEdgeTime;
	float pulseDuration;
} TimerCaptureData;

static TimerCaptureData timerCaptureData = { 0, 0, 0, 0 };

/**
 * @brief Starts the timer.
 * @param None
 * @retval None
 */
void TIMER_portStart() {
	HAL_TIM_Base_Start(&TIM2_HANDLE);
}

/**
 * @brief Initializes the TIM2 timer.
 * @param None
 * @retval None
 */
void TIMER_portInit(void) {
	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_IC_InitTypeDef sConfigIC = { 0 };

	TIM2_HANDLE.Instance = TIM2;
	TIM2_HANDLE.Init.Prescaler = 84 - 1;
	TIM2_HANDLE.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM2_HANDLE.Init.Period = 4294967295;
	TIM2_HANDLE.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM2_HANDLE.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&TIM2_HANDLE) != HAL_OK) {
		TIMER_errorHandler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&TIM2_HANDLE, &sClockSourceConfig)
			!= HAL_OK) {
		TIMER_errorHandler();
	}
	if (HAL_TIM_IC_Init(&TIM2_HANDLE) != HAL_OK) {
		TIMER_errorHandler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&TIM2_HANDLE, &sMasterConfig)
			!= HAL_OK) {
		TIMER_errorHandler();
	}
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 4;
	if (HAL_TIM_IC_ConfigChannel(&TIM2_HANDLE, &sConfigIC, TIM_CHANNEL_1)
			!= HAL_OK) {
		TIMER_errorHandler();
	}
}

/**
 * @brief Enables timer capture interrupts.
 * @param None
 * @retval None
 */
void TIMER_portEnableInterrupt() {
	__HAL_TIM_ENABLE_IT(&TIM2_HANDLE, TIM_IT_CC1);
}

/**
 * @brief Disables timer capture interrupts.
 * @param None
 * @retval None
 */
void TIMER_portDisableInterrupt() {
	__HAL_TIM_DISABLE_IT(&TIM2_HANDLE, TIM_IT_CC1);
}

/**
 * @brief Starts the timer interrupt capture.
 * @param None
 * @retval None
 */
void TIMER_portStartInterrupt() {
	HAL_TIM_IC_Start_IT(&TIM2_HANDLE, TIM_CHANNEL_1);
}

/**
 * @brief Resets the timer counter to zero.
 * @param None
 * @retval None
 */
static void TIMER_portReStartTimerCounter() {
	__HAL_TIM_SET_COUNTER(&TIM2_HANDLE, 0);
}

/**
 * @brief Restarts the timer counter and returns its value.
 * @param None
 * @retval uint32_t The value of the timer counter after restarting (typically 0).
 */
uint32_t TIMER_portGetTimerCounter() {
	return __HAL_TIM_GET_COUNTER(&TIM2_HANDLE);
}

/**
 * @brief Timer capture interrupt callback.
 * @param TIM2_HANDLE: TIM2 timer handle.
 * @retval None
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *TIM2_HANDLE) {
	if (TIM2_HANDLE->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
		if (TIMER_getCaptureIdx() == 0) {
			TIMER_setFirstEdgeTime(HAL_TIM_ReadCapturedValue(TIM2_HANDLE, TIM_CHANNEL_1));
			TIMER_setCaptureIdx(1);
		} else if (TIMER_getCaptureIdx() == 1) {
			TIMER_setSecondEdgeTime(HAL_TIM_ReadCapturedValue(TIM2_HANDLE, TIM_CHANNEL_1));
			TIMER_portReStartTimerCounter();
			if (TIMER_getSecondEdgeTime() > TIMER_getFirstEdgeTime()) {
				TIMER_setPulseDuration(TIMER_getSecondEdgeTime() - TIMER_getFirstEdgeTime());
			} else {
				TIMER_setPulseDuration(0);
			}
			TIMER_setCaptureIdx(0);
			TIMER_portDisableInterrupt();
		}
	}
}

/**
 * @brief Handles TIM2 global interrupt.
 * @param None
 * @retval None
 */
void TIM2_IRQHandler(void) {
	HAL_TIM_IRQHandler(&TIM2_HANDLE);
}

/**
 * @brief Introduces a delay using the timer.
 * @param time: Time in microseconds to wait.
 * @retval None
 */
void TIMER_portDelay(uint32_t time) {
	TIMER_portReStartTimerCounter();
	while (TIMER_portGetTimerCounter() < time);
}

/**
 * @brief Gets the capture index.
 * @param None
 * @retval Capture index.
 */
static uint8_t TIMER_getCaptureIdx(void) {
	return timerCaptureData.captureIdx;
}

/**
 * @brief Sets the capture index.
 * @param idx: Capture index.
 * @retval None
 */
static void TIMER_setCaptureIdx(uint8_t idx) {
	timerCaptureData.captureIdx = idx;
}

/**
 * @brief Gets the first capture time.
 * @param None
 * @retval First capture time.
 */
static uint32_t TIMER_getFirstEdgeTime(void) {
	return timerCaptureData.firstEdgeTime;
}

/**
 * @brief Sets the first capture time.
 * @param time: First capture time.
 * @retval None
 */
static void TIMER_setFirstEdgeTime(uint32_t time) {
	timerCaptureData.firstEdgeTime = time;
}

/**
 * @brief Gets the second capture time.
 * @param None
 * @retval Second capture time.
 */
static uint32_t TIMER_getSecondEdgeTime(void) {
	return timerCaptureData.secondEdgeTime;
}

/**
 * @brief Sets the second capture time.
 * @param time: Second capture time.
 * @retval None
 */
static void TIMER_setSecondEdgeTime(uint32_t time) {
	timerCaptureData.secondEdgeTime = time;
}

/**
 * @brief Gets the captured pulse duration.
 * @param None
 * @retval Pulse duration in microseconds.
 */
float TIMER_getPulseDuration(void) {
	return timerCaptureData.pulseDuration;
}

/**
 * @brief Sets the captured pulse duration.
 * @param duration: Pulse duration in microseconds.
 * @retval None
 */
static void TIMER_setPulseDuration(float duration) {
	timerCaptureData.pulseDuration = duration;
}

/**
 * @brief Handles timer errors.
 * @param None
 * @retval None
 */
static void TIMER_errorHandler(void) {
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1) {
	}
}

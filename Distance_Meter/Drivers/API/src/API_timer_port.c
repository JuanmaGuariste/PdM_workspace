/*
 * API_timer_port.c
 *
 *  Created on: Aug 8, 2024
 *      Author: juanma
 */
#include "API_timer_port.h"

TIM_HandleTypeDef TIM2_HANDLE;

void TIMER_portStart(){
	HAL_TIM_Base_Start(&TIM2_HANDLE);
}
static void TIMER_errorHandler(void);


void TIMER_portInit(void){
	 TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	  TIM_MasterConfigTypeDef sMasterConfig = {0};
	  TIM_IC_InitTypeDef sConfigIC = {0};

	  TIM2_HANDLE.Instance = TIM2;
	  TIM2_HANDLE.Init.Prescaler = 84-1;
	  TIM2_HANDLE.Init.CounterMode = TIM_COUNTERMODE_UP;
	  TIM2_HANDLE.Init.Period = 4294967295;
	  TIM2_HANDLE.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  TIM2_HANDLE.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if (HAL_TIM_Base_Init(&TIM2_HANDLE) != HAL_OK)
	  {
		  TIMER_errorHandler();
	  }
	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  if (HAL_TIM_ConfigClockSource(&TIM2_HANDLE, &sClockSourceConfig) != HAL_OK)
	  {
		  TIMER_errorHandler();
	  }
	  if (HAL_TIM_IC_Init(&TIM2_HANDLE) != HAL_OK)
	  {
		  TIMER_errorHandler();
	  }
	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  if (HAL_TIMEx_MasterConfigSynchronization(&TIM2_HANDLE, &sMasterConfig) != HAL_OK)
	  {
		  TIMER_errorHandler();
	  }
	  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	  sConfigIC.ICFilter = 0;
	  if (HAL_TIM_IC_ConfigChannel(&TIM2_HANDLE, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	  {
		  TIMER_errorHandler();
	  }
}

void TIMER_portDelay(uint32_t time){
	__HAL_TIM_SET_COUNTER(&TIM2_HANDLE, 0);
	while ((__HAL_TIM_GET_COUNTER(&TIM2_HANDLE)) < time);
}

static void TIMER_errorHandler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

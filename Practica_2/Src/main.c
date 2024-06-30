/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/main.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/** @addtogroup UART_Printf
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PERIOD1				1000
#define PERIOD2				200
#define PERIOD3				100
#define INITIALpERIOD		0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t DUTYcYCLE = 50;
const uint8_t CYCLE = 100;

const tick_t periodSecuence[] = { PERIOD1 * DUTYcYCLE / CYCLE, PERIOD2
		* DUTYcYCLE / CYCLE, PERIOD3 * DUTYcYCLE / CYCLE };
const uint8_t MAXpERIODS = sizeof(periodSecuence) / sizeof(tick_t); //Determine the total amount of periods

const uint8_t TOTALpERIODS = 5;
uint8_t repetitions = TOTALpERIODS * 2;

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
	/* STM32F4xx HAL library initialization:
	 - Configure the Flash prefetch
	 - Systick timer is configured by default as source of time base, but user
	 can eventually implement his proper time base source (a general purpose
	 timer for example or other time source), keeping in mind that Time base
	 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
	 handled in milliseconds basis.
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP Led for LED1*/
	BSP_LED_Init(LED1);
	delay_t delay;
	delayInit(&delay, periodSecuence[INITIALpERIOD]);
	uint8_t count = 0;
	uint8_t countSecuence = 0;

	/* Infinite loop */
	while (1) {
		for (countSecuence = 0; countSecuence < MAXpERIODS; countSecuence++) {
			delayWrite(&delay, periodSecuence[countSecuence]);
			while (count < repetitions) {
				if (!delayRead(&delay)) {
					BSP_LED_Toggle(LED1);
					count++;
				}
			}
			count = 0;
		}
	}
}

/**
 * @brief  Initializes the delay structure with the specified duration.
 * @param  delay: Pointer to the delay structure.
 * @param  duration: Duration of the delay in ticks.
 * @retval None
 */
void delayInit(delay_t *delay, tick_t duration) {
	if (delay == NULL) { //Verify that pointer is not null
		return;
	}
	if (duration == 0) { //Verify that duration is not zero
		return;
	}
	delay->duration = duration;
	delay->running = false;
}

/**
 * @brief  Reads the delay status and updates the running state.
 * @param  delay: Pointer to the delay structure.
 * @retval bool_t: True if the delay is still running, false if the delay has elapsed.
 */
bool_t delayRead(delay_t *delay) {
	if (delay == NULL) { //Verify that pointer is not null
		return false;
	}
	if (delay->duration == 0) { //Verify that duration is not zero
		return false;
	}
	tick_t currentTime = HAL_GetTick();
	bool_t timerState = false;
	if (!(delay->running)) {
		delay->startTime = currentTime;
		delay->running = true;
		timerState = true;
	} else {
		if ((currentTime - delay->startTime) >= delay->duration) {
			timerState = false;
			delay->running = false;
		} else {
			timerState = true;
			delay->running = true;
		}
	}

	return timerState;
}

/**
 * @brief  Updates the duration of the delay.
 * @param  delay: Pointer to the delay structure.
 * @param  duration: New duration of the delay in ticks.
 * @retval None
 */
void delayWrite(delay_t *delay, tick_t duration) {
	if (delay == NULL) { //Verify that pointer is not null
		return;
	}
	if (duration == 0) { //Verify that duration is not zero
		return;
	}
	delay->duration = duration;
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/*
 * API_ledmatrix_port.h
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_LEDMATRIX_PORT_H_
#define API_INC_API_LEDMATRIX_PORT_H_

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_hal_spi.h"
#include "stdbool.h"

#define CS_LED_MATRIX_Pin GPIO_PIN_15
#define CS_LED_MATRIX_GPIO_Port GPIOD

typedef bool bool_t;

bool_t port_initSPI();
#endif /* API_INC_API_LEDMATRIX_PORT_H_ */

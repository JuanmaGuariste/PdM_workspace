/*
 * API_ledmatrix.h
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_LEDMATRIX_H_
#define API_INC_API_LEDMATRIX_H_

#include "API_ledmatrix_port.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_spi.h"

typedef enum {
	LED_MATRIX_OK,
	LED_MATRIX_FAIL
} LEDMATRIX_StatusTypedef;

typedef enum {
	DISTANCE_VERY_CLOSE,
	DISTANCE_CLOSE,
	DISTANCE_FAR,
	DISTANCE_VERY_FAR,
	NO_OBSTACLE_DETECTED,
} displayMatrixState_t;

LEDMATRIX_StatusTypedef LEDMATRIX_init();
void MATRIXLED_display(uint8_t data);


#endif /* API_INC_API_LEDMATRIX_H_ */

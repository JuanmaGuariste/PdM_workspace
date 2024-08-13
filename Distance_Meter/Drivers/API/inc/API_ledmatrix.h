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

/*Register Address Map*/
#define DECODE_MODE				0x09
#define INTENSITY				0x0A
#define SCAN_LIMIT				0x0B
#define SHUT_DOWN				0x0C
#define DISPLAY_TEST			0x0F

/*Register Data Map*/
#define NO_DECODE 				0x00
#define DUTY_CYCLE				0x0F
#define AMOUNT_OF_COLUMNS		0x07
#define NORMAL_OPERATION		0x01
#define DISPLAY_TEST_MODE		0x00

#define COLUMN_1				0x01
#define COLUMN_2				0x02
#define COLUMN_3				0x03
#define COLUMN_4				0x04
#define COLUMN_5				0x05
#define COLUMN_6				0x06
#define COLUMN_7				0x07
#define COLUMN_8				0x08



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

/*
 * API_ledmatrix.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_ledmatrix.h"

static void MATRIXLED_sendMsg(uint8_t reg, uint8_t data);

/**
 * @brief Initializes the LED matrix.
 *
 * This function sets up the SPI port and configures the LED matrix with specific parameters.
 *
 * @param void This function does not take any parameters.
 * @return LEDMATRIX_StatusTypedef Returns `LED_MATRIX_OK` if initialization is successful,
 *         otherwise returns `LED_MATRIX_FAIL`.
 */
LEDMATRIX_StatusTypedef
LEDMATRIX_init ()
{
	bool_t estadoSPI = port_initSPI();
	if (estadoSPI == false)	return (LED_MATRIX_FAIL);
	MATRIXLED_sendMsg(DECODE_MODE, NO_DECODE);
	MATRIXLED_sendMsg(INTENSITY, DUTY_CYCLE);
	MATRIXLED_sendMsg(SCAN_LIMIT, AMOUNT_OF_COLUMNS);
	MATRIXLED_sendMsg(SHUT_DOWN, NORMAL_OPERATION);
	MATRIXLED_sendMsg(DISPLAY_TEST, DISPLAY_TEST_MODE);
	return (LED_MATRIX_OK);
}

/**
 * @brief Sends a message to the LED matrix via the SPI port.
 *
 * @param reg The register address to write to.
 * @param data The data to write to the register.
 * @retval None
 */
static void
MATRIXLED_sendMsg (uint8_t reg, uint8_t data)
{
	MATRIXLED_portSendMsg(reg, data);
}

/**
 * @brief Displays a pattern on the LED matrix based on the distance state.
 *
 * @param data The distance state to display.
 * DISTANCE_VERY_CLOSE, DISTANCE_CLOSE, DISTANCE_FAR, DISTANCE_VERY_FAR, or NO_OBSTACLE_DETECTED.
 * @retval None
 */
void
MATRIXLED_display (displayMatrixState_t data)
{
	switch (data)
	{
		case DISTANCE_VERY_CLOSE: // All LEDs are turned on (8x8 matrix)
			MATRIXLED_sendMsg(COLUMN_1, 0xFF);
			MATRIXLED_sendMsg(COLUMN_2, 0xFF);
			MATRIXLED_sendMsg(COLUMN_3, 0xFF);
			MATRIXLED_sendMsg(COLUMN_4, 0xFF);
			MATRIXLED_sendMsg(COLUMN_5, 0xFF);
			MATRIXLED_sendMsg(COLUMN_6, 0xFF);
			MATRIXLED_sendMsg(COLUMN_7, 0xFF);
			MATRIXLED_sendMsg(COLUMN_8, 0xFF);
			break;
		case DISTANCE_CLOSE: // All LEDs are turned on except for the outermost ones (6x6 matrix)
			MATRIXLED_sendMsg(COLUMN_1, 0x00);
			MATRIXLED_sendMsg(COLUMN_2, 0x7E);
			MATRIXLED_sendMsg(COLUMN_3, 0x7E);
			MATRIXLED_sendMsg(COLUMN_4, 0x7E);
			MATRIXLED_sendMsg(COLUMN_5, 0x7E);
			MATRIXLED_sendMsg(COLUMN_6, 0x7E);
			MATRIXLED_sendMsg(COLUMN_7, 0x7E);
			MATRIXLED_sendMsg(COLUMN_8, 0x00);
			break;
		case DISTANCE_FAR: // Center LEDs are turned on (4x4 matrix)
			MATRIXLED_sendMsg(COLUMN_1, 0x00);
			MATRIXLED_sendMsg(COLUMN_2, 0x00);
			MATRIXLED_sendMsg(COLUMN_3, 0x3C);
			MATRIXLED_sendMsg(COLUMN_4, 0x3C);
			MATRIXLED_sendMsg(COLUMN_5, 0x3C);
			MATRIXLED_sendMsg(COLUMN_6, 0x3C);
			MATRIXLED_sendMsg(COLUMN_7, 0x00);
			MATRIXLED_sendMsg(COLUMN_8, 0x00);
			break;
		case DISTANCE_VERY_FAR: // Center LEDs are turned on (2x2 matrix)
			MATRIXLED_sendMsg(COLUMN_1, 0x00);
			MATRIXLED_sendMsg(COLUMN_2, 0x00);
			MATRIXLED_sendMsg(COLUMN_3, 0x00);
			MATRIXLED_sendMsg(COLUMN_4, 0x18);
			MATRIXLED_sendMsg(COLUMN_5, 0x18);
			MATRIXLED_sendMsg(COLUMN_6, 0x00);
			MATRIXLED_sendMsg(COLUMN_7, 0x00);
			MATRIXLED_sendMsg(COLUMN_8, 0x00);
			break;
		case NO_OBSTACLE_DETECTED: // No LEDs are turned on (0x0)
			MATRIXLED_sendMsg(COLUMN_1, 0x00);
			MATRIXLED_sendMsg(COLUMN_2, 0x00);
			MATRIXLED_sendMsg(COLUMN_3, 0x00);
			MATRIXLED_sendMsg(COLUMN_4, 0x00);
			MATRIXLED_sendMsg(COLUMN_5, 0x00);
			MATRIXLED_sendMsg(COLUMN_6, 0x00);
			MATRIXLED_sendMsg(COLUMN_7, 0x00);
			MATRIXLED_sendMsg(COLUMN_8, 0x00);
			break;
		default: // No LEDs are turned on (0x0)
			MATRIXLED_sendMsg(COLUMN_1, 0x00);
			MATRIXLED_sendMsg(COLUMN_2, 0x00);
			MATRIXLED_sendMsg(COLUMN_3, 0x00);
			MATRIXLED_sendMsg(COLUMN_4, 0x00);
			MATRIXLED_sendMsg(COLUMN_5, 0x00);
			MATRIXLED_sendMsg(COLUMN_6, 0x00);
			MATRIXLED_sendMsg(COLUMN_7, 0x00);
			MATRIXLED_sendMsg(COLUMN_8, 0x00);
			break;
	}
}

















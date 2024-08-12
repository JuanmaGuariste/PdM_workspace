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
 * This function sets up the SPI port, and configures the LED matrix for normal operation.
 *
 * @param None
 * @retval LED_MATRIX_OK if initialization is successful, LED_MATRIX_FAIL otherwise.
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
		case DISTANCE_VERY_CLOSE:
			MATRIXLED_sendMsg(0x01, 0xFF);
			MATRIXLED_sendMsg(0x02, 0xFF);
			MATRIXLED_sendMsg(0x03, 0xFF);
			MATRIXLED_sendMsg(0x04, 0xFF);
			MATRIXLED_sendMsg(0x05, 0xFF);
			MATRIXLED_sendMsg(0x06, 0xFF);
			MATRIXLED_sendMsg(0x07, 0xFF);
			MATRIXLED_sendMsg(0x08, 0xFF);
			break;
		case DISTANCE_CLOSE:
			MATRIXLED_sendMsg(0x01, 0x00);
			MATRIXLED_sendMsg(0x02, 0x7E);
			MATRIXLED_sendMsg(0x03, 0x7E);
			MATRIXLED_sendMsg(0x04, 0x7E);
			MATRIXLED_sendMsg(0x05, 0x7E);
			MATRIXLED_sendMsg(0x06, 0x7E);
			MATRIXLED_sendMsg(0x07, 0x7E);
			MATRIXLED_sendMsg(0x08, 0x00);
			break;
		case DISTANCE_FAR:
			MATRIXLED_sendMsg(0x01, 0x00);
			MATRIXLED_sendMsg(0x02, 0x00);
			MATRIXLED_sendMsg(0x03, 0x3C);
			MATRIXLED_sendMsg(0x04, 0x3C);
			MATRIXLED_sendMsg(0x05, 0x3C);
			MATRIXLED_sendMsg(0x06, 0x3C);
			MATRIXLED_sendMsg(0x07, 0x00);
			MATRIXLED_sendMsg(0x08, 0x00);
			break;
		case DISTANCE_VERY_FAR:
			MATRIXLED_sendMsg(0x01, 0x00);
			MATRIXLED_sendMsg(0x02, 0x00);
			MATRIXLED_sendMsg(0x03, 0x00);
			MATRIXLED_sendMsg(0x04, 0x18);
			MATRIXLED_sendMsg(0x05, 0x18);
			MATRIXLED_sendMsg(0x06, 0x00);
			MATRIXLED_sendMsg(0x07, 0x00);
			MATRIXLED_sendMsg(0x08, 0x00);
			break;
		case NO_OBSTACLE_DETECTED:
			MATRIXLED_sendMsg(0x01, 0x00);
			MATRIXLED_sendMsg(0x02, 0x00);
			MATRIXLED_sendMsg(0x03, 0x00);
			MATRIXLED_sendMsg(0x04, 0x00);
			MATRIXLED_sendMsg(0x05, 0x00);
			MATRIXLED_sendMsg(0x06, 0x00);
			MATRIXLED_sendMsg(0x07, 0x00);
			MATRIXLED_sendMsg(0x08, 0x00);
			break;
		default:
			MATRIXLED_sendMsg(0x01, 0x00);
			MATRIXLED_sendMsg(0x02, 0x00);
			MATRIXLED_sendMsg(0x03, 0x00);
			MATRIXLED_sendMsg(0x04, 0x00);
			MATRIXLED_sendMsg(0x05, 0x00);
			MATRIXLED_sendMsg(0x06, 0x00);
			MATRIXLED_sendMsg(0x07, 0x00);
			MATRIXLED_sendMsg(0x08, 0x00);
			break;
	}
}

















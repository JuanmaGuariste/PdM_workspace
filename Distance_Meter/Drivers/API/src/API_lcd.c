/*
 * API_lcd.c
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */
#include "API_lcd.h"

static void LCD_delay(uint8_t delay);

static LCD_StatusTypedef LCD_sendNibble(uint8_t data, uint8_t rs);

static LCD_StatusTypedef LCD_sendMsg(uint8_t data, uint8_t rs);

static LCD_StatusTypedef LCD_sendByte(uint8_t byte);

static LCD_StatusTypedef LCD_printChar(char dato);

static const uint8_t LCD_INIT_CMD[]={
	_4BIT_MODE,
	DISPLAY_CONTROL,
	RETURN_HOME,
	ENTRY_MODE_SET | AUTOINCREMENT,
	DISPLAY_CONTROL | DISPLAY_ON,
	CLEAR_DISPLAY
};

static uint8_t backLight = 1;

/**
 * @brief Initializes the LCD.
 *
 * @param void
 * @return LCD_StatusTypedef Returns LCD_OK if the LCD was initialized correctly, otherwise LCD_FAIL.
 */
LCD_StatusTypedef LCD_init(){
	bool_t estadoI2C = port_init();
	if (estadoI2C == false)	return LCD_FAIL;
	LCD_delay(DELAY20ms);
	if (LCD_sendNibble(CMD_INI1, COMMAND) == LCD_FAIL) return LCD_FAIL;
	LCD_delay(DELAY10ms);
	if (LCD_sendNibble(CMD_INI1, COMMAND) == LCD_FAIL) return LCD_FAIL;
	LCD_delay(DELAY1ms);
	if (LCD_sendNibble(CMD_INI1, COMMAND) == LCD_FAIL) return LCD_FAIL;
	if (LCD_sendNibble(CMD_INI2, COMMAND) == LCD_FAIL) return LCD_FAIL;
	for (uint8_t index = 0; index < sizeof(LCD_INIT_CMD); index++) {
		LCD_delay(DELAY1ms);
		if (LCD_sendMsg(LCD_INIT_CMD[index], COMMAND) == LCD_FAIL) return LCD_FAIL;
	}

	return LCD_OK;
}

/**
 * @brief Clears the LCD.
 *
 * @param void
 * @return LCD_StatusTypedef Returns LCD_OK if the LCD was cleared correctly, otherwise LCD_FAIL.
 */
LCD_StatusTypedef LCD_clear() {
	return LCD_sendMsg(CLEAR_DISPLAY, COMMAND);
}

/**
 * @brief Sets the cursor position on the LCD.
 *
 * @param row Row where the cursor will be positioned (LCD_ROW_1 = 0 or LCD_ROW_2 = 1).
 * @param col Column where the cursor will be positioned.
 * @return LCD_StatusTypedef Returns LCD_OK if the cursor position was set correctly, otherwise LCD_FAIL.
 */
LCD_StatusTypedef LCD_setCursor(uint8_t row, uint8_t col) {
	switch (row) {
	case LCD_ROW_1:
		LCD_sendMsg((LCD_ROW_1_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND);
		break;
	case LCD_ROW_2:
		LCD_sendMsg((LCD_ROW_2_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND);
		break;
	default:
		LCD_sendMsg((LCD_ROW_1_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND);
		break;
	}
	return LCD_OK;
}

/**
 * @brief Prints text on the LCD.
 *
 * @param ptrText Pointer to the text to print.
 * @return LCD_StatusTypedef Returns LCD_OK if the text was printed correctly, otherwise LCD_FAIL.
 */
LCD_StatusTypedef LCD_printText(char *ptrText) {
	if (ptrText == NULL) return LCD_FAIL;
	LCD_clear();
	LCD_setCursor(LCD_ROW_1, LCD_COL_0);
	uint8_t row = LCD_ROW_1;
	uint8_t columnPosition = 0;
	while (*ptrText != NULL_CHAR) {
		if (*ptrText == '\n') {
			row = (row == LCD_ROW_1) ? LCD_ROW_2 : LCD_ROW_1;
			columnPosition = 0;
			LCD_setCursor(row, LCD_COL_0);
			ptrText++;
			continue;
		}
		if (LCD_printChar(*ptrText++) == LCD_FAIL) return LCD_FAIL;
		columnPosition++;
		if (columnPosition >= LCD_MAX_COLUMNS) {
			if (row == LCD_ROW_1) {
				row = LCD_ROW_2;
				LCD_setCursor(LCD_ROW_2, LCD_COL_0);
			} else {
				break; // If both rows are filled, stop printing
			}
			columnPosition = 0;
		}
	}
	return LCD_OK;
}

/**
 * @brief Prints formatted text with a number on the LCD.
 *
 * @param format Format of the text to print.
 * @param number Number to include in the text.
 * @return LCD_StatusTypedef Returns LCD_OK if the text was printed correctly, otherwise LCD_FAIL.
 */
LCD_StatusTypedef LCD_printFormattedText(const char *format, int number) {
    char buffer[32];
    sprintf(buffer, format, number);
    return LCD_printText(buffer);
}

/**
 * @brief Prints a character on the LCD.
 *
 * @param dato Character to print.
 * @return LCD_StatusTypedef Returns LCD_OK if the character was printed correctly, otherwise LCD_FAIL.
 */
LCD_StatusTypedef LCD_printChar(char dato) {
	return LCD_sendMsg(dato, DATA);
}

/**
 * @brief Introduces a delay.
 *
 * @param delay Amount of time to delay in milliseconds.
 * @return void
 */
static void LCD_delay(uint8_t delay){
	LCD_portDelay(delay);
}

/**
 * @brief Sends a nibble to the LCD.
 *
 * @param data Data to send.
 * @param rs Register select flag (COMMAND = 0 or DATA = 1).
 * @return LCD_StatusTypedef Returns LCD_OK if the nibble was sent correctly, otherwise LCD_FAIL.
 */
static LCD_StatusTypedef LCD_sendNibble(uint8_t data, uint8_t rs) {
	return LCD_sendByte((data & LOW_NIBBLE_MASK) << TO_HIGH_NIBBLE_SHIFT | (backLight << BACKLIGHT_SHIFT) | rs );
}

/**
 * @brief Sends a message (byte) to the LCD.
 *
 * @param data Data to send.
 * @param rs Register select flag (COMMAND = 0 or DATA = 1).
 * @return LCD_StatusTypedef Returns LCD_OK if the message was sent correctly, otherwise LCD_FAIL.
 */
static LCD_StatusTypedef LCD_sendMsg(uint8_t data, uint8_t rs) {
	if (LCD_sendByte((data & HIGH_NIBBLE_MASK) | (backLight << BACKLIGHT_SHIFT) | rs  ) == LCD_FAIL) return LCD_FAIL;
	if (LCD_sendByte((data & LOW_NIBBLE_MASK) << TO_HIGH_NIBBLE_SHIFT | (backLight << BACKLIGHT_SHIFT) | rs) == LCD_FAIL) return LCD_FAIL;
	return LCD_OK;
}

/**
 * @brief Sends a byte to the LCD.
 *
 * @param byte Byte to send.
 * @return LCD_StatusTypedef Returns LCD_OK if the byte was sent correctly, otherwise LCD_FAIL.
 */
static LCD_StatusTypedef LCD_sendByte(uint8_t byte) {
	if (!LCD_portWriteByte(byte | ENABLE)) return LCD_FAIL;
	LCD_delay(DELAY1ms);
	if (!LCD_portWriteByte(byte)) return LCD_FAIL;
	LCD_delay(DELAY1ms);
	return LCD_OK;
}

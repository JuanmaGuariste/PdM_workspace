/*
 * API_lcd.hLCD_sendNibble
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

#include "API_lcd_port.h"
#include "stdio.h"
/* Control commands*/
#define CLEAR_DISPLAY 			1
#define _4BIT_MODE 				0x28
#define RETURN_HOME				(1<<1)
#define ENTRY_MODE_SET			(1<<2)
#define DISPLAY_CONTROL			(1<<3)
#define CURSOR_DISPLAY_SHIFT	(1<<4)
#define FUNCTION_SET			(1<<5)
#define SET_CGRAM_ADDRESS		(1<<6)
#define SET_DDRAM_ADDRESS		(1<<7)

#define AUTOINCREMENT 			(1<<1)
#define DISPLAY_ON 				(1<<2)

/* Required delays*/
#define DELAY20ms				20
#define DELAY10ms				10
#define DELAY1ms				1

//Initialize commands
#define CMD_INI1 				0x03
#define CMD_INI2 				0x02

#define DATA 					1
#define COMMAND 				0

#define BACKLIGHT_SHIFT			3

#define LOW_NIBBLE_MASK			0x0f
#define HIGH_NIBBLE_MASK		0xf0
#define TO_HIGH_NIBBLE_SHIFT	4

#define ENABLE 					(1<<2)

#define LCD_ROW_1_ADDRESS		0x00
#define LCD_ROW_2_ADDRESS		0x40
#define LCD_ROW_1				0
#define LCD_ROW_2				1

#define LCD_MAX_COLUMNS			16
#define LCD_CANTIDAD_FILAS		2
#define NULL_CHAR				'\0'

#define SET_CURSOR				(1<<7)
#define LCD_FILA_1				0x00
#define LCD_FILA_2				0x40
#define LCD_COL_0				0

#define INT_TO_ASCII			48
#define TWO_DECIMALS			100

typedef enum
{
	LCD_OK,
	LCD_FAIL
} LCD_StatusTypedef;

LCD_StatusTypedef LCD_init();
LCD_StatusTypedef LCD_clear();
LCD_StatusTypedef LCD_setCursor(uint8_t row, uint8_t col);
LCD_StatusTypedef LCD_printText(char *ptrText);
LCD_StatusTypedef LCD_printFormattedText(const char *format, float number);

#endif /* API_INC_API_LCD_H_ */

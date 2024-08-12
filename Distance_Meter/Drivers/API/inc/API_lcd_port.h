/*
 * API_lcd_port.h
 *
 *  Created on: Aug 3, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_LCD_PORT_H_
#define API_INC_API_LCD_PORT_H_

#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"
#include "API_uart.h"

#define LCD_ADDRESS					0x27
#define I2C_TIMEOUT					10
#define I2C_INSTANCE				I2C1
#define I2C_CLOCK_SPEED				100000
#define I2C_TIMEOUT					10

void LCD_portDelay(uint32_t delay);
bool_t port_init(void);
bool_t LCD_portWriteByte(uint8_t byte);

#endif /* API_INC_API_LCD_PORT_H_ */

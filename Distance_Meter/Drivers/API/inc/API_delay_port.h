/*
 * API_delay_port.h
 *
 *  Created on: Aug 12, 2024
 *      Author: juanma
 */

#ifndef API_INC_API_DELAY_PORT_H_
#define API_INC_API_DELAY_PORT_H_

#include <stdint.h>

typedef uint32_t tick_t;

tick_t DELAY_portGetTick(void);
void DELAY_portBlockingDelay(uint32_t delay);

#endif /* API_INC_API_DELAY_PORT_H_ */

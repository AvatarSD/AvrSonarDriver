/*
 * uartport.h
 *
 *  Created on: 9 лют. 2016
 *      Author: sd
 */

#ifndef UARTPORT_UARTPORT_H_
#define UARTPORT_UARTPORT_H_

#include "../platformDepend/UART/UART.h"

void sendData(UART & port, const char* portName, uint8_t pinNum,
		uint16_t distance);

#endif /* UARTPORT_UARTPORT_H_ */

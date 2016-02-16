/*
 * uartport.cpp
 *
 *  Created on: 9 лют. 2016
 *      Author: sd
 */

#include "uartport.h"
#include <avr/interrupt.h>

void sendData(UART & port, const char* portName, uint8_t pinNum,
		uint16_t distance)
{
	unsigned char buff[8] =
	{ '$' };
	buff[1] = portName[0];
	buff[2] = portName[1];
	buff[3] = pinNum;
	buff[4] = distance & 0xff;
	buff[5] = (distance >> 8) & 0xff;
	for (uint8_t i = 0; i < 6; i++)
		buff[6] ^= buff[i];
	buff[7] = 0;
	cli();
	port.WriteCOM(8, buff);
	sei();
}

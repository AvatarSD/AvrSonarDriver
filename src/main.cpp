/*
 * main.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "init/init.h"
#include "UART/UART.h"
//#include "ADC/Analog.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "util/delay.h"
#include "string.h"

#include "platformDepend/platform.h"


#define SONAR_COUNT 	2 // just for init
#define RELAX_TIME		20
//#define MAX_ADC_DATA	1000



inline void sendData(UART & port, const char* portName, uint8_t pinNum,
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

volatile uint8_t sonarIter = 0;
uint8_t flag; //one enter - one exit pear timer cycle

inline void sonarRoutineHandler(uint16_t timerCurr, bool pinState,
		uint8_t sonarNum)
{
	static uint16_t timerLast;

	if ((pinState) && (flag == 0))
	{
		timerLast = timerCurr;
		flag = 1;
	}
	else if ((!pinState) && (flag == 1))
	{
		unsigned int distance = timerCurr - timerLast;
		distance /= ((double) 58 / 4);
		sendData(mainPort, "SR", sonarNum, distance);
		flag = -1;
#ifdef RELAX_TIME
		TIM_VAL = ICR1 - (RELAX_TIME * 250);
#endif
	}
}

inline void timTrigOnEvent()
{
	if (++sonarIter == sonarsCount)
		sonarIter = 0;

	trigOn(sonarIter);

	static uint16_t counter;
	if (sonarIter == 0)
		sendData(mainPort, "SB", 200, counter++);

//	for (uint8_t i = 0; i < LAST_ADC_INPUT - FIRST_ADC_INPUT; i++)
//		if (analog[i] < MAX_ADC_DATA)
//			sendData(mainPort, "OP", i, analog[i]);
}

inline void timTrigOffEvent()
{
	trigOff(sonarIter);
	flag = 0;
}



int main()
{
	init();
	setSonarCount(SONAR_COUNT);
	setupTimer();
	setupExtInt();


	while (true)
		;

	return 0;
}

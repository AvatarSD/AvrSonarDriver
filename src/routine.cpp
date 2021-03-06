/*
 * timerRoutine.cpp
 *
 *  Created on: 9 лют. 2016
 *      Author: sd
 */

#include "routine.h"
#include "uartport/uartport.h"

#include "platformDepend/ADC/Analog.h"
#define MAX_ADC_DATA	1000
#define MIN_ADC_DATA	100

#define RELAX_TIME		20

volatile uint8_t sonarIter = 0;
volatile uint8_t sonarCurrIterCount;
volatile uint8_t flag[MAX_SONAR_COUNT]; //one enter - one exit pear timer cycle

void sonarPCintHandler(uint16_t timerCurr, uint8_t currPortState,
		uint8_t lastPortState, uint8_t portNum)
{
	uint8_t xorByte = currPortState ^ lastPortState;
	uint8_t pinNum = 0;
	for (; pinNum <= 8; pinNum++, xorByte >>= 1)
		if ((xorByte & 0x01) == 0x01)
			break;
	if (pinNum >= 8)
		return;
	bool pinState = currPortState & (1 << pinNum);
	uint8_t sonarNum = pinNum + portNum * 8;
	sonarRoutineHandler(timerCurr, pinState, sonarNum);
}

void sonarRoutineHandler(uint16_t timerCurr, bool pinState, uint8_t sonarNum)
{
	static uint16_t timerLast[MAX_SONAR_COUNT];

	if ((pinState) && (flag[sonarNum] == 0))
	{
		timerLast[sonarNum] = timerCurr;
		flag[sonarNum] = 1;
	}
	else if ((!pinState) && (flag[sonarNum] == 1))
	{
		unsigned int distance = timerCurr - timerLast[sonarNum];
		distance /= ((double) 58 / 4);
		sendData(mainPort, "SR", sonarNum, distance);
		flag[sonarNum] = -1;
#ifdef RELAX_TIME
		if (--sonarCurrIterCount == 0)
			TIM_VAL = TIM_MAX - (RELAX_TIME * 250);
#endif
	}
}

void timTrigOnEvent()
{
	// uart strobe and iteration point
	sendData(mainPort, "IT", 201, sonarIter);
	static uint16_t counter;
	if (++sonarIter == getIterationCount())
	{
		sonarIter = 0;
		sendData(mainPort, "SB", 200, counter++);
	}

	// trig on
	sonarCurrIterCount = 0;
	for (uint8_t i = 0; i < getSonarCount(); i++)
		if (getMapPosition(sonarIter, i))
		{
			trigOn(i);
			sonarCurrIterCount++;
		}

	// trig off
	delay_ns(10);
	trigOff();
	for (uint8_t i = 0; i < getSonarCount(); i++)
		flag[i] = 0;

	//ADC routine for optical
	for (uint8_t i = 0; i <= (LAST_ADC_INPUT - FIRST_ADC_INPUT); i++)
		if ((analog[i] > MIN_ADC_DATA)&&(analog[i] < MAX_ADC_DATA))
			sendData(mainPort, "OP", i, analog[i]);
}

uint8_t getCurrentIteration()
{
	return sonarIter;
}

/*
 * timerRoutine.h
 *
 *  Created on: 9 лют. 2016
 *      Author: sd
 */

#ifndef PLATFORMDEPEND_TIMERROUTINE_H_
#define PLATFORMDEPEND_TIMERROUTINE_H_

#include "inttypes.h"

void sonarPCintHandler(uint16_t timerCurr, uint8_t currPortState,
		uint8_t lastPortState, uint8_t portNum);
void sonarRoutineHandler(uint16_t timerCurr, bool pinState, uint8_t sonarNum);
void timTrigOnEvent();
void timTrigOffEvent();

inline void PCintFastHandler(uint8_t port, uint8_t portNum)
{
	static volatile uint8_t lastSnap = 0, lastSnapR;
	cli();
	volatile uint8_t currSnap = port;
	volatile uint16_t timCurr = TIM_VAL;
	lastSnapR = lastSnap;
	lastSnap = currSnap;
	sei();

	sonarPCintHandler(timCurr, currSnap, lastSnapR, portNum);
}

inline void PCintSingleFastHandler(uint8_t port, uint8_t portNum)
{
	cli();
	volatile uint8_t currSnap = port;
	volatile uint16_t timCurr = TIM_VAL;
	sei();

	uint8_t sonarNum = 0;
	for (; sonarNum < MAX_SONAR_COUNT; sonarNum++)
		if (getMapPosition(sonarIter, sonarNum))
			break;

	sonarRoutineHandler(timCurr, (currSnap & (1 << (sonarNum - portNum * 8))),
			sonarNum);

}

#endif /* PLATFORMDEPEND_TIMERROUTINE_H_ */

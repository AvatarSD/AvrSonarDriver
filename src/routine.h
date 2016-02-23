/*
 * timerRoutine.h
 *
 *  Created on: 9 лют. 2016
 *      Author: sd
 */

#ifndef PLATFORMDEPEND_TIMERROUTINE_H_
#define PLATFORMDEPEND_TIMERROUTINE_H_

#include "inttypes.h"
#include "map/timingmap.h"
#include <avr/interrupt.h>

void sonarPCintHandler(uint16_t timerCurr, uint8_t currPortState,
		uint8_t lastPortState, uint8_t portNum);
void sonarRoutineHandler(uint16_t timerCurr, bool pinState, uint8_t sonarNum);
void timTrigOnEvent();
//void timTrigOffEvent();
uint8_t getCurrentIteration();

/*
 * use for multiply parallel working sonar on one port,
 * instead PCintSingleFastHandler work only with one sonar at same time
 */
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

/*
 * use it for detect rise and fall level on first
 * sonar in row in timingMap at current iteration
 */
inline void PCintSingleFastHandler(uint8_t port, uint8_t portNum)
{
	cli();
	volatile uint8_t currSnap = port;
	volatile uint16_t timCurr = TIM_VAL;
	sei();

	uint8_t sonarNum = portNum * 8;
	for (; sonarNum < ((portNum + 1) * 8); sonarNum++)
		if (getMapPosition(getCurrentIteration(), sonarNum))
			break;

	sonarRoutineHandler(timCurr, (currSnap & (1 << (sonarNum - portNum * 8))), sonarNum);

}

#endif /* PLATFORMDEPEND_TIMERROUTINE_H_ */

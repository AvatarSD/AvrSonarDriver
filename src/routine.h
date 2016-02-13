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

#endif /* PLATFORMDEPEND_TIMERROUTINE_H_ */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "platform.h"


#include "../routine.h"

inline void PCintFastHendler(uint8_t portNum)
{
	static uint8_t lastSnap = 0, lastSnapR;
	cli();
	uint8_t currSnap = PIND;
	uint16_t timCurr = TIM_VAL;
	lastSnapR = lastSnap;
	lastSnap = currSnap;
	sei();

	sonarPCintHandler(timCurr, currSnap, lastSnapR, portNum);
}

// Pin change 0-7 interrupt service routine
ISR(PCINT2_vect)
{
	PCintFastHendler(0);
}



//External Interrupt 0 service routine
//ISR(INT0_vect)
//{
//	cli();
//	uint16_t timCurr = TIM_VAL;
//	sonarRoutineHandler(timCurr, (PIND & (1 << 2)), 0);
//	sei();
//}

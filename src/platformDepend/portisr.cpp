
#include <avr/io.h>
#include <avr/interrupt.h>
#include "platform.h"


#include "../routine.h"

inline void PCintFastHandler(uint8_t portNum)
{
	static volatile uint8_t lastSnap = 0, lastSnapR;
	cli();
	volatile uint8_t currSnap = PIND;
	volatile uint16_t timCurr = TIM_VAL;
	lastSnapR = lastSnap;
	lastSnap = currSnap;
	sei();

	sonarPCintHandler(timCurr, currSnap, lastSnapR, portNum);
}

// Pin change 0-7 interrupt service routine
ISR(PCINT2_vect)
{
	PCintFastHandler(0);
}



//External Interrupt 0 service routine
//ISR(INT0_vect)
//{
//	cli();
//	uint16_t timCurr = TIM_VAL;
//	sonarRoutineHandler(timCurr, (PIND & (1 << 2)), 0);
//	sei();
//}

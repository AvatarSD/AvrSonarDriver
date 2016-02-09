
#include <avr/io.h>
#include <avr/interrupt.h>
#include "platform.h"

// Pin change 0-7 interrupt service routine
ISR(PCINT2_vect)
{
	cli();
	uint8_t currSnap = PIND;
	uint16_t timCurr = TIM_VAL;

	bool pinState = (currSnap & (1 << (sonarIter + 2)));

	sonarRoutineHandler(timCurr, pinState, sonarIter);
	sei();
}



//External Interrupt 0 service routine
//ISR(INT0_vect)
//{
//	cli();
//	uint16_t timCurr = TIM_VAL;
//	sonarRoutineHandler(timCurr, (PIND & (1 << 2)), 0);
//	sei();
//}

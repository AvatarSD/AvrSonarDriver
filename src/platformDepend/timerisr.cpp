
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../routine.h"

// Timer1 input capture interrupt service routine
ISR(TIMER1_CAPT_vect)
{
	timTrigOnEvent();
}

// Timer1 output compare A interrupt service routine
//ISR(TIMER1_COMPA_vect)
//{
//	timTrigOffEvent();
//}

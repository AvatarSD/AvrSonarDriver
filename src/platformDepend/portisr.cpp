#include <avr/io.h>
#include <avr/interrupt.h>
#include "platform.h"

#include "../routine.h"

/*
 * PORTB(PCINT0-7) is 0-7 sonars echo input
 * PORTA is trig for 0-7 sonars trig output
 * PORTC is trig for 8-15 sonars trig output
 * INT0-7 is 8-15 sonars echo input for parallel working
 * PORTF and PORTK is analog input for optical sensor
 *
 * PORTD0-3 is INT0-3
 * PORTE4-7 is INT4-7
 */


// Pin change 0-7 interrupt service routine
ISR(PCINT0_vect)
{
	PCintSingleFastHandler(PINB, 0);
	//PCintFastHandler(PINB, 0);
}

ISR(INT0_vect)
{
	cli();
	uint8_t currSnap = PIND;
	uint16_t timCurr = TIM_VAL;
	sei();

	sonarRoutineHandler(timCurr, (currSnap & (1 << 0)), 8);
}

ISR(INT1_vect)
{
	cli();
	uint8_t currSnap = PIND;
	uint16_t timCurr = TIM_VAL;
	sei();

	sonarRoutineHandler(timCurr, (currSnap & (1 << 1)), 9);
}

ISR(INT2_vect)
{
	cli();
	uint8_t currSnap = PIND;
	uint16_t timCurr = TIM_VAL;
	sei();

	sonarRoutineHandler(timCurr, (currSnap & (1 << 2)), 10);
}

ISR(INT3_vect)
{
	cli();
	uint8_t currSnap = PIND;
	uint16_t timCurr = TIM_VAL;
	sei();

	sonarRoutineHandler(timCurr, (currSnap & (1 << 3)), 11);
}

ISR(INT4_vect)
{
	cli();
	uint8_t currSnap = PINE;
	uint16_t timCurr = TIM_VAL;
	sei();

	sonarRoutineHandler(timCurr, (currSnap & (1 << 4)), 12);
}

ISR(INT5_vect)
{
	cli();
	uint8_t currSnap = PINE;
	uint16_t timCurr = TIM_VAL;
	sei();

	sonarRoutineHandler(timCurr, (currSnap & (1 << 5)), 13);
}

ISR(INT6_vect)
{
	cli();
	uint8_t currSnap = PINE;
	uint16_t timCurr = TIM_VAL;
	sei();

	sonarRoutineHandler(timCurr, (currSnap & (1 << 6)), 14);
}

ISR(INT7_vect)
{
	cli();
	uint8_t currSnap = PINE;
	uint16_t timCurr = TIM_VAL;
	sei();

	sonarRoutineHandler(timCurr, (currSnap & (1 << 7)), 15);
}

//External Interrupt 0 service routine
//ISR(INT0_vect)
//{
//	cli();
//	uint16_t timCurr = TIM_VAL;
//	sonarRoutineHandler(timCurr, (PIND & (1 << 2)), 0);
//	sei();
//}

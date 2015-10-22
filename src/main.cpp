/*
 * main.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "init/init.h"
#include "UART/UART.h"
#include "ADC/Analog.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "util/delay.h"

UART mainPort(UDR0, 115200, 128, 32);

// Pin change 0-7 interrupt service routine
ISR(PCINT0_vect)//interrupt [PC_INT0] void pin_change_isr0(void)
{
	// Place your code here

}

// Pin change 8-15 interrupt service routine
ISR(PCINT1_vect)//interrupt [PC_INT1] void pin_change_isr1(void)
{
	// Place your code here

}

// External Interrupt 0 service routine
ISR(INT0_vect)//interrupt [EXT_INT0] void ext_int0_isr(void)
{
	// Place your code here

}

// External Interrupt 1 service routine
ISR(INT1_vect)//interrupt [EXT_INT1] void ext_int1_isr(void)
{
	// Place your code here

}

// External Interrupt 2 service routine
ISR(INT2_vect)//interrupt [EXT_INT2] void ext_int2_isr(void)
{
	// Place your code here

}

// External Interrupt 3 service routine
ISR(INT3_vect)//interrupt [EXT_INT3] void ext_int3_isr(void)
{
	// Place your code here

}

// External Interrupt 4 service routine
ISR(INT4_vect)//interrupt [EXT_INT4] void ext_int4_isr(void)
{
	// Place your code here

}

// External Interrupt 5 service routine
ISR(INT5_vect)//interrupt [EXT_INT5] void ext_int5_isr(void)
{
	// Place your code here

}

// External Interrupt 6 service routine
ISR(INT6_vect)//interrupt [EXT_INT6] void ext_int6_isr(void)
{
	// Place your code here

}

// External Interrupt 7 service routine
ISR(INT7_vect)//interrupt [EXT_INT7] void ext_int7_isr(void)
{
	// Place your code here

}

// Timer1 input capture interrupt service routine
ISR(TIMER1_CAPT_vect)//interrupt [TIM1_CAPT] void timer1_capt_isr(void)
{
	// Place your code here

}

// Timer1 output compare A interrupt service routine
ISR(TIMER1_COMPA_vect)//interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
	// Place your code here

}



int main()
{
	init();


	DDRB |= (1<<7);

	while(true)
	{
		_delay_ms(300);

		PORTB ^= (1<<7);
		//mainPort("Hello!\r\n");
	}
	return 0;
}

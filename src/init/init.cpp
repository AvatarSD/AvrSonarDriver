/*
 * init.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "init.h"
#include <avr/io.h>
#include <avr/iom2560.h>
#include <util/atomic.h>

void init()
{

	// Input/Output Ports initialization
	// Port A initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

	// Port B initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

	// Port C initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

	// Port D initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

	// Port E initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (0<<DDE2) | (0<<DDE1) | (0<<DDE0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTE=(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

	// Port F initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTF=(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

	// Port G initialization
	// Function: Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRG=(0<<DDG5) | (0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (0<<DDG1) | (0<<DDG0);
	// State: Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTG=(0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

	// Port H initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRH=(0<<DD7) | (0<<DD6) | (0<<DD5) | (0<<DD4) | (0<<DD3) | (0<<DD2) | (0<<DD1) | (0<<DD0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTH=(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

	// Port J initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRJ=(0<<DD7) | (0<<DD6) | (0<<DD5) | (0<<DD4) | (0<<DD3) | (0<<DD2) | (0<<DD1) | (0<<DD0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTJ=(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

	// Port K initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRK=(0<<DD7) | (0<<DD6) | (0<<DD5) | (0<<DD4) | (0<<DD3) | (0<<DD2) | (0<<DD1) | (0<<DD0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTK=(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

	// Port L initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRL=(0<<DD7) | (0<<DD6) | (0<<DD5) | (0<<DD4) | (0<<DD3) | (0<<DD2) | (0<<DD1) | (0<<DD0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTL=(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: Timer 0 Stopped
	// Mode: Normal top=0xFF
	// OC0A output: Disconnected
	// OC0B output: Disconnected
	TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
	TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
	TCNT0=0x00;
	OCR0A=0x00;
	OCR0B=0x00;



	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: Timer2 Stopped
	// Mode: Normal top=0xFF
	// OC2A output: Disconnected
	// OC2B output: Disconnected
	ASSR=(0<<EXCLK) | (0<<AS2);
	TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
	TCCR2B=(0<<WGM22) | (0<<CS22) | (0<<CS21) | (0<<CS20);
	TCNT2=0x00;
	OCR2A=0x00;
	OCR2B=0x00;

	// Timer/Counter 3 initialization
	// Clock source: System Clock
	// Clock value: Timer3 Stopped
	// Mode: Normal top=0xFFFF
	// OC3A output: Disconnected
	// OC3B output: Disconnected
	// OC3C output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer3 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	// Compare C Match Interrupt: Off
	TCCR3A=(0<<COM3A1) | (0<<COM3A0) | (0<<COM3B1) | (0<<COM3B0) | (0<<COM3C1) | (0<<COM3C0) | (0<<WGM31) | (0<<WGM30);
	TCCR3B=(0<<ICNC3) | (0<<ICES3) | (0<<WGM33) | (0<<WGM32) | (0<<CS32) | (0<<CS31) | (0<<CS30);
	TCNT3H=0x00;
	TCNT3L=0x00;
	ICR3H=0x00;
	ICR3L=0x00;
	OCR3AH=0x00;
	OCR3AL=0x00;
	OCR3BH=0x00;
	OCR3BL=0x00;
	OCR3CH=0x00;
	OCR3CL=0x00;

	// Timer/Counter 4 initialization
	// Clock source: System Clock
	// Clock value: Timer4 Stopped
	// Mode: Normal top=0xFFFF
	// OC4A output: Disconnected
	// OC4B output: Disconnected
	// OC4C output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer4 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	// Compare C Match Interrupt: Off
	TCCR4A=(0<<COM4A1) | (0<<COM4A0) | (0<<COM4B1) | (0<<COM4B0) | (0<<COM4C1) | (0<<COM4C0) | (0<<WGM41) | (0<<WGM40);
	TCCR4B=(0<<ICNC4) | (0<<ICES4) | (0<<WGM43) | (0<<WGM42) | (0<<CS42) | (0<<CS41) | (0<<CS40);
	TCNT4H=0x00;
	TCNT4L=0x00;
	ICR4H=0x00;
	ICR4L=0x00;
	OCR4AH=0x00;
	OCR4AL=0x00;
	OCR4BH=0x00;
	OCR4BL=0x00;
	OCR4CH=0x00;
	OCR4CL=0x00;

	// Timer/Counter 5 initialization
	// Clock source: System Clock
	// Clock value: Timer5 Stopped
	// Mode: Normal top=0xFFFF
	// OC5A output: Disconnected
	// OC5B output: Disconnected
	// OC5C output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer5 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	// Compare C Match Interrupt: Off
	TCCR5A=(0<<COM5A1) | (0<<COM5A0) | (0<<COM5B1) | (0<<COM5B0) | (0<<COM5C1) | (0<<COM5C0) | (0<<WGM51) | (0<<WGM50);
	TCCR5B=(0<<ICNC5) | (0<<ICES5) | (0<<WGM53) | (0<<WGM52) | (0<<CS52) | (0<<CS51) | (0<<CS50);
	TCNT5H=0x00;
	TCNT5L=0x00;
	ICR5H=0x00;
	ICR5L=0x00;
	OCR5AH=0x00;
	OCR5AL=0x00;
	OCR5BH=0x00;
	OCR5BL=0x00;
	OCR5CH=0x00;
	OCR5CL=0x00;

	// Timer/Counter 0 Interrupt(s) initialization
	TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);



	// Timer/Counter 2 Interrupt(s) initialization
	TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2);

	// Timer/Counter 3 Interrupt(s) initialization
	TIMSK3=(0<<ICIE3) | (0<<OCIE3C) | (0<<OCIE3B) | (0<<OCIE3A) | (0<<TOIE3);

	// Timer/Counter 4 Interrupt(s) initialization
	TIMSK4=(0<<ICIE4) | (0<<OCIE4C) | (0<<OCIE4B) | (0<<OCIE4A) | (0<<TOIE4);

	// Timer/Counter 5 Interrupt(s) initialization
	TIMSK5=(0<<ICIE5) | (0<<OCIE5C) | (0<<OCIE5B) | (0<<OCIE5A) | (0<<TOIE5);


	// Analog Comparator initialization
	// Analog Comparator: Off
	// The Analog Comparator's positive input is
	// connected to the AIN0 pin
	// The Analog Comparator's negative input is
	// connected to the AIN1 pin
	ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
	// Digital input buffer on AIN0: On
	// Digital input buffer on AIN1: On
	DIDR1=(0<<AIN0D) | (0<<AIN1D);

	// SPI initialization
	// SPI disabled
	SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

	// TWI initialization
	// TWI disabled
	TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

	// Global enable interrupts
	sei();



}


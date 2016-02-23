/*
 * platformDepend.cpp
 *
 *  Created on: 9 лют. 2016
 *      Author: sd
 */

#include "platform.h"

#include <avr/io.h>
#include <avr/eeprom.h>

volatile uint8_t sonarsCount;

UART mainPort(UART_PORT, UART_SPEED, UART_TX_BUFF, UART_RX_BUF);

ISR(UART_RX_INT_VEC)
{
	mainPort.rx_byte_int();
}
ISR(UART_TX_INT_VEC)
{
	mainPort.tx_byte_int();
}

void trigOn(uint8_t pin)
{
	if (pin < 8)
		PORTA |= (1 << pin);
	else if ((pin >= 8)&&(pin < 16))
		PORTC |= (1 << (pin - 8));
}

void trigOff(uint8_t pin)
{
	if (pin < 8)
		PORTA &= ~(1 << pin);
	else if ((pin >= 8)&&(pin < 16))
		PORTC &= ~(1 << (pin - 8));
}

void trigOff()
{
		PORTA = 0x00;
		PORTC = 0x00;
}

void pinTrigOutOn(uint8_t pin)
{
	if (pin < 8)
		DDRA |= (1 << pin);
	else if ((pin >= 8)&&(pin < 16))
		DDRC |= (1 << (pin - 8));
}

void pinTrigOutOff(uint8_t pin)
{
	if (pin < 8)
		DDRA &= ~(1 << pin);
	else if ((pin >= 8)&&(pin < 16))
		DDRC &= ~(1 << (pin - 8));
}

void setSonarCount(uint8_t count)
{
	sonarsCount = count;
	for (uint8_t pin = 0; pin < MAX_SONAR_COUNT; pin++)
		if (pin < count)
			pinTrigOutOn(pin);
		else
			pinTrigOutOff(pin);
}

uint8_t getSonarCount()
{
	return sonarsCount;
}

void init()
{
	// Input/Output Ports initialization


	// Port G initialization
	// Function: Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRG=(0<<DDG5) | (0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (0<<DDG1) | (0<<DDG0);
	// State: Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTG=(0<<PORTG5) | (0<<PORTG4) | (0<<PORTG3) | (0<<PORTG2) | (0<<PORTG1) | (0<<PORTG0);

	// Port H initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRH=(0<<DDH7) | (0<<DDH6) | (0<<DDH5) | (0<<DDH4) | (0<<DDH3) | (0<<DDH2) | (0<<DDH1) | (0<<DDH0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTH=(0<<PORTH7) | (0<<PORTH6) | (0<<PORTH5) | (0<<PORTH4) | (0<<PORTH3) | (0<<PORTH2) | (0<<PORTH1) | (0<<PORTH0);

	// Port J initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRJ=(0<<DDJ7) | (0<<DDJ6) | (0<<DDJ5) | (0<<DDJ4) | (0<<DDJ3) | (0<<DDJ2) | (0<<DDJ1) | (0<<DDJ0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTJ=(0<<PORTJ7) | (0<<PORTJ6) | (0<<PORTJ5) | (0<<PORTJ4) | (0<<PORTJ3) | (0<<PORTJ2) | (0<<PORTJ1) | (0<<PORTJ0);

	// Port L initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRL=(0<<DDL7) | (0<<DDL6) | (0<<DDL5) | (0<<DDL4) | (0<<DDL3) | (0<<DDL2) | (0<<DDL1) | (0<<DDL0);
	// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
	PORTL=(0<<PORTL7) | (0<<PORTL6) | (0<<PORTL5) | (0<<PORTL4) | (0<<PORTL3) | (0<<PORTL2) | (0<<PORTL1) | (0<<PORTL0);

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

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 250,000 kHz
	// Mode: CTC top=ICR1
	// OC1A output: Disconnected
	// OC1B output: Disconnected
	// OC1C output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 60 ms
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: On
	// Compare A Match Interrupt: On
	// Compare B Match Interrupt: Off
	// Compare C Match Interrupt: Off
//	TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
//	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10);
//	TCNT1H=0x00;
//	TCNT1L=0x00;
//	ICR1H=0x3A;
//	ICR1L=0x97;
//	OCR1AH=0x00;
//	OCR1AL=0x03;
//	OCR1BH=0x00;
//	OCR1BL=0x00;
//	OCR1CH=0x00;
//	OCR1CL=0x00;

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

	// Timer/Counter 1 Interrupt(s) initialization
	//TIMSK1=(1<<ICIE1) | (0<<OCIE1C) | (0<<OCIE1B) | (1<<OCIE1A) | (0<<TOIE1);

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

	// Global enable interrupts
	sei();

}

void setupTimer()
{
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 250,000 kHz
	// Mode: CTC top=ICR1
	// OC1A output: Disconnected
	// OC1B output: Disconnected
	// OC1C output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 60 ms
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: On
	// Compare A Match Interrupt: On
	// Compare B Match Interrupt: Off
	// Compare C Match Interrupt: Off
	TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0)
			| (0 << WGM11) | (0 << WGM10);
	TCCR1B = (0 << ICNC1) | (0 << ICES1) | (1 << WGM13) | (1 << WGM12)
			| (0 << CS12) | (1 << CS11) | (1 << CS10);
	TCNT1 = 0x0000;

	ICR1 = TIM_MAX;
	OCR1A = 3;

	// Timer/Counter 1 Interrupt(s) initialization
	TIMSK1 = (1 << ICIE1) | (0 << OCIE1B) | (0 << OCIE1A) | (0 << TOIE1);
}

void setupExtInt()
{
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
	PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (0<<PORTE1) | (0<<PORTE0);

	// Port F initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
	// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P
	PORTF=(1<<PORTF7) | (1<<PORTF6) | (1<<PORTF5) | (1<<PORTF4) | (1<<PORTF3) | (1<<PORTF2) | (1<<PORTF1) | (1<<PORTF0);

	// Port K initialization
	// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
	DDRK=(0<<DDK7) | (0<<DDK6) | (0<<DDK5) | (0<<DDK4) | (0<<DDK3) | (0<<DDK2) | (0<<DDK1) | (0<<DDK0);
	// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P
	PORTK=(1<<PORTK7) | (1<<PORTK6) | (1<<PORTK5) | (1<<PORTK4) | (1<<PORTK3) | (1<<PORTK2) | (1<<PORTK1) | (1<<PORTK0);


	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Any change
	// INT1: On
	// INT1 Mode: Any change
	// INT2: On
	// INT2 Mode: Any change
	// INT3: On
	// INT3 Mode: Any change
	// INT4: On
	// INT4 Mode: Any change
	// INT5: On
	// INT5 Mode: Any change
	// INT6: On
	// INT6 Mode: Any change
	// INT7: On
	// INT7 Mode: Any change
	EICRA=(0<<ISC31) | (1<<ISC30) | (0<<ISC21) | (1<<ISC20) | (0<<ISC11) | (1<<ISC10) | (0<<ISC01) | (1<<ISC00);
	EICRB=(0<<ISC71) | (1<<ISC70) | (0<<ISC61) | (1<<ISC60) | (0<<ISC51) | (1<<ISC50) | (0<<ISC41) | (1<<ISC40);
	EIMSK=(1<<INT7) | (1<<INT6) | (1<<INT5) | (1<<INT4) | (1<<INT3) | (1<<INT2) | (1<<INT1) | (1<<INT0);
	EIFR=(1<<INTF7) | (1<<INTF6) | (1<<INTF5) | (1<<INTF4) | (1<<INTF3) | (1<<INTF2) | (1<<INTF1) | (1<<INTF0);
	// PCINT0 interrupt: On
	// PCINT1 interrupt: On
	// PCINT2 interrupt: On
	// PCINT3 interrupt: On
	// PCINT4 interrupt: On
	// PCINT5 interrupt: On
	// PCINT6 interrupt: On
	// PCINT7 interrupt: On
	// PCINT8 interrupt: Off
	// PCINT9 interrupt: Off
	// PCINT10 interrupt: Off
	// PCINT11 interrupt: Off
	// PCINT12 interrupt: Off
	// PCINT13 interrupt: Off
	// PCINT14 interrupt: Off
	// PCINT15 interrupt: Off
	// PCINT16 interrupt: Off
	// PCINT17 interrupt: Off
	// PCINT18 interrupt: Off
	// PCINT19 interrupt: Off
	// PCINT20 interrupt: Off
	// PCINT21 interrupt: Off
	// PCINT22 interrupt: Off
	// PCINT23 interrupt: Off
	PCMSK0=(1<<PCINT7) | (1<<PCINT6) | (1<<PCINT5) | (1<<PCINT4) | (1<<PCINT3) | (1<<PCINT2) | (1<<PCINT1) | (1<<PCINT0);
	PCMSK1=(0<<PCINT15) | (0<<PCINT14) | (0<<PCINT13) | (0<<PCINT12) | (0<<PCINT11) | (0<<PCINT10) | (0<<PCINT9) | (0<<PCINT8);
	PCMSK2=(0<<PCINT23) | (0<<PCINT22) | (0<<PCINT21) | (0<<PCINT20) | (0<<PCINT19) | (0<<PCINT18) | (0<<PCINT17) | (0<<PCINT16);
	PCICR=(0<<PCIE2) | (0<<PCIE1) | (1<<PCIE0);
}

uint8_t sonarsCountEeprom EEMEM;
void saveSonarCount()
{
	eeprom_write_byte(&sonarsCountEeprom, getSonarCount());
}

void loadSonarCount()
{
	setSonarCount(eeprom_read_byte(&sonarsCountEeprom));
}

uint8_t iterEepromc EEMEM;
void saveIterCount(uint8_t count)
{
	eeprom_write_byte(&iterEepromc, count);
}

uint8_t loadIterCount()
{
	return eeprom_read_byte(&iterEepromc);
}

bool mapeeprom[MAP_SIZE] EEMEM;
void saveMapEeprom(const bool * map)
{
	eeprom_write_block(map, mapeeprom, MAP_SIZE);
}

void loadMapEeprom(bool * map)
{
	eeprom_read_block(map, mapeeprom, MAP_SIZE);
}

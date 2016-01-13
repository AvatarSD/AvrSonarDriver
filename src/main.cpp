/*
 * main.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "init/init.h"
#include "UART/UART.h"
//#include "ADC/Analog.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "string.h"

/********* Settings ********/
#define UART_PORT 		UDR0
#define UART_SPEED 		115200
#define UART_TX_BUFF 	128
#define UART_RX_BUF 	32
#define UART_RX_INT_VEC USART_RX_vect
#define UART_TX_INT_VEC USART_TX_vect
//#define MAX_ADC_DATA	1000
//#define STR_VAL
/***************************/

#define TIM_VAL TCNT1
#define TIM_MAX 0xFFFF
uint8_t SONARS_COUNT = 4;
volatile uint8_t sonarIter = 0;
int8_t flag = 0;

UART mainPort(UART_PORT, UART_SPEED, UART_TX_BUFF, UART_RX_BUF);

ISR(UART_RX_INT_VEC)
{
	mainPort.rx_byte_int();
}

ISR(UART_TX_INT_VEC)
{
	mainPort.tx_byte_int();
}

inline void sendData(UART & port, const char* portName, uint8_t pinNum,
		uint16_t distance)
{
	unsigned char buff[8] =
	{ '$' };
	buff[1] = portName[0];
	buff[2] = portName[1];
	buff[3] = pinNum;
	buff[4] = distance & 0xff;
	buff[5] = (distance >> 8) & 0xff;
	for (uint8_t i = 0; i < 6; i++)
		buff[6] ^= buff[i];
	buff[7] = 0;
	//cli();
	port.WriteCOM(8, buff);
	//sei();
}

inline void sonarRoutineHandler(uint16_t timerCurr, bool pin, uint8_t sonarNum,
		UART & port)
{
	static uint16_t timerLast;

if ((pin) && (flag == 0))
	{
		timerLast = timerCurr;
		flag = 1;
	}
	else if (flag == true)
	{
		unsigned int distance = timerCurr - timerLast;
		distance /= ((double) 58 / 4);
		sendData(port, "SR", sonarNum, distance);
		flag = -1;
		TIM_VAL = TIM_MAX;
	}
}

void trigOn(uint8_t pin)
{
	if (pin < 5)
	{
		DDRB |= (1 << pin);
		PORTB |= (1 << pin);
	}
	else if (pin < 10)
	{
		DDRD |= (1 << (pin - 2));
		PORTD |= (1 << (pin - 2));
	}
	else if (pin < 16)
	{
		DDRC |= (1 << (pin - 10));
		PORTC |= (1 << (pin - 10));
	}
}

void trigOff(uint8_t pin)
{
	if (pin < 5)
	{
		PORTB &= ~(1 << pin);
		DDRB &= ~(1 << pin);
	}
	else if (pin < 10)
	{
		PORTD &= ~(1 << (pin - 2));
		DDRD &= ~(1 << (pin - 2));
	}
	else if (pin < 16)
	{
		PORTC &= ~(1 << (pin - 10));
		DDRC &= ~(1 << (pin - 10));
	}
}

// External Interrupt 0 service routine
ISR(INT0_vect)
{
	cli();
	sonarRoutineHandler(TIM_VAL, (PIND & (1 << 2)), sonarIter, mainPort);
	sei();
}

// Timer1 input capture interrupt service routine
ISR(TIMER1_CAPT_vect)
{
	if (++sonarIter == SONARS_COUNT)
	{
		static uint16_t counter;
		sendData(mainPort, "SB", 200, counter++);
		sonarIter = 0;
	}
	trigOn(sonarIter);

//	for (uint8_t i = 0; i < LAST_ADC_INPUT - FIRST_ADC_INPUT; i++)
//		if (analog[i] < MAX_ADC_DATA)
//			sendData(mainPort, "OP", i, analog[i]);
}

// Timer1 output compare A interrupt service routine
ISR(TIMER1_COMPA_vect)
{
	trigOff(sonarIter);
	flag = 0;
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
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	ICR1H = 0x3A;
	ICR1L = 0x97;
	OCR1AH = 0x00;
	OCR1AL = 3;	//0x03;
	OCR1BH = 0x00;
	OCR1BL = 0x00;

	// Timer/Counter 1 Interrupt(s) initialization
	TIMSK1 = (1 << ICIE1) | (0 << OCIE1B) | (1 << OCIE1A) | (0 << TOIE1);
}

void setupExtInt()
{
	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Any change
	// INT1: On
	// INT1 Mode: Any change
	// Interrupt on any change on pins PCINT0-7: On
	// Interrupt on any change on pins PCINT8-14: On
	// Interrupt on any change on pins PCINT16-23: Off
	EICRA = (0 << ISC11) | (0 << ISC10) | (0 << ISC01) | (1 << ISC00);
	EIMSK = (0 << INT1) | (1 << INT0);
	EIFR = (0 << INTF1) | (1 << INTF0);
//	PCICR = (0 << PCIE2) | (1 << PCIE1) | (1 << PCIE0);
//	PCMSK0 = (1 << PCINT4) | (1 << PCINT3) | (1 << PCINT2) | (1 << PCINT1)
//			| (1 << PCINT0);
//	PCMSK1 = (1 << PCINT13) | (1 << PCINT12) | (1 << PCINT11) | (1 << PCINT10)
//			| (1 << PCINT9) | (1 << PCINT8);
//	PCIFR = (0 << PCIF2) | (1 << PCIF1) | (1 << PCIF0);

//	PORTB = (1 << PORTB4) | (1 << PORTB3) | (1 << PORTB2) | (1 << PORTB1)
//			| (1 << PORTB0);
//	PORTC = (1 << PORTC5) | (1 << PORTC4) | (1 << PORTC3) | (1 << PORTC2)
//			| (1 << PORTC1) | (1 << PORTC0);

}

int main()
{
	init();
	setupTimer();
	setupExtInt();

//	ARDU_LED_SETUP;
//	TRIGGER_SETUP;

	//mainPort("Hello!\r\n");

	while (true)
		;

	return 0;
}

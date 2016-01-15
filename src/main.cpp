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
#define MAX_SONAR_COUNT 6
#define RELAX_TIME		20
//#define MAX_ADC_DATA	1000
//#define STR_VAL
/***************************/

#define TIM_VAL TCNT1
#define TIM_MAX 0xFFFF
uint8_t sonarsCount;
volatile uint8_t sonarIter = 0;
uint8_t flag[MAX_SONAR_COUNT];

#define SONAR_ROUTINE_HANDLER sonarRoutineHandler(TIM_VAL, \
		timerLast[SONAR_NUM], \
		SONAR_PIN_REG, \
		SONAR_PIN_NUM, \
		flag[SONAR_NUM], \
		mainPort, \
		SONAR_NUM)

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
	cli();
	port.WriteCOM(8, buff);
	sei();
}

inline void sonarRoutineHandler(uint16_t timerCurr, bool pinState,
		uint8_t sonarNum)
{
	static uint16_t timerLast[MAX_SONAR_COUNT];

//	if(sonarIter != sonarNum)
//		return;

	if ((pinState) && (flag[sonarNum] == 0))
	{
		timerLast[sonarNum] = timerCurr;
		flag[sonarNum] = 1;
	}
	else if (flag[sonarNum] == 1)
	{
		unsigned int distance = timerCurr - timerLast[sonarNum];
		distance /= ((double) 58 / 4);
		sendData(mainPort, "SR", sonarNum, distance);
		flag[sonarNum] = -1;
		TIM_VAL = ICR1 - (RELAX_TIME * 250);
	}

}

inline void pcIntRoutineHandler(uint8_t currSnapPCint, uint8_t & lastSnapPCint,
		uint16_t currTimerVal, uint8_t pinStart)
{
	uint8_t xorByte = currSnapPCint ^ lastSnapPCint;
	lastSnapPCint = currSnapPCint;

	uint8_t pinNum = 0;
	for (; pinNum <= 8; pinNum++, xorByte >>= 1)
		if ((xorByte & 0x01) == 0x01)
			break;

	if (pinNum >= 8)
		return;

	bool pinState = ((currSnapPCint & (1 << pinNum)) >> pinNum);

	sonarRoutineHandler(currTimerVal, pinState, pinNum + pinStart);

}

// Pin change 0-7 interrupt service routine
ISR(PCINT2_vect)
{
	cli();
	uint8_t currSnapPCint = PIND;
	uint16_t currTimerVal = TIM_VAL;


	static uint8_t lastSnapPCint = 0;
	pcIntRoutineHandler(currSnapPCint, lastSnapPCint, currTimerVal, 0);
	sei();
}

void trigOn(uint8_t pin)
{
	if (pin < 6)
		PORTB |= (1 << pin);
}

void trigOff(uint8_t pin)
{
	if (pin < 6)
		PORTB &= ~(1 << pin);
}

void setSonarCount(uint8_t count)
{
	sonarsCount = count;
	for (uint8_t pin = 0; pin < MAX_SONAR_COUNT; pin++)
		if (pin < 6)
		{
			if (pin >= count)
				DDRB &= ~(1 << pin);
			else
				DDRB |= (1 << pin);
		}
}

//External Interrupt 0 service routine
//ISR(INT0_vect)
//{
//	cli();
//	uint16_t timCurr = TIM_VAL;
//	sonarRoutineHandler(timCurr, (PIND & (1 << 2)), 0);
//	sei();
//}

// Timer1 input capture interrupt service routine
ISR(TIMER1_CAPT_vect)
{
	if (++sonarIter == sonarsCount)
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
	flag[sonarIter] = 0;
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

	ICR1 = 0x3A97;
	OCR1A = 3;

	// Timer/Counter 1 Interrupt(s) initialization
	TIMSK1 = (1 << ICIE1) | (0 << OCIE1B) | (1 << OCIE1A) | (0 << TOIE1);
}

void setupExtInt()
{
	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	// Interrupt on any change on pins PCINT0-7: Off
	// Interrupt on any change on pins PCINT8-14: Off
	// Interrupt on any change on pins PCINT16-23: On
	EICRA = (0 << ISC11) | (0 << ISC10) | (0 << ISC01) | (0 << ISC00);
	EIMSK = (0 << INT1) | (0 << INT0);
	PCICR = (1 << PCIE2) | (0 << PCIE1) | (0 << PCIE0);
	PCMSK2 = (1 << PCINT23) | (1 << PCINT22) | (1 << PCINT21) | (1 << PCINT20)
			| (1 << PCINT19) | (1 << PCINT18) | (0 << PCINT17) | (0 << PCINT16);
	PCIFR = (1 << PCIF2) | (0 << PCIF1) | (0 << PCIF0);

//	EICRA=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (1<<ISC00);
//	EIMSK=(0<<INT1) | (1<<INT0);
//	EIFR=(0<<INTF1) | (1<<INTF0);
//	PCICR=(0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);
}

int main()
{
	init();
	setSonarCount(4);
	setupTimer();
	setupExtInt();

//	ARDU_LED_SETUP;
//	TRIGGER_SETUP;

	//mainPort("Hello!\r\n");

	while (true)
		;

	return 0;
}

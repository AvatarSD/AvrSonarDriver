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
#define TRIGGER_PORT 	PORTD
#define TRIGGER_DDR 	DDRD
#define TRIGGER_PIN_NUM	7
//#define STR_VAL
/***************************/

#define TIM_VAL TCNT1

#define TRIGGER_TOGGLE 	TRIGGER_PORT ^= (1<<TRIGGER_PIN_NUM)
#define TRIGGER_SETUP 	TRIGGER_DDR |= (1<<TRIGGER_PIN_NUM)
#define TRIGGER_OFF		TRIGGER_PORT &=~ (1<<TRIGGER_PIN_NUM)
#define TRIGGER_ON 		TRIGGER_PORT |= (1<<TRIGGER_PIN_NUM)

#define ARDU_LED_DDR	DDRB
#define ARDU_LED_PORT	PORTB
#define ARDU_LED_PIN	5
#define ARDU_LED_TOGGLE ARDU_LED_PORT ^= (1<<ARDU_LED_PIN)
#define ARDU_LED_SETUP 	ARDU_LED_DDR |= (1<<ARDU_LED_PIN)
#define ARDU_LED_OFF	ARDU_LED_PORT &=~ (1<<ARDU_LED_PIN)
#define ARDU_LED_ON 	ARDU_LED_PORT |= (1<<ARDU_LED_PIN)

#define SONARS_COUNT 18
uint8_t flag[SONARS_COUNT];
uint16_t timerLast[SONARS_COUNT];

#define SONAR_ROUTINE_HANDLER sonarRoutineHandler(TIM_VAL, \
		timerLast[SONAR_NUM], \
		SONAR_PIN_REG, \
		SONAR_PIN_NUM, \
		flag[SONAR_NUM], \
		mainPort, \
		SONAR_NAME)

UART mainPort(UART_PORT, UART_SPEED, UART_TX_BUFF, UART_RX_BUF);

ISR(UART_RX_INT_VEC)
{
	mainPort.rx_byte_int();
}

ISR(UART_TX_INT_VEC)
{
	mainPort.tx_byte_int();
}

inline void sendData(UART & port, const char* pin, uint16_t distance)
{
#ifndef STR_VAL
	unsigned char buff[8] =
	{	'$'};
	for (unsigned char i = 0; i < 3; i++)
	buff[i + 1] = pin[i];
	buff[4] = distance & 0xff;
	buff[5] = (distance >> 8) & 0xff;
	for (uint8_t i = 0; i < 6; i++)
	buff[6] ^= buff[i];
	buff[7] = 0;
	cli();
	port.WriteCOM(8, buff);
	sei();
#else
	char buff[20];
	buff[0] = pin[0];
	buff[1] = pin[1];
	buff[2] = pin[2];
	buff[3] = ' ';
	sprintf(buff + 4, "%d    \t", distance);
	cli();
	port(buff);
	sei();
#endif
}

inline void sonarRoutineHandler(uint16_t timerCurr, uint16_t & timerLast,
		uint8_t pin, uint8_t pinNum, uint8_t & flag, UART & port,
		const char * portName)
{
#define TM_PERIOD_MS 4

	if ((pin & (1 << pinNum)) && (flag == false))
	{
		timerLast = timerCurr;
		flag = true;
	}
	else if (flag == true)
	{
		unsigned int distance = timerCurr - timerLast;
		distance /= ((double) 58 / TM_PERIOD_MS);
		sendData(port, portName, distance);
		flag = -1;
	}

}

inline void pcIntRoutineHandler(volatile uint8_t & PINx, uint8_t numStart,
		uint8_t & lastSnapPCint)
{
	cli();
	uint8_t currSnapPCint = PINx;
	uint16_t currTimerVal = TIM_VAL;
	sei();

	uint8_t xorByte = currSnapPCint ^ lastSnapPCint;
	lastSnapPCint = currSnapPCint;

	uint8_t pinNum = 0;
	for (; pinNum <= 8; pinNum++, xorByte >>= 1)
		if ((xorByte & 0x01) == 0x01)
			break;

	if (pinNum >= 8)
		return;

	uint8_t sonarNum = pinNum + numStart;

	char nameBuff[4] = {'S', 'R', sonarNum, '\0'};
	//sprintf(nameBuff, "S%02d", sonarNum);


	sonarRoutineHandler(currTimerVal, timerLast[sonarNum], currSnapPCint,
			pinNum, flag[sonarNum], mainPort, nameBuff);

}

// Pin change 0-7 interrupt service routine
ISR(PCINT0_vect)
{
#define PCINT_PIN PINB
#define PCINT_NUM_START 2

	static uint8_t lastSnapPCint = 0;
	pcIntRoutineHandler(PCINT_PIN, PCINT_NUM_START, lastSnapPCint);

#undef PCINT_PIN
#undef PCINT_NUM_START
}

// Pin change 8-15 interrupt service routine
ISR(PCINT1_vect)
{
#define PCINT_PIN PINC
#define PCINT_NUM_START 10

	static uint8_t lastSnapPCint = 0;
	pcIntRoutineHandler(PCINT_PIN, PCINT_NUM_START, lastSnapPCint);

#undef PCINT_PIN
#undef PCINT_NUM_START
}

// External Interrupt 0 service routine
ISR(INT0_vect)
{
#define SONAR_NUM 		0
#define SONAR_PIN_REG 	PIND
#define SONAR_PIN_NUM 	2
#define SONAR_NAME 		"SR\0"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// External Interrupt 1 service routine
ISR(INT1_vect)
{
#define SONAR_NUM 		1
#define SONAR_PIN_REG 	PIND
#define SONAR_PIN_NUM 	3
#define SONAR_NAME 		"SR\1"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// Timer1 input capture interrupt service routine
ISR(TIMER1_CAPT_vect)
{
	for (unsigned char i = 0; i < SONARS_COUNT; i++)
	{
		flag[i] = false;
		timerLast[i] = 0;
	}
	TRIGGER_ON;

#ifdef STR_VAL
	ARDU_LED_TOGGLE;
	mainPort("\r\n");
#else
	static uint16_t counter;
	sendData(mainPort, "SB", counter++);
#endif
}

// Timer1 output compare A interrupt service routine
ISR(TIMER1_COMPA_vect)
{
	TRIGGER_OFF;
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
	EICRA = (0 << ISC11) | (1 << ISC10) | (0 << ISC01) | (1 << ISC00);
	EIMSK = (1 << INT1) | (1 << INT0);
	EIFR = (1 << INTF1) | (1 << INTF0);
	PCICR = (0 << PCIE2) | (1 << PCIE1) | (1 << PCIE0);
	PCMSK0 = (1 << PCINT4) | (1 << PCINT3) | (1 << PCINT2) | (1 << PCINT1)
			| (1 << PCINT0);
	PCMSK1 = (1 << PCINT13) | (1 << PCINT12) | (1 << PCINT11) | (1 << PCINT10)
			| (1 << PCINT9) | (1 << PCINT8);
	PCIFR = (0 << PCIF2) | (1 << PCIF1) | (1 << PCIF0);

	PORTB = (1 << PORTB4) | (1 << PORTB3) | (1 << PORTB2) | (1 << PORTB1)
			| (1 << PORTB0);
	PORTC = (1 << PORTC5) | (1 << PORTC4) | (1 << PORTC3) | (1 << PORTC2)
			| (1 << PORTC1) | (1 << PORTC0);

}

int main()
{
	init();
	setupTimer();
	setupExtInt();

	ARDU_LED_SETUP;
	TRIGGER_SETUP;

	mainPort("Hello!\r\n");

	while (true)
		;

	return 0;
}

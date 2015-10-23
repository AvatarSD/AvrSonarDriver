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
#include "stdio.h"
#include "string.h"



/********* Settings ********/
#define UART_PORT 		UDR2
#define UART_SPEED 		115200
#define UART_TX_BUFF 	128
#define UART_RX_BUF 	32
#define UART_RX_INT_VEC USART2_RX_vect
#define UART_TX_INT_VEC USART2_TX_vect
#define TRIGGER_PORT 	PORTH
#define TRIGGER_DDR 	DDRH
#define TRIGGER_PIN_NUM	5
/***************************/

#define TIM_VAL TCNT1

#define TRIGGER_TOGGLE 	TRIGGER_PORT ^= (1<<TRIGGER_PIN_NUM)
#define TRIGGER_SETUP 	TRIGGER_DDR |= (1<<TRIGGER_PIN_NUM)
#define TRIGGER_OFF		TRIGGER_PORT &=~ (1<<TRIGGER_PIN_NUM)
#define TRIGGER_ON 		TRIGGER_PORT |= (1<<TRIGGER_PIN_NUM)


#define ARDU_LED_DDR	DDRB
#define ARDU_LED_PORT	PORTB
#define ARDU_LED_PIN	7
#define ARDU_LED_TOGGLE ARDU_LED_PORT ^= (1<<ARDU_LED_PIN)
#define ARDU_LED_SETUP 	ARDU_LED_DDR |= (1<<ARDU_LED_PIN)
#define ARDU_LED_OFF	ARDU_LED_PORT &=~ (1<<ARDU_LED_PIN)
#define ARDU_LED_ON 	ARDU_LED_PORT |= (1<<ARDU_LED_PIN)


#define STR_VAL


UART mainPort(UART_PORT, UART_SPEED, UART_TX_BUFF, UART_RX_BUF);

ISR(UART_RX_INT_VEC)
{
	mainPort.rx_byte_int();
}

ISR(UART_TX_INT_VEC)
{
	mainPort.tx_byte_int();
}



void sendData(UART & port, const char* pin, unsigned int distance)
{
#ifndef STR_VAL
	char buff[8] = {'$', 'P'};
	buff[2] = pin[1];
	buff[3] = pin[2];
	*(unsigned short int *)(buff+4) = distance;
	for(char i = 0; i < 6; i++)
		buff[6] ^= buff[i];
	buff[7] = 0;
#else
	char buff[14] = {'P'};
	buff[1] = pin[1];
	buff[2] = pin[2];
	buff[3] = ' ';
	sprintf(buff+4, "%d", distance);
	unsigned char buffLen = strlen(buff);
	buff[buffLen] = ' ';
	buff[buffLen+1] = ' ';
	buff[buffLen+2] = 0;
#endif
	port(buff);
}

#define SONARS_COUNT 24
bool flag[SONARS_COUNT];
unsigned int timerLast[SONARS_COUNT];

#define SONAR_ROUTINE_HANDLER sonarRoutineHandler(TIM_VAL, \
		timerLast[SONAR_NUM], \
		SONAR_PIN_REG, \
		SONAR_PIN_NUM, \
		flag[SONAR_NUM], \
		mainPort, \
		SONAR_NAME)

inline void sonarRoutineHandler(
		unsigned int timerCurr,
		unsigned int & timerLast,
		volatile unsigned char pin,
		char pinNum,
		bool & flag,
		UART & port,
		const char * portName)
{
	sei();
	if(pin&(1<<pinNum))
	{
		timerLast = timerCurr;
		flag = true;
	}
	else if(flag)
	{
		unsigned int distance = timerCurr - timerLast;
		distance /= ((double)58/2.5);
		sendData(port, portName, distance);
		flag = false;
	}
	cli();
}



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
#define SONAR_NUM 		0
#define SONAR_PIN_REG 	PIND
#define SONAR_PIN_NUM 	0
#define SONAR_NAME 		"PD0"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// External Interrupt 1 service routine
ISR(INT1_vect)//interrupt [EXT_INT1] void ext_int1_isr(void)
{
#define SONAR_NUM 		1
#define SONAR_PIN_REG 	PIND
#define SONAR_PIN_NUM 	1
#define SONAR_NAME 		"PD1"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// External Interrupt 2 service routine
ISR(INT2_vect)//interrupt [EXT_INT2] void ext_int2_isr(void)
{
#define SONAR_NUM 		2
#define SONAR_PIN_REG 	PIND
#define SONAR_PIN_NUM 	2
#define SONAR_NAME 		"PD2"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// External Interrupt 3 service routine
ISR(INT3_vect)//interrupt [EXT_INT3] void ext_int3_isr(void)
{
#define SONAR_NUM 		3
#define SONAR_PIN_REG 	PIND
#define SONAR_PIN_NUM 	3
#define SONAR_NAME 		"PD3"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// External Interrupt 4 service routine
ISR(INT4_vect)//interrupt [EXT_INT4] void ext_int4_isr(void)
{
#define SONAR_NUM 		4
#define SONAR_PIN_REG 	PINE
#define SONAR_PIN_NUM 	4
#define SONAR_NAME 		"PE4"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// External Interrupt 5 service routine
ISR(INT5_vect)//interrupt [EXT_INT5] void ext_int5_isr(void)
{
#define SONAR_NUM 		5
#define SONAR_PIN_REG 	PINE
#define SONAR_PIN_NUM 	5
#define SONAR_NAME 		"PE5"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// External Interrupt 6 service routine
ISR(INT6_vect)//interrupt [EXT_INT6] void ext_int6_isr(void)
{
#define SONAR_NUM 		6
#define SONAR_PIN_REG 	PINE
#define SONAR_PIN_NUM 	6
#define SONAR_NAME 		"PE6"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}

// External Interrupt 7 service routine
ISR(INT7_vect)//interrupt [EXT_INT7] void ext_int7_isr(void)
{
#define SONAR_NUM 		7
#define SONAR_PIN_REG 	PINE
#define SONAR_PIN_NUM 	7
#define SONAR_NAME 		"PE7"

	SONAR_ROUTINE_HANDLER;

#undef SONAR_NUM
#undef SONAR_PIN_REG
#undef SONAR_PIN_NUM
#undef SONAR_NAME
}


#define VOLTAGE_THRESHOLD 2.30f
void opticalRoutineSend()
{
	for(unsigned char i = 0; i < ADC_INPUT_COUNT; i++)
	{
		unsigned int adcData = analog[i];
		if (adcData < VOLTAGE_THRESHOLD*400)
		{
#ifndef STR_VAL

#else
			mainPort("$ADC");
			mainPort(" ");
			mainPort((int)i+FIRST_ADC_INPUT);
			mainPort(" ");
			mainPort(adcData);
			mainPort("  ");
#endif
		}
	}

}

// Timer1 input capture interrupt service routine
ISR(TIMER1_CAPT_vect)//interrupt [TIM1_CAPT] void timer1_capt_isr(void)
{
	TRIGGER_ON;
	for(unsigned char i = 0; i< SONARS_COUNT; i++)
	{
		flag[i] = false;
		timerLast[i] = 0;
	}
opticalRoutineSend();

#ifdef STR_VAL
	ARDU_LED_TOGGLE;
	mainPort("\r\n");
#endif
}

// Timer1 output compare A interrupt service routine
ISR(TIMER1_COMPA_vect)//interrupt [TIM1_COMPA] void timer1_compa_isr(void)
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
	TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10);
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x3A;
	ICR1L=0x97;
	OCR1AH=0x00;
	OCR1AL=3;//0x03;
	OCR1BH=0x00;
	OCR1BL=0x00;
	OCR1CH=0x00;
	OCR1CL=0x00;

	// Timer/Counter 1 Interrupt(s) initialization
	TIMSK1=(1<<ICIE1) | (0<<OCIE1C) | (0<<OCIE1B) | (1<<OCIE1A) | (0<<TOIE1);
}

void setupExtInt()
{
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
	// PCINT8 interrupt: On
	// PCINT9 interrupt: On
	// PCINT10 interrupt: On
	// PCINT11 interrupt: On
	// PCINT12 interrupt: On
	// PCINT13 interrupt: On
	// PCINT14 interrupt: On
	// PCINT15 interrupt: On
	// PCINT16 interrupt: Off
	// PCINT17 interrupt: Off
	// PCINT18 interrupt: Off
	// PCINT19 interrupt: Off
	// PCINT20 interrupt: Off
	// PCINT21 interrupt: Off
	// PCINT22 interrupt: Off
	// PCINT23 interrupt: Off
	PCMSK0=(1<<PCINT7) | (1<<PCINT6) | (1<<PCINT5) | (1<<PCINT4) | (1<<PCINT3) | (1<<PCINT2) | (1<<PCINT1) | (1<<PCINT0);
	PCMSK1=(1<<PCINT15) | (1<<PCINT14) | (1<<PCINT13) | (1<<PCINT12) | (1<<PCINT11) | (1<<PCINT10) | (1<<PCINT9) | (1<<PCINT8);
	PCMSK2=0;//(0<<PCINT23) | (0<<PCINT22) | (0<<PCINT21) | (0<<PCINT20) | (0<<PCINT19) | (0<<PCINT18) | (0<<PCINT17) | (0<<PCINT16);
	PCICR=(0<<2) | (1<<PCIE1) | (1<<PCIE0);

}

void setupIO()
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
		PORTB=0xFF;//(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

		// Port C initialization
		// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
		DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
		// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
		PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

		// Port D initialization
		// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
		DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
		// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
		PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

		// Port E initialization
		// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
		DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (0<<DDE2) | (0<<DDE1) | (0<<DDE0);
		// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
		PORTE=(1<<PORT7) | (1<<PORT6) | (1<<PORT5) | (1<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

		// Port F initialization
		// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
		DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
		// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
		PORTF=0xff;//(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

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
		PORTJ=0xff;//(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

		// Port K initialization
		// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
		DDRK=(0<<DD7) | (0<<DD6) | (0<<DD5) | (0<<DD4) | (0<<DD3) | (0<<DD2) | (0<<DD1) | (0<<DD0);
		// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
		PORTK=0xff;//(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

		// Port L initialization
		// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
		DDRL=(0<<DD7) | (0<<DD6) | (0<<DD5) | (0<<DD4) | (0<<DD3) | (0<<DD2) | (0<<DD1) | (0<<DD0);
		// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
		PORTL=(0<<PORT7) | (0<<PORT6) | (0<<PORT5) | (0<<PORT4) | (0<<PORT3) | (0<<PORT2) | (0<<PORT1) | (0<<PORT0);

}

int main()
{
	//init();
	setupTimer();
	setupExtInt();
	setupIO();

	ARDU_LED_SETUP;
	TRIGGER_SETUP;

	mainPort("Hello!\r\n");

	while(true)
	{
		_delay_ms(300);

		//ARDU_LED_TOGGLE;

		//sendData(mainPort, "Denjicb", 333);
		//mainPort.print(F("Hell0!\r\n"));
	}
	return 0;
}

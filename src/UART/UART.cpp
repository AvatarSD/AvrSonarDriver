/*
 * UART.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "UART.h"
#include <avr/io.h>
#include <avr/iom2560.h>
#include <util/atomic.h>

void uartInit()
{
	// USART0 initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART0 Receiver: On
	// USART0 Transmitter: On
	// USART0 Mode: Asynchronous
	// USART0 Baud Rate: 115200 (Double Speed Mode)
	UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (1<<U2X0) | (0<<MPCM0);
	UCSR0B=(1<<RXCIE0) | (1<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
	UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
	UBRR0H=0x00;
	UBRR0L=0x10;

	// USART1 initialization
	// USART1 disabled
	UCSR1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (0<<RXEN1) | (0<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);
	/*
	// USART2 initialization
	// USART2 disabled
	UCSR2B=(0<<RXCIE2) | (0<<TXCIE2) | (0<<UDRIE2) | (0<<RXEN2) | (0<<TXEN2) | (0<<UCSZ22) | (0<<RXB82) | (0<<TXB82);

	// USART3 initialization
	// USART3 disabled
	UCSR3B=(0<<RXCIE3) | (0<<TXCIE3) | (0<<UDRIE3) | (0<<RXEN3) | (0<<TXEN3) | (0<<UCSZ32) | (0<<RXB83) | (0<<TXB83);
	 */
}


#define DATA_REGISTER_EMPTY (1<<UDRE0)
#define RX_COMPLETE (1<<RXC0)
#define FRAMING_ERROR (1<<FE0)
#define PARITY_ERROR (1<<UPE0)
#define DATA_OVERRUN (1<<DOR0)

// USART0 Receiver buffer
#define RX_BUFFER_SIZE0 64
char rx_buffer0[RX_BUFFER_SIZE0];

#if RX_BUFFER_SIZE0 <= 256
unsigned char rx_wr_index0=0,rx_rd_index0=0;
#else
unsigned int rx_wr_index0=0,rx_rd_index0=0;
#endif

#if RX_BUFFER_SIZE0 < 256
unsigned char rx_counter0=0;
#else
unsigned int rx_counter0=0;
#endif

// This flag is set on USART0 Receiver buffer overflow
bool rx_buffer_overflow0;

// USART0 Receiver interrupt service routine
ISR(USART0_RX_vect)//interrupt [USART0_RXC] void usart0_rx_isr(void)
{
	char status,data;
	status=UCSR0A;
	data=UDR0;
	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	{
		rx_buffer0[rx_wr_index0++]=data;
#if RX_BUFFER_SIZE0 == 256
		// special case for receiver buffer size=256
		if (++rx_counter0 == 0) rx_buffer_overflow0=1;
#else
		if (rx_wr_index0 == RX_BUFFER_SIZE0) rx_wr_index0=0;
		if (++rx_counter0 == RX_BUFFER_SIZE0)
		{
			rx_counter0=0;
			rx_buffer_overflow0=1;
		}
#endif
	}
}


char getchar(void)
{
	char data;
	while (rx_counter0==0);
	data=rx_buffer0[rx_rd_index0++];
//#if RX_BUFFER_SIZE0 != 256
	if (rx_rd_index0 == RX_BUFFER_SIZE0) rx_rd_index0=0;
//#endif
	cli();
	--rx_counter0;
	sei();
	return data;
}
//#endif

// USART0 Transmitter buffer
#define TX_BUFFER_SIZE0 128
char tx_buffer0[TX_BUFFER_SIZE0];


unsigned int tx_wr_index0=0, tx_rd_index0=0, tx_counter0=0;

// USART0 Transmitter interrupt service routine
ISR(USART0_TX_vect)//interrupt [USART0_TXC] void usart0_tx_isr(void)
{
	if (tx_counter0)
	{
		--tx_counter0;
		UDR0=tx_buffer0[tx_rd_index0++];
#if TX_BUFFER_SIZE0 != 256
		if (tx_rd_index0 == TX_BUFFER_SIZE0) tx_rd_index0=0;
#endif
	}
}


void putchar(char c)
{
	while (tx_counter0 == TX_BUFFER_SIZE0);
	cli();
	if (tx_counter0 || ((UCSR0A & DATA_REGISTER_EMPTY)==0))
	{
		tx_buffer0[tx_wr_index0++]=c;
#if TX_BUFFER_SIZE0 != 256
		if (tx_wr_index0 == TX_BUFFER_SIZE0) tx_wr_index0=0;
#endif
		++tx_counter0;
	}
	else
		UDR0=c;
	sei();
}




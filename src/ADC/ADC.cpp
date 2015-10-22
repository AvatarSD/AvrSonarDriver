/*
 * ADC.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "ADC.h"
#include <avr/io.h>
#include <avr/iom2560.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 15
unsigned int adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
// Voltage Reference: 2.56V, cap. on AREF
#define ADC_VREF_TYPE ((1<<REFS1) | (1<<REFS0) | (0<<ADLAR))

void adcInit()
{

	// ADC initialization
	// ADC Clock frequency: 1000,000 kHz
	// ADC Voltage Reference: 2.56V, cap. on AREF
	// ADC Auto Trigger Source: Free Running
	// Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
	// ADC4: On, ADC5: On, ADC6: On, ADC7: On
	DIDR0=(0<<ADC7D) | (0<<ADC6D) | (0<<ADC5D) | (0<<ADC4D) | (0<<ADC3D) | (0<<ADC2D) | (0<<ADC1D) | (0<<ADC0D);
	// Digital input buffers on ADC8: On, ADC9: On, ADC10: On, ADC11: On
	// ADC12: On, ADC13: On, ADC14: On, ADC15: On
	DIDR2=(0<<ADC15D) | (0<<ADC14D) | (0<<ADC13D) | (0<<ADC12D) | (0<<ADC11D) | (0<<ADC10D) | (0<<ADC9D) | (0<<ADC8D);
	ADMUX=(FIRST_ADC_INPUT & 0x1f) | ADC_VREF_TYPE;
	ADCSRA=(1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (0<<ADIF) | (1<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
	ADCSRB=(((FIRST_ADC_INPUT & 0x20)!=0)<<MUX5) | (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

}

// ADC interrupt service routine
// with auto input scanning
ISR(ADC_vect)//interrupt [ADC_INT] void adc_isr(void)
{
	static unsigned char input_index=0;
	// Read the AD conversion result
	adc_data[input_index]=ADCW;
	// Select next ADC input
	if (++input_index > (LAST_ADC_INPUT-FIRST_ADC_INPUT))
		input_index=0;
	ADMUX=((FIRST_ADC_INPUT+input_index) & 0x1f) | ADC_VREF_TYPE;
	if ((FIRST_ADC_INPUT+input_index) & 0x20) ADCSRB|=(1<<MUX5);
	else ADCSRB&=~(1<<MUX5);
	// Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=(1<<ADSC);
}


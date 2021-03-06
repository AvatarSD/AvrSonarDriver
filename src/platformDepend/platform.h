/*
 * platformDepend.h
 *
 *  Created on: 9 лют. 2016
 *      Author: sd
 */

#ifndef PLATFORMDEPEND_PLATFORMDEPEND_H_
#define PLATFORMDEPEND_PLATFORMDEPEND_H_

#include <avr/io.h>
#include "UART/UART.h"
#include <util/delay.h>
#include <avr/interrupt.h>

/********* Settings ********/
#define UART_PORT 		UDR0
#define UART_SPEED 		115200
#define UART_TX_BUFF 	512
#define UART_RX_BUF 	32
#define UART_RX_INT_VEC USART0_RX_vect
#define UART_TX_INT_VEC USART0_TX_vect
#define MAX_SONAR_COUNT 16 // platform depended(lim for runtime reconfiguring)
#define MAX_ITERATIONS 20  //for eeprom mem buff
#define TIM_MAX 0x3A97 // 0x3A97 - is 60ms period
#define TIM_VAL TCNT1
#define MAP_SIZE MAX_ITERATIONS*MAX_SONAR_COUNT
/***************************/

#define delay_ns(x) _delay_us(x)
#define delay_ms(x) _delay_ms(x)

extern UART mainPort;

void init();
void setupTimer();
void setupExtInt();
void trigOn(uint8_t pin);
void trigOff(uint8_t pin);
void trigOff();
void setSonarCount(uint8_t count);
uint8_t getSonarCount();

void saveSonarCount();
void loadSonarCount();
void saveIterCount(uint8_t count);
uint8_t loadIterCount();
void saveMapEeprom(const bool * map);
void loadMapEeprom(bool * map);


#endif /* PLATFORMDEPEND_PLATFORMDEPEND_H_ */

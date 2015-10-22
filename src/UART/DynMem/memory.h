/*
 * memory.h
 *
 *  Created on: 23 жовт. 2015 р.
 *      Author: sd
 */

#ifndef UART_DYNMEM_MEMORY_H_
#define UART_DYNMEM_MEMORY_H_

#include "stdlib.h"

void * operator new(size_t size);
void operator delete(void * ptr);


#endif /* UART_DYNMEM_MEMORY_H_ */

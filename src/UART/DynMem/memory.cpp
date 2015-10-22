/*
 * memory.cpp
 *
 *  Created on: 23 жовт. 2015 р.
 *      Author: sd
 */

#include "memory.h"


void * operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void * ptr)
{
	free(ptr);
}




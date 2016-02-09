/*
 * main.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "platformDepend/platform.h"

#define SONAR_COUNT 	2 // just for init

int main()
{
	init();
	setSonarCount(SONAR_COUNT);
	setupTimer();
	setupExtInt();


	while (true)
		;

	return 0;
}

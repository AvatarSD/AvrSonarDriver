/*
 * main.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "map/timingmap.h"

#define SONAR_COUNT 	2 // just for init

int main()
{
	init();
	//setSonarCount(SONAR_COUNT);
	setupTimer();
	setupExtInt();

	bool timingMap[8*16] =
	{
	1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	writeMap(timingMap, 8, 16);


	while (true)
		;

	return 0;
}

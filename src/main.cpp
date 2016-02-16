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

	bool timingMap[3*2] =
	{
	 1, 1 ,
	 0, 1 ,
	 1, 0 };

	writeMap(timingMap, 3, 2);


	while (true)
		;

	return 0;
}

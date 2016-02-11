/*
 * timingmap.cpp
 *
 *  Created on: 11 лют. 2016
 *      Author: sd
 */

#include "timingmap.h"
#include "string.h"
#include "../platformDepend/platform.h"


bool timingMap[MAX_ITERATIONS][MAX_SONAR_COUNT];
//=
//{
//{ 1, 0 },
//{ 0, 1 },
//{ 1, 1 } };

uint8_t iterationCount = 0;

bool writeMap(bool ** map, uint8_t iterations, uint8_t sonars)
{
	if(!((iterations < MAX_ITERATIONS)||(sonars < MAX_SONAR_COUNT)))
		return false;
//	uint16_t size = iterations * sonars;
//	size = size/8 + size%8;
	memcpy(timingMap, map, sizeof(timingMap));
	iterationCount = iterations;
	setSonarCount(sonars);
	return true;
}

void loadMap()
{

}

void saveMap()
{

}

//const bool ** getMap()
//{
//	return timingMap;
//}

uint8_t getIterationCount()
{
	return iterationCount;
}

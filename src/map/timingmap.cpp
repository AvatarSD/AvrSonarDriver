/*
 * timingmap.cpp
 *
 *  Created on: 11 лют. 2016
 *      Author: sd
 */

#include "timingmap.h"
#include "string.h"
#include "../platformDepend/platform.h"

bool timingMap[MAP_SIZE];
uint8_t iterationCount = 0;

bool getMapPosition(uint8_t iteration, uint8_t sonarNum)
{
	if ((iteration < getIterationCount()) && (iteration < MAX_ITERATIONS)
			&& (sonarNum < getSonarCount()) && (sonarNum < MAX_SONAR_COUNT))
		return timingMap[iteration * MAX_SONAR_COUNT + sonarNum];

	return 0;
}

bool writeMap(const bool * map, uint8_t iterations, uint8_t sonars)
{
	if ((iterations > MAX_ITERATIONS) || (sonars > MAX_SONAR_COUNT))
		return false;
	for (uint8_t i = 0; i < iterations; i++)
		for (uint8_t s = 0; s < sonars; s++)
			timingMap[i * MAX_SONAR_COUNT + s] = map[i * sonars + s];
	iterationCount = iterations;
	setSonarCount(sonars);
	return true;
}

void loadMap()
{
	loadMapEeprom(timingMap);
}

void saveMap()
{
	saveMapEeprom(timingMap);
}

//const bool * getMap()
//{
//	return timingMap;
//}

uint8_t getIterationCount()
{
	return iterationCount;
}

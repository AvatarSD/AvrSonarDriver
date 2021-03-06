/*
 * timingmap.h
 *
 *  Created on: 11 лют. 2016
 *      Author: sd
 */

#ifndef MAP_TIMINGMAP_H_
#define MAP_TIMINGMAP_H_

#include <inttypes.h>
#include "../platformDepend/platform.h"

bool getMapPosition(uint8_t iteration, uint8_t sonarNum);
bool writeMap(const bool * map, uint8_t iterations, uint8_t sonars);
//const bool * getMap();
void loadMap();
void saveMap();
uint8_t getIterationCount();
void setIterationCount(uint8_t iterations);

#endif /* MAP_TIMINGMAP_H_ */

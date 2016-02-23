/*
 * main.cpp
 *
 *  Created on: 21 жовт. 2015
 *      Author: sd
 */

#include "map/timingmap.h"

int main()
{
	init();
	loadMap();
	setupExtInt();
	setupTimer();


//	bool timingMap[8*16] =
//	{
//	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
//	0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1,
//	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
//	0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0,
//	0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1,
//	0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1,
//	0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1,
//	0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0,
//	};
//
//	writeMap(timingMap, 8, 16);
//
//	saveMap();


//	for(uint8_t i = 0; i < 8; i++)
//	{
//		for(uint8_t s = 0; s < 16; s++)
//		{
//			mainPort(getMapPosition(i,s)); //timingMap[i*16+s]);
//			mainPort(", ");
//		}
//		mainPort("\r\n");
//	}
//	uint32_t t =0;
//	while(1)
//	{
//	mainPort("okk ");
//	mainPort(t++);
//	mainPort("\r\n");
//	}


	while (true)
		;

	return 0;
}

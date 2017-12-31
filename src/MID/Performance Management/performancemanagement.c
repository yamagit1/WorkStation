/*
 * performancemanagement.c
 *
 *  Created on: Dec 18, 2017
 *      Author: yama
 */

#include "performancemanagement.h"

TaskHandle_t gPIDTask[MAX_NUMBER_PID];

__S_TIME gTimeCount;

void PM_updateTimeCount()
{
	if (gTimeCount.section < 59)
	{
		gTimeCount.section++;
	}
	else if (gTimeCount.miuter < 59)
	{
		gTimeCount.section = 0;
		gTimeCount.miuter++;
	}
	else if (gTimeCount.hour <24)
	{
		gTimeCount.section = 0;
		gTimeCount.miuter = 0;
		gTimeCount.hour++;
	}
	else
	{
		gTimeCount.section = 0;
		gTimeCount.miuter = 0;
		gTimeCount.hour = 0;
	}
}

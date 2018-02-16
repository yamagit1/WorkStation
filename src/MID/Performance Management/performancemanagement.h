/*
 * performance management.h
 *
 *  Created on: Dec 18, 2017
 *      Author: yama
 */

#ifndef __PERFORMANCEMANAGEMENT_H__
#define __PERFORMANCEMANAGEMENT_H__

#include "header.h"
#include "task.h"


#define MAX_NUMBER_PID		20

extern TaskHandle_t gPIDTask[MAX_NUMBER_PID];

typedef struct
{
	__uint32 miliSection;
	__uint32 section;
	__uint32 miuter;
	__uint32 hour;
}__S_TIME;

extern __S_TIME gTimeCount;

void PM_updateTimeCount();


#endif /* __PERFORMANCEMANAGEMENT_H__ */

/*
 * ConsoleLog.h
 *
 *  Created on: Feb 14, 2018
 *      Author: yama
 */

#ifndef __CONSOLELOG_H_
#define __CONSOLELOG_H_

#include "header.h"
#include "Trace.h"

#define MAX_STRLEN 12 // this is the maximum string length of our string in characters

void Console_log_init();
void Console_Trace(volatile char *s);
void Console_Print(const char* format, ...);
void Console_Log_Print(const char* format, ...);
void Console_Log(const char* format, ...);
void Console_put_char(const char *ch);

#endif /* __CONSOLELOG_H_ */

/*
 * ConsoleLog.c
 *
 *  Created on: Feb 14, 2018
 *      Author: yama
 */

#include "ConsoleLog.h"
#include "Trace.h"
#include <stdio.h>
#include <stdarg.h>


#if OS_BUILD == OS_LIN64_UBUNTU_16_4 && BUILD_TARGET == BUILD_TARGET_DEBUG

void Console_Log_Print(const char* format, ...)
{
	va_list vaArgs;
	char buf[BUFF_SIZE_LOW];

	va_start (vaArgs, format);
	// Print to the local buffer
	vsnprintf (buf, sizeof(buf), format, vaArgs);

	va_end (vaArgs);

	trace_printf("[___LOG___]: %s .", buf);
	trace_printf("\n");
}

#else

void Console_Log_Print(const char* format, ...)
{

}

#endif

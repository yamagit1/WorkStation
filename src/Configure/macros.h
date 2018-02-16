/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

/*==================================================================
 * In this file:
 * 		- define some macro usually use
 * 		- define macro print log to LCD
 *==================================================================*/

#ifndef __MACROS_H__
#define __MACROS_H__

#include <header.h>
#include "ConsoleLog.h"

#if BUILD_TARGET == BUILD_TARGET_DEBUG

#define PRINT_LOG(tofile, lvLog, content) do{} while(0)

#define __ENTER__	do{	trace_printf("[__ENTER__]: %s() ||  %5d || %s .", __FUNCTION__, __LINE__, __FILE__);				\
						trace_printf("\n");																			\
					}while(0);

#define __LEAVE__	do{	trace_printf("[__LEAVE__]: %s() ||  %5d || %s .", __FUNCTION__, __LINE__, __FILE__);				\
						trace_printf("\n");																			\
					}while(0);

#else

#define __ENTER__			do{}while(0);
#define __LEAVE__			do{}while(0);

#endif

#endif

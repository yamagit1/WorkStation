/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

/*==============================================================================
 * In this file:
 * 		- define device can use
 * 		- typedef basic data
 * 		- include library
 *============================================================================*/

#ifndef __HEADER_H__
#define __HEADER_H__

/*==============================================================================
 * id for flatfrom:  x yyyy zzz
 * 					 ^ ^^^^ ^^^
 * 					 a 	b	 c
 * 	- a: company
 * 		 1-ARM  2-ATMEGA ...
 * 	- b: seri
 * 	- c: reserver (ex: version)
 *
 *============================================================================*/

#define FLATFORM_STM32_F407VG 	10407000
#define FLATFORM_ATMEGA_ARDUNO	20000000

/*==============================================================================
 * enviement build:  xx yy zzzzz
 * 					 ^^ ^^ ^^^^
 * 					 a 	 b 	 c
 * 	- a: company
 * 		 1-windows  2-Linix ...
 * 	- b: seri : 32/64 bit
 * 	- c: reserver (ex: ubuntu, red hat, win7, winxp, ...)
 *
 *============================================================================*/

#define OS_WIN32_7					10320070
#define OS_WIN64_7					10640070

#define	OS_LIN32_UBUNTU_16_4		20321016
#define OS_LIN64_UBUNTU_16_4		20641016

/*==============================================================================
 * LCD view:  x y zzzzzz
 * 			  ^ ^ ^^^^
 * 			  a b  c
 * 	- a: type
 * 		 1-mono  2-color ...
 * 	- b: type
 * 		1- small	2- medium	3- larger 4- QHD 5- HD,...
 * 	- c: ID
 *
 *============================================================================*/

#define MONITOR_LCD_1202			11001202


/*==============================================================================
 * build target
 *============================================================================*/

#define BUILD_TARGET_RELEASE		10000000
#define BUILD_TARGET_DEBUG			20000000


#include<config.h>

/*==============================================================================
 * typedef basic type data
 *============================================================================*/

#if CONFIG_FLATFORM == FLATFORM_STM32_F407VG

typedef		signed		char		__INT8;
typedef		unsigned	char		__UINT8;
typedef		signed		short		__INT16;
typedef		unsigned 	short		__UINT16;
typedef		signed		int			__INT32;
typedef 	unsigned	int			__UINT32;
typedef		signed		long long	__INT64;
typedef		unsigned  	long long	__UINT64;

#endif

typedef enum
{
	eFALSE = 0,
	eTRUE  = !eFALSE
}__E_Bollen;

#define TRUE			1
#define FALSE			0
/*==============================================================================
 * include library
 *============================================================================*/

#include "FreeRTOS.h"

#if CONFIG_FLATFORM == FLATFORM_STM32_F407VG
#include"string.h"
#include"stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_spi.h"
//#include "stm32f4xx_syscfg.h"
//#include "stm32f4xx_can.h"
//#include "stm32f4xx_crc.h"
//#include "stm32f4xx_cryp.h"
//#include "stm32f4xx_dac.h"
//#include "stm32f4xx_dbgmcu.h"
//#include "stm32f4xx_dcmi.h"
//#include "stm32f4xx_dma.h"
//#include "stm32f4xx_exti.h"
//#include "stm32f4xx_flash.h"
//#include "stm32f4xx_fsmc.h"
//#include "stm32f4xx_hash.h"
//#include "stm32f4xx_i2c.h"
//#include "stm32f4xx_iwdg.h"
//#include "stm32f4xx_pwr.h"
//#include "stm32f4xx_rng.h"
//#include "stm32f4xx_rtc.h"
//#include "stm32f4xx_sdio.h"
//#include "stm32f4xx_usart.h"
//#include "stm32f4xx_wwdg.h"
//#include "misc.h"
#endif

#include<macros.h>

#endif

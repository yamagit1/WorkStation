/*
 * FreeRTOSConfig.h
 *
 *  Created on: Dec 15, 2017
 *      Author: yama
 */

#ifndef __FREERTOS_CONFIG_H__
#define __FREERTOS_CONFIG_H__

#include <header.h>

#if CONFIG_FLATFORM == FLATFORM_STM32_F407VG
	#include"FreeRTOSConfig_stm32f4xx.h"
#endif

#endif /* SRC_OS_FREERTOS_KERNEL_FREERTOSCONFIG_H_ */

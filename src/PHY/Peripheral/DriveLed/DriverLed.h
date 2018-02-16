/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/


#ifndef __DRIVER_LED_H__
#define __DRIVER_LED_H__

#include "header.h"

/*==============================================================================
 *	Led is use
 *============================================================================*/
#define LED_RED							0
#define LED_BLUE						1
#define LED_YELLOW						2
#define LED_GREEN						3

/*==============================================================================
 *	config with device stm32f407
 *============================================================================*/


#if CONFIG_FLATFORM == FLATFORM_STM32_F407VG

#define	PIN_LED_RED						GPIO_Pin_12
#define	PIN_LED_BLUE					GPIO_Pin_13
#define	PIN_LED_YELLOW					GPIO_Pin_14
#define	PIN_LED_GREEN					GPIO_Pin_15

#define COM_LED_RED						GPIOD
#define COM_LED_BLUE					GPIOD
#define COM_LED_YELLOW					GPIOD
#define COM_LED_GREEN					GPIOD

#define RCC_LED_RED						RCC_AHB1Periph_GPIOD
#define RCC_LED_BLUE					RCC_AHB1Periph_GPIOD
#define RCC_LED_YELLOW					RCC_AHB1Periph_GPIOD
#define RCC_LED_GREEN					RCC_AHB1Periph_GPIOD


#endif

extern __E_Bollen gLedStatus[4];

/*==============================================================================
 *	function
 *============================================================================*/

void DL_initialize();
void DL_turnOnLedRed(__uint32 led);
void DL_turnOffLedRed(__uint32 led);

#endif /* SRC_PHY_PERIPHERAL_DRIVELED_DRIVERLED_H_ */

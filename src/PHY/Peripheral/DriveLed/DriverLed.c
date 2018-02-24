/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#include "DriverLed.h"

__E_Bollen gLedStatus[4];

void DL_initialize()
{
//	__ENTER__

	GPIO_InitTypeDef ledConfigure;

	ledConfigure.GPIO_Mode  =  GPIO_Mode_OUT;
	ledConfigure.GPIO_OType =  GPIO_OType_PP;
	ledConfigure.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	ledConfigure.GPIO_Speed	=	GPIO_Speed_100MHz;

	//
	ledConfigure.GPIO_Pin = PIN_LED_RED;

	RCC_AHB1PeriphClockCmd(RCC_LED_RED, ENABLE);
	GPIO_Init(COM_LED_RED, &ledConfigure);

	//
	ledConfigure.GPIO_Pin = PIN_LED_BLUE;

	RCC_AHB1PeriphClockCmd(RCC_LED_BLUE, ENABLE);
	GPIO_Init(COM_LED_BLUE, &ledConfigure);

	//
	ledConfigure.GPIO_Pin = PIN_LED_YELLOW;

	RCC_AHB1PeriphClockCmd(RCC_LED_YELLOW, ENABLE);
	GPIO_Init(COM_LED_YELLOW, &ledConfigure);

	//
	ledConfigure.GPIO_Pin = PIN_LED_GREEN;

	RCC_AHB1PeriphClockCmd(RCC_LED_GREEN, ENABLE);
	GPIO_Init(COM_LED_GREEN, &ledConfigure);

//	__LEAVE__
}

/**
 *
 */

void DL_turnOffLedRed(__uint32 led)
{
	switch(led)
	{
	case LED_RED:
			GPIO_ResetBits(COM_LED_RED, PIN_LED_RED);
			gLedStatus[LED_RED] = eFALSE;
		break;

	case LED_BLUE:
		GPIO_ResetBits(COM_LED_BLUE, PIN_LED_BLUE);
		gLedStatus[LED_BLUE] = eFALSE;
		break;

	case LED_YELLOW:
		GPIO_ResetBits(COM_LED_YELLOW, PIN_LED_YELLOW);
		gLedStatus[LED_YELLOW] = eFALSE;
		break;

	case LED_GREEN:
		GPIO_ResetBits(COM_LED_GREEN, PIN_LED_GREEN);
		gLedStatus[LED_GREEN] = eFALSE;
		break;

	default:
		break;
	}

}

/**
 *
 */

void DL_turnOnLedRed(__uint32 led)
{
	switch(led)
	{
	case LED_RED:
			GPIO_SetBits(COM_LED_RED, PIN_LED_RED);
			gLedStatus[LED_RED] = eTRUE;
		break;

	case LED_BLUE:
		GPIO_SetBits(COM_LED_BLUE, PIN_LED_BLUE);
		gLedStatus[LED_BLUE] = eTRUE;
		break;

	case LED_YELLOW:
		GPIO_SetBits(COM_LED_YELLOW, PIN_LED_YELLOW);
		gLedStatus[LED_YELLOW] = eTRUE;
		break;

	case LED_GREEN:
		GPIO_SetBits(COM_LED_GREEN, PIN_LED_GREEN);
		gLedStatus[LED_GREEN] = eTRUE;
		break;

	default:
		break;
	}
}

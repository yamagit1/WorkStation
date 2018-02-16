/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#include "configmanagement.h"
#include "monitor.h"
#include "lcd1202.h"
#include "task.h"
#include "temperature.h"
#include "DriverLed.h"
#include "performancemanagement.h"

void CM_taskMonitorHandler(void *p_parameters)
{
	for(;;)
	{
		MNT_update();

		MNT_Render();

		vTaskDelay(pdMS_TO_TICKS(12));
	}

	vTaskDelete(NULL);
}

void CM_taksTime(void *p_parameters)
{
	for(;;)
	{
		PM_updateTimeCount();

		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	vTaskDelete(NULL);
}

void CM_taskCountTime(void *p_parameters)
{
	__int32 count = 0;
	__uint32 placeNumCount 	= LCD_1202_ADDRESS_LINE_TEXT_1;

	for (;;)
	{
		count++;
		LCD1202_printNumberInterger(count, &placeNumCount);
		placeNumCount = LCD_1202_ADDRESS_LINE_TEXT_1;

		vTaskDelay(pdMS_TO_TICKS(125));
	}

	vTaskDelete(NULL);
}

void CM_taskUpdateTemperature(void *p_parameters)
{
	for (;;)
	{
		TEM_updateTemperature();

		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	vTaskDelete(NULL);
}

void CM_taskBinlkLed()
{
	__int32 i = 0;

	for (;;)
	{
		switch(i)
		{
		case 0:
			DL_turnOnLedRed(LED_RED);
			DL_turnOffLedRed(LED_GREEN);
			break;

		case 1:
			DL_turnOnLedRed(LED_BLUE);
			DL_turnOffLedRed(LED_RED);
			break;

		case 2:
			DL_turnOnLedRed(LED_YELLOW);
			DL_turnOffLedRed(LED_BLUE);
			break;

		case 3:
			DL_turnOnLedRed(LED_GREEN);
			DL_turnOffLedRed(LED_YELLOW);
			break;

		default:
			i = 0;
			break;
		}

		i++;

		if (i > 3)
		{
			i = 0;
		}

		vTaskDelay(pdMS_TO_TICKS(120));
	}

	vTaskDelete(NULL);
}

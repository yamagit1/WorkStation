#include "network.h"
#include "stm32f4_html.h"
#include "performancemanagement.h"
#include "DriverLed.h"
#include "task.h"
#include "temperature.h"

extern unsigned long _sdata;
extern unsigned long _flash_s;

void HTML_prepare_web()
{
	char statusLedRed[5], statusLedBlue[5],statusLedYellow[5],statusLedGreen[5];
	char pro1[125], pro2[125], pro3[125], pro4[125], pro5[125];
	__uint64 flashUse = 0;

	if (gLedStatus[LED_RED])
		{
			sprintf(statusLedRed,"ON");
		}
		else
		{
			sprintf(statusLedRed,"OFF");
		}

	if (gLedStatus[LED_BLUE])
		{
			sprintf(statusLedBlue,"ON");
		}
		else
		{
			sprintf(statusLedBlue,"OFF");
		}

	if (gLedStatus[LED_YELLOW])
		{
			sprintf(statusLedYellow,"ON");
		}
		else
		{
			sprintf(statusLedYellow,"OFF");
		}

	if (gLedStatus[LED_GREEN])
		{
			sprintf(statusLedGreen,"ON");
		}
		else
		{
			sprintf(statusLedGreen,"OFF");
		}

	sprintf(pro1,"<tr><td>%5d</td><td>%s</td><td>RUNNING</td></tr>",(__uint32)gPIDTask[0], pcTaskGetName(gPIDTask[0]));
	sprintf(pro2,"<tr><td>%5d</td><td>%s</td><td>RUNNING</td></tr>",(__uint32)gPIDTask[1], pcTaskGetName(gPIDTask[1]));
	sprintf(pro3,"<tr><td>%5d</td><td>%s</td><td>RUNNING</td></tr>",(__uint32)gPIDTask[2], pcTaskGetName(gPIDTask[2]));
	sprintf(pro4,"<tr><td>%5d</td><td>%s</td><td>RUNNING</td></tr>",(__uint32)gPIDTask[3], pcTaskGetName(gPIDTask[3]));
	sprintf(pro5,"<tr><td>%5d</td><td>%s</td><td>RUNNING</td></tr></table>",(__uint32)gPIDTask[4], pcTaskGetName(gPIDTask[4]));
//	memcpy(gBufferWebsite,stm32f4_html, strlen(stm32f4_html));

//	flashUse = _flash_s - _sdata;

	sprintf((char*)gBufferWebsite,stm32f4_html,statusLedRed,statusLedBlue,statusLedYellow,statusLedGreen, pro1, pro2, pro3, pro4, pro5, gCurrentTemperatureC, gCurrentTemperatureF);
//	Console_Print(gBufferWebsite);
}

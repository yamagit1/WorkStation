
#include"header.h"
#include"lcd1202.h"
#include "lcd_logo.h"
#include "lcd_font.h"
#include "DriverLed.h"
#include "enc208j60.h"
#include "monitor.h"
#include "temperature.h"
#include "configmanagement.h"
#include "performancemanagement.h"

#include "task.h"

int main( void )
{
	SystemInit();
	DL_initialize();
	ENC28J60_initialize();
	MNT_initialize();
	TEM_initialize();

	LCD1202_viewImageBitmap(gLogo);
	LCD1202_delay(1680000);

	xTaskCreate(CM_taskBinlkLed, "DL", 1000, NULL, 2, &gPIDTask[0]);
	xTaskCreate(CM_taskMonitorHandler, "MN", 1000, NULL, 2, &gPIDTask[1]);

	xTaskCreate(CM_taskUpdateTemperature, "TP", 1000, NULL, 2, &gPIDTask[2]);
	xTaskCreate(CM_taksTime, "TI", 1000, NULL, 3, &gPIDTask[3]);


	vTaskStartScheduler();


	return 0;
}

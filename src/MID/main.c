
#include <enc28j60.h>
#include"header.h"
#include"lcd1202.h"
#include "lcd_logo.h"
#include "lcd_font.h"
#include "DriverLed.h"
#include "monitor.h"
#include "temperature.h"
#include "configmanagement.h"
#include "performancemanagement.h"

#include "task.h"

int main( void )
{
	SystemInit();
	MNT_initialize();
	LCD1202_clearScreen();
	DL_initialize();
	TEM_initialize();

	LCD1202_viewImageBitmap(gLogo);
	LCD1202_delay(16800);

	//	xTaskCreate(CM_taskBinlkLed, "DL", 1000, NULL, 2, &gPIDTask[0]);
	//	xTaskCreate(CM_taskMonitorHandler, "MN", 1000, NULL, 2, &gPIDTask[1]);
	//
	//	xTaskCreate(CM_taskUpdateTemperature, "TP", 1000, NULL, 2, &gPIDTask[2]);
	//	xTaskCreate(CM_taksTime, "TI", 1000, NULL, 3, &gPIDTask[3]);
	//
	//
	//	vTaskStartScheduler();


	//	ENC28J60_writeBuffer(1 , &dataSend);
	//
	//	ENC28J60_readBuffer(1, &dataRecive);
	ENC28J60_SPI1_Configuration();
	ENC28J60_GPIO_Configuration();

	enc28j60Init(NULL);

//	LCD1202_clearScreen();
	LCD1202_flush();

	__UINT8 data = 55;
	__UINT8  dataReceive = 11;

	for(;;)
	{
		LCD1202_clearScreen();
		dataReceive = enc28j60Read(ECON1);

		LCD1202_printText("data receiver :", &gLcd1202CurrentOffset);
		LCD1202_printNumberInterger(dataReceive, &gLcd1202CurrentOffset);
		LCD1202_endLine();

		LCD1202_flush();
		LCD1202_delay(16800000);
	}


	return 0;
}

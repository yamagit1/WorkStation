
#include "main.h"
__uint8 macaddr[]={0x01,0x02,0x03,0x04,0x05,0x06};

__uint8 macdestaddr[]={0x8c, 0x70, 0x5a, 0xb5, 0xbc, 0x2c};

__uint8 data[]={32, 33, 34, 35, 36, 37};
//extern uint8_t ipaddr[4];



int main( void )
{
	Console_log_init(115200);
	Console_Log_Print("***************************************************************");
	Console_Log_Print("*     ****   ****       ****       ****    ****  **********    *");
	Console_Log_Print("*     ****   ****      ******      ****    ****  **********    *");
	Console_Log_Print("*     ****   ****     ********     ****    ****     ****       *");
	Console_Log_Print("*     ***********    ****  ****    ****    ****     ****       *");
	Console_Log_Print("*     ***********   ************   ****    ****     ****       *");
	Console_Log_Print("*     ***********  **************  ****    ****     ****       *");
	Console_Log_Print("*     ****   ****  *****    *****  ************     ****       *");
	Console_Log_Print("*     ****   ****  *****    *****  ************  **********    *");
	Console_Log_Print("*     ****   ****  *****    *****    **********  **********    *");
	Console_Log_Print("****************************************************************");

	__ENTER__

	Console_Log_Print("Initialize driver LED ");
	DL_initialize();

	Console_Log_Print("Initialize network");
//	enc28j60_init(macaddr);
	Console_Log_Print("Initialize monitor");
	MNT_initialize();

	Console_Log_Print("Initialize Temperature");
	TEM_initialize();

	Console_Log_Print("***************************************************************");
//	Console_Log_Print("%d",_flash_s - _sdata );
	Console_Log_Print("***************************************************************");

	//
	xTaskCreate(CM_taskBinlkLed, "BinlkLed", 1000, NULL, 2, &gPIDTask[0]);
	xTaskCreate(CM_taskMonitorHandler, "MonitorHandler", 1000, NULL, 2, &gPIDTask[1]);
	xTaskCreate(CM_taskNetwork, "network", 3000, NULL, 2, &gPIDTask[2]);
	xTaskCreate(CM_taskUpdateTemperature, "UpdateTemperature", 1000, NULL, 2, &gPIDTask[3]);
	xTaskCreate(CM_taksTime, "Timer", 1000, NULL, 3, &gPIDTask[4]);

	vTaskStartScheduler();

	while(1);
}
//
//////0978431875
//

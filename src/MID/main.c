
#include "main.h"
#include "stm32f4_html.h"
__uint8 macaddr[]={0x01,0x02,0x03,0x04,0x05,0x06};

__uint8 macdestaddr[]={0x8c, 0x70, 0x5a, 0xb5, 0xbc, 0x2c};

__uint8 data[]={32, 33, 34, 35, 36, 37};
//extern uint8_t ipaddr[4];



int main( void )
{
	console_serial_init(115200);
	console_serial_print_log("***************************************************************");
	console_serial_print_log("*     ****   ****       ****       ****    ****  **********    *");
	console_serial_print_log("*     ****   ****      ******      ****    ****  **********    *");
	console_serial_print_log("*     ****   ****     ********     ****    ****     ****       *");
	console_serial_print_log("*     ***********    ****  ****    ****    ****     ****       *");
	console_serial_print_log("*     ***********   ************   ****    ****     ****       *");
	console_serial_print_log("*     ***********  **************  ****    ****     ****       *");
	console_serial_print_log("*     ****   ****  *****    *****  ************     ****       *");
	console_serial_print_log("*     ****   ****  *****    *****  ************  **********    *");
	console_serial_print_log("*     ****   ****  *****    *****    **********  **********    *");
	console_serial_print_log("****************************************************************");

	__ENTER__

	console_serial_print_log("Initialize driver LED ");
	DL_initialize();

	console_serial_print_log("Initialize network");
//	enc28j60_init(macaddr);
	net_ini();
	console_serial_print_log("Initialize monitor");
	MNT_initialize();

	console_serial_print_log("Initialize Temperature");
	TEM_initialize();

	console_serial_print_log("***************************************************************");
//	console_serial_print_log("%d",_flash_s - _sdata );
	console_serial_print_log("***************************************************************");

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

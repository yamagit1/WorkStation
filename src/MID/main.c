
#include"header.h"
#include "DriverLed.h"
#include "ConsoleLog.h"
#include "enc28j60.h"
#include "lcd1202.h"
#include "net.h"

__uint8 arp_pkt[] = {
		0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0x74 ,0xe6 ,0xe2 ,0x07 ,0x43 ,0xfd ,0x08 ,0x06 ,0x00 ,0x01,
		0x08 ,0x00 ,0x06 ,0x04 ,0x00 ,0x01 ,0x74 ,0xe6 ,0xe2 ,0x07 ,0x43 ,0xfd ,0xc0 ,0xa8 ,0x1 ,0xc5,
		0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xc0 ,0xa8 ,0x01 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
		0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00
};


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
	net_ini();

	__uint32 i = 0;
	for(;;)
	{
		net_poll();
	}

	/// =============
	//	__uint32 position;
	//	SystemInit();
	//	LCD1202_initialize();
	//	DL_initialize();
	//	while(1)
	//	{
	//		position = LCD_1202_ADDRESS_LINE_TEXT_1;
	//		LCD1202_printText("Hello", &position);;
	//		LCD1202_flush();
	//		LCD1202_delay(56800000);
	//		DL_turnOnLedRed(LED_RED);
	//				DL_turnOnLedRed(LED_BLUE);
	//				DL_turnOnLedRed(LED_YELLOW);
	//				DL_turnOnLedRed(LED_GREEN);
	//
	//				LCD1202_delay(16800000);
	//
	//				DL_turnOffLedRed(LED_RED);
	//				DL_turnOffLedRed(LED_BLUE);
	//				DL_turnOffLedRed(LED_YELLOW);
	//				DL_turnOffLedRed(LED_GREEN);
	//
	//				LCD1202_delay(16800000);
	//	}
	//	return 0;
}
//
//////0978431875
//

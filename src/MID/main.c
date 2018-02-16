
#include"header.h"
#include "DriverLed.h"
#include "ConsoleLog.h"
#include "enc28j60.h"
#include "lcd1202.h"

int main( void )
{
	__ENTER__

	__uint8 macaddr[]={0x01,0x02,0x03,0x04,0x05,0x06};
	Console_Log_Print("Initialize system with configure clock source,use HSE ");
	SystemInit();

	Console_Log_Print("Initialize driver LED ");
	DL_initialize();

	Console_Log_Print("Initialize module enc28j60 with mac address : %d", macaddr);
	enc28j60_init(macaddr);

	__uint32 index = 0;

	__uint32 dataReciver = 0;
	enc28j60_write_phy(PHLCON, 0x3AB0);
	for(;;)
	{
		index ++;

		Console_Log_Print("session blink led %d", index);

		DL_turnOnLedRed(LED_RED);
		DL_turnOnLedRed(LED_BLUE);
		DL_turnOnLedRed(LED_YELLOW);
		DL_turnOnLedRed(LED_GREEN);

		LCD1202_delay(16800000);

		DL_turnOffLedRed(LED_RED);
		DL_turnOffLedRed(LED_BLUE);
		DL_turnOffLedRed(LED_YELLOW);
		DL_turnOffLedRed(LED_GREEN);

		LCD1202_delay(16800000);
		dataReciver = enc28j60_rcr16(ERDPTL);
		Console_Log_Print("data reciver is %d", dataReciver);

	}


	return 0;
}

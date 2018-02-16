
#include "monitor.h"
#include "lcd1202.h"
#include "temperature.h"
#include "lcd_font.h"
#include "performancemanagement.h"
#include "DriverLed.h"

void MNT_initialize(void)
{
	LCD1202_initialize();
	MNT_printBorder();
}

void MNT_printBorder(void)
{
	__uint32 position = 0;

	// line text 0
	position = LCD_1202_ADDRESS_LINE_TEXT_0;
	LCD1202_printText("-PID-|--SYS INFOR--", &position);

	// line text 1
	position = LCD_1202_ADDRESS_LINE_TEXT_1;
	LCD1202_printText("     |TIME|        ", &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_1;
	LCD1202_printNumberInterger((__int64)((__int16)gPIDTask[0]), &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_1 + gCurrentFont.charWidth * 11;
	LCD1202_printNumberInterger((__int64)gTimeCount.hour, &position);
	LCD1202_printText(":", &position);
	LCD1202_printNumberInterger((__int64)gTimeCount.miuter, &position);
	LCD1202_printText(":", &position);
	LCD1202_printNumberInterger((__int64)gTimeCount.section, &position);

	//line text 2
	position = LCD_1202_ADDRESS_LINE_TEXT_2;
	LCD1202_printText("     | *C |        ", &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_2;
	LCD1202_printNumberInterger((__int64)((__int16)gPIDTask[1]), &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_2 + gCurrentFont.charWidth * 12;
	LCD1202_printNumberInterger((__int64)gCurrentTemperatureC, &position);
	LCD1202_printText("*C", &position);

	// line text 3
	position = LCD_1202_ADDRESS_LINE_TEXT_3;
	LCD1202_printText("     | *F |        ", &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_3;
	LCD1202_printNumberInterger((__int64)((__int16)gPIDTask[2]), &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_3 + gCurrentFont.charWidth * 12;
	LCD1202_printNumberInterger((__int64)gCurrentTemperatureF, &position);
	LCD1202_printText("*F", &position);

	// line text 4
	position = LCD_1202_ADDRESS_LINE_TEXT_4;
	LCD1202_printText("     |LedR|   |    ", &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_4;
	LCD1202_printNumberInterger((__int64)((__int16)gPIDTask[3]), &position);



	if (gLedStatus[LED_RED] == eTRUE)
	{
		position = LCD_1202_ADDRESS_LINE_TEXT_4 + gCurrentFont.charWidth * 12;

		LCD1202_printText("ON", &position);
	}
	else
	{
		position = LCD_1202_ADDRESS_LINE_TEXT_4 + gCurrentFont.charWidth * 16;

		LCD1202_printText("OFF", &position);
	}

	//	//
	position = LCD_1202_ADDRESS_LINE_TEXT_5;
	LCD1202_printText("     |LedG|   |    ", &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_5;
	LCD1202_printNumberInterger((__int64)((__int16)gPIDTask[4]), &position);

	if (gLedStatus[LED_GREEN] == eTRUE)
	{
		position = LCD_1202_ADDRESS_LINE_TEXT_5 + gCurrentFont.charWidth * 12;
		LCD1202_printText("ON", &position);
	}
	else
	{
		position = LCD_1202_ADDRESS_LINE_TEXT_5 + gCurrentFont.charWidth * 16;
		LCD1202_printText("OFF", &position);
	}

	//
	position = LCD_1202_ADDRESS_LINE_TEXT_6;
	LCD1202_printText("     |LedY|   |    ", &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_6;
	LCD1202_printNumberInterger((__int64)((__int16)gPIDTask[5]), &position);


	if (gLedStatus[LED_YELLOW] == eTRUE)
	{
		position = LCD_1202_ADDRESS_LINE_TEXT_6 + gCurrentFont.charWidth * 12;

		LCD1202_printText("ON", &position);
	}
	else
	{
		position = LCD_1202_ADDRESS_LINE_TEXT_6 + gCurrentFont.charWidth * 16;

		LCD1202_printText("OFF", &position);
	}

	//
	position = LCD_1202_ADDRESS_LINE_TEXT_7;
	LCD1202_printText("     |LedB|   |    ", &position);

	position = LCD_1202_ADDRESS_LINE_TEXT_7;
	LCD1202_printNumberInterger((__int64)((__int16)gPIDTask[6]), &position);

	if (gLedStatus[LED_BLUE] == eTRUE)
	{
		position = LCD_1202_ADDRESS_LINE_TEXT_7 + gCurrentFont.charWidth * 12;
		LCD1202_printText("ON", &position);
	}
	else
	{
		position = LCD_1202_ADDRESS_LINE_TEXT_7 + gCurrentFont.charWidth * 16;

		LCD1202_printText("OFF", &position);
	}
}

/**
 *
 */

void MNT_update()
{

}

void MNT_Render()
{
	MNT_printBorder();
	LCD1202_flush();
}


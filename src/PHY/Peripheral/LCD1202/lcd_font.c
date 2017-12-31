/*==================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *==================================================================*/

/*==================================================================
 * In this file:
 *
 *==================================================================*/
#include <lcd_font.h>
#include <lcd1202.h>

__S_Font_Header gCurrentFont;

void LF_setFontIsUse(__UINT8 *p_fontSwith)
{
	gCurrentFont.charWidth = (__UINT32) p_fontSwith[0];
	gCurrentFont.charHight = (__UINT32) p_fontSwith[1];
	gCurrentFont.fontIsFull= (__UINT16) p_fontSwith[2];
	gCurrentFont.Resource  = &p_fontSwith[3];
}


void LF_printCharToLcdRam(__UINT8 ch, __UINT32 *p_position)
{
	__INT32 i;
	__INT32 charIndexInFont;

	charIndexInFont = 0;

	if (gCurrentFont.fontIsFull)
	{
		if (' ' <= ch && ch <= '~')
		{
			charIndexInFont = (__UINT32)(ch - ' ');
		}

	}
	else
	{
		if ('0' <= ch && ch <= '9')
		{
			charIndexInFont = (__UINT32)(ch - '0');
		}
		else if ('A' <= ch && ch <= 'Z')
		{
			charIndexInFont = (__UINT32)(ch - 'A');
		}
		else if ('a' <= ch && ch <= 'z')
		{
			charIndexInFont = (__UINT32)(ch - 'a');
		}
	}

	for (i = 0; i < gCurrentFont.charWidth; i++)
	{
		gLcd1202Ram[*p_position + i] = gCurrentFont.Resource[(charIndexInFont * gCurrentFont.charWidth) + i];
//		gLcd1202Ram[*p_position + i] = gCurrentFont.Resource[33*5 + i];

	}

	(*p_position) += gCurrentFont.charWidth;

}

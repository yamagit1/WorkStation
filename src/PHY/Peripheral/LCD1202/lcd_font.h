/*==================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *==================================================================*/

/*==================================================================
 * In this file:
 * 		- declare struct Font
 * 		- declare function initialize font ,..
 *==================================================================*/

#ifndef __FONT_H__
#define __FONT_H__

#include <header.h>


typedef enum{
	EF_LCD1202 = 1
}__E_Lcd_Font;

typedef struct {
	 __INT32 charWidth;
	 __INT32 charHight;
	 __INT32 fontIsFull;
	 __UINT8 *Resource;
}__S_Font_Header ;

extern __S_Font_Header gCurrentFont;


void LF_setFontIsUse(__UINT8 *p_fontSwith);

void LF_printCharToLcdRam(__UINT8 ch, __UINT32 *p_position);

#endif

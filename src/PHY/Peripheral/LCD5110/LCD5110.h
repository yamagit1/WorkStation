#ifndef __LCD5110_H__
#define __LCD5110_H__

//========================================
// 			HOANG NAM
//
//	dia chi :	DH-CONG NGHIEP HA NOI (HAUI)
// 	sdt		:	0167.440.1175
//	mail	: 	yamahi95@gmail.com
//=======================================

#include "header.h"

#define LCD_COM		GPIOD

#define LCD_RST 	GPIO_Pin_8
#define LCD_CE		GPIO_Pin_9
#define LCD_DC		GPIO_Pin_10
#define LCD_DIN		GPIO_Pin_11
#define LCD_CLK		GPIO_Pin_12
#define LCD_VCC		GPIO_Pin_13
#define LCD_LIG		GPIO_Pin_14
#define LCD_GND		GPIO_Pin_15

#define LCD_RCC_D	RCC_AHB1Periph_GPIOD

#define LCD_X		84
#define LCD_Y		48

//=====================
#define HIGHT(X)		GPIO_SetBits(LCD_COM,(X))
#define LOW(X)			GPIO_ResetBits(LCD_COM,(X))
//=====================
void LCDDelay(volatile __UINT32 time);

void InitPIN(GPIO_InitTypeDef *x,uint32_t PIN);

void LCDSetPin(void);

void LCDSendData(__UINT8 data);

#define EW_DATA 	1
#define	EW_COMMAND	0

void LCDWrite(__INT32 ew,__UINT8 data);

void LCDInit(void);

void LCDBitmap(__UINT8 *my_array);
#endif

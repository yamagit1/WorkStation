/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#ifndef __ENC28J60_SPI_H__
#define __ENC28J60_SPI_H__

#include "header.h"
#include "delay.h"

#if CONFIG_FLATFORM == FLATFORM_STM32_F407VG

#define disableChip  GPIO_SetBits(GPIOA,GPIO_Pin_2); Delay_us(2);
#define enableChip   GPIO_ResetBits(GPIOA,GPIO_Pin_2); Delay_us(2);

#else

#define disableChip
#define enableChip

#endif

void ENC28J60_SPI1_Configuration(void);
void ENC28J60_GPIO_Configuration(void);


__UINT8 ENC28J60_sendAndReceiveByte(__UINT8 dt);

void ENC28J60_SpiInit(void);


#endif /* __ENC28J60_SPI_H__ */

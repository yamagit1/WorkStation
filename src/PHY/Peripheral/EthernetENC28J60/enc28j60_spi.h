/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#ifndef __ENC28J60_SPI_H__
#define __ENC28J60_SPI_H__

#include "header.h"

#define enc28j60_Spi_Receive() ENC28J60_Send_And_Receive_Byte(0xff)
#define enc28j60_Spi_Send(data) ENC28J60_Send_And_Receive_Byte(data)

#define enc28j60_Enable() GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define enc28j60_Disable() GPIO_SetBits(GPIOB, GPIO_Pin_12)

__uint8 ENC28J60_Send_And_Receive_Byte(__uint8 data);
void ENC28J60_GPIO_Config(void);
void ENC28J60_SPI_Config(void);
void ENC28J60_SPI_Init(void);

#endif /* __ENC28J60_SPI_H__ */

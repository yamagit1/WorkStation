
#include "enc28j60_spi.h"

#if CONFIG_FLATFORM == FLATFORM_STM32_F407VG

__uint8 ENC28J60_Send_And_Receive_Byte(__uint8 data)
{
	// while transfer complete
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);

	SPI_I2S_SendData(SPI2,data);

	// while receive complete
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);

	return SPI_I2S_ReceiveData(SPI2);
}


void ENC28J60_GPIO_Config(void)
{
	__ENTER__

	GPIO_InitTypeDef GPIO_InitStruct;

	Console_Log_Print("Enable RCC for COM B ");

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);

	/* configure pins used by SPI1
	 * PB13 = SCK
	 * PB14 = MISO
	 * PB15 = MOSI
	 */
	Console_Log_Print("Configure pins used by SPI2 ");
	Console_Log_Print("\t PB13 = SCK \t PB14 = MISO \t PB15 = MOSI ");

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOB, &GPIO_InitStruct);

	// connect SPI1 pins to SPI alternate function
	Console_Log_Print("\t Connect SPI1 pins to SPI alternate function ");

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13 , GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15 , GPIO_AF_SPI2);

	// SS
	Console_Log_Print("\t PB12 = CS");

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIO_InitStruct);

	__LEAVE__
}


void ENC28J60_SPI_Config(void)
{
	__ENTER__

	SPI_InitTypeDef SPI_InitStruct;

	Console_Log_Print("Enable RCC for SPI 2 ");

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	Console_Log_Print("Configure module SPI2 ");

	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;

	SPI_Init(SPI2, &SPI_InitStruct);

	Console_Log_Print("Enable module SPI2 ");

	SPI_Cmd(SPI2, ENABLE);

	__LEAVE__
}


void ENC28J60_SPI_Init(void)
{
	__ENTER__

	ENC28J60_GPIO_Config();
	ENC28J60_SPI_Config();

	__LEAVE__
}
#endif


#include "enc28j60_spi.h"

#if CONFIG_FLATFORM == FLATFORM_STM32_F407VG

void ENC28J60_SPI1_Configuration(void)
{

	PRINT_LOG(0, LOG_PHY, "ENC28J60_SPI1_Configuration...enc28j60 config");

	SPI_InitTypeDef   SPI_InitStructure;

	/* Enable the SPI periph */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	/* SPI configuration -------------------------------------------------------*/
	// reset config to default
	SPI_I2S_DeInit(SPI1);

	// config SPI1
	SPI_InitStructure.SPI_Direction 	= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize 		= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL	 		= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA 			= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS 			= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStructure.SPI_FirstBit 		= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode 			= SPI_Mode_Master;

	SPI_Init(SPI1, &SPI_InitStructure);

	/* Enable SPI1  */
	SPI_Cmd(SPI1, ENABLE);

	PRINT_LOG(0, LOG_PHY, "done...\n");
}

void ENC28J60_GPIO_Configuration(void)
{
	PRINT_LOG(0, LOG_PHY, "ENC28J60_GPIO_Configuration...spi pin config for enc28j60");

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable SCK, MOSI and MISO GPIO clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Enable CS  GPIO clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// config mode AF with SPI 1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	// setup pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;

	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* SPI  MOSI pin configuration */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* SPI MISO pin configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure GPIO PIN for Chip select */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Deselect : Chip Select high */
	GPIO_SetBits(GPIOA, GPIO_Pin_2);

	PRINT_LOG(0, LOG_PHY, "done...\n");

}

__UINT8 ENC28J60_sendAndReceiveByte(__UINT8 dt)
{
	// while tranmistion complie
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData(SPI1, dt);

	// while receive complie
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	return SPI_I2S_ReceiveData(SPI1);
}

void ENC28J60_SpiInit(void)
{
	PRINT_LOG(0, LOG_PHY, "ENC28J60_SpiInit...");

	ENC28J60_SPI1_Configuration();
	ENC28J60_GPIO_Configuration();

	PRINT_LOG(0, LOG_PHY, "done...\n");
}

#endif

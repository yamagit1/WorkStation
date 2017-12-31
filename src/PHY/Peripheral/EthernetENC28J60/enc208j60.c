/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#include "enc208j60.h"
#include "lcd1202.h"

void ENC28J60_delay(volatile __UINT32 timeCount)
{

	while (timeCount != 0)
	{
		timeCount--;
	}

}

/**
 *
 */

void ENC28J60_configurePin(__UINT32 pinNumber)
{

	GPIO_InitTypeDef  pinConfig;

	pinConfig.GPIO_Mode		=	GPIO_Mode_OUT;
	pinConfig.GPIO_OType	=	GPIO_OType_PP;
	pinConfig.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	pinConfig.GPIO_Speed	=	GPIO_Speed_100MHz;

	switch (pinNumber)
	{
	case ENC28J60_INT:
	{
		pinConfig.GPIO_Pin = ENC28J60_INT_PIN;

		RCC_AHB1PeriphClockCmd(ENC28J60_INT_RCC, ENABLE);
		GPIO_Init(ENC28J60_INT_COM, &pinConfig);
	}
	break;

	case ENC28J60_CLKOUT:
	{
		pinConfig.GPIO_Pin = ENC28J60_CLKOUT_PIN;

		RCC_AHB1PeriphClockCmd(ENC28J60_CLKOUT_RCC, ENABLE);
		GPIO_Init(ENC28J60_CLKOUT_COM, &pinConfig);
	}
	break;

	case ENC28J60_SO:
	{
		pinConfig.GPIO_Pin = ENC28J60_SO_PIN;

		RCC_AHB1PeriphClockCmd(ENC28J60_SO_RCC, ENABLE);
		GPIO_Init(ENC28J60_SO_COM, &pinConfig);
	}
	break;

	case ENC28J60_WOL:
	{
		pinConfig.GPIO_Pin = ENC28J60_WOL_PIN;

		RCC_AHB1PeriphClockCmd(ENC28J60_WOL_RCC, ENABLE);
		GPIO_Init(ENC28J60_WOL_COM, &pinConfig);
	}
	break;

	case ENC28J60_SCK:
	{
		pinConfig.GPIO_Pin = ENC28J60_SCK_PIN;

		RCC_AHB1PeriphClockCmd(ENC28J60_SCK_RCC, ENABLE);
		GPIO_Init(ENC28J60_SCK_COM, &pinConfig);
	}
	break;

	case ENC28J60_SI:
	{
		pinConfig.GPIO_Pin = ENC28J60_SI_PIN;

		RCC_AHB1PeriphClockCmd(ENC28J60_SI_RCC, ENABLE);
		GPIO_Init(ENC28J60_SI_COM, &pinConfig);
	}
	break;

	case ENC28J60_RESET:
	{
		pinConfig.GPIO_Pin = ENC28J60_RESET_PIN;

		RCC_AHB1PeriphClockCmd(ENC28J60_RESET_RCC, ENABLE);
		GPIO_Init(ENC28J60_RESET_COM, &pinConfig);
	}
	break;

	case ENC28J60_CS:
	{
		pinConfig.GPIO_Pin = ENC28J60_CS_PIN;

		RCC_AHB1PeriphClockCmd(ENC28J60_CS_RCC, ENABLE);
		GPIO_Init(ENC28J60_CS_COM, &pinConfig);
	}
	break;

	default:
		break;
	}
}

/**
 *
 */

void ENC28J60_hightPowerPin(__UINT32 pinSetup)
{
	switch (pinSetup)
	{
	case ENC28J60_INT:
	{
		GPIO_SetBits(ENC28J60_INT_COM, ENC28J60_INT_PIN);
	}
	break;

	case ENC28J60_CLKOUT:
	{
		GPIO_SetBits(ENC28J60_CLKOUT_COM, ENC28J60_CLKOUT_PIN);
	}
	break;

	case ENC28J60_SO:
	{
		GPIO_SetBits(ENC28J60_SO_COM, ENC28J60_SO_PIN);
	}
	break;

	case ENC28J60_WOL:
	{
		GPIO_SetBits(ENC28J60_WOL_COM, ENC28J60_WOL_PIN);
	}
	break;

	case ENC28J60_SCK:
	{
		GPIO_SetBits(ENC28J60_SCK_COM, ENC28J60_SCK_PIN);
	}
	break;

	case ENC28J60_SI:
	{
		GPIO_SetBits(ENC28J60_SI_COM, ENC28J60_SI_PIN);
	}
	break;

	case ENC28J60_RESET:
	{
		GPIO_SetBits(ENC28J60_RESET_COM, ENC28J60_RESET_PIN);
	}
	break;

	case ENC28J60_CS:
	{
		GPIO_SetBits(ENC28J60_CS_COM, ENC28J60_CS_PIN);
	}
	break;

	default:
		break;
	}
}

/**
 *
 */

void ENC28J60_lowerPowerPin(__UINT32 pinSetup)
{
	switch (pinSetup)
	{
	case ENC28J60_INT:
	{
		GPIO_ResetBits(ENC28J60_INT_COM, ENC28J60_INT_PIN);
	}
	break;

	case ENC28J60_CLKOUT:
	{
		GPIO_ResetBits(ENC28J60_CLKOUT_COM, ENC28J60_CLKOUT_PIN);
	}
	break;

	case ENC28J60_SO:
	{
		GPIO_ResetBits(ENC28J60_SO_COM, ENC28J60_SO_PIN);
	}
	break;

	case ENC28J60_WOL:
	{
		GPIO_ResetBits(ENC28J60_WOL_COM, ENC28J60_WOL_PIN);
	}
	break;

	case ENC28J60_SCK:
	{
		GPIO_ResetBits(ENC28J60_SCK_COM, ENC28J60_SCK_PIN);
	}
	break;

	case ENC28J60_SI:
	{
		GPIO_ResetBits(ENC28J60_SI_COM, ENC28J60_SI_PIN);
	}
	break;

	case ENC28J60_RESET:
	{
		GPIO_ResetBits(ENC28J60_RESET_COM, ENC28J60_RESET_PIN);
	}
	break;

	case ENC28J60_CS:
	{
		GPIO_ResetBits(ENC28J60_CS_COM, ENC28J60_CS_PIN);
	}
	break;

	default:
		break;
	}
}

/**
 *
 */

__E_Bollen ENC28J60_checkPinData()
{
	if (GPIO_ReadOutputDataBit(ENC28J60_SO_COM, ENC28J60_SO_PIN) == Bit_SET)
	{
		return eTRUE;
	}
	else
	{
		return eFALSE;
	}
}

/**
 *
 */

void ENC28J60_settingPinConnection(void)
{

	//ENC28J60_configurePin(ENC28J60_INT);
	//	ENC28J60_configurePin(ENC28J60_CLKOUT);
	ENC28J60_configurePin(ENC28J60_SO);
	//	ENC28J60_configurePin(ENC28J60_WOL);
	ENC28J60_configurePin(ENC28J60_SCK);
	ENC28J60_configurePin(ENC28J60_SI);
	ENC28J60_configurePin(ENC28J60_RESET);
	ENC28J60_configurePin(ENC28J60_CS);

	ENC28J60_lowerPowerPin(ENC28J60_SO);
	ENC28J60_lowerPowerPin(ENC28J60_SCK);
	ENC28J60_lowerPowerPin(ENC28J60_SI);
	ENC28J60_lowerPowerPin(ENC28J60_RESET);
	ENC28J60_hightPowerPin(ENC28J60_CS);

}

/**
 *
 */

void ENC28J60_transficDataIn(__UINT8 data)
{
	__INT32 bitIndex;

	ENC28J60_lowerPowerPin(ENC28J60_SCK);
	ENC28J60_hightPowerPin(ENC28J60_SCK);

	for (bitIndex = 0; bitIndex < 8; bitIndex++)
	{

		if ((data << bitIndex) & 0x80)
		{
			ENC28J60_hightPowerPin(ENC28J60_SI);
		}
		else
		{
			ENC28J60_lowerPowerPin(ENC28J60_SI);
		}

		ENC28J60_lowerPowerPin(ENC28J60_SCK);
		ENC28J60_hightPowerPin(ENC28J60_SCK);

//		ENC28J60_delay(200);
	}
}

/**
 *
 */

__UINT8 ENC28J60_transficDataOut()
{
	__UINT8 data = 0x00;
	__INT32 bitIndex;

	ENC28J60_lowerPowerPin(ENC28J60_SCK);
	ENC28J60_hightPowerPin(ENC28J60_SCK);

	for (bitIndex = 8; bitIndex > 0; bitIndex--)
	{

		if (ENC28J60_checkPinData() == eTRUE)
		{
			data |= 0x01;

		}

		data <<= 0x01;

		ENC28J60_lowerPowerPin(ENC28J60_SCK);
		ENC28J60_hightPowerPin(ENC28J60_SCK);

//		ENC28J60_delay(200);
	}

	return data;
}

/**
 *
 */

void ENC28J60_readControlRegister(__UINT8 address, __UINT8 *p_buffer, __UINT32 numberData)
{
	__UINT32 i = 0;
	__UINT8 oppcodeAndAddress = 0x00;

	oppcodeAndAddress |= ENC28J60_SPI_OPCODE_RCR;
	oppcodeAndAddress |= (__UINT8)(address & ENC28J60_ADRRESS_MASK);

	// start
	ENC28J60_lowerPowerPin(ENC28J60_CS);

	ENC28J60_transficDataIn(oppcodeAndAddress);

	for (i = 0; i < numberData; i++)
	{
		p_buffer[i] = ENC28J60_transficDataOut();
	}

	ENC28J60_hightPowerPin(ENC28J60_CS);
}

/**
 *
 */

void ENC28J60_readBufferMemory(__UINT8 address, __UINT8 *p_buffer, __UINT32 numberData)
{
	__UINT32 i = 0;
	__UINT8 oppcodeAndAddress = 0x00;

	oppcodeAndAddress |= ENC28J60_SPI_OPCODE_RBM;
	oppcodeAndAddress |= (__UINT8)(address & ENC28J60_ADRRESS_MASK);

	ENC28J60_lowerPowerPin(ENC28J60_CS);

	ENC28J60_transficDataIn(oppcodeAndAddress);

	__UINT32 posiotion = LCD_1202_ADDRESS_LINE_TEXT_1;

	for (i = 0; i < numberData; i++)
	{
		p_buffer[i] = ENC28J60_transficDataOut();

		LCD1202_printText("Data send", &posiotion);
	}

	ENC28J60_hightPowerPin(ENC28J60_CS);

}

/**
 *
 */

void ENC28J60_writeControlRegister(__UINT8 address, __UINT8 data)
{
	__UINT8 oppcodeAndAddress = 0x00;

	oppcodeAndAddress |= ENC28J60_SPI_OPCODE_RBM;
	oppcodeAndAddress |= (__UINT8)(address & ENC28J60_ADRRESS_MASK);

	ENC28J60_lowerPowerPin(ENC28J60_CS);

	ENC28J60_transficDataIn(oppcodeAndAddress);
	ENC28J60_transficDataIn(data);

	ENC28J60_hightPowerPin(ENC28J60_CS);

}

/**
 *
 */

void ENC28J60_writeBufferMemory(__UINT8 address, __UINT8 *p_buffer, __UINT32 numberData)
{
	__UINT32 i = 0;
	__UINT8 oppcodeAndAddress = 0x00;

	oppcodeAndAddress |= ENC28J60_SPI_OPCODE_RBM;
	oppcodeAndAddress |= (__UINT8)(address & ENC28J60_ADRRESS_MASK);

	ENC28J60_lowerPowerPin(ENC28J60_CS);

	ENC28J60_transficDataIn(oppcodeAndAddress);

	for (i = 0; i < numberData; i++)
	{
		ENC28J60_transficDataIn(p_buffer[i]);
	}

	ENC28J60_hightPowerPin(ENC28J60_CS);

}


/**
 *
 */

void ENC28J60_initialize(void)
{

	ENC28J60_settingPinConnection();

	__LEAVE__();
}

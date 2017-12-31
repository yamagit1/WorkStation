/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/

#ifndef __ENC28J60_H__
#define __ENC28J60_H__

#include "header.h"

/*==============================================================================
 * Pin for SPI
 *============================================================================*/

#define ENC28J60_INT						1
#define ENC28J60_CLKOUT						2		// default not use
#define ENC28J60_SO							3
#define ENC28J60_WOL						4		// default not use
#define ENC28J60_SCK						5
#define ENC28J60_SI							6
#define ENC28J60_RESET						7
#define ENC28J60_CS							8

/*==============================================================================
 * config pin device stm32f407
 *============================================================================*/

#if CONFIG_FLATFORM == FLATFORM_STM32_F407VG

#define ENC28J60_INT_PIN					GPIO_Pin_0
#define ENC28J60_INT_COM					GPIOE
#define ENC28J60_INT_RCC					RCC_AHB1Periph_GPIOE
//d10
#define ENC28J60_CLKOUT_PIN					GPIO_Pin_1
#define ENC28J60_CLKOUT_COM					GPIOE
#define ENC28J60_CLKOUT_RCC					RCC_AHB1Periph_GPIOE
//b15
#define ENC28J60_SO_PIN						GPIO_Pin_2
#define ENC28J60_SO_COM						GPIOE
#define ENC28J60_SO_RCC						RCC_AHB1Periph_GPIOE
//d8
#define ENC28J60_WOL_PIN					GPIO_Pin_3
#define ENC28J60_WOL_COM					GPIOE
#define ENC28J60_WOL_RCC					RCC_AHB1Periph_GPIOE
//b13
#define ENC28J60_SCK_PIN					GPIO_Pin_4
#define ENC28J60_SCK_COM					GPIOE
#define ENC28J60_SCK_RCC					RCC_AHB1Periph_GPIOE
//b14
#define ENC28J60_SI_PIN						GPIO_Pin_5
#define ENC28J60_SI_COM						GPIOE
#define ENC28J60_SI_RCC						RCC_AHB1Periph_GPIOE
//b11
#define ENC28J60_RESET_PIN					GPIO_Pin_6
#define ENC28J60_RESET_COM					GPIOE
#define ENC28J60_RESET_RCC					RCC_AHB1Periph_GPIOE
//b12
#define ENC28J60_CS_PIN						GPIO_Pin_13
#define ENC28J60_CS_COM						GPIOC
#define ENC28J60_CS_RCC						RCC_AHB1Periph_GPIOC

#endif

/*========== ECOCON register =================================================*/

#define ENC28J60_ECOCON_DIV_8					((__UINT8)(0x05))
#define ENC28J60_ECOCON_DIV_4					((__UINT8)(0x04))
#define ENC28J60_ECOCON_DIV_3					((__UINT8)(0x03))
#define ENC28J60_ECOCON_DIV_2					((__UINT8)(0x02))
#define ENC28J60_ECOCON_DIV_1					((__UINT8)(0x01))
#define ENC28J60_ECOCON_DISENABLE				((__UINT8)(0x00))

/*=========== PHY MODULE LED CONTROL REGISTER ================================*/

//#define ENC28J60_PHLCON_LACFG_3				((__UINT8)(0x08))
//#define ENC28J60_PHLCON_LACFG_3				((__UINT8)(0x04))
//#define ENC28J60_PHLCON_LACFG_3				((__UINT8)(0x02))
//#define ENC28J60_PHLCON_LACFG_3				((__UINT8)(0x01))
//
//#define ENC28J60_PHLCON_LBCFG_3				((__UINT8)(0x80))
//#define ENC28J60_PHLCON_LBCFG_3				((__UINT8)(0x40))
//#define ENC28J60_PHLCON_LBCFG_3				((__UINT8)(0x20))
//#define ENC28J60_PHLCON_LBCFG_3				((__UINT8)(0x10))
//
//#define ENC28J60_PHLCON_LFRQ_1					((__UINT8)(0x08))
//#define ENC28J60_PHLCON_LFRQ_1					((__UINT8)(0x04))
//
//#define ENC28J60_PHLCON_STRCH					((__UINT8)(0x02))

/*=========== ENC28J60 CONTROL REGISTER MAP ====================================
 * - Control register definitions are a combination of address,
 * - bank number, and Ethernet/MAC/PHY indicator bits.
 * - Register address        (bits 0-4)
 * - Bank number        (bits 5-6)
 * - MAC/PHY indicator        (bit 7)
 *============================================================================*/

#define ADDR_MASK        0x1F
#define BANK_MASK        0x60
#define SPRD_MASK        0x80
// All-bank registers
#define EIE              0x1B
#define EIR              0x1C
#define ESTAT            0x1D
#define ECON2            0x1E
#define ECON1            0x1F
// Bank 0 registers
#define ERDPTL           (0x00|0x00)
#define ERDPTH           (0x01|0x00)
#define EWRPTL           (0x02|0x00)
#define EWRPTH           (0x03|0x00)
#define ETXSTL           (0x04|0x00)
#define ETXSTH           (0x05|0x00)
#define ETXNDL           (0x06|0x00)
#define ETXNDH           (0x07|0x00)
#define ERXSTL           (0x08|0x00)
#define ERXSTH           (0x09|0x00)
#define ERXNDL           (0x0A|0x00)
#define ERXNDH           (0x0B|0x00)
#define ERXRDPTL         (0x0C|0x00)
#define ERXRDPTH         (0x0D|0x00)
#define ERXWRPTL         (0x0E|0x00)
#define ERXWRPTH         (0x0F|0x00)
#define EDMASTL          (0x10|0x00)
#define EDMASTH          (0x11|0x00)
#define EDMANDL          (0x12|0x00)
#define EDMANDH          (0x13|0x00)
#define EDMADSTL         (0x14|0x00)
#define EDMADSTH         (0x15|0x00)
#define EDMACSL          (0x16|0x00)
#define EDMACSH          (0x17|0x00)
// Bank 1 registers
#define EHT0             (0x00|0x20)
#define EHT1             (0x01|0x20)
#define EHT2             (0x02|0x20)
#define EHT3             (0x03|0x20)
#define EHT4             (0x04|0x20)
#define EHT5             (0x05|0x20)
#define EHT6             (0x06|0x20)
#define EHT7             (0x07|0x20)
#define EPMM0            (0x08|0x20)
#define EPMM1            (0x09|0x20)
#define EPMM2            (0x0A|0x20)
#define EPMM3            (0x0B|0x20)
#define EPMM4            (0x0C|0x20)
#define EPMM5            (0x0D|0x20)
#define EPMM6            (0x0E|0x20)
#define EPMM7            (0x0F|0x20)
#define EPMCSL           (0x10|0x20)
#define EPMCSH           (0x11|0x20)
#define EPMOL            (0x14|0x20)
#define EPMOH            (0x15|0x20)
#define EWOLIE           (0x16|0x20)
#define EWOLIR           (0x17|0x20)
#define ERXFCON          (0x18|0x20)
#define EPKTCNT          (0x19|0x20)
// Bank 2 registers
#define MACON1           (0x00|0x40|0x80)
#define MACON2           (0x01|0x40|0x80)
#define MACON3           (0x02|0x40|0x80)
#define MACON4           (0x03|0x40|0x80)
#define MABBIPG          (0x04|0x40|0x80)
#define MAIPGL           (0x06|0x40|0x80)
#define MAIPGH           (0x07|0x40|0x80)
#define MACLCON1         (0x08|0x40|0x80)
#define MACLCON2         (0x09|0x40|0x80)
#define MAMXFLL          (0x0A|0x40|0x80)
#define MAMXFLH          (0x0B|0x40|0x80)
#define MAPHSUP          (0x0D|0x40|0x80)
#define MICON            (0x11|0x40|0x80)
#define MICMD            (0x12|0x40|0x80)
#define MIREGADR         (0x14|0x40|0x80)
#define MIWRL            (0x16|0x40|0x80)
#define MIWRH            (0x17|0x40|0x80)
#define MIRDL            (0x18|0x40|0x80)
#define MIRDH            (0x19|0x40|0x80)
// Bank 3 registers
#define MAADR1           (0x00|0x60|0x80)
#define MAADR0           (0x01|0x60|0x80)
#define MAADR3           (0x02|0x60|0x80)
#define MAADR2           (0x03|0x60|0x80)
#define MAADR5           (0x04|0x60|0x80)
#define MAADR4           (0x05|0x60|0x80)
#define EBSTSD           (0x06|0x60)
#define EBSTCON          (0x07|0x60)
#define EBSTCSL          (0x08|0x60)
#define EBSTCSH          (0x09|0x60)
#define MISTAT           (0x0A|0x60|0x80)
#define EREVID           (0x12|0x60)
#define ECOCON           (0x15|0x60)
#define EFLOCON          (0x17|0x60)
#define EPAUSL           (0x18|0x60)
#define EPAUSH           (0x19|0x60)

/*========== SPI operation codes =============================================*/

#define ENC28J60_ADRRESS_MASK			((__UINT8)0x1F)

#define ENC28J60_SPI_OPCODE_RCR       	((__UINT8)0x00)	// Read Control Register
#define ENC28J60_SPI_OPCODE_RBM        	((__UINT8)0x3A)	// Read Buffer Memory
#define ENC28J60_SPI_OPCODE_WCR      	((__UINT8)0x40)	// Write Control Register
#define ENC28J60_SPI_OPCODE_WBM       	((__UINT8)0x7A)	// Write Buffer Memory
#define ENC28J60_SPI_OPCODE_BFS       	((__UINT8)0x80)	// Bit Field Set
#define ENC28J60_SPI_OPCODE_BFC       	((__UINT8)0xA0)	// Bit Field Clear
#define ENC28J60_SPI_OPCODE_SRC         ((__UINT8)0xFF)	// System Reset Command (Soft Reset)

#define ENC28J60_GRUP_ETH_REGISTERS				0
#define ENC28J60_GRUP_MAC_AND_MII_REGISTERS		1

#define ENC28J60_BUFFER_ADDRESS			((__UINT8)0x1A)
/*==============================================================================
 * config pin device stm32f407
 *============================================================================*/

void ENC28J60_delay(volatile __UINT32 timeCount);
void ENC28J60_configurePin(__UINT32 pinNumber);
void ENC28J60_hightPowerPin(__UINT32 pinSetup);
void ENC28J60_lowerPowerPin(__UINT32 pinSetup);
__E_Bollen ENC28J60_checkPinData();
void ENC28J60_settingPinConnection(void);

void ENC28J60_transficDataIn(__UINT8 data);
__UINT8 ENC28J60_transficDataOut();

void ENC28J60_readControlRegister(__UINT8 address, __UINT8 *p_buffer, __UINT32 numberData);
void ENC28J60_readBufferMemory(__UINT8 address, __UINT8 *p_buffer, __UINT32 numberData);
void ENC28J60_writeControlRegister(__UINT8 address, __UINT8 data);
void ENC28J60_writeBufferMemory(__UINT8 address, __UINT8 *p_buffer, __UINT32 numberData);

void ENC28J60_initialize(void);






#endif // __ENC28J60_H__

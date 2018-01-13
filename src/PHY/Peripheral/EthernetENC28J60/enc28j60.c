#include "enc28j60.h"
#include "enc28j60_spi.h"

static __UINT8 ENC28J60Bank;
static __UINT16 gNextPacketPtr;
static __UINT8 erxfcon;


/**
 *
 */

__UINT8 ENC28J60_readWithOpcode(__UINT8 op, __UINT8 address)
{
	__UINT8 temp;

	enableChip;
	// issue read command
	ENC28J60_sendAndReceiveByte(op | (address & ADDR_MASK));
	// reciver data
	temp = ENC28J60_sendAndReceiveByte(0xFF);
	// get dump byte
	if (address & 0x80)
	{
		temp = ENC28J60_sendAndReceiveByte(0xFF);
	}

	disableChip;

	return temp;
}

/**
 *
 */

void ENC28J60_writeWithOpcode(__UINT8 op, __UINT8 address, __UINT8 data)
{
	enableChip;

	ENC28J60_sendAndReceiveByte(op | (address & ADDR_MASK));
	ENC28J60_sendAndReceiveByte(data);

	disableChip;

}

/**
 *
 */

void ENC28J60_powerDown()
{
	ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_RXEN);

	while (ENC28J60_readControlRegister(ESTAT) & ESTAT_RXBUSY);
	while (ENC28J60_readControlRegister(ECON1) & ECON1_TXRTS);

	ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PWRSV);
}

/**
 *
 */

void ENC28J60_powerUp()
{
	ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_CLR, ECON2, ECON2_PWRSV);

	while (!ENC28J60_readControlRegister(ESTAT) & ESTAT_CLKRDY);
}

/**
 *
 */

void ENC28J60_readBuffer(__UINT16 len, __UINT8* data)
{
	enableChip;

	ENC28J60_sendAndReceiveByte(ENC28J60_READ_BUF_MEM);

	while (len--)
	{
		*data++ = ENC28J60_sendAndReceiveByte(0x00);
	}

	disableChip;
	// Remove next line suggested by user epam - not needed
	//    *data='\0';
}

/**
 *
 */
__UINT16 ENC28J60_readBufferWord()
{
    uint16_t result;

    ENC28J60_readBuffer(2, (uint8_t*) &result);

    return result;
}


void ENC28J60_writeBuffer(__UINT16 len, __UINT8* data)
{
	enableChip;

	ENC28J60_sendAndReceiveByte(ENC28J60_WRITE_BUF_MEM);

	while (len--)
	{
		ENC28J60_sendAndReceiveByte(*data++);
	}

	disableChip;
}

/**
 *
 */

void ENC28J60_setBank(__UINT8 address)
{
	if ((address & BANK_MASK) != ENC28J60Bank)
	{
		ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_BSEL1|ECON1_BSEL0);

		ENC28J60Bank = address & BANK_MASK;

		ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, ECON1, ENC28J60Bank>>5);
	}
}

/**
 *
 */


__UINT8 ENC28J60_readControlRegister(__UINT8 address)
{
	// set the bank
	ENC28J60_setBank(address);
	// do the read
	return ENC28J60_readWithOpcode(ENC28J60_READ_CTRL_REG, address);
}

/**
 *
 */

void ENC28J60_writeControlRegister(__UINT8 address, __UINT8 data)
{
	// set the bank
	ENC28J60_setBank(address);
	// do the write
	ENC28J60_writeWithOpcode(ENC28J60_WRITE_CTRL_REG, address, data);
}

/**
 *
 */

void ENC28J60_writeControlRegisterWord(__UINT8 address, __UINT16 data)
{
	ENC28J60_writeControlRegister(address, data & 0xff);
	ENC28J60_writeControlRegister(address + 1, data >> 8);
}

/**
 *
 */

// read upper 8 bits
__UINT16 ENC28J60_phyReadH(__UINT8 address)
{
	// Set the right address and start the register read operation
	ENC28J60_writeControlRegister(MIREGADR, address);
	ENC28J60_writeControlRegister(MICMD, MICMD_MIIRD);

	Delay_us(15);
	// wait until the PHY read completes
	while (ENC28J60_readControlRegister(MISTAT) & MISTAT_BUSY);
	// reset reading bit
	ENC28J60_writeControlRegister(MICMD, 0x00);

	return (ENC28J60_readControlRegister(MIRDH));
}

/**
 *
 */

void ENC28J60_phyWrite(__UINT8 address, __UINT16 data)
{
	// set the PHY register address
	ENC28J60_writeControlRegister(MIREGADR, address);
	// write the PHY data
	ENC28J60_writeControlRegister(MIWRL, data);
	ENC28J60_writeControlRegister(MIWRH, data>>8);
	// wait until the PHY write completes
	while (ENC28J60_readControlRegister(MISTAT) & MISTAT_BUSY)
	{
		Delay_us(15);
	}
}
/*
static void ENC28J60_phyWriteWord(byte address, word data) {
    ENC28J60_writeControlRegister(MIREGADR, address);
    //ENC28J60_writeControlRegisterByte(MIREGADR, address);
    ENC28J60_writeControlRegisterWord(MIWRL, data);
    while (ENC28J60_readControlRegisterByte(MISTAT) & MISTAT_BUSY)
        ;
}
 */
void ENC28J60_clkout(__UINT8 clk)
{
	//setup clkout: 2 is 12.5MHz:
	ENC28J60_writeControlRegister(ECOCON, clk & 0x7);
}

void ENC28J60_init( __UINT8* macaddr )
{
	PRINT_LOG(0, LOG_PHY, "ENC28J60_init...");

	ENC28J60_SpiInit();

	enableChip; // ss=0

	// perform system reset
	ENC28J60_writeWithOpcode(ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);
	Delay_Ms(50);
	// check CLKRDY bit to see if reset is complete
	// The CLKRDY does not work. See Rev. B4 Silicon Errata point. Just wait.
	//while(!(ENC28J60_readControlRegister(ESTAT) & ESTAT_CLKRDY));
	// do bank 0 stuff
	// initialize receive buffer
	// 16-bit transfers, must write low byte first
	// set receive buffer start address
	gNextPacketPtr = RXSTART_INIT;
	// Rx start
	ENC28J60_writeControlRegisterWord(ERXSTL, RXSTART_INIT);
	// set receive pointer address
	ENC28J60_writeControlRegisterWord(ERXRDPTL, RXSTART_INIT);
	// RX end
	ENC28J60_writeControlRegisterWord(ERXNDL, RXSTOP_INIT);
	// TX start
	ENC28J60_writeControlRegisterWord(ETXSTL, TXSTART_INIT);
	// TX end
	ENC28J60_writeControlRegisterWord(ETXNDL, TXSTOP_INIT);
	// do bank 1 stuff, packet filter:
	// For broadcast packets we allow only ARP packtets
	// All other packets should be unicast only for our mac (MAADR)
	//
	// The pattern to match on is therefore
	// Type     ETH.DST
	// ARP      BROADCAST
	// 06 08 -- ff ff ff ff ff ff -> ip checksum for theses bytes=f7f9
	// in binary these poitions are:11 0000 0011 1111
	// This is hex 303F->EPMM0=0x3f,EPMM1=0x30

	//ENC28J60_writeControlRegister(ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN);
	//Change to add ERXFCON_BCEN recommended by epam
	//ENC28J60_writeControlRegister(ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN|ERXFCON_BCEN);
	erxfcon =  ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN|ERXFCON_BCEN;

	ENC28J60_writeControlRegister(ERXFCON, erxfcon );
	ENC28J60_writeControlRegisterWord(EPMM0, 0x303f);
	ENC28J60_writeControlRegisterWord(EPMCSL, 0xf7f9);
	//
	// do bank 2 stuff
	// enable MAC receive
	ENC28J60_writeControlRegister(MACON1, MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
	// bring MAC out of reset
	ENC28J60_writeControlRegister(MACON2, 0x00);
	// enable automatic padding to 60bytes and CRC operations
	ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN);  //|MACON3_FULDPX);
	// set inter-frame gap (non-back-to-back)
	ENC28J60_writeControlRegisterWord(MAIPGL, 0x0C12);
	// set inter-frame gap (back-to-back)
	ENC28J60_writeControlRegister(MABBIPG, 0x12);
	// Set the maximum packet size which the controller will accept
	// Do not send packets longer than MAX_FRAMELEN:
	ENC28J60_writeControlRegisterWord(MAMXFLL, MAX_FRAMELEN);
	// do bank 3 stuff
	// write MAC address
	// NOTE: MAC address in ENC28J60 is byte-backward
	ENC28J60_writeControlRegister(MAADR5, macaddr[0]);
	ENC28J60_writeControlRegister(MAADR4, macaddr[1]);
	ENC28J60_writeControlRegister(MAADR3, macaddr[2]);
	ENC28J60_writeControlRegister(MAADR2, macaddr[3]);
	ENC28J60_writeControlRegister(MAADR1, macaddr[4]);
	ENC28J60_writeControlRegister(MAADR0, macaddr[5]);
	// no loopback of transmitted frames
	ENC28J60_phyWrite(PHCON2, PHCON2_HDLDIS);
	// switch to bank 0
	ENC28J60_setBank(ECON1);
	// enable interrutps
	ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE|EIE_PKTIE);
	// enable packet reception
	ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);

	PRINT_LOG(0, LOG_PHY, "done...\n");
}

// read the revision of the chip:
__UINT8 ENC28J60_getrev(void)
{
	__UINT8 rev;

	rev = ENC28J60_readControlRegister(EREVID);
	// microchip forgot to step the number on the silcon when they
	// released the revision B7. 6 is now rev B7. We still have
	// to see what they do when they release B8. At the moment
	// there is no B8 out yet
	if (rev > 5)
	{
		rev++;
	}

	return(rev);
}

// A number of utility functions to enable/disable broadcast and multicast bits
void ENC28J60_enableBroadcast( void )
{
	erxfcon |= ERXFCON_BCEN;

	ENC28J60_writeControlRegister(ERXFCON, erxfcon);
}

void ENC28J60_disableBroadcast( void )
{
	erxfcon &= (0xff ^ ERXFCON_BCEN);
	ENC28J60_writeControlRegister(ERXFCON, erxfcon);
}

void ENC28J60_enableMulticast( void )
{
	erxfcon |= ERXFCON_MCEN;
	ENC28J60_writeControlRegister(ERXFCON, erxfcon);
}

void ENC28J60_disableMulticast( void )
{
	erxfcon &= (0xff ^ ERXFCON_MCEN);
	ENC28J60_writeControlRegister(ERXFCON, erxfcon);
}


// link status
__UINT8 ENC28J60_linkup(void)
{
	// bit 10 (= bit 3 in upper reg)
	return(ENC28J60_phyReadH(PHSTAT2) && 4);
}

void ENC28J60_packetSend(__UINT16 len, __UINT8* packet)
{
	// Check no transmit in progress
	while (ENC28J60_readWithOpcode(ENC28J60_READ_CTRL_REG, ECON1) & ECON1_TXRTS)
	{
		// Reset the transmit logic problem. See Rev. B4 Silicon Errata point 12.
		if ((ENC28J60_readControlRegister(EIR) & EIR_TXERIF))
		{
			ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRST);
			ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRST);
		}
	}

	// Set the write pointer to start of transmit buffer area
	ENC28J60_writeControlRegisterWord(EWRPTL, TXSTART_INIT);
	// Set the TXND pointer to correspond to the packet size given
	ENC28J60_writeControlRegisterWord(ETXNDL, (TXSTART_INIT+len));
	// write per-packet control byte (0x00 means use macon3 settings)
	ENC28J60_writeWithOpcode(ENC28J60_WRITE_BUF_MEM, 0, 0x00);
	// copy the packet into the transmit buffer
	ENC28J60_writeBuffer(len, packet);
	// send the contents of the transmit buffer onto the network
	ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);
	// Reset the transmit logic problem. See Rev. B4 Silicon Errata point 12.
}

// just probe if there might be a packet
//__UINT8 ENC28J60hasRxPkt(void)
//{
//       return ENC28J60_readControlRegisterByte(EPKTCNT) > 0;
//}

// Gets a packet from the network receive buffer, if one is available.
// The packet will by headed by an ethernet header.
//      maxlen  The maximum acceptable length of a retrieved packet.
//      packet  Pointer where packet data should be stored.
// Returns: Packet length in bytes if a packet was retrieved, zero otherwise.
__UINT16 ENC28J60_packetReceive(__UINT16 maxlen, __UINT8* packet)
{
	__UINT16 rxstat;
	__UINT16 len;
	// check if a packet has been received and buffered
	//if( !(ENC28J60_readControlRegister(EIR) & EIR_PKTIF) ){
	// The above does not work. See Rev. B4 Silicon Errata point 6.
	if (ENC28J60_readControlRegister(EPKTCNT) == 0)
	{
		return(0);
	}

	// Set the read pointer to the start of the received packet
	ENC28J60_writeControlRegisterWord(ERDPTL, gNextPacketPtr);
	//ENC28J60_writeControlRegister(ERDPTL, (gNextPacketPtr &0xFF));
	//ENC28J60_writeControlRegister(ERDPTH, (gNextPacketPtr)>>8);
	// read the next packet pointer
	gNextPacketPtr  = ENC28J60_readBufferWord();
	//gNextPacketPtr  = ENC28J60_readWithOpcode(ENC28J60_READ_BUF_MEM, 0);
	//gNextPacketPtr |= ENC28J60_readWithOpcode(ENC28J60_READ_BUF_MEM, 0)<<8;
	// read the packet length (see datasheet page 43)
	len = ENC28J60_readBufferWord() - 4;
	//len = ENC28J60_readWithOpcode(ENC28J60_READ_BUF_MEM, 0);
	//len |= ENC28J60_readWithOpcode(ENC28J60_READ_BUF_MEM, 0)<<8;
	//len-=4; //remove the CRC count
	// read the receive status (see datasheet page 43)
	rxstat  = ENC28J60_readBufferWord();
	//rxstat  = ENC28J60_readWithOpcode(ENC28J60_READ_BUF_MEM, 0);
	//rxstat |= ((__UINT16)ENC28J60_readWithOpcode(ENC28J60_READ_BUF_MEM, 0))<<8;
	// limit retrieve length
	if (len > (maxlen - 1))
	{
		len = maxlen - 1;
	}
	// check CRC and symbol errors (see datasheet page 44, table 7-3):
	// The ERXFCON.CRCEN is set by default. Normally we should not
	// need to check this.
	if ((rxstat & 0x80) == 0)
	{
		// invalid
		len=0;
	}
	else
	{
		// copy the packet from the receive buffer
		ENC28J60_readBuffer(len, packet);
	}
	// Move the RX read pointer to the start of the next received packet
	// This frees the memory we just read out
	ENC28J60_writeControlRegisterWord(ERXRDPTL, gNextPacketPtr );
	//ENC28J60_writeControlRegister(ERXRDPTL, (gNextPacketPtr &0xFF));
	//ENC28J60_writeControlRegister(ERXRDPTH, (gNextPacketPtr)>>8);
	// However, compensate for the errata point 13, rev B4: enver write an even address!
	if ((gNextPacketPtr - 1 < RXSTART_INIT)
			|| (gNextPacketPtr -1 > RXSTOP_INIT))
	{
		ENC28J60_writeControlRegisterWord(ERXRDPTL, RXSTOP_INIT);
		//ENC28J60_writeControlRegister(ERXRDPTL, (RXSTOP_INIT)&0xFF);
		//ENC28J60_writeControlRegister(ERXRDPTH, (RXSTOP_INIT)>>8);
	}
	else
	{
		ENC28J60_writeControlRegisterWord(ERXRDPTL, (gNextPacketPtr-1));
		//ENC28J60_writeControlRegister(ERXRDPTL, (gNextPacketPtr-1)&0xFF);
		//ENC28J60_writeControlRegister(ERXRDPTH, (gNextPacketPtr-1)>>8);
	}
	// decrement the packet counter indicate we are done with this packet
	ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC);

	return(len);

	/*
  __UINT16 rxstat;
    __UINT16 len;
    // check if a packet has been received and buffered
    //if( !(ENC28J60_readControlRegister(EIR) & EIR_PKTIF) ){
        // The above does not work. See Rev. B4 Silicon Errata point 6.
    if( ENC28J60_readControlRegister(EPKTCNT) ==0 ){
        return(0);
        }

    // Set the read pointer to the start of the received packet
    ENC28J60_writeControlRegisterWord(ERDPTL, gNextPacketPtr);
    // read the next packet pointer
    gNextPacketPtr  = ENC28J60_readBufferWord();
    // read the packet length (see datasheet page 43)
    len  = ENC28J60_readBufferWord() - 4;
    // read the receive status (see datasheet page 43)
    rxstat  = ENC28J60_readBufferWord();
    // limit retrieve length
        if (len>maxlen-1){
                len=maxlen-1;
        }
        // check CRC and symbol errors (see datasheet page 44, table 7-3):
        // The ERXFCON.CRCEN is set by default. Normally we should not
        // need to check this.
        if ((rxstat & 0x80)==0){
                // invalid
                len=0;
        }else{
                // copy the packet from the receive buffer
                ENC28J60_readBuffer(len, packet);
        }
    // Move the RX read pointer to the start of the next received packet
    // This frees the memory we just read out
//  ENC28J60_writeControlRegisterWord(ERXRDPTL, gNextPacketPtr );
        // However, compensate for the errata point 13, rev B4: enver write an even address!
        if ((gNextPacketPtr - 1 < RXSTART_INIT)
                || (gNextPacketPtr -1 > RXSTOP_INIT)) {
                ENC28J60_writeControlRegisterWord(ERXRDPTL, RXSTOP_INIT);
        } else {
                ENC28J60_writeControlRegisterWord(ERXRDPTL, (gNextPacketPtr-1));
        }
    // decrement the packet counter indicate we are done with this packet
    ENC28J60_writeWithOpcode(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC);
    return(len);
	 */
}

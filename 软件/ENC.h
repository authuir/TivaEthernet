/*
 * ENC.h
 *
 *  Created on: 2015-4-29
 *      Author: Authuir
 */

#ifndef ENC_H_
#define ENC_H_


//	PB4---RST	�͵�ƽ��Ч������λ���롣
//	PB5---CS	SPI �ӿڵ�Ƭѡ�������š�
//	PD3---SCK	SPI �ӿڵ�ʱ���������š�
//	PD2---SI	SPI �ӿڵ������������š�
//	PB7---SO	SPI �ӿڵ�����������š�
//  PB6---WOL	LAN �жϻ���������š�
//  PE2---INT	INT �ж�������š�
//  PE3---CLK	�ɱ��ʱ��������š�

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

/*
According to SPI communication all registers defined as combination of
MAC, PHY registers marker (7 bit) | bank marker (6-5 bits) | register address (4-0)
*/
#define MAC_PHY_REG                 ( 0x80 )
#define BANK0                       ( 0x00 )
#define BANK1                       ( 0x20 )
#define BANK2                       ( 0x40 )
#define BANK3                       ( 0x60 )

#define ADDR_MASK                   ( 0x1F )
#define BANK_MASK                   ( 0x60 )
#define SPRD_MASK                   ( 0x80 )

// Shared registers
#define EIE                         ( 0x1B )
#define EIR                         ( 0x1C )
#define ESTAT                       ( 0x1D )
#define ECON2                       ( 0x1E )
#define ECON1                       ( 0x1F )

// BANK0
#define ERDPTL                      ( 0x00 | BANK0 )
#define ERDPTH                      ( 0x01 | BANK0 )
#define EWRPTL                      ( 0x02 | BANK0 )
#define EWRPTH                      ( 0x03 | BANK0 )
#define ETXSTL                      ( 0x04 | BANK0 )
#define ETXSTH                      ( 0x05 | BANK0 )
#define ETXNDL                      ( 0x06 | BANK0 )
#define ETXNDH                      ( 0x07 | BANK0 )
#define ERXSTL                      ( 0x08 | BANK0 )
#define ERXSTH                      ( 0x09 | BANK0 )
#define ERXNDL                      ( 0x0A | BANK0 )
#define ERXNDH                      ( 0x0B | BANK0 )
#define ERXRDPTL                    ( 0x0C | BANK0 )
#define ERXRDPTH                    ( 0x0D | BANK0 )
#define ERXWRPTL                    ( 0x0E | BANK0 )
#define ERXWRPTH                    ( 0x0F | BANK0 )
#define EDMASTL                     ( 0x10 | BANK0 )
#define EDMASTH                     ( 0x11 | BANK0 )
#define EDMANDL                     ( 0x12 | BANK0 )
#define EDMANDH                     ( 0x13 | BANK0 )
#define EDMADSTL                    ( 0x14 | BANK0 )
#define EDMADSTH                    ( 0x15 | BANK0 )
#define EDMACSL                     ( 0x16 | BANK0 )
#define EDMACSH                     ( 0x17 | BANK0 )

//-- BANK1
#define EHT0                        ( 0x00 | BANK1 )
#define EHT1                        ( 0x01 | BANK1 )
#define EHT2                        ( 0x02 | BANK1 )
#define EHT3                        ( 0x03 | BANK1 )
#define EHT4                        ( 0x04 | BANK1 )
#define EHT5                        ( 0x05 | BANK1 )
#define EHT6                        ( 0x06 | BANK1 )
#define EHT7                        ( 0x07 | BANK1 )
#define EPMM0                       ( 0x08 | BANK1 )
#define EPMM1                       ( 0x09 | BANK1 )
#define EPMM2                       ( 0x0A | BANK1 )
#define EPMM3                       ( 0x0B | BANK1 )
#define EPMM4                       ( 0x0C | BANK1 )
#define EPMM5                       ( 0x0D | BANK1 )
#define EPMM6                       ( 0x0E | BANK1 )
#define EPMM7                       ( 0x0F | BANK1 )
#define EPMCSL                      ( 0x10 | BANK1 )
#define EPMCSH                      ( 0x11 | BANK1 )
#define EPMOL                       ( 0x14 | BANK1 )
#define EPMOH                       ( 0x15 | BANK1 )
#define ERXFCON                     ( 0x18 | BANK1 )
#define EPKTCNT                     ( 0x19 | BANK1 )

// Bank 2 registers
#define MACON1                      ( 0x00 | BANK2 | MAC_PHY_REG )
#define MACON2                      ( 0x01 | BANK2 | MAC_PHY_REG )
#define MACON3                      ( 0x02 | BANK2 | MAC_PHY_REG )
#define MACON4                      ( 0x03 | BANK2 | MAC_PHY_REG )
#define MABBIPG                     ( 0x04 | BANK2 | MAC_PHY_REG )
#define MAIPGL                      ( 0x06 | BANK2 | MAC_PHY_REG )
#define MAIPGH                      ( 0x07 | BANK2 | MAC_PHY_REG )
#define MACLCON1                    ( 0x08 | BANK2 | MAC_PHY_REG )
#define MACLCON2                    ( 0x09 | BANK2 | MAC_PHY_REG )
#define MAMXFLL                     ( 0x0A | BANK2 | MAC_PHY_REG )
#define MAMXFLH                     ( 0x0B | BANK2 | MAC_PHY_REG )
#define MICON                       ( 0x11 | BANK2 | MAC_PHY_REG )
#define MICMD                       ( 0x12 | BANK2 | MAC_PHY_REG )
#define MIREGADR                    ( 0x14 | BANK2 | MAC_PHY_REG )
#define MIWRL                       ( 0x16 | BANK2 | MAC_PHY_REG )
#define MIWRH                       ( 0x17 | BANK2 | MAC_PHY_REG )
#define MIRDL                       ( 0x18 | BANK2 | MAC_PHY_REG )
#define MIRDH                       ( 0x19 | BANK2 | MAC_PHY_REG )

// Bank 3 registers
#define MAADR1                      ( 0x00 | BANK3 | MAC_PHY_REG )
#define MAADR0                      ( 0x01 | BANK3 | MAC_PHY_REG )
#define MAADR3                      ( 0x02 | BANK3 | MAC_PHY_REG )
#define MAADR2                      ( 0x03 | BANK3 | MAC_PHY_REG )
#define MAADR5                      ( 0x04 | BANK3 | MAC_PHY_REG )
#define MAADR4                      ( 0x05 | BANK3 | MAC_PHY_REG )
#define EBSTSD                      ( 0x06 | BANK3 )
#define EBSTCON                     ( 0x07 | BANK3 )
#define EBSTCSL                     ( 0x08 | BANK3 )
#define EBSTCSH                     ( 0x09 | BANK3 )
#define MISTAT                      ( 0x0A | BANK3 | MAC_PHY_REG )
#define EREVID                      ( 0x12 | BANK3 )
#define ECOCON                      ( 0x15 | BANK3 )
#define EFLOCON                     ( 0x17 | BANK3 )
#define EPAUSL                      ( 0x18 | BANK3 )
#define EPAUSH                      ( 0x19 | BANK3 )

// PHY
#define PHCON1                      ( 0x00 )
#define PHSTAT1                     ( 0x01 )
#define PHHID1                      ( 0x02 )
#define PHHID2                      ( 0x03 )
#define PHCON2                      ( 0x10 )
#define PHSTAT2                     ( 0x11 )
#define PHIE                        ( 0x12 )
#define PHIR                        ( 0x13 )
#define PHLCON                      ( 0x14 )

// ERXFCON bits
#define ERXFCON_BCEN                ( 0x01 )
#define ERXFCON_MCEN                ( 0x02 )
#define ERXFCON_HTEN                ( 0x04 )
#define ERXFCON_MPEN                ( 0x08 )
#define ERXFCON_PMEN                ( 0x10 )
#define ERXFCON_CRCEN               ( 0x20 )
#define ERXFCON_ANDOR               ( 0x40 )
#define ERXFCON_UCEN                ( 0x80 )

// EIE bits
#define EIE_RXERIE                  ( 0x01 )
#define EIE_TXERIE                  ( 0x02 )
#define EIE_WOLIE                   ( 0x04 )
#define EIE_TXIE                    ( 0x08 )
#define EIE_LINKIE                  ( 0x10 )
#define EIE_DMAIE                   ( 0x20 )
#define EIE_PKTIE                   ( 0x40 )
#define EIE_INTIE                   ( 0x80 )

// EIR bits
#define EIR_RXERIF                  ( 0x01 )
#define EIR_TXERIF                  ( 0x02 )
#define EIR_WOLIF                   ( 0x04 )
#define EIR_TXIF                    ( 0x08 )
#define EIR_LINKIF                  ( 0x10 )
#define EIR_DMAIF                   ( 0x20 )
#define EIR_PKTIF                   ( 0x40 )

// ESTAT bits
#define ESTAT_CLKRDY                ( 0x01 )
#define ESTAT_TXABRT                ( 0x02 )
#define ESTAT_RXBUSY                ( 0x04 )
#define ESTAT_LATECOL               ( 0x10 )
#define ESTAT_INT                   ( 0x80 )

// ECON2 bits
#define ECON2_VRPS                  ( 0x08 )
#define ECON2_PWRSV                 ( 0x20 )
#define ECON2_PKTDEC                ( 0x40 )
#define ECON2_AUTOINC               ( 0x80 )

// ECON1 bits
#define ECON1_BSEL0                 ( 0x01 )
#define ECON1_BSEL1                 ( 0x02 )
#define ECON1_RXEN                  ( 0x04 )
#define ECON1_TXRTS                 ( 0x08 )
#define ECON1_CSUMEN                ( 0x10 )
#define ECON1_DMAST                 ( 0x20 )
#define ECON1_RXRST                 ( 0x40 )
#define ECON1_TXRST                 ( 0x80 )

// MACON1 bits
#define MACON1_MARXEN               ( 0x01 )
#define MACON1_PASSALL              ( 0x02 )
#define MACON1_RXPAUS               ( 0x04 )
#define MACON1_TXPAUS               ( 0x08 )
#define MACON1_LOOPBK               ( 0x10 )

// MACON2 bits
#define MACON2_TFUNRST              ( 0x01 )
#define MACON2_MATXRST              ( 0x02 )
#define MACON2_RFUNRST              ( 0x04 )
#define MACON2_MARXRST              ( 0x08 )
#define MACON2_RNDRST               ( 0x40 )
#define MACON2_MARST                ( 0x80 )

// MACON3 bits
#define MACON3_FULDPX               ( 0x01 )
#define MACON3_FRMLNEN              ( 0x02 )
#define MACON3_HFRMLEN              ( 0x04 )
#define MACON3_PHDRLEN              ( 0x08 )
#define MACON3_TXCRCEN              ( 0x10 )
#define MACON3_PADCFG0              ( 0x20 )
#define MACON3_PADCFG1              ( 0x40 )
#define MACON3_PADCFG2              ( 0x80 )

// MICMD bits
#define MICMD_MIIRD                 ( 0x01 )
#define MICMD_MIISCAN               ( 0x02 )

// MISTAT bits
#define MISTAT_BUSY                 ( 0x01 )
#define MISTAT_SCAN                 ( 0x02 )
#define MISTAT_NVALID               ( 0x04 )

// PHCON1 bits
#define PHCON1_PDPXMD               ( 0x0100 )
#define PHCON1_PPWRSV               ( 0x0800 )
#define PHCON1_PLOOPBK              ( 0x4000 )
#define PHCON1_PRST                 ( 0x8000 )

// PHSTAT1 bits
#define PHSTAT1_JBSTAT              ( 0x0002 )
#define PHSTAT1_LLSTAT              ( 0x0004 )
#define PHSTAT1_PHDPX               ( 0x0800 )
#define PHSTAT1_PFDPX               ( 0x1000 )

// PHSTAT2 bits
#define PHSTAT2_PLRITY              ( 0x0010 )
#define PHSTAT2_DPXSTAT             ( 0x0200 )
#define PHSTAT2_LSTAT               ( 0x0400 )
#define PHSTAT2_COLSTAT             ( 0x0800 )
#define PHSTAT2_RXSTAT              ( 0x1000 )
#define PHSTAT2_TXSTAT              ( 0x2000 )

// PHCON2 bits
#define PHCON2_HDLDIS               ( 0x0100 )
#define PHCON2_JABBER               ( 0x0400 )
#define PHCON2_TXDIS                ( 0x2000 )
#define PHCON2_FRCLINK              ( 0x4000 )

// PKTCTRL bits
#define PKTCTRL_POVERRIDE           ( 0x01 )
#define PKTCTRL_PCRCEN              ( 0x02 )
#define PKTCTRL_PPADEN              ( 0x04 )
#define PKTCTRL_PHUGEEN             ( 0x08 )

// SPI operation codes
#define ENC28J60_READ_CTRL_REG      ( 0x00 )
#define ENC28J60_READ_BUF_MEM       ( 0x3A )
#define ENC28J60_WRITE_CTRL_REG     ( 0x40 )
#define ENC28J60_WRITE_BUF_MEM      ( 0x7A )
#define ENC28J60_BIT_FIELD_SET      ( 0x80 )
#define ENC28J60_BIT_FIELD_CLR      ( 0xA0 )
#define ENC28J60_SOFT_RESET         ( 0xFF )

// The RXSTART_INIT should be zero. See Rev. B4 Silicon Errata
// buffer boundaries applied to internal 8K ram
// the entire available packet buffer space is allocated
//
// start with recbuf at 0/
#define RXSTART_INIT     0x0
// receive buffer end
#define RXSTOP_INIT      (0x1FFF-1518-1)
// start TX buffer at 0x1FFF-0x0600, pace for one full ethernet frame (0~1518 bytes)
#define TXSTART_INIT     (0x1FFF-1518)
// stp TX buffer at end of mem
#define TXSTOP_INIT      0x1FFF
// max frame length which the conroller will accept:
#define   MAX_FRAMELEN    1518        // (note: maximum ethernet frame length would be 1518)

#define RST_1 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define RST_0 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0)

#define CS_1 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5)
#define CS_0 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0)

#define CLK_1 GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define CLK_0 GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0)

#define INT_1 GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define INT_0 GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0)

#define SCK_1 GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define SCK_0 GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0)

#define SI_1 GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define SI_0 GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0)

#define SO_1 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7)
#define SO_0 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0)
#define SO_R ( GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_7) >> 7 )

#define WOL_1 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_PIN_6)
#define WOL_0 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0)



void ENC_Pin_Init(void);
uint8_t ENC_Read_ETH(uint8_t In);										//��ȡETH�Ĵ���
void ENC_Write_ETH(uint8_t ADDR,uint8_t Val);						//д��ETH�Ĵ���

uint8_t ENC_Read_Op(uint8_t op,uint8_t addr);
void ENC_Write_Op(uint8_t op,uint8_t addr,uint8_t data);
void ENC_Read_Buf(uint32_t len,uint8_t* data);
void ENC_Write_Buf(uint32_t len,uint8_t* data);
void ENC_Set_Bank(uint8_t bank);
uint8_t ENC_Read(uint8_t addr);
void ENC_Write(uint8_t addr,uint8_t data);
void ENC_PHY_Write(uint8_t addr,uint32_t data);
uint8_t ENC_Init(uint8_t* macaddr);
uint8_t ENC_Get_EREVID(void);
void ENC_Packet_Send(uint32_t len,uint8_t* packet);
uint32_t ENC_Packet_Receive(uint32_t maxlen,uint8_t* packet);


#endif /* ENC_H_ */

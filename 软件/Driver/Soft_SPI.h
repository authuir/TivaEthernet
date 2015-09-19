/*
 * Soft_SPI.h
 *
 *  Created on: 2015-9-12
 *      Author: Authuir
 */

#ifndef SOFT_SPI_H_
#define SOFT_SPI_H_

#define uint uint8_t
#define uchar uint8_t

/****************
 *	¶Ë¿Úºê¶¨Òå  *
 ****************/
/************************SPI1**********************/
#define SPI1_CE_0 ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0)
#define SPI1_CE_1 ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6)

#define SPI1_CSN_0 ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0)
#define SPI1_CSN_1 ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3)

#define SPI1_MOSI_0 ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0)
#define SPI1_MOSI_1 ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1)

#define SPI1_MISO ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);

#define SPI1_SCK_0 ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0)
#define SPI1_SCK_1 ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2)
/**************************************************/

/************************SPI2**********************/
#define SPI2_CSN_0 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0)
#define SPI2_CSN_1 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5)

#define SPI2_MOSI_0 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0)
#define SPI2_MOSI_1 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7)

#define SPI2_MISO ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_6);

#define SPI2_SCK_0 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0)
#define SPI2_SCK_1 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4)
/**************************************************/

/************************SPI2**********************/
#define SPI3_CSN_0 ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0)
#define SPI3_CSN_1 ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1)

#define SPI3_MOSI_0 ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0)
#define SPI3_MOSI_1 ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3)

#define SPI3_MISO ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2);

#define SPI3_SCK_0 ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0)
#define SPI3_SCK_1 ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0)
/**************************************************/

#define SPI0 0x00
#define SPI1 0x01
#define SPI2 0x02
#define SPI3 0x03

void SPI1_Init();
uint SPI1_RW(uint uchar);
uchar SPI1_Read(uchar reg);
uint SPI1_RW_Reg(uchar reg, uchar value);
uint SPI1_Read_Buf(uchar reg, uchar *pBuf, uchar uchars);
uint SPI1_Write_Buf(uchar reg,const  uchar *pBuf, uchar uchars);

void SPI2_Init();
uint SPI2_RW(uint uchar);
uchar SPI2_Read(uchar reg);
uint SPI2_RW_Reg(uchar reg, uchar value);
uint SPI2_Read_Buf(uchar reg, uchar *pBuf, uchar uchars);
uint SPI2_Write_Buf(uchar reg,const  uchar *pBuf, uchar uchars);

void SPI3_Init();
uint SPI3_RW(uint uchar);
uchar SPI3_Read(uchar reg);
uint SPI3_RW_Reg(uchar reg, uchar value);
uint SPI3_Read_Buf(uchar reg, uchar *pBuf, uint32_t uchars);
uint SPI3_Write_Buf(uchar reg,const uchar *pBuf, uint32_t uchars);

#endif /* SOFT_SPI_H_ */

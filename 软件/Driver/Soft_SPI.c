/*
 * Soft_SPI.c
 *
 *  Created on: 2015-9-12
 *      Author: Authuir
 */
#include "Common.h"


uint SPI1_RW(uint ucharss)
{
	uint8_t bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		if (ucharss & 0x80)
			SPI1_MOSI_1;
		else
			SPI1_MOSI_0;						// output 'uchar', MSB to MOSI
		ucharss = (ucharss << 1);           // shift next bit into MSB..
		SPI1_SCK_1;                      	// Set SCK high..
		ucharss |= SPI1_MISO;       		  	// capture current MISO bit
		SPI1_SCK_0;            		  		// ..then set SCK low again
   	}
    return(ucharss);           		  	// return read uchar
}

uchar SPI1_Read(uchar reg)
{
	uchar reg_val;

	SPI1_CSN_0;                // CSN low, initialize SPI communication...
	SPI1_RW(reg);            // Select register to read from..
	reg_val = SPI1_RW(0);    // ..then read registervalue
	SPI1_CSN_1;                // CSN high, terminate SPI communication

	return(reg_val);        // return register value
}


uint SPI1_RW_Reg(uchar reg, uchar value)
{
	uint status;

	SPI1_CSN_0;                   	// CSN low, init SPI transaction
	status = SPI1_RW(reg);      	// select register
	SPI1_RW(value);             	// ..and write value to it..
	SPI1_CSN_1;                   	// CSN high again

	return(status);            // return nRF24L01 status uchar
}


uint SPI1_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;

	SPI1_CSN_0;                    		// Set CSN low, init SPI tranaction
	status = SPI1_RW(reg);       		// Select register to write to and read status uchar

	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
		pBuf[uchar_ctr] = SPI1_RW(0);    //

	SPI1_CSN_1;

	return(status);                    // return nRF24L01 status uchar
}

uint SPI1_Write_Buf(uchar reg,const uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	SPI1_CSN_0;            //SPI使能
	status = SPI1_RW(reg);
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI1_RW(*pBuf++);
	SPI1_CSN_1;           //关闭SPI
	return(status);    //
}

void SPI1_Init()
{
	/* 解锁PD6并初始化 */
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x0;
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
}

void SPI2_Init()
{
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7);
}

uint SPI2_RW(uint ucharss)
{
	uint8_t bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		if (ucharss & 0x80)
			SPI2_MOSI_1;
		else
			SPI2_MOSI_0;						// output 'uchar', MSB to MOSI
		ucharss = (ucharss << 1);           // shift next bit into MSB..
		SPI2_SCK_1;                      	// Set SCK high..
		ucharss |= SPI2_MISO;       		  	// capture current MISO bit
		SPI2_SCK_0;            		  		// ..then set SCK low again
   	}
    return(ucharss);           		  	// return read uchar
}

uchar SPI2_Read(uchar reg)
{
	uchar reg_val;

	SPI2_CSN_0;                // CSN low, initialize SPI communication...
	SPI2_RW(reg);            // Select register to read from..
	reg_val = SPI2_RW(0);    // ..then read registervalue
	SPI2_CSN_1;                // CSN high, terminate SPI communication

	return(reg_val);        // return register value
}

uint SPI2_RW_Reg(uchar reg, uchar value)
{
	uint status;

	SPI2_CSN_0;                   	// CSN low, init SPI transaction
	status = SPI2_RW(reg);      	// select register
	SPI2_RW(value);             	// ..and write value to it..
	SPI2_CSN_1;                   	// CSN high again

	return(status);            		// return status uchar
}

uint SPI2_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;

	SPI2_CSN_0;                    		// Set CSN low, init SPI tranaction
	status = SPI2_RW(reg);       		// Select register to write to and read status uchar

	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
		pBuf[uchar_ctr] = SPI2_RW(0);    //

	SPI2_CSN_1;

	return(status);                    // return status uchar
}

uint SPI2_Write_Buf(uchar reg,const uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	SPI2_CSN_0;            //SPI使能
	status = SPI2_RW(reg);
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI2_RW(*pBuf++);
	SPI2_CSN_1;           //关闭SPI
	return(status);    //
}


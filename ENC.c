/*
 * ENC.c
 *
 *  Created on: 2015-4-29
 *      Author: Authuir
 */

#include "ENC.h"

void ENC_Pin_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6);
	//GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_7);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3);
	RST_1;
}

void delay_ENC()
{
	int i,j;
	for (i=0;i<1;i++)
		for (j=0;j<5;j++);
}

uint8_t ENC_Read_ETH(uint8_t In)
{
	int i;
	CS_0;
	delay_ENC();
	for (i=0;i<8;i++)
	{
		SCK_0;
		delay_ENC();
		if( (In&0x80) == 0x80 )
			SI_1;
		else
			SI_0;
		SCK_1;
		delay_ENC();
		In = In << 1;
	}
	In = 0;
	for (i=0;i<8;i++)
	{
		In = In << 1;
		SCK_0;
		delay_ENC();
		In += SO_R;
		SCK_1;
		delay_ENC();
	}
	CS_1;
	return In;
}


uint8_t ENC_Write_ETH(uint8_t ADDR,uint8_t Val)
{
	int i;
	ADDR = ADDR + 0x40;
	CS_0;
	delay_ENC();
	for (i=0;i<8;i++)
	{
		SCK_0;
		delay_ENC();
		if( (ADDR&0x80) == 0x80 )
			SI_1;
		else
			SI_0;
		SCK_1;
		delay_ENC();
		ADDR = ADDR << 1;
	}
	for (i=0;i<8;i++)
	{
		SCK_0;
		delay_ENC();
		if( (Val&0x80) == 0x80 )
			SI_1;
		else
			SI_0;
		SCK_1;
		delay_ENC();
		Val = Val << 1;
	}
	CS_1;
	return 0;
}

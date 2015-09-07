/*
 * NRF.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */
#include "Common.h"

void Init_NRF24L01(void)
{
	uint32_t TMP[255];
//	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
//	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;
//	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x0;

//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
//    GPIOPadConfigSet(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD);
//    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6,GPIO_PIN_6);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    GPIOPinConfigure(GPIO_PF0_SSI1RX);
    GPIOPinConfigure(GPIO_PF1_SSI1TX);
    GPIOPinConfigure(GPIO_PF2_SSI1CLK);
    GPIOPinConfigure(GPIO_PF3_SSI1FSS);
    GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    SSIConfigSetExpClk(SSI1_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI1_BASE);

    while (TMP[0] != 1 )
    {
    	 SSIDataGet(SSI0_BASE, TMP);
    };

}

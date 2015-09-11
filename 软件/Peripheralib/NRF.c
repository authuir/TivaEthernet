/*
 * NRF.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */
#include "Common.h"
void Init_NRF24L01(void)
{

	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
	NRF_CE_0;
#ifdef HARD_SSI
	GPIOPinConfigure(GPIO_PF1_SSI1TX);
	GPIOPinConfigure(GPIO_PF2_SSI1CLK);
	GPIOPinConfigure(GPIO_PF3_SSI1FSS);
	GPIOPinConfigure(GPIO_PF0_SSI1RX);

	GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	SSIConfigSetExpClk(SSI1_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);

	SSIEnable(SSI1_BASE);
	SSIDisable(SSI1_BASE);
#else

#endif
}

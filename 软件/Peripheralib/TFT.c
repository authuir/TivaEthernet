/*
 * TFT.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */
#include "Common.h"

void Init_TFT()
{
    uint32_t pui32DataTx[NUM_SSI_DATA];
    uint32_t pui32DataRx[NUM_SSI_DATA];
    uint32_t ui32Index;
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0,GPIO_PIN_0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
    GPIOPinConfigure(GPIO_PD0_SSI3CLK);
    GPIOPinConfigure(GPIO_PD1_SSI3FSS);
    GPIOPinConfigure(GPIO_PD2_SSI3RX);
    GPIOPinConfigure(GPIO_PD3_SSI3TX);
    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    SSIConfigSetExpClk(SSI3_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI3_BASE);
    while(SSIDataGetNonBlocking(SSI0_BASE, &pui32DataRx[0]));
    for(ui32Index = 0; ui32Index < NUM_SSI_DATA; ui32Index++)
    {
    	SSIDataPut(SSI3_BASE, pui32DataTx[ui32Index]);
    }
}

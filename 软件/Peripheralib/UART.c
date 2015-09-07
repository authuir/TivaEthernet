/*
 * UART.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */

#include "Common.h"

uint8_t UART1_Buffer[ UART_MAX_Buffer ];
uint8_t UART2_Buffer[ UART_MAX_Buffer ];

void Init_UART()
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), UART2_BAUD,
                                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), UART1_BAUD,
                                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    ROM_IntEnable(INT_UART0|INT_UART1);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
    ROM_UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
}

void UART0IntHandler()
{
	int a = 3.15;
	a=a*2;
}

void UART1IntHandler()
{
	int a = 3.15;
	a=a*2;
}

void
UART1_Send(char *pui8Buffer, uint32_t ui32Count)
{
    while(ui32Count--)
    {
    	UARTCharPut(UART1_BASE, *pui8Buffer++);
    }
}

/*
 *  π”√£∫    UART2_Send("Test",4);
    	UART2_Receive(d,8);
 *
 */

void
UART2_Send(char *pui8Buffer, uint32_t ui32Count)
{
    while(ui32Count--)
    {
        UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

void UART1_Receive(uint8_t * Dst_Ptr,uint32_t Dst_Cnt)
{

	uint8_t Cnt = 0;
	while(!UARTCharsAvail(UART1_BASE));
	while(UART1_Buffer[Cnt++] = UARTCharGet(UART1_BASE));
	memcpy(Dst_Ptr, UART1_Buffer, sizeof(uint8_t) * Dst_Cnt);

}

void UART2_Receive(uint8_t * Dst_Ptr,uint32_t Dst_Cnt)
{

	while(!UARTCharsAvail(UART0_BASE));
	while(*Dst_Ptr = UARTCharGet(UART0_BASE))
	{
		Dst_Ptr++;
	}
	memcpy(Dst_Ptr, UART2_Buffer, sizeof(uint8_t) * Dst_Cnt);

}

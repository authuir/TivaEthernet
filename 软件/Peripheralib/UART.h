/*
 * UART.h
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */

#ifndef UART_H_
#define UART_H_

#define UART1_BAUD 9600
#define UART2_BAUD 9600
#define UART_MAX_Buffer 256

extern uint8_t UART1_Buffer[ UART_MAX_Buffer ];
extern uint8_t UART2_Buffer[ UART_MAX_Buffer ];

extern void Init_UART();
extern void UART1IntHandler();
extern void UART2IntHandler();
extern void UART1_Send(char *pui8Buffer, uint32_t ui32Count);
extern void UART2_Send(char *pui8Buffer, uint32_t ui32Count);
extern void UART1_Receive(uint8_t * Dst_Ptr,uint32_t Dst_Cnt);
extern void UART2_Receive(uint8_t * Dst_Ptr,uint32_t Dst_Cnt);

#endif /* UART_H_ */

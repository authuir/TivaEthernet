/*
 * NRF.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */
#include "Common.h"

uint16_t sta;
#define	RX_DR	sta^6
#define	TX_DS	sta^5
#define	MAX_RT	sta^4

void Delay(unsigned int s)
{
	unsigned int i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}
#ifdef SOFT_SSI
uint const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���ص�ַ
uint const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���յ�ַ
#endif

void Init_NRF24L01(void)
{

#ifdef HARD_SSI
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
	GPIOPinConfigure(GPIO_PF1_SSI1TX);
	GPIOPinConfigure(GPIO_PF2_SSI1CLK);
	GPIOPinConfigure(GPIO_PF3_SSI1FSS);
	GPIOPinConfigure(GPIO_PF0_SSI1RX);

	GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	SSIConfigSetExpClk(SSI1_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);

	SSIEnable(SSI1_BASE);
	SSIDisable(SSI1_BASE);
#endif

#ifdef SOFT_SSI
	SPI1_Init();
    Delay(10);
    SPI1_CE_0;    // chip enable
    SPI1_CSN_1;   // Spi disable
    SPI1_SCK_0;   // Spi clock line init high

	SPI1_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    	//д���ص�ַ
	SPI1_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); 	//д���ն˵�ַ
	SPI1_RW_Reg(WRITE_REG + EN_AA, 0x01);      							//Ƶ��0�Զ�	ACKӦ������
	SPI1_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  							//������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21
	SPI1_RW_Reg(WRITE_REG + RF_CH, 0);        							//�����ŵ�����Ϊ2.4GHZ���շ�����һ��
	SPI1_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); 					//���ý������ݳ��ȣ���������Ϊ32�ֽ�
	SPI1_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   							//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB
	SPI1_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 					//IRQ�շ�����ж���Ӧ��16λCRC��������
#endif

}

void SetRX_Mode(void)
{
	SPI1_CE_0;
	SPI1_RW_Reg(WRITE_REG + CONFIG, 0x0f);   					// IRQ�շ�����ж���Ӧ��16λCRC	��������
	SPI1_CE_1;
	Delay(13);    												//��ʱ����̫��
}

unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	sta = SPI1_Read(STATUS);										// ��ȡ״̬�Ĵ������ж����ݽ���״��
	if(RX_DR)													// �ж��Ƿ���յ�����   ////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		SPI1_CE_0; 													//SPIʹ��
		SPI1_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);		// read receive payload from RX_FIFO buffer
		revale =1;												//��ȡ������ɱ�־
	}
	SPI1_RW_Reg(WRITE_REG+STATUS,sta);   						//���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	return revale;
}

void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	uint const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���ص�ַ
//	uint const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���յ�ַ
	SPI1_CE_0;																//StandBy Iģʽ
	SPI1_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); 	// װ�ؽ��ն˵�ַ
	SPI1_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 	// װ������
//	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 					// IRQ�շ�����ж���Ӧ��16λCRC��������
	SPI1_CE_1;		 														//�ø�CE���������ݷ���
	Delay(1);
}

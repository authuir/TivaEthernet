/*
 * NRF.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */
#include "Common.h"

uint16_t sta;
#define	RX_DR sta^6
#define	TX_DS sta^5
#define	MAX_RT sta^4

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
	/* ����PD6����ʼ�� */
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x0;
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
	CE_0;
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
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    Delay(10);
 	CE_0;    // chip enable
 	CSN_1;   // Spi disable
 	SCK_0;   // Spi clock line init high

	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    	//д���ص�ַ
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); 	//д���ն˵�ַ
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      							//Ƶ��0�Զ�	ACKӦ������
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  							//������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);        							//�����ŵ�����Ϊ2.4GHZ���շ�����һ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); 					//���ý������ݳ��ȣ���������Ϊ32�ֽ�
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   							//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 					//IRQ�շ�����ж���Ӧ��16λCRC��������
#endif

}


uint SPI_RW(uint ucharss)
{
	uint8_t bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		if (ucharss & 0x80)
			MOSI_1;
		else
			MOSI_0;						// output 'uchar', MSB to MOSI
		ucharss = (ucharss << 1);           // shift next bit into MSB..
		SCK_1;                      	// Set SCK high..
		ucharss |= MISO;       		  	// capture current MISO bit
		SCK_0;            		  		// ..then set SCK low again
   	}
    return(ucharss);           		  	// return read uchar
}



uchar SPI_Read(uchar reg)
{
	uchar reg_val;

	CSN_0;                // CSN low, initialize SPI communication...
	SPI_RW(reg);            // Select register to read from..
	reg_val = SPI_RW(0);    // ..then read registervalue
	CSN_1;                // CSN high, terminate SPI communication

	return(reg_val);        // return register value
}


uint SPI_RW_Reg(uchar reg, uchar value)
{
	uint status;

	CSN_0;                   	// CSN low, init SPI transaction
	status = SPI_RW(reg);      	// select register
	SPI_RW(value);             	// ..and write value to it..
	CSN_1;                   	// CSN high again

	return(status);            // return nRF24L01 status uchar
}


uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;

	CSN_0;                    		// Set CSN low, init SPI tranaction
	status = SPI_RW(reg);       		// Select register to write to and read status uchar

	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
		pBuf[uchar_ctr] = SPI_RW(0);    //

	CSN_1;

	return(status);                    // return nRF24L01 status uchar
}

uint SPI_Write_Buf(uchar reg,const uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	CSN_0;            //SPIʹ��
	status = SPI_RW(reg);
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI_RW(*pBuf++);
	CSN_1;           //�ر�SPI
	return(status);    //
}

void SetRX_Mode(void)
{
	CE_0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	CE_1;
	Delay(13);    //��ʱ����̫��
}

unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	sta = SPI_Read(STATUS);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	if(RX_DR)				// �ж��Ƿ���յ�����   ////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
	    CE_0; 			//SPIʹ��
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;			//��ȡ������ɱ�־
	}
	SPI_RW_Reg(WRITE_REG+STATUS,sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	return revale;
}

void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	uint const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���ص�ַ
//	uint const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���յ�ַ
	CE_0;																//StandBy Iģʽ
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); 	// װ�ؽ��ն˵�ַ
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 	// װ������
//	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 					// IRQ�շ�����ж���Ӧ��16λCRC��������
	CE_1;		 														//�ø�CE���������ݷ���
	Delay(1);
}

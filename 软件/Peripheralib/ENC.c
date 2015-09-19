/*
 * ENC.c
 *
 *  Created on: 2015-4-29
 *      Author: Authuir
 */

#include "ENC.h"

#define Gal_Reg(Reg) temps=ENC_Read(Reg)

uint8_t ENC28J60BANK;
uint8_t DOSD;
static uint32_t NextPacketPtr;

static void delayms_ENC(uint32_t secs)
{
	SysCtlDelay(SysCtlClockGet()/3000*secs);
}

static void delayus_ENC(uint32_t secs)
{
	SysCtlDelay(SysCtlClockGet()/3000000*secs);
}
/*
static void delayms_ENC(uint8_t d)
{
	int i,j;
	i=NextPacketPtr;
	for (i=0;i<d;i++)
		for (j=0;j<500;j++);
}*/

static void delay_ENC()
{
/*	int i,j;
	for (i=0;i<1;i++)
		for (j=0;j<50;j++);*/
	delayus_ENC(2);
}

static uint8_t SPI_R_W(uint8_t Data)
{
	uint8_t i,rtn=0;
	for (i=0;i<8;i++)
	{
		rtn = rtn << 1;
		SCK_0;
		delay_ENC();
		if( (Data&0x80) == 0x80 )
			SI_1;
		else
			SI_0;
		SCK_1;
		rtn += SO_R;
		delay_ENC();
		Data = Data << 1;
	}
	return rtn;
}

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

uint8_t ENC_Read_ETH(uint8_t In)
{
	CS_0;
	delay_ENC();
	SPI_R_W(In);
	In = SPI_R_W(0xff);
	CS_1;
	return In;
}


void ENC_Write_ETH(uint8_t ADDR,uint8_t Val)
{
	ADDR = ADDR + 0x40;
	CS_0;
	delay_ENC();
	SPI_R_W(ADDR);
	SPI_R_W(Val);
	CS_1;
}

uint8_t ENC_Read_Op(uint8_t op,uint8_t addr)
{
	uint8_t i,rtn=0;
	uint8_t dat=0;
	CS_0;
	dat=op|(addr&ADDR_MASK);
	for (i=0;i<8;i++)
	{
		rtn = rtn << 1;
		SCK_0;
		delay_ENC();
		rtn += SO_R;
		if( (dat&0x80) == 0x80 )
			SI_1;
		else
			SI_0;
		SCK_1;

		delay_ENC();
		dat = dat << 1;
	}
	for (i=0;i<8;i++)
	{
		rtn = rtn << 1;
		SCK_0;
		delay_ENC();
		rtn += SO_R;
		if( (0xFF&0x80) == 0x80 )
			SI_1;
		else
			SI_0;
		SCK_1;
		delay_ENC();
	}
	dat=rtn;
	//����Ƕ�ȡMAC/MII�Ĵ���,��ڶ��ζ��������ݲ�����ȷ��,���ֲ�29ҳ
 	if(addr&0x80)
 	{
 		for (i=0;i<8;i++)
 		{
 			rtn = rtn << 1;
 			SCK_0;
 			delay_ENC();
 			if( (0xFF&0x80) == 0x80 )
 				SI_1;
 			else
 				SI_0;
 			SCK_1;
 			rtn += SO_R;
 			delay_ENC();
 		}
 		dat=rtn;
 	}
 	CS_1;
	return dat;
}

void ENC_Write_Op(uint8_t op,uint8_t addr,uint8_t data)
{
	uint8_t dat = 0;
	CS_0;
	dat=op|(addr&ADDR_MASK);
	SPI_R_W(dat);
	SPI_R_W(data);
	CS_1;
}

void ENC_Read_Buf(uint32_t len,uint8_t* data)
{
	CS_0;
	SPI_R_W(ENC28J60_READ_BUF_MEM);
	while(len)
	{
		len--;
		*data=(uint8_t)SPI_R_W(0);
		data++;
	}
	*data='\0';
	CS_1;
}

void ENC_Write_Buf(uint32_t len,uint8_t* data)
{
	CS_0;
	SPI_R_W(ENC28J60_WRITE_BUF_MEM);
	while(len)
	{
		len--;
		SPI_R_W(*data);
		data++;
	}
	CS_1;
}

void ENC_Set_Bank(uint8_t bank)
{
	if((bank&BANK_MASK)!=ENC28J60BANK)//�͵�ǰbank��һ�µ�ʱ��,������
	{
		ENC_Write_Op(ENC28J60_BIT_FIELD_CLR,ECON1,(ECON1_BSEL1|ECON1_BSEL0));
		ENC_Write_Op(ENC28J60_BIT_FIELD_SET,ECON1,(bank&BANK_MASK)>>5);
		ENC28J60BANK=(bank&BANK_MASK);
	}
}

uint8_t ENC_Read(uint8_t addr)
{
	ENC_Set_Bank(addr);//����BANK
	return ENC_Read_Op(ENC28J60_READ_CTRL_REG,addr);
}

void ENC_Write(uint8_t addr,uint8_t data)
{
	ENC_Set_Bank(addr);
	ENC_Write_Op(ENC28J60_WRITE_CTRL_REG,addr,data);
}

void ENC_PHY_Write(uint8_t addr,uint32_t data)
{
	uint16_t retry=0;
	ENC_Write(MIREGADR,addr);	//����PHY�Ĵ�����ַ
	ENC_Write(MIWRL,data);		//д������
	ENC_Write(MIWRH,data>>8);
	while((ENC_Read(MISTAT)&MISTAT_BUSY)&&retry<0XFFF)retry++;//�ȴ�д��PHY����
}

uint8_t ENC_Init(uint8_t* macaddr)
{
	uint16_t retry=0;
	uint8_t temps;
	RST_0;			//��λENC28J60
	delayms_ENC(100);
	RST_1;			//��λ����
	delayms_ENC(100);
	ENC_Write_Op(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);//�����λ
	Gal_Reg(ESTAT);
	while(!(temps&ESTAT_CLKRDY)&&retry<500)//�ȴ�ʱ���ȶ�
	{
		ENC_Write_ETH(EIE,retry);
		Gal_Reg(ESTAT);
		retry++;
		delayms_ENC(10);
	};
	if(retry>=500)return 1;//ENC28J60��ʼ��ʧ��
	// do bank 0 stuff
	// initialize receive buffer
	// 16-bit transfers,must write low byte first
	// set receive buffer start address	   ���ý��ջ�������ַ  8K�ֽ�����
	NextPacketPtr=RXSTART_INIT;
	DOSD=ENC_Read(ECON1);
	// Rx start
	//���ջ�������һ��Ӳ�������ѭ��FIFO ���������ɡ�
	//�Ĵ�����ERXSTH:ERXSTL ��ERXNDH:ERXNDL ��
	//Ϊָ�룬���建���������������ڴ洢���е�λ�á�
	//ERXST��ERXNDָ����ֽھ�������FIFO�������ڡ�
	//������̫���ӿڽ��������ֽ�ʱ����Щ�ֽڱ�˳��д��
	//���ջ������� ���ǵ�д����ERXND ָ��Ĵ洢��Ԫ
	//��Ӳ�����Զ������յ���һ�ֽ�д����ERXST ָ��
	//�Ĵ洢��Ԫ�� ��˽���Ӳ��������д��FIFO ����ĵ�
	//Ԫ��
	//���ý�����ʼ�ֽ�
	ENC_Write(ERXSTL,RXSTART_INIT&0xFF);Gal_Reg(ERXSTL);
	ENC_Write(ERXSTH,RXSTART_INIT>>8);Gal_Reg(ERXSTH);
	//ERXWRPTH:ERXWRPTL �Ĵ�������Ӳ����FIFO ��
	//���ĸ�λ��д������յ����ֽڡ� ָ����ֻ���ģ��ڳ�
	//�����յ�һ�����ݰ���Ӳ�����Զ�����ָ�롣 ָ���
	//�����ж�FIFO ��ʣ��ռ�Ĵ�С  8K-1500��
	//���ý��ն�ָ���ֽ�
	ENC_Write(ERXRDPTL,RXSTART_INIT&0xFF);
	Gal_Reg(ERXRDPTL);
	ENC_Write(ERXRDPTH,RXSTART_INIT>>8);
	Gal_Reg(ERXRDPTH);
	//���ý��ս����ֽ�
	ENC_Write(ERXNDL,RXSTOP_INIT&0xFF);
	Gal_Reg(ERXNDL);
	ENC_Write(ERXNDH,RXSTOP_INIT>>8);
	Gal_Reg(ERXNDH);
	//���÷�����ʼ�ֽ�
	ENC_Write(ETXSTL,TXSTART_INIT&0xFF);
	Gal_Reg(ETXSTL);
	ENC_Write(ETXSTH,TXSTART_INIT>>8);
	Gal_Reg(ETXSTH);
	//���÷��ͽ����ֽ�
	ENC_Write(ETXNDL,TXSTOP_INIT&0xFF);
	Gal_Reg(ETXNDL);
	ENC_Write(ETXNDH,TXSTOP_INIT>>8);
	Gal_Reg(ETXNDH);
	// do bank 1 stuff,packet filter:
	// For broadcast packets we allow only ARP packtets
	// All other packets should be unicast only for our mac (MAADR)
	//
	// The pattern to match on is therefore
	// Type     ETH.DST
	// ARP      BROADCAST
	// 06 08 -- ff ff ff ff ff ff -> ip checksum for theses bytes=f7f9
	// in binary these poitions are:11 0000 0011 1111
	// This is hex 303F->EPMM0=0x3f,EPMM1=0x30
	//���չ�����
	//UCEN������������ʹ��λ
	//��ANDOR = 1 ʱ��
	//1 = Ŀ���ַ�뱾��MAC ��ַ��ƥ������ݰ���������
	//0 = ��ֹ������
	//��ANDOR = 0 ʱ��
	//1 = Ŀ���ַ�뱾��MAC ��ַƥ������ݰ��ᱻ����
	//0 = ��ֹ������
	//CRCEN���������CRC У��ʹ��λ
	//1 = ����CRC ��Ч�����ݰ�����������
	//0 = ������CRC �Ƿ���Ч
	//PMEN����ʽƥ�������ʹ��λ
	//��ANDOR = 1 ʱ��
	//1 = ���ݰ�������ϸ�ʽƥ�����������򽫱�����
	//0 = ��ֹ������
	//��ANDOR = 0 ʱ��
	//1 = ���ϸ�ʽƥ�����������ݰ���������
	//0 = ��ֹ������
	DOSD=ENC_Read(ECON1);
	ENC_Write(ERXFCON,ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN);
	Gal_Reg(ERXFCON);
	DOSD=ENC_Read(ECON1);
	ENC_Write(EPMM0,0x3f);
	Gal_Reg(EPMM0);
	ENC_Write(EPMM1,0x30);
	Gal_Reg(EPMM1);
	ENC_Write(EPMCSL,0xf9);
	Gal_Reg(EPMCSL);
	ENC_Write(EPMCSH,0xf7);
	Gal_Reg(EPMCSH);

	// do bank 2 stuff
	// enable MAC receive
	//bit 0 MARXEN��MAC ����ʹ��λ
	//1 = ����MAC �������ݰ�
	//0 = ��ֹ���ݰ�����
	//bit 3 TXPAUS����ͣ����֡����ʹ��λ
	//1 = ����MAC ������ͣ����֡������ȫ˫��ģʽ�µ��������ƣ�
	//0 = ��ֹ��ͣ֡����
	//bit 2 RXPAUS����ͣ����֡����ʹ��λ
	//1 = �����յ���ͣ����֡ʱ����ֹ���ͣ�����������
	//0 = ���Խ��յ�����ͣ����֡
	ENC_Write(MACON1,MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
	Gal_Reg(MACON1);
	DOSD=ENC_Read(ECON1);
	ENC_Write(MACON1,MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
	Gal_Reg(MACON1);
	DOSD=ENC_Read(ECON1);
	// bring MAC out of reset
	//��MACON2 �е�MARST λ���㣬ʹMAC �˳���λ״̬��
	ENC_Write(MACON2,0x00);
	Gal_Reg(MACON2);

	// enable automatic padding to 60bytes and CRC operations
	//bit 7-5 PADCFG2:PACDFG0���Զ�����CRC ����λ
	//111 = ��0 ������ж�֡��64 �ֽڳ�����׷��һ����Ч��CRC
	//110 = ���Զ�����֡
	//101 = MAC �Զ�������8100h �����ֶε�VLAN Э��֡�����Զ���䵽64 �ֽڳ��������
	//��VLAN ֡���������60 �ֽڳ�������Ҫ׷��һ����Ч��CRC
	//100 = ���Զ�����֡
	//011 = ��0 ������ж�֡��64 �ֽڳ�����׷��һ����Ч��CRC
	//010 = ���Զ�����֡
	//001 = ��0 ������ж�֡��60 �ֽڳ�����׷��һ����Ч��CRC
	//000 = ���Զ�����֡
	//bit 4 TXCRCEN������CRC ʹ��λ
	//1 = ����PADCFG��Σ�MAC�����ڷ���֡��ĩβ׷��һ����Ч��CRC�� ���PADCFG�涨Ҫ
	//׷����Ч��CRC������뽫TXCRCEN ��1��
	//0 = MAC����׷��CRC�� ������4 ���ֽڣ����������Ч��CRC �򱨸������״̬������
	//bit 0 FULDPX��MAC ȫ˫��ʹ��λ
	//1 = MAC������ȫ˫��ģʽ�¡� PHCON1.PDPXMD λ������1��
	//0 = MAC�����ڰ�˫��ģʽ�¡� PHCON1.PDPXMD λ�������㡣
	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,MACON3,MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN|MACON3_FULDPX);
	// set inter-frame gap (non-back-to-back)
	//���÷Ǳ��Ա��������Ĵ����ĵ��ֽ�
	//MAIPGL�� �����Ӧ��ʹ��12h ��̸üĴ�����
	//���ʹ�ð�˫��ģʽ��Ӧ��̷Ǳ��Ա�������
	//�Ĵ����ĸ��ֽ�MAIPGH�� �����Ӧ��ʹ��0Ch
	//��̸üĴ�����
	ENC_Write(MAIPGL,0x12);
	Gal_Reg(MAIPGL);
	ENC_Write(MAIPGH,0x0C);
	Gal_Reg(MAIPGH);
	// set inter-frame gap (back-to-back)
	//���ñ��Ա��������Ĵ���MABBIPG����ʹ��
	//ȫ˫��ģʽʱ�������Ӧ��ʹ��15h ��̸üĴ�
	//������ʹ�ð�˫��ģʽʱ��ʹ��12h ���б�̡�
	ENC_Write(MABBIPG,0x15);
	Gal_Reg(MABBIPG);
	// Set the maximum packet size which the controller will accept
	// Do not send packets longer than MAX_FRAMELEN:
	// ���֡����  1500
	ENC_Write(MAMXFLL,MAX_FRAMELEN&0xFF);
	Gal_Reg(MAMXFLL);
	ENC_Write(MAMXFLH,MAX_FRAMELEN>>8);
	Gal_Reg(MAMXFLH);
	// do bank 3 stuff
	// write MAC address
	// NOTE: MAC address in ENC28J60 is byte-backward
	//����MAC��ַ
	ENC_Write(MAADR5,macaddr[0]);
	ENC_Write(MAADR4,macaddr[1]);
	ENC_Write(MAADR3,macaddr[2]);
	ENC_Write(MAADR2,macaddr[3]);
	ENC_Write(MAADR1,macaddr[4]);
	ENC_Write(MAADR0,macaddr[5]);
	//����PHYΪȫ˫��  LEDBΪ������
	ENC_PHY_Write(PHCON1,PHCON1_PDPXMD);
	// no loopback of transmitted frames	 ��ֹ����
	//HDLDIS��PHY ��˫�����ؽ�ֹλ
	//��PHCON1.PDPXMD = 1 ��PHCON1.PLOOPBK = 1 ʱ��
	//��λ�ɱ����ԡ�
	//��PHCON1.PDPXMD = 0 ��PHCON1.PLOOPBK = 0 ʱ��
	//1 = Ҫ���͵����ݽ�ͨ��˫���߽ӿڷ���
	//0 = Ҫ���͵����ݻỷ�ص�MAC ��ͨ��˫���߽ӿڷ���
	ENC_PHY_Write(PHCON2,PHCON2_HDLDIS);
	// switch to bank 0
	//ECON1 �Ĵ���
	//�Ĵ���3-1 ��ʾΪECON1 �Ĵ����������ڿ���
	//ENC28J60 ����Ҫ���ܡ� ECON1 �а�������ʹ�ܡ���
	//������DMA ���ƺʹ洢��ѡ��λ��
	ENC_Set_Bank(ECON1);
	// enable interrutps
	//EIE�� ��̫���ж�����Ĵ���
	//bit 7 INTIE�� ȫ��INT �ж�����λ
	//1 = �����ж��¼�����INT ����
	//0 = ��ֹ����INT ���ŵĻ������ʼ�ձ�����Ϊ�ߵ�ƽ��
	//bit 6 PKTIE�� �������ݰ��������ж�����λ
	//1 = ����������ݰ��������ж�
	//0 = ��ֹ�������ݰ��������ж�
	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,EIE,EIE_INTIE|EIE_PKTIE);
	// enable packet reception
	//bit 2 RXEN������ʹ��λ
	//1 = ͨ����ǰ�����������ݰ�����д����ջ�����
	//0 = �������н��յ����ݰ�
	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,ECON1,ECON1_RXEN);

	//�������޸���һ�£���Ϊʼ�ն�����MA�Ĵ�����ֵ
	/*if(ENC_Read(MAADR5)== macaddr[0])return 0;//��ʼ���ɹ�
	else return 1;*/
	return 0;
}

//��ȡEREVID
uint8_t ENC_Get_EREVID(void)
{
	//��EREVID ��Ҳ�洢�˰汾��Ϣ�� EREVID ��һ��ֻ����
	//�ƼĴ���������һ��5 λ��ʶ����������ʶ�����ض���Ƭ
	//�İ汾��
	return ENC_Read(EREVID);
}
#include "uip/uip.h"
//ͨ��ENC28J60�������ݰ�������
//len:���ݰ���С
//packet:���ݰ�
void ENC_Packet_Send(uint32_t len,uint8_t* packet)
{
	//���÷��ͻ�������ַдָ�����
	ENC_Write(EWRPTL,TXSTART_INIT&0xFF);
	ENC_Write(EWRPTH,TXSTART_INIT>>8);
	//����TXNDָ�룬�Զ�Ӧ���������ݰ���С
	ENC_Write(ETXNDL,(TXSTART_INIT+len)&0xFF);
	ENC_Write(ETXNDH,(TXSTART_INIT+len)>>8);
	//дÿ�������ֽڣ�0x00��ʾʹ��macon3�����ã�
	ENC_Write_Op(ENC28J60_WRITE_BUF_MEM,0,0x00);
	//�������ݰ������ͻ�����
	//printf("len:%d\r\n",len);	//���ӷ������ݳ���
 	ENC_Write_Buf(len,packet);
 	//�������ݵ�����
	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,ECON1,ECON1_TXRTS);
	//��λ�����߼������⡣�μ�Rev. B4 Silicon Errata point 12.
	if((ENC_Read(EIR)&EIR_TXERIF))ENC_Write_Op(ENC28J60_BIT_FIELD_CLR,ECON1,ECON1_TXRTS);
}
//�������ȡһ�����ݰ�����
//maxlen:���ݰ����������ճ���
//packet:���ݰ�������
//����ֵ:�յ������ݰ�����(�ֽ�)
uint32_t ENC_Packet_Receive(uint32_t maxlen,uint8_t* packet)
{
	uint32_t rxstat;
	uint32_t len;
	if(ENC_Read(EPKTCNT)==0)return 0;  //�Ƿ��յ����ݰ�?
	//���ý��ջ�������ָ��
	ENC_Write(ERDPTL,(NextPacketPtr));
	ENC_Write(ERDPTH,(NextPacketPtr)>>8);
	// ����һ������ָ��
	NextPacketPtr=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0);
	NextPacketPtr|=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0)<<8;
	//�����ĳ���
	len=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0);
	len|=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0)<<8;
 	len-=4; //ȥ��CRC����
	//��ȡ����״̬
	rxstat=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0);
	rxstat|=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0)<<8;
	//���ƽ��ճ���
	if (len>maxlen-1)len=maxlen-1;
	//���CRC�ͷ��Ŵ���
	// ERXFCON.CRCENΪĬ������,һ�����ǲ���Ҫ���.
	if((rxstat&0x80)==0)len=0;//��Ч
	else ENC_Read_Buf(len,packet);//�ӽ��ջ������и������ݰ�
	//RX��ָ���ƶ�����һ�����յ������ݰ��Ŀ�ʼλ��
	//���ͷ����ǸղŶ��������ڴ�
	ENC_Write(ERXRDPTL,(NextPacketPtr));
	ENC_Write(ERXRDPTH,(NextPacketPtr)>>8);
	//�ݼ����ݰ���������־�����Ѿ��õ��������
 	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,ECON2,ECON2_PKTDEC);
	return(len);
}

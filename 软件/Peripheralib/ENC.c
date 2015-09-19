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
	//如果是读取MAC/MII寄存器,则第二次读到的数据才是正确的,见手册29页
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
	if((bank&BANK_MASK)!=ENC28J60BANK)//和当前bank不一致的时候,才设置
	{
		ENC_Write_Op(ENC28J60_BIT_FIELD_CLR,ECON1,(ECON1_BSEL1|ECON1_BSEL0));
		ENC_Write_Op(ENC28J60_BIT_FIELD_SET,ECON1,(bank&BANK_MASK)>>5);
		ENC28J60BANK=(bank&BANK_MASK);
	}
}

uint8_t ENC_Read(uint8_t addr)
{
	ENC_Set_Bank(addr);//设置BANK
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
	ENC_Write(MIREGADR,addr);	//设置PHY寄存器地址
	ENC_Write(MIWRL,data);		//写入数据
	ENC_Write(MIWRH,data>>8);
	while((ENC_Read(MISTAT)&MISTAT_BUSY)&&retry<0XFFF)retry++;//等待写入PHY结束
}

uint8_t ENC_Init(uint8_t* macaddr)
{
	uint16_t retry=0;
	uint8_t temps;
	RST_0;			//复位ENC28J60
	delayms_ENC(100);
	RST_1;			//复位结束
	delayms_ENC(100);
	ENC_Write_Op(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);//软件复位
	Gal_Reg(ESTAT);
	while(!(temps&ESTAT_CLKRDY)&&retry<500)//等待时钟稳定
	{
		ENC_Write_ETH(EIE,retry);
		Gal_Reg(ESTAT);
		retry++;
		delayms_ENC(10);
	};
	if(retry>=500)return 1;//ENC28J60初始化失败
	// do bank 0 stuff
	// initialize receive buffer
	// 16-bit transfers,must write low byte first
	// set receive buffer start address	   设置接收缓冲区地址  8K字节容量
	NextPacketPtr=RXSTART_INIT;
	DOSD=ENC_Read(ECON1);
	// Rx start
	//接收缓冲器由一个硬件管理的循环FIFO 缓冲器构成。
	//寄存器对ERXSTH:ERXSTL 和ERXNDH:ERXNDL 作
	//为指针，定义缓冲器的容量和其在存储器中的位置。
	//ERXST和ERXND指向的字节均包含在FIFO缓冲器内。
	//当从以太网接口接收数据字节时，这些字节被顺序写入
	//接收缓冲器。 但是当写入由ERXND 指向的存储单元
	//后，硬件会自动将接收的下一字节写入由ERXST 指向
	//的存储单元。 因此接收硬件将不会写入FIFO 以外的单
	//元。
	//设置接收起始字节
	ENC_Write(ERXSTL,RXSTART_INIT&0xFF);Gal_Reg(ERXSTL);
	ENC_Write(ERXSTH,RXSTART_INIT>>8);Gal_Reg(ERXSTH);
	//ERXWRPTH:ERXWRPTL 寄存器定义硬件向FIFO 中
	//的哪个位置写入其接收到的字节。 指针是只读的，在成
	//功接收到一个数据包后，硬件会自动更新指针。 指针可
	//用于判断FIFO 内剩余空间的大小  8K-1500。
	//设置接收读指针字节
	ENC_Write(ERXRDPTL,RXSTART_INIT&0xFF);
	Gal_Reg(ERXRDPTL);
	ENC_Write(ERXRDPTH,RXSTART_INIT>>8);
	Gal_Reg(ERXRDPTH);
	//设置接收结束字节
	ENC_Write(ERXNDL,RXSTOP_INIT&0xFF);
	Gal_Reg(ERXNDL);
	ENC_Write(ERXNDH,RXSTOP_INIT>>8);
	Gal_Reg(ERXNDH);
	//设置发送起始字节
	ENC_Write(ETXSTL,TXSTART_INIT&0xFF);
	Gal_Reg(ETXSTL);
	ENC_Write(ETXSTH,TXSTART_INIT>>8);
	Gal_Reg(ETXSTH);
	//设置发送结束字节
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
	//接收过滤器
	//UCEN：单播过滤器使能位
	//当ANDOR = 1 时：
	//1 = 目标地址与本地MAC 地址不匹配的数据包将被丢弃
	//0 = 禁止过滤器
	//当ANDOR = 0 时：
	//1 = 目标地址与本地MAC 地址匹配的数据包会被接受
	//0 = 禁止过滤器
	//CRCEN：后过滤器CRC 校验使能位
	//1 = 所有CRC 无效的数据包都将被丢弃
	//0 = 不考虑CRC 是否有效
	//PMEN：格式匹配过滤器使能位
	//当ANDOR = 1 时：
	//1 = 数据包必须符合格式匹配条件，否则将被丢弃
	//0 = 禁止过滤器
	//当ANDOR = 0 时：
	//1 = 符合格式匹配条件的数据包将被接受
	//0 = 禁止过滤器
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
	//bit 0 MARXEN：MAC 接收使能位
	//1 = 允许MAC 接收数据包
	//0 = 禁止数据包接收
	//bit 3 TXPAUS：暂停控制帧发送使能位
	//1 = 允许MAC 发送暂停控制帧（用于全双工模式下的流量控制）
	//0 = 禁止暂停帧发送
	//bit 2 RXPAUS：暂停控制帧接收使能位
	//1 = 当接收到暂停控制帧时，禁止发送（正常操作）
	//0 = 忽略接收到的暂停控制帧
	ENC_Write(MACON1,MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
	Gal_Reg(MACON1);
	DOSD=ENC_Read(ECON1);
	ENC_Write(MACON1,MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
	Gal_Reg(MACON1);
	DOSD=ENC_Read(ECON1);
	// bring MAC out of reset
	//将MACON2 中的MARST 位清零，使MAC 退出复位状态。
	ENC_Write(MACON2,0x00);
	Gal_Reg(MACON2);

	// enable automatic padding to 60bytes and CRC operations
	//bit 7-5 PADCFG2:PACDFG0：自动填充和CRC 配置位
	//111 = 用0 填充所有短帧至64 字节长，并追加一个有效的CRC
	//110 = 不自动填充短帧
	//101 = MAC 自动检测具有8100h 类型字段的VLAN 协议帧，并自动填充到64 字节长。如果不
	//是VLAN 帧，则填充至60 字节长。填充后还要追加一个有效的CRC
	//100 = 不自动填充短帧
	//011 = 用0 填充所有短帧至64 字节长，并追加一个有效的CRC
	//010 = 不自动填充短帧
	//001 = 用0 填充所有短帧至60 字节长，并追加一个有效的CRC
	//000 = 不自动填充短帧
	//bit 4 TXCRCEN：发送CRC 使能位
	//1 = 不管PADCFG如何，MAC都会在发送帧的末尾追加一个有效的CRC。 如果PADCFG规定要
	//追加有效的CRC，则必须将TXCRCEN 置1。
	//0 = MAC不会追加CRC。 检查最后4 个字节，如果不是有效的CRC 则报告给发送状态向量。
	//bit 0 FULDPX：MAC 全双工使能位
	//1 = MAC工作在全双工模式下。 PHCON1.PDPXMD 位必须置1。
	//0 = MAC工作在半双工模式下。 PHCON1.PDPXMD 位必须清零。
	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,MACON3,MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN|MACON3_FULDPX);
	// set inter-frame gap (non-back-to-back)
	//配置非背对背包间间隔寄存器的低字节
	//MAIPGL。 大多数应用使用12h 编程该寄存器。
	//如果使用半双工模式，应编程非背对背包间间隔
	//寄存器的高字节MAIPGH。 大多数应用使用0Ch
	//编程该寄存器。
	ENC_Write(MAIPGL,0x12);
	Gal_Reg(MAIPGL);
	ENC_Write(MAIPGH,0x0C);
	Gal_Reg(MAIPGH);
	// set inter-frame gap (back-to-back)
	//配置背对背包间间隔寄存器MABBIPG。当使用
	//全双工模式时，大多数应用使用15h 编程该寄存
	//器，而使用半双工模式时则使用12h 进行编程。
	ENC_Write(MABBIPG,0x15);
	Gal_Reg(MABBIPG);
	// Set the maximum packet size which the controller will accept
	// Do not send packets longer than MAX_FRAMELEN:
	// 最大帧长度  1500
	ENC_Write(MAMXFLL,MAX_FRAMELEN&0xFF);
	Gal_Reg(MAMXFLL);
	ENC_Write(MAMXFLH,MAX_FRAMELEN>>8);
	Gal_Reg(MAMXFLH);
	// do bank 3 stuff
	// write MAC address
	// NOTE: MAC address in ENC28J60 is byte-backward
	//设置MAC地址
	ENC_Write(MAADR5,macaddr[0]);
	ENC_Write(MAADR4,macaddr[1]);
	ENC_Write(MAADR3,macaddr[2]);
	ENC_Write(MAADR2,macaddr[3]);
	ENC_Write(MAADR1,macaddr[4]);
	ENC_Write(MAADR0,macaddr[5]);
	//配置PHY为全双工  LEDB为拉电流
	ENC_PHY_Write(PHCON1,PHCON1_PDPXMD);
	// no loopback of transmitted frames	 禁止环回
	//HDLDIS：PHY 半双工环回禁止位
	//当PHCON1.PDPXMD = 1 或PHCON1.PLOOPBK = 1 时：
	//此位可被忽略。
	//当PHCON1.PDPXMD = 0 且PHCON1.PLOOPBK = 0 时：
	//1 = 要发送的数据仅通过双绞线接口发出
	//0 = 要发送的数据会环回到MAC 并通过双绞线接口发出
	ENC_PHY_Write(PHCON2,PHCON2_HDLDIS);
	// switch to bank 0
	//ECON1 寄存器
	//寄存器3-1 所示为ECON1 寄存器，它用于控制
	//ENC28J60 的主要功能。 ECON1 中包含接收使能、发
	//送请求、DMA 控制和存储区选择位。
	ENC_Set_Bank(ECON1);
	// enable interrutps
	//EIE： 以太网中断允许寄存器
	//bit 7 INTIE： 全局INT 中断允许位
	//1 = 允许中断事件驱动INT 引脚
	//0 = 禁止所有INT 引脚的活动（引脚始终被驱动为高电平）
	//bit 6 PKTIE： 接收数据包待处理中断允许位
	//1 = 允许接收数据包待处理中断
	//0 = 禁止接收数据包待处理中断
	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,EIE,EIE_INTIE|EIE_PKTIE);
	// enable packet reception
	//bit 2 RXEN：接收使能位
	//1 = 通过当前过滤器的数据包将被写入接收缓冲器
	//0 = 忽略所有接收的数据包
	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,ECON1,ECON1_RXEN);

	//在这里修改了一下，因为始终读不出MA寄存器的值
	/*if(ENC_Read(MAADR5)== macaddr[0])return 0;//初始化成功
	else return 1;*/
	return 0;
}

//读取EREVID
uint8_t ENC_Get_EREVID(void)
{
	//在EREVID 内也存储了版本信息。 EREVID 是一个只读控
	//制寄存器，包含一个5 位标识符，用来标识器件特定硅片
	//的版本号
	return ENC_Read(EREVID);
}
#include "uip/uip.h"
//通过ENC28J60发送数据包到网络
//len:数据包大小
//packet:数据包
void ENC_Packet_Send(uint32_t len,uint8_t* packet)
{
	//设置发送缓冲区地址写指针入口
	ENC_Write(EWRPTL,TXSTART_INIT&0xFF);
	ENC_Write(EWRPTH,TXSTART_INIT>>8);
	//设置TXND指针，以对应给定的数据包大小
	ENC_Write(ETXNDL,(TXSTART_INIT+len)&0xFF);
	ENC_Write(ETXNDH,(TXSTART_INIT+len)>>8);
	//写每包控制字节（0x00表示使用macon3的设置）
	ENC_Write_Op(ENC28J60_WRITE_BUF_MEM,0,0x00);
	//复制数据包到发送缓冲区
	//printf("len:%d\r\n",len);	//监视发送数据长度
 	ENC_Write_Buf(len,packet);
 	//发送数据到网络
	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,ECON1,ECON1_TXRTS);
	//复位发送逻辑的问题。参见Rev. B4 Silicon Errata point 12.
	if((ENC_Read(EIR)&EIR_TXERIF))ENC_Write_Op(ENC28J60_BIT_FIELD_CLR,ECON1,ECON1_TXRTS);
}
//从网络获取一个数据包内容
//maxlen:数据包最大允许接收长度
//packet:数据包缓存区
//返回值:收到的数据包长度(字节)
uint32_t ENC_Packet_Receive(uint32_t maxlen,uint8_t* packet)
{
	uint32_t rxstat;
	uint32_t len;
	if(ENC_Read(EPKTCNT)==0)return 0;  //是否收到数据包?
	//设置接收缓冲器读指针
	ENC_Write(ERDPTL,(NextPacketPtr));
	ENC_Write(ERDPTH,(NextPacketPtr)>>8);
	// 读下一个包的指针
	NextPacketPtr=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0);
	NextPacketPtr|=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0)<<8;
	//读包的长度
	len=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0);
	len|=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0)<<8;
 	len-=4; //去掉CRC计数
	//读取接收状态
	rxstat=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0);
	rxstat|=ENC_Read_Op(ENC28J60_READ_BUF_MEM,0)<<8;
	//限制接收长度
	if (len>maxlen-1)len=maxlen-1;
	//检查CRC和符号错误
	// ERXFCON.CRCEN为默认设置,一般我们不需要检查.
	if((rxstat&0x80)==0)len=0;//无效
	else ENC_Read_Buf(len,packet);//从接收缓冲器中复制数据包
	//RX读指针移动到下一个接收到的数据包的开始位置
	//并释放我们刚才读出过的内存
	ENC_Write(ERXRDPTL,(NextPacketPtr));
	ENC_Write(ERXRDPTH,(NextPacketPtr)>>8);
	//递减数据包计数器标志我们已经得到了这个包
 	ENC_Write_Op(ENC28J60_BIT_FIELD_SET,ECON2,ECON2_PKTDEC);
	return(len);
}

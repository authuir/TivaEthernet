/*
 * TFT.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */
#include "Common.h"

uint16_t BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ

void delay_ms(unsigned int s)
{
	SysCtlDelay(SysCtlClockGet()/10000*9);
}

void LCD_Writ_Bus(char da)   //��������д��
{
	//SPI2_RW(da);
	uint8_t i;
	for (i=0;i<8;i++)
	{
		if (da & 0x80)
			SPI2_MOSI_1;
		else
			SPI2_MOSI_0;
		SPI2_SCK_0;
		SPI2_SCK_1;
		da = da << 1;
	}
}

void LCD_WR_DATA(uint16_t da)  //��������-16λ����
{
	LCD_DC_1;
	LCD_Writ_Bus(da>>8);
	LCD_Writ_Bus(da);
}
void LCD_WR_REG(char da)
{
	LCD_DC_0;
	LCD_Writ_Bus(da);
}

void LCD_WR_REG_DATA(uint16_t reg,uint16_t da)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}

void LCD_WR_DATA8(char da) //��������-8λ����
{
    LCD_DC_1;
	LCD_Writ_Bus(da);
}

void Init_TFT()
{
	SPI2_Init();
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3);
	LCD_CS_1;
	LCD_REST_0;
	delay_ms(20);
	LCD_REST_1;
	delay_ms(20);
	LCD_CS_0;

	LCD_WR_REG(0xCB);
    LCD_WR_DATA8(0x39);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x34);
    LCD_WR_DATA8(0x02);

    LCD_WR_REG(0xCF);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0XC1);
    LCD_WR_DATA8(0X30);

    LCD_WR_REG(0xE8);
    LCD_WR_DATA8(0x85);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x78);

    LCD_WR_REG(0xEA);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0xED);
    LCD_WR_DATA8(0x64);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0X12);
    LCD_WR_DATA8(0X81);

    LCD_WR_REG(0xF7);
    LCD_WR_DATA8(0x20);

    LCD_WR_REG(0xC0);    //Power control
    LCD_WR_DATA8(0x23);   //VRH[5:0]

    LCD_WR_REG(0xC1);    //Power control
    LCD_WR_DATA8(0x10);   //SAP[2:0];BT[3:0]

    LCD_WR_REG(0xC5);    //VCM control
    LCD_WR_DATA8(0x3e); //�Աȶȵ���
    LCD_WR_DATA8(0x28);

    LCD_WR_REG(0xC7);    //VCM control2
    LCD_WR_DATA8(0x86);  //--

    LCD_WR_REG(0x36);    // Memory Access Control
    LCD_WR_DATA8(0x48); //C8	   //48 68����//28 E8 ����

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x55);

    LCD_WR_REG(0xB1);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x18);

    LCD_WR_REG(0xB6);    // Display Function Control
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x82);
    LCD_WR_DATA8(0x27);

    LCD_WR_REG(0xF2);    // 3Gamma Function Disable
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0x26);    //Gamma curve selected
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xE0);    //Set Gamma
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x31);
    LCD_WR_DATA8(0x2B);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x4E);
    LCD_WR_DATA8(0xF1);
    LCD_WR_DATA8(0x37);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0XE1);    //Set Gamma
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x11);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x31);
    LCD_WR_DATA8(0xC1);
    LCD_WR_DATA8(0x48);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x31);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x0F);

    LCD_WR_REG(0x11);    //Exit Sleep
    delay_ms(120);

    LCD_WR_REG(0x29);    //Display on
    LCD_WR_REG(0x2c);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	LCD_WR_REG(0x2a);
	LCD_WR_DATA8(x1>>8);
	LCD_WR_DATA8(x1);
	LCD_WR_DATA8(x2>>8);
	LCD_WR_DATA8(x2);
	LCD_WR_REG(0x2b);
	LCD_WR_DATA8(y1>>8);
	LCD_WR_DATA8(y1);
	LCD_WR_DATA8(y2>>8);
	LCD_WR_DATA8(y2);
	LCD_WR_REG(0x2C);
}

void LCD_Clear(uint16_t Color)
{
	uint16_t i,j;
	Address_set(0,0,LCD_W-1,LCD_H-1);
	for(i=0;i<LCD_W;i++)
		for (j=0;j<LCD_H;j++)
		{
			LCD_WR_DATA(Color);
		}
}

//����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	Address_set(x,y,x,y);		//���ù��λ��
	LCD_WR_DATA(POINT_COLOR);
}

//��һ�����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint_big(uint16_t x,uint16_t y)
{
	LCD_Fill(x-1,y-1,x+1,y+1,POINT_COLOR);
}
//��ָ�����������ָ����ɫ
//�����С:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{
	uint16_t i,j;
	Address_set(xsta,ysta,xend,yend);      //���ù��λ��
	for(i=ysta;i<=yend;i++)
	{
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//���ù��λ��
	}
}
//����
//x1,y1:�������
//x2,y2:�յ�����
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;

	delta_x=x2-x1; //������������
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; //���õ�������
	else if(delta_x==0)incx=0;//��ֱ��
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//ˮƽ��
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//�������
	{
		LCD_DrawPoint(uRow,uCol);//����
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}
//������
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)
{
	int a,b;
	int di;
	a=0;b=r;
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a);             //3
		LCD_DrawPoint(x0+b,y0-a);             //0
		LCD_DrawPoint(x0-a,y0+b);             //1
		LCD_DrawPoint(x0-b,y0-a);             //7
		LCD_DrawPoint(x0-a,y0-b);             //2
		LCD_DrawPoint(x0+b,y0+a);             //4
		LCD_DrawPoint(x0+a,y0-b);             //5
		LCD_DrawPoint(x0+a,y0+b);             //6
		LCD_DrawPoint(x0-b,y0+a);
		a++;
		//ʹ��Bresenham�㷨��Բ
		if(di<0)di +=4*a+6;
		else
		{
			di+=10+4*(a-b);
			b--;
		}
		LCD_DrawPoint(x0+a,y0+b);
	}
}

/*
 * TFT.h
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */

#ifndef TFT_H_
#define TFT_H_

 //定义LCD的尺寸
#define LCD_W 320
#define LCD_H 240

#define Screen_W 40
#define Screen_H 15

#define LCD_DC_0 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0)
#define LCD_DC_1 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2)

#define LCD_REST_0 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0)
#define LCD_REST_1 ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3)

#define LCD_CS_0 SPI2_CSN_0
#define LCD_CS_1 SPI2_CSN_1

extern char Screen[15][41];
extern uint16_t BACK_COLOR, POINT_COLOR;

void Init_TFT();
void LCD_Clear(uint16_t Color);
//画点
void LCD_DrawPoint(uint16_t x,uint16_t y);
//画一个大点
void LCD_DrawPoint_big(uint16_t x,uint16_t y);

void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void DisPlay();
uint16_t RGB_Color(uint8_t R,uint8_t G,uint8_t B);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,const char *p);
void ScreenFlush();

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#endif /* TFT_H_ */

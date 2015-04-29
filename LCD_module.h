#ifndef  __LCD_MODULE_H__
#define  __LCD_MODULE_H__


#ifndef TARGET_IS_BLIZZARD_RB1
#define TARGET_IS_BLIZZARD_RB1
#endif

#ifndef PART_TM4C123GH6PM
#define PART_TM4C123GH6PM
#endif

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"



/*************************************************************************************************
 * LCDΪJLX12864G-086,����ͨ����4����+1����λ��
 *
 * SDA����������
 * SCK������ʱ��
 * CS0��Ƭѡ,�͵�ƽƬѡ
 * CD���Ĵ���ѡ���źţ�H:���ݼĴ��� 0:ָ��Ĵ���
 * RES����λ���͵�ƽ��λ����λ��ɺ󣬻ص��ߵ�ƽ��Һ��ģ�鿪ʼ����
 *
 * PE5 <----> CS
 * PE4 <----> CD
 * PC5 <----> SCK
 * PC4 <----> SDA
 * RES ֱ�ӽ���ϵͳ�ĸ�λ��
 *
 *************************************************************************************************/
extern const uint8_t LCD_symbol_my[8][128];
extern const uint8_t LCD_ASCII[127][16];

#define CS_EQ_0() GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0x00)
#define CS_EQ_1() GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0x20)

#define CD_EQ_0() GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0x00)
#define CD_EQ_1() GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0x10)

#define SDA_EQ_0() GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x00)
#define SDA_EQ_1() GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x10)

#define SCK_EQ_0() GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0x00)
#define SCK_EQ_1() GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0x20)

void LCD_pin_init(void);
void LCD_initialization(void);
void LCD_transfer_command(uint8_t com);
void LCD_transfer_data(uint8_t data);
void LCD_clear_screen(void);
void LCD_address(uint8_t page, uint8_t column);
void LCD_full_display(void);
void LCD_Test_image(uint8_t LCD_symbol_test[][128]);
void LCD_char_16x16(uint8_t row, uint8_t column, const uint8_t *str);
void LCD_char_16x8(uint8_t row, uint8_t column, const uint8_t *str);
void LCD_num_16x8(uint8_t row, uint8_t column, uint8_t p_d, int32_t num);
void LCD_string_16x8(uint8_t row, uint8_t column, char *str);

#endif

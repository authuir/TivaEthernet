#ifndef TARGET_IS_BLIZZARD_RA1
#define TARGET_IS_BLIZZARD_RA1
#endif
#ifndef PART_TM4C123GH6PM
#define PART_TM4C123GH6PM
#endif

#include <stdint.h>
#include <stdbool.h>
#include <cmath>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "ENC.h"
#include "LCD_module.h"

//	PB4---RST	低电平有效器件复位输入。
//	PB5---CS	SPI 接口的片选输入引脚。
//	PD3---SCK	SPI 接口的时钟输入引脚。
//	PD2---SI	SPI 接口的数据输入引脚。
//	PB7---SO	SPI 接口的数据输出引脚。
//  PB6---WOL	LAN 中断唤醒输出引脚。
//  PE2---INT	INT 中断输出引脚。
//  PE3---CLK	可编程时钟输出引脚。

uint8_t temp;

uint8_t mymac[6]={0x04,0x02,0x35,0x00,0x00,0x01};

int main(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);

	ENC_Pin_Init();
	LCD_pin_init();
	LCD_initialization();
	LCD_clear_screen();
	LCD_string_16x8(1,1,"EthernetX");
	ENC_Write_ETH(EIE,0x89);
	temp = ENC_Read(EIE);
	temp = ENC_Init(mymac);

	while(ENC_Init(mymac))
	{
		LCD_string_16x8(3,1,"Error");
	}
	LCD_string_16x8(3,1,"     ");
	while (1)
	{
		ENC_Write_ETH(EIE,0x89);
		temp = ENC_Read_ETH(EIE);
		LCD_num_16x8(2,1,0,temp);
	}

}

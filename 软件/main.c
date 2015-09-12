#include "Common.h"
uint8_t TMP[256];
uint32_t TMPs[256];
uint8_t o;
int main(void) {
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_24MHZ);
    ROM_FPUEnable();
    ROM_FPULazyStackingEnable();

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	TMP[255] = 0;
	//Init_NRF24L01();
	Init_TFT();

	LCD_Clear(WHITE);
	LCD_Clear(BRED);


	while(1){
		POINT_COLOR=RED;
		for (o=119;o>1;o--)
			Draw_Circle(120,160,o);
		POINT_COLOR=BLUE;
		for (o=1;o<120;o++)
			Draw_Circle(120,160,o);
		POINT_COLOR=GRED;
		for (o=119;o>1;o--)
			Draw_Circle(120,160,o);
		POINT_COLOR=GBLUE;
		for (o=1;o<120;o++)
			Draw_Circle(120,160,o);
		POINT_COLOR=MAGENTA;
		for (o=119;o>1;o--)
			Draw_Circle(120,160,o);
		POINT_COLOR=GREEN;
		for (o=1;o<120;o++)
			Draw_Circle(120,160,o);
		POINT_COLOR=CYAN;
		for (o=119;o>1;o--)
			Draw_Circle(120,160,o);
		POINT_COLOR=YELLOW;
		for (o=1;o<120;o++)
			Draw_Circle(120,160,o);
		POINT_COLOR=BROWN;
		for (o=119;o>1;o--)
			Draw_Circle(120,160,o);
		POINT_COLOR=LIGHTBLUE;
		for (o=1;o<120;o++)
			Draw_Circle(120,160,o);
	}
}

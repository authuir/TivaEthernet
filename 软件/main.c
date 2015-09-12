#include "Common.h"
uint8_t TMP[256];
uint32_t TMPs[256];

int main(void) {
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
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
	LCD_Clear(RGB_Color(48,195,190));
	LCD_Clear(BLACK);

	//LCD_Clear(BRED);
	//DisPlay();
	POINT_COLOR = WHITE;
	strcpy(Screen[0],"   Authuir Operating System");
	strcpy(Screen[1],"[root@localhost ~]# ls");
	strcpy(Screen[2],"[root@localhost ~]# cd /");
	strcpy(Screen[3],"boot etc lost+found opt sbin srv usr");
	strcpy(Screen[4],"cfg home media proc selinux sys var");
	strcpy(Screen[5],"bin dev lib mnt root shadowsocks tmp");
	strcpy(Screen[6],"[root@localhost ~]# ");
	while(1){
		ScreenFlush();
	}
}

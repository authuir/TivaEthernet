#include "Common.h"
uint8_t TMP[256];
uint32_t TMPs[256];

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
	Init_NRF24L01();

	SPI_RW_Reg(WRITE_REG+CONFIG,0xFE);
	SPI_Read(WRITE_REG+CONFIG);

	while(1);
}

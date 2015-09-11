#include "Common.h"
uint32_t TMP[256];

void SPI_RW(uint8_t reg_val,uint32_t * reg)
{
    SSIDataPut(SSI1_BASE,reg_val);
    SSIDataGet(SSI1_BASE,reg);
}

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

	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x0;
	TMP[255] = 0;
	Init_NRF24L01();

    /*TMP[0] = 0;
    SSIEnable(SSI1_BASE);
    SPI_RW(READ_REG + TX_ADDR,TMP);
    SSIDisable(SSI1_BASE);
    while(1)
    {
        TMP[0] = READ_REG + TX_ADDR;
        SSIEnable(SSI1_BASE);
        SSIDataPut(SSI1_BASE,TMP[0]);
        SSIDataGet(SSI1_BASE,TMP);
        SSIDataPut(SSI1_BASE,0xFF);
        SSIDataGet(SSI1_BASE,TMP);
        SSIDisable(SSI1_BASE);
    }*/
}

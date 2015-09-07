/*
 * Button.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */

#include "Common.h"

void Init_Button()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
}

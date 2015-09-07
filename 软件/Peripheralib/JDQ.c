/*
 * JDQ.c
 *
 *  Created on: 2015-8-7
 *      Author: Authuir
 */

#ifndef JDQ_C_
#define JDQ_C_

#include "Common.h"

void Init_JDQ()
{
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_0,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD);
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,GPIO_PIN_0);
}

#endif /* JDQ_C_ */

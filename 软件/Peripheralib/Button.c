/*
 * Button.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */

#include "Common.h"

/************
 * ȫ�ֱ��� *
 ************/

//��ť���ŷ���ָʾ 0B00000000 ����λΪ1�����Ӧ����λΪLED���ܣ�Ϊ0��ΪButton����
uint8_t Button_LED_Direct = 0x00;

void Button_LED(uint8_t val)
{
	Button_LED_Direct = 0x07;
	if (val & 0x01)
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
	else
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);

	if (val & 0x02)
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
	else
		GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);

	if (val & 0x04)
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_PIN_7);
	else
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0);
}


/* ��ʼ���������� */
void Init_Button()
{
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x0;

	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_7);

	Button_LED(0x00);
	Button_LED(0xFF);
	Button_LED(0x00);
	Button_LED(0xFF);
	Button_LED(0x00);
	Button_LED(0xFF);
}


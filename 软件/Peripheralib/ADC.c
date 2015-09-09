/*
 * ADC.c
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */
#include "Common.h"

uint32_t ADC1Value[1],ADC2Value[1];


/*
 * ��ʼ��ADC���ź�����
 * ����ADC0��������������ΪCH1��ADC1��������������ΪCH2
 */
void Init_ADC()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1);
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);

	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);

	ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC1_BASE, 3);
    ADCIntClear(ADC1_BASE, 3);
}

/*
 * ����AD1���ŵ�ֵ
 */
void ADC1_Value_Get()
{
    //
    // Trigger the ADC conversion.
    //
    ADCProcessorTrigger(ADC0_BASE, 3);

    //
    // Wait for conversion to be completed.
    //
    while(!ADCIntStatus(ADC0_BASE, 3, false))
    {
    }

    //
    // Clear the ADC interrupt flag.
    //
    ADCIntClear(ADC0_BASE, 3);

    //
    // Read ADC Value.
    //
    ADCSequenceDataGet(ADC0_BASE, 3, ADC1Value);
}

/*
 * ����AD2���ŵ�ֵ
 */
void ADC2_Value_Get()
{
    //
    // Trigger the ADC conversion.
    //
    ADCProcessorTrigger(ADC1_BASE, 3);

    //
    // Wait for conversion to be completed.
    //
    while(!ADCIntStatus(ADC1_BASE, 3, false))
    {
    }

    //
    // Clear the ADC interrupt flag.
    //
    ADCIntClear(ADC1_BASE, 3);

    //
    // Read ADC Value.
    //
    ADCSequenceDataGet(ADC1_BASE, 3, ADC2Value);
}

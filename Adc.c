#include "Adc.h"

void ADC_Delay2us(void)		//@11.0592MHz
{
	unsigned char i;
	i = 3;
	while (--i);
}

/*----------------------------
��ȡADC���
����ֵ��ADC���
----------------------------*/
BYTE ADC_GetResult(void)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | Adc_ch | ADC_START;
    ADC_Delay2us();                    			//�ȴ�4��NOP
    while (!(ADC_CONTR & ADC_FLAG));	//�ȴ�ADCת�����
    ADC_CONTR &= ~ADC_FLAG;         		//Close ADC
    return ADC_RES;                 			//����ADC���
}

/*----------------------------
��ʼ��ADC
----------------------------*/
void ADC_Init(void)
{
	//P1.7����Ϊ�������룬��ΪAD�˿�ʹ��
	P1M0 &= ~0x80;
	P1M1 |=    0x80;

	//P1ASF = 0xff;                   		//����P1��ΪAD��
	P1ASF = P17ASF;                   	//����P1.7��ΪAD��
	ADC_RES = 0;                    		//�������Ĵ���
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
}


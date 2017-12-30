#include 	"Adc.h"
#include	"Uart.h"

void ADC_Delay2us(void)		//@11.0592MHz
{
	unsigned char i;
	i = 3;
	while (--i);
}

void ADC_Delay500ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
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
/*----------------------------
����ADC
----------------------------*/
void ADC_Test(void)
{
	BYTE		ADC_Result[3];
	
	ADC_Result[0] = ADC_GetResult();
	ADC_Result[1] = '0' + ADC_Result[0]/10;
	ADC_Result[2] = '0' + ADC_Result[1]%10;
	SendString("Current ADC Result is :");
	SendData(ADC_Result[1]);
	SendData(ADC_Result[2]);
	SendString("\r\n");
	ADC_Delay500ms();
	//�հ���Խ��Ϊ75
	while(0)
	{
		ADC_Result[0] = ADC_GetResult();
		ADC_Result[1] = '0' + ADC_Result[0]/10;
		ADC_Result[2] = '0' + ADC_Result[1]%10;
		SendString("Current ADC Result is :");
		SendData(ADC_Result[1]);
		SendData(ADC_Result[2]);
		SendString("\r\n");
		ADC_Delay500ms();
	}
}



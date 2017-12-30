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
读取ADC结果
返回值是ADC结果
----------------------------*/
BYTE ADC_GetResult(void)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | Adc_ch | ADC_START;
    ADC_Delay2us();                    			//等待4个NOP
    while (!(ADC_CONTR & ADC_FLAG));	//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         		//Close ADC
    return ADC_RES;                 			//返回ADC结果
}

/*----------------------------
初始化ADC
----------------------------*/
void ADC_Init(void)
{
	//P1.7配置为高阻输入，作为AD端口使用
	P1M0 &= ~0x80;
	P1M1 |=    0x80;

	//P1ASF = 0xff;                   		//设置P1口为AD口
	P1ASF = P17ASF;                   	//设置P1.7口为AD口
	ADC_RES = 0;                    		//清除结果寄存器
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
}
/*----------------------------
测试ADC
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
	//空板测试结果为75
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



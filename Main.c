#include "Adc.h"
#include "Stc15.h"
#include "RF433.h"
#include "Uart.h"
#include "Door.h"
#include "Battery.h"
#include "IR.h"


//--------------------------
//|	PxM1 | PxM0 |   ģʽ   |
//--------------------------
//|	 0   |  0   | ׼˫��� |
//--------------------------
//|	 0   |  1   | ǿ����   |
//--------------------------
//|	 1   |  0   | �������� |
//--------------------------
//|	 1   |  1   | ��©��� |
//--------------------------
void Main_Delay500ms()		//@11.0592MHz
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


void main(void)
{
	//��ʼ������
	Uart_Init();
	
	SendString("Uart Init Success.\r\n");
	
	//��ʼ��ADC
	ADC_Init();
	//ADC_Test();
	
	//��ʼ��RF433
	//RF433_Init();
	//RF433_Recv_Test();

	//��ʼ��������
	Door_Init();
	//Door_Test();

	//��ʼ����ص�����
	//Battery_Init();
	//Battery_Test();
	ir_init();
	ir_test();
	
	while(1)
	{
		P33 = ~P33;
		Main_Delay500ms();
		//UartSendRecvData();
	}
	
	while(1);
}










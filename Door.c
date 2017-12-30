#include "Door.h"

void Door_Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void Door_Delay500ms()		//@11.0592MHz
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

//��ʼ���˿�
void Door_Init(void)
{
	//P1.1 P1.2 P1.6 ����Ϊ׼˫���
	P1M0 &= ~0x46;
	P1M1 &= ~0x46;
	//P0.0 P0.1 ����Ϊ׼˫���
	P1M0 &= ~0x03;
	P1M1 &= ~0x03;
}

//ֹͣ
void Door_Stop(void)
{
	Door_MotorA 	= 1;
	Door_MotorB 	= 1;
	Door_Pwr_EN		= 0;
}

//����
void Door_Open(void)
{
	Door_Pwr_EN		= 1;
	Door_MotorA 	= 0;
	Door_MotorB		= 1;
	
	//���������ֹͣ
	while(Door_Open_Stop_Thethord < ADC_GetResult());
	Door_Stop();
}

//����
void Door_Close(void)
{
	Door_Pwr_EN		= 1;
	Door_MotorA 	= 1;
	Door_MotorB 	= 0;
	
	//���������ֹͣ
	while(ADC_GetResult() < Door_Close_Stop_Thethord);
	Door_Stop();
}

//�˿�A������
BYTE Door_SenseA_State(void)
{
	BYTE A,B;
	Door_SenseA =	1;
	A = Door_SenseA;
	Door_SenseA =	0;
	B = Door_SenseA;
	if(A==0&&B==0)
	 {
		return	1;
	 }
	else
		return	0;
}

//�˿�B������
BYTE Door_SenseB_State(void)
{
	BYTE A,B;
	Door_SenseB=1;
	A=Door_SenseB;
	Door_SenseB=0;
	B=Door_SenseB;
	if(A==0&&B==0)
	 {
		return	1;
	 }
	else
		return	0;
}

//���������Գ���
void Door_Test(void)
{
	BYTE	ADC_Result = 0;
	BYTE	ADC_Max = 0;
	BYTE    ADC_Min = 0;
	//���Թ��ż���ź�
	while(0)
	{
		if(Door_SenseA_State() || Door_SenseB_State())
		{
			Door_Close();
			Door_Delay500ms();
			Door_Delay500ms();
			Door_Stop();
			Door_Delay500ms();
			Door_Delay500ms();
			Door_Open();
		}
	}
	
	//���Կ���������
	while(1)
	{
		//����
		Door_Open();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		//����
		Door_Close();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
	}
	
	//���Կ���ֵ
	while(0)
	{
#if 0
		//����
		Door_Open();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		//����
		Door_Close();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		
#endif
#if 1
		//����
		Door_Close();
		ADC_Result = ADC_GetResult();
		//SendString("ADC_Result Is: ");
		SendData(ADC_Result/100 + '0');
		SendData((ADC_Result/10)%10 + '0');
		SendData(ADC_Result%10 + '0');
		SendString("\r\n");	
		/*
		if(ADC_Result > ADC_Max)
		{
			ADC_Max = ADC_Result;
			SendData(ADC_Max/100 + '0');
			SendData((ADC_Max/10)%10 + '0');
			SendData(ADC_Max%10 + '0');
			SendString("\r\n");	
		}
		*/
		//���������ֹͣ
		if(ADC_Result > Door_Close_Stop_Thethord)
		{
			Door_Stop();
			while(1);
		}
#else
		//����
		Door_Open();
		ADC_Result = ADC_GetResult();
		SendData(ADC_Result/100 + '0');
		SendData((ADC_Result/10)%10 + '0');
		SendData(ADC_Result%10 + '0');
		SendString("\r\n");	
		/*
		if(ADC_Result < ADC_Min)
		{
			ADC_Min = ADC_Result;
			SendData(ADC_Min/100 + '0');
			SendData((ADC_Min/10)%10 + '0');
			SendData(ADC_Min%10 + '0');
			SendString("\r\n");	
		}
		*/
		//���������ֹͣ
		if(ADC_Result < Door_Open_Stop_Thethord)
		{
			Door_Stop();
			while(1);
		}
#endif
	}
}


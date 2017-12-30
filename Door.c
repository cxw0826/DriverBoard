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

//初始化端口
void Door_Init(void)
{
	//P1.1 P1.2 P1.6 配置为准双向口
	P1M0 &= ~0x46;
	P1M1 &= ~0x46;
	//P0.0 P0.1 配置为准双向口
	P1M0 &= ~0x03;
	P1M1 &= ~0x03;
}

//停止
void Door_Stop(void)
{
	Door_MotorA 	= 1;
	Door_MotorB 	= 1;
	Door_Pwr_EN		= 0;
}

//开门
void Door_Open(void)
{
	Door_Pwr_EN		= 1;
	Door_MotorA 	= 0;
	Door_MotorB		= 1;
	
	//如果卡死就停止
	while(Door_Open_Stop_Thethord < ADC_GetResult());
	Door_Stop();
}

//关门
void Door_Close(void)
{
	Door_Pwr_EN		= 1;
	Door_MotorA 	= 1;
	Door_MotorB 	= 0;
	
	//如果卡死就停止
	while(ADC_GetResult() < Door_Close_Stop_Thethord);
	Door_Stop();
}

//端口A检测程序
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

//端口B检测程序
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

//开关锁测试程序
void Door_Test(void)
{
	BYTE	ADC_Result = 0;
	BYTE	ADC_Max = 0;
	BYTE    ADC_Min = 0;
	//测试关门检测信号
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
	
	//测试开关门流程
	while(1)
	{
		//开门
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
		//关门
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
	
	//测试卡死值
	while(0)
	{
#if 0
		//开门
		Door_Open();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		//关门
		Door_Close();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		Door_Delay500ms();
		
#endif
#if 1
		//关门
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
		//如果卡死就停止
		if(ADC_Result > Door_Close_Stop_Thethord)
		{
			Door_Stop();
			while(1);
		}
#else
		//开门
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
		//如果卡死就停止
		if(ADC_Result < Door_Open_Stop_Thethord)
		{
			Door_Stop();
			while(1);
		}
#endif
	}
}


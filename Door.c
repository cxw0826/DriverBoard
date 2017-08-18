#include "Door.h"

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

//开门
void Door_Open(void)
{
	Door_Pwr_EN	= 1;
	Door_MotorA 	= 0;
	Door_MotorB	= 1;
}
//关门
void Door_Close(void)
{
	Door_Pwr_EN	= 1;
	Door_MotorA 	= 1;
	Door_MotorB 	= 0;
}

//停止
void Door_Stop(void)
{
	Door_MotorA 	= 1;
	Door_MotorB 	= 1;
	Door_Pwr_EN	= 0;
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
	while(1)
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
}


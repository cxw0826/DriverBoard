#include "IR.h"

//��ʼ��
void ir_init(void)
{	
	//P0.0 P0.1����Ϊ�������룬��Ϊir�˿�ʹ��
	//P0M0 &= ~0x03;
	//P0M1 |=  0x03;
	//P0M0 &= ~0x03;
	//P0M1 &= ~0x03;
}
//IR�˿ڼ�⣬���ڵ�����1
int ir_detect(void)
{
	if (IR_Recv_Ch1 == 0 || IR_Recv_Ch2 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void ir_test(void)
{/*
	while (1)
	{
		if (ir_detect())
		{
			WorkLed = 0;
		}
		else
		{
			WorkLed = 1;
		}		
	}*/
}


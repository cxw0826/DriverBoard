#ifndef 	DOOR_H
#define	DOOR_H

#include "Stc15.h"
#include "Adc.h"
#include "Uart.h"

sbit Door_MotorA	= P1^1;	//��������ź�A
sbit Door_MotorB 	= P1^2;	//��������ź�B
sbit Door_Pwr_EN	= P1^6;	//���������Դ�����ź�
sbit Door_SenseA	= P0^1;	//���ŵ�λ����ź�A
sbit Door_SenseB 	= P0^0;	//���ŵ�λ����ź�B

#define	Door_Close_Stop_Thethord	0x82	//130
#define	Door_Open_Stop_Thethord		0x1E	//30

void  Door_Init(void);
void  Door_Open(void);
void  Door_Close(void);
void  Door_Stop(void);
BYTE  Door_SenseA_State(void);
BYTE  Door_SenseB_State(void);
void  Door_Test(void);



						






#endif


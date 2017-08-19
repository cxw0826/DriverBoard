#ifndef 	DOOR_H
#define	DOOR_H

#include "Stc15.h"
#include "Adc.h"
#include "Uart.h"

sbit Door_MotorA	= P1^1;	//开锁电机信号A
sbit Door_MotorB 	= P1^2;	//开锁电机信号B
sbit Door_Pwr_EN	= P1^6;	//开锁电机电源控制信号
sbit Door_SenseA	= P0^1;	//关门到位检测信号A
sbit Door_SenseB 	= P0^0;	//关门到位检测信号B

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


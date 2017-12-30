#ifndef _IR_H_
#define _IR_H_

#include "STC15.H"

sbit IR_Recv_Ch1 = P0^0;
sbit IR_Recv_Ch2 = P0^1;

sbit WorkLed = P3^3;

void ir_init(void);
int  ir_detect(void);
void ir_test(void);








#endif


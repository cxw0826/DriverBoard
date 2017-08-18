#include "Uart.h"

bit busy;
//串口初始化
void Uart_Init(void)
{
	//初始化P3.0 P3.1为准双向口
	P3M0 &=  ~0x03;
	P3M1 &=  ~0x03;

	SCON	= 0x50;	//8位可变波特率
	AUXR	= 0x40;	//定时器1为1T模式
	TMOD	= 0x00;	//定时器1为模式0(16位自动重载)
	TL1		= (65536 - (FOSC/4/BAUD));	//设置波特率重装值高8位
	TH1		= (65536 - (FOSC/4/BAUD))>>8;	//设置波特率重装值低8位
	TR1		= 1;	//定时器1开始启动
	ES		= 1;	//使能串口中断
	EA		= 1;
}
/*----------------------------
UART 中断服务程序
-----------------------------*/
void Uart() interrupt 4 using 1
{
	if (RI)
	{
		RI = 0;                 //清除RI位
	}
	if (TI)
	{
		TI = 0;                 //清除TI位
		busy = 0;               //清忙标志
	}
}
/*----------------------------
发送串口数据
----------------------------*/
void SendData(BYTE dat)
{
	while (busy); 	//等待前面的数据发送完成
	busy = 1;
	SBUF = dat;	//写数据到UART数据寄存器
}
/*----------------------------
发送字符串
----------------------------*/
void SendString(char *s)
{
	while (*s)	//检测字符串结束标志
	{
		SendData(*s++); 	//发送当前字符
	}
}
/*----------------------------
发送数据块
----------------------------*/
void SendBlock(char *s,char size)
{
	char i=0;
	while(i<size)
	{
		SendData(s[i++]);
	}
}




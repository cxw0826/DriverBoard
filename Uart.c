#include "Uart.h"
#include "string.h"
#include "stdlib.h"
#include "Door.h"

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
char UART1_Recv_BUF[20];
int  UART1_Recv_count = 0;
int  UART1_Recv_Finish = 1;

void Uart() interrupt 4 using 1
{
	if (TI)
	{
		TI = 0;                 //清除TI位
		busy = 0;               //清忙标志
	}

	if (RI == 1)  
	{  
		RI = 0; 
		UART1_Recv_BUF[UART1_Recv_count++] = SBUF; 
		//buffer接收够5个字符了
		if(UART1_Recv_count >= 5)
		{
			//接收buffer计数清零
			UART1_Recv_count = 0;
			//接收完成标志置位
			UART1_Recv_Finish = 1;
		}	
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
/*----------------------------
//8位累加和校验
----------------------------*/
int Check_Sum(char *dat,int size,char *sum)
{	
	if(dat == NULL || size == 0 || sum == NULL)
	{
		return 1;
	}

	*sum = 0;
	
	while(size--)
	{
		*sum+=dat[size];
	}

	return 0;
}
/*----------------------------
发送接收到的数据
主机定义从机响应方式为
	回传主机给的数据
----------------------------*/
#define	TYPE_TEST	0	//通信测试
#define	TYPE_DOOR	1	//开关门操作
#define	TYPE_MUSIC	2	//播放音乐操作
char KnownState[] = {0xAA,0x55,0x00,0x00,0xFF};
char CheckSum;
void UartSendRecvData(void)
{
	if(UART1_Recv_Finish)
	{
		//SendString(UART1_Recv_BUF);
		SendData(UART1_Recv_BUF[0]);
		SendData(UART1_Recv_BUF[1]);
		SendData(UART1_Recv_BUF[2]);
		SendData(UART1_Recv_BUF[3]);
		SendData(UART1_Recv_BUF[4]);
		//验证checksum
		Check_Sum(UART1_Recv_BUF,4,&CheckSum);
		if(CheckSum == UART1_Recv_BUF[4])
		{
			//判断命令类型
			switch (UART1_Recv_BUF[2])
			{
				case TYPE_TEST:
					P33 = ~P33;
					SendBlock(UART1_Recv_BUF,5);
					break;
				case TYPE_DOOR:
					P33 = ~P33;
					Door_Open();
					SendBlock(UART1_Recv_BUF,5);
					break;
				case TYPE_MUSIC:
					P33 = ~P33;
					SendBlock(UART1_Recv_BUF,5);
					break;
			}
		}
		memset(UART1_Recv_BUF,0,sizeof(UART1_Recv_BUF));
		UART1_Recv_count = 0;
		UART1_Recv_Finish = 0;
	}
}



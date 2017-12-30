#ifndef	UART_H
#define 	UART_H

#include "Stc15.h"

#define FOSC 11059200L	//系统频率
#define BAUD 9600	//串口波特率

void SendData(BYTE dat);
void SendString(char *s);
void Uart_Init(void);
void SendBlock(char *s,char size);
void UartSendRecvData(void);



#endif


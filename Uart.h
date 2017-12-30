#ifndef	UART_H
#define 	UART_H

#include "Stc15.h"

#define FOSC 11059200L	//ϵͳƵ��
#define BAUD 9600	//���ڲ�����

void SendData(BYTE dat);
void SendString(char *s);
void Uart_Init(void);
void SendBlock(char *s,char size);
void UartSendRecvData(void);



#endif


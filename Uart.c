#include "Uart.h"
#include "string.h"
#include "stdlib.h"
#include "Door.h"

bit busy;
//���ڳ�ʼ��
void Uart_Init(void)
{
	//��ʼ��P3.0 P3.1Ϊ׼˫���
	P3M0 &=  ~0x03;
	P3M1 &=  ~0x03;

	SCON	= 0x50;	//8λ�ɱ䲨����
	AUXR	= 0x40;	//��ʱ��1Ϊ1Tģʽ
	TMOD	= 0x00;	//��ʱ��1Ϊģʽ0(16λ�Զ�����)
	TL1		= (65536 - (FOSC/4/BAUD));	//���ò�������װֵ��8λ
	TH1		= (65536 - (FOSC/4/BAUD))>>8;	//���ò�������װֵ��8λ
	TR1		= 1;	//��ʱ��1��ʼ����
	ES		= 1;	//ʹ�ܴ����ж�
	EA		= 1;
}
/*----------------------------
UART �жϷ������
-----------------------------*/
char UART1_Recv_BUF[20];
int  UART1_Recv_count = 0;
int  UART1_Recv_Finish = 1;

void Uart() interrupt 4 using 1
{
	if (TI)
	{
		TI = 0;                 //���TIλ
		busy = 0;               //��æ��־
	}

	if (RI == 1)  
	{  
		RI = 0; 
		UART1_Recv_BUF[UART1_Recv_count++] = SBUF; 
		//buffer���չ�5���ַ���
		if(UART1_Recv_count >= 5)
		{
			//����buffer��������
			UART1_Recv_count = 0;
			//������ɱ�־��λ
			UART1_Recv_Finish = 1;
		}	
	} 
}
/*----------------------------
���ʹ�������
----------------------------*/
void SendData(BYTE dat)
{
	while (busy); 	//�ȴ�ǰ������ݷ������
	busy = 1;
	SBUF = dat;	//д���ݵ�UART���ݼĴ���
}
/*----------------------------
�����ַ���
----------------------------*/
void SendString(char *s)
{
	while (*s)	//����ַ���������־
	{
		SendData(*s++); 	//���͵�ǰ�ַ�
	}
}
/*----------------------------
�������ݿ�
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
//8λ�ۼӺ�У��
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
���ͽ��յ�������
��������ӻ���Ӧ��ʽΪ
	�ش�������������
----------------------------*/
#define	TYPE_TEST	0	//ͨ�Ų���
#define	TYPE_DOOR	1	//�����Ų���
#define	TYPE_MUSIC	2	//�������ֲ���
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
		//��֤checksum
		Check_Sum(UART1_Recv_BUF,4,&CheckSum);
		if(CheckSum == UART1_Recv_BUF[4])
		{
			//�ж���������
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



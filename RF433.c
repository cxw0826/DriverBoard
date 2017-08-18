#include	"RF433.h"
#include	"Uart.h"
//��ʼ��RF433���պͷ�������
void	RF433_Init(void)
{
	//P0.3 P0.2����Ϊ׼˫���
	P0M0 &= ~0x0C;
	P0M1 &= ~0x0C;
	//P2.3 P2.4 P2.5 P2.6 P2.7 ����Ϊ׼˫���
	P2M0 &= ~0xFC;
	P2M1 &= ~0xFC;
}

void RF_Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

void RF_Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

//RF433���ͼ���K0
void	RF433_Trans_K0(void)
{
	RF_TX_K0	=	0;
	RF_TX_K1	=	0;
	RF_Delay10ms();
	RF_TX_K0	=	0;
	RF_TX_K1	=	1;
	RF_Delay10ms();
	RF_TX_K0	=	0;
	RF_TX_K1	=	0;
	RF_Delay10ms();
}

//RF433���ͼ���K1
void	RF433_Trans_K1(void)
{
	RF_TX_K0	=	0;
	RF_TX_K1	=	0;
	RF_Delay10ms();
	RF_TX_K0	=	1;
	RF_TX_K1	=	0;
	RF_Delay10ms();
	RF_TX_K0	=	0;
	RF_TX_K1	=	0;
	RF_Delay10ms();
}
//RF433���ͱ����źţ�����3�Σ���ֹδ���ճɹ�
void RF433_Alarm(void)
{
	RF433_Trans_K0();
	RF_Delay10ms();
	RF433_Trans_K0();
	RF_Delay10ms();
	RF433_Trans_K0();
}
//RF433��������źţ�����3�Σ���ֹδ���ճɹ�
void RF433_Cancel_Alarm(void)
{
	RF433_Trans_K1();
	RF_Delay10ms();
	RF433_Trans_K1();
	RF_Delay10ms();
	RF433_Trans_K1();
}
//RF433���ն˿ڼ�����
BYTE RF433_Recv_IO_State(BYTE Channel)
{
	BYTE A,B;

	switch(Channel)
	{
		case	0:
			{
				RF_D0	=	1;
				A	=	RF_D0;
				RF_D0	=	0;                                                                                                                                    
				B	=	RF_D0;
				if(A==1&&B==1)
				 {
					return	1;
				 }
				else
				{
					return	0;
				}
				break;
			}
		case	1:
			{
				RF_D1	=	1;
				A	=	RF_D1;
				RF_D1	=	0;                                                                                                                                    
				B	=	RF_D1;
				if(A==1&&B==1)
				 {
					return	2;
				 }
				else
				{
					return	0;
				}
				break;
			}
		case	2:
			{
				RF_D2	=	1;
				A	=	RF_D2;
				RF_D2	=	0;                                                                                                                                    
				B	=	RF_D2;
				if(A==1&&B==1)
				 {
					return	3;
				 }
				else
				{
					return	0;
				}
				break;
			}
		case	3:
			{
				RF_D3	=	1;
				A	=	RF_D3;
				RF_D3	=	0;                                                                                                                                    
				B	=	RF_D3;
				if(A==1&&B==1)
				 {
					return	4;
				 }
				else
				{
					return	0;
				}
				break;
			}
		default	:
			{
				return	0;
				break;
			}
	}
}

//RF433����������
void	RF433_Recv_Detect(void)
{
	BYTE		i;
	for(i=0;i<4;i++)
	{
		switch(RF433_Recv_IO_State(i))
		{
			case 1:
			{
				SendString("Detect Key B\r\n");
				break;
			}
			case 2:
			{
				SendString("Detect Key C\r\n");
				break;
			}
			case 3:
			{
				SendString("Detect Key A\r\n");
				break;
			}
			case 4:
			{
				SendString("Detect Key D\r\n");
				break;
			}
			default:
			{
				break;
			}
		}
	}

}

//RF433���ղ��Գ���
void	RF433_Recv_Test(void)
{
	while(1)
	{
		RF433_Recv_Detect();
	}
}




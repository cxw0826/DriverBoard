#ifndef	RF433_H
#define	RF433_H

#include	"Stc15.h"

sbit	RF_TX_K0		=	P0^3;
sbit	RF_TX_K1		=	P0^2;
sbit	RF_D0		=	P2^3;	//B
sbit	RF_D1		=	P2^4;	//C
sbit	RF_D2		=	P2^5;	//D
sbit	RF_D3		=	P2^6;	//A
sbit	RF_VT		=	P2^7;

//RF433初始化程序
void	RF433_Init(void);
//RF433发送相关程序
void	RF433_Trans_K0(void);
void	RF433_Trans_K1(void);
void  RF433_Alarm(void);
void  RF433_Cancel_Alarm(void);
//RF433接收相关程序
BYTE	RF433_Recv_IO_State(BYTE Channel);
void	RF433_Recv_Detect(void);
void	RF433_Recv_Test(void);







#endif


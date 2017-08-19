#include	"Adc.h"
#include	"Stc15.h"
#include	"RF433.h"
#include	"Uart.h"
#include	"Door.h"
#include	"Battery.h"

//--------------------------
//|	PxM1 | PxM0 |   ģʽ   |
//--------------------------
//|	 0   |  0   | ׼˫��� |
//--------------------------
//|	 0   |  1   | ǿ����   |
//--------------------------
//|	 1   |  0   | �������� |
//--------------------------
//|	 1   |  1   | ��©��� |
//--------------------------


void main(void)
{
	//��ʼ������
	Uart_Init();
	SendString("Uart Init Success.\r\n");
	
	//��ʼ��ADC
	ADC_Init();
	//ADC_Test();
	
	//��ʼ��RF433
	RF433_Init();
	//RF433_Recv_Test();

	//��ʼ��������
	Door_Init();
	Door_Test();

	//��ʼ����ص�����
	Battery_Init();
	//Battery_Test();
	
	while(1);
}










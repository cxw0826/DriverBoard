#include	"Adc.h"
#include	"Stc15.h"
#include	"RF433.h"
#include	"Uart.h"
#include	"Door.h"

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

	
	while(1);
}










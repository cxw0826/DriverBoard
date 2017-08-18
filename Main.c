#include	"Adc.h"
#include	"Stc15.h"
#include	"RF433.h"
#include	"Uart.h"
#include	"Door.h"
#include	"Battery.h"

void main(void)
{
	//初始化串口
	Uart_Init();
	SendString("Uart Init Success.\r\n");
	
	//初始化ADC
	ADC_Init();
	//ADC_Test();
	
	//初始化RF433
	RF433_Init();
	//RF433_Recv_Test();

	//初始化开关锁
	Door_Init();
	//Door_Test();

	//初始化电池电量计
	Battery_Init();
	Battery_Test();
	
	while(1);
}










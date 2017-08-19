#include	"Battery.h"
#include	"Uart.h"

void Cw2015_Pwr_CtrlA(BYTE State);
void Cw2015_Pwr_CtrlB(BYTE State);
void IIC_Delay(void);
void Cw2015_Init_A(void);



void Bat_Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//初始化IIC和电量计芯片
void Battery_Init(void)
{
	//P3.5 P3.6 配置为准双向口
	P3M0 &= ~0xE0;
	P3M1 &= ~0xE0;
	//P2.1 配置为准双向口
	P2M0 &= ~0x03;
	P2M1 &= ~0x03;
	/*
	//P2.0  P3.7 配置为高阻输入
	P2M0 &= ~0x01;
	P2M1 |=  0x01;
	
	P3M0 &= ~0x80;
	P3M1 |=  0x80;
	*/
	IIC_Delay();
	//拉高总线
	IIC_SDA  =  1;
	IIC_Delay();
	IIC_SCL  =  1;
	IIC_Delay();
	//关闭两路电量计芯片电压
	Cw2015_Pwr_CtrlA(Off);
	Cw2015_Pwr_CtrlB(Off);
	//初始化电量计参数
	Cw2015_Init_A();
}

/*********************************************************
			模拟IIC相关函数
*********************************************************/
void IIC_Delay(void)		//时钟产生计时控制 11.0592MHz 6us
{
	BYTE Cnt;

	Cnt = 14;
	while (--Cnt);
}

//开始信号 SCL在高电平期间，SDA一个下降沿则表示启动信号  
void IIC_Start(void)  
{     
	IIC_SDA = 1; //释放SDA总线  
	IIC_Delay();  
	IIC_SCL = 1;  
	IIC_Delay();  
	IIC_SDA = 0;  
	IIC_Delay();  
}  

//停止 SCL在高电平期间，SDA一个上升沿则表示停止信号
void IIC_Stop(void)    
{  
	IIC_SDA = 0;  
	IIC_Delay();  
	IIC_SCL = 	1;  
	IIC_Delay();  
	IIC_SDA =	1;  
	IIC_Delay();  
}

//应答 SCL在高电平期间，SDA被从设备拉为低电平表示应答  
void IIC_Respons(void)  
{  
	BYTE i;  
	IIC_SCL  = 1;  
	IIC_Delay();
	IIC_Delay(); 
	//至多等待250个CPU时钟周期 
	while((IIC_SDA==1) && (i<250))
		i++;  
	IIC_SCL  = 0;  
	IIC_Delay();  
}

//写一个字节
void IIC_Write_Byte(BYTE DAT)   
{  
	BYTE DAT_Cnt,DAT_Temp;  
	DAT_Temp = DAT;  

	for(DAT_Cnt = 0;DAT_Cnt < 8;DAT_Cnt++)  
	{  
		DAT_Temp = DAT_Temp << 1;  
		//拉低SCL，因为只有在时钟信号为低电平期间按数据线上的高低电平状态才允许变化；
		//并在此时和上一个循环的scl=1一起形成一个上升沿
		IIC_SCL  = 0;  
		IIC_Delay();  
		IIC_SDA = CY;  
		IIC_Delay();  
		IIC_SCL  = 1;//拉高SCL，此时SDA上的数据稳定  
		IIC_Delay(); 
		IIC_Delay(); 
	}  
	IIC_SCL = 0;//拉低SCL，为下次数据传输做好准备  
	IIC_Delay();  
	//释放SDA总线，接下来由从设备控制
	//比如从设备接收完数据后，在SCL为高时，拉低SDA作为应答信号
	IIC_SDA = 1;  
	IIC_Delay();  
}

//读一个字节  
BYTE IIC_Read_Byte(void)
{  
	BYTE DAT_Cnt,DAT = 0;  
	IIC_SCL 	= 	0;  
	IIC_Delay(); 
	IIC_SDA	=	1;
	for(DAT_Cnt = 0;DAT_Cnt < 8;DAT_Cnt++)  
	{  
		//上升沿时，IIC设备将数据放在sda线上
		//并在高电平期间数据已经稳定，可以接收啦 
		IIC_SCL = 1; 
		IIC_Delay(); 
		IIC_Delay();         
		DAT = (DAT << 1) | IIC_SDA;   
		IIC_Delay(); 
		IIC_Delay();    
		IIC_SCL = 0;//拉低SCL，使发送端可以把数据放在SDA上  
		IIC_Delay();  
    	}  
	IIC_Delay();
	return DAT;  
} 

//写设备函数
//Write_ID:	要操作器件的写ID
//Reg_ID:	要操作的寄存器
//DAT:		需要写入的数据
void IIC_Write_Reg(BYTE Write_ID,BYTE Reg_ID,BYTE DAT)
{
	IIC_Start();
	IIC_Write_Byte(Write_ID);
	IIC_Respons();
	IIC_Write_Byte(Reg_ID);
	IIC_Respons();
	IIC_Write_Byte(DAT);
	IIC_Respons();
	IIC_Stop();
}

//读设备函数
//Write_ID:	要操作器件的写ID
//Reg_ID:	要操作的寄存器
//DAT:		需要写入的数据
//Return:		返回所读寄存器的值
BYTE IIC_Read_Reg(BYTE Write_ID,BYTE Reg_ID,BYTE Read_ID)
{	
	BYTE Read_Dat;
	
	IIC_Start();
	IIC_Write_Byte(Write_ID);
	IIC_Respons();
	IIC_Write_Byte(Reg_ID);
	IIC_Respons();
	IIC_Start();
	IIC_Write_Byte(Read_ID);
	IIC_Respons();
	Read_Dat	= IIC_Read_Byte();
	IIC_Stop();
	IIC_Delay();
	
	return Read_Dat;
}

/***********************************************
			操作Cw2015相关函数
***********************************************/

//第一路Cw2015电源控制
void Cw2015_Pwr_CtrlA(BYTE State)
{
	if(State == On)
	{
		Bat_Detect_Pwr_Ctrl_A = 1;
	}
	else if(State == Off)
	{
		Bat_Detect_Pwr_Ctrl_A = 0;
	}
	else
	{
		Bat_Detect_Pwr_Ctrl_A = 0;
	}
}

//第二路Cw2015电源控制
void Cw2015_Pwr_CtrlB(BYTE State)
{
	if(State == On)
	{
		Bat_Detect_Pwr_Ctrl_B = 1;
	}
	else if(State == Off)
	{
		Bat_Detect_Pwr_Ctrl_B = 0;
	}
	else
	{
		Bat_Detect_Pwr_Ctrl_B = 0;
	}
}
//刷新Cw2015,就像断电重启一样
void Cw2015_POR_Refresh(void)
{
	IIC_Write_Reg(Cw2015_WR_ID,Cw2015_Mode_Reg,Cw2015_Refresh_Value);
}
//启动Cw2015
void Cw2015_Wakeup(void)
{
	IIC_Write_Reg(Cw2015_WR_ID,Cw2015_Mode_Reg,Cw2015_Wakeup_Value);
}

//设置低电压报警阈值
void Cw2015_Set_Alarm_THD(void)
{
	IIC_Write_Reg(Cw2015_WR_ID,Cw2015_ALRT_Reg,Cw2015_Alarm_THD_Value);
}

//读取Cw2015电量百分比
void Cw2015_Read_Bat_Percentage(void)
{
	BYTE		Result;

	Result = IIC_Read_Reg(Cw2015_WR_ID,Cw2015_SOCH_Reg,Cw2015_RD_ID);
	SendString("The Battery Percentage is:");
	SendData((Result/100) + '0');
	SendData(((Result/10)%10) + '0');
	SendData((Result%10) + '0');
	SendString("\r\n");
}

//读取Cw2015版本信息
void Cw2015_Read_Version(void)
{
	BYTE	Result;

	Result = IIC_Read_Reg(Cw2015_WR_ID,Cw2015_Version_Reg,Cw2015_RD_ID);
	SendString("The Cw2015 Version is:");
	SendData((Result/100) + '0');
	SendData(((Result/10)%10) + '0');
	SendData((Result%10) + '0');
	SendString("\r\n");
}

//清除状态标志位，低电压报警
void Cw2015_Clean_Alram_Flag(void)
{
	//清除报警标志位
	IIC_Write_Reg(Cw2015_WR_ID,Cw2015_RRT_ALRT_Msb,0x00);
}

//初始化Cw2015电量计IC
void Cw2015_Init_A(void)
{
	//打开电源
	Cw2015_Pwr_CtrlA(On);
	Bat_Delay500ms();
	Bat_Delay500ms();
	Bat_Delay500ms();
	Bat_Delay500ms();
	//唤醒Cw2015
	Cw2015_Wakeup();
	Bat_Delay500ms();
	//设置Cw2015报警阈值
	Cw2015_Set_Alarm_THD();
	Bat_Delay500ms();
	//清除报警标志位
	Cw2015_Clean_Alram_Flag();
	Bat_Delay500ms();
	//读取Cw2015 A路电量
	//Cw2015_Read_Bat_Percentage();
}

//Cw2015报警检测
BYTE Cw2015_Alarm_DetectA(void)
{
	BYTE A,B;
	Bat_Low_Pwr_AlarmA = 1;
	A = Bat_Low_Pwr_AlarmA;
	Bat_Low_Pwr_AlarmA = 0;																																	  
	B = Bat_Low_Pwr_AlarmA;
	if(A==0&&B==0)
	 {
		return	0;
	 }
	else
		return	1;
}


//测试电量计报警功能
void Cw2015_Alarm_Test(void)
{
	while(1)
	{
		SendString("Fuction Test!\r\n");
		//刷新Cw2015
		Cw2015_POR_Refresh();
		Bat_Delay500ms();
		//唤醒Cw2015
		Cw2015_Wakeup();
		Bat_Delay500ms();
		//如果检测到有报警信号，刷新标志位
		while(Cw2015_Alarm_DetectA() == 0)
		{
			Cw2015_Clean_Alram_Flag();
			SendString("Cw2015 Alramed !\r\n");
		}
		Bat_Delay500ms();
		//读取电量
		Cw2015_Read_Bat_Percentage();
		
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
	}
}

//测试电池电量计
void Battery_Test(void)
{
	Cw2015_Alarm_Test();
}




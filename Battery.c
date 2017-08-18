#include	"Battery.h"
#include	"Uart.h"

void Cw2015_Pwr_CtrlA(BYTE State);
void Cw2015_Pwr_CtrlB(BYTE State);
void IIC_Delay(void)	;


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

//��ʼ��IIC�͵�����оƬ
void Battery_Init(void)
{
	//P3.5 P3.6 P3.7����Ϊ׼˫���
	P3M0 &= ~0xE0;
	P3M1 &= ~0xE0;
	//P2.0  P2.1 ����Ϊ׼˫���
	P2M0 &= ~0x03;
	P2M1 &= ~0x03;
	IIC_Delay();
	//��������
	IIC_SDA  =  1;
	IIC_Delay();
	IIC_SCL  =  1;
	IIC_Delay();
	//��ʼ��������оƬ
	Cw2015_Pwr_CtrlA(Off);
	Cw2015_Pwr_CtrlB(Off);
}

/*********************************************************
			ģ��IIC��غ���
*********************************************************/
void IIC_Delay(void)		//ʱ�Ӳ�����ʱ���� 11.0592MHz 6us
{
	BYTE Cnt;

	Cnt = 14;
	while (--Cnt);
}

//��ʼ�ź� SCL�ڸߵ�ƽ�ڼ䣬SDAһ���½������ʾ�����ź�  
void IIC_Start(void)  
{     
	IIC_SDA = 1; //�ͷ�SDA����  
	IIC_Delay();  
	IIC_SCL = 1;  
	IIC_Delay();  
	IIC_SDA = 0;  
	IIC_Delay();  
}  

//ֹͣ SCL�ڸߵ�ƽ�ڼ䣬SDAһ�����������ʾֹͣ�ź�
void IIC_Stop(void)    
{  
	IIC_SDA = 0;  
	IIC_Delay();  
	IIC_SCL = 	1;  
	IIC_Delay();  
	IIC_SDA =	1;  
	IIC_Delay();  
}

//Ӧ�� SCL�ڸߵ�ƽ�ڼ䣬SDA�����豸��Ϊ�͵�ƽ��ʾӦ��  
void IIC_Respons(void)  
{  
	BYTE i;  
	IIC_SCL  = 1;  
	IIC_Delay();
	IIC_Delay(); 
	//����ȴ�250��CPUʱ������ 
	while((IIC_SDA==1) && (i<250))
		i++;  
	IIC_SCL  = 0;  
	IIC_Delay();  
}

//дһ���ֽ�
void IIC_Write_Byte(BYTE DAT)   
{  
	BYTE DAT_Cnt,DAT_Temp;  
	DAT_Temp = DAT;  

	for(DAT_Cnt = 0;DAT_Cnt < 8;DAT_Cnt++)  
	{  
		DAT_Temp = DAT_Temp << 1;  
		//����SCL����Ϊֻ����ʱ���ź�Ϊ�͵�ƽ�ڼ䰴�������ϵĸߵ͵�ƽ״̬������仯��
		//���ڴ�ʱ����һ��ѭ����scl=1һ���γ�һ��������
		IIC_SCL  = 0;  
		IIC_Delay();  
		IIC_SDA = CY;  
		IIC_Delay();  
		IIC_SCL  = 1;//����SCL����ʱSDA�ϵ������ȶ�  
		IIC_Delay(); 
		IIC_Delay(); 
	}  
	IIC_SCL = 0;//����SCL��Ϊ�´����ݴ�������׼��  
	IIC_Delay();  
	//�ͷ�SDA���ߣ��������ɴ��豸����
	//������豸���������ݺ���SCLΪ��ʱ������SDA��ΪӦ���ź�
	IIC_SDA = 1;  
	IIC_Delay();  
}

//��һ���ֽ�  
BYTE IIC_Read_Byte(void)
{  
	BYTE DAT_Cnt,DAT = 0;  
	IIC_SCL 	= 	0;  
	IIC_Delay(); 
	IIC_SDA	=	1;
	for(DAT_Cnt = 0;DAT_Cnt < 8;DAT_Cnt++)  
	{  
		//������ʱ��IIC�豸�����ݷ���sda����
		//���ڸߵ�ƽ�ڼ������Ѿ��ȶ������Խ����� 
		IIC_SCL = 1; 
		IIC_Delay(); 
		IIC_Delay();         
		DAT = (DAT << 1) | IIC_SDA;   
		IIC_Delay(); 
		IIC_Delay();    
		IIC_SCL = 0;//����SCL��ʹ���Ͷ˿��԰����ݷ���SDA��  
		IIC_Delay();  
    	}  
	IIC_Delay();
	return DAT;  
} 

//д�豸����
//Write_ID:	Ҫ����������дID
//Reg_ID:	Ҫ�����ļĴ���
//DAT:		��Ҫд�������
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

//���豸����
//Write_ID:	Ҫ����������дID
//Reg_ID:	Ҫ�����ļĴ���
//DAT:		��Ҫд�������
//Return:		���������Ĵ�����ֵ
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
			����Cw2015��غ���
***********************************************/

//��һ·Cw2015��Դ����
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

//�ڶ�·Cw2015��Դ����
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

//����Cw2015
void	Cw2015_Wakeup(void)
{
	IIC_Write_Reg(Cw2015_WR_ID,Cw2015_Mode_Reg,Cw2015_Wakeup_Value);
}
//��ȡCw2015�����ٷֱ�
void Cw2015_Read_Bat_Percentage(void)
{
	//BYTE		Tmp;
	int		Result;

	Result = IIC_Read_Reg(Cw2015_WR_ID,Cw2015_SOCH_Reg,Cw2015_RD_ID);
	//Tmp    = IIC_Read_Reg(Cw2015_WR_ID,Cw2015_SOCL_Reg,Cw2015_RD_ID);
	//Result = (Result<<8) | Tmp;
	SendString("The Battery Percentage is:");
	SendData((Result/10) + '0');
	SendData((Result%10) + '0');
	SendString("\r\n");
}

//���Ե�ص�����
void Battery_Test(void)
{
	while(0)
	{
		/*
		SendString("Detect Cw2015 A!\r\n");
		Cw2015_Pwr_CtrlA(On);
		Cw2015_Pwr_CtrlB(Off);
		Bat_Delay500ms();
		Cw2015_Wakeup();
		Bat_Delay500ms();
		Cw2015_Read_Bat_Percentage();
		
		Cw2015_Pwr_CtrlA(Off);
		Cw2015_Pwr_CtrlB(Off);
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		*/
		SendString("Detect Cw2015 B!\r\n");
		Cw2015_Pwr_CtrlA(Off);
		Cw2015_Pwr_CtrlB(On);
		Bat_Delay500ms();
		Cw2015_Wakeup();
		Bat_Delay500ms();
		Cw2015_Read_Bat_Percentage();
		
		Cw2015_Pwr_CtrlA(Off);
		Cw2015_Pwr_CtrlB(Off);
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
		Bat_Delay500ms();
	}
	
	SendString("Detect Cw2015 B!\r\n");
	Cw2015_Pwr_CtrlA(Off);
	Cw2015_Pwr_CtrlB(On);
	Bat_Delay500ms();
	Bat_Delay500ms();
	Bat_Delay500ms();
	Bat_Delay500ms();
	Bat_Delay500ms();
	Bat_Delay500ms();
	Cw2015_Wakeup();
	Bat_Delay500ms();
	while(1)
	{
		Cw2015_Read_Bat_Percentage();
		Bat_Delay500ms();
		Bat_Delay500ms();
	}
}




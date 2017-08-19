#ifndef	BATTERY_H
#define	BATTERY_H

#include	"Stc15.h"

sbit 	IIC_SDA						=	P2^2;
sbit 	IIC_SCL						=	P2^1;

sbit	Bat_Detect_Pwr_Ctrl_B		=	P3^5;
sbit	Bat_Detect_Pwr_Ctrl_A		=	P3^6;
sbit	Bat_Low_Pwr_AlarmA			=	P2^0;
sbit	Bat_Low_Pwr_AlarmB			=	P3^7;

#define	On	1
#define	Off	0

//CW2015�̶���ַ��0x62
#define Cw2015_ID			0x62
//������дID
#define Cw2015_WR_ID		Cw2015_ID << 1
//�����ƶ�ID
#define Cw2015_RD_ID		(Cw2015_ID << 1) + 1
//�����ư汾��Ϣ�Ĵ���
#define Cw2015_Version_Reg		0x00
//�����Ĵ�����6λ�Ĵ���
#define Cw2015_Pwr_REG1		0x02
//�����Ĵ�����8λ�Ĵ���
#define Cw2015_Pwr_REG2		0x03
//������SOC����Ĵ�����8λ
#define Cw2015_SOCH_Reg		0x04
//������SOC����Ĵ�����8λ
#define Cw2015_SOCL_Reg		0x05
//�����Ƶ��ʣ��ʱ��Ĵ���1
//���λ�ǵ͵�ѹ������־λ����ҪMCU���
#define Cw2015_RRT_ALRT_Msb	0x06
//�����Ƶ��ʣ��ʱ��Ĵ���2
#define Cw2015_RRT_ALRT_Lsb	0x07
//�����ƾ�����ֵ���üĴ���
//��5λ����ֵ���üĴ���
//ÿbit����һ��percent,�ܹ���0%-31%
//bit1�ǵ�ظ���״ָ̬ʾ�Ĵ���
#define Cw2015_ALRT_Reg		0x08
//������ģʽ���üĴ���
//��2λ��˯��ģʽ�Ĵ�����д11����˯��ģʽ��д00����
//bit4-bit5��QSTRT�Ĵ�����д11��������
//bit0-bit3��������������д1111ǿ������
#define Cw2015_Mode_Reg		0x0A

//����������ֵ
#define Cw2015_Wakeup_Value		0x30
//ˢ�µ�����ֵ
#define Cw2015_Refresh_Value	0x3F
//�����Ƶ͵�ѹ������ֵ
#define Cw2015_Alarm_THD_Value 	0x40

void Battery_Init(void);
void Battery_Test(void);




















#endif


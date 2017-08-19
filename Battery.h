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

//CW2015固定地址是0x62
#define Cw2015_ID			0x62
//电量计写ID
#define Cw2015_WR_ID		Cw2015_ID << 1
//电量计读ID
#define Cw2015_RD_ID		(Cw2015_ID << 1) + 1
//电量计版本信息寄存器
#define Cw2015_Version_Reg		0x00
//电量寄存器高6位寄存器
#define Cw2015_Pwr_REG1		0x02
//电量寄存器低8位寄存器
#define Cw2015_Pwr_REG2		0x03
//电量计SOC结果寄存器高8位
#define Cw2015_SOCH_Reg		0x04
//电量计SOC结果寄存器低8位
#define Cw2015_SOCL_Reg		0x05
//电量计电池剩余时间寄存器1
//最高位是低电压报警标志位，需要MCU清除
#define Cw2015_RRT_ALRT_Msb	0x06
//电量计电池剩余时间寄存器2
#define Cw2015_RRT_ALRT_Lsb	0x07
//电量计警报阈值设置寄存器
//高5位是阈值设置寄存器
//每bit代表一个percent,总共从0%-31%
//bit1是电池更新状态指示寄存器
#define Cw2015_ALRT_Reg		0x08
//电量计模式设置寄存器
//高2位是睡眠模式寄存器，写11进入睡眠模式，写00唤醒
//bit4-bit5是QSTRT寄存器，写11快速启动
//bit0-bit3是重启控制器，写1111强制重启
#define Cw2015_Mode_Reg		0x0A

//启动电量计值
#define Cw2015_Wakeup_Value		0x30
//刷新电量计值
#define Cw2015_Refresh_Value	0x3F
//电量计低电压报警阈值
#define Cw2015_Alarm_THD_Value 	0x40

void Battery_Init(void);
void Battery_Test(void);




















#endif


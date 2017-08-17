#ifndef ADC_H
#define ADC_H

#include "Stc15.h"

sfr ADC_LOW2    =   0xBE;           //ADC��2λ���

#define ADC_POWER	 0x80            //ADC��Դ����λ
#define ADC_FLAG		0x10            //ADC��ɱ�־
#define ADC_START		0x08            //ADC��ʼ����λ
#define ADC_SPEEDLL	 0x00           //540��ʱ��
#define ADC_SPEEDL  	0x20            //360��ʱ��
#define ADC_SPEEDH  	0x40            //180��ʱ��
#define ADC_SPEEDHH 	0x60            //90��ʱ��
#define Adc_ch			0x07		 //ADCͨ��7


void  ADC_Init(void);
BYTE ADC_GetResult(void);



#endif


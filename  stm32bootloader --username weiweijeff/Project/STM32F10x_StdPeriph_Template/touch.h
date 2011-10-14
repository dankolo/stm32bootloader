#ifndef __TOUCH_H
#define __TOUCH_H

#include "stm32f10x.h"


#define TP_CS()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)//ʹ��Ƭѡ
#define TP_DCS() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define CHX  0xd0  //ͨ��X+��ѡ�������
#define CHY  0x90 //ͨ��Y+��ѡ�������



void Touch_Config(void);

unsigned char SPI_WriteByte(unsigned char data);

void SpiDelay(unsigned int DelayCnt);

int16_t TPReadX(void);

int16_t TPReadY(void);

int16_t  TP_MeasureX(void);
int16_t  TP_MeasureY(void);

#endif

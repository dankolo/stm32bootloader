#ifndef __TOUCH_H
#define __TOUCH_H

#include "stm32f10x.h"


#define TP_CS()  GPIO_ResetBits(GPIOF,GPIO_Pin_10)//使能片选
#define TP_DCS() GPIO_SetBits(GPIOF,GPIO_Pin_10)

#define CHX  0xd0  //通道X+的选择控制字
#define CHY  0x90 //通道Y+的选择控制字



void Touch_Config(void);

unsigned char SPI_WriteByte(unsigned char data);

void SpiDelay(unsigned int DelayCnt);

int16_t TPReadX(void);

int16_t TPReadY(void);

int16_t  TP_MeasureX(void);
int16_t  TP_MeasureY(void);

#endif

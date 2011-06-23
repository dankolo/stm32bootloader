#ifndef __COMMONALITY_H
#define __COMMONALITY_H
#include "stm32f10x.h"
#include <stdio.h>
#include "ili9320.h"
#include "RTC_Time.h"
#include "fatfs.h"


#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define CD4067_EN  GPIO_ResetBits(GPIOD,GPIO_Pin_5)
#define CD4067_DIS  GPIO_SetBits(GPIOD,GPIO_Pin_5)
//#define RAM_DEBUG//在内存调试


struct contact  // 触点数据结构
{
  unsigned int point_coordinate[2];//打点圆心坐标值
  unsigned int value_coordinate[2];//显示值起始坐标
  unsigned char flag_last;//是不是  本级位最后一个触点,非0:是,0:不是
  unsigned char channel; //采集通道号
  unsigned char R[6];  //触点电阻值

};

struct level   // 级位数据结构
{
  //unsigned char level_index[];//级位索引
  unsigned char level_V[6];//级位电压
  struct contact contacts[5];//级位触点
};


void delay_nus(vu32 nCount);

void delay_long(void);
unsigned char *Get_ADC1_Value();
void ADC1_DMA_Config(void);
void ADC1_GPIO_Config(void);
void ADC1_Config(void);
void RCC_Configuration(void);
void NVIC_Config(void);
void EXTI_Config(void);
void USART1_Init();
void CD4067_GPIO_Config(void);
void draw_choosemodel(void);
unsigned char *get_time_now();
void LCD_Set_Time(unsigned char *set_buffer);
void draw_time_manger(void);
void time_manager(int x,int y);
void TP_EXTI_DISABLE(void);
void TP_EXTI_ENABLE(void);


#endif
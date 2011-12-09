#ifndef __COMMONALITY_H
#define __COMMONALITY_H
#include "stm32f10x.h"
#include <stdio.h>
#include "RTC_Time.h"
#include "fatfs.h"
#include "stm3210e_eval_lcd.h"
#include"time_manage.h"
#include"ref_manage.h"
#include "main_panel.h"
#include "s640k1.h"

#define CD4067_RCC               RCC_APB2Periph_GPIOF 
#define CD4067_PORT              GPIOF
#define CD4067_E                 GPIO_Pin_8
#define CD4067_s0                GPIO_Pin_10
#define CD4067_s1                GPIO_Pin_9
#define CD4067_s2                GPIO_Pin_7
#define CD4067_s3                GPIO_Pin_6

#define PowerA_RCC               RCC_APB2Periph_GPIOE
#define PowerA_PORT              GPIOE
#define PowerA_Pin               GPIO_Pin_2

#define LCD_RST_RCC               RCC_APB2Periph_GPIOG
#define LCD_RST_PORT              GPIOG
#define LCD_RST_Pin               GPIO_Pin_8


#define ADC_R_DR_Address         ((uint32_t)0x4001244C)//adc1
#define ADC_V_DR_Address         ((uint32_t)0x40013c4C)//adc3

#define ADC_V                    ADC3
#define ADC_V_RCC                RCC_APB2Periph_ADC3 | RCC_APB2Periph_GPIOC
#define ADC_V_Channel            ADC_Channel_10
#define ADC_V_PORT               GPIOC
#define ADC_V_pin                GPIO_Pin_0
#define ADC_V_DMA_RCC            RCC_AHBPeriph_DMA2
#define ADC_V_DMA_Channel        DMA2_Channel5


#define ADC_R                    ADC1
#define ADC_R_RCC                RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC
#define ADC_R_Channel            ADC_Channel_13
#define ADC_R_PORT               GPIOC
#define ADC_R_pin                GPIO_Pin_3
#define ADC_R_DMA_RCC            RCC_AHBPeriph_DMA1
#define ADC_R_DMA_Channel        DMA1_Channel1

#define ADC_R_DMA_BufferSize     64
#define ADC_V_DMA_BufferSize     64

#define ADC1_stop();             { ADC_DMACmd(ADC1, DISABLE);ADC_SoftwareStartConvCmd(ADC1, DISABLE);}
#define ADC3_stop();             { ADC_DMACmd(ADC3, DISABLE);ADC_SoftwareStartConvCmd(ADC3, DISABLE);}
#define ADC1_restart();          { ADC_DMACmd(ADC1, ENABLE);ADC_SoftwareStartConvCmd(ADC1, ENABLE);}
#define ADC3_restart();          { ADC_DMACmd(ADC3, ENABLE);ADC_SoftwareStartConvCmd(ADC3, ENABLE);}
#define TP_stop();               {TIM_Cmd(TIM2, DISABLE);TIM_Cmd(TIM3, DISABLE);}
#define TP_restart();            {TIM_Cmd(TIM2, ENABLE);TIM_Cmd(TIM3, ENABLE);}

#define CD4067_EN()              GPIO_ResetBits(GPIOF,GPIO_Pin_8)
#define CD4067_DIS()             GPIO_SetBits(GPIOF,GPIO_Pin_8)
#define PowerA_EN()              GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define PowerA_DIS()             GPIO_ResetBits(GPIOE,GPIO_Pin_2)

extern unsigned char ADC_R_Value[5];
extern unsigned char ADC_V_Value[5];
extern unsigned char time_buffer[20];
extern unsigned char Scan_Channels[16];
extern uint8_t     tp_flag;
extern uint16_t    tp_x[5],tp_y[5],x,y;
extern uint8_t     sys_flag;
extern uint16_t    ref;

enum system_flag{main_panel,set_ref,set_time,tks640k1,tks14a};

struct contact  // 触点数据结构
{
  unsigned int point_coordinate[2];//打点圆心坐标值
  unsigned int value_coordinate[2];//显示值起始坐标
  unsigned char flag_last;//是不是  本级位最后一个触点,非0:是,0:不是
  unsigned char channel; //采集通道号
  float div; //多点数,多点串联，结果要平分
  unsigned char R[5];  //触点电阻值

};

struct level   // 级位数据结构
{
  //unsigned char level_index[];//级位索引
  unsigned char level_V[6];//级位电压
  struct contact contacts[5];//级位触点
};


void delay_nus(vu32 nCount);
void  delay(u32 t);
u16 *Get_ADC_R_Value();
extern unsigned char *Get_ADC_V_Value();
void ADC_GPIO_Config(void);
void ADC_R_DMA_Config(void);
void ADC_R_Config(void);
void ADC_V_DMA_Config(void);
void ADC_V_Config(void);

void RCC_Configuration(void);
void NVIC_Configuration(void);
void TIM2_Config(void);
void TIM3_Config(void);
void CD4067_GPIO_Config(void);
void PowerA_GPIO_Config(void);
void Set_Scan_Channel(unsigned char x);
unsigned char *get_time_now();
void LCD_Set_Time(unsigned char *set_buffer);

void schedule(uint16_t x,uint16_t y);





#endif
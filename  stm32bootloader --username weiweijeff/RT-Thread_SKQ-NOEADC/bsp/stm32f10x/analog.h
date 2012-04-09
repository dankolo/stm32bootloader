#ifndef __ANALOG_H
#define __ANALOG_H

#include "stm32f10x.h"
#include <stdio.h>
#include <rtthread.h>
#include "lcd.h"

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
#define ADC_V_DMA_Flag           DMA2_FLAG_TC5

#define ADC_R                    ADC1
#define ADC_R_RCC                RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC
#define ADC_R_Channel            ADC_Channel_13
#define ADC_R_PORT               GPIOC
#define ADC_R_pin                GPIO_Pin_3
#define ADC_R_DMA_RCC            RCC_AHBPeriph_DMA1
#define ADC_R_DMA_Channel        DMA1_Channel1
#define ADC_R_DMA_Flag           DMA1_FLAG_TC1

#define ADC_R_DMA_BufferSize     32
#define ADC_V_DMA_BufferSize     32



#define CD4067_EN()              GPIO_ResetBits(GPIOF,GPIO_Pin_8)
#define CD4067_DIS()             GPIO_SetBits(GPIOF,GPIO_Pin_8)
#define PowerA_EN()              GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define PowerA_DIS()             GPIO_ResetBits(GPIOE,GPIO_Pin_2)




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
  unsigned char level_V[7];//级位电压
  struct contact contacts[5];//级位触点
};

extern rt_uint8_t     auto_scan_flag;



rt_int16_t *Get_ADC_R_Value();
rt_int16_t *Get_ADC_V_Value();
void ADC_GPIO_Config(void);
void ADC_R_DMA_Config(void);
void ADC_R_Config(void);
void ADC_V_DMA_Config(void);
void ADC_V_Config(void);

void CD4067_GPIO_Config(void);
void PowerA_GPIO_Config(void);
void Set_Scan_Channel(unsigned char x);

void ADC_R_stop(void);
void ADC_V_stop(void);
void ADC_R_Restart(void);
void ADC_V_Restart(void);


#endif
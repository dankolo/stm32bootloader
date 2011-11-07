#ifndef __COMMONALITY_H
#define __COMMONALITY_H
#include "stm32f10x.h"
#include <stdio.h>
#include "RTC_Time.h"
#include "fatfs.h"


#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define ADC3_DR_Address    ((uint32_t)0x40013c4C)

#define CD4067_RCC    RCC_APB2Periph_GPIOD 
#define CD4067_PORT   GPIOF
#define CD4067_E      GPIO_Pin_8
#define CD4067_s0     GPIO_Pin_10
#define CD4067_s1     GPIO_Pin_9
#define CD4067_s2     GPIO_Pin_7
#define CD4067_s3     GPIO_Pin_6

#define PowerA_RCC    RCC_APB2Periph_GPIOE
#define PowerA_PORT   GPIOE
#define PowerA_pin    GPIO_Pin_2

#define ADC_V         ADC1
#define ADC_V_RCC     RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC
#define ADC_V_Channel ADC_Channel_10
#define ADC_V_PORT    GPIOC
#define ADC_V_pin     GPIO_Pin_0

#define ADC_R         ADC3
#define ADC_R_RCC     RCC_APB2Periph_ADC3 | RCC_APB2Periph_GPIOC
#define ADC_R_Channel ADC_Channel_13
#define ADC_R_PORT    GPIOC
#define ADC_R_pin     GPIO_Pin_3

#define CD4067_EN()  GPIO_ResetBits(GPIOF,GPIO_Pin_8)
#define CD4067_DIS()  GPIO_SetBits(GPIOF,GPIO_Pin_8)
#define PowerA_EN()  GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define PowerA_DIS()  GPIO_ResetBits(GPIOE,GPIO_Pin_2)

#define ADC1_DMA_BufferSize 64;
#define ADC3_DMA_BufferSize 64;
extern unsigned char ADC_R_Value[6];
extern unsigned char ADC_V_Value[6];
extern unsigned char time_buffer[20];


struct contact  // �������ݽṹ
{
  unsigned int point_coordinate[2];//���Բ������ֵ
  unsigned int value_coordinate[2];//��ʾֵ��ʼ����
  unsigned char flag_last;//�ǲ���  ����λ���һ������,��0:��,0:����
  unsigned char channel; //�ɼ�ͨ����
  unsigned char R[6];  //�������ֵ

};

struct level   // ��λ���ݽṹ
{
  //unsigned char level_index[];//��λ����
  unsigned char level_V[6];//��λ��ѹ
  struct contact contacts[5];//��λ����
};


void delay_nus(vu32 nCount);
void delay_long(void);
unsigned char *Get_ADC1_Value();
unsigned char *Get_ADC3_Value();
void ADC1_DMA_Config(void);
void ADC_GPIO_Config(void);
void ADC1_Config(void);
void ADC2_Config(void);
void ADC3_DMA_Config(void);
void ADC3_Config(void);

void RCC_Configuration(void);
void NVIC_Configuration(void);
void TIM2_Config(void);
void TIM3_Config(void);
void CD4067_GPIO_Config(void);
void PowerA_GPIO_Config(void);
void Set_Scan_Channel(unsigned char x);
unsigned char *get_time_now();
void LCD_Set_Time(unsigned char *set_buffer);

void draw_choosemodel(void);
void draw_time_manger(void);
void time_manager(int x,int y);


#endif
#ifndef __ADC_H
#define __ADC_H
#include "stm32f10x.h"



#define ADC1_DR_Address    ((uint32_t)0x4001244C)

void Get_ADC1_Value();
void ADC1_Config(void);
void ADC1_DMA_Config(void);
void ADC1_GPIO_Config(void);

#endif
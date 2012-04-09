#ifndef _LTC1865_H_
#define _LTC1865_H_



#include <rtthread.h>
#include "stm32f10x.h"











#define LTC1865_SPI                   SPI1
#define LTC1865_SPI_CLK               RCC_APB2Periph_SPI1

#define LTC1865_SPI_DMA		DMA1_Channel3
#define LTC1865_SPI_DMA_IRQ	DMA1_Channel3_IRQn
#define LTC1865_SPI_RCC_AHB	RCC_AHBPeriph_DMA1
#define LTC1865_SPI_DR_ADDRESS  0x4001300c


#define LTC1865_SPI_GPIO              GPIOA
#define LTC1865_SPI_GPIO_CLK          RCC_APB2Periph_GPIOA  
#define LTC1865_SPI_PIN_SCK           GPIO_Pin_5
#define LTC1865_SPI_PIN_MISO          GPIO_Pin_6
#define LTC1865_SPI_PIN_MOSI          GPIO_Pin_7


#define LTC1865_GPIO                  GPIOA
#define LTC1865_GPIO_CLK              RCC_APB2Periph_GPIOB
#define LTC1865_PIN_CONV              GPIO_Pin_0



void ltc1865_init(void);



rt_uint16_t ltc1865_read_ch(rt_uint8_t mode ,rt_uint8_t ch);



#endif   // _LTC1865_H_
/**
  ******************************************************************************
  * @file    SDIO/uSDCard/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32_eval_sdio_sd.h"
#include "stdio.h"
#include "fatfs.h"
#include "stm32f10x_adc.h"
#include "stm3210e_eval_lcd.h"
#include "touch.h"
#include <stdlib.h>
#include "commonality.h"




extern void TIM2_Config(void);
extern void TIM3_Config(void);
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup SDIO_uSDCard
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */


void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles SDIO global interrupt request.
  * @param  None
  * @retval None
  */
void SDIO_IRQHandler(void)
{
  /* Process All SDIO Interrupt Sources */
  SD_ProcessIRQSrc();
}

/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{ 
  ;
}

void USART2_IRQHandler(void)
{
  ;
}
void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
    {
      TIM_Cmd(TIM3, ENABLE);
    }    
  }   
}

void TIM3_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
  {
    if(tp_flag<4)
    {
      tp_x[tp_flag]=TP_MeasureX();
      tp_y[tp_flag]=TP_MeasureY();
      if((-10<(tp_x[tp_flag]-tp_x[tp_flag-1])<10)&&(-10<(tp_y[tp_flag]-tp_y[tp_flag-1])<10))
      {tp_flag+=1;}
      else
      {tp_flag=0;}
    }
    else
    {
      tp_flag=0;
      TIM_Cmd(TIM3, DISABLE);
     
      u16 j=0,i=0;
      uint16_t temp=0;
      for(j=0;j<=4;j++)
      {
        for (i=0;i<4-j;i++)
        {
          if (tp_x[i]>tp_x[i+1])
          {
            temp=tp_x[i];
            tp_x[i]=tp_x[i+1];
            tp_x[i+1]=temp;
          }
        }
      }
      for(j=0;j<=4;j++)
      {
        for (i=0;i<4-j;i++)
        {
          if (tp_y[i]>tp_y[i+1])
          {
            temp=tp_y[i];
            tp_y[i]=tp_y[i+1];
            tp_y[i+1]=temp;
          }
        }
      }
      x=(tp_x[1]+tp_x[2]+tp_x[3])/3;
      y=(tp_y[1]+tp_y[2]+tp_y[3])/3;
     if((x<800)&&(y<479))
     {
       schedule(x,y);
     }
     return;
    }
  }
}


void DMA1_Channel5_IRQHandler(void)
{
  ;
}

void DMA1_Channel6_IRQHandler(void)
{
  ;
}


void DMA1_Channel1_IRQHandler(void)
{
  DMA_ClearITPendingBit(DMA1_IT_TC1);
  
}
#if 1
void DMA2_Channel4_5_IRQHandler(void)
{
  DMA_ClearITPendingBit(DMA2_IT_TC5);
  //ADC_DMACmd(ADC3, DISABLE);
}

#endif




void ADC1_2_IRQnHandler(void)
{
;
}

//外部中断服务程序
void EXTI15_10_IRQHandler(void)
{
  ;   
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

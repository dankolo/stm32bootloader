/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body.
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
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <stdio.h>
#include "stm3210e_eval_lcd.h"
#include "touch.h"
#include "fatfs.h"
#include "ff.h"
#include <assert.h>
#include "RTC_Time.h"
/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @param  None
  * @retval None
  */



struct tm time_now;
unsigned char time_buffer[20]="2011-10-20 10:05:30";
unsigned char *get_time_now();

void LCD_Set_Time(unsigned char *set_buffer);


void NVIC_Configuration(void);
void SetSysClockTo72(void);
void LED_GPIO_Configuration(void);
void TIM2_Config(void);
void TIM3_Config(void);







void delay(void)//延时函数，流水灯显示用
{
 uint32_t i;
 for(i=0;i<0x1FFFF;i++);
}




/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
char *str;
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
  
  
       
  SetSysClockTo72();
  RTC_Config();
  NVIC_Configuration();
  STM3210E_LCD_Init();
  Touch_Config();
  LED_GPIO_Configuration();
  TIM2_Config();
  TIM3_Config();
//  LCD_Set_Time(time_buffer);
//  creat_file("0123456789876543210.txt");
  
  
//  format_disk(0,0,512);
//  get_disk_info();
//  list_file();
//  str=read_file("/","test.txt",0,32);
//  printf("\n\r");
//  printf(str);
//  delete_file("/","test.txt");
//  creat_file("test.txt");  
//  delete_file("/","hello.txt");
//  creat_file("hello.txt");
//  delay();
//  edit_file("/","hello.txt","creat_file is ok!",0x00);
//  str=read_file("/","test.txt",0x00,512);
//  printf("\n\r");
//  printf(str);
//  printf("\n\r");
  
//  list_file();
  
  
  

  uint16_t colour=4096;
  while(colour!=0)
  {
    LCD_Clear(colour);
    colour-=512;
  }
  #if 0
  LCD_Clear(0xf000);

  LCD_DrawUniLine(0,0,799,479,0xaaaa);
  LCD_DrawUniLine(0,479,799,0,0xaaaa);
  LCD_DrawUniLine(100,100,700,100,0xaaaa);
  LCD_DrawUniLine(100,240,700,240,0xaaaa);
  LCD_DrawUniLine(100,400,700,400,0xaaaa);
  LCD_DrawUniLine(100,100,100,400,0xaaaa);
  LCD_DrawUniLine(400,100,400,400,0xaaaa);
  LCD_DrawUniLine(700,100,700,400,0xaaaa);
  LCD_DrawFullRect(100,200,500,300,LCD_COLOR_RED,0);
  LCD_str(0,100,"nice to meet you!你好",12,0xaaaa,0x00ff);
  LCD_str(0,300,"nice to meet you!你好",16,0xaaaa,0x00ff);
  LCD_DrawFullCircle( 100,  100,  3,  0xaaaa, 1);
  LCD_DrawFullCircle( 100,  240,  3,  0xaaaa, 1);  
  LCD_DrawFullCircle( 100,  400,  3,  0xaaaa, 1);
  LCD_DrawFullCircle( 400,  100,  3,  0xaaaa, 1);
  LCD_DrawFullCircle( 400,  240,  3,  0xaaaa, 1);
  LCD_DrawFullCircle( 400,  400,  3,  0xaaaa, 1);
  LCD_DrawFullCircle( 700,  100,  3,  0xaaaa, 1);  
  LCD_DrawFullCircle( 700,  240,  3,  0xaaaa, 1);
  LCD_DrawFullCircle( 700,  400,  3,  0xaaaa, 1);

#endif
  
  
    /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PD0 or PD2 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */
  
  while (1)
  {
    get_time_now();
    LCD_str(10,100,time_buffer,24,0xaaaa,0x00ff);
    delay();
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/




void SetSysClockTo72(void)
{
  
  ErrorStatus HSEStartUpStatus;
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
    
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); 

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}



/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0xF000);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  NVIC_InitTypeDef NVIC_InitStructure;
  
  
  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
  
  
  
  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}


void TIM2_Config(void)
{
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  /* TIM2 configuration */
  TIM_TimeBaseStructure.TIM_Period = 24000-1;          
  TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/120000) - 1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* TIM IT enable */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM2->EGR |=(1<<0);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

void TIM3_Config(void)
{
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  /* TIM3 configuration */
  TIM_TimeBaseStructure.TIM_Period = 2000-1;          
  TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/120000) - 1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* TIM IT enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  
  TIM3->EGR |=(1<<0);

  /* TIM3 enable counter */
//  TIM_Cmd(TIM3, ENABLE);
}


void LED_GPIO_Configuration(void)
{
  /* GPIOF Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOC Configuration:Pin6, 7, 8 and 9 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOF, &GPIO_InitStructure);
}


unsigned char *get_time_now()
{

  time_now = Time_GetCalendarTime();//获得当前时间
  //转换年月日时分秒
  time_buffer[0]=time_now.tm_year/1000+'0';
  time_buffer[1]=(time_now.tm_year%1000)/100+'0';
  time_buffer[2]=(time_now.tm_year%100)/10+'0';
  time_buffer[3]=time_now.tm_year%10+'0';
  //年
  time_buffer[5]=((time_now.tm_mon+1)%100)/10+'0';
  time_buffer[6]=(time_now.tm_mon+1)%10+'0';
  //月,时间戳是0-11,显示+1
  time_buffer[8]=(time_now.tm_mday%100)/10+'0';
  time_buffer[9]=time_now.tm_mday%10+'0';
  //日
  time_buffer[11]=(time_now.tm_hour%100)/10+'0';
  time_buffer[12]=time_now.tm_hour%10+'0';
  //时
  time_buffer[14]=(time_now.tm_min%100)/10+'0';
  time_buffer[15]=time_now.tm_min%10+'0';
  //分
  time_buffer[17]=(time_now.tm_sec%100)/10+'0';
  time_buffer[18]=time_now.tm_sec%10+'0';
  //秒

  return time_buffer;
}

void LCD_Set_Time(unsigned char *set_buffer)
{
  time_now.tm_year = (*set_buffer-'0')*1000+(*(set_buffer+1)-'0')*100+(*(set_buffer+2)-'0')*10+(*(set_buffer+3)-'0');
  time_now.tm_mon =  (*(set_buffer+5)-'0')*10+(*(set_buffer+6)-'0'-1);
  time_now.tm_mday = (*(set_buffer+8)-'0')*10+(*(set_buffer+9)-'0');
  time_now.tm_hour = (*(set_buffer+11)-'0')*10+(*(set_buffer+12)-'0');
  time_now.tm_min =  (*(set_buffer+14)-'0')*10+(*(set_buffer+15)-'0');
  time_now.tm_sec =  (*(set_buffer+17)-'0')*10+(*(set_buffer+18)-'0');
  Time_SetCalendarTime(time_now);
}
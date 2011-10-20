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
#include "mass_storage.h"
#include "sdcard.h"
#include "RTC_Time.h"
/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @param  None
  * @retval None
  */


/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#define ApplicationAddress       ((uint32_t)0x800F000)
#define FLASH_PAGE_SIZE    ((uint16_t)0x800)
//#define BANK1_WRITE_START_ADDR  ((uint32_t)0x0800F000)
//#define BANK1_WRITE_END_ADDR    ((uint32_t)0x0807FFFF)
uint32_t BANK1_WRITE_START_ADDR=0x0800F000;
uint32_t BANK1_WRITE_END_ADDR;
uint32_t APP_PROGRAM_FLAG=0x00;
uint32_t Jump_To_App_flag=0x00;
uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t NbrOfPage = 0x00;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
volatile TestStatus MemoryProgramStatus = PASSED;

struct tm time_now;
unsigned char time_buffer[20]="2011-10-20 10:05:30";
unsigned char *get_time_now();
void LCD_Set_Time(unsigned char *set_buffer);



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction Jump_To_Application;
__IO uint32_t JumpAddress;
void Run_App(void);

void NVIC_Configuration(void);
void SetSysClockTo72(void);
void TIM2_Config(void);
void TIM3_Config(void);

void delay(void)//延时函数，流水灯显示用
{
 uint32_t i;
 for(i=0;i<0x9fFFFF;i++);
}

      FILINFO file_info;
      FILINFO *info;
      DWORD	app_size;
void stat_file(const TCHAR *dir,const TCHAR *file_name)
{
      FATFS fs;
      FIL	file;
      FRESULT res;
      info=&file_info;
      res = f_mount(0,&fs);
      res = f_chdir(dir);
      res = f_stat(file_name,info);
      app_size=file_info.fsize;
      f_mount(0,NULL);
}

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
  Mass_Storage_Start();
  NVIC_Configuration();
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); 
  STM3210E_LCD_Init();
  Touch_Config();  
  delay();   
  TIM2_Config();
  TIM3_Config();  
  stat_file("/","app.bin");  
  LCD_Clear(LCD_COLOR_BLACK);
  LCD_str(144,50,"司机控制器测试仪", 64, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
//  LCD_str(176,150,"软件版本：ver0.1 beta", 24, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(176,200,"设计单位：武昌南机务段", 24, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(176,250,"技术支持：weiweijeff@gmail.com", 24, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_DrawFullRect( 24, 320, 320,  424,  LCD_COLOR_BLUE, 0);
  LCD_str(44,340,"升级软件", 64, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_DrawFullRect( 480, 320, 776,  424,  LCD_COLOR_BLUE, 0);
  LCD_str(500,340,"选择实验", 64, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
//  LCD_Set_Time("2011-10-20 10:50:30");
  while (1)
  {
    get_time_now();
    LCD_str(176,150,time_buffer, 24, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
    if(APP_PROGRAM_FLAG==0x01)
    {
      LCD_Clear(LCD_COLOR_BLACK);
      LCD_str(200,50,"开始升级，请等待...", 32, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
      uint32_t m_size,n_size,k,p,offset=0;
      
      
      /* Porgram FLASH Bank1 ********************************************************/
      /* Unlock the Flash Bank1 Program Erase controller */
      FLASH_UnlockBank1();
      
      /* Define the number of page to be erased */
//      NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
      NbrOfPage = app_size / FLASH_PAGE_SIZE +1;
      
      /* Clear All pending flags */
      FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
      
      /* Erase the FLASH pages */
      for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
      {
        FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
      }   
      
      
      /* Program Flash Bank1 */
      Address = BANK1_WRITE_START_ADDR;
      BANK1_WRITE_END_ADDR=BANK1_WRITE_START_ADDR+app_size;
      m_size=app_size/512;
      n_size=app_size%512;
      
      
      
      while((Address < BANK1_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE))
      {
        
        char *app_buffer;
        for(k=0;k<=m_size;k++)
        {
          app_buffer=read_file("/","app.bin",offset,512);
          for(p=0;p<512;p+=2)
          {
            FLASHStatus=FLASH_ProgramHalfWord(Address, ((uint16_t)(*app_buffer)|((uint16_t)(*(app_buffer+1)))<<8));
            Address+=2;
            app_buffer+=2;
          } 
          offset+=512;
        }
        app_buffer=read_file("/","app.bin",offset,n_size);
        if(n_size%2)
        {
          *(app_buffer+n_size+1)=0xff;
          for(p=0;p<n_size+1;p+=2)
          {
            FLASHStatus=FLASH_ProgramHalfWord(Address, ((uint16_t)(*app_buffer)|((uint16_t)(*(app_buffer+1)))<<8));
            Address+=2;
            app_buffer+=2;
          }
          FLASHStatus=FLASH_ProgramHalfWord(Address, (uint16_t)((*app_buffer)));
        }
        else
        {
          for(p=0;p<n_size;p+=2)
          {
            FLASHStatus=FLASH_ProgramHalfWord(Address, ((uint16_t)(*app_buffer)|((uint16_t)(*(app_buffer+1)))<<8));
            Address+=2;
            app_buffer+=2;
          }
        }
                
      }
      FLASH_LockBank1();
      
      LCD_Clear(LCD_COLOR_BLACK);
      LCD_str(10,50,"软件升级成功！请稍候...", 64, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
      delay();
      APP_PROGRAM_FLAG=0x00;      
      LCD_Clear(LCD_COLOR_BLACK);
      LCD_str(144,50,"司机控制器测试仪", 64, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
      LCD_str(176,150,"软件版本：ver0.1 beta", 24, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
      LCD_str(176,200,"设计单位：武昌南机务段", 24, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
      LCD_str(176,250,"技术支持：weiweijeff@gmail.com", 24, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
      LCD_DrawFullRect( 24, 320, 320,  424,  LCD_COLOR_BLUE, 0);
      LCD_str(44,340,"升级软件", 64, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
      LCD_DrawFullRect( 480, 320, 776,  424,  LCD_COLOR_BLUE, 0);
      LCD_str(500,340,"选择实验", 64, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
#if 0   //     Check
      /* Check the correctness of written data */
      Address = BANK1_WRITE_START_ADDR;
      
      while((Address < BANK1_WRITE_END_ADDR) && (MemoryProgramStatus != FAILED))
      {
        if((*(__IO uint32_t*) Address) != Data)
        {
          MemoryProgramStatus = FAILED;
        }
        Address += 4;
      }
#endif       //Check
    }
    
    
    if(Jump_To_App_flag==0x01)
    {
      Run_App();
    }
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


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}


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
//  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0);
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0); 
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

  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
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


void Run_App(void)
{    
  JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
  Jump_To_Application = (pFunction) JumpAddress;

  /* Initialize user application's Stack Pointer */
  __set_MSP(*(__IO uint32_t*) ApplicationAddress); 

  Jump_To_Application();
}






#if 0
void Set_Channel(unsigned char x)
{
  if((Channel[x]>>3)==0)
  {GPIO_ResetBits(GPIOF,GPIO_Pin_6);}
  else
  {GPIO_SetBits(GPIOF,GPIO_Pin_6);}
    if(((Channel[x]&0x04)>>2)==0)
  {GPIO_ResetBits(GPIOF,GPIO_Pin_7);}
  else
  {GPIO_SetBits(GPIOF,GPIO_Pin_7);}
    if(((Channel[x]&0x02)>>1)==0)
  {GPIO_ResetBits(GPIOF,GPIO_Pin_9);}
  else
  {GPIO_SetBits(GPIOF,GPIO_Pin_9);}
   if((Channel[x]&0x01)==0)
  {GPIO_ResetBits(GPIOF,GPIO_Pin_10);}
  else
  {GPIO_SetBits(GPIOF,GPIO_Pin_10);}
}
#endif



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
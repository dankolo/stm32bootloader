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
#include <string.h> 
#include "commonality.h"





#if 0
u8 files_name[16][63];
u8 num=0;
u16 lcd_y=0;

FRESULT scan_files (
    char* path        /* Start node to be scanned (also used as work area) */
)
{
  
  FATFS fs;
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
    
    char *fn;   /* This function is assuming non-Unicode cfg. */
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

res = f_mount(0,&fs);
    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fname[0] == '.') continue;             /* Ignore dot entry */
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                sprintf(&path[i], "/%s", fn);
                res = scan_files(path);
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* It is a file. */
                //printf("%s/%s\n", path, fn);              
              memcpy(files_name[num],fn,strlen(fn));
              num+=1;
            }
        }
    }
f_mount(0,NULL);
    return res;
}
#endif 


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
char *str;

  u8 chx=0;
int main(void)
{
  
  sys_flag=main_panel;
  RCC_Configuration();
  RTC_Config();
  NVIC_Configuration();
  Touch_Config();
  PowerA_GPIO_Config();
  CD4067_GPIO_Config(); 
  STM3210E_LCD_Init();  
  TIM2_Config();
  TIM3_Config();
  LCD_Clear(LCD_COLOR_CYAN);
  ADC_GPIO_Config();
  
  
//  ADC3_DMA_Config();
//  ADC3_Config();
  
  
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



  

  
#if 0  
  scan_files("/");
  while(num--!=0)
  {
    LCD_str(0,lcd_y,files_name[num], 16, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
    lcd_y+=16;
  }
#endif  
  
    /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PD0 or PD2 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */
   
  
  
 ADC_R_DMA_Config();
 ADC_V_DMA_Config();
 ADC_R_Config();
 ADC_V_Config();
// PowerA_DIS();
 CD4067_EN();
 PowerA_EN();
 delay(0xffff); 
 read_ref(); 
 
 while (1)
 { 
  while(sys_flag==main_panel)
    {
      draw_main_panel();
      while(sys_flag==main_panel)
      {
        LCD_str(534,0,get_time_now(),24,LCD_COLOR_CYAN,LCD_COLOR_BLACK);
        delay(0xffff);
      }
    }
   while(sys_flag==set_ref)
   {
     TP_stop();
     draw_ref_manager();
     TP_restart();
     while(sys_flag==set_ref);
   }
    while(sys_flag==set_time)
    {
      TP_stop();
      draw_time_manager();
      TP_restart();
      while(sys_flag==set_time);
    }
    while(sys_flag==tks640k1)
    {
      TP_stop();
      S640K1_INIT();
      draw_s640k1();
      TP_restart();
      while(sys_flag==tks640k1);
      
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








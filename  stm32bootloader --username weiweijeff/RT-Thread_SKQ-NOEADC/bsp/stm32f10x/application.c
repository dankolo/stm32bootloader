
/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>
#endif

#include "led.h"
#include "lcd.h"
#include "touch.h"
#include "gel.h"
#include "analog.h"


ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[ 512 ];
static struct rt_thread led_thread;
static void led_thread_entry(void* parameter)
{
    rt_hw_led_init();
#if 0
/* �����������������󣬽������л��������̣߳�����Ӧ�ж� */
	rt_enter_critical();
        ADC_GPIO_Config();
        CD4067_GPIO_Config();
        PowerA_GPIO_Config();
        PowerA_EN();
        CD4067_EN();
        Set_Scan_Channel(0);
        ADC_R_DMA_Config();        
        ADC_R_Config();
        ADC_V_DMA_Config();        
        ADC_V_Config();
        rt_int16_t *p,*q;
        

    while (1)
    {
      ADC_R_Restart();
      ADC_R_DMA_Config();
      while(!DMA_GetFlagStatus(ADC_R_DMA_Flag));
      p=Get_ADC_R_Value();
      
      ADC_V_Restart();
      ADC_V_DMA_Config();
      while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
      q=Get_ADC_V_Value();
      rt_kprintf("%d\t%d\r\n",*p,*q);
//      LCD_Clear(Blue);
//      rt_hw_led_on(0);
//        rt_thread_delay( 200 ); /* sleep 0.5 second and switch to other thread */

//        rt_hw_led_off(0);
        rt_thread_delay( 50 );
    }
#endif
    
     while (1)
    {
      
      rt_hw_led_on(0);
        rt_thread_delay( 200 ); /* sleep 0.5 second and switch to other thread */

        rt_hw_led_off(0);
        rt_thread_delay( RT_TICK_PER_SECOND/2 );
    }
}






static rt_uint8_t touch_stack[ 4096 ];
static struct rt_thread touch_thread;
static void touch_thread_entry(void* parameter)
{
  read_ref();
  double KX1=0.221578, KX2=0.000183458, KX3=-54.4787, KY1=-0.000401399, KY2=0.135246, KY3=-48.2589;
  rt_int16_t x=0,y=0;
  Touch_Config();
  
  ADC_GPIO_Config();
  CD4067_GPIO_Config();
  PowerA_GPIO_Config();
  
  ADC_R_Config();
  ADC_V_Config();
  ADC_R_stop();
  ADC_V_stop();
  ADC_R_DMA_Config();
  ADC_V_DMA_Config();
 

 
  
//  LCD_DrawFullCircle( 400, 240, 230,  Yellow,  0);
  /* �����������������󣬽������л��������̣߳�����Ӧ�ж� */
  rt_enter_critical();
  draw_main_panel();
  /* ���������� */
  rt_exit_critical();
  while (1)
  {
    rt_thread_delay(10);
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
    {
      rt_thread_delay(5);
      if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
      {
        x=TP_MeasureX();
        y=TP_MeasureY();
        x=(signed short int)(KX1*(x)+KX2*(y)+KX3+0.5);
        y=(signed short int)(KY1*(x)+KY2*(y)+KY3+0.5);
        x=800-x;
//        LCD_DrawFullCircle( x, y, 2,  Red,  1);
        touch_schedule(x,y);
      }
    }
  }
}
















void rt_init_thread_entry(void* parameter)
{
/* Filesystem Initialization */
#ifdef RT_USING_DFS
	{
		/* init the device filesystem */
		dfs_init();

#ifdef RT_USING_DFS_ELMFAT
		/* init the elm chan FatFs filesystam*/
		elm_init();

		/* mount sd card fat partition 1 as root directory */
		if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
		{
			rt_kprintf("File System initialized!\n");
		}
		else
			rt_kprintf("File System initialzation failed!\n");
#endif
	}
#endif

/* LwIP Initialization */
#ifdef RT_USING_LWIP
	{
		extern void lwip_sys_init(void);

		/* register ethernetif device */
		eth_system_device_init();

#ifdef STM32F10X_CL
		rt_hw_stm32_eth_init();
#else
	/* STM32F103 */
	#if STM32_ETH_IF == 0
			rt_hw_enc28j60_init();
	#elif STM32_ETH_IF == 1
			rt_hw_dm9000_init();
	#endif
#endif

		/* re-init device driver */
		rt_device_init_all();

		/* init lwip system */
		lwip_sys_init();
		rt_kprintf("TCP/IP initialized!\n");
	}
#endif

#ifdef RT_USING_RTGUI
	{
	    extern void rtgui_startup();
	    extern void rt_hw_lcd_init();
	    extern void rtgui_touch_hw_init(void);

		rt_device_t lcd;

		/* init lcd */
		rt_hw_lcd_init();

		/* init touch panel */
		rtgui_touch_hw_init();

		/* re-init device driver */
		rt_device_init_all();

		/* find lcd device */
		lcd = rt_device_find("lcd");

		/* set lcd device as rtgui graphic driver */
		rtgui_graphic_set_device(lcd);

		/* startup rtgui */
		rtgui_startup();
	}
#endif /* #ifdef RT_USING_RTGUI */
}


int rt_application_init()
{
	rt_thread_t init_thread;

	rt_err_t result;

    /* init led thread */
	result = rt_thread_init(&led_thread,
		"led",
		led_thread_entry, RT_NULL,
		(rt_uint8_t*)&led_stack[0], sizeof(led_stack), 25, 20);
	if (result == RT_EOK)
	{
        rt_thread_startup(&led_thread);
	}
        
        result = rt_thread_init(&touch_thread,
		"touch",
		touch_thread_entry, RT_NULL,
		(rt_uint8_t*)&touch_stack[0], sizeof(touch_stack), 10, 20);
	if (result == RT_EOK)
	{
        rt_thread_startup(&touch_thread);
	}
        
        
        
#if (RT_THREAD_PRIORITY_MAX == 32)
	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								2048, 2, 20);
#else
	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								2048, 80, 20);
#endif

	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);

	return 0;
}

/*@}*/

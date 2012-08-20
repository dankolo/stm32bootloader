/*
 * File      : stm3210e_eval_lcd.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-11-01     Bernard      the first version
 */

#include <rtthread.h>

#include "stm32f10x.h"
#include "stm32f10x_fsmc.h"
#include "lcd.h"

//#ifdef RT_USING_RTGUI
#if 1
#include <rtgui/driver.h>
#include <rtgui/color.h>
#include <dfs_posix.h>


rt_uint16_t BK_PWM=0x3f;
rt_uint16_t coy_src=0x00;
rt_uint16_t cur_page=0x00;
rt_uint16_t opt_page=0x00;


/*
 * LCD Driver
 * RGB mode (5-6-5)
 * 240 x 320 pixel LCD
 */
/* convert rtgui color to hardware color, rgb 5-6-5 */
typedef struct
{
  rt_uint16_t LCD_REG;
  rt_uint16_t LCD_RAM;
} LCD_TypeDef;

/* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */
#define LCD_BASE        ((rt_uint32_t)(0x60000000 | 0x0C000000))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

#define ABS(X)  ((X) > 0 ? (X) : -(X))

/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
rt_inline void LCD_WriteRAM(rt_uint16_t RGB_Code)
{
	/* Write 16-bit GRAM Reg */
//	LCD->LCD_RAM = (RGB_Code>>8);
        LCD->LCD_RAM = RGB_Code;
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteReg(rt_uint8_t LCD_Reg, rt_uint16_t LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD_WriteRAM(LCD_RegValue);
}

/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
rt_uint16_t LCD_ReadReg(rt_uint8_t LCD_Reg)
{
  /* Write 16-bit Index (then Read Reg) */
//  LCD->LCD_REG = LCD_Reg;
  /* Read 16-bit Reg */
//  return (LCD->LCD_RAM);
  return 0;
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : Prepare to write to the LCD RAM.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
	LCD->LCD_REG = PIXELS;
}



/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
rt_inline rt_uint16_t LCD_ReadRAM(void)
{
	/* Write 16-bit Index (then Read Reg) */
//	LCD->LCD_REG = R34; /* Select GRAM Reg */
	/* Read 16-bit Reg */
//	return LCD->LCD_RAM;
  return 0;
}

/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : Enables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{
	/* Display On */
//	LCD_WriteReg(0x26, 0x3C); /* 262K color and display ON */
}

/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : Disables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{
	/* Display Off */
//	LCD_WriteReg(0x26, 0x0);
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(rt_uint16_t x, rt_uint16_t y)
{
//	LCD_WriteReg(0x06, (x & 0xff00) >> 8);
//	LCD_WriteReg(0x07, (x & 0x00ff));

//	LCD_WriteReg(0x02, (y & 0xff00) >> 8);
//	LCD_WriteReg(0x03, (y & 0x00ff));
  LCD_WriteReg(CUR_X,x); // .............. CUR_X  
  LCD_WriteReg(CUR_Y,y); // .............. CUR_Y
}

/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD Control lines (FSMC Pins) in alternate function
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |
                         RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG |
                         RCC_APB2Periph_AFIO, ENABLE);
  /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
     PD.10(D15), PD.14(D0), PD.15(D1) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  /* Set PF.00(A0 (RS)) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
 //LCD_RESET_PIN 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_FSMCConfig
* Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FSMCConfig(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;

	/*-- FSMC Configuration ------------------------------------------------------*/
	/*----------------------- SRAM Bank 4 ----------------------------------------*/
	/* FSMC_Bank1_NORSRAM4 configuration */
	p.FSMC_AddressSetupTime = 1;
	p.FSMC_AddressHoldTime = 0;
	p.FSMC_DataSetupTime = 2;
	p.FSMC_BusTurnAroundDuration = 0;
	p.FSMC_CLKDivision = 0;
	p.FSMC_DataLatency = 0;
	p.FSMC_AccessMode = FSMC_AccessMode_A;

	/* Color LCD configuration ------------------------------------
	 LCD configured as follow:
	    - Data/Address MUX = Disable
	    - Memory Type = SRAM
	    - Data Width = 16bit
	    - Write Operation = Enable
	    - Extended Mode = Enable
	    - Asynchronous Wait = Disable */
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
        FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	/* BANK 4 (of NOR/SRAM Bank 1~4) is enabled */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}

void rt_hw_lcd_update(rtgui_rect_t *rect)
{
	/* nothing */
}

rt_uint8_t * rt_hw_lcd_get_framebuffer(void)
{
	return RT_NULL;
}

void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    unsigned short p;

	/* get color pixel */
	p = rtgui_color_to_565p(*c);

	LCD_SetCursor(x, y);

	/* Prepare to write GRAM */
	LCD_WriteRAM_Prepare();
	LCD_WriteRAM(p);
}

void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
//	rt_uint16_t hc;

//	LCD_SetCursor(y, x);
//	hc = LCD_ReadRAM();
//	*c = rtgui_color_from_565p(hc);
}

void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_uint16_t hc,m,n=0;
        m=x2-x1;

	hc = rtgui_color_to_565p(*c);

	LCD_SetCursor(x1, y);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

	while (n < m)
	{
		LCD_WriteRAM(hc);
		n++;
	}
}

void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2)
{
	rt_uint16_t hc;

	hc = rtgui_color_to_565p(*c);

	while (y1 < y2)
	{
		LCD_SetCursor(x, y1); 
                y1 ++;

		/* Prepare to write GRAM */
		LCD_WriteRAM_Prepare();
		LCD_WriteRAM(hc);
	}
}

void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_uint16_t *ptr;

	/* get pixel */
	ptr = (rt_uint16_t*) pixels;

	LCD_SetCursor(x1, y);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

	while (x1 < x2)
	{
		LCD_WriteRAM(*ptr);
		x1 ++; 
                ptr ++;
	}
}
#if 0
struct rtgui_graphic_driver _rtgui_lcd_driver =
{
	"lcd",
	2,
	800,
	480,
	rt_hw_lcd_update,
	rt_hw_lcd_get_framebuffer,
	rt_hw_lcd_set_pixel,
	rt_hw_lcd_get_pixel,
	rt_hw_lcd_draw_hline,
	rt_hw_lcd_draw_vline,
	rt_hw_lcd_draw_raw_hline
};
#endif


#define Delay(v)									\
	{												\
		volatile  rt_uint32_t index;				\
		for (index = 0; index < v * 100; index ++)	\
			;										\
	}



void ch_BK(u16 p)
{
  BK_PWM=p;
  LCD_WriteReg(PREF,(BK_PWM+(coy_src<<6)+(cur_page<<9)+(opt_page<<12)));
}

void ch_coy_src(u16 p)
{
  cur_page=p;
  LCD_WriteReg(PREF,(BK_PWM+(coy_src<<6)+(cur_page<<9)+(opt_page<<12)));
}
void ch_cur_page(u16 p)
{
  BK_PWM=p;
  LCD_WriteReg(PREF,(BK_PWM+(coy_src<<6)+(cur_page<<9)+(opt_page<<12)));
}
void ch_opt_page(u16 p)
{
  opt_page=p;
  LCD_WriteReg(PREF,(BK_PWM+(coy_src<<6)+(cur_page<<9)+(opt_page<<12)));
}

void LCD_Clear(rt_uint16_t Color)
{
  uint32_t index;
    
  LCD_SetCursor(0,0);
  LCD_WriteReg(END_X,799); // ............ END_X
  LCD_WriteRAM_Prepare();
  
  
  for(index = 0; index < 384000; index++)
  {
    LCD_WriteRAM(Color);
  }  
}

void rt_hw_lcd_init()
{
	/* Configure the LCD Control pins --------------------------------------------*/
	LCD_CtrlLinesConfig();
        
	/* Configure the FSMC Parallel interface -------------------------------------*/
	LCD_FSMCConfig();
        LCD_WriteReg(PREF,(BK_PWM+(coy_src<<6)+(cur_page<<9)+(opt_page<<12)));
        //LCD_WriteReg(MIRROR,0x03);
        //LCD_Clear(Blue2);

	

	/* add lcd driver into graphic driver */
//	rtgui_list_init(&_rtgui_lcd_driver.list);
//	rtgui_graphic_driver_add(&_rtgui_lcd_driver);
}

#endif
#if 0
void stm3210e_rtgui_init()
{
	rtgui_rect_t rect;

	rtgui_system_server_init();

	/* register dock panel */
	rect.x1 = 0;
	rect.y1 = 0;
	rect.x2 = 320;
	rect.y2 = 25;
	rtgui_panel_register("info", &rect);

	/* register main panel */
	rect.x1 = 0;
	rect.y1 = 25;
	rect.x2 = 320;
	rect.y2 = 240;
	rtgui_panel_register("main", &rect);
	rtgui_panel_set_default_focused("main");

	rt_hw_lcd_init();

	info_init();
	today_init();
}

#endif






void DrawPixel(rt_uint16_t x, rt_uint16_t y, rt_uint16_t colour)
{

  LCD_WriteReg(CUR_X,x); // .............. CUR_X  
  LCD_WriteReg(CUR_Y,y); // .............. CUR_Y
  LCD->LCD_REG=PIXELS; // .............. PIXELS
//  LCD->LCD_RAM = colour>>8;
  LCD->LCD_RAM = colour;
}


/**
  * @brief  Displays an uni line (between two points).
  * @param  x1: specifies the point 1 x position.
  * @param  y1: specifies the point 1 y position.
  * @param  x2: specifies the point 2 x position.
  * @param  y2: specifies the point 2 y position.
  * @retval None
  */
void LCD_DrawUniLine(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2, rt_uint16_t colour)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    DrawPixel(x, y, colour);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}

/**
  * @brief  Displays a full rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: rectangle height.
  * @param  Width: rectangle width.
  * @retval None
  */
void LCD_DrawFullRect(rt_uint16_t Xpos, rt_uint16_t Ypos, rt_uint16_t Xend, rt_uint16_t Yend, rt_uint16_t Rect_colour,rt_uint16_t full_or_not)
{
  if(full_or_not!=0)
  {
    LCD_WriteReg(CUR_X,Xpos);
    LCD_WriteReg(CUR_Y,Ypos);
    LCD_WriteReg(END_X,Xend);
    LCD->LCD_REG=PIXELS;
    uint32_t index,index_end;
    index_end = (Xend-Xpos+1)*(Yend-Ypos+1);
    for(index = 0; index < index_end; index++)
    {
      LCD_WriteRAM(Rect_colour);
    }
  }
  else
  {
    LCD_DrawUniLine(Xpos, Ypos, Xend, Ypos, Rect_colour);
    LCD_DrawUniLine(Xpos, Yend, Xend, Yend, Rect_colour);
    LCD_DrawUniLine(Xpos, Ypos, Xpos, Yend, Rect_colour);
    LCD_DrawUniLine(Xend, Ypos, Xend, Yend, Rect_colour);
  }
}


static void LCD_DrawLine_HORIZONTAL(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint16_t colour)
{
  LCD_WriteReg(CUR_X,Xpos);
  LCD_WriteReg(CUR_Y,Ypos);
  LCD->LCD_REG=PIXELS;
  uint32_t index;
  for(index = 0; index < Length; index++)
  {
    LCD_WriteRAM(colour);
  }
}

void LCD_DrawFullCircle(rt_uint16_t Xpos, rt_uint16_t Ypos, rt_uint16_t Radius, rt_uint16_t Circle_colour, rt_uint16_t full_or_not)
{
  int32_t  D;    /* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;    
  
  
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  while (CurX <= CurY)
  {
    if(full_or_not!=0)
    {
      LCD_DrawLine_HORIZONTAL(Xpos - CurX, Ypos + CurY, 2*CurX, Circle_colour);
      LCD_DrawLine_HORIZONTAL(Xpos - CurX, Ypos - CurY, 2*CurX, Circle_colour);
      
      LCD_DrawLine_HORIZONTAL(Xpos - CurY, Ypos + CurX, 2*CurY, Circle_colour);
      LCD_DrawLine_HORIZONTAL(Xpos - CurY, Ypos - CurX, 2*CurY, Circle_colour);
    }
    else
    {
      DrawPixel(Xpos + CurX, Ypos + CurY, Circle_colour);
      DrawPixel(Xpos + CurX, Ypos - CurY, Circle_colour);
      DrawPixel(Xpos - CurX, Ypos + CurY, Circle_colour);
      DrawPixel(Xpos - CurX, Ypos - CurY, Circle_colour);
      DrawPixel(Xpos + CurY, Ypos + CurX, Circle_colour);
      DrawPixel(Xpos + CurY, Ypos - CurX, Circle_colour);
      DrawPixel(Xpos - CurY, Ypos + CurX, Circle_colour);
      DrawPixel(Xpos - CurY, Ypos - CurX, Circle_colour);
    }
    
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}


























static rt_uint8_t buffer[512]={0};

/************************************************************************/
//函数名称:void write_CN16(u16 x,u16 y,uc8 *p,u16 charColor,u16 bkColor)
//用途:液晶屏上坐标x,y写16*16汉字
//返回:无
//用法:write_CN16(10,12,"哦",16,Red,Blue)
/************************************************************************/
void LCD_CN(rt_uint16_t x,rt_uint16_t y,const rt_uint8_t *p,rt_uint8_t fon, rt_uint16_t charColor,rt_uint16_t bkColor)
{
  int fd;
  
  unsigned char region   = *p-0xa0;//得到区号  gb2312
  unsigned char location = *(p+1)-0xa0;//得到位号
  uint32_t index;//地址偏移量  
  uint16_t i,n,end_x;
  
  
  switch(fon)
  {
  case 12:
    {
      index = (94*(region-1)+location-1)*24;//地址偏移量  
      end_x=x+11;
      fd = open("/Chinese12.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 24);
      
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<24;n++)
      {
        for (i = 0; i < 8; i++)//
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
        for (i = 0; i < 4; i++)//
        {
          if (buffer[n+1] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
        n+=1;
      }
    }
    break;
  case 16:
    {
      index = (94*(region-1)+location-1)*32;//地址偏移量  
      end_x=x+15;
      
      fd = open("/Chinese16.FON", O_RDONLY, 0);//打开在根目录的字库
      if (fd < 0)
	{
		rt_kprintf("check: open file for read failed\n");
		return;
	}
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 32);
      
      
      
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<32;n++)
      {
        for (i = 0; i < 8; i++)//
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
      }
    }
    break;
  case 24:
    {
      index = (94*(region-1)+location-1)*72;//地址偏移量  
      end_x=x+23;
      
      fd = open("/Chinese24.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 72);
      
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<72;n++)
      {
        for (i = 0; i < 8; i++)//
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }        
      }
    }
    break;
  case 32:
    {
      index = (94*(region-1)+location-1)*128;//地址偏移量  
      end_x=x+31;
      fd = open("/Chinese32.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 128);
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<128;n++)
      {
        for (i = 0; i < 8; i++)//
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
      }
    }
    break;
    case 64:
    {
      index = (94*(region-1)+location-1)*448;//地址偏移量  
      end_x=x+63;
      fd = open("/Chinese64.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 448);
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<448;n++)
      {
        for (i = 0; i < 8; i++)//
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
      }
    }
    break;
  default:break;
  }
  
  close(fd);
}






void LCD_ASCII(u16 x,u16 y,u8 p,uint8_t fon, u16 charColor,u16 bkColor)
{
  int fd;
  uint32_t index;//地址偏移量  
  uint16_t i,n,end_x;
  
  
  switch(fon)
  {
  case 12:
    {
      index = p*12;
      end_x=x+5;
      
      fd = open("/ASCII12.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 12);
     
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<12;n++)
      {
        for (i = 0; i < 6; i++)
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
      }
    }
    break;
  case 16:
    {
      index = p*16;
      end_x=x+7;
      
      fd = open("/ASCII16.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 16);
      
      
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<16;n++)
      {
        for (i = 0; i < 8; i++)
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
      }
    }
    break;
  case 24:
    {
      index = p*48;
      end_x=x+11;
      
      fd = open("/ASCII24.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 48);      
      
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<48;n++)
      {
        for (i = 0; i < 8; i++)
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
        for (i = 0; i < 4; i++)
        {
          if (buffer[n+1] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
        n+=1;
      }
    }
    break;
  case 32:
    {
      index = p*64;
      end_x=x+15;
      
      fd = open("/ASCII32.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 64);
            
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<64;n++)
      {
        for (i = 0; i < 8; i++)
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
      }
    }
    break;
    case 64:
    {
      index = p*256;
      end_x=x+31;
      
      fd = open("/ASCII64.FON", O_RDONLY, 0);//打开在根目录的字库
      lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
      read(fd, buffer, 256);
      
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<256;n++)
      {
        for (i = 0; i < 8; i++)
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WriteRAM(charColor);//写有效点
          }
          else
          {
            LCD_WriteRAM(bkColor);//写底色
          }
        }
      }
    }
    break;
    
  default:break;
  }
  
  close(fd);
  
}


void LCD_str(u16 x, u16 y, unsigned char *str, uint8_t fon, u16 Color, u16 bkColor)
{
  u16 x_start=x;
  while (*str)
  {    
    if (*str < 128)
    {
      if((x+fon/2)>799)//一行写满了
      {
        x=x_start;
        y+=fon;
      }
      if((y+fon/2)>479)//整屏写满了
      {
        y=0;
      }
      if(*str=='\n')//手动换行
      {
        x=x_start;
        y+=fon;
        str+=1;
      }
      else
      {
        LCD_ASCII(x,y,*str,fon,Color,bkColor);
        x=x+fon/2;
        str+=1;
      }
    }
    else
    {
      if((x+fon)>799)//一行写满了
      {
        x=0;
        y+=fon;
      }
      if((y+fon)>479)//整屏写满了
      {
        y=0;
      }
      LCD_CN(x,y,str,fon,Color,bkColor);
      x+= fon;
      str+=2;
    }    
  }
}



/*********************************************************************************
//wdx:    1 Wingdings, 2 Wingdings2, 3 Wingdings3;
//wide:   0 40*48, 1 96*128
*********************************************************************************/

void LCD_WD(rt_uint16_t x,rt_uint16_t y,rt_uint8_t p,rt_uint8_t wdx,rt_uint8_t wide, rt_uint16_t charColor,rt_uint16_t bkColor)
{
  uint32_t index;//地址偏移量  
  uint16_t i,m,n,end_x;
  
  int fd;
  
  if(wide==0)
  {
    index = p*240;
    end_x=x+39;
    switch(wdx)
    {
    case 1:
      fd = open("/Wingdings.FON", O_RDONLY, 0);//打开在根目录的字库
      break;
    case 2:
      fd = open("/Wingdings2.FON", O_RDONLY, 0);//打开在根目录的字库
      break;
    case 3:
      fd = open("/Wingdings3.FON", O_RDONLY, 0);//打开在根目录的字库
      break;
    default:break;
    }
    lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
    read(fd, buffer, 240);
    LCD_WriteReg(CUR_X,x); // .............. CUR_x
    LCD_WriteReg(CUR_Y,y); // .............. CUR_y
    LCD_WriteReg(END_X,end_x); // ............ END_X
    LCD_WriteRAM_Prepare(); // .............. PIXELS
    for(n=0;n<240;n++)
    {
      for (i = 0; i < 8; i++)
      {
        if (buffer[n] & (0x01<<i))
        {
          LCD_WriteRAM(charColor);//写有效点
        }
        else
        {
          LCD_WriteRAM(bkColor);//写底色
        }
      }
    }
  }
  if(wide==1)
  {
    index = p*1536;
    end_x=x+95;
    switch(wdx)
    {
    case 1:
      fd = open("/BWingdings.FON", O_RDONLY, 0);//打开在根目录的字库
      break;
    case 2:
      fd = open("/BWingdings2.FON", O_RDONLY, 0);//打开在根目录的字库
      break;
    case 3:
      fd = open("/BWingdings3.FON", O_RDONLY, 0);//打开在根目录的字库
      break;
    default:break;
    }
    index-=384;
        y-=32;
    
      for(m=0;m<4;m++)
      {
        index+=384;
        y+=32;
        lseek(fd,  index,  DFS_SEEK_SET);//设置偏移量
        read(fd, buffer, 384);
        LCD_WriteReg(CUR_X,x); // .............. CUR_x
        LCD_WriteReg(CUR_Y,y); // .............. CUR_y
        LCD_WriteReg(END_X,end_x); // ............ END_X
        LCD_WriteRAM_Prepare(); // .............. PIXELS
        for(n=0;n<384;n++)
        {
          for (i = 0; i < 8; i++)
          {
            if (buffer[n] & (0x01<<i))
            {
              LCD_WriteRAM(charColor);//写有效点
            }
            else
            {
              LCD_WriteRAM(bkColor);//写底色
            }
          }
        }
      }
    
  }
  close(fd);
}

/*
 * File      : stm3210e_eval_lcd.h
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

#ifndef __LCD_H__
#define __LCD_H__

#include <rthw.h>
#include <rtthread.h>


#define CUR_Y      0x00
#define CUR_X      0x01
#define PIXELS     0x02
#define END_X      0x03
#define END_Y      0x04
#define PREF       0x05
#define RVS_MASK   0x06
#define MIRROR     0x07



/* LCD Control pins */
#define CtrlPin_NCS    GPIO_Pin_2   /* PB.02 */
#define CtrlPin_RS     GPIO_Pin_7   /* PD.07 */
#define CtrlPin_NWR    GPIO_Pin_15  /* PD.15 */

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


#define Horizontal     0x00
#define Vertical       0x01


void LCD_Clear(rt_uint16_t Color);

void DrawPixel(rt_uint16_t x, rt_uint16_t y, rt_uint16_t colour);
void LCD_DrawUniLine(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2, rt_uint16_t colour);
void LCD_DrawFullRect(rt_uint16_t Xpos, rt_uint16_t Ypos, rt_uint16_t Xend, rt_uint16_t Yend, rt_uint16_t Rect_colour,rt_uint16_t full_or_not);
void LCD_DrawFullCircle(rt_uint16_t Xpos, rt_uint16_t Ypos, rt_uint16_t Radius, rt_uint16_t Circle_colour, rt_uint16_t full_or_not);




void LCD_CN(rt_uint16_t x,rt_uint16_t y,const rt_uint8_t *p,rt_uint8_t fon, rt_uint16_t charColor,rt_uint16_t bkColor);
void LCD_ASCII(rt_uint16_t x,rt_uint16_t y,rt_uint8_t p,rt_uint8_t fon, rt_uint16_t charColor,rt_uint16_t bkColor);
void LCD_str(rt_uint16_t x, rt_uint16_t y, unsigned char *str, rt_uint8_t fon, rt_uint16_t Color, rt_uint16_t bkColor);
void LCD_WD(rt_uint16_t x,rt_uint16_t y,rt_uint8_t p,rt_uint8_t wdx,rt_uint8_t wide, rt_uint16_t charColor,rt_uint16_t bkColor);







#endif

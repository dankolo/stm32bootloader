#ifndef __TKS231_1_II_H
#define __TKS231_1_II_H

#include "stm32f10x.h"
#include "ili9320.h"
#include "touch.h"
#include "commonality.h"


void Set_Channel_TKS231_1_II(unsigned char x);
void draw_TKS231_1_II();
void TKS231_1_II_table();
void measure_TKS231_1_II_level(unsigned char n);
void measure_TKS231_1_II(int x,int y);

#endif
#ifndef __TKS14A_I_H
#define __TKS14A_I_H

#include "stm32f10x.h"
#include "ili9320.h"
#include "touch.h"
#include "commonality.h"


void Set_Channel_TKS14A_I(unsigned char x);
void draw_TKS14A_I();
void TKS14A_I_table();
void measure_TKS14A_I_level(unsigned char n);
void measure_TKS14A_I(int x,int y);
void TKS14A_I_Scan();

#endif
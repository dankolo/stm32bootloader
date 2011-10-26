#ifndef __SS7E_QS1_3_H
#define __SS7E_QS1_3_H

#include "stm32f10x.h"
#include "ili9320.h"
#include "touch.h"
#include "commonality.h"


void Set_Channel_SS7E_QS1_3(unsigned char x);
void draw_SS7E_QS1_3();
void SS7E_QS1_3_table();
void measure_SS7E_QS1_3_level(unsigned char n);
void measure_SS7E_QS1_3(int x,int y);

#endif
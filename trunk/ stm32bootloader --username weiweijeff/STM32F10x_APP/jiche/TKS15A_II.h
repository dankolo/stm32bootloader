#ifndef __TKS15A_II_H
#define __TKS15A_II_H
#include "stm32f10x.h"
#include "ili9320.h"
#include "touch.h"
#include "commonality.h"

void Set_Channel_TKS15A_II(unsigned char x);
void draw_TKS15A_II();
void TKS15A_II_table();
void measure_TKS15A_II_level(unsigned char n);
void measure_TKS15A_II(int x,int y);
#endif
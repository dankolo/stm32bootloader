#ifndef __S640K1_H
#define __S640K1_H



enum sk640_logic{zhi_dong,xiang_qian,xiang_hou};

void S640K1_INIT(void);
void draw_s640k1(void);
void S640K1_TP_respond(int x,int y);
void S640K1_measure_levels(unsigned char n);
void sk640k1_scan(void);
void ss7e_save_data(void);














#endif
#ifndef __GEL_H
#define __GEL_H

#include "stm32f10x.h"
#include <rtthread.h>
#include <time.h>
#include <dfs_posix.h>
#include "lcd.h"
#include "s640k1.h"
#include "hxd3c.h"

enum system_flag{main_panel,set_ref,set_sys_time,history,tks640k1,hxd3c};


extern rt_uint8_t sys_flag;
extern rt_uint16_t R_ref;
extern rt_thread_t skq_scan_thread;
void touch_schedule(rt_uint16_t x,rt_uint16_t y);

void draw_main_panel(void);
void main_panel_manager(rt_uint16_t x,rt_uint16_t y);

void draw_time_manager(void);
void time_manager(rt_uint16_t x,rt_uint16_t y);

void read_ref(void);
void write_ref(void);
void draw_ref_manager(void);
void ref_manager(rt_uint16_t x,rt_uint16_t y);

int skq_scan_thread_create();





























#endif

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

extern rt_thread_t skq_scan_thread;
extern rt_uint8_t sys_flag;
extern rt_uint16_t R_ref;
extern rt_uint8_t uchar_check_step;

extern char untest[5];

extern char zc[5];
extern char gz[5];
extern char *lamp,*bhlj,*V_jiwei;
extern char file_name[32];
extern rt_uint8_t ref_buffer[5];
//extern rt_uint8_t scan_over_one_time;
extern rt_mutex_t scan_over_one_time;
//extern struct rt_semaphore auto_scan_flag;
extern rt_uint8_t auto_scan_flag;

void touch_schedule(rt_uint16_t x,rt_uint16_t y);

void draw_main_panel(void);
void main_panel_manager(rt_uint16_t x,rt_uint16_t y);

void draw_time_manager(void);
void time_manager(rt_uint16_t x,rt_uint16_t y);

void read_ref(void);
void write_ref(void);
void draw_ref_manager(void);
void ref_manager(rt_uint16_t x,rt_uint16_t y);
void history_manager(rt_uint16_t x,rt_uint16_t y);
int skq_scan_thread_create();
void txt2lcd(char *file_name);
rt_uint8_t scan_dir(const char *path);
rt_uint8_t scan_file(const char *path);
void draw_history_top_dir(void);


























#endif

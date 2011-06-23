
#ifndef __FATFS_H
#define __FATFS_H

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "ff.h"
#include "diskio.h"

void list_file(void);

char *read_file(const TCHAR *dir,const TCHAR *file_name,int offset,int length);

void creat_file(const TCHAR *file_name);

void delete_file(const TCHAR *dir, const TCHAR *file_name);

void creat_dir(const TCHAR *dir_name);

void edit_file(const TCHAR *dir,const TCHAR *write_file,char *write_data,uint32_t index);
void write_buffer(const TCHAR *write_file,char *write_buffer,uint16_t n_write, uint32_t index);

void get_disk_info(void);
void format_disk(
                 BYTE drv,			/* Logical drive number */
                 BYTE partition,		/* Partitioning rule 0:FDISK, 1:SFD */
                 WORD allocsize		/* Allocation unit size [bytes] */
                 );




void LCD_CN(u16 x,u16 y,uc8 *p,uint8_t fon, u16 charColor,u16 bkColor);
void LCD_ASCII(u16 x,u16 y,u8 p,uint8_t fon, u16 charColor,u16 bkColor);
void LCD_str(u16 x, u16 y, unsigned char *str, uint8_t fon, u16 Color, u16 bkColor);



#endif
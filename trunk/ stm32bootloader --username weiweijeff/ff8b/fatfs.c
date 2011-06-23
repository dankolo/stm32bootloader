

#include "fatfs.h"
#include "ff.h"
#include "stdlib.h"
#include "stm3210e_eval_lcd.h"
char buffer[512]={0};

void list_file(void)
{
        FATFS fs;
	FILINFO finfo;
	FRESULT res;
	DIR dirs;
	int i;
	int files_num=0;
	res = f_mount(0,&fs);
	if (res != FR_OK)
	{
		printf("\r\n挂载文件系统失败,错误代码: %u",res);
		return;
	}	
	res = f_opendir(&dirs, (const TCHAR*) "/");
	if (res == FR_OK)
	{
          printf("\r\n------------文件列表------------");
		while ((f_readdir(&dirs, &finfo) == FR_OK) && finfo.fname[0])
		{
			i = strlen(finfo.fname);
			if (finfo.fattrib & AM_DIR)//如果是文件夹
			{
				files_num++;
				printf("\r\n/%s", &finfo.fname[0]);
				switch(i)//作用：输出文件名左对齐
				{
				case 1:printf(" ");
				case 2:printf(" ");
				case 3:printf(" ");
				case 4:printf(" ");
				case 5:printf(" ");
				case 6:printf(" ");
				case 7:printf(" ");
				case 8:printf("%15s"," ");
				}

				
			}
			else
			{
				continue;
			}	
		}

	}
	else
	{
		printf("\r\n打开根目录失败!");
		printf("\r\n错误代码: %u",res);
	}
	res = f_opendir(&dirs, (const TCHAR*)"/");



	if (res == FR_OK)
	{
		//i = strlen(path);
		
		while ((f_readdir(&dirs, &finfo) == FR_OK) && finfo.fname[0])
		{
			if (finfo.fattrib & AM_DIR)
			{
				continue;
			}
			else
			{
				files_num++;				
				printf("\r\n/.%12s%7ld KB ",  &finfo.fname[0],(finfo.fsize+512)/1024);				
			}
		}
		if( files_num==0 )//无文件
		{
			printf("\r\n无文件!");
		}
	}
	else
	{
		printf("\r\n打开根目录失败!");
		printf("\r\n错误代码: %u",res);
	}
        printf("\n\r");
	f_mount(0,NULL);

}

void get_disk_info(void)
{
	FATFS fs;
	FATFS *fls = &fs;
	FRESULT res;
	DWORD clust,tot_sect,fre_sect;	
	
	res = f_mount(0,&fs);
//        printf("f_mount---%u---",res);
	if (res != FR_OK)
	{
		printf("\r\n挂载文件系统失败,错误代码: %u",res);
		return;
	}	

	res = f_getfree((const TCHAR*)"0:",&clust,&fls);
	if (res == FR_OK)
	{
		tot_sect = (fls->n_fatent - 2) * fls->csize;
		fre_sect = clust * fls->csize;

		printf("\r\nfree space in unit of KB (assuming 512B/sector)");
		printf("\r\n%lu KB total drive space.\r\n"
			"%lu KB available.",
			fre_sect / 2, tot_sect / 2);
	}
	else
	{
		printf("\r\n获得磁盘信息失败!");
		printf("\r\n错误代码: %u",res);
	}
	
	f_mount(0,NULL);

}

void format_disk(
                 BYTE drv,			/* Logical drive number */
                 BYTE partition,		/* Partitioning rule 0:FDISK, 1:SFD */
                 WORD allocsize		/* Allocation unit size [bytes]={0} */
                 )
{
	FATFS fs;
//	FATFS *fls = &fs;
	uint8_t res;
	res = f_mount(0,&fs);
	if (res != FR_OK)
	{
		printf("\r\n挂载文件系统失败,错误代码: %u",res);
		return;
	}	
	printf("\r\n正在格式化磁盘,请稍候...");
	res = f_mkfs(drv,partition,allocsize);
	if (res == FR_OK)
	{
		printf("\r\n格式化成功...");
	}
	else
	{
		printf("\r\n格式化失败...");
		printf("\r\n错误代码: %u",res);
	}
	f_mount(0,NULL);
}

/************************************************************************/
//函数名称:char *read_file(char *dir,char *p,int n,int k)
//用途:读取文件夹*dir下文件n字节开始的k字节数据,k<512;
//返回:读出数据缓存的指针
//用法:xxx=read_file("/book","小说.txt",100,256)

/************************************************************************/

char *read_file(const TCHAR *dir,const TCHAR *file_name,int offset,int length)
{

  FATFS fs;
  FIL	file;
  FRESULT res;
//  DIR dirs;
//  FILINFO finfo;
  uint32_t re;
  res = f_mount(0,&fs);
  res = f_chdir(dir);
  res = f_open(&file,file_name,FA_READ);
  res = f_lseek (&file, offset);
  res = f_read(&file,buffer,length,&re);
  f_close(&file);
  f_mount(0,NULL);
  return buffer;
}


void creat_file(const TCHAR *file_name)
{
	FIL file;
	FIL *pf = &file;
	FATFS fs;
//	FATFS *fls = &fs;
	uint8_t res;

	
	res = f_mount(0,&fs);
	if (res != FR_OK)
	{
		printf("\r\n挂载文件系统失败,错误代码: %u",res);
		return;
	}	
	res = f_open(pf,file_name,FA_READ | FA_WRITE | FA_CREATE_NEW);
	if (res == FR_OK)
	{
		printf("\r\n创建文件成功!");
		res = f_close(pf);
		if (res != FR_OK)
		{
			printf("\r\n创建文件成功,但关闭文件时,失败!");
			printf("\r\n错误代码: %u",res);				
		}				
	}
	else
	{
		printf("\r\n创建文件失败!");
		printf("\r\n错误代码: %u",res);	
	}
	f_mount(0,NULL);
}

void creat_dir(const TCHAR *dir_name)
{
	FATFS fs;
	FRESULT res;
	res = f_mount(0,&fs);
	if (res != FR_OK)
	{
		printf("\r\n挂载文件系统失败,错误代码: %u",res);
		return;
	}		
	res = f_mkdir(dir_name);
	if (res == FR_OK)
	{
		printf("\r\n创建文件目录成功!");
	}
	else
	{
		printf("\r\n创建目录失败...");
		printf("\r\n错误代码: %u",res);
	}
	f_mount(0,NULL);
}


void delete_file(const TCHAR *dir, const TCHAR *file_name)
{
	FATFS fs;
        DIR dirs;
	FRESULT res;
	res = f_mount(0,&fs);        
	if (res != FR_OK)
	{
		printf("\r\n挂载文件系统失败,错误: %u",res);
		return;
	}
        res = f_opendir(&dirs,(const TCHAR*)"/");
        res = f_chdir(dir);	
	res = f_unlink((TCHAR *)file_name);	
	f_mount(0,NULL);
}

void edit_file(const TCHAR *dir,const TCHAR *write_file,char *write_data,uint32_t index)
{
	FATFS fs;
	FIL	file;
	FRESULT res;
	DIR dirs;
        uint32_t n_write=0x00;
        uint32_t n_written = 0x00;
        for(n_write=0;*write_data++!='\0';)
        {
          n_write++;
        }
        write_data=write_data-n_write-1;
	res = f_mount(0,&fs);
	if (res != FR_OK)
	{
		printf("\r\n挂载文件系统失败,错误代码: %u",res);
		return;
	}
	res = f_opendir(&dirs,(const TCHAR*)"/");
        res = f_chdir(dir);
	res = f_open(&file,write_file,FA_READ | FA_WRITE);
        res = f_lseek (&file, index);
	if (res == FR_OK)
	{
          if(n_write<=512)
          {
            res = f_write(&file,write_data,n_write,&n_written);
            if ((res == FR_OK) && (n_written==n_write))
            {
              f_close(&file);
            }
            else
            {
              printf("\r\n保存数据失败!");
              printf("\r\n错误代码: %u",res);
            }
          }
          else
          {
            while(*write_data!='\0')
            {
              res = f_write(&file,write_data,512,&n_written);
              if ((res == FR_OK) && (n_written==512))
              {
                f_close(&file);
              }
              else
              {
                printf("\r\n保存数据失败!");
                printf("\r\n错误代码: %u",res);
              }
              write_data+=512;
              index+=512;
              res = f_open(&file,write_file,FA_READ | FA_WRITE);
              res = f_lseek (&file, index);
            }
          }
	}
	else
	{
		printf("\r\n打开文件失败,错误代码: %u",res);
	}
        f_mount(0,NULL);
}

//写入<512byte数据,n_write<=512
void write_buffer(const TCHAR *write_file,char *write_buffer,uint16_t n_write, uint32_t index)
{
  FATFS fs;
  FIL file;
  FRESULT res;
  DIR dirs;
  uint32_t n_written = 0x00;
  res = f_mount(0,&fs);
  res = f_opendir(&dirs,(const TCHAR*)"/");
  res = f_open(&file,write_file,FA_READ | FA_WRITE);
  res = f_lseek (&file, index);
  if (res == FR_OK)
  {
  retry:  res = f_write(&file,write_buffer,n_write,&n_written);
    if ((res == FR_OK) && (n_written==n_write))
    {
      f_close(&file);
    }
    else
    {
      n_written=0;
      goto retry;
    }
  }
  f_mount(0,NULL);
}

/************************************************************************/
//函数名称:void write_CN16(u16 x,u16 y,uc8 *p,u16 charColor,u16 bkColor)
//用途:液晶屏上坐标x,y写16*16汉字
//返回:无
//用法:write_CN16(10,12,"哦",16,Red,Blue)
/************************************************************************/
void LCD_CN(u16 x,u16 y,uc8 *p,uint8_t fon, u16 charColor,u16 bkColor)
{
  unsigned char region   = *p-0xa0;//得到区号  gb2312
  unsigned char location = *(p+1)-0xa0;//得到位号
  uint32_t index;//地址偏移量  
  uint16_t i,n,end_x;
  
  FATFS fs;
  FIL	file;
  FRESULT res;
  DIR dirs;
  u8 buffer[32]={0};
  uint32_t re;
  res = f_mount(0,&fs);
  res = f_opendir(&dirs,(const TCHAR*)"/");//打开根目录
  switch(fon)
  {
  case 12:
    {
      index = (94*(region-1)+location-1)*24;//地址偏移量  
      end_x=x+11;
      res = f_open(&file,(const TCHAR*)"Chinese12.FON",FA_READ);//打开在根目录的字库
      res = f_lseek (&file, index);//设置偏移量
      res = f_read(&file,buffer,24,&re);//
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
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }
        for (i = 0; i < 4; i++)//
        {
          if (buffer[n+1] & (0x01<<i))
          {
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
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
      res = f_open(&file,(const TCHAR*)"Chinese16.FON",FA_READ);//打开在根目录的字库
      res = f_lseek (&file, index);//设置偏移量
      res = f_read(&file,buffer,32,&re);//读出32字节字模数据
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
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }
      }
    }
    break;
  case 24:
    {
      index = (94*(region-1)+location-1)*72;//地址偏移量  
      end_x=x+23;
      res = f_open(&file,(const TCHAR*)"Chinese24.FON",FA_READ);//打开在根目录的字库
      res = f_lseek (&file, index);//设置偏移量
      res = f_read(&file,buffer,72,&re);//
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
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }        
      }
    }
    break;
  case 32:
    {
      index = (94*(region-1)+location-1)*128;//地址偏移量  
      end_x=x+31;
      res = f_open(&file,(const TCHAR*)"Chinese32.FON",FA_READ);//打开在根目录的字库
      res = f_lseek (&file, index);//设置偏移量
      res = f_read(&file,buffer,128,&re);//读出32字节字模数据
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
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }
      }
    }
    break;
  default:break;
  }
  
  f_close(&file);
  f_mount(0,NULL);
}





void LCD_ASCII(u16 x,u16 y,u8 p,uint8_t fon, u16 charColor,u16 bkColor)
{
  
  uint32_t index;//地址偏移量  
  uint16_t i,n,end_x;
  FATFS fs;
  FIL	file;
  FRESULT res;
  DIR dirs;
  uint32_t re;
  res = f_mount(0,&fs);
  res = f_opendir(&dirs,(const TCHAR*)"/");//打开根目录
  
  
  
  switch(fon)
  {
  case 12:
    {
      u8 buffer[12]={0};
      index = p*12;
      end_x=x+5;
      res = f_open(&file,(const TCHAR*)"ASCII12.FON",FA_READ);//打开在根目录的字库
      res = f_lseek (&file, index);//设置偏移量
      res = f_read(&file,buffer,12,&re);//读出32字节字模数据
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
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }
      }
    }
    break;
  case 16:
    {
      u8 buffer[16]={0};
      index = p*16;
      end_x=x+7;
      res = f_open(&file,(const TCHAR*)"ASCII16.FON",FA_READ);//打开在根目录的字库
      res = f_lseek (&file, index);//设置偏移量
      res = f_read(&file,buffer,16,&re);//读出32字节字模数据
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
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }
      }
    }
    break;
  case 24:
    {
      u8 buffer[48]={0};
      index = p*48;
      end_x=x+11;
      res = f_open(&file,(const TCHAR*)"ASCII24.FON",FA_READ);//打开在根目录的字库
      res = f_lseek (&file, index);//设置偏移量
      res = f_read(&file,buffer,48,&re);//读出32字节字模数据
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
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }
        for (i = 0; i < 4; i++)
        {
          if (buffer[n+1] & (0x01<<i))
          {
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }
        n+=1;
      }
    }
    break;
  case 32:
    {
      u8 buffer[64]={0};
      index = p*64;
      end_x=x+15;
      res = f_open(&file,(const TCHAR*)"ASCII32.FON",FA_READ);//打开在根目录的字库
      res = f_lseek (&file, index);//设置偏移量
      res = f_read(&file,buffer,64,&re);//读出32字节字模数据
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
            LCD_WritePoint(charColor);//写有效点
          }
          else
          {
            LCD_WritePoint(bkColor);//写底色
          }
        }
      }
    }
    break;
    
    
  default:break;
  }
  
  f_close(&file);
  f_mount(0,NULL);
}


void LCD_str(u16 x, u16 y, unsigned char *str, uint8_t fon, u16 Color, u16 bkColor)
{
  while (*str)
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
    if (*str < 128)
    {
      LCD_ASCII(x,y,*str,fon,Color,bkColor);
      x=x+fon/2;
      str+=1;
    }
    else
    {
      LCD_CN(x,y,str,fon,Color,bkColor);
      x+= fon;
      str+=2;
    }    
  }
}

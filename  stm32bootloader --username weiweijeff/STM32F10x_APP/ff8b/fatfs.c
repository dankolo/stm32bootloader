

#include "fatfs.h"
#include "ff.h"
#include "stdlib.h"
#include "stm3210e_eval_lcd.h"
char buffer[512]={0};


#if 1
u8 files_name[16][63];
uint8_t files_num=0;
FRESULT scan_files (
    char* path        /* Start node to be scanned (also used as work area) */
)
{
  
    FATFS fs;
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
    
    char *fn;   /* This function is assuming non-Unicode cfg. */
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

res = f_mount(0,&fs);
    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fname[0] == '.') continue;             /* Ignore dot entry */
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                sprintf(&path[i], "/%s", fn);
                res = scan_files(path);
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* It is a file. */
                //printf("%s/%s\n", path, fn);              
              memcpy(files_name[files_num],fn,strlen(fn));
              files_num+=1;
            }
        }
    }
f_mount(0,NULL);
    return res;
}
#endif 

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
		//printf("\r\n�����ļ�ϵͳʧ��,�������: %u",res);
		return;
	}	
	res = f_opendir(&dirs, (const TCHAR*) "/");
	if (res == FR_OK)
	{
          //printf("\r\n------------�ļ��б�------------");
		while ((f_readdir(&dirs, &finfo) == FR_OK) && finfo.fname[0])
		{
			i = strlen(finfo.fname);
			if (finfo.fattrib & AM_DIR)//������ļ���
			{
				files_num++;
				//printf("\r\n/%s", &finfo.fname[0]);
				switch(i)//���ã�����ļ��������
				{
				case 1://printf(" ");
				case 2://printf(" ");
				case 3://printf(" ");
				case 4://printf(" ");
				case 5://printf(" ");
				case 6://printf(" ");
				case 7://printf(" ");
				case 8://printf("%15s"," ");
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
		//printf("\r\n�򿪸�Ŀ¼ʧ��!");
		//printf("\r\n�������: %u",res);
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
				//printf("\r\n/.%12s%7ld KB ",  &finfo.fname[0],(finfo.fsize+512)/1024);				
			}
		}
		if( files_num==0 )//���ļ�
		{
			//printf("\r\n���ļ�!");
		}
	}
	else
	{
		//printf("\r\n�򿪸�Ŀ¼ʧ��!");
		//printf("\r\n�������: %u",res);
	}
        //printf("\n\r");
	f_mount(0,NULL);

}

void get_disk_info(void)
{
	FATFS fs;
	FATFS *fls = &fs;
	FRESULT res;
	DWORD clust,tot_sect,fre_sect;	
	
	res = f_mount(0,&fs);
//        //printf("f_mount---%u---",res);
	if (res != FR_OK)
	{
		//printf("\r\n�����ļ�ϵͳʧ��,�������: %u",res);
		return;
	}	

	res = f_getfree((const TCHAR*)"0:",&clust,&fls);
	if (res == FR_OK)
	{
		tot_sect = (fls->n_fatent - 2) * fls->csize;
		fre_sect = clust * fls->csize;

		//printf("\r\nfree space in unit of KB (assuming 512B/sector)");
		//printf("\r\n%lu KB total drive space.\r\n"	"%lu KB available.",fre_sect / 2, tot_sect / 2);
	}
	else
	{
		//printf("\r\n��ô�����Ϣʧ��!");
		//printf("\r\n�������: %u",res);
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
		//printf("\r\n�����ļ�ϵͳʧ��,�������: %u",res);
		return;
	}	
	//printf("\r\n���ڸ�ʽ������,���Ժ�...");
	res = f_mkfs(drv,partition,allocsize);
	if (res == FR_OK)
	{
		//printf("\r\n��ʽ���ɹ�...");
	}
	else
	{
		//printf("\r\n��ʽ��ʧ��...");
		//printf("\r\n�������: %u",res);
	}
	f_mount(0,NULL);
}

/************************************************************************/
//��������:char *read_file(char *dir,char *p,int n,int k)
//��;:��ȡ�ļ���*dir���ļ�n�ֽڿ�ʼ��k�ֽ�����,k<512;
//����:�������ݻ����ָ��
//�÷�:xxx=read_file("/book","С˵.txt",100,256)

/************************************************************************/

char *read_file(const TCHAR *dir,const TCHAR *file_name,int offset,int length)
{

  FATFS fs;
  FIL	file;
  FRESULT res;
//  DIR dirs;
  FILINFO finfo;
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
		//printf("\r\n�����ļ�ϵͳʧ��,�������: %u",res);
		return;
	}	
	res = f_open(pf,file_name,FA_READ | FA_WRITE | FA_CREATE_NEW);
	if (res == FR_OK)
	{
		//printf("\r\n�����ļ��ɹ�!");
		res = f_close(pf);
		if (res != FR_OK)
		{
			//printf("\r\n�����ļ��ɹ�,���ر��ļ�ʱ,ʧ��!");
			//printf("\r\n�������: %u",res);				
		}				
	}
	else
	{
		//printf("\r\n�����ļ�ʧ��!");
		//printf("\r\n�������: %u",res);	
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
		//printf("\r\n�����ļ�ϵͳʧ��,�������: %u",res);
		return;
	}		
	res = f_mkdir(dir_name);
	if (res == FR_OK)
	{
		//printf("\r\n�����ļ�Ŀ¼�ɹ�!");
	}
	else
	{
		//printf("\r\n����Ŀ¼ʧ��...");
		//printf("\r\n�������: %u",res);
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
		//printf("\r\n�����ļ�ϵͳʧ��,����: %u",res);
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
		//printf("\r\n�����ļ�ϵͳʧ��,�������: %u",res);
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
              //printf("\r\n��������ʧ��!");
              //printf("\r\n�������: %u",res);
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
                //printf("\r\n��������ʧ��!");
                //printf("\r\n�������: %u",res);
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
		//printf("\r\n���ļ�ʧ��,�������: %u",res);
	}
        f_mount(0,NULL);
}

//д��<512byte����,n_write<=512
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
//��������:void write_CN16(u16 x,u16 y,uc8 *p,u16 charColor,u16 bkColor)
//��;:Һ����������x,yд16*16����
//����:��
//�÷�:write_CN16(10,12,"Ŷ",16,Red,Blue)
/************************************************************************/
void LCD_CN(u16 x,u16 y,uc8 *p,uint8_t fon, u16 charColor,u16 bkColor)
{
  unsigned char region   = *p-0xa0;//�õ�����  gb2312
  unsigned char location = *(p+1)-0xa0;//�õ�λ��
  uint32_t index;//��ַƫ����  
  uint16_t i,n,end_x;
  
  FATFS fs;
  FIL	file;
  FRESULT res;
  DIR dirs;
  uint32_t re;
  res = f_mount(0,&fs);
  res = f_opendir(&dirs,(const TCHAR*)"/");//�򿪸�Ŀ¼
  switch(fon)
  {
  case 12:
    {
      index = (94*(region-1)+location-1)*24;//��ַƫ����  
      end_x=x+11;
      res = f_open(&file,(const TCHAR*)"Chinese12.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
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
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
        for (i = 0; i < 4; i++)//
        {
          if (buffer[n+1] & (0x01<<i))
          {
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
        n+=1;
      }
    }
    break;
  case 16:
    {
      index = (94*(region-1)+location-1)*32;//��ַƫ����  
      end_x=x+15;
      res = f_open(&file,(const TCHAR*)"Chinese16.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
      res = f_read(&file,buffer,32,&re);//����32�ֽ���ģ����
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
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
      }
    }
    break;
  case 24:
    {
      index = (94*(region-1)+location-1)*72;//��ַƫ����  
      end_x=x+23;
      res = f_open(&file,(const TCHAR*)"Chinese24.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
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
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }        
      }
    }
    break;
  case 32:
    {
      index = (94*(region-1)+location-1)*128;//��ַƫ����  
      end_x=x+31;
      res = f_open(&file,(const TCHAR*)"Chinese32.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
      res = f_read(&file,buffer,128,&re);//����32�ֽ���ģ����
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
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
      }
    }
    break;
    case 64:
    {
      index = (94*(region-1)+location-1)*448;//��ַƫ����  
      end_x=x+63;
      res = f_open(&file,(const TCHAR*)"Chinese64.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
      res = f_read(&file,buffer,448,&re);//����32�ֽ���ģ����
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<448;n++)
      {
        for (i = 0; i < 8; i++)//
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
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
  
  uint32_t index;//��ַƫ����  
  uint16_t i,n,end_x;
  FATFS fs;
  FIL	file;
  FRESULT res;
  DIR dirs;
  uint32_t re;
  res = f_mount(0,&fs);
  res = f_opendir(&dirs,(const TCHAR*)"/");//�򿪸�Ŀ¼
  
  
  
  switch(fon)
  {
  case 12:
    {
      index = p*12;
      end_x=x+5;
      res = f_open(&file,(const TCHAR*)"ASCII12.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
      res = f_read(&file,buffer,12,&re);//����32�ֽ���ģ����
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
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
      }
    }
    break;
  case 16:
    {
      index = p*16;
      end_x=x+7;
      res = f_open(&file,(const TCHAR*)"ASCII16.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
      res = f_read(&file,buffer,16,&re);//����32�ֽ���ģ����
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
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
      }
    }
    break;
  case 24:
    {
      index = p*48;
      end_x=x+11;
      res = f_open(&file,(const TCHAR*)"ASCII24.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
      res = f_read(&file,buffer,48,&re);//����32�ֽ���ģ����
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
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
        for (i = 0; i < 4; i++)
        {
          if (buffer[n+1] & (0x01<<i))
          {
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
        n+=1;
      }
    }
    break;
  case 32:
    {
      index = p*64;
      end_x=x+15;
      res = f_open(&file,(const TCHAR*)"ASCII32.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
      res = f_read(&file,buffer,64,&re);//����32�ֽ���ģ����
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
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
          }
        }
      }
    }
    break;
    case 64:
    {
      index = p*256;
      end_x=x+31;
      res = f_open(&file,(const TCHAR*)"ASCII64.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      res = f_lseek (&file, index);//����ƫ����
      res = f_read(&file,buffer,256,&re);//����32�ֽ���ģ����
      LCD_WriteReg(CUR_X,x); // .............. CUR_x
      LCD_WriteReg(CUR_Y,y); // .............. CUR_y
      LCD_WriteReg(END_X,end_x); // ............ END_X
      LCD_WriteRAM_Prepare(); // .............. PIXELS
      for(n=0;n<256;n++)
      {
        for (i = 0; i < 8; i++)
        {
          if (buffer[n] & (0x01<<i))
          {
            LCD_WritePoint(charColor);//д��Ч��
          }
          else
          {
            LCD_WritePoint(bkColor);//д��ɫ
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
    if (*str < 128)
    {
      if((x+(fon>>1))>799)//һ��д����
      {
        x=0;
        y+=fon;
      }
      if((y+(fon>>1))>479)//����д����
      {
        y=0;
      }
      LCD_ASCII(x,y,*str,fon,Color,bkColor);
      x=x+fon/2;
      str+=1;
    }
    else
    {
      if((x+fon)>799)//һ��д����
      {
        x=0;
        y+=fon;
      }
      if((y+fon)>479)//����д����
      {
        y=0;
      }
      LCD_CN(x,y,str,fon,Color,bkColor);
      x+= fon;
      str+=2;
    }    
  }
}


/*********************************************************************************
//wdx:    1 Wingdings, 2 Wingdings2, 3 Wingdings3;
//wide:   0 40*48, 1 96*128
*********************************************************************************/

void LCD_WD(u16 x,u16 y,u8 p,uint8_t wdx,uint8_t wide, u16 charColor,u16 bkColor)
{
  uint32_t index;//��ַƫ����  
  uint16_t i,m,n,end_x;
  FATFS fs;
  FIL	file;
  FRESULT res;
  DIR dirs;
  uint32_t re;
  res = f_mount(0,&fs);
  res = f_opendir(&dirs,(const TCHAR*)"/");//�򿪸�Ŀ¼
  
  if(wide==0)
  {
    index = p*240;
    end_x=x+39;
    switch(wdx)
    {
    case 1:
      res = f_open(&file,(const TCHAR*)"Wingdings.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      break;
    case 2:
      res = f_open(&file,(const TCHAR*)"Wingdings2.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      break;
    case 3:
      res = f_open(&file,(const TCHAR*)"Wingdings3.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      break;
    default:break;
    }
    res = f_lseek (&file, index);//����ƫ����
    res = f_read(&file,buffer,240,&re);//����32�ֽ���ģ����
    LCD_WriteReg(CUR_X,x); // .............. CUR_x
    LCD_WriteReg(CUR_Y,y); // .............. CUR_y
    LCD_WriteReg(END_X,end_x); // ............ END_X
    LCD_WriteRAM_Prepare(); // .............. PIXELS
    for(n=0;n<240;n++)
    {
      for (i = 0; i < 8; i++)
      {
        if (buffer[n] & (0x01<<i))
        {
          LCD_WritePoint(charColor);//д��Ч��
        }
        else
        {
          LCD_WritePoint(bkColor);//д��ɫ
        }
      }
    }
  }
  if(wide==1)
  {
    index = p*1536;
    end_x=x+95;
    switch(wdx)
    {
    case 1:
      res = f_open(&file,(const TCHAR*)"BWingdings.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      break;
    case 2:
      res = f_open(&file,(const TCHAR*)"BWingdings2.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      break;
    case 3:
      res = f_open(&file,(const TCHAR*)"BWingdings3.FON",FA_READ);//���ڸ�Ŀ¼���ֿ�
      break;
    default:break;
    }
    index-=384;
        y-=32;
    
      for(m=0;m<4;m++)
      {
        index+=384;
        y+=32;
        res = f_lseek (&file, index);//����ƫ����
        res = f_read(&file,buffer,384,&re);//����480�ֽ���ģ����
        LCD_WriteReg(CUR_X,x); // .............. CUR_x
        LCD_WriteReg(CUR_Y,y); // .............. CUR_y
        LCD_WriteReg(END_X,end_x); // ............ END_X
        LCD_WriteRAM_Prepare(); // .............. PIXELS
        for(n=0;n<384;n++)
        {
          for (i = 0; i < 8; i++)
          {
            if (buffer[n] & (0x01<<i))
            {
              LCD_WritePoint(charColor);//д��Ч��
            }
            else
            {
              LCD_WritePoint(bkColor);//д��ɫ
            }
          }
        }
      }
    
  }
  f_close(&file);
  f_mount(0,NULL);
}
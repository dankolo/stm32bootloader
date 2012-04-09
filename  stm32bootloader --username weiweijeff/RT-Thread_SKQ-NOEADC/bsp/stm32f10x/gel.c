


#include "gel.h"
#include "analog.h"



rt_uint8_t sys_flag=main_panel;
rt_uint16_t R_ref=500;


rt_uint8_t main_panel_flag[5]={set_ref,set_sys_time,history,tks640k1,hxd3c};



unsigned int main_panel_tp[12][4]=
{
{0,96,266,192},{266,96,532,192},{532,96,798,192},
{0,192,266,288},{266,192,532,288},{532,192,798,288},
{0,288,266,384},{266,288,532,384},{532,288,798,384},
{0,384,266,480},{266,384,532,480},{532,384,798,480}
};//set_ref     set_sys_time      history
//  tks640k1    hxd3c              5
//  6           7                  8
//  9           10                11


void touch_schedule(uint16_t x,uint16_t y)
{
  switch(sys_flag)
  {
  case set_ref:
    {
      ref_manager(x,y);
      break;
    }
  case set_sys_time:
    {
       time_manager(x,y);
       break;
    }
  case history:
    {
//      sys_flag=main_panel;
      break;
    }
  case tks640k1:
    { 
      S640K1_TP_respond(x,y);
      break;
    }
  case hxd3c:
    {
      hxd3c_TP_respond(x,y);
      break;
    }
  default:
    {
      main_panel_manager(x,y);
      break;
    }
  }
}


void draw_main_panel(void)
{
  LCD_Clear(Black);
  LCD_str(267,0,"选择项目",64,Blue,Black);
  LCD_str(0,112,"设置阀值",64,Blue,Black);
  LCD_str(267,112,"设置时间",64,Blue,Black);
  LCD_str(533,112,"历史数据",64,Blue,Black);
  LCD_str(0,208,"-SS7E-",64,Blue,Black);
  LCD_str(267,208,"-HXD3C-",64,Blue,Black);
}




void main_panel_manager(rt_uint16_t x,rt_uint16_t y)
{

  u8 t;
  for(t=0;t<12;t++)
  {
    if(((y>main_panel_tp[t][1])&&(y<main_panel_tp[t][3]))&&((x>main_panel_tp[t][0])&&(x<main_panel_tp[t][2])))
    {
      sys_flag=main_panel_flag[t];
      switch(sys_flag)
      {
      case set_ref:
        {
          draw_ref_manager();
          break;
        }
      case set_sys_time:
        {
          draw_time_manager();
          break;
        }
      case history:
        {
          //      sys_flag=main_panel;
          break;
        }
      case tks640k1:
        {
          S640K1_INIT();
          draw_s640k1();
          PowerA_EN();
          CD4067_EN();
          ADC_R_Restart();
          ADC_V_Restart();
          skq_scan_thread_create();
          break;
        }
      case hxd3c:
        {
          hxd3c_INIT();
          draw_hxd3c();
          PowerA_EN();
          CD4067_EN();
          ADC_R_Restart();
          ADC_V_Restart();
          skq_scan_thread_create();
          break;
        }
      default:
        {
          main_panel_manager(x,y);
          break;
        }
      }
    }
  }
  return;
}



extern void set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second);
extern void set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day);
rt_uint8_t time_buffer[20]="2012-03-26 09:17:10";
rt_uint8_t time_set_flag=0;
rt_uint8_t time_bit[14]={0,1,2,3,5,6,8,9,11,12,14,15,17,18};
rt_uint8_t time_keypad[11]="ijklmnopqr";
rt_uint8_t time_keypad_flash[11]="tuvwxyz{|}";
unsigned int time_coordinate[14][4]=
{
{416,248,432,279},{432,248,448,279},
{448,248,464,279},{464,248,480,279},
{496,248,512,279},{512,248,528,279},
{544,248,560,279},{560,248,576,279},
{592,248,608,279},{608,248,624,279},
{640,248,656,279},{656,248,672,279},
{688,248,704,279},{704,248,719,279},
};


unsigned int action_tp[13][4]=
{
{416,72,512,200},
{64,328,160,456},{160,328,256,456},{256,328,352,456},
{64,200,160,328},{160,200,256,328},{256,200,352,328},
{64,72,160,200},{160,72,256,200},{256,72,352,200},
{576,72,672,200},{416,328,512,456},{576,328,672,456}
};//0123456789H<>


void LCD_Set_Time(void)
{
  rt_uint32_t year, month, day, hour, minute, second;
  year=1000*(time_buffer[0]-'0')+100*(time_buffer[1]-'0')+10*(time_buffer[2]-'0')+(time_buffer[3]-'0');
  month=10*(time_buffer[5]-'0')+(time_buffer[6]-'0');
  day=10*(time_buffer[8]-'0')+(time_buffer[9]-'0');
  hour=10*(time_buffer[11]-'0')+(time_buffer[12]-'0');
  minute=10*(time_buffer[14]-'0')+(time_buffer[15]-'0');
  second=10*(time_buffer[17]-'0')+(time_buffer[18]-'0');
  set_date(year, month, day);
  set_time(hour, minute, second);
}

void LCD_Get_Time(void)
{
  time_t now;
  struct tm* ti;
  /* get current time */
  time(&now);
  ti = localtime(&now);
  time_buffer[0]=(ti->tm_year+1900)/1000+'0';
  time_buffer[1]=((ti->tm_year+1900)%1000)/100+'0';
  time_buffer[2]=((ti->tm_year+1900)%100)/10+'0';
  time_buffer[3]=(ti->tm_year+1900)%10+'0';
                   
  time_buffer[5]=(ti->tm_mon+1)/10+'0';
  time_buffer[6]=(ti->tm_mon+1)%10+'0';
  
  time_buffer[8]=ti->tm_mday/10+'0';
  time_buffer[9]=ti->tm_mday%10+'0';
  
  time_buffer[11]=ti->tm_hour/10+'0';
  time_buffer[12]=ti->tm_hour%10+'0';
  
  time_buffer[14]=ti->tm_min/10+'0';
  time_buffer[15]=ti->tm_min%10+'0';
  
  time_buffer[17]=ti->tm_sec/10+'0';
  time_buffer[18]=ti->tm_sec%10+'0';

  
}

void draw_time_manager(void)
{
  LCD_Clear(Black);
  LCD_str(272,0,"设置时间",64,Blue,Black);  
  LCD_WD( 64,72,  'p', 2, 1, Blue,Black);
  LCD_WD( 160,72, 'q', 2, 1, Blue,Black);
  LCD_WD( 256,72, 'r', 2, 1, Blue,Black);
  LCD_WD( 416,72, 'i', 2, 1, Blue,Black);
  LCD_WD( 576,72, '<', 1, 1, Blue,Black);
  
  LCD_WD( 64,200, 'm', 2, 1, Blue,Black);
  LCD_WD( 160,200, 'n', 2, 1, Blue,Black);
  LCD_WD( 256,200, 'o', 2, 1, Blue,Black);
  
  LCD_WD( 64,328, 'j', 2, 1, Blue,Black);
  LCD_WD( 160,328, 'k', 2, 1, Blue,Black);
  LCD_WD( 256,328, 'l', 2, 1, Blue,Black);
  LCD_WD( 416,328, 'B', 2, 1, Blue,Black);
  LCD_WD( 576,328, 'C', 2, 1, Blue,Black);
  LCD_DrawFullRect( time_coordinate[0][0],  time_coordinate[0][1],  time_coordinate[0][2],  time_coordinate[0][3],  Red, 0);  
  LCD_Get_Time();
  LCD_str(416,248,time_buffer,32,Blue,Black);
}




void time_manager(rt_uint16_t x,rt_uint16_t y)
{

  u8 t;
  for(t=0;t<13;t++)
  {
    if(((y>action_tp[t][1])&&(y<action_tp[t][3]))&&((x>action_tp[t][0])&&(x<action_tp[t][2])))
    {
      if(t<10)
      {
        LCD_WD( action_tp[t][0],action_tp[t][1], time_keypad_flash[t], 2, 1, Cyan,Black);
        LCD_WD( action_tp[t][0],action_tp[t][1], time_keypad[t], 2, 1, Blue,Black);
        time_buffer[time_bit[time_set_flag]]=t+'0';
        LCD_str(416,248,time_buffer,32,Blue,Black);
        LCD_DrawFullRect( time_coordinate[time_set_flag][0],  time_coordinate[time_set_flag][1],  time_coordinate[time_set_flag][2],  time_coordinate[time_set_flag][3],  Red, 0);
      }
      if(t==10)
      {
        LCD_Set_Time();
        sys_flag=main_panel;
        draw_main_panel();
      }
      if(t==11)
      {
        LCD_WD( 416,328, 'D', 2, 1, Cyan,Black);
        LCD_WD( 416,328, 'B', 2, 1, Blue,Black);
        if(time_set_flag==0)
        {
          time_set_flag=13;
        }
        time_set_flag-=1;
        LCD_str(416,248,time_buffer,32,Blue,Black);
        LCD_DrawFullRect( time_coordinate[time_set_flag][0],  time_coordinate[time_set_flag][1],  time_coordinate[time_set_flag][2],  time_coordinate[time_set_flag][3],  Red, 0);
      }
      if(t==12)
      {
        LCD_WD( 576,328, 'E', 2, 1, Cyan,Black);
        LCD_WD( 576,328, 'C', 2, 1, Blue,Black);
        if(time_set_flag==13)
        {
          time_set_flag=0;
        }
        time_set_flag+=1;
        LCD_str(416,248,time_buffer,32,Blue,Black);
        LCD_DrawFullRect( time_coordinate[time_set_flag][0],  time_coordinate[time_set_flag][1],  time_coordinate[time_set_flag][2],  time_coordinate[time_set_flag][3],  Red, 0);
      }
    }
  }
}




rt_uint8_t ref_set_flag=0;
rt_uint8_t ref_keypad[11]="ijklmnopqr";
rt_uint8_t ref_keypad_flash[11]="tuvwxyz{|}";
rt_uint8_t ref_buffer[5]={'0','0','0','0','\0'};
unsigned int ref_coordinate[4][4]=
{
{416,248,448,311},{448,248,480,311},
{480,248,512,311},{512,248,543,311},
};


unsigned int ref_action_tp[13][4]=
{
{416,72,512,200},
{64,328,160,456},{160,328,256,456},{256,328,352,456},
{64,200,160,328},{160,200,256,328},{256,200,352,328},
{64,72,160,200},{160,72,256,200},{256,72,352,200},
{576,72,672,200},{416,328,512,456},{576,328,672,456}
};//0123456789H<>


void read_ref(void)
{
  int fd;
  fd = open("/ref.txt", O_RDONLY, 0);//打开在根目录的字库
  read(fd, ref_buffer, 5);
  close(fd);
  R_ref=(ref_buffer[0]-'0')*1000+(ref_buffer[1]-'0')*100+(ref_buffer[2]-'0')*10+(ref_buffer[3]-'0');
}
void write_ref(void)
{
  int fd;
  fd = open("/ref.txt", O_WRONLY | O_CREAT | O_TRUNC, 0);
  lseek(fd,  0x00,  DFS_SEEK_SET);//设置偏移量
  write(fd, ref_buffer, 5);
  close(fd);
  R_ref=(ref_buffer[0]-'0')*1000+(ref_buffer[1]-'0')*100+(ref_buffer[2]-'0')*10+(ref_buffer[3]-'0');
}

void draw_ref_manager(void)
{
  //LCD_Clear(Cyan);
  LCD_Clear(Black);
  LCD_str(272,0,"设置阀值",64,Blue,Black);
  
  
  LCD_WD( 64,72,  'p', 2, 1, Blue,Black);
  LCD_WD( 160,72, 'q', 2, 1, Blue,Black);
  LCD_WD( 256,72, 'r', 2, 1, Blue,Black);
  LCD_WD( 416,72, 'i', 2, 1, Blue,Black);
  LCD_WD( 576,72, '<', 1, 1, Blue,Black);
  
  LCD_WD( 64,200, 'm', 2, 1, Blue,Black);
  LCD_WD( 160,200, 'n', 2, 1, Blue,Black);
  LCD_WD( 256,200, 'o', 2, 1, Blue,Black);
  read_ref();
  LCD_str(416,248,ref_buffer,64,Blue2,Black);
  LCD_str(560,280,"毫欧",32,Blue2,Black);
  
  LCD_WD( 64,328, 'j', 2, 1, Blue,Black);
  LCD_WD( 160,328, 'k', 2, 1, Blue,Black);
  LCD_WD( 256,328, 'l', 2, 1, Blue,Black);
  LCD_WD( 416,328, 'B', 2, 1, Blue,Black);
  LCD_WD( 576,328, 'C', 2, 1, Blue,Black);
  LCD_DrawFullRect( ref_coordinate[0][0],  ref_coordinate[0][1],  ref_coordinate[0][2],  ref_coordinate[0][3],  Red, 0);
}



void ref_manager(rt_uint16_t x,rt_uint16_t y)
{

  u8 t;
  for(t=0;t<13;t++)
  {
    if(((y>ref_action_tp[t][1])&&(y<ref_action_tp[t][3]))&&((x>ref_action_tp[t][0])&&(x<ref_action_tp[t][2])))
    {
      if(t<10)
      {
        LCD_WD( ref_action_tp[t][0],ref_action_tp[t][1], ref_keypad_flash[t], 2, 1, Cyan,Black);
        LCD_WD( ref_action_tp[t][0],ref_action_tp[t][1], ref_keypad[t], 2, 1, Blue,Black);
        ref_buffer[ref_set_flag]=t+'0';
        LCD_str(416,248,ref_buffer,64,Blue2,Black);
        LCD_DrawFullRect( ref_coordinate[ref_set_flag][0],  ref_coordinate[ref_set_flag][1],  ref_coordinate[ref_set_flag][2],  ref_coordinate[ref_set_flag][3],  Red, 0);
      }
      if(t==10)
      {
        write_ref();
        sys_flag=main_panel;
        draw_main_panel();
//        return;
      }
      if(t==11)
      {
        LCD_WD( 416,328, 'D', 2, 1, Cyan,Black);
        LCD_WD( 416,328, 'B', 2, 1, Blue,Black);
        if(ref_set_flag==0)
        {
          ref_set_flag=3;
        }
        ref_set_flag-=1;
        LCD_str(416,248,ref_buffer,64,Blue2,Black);
        LCD_DrawFullRect( ref_coordinate[ref_set_flag][0],  ref_coordinate[ref_set_flag][1],  ref_coordinate[ref_set_flag][2],  ref_coordinate[ref_set_flag][3],  Red, 0);
      }
      if(t==12)
      {
        LCD_WD( 576,328, 'E', 2, 1, Cyan,Black);
        LCD_WD( 576,328, 'C', 2, 1, Blue,Black);
        if(ref_set_flag==3)
        {
          ref_set_flag=0;
        }
        ref_set_flag+=1;
        LCD_str(416,248,ref_buffer,64,Blue2,Black);
        LCD_DrawFullRect( ref_coordinate[ref_set_flag][0],  ref_coordinate[ref_set_flag][1],  ref_coordinate[ref_set_flag][2],  ref_coordinate[ref_set_flag][3],  Red, 0);
      }
    }
  }
}

#include "tc_comm.h"

rt_thread_t skq_scan_thread;
void skq_scan_thread_entry(void* parameter)
{
  
  while (auto_scan_flag)
  {
    rt_thread_delay(10);
    switch(sys_flag)
    {
    case tks640k1:
      {
        sk640k1_scan();
        break;
      }
    case hxd3c:
      {
        hxd3c_scan();
        break;
      }
    default:
      {
          break;
      }
    }
  }
}
int skq_scan_thread_create()
{

	skq_scan_thread = rt_thread_create("skq_scan",
		skq_scan_thread_entry, RT_NULL,
		2048, 5, 10);
	if (skq_scan_thread != RT_NULL)
		rt_thread_startup(skq_scan_thread);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	return 0;
}





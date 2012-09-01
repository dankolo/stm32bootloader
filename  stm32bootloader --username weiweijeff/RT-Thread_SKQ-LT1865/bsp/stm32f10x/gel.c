


#include "gel.h"
#include "analog.h"


rt_thread_t skq_scan_thread_id=RT_NULL;
rt_uint8_t sys_flag=main_panel;
rt_uint16_t R_ref=500;
//rt_mutex_t scan_over_one_time=RT_NULL;
rt_uint8_t auto_scan_flag = 0;
rt_uint8_t uchar_check_step=0;

char untest[5]="未测";
char zc[5]="正常";
char gz[5]="故障";
char *lamp,*bhlj,*V_jiwei;//夜光灯，闭合逻辑，级位电压
char file_name[32]= {0};

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
      history_manager(x,y);
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
  LCD_Clear(Blue2);
  LCD_str(267,0,"选择项目",64,Blue,Blue2);
  LCD_str(0,112,"设置阀值",64,Blue,Blue2);
  LCD_str(267,112,"设置时间",64,Blue,Blue2);
  LCD_str(533,112,"历史数据",64,Blue,Blue2);
  LCD_str(0,208,"-SS7E-",64,Blue,Blue2);
  LCD_str(267,208,"-HXD3C-",64,Blue,Blue2);
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
          draw_history_top_dir();
          break;
        }
      case tks640k1:
        {
          S640K1_INIT();
          draw_s640k1();
          PowerA_EN();
          CD4067_EN();
          //rt_thread_resume(skq_scan_thread);
          //skq_scan_thread_create();
          break;
        }
      case hxd3c:
        {
          hxd3c_INIT();
          draw_hxd3c();
          PowerA_EN();
          CD4067_EN();
          //rt_thread_resume(skq_scan_thread);
          //skq_scan_thread_create();
          break;
        }
      default:
        {
          //main_panel_manager(x,y);
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
  strftime(time_buffer,sizeof(time_buffer),"%Y-%m-%d %H:%M:%S",ti);
#if 0
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
#endif
  
}

void draw_time_manager(void)
{
  LCD_Clear(Blue2);
  LCD_str(272,0,"设置时间",64,Blue,Blue2);  
  LCD_WD( 64,72,  'p', 2, 1, Blue,Blue2);
  LCD_WD( 160,72, 'q', 2, 1, Blue,Blue2);
  LCD_WD( 256,72, 'r', 2, 1, Blue,Blue2);
  LCD_WD( 416,72, 'i', 2, 1, Blue,Blue2);
  LCD_WD( 576,72, '<', 1, 1, Blue,Blue2);
  
  LCD_WD( 64,200, 'm', 2, 1, Blue,Blue2);
  LCD_WD( 160,200, 'n', 2, 1, Blue,Blue2);
  LCD_WD( 256,200, 'o', 2, 1, Blue,Blue2);
  
  LCD_WD( 64,328, 'j', 2, 1, Blue,Blue2);
  LCD_WD( 160,328, 'k', 2, 1, Blue,Blue2);
  LCD_WD( 256,328, 'l', 2, 1, Blue,Blue2);
  LCD_WD( 416,328, 'B', 2, 1, Blue,Blue2);
  LCD_WD( 576,328, 'C', 2, 1, Blue,Blue2);  
  LCD_Get_Time();
  LCD_str(416,248,time_buffer,32,Blue,Blue2);
  LCD_DrawFullRect( time_coordinate[0][0],  time_coordinate[0][1],  time_coordinate[0][2],  time_coordinate[0][3],  Red, 0);  
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
        LCD_WD( action_tp[t][0],action_tp[t][1], time_keypad_flash[t], 2, 1, Blue,Blue2);
        LCD_WD( action_tp[t][0],action_tp[t][1], time_keypad[t], 2, 1, Blue,Blue2);
        time_buffer[time_bit[time_set_flag]]=t+'0';
        LCD_str(416,248,time_buffer,32,Blue,Blue2);
        time_set_flag++;
        if(time_set_flag==14)
        {
          time_set_flag=0;
        }
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
        LCD_WD( 416,328, 'D', 2, 1, Blue,Blue2);
        LCD_WD( 416,328, 'B', 2, 1, Blue,Blue2);
        if(time_set_flag==0)
        {
          time_set_flag=13;
        }
        time_set_flag-=1;
        LCD_str(416,248,time_buffer,32,Blue,Blue2);
        LCD_DrawFullRect( time_coordinate[time_set_flag][0],  time_coordinate[time_set_flag][1],  time_coordinate[time_set_flag][2],  time_coordinate[time_set_flag][3],  Red, 0);
      }
      if(t==12)
      {
        LCD_WD( 576,328, 'E', 2, 1, Blue,Blue2);
        LCD_WD( 576,328, 'C', 2, 1, Blue,Blue2);
        if(time_set_flag==13)
        {
          time_set_flag=0;
        }
        time_set_flag+=1;
        LCD_str(416,248,time_buffer,32,Blue,Blue2);
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
  //LCD_Clear(Blue2);
  LCD_Clear(Blue2);
  LCD_str(272,0,"设置阀值",64,Blue,Blue2);
  
  
  LCD_WD( 64,72,  'p', 2, 1, Blue,Blue2);
  LCD_WD( 160,72, 'q', 2, 1, Blue,Blue2);
  LCD_WD( 256,72, 'r', 2, 1, Blue,Blue2);
  LCD_WD( 416,72, 'i', 2, 1, Blue,Blue2);
  LCD_WD( 576,72, '<', 1, 1, Blue,Blue2);
  
  LCD_WD( 64,200, 'm', 2, 1, Blue,Blue2);
  LCD_WD( 160,200, 'n', 2, 1, Blue,Blue2);
  LCD_WD( 256,200, 'o', 2, 1, Blue,Blue2);
  read_ref();
  LCD_str(416,248,ref_buffer,64,Blue,Blue2);
  LCD_str(560,280,"毫欧",32,Blue,Blue2);
  
  LCD_WD( 64,328, 'j', 2, 1, Blue,Blue2);
  LCD_WD( 160,328, 'k', 2, 1, Blue,Blue2);
  LCD_WD( 256,328, 'l', 2, 1, Blue,Blue2);
  LCD_WD( 416,328, 'B', 2, 1, Blue,Blue2);
  LCD_WD( 576,328, 'C', 2, 1, Blue,Blue2);
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
        LCD_WD( ref_action_tp[t][0],ref_action_tp[t][1], ref_keypad_flash[t], 2, 1, Blue,Blue2);
        LCD_WD( ref_action_tp[t][0],ref_action_tp[t][1], ref_keypad[t], 2, 1, Blue,Blue2);
        ref_buffer[ref_set_flag]=t+'0';
        LCD_str(416,248,ref_buffer,64,Blue,Blue2);
        ref_set_flag++;
        if(ref_set_flag==4)
        {
          ref_set_flag=0;
        }
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
        LCD_WD( 416,328, 'D', 2, 1, Blue,Blue2);
        LCD_WD( 416,328, 'B', 2, 1, Blue,Blue2);
        if(ref_set_flag==0)
        {
          ref_set_flag=3;
        }
        ref_set_flag-=1;
        LCD_str(416,248,ref_buffer,64,Blue,Blue2);
        LCD_DrawFullRect( ref_coordinate[ref_set_flag][0],  ref_coordinate[ref_set_flag][1],  ref_coordinate[ref_set_flag][2],  ref_coordinate[ref_set_flag][3],  Red, 0);
      }
      if(t==12)
      {
        LCD_WD( 576,328, 'E', 2, 1, Blue,Blue2);
        LCD_WD( 576,328, 'C', 2, 1, Blue,Blue2);
        if(ref_set_flag==3)
        {
          ref_set_flag=0;
        }
        ref_set_flag+=1;
        LCD_str(416,248,ref_buffer,64,Blue,Blue2);
        LCD_DrawFullRect( ref_coordinate[ref_set_flag][0],  ref_coordinate[ref_set_flag][1],  ref_coordinate[ref_set_flag][2],  ref_coordinate[ref_set_flag][3],  Red, 0);
      }
    }
  }
}

#if 0
#include "tc_comm.h"

rt_thread_t skq_scan_thread=RT_NULL;;
void skq_scan_thread_entry(void* parameter)
{
  //rt_err_t result;
  while (auto_scan_flag)
  {
    rt_thread_delay(10);
    switch(sys_flag)
    {
    case tks640k1:
      {
//        scan_over_one_time=0;
        rt_mutex_take(scan_over_one_time, RT_WAITING_FOREVER);
        sk640k1_scan();
//        scan_over_one_time=1;
        rt_mutex_release(scan_over_one_time);
        break;
      }
    case hxd3c:
      {
//        scan_over_one_time=0;
        rt_mutex_take(scan_over_one_time, RT_WAITING_FOREVER);
        hxd3c_scan();
//        scan_over_one_time=1;
        rt_mutex_release(scan_over_one_time);
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
  scan_over_one_time= rt_mutex_create("scan_over", RT_IPC_FLAG_FIFO);
  skq_scan_thread = rt_thread_create("skq_scan", skq_scan_thread_entry, RT_NULL, 2048, 25, 10);
  if (skq_scan_thread != RT_NULL)
  {
    rt_thread_startup(skq_scan_thread);
  }
  else
  {
    tc_stat(TC_STAT_END | TC_STAT_FAILED);
  }
  return 0;
}
#endif

int lcd_hv[24][10][2]={{{0,0},{80,0},{160,0},{240,0},{320,0},{400,0},{480,0},{560,0},{640,0},{720,0}},

{{0,20},{80,20},{160,20},{240,20},{320,20},{400,20},{480,20},{560,20},{640,20},{720,20}},

{{0,40},{80,40},{160,40},{240,40},{320,40},{400,40},{480,40},{560,40},{640,40},{720,40}},

{{0,60},{80,60},{160,60},{240,60},{320,60},{400,60},{480,60},{560,60},{640,60},{720,60}},

{{0,80},{80,80},{160,80},{240,80},{320,80},{400,80},{480,80},{560,80},{640,80},{720,80}},

{{0,100},{80,100},{160,100},{240,100},{320,100},{400,100},{480,100},{560,100},{640,100},{720,100}},

{{0,120},{80,120},{160,120},{240,120},{320,120},{400,120},{480,120},{560,120},{640,120},{720,120}},

{{0,140},{80,140},{160,140},{240,140},{320,140},{400,140},{480,140},{560,140},{640,140},{720,140}},

{{0,160},{80,160},{160,160},{240,160},{320,160},{400,160},{480,160},{560,160},{640,160},{720,160}},

{{0,180},{80,180},{160,180},{240,180},{320,180},{400,180},{480,180},{560,180},{640,180},{720,180}},

{{0,200},{80,200},{160,200},{240,200},{320,200},{400,200},{480,200},{560,200},{640,200},{720,200}},

{{0,220},{80,220},{160,220},{240,220},{320,220},{400,220},{480,220},{560,220},{640,220},{720,220}},

{{0,240},{80,240},{160,240},{240,240},{320,240},{400,240},{480,240},{560,240},{640,240},{720,240}},

{{0,260},{80,260},{160,260},{240,260},{320,260},{400,260},{480,260},{560,260},{640,260},{720,260}},

{{0,280},{80,280},{160,280},{240,280},{320,280},{400,280},{480,280},{560,280},{640,280},{720,280}},

{{0,300},{80,300},{160,300},{240,300},{320,300},{400,300},{480,300},{560,300},{640,300},{720,300}},

{{0,320},{80,320},{160,320},{240,320},{320,320},{400,320},{480,320},{560,320},{640,320},{720,320}},

{{0,340},{80,340},{160,340},{240,340},{320,340},{400,340},{480,340},{560,340},{640,340},{720,340}},

{{0,360},{80,360},{160,360},{240,360},{320,360},{400,360},{480,360},{560,360},{640,360},{720,360}},

{{0,380},{80,380},{160,380},{240,380},{320,380},{400,380},{480,380},{560,380},{640,380},{720,380}}};
static char txt2lcd_buffer[1024];
void txt2lcd(char *file_name)
{
  LCD_Clear(Blue2);
  char *p_start,*p_table,h=0,v=0;
  int length=0,fd;
  /* 只读打开进行数据校验 */
  fd = open(file_name, O_RDONLY, 0);
  if (fd < 0)
  {
    rt_kprintf("check: open file for read failed\n");
    return;
  }
  length = read(fd, txt2lcd_buffer, sizeof(txt2lcd_buffer)-1);
  
  
  p_start=txt2lcd_buffer;
  for(p_table=txt2lcd_buffer;p_table<txt2lcd_buffer+sizeof(txt2lcd_buffer);p_table++)
  {
    if(*(p_table)==',')
    {
      *(p_table)='\0';
      LCD_str(lcd_hv[h][v][0],lcd_hv[h][v][1], (unsigned char *)(p_start),16,Blue, Blue2);
      p_start=p_table+1;
      v+=1;
    }
    if(*(p_table)=='\r')
    {
      h+=1;
      v=0;
      p_start+=2;
    }
    
  }
  //txt2lcd_buffer[64]='\0';
  //rt_kprintf("%s\r\n",p+32);
  //if (length != sizeof(txt2lcd_buffer))
  //{
 //   rt_kprintf("check: read file failed\n");
 //   close(fd);
 //   return;
 // }
  close(fd);
  //LCD_str(0,0, (unsigned char *)(p+32),16,Green, Blue);
  return;
}

static char file_names[64][32]={0};
static char dir_names[32][32]={0};
static char fullpath[64];
static char txtpath[128];
rt_uint8_t scan_dir(const char *path)
{
  rt_uint8_t dir_number=0;
  DIR *dir;
  dir = opendir(path);  
  if (dir != RT_NULL)
  {
    struct dirent* dirent;
    struct stat s;
    do
    {
      dirent = readdir(dir);
      if (dirent == RT_NULL) break;
      rt_memset(&s, 0, sizeof(struct stat));
      /* build full path for each file */
      rt_sprintf(fullpath, "/%s", dirent->d_name);
      stat(fullpath, &s);
      if ( s.st_mode & DFS_S_IFDIR )
      {
        rt_kprintf("%s\t\t<DIR>\n", dirent->d_name);
        rt_sprintf(dir_names[dir_number], "%s", dirent->d_name);
        dir_number++;
      }
      else
      {
        //rt_kprintf("%s\t\t%lu\n", dirent->d_name, s.st_size);
        //rt_sprintf(file_names[dir_number], "%s", dirent->d_name);
        //file_number++;
      }
    }
    while (dirent != RT_NULL);
    closedir(dir);
  }
  else rt_kprintf("open %s directory failed\n", path);
  return dir_number;
}


rt_uint8_t scan_file(const char *path)
{
  rt_uint8_t file_number=0;
  DIR *dir;
  dir = opendir(path);  
  if (dir != RT_NULL)
  {
    struct dirent* dirent;
    struct stat s;
    do
    {
      dirent = readdir(dir);
      if (dirent == RT_NULL) break;
      rt_memset(&s, 0, sizeof(struct stat));
      /* build full path for each file */
      rt_sprintf(fullpath, "/%s", dirent->d_name);
      stat(fullpath, &s);
      if ( s.st_mode & DFS_S_IFDIR )
      {
        //rt_kprintf("%s\t\t<DIR>\n", dirent->d_name);
        //rt_sprintf(dir_names[dir_number], "%s", dirent->d_name);
        //dir_number++;
      }
      else
      {
        rt_kprintf("%s\t\t%lu\n", dirent->d_name, s.st_size);
        rt_sprintf(file_names[file_number], "%s", dirent->d_name);
        file_number++;
      }
    }
    while (dirent != RT_NULL);
    closedir(dir);
  }
  else rt_kprintf("open %s directory failed\n", path);
  return file_number;
}






#ifdef RT_USING_FINSH
#include <finsh.h>
/* 输出函数到finsh shell命令行中 */
FINSH_FUNCTION_EXPORT(txt2lcd, display txt file on lcd);
FINSH_FUNCTION_EXPORT(scan_file, scan files in a DIR);
FINSH_FUNCTION_EXPORT(scan_dir, scan dir in a DIR);
FINSH_FUNCTION_EXPORT(history_manager,  display data files);
#endif


rt_int8_t txt_displaying=0;
rt_int8_t dir_opened=0;
rt_int8_t history_top_dir=0;


rt_int16_t chexing_zuobiao[15][2]={
  {0,88},{266,88},{532,88},
{0,168},{266,168},{532,168},
{0,248},{266,248},{532,248},
{0,328},{266,328},{532,328},
{0,408},{266,408},{532,408}};

rt_int16_t chexing_chumo[15][4]={
  {0,80,266,160},{266,80,532,160},{532,80,798,160},
{0,160,266,240},{266,160,532,240},{532,160,798,240},
{0,240,266,320},{266,240,532,320},{532,240,798,320},
{0,320,266,400},{266,320,532,400},{532,320,798,400},
{0,400,266,480},{266,400,532,480},{532,400,798,480}};

rt_int16_t txt_zuobiao[34][2]={
{0,0},{400,0},{0,24},{400,24},{0,48},{400,48},{0,72},
{400,72},{0,96},{400,96},{0,120},{400,120},{0,144},
{400,144},{0,168},{400,168},{0,192},{400,192},{0,216},
{400,216},{0,240},{400,240},{0,264},{400,264},{0,288},
{400,288},{0,312},{400,312},{0,336},{400,336},{0,360},
{400,360},{0,384},{400,384}};

rt_int16_t txt_chumo[37][4]={
{0,0,400,24},{400,0,800,24},{0,24,400,48},{400,24,800,48},
{0,48,400,72},{400,48,800,72},{0,72,400,96},{400,72,800,96},
{0,96,400,120},{400,96,800,120},{0,120,400,144},{400,120,800,144},
{0,144,400,168},{400,144,800,168},{0,168,400,192},{400,168,800,192},
{0,192,400,216},{400,192,800,216},{0,216,400,240},{400,216,800,240},
{0,240,400,264},{400,240,800,264},{0,264,400,288},{400,264,800,288},
{0,288,400,312},{400,288,800,312},{0,312,400,336},{400,312,800,336},
{0,336,400,360},{400,336,800,360},{0,360,400,384},{400,360,800,384},
{0,384,400,408},{400,384,800,408},

{0,416,266,480},{266,416,532,480},{532,416,798,480}};



void draw_history_top_dir(void)
{
  LCD_Clear(Blue2);
  rt_uint16_t n,t;
  LCD_str(272,0,"选择型号",64,Blue,Blue2);
  t=scan_dir("/");
  for(n=0;n<t;n++)
  {
    LCD_str(chexing_zuobiao[n][0],chexing_zuobiao[n][1],dir_names[n],64,Blue,Blue2);
  }
  LCD_str(chexing_zuobiao[14][0],chexing_zuobiao[14][1],"返回主页",64,Blue,Blue2);
  history_top_dir=1;
}
void history_manager(rt_uint16_t x,rt_uint16_t y)
{
  rt_uint8_t t,m,n;
  n=scan_dir("/");
  if(history_top_dir)
  {
    for(t=0;t<15;t++)
    {
      if(((y>chexing_chumo[t][1])&&(y<chexing_chumo[t][3]))&&((x>chexing_chumo[t][0])&&(x<chexing_chumo[t][2])))
      {
        dir_opened=t;
        break;
      }
    }
    if(t==14)
    {
      sys_flag=main_panel;
      draw_main_panel();
    }
    else if(t==13)
    {
      //上一页
    }
    else if(t==12)
    {
      //下一页
    }
    else if(t<n)
    {
      rt_sprintf(fullpath, "/%s", dir_names[t]);
      t=scan_file(fullpath);
      LCD_Clear(Blue2);
      if(t==0)
      {
        LCD_str(txt_zuobiao[0][0],txt_zuobiao[0][1],"这个文件夹目前无内容",24,Blue,Blue2);
      }
      else
      {
        for(m=0;m<t;m++)
        {
          LCD_str(txt_zuobiao[m][0],txt_zuobiao[m][1],file_names[m],24,Blue,Blue2);
        }
      }      
      LCD_str(chexing_zuobiao[14][0],chexing_zuobiao[14][1],"返回上级",64,Blue,Blue2);
      history_top_dir=0;
    }
  }
  else
  {
    if(txt_displaying)
    {
      if(((y>txt_chumo[36][1])&&(y<txt_chumo[36][3]))&&((x>txt_chumo[36][0])&&(x<txt_chumo[36][2])))
      {
        rt_sprintf(fullpath, "/%s", dir_names[dir_opened]);
        t=scan_file(fullpath);
        LCD_Clear(Blue2);
        for(m=0;m<t;m++)
        {
          LCD_str(txt_zuobiao[m][0],txt_zuobiao[m][1],file_names[m],24,Blue,Blue2);
        }
        LCD_str(chexing_zuobiao[14][0],chexing_zuobiao[14][1],"返回上级",64,Blue,Blue2);
        history_top_dir=0;
        txt_displaying=0;
      }
    }
    else
    {
      rt_sprintf(fullpath, "/%s", dir_names[dir_opened]);
      m=scan_file(fullpath);
      for(t=0;t<37;t++)
      {
        if(((y>txt_chumo[t][1])&&(y<txt_chumo[t][3]))&&((x>txt_chumo[t][0])&&(x<txt_chumo[t][2])))
        {
          break;
        }
      }
      if(t==36)//返回history界面
      {
        history_top_dir=1;
        draw_history_top_dir();
      }
      else if(t==35)
      {
        //上一页
      }
      else if(t==34)
      {
        //下一页
      }
      else if(t<m)
      {
        txt_displaying=1;
        LCD_Clear(Blue2);
        rt_sprintf(txtpath, "/%s/%s", dir_names[dir_opened],file_names[t]);
        txt2lcd(txtpath);
        LCD_str(chexing_zuobiao[14][0],chexing_zuobiao[14][1],"返回上级",64,Blue,Blue2);
      }      
    }    
  }
}




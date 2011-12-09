

#include"ref_manage.h"


unsigned char ref_set_flag=0;
unsigned char ref_keypad[11]="ijklmnopqr";
unsigned char ref_keypad_flash[11]="tuvwxyz{|}";
char ref_buffer[5]={0,0,0,0,'\0'};
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
  char *str,n;
  str=read_file("/","ref.txt",0x00,4);
  for(n=0;n<4;n++)
  {
    ref_buffer[n]=*(str+n);
  }
  ref=(ref_buffer[0]-'0')*1000+(ref_buffer[1]-'0')*100+(ref_buffer[2]-'0')*10+(ref_buffer[3]-'0');
}
void write_ref(void)
{
  edit_file("/","ref.txt",ref_buffer,0x00);
  ref=(ref_buffer[0]-'0')*1000+(ref_buffer[1]-'0')*100+(ref_buffer[2]-'0')*10+(ref_buffer[3]-'0');
}

void draw_ref_manager(void)
{
  LCD_Clear(LCD_COLOR_CYAN);
  LCD_Clear(LCD_COLOR_BLACK);
  LCD_str(272,0,"ÉèÖÃ·§Öµ",64,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  
  LCD_WD( 64,72,  'p', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 160,72, 'q', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 256,72, 'r', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 416,72, 'i', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 576,72, '<', 1, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  LCD_WD( 64,200, 'm', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 160,200, 'n', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 256,200, 'o', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  read_ref();
  LCD_str(416,248,ref_buffer,64,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
  LCD_str(560,280,"ºÁÅ·",32,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
  
  LCD_WD( 64,328, 'j', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 160,328, 'k', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 256,328, 'l', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 416,328, 'B', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 576,328, 'C', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_DrawFullRect( ref_coordinate[0][0],  ref_coordinate[0][1],  ref_coordinate[0][2],  ref_coordinate[0][3],  LCD_COLOR_RED, 0);
}



void ref_manager(u16 x,u16 y)
{

  u8 t;
  for(t=0;t<13;t++)
  {
    if(((y>ref_action_tp[t][1])&&(y<ref_action_tp[t][3]))&&((x>ref_action_tp[t][0])&&(x<ref_action_tp[t][2])))
    {
      if(t<10)
      {
        LCD_WD( ref_action_tp[t][0],ref_action_tp[t][1], ref_keypad_flash[t], 2, 1, LCD_COLOR_CYAN,LCD_COLOR_BLACK);
        LCD_WD( ref_action_tp[t][0],ref_action_tp[t][1], ref_keypad[t], 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        ref_buffer[ref_set_flag]=t+'0';
        LCD_str(416,248,ref_buffer,64,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
        LCD_DrawFullRect( ref_coordinate[ref_set_flag][0],  ref_coordinate[ref_set_flag][1],  ref_coordinate[ref_set_flag][2],  ref_coordinate[ref_set_flag][3],  LCD_COLOR_RED, 0);
      }
      if(t==10)
      {
        write_ref();
        sys_flag=main_panel;
        LCD_Clear(LCD_COLOR_BLACK);
      }
      if(t==11)
      {
        LCD_WD( 416,328, 'D', 2, 1, LCD_COLOR_CYAN,LCD_COLOR_BLACK);
        LCD_WD( 416,328, 'B', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        if(ref_set_flag==0)
        {
          ref_set_flag=3;
        }
        ref_set_flag-=1;
        LCD_str(416,248,ref_buffer,64,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
        LCD_DrawFullRect( ref_coordinate[ref_set_flag][0],  ref_coordinate[ref_set_flag][1],  ref_coordinate[ref_set_flag][2],  ref_coordinate[ref_set_flag][3],  LCD_COLOR_RED, 0);
      }
      if(t==12)
      {
        LCD_WD( 576,328, 'E', 2, 1, LCD_COLOR_CYAN,LCD_COLOR_BLACK);
        LCD_WD( 576,328, 'C', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        if(ref_set_flag==3)
        {
          ref_set_flag=0;
        }
        ref_set_flag+=1;
        LCD_str(416,248,ref_buffer,64,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
        LCD_DrawFullRect( ref_coordinate[ref_set_flag][0],  ref_coordinate[ref_set_flag][1],  ref_coordinate[ref_set_flag][2],  ref_coordinate[ref_set_flag][3],  LCD_COLOR_RED, 0);
      }
    }
  }
}


#include"time_manage.h"


unsigned char time_set_flag=0;
unsigned char time_bit[14]={0,1,2,3,5,6,8,9,11,12,14,15,17,18};
unsigned char time_keypad[11]="ijklmnopqr";
unsigned char time_keypad_flash[11]="tuvwxyz{|}";
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



void draw_time_manager(void)
{
  LCD_Clear(LCD_COLOR_BLACK);
  LCD_str(272,0,"…Ë÷√ ±º‰",64,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  
  LCD_WD( 64,72,  'p', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 160,72, 'q', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 256,72, 'r', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 416,72, 'i', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 576,72, '<', 1, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  LCD_WD( 64,200, 'm', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 160,200, 'n', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 256,200, 'o', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(416,248,get_time_now(),32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  LCD_WD( 64,328, 'j', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 160,328, 'k', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 256,328, 'l', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 416,328, 'B', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_WD( 576,328, 'C', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_DrawFullRect( time_coordinate[0][0],  time_coordinate[0][1],  time_coordinate[0][2],  time_coordinate[0][3],  LCD_COLOR_RED, 0);
}




void time_manager(u16 x,u16 y)
{

  u8 t;
  for(t=0;t<13;t++)
  {
    if(((y>action_tp[t][1])&&(y<action_tp[t][3]))&&((x>action_tp[t][0])&&(x<action_tp[t][2])))
    {
      if(t<10)
      {
        LCD_WD( action_tp[t][0],action_tp[t][1], time_keypad_flash[t], 2, 1, LCD_COLOR_CYAN,LCD_COLOR_BLACK);
        LCD_WD( action_tp[t][0],action_tp[t][1], time_keypad[t], 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        time_buffer[time_bit[time_set_flag]]=t+'0';
        LCD_str(416,248,time_buffer,32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        LCD_DrawFullRect( time_coordinate[time_set_flag][0],  time_coordinate[time_set_flag][1],  time_coordinate[time_set_flag][2],  time_coordinate[time_set_flag][3],  LCD_COLOR_RED, 0);
      }
      if(t==10)
      {
        LCD_Set_Time(time_buffer);
        sys_flag=main_panel;
        LCD_Clear(LCD_COLOR_BLACK);
      }
      if(t==11)
      {
        LCD_WD( 416,328, 'D', 2, 1, LCD_COLOR_CYAN,LCD_COLOR_BLACK);
        LCD_WD( 416,328, 'B', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        if(time_set_flag==0)
        {
          time_set_flag=13;
        }
        time_set_flag-=1;
        LCD_str(416,248,time_buffer,32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        LCD_DrawFullRect( time_coordinate[time_set_flag][0],  time_coordinate[time_set_flag][1],  time_coordinate[time_set_flag][2],  time_coordinate[time_set_flag][3],  LCD_COLOR_RED, 0);
      }
      if(t==12)
      {
        LCD_WD( 576,328, 'E', 2, 1, LCD_COLOR_CYAN,LCD_COLOR_BLACK);
        LCD_WD( 576,328, 'C', 2, 1, LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        if(time_set_flag==13)
        {
          time_set_flag=0;
        }
        time_set_flag+=1;
        LCD_str(416,248,time_buffer,32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        LCD_DrawFullRect( time_coordinate[time_set_flag][0],  time_coordinate[time_set_flag][1],  time_coordinate[time_set_flag][2],  time_coordinate[time_set_flag][3],  LCD_COLOR_RED, 0);
      }
    }
  }
}
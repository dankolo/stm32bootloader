

#include"main_panel.h"


unsigned char main_panel_flag[12]={set_ref,set_time,history,tks640k1,tks14a};



unsigned int main_panel_tp[12][4]=
{
{0,96,266,192},{266,96,532,192},{532,96,798,192},
{0,192,266,288},{266,192,532,288},{532,192,798,288},
{0,288,266,384},{266,288,532,384},{532,288,798,384},
{0,384,266,480},{266,384,532,480},{532,384,798,480}
};//0 1 2
//  3 4 5
//  6 7 8
//  9 10 11

void draw_main_panel(void)
{
  LCD_Clear(LCD_COLOR_BLACK);
  LCD_str(267,0,"选择项目",64,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(0,112,"设置阀值",64,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(267,112,"设置时间",64,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(533,112,"历史数据",64,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(0,208,"S640K1",64,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
}




void main_panel_manager(u16 x,u16 y)
{

  u8 t;
  for(t=0;t<12;t++)
  {
    if(((y>main_panel_tp[t][1])&&(y<main_panel_tp[t][3]))&&((x>main_panel_tp[t][0])&&(x<main_panel_tp[t][2])))
    {
      sys_flag=main_panel_flag[t];
      return;
    }
  }
}
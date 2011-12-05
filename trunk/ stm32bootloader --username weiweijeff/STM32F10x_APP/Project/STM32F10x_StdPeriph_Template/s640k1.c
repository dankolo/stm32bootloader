#include "s640k1.h"


void draw_s640k1(void)
{
  LCD_Clear(LCD_COLOR_BLACK);
  LCD_str(267,0,"S640K1",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
//  LCD_str(0,32,"换向手柄",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(64,32,"后零前制",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  u8 n=0;
  for(n=0;n<7;n++)
  {
    LCD_DrawUniLine( 64,  (80+32*n),  192,  (80+32*n),  LCD_COLOR_CYAN);
  }
  for(n=0;n<4;n++)
  {
    LCD_DrawUniLine( (80+32*n),  64,  (80+32*n),  288,  LCD_COLOR_CYAN);
  }
  
//  LCD_str(384,64,"控制手柄",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(112,288,"制动",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(272,288,"零",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(428,288,"牵引",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(76,336,"1   3   6   9   12  15  17  0   *   3   6   9   12  15  17",16,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  for(n=0;n<4;n++)
  {
    LCD_DrawUniLine( 64,  (368+32*n),  544,  (368+32*n),  LCD_COLOR_CYAN);
  }
  for(n=0;n<15;n++)
  {
    LCD_DrawUniLine( (80+32*n),  352,  (80+32*n),  479,  LCD_COLOR_CYAN);
  }
}
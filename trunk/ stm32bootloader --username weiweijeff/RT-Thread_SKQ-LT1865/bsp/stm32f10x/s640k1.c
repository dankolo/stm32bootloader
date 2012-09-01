
#include <rtthread.h>
#include "tc_comm.h"
#include "gel.h"
#include "analog.h"
#include "s640k1.h"



#define sk640_steps 12

struct level S640K1_levels[18];
u16 S640K1_TP[26][4]=
{
  {128,64,160,96},{160,64,192,96},{192,64,224,96},{224,64,256,96},{256,64,288,96},{288,64,320,96},{320,64,352,96},
  {352,64,384,96},
  {384,64,416,96},{416,64,448,96},{448,64,480,96},{480,64,512,96},{512,64,544,96},{544,64,576,96},{576,64,608,96},
  {128,224,160,256},{160,224,192,256},{192,224,224,256},{224,224,256,256},
  {0,1,128,63},{670,1,798,63},{536,336,664,400},{670,336,798,400},{536,416,600,479},{600,416,664,479},{670,416,798,479}
};

u16 S640K1_POINTS[43][2]=
{
  {144,272},          {144,336},{144,368},                    {144,464},
  
  {208,272},{208,304},          {208,368},          {208,432},
  {240,272},          {240,336},          {240,400},{240,432},
  /*********************************************************************/
  {144,144},{144,176},
  {176,144},{176,176},
  {208,144},{208,176},
  {240,144},{240,176},
  {272,144},{272,176},
  {304,144},{304,176},
  {336,144},{336,176},
  {368,112},
  {400,144},{400,176},{400,208},
  {432,144},{432,176},{432,208},
  {464,144},{464,176},
  {496,144},{496,176},
  {528,144},{528,176},
  {560,144},{560,176},
  {592,144},{592,176}
};

u16 S640K1_value_disp[11][2]=
{
  {735,96},{735,128},{735,160},{735,192},
  {384,256},{384,288},{384,320},{384,352},{384,384},{384,416},{384,447}
};
u16 sk640_jiwei_v[19]= {0,200,1085,1966,2847,3728,4609,5490,6371,7252,8133,9014,9895,10776,11657,12538,13419,14300,15000};
u8 sk640_jiwei_flag=0x7f;
u8 sk640_jiwei_q[7]= {0,3,6,9,12,15,17};
u8 sk640_jiwei_z[7]= {17,15,12,9,6,3,0};


void draw_s640k1(void)
{
  LCD_Clear(Black);
  LCD_str(267,0,"测试型号:S640K1",32,Blue,Black);
  
  
  //  LCD_str(0,32,"换向手柄",32,Blue,Black);
  LCD_str(128,224,"后零前制",32,Blue,Black);
  LCD_str(0,256,"402(403)",32,Blue,Black);
  LCD_str(0,288,"404(405)",32,Blue,Black);
  LCD_str(0,320,"405(404)",32,Blue,Black);
  LCD_str(0,352,"407(407)",32,Blue,Black);
  LCD_str(0,384,"406(406)",32,Blue,Black);
  LCD_str(0,416,"409(410)",32,Blue,Black);
  LCD_str(0,447,"410(409)",32,Blue,Black);
  
  LCD_str(256,256,"401(401)",32,Blue,Black);
  //  LCD_str(256,96,"401(401)",32,Blue,Black);
  //  LCD_str(256,128,"401(401)",32,Blue,Black);
  //  LCD_str(256,352,"401(401)",32,Blue,Black);
  //  LCD_str(256,192,"401(401)",32,Blue,Black);
  //  LCD_str(256,224,"401(401)",32,Blue,Black);
  //  LCD_str(256,256,"401(401)",32,Blue,Black);
  
  u8 n=0;
  for(n=0; n<7; n++)
  {
    LCD_DrawUniLine( 128,  (272+32*n),  256,  (272+32*n),  Green);
  }
  for(n=0; n<4; n++)
  {
    LCD_DrawUniLine( (144+32*n),  256,  (144+32*n),  479,  Green);
  }
  LCD_DrawUniLine( 256, 272,  256,  464,  Green);
  
  
  //  LCD_str(384,64,"控制手柄",32,Blue,Black);
  LCD_str(176,32,"制动",32,Blue,Black);
  LCD_str(352,32,"零",32,Blue,Black);
  LCD_str(492,32,"牵引",32,Blue,Black);
  LCD_str(136,64,"1",32,Blue,Black);
  LCD_str(168,64,"3",32,Blue,Black);
  LCD_str(200,64,"6",32,Blue,Black);
  LCD_str(232,64,"9",32,Blue,Black);
  LCD_str(256,64,"12",32,Blue,Black);
  LCD_str(288,64,"15",32,Blue,Black);
  LCD_str(320,64,"17",32,Blue,Black);
  LCD_str(360,64,"0",32,Blue,Black);
  LCD_str(392,64,"*",32,Blue,Black);
  LCD_str(424,64,"3",32,Blue,Black);
  LCD_str(456,64,"6",32,Blue,Black);
  LCD_str(488,64,"9",32,Blue,Black);
  LCD_str(512,64,"12",32,Blue,Black);
  LCD_str(544,64,"15",32,Blue,Black);
  LCD_str(576,64,"17",32,Blue,Black);
  
  
  LCD_str(0,96,"422(415)",32,Blue,Black);
  LCD_str(0,160,"402(403)",32,Blue,Black);
  
  LCD_str(608,96,"414(416)",32,Blue,Black);
  LCD_str(608,144,"412(412)",32,Blue,Black);
  LCD_str(608,192,"413(413)",32,Blue,Black);
  
  for(n=0; n<4; n++)
  {
    LCD_DrawUniLine( 128,  (112+32*n),  608,  (112+32*n),  Green);
  }
  for(n=0; n<15; n++)
  {
    LCD_DrawUniLine( (144+32*n),  96,  (144+32*n),  224,  Green);
  }
  LCD_DrawUniLine( 608, 144,  608,  176,  Green);
  LCD_DrawUniLine( 128, 144,  128,  272,  Green);
  
  for(n=0; n<43; n++)
  {
    LCD_DrawFullCircle( S640K1_POINTS[n][0],  S640K1_POINTS[n][1],  5,  Blue2,  1);
  }
  for(n=0; n<26; n++)
  {
    LCD_DrawFullRect( S640K1_TP[n][0],   S640K1_TP[n][1],   S640K1_TP[n][2],   S640K1_TP[n][3],  Blue2, 0);
  }
  
  //LCD_str(671,352,"手动模式",32,Blue2,Black);
  LCD_str(0,16,"手动模式",32,Blue2,Black);
  LCD_str(671,432,"保存数据",32,Blue2,Black);
  LCD_str(671,256,"级位电压",32,Blue,Black);
  LCD_str(671,16,"退出实验",32,Red,Black);
  LCD_str(552,432,"是",32,Blue,Black);
  LCD_str(616,432,"否",32,Blue,Black);
  LCD_str(552,352,"上一步",32,Blue,Black);
  LCD_str(687,352,"下一步",32,Blue,Black);
  LCD_str(257,287,"扳到大零位\n完成后按是",24,Red,Black);
}



void S640K1_INIT(void)
{
  
  S640K1_levels[0].contacts[0].flag_last=0;
  S640K1_levels[0].contacts[0].channel=7;
  S640K1_levels[0].contacts[0].div=0.6667;
  S640K1_levels[0].contacts[0].point_coordinate[0]=S640K1_POINTS[12][0];
  S640K1_levels[0].contacts[0].point_coordinate[1]=S640K1_POINTS[12][1];
  S640K1_levels[0].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[0].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[0].contacts[1].flag_last=1;
  S640K1_levels[0].contacts[1].channel=7;
  S640K1_levels[0].contacts[1].div=0.6667;
  S640K1_levels[0].contacts[1].point_coordinate[0]=S640K1_POINTS[13][0];
  S640K1_levels[0].contacts[1].point_coordinate[1]=S640K1_POINTS[13][1];
  S640K1_levels[0].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[0].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  
  S640K1_levels[1].contacts[0].flag_last=0;
  S640K1_levels[1].contacts[0].channel=7;
  S640K1_levels[1].contacts[0].div=0.6667;
  S640K1_levels[1].contacts[0].point_coordinate[0]=S640K1_POINTS[14][0];
  S640K1_levels[1].contacts[0].point_coordinate[1]=S640K1_POINTS[14][1];
  S640K1_levels[1].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[1].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[1].contacts[1].flag_last=1;
  S640K1_levels[1].contacts[1].channel=7;
  S640K1_levels[1].contacts[1].div=0.6667;
  S640K1_levels[1].contacts[1].point_coordinate[0]=S640K1_POINTS[15][0];
  S640K1_levels[1].contacts[1].point_coordinate[1]=S640K1_POINTS[15][1];
  S640K1_levels[1].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[1].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  
  S640K1_levels[2].contacts[0].flag_last=0;
  S640K1_levels[2].contacts[0].channel=7;
  S640K1_levels[2].contacts[0].div=0.6667;
  S640K1_levels[2].contacts[0].point_coordinate[0]=S640K1_POINTS[16][0];
  S640K1_levels[2].contacts[0].point_coordinate[1]=S640K1_POINTS[16][1];
  S640K1_levels[2].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[2].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[2].contacts[1].flag_last=1;
  S640K1_levels[2].contacts[1].channel=7;
  S640K1_levels[2].contacts[1].div=0.6667;
  S640K1_levels[2].contacts[1].point_coordinate[0]=S640K1_POINTS[17][0];
  S640K1_levels[2].contacts[1].point_coordinate[1]=S640K1_POINTS[17][1];
  S640K1_levels[2].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[2].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  
  S640K1_levels[3].contacts[0].flag_last=0;
  S640K1_levels[3].contacts[0].channel=7;
  S640K1_levels[3].contacts[0].div=0.6667;
  S640K1_levels[3].contacts[0].point_coordinate[0]=S640K1_POINTS[18][0];
  S640K1_levels[3].contacts[0].point_coordinate[1]=S640K1_POINTS[18][1];
  S640K1_levels[3].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[3].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[3].contacts[1].flag_last=1;
  S640K1_levels[3].contacts[1].channel=7;
  S640K1_levels[3].contacts[1].div=0.6667;
  S640K1_levels[3].contacts[1].point_coordinate[0]=S640K1_POINTS[19][0];
  S640K1_levels[3].contacts[1].point_coordinate[1]=S640K1_POINTS[19][1];
  S640K1_levels[3].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[3].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  
  S640K1_levels[4].contacts[0].flag_last=0;
  S640K1_levels[4].contacts[0].channel=7;
  S640K1_levels[4].contacts[0].div=0.6667;
  S640K1_levels[4].contacts[0].point_coordinate[0]=S640K1_POINTS[20][0];
  S640K1_levels[4].contacts[0].point_coordinate[1]=S640K1_POINTS[20][1];
  S640K1_levels[4].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[4].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[4].contacts[1].flag_last=1;
  S640K1_levels[4].contacts[1].channel=7;
  S640K1_levels[4].contacts[1].div=0.6667;
  S640K1_levels[4].contacts[1].point_coordinate[0]=S640K1_POINTS[21][0];
  S640K1_levels[4].contacts[1].point_coordinate[1]=S640K1_POINTS[21][1];
  S640K1_levels[4].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[4].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  S640K1_levels[5].contacts[0].flag_last=0;
  S640K1_levels[5].contacts[0].channel=7;
  S640K1_levels[5].contacts[0].div=0.6667;
  S640K1_levels[5].contacts[0].point_coordinate[0]=S640K1_POINTS[22][0];
  S640K1_levels[5].contacts[0].point_coordinate[1]=S640K1_POINTS[22][1];
  S640K1_levels[5].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[5].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[5].contacts[1].flag_last=1;
  S640K1_levels[5].contacts[1].channel=7;
  S640K1_levels[5].contacts[1].div=0.6667;
  S640K1_levels[5].contacts[1].point_coordinate[0]=S640K1_POINTS[23][0];
  S640K1_levels[5].contacts[1].point_coordinate[1]=S640K1_POINTS[23][1];
  S640K1_levels[5].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[5].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  S640K1_levels[6].contacts[0].flag_last=0;
  S640K1_levels[6].contacts[0].channel=7;
  S640K1_levels[6].contacts[0].div=0.6667;
  S640K1_levels[6].contacts[0].point_coordinate[0]=S640K1_POINTS[24][0];
  S640K1_levels[6].contacts[0].point_coordinate[1]=S640K1_POINTS[24][1];
  S640K1_levels[6].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[6].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[6].contacts[1].flag_last=1;
  S640K1_levels[6].contacts[1].channel=7;
  S640K1_levels[6].contacts[1].div=0.6667;
  S640K1_levels[6].contacts[1].point_coordinate[0]=S640K1_POINTS[25][0];
  S640K1_levels[6].contacts[1].point_coordinate[1]=S640K1_POINTS[25][1];
  S640K1_levels[6].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[6].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  /**************************************************************************************************/
  
  S640K1_levels[7].contacts[0].flag_last=1;
  S640K1_levels[7].contacts[0].channel=0;
  S640K1_levels[7].contacts[0].div=1;
  S640K1_levels[7].contacts[0].point_coordinate[0]=S640K1_POINTS[26][0];
  S640K1_levels[7].contacts[0].point_coordinate[1]=S640K1_POINTS[26][1];
  S640K1_levels[7].contacts[0].value_coordinate[0]=S640K1_value_disp[0][0];
  S640K1_levels[7].contacts[0].value_coordinate[1]=S640K1_value_disp[0][1];
  
  /**************************************************************************************************/
  
  
  
  S640K1_levels[8].contacts[0].flag_last=0;
  S640K1_levels[8].contacts[0].channel=7;
  S640K1_levels[8].contacts[0].div=0.6667;
  S640K1_levels[8].contacts[0].point_coordinate[0]=S640K1_POINTS[27][0];
  S640K1_levels[8].contacts[0].point_coordinate[1]=S640K1_POINTS[27][1];
  S640K1_levels[8].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[8].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[8].contacts[1].flag_last=0;
  S640K1_levels[8].contacts[1].channel=7;
  S640K1_levels[8].contacts[1].div=0.6667;
  S640K1_levels[8].contacts[1].point_coordinate[0]=S640K1_POINTS[28][0];
  S640K1_levels[8].contacts[1].point_coordinate[1]=S640K1_POINTS[28][1];
  S640K1_levels[8].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[8].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  S640K1_levels[8].contacts[2].flag_last=1;
  S640K1_levels[8].contacts[2].channel=8;
  S640K1_levels[8].contacts[2].div=0.5;
  S640K1_levels[8].contacts[2].point_coordinate[0]=S640K1_POINTS[29][0];
  S640K1_levels[8].contacts[2].point_coordinate[1]=S640K1_POINTS[29][1];
  S640K1_levels[8].contacts[2].value_coordinate[0]=S640K1_value_disp[3][0];
  S640K1_levels[8].contacts[2].value_coordinate[1]=S640K1_value_disp[3][1];
  
  
  
  S640K1_levels[9].contacts[0].flag_last=0;
  S640K1_levels[9].contacts[0].channel=7;
  S640K1_levels[9].contacts[0].div=0.6667;
  S640K1_levels[9].contacts[0].point_coordinate[0]=S640K1_POINTS[30][0];
  S640K1_levels[9].contacts[0].point_coordinate[1]=S640K1_POINTS[30][1];
  S640K1_levels[9].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[9].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[9].contacts[1].flag_last=0;
  S640K1_levels[9].contacts[1].channel=7;
  S640K1_levels[9].contacts[1].div=0.6667;
  S640K1_levels[9].contacts[1].point_coordinate[0]=S640K1_POINTS[31][0];
  S640K1_levels[9].contacts[1].point_coordinate[1]=S640K1_POINTS[31][1];
  S640K1_levels[9].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[9].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  S640K1_levels[9].contacts[2].flag_last=1;
  S640K1_levels[9].contacts[2].channel=8;
  S640K1_levels[9].contacts[2].div=0.5;
  S640K1_levels[9].contacts[2].point_coordinate[0]=S640K1_POINTS[32][0];
  S640K1_levels[9].contacts[2].point_coordinate[1]=S640K1_POINTS[32][1];
  S640K1_levels[9].contacts[2].value_coordinate[0]=S640K1_value_disp[3][0];
  S640K1_levels[9].contacts[2].value_coordinate[1]=S640K1_value_disp[3][1];
  
  
  
  S640K1_levels[10].contacts[0].flag_last=0;
  S640K1_levels[10].contacts[0].channel=7;
  S640K1_levels[10].contacts[0].div=0.6667;
  S640K1_levels[10].contacts[0].point_coordinate[0]=S640K1_POINTS[33][0];
  S640K1_levels[10].contacts[0].point_coordinate[1]=S640K1_POINTS[33][1];
  S640K1_levels[10].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[10].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[10].contacts[1].flag_last=1;
  S640K1_levels[10].contacts[1].channel=7;
  S640K1_levels[10].contacts[1].div=0.6667;
  S640K1_levels[10].contacts[1].point_coordinate[0]=S640K1_POINTS[34][0];
  S640K1_levels[10].contacts[1].point_coordinate[1]=S640K1_POINTS[34][1];
  S640K1_levels[10].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[10].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  S640K1_levels[11].contacts[0].flag_last=0;
  S640K1_levels[11].contacts[0].channel=7;
  S640K1_levels[11].contacts[0].div=0.6667;
  S640K1_levels[11].contacts[0].point_coordinate[0]=S640K1_POINTS[35][0];
  S640K1_levels[11].contacts[0].point_coordinate[1]=S640K1_POINTS[35][1];
  S640K1_levels[11].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[11].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[11].contacts[1].flag_last=1;
  S640K1_levels[11].contacts[1].channel=7;
  S640K1_levels[11].contacts[1].div=0.6667;
  S640K1_levels[11].contacts[1].point_coordinate[0]=S640K1_POINTS[36][0];
  S640K1_levels[11].contacts[1].point_coordinate[1]=S640K1_POINTS[36][1];
  S640K1_levels[11].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[11].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  
  S640K1_levels[12].contacts[0].flag_last=0;
  S640K1_levels[12].contacts[0].channel=7;
  S640K1_levels[12].contacts[0].div=0.6667;
  S640K1_levels[12].contacts[0].point_coordinate[0]=S640K1_POINTS[37][0];
  S640K1_levels[12].contacts[0].point_coordinate[1]=S640K1_POINTS[37][1];
  S640K1_levels[12].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[12].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[12].contacts[1].flag_last=1;
  S640K1_levels[12].contacts[1].channel=7;
  S640K1_levels[12].contacts[1].div=0.6667;
  S640K1_levels[12].contacts[1].point_coordinate[0]=S640K1_POINTS[38][0];
  S640K1_levels[12].contacts[1].point_coordinate[1]=S640K1_POINTS[38][1];
  S640K1_levels[12].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[12].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  
  S640K1_levels[13].contacts[0].flag_last=0;
  S640K1_levels[13].contacts[0].channel=7;
  S640K1_levels[13].contacts[0].div=0.6667;
  S640K1_levels[13].contacts[0].point_coordinate[0]=S640K1_POINTS[39][0];
  S640K1_levels[13].contacts[0].point_coordinate[1]=S640K1_POINTS[39][1];
  S640K1_levels[13].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[13].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[13].contacts[1].flag_last=1;
  S640K1_levels[13].contacts[1].channel=7;
  S640K1_levels[13].contacts[1].div=0.6667;
  S640K1_levels[13].contacts[1].point_coordinate[0]=S640K1_POINTS[40][0];
  S640K1_levels[13].contacts[1].point_coordinate[1]=S640K1_POINTS[40][1];
  S640K1_levels[13].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[13].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  S640K1_levels[14].contacts[0].flag_last=0;
  S640K1_levels[14].contacts[0].channel=7;
  S640K1_levels[14].contacts[0].div=0.6667;
  S640K1_levels[14].contacts[0].point_coordinate[0]=S640K1_POINTS[41][0];
  S640K1_levels[14].contacts[0].point_coordinate[1]=S640K1_POINTS[41][1];
  S640K1_levels[14].contacts[0].value_coordinate[0]=S640K1_value_disp[1][0];
  S640K1_levels[14].contacts[0].value_coordinate[1]=S640K1_value_disp[1][1];
  
  S640K1_levels[14].contacts[1].flag_last=1;
  S640K1_levels[14].contacts[1].channel=7;
  S640K1_levels[14].contacts[1].div=0.667;
  S640K1_levels[14].contacts[1].point_coordinate[0]=S640K1_POINTS[42][0];
  S640K1_levels[14].contacts[1].point_coordinate[1]=S640K1_POINTS[42][1];
  S640K1_levels[14].contacts[1].value_coordinate[0]=S640K1_value_disp[2][0];
  S640K1_levels[14].contacts[1].value_coordinate[1]=S640K1_value_disp[2][1];
  
  
  /*****************************************************************************************************/
  
  
  
  
  
  
  S640K1_levels[15].contacts[0].flag_last=0;
  S640K1_levels[15].contacts[0].channel=7;
  S640K1_levels[15].contacts[0].div=0.6667;
  S640K1_levels[15].contacts[0].point_coordinate[0]=S640K1_POINTS[0][0];
  S640K1_levels[15].contacts[0].point_coordinate[1]=S640K1_POINTS[0][1];
  S640K1_levels[15].contacts[0].value_coordinate[0]=S640K1_value_disp[4][0];
  S640K1_levels[15].contacts[0].value_coordinate[1]=S640K1_value_disp[4][1];
  
  S640K1_levels[15].contacts[1].flag_last=0;
  S640K1_levels[15].contacts[1].channel=5;
  S640K1_levels[15].contacts[1].div=1;
  S640K1_levels[15].contacts[1].point_coordinate[0]=S640K1_POINTS[1][0];
  S640K1_levels[15].contacts[1].point_coordinate[1]=S640K1_POINTS[1][1];
  S640K1_levels[15].contacts[1].value_coordinate[0]=S640K1_value_disp[6][0];
  S640K1_levels[15].contacts[1].value_coordinate[1]=S640K1_value_disp[6][1];
  
  S640K1_levels[15].contacts[2].flag_last=0;
  S640K1_levels[15].contacts[2].channel=4;
  S640K1_levels[15].contacts[2].div=1;
  S640K1_levels[15].contacts[2].point_coordinate[0]=S640K1_POINTS[2][0];
  S640K1_levels[15].contacts[2].point_coordinate[1]=S640K1_POINTS[2][1];
  S640K1_levels[15].contacts[2].value_coordinate[0]=S640K1_value_disp[7][0];
  S640K1_levels[15].contacts[2].value_coordinate[1]=S640K1_value_disp[7][1];
  
  S640K1_levels[15].contacts[3].flag_last=1;
  S640K1_levels[15].contacts[3].channel=1;
  S640K1_levels[15].contacts[3].div=1;
  S640K1_levels[15].contacts[3].point_coordinate[0]=S640K1_POINTS[3][0];
  S640K1_levels[15].contacts[3].point_coordinate[1]=S640K1_POINTS[3][1];
  S640K1_levels[15].contacts[3].value_coordinate[0]=S640K1_value_disp[10][0];
  S640K1_levels[15].contacts[3].value_coordinate[1]=S640K1_value_disp[10][1];
  
  S640K1_levels[16].contacts[0].flag_last=0;
  S640K1_levels[16].contacts[0].channel=7;
  S640K1_levels[16].contacts[0].div=0.6667;
  S640K1_levels[16].contacts[0].point_coordinate[0]=S640K1_POINTS[4][0];
  S640K1_levels[16].contacts[0].point_coordinate[1]=S640K1_POINTS[4][1];
  S640K1_levels[16].contacts[0].value_coordinate[0]=S640K1_value_disp[4][0];
  S640K1_levels[16].contacts[0].value_coordinate[1]=S640K1_value_disp[4][1];
  
  S640K1_levels[16].contacts[1].flag_last=0;
  S640K1_levels[16].contacts[1].channel=6;
  S640K1_levels[16].contacts[1].div=1;
  S640K1_levels[16].contacts[1].point_coordinate[0]=S640K1_POINTS[5][0];
  S640K1_levels[16].contacts[1].point_coordinate[1]=S640K1_POINTS[5][1];
  S640K1_levels[16].contacts[1].value_coordinate[0]=S640K1_value_disp[5][0];
  S640K1_levels[16].contacts[1].value_coordinate[1]=S640K1_value_disp[5][1];
  
  S640K1_levels[16].contacts[2].flag_last=0;
  S640K1_levels[16].contacts[2].channel=4;
  S640K1_levels[16].contacts[2].div=1;
  S640K1_levels[16].contacts[2].point_coordinate[0]=S640K1_POINTS[6][0];
  S640K1_levels[16].contacts[2].point_coordinate[1]=S640K1_POINTS[6][1];
  S640K1_levels[16].contacts[2].value_coordinate[0]=S640K1_value_disp[7][0];
  S640K1_levels[16].contacts[2].value_coordinate[1]=S640K1_value_disp[7][1];
  
  S640K1_levels[16].contacts[3].flag_last=1;
  S640K1_levels[16].contacts[3].channel=2;
  S640K1_levels[16].contacts[3].div=1;
  S640K1_levels[16].contacts[3].point_coordinate[0]=S640K1_POINTS[7][0];
  S640K1_levels[16].contacts[3].point_coordinate[1]=S640K1_POINTS[7][1];
  S640K1_levels[16].contacts[3].value_coordinate[0]=S640K1_value_disp[9][0];
  S640K1_levels[16].contacts[3].value_coordinate[1]=S640K1_value_disp[9][1];
  
  
  S640K1_levels[17].contacts[0].flag_last=0;
  S640K1_levels[17].contacts[0].channel=7;
  S640K1_levels[17].contacts[0].div=0.6667;
  S640K1_levels[17].contacts[0].point_coordinate[0]=S640K1_POINTS[8][0];
  S640K1_levels[17].contacts[0].point_coordinate[1]=S640K1_POINTS[8][1];
  S640K1_levels[17].contacts[0].value_coordinate[0]=S640K1_value_disp[4][0];
  S640K1_levels[17].contacts[0].value_coordinate[1]=S640K1_value_disp[4][1];
  
  S640K1_levels[17].contacts[1].flag_last=0;
  S640K1_levels[17].contacts[1].channel=5;
  S640K1_levels[17].contacts[1].div=1;
  S640K1_levels[17].contacts[1].point_coordinate[0]=S640K1_POINTS[9][0];
  S640K1_levels[17].contacts[1].point_coordinate[1]=S640K1_POINTS[9][1];
  S640K1_levels[17].contacts[1].value_coordinate[0]=S640K1_value_disp[6][0];
  S640K1_levels[17].contacts[1].value_coordinate[1]=S640K1_value_disp[6][1];
  
  S640K1_levels[17].contacts[2].flag_last=0;
  S640K1_levels[17].contacts[2].channel=3;
  S640K1_levels[17].contacts[2].div=1;
  S640K1_levels[17].contacts[2].point_coordinate[0]=S640K1_POINTS[10][0];
  S640K1_levels[17].contacts[2].point_coordinate[1]=S640K1_POINTS[10][1];
  S640K1_levels[17].contacts[2].value_coordinate[0]=S640K1_value_disp[8][0];
  S640K1_levels[17].contacts[2].value_coordinate[1]=S640K1_value_disp[8][1];
  
  S640K1_levels[17].contacts[3].flag_last=1;
  S640K1_levels[17].contacts[3].channel=2;
  S640K1_levels[17].contacts[3].div=1;
  S640K1_levels[17].contacts[3].point_coordinate[0]=S640K1_POINTS[11][0];
  S640K1_levels[17].contacts[3].point_coordinate[1]=S640K1_POINTS[11][1];
  S640K1_levels[17].contacts[3].value_coordinate[0]=S640K1_value_disp[9][0];
  S640K1_levels[17].contacts[3].value_coordinate[1]=S640K1_value_disp[9][1];
  
  
  memcpy(S640K1_levels[0].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[0].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[1].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[1].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[2].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[2].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[3].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[3].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[4].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[4].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[5].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[5].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[6].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[6].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[7].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[8].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[8].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[8].contacts[2].R,untest,5);
  
  memcpy(S640K1_levels[9].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[9].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[9].contacts[2].R,untest,5);
  
  memcpy(S640K1_levels[10].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[10].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[11].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[11].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[12].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[12].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[13].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[13].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[14].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[14].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[15].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[15].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[15].contacts[2].R,untest,5);
  
  memcpy(S640K1_levels[15].contacts[3].R,untest,5);
  
  memcpy(S640K1_levels[16].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[16].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[16].contacts[2].R,untest,5);
  
  memcpy(S640K1_levels[16].contacts[3].R,untest,5);
  
  memcpy(S640K1_levels[17].contacts[0].R,untest,5);
  
  memcpy(S640K1_levels[17].contacts[1].R,untest,5);
  
  memcpy(S640K1_levels[17].contacts[2].R,untest,5);
  
  memcpy(S640K1_levels[17].contacts[3].R,untest,5);
  
  memcpy(S640K1_levels[0].level_V,untest,5);
  
  memcpy(S640K1_levels[1].level_V,untest,5);
  
  memcpy(S640K1_levels[2].level_V,untest,5);
  
  memcpy(S640K1_levels[3].level_V,untest,5);
  
  memcpy(S640K1_levels[4].level_V,untest,5);
  
  memcpy(S640K1_levels[5].level_V,untest,5);
  
  memcpy(S640K1_levels[6].level_V,untest,5);
  
  memcpy(S640K1_levels[7].level_V,untest,5);
  
  memcpy(S640K1_levels[8].level_V,untest,5);
  
  memcpy(S640K1_levels[9].level_V,untest,5);
  
  memcpy(S640K1_levels[10].level_V,untest,5);
  
  memcpy(S640K1_levels[11].level_V,untest,5);
  
  memcpy(S640K1_levels[12].level_V,untest,5);
  
  memcpy(S640K1_levels[13].level_V,untest,5);
  
  memcpy(S640K1_levels[14].level_V,untest,5);
  
  memcpy(S640K1_levels[15].level_V,untest,5);
  
  memcpy(S640K1_levels[16].level_V,untest,5);
  
  memcpy(S640K1_levels[17].level_V,untest,5);
  lamp=untest;
  V_jiwei=untest;
  bhlj=untest;//闭合逻辑
  
}

void ss7e_save_data(void)
{
  int fd;
  struct tm *time_now;
  time_t t;
  t=time(NULL);
  time_now =localtime(&t);
  strftime(file_name,sizeof(file_name),"SS7E_%Y_%m_%d_%H_%M_%S.csv",time_now);  
  char name_buffer[36];
  rt_sprintf(name_buffer,"/SS7E/%s",file_name);
  fd=open(name_buffer,O_RDWR|O_CREAT,0);
  
  write(fd,",,",2);
  write(fd,file_name,28);
  write(fd,",\r\n",3);
  write(fd,"制动级位,1,3,6,9,12,15,17,0,\r\n",30);
  
  write(fd,"422(415),,,,,,,,,,",16);
  write(fd,S640K1_levels[7].contacts[0].R,5);
  write(fd,",414(416),\r\n",12);
  
  write(fd,"402(403),",9);
  write(fd,S640K1_levels[0].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[1].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[2].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[3].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[4].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[5].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[6].contacts[0].R,5);
  write(fd,",,412(412),\r\n",13);
  
  write(fd,"402(403),",9);
  write(fd,S640K1_levels[0].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[1].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[2].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[3].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[4].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[5].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[6].contacts[1].R,5);
  write(fd,",,412(412),\r\n",13);
  
  write(fd,"级位电压,",9);
  write(fd,S640K1_levels[0].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[1].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[2].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[3].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[4].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[5].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[6].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[7].level_V,5);
  write(fd,",\r\n",3);
  
  write(fd,"牵引级位,*,3,6,9,12,15,17,0,\r\n",30);
  
  
  
  write(fd,"422(415),,,,,,,,,,",16);
  write(fd,S640K1_levels[7].contacts[0].R,5);
  write(fd,",414(416),\r\n",12);
  
  write(fd,"402(403),",9);
  write(fd,S640K1_levels[8].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[9].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[10].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[11].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[12].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[13].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[14].contacts[0].R,5);
  write(fd,",,412(412),\r\n",13);
  
  write(fd,"402(403),",9);
  write(fd,S640K1_levels[8].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[9].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[10].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[11].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[12].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[13].contacts[1].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[14].contacts[1].R,5);
  
  write(fd,",,412(412),\r\n",13);
  write(fd,"402(403),",9);
  write(fd,S640K1_levels[8].contacts[2].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[9].contacts[2].R,5);
  write(fd,",,,,,,,413(413),\r\n",18);
  
  write(fd,"级位电压,",9);
  write(fd,S640K1_levels[8].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[9].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[10].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[11].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[12].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[13].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[14].level_V,5);
  write(fd,",",1);
  write(fd,S640K1_levels[7].level_V,5);
  write(fd,",\r\n",3);
  
  
  write(fd,"换向级位,后,零,前,制,\r\n",23);
  write(fd,"402(403),",9);
  write(fd,S640K1_levels[15].contacts[0].R,5);
  write(fd,",,",2);
  write(fd,S640K1_levels[16].contacts[0].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[17].contacts[0].R,5);
  write(fd,",",1);
  write(fd,"401(401),接触电阻单位,,mΩ,\r\n",29);
  
  write(fd,"404(405),,,",11);
  write(fd,S640K1_levels[16].contacts[1].R,5);
  write(fd,",,401(401),联锁逻辑,,",21);
  write(fd,bhlj,5);
  write(fd,",\r\n",3);
  
  write(fd,"405(404),",9);
  write(fd,S640K1_levels[15].contacts[1].R,5);
  write(fd,",,,",3);
  write(fd,S640K1_levels[17].contacts[1].R,5);
  write(fd,",401(401),电位器总电阻值,,",26);
  write(fd,R_value,6);
  write(fd,",\r\n",3);
  
  write(fd,"407(407),",9);
  write(fd,S640K1_levels[15].contacts[2].R,5);
  write(fd,",,",2);
  write(fd,S640K1_levels[16].contacts[2].R,5);
  write(fd,",,401(401),级位电压,,",21);
  write(fd,V_jiwei,5);
  write(fd,",\r\n",3);
  
  
  write(fd,"406(406),,,,",12);
  write(fd,S640K1_levels[17].contacts[2].R,5);
  write(fd,",401(401),夜光灯,,",18);
  write(fd,lamp,5);
  write(fd,",\r\n",3);
  
  
  
  write(fd,"409(410),,,",11);
  write(fd,S640K1_levels[16].contacts[3].R,5);
  write(fd,",",1);
  write(fd,S640K1_levels[16].contacts[3].R,5);
  write(fd,",401(401),接触电阻参考值,,",26);
  write(fd,ref_buffer,5);
  write(fd,",\r\n",3);
  
  
  
  write(fd,"410(409),",9);
  write(fd,S640K1_levels[15].contacts[3].R,5);
  write(fd,",,,,401(401),",13);
  
  
  close(fd);
  //closedir(dir);
}

void S640K1_measure_levels(unsigned char n)
{
  unsigned char i=0;
  rt_int16_t  *p,temp=2000;
  if((n==17)||(n==18))
  {
    n-=1;
  }
  while(1)
  {
    
    Set_Scan_Channel(S640K1_levels[n].contacts[i].channel);
    rt_thread_delay(5);
    
    
    
    p=Get_ADC_R_Value();
    if((*p)>1250)
    {
      temp=*p;
      S640K1_levels[n].contacts[i].R[0]=' ';
      S640K1_levels[n].contacts[i].R[1]='_';
      S640K1_levels[n].contacts[i].R[2]='/';
      S640K1_levels[n].contacts[i].R[3]='_';
    }
    else if((*p)<=1250)
    {
      temp=(u16)((*p)*(S640K1_levels[n].contacts[i].div));
      S640K1_levels[n].contacts[i].R[0]=temp/1000+'0';
      S640K1_levels[n].contacts[i].R[1]=(temp%1000)/100+'0';
      S640K1_levels[n].contacts[i].R[2]=(temp%100)/10+'0';
      S640K1_levels[n].contacts[i].R[3]=temp%10+'0';
    }
    S640K1_levels[n].contacts[i].R[4]='\0';
    
    if(temp<R_ref)
    {
      LCD_DrawFullCircle(S640K1_levels[n].contacts[i].point_coordinate[0],S640K1_levels[n].contacts[i].point_coordinate[1],5,Green,0x01);
    }
    else
    {
      LCD_DrawFullCircle(S640K1_levels[n].contacts[i].point_coordinate[0],S640K1_levels[n].contacts[i].point_coordinate[1],5,Red,0x01);
    }
    LCD_str(S640K1_levels[n].contacts[i].value_coordinate[0], S640K1_levels[n].contacts[i].value_coordinate[1],S640K1_levels[n].contacts[i].R,32,Blue2, Black);
    
    if(S640K1_levels[n].contacts[i].flag_last==1)
    {
      p=Get_ADC_V_Value();
      *p=6*(*p);
      S640K1_levels[n].level_V[0]=*p/10000+'0';
      if(S640K1_levels[n].level_V[0]=='0')
      {
        S640K1_levels[n].level_V[0]=' ';
      }
      S640K1_levels[n].level_V[1]=(*p%10000)/1000+'0';
      S640K1_levels[n].level_V[2]='.';
      S640K1_levels[n].level_V[3]=(*p%1000)/100+'0';
      S640K1_levels[n].level_V[4]=(*p%100)/10+'0';
      S640K1_levels[n].level_V[5]=*p%10+'0';
      S640K1_levels[n].level_V[6]='V';
      S640K1_levels[n].level_V[7]='\0';
      
      
      LCD_str(671,304,S640K1_levels[n].level_V,32,Blue,Black);
      
      break;
    }
    i++;
  }
}





void sk640k1_scan(void)
{
  rt_int16_t  *p;
  u8 m,n,k;
  
  for(n=0; n<7; n++)
  {
    Set_Scan_Channel((7-n));
    rt_thread_delay(5);
    
    
    
    p=Get_ADC_R_Value();
    //    rt_kprintf("n=%d,r=%d\r\n",n,*p);
    if((*p)<=1250)
    {
      sk640_jiwei_flag=sk640_jiwei_flag|1<<n;
    }
    else
    {
      sk640_jiwei_flag=sk640_jiwei_flag&~(1<<n);
    }
  }
  Set_Scan_Channel(0);//是否在零位
  rt_thread_delay(5);
  
  
  
  p=Get_ADC_R_Value();
  if((*p)<=1250)//是
  {
    switch(sk640_jiwei_flag)
    {
    case 0x00://级位为0
      {
        S640K1_measure_levels(7);
        LCD_DrawFullRect( S640K1_TP[7][0],   S640K1_TP[7][1],   S640K1_TP[7][2],   S640K1_TP[7][3],  Red, 0);
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        LCD_DrawFullRect( S640K1_TP[16][0],   S640K1_TP[16][1],   S640K1_TP[16][2],   S640K1_TP[16][3],  Red, 0);
        break;
      }
    case 0x4C://后
      {
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        S640K1_measure_levels(15);
        LCD_DrawFullRect( S640K1_TP[15][0],   S640K1_TP[15][1],   S640K1_TP[15][2],   S640K1_TP[15][3],  Red, 0);
        S640K1_measure_levels(7);
        LCD_DrawFullRect( S640K1_TP[7][0],   S640K1_TP[7][1],   S640K1_TP[7][2],   S640K1_TP[7][3],  Red, 0);
        break;
      }
    case 0x2A://前
      {
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        };
        S640K1_measure_levels(17);
        LCD_DrawFullRect( S640K1_TP[17][0],   S640K1_TP[17][1],   S640K1_TP[17][2],   S640K1_TP[17][3],  Red, 0);
        S640K1_measure_levels(7);
        LCD_DrawFullRect( S640K1_TP[7][0],   S640K1_TP[7][1],   S640K1_TP[7][2],   S640K1_TP[7][3],  Red, 0);
        break;
      }
    case 0x34://制
      {
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        S640K1_measure_levels(18);
        LCD_DrawFullRect( S640K1_TP[18][0],   S640K1_TP[18][1],   S640K1_TP[18][2],   S640K1_TP[18][3],  Red, 0);
        S640K1_measure_levels(7);
        LCD_DrawFullRect( S640K1_TP[7][0],   S640K1_TP[7][1],   S640K1_TP[7][2],   S640K1_TP[7][3],  Red, 0);
        break;
      }
    default:
      {
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        //LCD_str(400,432,"级位错误",32,Red,Black);
        LCD_str(257,287,"级位错误",32,Red,Black);
        S640K1_measure_levels(15);
        S640K1_measure_levels(17);
        S640K1_measure_levels(18);
        break;
      }
    }
  }
  else//不是在0位
  {
    switch(sk640_jiwei_flag)
    {
    case 0x00://级位为0
      {
        LCD_str(257,287,"无司控器",32,Red,Black);
        break;
      }
    case 0x4D://后
      {
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        S640K1_measure_levels(15);
        LCD_DrawFullRect( S640K1_TP[15][0],   S640K1_TP[15][1],   S640K1_TP[15][2],   S640K1_TP[15][3],  Red, 0);
        
        rt_thread_delay(5);
        
        
        
        p=Get_ADC_V_Value();
        *p=6*(*p);
        for(n=0; n<18; n++)
        {
          if(((*p)>= sk640_jiwei_v[n])&&((*p)< sk640_jiwei_v[n+1]))
          {
            for(m=0; m<7; m++)
            {
              if(n==sk640_jiwei_q[m])
              {
                S640K1_measure_levels((8+m));
                for(k=7; k<15; k++)
                {
                  LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
                }
                LCD_DrawFullRect( S640K1_TP[8+m][0],   S640K1_TP[8+m][1],   S640K1_TP[8+m][2],   S640K1_TP[8+m][3],  Red, 0);
                break;
              }
            }
            break;
          }
        }
        
        break;
      }
    case 0x2B://前
      {
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        S640K1_measure_levels(17);
        LCD_DrawFullRect( S640K1_TP[17][0],   S640K1_TP[17][1],   S640K1_TP[17][2],   S640K1_TP[17][3],  Red, 0);
        rt_thread_delay(5);
        
        
        
        p=Get_ADC_V_Value();
        *p=6*(*p);
        for(n=0; n<18; n++)
        {
          if(((*p)>= sk640_jiwei_v[n])&&((*p)< sk640_jiwei_v[n+1]))
          {
            for(m=0; m<7; m++)
            {
              if(n==sk640_jiwei_q[m])
              {
                S640K1_measure_levels((8+m));
                for(k=7; k<15; k++)
                {
                  LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
                }
                LCD_DrawFullRect( S640K1_TP[8+m][0],   S640K1_TP[8+m][1],   S640K1_TP[8+m][2],   S640K1_TP[8+m][3],  Red, 0);
                break;
              }
            }
            break;
          }
        }
        
        break;
      }
    case 0x35://制
      {
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        S640K1_measure_levels(18);
        LCD_DrawFullRect( S640K1_TP[18][0],   S640K1_TP[18][1],   S640K1_TP[18][2],   S640K1_TP[18][3],  Red, 0);
        rt_thread_delay(5);
        
        
        
        p=Get_ADC_V_Value();
        *p=6*(*p);
        for(n=0; n<18; n++)
        {
          if(((*p)>= sk640_jiwei_v[n])&&((*p)< sk640_jiwei_v[n+1]))
          {
            
            for(m=0; m<7; m++)
            {
              if(n==sk640_jiwei_z[m])
              {
                
                S640K1_measure_levels(m);
                for(k=0; k<7; k++)
                {
                  LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
                }
                LCD_DrawFullRect( S640K1_TP[m][0],   S640K1_TP[m][1],   S640K1_TP[m][2],   S640K1_TP[m][3],  Red, 0);
                break;
              }
            }
            break;
          }
        }
        break;
      }
    default:
      {
        for(k=0; k<21; k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        LCD_str(257,287,"级位错误",32,Red,Black);
        S640K1_measure_levels(15);
        S640K1_measure_levels(17);
        S640K1_measure_levels(18);
        break;
      }
    }
  }
}

rt_int16_t  sk640k1_scan_level(void)
{
  rt_int16_t  *p;
  rt_int8_t n;
  
  for(n=0; n<7; n++)
  {
    Set_Scan_Channel((7-n));
    rt_thread_delay(5);
    p=Get_ADC_R_Value();
    if((*p)<=1250)
    {
      sk640_jiwei_flag=sk640_jiwei_flag|1<<n;
    }
    else
    {
      sk640_jiwei_flag=sk640_jiwei_flag&~(1<<n);
    }
  }
  Set_Scan_Channel(0);//是否在零位
  rt_thread_delay(5);
  p=Get_ADC_R_Value();
  if((*p)<=1250)//是
  {
    return (sk640_jiwei_flag+(1<<8));
#if 0    
    switch(sk640_jiwei_flag)
    {
    case 0x00://级位为0
      {           
        break;
      }
    case 0x4C://后
      {
        
        break;
      }
    case 0x2A://前
      {
        
        break;
      }
    case 0x34://制
      {
        
        break;
      }
    default:
      {
        
        break;
      }
    }
#endif
  }
  else//不是在0位
  {
    return sk640_jiwei_flag;
#if 0
    switch(sk640_jiwei_flag)
    {
    case 0x00://级位为0
      {
        LCD_str(257,287,"无司控器",32,Red,Black);
        break;
      }
    case 0x4D://后
      {
        
        break;
      }
    case 0x2B://前
      {
        
        break;
      }
    case 0x35://制
      {
        
      }
    default:
      {            
        LCD_DrawFullRect(257,287,384,479,  Black, 1);
        LCD_str(257,287,"级位错误",32,Red,Black);
        break;
      }
    }
#endif
  }
}

void S640K1_TP_respond(int x,int y)
{
  unsigned char n;
  rt_int16_t  m;
  for(n=0; n<26; n++)
  {
    if(x>S640K1_TP[n][0]&&x<S640K1_TP[n][2]&&y>S640K1_TP[n][1]&&y<S640K1_TP[n][3])
    {
      if(n==19)//模式切换
      {
        auto_scan_flag=~auto_scan_flag;
        if (auto_scan_flag)
        {
          rt_thread_resume(&skq_scan_thread);
          LCD_DrawFullRect(257,287,384,479,  Black, 1);
          LCD_str(0,16,"自动模式",32,Blue2,Black);
          return;
        }
        else
        {
          rt_mutex_take(scan_over_one_time, RT_WAITING_FOREVER);
          rt_thread_suspend(&skq_scan_thread);
          LCD_str(0,16,"手动模式",32,Blue2,Black);
          rt_mutex_release(scan_over_one_time);
          LCD_DrawFullRect(257,287,384,479,  Black, 1);
          LCD_str(257,287,"扳到大零位\n完成后按是",24,Red,Black);
          return;
        }
      }
      else if(n==20)//（退出）
      {
        PowerA_DIS();
        CD4067_DIS();
        rt_mutex_take(scan_over_one_time, RT_WAITING_FOREVER);
        sys_flag=main_panel;
        draw_main_panel();
        rt_mutex_release(scan_over_one_time);
        rt_thread_suspend(&skq_scan_thread);
        auto_scan_flag=0x00;
        uchar_check_step=0;
        return;
      }
      else if(n==25)//保存
      {
        rt_mutex_take(scan_over_one_time, RT_WAITING_FOREVER);
        ss7e_save_data();
        LCD_str(671,432,"保存完毕",32,Blue,Black);
        rt_mutex_release(scan_over_one_time);
      }
      
      else if(n==21)//上一步
      {
        if(uchar_check_step>0)
        {
          uchar_check_step-=1;
          switch(uchar_check_step)
          {
          case 0:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"扳到大零位\n完成后按是",24,Red,Black);
              break;
            }
          case 1:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"扳到制动位\n的小零位\n完成后按是",24,Red,Black);
              break;
            }
          case 2:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到17级\n完成后按是",24,Red,Black);
              break;
            }
          case 3:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
              break;
            }
          case 4:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"扳到向前位\n的小零位\n完成后按是",24,Red,Black);
              break;
            }
          case 5:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到*级\n完成后按是",24,Red,Black);
              break;
            }
          case 6:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
              break;
            }
          case 7:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"扳到向后位\n的小零位\n完成后按是",24,Red,Black);
              break;
            }
          case 8:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到*级\n完成后按是",24,Red,Black);
              break;
            }
          case 9:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
              break;
            }
          case 10:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"夜光照明灯\n是否正常？",24,Red,Black);
              set_24V();
              break;
            }
          case 11:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"正在测量\n划片电阻器\n的总电阻值",24,Red,Black);
              measure_R();
              LCD_str(257,360,R_value,24,Red,Black);
              break;
            }
          default:
            {
              break;
            }
          }
        }
      }
      else if(n==22)//下一步
      {
        if(uchar_check_step<sk640_steps)
        {
          uchar_check_step+=1;
          switch(uchar_check_step)
          {
          case 1:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"扳到制动位\n的小零位\n完成后按是",24,Red,Black);
              break;
            }
          case 2:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到17级\n完成后按是",24,Red,Black);
              break;
            }
          case 3:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
              break;
            }
          case 4:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"扳到向前位\n的小零位\n完成后按是",24,Red,Black);
              break;
            }
          case 5:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到*级\n完成后按是",24,Red,Black);
              break;
            }
          case 6:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
              break;
            }
          case 7:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"扳到向后位\n的小零位\n完成后按是",24,Red,Black);
              break;
            }
          case 8:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到*级\n完成后按是",24,Red,Black);
              break;
            }
          case 9:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
              break;
            }
          case 10:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"夜光照明灯\n是否正常？",24,Red,Black);
              set_24V();
              break;
            }
          case 11:
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              LCD_str(257,287,"正在测量\n划片电阻器\n的总电阻值",24,Red,Black);
              measure_R();
              LCD_str(257,360,R_value,24,Red,Black);
              break;
            }
          case 12://还要该为显示测试结果
            {
              LCD_DrawFullRect(257,287,384,479,  Black, 1);
              //判断级位电压是否正常
              if((S640K1_levels[6].level_V[0]==' ')&&(S640K1_levels[6].level_V[1]=='0')&&(S640K1_levels[6].level_V[3]<'2')&&
                 (S640K1_levels[8].level_V[0]==' ')&&(S640K1_levels[8].level_V[1]=='0')&&(S640K1_levels[8].level_V[3]<'2')&&
                   (S640K1_levels[0].level_V[0]=='1')&&(S640K1_levels[0].level_V[1]=='4')&&(S640K1_levels[0].level_V[3]>'3')&&
                     (S640K1_levels[14].level_V[0]=='1')&&(S640K1_levels[14].level_V[1]=='4')&&(S640K1_levels[14].level_V[3]>'3')
                       )
                  {
                    V_jiwei=zc;
                  }
                  else
                  {
                    V_jiwei=gz;
                  }
              
              
              LCD_str(257,287,"实验已结束\n请保存数据\n并退出实验",24,Red,Black);
              break;
            }
          default:
            {
              break;
            }
          }
        }
      }
      else if(n==23)//是
      {
        switch(uchar_check_step)
        {
        case 0://扳到大零位\n完成后按是
          {
            m=sk640k1_scan_level();
            if((m>>8))
            {
              switch((m&0x00ff))
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  S640K1_measure_levels(7);//测量0级位触点和大零位级位电压
                  bhlj=zc;//闭合逻辑正常,后续实验出现一个故障就算工作，不再出现这条语句
                  LCD_str(257,287,"此步骤完成\n请按下一步",24,Red,Black);
                  return;
                  break;
                }
              case 0x4C://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n扳到大零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2A://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n扳到大零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x34://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在制动级位\n扳到大零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            else
            {
              switch(m)
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"测试仪\n没有检测到\n司机控制器",24,Red,Black);
                  break;
                }
              case 0x4D://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n扳到大零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2B://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n扳到大零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x35://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在制动级位\n扳到大零位\n完成后按是",24,Red,Black);
                  return;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            return;
            break;
          }
        case 1://扳到制动位\n的小零位\n完成后按是
          {
            m=sk640k1_scan_level();
            if((m>>8))
            {
              switch((m&0x00ff))
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在大零级位\n扳到制动位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x4C://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n扳到制动位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2A://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n扳到制动位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x34://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"此步骤完成\n请按下一步",24,Red,Black);
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            else
            {
              switch(m)
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"测试仪\n没有检测到\n司机控制器",24,Red,Black);
                  break;
                }
              case 0x4D://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n扳到制动位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2B://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n扳到制动位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x35://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"扳到小零位\n完成后按是",24,Red,Black);
                  return;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            return;
            break;
          }
        case 2://将调速手柄扳到17级完成后按是
          {
            m=sk640k1_scan_level();
            if((m>>8))
            {
              switch((m&0x00ff))
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在大零级位\n调速手柄扳\n到制动17级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x4C://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n调速手柄扳\n到制动17级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2A://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n调速手柄扳\n到制动17级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x34://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);                  
                  LCD_str(257,287,"将调速手柄\n扳到17级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            else
            {
              switch(m)
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"测试仪\n没有检测到\n司机控制器",24,Red,Black);
                  break;
                }
              case 0x4D://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n调速手柄扳\n到制动17级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2B://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n调速手柄扳\n到制动17级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x35://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);//需要判断闭合逻辑互锁和与小零位的电压差
                  S640K1_measure_levels(6);//检测制动17级                  
                  LCD_str(257,287,"此步骤完成\n请按下一步",24,Red,Black);
                  return;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            return;
            break;
          }
        case 3://将调速手柄扳到其余各个级位后点击相应级位数字的边框
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"点击完成后\n请按下一步",24,Red,Black);
            break;
          }
        case 4://扳到向前位的小零位完成后按是
          {
            m=sk640k1_scan_level();
            if((m>>8))
            {
              switch((m&0x00ff))
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在大零级位\n扳到向前位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x4C://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n扳到向前位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2A://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);//此处判断一下逻辑正常    
                  LCD_str(257,287,"此步骤完成\n请按下一步",24,Red,Black);
                  return;
                  break;
                }
              case 0x34://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);              
                  LCD_str(257,287,"司机控制器\n在制动级位\n扳到向前位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            else
            {
              switch(m)
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"测试仪\n没有检测到\n司机控制器",24,Red,Black);
                  break;
                }
              case 0x4D://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n扳到向前位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2B://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n扳到向前位\n扳到小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x35://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在制动级位\n扳到向前位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            return;
            break;
          }
        case 5://将调速手柄扳到*级完成后按是
          {
            m=sk640k1_scan_level();
            if((m>>8))
            {
              switch((m&0x00ff))
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在大零级位\n调速手柄扳\n到向前*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x4C://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n调速手柄扳\n到向前*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2A://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"调速手柄扳\n到向前*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x34://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在制动级位\n调速手柄扳\n到向前*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            else
            {
              switch(m)
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"测试仪\n没有检测到\n司机控制器",24,Red,Black);
                  break;
                }
              case 0x4D://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n调速手柄扳\n到向前*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2B://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  S640K1_measure_levels(8);//检测向前*级
                  LCD_str(257,287,"此步骤完成\n请按下一步",24,Red,Black);
                  return;
                  break;
                }
              case 0x35://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);//需要判断闭合逻辑互锁和与小零位的电压差
                  LCD_str(257,287,"司机控制器\n在向后级位\n调速手柄扳\n到向前*级\n完成后按是",24,Red,Black);                  
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            return;
            break;
          }
        case 6://将调速手柄扳到其余各个级位后点击相应级位数字的边框
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"点击完成后\n请按下一步",24,Red,Black);
            break;
          }
        case 7://扳到向后位的小零位完成后按是
          {
            m=sk640k1_scan_level();
            if((m>>8))
            {
              switch((m&0x00ff))
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在大零级位\n扳到向后位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x4C://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);//此处判断一下逻辑正常
                  LCD_str(257,287,"此步骤完成\n请按下一步",24,Red,Black);
                  return;
                  break;
                }
              case 0x2A://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n扳到向后位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x34://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n扳到向后位\n的小零位\n完成后按是",24,Red,Black);
                  
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            else
            {
              switch(m)
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"测试仪\n没有检测到\n司机控制器",24,Red,Black);
                  break;
                }
              case 0x4D://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"扳到小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2B://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n扳到向后位\n的小零位\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x35://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n扳到向后位\n的小零位\n完成后按是",24,Red,Black);                  
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            break;
          }
        case 8://将调速手柄扳到*级完成后按是
          {
            m=sk640k1_scan_level();
            if((m>>8))
            {
              switch((m&0x00ff))
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在大零级位\n调速手柄扳\n到向后*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x4C://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"调速手柄扳\n到向后*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x2A://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n调速手柄扳\n到向后*级\n完成后按是",24,Red,Black);
                  
                  return;
                  break;
                }
              case 0x34://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在制动级位\n调速手柄扳\n到向后*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            else
            {
              switch(m)
              {
              case 0x00://级位为0
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"测试仪\n没有检测到\n司机控制器",24,Red,Black);
                  break;
                }
              case 0x4D://后
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);//需要判断闭合逻辑互锁和与小零位的电压差
                  S640K1_measure_levels(8);//检测向前*级
                  LCD_str(257,287,"此步骤完成\n请按下一步",24,Red,Black);
                  
                  return;
                  break;
                }
              case 0x2B://前
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向前级位\n调速手柄扳\n到向后*级\n完成后按是",24,Red,Black);
                  return;
                  break;
                }
              case 0x35://制
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"司机控制器\n在向后级位\n调速手柄扳\n到向后*级\n完成后按是",24,Red,Black);
                  
                  return;
                }
              default:
                {
                  LCD_DrawFullRect(257,287,384,479,  Black, 1);
                  LCD_str(257,287,"级位错误",32,Red,Black);
                  bhlj=gz;//闭合逻辑故障
                  S640K1_measure_levels(15);
                  S640K1_measure_levels(17);
                  S640K1_measure_levels(18);
                  return;
                  break;
                }
              }
            }
            return;
            break;
          }
        case 9://将调速手柄扳到其余各个级位后点击相应级位数字的边框
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"点击完成后\n请按下一步",24,Red,Black);
            break;
          }
        case 10://夜光照明灯是否正常？
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            lamp=zc;//照明记录为正常
            LCD_str(257,287,"夜光灯正常\n请按下一步",24,Red,Black);
            reset_24V();
            break;
          }
        case 11://划片电阻器的总电阻值
          {
            LCD_str(257,287,"测量完成\n请按下一步",24,Red,Black);
            break;
          }
        case 12://还要该为显示测试结果
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"实验已结束\n请保存数据\n并退出实验",24,Red,Black);
            return;
            break;
          }
        default:
          {
            break;
          }
        }
      }
      else if(n==24)//否
      {
        switch(uchar_check_step)
        {
        case 0:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n扳到大零位\n完成后按是",24,Red,Black);
            break;
          }
        case 1:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n扳到制动位\n的小零位\n完成后按是",24,Red,Black);
            break;
          }
        case 2:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n将调速手柄\n扳到17级\n完成后按是",24,Red,Black);
            break;
          }
        case 3:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
            break;
          }
        case 4:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n扳到向前位\n的小零位\n完成后按是",24,Red,Black);
            break;
          }
        case 5:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n将调速手柄\n扳到*级\n完成后按是",24,Red,Black);
            break;
          }
        case 6:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
            break;
          }
        case 7:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n扳到向后位\n的小零位\n完成后按是",24,Red,Black);
            break;
          }
        case 8:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n将调速手柄\n扳到*级\n完成后按是",24,Red,Black);
            break;
          }
        case 9:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n将调速手柄\n扳到其余各\n个级位后点\n击相应级位\n数字的边框",24,Red,Black);
            break;
          }
        case 10:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            lamp=gz;//照明记录为故障
            reset_24V();
            LCD_str(257,287,"请按下一步",24,Red,Black);
            break;
          }
        case 11:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"请按照提示\n操作",24,Red,Black);
            break;
          }
        case 12:
          {
            LCD_DrawFullRect(257,287,384,479,  Black, 1);
            LCD_str(257,287,"实验已结束\n请保存数据\n并退出实验",24,Red,Black);
            break;
          default:
            {
              break;
            }
          }
        }
      }
      else if(n==16)//大零位
      {
        ;
      }
      else
      {
        LCD_DrawFullRect( S640K1_TP[n][0],   S640K1_TP[n][1],   S640K1_TP[n][2],   S640K1_TP[n][3],  Black, 0);
        S640K1_measure_levels(n);
        LCD_DrawFullRect( S640K1_TP[n][0],   S640K1_TP[n][1],   S640K1_TP[n][2],   S640K1_TP[n][3],  Blue2, 0);
      }
    }
  }  
}  

#ifdef RT_USING_FINSH
#include <finsh.h>
/* 输出函数到finsh shell命令行中 */
FINSH_FUNCTION_EXPORT(ss7e_save_data,  save ss7e data in a csv file);
#endif






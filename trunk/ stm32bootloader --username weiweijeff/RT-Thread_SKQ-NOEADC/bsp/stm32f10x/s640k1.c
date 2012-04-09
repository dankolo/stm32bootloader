
#include <rtthread.h>
#include "tc_comm.h"
#include "gel.h"
#include "analog.h"
#include "s640k1.h"

struct level S640K1_levels[18];
u16 S640K1_TP[21][4]=
{
  {128,64,160,96},{160,64,192,96},{192,64,224,96},{224,64,256,96},{256,64,288,96},{288,64,320,96},{320,64,352,96},
  {352,64,384,96},
  {384,64,416,96},{416,64,448,96},{448,64,480,96},{480,64,512,96},{512,64,544,96},{544,64,576,96},{576,64,608,96},
  {128,224,160,256},{160,224,192,256},{192,224,224,256},{224,224,256,256},
  {670,336,799,400},{670,416,799,479}
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
u16 sk640_jiwei_v[19]={0,200,1085,1966,2847,3728,4609,5490,6371,7252,8133,9014,9895,10776,11657,12538,13419,14300,15000};
u8 sk640_jiwei_flag=0x7f;
u8 sk640_jiwei_q[7]={0,3,6,9,12,15,17};
u8 sk640_jiwei_z[7]={17,15,12,9,6,3,1};


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
  
//  LCD_str(256,64,"401(401)",32,Blue,Black);
//  LCD_str(256,96,"401(401)",32,Blue,Black);
//  LCD_str(256,128,"401(401)",32,Blue,Black);
  LCD_str(256,352,"401(401)",32,Blue,Black); 
//  LCD_str(256,192,"401(401)",32,Blue,Black);
//  LCD_str(256,224,"401(401)",32,Blue,Black);
//  LCD_str(256,256,"401(401)",32,Blue,Black); 
  
  u8 n=0;
  for(n=0;n<7;n++)
  {
    LCD_DrawUniLine( 128,  (272+32*n),  256,  (272+32*n),  Cyan);
  }
  for(n=0;n<4;n++)
  {
    LCD_DrawUniLine( (144+32*n),  256,  (144+32*n),  479,  Cyan);
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
  
  for(n=0;n<4;n++)
  {
    LCD_DrawUniLine( 128,  (112+32*n),  608,  (112+32*n),  Cyan);
  }
  for(n=0;n<15;n++)
  {
    LCD_DrawUniLine( (144+32*n),  96,  (144+32*n),  224,  Cyan);
  }
  LCD_DrawUniLine( 608, 144,  608,  176,  Green);
  LCD_DrawUniLine( 128, 144,  128,  272,  Green);
  
  for(n=0;n<43;n++)
  {
    LCD_DrawFullCircle( S640K1_POINTS[n][0],  S640K1_POINTS[n][1],  5,  Blue2,  1);
  }
  for(n=0;n<21;n++)
  {
    LCD_DrawFullRect( S640K1_TP[n][0],   S640K1_TP[n][1],   S640K1_TP[n][2],   S640K1_TP[n][3],  Blue2, 0);
  }
  //LCD_str(671,352,"保存结果",32,Blue2,Black);
  LCD_str(671,352,"自动模式",32,Blue2,Black);
  LCD_str(671,432,"退出实验",32,Red,Black);
  LCD_str(671,256,"级位电压",32,Blue,Black);
  
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

}



void S640K1_TP_respond(int x,int y)
{
  unsigned char n;
  for(n=0;n<21;n++)
  {
    if(x>S640K1_TP[n][0]&&x<S640K1_TP[n][2]&&y>S640K1_TP[n][1]&&y<S640K1_TP[n][3])
    {
      if(n==19)//模式切换
      {
        //sys_flag=main_panel;
        //return;
        auto_scan_flag=~auto_scan_flag;
        if(auto_scan_flag==0xff)
        {
          skq_scan_thread_create();
          LCD_str(671,352,"自动模式",32,Blue2,Black);
        }
        else if(auto_scan_flag==0x00)
        {
          rt_thread_delete(skq_scan_thread);
          LCD_str(671,352,"手动模式",32,Blue2,Black);
        }
        return;
      }
      else if(n==20)//（退出）
      {
        rt_thread_delete(skq_scan_thread);
        ADC_R_stop();
        ADC_V_stop();
        PowerA_DIS();
        CD4067_DIS();
        sys_flag=main_panel;
        draw_main_panel();
        return;
      }
      else if(n==16)
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
        ADC_R_Restart();
        ADC_R_DMA_Config();
        while(!DMA_GetFlagStatus(ADC_R_DMA_Flag));
        p=Get_ADC_R_Value();
        if((*p)>1000)
        {
          temp=*p;
          S640K1_levels[n].contacts[i].R[0]=' ';
          S640K1_levels[n].contacts[i].R[1]='_';
          S640K1_levels[n].contacts[i].R[2]='/';
          S640K1_levels[n].contacts[i].R[3]='_';
        }
        else if((*p)<=1000)
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
        ADC_V_Restart();
        ADC_V_DMA_Config();
        while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
        p=Get_ADC_V_Value();*p=6*(*p);
        
        S640K1_levels[n].level_V[0]=*p/10000+'0';
        if(S640K1_levels[n].level_V[0]=='0')
        {
          S640K1_levels[n].level_V[0]=' ';
        }
        S640K1_levels[n].level_V[1]=(*p%10000)/1000+'0';
        S640K1_levels[n].level_V[2]='.';
        S640K1_levels[n].level_V[3]=(*p%1000)/100+'0';
        S640K1_levels[n].level_V[4]=(*p%100)/10+'0';
        S640K1_levels[n].level_V[5]='V';
        S640K1_levels[n].level_V[6]='\0';
        
        
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
  
  for(n=0;n<7;n++)
  {
    Set_Scan_Channel((7-n));
    rt_thread_delay(5);
    ADC_R_Restart();
    ADC_R_DMA_Config();
    while(!DMA_GetFlagStatus(ADC_R_DMA_Flag));
    p=Get_ADC_R_Value();
//    rt_kprintf("n=%d,r=%d\r\n",n,*p);
    if((*p)<1000)
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
  ADC_R_Restart();
  ADC_R_DMA_Config();
  while(!DMA_GetFlagStatus(ADC_R_DMA_Flag));
  p=Get_ADC_R_Value();
  if((*p)<1000)//是
  {
    switch(sk640_jiwei_flag)
    {
    case 0x00://级位为0
      {
      S640K1_measure_levels(7);
      LCD_DrawFullRect( S640K1_TP[7][0],   S640K1_TP[7][1],   S640K1_TP[7][2],   S640K1_TP[7][3],  Red, 0);
      LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
      }
      LCD_DrawFullRect( S640K1_TP[16][0],   S640K1_TP[16][1],   S640K1_TP[16][2],   S640K1_TP[16][3],  Red, 0);
      break;
      }
    case 0x4C://后
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<21;k++)
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
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<21;k++)
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
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<21;k++)
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
        for(k=0;k<21;k++)
        {
          LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
        }
        LCD_str(521,352,"级位错误",32,Red,Black);
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
        LCD_str(521,352,"无司控器",32,Red,Black);
        break;
      }
    case 0x4D://后
      {
      LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
      }
      S640K1_measure_levels(15);
      LCD_DrawFullRect( S640K1_TP[15][0],   S640K1_TP[15][1],   S640K1_TP[15][2],   S640K1_TP[15][3],  Red, 0);

      rt_thread_delay(5);
      ADC_V_Restart();
      ADC_V_DMA_Config();
      while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
      p=Get_ADC_V_Value();*p=6*(*p);
      for(n=0;n<18;n++)
      {
        if(((*p)> sk640_jiwei_v[n])&&((*p)<= sk640_jiwei_v[n+1]))
        {
          for(m=0;m<7;m++)
          {
            if(n==sk640_jiwei_q[m])
            {
              S640K1_measure_levels((8+m));
              for(k=7;k<15;k++)
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
      LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
      }
      S640K1_measure_levels(17);
      LCD_DrawFullRect( S640K1_TP[17][0],   S640K1_TP[17][1],   S640K1_TP[17][2],   S640K1_TP[17][3],  Red, 0);
      rt_thread_delay(5);
      ADC_V_Restart();
      ADC_V_DMA_Config();
      while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
      p=Get_ADC_V_Value();*p=6*(*p);
      for(n=0;n<18;n++)
      {
        if(((*p)> sk640_jiwei_v[n])&&((*p)<= sk640_jiwei_v[n+1]))
        {
          for(m=0;m<7;m++)
          {
            if(n==sk640_jiwei_q[m])
            {
              S640K1_measure_levels((8+m));
              for(k=7;k<15;k++)
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
      LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
      }
      S640K1_measure_levels(18);
      LCD_DrawFullRect( S640K1_TP[18][0],   S640K1_TP[18][1],   S640K1_TP[18][2],   S640K1_TP[18][3],  Red, 0);
      rt_thread_delay(5);
      ADC_V_Restart();
      ADC_V_DMA_Config();
      while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
      p=Get_ADC_V_Value();*p=6*(*p);
      for(n=0;n<18;n++)
      {
        if(((*p)> sk640_jiwei_v[n])&&((*p)<= sk640_jiwei_v[n+1]))
        {

          for(m=0;m<7;m++)
          {
            if(n==sk640_jiwei_z[m])
            {
              
                S640K1_measure_levels(m);
                for(k=0;k<7;k++)
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
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( S640K1_TP[k][0],   S640K1_TP[k][1],   S640K1_TP[k][2],   S640K1_TP[k][3],  Blue2, 0);
      }
      LCD_str(521,352,"级位错误",32,Red,Black);
      S640K1_measure_levels(15);
      S640K1_measure_levels(17);
      S640K1_measure_levels(18);
      break;
      }
    }
  }
}










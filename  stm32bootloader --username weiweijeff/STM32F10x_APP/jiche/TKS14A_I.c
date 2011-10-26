#include "TKS14A_I.h"

struct level TKS14A_I_levels[29];//29个级位:调速+换向-零

unsigned int TKS14A_I_TP[29][4]=
{ {28,24,37,35},{37,24,46,35},{46,24,55,35},{55,24,64,35},
  {64,24,73,35},{73,24,82,35},{82,24,91,35},{91,24,100,35},
  {100,24,109,35},{109,24,118,35},{118,24,127,35},{127,24,136,35},
  {136,24,145,35},{145,24,154,35},{154,24,163,35},{163,24,172,35},
  {172,24,181,35},{181,24,190,35},{190,24,199,35},{199,24,208,35},
  {208,24,217,35},{217,24,226,35},{226,24,235,35},{29,119,41,132},
  {53,119,65,132},{65,119,77,132},{77,119,89,132},{89,119,101,132},{101,119,113,132},};

unsigned char Channel_TKS14A_I[12]={0,1,2,3,4,5,6,9,10,11,12,14};//扫描通道


//float levels_TKS14A_I[23]={};//级位电压
float allowance_TKS14A_I=0.04;//级位电压容差

void Set_Channel_TKS14A_I(unsigned char x)
{
  if((Channel_TKS14A_I[x]>>3)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_2);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_2);}
    if(((Channel_TKS14A_I[x]&0x04)>>2)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_3);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_3);}
    if(((Channel_TKS14A_I[x]&0x02)>>1)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_4);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_4);}
   if((Channel_TKS14A_I[x]&0x01)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_7);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_7);}
}



void draw_TKS14A_I()
{
  int n;
  unsigned char number[23]="0123456789Ao0123456789A";
  ili9320_Clear(Black);
  ili9320_PutCN12(102,0,"调速闭合表",Cyan,Black);
  ili9320_writestr12(200,0,"TKS14A-I",Cyan,Black);//第一行
  ili9320_PutCN12(78,12,"制动",Cyan,Black);
  ili9320_PutCN12(126,12,"零",Cyan,Black);
  ili9320_PutCN12(162,12,"牵引",Cyan,Black);
  ili9320_PutCN12(264,12,"阻值oo",Cyan,Black);//第二行
  for(n=0;n<23;n++)
  {
    ili9320_PutChar12(30+9*n,24,number[n],Cyan,Black);
  }
  for(n=0;n<23;n++)
  {
    GUI_Rectangle(28+9*n,24,37+9*n,35,Blue2,0);
  }

  ili9320_writestr12(12,36,"414",Cyan,Black);
  ili9320_writestr12(237,36,"413",Cyan,Black);//4
  ili9320_writestr12(12,48,"415",Cyan,Black);
  ili9320_writestr12(237,48,"402",Cyan,Black);//5
  ili9320_writestr12(12,60,"417",Cyan,Black);
  ili9320_writestr12(237,60,"577",Cyan,Black);//6
  ili9320_writestr12(12,72,"416",Cyan,Black);
  ili9320_writestr12(237,72,"577",Cyan,Black);//7
  ili9320_writestr12(12,84,"401",Cyan,Black);
  ili9320_writestr12(237,84,"410",Cyan,Black);//8
  ili9320_PutCN12(42,108,"换向闭合表",Cyan,Black);//9
  ili9320_PutCN12(30,120,"后零制前壹贰叁",Cyan,Black);
  for(n=0;n<7;n++)
  {
    GUI_Rectangle(29+12*n,119,41+12*n,132,Blue2,0);
  }
  ili9320_PutCN12(150,120,"阻值oo",Cyan,Black);//10
  ili9320_writestr12(12,132,"401",Cyan,Black);
  ili9320_writestr12(114,132,"402",Cyan,Black);//11
  ili9320_writestr12(12,144,"401",Cyan,Black);
  ili9320_writestr12(114,144,"404",Cyan,Black);//12
  ili9320_writestr12(12,156,"401",Cyan,Black);
  ili9320_writestr12(114,156,"403",Cyan,Black);//13
  ili9320_writestr12(12,168,"401",Cyan,Black);
  ili9320_writestr12(114,168,"405",Cyan,Black);//14
  ili9320_writestr12(12,180,"401",Cyan,Black);
  ili9320_writestr12(114,180,"406",Cyan,Black);//15
  ili9320_writestr12(12,192,"407",Cyan,Black);
  ili9320_writestr12(114,192,"410",Cyan,Black);//16
  ili9320_writestr12(12,204,"408",Cyan,Black);
  ili9320_writestr12(114,204,"410",Cyan,Black);//17
  for(n=0;n<5;n++)
  {
    GUI_Line(30,42+12*n,236,42+12*n,Blue2);
  }
  for(n=0;n<23;n++)
  {
    GUI_Line(33+9*n,36,33+9*n,96,Blue2);
  }
  for(n=0;n<7;n++)
  {
    GUI_Line(30,138+12*n,113,138+12*n,Blue2);
  }
  for(n=0;n<7;n++)
  {
    GUI_Line(36+12*n,132,36+12*n,216,Blue2);
  }

  unsigned char points[]=
  {
                                                              123,42,132,42,141,42,
33,54,42,54,51,54,60,54,69,54,78,54,87,54,96,54,105,54,114,54,123,54,       141,54,150,54,159,54,168,54,177,54,186,54,195,54,204,54,213,54,222,54,231,54,
33,66,42,66,51,66,60,66,69,66,78,66,87,66,96,66,105,66,114,66,123,66,                                   159,66,168,66,177,66,186,66,195,66,204,66,213,66,222,66,231,66,
                                                105,78,114,78,123,78,       141,78,150,78,159,78,
                                                                                                                                    213,90,222,90,231,90,


36,138,       60,138,72,138,84,138,96,138,108,138,
              60,150,72,150,84,150,96,150,108,150,
36,162,
              60,174,
36,186,              72,186,84,186,96,186,108,186,
                            84,198,       108,198,
                                   96,210,108,210,
0xff
  };
  n=0;
  while(points[n]!=0xff)
  {
    GUI_Circle(points[n],points[n+1],4,Blue,0x01);
    n+=2;
  }

}


void TKS14A_I_table()
{
//Z0
TKS14A_I_levels[0].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
TKS14A_I_levels[0].contacts[0].channel=1;
TKS14A_I_levels[0].contacts[0].point_coordinate[0]=33;               //圆心x坐标
TKS14A_I_levels[0].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[0].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[0].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[0].contacts[1].flag_last=1;
TKS14A_I_levels[0].contacts[1].channel=2;
TKS14A_I_levels[0].contacts[1].point_coordinate[0]=33;               //圆心x坐标
TKS14A_I_levels[0].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[0].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[0].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

//Z1
TKS14A_I_levels[1].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
TKS14A_I_levels[1].contacts[0].channel=1;
TKS14A_I_levels[1].contacts[0].point_coordinate[0]=42;               //圆心x坐标
TKS14A_I_levels[1].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[1].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[1].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[1].contacts[1].flag_last=1;
TKS14A_I_levels[1].contacts[1].channel=2;
TKS14A_I_levels[1].contacts[1].point_coordinate[0]=42;               //圆心x坐标
TKS14A_I_levels[1].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[1].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[1].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z2
TKS14A_I_levels[2].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
TKS14A_I_levels[2].contacts[0].channel=1;
TKS14A_I_levels[2].contacts[0].point_coordinate[0]=51;               //圆心x坐标
TKS14A_I_levels[2].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[2].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[2].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[2].contacts[1].flag_last=1;
TKS14A_I_levels[2].contacts[1].channel=2;
TKS14A_I_levels[2].contacts[1].point_coordinate[0]=51;               //圆心x坐标
TKS14A_I_levels[2].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[2].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[2].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z3
TKS14A_I_levels[3].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
TKS14A_I_levels[3].contacts[0].channel=1;
TKS14A_I_levels[3].contacts[0].point_coordinate[0]=60;               //圆心x坐标
TKS14A_I_levels[3].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[3].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[3].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[3].contacts[1].flag_last=1;
TKS14A_I_levels[3].contacts[1].channel=2;
TKS14A_I_levels[3].contacts[1].point_coordinate[0]=60;               //圆心x坐标
TKS14A_I_levels[3].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[3].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[3].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z4
TKS14A_I_levels[4].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
TKS14A_I_levels[4].contacts[0].channel=1;
TKS14A_I_levels[4].contacts[0].point_coordinate[0]=69;               //圆心x坐标
TKS14A_I_levels[4].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[4].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[4].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[4].contacts[1].flag_last=1;
TKS14A_I_levels[4].contacts[1].channel=2;
TKS14A_I_levels[4].contacts[1].point_coordinate[0]=69;               //圆心x坐标
TKS14A_I_levels[4].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[4].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[4].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

//Z5
TKS14A_I_levels[5].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
TKS14A_I_levels[5].contacts[0].channel=1;
TKS14A_I_levels[5].contacts[0].point_coordinate[0]=78;               //圆心x坐标
TKS14A_I_levels[5].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[5].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[5].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[5].contacts[1].flag_last=1;
TKS14A_I_levels[5].contacts[1].channel=2;
TKS14A_I_levels[5].contacts[1].point_coordinate[0]=78;               //圆心x坐标
TKS14A_I_levels[5].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[5].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[5].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z6
TKS14A_I_levels[6].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
TKS14A_I_levels[6].contacts[0].channel=1;
TKS14A_I_levels[6].contacts[0].point_coordinate[0]=87;               //圆心x坐标
TKS14A_I_levels[6].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[6].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[6].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[6].contacts[1].flag_last=1;
TKS14A_I_levels[6].contacts[1].channel=2;
TKS14A_I_levels[6].contacts[1].point_coordinate[0]=87;               //圆心x坐标
TKS14A_I_levels[6].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[6].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[6].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z7
TKS14A_I_levels[7].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
TKS14A_I_levels[7].contacts[0].channel=1;
TKS14A_I_levels[7].contacts[0].point_coordinate[0]=96;               //圆心x坐标
TKS14A_I_levels[7].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[7].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[7].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[7].contacts[1].flag_last=1;
TKS14A_I_levels[7].contacts[1].channel=2;
TKS14A_I_levels[7].contacts[1].point_coordinate[0]=96;               //圆心x坐标
TKS14A_I_levels[7].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[7].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[7].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//z8
TKS14A_I_levels[8].contacts[0].flag_last=0;
TKS14A_I_levels[8].contacts[0].channel=1;
TKS14A_I_levels[8].contacts[0].point_coordinate[0]=105;               //圆心x坐标
TKS14A_I_levels[8].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[8].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[8].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[8].contacts[1].flag_last=0;
TKS14A_I_levels[8].contacts[1].channel=2;
TKS14A_I_levels[8].contacts[1].point_coordinate[0]=105;               //圆心x坐标
TKS14A_I_levels[8].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[8].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[8].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

TKS14A_I_levels[8].contacts[2].flag_last=1;
TKS14A_I_levels[8].contacts[2].channel=3;
TKS14A_I_levels[8].contacts[2].point_coordinate[0]=105;               //圆心x坐标
TKS14A_I_levels[8].contacts[2].point_coordinate[1]=78;               //圆心y坐标
TKS14A_I_levels[8].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[8].contacts[2].value_coordinate[1]=72;               //显示起始y坐标
//z9
TKS14A_I_levels[9].contacts[0].flag_last=0;
TKS14A_I_levels[9].contacts[0].channel=1;
TKS14A_I_levels[9].contacts[0].point_coordinate[0]=114;               //圆心x坐标
TKS14A_I_levels[9].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[9].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[9].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[9].contacts[1].flag_last=0;
TKS14A_I_levels[9].contacts[1].channel=2;
TKS14A_I_levels[9].contacts[1].point_coordinate[0]=114;               //圆心x坐标
TKS14A_I_levels[9].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[9].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[9].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

TKS14A_I_levels[9].contacts[2].flag_last=1;
TKS14A_I_levels[9].contacts[2].channel=3;
TKS14A_I_levels[9].contacts[2].point_coordinate[0]=114;               //圆心x坐标
TKS14A_I_levels[9].contacts[2].point_coordinate[1]=78;               //圆心y坐标
TKS14A_I_levels[9].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[9].contacts[2].value_coordinate[1]=72;               //显示起始y坐标
//z10
TKS14A_I_levels[10].contacts[0].flag_last=0;
TKS14A_I_levels[10].contacts[0].channel=0;
TKS14A_I_levels[10].contacts[0].point_coordinate[0]=123;               //圆心x坐标
TKS14A_I_levels[10].contacts[0].point_coordinate[1]=42;               //圆心y坐标
TKS14A_I_levels[10].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[10].contacts[0].value_coordinate[1]=36;               //显示起始y坐标

TKS14A_I_levels[10].contacts[1].flag_last=0;
TKS14A_I_levels[10].contacts[1].channel=1;
TKS14A_I_levels[10].contacts[1].point_coordinate[0]=123;               //圆心x坐标
TKS14A_I_levels[10].contacts[1].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[10].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[10].contacts[1].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[10].contacts[2].flag_last=0;
TKS14A_I_levels[10].contacts[2].channel=2;
TKS14A_I_levels[10].contacts[2].point_coordinate[0]=123;               //圆心x坐标
TKS14A_I_levels[10].contacts[2].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[10].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[10].contacts[2].value_coordinate[1]=60;               //显示起始y坐标

TKS14A_I_levels[10].contacts[3].flag_last=1;
TKS14A_I_levels[10].contacts[3].channel=3;
TKS14A_I_levels[10].contacts[3].point_coordinate[0]=123;               //圆心x坐标
TKS14A_I_levels[10].contacts[3].point_coordinate[1]=78;               //圆心y坐标
TKS14A_I_levels[10].contacts[3].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[10].contacts[3].value_coordinate[1]=72;               //显示起始y坐标
//oo
TKS14A_I_levels[11].contacts[0].flag_last=1;
TKS14A_I_levels[11].contacts[0].channel=0;
TKS14A_I_levels[11].contacts[0].point_coordinate[0]=132;               //圆心x坐标
TKS14A_I_levels[11].contacts[0].point_coordinate[1]=42;               //圆心y坐标
TKS14A_I_levels[11].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[11].contacts[0].value_coordinate[1]=36;               //显示起始y坐标
//q0
TKS14A_I_levels[12].contacts[0].flag_last=0;
TKS14A_I_levels[12].contacts[0].channel=0;
TKS14A_I_levels[12].contacts[0].point_coordinate[0]=141;               //圆心x坐标
TKS14A_I_levels[12].contacts[0].point_coordinate[1]=42;               //圆心y坐标
TKS14A_I_levels[12].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[12].contacts[0].value_coordinate[1]=36;               //显示起始y坐标

TKS14A_I_levels[12].contacts[1].flag_last=0;
TKS14A_I_levels[12].contacts[1].channel=1;
TKS14A_I_levels[12].contacts[1].point_coordinate[0]=141;               //圆心x坐标
TKS14A_I_levels[12].contacts[1].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[12].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[12].contacts[1].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[12].contacts[2].flag_last=1;
TKS14A_I_levels[12].contacts[2].channel=3;
TKS14A_I_levels[12].contacts[2].point_coordinate[0]=141;               //圆心x坐标
TKS14A_I_levels[12].contacts[2].point_coordinate[1]=78;               //圆心y坐标
TKS14A_I_levels[12].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[12].contacts[2].value_coordinate[1]=72;               //显示起始y坐标
//q1
TKS14A_I_levels[13].contacts[0].flag_last=0;
TKS14A_I_levels[13].contacts[0].channel=1;
TKS14A_I_levels[13].contacts[0].point_coordinate[0]=150;               //圆心x坐标
TKS14A_I_levels[13].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[13].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[13].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[13].contacts[1].flag_last=1;
TKS14A_I_levels[13].contacts[1].channel=3;
TKS14A_I_levels[13].contacts[1].point_coordinate[0]=150;               //圆心x坐标
TKS14A_I_levels[13].contacts[1].point_coordinate[1]=78;               //圆心y坐标
TKS14A_I_levels[13].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[13].contacts[1].value_coordinate[1]=72;               //显示起始y坐标

//q2
TKS14A_I_levels[14].contacts[0].flag_last=0;
TKS14A_I_levels[14].contacts[0].channel=1;
TKS14A_I_levels[14].contacts[0].point_coordinate[0]=159;               //圆心x坐标
TKS14A_I_levels[14].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[14].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[14].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[14].contacts[1].flag_last=0;
TKS14A_I_levels[14].contacts[1].channel=2;
TKS14A_I_levels[14].contacts[1].point_coordinate[0]=159;               //圆心x坐标
TKS14A_I_levels[14].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[14].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[14].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

TKS14A_I_levels[14].contacts[2].flag_last=1;
TKS14A_I_levels[14].contacts[2].channel=3;
TKS14A_I_levels[14].contacts[2].point_coordinate[0]=159;               //圆心x坐标
TKS14A_I_levels[14].contacts[2].point_coordinate[1]=78;               //圆心y坐标
TKS14A_I_levels[14].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[14].contacts[2].value_coordinate[1]=72;               //显示起始y坐标
//q3
TKS14A_I_levels[15].contacts[0].flag_last=0;
TKS14A_I_levels[15].contacts[0].channel=1;
TKS14A_I_levels[15].contacts[0].point_coordinate[0]=168;               //圆心x坐标
TKS14A_I_levels[15].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[15].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[15].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[15].contacts[1].flag_last=1;
TKS14A_I_levels[15].contacts[1].channel=2;
TKS14A_I_levels[15].contacts[1].point_coordinate[0]=168;               //圆心x坐标
TKS14A_I_levels[15].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[15].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[15].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//q4
TKS14A_I_levels[16].contacts[0].flag_last=0;
TKS14A_I_levels[16].contacts[0].channel=1;
TKS14A_I_levels[16].contacts[0].point_coordinate[0]=177;               //圆心x坐标
TKS14A_I_levels[16].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[16].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[16].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[16].contacts[1].flag_last=1;
TKS14A_I_levels[16].contacts[1].channel=2;
TKS14A_I_levels[16].contacts[1].point_coordinate[0]=177;               //圆心x坐标
TKS14A_I_levels[16].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[16].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[16].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//q5
TKS14A_I_levels[17].contacts[0].flag_last=0;
TKS14A_I_levels[17].contacts[0].channel=1;
TKS14A_I_levels[17].contacts[0].point_coordinate[0]=186;               //圆心x坐标
TKS14A_I_levels[17].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[17].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[17].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[17].contacts[1].flag_last=1;
TKS14A_I_levels[17].contacts[1].channel=2;
TKS14A_I_levels[17].contacts[1].point_coordinate[0]=186;               //圆心x坐标
TKS14A_I_levels[17].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[17].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[17].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//q6
TKS14A_I_levels[18].contacts[0].flag_last=0;
TKS14A_I_levels[18].contacts[0].channel=1;
TKS14A_I_levels[18].contacts[0].point_coordinate[0]=195;               //圆心x坐标
TKS14A_I_levels[18].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[18].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[18].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[18].contacts[1].flag_last=1;
TKS14A_I_levels[18].contacts[1].channel=2;
TKS14A_I_levels[18].contacts[1].point_coordinate[0]=195;               //圆心x坐标
TKS14A_I_levels[18].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[18].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[18].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

//q7
TKS14A_I_levels[19].contacts[0].flag_last=0;
TKS14A_I_levels[19].contacts[0].channel=1;
TKS14A_I_levels[19].contacts[0].point_coordinate[0]=204;               //圆心x坐标
TKS14A_I_levels[19].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[19].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[19].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[19].contacts[1].flag_last=1;
TKS14A_I_levels[19].contacts[1].channel=2;
TKS14A_I_levels[19].contacts[1].point_coordinate[0]=204;               //圆心x坐标
TKS14A_I_levels[19].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[19].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[19].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//q8
TKS14A_I_levels[20].contacts[0].flag_last=0;
TKS14A_I_levels[20].contacts[0].channel=1;
TKS14A_I_levels[20].contacts[0].point_coordinate[0]=213;               //圆心x坐标
TKS14A_I_levels[20].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[20].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[20].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[20].contacts[1].flag_last=0;
TKS14A_I_levels[20].contacts[1].channel=2;
TKS14A_I_levels[20].contacts[1].point_coordinate[0]=213;               //圆心x坐标
TKS14A_I_levels[20].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[20].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[20].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

TKS14A_I_levels[20].contacts[2].flag_last=1;
TKS14A_I_levels[20].contacts[2].channel=4;
TKS14A_I_levels[20].contacts[2].point_coordinate[0]=213;               //圆心x坐标
TKS14A_I_levels[20].contacts[2].point_coordinate[1]=90;               //圆心y坐标
TKS14A_I_levels[20].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[20].contacts[2].value_coordinate[1]=84;               //显示起始y坐标
//q9
TKS14A_I_levels[21].contacts[0].flag_last=0;
TKS14A_I_levels[21].contacts[0].channel=1;
TKS14A_I_levels[21].contacts[0].point_coordinate[0]=222;               //圆心x坐标
TKS14A_I_levels[21].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[21].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[21].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[21].contacts[1].flag_last=0;
TKS14A_I_levels[21].contacts[1].channel=2;
TKS14A_I_levels[21].contacts[1].point_coordinate[0]=222;               //圆心x坐标
TKS14A_I_levels[21].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[21].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[21].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

TKS14A_I_levels[21].contacts[2].flag_last=1;
TKS14A_I_levels[21].contacts[2].channel=4;
TKS14A_I_levels[21].contacts[2].point_coordinate[0]=222;               //圆心x坐标
TKS14A_I_levels[21].contacts[2].point_coordinate[1]=90;               //圆心y坐标
TKS14A_I_levels[21].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[21].contacts[2].value_coordinate[1]=84;               //显示起始y坐标
//q10
TKS14A_I_levels[22].contacts[0].flag_last=0;
TKS14A_I_levels[22].contacts[0].channel=1;
TKS14A_I_levels[22].contacts[0].point_coordinate[0]=231;               //圆心x坐标
TKS14A_I_levels[22].contacts[0].point_coordinate[1]=54;               //圆心y坐标
TKS14A_I_levels[22].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[22].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

TKS14A_I_levels[22].contacts[1].flag_last=0;
TKS14A_I_levels[22].contacts[1].channel=2;
TKS14A_I_levels[22].contacts[1].point_coordinate[0]=231;               //圆心x坐标
TKS14A_I_levels[22].contacts[1].point_coordinate[1]=66;               //圆心y坐标
TKS14A_I_levels[22].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[22].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

TKS14A_I_levels[22].contacts[2].flag_last=1;
TKS14A_I_levels[22].contacts[2].channel=4;
TKS14A_I_levels[22].contacts[2].point_coordinate[0]=231;               //圆心x坐标
TKS14A_I_levels[22].contacts[2].point_coordinate[1]=90;               //圆心y坐标
TKS14A_I_levels[22].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
TKS14A_I_levels[22].contacts[2].value_coordinate[1]=84;               //显示起始y坐标
//后
TKS14A_I_levels[23].contacts[0].flag_last=0;
TKS14A_I_levels[23].contacts[0].channel=5;
TKS14A_I_levels[23].contacts[0].point_coordinate[0]=36;               //圆心x坐标
TKS14A_I_levels[23].contacts[0].point_coordinate[1]=138;               //圆心y坐标
TKS14A_I_levels[23].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[23].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

TKS14A_I_levels[23].contacts[1].flag_last=0;
TKS14A_I_levels[23].contacts[1].channel=7;
TKS14A_I_levels[23].contacts[1].point_coordinate[0]=36;               //圆心x坐标
TKS14A_I_levels[23].contacts[1].point_coordinate[1]=162;               //圆心y坐标
TKS14A_I_levels[23].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[23].contacts[1].value_coordinate[1]=156;               //显示起始y坐标

TKS14A_I_levels[23].contacts[2].flag_last=1;
TKS14A_I_levels[23].contacts[2].channel=9;
TKS14A_I_levels[23].contacts[2].point_coordinate[0]=36;               //圆心x坐标
TKS14A_I_levels[23].contacts[2].point_coordinate[1]=186;               //圆心y坐标
TKS14A_I_levels[23].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[23].contacts[2].value_coordinate[1]=180;               //显示起始y坐标
//零
//制
TKS14A_I_levels[24].contacts[0].flag_last=0;
TKS14A_I_levels[24].contacts[0].channel=5;
TKS14A_I_levels[24].contacts[0].point_coordinate[0]=60;               //圆心x坐标
TKS14A_I_levels[24].contacts[0].point_coordinate[1]=138;               //圆心y坐标
TKS14A_I_levels[24].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[24].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

TKS14A_I_levels[24].contacts[1].flag_last=0;
TKS14A_I_levels[24].contacts[1].channel=6;
TKS14A_I_levels[24].contacts[1].point_coordinate[0]=60;               //圆心x坐标
TKS14A_I_levels[24].contacts[1].point_coordinate[1]=150;               //圆心y坐标
TKS14A_I_levels[24].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[24].contacts[1].value_coordinate[1]=144;               //显示起始y坐标

TKS14A_I_levels[24].contacts[2].flag_last=1;
TKS14A_I_levels[24].contacts[2].channel=8;
TKS14A_I_levels[24].contacts[2].point_coordinate[0]=60;               //圆心x坐标
TKS14A_I_levels[24].contacts[2].point_coordinate[1]=174;               //圆心y坐标
TKS14A_I_levels[24].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[24].contacts[2].value_coordinate[1]=168;               //显示起始y坐标
//前
TKS14A_I_levels[25].contacts[0].flag_last=0;
TKS14A_I_levels[25].contacts[0].channel=5;
TKS14A_I_levels[25].contacts[0].point_coordinate[0]=72;               //圆心x坐标
TKS14A_I_levels[25].contacts[0].point_coordinate[1]=138;               //圆心y坐标
TKS14A_I_levels[25].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[25].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

TKS14A_I_levels[25].contacts[1].flag_last=0;
TKS14A_I_levels[25].contacts[1].channel=6;
TKS14A_I_levels[25].contacts[1].point_coordinate[0]=72;               //圆心x坐标
TKS14A_I_levels[25].contacts[1].point_coordinate[1]=150;               //圆心y坐标
TKS14A_I_levels[25].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[25].contacts[1].value_coordinate[1]=144;               //显示起始y坐标

TKS14A_I_levels[25].contacts[2].flag_last=1;
TKS14A_I_levels[25].contacts[2].channel=9;
TKS14A_I_levels[25].contacts[2].point_coordinate[0]=72;               //圆心x坐标
TKS14A_I_levels[25].contacts[2].point_coordinate[1]=186;               //圆心y坐标
TKS14A_I_levels[25].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[25].contacts[2].value_coordinate[1]=180;               //显示起始y坐标
//壹
TKS14A_I_levels[26].contacts[0].flag_last=0;
TKS14A_I_levels[26].contacts[0].channel=5;
TKS14A_I_levels[26].contacts[0].point_coordinate[0]=84;               //圆心x坐标
TKS14A_I_levels[26].contacts[0].point_coordinate[1]=138;               //圆心y坐标
TKS14A_I_levels[26].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[26].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

TKS14A_I_levels[26].contacts[1].flag_last=0;
TKS14A_I_levels[26].contacts[1].channel=6;
TKS14A_I_levels[26].contacts[1].point_coordinate[0]=84;               //圆心x坐标
TKS14A_I_levels[26].contacts[1].point_coordinate[1]=150;               //圆心y坐标
TKS14A_I_levels[26].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[26].contacts[1].value_coordinate[1]=144;               //显示起始y坐标

TKS14A_I_levels[26].contacts[2].flag_last=0;
TKS14A_I_levels[26].contacts[2].channel=9;
TKS14A_I_levels[26].contacts[2].point_coordinate[0]=84;               //圆心x坐标
TKS14A_I_levels[26].contacts[2].point_coordinate[1]=186;               //圆心y坐标
TKS14A_I_levels[26].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[26].contacts[2].value_coordinate[1]=180;               //显示起始y坐标

TKS14A_I_levels[26].contacts[3].flag_last=1;
TKS14A_I_levels[26].contacts[3].channel=10;
TKS14A_I_levels[26].contacts[3].point_coordinate[0]=84;               //圆心x坐标
TKS14A_I_levels[26].contacts[3].point_coordinate[1]=198;               //圆心y坐标
TKS14A_I_levels[26].contacts[3].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[26].contacts[3].value_coordinate[1]=192;               //显示起始y坐标
//贰
TKS14A_I_levels[27].contacts[0].flag_last=0;
TKS14A_I_levels[27].contacts[0].channel=5;
TKS14A_I_levels[27].contacts[0].point_coordinate[0]=96;               //圆心x坐标
TKS14A_I_levels[27].contacts[0].point_coordinate[1]=138;               //圆心y坐标
TKS14A_I_levels[27].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[27].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

TKS14A_I_levels[27].contacts[1].flag_last=0;
TKS14A_I_levels[27].contacts[1].channel=6;
TKS14A_I_levels[27].contacts[1].point_coordinate[0]=96;               //圆心x坐标
TKS14A_I_levels[27].contacts[1].point_coordinate[1]=150;               //圆心y坐标
TKS14A_I_levels[27].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[27].contacts[1].value_coordinate[1]=144;              //显示起始y坐标

TKS14A_I_levels[27].contacts[2].flag_last=0;
TKS14A_I_levels[27].contacts[2].channel=9;
TKS14A_I_levels[27].contacts[2].point_coordinate[0]=96;               //圆心x坐标
TKS14A_I_levels[27].contacts[2].point_coordinate[1]=186;               //圆心y坐标
TKS14A_I_levels[27].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[27].contacts[2].value_coordinate[1]=180;               //显示起始y坐标

TKS14A_I_levels[27].contacts[3].flag_last=1;
TKS14A_I_levels[27].contacts[3].channel=11;
TKS14A_I_levels[27].contacts[3].point_coordinate[0]=96;               //圆心x坐标
TKS14A_I_levels[27].contacts[3].point_coordinate[1]=210;               //圆心y坐标
TKS14A_I_levels[27].contacts[3].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[27].contacts[3].value_coordinate[1]=204;               //显示起始y坐标
//叁
TKS14A_I_levels[28].contacts[0].flag_last=0;
TKS14A_I_levels[28].contacts[0].channel=5;
TKS14A_I_levels[28].contacts[0].point_coordinate[0]=108;               //圆心x坐标
TKS14A_I_levels[28].contacts[0].point_coordinate[1]=138;               //圆心y坐标
TKS14A_I_levels[28].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[28].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

TKS14A_I_levels[28].contacts[1].flag_last=0;
TKS14A_I_levels[28].contacts[1].channel=6;
TKS14A_I_levels[28].contacts[1].point_coordinate[0]=108;               //圆心x坐标
TKS14A_I_levels[28].contacts[1].point_coordinate[1]=150;               //圆心y坐标
TKS14A_I_levels[28].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[28].contacts[1].value_coordinate[1]=144;               //显示起始y坐标

TKS14A_I_levels[28].contacts[2].flag_last=0;
TKS14A_I_levels[28].contacts[2].channel=9;
TKS14A_I_levels[28].contacts[2].point_coordinate[0]=108;               //圆心x坐标
TKS14A_I_levels[28].contacts[2].point_coordinate[1]=186;               //圆心y坐标
TKS14A_I_levels[28].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[28].contacts[2].value_coordinate[1]=180;               //显示起始y坐标

TKS14A_I_levels[28].contacts[3].flag_last=0;
TKS14A_I_levels[28].contacts[3].channel=10;
TKS14A_I_levels[28].contacts[3].point_coordinate[0]=108;               //圆心x坐标
TKS14A_I_levels[28].contacts[3].point_coordinate[1]=198;               //圆心y坐标
TKS14A_I_levels[28].contacts[3].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[28].contacts[3].value_coordinate[1]=192;               //显示起始y坐标

TKS14A_I_levels[28].contacts[4].flag_last=1;
TKS14A_I_levels[28].contacts[4].channel=11;
TKS14A_I_levels[28].contacts[4].point_coordinate[0]=108;               //圆心x坐标
TKS14A_I_levels[28].contacts[4].point_coordinate[1]=210;               //圆心y坐标
TKS14A_I_levels[28].contacts[4].value_coordinate[0]=150;               //显示起始x坐标
TKS14A_I_levels[28].contacts[4].value_coordinate[1]=204;               //显示起始y坐标
}





void measure_TKS14A_I(int x,int y)
{
  unsigned char n;
     for(n=0;n<29;n++)
     {
       if(x>TKS14A_I_TP[n][0]&&x<TKS14A_I_TP[n][2]&&y>TKS14A_I_TP[n][1]&&y<TKS14A_I_TP[n][3])
       {
         GUI_Rectangle(TKS14A_I_TP[n][0],TKS14A_I_TP[n][1],TKS14A_I_TP[n][2],TKS14A_I_TP[n][3],Black,0);
         measure_TKS14A_I_level(n);
       }
     }
}


void measure_TKS14A_I_level(unsigned char n)
{
  unsigned char i=0,j=0,k=0;
  unsigned char *p;
  for(k=0;k<5;k++)
  {
      if(TKS14A_I_levels[n].contacts[i].flag_last==0)
      {
        Set_Channel_TKS14A_I(TKS14A_I_levels[n].contacts[i].channel);
        CD4067_EN;
//        printf("%d",TKS14A_I_levels[n].contacts[i].channel);
        delay_long();
        p=Get_ADC1_Value();
        for(j=0;j<6;j++)
        {
          TKS14A_I_levels[n].contacts[i].R[j]=*(p+j);
        }
//        printf(ADC_Value);
        if(TKS14A_I_levels[n].contacts[i].R[0]=='0')
        {
          GUI_Circle(TKS14A_I_levels[n].contacts[i].point_coordinate[0],TKS14A_I_levels[n].contacts[i].point_coordinate[1],4,Green,0x01);
        }
        else
        {
          GUI_Circle(TKS14A_I_levels[n].contacts[i].point_coordinate[0],TKS14A_I_levels[n].contacts[i].point_coordinate[1],4,Red,0x01);
        }
        ili9320_writestr12(TKS14A_I_levels[n].contacts[i].value_coordinate[0], TKS14A_I_levels[n].contacts[i].value_coordinate[1],TKS14A_I_levels[n].contacts[i].R,Cyan, Black);
      i++;
      }
      if(TKS14A_I_levels[n].contacts[i].flag_last==1)
      {
        Set_Channel_TKS14A_I(TKS14A_I_levels[n].contacts[i].channel);
        CD4067_EN;
//        printf("%d",TKS14A_I_levels[n].contacts[i].channel);
        delay_long();
        p=Get_ADC1_Value();
        for(j=0;j<6;j++)
        {
          TKS14A_I_levels[n].contacts[i].R[j]=*(p+j);
        }
//        printf(ADC_Value);
        for(j=0;j<6;j++)
        {
          TKS14A_I_levels[n].level_V[j]=*(p+j+6);
        }
        ili9320_writestr12(54, 227,TKS14A_I_levels[n].level_V,Cyan, Black);
        if(TKS14A_I_levels[n].contacts[i].R[0]=='0')
        {
          GUI_Circle(TKS14A_I_levels[n].contacts[i].point_coordinate[0],TKS14A_I_levels[n].contacts[i].point_coordinate[1],4,Green,0x01);
        }
        else
        {
          GUI_Circle(TKS14A_I_levels[n].contacts[i].point_coordinate[0],TKS14A_I_levels[n].contacts[i].point_coordinate[1],4,Red,0x01);
        }
        ili9320_writestr12(TKS14A_I_levels[n].contacts[i].value_coordinate[0], TKS14A_I_levels[n].contacts[i].value_coordinate[1],TKS14A_I_levels[n].contacts[i].R,Cyan, Black);
      CD4067_DIS;
      }
  }
}

void TKS14A_I_Scan()
{
  unsigned char ch,j;
  unsigned char *ad;
  unsigned char V_ch[6];
  unsigned int ch_flag=0;
  unsigned char R_ch[6];
  unsigned int R_xy[12][2]=
  {{264,36},{264,48},{264,60},{264,72},{264,84},
   {150,132},{150,144},{150,156},{150,168},{150,180},{150,192},{150,204}};
  for(ch=0;ch<12;ch++)
  {
    Set_Channel_TKS14A_I(ch);
    delay_nus(1000);
    ad=Get_ADC1_Value();
    for(j=0;j<6;j++)
    {
      R_ch[j]=*(ad+j);
    }
    ili9320_writestr12(R_xy[ch][0], R_xy[ch][1],R_ch,Cyan, Black);
    if(R_ch[0]=='O')
    {
      ch_flag=ch_flag&~(1<<ch);
    }
    else
    {
      ch_flag=ch_flag|1<<ch;
    }
  }
  ad=Get_ADC1_Value();
  for(j=0;j<6;j++)
  {
    V_ch[j]=*(ad+j+6);
  }
  ili9320_writestr12(54, 227,V_ch,Cyan, Black);
  switch((ch_flag&0xfe0)>>5)
  {
  case 0x15: //后
    {
      for(j=0;j<7;j++)
      {
        GUI_Rectangle(29+12*j,119,41+12*j,132,Blue2,0);
      }
      GUI_Rectangle(29,119,41,132,Red,0);
      break;
    }
  case 0x00://0
    {
      for(j=0;j<7;j++)
      {
        GUI_Rectangle(29+12*j,119,41+12*j,132,Blue2,0);
      }
      GUI_Rectangle(41,119,53,132,Red,0);
      break;
    }
  case 0x0b://制动
    {
      for(j=0;j<7;j++)
      {
        GUI_Rectangle(29+12*j,119,41+12*j,132,Blue2,0);
      }
      GUI_Rectangle(53,119,65,132,Red,0);
      break;
    }
    case 0x13://前进
    {
      for(j=0;j<7;j++)
      {
        GUI_Rectangle(29+12*j,119,41+12*j,132,Blue2,0);
      }
      GUI_Rectangle(65,119,77,132,Red,0);
      break;
    }
  case 0x33://一级
    {
      for(j=0;j<7;j++)
      {
        GUI_Rectangle(29+12*j,119,41+12*j,132,Blue2,0);
      }
      GUI_Rectangle(77,119,89,132,Red,0);
      break;
    }
  case 0x53://二级
    {
      for(j=0;j<7;j++)
      {
        GUI_Rectangle(29+12*j,119,41+12*j,132,Blue2,0);
      }
      GUI_Rectangle(89,119,101,132,Red,0);
      break;
    }
  case 0x73://三级
    {
      for(j=0;j<7;j++)
      {
        GUI_Rectangle(29+12*j,119,41+12*j,132,Blue2,0);
      }
      GUI_Rectangle(101,119,113,132,Red,0);
      break;
    }
  default:break;
  }
  if((ch_flag&0x20)==0)//零
  {
    for(j=0;j<23;j++)
    {
      GUI_Rectangle(28+9*j,24,37+9*j,35,Blue2,0);
    }
    GUI_Rectangle(127,24,136,35,Blue2,0);
  }
  if(((ch_flag&0x100)!=0))//制动
  {
  }
  if(((ch_flag&0x200)!=0))//牵引
  {
  }
}


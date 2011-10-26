#include "SS7E_QS1_3.h"

struct level SS7E_QS1_3_levels[];//17个级位:调速+换向-零

unsigned int SS7E_QS1_3_TP[17][4]=
{
};

unsigned char Channel_SS7E_QS1_3[12]={0,1,2,3,4,5,6,9,10,11,12,14};//扫描通道


//float levels_SS7E_QS1_3[23]={};//级位电压
//float allowance_SS7E_QS1_3;//级位电压容差

void Set_Channel_SS7E_QS1_3(unsigned char x)
{
  if((Channel_SS7E_QS1_3[x]>>3)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_2);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_2);}
    if(((Channel_SS7E_QS1_3[x]&0x04)>>2)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_3);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_3);}
    if(((Channel_SS7E_QS1_3[x]&0x02)>>1)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_4);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_4);}
   if((Channel_SS7E_QS1_3[x]&0x01)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_7);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_7);}
}



void draw_SS7E_QS1_3()
{
  int n;
  unsigned char number[23]="制   0123456789101112131415161718";
  ili9320_Clear(Black);
  ili9320_PutCN12(102,0,"调速闭合表",Cyan,Black);
  ili9320_writestr12(200,0,"SS7E_QS1_3",Cyan,Black);//第一行
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


void SS7E_QS1_3_table()
{
//Z0
SS7E_QS1_3_levels[0].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
SS7E_QS1_3_levels[0].contacts[0].channel=1;
SS7E_QS1_3_levels[0].contacts[0].point_coordinate[0]=33;               //圆心x坐标
SS7E_QS1_3_levels[0].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[0].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[0].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[0].contacts[1].flag_last=1;
SS7E_QS1_3_levels[0].contacts[1].channel=2;
SS7E_QS1_3_levels[0].contacts[1].point_coordinate[0]=33;               //圆心x坐标
SS7E_QS1_3_levels[0].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[0].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[0].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

//Z1
SS7E_QS1_3_levels[1].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
SS7E_QS1_3_levels[1].contacts[0].channel=1;
SS7E_QS1_3_levels[1].contacts[0].point_coordinate[0]=42;               //圆心x坐标
SS7E_QS1_3_levels[1].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[1].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[1].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[1].contacts[1].flag_last=1;
SS7E_QS1_3_levels[1].contacts[1].channel=2;
SS7E_QS1_3_levels[1].contacts[1].point_coordinate[0]=42;               //圆心x坐标
SS7E_QS1_3_levels[1].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[1].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[1].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z2
SS7E_QS1_3_levels[2].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
SS7E_QS1_3_levels[2].contacts[0].channel=1;
SS7E_QS1_3_levels[2].contacts[0].point_coordinate[0]=51;               //圆心x坐标
SS7E_QS1_3_levels[2].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[2].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[2].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[2].contacts[1].flag_last=1;
SS7E_QS1_3_levels[2].contacts[1].channel=2;
SS7E_QS1_3_levels[2].contacts[1].point_coordinate[0]=51;               //圆心x坐标
SS7E_QS1_3_levels[2].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[2].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[2].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z3
SS7E_QS1_3_levels[3].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
SS7E_QS1_3_levels[3].contacts[0].channel=1;
SS7E_QS1_3_levels[3].contacts[0].point_coordinate[0]=60;               //圆心x坐标
SS7E_QS1_3_levels[3].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[3].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[3].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[3].contacts[1].flag_last=1;
SS7E_QS1_3_levels[3].contacts[1].channel=2;
SS7E_QS1_3_levels[3].contacts[1].point_coordinate[0]=60;               //圆心x坐标
SS7E_QS1_3_levels[3].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[3].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[3].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z4
SS7E_QS1_3_levels[4].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
SS7E_QS1_3_levels[4].contacts[0].channel=1;
SS7E_QS1_3_levels[4].contacts[0].point_coordinate[0]=69;               //圆心x坐标
SS7E_QS1_3_levels[4].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[4].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[4].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[4].contacts[1].flag_last=1;
SS7E_QS1_3_levels[4].contacts[1].channel=2;
SS7E_QS1_3_levels[4].contacts[1].point_coordinate[0]=69;               //圆心x坐标
SS7E_QS1_3_levels[4].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[4].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[4].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

//Z5
SS7E_QS1_3_levels[5].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
SS7E_QS1_3_levels[5].contacts[0].channel=1;
SS7E_QS1_3_levels[5].contacts[0].point_coordinate[0]=78;               //圆心x坐标
SS7E_QS1_3_levels[5].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[5].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[5].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[5].contacts[1].flag_last=1;
SS7E_QS1_3_levels[5].contacts[1].channel=2;
SS7E_QS1_3_levels[5].contacts[1].point_coordinate[0]=78;               //圆心x坐标
SS7E_QS1_3_levels[5].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[5].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[5].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z6
SS7E_QS1_3_levels[6].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
SS7E_QS1_3_levels[6].contacts[0].channel=1;
SS7E_QS1_3_levels[6].contacts[0].point_coordinate[0]=87;               //圆心x坐标
SS7E_QS1_3_levels[6].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[6].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[6].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[6].contacts[1].flag_last=1;
SS7E_QS1_3_levels[6].contacts[1].channel=2;
SS7E_QS1_3_levels[6].contacts[1].point_coordinate[0]=87;               //圆心x坐标
SS7E_QS1_3_levels[6].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[6].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[6].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//Z7
SS7E_QS1_3_levels[7].contacts[0].flag_last=0;                       //0,不是本级位最后一个触点,1:是
SS7E_QS1_3_levels[7].contacts[0].channel=1;
SS7E_QS1_3_levels[7].contacts[0].point_coordinate[0]=96;               //圆心x坐标
SS7E_QS1_3_levels[7].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[7].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[7].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[7].contacts[1].flag_last=1;
SS7E_QS1_3_levels[7].contacts[1].channel=2;
SS7E_QS1_3_levels[7].contacts[1].point_coordinate[0]=96;               //圆心x坐标
SS7E_QS1_3_levels[7].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[7].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[7].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//z8
SS7E_QS1_3_levels[8].contacts[0].flag_last=0;
SS7E_QS1_3_levels[8].contacts[0].channel=1;
SS7E_QS1_3_levels[8].contacts[0].point_coordinate[0]=105;               //圆心x坐标
SS7E_QS1_3_levels[8].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[8].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[8].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[8].contacts[1].flag_last=0;
SS7E_QS1_3_levels[8].contacts[1].channel=2;
SS7E_QS1_3_levels[8].contacts[1].point_coordinate[0]=105;               //圆心x坐标
SS7E_QS1_3_levels[8].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[8].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[8].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

SS7E_QS1_3_levels[8].contacts[2].flag_last=1;
SS7E_QS1_3_levels[8].contacts[2].channel=3;
SS7E_QS1_3_levels[8].contacts[2].point_coordinate[0]=105;               //圆心x坐标
SS7E_QS1_3_levels[8].contacts[2].point_coordinate[1]=78;               //圆心y坐标
SS7E_QS1_3_levels[8].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[8].contacts[2].value_coordinate[1]=72;               //显示起始y坐标
//z9
SS7E_QS1_3_levels[9].contacts[0].flag_last=0;
SS7E_QS1_3_levels[9].contacts[0].channel=1;
SS7E_QS1_3_levels[9].contacts[0].point_coordinate[0]=114;               //圆心x坐标
SS7E_QS1_3_levels[9].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[9].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[9].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[9].contacts[1].flag_last=0;
SS7E_QS1_3_levels[9].contacts[1].channel=2;
SS7E_QS1_3_levels[9].contacts[1].point_coordinate[0]=114;               //圆心x坐标
SS7E_QS1_3_levels[9].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[9].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[9].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

SS7E_QS1_3_levels[9].contacts[2].flag_last=1;
SS7E_QS1_3_levels[9].contacts[2].channel=3;
SS7E_QS1_3_levels[9].contacts[2].point_coordinate[0]=114;               //圆心x坐标
SS7E_QS1_3_levels[9].contacts[2].point_coordinate[1]=78;               //圆心y坐标
SS7E_QS1_3_levels[9].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[9].contacts[2].value_coordinate[1]=72;               //显示起始y坐标
//z10
SS7E_QS1_3_levels[10].contacts[0].flag_last=0;
SS7E_QS1_3_levels[10].contacts[0].channel=0;
SS7E_QS1_3_levels[10].contacts[0].point_coordinate[0]=123;               //圆心x坐标
SS7E_QS1_3_levels[10].contacts[0].point_coordinate[1]=42;               //圆心y坐标
SS7E_QS1_3_levels[10].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[10].contacts[0].value_coordinate[1]=36;               //显示起始y坐标

SS7E_QS1_3_levels[10].contacts[1].flag_last=0;
SS7E_QS1_3_levels[10].contacts[1].channel=1;
SS7E_QS1_3_levels[10].contacts[1].point_coordinate[0]=123;               //圆心x坐标
SS7E_QS1_3_levels[10].contacts[1].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[10].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[10].contacts[1].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[10].contacts[2].flag_last=0;
SS7E_QS1_3_levels[10].contacts[2].channel=2;
SS7E_QS1_3_levels[10].contacts[2].point_coordinate[0]=123;               //圆心x坐标
SS7E_QS1_3_levels[10].contacts[2].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[10].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[10].contacts[2].value_coordinate[1]=60;               //显示起始y坐标

SS7E_QS1_3_levels[10].contacts[3].flag_last=1;
SS7E_QS1_3_levels[10].contacts[3].channel=3;
SS7E_QS1_3_levels[10].contacts[3].point_coordinate[0]=123;               //圆心x坐标
SS7E_QS1_3_levels[10].contacts[3].point_coordinate[1]=78;               //圆心y坐标
SS7E_QS1_3_levels[10].contacts[3].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[10].contacts[3].value_coordinate[1]=72;               //显示起始y坐标
//oo
SS7E_QS1_3_levels[11].contacts[0].flag_last=1;
SS7E_QS1_3_levels[11].contacts[0].channel=0;
SS7E_QS1_3_levels[11].contacts[0].point_coordinate[0]=132;               //圆心x坐标
SS7E_QS1_3_levels[11].contacts[0].point_coordinate[1]=42;               //圆心y坐标
SS7E_QS1_3_levels[11].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[11].contacts[0].value_coordinate[1]=36;               //显示起始y坐标
//q0
SS7E_QS1_3_levels[12].contacts[0].flag_last=0;
SS7E_QS1_3_levels[12].contacts[0].channel=0;
SS7E_QS1_3_levels[12].contacts[0].point_coordinate[0]=141;               //圆心x坐标
SS7E_QS1_3_levels[12].contacts[0].point_coordinate[1]=42;               //圆心y坐标
SS7E_QS1_3_levels[12].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[12].contacts[0].value_coordinate[1]=36;               //显示起始y坐标

SS7E_QS1_3_levels[12].contacts[1].flag_last=0;
SS7E_QS1_3_levels[12].contacts[1].channel=1;
SS7E_QS1_3_levels[12].contacts[1].point_coordinate[0]=141;               //圆心x坐标
SS7E_QS1_3_levels[12].contacts[1].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[12].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[12].contacts[1].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[12].contacts[2].flag_last=1;
SS7E_QS1_3_levels[12].contacts[2].channel=3;
SS7E_QS1_3_levels[12].contacts[2].point_coordinate[0]=141;               //圆心x坐标
SS7E_QS1_3_levels[12].contacts[2].point_coordinate[1]=78;               //圆心y坐标
SS7E_QS1_3_levels[12].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[12].contacts[2].value_coordinate[1]=72;               //显示起始y坐标
//q1
SS7E_QS1_3_levels[13].contacts[0].flag_last=0;
SS7E_QS1_3_levels[13].contacts[0].channel=1;
SS7E_QS1_3_levels[13].contacts[0].point_coordinate[0]=150;               //圆心x坐标
SS7E_QS1_3_levels[13].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[13].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[13].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[13].contacts[1].flag_last=1;
SS7E_QS1_3_levels[13].contacts[1].channel=3;
SS7E_QS1_3_levels[13].contacts[1].point_coordinate[0]=150;               //圆心x坐标
SS7E_QS1_3_levels[13].contacts[1].point_coordinate[1]=78;               //圆心y坐标
SS7E_QS1_3_levels[13].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[13].contacts[1].value_coordinate[1]=72;               //显示起始y坐标

//q2
SS7E_QS1_3_levels[14].contacts[0].flag_last=0;
SS7E_QS1_3_levels[14].contacts[0].channel=1;
SS7E_QS1_3_levels[14].contacts[0].point_coordinate[0]=159;               //圆心x坐标
SS7E_QS1_3_levels[14].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[14].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[14].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[14].contacts[1].flag_last=0;
SS7E_QS1_3_levels[14].contacts[1].channel=2;
SS7E_QS1_3_levels[14].contacts[1].point_coordinate[0]=159;               //圆心x坐标
SS7E_QS1_3_levels[14].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[14].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[14].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

SS7E_QS1_3_levels[14].contacts[2].flag_last=1;
SS7E_QS1_3_levels[14].contacts[2].channel=3;
SS7E_QS1_3_levels[14].contacts[2].point_coordinate[0]=159;               //圆心x坐标
SS7E_QS1_3_levels[14].contacts[2].point_coordinate[1]=78;               //圆心y坐标
SS7E_QS1_3_levels[14].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[14].contacts[2].value_coordinate[1]=72;               //显示起始y坐标
//q3
SS7E_QS1_3_levels[15].contacts[0].flag_last=0;
SS7E_QS1_3_levels[15].contacts[0].channel=1;
SS7E_QS1_3_levels[15].contacts[0].point_coordinate[0]=168;               //圆心x坐标
SS7E_QS1_3_levels[15].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[15].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[15].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[15].contacts[1].flag_last=1;
SS7E_QS1_3_levels[15].contacts[1].channel=2;
SS7E_QS1_3_levels[15].contacts[1].point_coordinate[0]=168;               //圆心x坐标
SS7E_QS1_3_levels[15].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[15].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[15].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//q4
SS7E_QS1_3_levels[16].contacts[0].flag_last=0;
SS7E_QS1_3_levels[16].contacts[0].channel=1;
SS7E_QS1_3_levels[16].contacts[0].point_coordinate[0]=177;               //圆心x坐标
SS7E_QS1_3_levels[16].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[16].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[16].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[16].contacts[1].flag_last=1;
SS7E_QS1_3_levels[16].contacts[1].channel=2;
SS7E_QS1_3_levels[16].contacts[1].point_coordinate[0]=177;               //圆心x坐标
SS7E_QS1_3_levels[16].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[16].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[16].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//q5
SS7E_QS1_3_levels[17].contacts[0].flag_last=0;
SS7E_QS1_3_levels[17].contacts[0].channel=1;
SS7E_QS1_3_levels[17].contacts[0].point_coordinate[0]=186;               //圆心x坐标
SS7E_QS1_3_levels[17].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[17].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[17].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[17].contacts[1].flag_last=1;
SS7E_QS1_3_levels[17].contacts[1].channel=2;
SS7E_QS1_3_levels[17].contacts[1].point_coordinate[0]=186;               //圆心x坐标
SS7E_QS1_3_levels[17].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[17].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[17].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//q6
SS7E_QS1_3_levels[18].contacts[0].flag_last=0;
SS7E_QS1_3_levels[18].contacts[0].channel=1;
SS7E_QS1_3_levels[18].contacts[0].point_coordinate[0]=195;               //圆心x坐标
SS7E_QS1_3_levels[18].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[18].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[18].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[18].contacts[1].flag_last=1;
SS7E_QS1_3_levels[18].contacts[1].channel=2;
SS7E_QS1_3_levels[18].contacts[1].point_coordinate[0]=195;               //圆心x坐标
SS7E_QS1_3_levels[18].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[18].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[18].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

//q7
SS7E_QS1_3_levels[19].contacts[0].flag_last=0;
SS7E_QS1_3_levels[19].contacts[0].channel=1;
SS7E_QS1_3_levels[19].contacts[0].point_coordinate[0]=204;               //圆心x坐标
SS7E_QS1_3_levels[19].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[19].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[19].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[19].contacts[1].flag_last=1;
SS7E_QS1_3_levels[19].contacts[1].channel=2;
SS7E_QS1_3_levels[19].contacts[1].point_coordinate[0]=204;               //圆心x坐标
SS7E_QS1_3_levels[19].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[19].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[19].contacts[1].value_coordinate[1]=60;               //显示起始y坐标
//q8
SS7E_QS1_3_levels[20].contacts[0].flag_last=0;
SS7E_QS1_3_levels[20].contacts[0].channel=1;
SS7E_QS1_3_levels[20].contacts[0].point_coordinate[0]=213;               //圆心x坐标
SS7E_QS1_3_levels[20].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[20].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[20].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[20].contacts[1].flag_last=0;
SS7E_QS1_3_levels[20].contacts[1].channel=2;
SS7E_QS1_3_levels[20].contacts[1].point_coordinate[0]=213;               //圆心x坐标
SS7E_QS1_3_levels[20].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[20].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[20].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

SS7E_QS1_3_levels[20].contacts[2].flag_last=1;
SS7E_QS1_3_levels[20].contacts[2].channel=4;
SS7E_QS1_3_levels[20].contacts[2].point_coordinate[0]=213;               //圆心x坐标
SS7E_QS1_3_levels[20].contacts[2].point_coordinate[1]=90;               //圆心y坐标
SS7E_QS1_3_levels[20].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[20].contacts[2].value_coordinate[1]=84;               //显示起始y坐标
//q9
SS7E_QS1_3_levels[21].contacts[0].flag_last=0;
SS7E_QS1_3_levels[21].contacts[0].channel=1;
SS7E_QS1_3_levels[21].contacts[0].point_coordinate[0]=222;               //圆心x坐标
SS7E_QS1_3_levels[21].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[21].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[21].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[21].contacts[1].flag_last=0;
SS7E_QS1_3_levels[21].contacts[1].channel=2;
SS7E_QS1_3_levels[21].contacts[1].point_coordinate[0]=222;               //圆心x坐标
SS7E_QS1_3_levels[21].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[21].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[21].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

SS7E_QS1_3_levels[21].contacts[2].flag_last=1;
SS7E_QS1_3_levels[21].contacts[2].channel=4;
SS7E_QS1_3_levels[21].contacts[2].point_coordinate[0]=222;               //圆心x坐标
SS7E_QS1_3_levels[21].contacts[2].point_coordinate[1]=90;               //圆心y坐标
SS7E_QS1_3_levels[21].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[21].contacts[2].value_coordinate[1]=84;               //显示起始y坐标
//q10
SS7E_QS1_3_levels[22].contacts[0].flag_last=0;
SS7E_QS1_3_levels[22].contacts[0].channel=1;
SS7E_QS1_3_levels[22].contacts[0].point_coordinate[0]=231;               //圆心x坐标
SS7E_QS1_3_levels[22].contacts[0].point_coordinate[1]=54;               //圆心y坐标
SS7E_QS1_3_levels[22].contacts[0].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[22].contacts[0].value_coordinate[1]=48;               //显示起始y坐标

SS7E_QS1_3_levels[22].contacts[1].flag_last=0;
SS7E_QS1_3_levels[22].contacts[1].channel=2;
SS7E_QS1_3_levels[22].contacts[1].point_coordinate[0]=231;               //圆心x坐标
SS7E_QS1_3_levels[22].contacts[1].point_coordinate[1]=66;               //圆心y坐标
SS7E_QS1_3_levels[22].contacts[1].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[22].contacts[1].value_coordinate[1]=60;               //显示起始y坐标

SS7E_QS1_3_levels[22].contacts[2].flag_last=1;
SS7E_QS1_3_levels[22].contacts[2].channel=4;
SS7E_QS1_3_levels[22].contacts[2].point_coordinate[0]=231;               //圆心x坐标
SS7E_QS1_3_levels[22].contacts[2].point_coordinate[1]=90;               //圆心y坐标
SS7E_QS1_3_levels[22].contacts[2].value_coordinate[0]=264;               //显示起始x坐标
SS7E_QS1_3_levels[22].contacts[2].value_coordinate[1]=84;               //显示起始y坐标
//后
SS7E_QS1_3_levels[23].contacts[0].flag_last=0;
SS7E_QS1_3_levels[23].contacts[0].channel=5;
SS7E_QS1_3_levels[23].contacts[0].point_coordinate[0]=36;               //圆心x坐标
SS7E_QS1_3_levels[23].contacts[0].point_coordinate[1]=138;               //圆心y坐标
SS7E_QS1_3_levels[23].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[23].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

SS7E_QS1_3_levels[23].contacts[1].flag_last=0;
SS7E_QS1_3_levels[23].contacts[1].channel=7;
SS7E_QS1_3_levels[23].contacts[1].point_coordinate[0]=36;               //圆心x坐标
SS7E_QS1_3_levels[23].contacts[1].point_coordinate[1]=162;               //圆心y坐标
SS7E_QS1_3_levels[23].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[23].contacts[1].value_coordinate[1]=156;               //显示起始y坐标

SS7E_QS1_3_levels[23].contacts[2].flag_last=1;
SS7E_QS1_3_levels[23].contacts[2].channel=9;
SS7E_QS1_3_levels[23].contacts[2].point_coordinate[0]=36;               //圆心x坐标
SS7E_QS1_3_levels[23].contacts[2].point_coordinate[1]=186;               //圆心y坐标
SS7E_QS1_3_levels[23].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[23].contacts[2].value_coordinate[1]=180;               //显示起始y坐标
//零
//制
SS7E_QS1_3_levels[24].contacts[0].flag_last=0;
SS7E_QS1_3_levels[24].contacts[0].channel=5;
SS7E_QS1_3_levels[24].contacts[0].point_coordinate[0]=60;               //圆心x坐标
SS7E_QS1_3_levels[24].contacts[0].point_coordinate[1]=138;               //圆心y坐标
SS7E_QS1_3_levels[24].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[24].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

SS7E_QS1_3_levels[24].contacts[1].flag_last=0;
SS7E_QS1_3_levels[24].contacts[1].channel=6;
SS7E_QS1_3_levels[24].contacts[1].point_coordinate[0]=60;               //圆心x坐标
SS7E_QS1_3_levels[24].contacts[1].point_coordinate[1]=150;               //圆心y坐标
SS7E_QS1_3_levels[24].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[24].contacts[1].value_coordinate[1]=144;               //显示起始y坐标

SS7E_QS1_3_levels[24].contacts[2].flag_last=1;
SS7E_QS1_3_levels[24].contacts[2].channel=8;
SS7E_QS1_3_levels[24].contacts[2].point_coordinate[0]=60;               //圆心x坐标
SS7E_QS1_3_levels[24].contacts[2].point_coordinate[1]=174;               //圆心y坐标
SS7E_QS1_3_levels[24].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[24].contacts[2].value_coordinate[1]=168;               //显示起始y坐标
//前
SS7E_QS1_3_levels[25].contacts[0].flag_last=0;
SS7E_QS1_3_levels[25].contacts[0].channel=5;
SS7E_QS1_3_levels[25].contacts[0].point_coordinate[0]=72;               //圆心x坐标
SS7E_QS1_3_levels[25].contacts[0].point_coordinate[1]=138;               //圆心y坐标
SS7E_QS1_3_levels[25].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[25].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

SS7E_QS1_3_levels[25].contacts[1].flag_last=0;
SS7E_QS1_3_levels[25].contacts[1].channel=6;
SS7E_QS1_3_levels[25].contacts[1].point_coordinate[0]=72;               //圆心x坐标
SS7E_QS1_3_levels[25].contacts[1].point_coordinate[1]=150;               //圆心y坐标
SS7E_QS1_3_levels[25].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[25].contacts[1].value_coordinate[1]=144;               //显示起始y坐标

SS7E_QS1_3_levels[25].contacts[2].flag_last=1;
SS7E_QS1_3_levels[25].contacts[2].channel=9;
SS7E_QS1_3_levels[25].contacts[2].point_coordinate[0]=72;               //圆心x坐标
SS7E_QS1_3_levels[25].contacts[2].point_coordinate[1]=186;               //圆心y坐标
SS7E_QS1_3_levels[25].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[25].contacts[2].value_coordinate[1]=180;               //显示起始y坐标
//壹
SS7E_QS1_3_levels[26].contacts[0].flag_last=0;
SS7E_QS1_3_levels[26].contacts[0].channel=5;
SS7E_QS1_3_levels[26].contacts[0].point_coordinate[0]=84;               //圆心x坐标
SS7E_QS1_3_levels[26].contacts[0].point_coordinate[1]=138;               //圆心y坐标
SS7E_QS1_3_levels[26].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[26].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

SS7E_QS1_3_levels[26].contacts[1].flag_last=0;
SS7E_QS1_3_levels[26].contacts[1].channel=6;
SS7E_QS1_3_levels[26].contacts[1].point_coordinate[0]=84;               //圆心x坐标
SS7E_QS1_3_levels[26].contacts[1].point_coordinate[1]=150;               //圆心y坐标
SS7E_QS1_3_levels[26].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[26].contacts[1].value_coordinate[1]=144;               //显示起始y坐标

SS7E_QS1_3_levels[26].contacts[2].flag_last=0;
SS7E_QS1_3_levels[26].contacts[2].channel=9;
SS7E_QS1_3_levels[26].contacts[2].point_coordinate[0]=84;               //圆心x坐标
SS7E_QS1_3_levels[26].contacts[2].point_coordinate[1]=186;               //圆心y坐标
SS7E_QS1_3_levels[26].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[26].contacts[2].value_coordinate[1]=180;               //显示起始y坐标

SS7E_QS1_3_levels[26].contacts[3].flag_last=1;
SS7E_QS1_3_levels[26].contacts[3].channel=10;
SS7E_QS1_3_levels[26].contacts[3].point_coordinate[0]=84;               //圆心x坐标
SS7E_QS1_3_levels[26].contacts[3].point_coordinate[1]=198;               //圆心y坐标
SS7E_QS1_3_levels[26].contacts[3].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[26].contacts[3].value_coordinate[1]=192;               //显示起始y坐标
//贰
SS7E_QS1_3_levels[27].contacts[0].flag_last=0;
SS7E_QS1_3_levels[27].contacts[0].channel=5;
SS7E_QS1_3_levels[27].contacts[0].point_coordinate[0]=96;               //圆心x坐标
SS7E_QS1_3_levels[27].contacts[0].point_coordinate[1]=138;               //圆心y坐标
SS7E_QS1_3_levels[27].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[27].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

SS7E_QS1_3_levels[27].contacts[1].flag_last=0;
SS7E_QS1_3_levels[27].contacts[1].channel=6;
SS7E_QS1_3_levels[27].contacts[1].point_coordinate[0]=96;               //圆心x坐标
SS7E_QS1_3_levels[27].contacts[1].point_coordinate[1]=150;               //圆心y坐标
SS7E_QS1_3_levels[27].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[27].contacts[1].value_coordinate[1]=144;              //显示起始y坐标

SS7E_QS1_3_levels[27].contacts[2].flag_last=0;
SS7E_QS1_3_levels[27].contacts[2].channel=9;
SS7E_QS1_3_levels[27].contacts[2].point_coordinate[0]=96;               //圆心x坐标
SS7E_QS1_3_levels[27].contacts[2].point_coordinate[1]=186;               //圆心y坐标
SS7E_QS1_3_levels[27].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[27].contacts[2].value_coordinate[1]=180;               //显示起始y坐标

SS7E_QS1_3_levels[27].contacts[3].flag_last=1;
SS7E_QS1_3_levels[27].contacts[3].channel=11;
SS7E_QS1_3_levels[27].contacts[3].point_coordinate[0]=96;               //圆心x坐标
SS7E_QS1_3_levels[27].contacts[3].point_coordinate[1]=210;               //圆心y坐标
SS7E_QS1_3_levels[27].contacts[3].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[27].contacts[3].value_coordinate[1]=204;               //显示起始y坐标
//叁
SS7E_QS1_3_levels[28].contacts[0].flag_last=0;
SS7E_QS1_3_levels[28].contacts[0].channel=5;
SS7E_QS1_3_levels[28].contacts[0].point_coordinate[0]=108;               //圆心x坐标
SS7E_QS1_3_levels[28].contacts[0].point_coordinate[1]=138;               //圆心y坐标
SS7E_QS1_3_levels[28].contacts[0].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[28].contacts[0].value_coordinate[1]=132;               //显示起始y坐标

SS7E_QS1_3_levels[28].contacts[1].flag_last=0;
SS7E_QS1_3_levels[28].contacts[1].channel=6;
SS7E_QS1_3_levels[28].contacts[1].point_coordinate[0]=108;               //圆心x坐标
SS7E_QS1_3_levels[28].contacts[1].point_coordinate[1]=150;               //圆心y坐标
SS7E_QS1_3_levels[28].contacts[1].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[28].contacts[1].value_coordinate[1]=144;               //显示起始y坐标

SS7E_QS1_3_levels[28].contacts[2].flag_last=0;
SS7E_QS1_3_levels[28].contacts[2].channel=9;
SS7E_QS1_3_levels[28].contacts[2].point_coordinate[0]=108;               //圆心x坐标
SS7E_QS1_3_levels[28].contacts[2].point_coordinate[1]=186;               //圆心y坐标
SS7E_QS1_3_levels[28].contacts[2].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[28].contacts[2].value_coordinate[1]=180;               //显示起始y坐标

SS7E_QS1_3_levels[28].contacts[3].flag_last=0;
SS7E_QS1_3_levels[28].contacts[3].channel=10;
SS7E_QS1_3_levels[28].contacts[3].point_coordinate[0]=108;               //圆心x坐标
SS7E_QS1_3_levels[28].contacts[3].point_coordinate[1]=198;               //圆心y坐标
SS7E_QS1_3_levels[28].contacts[3].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[28].contacts[3].value_coordinate[1]=192;               //显示起始y坐标

SS7E_QS1_3_levels[28].contacts[4].flag_last=1;
SS7E_QS1_3_levels[28].contacts[4].channel=11;
SS7E_QS1_3_levels[28].contacts[4].point_coordinate[0]=108;               //圆心x坐标
SS7E_QS1_3_levels[28].contacts[4].point_coordinate[1]=210;               //圆心y坐标
SS7E_QS1_3_levels[28].contacts[4].value_coordinate[0]=150;               //显示起始x坐标
SS7E_QS1_3_levels[28].contacts[4].value_coordinate[1]=204;               //显示起始y坐标
}





void measure_SS7E_QS1_3(int x,int y)
{
  unsigned char n;
     for(n=0;n<29;n++)
     {
       if(x>SS7E_QS1_3_TP[n][0]&&x<SS7E_QS1_3_TP[n][2]&&y>SS7E_QS1_3_TP[n][1]&&y<SS7E_QS1_3_TP[n][3])
       {
         GUI_Rectangle(SS7E_QS1_3_TP[n][0],SS7E_QS1_3_TP[n][1],SS7E_QS1_3_TP[n][2],SS7E_QS1_3_TP[n][3],Black,0);
         measure_SS7E_QS1_3_level(n);
       }
     }
}


void measure_SS7E_QS1_3_level(unsigned char n)
{
  unsigned char i=0,j=0,k=0;
  unsigned char *p;
  for(k=0;k<5;k++)
  {
      if(SS7E_QS1_3_levels[n].contacts[i].flag_last==0)
      {
        Set_Channel_SS7E_QS1_3(SS7E_QS1_3_levels[n].contacts[i].channel);
        CD4067_EN;
//        printf("%d",SS7E_QS1_3_levels[n].contacts[i].channel);
        delay_long();
        p=Get_ADC1_Value();
        for(j=0;j<6;j++)
        {
          SS7E_QS1_3_levels[n].contacts[i].R[j]=*(p+j);
        }
//        printf(ADC_Value);
        if(SS7E_QS1_3_levels[n].contacts[i].R[0]=='0')
        {
          GUI_Circle(SS7E_QS1_3_levels[n].contacts[i].point_coordinate[0],SS7E_QS1_3_levels[n].contacts[i].point_coordinate[1],4,Green,0x01);
        }
        else
        {
          GUI_Circle(SS7E_QS1_3_levels[n].contacts[i].point_coordinate[0],SS7E_QS1_3_levels[n].contacts[i].point_coordinate[1],4,Red,0x01);
        }
        ili9320_writestr12(SS7E_QS1_3_levels[n].contacts[i].value_coordinate[0], SS7E_QS1_3_levels[n].contacts[i].value_coordinate[1],SS7E_QS1_3_levels[n].contacts[i].R,Cyan, Black);
      i++;
      }
      if(SS7E_QS1_3_levels[n].contacts[i].flag_last==1)
      {
        Set_Channel_SS7E_QS1_3(SS7E_QS1_3_levels[n].contacts[i].channel);
        CD4067_EN;
//        printf("%d",SS7E_QS1_3_levels[n].contacts[i].channel);
        delay_long();
        p=Get_ADC1_Value();
        for(j=0;j<6;j++)
        {
          SS7E_QS1_3_levels[n].contacts[i].R[j]=*(p+j);
        }
//        printf(ADC_Value);
        for(j=0;j<6;j++)
        {
          SS7E_QS1_3_levels[n].level_V[j]=*(p+j+6);
        }
        ili9320_writestr12(54, 227,SS7E_QS1_3_levels[n].level_V,Cyan, Black);
        if(SS7E_QS1_3_levels[n].contacts[i].R[0]=='0')
        {
          GUI_Circle(SS7E_QS1_3_levels[n].contacts[i].point_coordinate[0],SS7E_QS1_3_levels[n].contacts[i].point_coordinate[1],4,Green,0x01);
        }
        else
        {
          GUI_Circle(SS7E_QS1_3_levels[n].contacts[i].point_coordinate[0],SS7E_QS1_3_levels[n].contacts[i].point_coordinate[1],4,Red,0x01);
        }
        ili9320_writestr12(SS7E_QS1_3_levels[n].contacts[i].value_coordinate[0], SS7E_QS1_3_levels[n].contacts[i].value_coordinate[1],SS7E_QS1_3_levels[n].contacts[i].R,Cyan, Black);
      CD4067_DIS;
      }
  }
}

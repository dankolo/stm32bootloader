#include "TKS231_1_II.h"

struct level TKS231_1_II_levels[41];//41����λ:����+����-��

unsigned int TKS231_1_II_TP[41][4]=
{
  {30,12,42,24},{42,12,54,24},{54,12,66,24},{66,12,78,24},
  {78,12,90,24},{90,12,102,24},{102,12,114,24},{114,12,126,24},
  {126,12,138,24},{138,12,150,24},{150,12,162,24},{162,12,174,24},
  {174,12,186,24},{186,12,198,24},{198,12,210,24},{210,12,222,24},
  {222,12,234,24},{234,12,246,24},{246,12,258,24},
  {30,48,42,60},{42,48,54,60},{54,48,66,60},{66,48,78,60},
  {78,48,90,60},{90,48,102,60},{102,48,114,60},{114,48,126,60},
  {126,48,138,60},{138,48,150,60},{150,48,162,60},{162,48,174,60},
  {174,48,186,60},{186,48,198,60},{198,48,210,60},{210,48,222,60},
  {222,48,234,60},{234,48,246,60},{246,48,258,60},
  {24,107,36,120},{60,107,72,120},{78,107,90,120}
};

unsigned char Channel_TKS231_1_II[12]={0,1,2,3,4,5,6,9,10,11,12,14};//ɨ��ͨ��


//float levels_TKS231_1_II[23]={};//��λ��ѹ
//float allowance_TKS231_1_II;//��λ��ѹ�ݲ�

void Set_Channel_TKS231_1_II(unsigned char x)
{
  if((Channel_TKS231_1_II[x]>>3)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_2);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_2);}
    if(((Channel_TKS231_1_II[x]&0x04)>>2)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_3);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_3);}
    if(((Channel_TKS231_1_II[x]&0x02)>>1)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_4);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_4);}
   if((Channel_TKS231_1_II[x]&0x01)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_7);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_7);}
}


/*******************************************************************************/
/////         10        20       30         40        50
/////12345678901234567890123456789012345678901234567890123
//1//                  ���ٱպϱ�     TKS231-1-II
//2//      0 1 2 3 4 5 6 7 8 9101112131415161718    ��ֵ00
//3//��419                                      401 0.123
//4//��412 . . . . . . . . . . . . . . . . . . .403 0.123
//5//      0 1 2 3 4 5 6 7 8 9101112131415161718
//6//ǣ419 . . . .                              401 0.123
//7//��412 . . . . . . . . . . . . . . . . . . .403 0.123
//8//     ����պϱ�
//9//    �� �� ǰ ��     ��ֵ00
//10/403 .     .  .  401 0.123
//11/404 .           401 0.123
//12/405       .  .  401 0.123
//13/406          .  401 0.123
//14/407 .     .     401 0.123
//15/
//16/
//17/
//18/
/*******************************************************************************/

void draw_TKS231_1_II()
{
  int n;
  ili9320_Clear(Black);
  ili9320_PutCN12(102,0,"���ٱպϱ�",Cyan,Black);
  ili9320_writestr12(200,0,"TKS231-1-II",Cyan,Black);
  ili9320_writestr12(30,12," 0 1 2 3 4 5 6 7 8 9101112131415161718",Cyan,Black);
  ili9320_PutCN12(284,12,"��ֵoo",Cyan,Black);
  ili9320_PutCN12(0,24,"��",Cyan,Black);
  ili9320_PutCN12(0,36,"��",Cyan,Black);
  ili9320_writestr12(12,24,"419",Cyan,Black);
  ili9320_writestr12(12,36,"412",Cyan,Black);
  ili9320_writestr12(262,24,"401",Cyan,Black);
  ili9320_writestr12(262,36,"403",Cyan,Black);
  ili9320_writestr12(30,48," 0 1 2 3 4 5 6 7 8 9101112131415161718",Cyan,Black);
  ili9320_PutCN12(0,60,"ǣ",Cyan,Black);
  ili9320_PutCN12(0,72,"��",Cyan,Black);
  ili9320_writestr12(12,60,"419",Cyan,Black);
  ili9320_writestr12(12,72,"412",Cyan,Black);
  ili9320_writestr12(262,60,"401",Cyan,Black);
  ili9320_writestr12(262,72,"403",Cyan,Black);
  ili9320_writestr12(0,120,"403",Cyan,Black);
  ili9320_writestr12(0,132,"404",Cyan,Black);
  ili9320_writestr12(0,144,"405",Cyan,Black);
  ili9320_writestr12(0,156,"406",Cyan,Black);
  ili9320_writestr12(0,168,"407",Cyan,Black);
  for(n=0;n<5;n++)
  {
    ili9320_writestr12(96,120+12*n,"401",Cyan,Black);
  }
  ili9320_PutCN12(30,96,"����պϱ�",Cyan,Black);
  ili9320_PutCN12(24,108,"��",Cyan,Black);
  ili9320_PutCN12(42,108,"��",Cyan,Black);
  ili9320_PutCN12(60,108,"ǰ",Cyan,Black);
  ili9320_PutCN12(78,108,"��",Cyan,Black);
  ili9320_PutCN12(120,108,"��ֵoo",Cyan,Black);
  for(n=0;n<19;n++)
  {
    GUI_Line(38+12*n,24,38+12*n,48,Blue2);
  }
//  GUI_Line(32,30,258,30,Blue2);
  GUI_Line(32,42,258,42,Blue2);
  for(n=0;n<19;n++)
  {
    GUI_Line(38+12*n,60,38+12*n,84,Blue2);
  }
  GUI_Line(32,66,78,66,Blue2);
  GUI_Line(32,78,258,78,Blue2);
  for(n=0;n<4;n++)
  {
    GUI_Line(30+18*n,120,30+18*n,180,Blue2);
  }
  for(n=0;n<5;n++)
  {
    GUI_Line(20,126+12*n,94,126+12*n,Blue2);
  }
  for(n=0;n<41;n++)
  {
    GUI_Rectangle(TKS231_1_II_TP[n][0],TKS231_1_II_TP[n][1],TKS231_1_II_TP[n][2],TKS231_1_II_TP[n][3],Blue2,0);
  }

  unsigned char points[]=
  {
38,42,50,42,62,42,74,42,86,42,98,42,110,42,122,42,134,42,146,42,158,42,170,42,182,42,194,42,206,42,218,42,230,42,242,42,254,42,

38,66,50,66,62,66,74,66,

38,78,50,78,62,78,74,78,86,78,98,78,110,78,122,78,134,78,146,78,158,78,170,78,182,78,194,78,206,78,218,78,230,78,242,78,254,78,

30,126,       66,126,84,126,

30,138,

              66,150,84,150,

                     84,162,

30,174,       66,174,


0xff
  };
  n=0;
  while(points[n]!=0xff)
  {
    GUI_Circle(points[n],points[n+1],4,Blue,0x01);
    n+=2;
  }
}


void TKS231_1_II_table()
{
//z0
TKS231_1_II_levels[0].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS231_1_II_levels[0].contacts[0].channel=1;
TKS231_1_II_levels[0].contacts[0].point_coordinate[0]=38;               //Բ��x����
TKS231_1_II_levels[0].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[0].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[0].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z1
TKS231_1_II_levels[1].contacts[0].flag_last=1;
TKS231_1_II_levels[1].contacts[0].channel=1;
TKS231_1_II_levels[1].contacts[0].point_coordinate[0]=50;               //Բ��x����
TKS231_1_II_levels[1].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[1].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[1].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z2
TKS231_1_II_levels[2].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS231_1_II_levels[2].contacts[0].channel=1;
TKS231_1_II_levels[2].contacts[0].point_coordinate[0]=62;               //Բ��x����
TKS231_1_II_levels[2].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[2].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[2].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z3
TKS231_1_II_levels[3].contacts[0].flag_last=1;
TKS231_1_II_levels[3].contacts[0].channel=1;
TKS231_1_II_levels[3].contacts[0].point_coordinate[0]=74;               //Բ��x����
TKS231_1_II_levels[3].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[3].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[3].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z4
TKS231_1_II_levels[4].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS231_1_II_levels[4].contacts[0].channel=1;
TKS231_1_II_levels[4].contacts[0].point_coordinate[0]=86;               //Բ��x����
TKS231_1_II_levels[4].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[4].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[4].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z5
TKS231_1_II_levels[5].contacts[0].flag_last=1;
TKS231_1_II_levels[5].contacts[0].channel=1;
TKS231_1_II_levels[5].contacts[0].point_coordinate[0]=98;               //Բ��x����
TKS231_1_II_levels[5].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[5].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[5].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z6
TKS231_1_II_levels[6].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS231_1_II_levels[6].contacts[0].channel=1;
TKS231_1_II_levels[6].contacts[0].point_coordinate[0]=110;               //Բ��x����
TKS231_1_II_levels[6].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[6].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[6].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z7
TKS231_1_II_levels[7].contacts[0].flag_last=1;
TKS231_1_II_levels[7].contacts[0].channel=1;
TKS231_1_II_levels[7].contacts[0].point_coordinate[0]=122;               //Բ��x����
TKS231_1_II_levels[7].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[7].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[7].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z8
TKS231_1_II_levels[8].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS231_1_II_levels[8].contacts[0].channel=1;
TKS231_1_II_levels[8].contacts[0].point_coordinate[0]=134;               //Բ��x����
TKS231_1_II_levels[8].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[8].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[8].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z9
TKS231_1_II_levels[9].contacts[0].flag_last=1;
TKS231_1_II_levels[9].contacts[0].channel=1;
TKS231_1_II_levels[9].contacts[0].point_coordinate[0]=146;               //Բ��x����
TKS231_1_II_levels[9].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[9].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[9].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z10
TKS231_1_II_levels[10].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS231_1_II_levels[10].contacts[0].channel=1;
TKS231_1_II_levels[10].contacts[0].point_coordinate[0]=158;               //Բ��x����
TKS231_1_II_levels[10].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[10].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[10].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z11
TKS231_1_II_levels[11].contacts[0].flag_last=1;
TKS231_1_II_levels[11].contacts[0].channel=1;
TKS231_1_II_levels[11].contacts[0].point_coordinate[0]=170;               //Բ��x����
TKS231_1_II_levels[11].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[11].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[11].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z12
TKS231_1_II_levels[12].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS231_1_II_levels[12].contacts[0].channel=1;
TKS231_1_II_levels[12].contacts[0].point_coordinate[0]=182;               //Բ��x����
TKS231_1_II_levels[12].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[12].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[12].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z13
TKS231_1_II_levels[13].contacts[0].flag_last=1;
TKS231_1_II_levels[13].contacts[0].channel=1;
TKS231_1_II_levels[13].contacts[0].point_coordinate[0]=194;               //Բ��x����
TKS231_1_II_levels[13].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[13].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[13].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z14
TKS231_1_II_levels[14].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS231_1_II_levels[14].contacts[0].channel=1;
TKS231_1_II_levels[14].contacts[0].point_coordinate[0]=206;               //Բ��x����
TKS231_1_II_levels[14].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[14].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[14].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z15
TKS231_1_II_levels[15].contacts[0].flag_last=1;
TKS231_1_II_levels[15].contacts[0].channel=1;
TKS231_1_II_levels[15].contacts[0].point_coordinate[0]=218;               //Բ��x����
TKS231_1_II_levels[15].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[15].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[15].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z16
TKS231_1_II_levels[16].contacts[0].flag_last=1;
TKS231_1_II_levels[16].contacts[0].channel=1;
TKS231_1_II_levels[16].contacts[0].point_coordinate[0]=230;               //Բ��x����
TKS231_1_II_levels[16].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[16].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[16].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z17
TKS231_1_II_levels[17].contacts[0].flag_last=1;
TKS231_1_II_levels[17].contacts[0].channel=1;
TKS231_1_II_levels[17].contacts[0].point_coordinate[0]=242;               //Բ��x����
TKS231_1_II_levels[17].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[17].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[17].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//z18
TKS231_1_II_levels[18].contacts[0].flag_last=1;
TKS231_1_II_levels[18].contacts[0].channel=1;
TKS231_1_II_levels[18].contacts[0].point_coordinate[0]=254;               //Բ��x����
TKS231_1_II_levels[18].contacts[0].point_coordinate[1]=42;               //Բ��y����
TKS231_1_II_levels[18].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[18].contacts[0].value_coordinate[1]=36;               //��ʾ��ʼy����
//q0
TKS231_1_II_levels[19].contacts[0].flag_last=0;
TKS231_1_II_levels[19].contacts[0].channel=0;
TKS231_1_II_levels[19].contacts[0].point_coordinate[0]=38;               //Բ��x����
TKS231_1_II_levels[19].contacts[0].point_coordinate[1]=66;               //Բ��y����
TKS231_1_II_levels[19].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[19].contacts[0].value_coordinate[1]=60;               //��ʾ��ʼy����

TKS231_1_II_levels[19].contacts[1].flag_last=1;
TKS231_1_II_levels[19].contacts[1].channel=1;
TKS231_1_II_levels[19].contacts[1].point_coordinate[0]=38;               //Բ��x����
TKS231_1_II_levels[19].contacts[1].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[19].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[19].contacts[1].value_coordinate[1]=72;               //��ʾ��ʼy����
//q1
TKS231_1_II_levels[20].contacts[0].flag_last=0;
TKS231_1_II_levels[20].contacts[0].channel=0;
TKS231_1_II_levels[20].contacts[0].point_coordinate[0]=50;               //Բ��x����
TKS231_1_II_levels[20].contacts[0].point_coordinate[1]=66;               //Բ��y����
TKS231_1_II_levels[20].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[20].contacts[0].value_coordinate[1]=60;               //��ʾ��ʼy����

TKS231_1_II_levels[20].contacts[1].flag_last=1;
TKS231_1_II_levels[20].contacts[1].channel=1;
TKS231_1_II_levels[20].contacts[1].point_coordinate[0]=50;               //Բ��x����
TKS231_1_II_levels[20].contacts[1].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[20].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[20].contacts[1].value_coordinate[1]=72;               //��ʾ��ʼy����
//q2
TKS231_1_II_levels[21].contacts[0].flag_last=0;
TKS231_1_II_levels[21].contacts[0].channel=0;
TKS231_1_II_levels[21].contacts[0].point_coordinate[0]=62;               //Բ��x����
TKS231_1_II_levels[21].contacts[0].point_coordinate[1]=66;               //Բ��y����
TKS231_1_II_levels[21].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[21].contacts[0].value_coordinate[1]=60;               //��ʾ��ʼy����

TKS231_1_II_levels[21].contacts[1].flag_last=1;
TKS231_1_II_levels[21].contacts[1].channel=1;
TKS231_1_II_levels[21].contacts[1].point_coordinate[0]=62;               //Բ��x����
TKS231_1_II_levels[21].contacts[1].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[21].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[21].contacts[1].value_coordinate[1]=72;               //��ʾ��ʼy����
//q3
TKS231_1_II_levels[22].contacts[0].flag_last=0;
TKS231_1_II_levels[22].contacts[0].channel=0;
TKS231_1_II_levels[22].contacts[0].point_coordinate[0]=74;               //Բ��x����
TKS231_1_II_levels[22].contacts[0].point_coordinate[1]=66;               //Բ��y����
TKS231_1_II_levels[22].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[22].contacts[0].value_coordinate[1]=60;               //��ʾ��ʼy����

TKS231_1_II_levels[22].contacts[1].flag_last=1;
TKS231_1_II_levels[22].contacts[1].channel=1;
TKS231_1_II_levels[22].contacts[1].point_coordinate[0]=74;               //Բ��x����
TKS231_1_II_levels[22].contacts[1].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[22].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[22].contacts[1].value_coordinate[1]=72;               //��ʾ��ʼy����
//q4
TKS231_1_II_levels[23].contacts[0].flag_last=1;
TKS231_1_II_levels[23].contacts[0].channel=1;
TKS231_1_II_levels[23].contacts[0].point_coordinate[0]=86;               //Բ��x����
TKS231_1_II_levels[23].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[23].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[23].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q5
TKS231_1_II_levels[24].contacts[0].flag_last=1;
TKS231_1_II_levels[24].contacts[0].channel=1;
TKS231_1_II_levels[24].contacts[0].point_coordinate[0]=98;               //Բ��x����
TKS231_1_II_levels[24].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[24].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[24].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q6
TKS231_1_II_levels[25].contacts[0].flag_last=1;
TKS231_1_II_levels[25].contacts[0].channel=1;
TKS231_1_II_levels[25].contacts[0].point_coordinate[0]=110;               //Բ��x����
TKS231_1_II_levels[25].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[25].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[25].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q7
TKS231_1_II_levels[26].contacts[0].flag_last=1;
TKS231_1_II_levels[26].contacts[0].channel=1;
TKS231_1_II_levels[26].contacts[0].point_coordinate[0]=122;               //Բ��x����
TKS231_1_II_levels[26].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[26].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[26].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q8
TKS231_1_II_levels[27].contacts[0].flag_last=1;
TKS231_1_II_levels[27].contacts[0].channel=1;
TKS231_1_II_levels[27].contacts[0].point_coordinate[0]=134;               //Բ��x����
TKS231_1_II_levels[27].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[27].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[27].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q9
TKS231_1_II_levels[28].contacts[0].flag_last=1;
TKS231_1_II_levels[28].contacts[0].channel=1;
TKS231_1_II_levels[28].contacts[0].point_coordinate[0]=146;               //Բ��x����
TKS231_1_II_levels[28].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[28].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[28].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q10
TKS231_1_II_levels[29].contacts[0].flag_last=1;
TKS231_1_II_levels[29].contacts[0].channel=1;
TKS231_1_II_levels[29].contacts[0].point_coordinate[0]=158;               //Բ��x����
TKS231_1_II_levels[29].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[29].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[29].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q11
TKS231_1_II_levels[30].contacts[0].flag_last=1;
TKS231_1_II_levels[30].contacts[0].channel=1;
TKS231_1_II_levels[30].contacts[0].point_coordinate[0]=170;               //Բ��x����
TKS231_1_II_levels[30].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[30].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[30].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q12
TKS231_1_II_levels[31].contacts[0].flag_last=1;
TKS231_1_II_levels[31].contacts[0].channel=1;
TKS231_1_II_levels[31].contacts[0].point_coordinate[0]=182;               //Բ��x����
TKS231_1_II_levels[31].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[31].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[31].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q13
TKS231_1_II_levels[32].contacts[0].flag_last=1;
TKS231_1_II_levels[32].contacts[0].channel=1;
TKS231_1_II_levels[32].contacts[0].point_coordinate[0]=194;               //Բ��x����
TKS231_1_II_levels[32].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[32].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[32].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q14
TKS231_1_II_levels[33].contacts[0].flag_last=1;
TKS231_1_II_levels[33].contacts[0].channel=1;
TKS231_1_II_levels[33].contacts[0].point_coordinate[0]=206;               //Բ��x����
TKS231_1_II_levels[33].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[33].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[33].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q15
TKS231_1_II_levels[34].contacts[0].flag_last=1;
TKS231_1_II_levels[34].contacts[0].channel=1;
TKS231_1_II_levels[34].contacts[0].point_coordinate[0]=218;               //Բ��x����
TKS231_1_II_levels[34].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[34].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[34].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q16
TKS231_1_II_levels[35].contacts[0].flag_last=1;
TKS231_1_II_levels[35].contacts[0].channel=1;
TKS231_1_II_levels[35].contacts[0].point_coordinate[0]=230;               //Բ��x����
TKS231_1_II_levels[35].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[35].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[35].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q17
TKS231_1_II_levels[36].contacts[0].flag_last=1;
TKS231_1_II_levels[36].contacts[0].channel=1;
TKS231_1_II_levels[36].contacts[0].point_coordinate[0]=242;               //Բ��x����
TKS231_1_II_levels[36].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[36].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[36].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//q18
TKS231_1_II_levels[37].contacts[0].flag_last=1;
TKS231_1_II_levels[37].contacts[0].channel=1;
TKS231_1_II_levels[37].contacts[0].point_coordinate[0]=254;               //Բ��x����
TKS231_1_II_levels[37].contacts[0].point_coordinate[1]=78;               //Բ��y����
TKS231_1_II_levels[37].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS231_1_II_levels[37].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����
//��
TKS231_1_II_levels[38].contacts[0].flag_last=0;
TKS231_1_II_levels[38].contacts[0].channel=2;
TKS231_1_II_levels[38].contacts[0].point_coordinate[0]=30;               //Բ��x����
TKS231_1_II_levels[38].contacts[0].point_coordinate[1]=126;               //Բ��y����
TKS231_1_II_levels[38].contacts[0].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[38].contacts[0].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS231_1_II_levels[38].contacts[1].flag_last=0;
TKS231_1_II_levels[38].contacts[1].channel=3;
TKS231_1_II_levels[38].contacts[1].point_coordinate[0]=30;               //Բ��x����
TKS231_1_II_levels[38].contacts[1].point_coordinate[1]=138;               //Բ��y����
TKS231_1_II_levels[38].contacts[1].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[38].contacts[1].value_coordinate[1]=132;               //��ʾ��ʼy����

TKS231_1_II_levels[38].contacts[2].flag_last=1;
TKS231_1_II_levels[38].contacts[2].channel=6;
TKS231_1_II_levels[38].contacts[2].point_coordinate[0]=30;               //Բ��x����
TKS231_1_II_levels[38].contacts[2].point_coordinate[1]=174;               //Բ��y����
TKS231_1_II_levels[38].contacts[2].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[38].contacts[2].value_coordinate[1]=168;               //��ʾ��ʼy����
//��
//ǰ
TKS231_1_II_levels[39].contacts[0].flag_last=0;
TKS231_1_II_levels[39].contacts[0].channel=2;
TKS231_1_II_levels[39].contacts[0].point_coordinate[0]=66;               //Բ��x����
TKS231_1_II_levels[39].contacts[0].point_coordinate[1]=126;               //Բ��y����
TKS231_1_II_levels[39].contacts[0].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[39].contacts[0].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS231_1_II_levels[39].contacts[1].flag_last=0;
TKS231_1_II_levels[39].contacts[1].channel=4;
TKS231_1_II_levels[39].contacts[1].point_coordinate[0]=66;               //Բ��x����
TKS231_1_II_levels[39].contacts[1].point_coordinate[1]=150;               //Բ��y����
TKS231_1_II_levels[39].contacts[1].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[39].contacts[1].value_coordinate[1]=144;               //��ʾ��ʼy����

TKS231_1_II_levels[39].contacts[2].flag_last=1;
TKS231_1_II_levels[39].contacts[2].channel=6;
TKS231_1_II_levels[39].contacts[2].point_coordinate[0]=66;               //Բ��x����
TKS231_1_II_levels[39].contacts[2].point_coordinate[1]=174;               //Բ��y����
TKS231_1_II_levels[39].contacts[2].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[39].contacts[2].value_coordinate[1]=168;               //��ʾ��ʼy����
//��
TKS231_1_II_levels[40].contacts[0].flag_last=0;
TKS231_1_II_levels[40].contacts[0].channel=2;
TKS231_1_II_levels[40].contacts[0].point_coordinate[0]=84;               //Բ��x����
TKS231_1_II_levels[40].contacts[0].point_coordinate[1]=126;               //Բ��y����
TKS231_1_II_levels[40].contacts[0].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[40].contacts[0].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS231_1_II_levels[40].contacts[1].flag_last=0;
TKS231_1_II_levels[40].contacts[1].channel=4;
TKS231_1_II_levels[40].contacts[1].point_coordinate[0]=84;               //Բ��x����
TKS231_1_II_levels[40].contacts[1].point_coordinate[1]=150;               //Բ��y����
TKS231_1_II_levels[40].contacts[1].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[40].contacts[1].value_coordinate[1]=144;               //��ʾ��ʼy����

TKS231_1_II_levels[40].contacts[2].flag_last=1;
TKS231_1_II_levels[40].contacts[2].channel=5;
TKS231_1_II_levels[40].contacts[2].point_coordinate[0]=84;               //Բ��x����
TKS231_1_II_levels[40].contacts[2].point_coordinate[1]=162;               //Բ��y����
TKS231_1_II_levels[40].contacts[2].value_coordinate[0]=120;               //��ʾ��ʼx����
TKS231_1_II_levels[40].contacts[2].value_coordinate[1]=156;               //��ʾ��ʼy����

}





void measure_TKS231_1_II(int x,int y)
{
  unsigned char n;
     for(n=0;n<42;n++)
     {
       if(x>TKS231_1_II_TP[n][0]&&x<TKS231_1_II_TP[n][2]&&y>TKS231_1_II_TP[n][1]&&y<TKS231_1_II_TP[n][3])
       {
         GUI_Rectangle(TKS231_1_II_TP[n][0],TKS231_1_II_TP[n][1],TKS231_1_II_TP[n][2],TKS231_1_II_TP[n][3],Black,0);
         measure_TKS231_1_II_level(n);
       }
     }
}


void measure_TKS231_1_II_level(unsigned char n)
{
  unsigned char i=0,j=0,k=0;
  unsigned char *p;
  for(k=0;k<5;k++)
  {
      if(TKS231_1_II_levels[n].contacts[i].flag_last==0)
      {
        Set_Channel_TKS231_1_II(TKS231_1_II_levels[n].contacts[i].channel);
        CD4067_EN;
//        printf("%d",TKS231_1_II_levels[n].contacts[i].channel);
        delay_long();
        p=Get_ADC1_Value();
        for(j=0;j<6;j++)
        {
          TKS231_1_II_levels[n].contacts[i].R[j]=*(p+j);
        }
//        printf(ADC_Value);
        if(TKS231_1_II_levels[n].contacts[i].R[0]=='0')
        {
          GUI_Circle(TKS231_1_II_levels[n].contacts[i].point_coordinate[0],TKS231_1_II_levels[n].contacts[i].point_coordinate[1],4,Green,0x01);
        }
        else
        {
          GUI_Circle(TKS231_1_II_levels[n].contacts[i].point_coordinate[0],TKS231_1_II_levels[n].contacts[i].point_coordinate[1],4,Red,0x01);
        }
        ili9320_writestr12(TKS231_1_II_levels[n].contacts[i].value_coordinate[0], TKS231_1_II_levels[n].contacts[i].value_coordinate[1],TKS231_1_II_levels[n].contacts[i].R,Cyan, Black);
      i++;
      }
      if(TKS231_1_II_levels[n].contacts[i].flag_last==1)
      {
        Set_Channel_TKS231_1_II(TKS231_1_II_levels[n].contacts[i].channel);
        CD4067_EN;
//        printf("%d",TKS231_1_II_levels[n].contacts[i].channel);
        delay_long();
        p=Get_ADC1_Value();
        for(j=0;j<6;j++)
        {
          TKS231_1_II_levels[n].contacts[i].R[j]=*(p+j);
        }
//        printf(ADC_Value);
        for(j=0;j<6;j++)
        {
          TKS231_1_II_levels[n].level_V[j]=*(p+j+6);
        }
        ili9320_writestr12(54, 227,TKS231_1_II_levels[n].level_V,Cyan, Black);
        if(TKS231_1_II_levels[n].contacts[i].R[0]=='0')
        {
          GUI_Circle(TKS231_1_II_levels[n].contacts[i].point_coordinate[0],TKS231_1_II_levels[n].contacts[i].point_coordinate[1],4,Green,0x01);
        }
        else
        {
          GUI_Circle(TKS231_1_II_levels[n].contacts[i].point_coordinate[0],TKS231_1_II_levels[n].contacts[i].point_coordinate[1],4,Red,0x01);
        }
        ili9320_writestr12(TKS231_1_II_levels[n].contacts[i].value_coordinate[0], TKS231_1_II_levels[n].contacts[i].value_coordinate[1],TKS231_1_II_levels[n].contacts[i].R,Cyan, Black);
      CD4067_DIS;
      }
  }
}

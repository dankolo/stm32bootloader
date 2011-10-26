#include "TKS15A_I.h"
#include "ili9320.h"
unsigned char Channel_TKS15A_II[7]={0,1,2,3,4,5,6};//ɨ��ͨ��

struct level TKS15A_I_levels[12];//12����λ:4-0ȡȡ0-4

unsigned int TKS15A_I_TP[12][4]=
{ 
  {36,31,52,47},{52,31,68,47},{68,31,84,47},{84,31,100,47},
  {100,31,116,47},{116,31,132,47},{132,31,148,47},{148,31,164,47},
  {164,31,180,47},{180,31,196,47},{196,31,212,47},{212,31,228,47}
};

void Set_Channel_TKS15A_I(unsigned char x)
{
  if((Channel_TKS15A_II[x]>>3)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_2);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_2);}
    if(((Channel_TKS15A_II[x]&0x04)>>2)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_3);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_3);}
    if(((Channel_TKS15A_II[x]&0x02)>>1)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_4);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_4);}
   if((Channel_TKS15A_II[x]&0x01)==0)
  {GPIO_ResetBits(GPIOD,GPIO_Pin_7);}
  else
  {GPIO_SetBits(GPIOD,GPIO_Pin_7);}
}



void draw_TKS15A_I()
{
  int n;
  ili9320_Clear(Black);
  ili9320_PutCN(72,16,"��ǰ",Cyan,Black);
  ili9320_PutCN(160,16,"���",Cyan,Black);
  ili9320_PutCN(124,16,"ȡ",Cyan,Black);
  ili9320_writestr(96,0,"TKS15A-I",Cyan,Black);
  ili9320_writestr(32,32," 4 3 2 1 0 Q Q 0 1 2 3 4",Cyan,Black);
  ili9320_writestr(8,56,"412",Cyan,Black);
  ili9320_writestr(8,72,"401",Cyan,Black);
  ili9320_writestr(8,88,"401",Cyan,Black);
  ili9320_writestr(8,104,"401",Cyan,Black);
  ili9320_writestr(8,120,"401",Cyan,Black);
  ili9320_writestr(8,136,"577",Cyan,Black);
  ili9320_writestr(8,152,"577",Cyan,Black);
  ili9320_writestr(232,56,"413/1",Cyan,Black);
  ili9320_writestr(232,72,"404/3",Cyan,Black);
  ili9320_writestr(232,88,"403/4",Cyan,Black);
  ili9320_writestr(232,104,"406",Cyan,Black);
  ili9320_writestr(232,120,"415",Cyan,Black);
  ili9320_writestr(232,136,"416",Cyan,Black);
  ili9320_writestr(232,152,"417",Cyan,Black);
  ili9320_PutCN12(284,34,"��ֵoo",Cyan,Black);
  for(n=0;n<7;n++)
  {
    GUI_Line(32,64+16*n,228,64+16*n,Blue2);
  }
  for(n=0;n<12;n++)
  {
    GUI_Line(44+16*n,48,44+16*n,176,Blue2);
  }
  for(n=0;n<12;n++)
  {
    GUI_Rectangle(36+16*n,31,52+16*n,47,Blue2,0);
  }
   unsigned char points[]=
  {
                                108,64, 124,64, 140,64, 156,64,
44,80,  60,80,  76,80,  92,80,  108,80,
                                                        156,96, 172,96, 188,96, 204,96, 220,96,
44,112, 60,112, 76,112, 92,112, 108,112,                156,112,172,112,188,112,204,112,220,112,
44,128, 60,128, 76,128, 92,128, 108,128,                156,128,172,128,188,128,204,128,220,128,
                        92,144, 108,144,                156,144,172,144,
44,160,	60,160,	76,160,                                                 188,160,204,160,220,160,
0xff
  };
  n=0;
  while(points[n]!=0xff)
  {
    GUI_Circle(points[n],points[n+1],4,Blue,0x01);
    n+=2;
  }

}


void measure_TKS15A_I(int x,int y)
{
  unsigned char n;
     for(n=0;n<12;n++)
     {
       if(x>TKS15A_I_TP[n][0]&&x<TKS15A_I_TP[n][2]&&y>TKS15A_I_TP[n][1]&&y<TKS15A_I_TP[n][3])
       {
         GUI_Rectangle(TKS15A_I_TP[n][0],TKS15A_I_TP[n][1],TKS15A_I_TP[n][2],TKS15A_I_TP[n][3],Black,0);
         measure_TKS15A_I_level(n);
       }  
     }
}


void measure_TKS15A_I_level(unsigned char n)
{
  unsigned char i=0,j=0,k=0;
  unsigned char *p;
  for(k=0;k<5;k++)
  {
      if(TKS15A_I_levels[n].contacts[i].flag_last==0)
      {
        Set_Channel_TKS15A_I(TKS15A_I_levels[n].contacts[i].channel);
        CD4067_EN;
//        printf("%d",TKS15A_I_levels[n].contacts[i].channel);
        delay_long();        
        p=Get_ADC1_Value();
        for(j=0;j<6;j++)
        {
          TKS15A_I_levels[n].contacts[i].R[j]=*(p+j);
        }
//        printf(ADC_Value);
        if(TKS15A_I_levels[n].contacts[i].R[0]=='0')
        {
          GUI_Circle(TKS15A_I_levels[n].contacts[i].point_coordinate[0],TKS15A_I_levels[n].contacts[i].point_coordinate[1],4,Green,0x01);
        }
        else
        {
          GUI_Circle(TKS15A_I_levels[n].contacts[i].point_coordinate[0],TKS15A_I_levels[n].contacts[i].point_coordinate[1],4,Red,0x01);
        }
        ili9320_writestr12(TKS15A_I_levels[n].contacts[i].value_coordinate[0], TKS15A_I_levels[n].contacts[i].value_coordinate[1],TKS15A_I_levels[n].contacts[i].R,Cyan, Black);
      i++;
      }
      if(TKS15A_I_levels[n].contacts[i].flag_last==1)
      {
        Set_Channel_TKS15A_I(TKS15A_I_levels[n].contacts[i].channel);
        CD4067_EN;
//        printf("%d",TKS15A_I_levels[n].contacts[i].channel);
        delay_long();
        p=Get_ADC1_Value();
        for(j=0;j<6;j++)
        {
          TKS15A_I_levels[n].contacts[i].R[j]=*(p+j);
        }
//        printf(ADC_Value);
        for(j=0;j<6;j++)
        {
          TKS15A_I_levels[n].level_V[j]=*(p+j+6);
        }
        ili9320_writestr12(54, 227,TKS15A_I_levels[n].level_V,Cyan, Black);
        if(TKS15A_I_levels[n].contacts[i].R[0]=='0')
        {
          GUI_Circle(TKS15A_I_levels[n].contacts[i].point_coordinate[0],TKS15A_I_levels[n].contacts[i].point_coordinate[1],4,Green,0x01);
        }
        else
        {
          GUI_Circle(TKS15A_I_levels[n].contacts[i].point_coordinate[0],TKS15A_I_levels[n].contacts[i].point_coordinate[1],4,Red,0x01);
        }
        ili9320_writestr12(TKS15A_I_levels[n].contacts[i].value_coordinate[0], TKS15A_I_levels[n].contacts[i].value_coordinate[1],TKS15A_I_levels[n].contacts[i].R,Cyan, Black);
      CD4067_DIS;
      }
 
  }
}


void TKS15A_I_table()
{
//-4  
TKS15A_I_levels[0].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[0].contacts[0].channel=1;
TKS15A_I_levels[0].contacts[0].point_coordinate[0]=44;               //Բ��x����
TKS15A_I_levels[0].contacts[0].point_coordinate[1]=80;               //Բ��y����
TKS15A_I_levels[0].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[0].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����

TKS15A_I_levels[0].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[0].contacts[1].channel=3;
TKS15A_I_levels[0].contacts[1].point_coordinate[0]=44;               //Բ��x����
TKS15A_I_levels[0].contacts[1].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[0].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[0].contacts[1].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[0].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[0].contacts[2].channel=4;
TKS15A_I_levels[0].contacts[2].point_coordinate[0]=44;               //Բ��x����
TKS15A_I_levels[0].contacts[2].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[0].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[0].contacts[2].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[0].contacts[3].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[0].contacts[3].channel=6;
TKS15A_I_levels[0].contacts[3].point_coordinate[0]=44;               //Բ��x����
TKS15A_I_levels[0].contacts[3].point_coordinate[1]=160;               //Բ��y����
TKS15A_I_levels[0].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[0].contacts[3].value_coordinate[1]=152;               //��ʾ��ʼy����
//-3
TKS15A_I_levels[1].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[1].contacts[0].channel=1;
TKS15A_I_levels[1].contacts[0].point_coordinate[0]=60;               //Բ��x����
TKS15A_I_levels[1].contacts[0].point_coordinate[1]=80;               //Բ��y����
TKS15A_I_levels[1].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[1].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����

TKS15A_I_levels[1].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[1].contacts[1].channel=3;
TKS15A_I_levels[1].contacts[1].point_coordinate[0]=60;               //Բ��x����
TKS15A_I_levels[1].contacts[1].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[1].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[1].contacts[1].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[1].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[1].contacts[2].channel=4;
TKS15A_I_levels[1].contacts[2].point_coordinate[0]=60;               //Բ��x����
TKS15A_I_levels[1].contacts[2].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[1].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[1].contacts[2].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[1].contacts[3].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[1].contacts[3].channel=6;
TKS15A_I_levels[1].contacts[3].point_coordinate[0]=60;               //Բ��x����
TKS15A_I_levels[1].contacts[3].point_coordinate[1]=160;               //Բ��y����
TKS15A_I_levels[1].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[1].contacts[3].value_coordinate[1]=152;               //��ʾ��ʼy����
//-2
TKS15A_I_levels[2].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[2].contacts[0].channel=1;
TKS15A_I_levels[2].contacts[0].point_coordinate[0]=76;               //Բ��x����
TKS15A_I_levels[2].contacts[0].point_coordinate[1]=80;               //Բ��y����
TKS15A_I_levels[2].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[2].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����

TKS15A_I_levels[2].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[2].contacts[1].channel=3;
TKS15A_I_levels[2].contacts[1].point_coordinate[0]=76;               //Բ��x����
TKS15A_I_levels[2].contacts[1].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[2].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[2].contacts[1].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[2].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[2].contacts[2].channel=4;
TKS15A_I_levels[2].contacts[2].point_coordinate[0]=76;               //Բ��x����
TKS15A_I_levels[2].contacts[2].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[2].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[2].contacts[2].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[2].contacts[3].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[2].contacts[3].channel=6;
TKS15A_I_levels[2].contacts[3].point_coordinate[0]=76;               //Բ��x����
TKS15A_I_levels[2].contacts[3].point_coordinate[1]=160;               //Բ��y����
TKS15A_I_levels[2].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[2].contacts[3].value_coordinate[1]=152;               //��ʾ��ʼy����
//-1
TKS15A_I_levels[3].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[3].contacts[0].channel=1;
TKS15A_I_levels[3].contacts[0].point_coordinate[0]=92;               //Բ��x����
TKS15A_I_levels[3].contacts[0].point_coordinate[1]=80;               //Բ��y����
TKS15A_I_levels[3].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[3].contacts[0].value_coordinate[1]=72;               //��ʾ��ʼy����

TKS15A_I_levels[3].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[3].contacts[1].channel=3;
TKS15A_I_levels[3].contacts[1].point_coordinate[0]=92;               //Բ��x����
TKS15A_I_levels[3].contacts[1].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[3].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[3].contacts[1].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[3].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[3].contacts[2].channel=4;
TKS15A_I_levels[3].contacts[2].point_coordinate[0]=92;               //Բ��x����
TKS15A_I_levels[3].contacts[2].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[3].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[3].contacts[2].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[3].contacts[3].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[3].contacts[3].channel=6;
TKS15A_I_levels[3].contacts[3].point_coordinate[0]=92;               //Բ��x����
TKS15A_I_levels[3].contacts[3].point_coordinate[1]=144;               //Բ��y����
TKS15A_I_levels[3].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[3].contacts[3].value_coordinate[1]=136;               //��ʾ��ʼy����
//-0
TKS15A_I_levels[4].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[4].contacts[0].channel=0;
TKS15A_I_levels[4].contacts[0].point_coordinate[0]=108;               //Բ��x����
TKS15A_I_levels[4].contacts[0].point_coordinate[1]=64;               //Բ��y����
TKS15A_I_levels[4].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[4].contacts[0].value_coordinate[1]=56;               //��ʾ��ʼy����

TKS15A_I_levels[4].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[4].contacts[1].channel=1;
TKS15A_I_levels[4].contacts[1].point_coordinate[0]=108;               //Բ��x����
TKS15A_I_levels[4].contacts[1].point_coordinate[1]=80;               //Բ��y����
TKS15A_I_levels[4].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[4].contacts[1].value_coordinate[1]=72;               //��ʾ��ʼy����

TKS15A_I_levels[4].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[4].contacts[2].channel=3;
TKS15A_I_levels[4].contacts[2].point_coordinate[0]=108;               //Բ��x����
TKS15A_I_levels[4].contacts[2].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[4].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[4].contacts[2].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[4].contacts[3].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[4].contacts[3].channel=4;
TKS15A_I_levels[4].contacts[3].point_coordinate[0]=108;               //Բ��x����
TKS15A_I_levels[4].contacts[3].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[4].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[4].contacts[3].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[4].contacts[4].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[4].contacts[4].channel=5;
TKS15A_I_levels[4].contacts[4].point_coordinate[0]=108;               //Բ��x����
TKS15A_I_levels[4].contacts[4].point_coordinate[1]=144;               //Բ��y����
TKS15A_I_levels[4].contacts[4].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[4].contacts[4].value_coordinate[1]=136;               //��ʾ��ʼy����
//Q1
TKS15A_I_levels[5].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[5].contacts[0].channel=0;
TKS15A_I_levels[5].contacts[0].point_coordinate[0]=124;               //Բ��x����
TKS15A_I_levels[5].contacts[0].point_coordinate[1]=64;               //Բ��y����
TKS15A_I_levels[5].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[5].contacts[0].value_coordinate[1]=56;               //��ʾ��ʼy����
//Q2
TKS15A_I_levels[6].contacts[0].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[6].contacts[0].channel=0;
TKS15A_I_levels[6].contacts[0].point_coordinate[0]=140;               //Բ��x����
TKS15A_I_levels[6].contacts[0].point_coordinate[1]=64;               //Բ��y����
TKS15A_I_levels[6].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[6].contacts[0].value_coordinate[1]=56;              //��ʾ��ʼy����
//+0
TKS15A_I_levels[7].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[7].contacts[0].channel=0;
TKS15A_I_levels[7].contacts[0].point_coordinate[0]=156;               //Բ��x����
TKS15A_I_levels[7].contacts[0].point_coordinate[1]=64;               //Բ��y����
TKS15A_I_levels[7].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[7].contacts[0].value_coordinate[1]=56;               //��ʾ��ʼy����

TKS15A_I_levels[7].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[7].contacts[1].channel=2;
TKS15A_I_levels[7].contacts[1].point_coordinate[0]=156;               //Բ��x����
TKS15A_I_levels[7].contacts[1].point_coordinate[1]=96;               //Բ��y����
TKS15A_I_levels[7].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[7].contacts[1].value_coordinate[1]=88;               //��ʾ��ʼy����

TKS15A_I_levels[7].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[7].contacts[2].channel=3;
TKS15A_I_levels[7].contacts[2].point_coordinate[0]=156;               //Բ��x����
TKS15A_I_levels[7].contacts[2].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[7].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[7].contacts[2].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[7].contacts[3].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[7].contacts[3].channel=4;
TKS15A_I_levels[7].contacts[3].point_coordinate[0]=156;               //Բ��x����
TKS15A_I_levels[7].contacts[3].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[7].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[7].contacts[3].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[7].contacts[4].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[7].contacts[4].channel=5;
TKS15A_I_levels[7].contacts[4].point_coordinate[0]=156;               //Բ��x����
TKS15A_I_levels[7].contacts[4].point_coordinate[1]=144;               //Բ��y����
TKS15A_I_levels[7].contacts[4].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[7].contacts[4].value_coordinate[1]=136;               //��ʾ��ʼy����
//+1
TKS15A_I_levels[8].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[8].contacts[0].channel=2;
TKS15A_I_levels[8].contacts[0].point_coordinate[0]=172;               //Բ��x����
TKS15A_I_levels[8].contacts[0].point_coordinate[1]=96;               //Բ��y����
TKS15A_I_levels[8].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[8].contacts[0].value_coordinate[1]=88;               //��ʾ��ʼy����

TKS15A_I_levels[8].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[8].contacts[1].channel=3;
TKS15A_I_levels[8].contacts[1].point_coordinate[0]=172;               //Բ��x����
TKS15A_I_levels[8].contacts[1].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[8].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[8].contacts[1].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[8].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[8].contacts[2].channel=4;
TKS15A_I_levels[8].contacts[2].point_coordinate[0]=172;               //Բ��x����
TKS15A_I_levels[8].contacts[2].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[8].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[8].contacts[2].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[8].contacts[3].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[8].contacts[3].channel=5;
TKS15A_I_levels[8].contacts[3].point_coordinate[0]=172;               //Բ��x����
TKS15A_I_levels[8].contacts[3].point_coordinate[1]=144;               //Բ��y����
TKS15A_I_levels[8].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[8].contacts[3].value_coordinate[1]=136;               //��ʾ��ʼy����
//+2
TKS15A_I_levels[9].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[9].contacts[0].channel=2;
TKS15A_I_levels[9].contacts[0].point_coordinate[0]=188;               //Բ��x����
TKS15A_I_levels[9].contacts[0].point_coordinate[1]=96;               //Բ��y����
TKS15A_I_levels[9].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[9].contacts[0].value_coordinate[1]=88;               //��ʾ��ʼy����

TKS15A_I_levels[9].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[9].contacts[1].channel=3;
TKS15A_I_levels[9].contacts[1].point_coordinate[0]=188;               //Բ��x����
TKS15A_I_levels[9].contacts[1].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[9].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[9].contacts[1].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[9].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[9].contacts[2].channel=4;
TKS15A_I_levels[9].contacts[2].point_coordinate[0]=188;               //Բ��x����
TKS15A_I_levels[9].contacts[2].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[9].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[9].contacts[2].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[9].contacts[3].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[9].contacts[3].channel=6;
TKS15A_I_levels[9].contacts[3].point_coordinate[0]=188;               //Բ��x����
TKS15A_I_levels[9].contacts[3].point_coordinate[1]=160;               //Բ��y����
TKS15A_I_levels[9].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[9].contacts[3].value_coordinate[1]=152;               //��ʾ��ʼy����
//+3
TKS15A_I_levels[10].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[10].contacts[0].channel=2;
TKS15A_I_levels[10].contacts[0].point_coordinate[0]=204;               //Բ��x����
TKS15A_I_levels[10].contacts[0].point_coordinate[1]=96;               //Բ��y����
TKS15A_I_levels[10].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[10].contacts[0].value_coordinate[1]=88;               //��ʾ��ʼy����

TKS15A_I_levels[10].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[10].contacts[1].channel=3;
TKS15A_I_levels[10].contacts[1].point_coordinate[0]=204;               //Բ��x����
TKS15A_I_levels[10].contacts[1].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[10].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[10].contacts[1].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[10].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[10].contacts[2].channel=4;
TKS15A_I_levels[10].contacts[2].point_coordinate[0]=204;               //Բ��x����
TKS15A_I_levels[10].contacts[2].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[10].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[10].contacts[2].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[10].contacts[3].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[10].contacts[3].channel=6;
TKS15A_I_levels[10].contacts[3].point_coordinate[0]=204;               //Բ��x����
TKS15A_I_levels[10].contacts[3].point_coordinate[1]=160;               //Բ��y����
TKS15A_I_levels[10].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[10].contacts[3].value_coordinate[1]=152;               //��ʾ��ʼy����
//+4
TKS15A_I_levels[11].contacts[0].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[11].contacts[0].channel=2;
TKS15A_I_levels[11].contacts[0].point_coordinate[0]=220;               //Բ��x����
TKS15A_I_levels[11].contacts[0].point_coordinate[1]=96;               //Բ��y����
TKS15A_I_levels[11].contacts[0].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[11].contacts[0].value_coordinate[1]=88;               //��ʾ��ʼy����

TKS15A_I_levels[11].contacts[1].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[11].contacts[1].channel=3;
TKS15A_I_levels[11].contacts[1].point_coordinate[0]=220;               //Բ��x����
TKS15A_I_levels[11].contacts[1].point_coordinate[1]=112;               //Բ��y����
TKS15A_I_levels[11].contacts[1].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[11].contacts[1].value_coordinate[1]=104;               //��ʾ��ʼy����

TKS15A_I_levels[11].contacts[2].flag_last=0;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[11].contacts[2].channel=4;
TKS15A_I_levels[11].contacts[2].point_coordinate[0]=220;               //Բ��x����
TKS15A_I_levels[11].contacts[2].point_coordinate[1]=128;               //Բ��y����
TKS15A_I_levels[11].contacts[2].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[11].contacts[2].value_coordinate[1]=120;               //��ʾ��ʼy����

TKS15A_I_levels[11].contacts[3].flag_last=1;                       //0,���Ǳ���λ���һ������,1:��
TKS15A_I_levels[11].contacts[3].channel=6;
TKS15A_I_levels[11].contacts[3].point_coordinate[0]=220;               //Բ��x����
TKS15A_I_levels[11].contacts[3].point_coordinate[1]=160;               //Բ��y����
TKS15A_I_levels[11].contacts[3].value_coordinate[0]=284;               //��ʾ��ʼx����
TKS15A_I_levels[11].contacts[3].value_coordinate[1]=152;               //��ʾ��ʼy����
}

#include "hxd3c.h"



struct level hxd3c_levels[18];
u16 hxd3c_TP[22][4]=
{
  {160,32,192,64},{192,32,224,64},{224,32,256,64},{256,32,288,64},{288,32,320,64},{320,32,352,64},{352,32,384,64},{384,32,416,64},
  {160,96,192,128},{192,96,224,128},{224,96,256,128},{256,96,288,128},{288,96,320,128},{320,96,352,128},{352,96,384,128},{384,96,416,128},
  {160,160,192,192},
  {160,224,192,256},{192,224,224,256},{224,224,256,256},
  
  {670,336,799,400},{670,416,799,479}
};

u16 hxd3c_POINTS[22][2]=
{
  {176,80,},{208,80,},{240,80,},{272,80,},{304,80,},{336,80,},{368,80,},{400,80,},
  {176,144},{208,144},{240,144},{272,144},{304,144},{336,144},{368,144},{400,144},
  {176,208},
  {176,336},{176,368},
  {208,304},
  {240,272},{240,368},
};

u16 hxd3c_value_disp[7][2]=
{
  {592,64},{592,128},{592,192},{448,256},{448,288},{448,320},{448,352}
};

//u16 sk640_jiwei_v[19]={0,200,1085,1966,2847,3728,4609,5490,6371,7252,8133,9014,9895,10776,11657,12538,13419,14300,15000};
//u8 sk640_jiwei_flag=0x7f;
//u8 sk640_jiwei[7]={0,3,6,9,12,15,17};



void draw_hxd3c(void)
{
  LCD_Clear(LCD_COLOR_BLACK);
  LCD_str(192,0,"测试型号:S640U_BCC005",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  
  LCD_str(16,32,"制",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(80,32,"动",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(168,32,"* 1 3 5 7 9",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(352,32,"1112",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(0,64,"506(606)",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  LCD_str(16,96,"牵",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(80,96,"引",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(168,96,"* 2 4 6 8",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(320,96,"101213",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(0,128,"508(608)",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  LCD_str(448,96,"505(605)",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  LCD_str(16,160,"零",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(168,160,"0",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  LCD_str(208,192,"507(607)",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  LCD_str(160,224,"后零前",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(0,288,"353(354)",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(272,256,"502(602)",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(272,288,"503(603)",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_str(272,320,"504(604)",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
  
  
    
  
  LCD_DrawUniLine( 128, 80,  432,  80,  LCD_COLOR_GREEN);
  LCD_DrawUniLine( 128, 144,  432,  144,  LCD_COLOR_GREEN);
  LCD_DrawUniLine( 432, 80,  432,  368,  LCD_COLOR_GREEN);  
  LCD_DrawUniLine( 144, 368,  432,  368,  LCD_COLOR_GREEN);
  LCD_DrawUniLine( 144, 336,  272,  336,  LCD_COLOR_GREEN);
  LCD_DrawUniLine( 128, 304,  272,  304,  LCD_COLOR_GREEN);
  LCD_DrawUniLine( 144, 272,  272,  272,  LCD_COLOR_GREEN);
  LCD_DrawUniLine( 144, 208,  144,  368,  LCD_COLOR_GREEN);
  LCD_DrawUniLine( 144, 208,  208,  208,  LCD_COLOR_GREEN);
  LCD_DrawUniLine( 432, 112,  448,  112,  LCD_COLOR_GREEN);
  
  u8 n=0;
  for(n=0;n<22;n++)
  {
    LCD_DrawFullCircle( hxd3c_POINTS[n][0],  hxd3c_POINTS[n][1],  5,  LCD_COLOR_BLUE2,  1);
  }
  for(n=0;n<22;n++)
  {
    LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  LCD_COLOR_BLUE2, 0);
  }
  
  //LCD_str(671,352,"保存结果",32,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
  LCD_str(671,352,"自动模式",32,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
  LCD_str(671,432,"退出实验",32,LCD_COLOR_RED,LCD_COLOR_BLACK);
  LCD_str(671,256,"级位电压",32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  
}



void hxd3c_INIT(void)
{
 ;

}


#if 0
void hxd3c_TP_respond(int x,int y)
{
  unsigned char n;
  for(n=0;n<21;n++)
  {
    if(x>hxd3c_TP[n][0]&&x<hxd3c_TP[n][2]&&y>hxd3c_TP[n][1]&&y<hxd3c_TP[n][3])
    {
      if(n==19)//保存
      {
        //sys_flag=main_panel;
        //return;
        auto_scan_flag=~auto_scan_flag;
        if(auto_scan_flag==0xff)
        {
          LCD_str(671,352,"自动模式",32,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
        }
        else if(auto_scan_flag==0x00)
        {
          LCD_str(671,352,"手动模式",32,LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
        }
        return;
      }
      else if(n==20)//（退出）
      {
        sys_flag=main_panel;
        return;
      }
      else if(n==16)
      {
        ;
      }
      else 
      {        
        LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  LCD_COLOR_BLACK, 0);
        PowerA_EN();
        hxd3c_measure_levels(n);
        PowerA_DIS();
        LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  LCD_COLOR_BLUE2, 0);
      } 
    }
  }
}

void hxd3c_measure_levels(unsigned char n)
{
  PowerA_EN();
  unsigned char i=0,j=0;
  u16  *p,temp=2000;
  if((n==17)||(n==18))
  {
    n-=1;
  }
  while(1)
  {
    
        Set_Scan_Channel(hxd3c_levels[n].contacts[i].channel);
        delay(0xfff);
        p=Get_ADC_R_Value();
        if((*p)==1583)
        {
          temp=*p;
          hxd3c_levels[n].contacts[i].R[0]=' ';
          hxd3c_levels[n].contacts[i].R[1]='_';
          hxd3c_levels[n].contacts[i].R[2]='/';
          hxd3c_levels[n].contacts[i].R[3]='_';
        }
        else if((*p)<=1500)
        {
          temp=(u16)((*p)*(hxd3c_levels[n].contacts[i].div));
          hxd3c_levels[n].contacts[i].R[0]=temp/1000+'0';
          hxd3c_levels[n].contacts[i].R[1]=(temp%1000)/100+'0';
          hxd3c_levels[n].contacts[i].R[2]=(temp%100)/10+'0';
          hxd3c_levels[n].contacts[i].R[3]=temp%10+'0';
        }
        else
        {
          temp=58;
          hxd3c_levels[n].contacts[i].R[0]='0';
          hxd3c_levels[n].contacts[i].R[1]='0';
          hxd3c_levels[n].contacts[i].R[2]='5';
          hxd3c_levels[n].contacts[i].R[3]='8';
        }
        hxd3c_levels[n].contacts[i].R[4]='\0';
        
        if(temp<ref)
        {
          LCD_DrawFullCircle(hxd3c_levels[n].contacts[i].point_coordinate[0],hxd3c_levels[n].contacts[i].point_coordinate[1],5,LCD_COLOR_GREEN,0x01);
        }
        else
        {
          LCD_DrawFullCircle(hxd3c_levels[n].contacts[i].point_coordinate[0],hxd3c_levels[n].contacts[i].point_coordinate[1],5,LCD_COLOR_RED,0x01);
        }
        LCD_str(hxd3c_levels[n].contacts[i].value_coordinate[0], hxd3c_levels[n].contacts[i].value_coordinate[1],hxd3c_levels[n].contacts[i].R,32,LCD_COLOR_BLUE2, LCD_COLOR_BLACK);
      
      if(hxd3c_levels[n].contacts[i].flag_last==1)
      {
        p=Get_ADC_V_Value();
        for(j=0;j<7;j++)
        {
          hxd3c_levels[n].level_V[j]=ADC_V_Value[j];
        }
        LCD_str(671,304,hxd3c_levels[n].level_V,32,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
        break;
      }
      i++;
  }
  PowerA_DIS();
}





void sk640k1_scan(void)
{
  u16  *p;
  u8 m,n,k,j;
  
  for(n=0;n<7;n++)
  {
    Set_Scan_Channel((7-n));
    PowerA_EN();
    delay(0xfff);
    p=Get_ADC_R_Value();
    PowerA_DIS();
    if((*p)<1500)
    {
      sk640_jiwei_flag=sk640_jiwei_flag|1<<n;
    }
    else
    {
      sk640_jiwei_flag=sk640_jiwei_flag&~(1<<n);      
    }
  }
  Set_Scan_Channel(0);//是否在零位
  PowerA_EN();
  delay(0xfff);
  p=Get_ADC_R_Value();
  PowerA_DIS();
  if((*p)<1500)//是
  {
    switch(sk640_jiwei_flag)
    {
    case 0x00://级位为0
      {
      hxd3c_measure_levels(7);
      LCD_DrawFullRect( hxd3c_TP[7][0],   hxd3c_TP[7][1],   hxd3c_TP[7][2],   hxd3c_TP[7][3],  LCD_COLOR_RED, 0);
      LCD_DrawFullRect( 520,   350,   650,   385,  LCD_COLOR_BLACK, 1);
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
      }
      LCD_DrawFullRect( hxd3c_TP[16][0],   hxd3c_TP[16][1],   hxd3c_TP[16][2],   hxd3c_TP[16][3],  LCD_COLOR_RED, 0);
      break;
      }
    case 0x4C://后
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  LCD_COLOR_BLACK, 1);
        for(k=0;k<21;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
        }
        hxd3c_measure_levels(15);
        LCD_DrawFullRect( hxd3c_TP[15][0],   hxd3c_TP[15][1],   hxd3c_TP[15][2],   hxd3c_TP[15][3],  LCD_COLOR_RED, 0);
        hxd3c_measure_levels(7);
        LCD_DrawFullRect( hxd3c_TP[7][0],   hxd3c_TP[7][1],   hxd3c_TP[7][2],   hxd3c_TP[7][3],  LCD_COLOR_RED, 0);
        break;
      }
    case 0x2A://前
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  LCD_COLOR_BLACK, 1);
        for(k=0;k<21;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
        };
        hxd3c_measure_levels(17);
        LCD_DrawFullRect( hxd3c_TP[17][0],   hxd3c_TP[17][1],   hxd3c_TP[17][2],   hxd3c_TP[17][3],  LCD_COLOR_RED, 0);
        hxd3c_measure_levels(7);
        LCD_DrawFullRect( hxd3c_TP[7][0],   hxd3c_TP[7][1],   hxd3c_TP[7][2],   hxd3c_TP[7][3],  LCD_COLOR_RED, 0);
        break;
      }
    case 0x34://制
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  LCD_COLOR_BLACK, 1);
        for(k=0;k<21;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
        }
        hxd3c_measure_levels(18);
        LCD_DrawFullRect( hxd3c_TP[18][0],   hxd3c_TP[18][1],   hxd3c_TP[18][2],   hxd3c_TP[18][3],  LCD_COLOR_RED, 0);
        hxd3c_measure_levels(7);
        LCD_DrawFullRect( hxd3c_TP[7][0],   hxd3c_TP[7][1],   hxd3c_TP[7][2],   hxd3c_TP[7][3],  LCD_COLOR_RED, 0);
        break;
      }
    default:
      {
        for(k=0;k<21;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
        }
        LCD_str(521,352,"级位错误",32,LCD_COLOR_RED,LCD_COLOR_BLACK);
        hxd3c_measure_levels(15);
        hxd3c_measure_levels(17);
        hxd3c_measure_levels(18);
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
        LCD_str(521,352,"无司控器",32,LCD_COLOR_RED,LCD_COLOR_BLACK);
        break;
      }
    case 0x4D://后
      {
      LCD_DrawFullRect( 520,   350,   650,   385,  LCD_COLOR_BLACK, 1);
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
      }
      PowerA_EN();
      hxd3c_measure_levels(15);
      PowerA_DIS();
      LCD_DrawFullRect( hxd3c_TP[15][0],   hxd3c_TP[15][1],   hxd3c_TP[15][2],   hxd3c_TP[15][3],  LCD_COLOR_RED, 0);
      PowerA_EN();
      delay(0xfff);
      p=Get_ADC_V_Value();
      PowerA_DIS();
      for(n=0;n<18;n++)
      {
        if(((*p)> sk640_jiwei_v[n])&&((*p)<= sk640_jiwei_v[n+1]))
        {
          for(m=0;m<7;m++)
          {
            if(n==sk640_jiwei[m])
            {
              PowerA_EN();
              hxd3c_measure_levels((8+m));
              PowerA_DIS();
              for(k=7;k<15;k++)
              {
                LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
              }
              LCD_DrawFullRect( hxd3c_TP[8+m][0],   hxd3c_TP[8+m][1],   hxd3c_TP[8+m][2],   hxd3c_TP[8+m][3],  LCD_COLOR_RED, 0);
            }
          }
        }
      }
      
      break;
      }
    case 0x2B://前
      {
      LCD_DrawFullRect( 520,   350,   650,   385,  LCD_COLOR_BLACK, 1);
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
      }
      PowerA_EN();
      hxd3c_measure_levels(17);
      PowerA_DIS();
      LCD_DrawFullRect( hxd3c_TP[17][0],   hxd3c_TP[17][1],   hxd3c_TP[17][2],   hxd3c_TP[17][3],  LCD_COLOR_RED, 0);
      PowerA_EN();
      delay(0xfff);
      p=Get_ADC_V_Value();
      PowerA_DIS();
      for(n=0;n<18;n++)
      {
        if(((*p)> sk640_jiwei_v[n])&&((*p)<= sk640_jiwei_v[n+1]))
        {
          for(m=0;m<7;m++)
          {
            if(n==sk640_jiwei[m])
            {
              PowerA_EN();
              hxd3c_measure_levels((8+m));
              PowerA_DIS();
              for(k=7;k<15;k++)
              {
                LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
              }
              LCD_DrawFullRect( hxd3c_TP[8+m][0],   hxd3c_TP[8+m][1],   hxd3c_TP[8+m][2],   hxd3c_TP[8+m][3],  LCD_COLOR_RED, 0);
            }
          }
        }
      }
      
      break;
      }
    case 0x35://制
      {
      LCD_DrawFullRect( 520,   350,   650,   385,  LCD_COLOR_BLACK, 1);
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
      }
      PowerA_EN();
      hxd3c_measure_levels(18);
      PowerA_DIS();
      LCD_DrawFullRect( hxd3c_TP[18][0],   hxd3c_TP[18][1],   hxd3c_TP[18][2],   hxd3c_TP[18][3],  LCD_COLOR_RED, 0);
      PowerA_EN();
      delay(0xfff);
      p=Get_ADC_V_Value();
      PowerA_DIS();
      for(n=0;n<18;n++)
      {
        if(((*p)> sk640_jiwei_v[n])&&((*p)<= sk640_jiwei_v[n+1]))
        {
          j=17-n;
          for(m=0;m<7;m++)
          {
            if(j==sk640_jiwei[m])
            {
              PowerA_EN();
              {
                hxd3c_measure_levels(m);
                PowerA_DIS();
                for(k=0;k<7;k++)
                {
                  LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
                }
                LCD_DrawFullRect( hxd3c_TP[m][0],   hxd3c_TP[m][1],   hxd3c_TP[m][2],   hxd3c_TP[m][3],  LCD_COLOR_RED, 0);
              }
            }
          }
        }
      }
      break;
      }
    default:
      {
      for(k=0;k<21;k++)
      {
        LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  LCD_COLOR_BLUE2, 0);
      }
      LCD_str(521,352,"级位错误",32,LCD_COLOR_RED,LCD_COLOR_BLACK);
      hxd3c_measure_levels(15);
      hxd3c_measure_levels(17);
      hxd3c_measure_levels(18);
      break;
      }
    }
  }
}



#endif
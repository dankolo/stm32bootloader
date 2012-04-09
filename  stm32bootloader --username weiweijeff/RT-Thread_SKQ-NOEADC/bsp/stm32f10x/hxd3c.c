
#include <rtthread.h>
#include "tc_comm.h"
#include "gel.h"
#include "analog.h"
#include "hxd3c.h"

struct level hxd3c_levels[20];
rt_uint16_t hxd3c_TP[22][4]=
{
  {160,32,192,64},{192,32,224,64},{224,32,256,64},{256,32,288,64},{288,32,320,64},{320,32,352,64},{352,32,384,64},{384,32,416,64},
  
  {160,160,192,192},
  
  {160,96,192,128},{192,96,224,128},{224,96,256,128},{256,96,288,128},{288,96,320,128},{320,96,352,128},{352,96,384,128},{384,96,416,128},

  {160,224,192,256},{192,224,224,256},{224,224,256,256},
  
  {670,336,799,400},{670,416,799,479}
};

rt_uint16_t hxd3c_POINTS[22][2]=
{
  //制动
  {176,80,},{208,80,},{240,80,},{272,80,},{304,80,},{336,80,},{368,80,},{400,80,},
  //0
  {176,208},
  //牵引
  {176,144},{208,144},{240,144},{272,144},{304,144},{336,144},{368,144},{400,144},
  //后
  {176,336},{176,368},
  //零
  {208,304},  
  //前
  {240,272},{240,368},
};

rt_uint16_t hxd3c_value_disp[7][2]=
{
  {592,64},{592,128},{592,192},{448,256},{448,288},{448,320},{448,352}
};

rt_uint16_t hxd3c_jiwei_qv[15]={0,100,1960,3920,5880,7840,9800,11760,13720,15680,17640,19600,21560,23520,24000};
rt_uint16_t hxd3c_jiwei_zv[14]={0,100,2236,4372,6508,8644,10780,12916,15052,17188,19324,21460,23596,24000};
rt_uint8_t hxd3c_jiwei_flag=0x0f;
rt_uint8_t hxd3c_jiwei_q[8]={0,2,4,6,8,10,12,13};
rt_uint8_t hxd3c_jiwei_z[8]={0,1,3,5,7,9,11,12};


void draw_hxd3c(void)
{
  LCD_Clear(Black);
  LCD_str(192,0,"测试型号:S640U_BCC005",32,Blue,Black);
  
  
  LCD_str(16,32,"制",32,Blue,Black);
  LCD_str(80,32,"动",32,Blue,Black);
  LCD_str(168,32,"* 1 3 5 7 9",32,Blue,Black);
  LCD_str(352,32,"1112",32,Blue,Black);
  LCD_str(0,64,"506(606)",32,Blue,Black);
  
  LCD_str(16,96,"牵",32,Blue,Black);
  LCD_str(80,96,"引",32,Blue,Black);
  LCD_str(168,96,"* 2 4 6 8",32,Blue,Black);
  LCD_str(320,96,"101213",32,Blue,Black);
  LCD_str(0,128,"508(608)",32,Blue,Black);
  
  LCD_str(448,96,"505(605)",32,Blue,Black);
  
  LCD_str(16,160,"零",32,Blue,Black);
  LCD_str(168,160,"0",32,Blue,Black);
  
  LCD_str(208,192,"507(607)",32,Blue,Black);
  
  LCD_str(160,224,"后零前",32,Blue,Black);
  LCD_str(0,288,"353(354)",32,Blue,Black);
  LCD_str(272,256,"502(602)",32,Blue,Black);
  LCD_str(272,288,"503(603)",32,Blue,Black);
  LCD_str(272,320,"504(604)",32,Blue,Black);
  
  
  
    
  
  LCD_DrawUniLine( 128, 80,  432,  80,  Green);
  LCD_DrawUniLine( 128, 144,  432,  144,  Green);
  LCD_DrawUniLine( 432, 80,  432,  368,  Green);  
  LCD_DrawUniLine( 144, 368,  432,  368,  Green);
  LCD_DrawUniLine( 144, 336,  272,  336,  Green);
  LCD_DrawUniLine( 128, 304,  272,  304,  Green);
  LCD_DrawUniLine( 144, 272,  272,  272,  Green);
  LCD_DrawUniLine( 144, 208,  144,  368,  Green);
  LCD_DrawUniLine( 144, 208,  208,  208,  Green);
  LCD_DrawUniLine( 432, 112,  448,  112,  Green);
  
  rt_uint8_t n=0;
  for(n=0;n<22;n++)
  {
    LCD_DrawFullCircle( hxd3c_POINTS[n][0],  hxd3c_POINTS[n][1],  5,  Blue2,  1);
  }
  for(n=0;n<22;n++)
  {
    LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  Blue2, 0);
  }
  
  //LCD_str(671,352,"保存结果",32,Blue2,Black);
  LCD_str(671,352,"自动模式",32,Blue2,Black);
  LCD_str(671,432,"退出实验",32,Red,Black);
  LCD_str(671,256,"级位电压",32,Blue,Black);
  
}



void hxd3c_INIT(void)
{
  rt_uint8_t n;
  for(n=0;n<8;n++)
  {
    hxd3c_levels[n].contacts[0].flag_last=1;
    hxd3c_levels[n].contacts[0].channel=4;
    hxd3c_levels[n].contacts[0].div=1;
    hxd3c_levels[n].contacts[0].point_coordinate[0]=hxd3c_POINTS[n][0];
    hxd3c_levels[n].contacts[0].point_coordinate[1]=hxd3c_POINTS[n][1];
    hxd3c_levels[n].contacts[0].value_coordinate[0]=hxd3c_value_disp[0][0];
    hxd3c_levels[n].contacts[0].value_coordinate[1]=hxd3c_value_disp[0][1];
  }
  
   
  hxd3c_levels[8].contacts[0].flag_last=1;
  hxd3c_levels[8].contacts[0].channel=6;
  hxd3c_levels[8].contacts[0].div=1;
  hxd3c_levels[8].contacts[0].point_coordinate[0]=hxd3c_POINTS[8][0];
  hxd3c_levels[8].contacts[0].point_coordinate[1]=hxd3c_POINTS[8][1];
  hxd3c_levels[8].contacts[0].value_coordinate[0]=hxd3c_value_disp[2][0];
  hxd3c_levels[8].contacts[0].value_coordinate[1]=hxd3c_value_disp[2][1];

  for(n=9;n<17;n++)
  {
    hxd3c_levels[n].contacts[0].flag_last=1;
    hxd3c_levels[n].contacts[0].channel=5;
    hxd3c_levels[n].contacts[0].div=1;
    hxd3c_levels[n].contacts[0].point_coordinate[0]=hxd3c_POINTS[n][0];
    hxd3c_levels[n].contacts[0].point_coordinate[1]=hxd3c_POINTS[n][1];
    hxd3c_levels[n].contacts[0].value_coordinate[0]=hxd3c_value_disp[1][0];
    hxd3c_levels[n].contacts[0].value_coordinate[1]=hxd3c_value_disp[1][1];    
  }
  
  hxd3c_levels[17].contacts[0].flag_last=0;
  hxd3c_levels[17].contacts[0].channel=2;
  hxd3c_levels[17].contacts[0].div=1;
  hxd3c_levels[17].contacts[0].point_coordinate[0]=hxd3c_POINTS[17][0];
  hxd3c_levels[17].contacts[0].point_coordinate[1]=hxd3c_POINTS[17][1];
  hxd3c_levels[17].contacts[0].value_coordinate[0]=hxd3c_value_disp[5][0];
  hxd3c_levels[17].contacts[0].value_coordinate[1]=hxd3c_value_disp[5][1];
  
  hxd3c_levels[17].contacts[1].flag_last=1;
  hxd3c_levels[17].contacts[1].channel=3;
  hxd3c_levels[17].contacts[1].div=1;
  hxd3c_levels[17].contacts[1].point_coordinate[0]=hxd3c_POINTS[18][0];
  hxd3c_levels[17].contacts[1].point_coordinate[1]=hxd3c_POINTS[18][1];
  hxd3c_levels[17].contacts[1].value_coordinate[0]=hxd3c_value_disp[6][0];
  hxd3c_levels[17].contacts[1].value_coordinate[1]=hxd3c_value_disp[6][1];
  
  hxd3c_levels[18].contacts[0].flag_last=1;
  hxd3c_levels[18].contacts[0].channel=2;
  hxd3c_levels[18].contacts[0].div=1;
  hxd3c_levels[18].contacts[0].point_coordinate[0]=hxd3c_POINTS[19][0];
  hxd3c_levels[18].contacts[0].point_coordinate[1]=hxd3c_POINTS[19][1];
  hxd3c_levels[18].contacts[0].value_coordinate[0]=hxd3c_value_disp[4][0];
  hxd3c_levels[18].contacts[0].value_coordinate[1]=hxd3c_value_disp[4][1];
  
  hxd3c_levels[19].contacts[0].flag_last=0;
  hxd3c_levels[19].contacts[0].channel=0;
  hxd3c_levels[19].contacts[0].div=1;
  hxd3c_levels[19].contacts[0].point_coordinate[0]=hxd3c_POINTS[20][0];
  hxd3c_levels[19].contacts[0].point_coordinate[1]=hxd3c_POINTS[20][1];
  hxd3c_levels[19].contacts[0].value_coordinate[0]=hxd3c_value_disp[3][0];
  hxd3c_levels[19].contacts[0].value_coordinate[1]=hxd3c_value_disp[3][1];
  
  hxd3c_levels[19].contacts[1].flag_last=1;
  hxd3c_levels[19].contacts[1].channel=3;
  hxd3c_levels[19].contacts[1].div=1;
  hxd3c_levels[19].contacts[1].point_coordinate[0]=hxd3c_POINTS[21][0];
  hxd3c_levels[19].contacts[1].point_coordinate[1]=hxd3c_POINTS[21][1];
  hxd3c_levels[19].contacts[1].value_coordinate[0]=hxd3c_value_disp[6][0];
  hxd3c_levels[19].contacts[1].value_coordinate[1]=hxd3c_value_disp[6][1];
}




void hxd3c_TP_respond(int x,int y)
{
  unsigned char n;
  for(n=0;n<22;n++)
  {
    if(x>hxd3c_TP[n][0]&&x<hxd3c_TP[n][2]&&y>hxd3c_TP[n][1]&&y<hxd3c_TP[n][3])
    {
      if(n==20)
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
      else if(n==21)//（退出）
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
      else 
      {        
        LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  Black, 0);
        hxd3c_measure_levels(n);
        LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  Blue2, 0);
      } 
    }
  }
}





void hxd3c_measure_levels(unsigned char n)
{
  rt_int8_t  i=0;
  rt_int16_t  *p,temp=2000;
  
  while(1)
  {
    
        Set_Scan_Channel(hxd3c_levels[n].contacts[i].channel);
        rt_thread_delay(5);
        ADC_R_Restart();
        ADC_R_DMA_Config();
        while(!DMA_GetFlagStatus(ADC_R_DMA_Flag));
        p=Get_ADC_R_Value();
        if((*p)>1000)
        {
          temp=*p;
          hxd3c_levels[n].contacts[i].R[0]=' ';
          hxd3c_levels[n].contacts[i].R[1]='_';
          hxd3c_levels[n].contacts[i].R[2]='/';
          hxd3c_levels[n].contacts[i].R[3]='_';
        }
        else if((*p)<=1000)
        {
          temp=(u16)((*p)*(hxd3c_levels[n].contacts[i].div));
          hxd3c_levels[n].contacts[i].R[0]=temp/1000+'0';
          hxd3c_levels[n].contacts[i].R[1]=(temp%1000)/100+'0';
          hxd3c_levels[n].contacts[i].R[2]=(temp%100)/10+'0';
          hxd3c_levels[n].contacts[i].R[3]=temp%10+'0';
        }

        hxd3c_levels[n].contacts[i].R[4]='\0';
        
        if(temp<R_ref)
        {
          LCD_DrawFullCircle(hxd3c_levels[n].contacts[i].point_coordinate[0],hxd3c_levels[n].contacts[i].point_coordinate[1],5,Green,0x01);
        }
        else
        {
          LCD_DrawFullCircle(hxd3c_levels[n].contacts[i].point_coordinate[0],hxd3c_levels[n].contacts[i].point_coordinate[1],5,Red,0x01);
        }
        LCD_str(hxd3c_levels[n].contacts[i].value_coordinate[0], hxd3c_levels[n].contacts[i].value_coordinate[1],hxd3c_levels[n].contacts[i].R,32,Blue2, Black);
      
      if(hxd3c_levels[n].contacts[i].flag_last==1)
      {
        ADC_V_Restart();
        ADC_V_DMA_Config();
        while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
        
        hxd3c_levels[n].level_V[0]=*p/10000+'0';
        if(hxd3c_levels[n].level_V[0]=='0')
        {
          hxd3c_levels[n].level_V[0]=' ';
        }
        hxd3c_levels[n].level_V[1]=(*p%10000)/1000+'0';
        hxd3c_levels[n].level_V[2]='.';
        hxd3c_levels[n].level_V[3]=(*p%1000)/100+'0';
        hxd3c_levels[n].level_V[4]=(*p%100)/10+'0';
        hxd3c_levels[n].level_V[5]='V';
        hxd3c_levels[n].level_V[6]='\0';
        
        
        LCD_str(671,304,hxd3c_levels[n].level_V,32,Blue,Black);
        
        break;
      }
      i++;
  }
}










































void hxd3c_scan(void)
{
  rt_int16_t  *p;
  rt_uint8_t m,n,k;
  
  for(n=0;n<7;n++)
  {
    Set_Scan_Channel(n);
    rt_thread_delay(5);
    ADC_R_Restart();
    ADC_R_DMA_Config();
    while(!DMA_GetFlagStatus(ADC_R_DMA_Flag));
    p=Get_ADC_R_Value();
//    rt_kprintf("R=%d\r\n",(*p));
    if((*p)<1000)
    {
      hxd3c_jiwei_flag=hxd3c_jiwei_flag|1<<n;
    }
    else
    {
      hxd3c_jiwei_flag=hxd3c_jiwei_flag&~(1<<n);      
    }
  }
//  rt_kprintf("hxd3c_jiwei_flag=%x\r\n",hxd3c_jiwei_flag);
//是否在零位
  if((hxd3c_jiwei_flag>>6))//是
  {
    switch(hxd3c_jiwei_flag)
    {
    case 0x42://级位为0
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(18);
        LCD_DrawFullRect( hxd3c_TP[18][0],   hxd3c_TP[18][1],   hxd3c_TP[18][2],   hxd3c_TP[18][3],  Red, 0);
        hxd3c_measure_levels(8);
        LCD_DrawFullRect( hxd3c_TP[8][0],   hxd3c_TP[8][1],   hxd3c_TP[8][2],   hxd3c_TP[8][3],  Red, 0);
        
        break;
      }
    case 0x4C://后
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(17);
        LCD_DrawFullRect( hxd3c_TP[17][0],   hxd3c_TP[17][1],   hxd3c_TP[17][2],   hxd3c_TP[17][3],  Red, 0);
        hxd3c_measure_levels(8);
        LCD_DrawFullRect( hxd3c_TP[8][0],   hxd3c_TP[8][1],   hxd3c_TP[8][2],   hxd3c_TP[8][3],  Red, 0);
        break;
      }
    case 0x49://前
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        };
        hxd3c_measure_levels(19);
        LCD_DrawFullRect( hxd3c_TP[19][0],   hxd3c_TP[19][1],   hxd3c_TP[19][2],   hxd3c_TP[19][3],  Red, 0);
        hxd3c_measure_levels(8);
        LCD_DrawFullRect( hxd3c_TP[8][0],   hxd3c_TP[8][1],   hxd3c_TP[8][2],   hxd3c_TP[8][3],  Red, 0);
        break;
      }    
    default:
      {
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        LCD_str(521,352,"级位错误",32,Red,Black);
        hxd3c_measure_levels(17);
        hxd3c_measure_levels(18);
        hxd3c_measure_levels(19);
        break;
      }
    }
  }
  else//不是在0位
  {
    switch(hxd3c_jiwei_flag)
    {
    case 0x00://级位为0
      {
        LCD_str(521,352,"无司控器",32,Red,Black);
        break;
      }
    case 0x29://前牵
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(19);
        LCD_DrawFullRect( hxd3c_TP[19][0],   hxd3c_TP[19][1],   hxd3c_TP[19][2],   hxd3c_TP[19][3],  Red, 0);
        rt_thread_delay(5);
        ADC_V_Restart();
        ADC_V_DMA_Config();
        while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
        for(n=0;n<15;n++)
        {
          if(((*p)> hxd3c_jiwei_qv[n])&&((*p)<= hxd3c_jiwei_qv[n+1]))
          {
            for(m=0;m<8;m++)
            {
              if(n==hxd3c_jiwei_q[m])
              {
                hxd3c_measure_levels((9+m));
              for(k=8;k<16;k++)
              {
                LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
              }
              LCD_DrawFullRect( hxd3c_TP[9+m][0],   hxd3c_TP[9+m][1],   hxd3c_TP[9+m][2],   hxd3c_TP[9+m][3],  Red, 0);
              break;
            }            
          }
          break;
        }
      }      
      break;
      }
      
      case 0x2C://后牵
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(17);
        LCD_DrawFullRect( hxd3c_TP[17][0],   hxd3c_TP[17][1],   hxd3c_TP[17][2],   hxd3c_TP[17][3],  Red, 0);
        rt_thread_delay(5);
        ADC_V_Restart();
        ADC_V_DMA_Config();
        while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
        for(n=0;n<15;n++)
        {
          if(((*p)> hxd3c_jiwei_qv[n])&&((*p)<= hxd3c_jiwei_qv[n+1]))
          {
            for(m=0;m<8;m++)
            {
              if(n==hxd3c_jiwei_q[m])
              {
                hxd3c_measure_levels((9+m));
              for(k=8;k<16;k++)
              {
                LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
              }
              LCD_DrawFullRect( hxd3c_TP[9+m][0],   hxd3c_TP[9+m][1],   hxd3c_TP[9+m][2],   hxd3c_TP[9+m][3],  Red, 0);
              break;
            }
          }
          break;
        }
      }
      break;
      }
      
    case 0x19://前制
      {  
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(19);
        LCD_DrawFullRect( hxd3c_TP[19][0],   hxd3c_TP[19][1],   hxd3c_TP[19][2],   hxd3c_TP[19][3],  Red, 0);
        rt_thread_delay(5);
        ADC_V_Restart();
        ADC_V_DMA_Config();
        while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
//        rt_kprintf("jiwei_v=%d\r\n",(*p));
        for(n=0;n<14;n++)
        {
          if(((*p)> hxd3c_jiwei_zv[n])&&((*p)<= hxd3c_jiwei_zv[n+1]))
          {
//             rt_kprintf("jiwei_n=%x\r\n",n);
            for(m=0;m<8;m++)
            {
              if(n==hxd3c_jiwei_z[m])
              {
                hxd3c_measure_levels(m);
                for(k=0;k<8;k++)
                {
                  LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
                }
                LCD_DrawFullRect( hxd3c_TP[m][0],   hxd3c_TP[m][1],   hxd3c_TP[m][2],   hxd3c_TP[m][3],  Red, 0);
                break;
              }
            }
            break;
          }
        }
        break;
      }
      
      case 0x1C://后制
      {  
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(17);
        LCD_DrawFullRect( hxd3c_TP[17][0],   hxd3c_TP[17][1],   hxd3c_TP[17][2],   hxd3c_TP[17][3],  Red, 0);
        rt_thread_delay(5);
        ADC_V_Restart();
        ADC_V_DMA_Config();
        while(!DMA_GetFlagStatus(ADC_V_DMA_Flag));
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
        for(n=0;n<14;n++)
        {
          if(((*p)> hxd3c_jiwei_zv[n])&&((*p)<= hxd3c_jiwei_zv[n+1]))
          {
            for(m=0;m<8;m++)
            {
              if(n==hxd3c_jiwei_z[m])
              {
                hxd3c_measure_levels(m);
                for(k=0;k<8;k++)
                {
                  LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
                }
                LCD_DrawFullRect( hxd3c_TP[m][0],   hxd3c_TP[m][1],   hxd3c_TP[m][2],   hxd3c_TP[m][3],  Red, 0);
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
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        LCD_str(521,352,"级位错误",32,Red,Black);
        hxd3c_measure_levels(17);
        hxd3c_measure_levels(18);
        hxd3c_measure_levels(19);
        break;
      }
    }
  }
}
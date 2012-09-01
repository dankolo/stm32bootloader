
#include <rtthread.h>
#include "tc_comm.h"
#include "gel.h"
#include "analog.h"
#include "hxd3c.h"
#define hxd3c_steps 14

struct level hxd3c_levels[20];
rt_uint16_t hxd3c_TP[27][4]=
{
  {160,96,192,128},{192,96,224,128},{224,96,256,128},{256,96,288,128},{288,96,320,128},{320,96,352,128},{352,96,384,128},{384,96,416,128},
  
  {160,224,192,256},
  
  {160,160,192,192},{192,160,224,192},{224,160,256,192},{256,160,288,192},{288,160,320,192},{320,160,352,192},{352,160,384,192},{384,160,416,192},
  
  {160,288,192,320},{192,288,224,320},{224,288,256,320},
  
  {0,1,128,63},{670,1,798,63},{536,336,664,400},{670,336,798,400},{536,416,600,479},{600,416,664,479},{670,416,798,479}
};
//�ֶ�ģʽ     �˳�ʵ��        ��һ��            ��һ��              ��                  ��                 ��������
rt_uint16_t hxd3c_POINTS[22][2]=
{
  //�ƶ�
  {176,144},{208,144},{240,144},{272,144},{304,144},{336,144},{368,144},{400,144},
  //0
  {176,272},
  //ǣ��
  {176,208},{208,208},{240,208},{272,208},{304,208},{336,208},{368,208},{400,208},
  //��
  {176,400},{176,432},
  //��
  {208,370},  
  //ǰ
  {240,336},{240,432},
};

rt_uint16_t hxd3c_value_disp[7][2]=
{
  {592,128},{592,192},{592,256},{448,320},{448,352},{448,384},{448,416}
};

rt_uint16_t hxd3c_jiwei_qv[15]={0,100,1960,3920,5880,7840,9800,11760,13720,15680,17640,19600,21560,23520,24000};
rt_uint16_t hxd3c_jiwei_zv[14]={0,100,2236,4372,6508,8644,10780,12916,15052,17188,19324,21460,23596,24000};
rt_uint8_t hxd3c_jiwei_flag=0x0f;
rt_uint8_t hxd3c_jiwei_q[8]={0,2,4,6,8,10,12,13};
rt_uint8_t hxd3c_jiwei_z[8]={0,1,3,5,7,9,11,12};


void draw_hxd3c(void)
{
  LCD_Clear(Black);
  LCD_str(192,0,"�����ͺ�:S640U_BCC005",32,Blue,Black);
  
  
  LCD_str(16,96,"��",32,Blue,Black);
  LCD_str(80,96,"��",32,Blue,Black);
  LCD_str(168,96,"* 1 3 5 7 9",32,Blue,Black);
  LCD_str(352,96,"1112",32,Blue,Black);
  LCD_str(0,128,"506(606)",32,Blue,Black);
  
  LCD_str(16,160,"ǣ",32,Blue,Black);
  LCD_str(80,160,"��",32,Blue,Black);
  LCD_str(168,160,"* 2 4 6 8",32,Blue,Black);
  LCD_str(320,160,"101213",32,Blue,Black);
  LCD_str(0,192,"508(608)",32,Blue,Black);
  
  LCD_str(448,128,"505(605)",32,Blue,Black);
  
  LCD_str(16,224,"��",32,Blue,Black);
  LCD_str(168,224,"0",32,Blue,Black);
  
  LCD_str(208,258,"507(607)",32,Blue,Black);
  
  LCD_str(160,290,"����ǰ",32,Blue,Black);
  LCD_str(0,352,"353(354)",32,Blue,Black);
  LCD_str(272,320,"502(602)",32,Blue,Black);
  LCD_str(272,352,"503(603)",32,Blue,Black);
  LCD_str(272,384,"504(604)",32,Blue,Black);
  
  
  
  
  
  LCD_DrawUniLine( 128, 144,  448,  144,  Green);
  LCD_DrawUniLine( 128, 208,  432,  208,  Green);
  LCD_DrawUniLine( 432, 144,  432,  432,  Green);  
  LCD_DrawUniLine( 144, 432,  432,  432,  Green);
  LCD_DrawUniLine( 144, 400,  272,  400,  Green);
  LCD_DrawUniLine( 128, 368,  272,  368,  Green);
  LCD_DrawUniLine( 144, 336,  272,  336,  Green);
  LCD_DrawUniLine( 144, 272,  144,  432,  Green);
  LCD_DrawUniLine( 144, 272,  208,  272,  Green);
  //LCD_DrawUniLine( 432, 176,  448,  176,  Green);
  
  rt_uint8_t n=0;
  for(n=0;n<22;n++)
  {
    LCD_DrawFullCircle( hxd3c_POINTS[n][0],  hxd3c_POINTS[n][1],  5,  Blue2,  1);
  }
  for(n=0;n<27;n++)
  {
    LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  Blue2, 0);
  }
  
  LCD_str(0,16,"�ֶ�ģʽ",32,Blue2,Black);
  LCD_str(671,432,"��������",32,Blue2,Black);
  LCD_str(671,96,"��λ��ѹ",32,Blue,Black);
  LCD_str(671,16,"�˳�ʵ��",32,Red,Black);
  LCD_str(552,432,"��",32,Blue,Black);
  LCD_str(616,432,"��",32,Blue,Black);
  LCD_str(552,352,"��һ��",32,Blue,Black);
  LCD_str(687,352,"��һ��",32,Blue,Black);
  LCD_str(448,160,"�⵽����λ\n��ɺ���",24,Red,Black);
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
    memcpy(hxd3c_levels[n].level_V,untest,5);
    memcpy(hxd3c_levels[n].contacts[0].R,untest,5);
  }
  
  
  hxd3c_levels[8].contacts[0].flag_last=1;
  hxd3c_levels[8].contacts[0].channel=6;
  hxd3c_levels[8].contacts[0].div=1;
  hxd3c_levels[8].contacts[0].point_coordinate[0]=hxd3c_POINTS[8][0];
  hxd3c_levels[8].contacts[0].point_coordinate[1]=hxd3c_POINTS[8][1];
  hxd3c_levels[8].contacts[0].value_coordinate[0]=hxd3c_value_disp[2][0];
  hxd3c_levels[8].contacts[0].value_coordinate[1]=hxd3c_value_disp[2][1];
  memcpy(hxd3c_levels[8].contacts[0].R,untest,5);
  memcpy(hxd3c_levels[8].level_V,untest,5);
  
  for(n=9;n<17;n++)
  {
    hxd3c_levels[n].contacts[0].flag_last=1;
    hxd3c_levels[n].contacts[0].channel=5;
    hxd3c_levels[n].contacts[0].div=1;
    hxd3c_levels[n].contacts[0].point_coordinate[0]=hxd3c_POINTS[n][0];
    hxd3c_levels[n].contacts[0].point_coordinate[1]=hxd3c_POINTS[n][1];
    hxd3c_levels[n].contacts[0].value_coordinate[0]=hxd3c_value_disp[1][0];
    hxd3c_levels[n].contacts[0].value_coordinate[1]=hxd3c_value_disp[1][1]; 
    memcpy(hxd3c_levels[n].level_V,untest,5);
    memcpy(hxd3c_levels[n].contacts[0].R,untest,5);
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
  
  memcpy(hxd3c_levels[17].level_V,untest,5);
  memcpy(hxd3c_levels[17].contacts[0].R,untest,5);
  memcpy(hxd3c_levels[17].contacts[1].R,untest,5);
  
  hxd3c_levels[18].contacts[0].flag_last=1;
  hxd3c_levels[18].contacts[0].channel=2;
  hxd3c_levels[18].contacts[0].div=1;
  hxd3c_levels[18].contacts[0].point_coordinate[0]=hxd3c_POINTS[19][0];
  hxd3c_levels[18].contacts[0].point_coordinate[1]=hxd3c_POINTS[19][1];
  hxd3c_levels[18].contacts[0].value_coordinate[0]=hxd3c_value_disp[4][0];
  hxd3c_levels[18].contacts[0].value_coordinate[1]=hxd3c_value_disp[4][1];
  memcpy(hxd3c_levels[18].level_V,untest,5);
  memcpy(hxd3c_levels[18].contacts[0].R,untest,5);
  
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
  memcpy(hxd3c_levels[19].level_V,untest,5);
  memcpy(hxd3c_levels[19].contacts[0].R,untest,5);
  memcpy(hxd3c_levels[19].contacts[1].R,untest,5);
  V_jiwei=untest;
  lamp=untest;
  bhlj=untest;//�պ��߼�
}


void hxd3c_save_data(void)
{
  int fd,i;
  struct tm *time_now;
  time_t t;
  t=time(NULL);
  time_now =localtime(&t);
  strftime(file_name,sizeof(file_name),"HXD3C_%Y_%m_%d_%H_%M_%S.csv",time_now);  
  char name_buffer[37];
  rt_sprintf(name_buffer,"/HXD3C/%s",file_name);
  fd=open(name_buffer,O_RDWR|O_CREAT,0);
  
  write(fd,",,",2);
  write(fd,file_name,29);
  write(fd,",\r\n",3);
  write(fd,"�ƶ���λ,*,1,3,5,7,19,11,12,\r\n",30);
  
  write(fd,"506(606),",9);
  for(i=0;i<8;i++)
  {
    write(fd,hxd3c_levels[i].contacts[0].R,5);
    write(fd,",",1);
  }  
  write(fd,"505(605),\r\n",11);
  
  write(fd,"��λ��ѹ,",9);
  for(i=0;i<8;i++)
  {
    write(fd,hxd3c_levels[i].level_V,7);
    write(fd,",",1);
  }
  write(fd,"\r\n\r\n",4);
  
  write(fd,"ǣ����λ,*,2,4,6,8,10,12,13,\r\n",30); 
  write(fd,"508(608),",9);
  for(i=9;i<17;i++)
  {
    write(fd,hxd3c_levels[i].contacts[0].R,5);
    write(fd,",",1);
  }  
  write(fd,"505(605),\r\n",11);
  
  write(fd,"��λ��ѹ,",9);
  for(i=9;i<17;i++)
  {
    write(fd,hxd3c_levels[i].level_V,7);
    write(fd,",",1);
  }
  write(fd,"\r\n\r\n",4);
  
  write(fd,"����λ,0,\r\n",11);
  write(fd,"353(354),",9);
  write(fd,hxd3c_levels[8].contacts[0].R,5);
  write(fd,",",1);
  write(fd,hxd3c_levels[i].level_V,7);
  write(fd,",507(607),\r\n\r\n",14);
  
  
  
  
  
  
  write(fd,"����λ,��,��,ǰ,\r\n",20);
  write(fd,"353(354),,,",11);
  
  write(fd,hxd3c_levels[19].contacts[0].R,5);
  
  write(fd,",502(602),�Ӵ����赥λ,,m��,\r\n",30);
  
  
  write(fd,"353(354),,",10);
  write(fd,hxd3c_levels[18].contacts[0].R,5);
  write(fd,",,503(603),�����߼�,,",21);
  write(fd,bhlj,5);
  write(fd,",\r\n",3);
  
  write(fd,"353(354),",9);
  write(fd,hxd3c_levels[17].contacts[0].R,5);  
  write(fd,",,,504(604),��λ���ܵ���ֵ,,",28);
  write(fd,R_value,6);
  write(fd,",\r\n",3);
  
  write(fd,"353(354),",9);
  write(fd,hxd3c_levels[17].contacts[1].R,5);
  write(fd,",,",2);
  write(fd,hxd3c_levels[19].contacts[1].R,5);
  write(fd,",505(605),��λ��ѹ,,",20);
  write(fd,V_jiwei,5);
  write(fd,",\r\n",3);  
  
  
  write(fd,"�Ӵ�����ο�ֵ,,",16);
  write(fd,ref_buffer,5);
  write(fd,",,,ҹ���,,",11);
  write(fd,lamp,5);
  write(fd,",\r\n",3);
  
  close(fd);
  //closedir(dir);
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(hxd3c_save_data, hxd3c_save_data.)
FINSH_FUNCTION_EXPORT(hxd3c_INIT, hxd3c_INIT.)
#endif


void hxd3c_TP_respond(int x,int y)
{
  unsigned char n;
  for(n=0;n<27;n++)
  {
    if(x>hxd3c_TP[n][0]&&x<hxd3c_TP[n][2]&&y>hxd3c_TP[n][1]&&y<hxd3c_TP[n][3])
    {
      if(n==20)//�ֶ��Զ��л�
      {        
        auto_scan_flag=~auto_scan_flag;
        if(auto_scan_flag)
        {
          rt_thread_resume(&skq_scan_thread);
          LCD_str(0,16,"�Զ�ģʽ",32,Blue2,Black);
        }
        else
        {         
          rt_mutex_take(scan_over_one_time, RT_WAITING_FOREVER);
          rt_thread_suspend(&skq_scan_thread);
          LCD_str(0,16,"�ֶ�ģʽ",32,Blue2,Black);
          rt_mutex_release(scan_over_one_time);
          LCD_DrawFullRect(448,160,576,319,  Black, 1);
          LCD_str(448,160,"�⵽����λ\n��ɺ���",24,Red,Black);
        }
        return;
      }
      else if(n==21)//���˳���
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
        //rt_schedule();
        
        
        
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
      else if(n==22)//��һ��
      {
        if(uchar_check_step>0)
        {
          uchar_check_step-=1;
          switch(uchar_check_step)
          {
          case 0:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"�⵽��λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 1:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"�⵽���λ\n�Ĵ���λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 2:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ��С��λ\n��ɺ���",24,Red,Black);
              break;            
            }
          case 3:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ��13��\n��ɺ���",24,Red,Black);
              break;
            }
          case 4:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ�������\n����λ���\n����Ӧ��λ\n���ֵı߿�",24,Red,Black);
              break;
            }
          case 5:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"�⵽�ƶ�λ\n��С��λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 6:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\n�ƶ�12��\n��ɺ���",24,Red,Black);
              break;
            }
          case 7:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\n�ƶ������\n����λ���\n����Ӧ��λ\n���ֵı߿�",24,Red,Black);
              break;
            }
          case 8:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"�⵽��ǰλ\n�Ĵ���λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 9:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ��С��λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 10:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ��13��\n��ɺ���",24,Red,Black);
              break;
            }
          case 11:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ�������\n����λ���\n����Ӧ��λ\n���ֵı߿�",24,Red,Black);
              break;
            }
          case 12:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"ҹ��������\n�Ƿ�������",24,Red,Black);
              set_24V();
              break;
            }
          case 13:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"����\n��Ƭ������\n���ܵ���ֵ",24,Red,Black);
              measure_R();
              LCD_str(448,233,R_value,24,Red,Black);
              break;
            }
          default:
            {
              break;
            }
          }
        }
      }
      else if(n==23)//��һ��
      {
        if(uchar_check_step<hxd3c_steps)
        {
          uchar_check_step+=1;
          switch(uchar_check_step)
          {          
          case 1:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"�⵽���λ\n�Ĵ���λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 2:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ��С��λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 3:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ��13��\n��ɺ���",24,Red,Black);
              break;
            }
          case 4:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ�������\n����λ���\n����Ӧ��λ\n���ֵı߿�",24,Red,Black);
              break;
            }
          case 5:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"�⵽�ƶ�λ\n��С��λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 6:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\n�ƶ�12��\n��ɺ���",24,Red,Black);
              break;
            }
          case 7:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\n�ƶ������\n����λ���\n����Ӧ��λ\n���ֵı߿�",24,Red,Black);
              break;
            }
          case 8:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"�⵽��ǰλ\n�Ĵ���λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 9:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ��С��λ\n��ɺ���",24,Red,Black);
              break;
            }
          case 10:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ��13��\n��ɺ���",24,Red,Black);
              break;
            }
          case 11:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"���ֱ��⵽\nǣ�������\n����λ���\n����Ӧ��λ\n���ֵı߿�",24,Red,Black);
              break;
            }
          case 12:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"ҹ��������\n�Ƿ�������",24,Red,Black);
              set_24V();
              break;
            }
          case 13:
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              LCD_str(448,160,"����\n��Ƭ������\n���ܵ���ֵ",24,Red,Black);
              measure_R();
              LCD_str(448,233,R_value,24,Red,Black);
              break;
            }
          case 14://��Ҫ��Ϊ��ʾ���Խ��
            {
              LCD_DrawFullRect(448,160,576,319,  Black, 1);
              //�жϼ�λ��ѹ�Ƿ�����
              // if((S640K1_levels[6].level_V[0]==' ')&&(S640K1_levels[6].level_V[1]=='0')&&(S640K1_levels[6].level_V[3]<'2')&&
              //   (S640K1_levels[8].level_V[0]==' ')&&(S640K1_levels[8].level_V[1]=='0')&&(S640K1_levels[8].level_V[3]<'2')&&
              //    (S640K1_levels[0].level_V[0]=='1')&&(S640K1_levels[0].level_V[1]=='4')&&(S640K1_levels[0].level_V[3]>'3')&&
              //      (S640K1_levels[14].level_V[0]=='1')&&(S640K1_levels[14].level_V[1]=='4')&&(S640K1_levels[14].level_V[3]>'3')
              //        )
              //    {
              V_jiwei=zc;
              //    }
              //     else
              {
                //      V_jiwei=gz;
              }
              
              
              LCD_str(448,160,"ʵ���ѽ���\n�뱣������\n���˳�ʵ��",24,Red,Black);
              break;
            }
          default:
            {
              break;
            }
          }
        }
        
      }
      else if(n==24)//��
      {
        
      }
      else if(n==25)//��
      {
        
      }
      else if(n==26)//��������
      {
        rt_mutex_take(scan_over_one_time, RT_WAITING_FOREVER);
        hxd3c_save_data();
        LCD_str(671,432,"�������",32,Blue,Black);
        rt_mutex_release(scan_over_one_time);
      }
      else
      {        
        LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  Black, 0);
        hxd3c_measure_levels(n);
        LCD_DrawFullRect( hxd3c_TP[n][0],   hxd3c_TP[n][1],   hxd3c_TP[n][2],   hxd3c_TP[n][3],  Blue2, 0);
        return;
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
    
    p=Get_ADC_R_Value();
    if((*p)>1100)
    {
      temp=*p;
      hxd3c_levels[n].contacts[i].R[0]=' ';
      hxd3c_levels[n].contacts[i].R[1]='_';
      hxd3c_levels[n].contacts[i].R[2]='/';
      hxd3c_levels[n].contacts[i].R[3]='_';
      hxd3c_levels[n].contacts[i].R[4]='\0';
    }
    else if((*p)<=1100)
    {
      temp=(u16)((*p)*(hxd3c_levels[n].contacts[i].div));
      hxd3c_levels[n].contacts[i].R[0]=temp/1000+'0';
      hxd3c_levels[n].contacts[i].R[1]=(temp%1000)/100+'0';
      hxd3c_levels[n].contacts[i].R[2]=(temp%100)/10+'0';
      hxd3c_levels[n].contacts[i].R[3]=temp%10+'0';
      hxd3c_levels[n].contacts[i].R[4]='\0';
      //rt_sprintf(hxd3c_levels[n].contacts[i].R,"%d",temp);
    }
    
    
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
      hxd3c_levels[n].level_V[5]=*p%10+'0';
      hxd3c_levels[n].level_V[6]='V';
      hxd3c_levels[n].level_V[7]='\0';
      
      
      LCD_str(671,128,hxd3c_levels[n].level_V,32,Blue,Black);
      
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
    
    p=Get_ADC_R_Value();
    //    rt_kprintf("R=%d\r\n",(*p));
    if((*p)<=1250)
    {
      hxd3c_jiwei_flag=hxd3c_jiwei_flag|1<<n;
    }
    else
    {
      hxd3c_jiwei_flag=hxd3c_jiwei_flag&~(1<<n);      
    }
  }
  //  rt_kprintf("hxd3c_jiwei_flag=%x\r\n",hxd3c_jiwei_flag);
  //�Ƿ�����λ
  if((hxd3c_jiwei_flag>>6))//��
  {
    switch(hxd3c_jiwei_flag)
    {
    case 0x42://��λΪ0
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
    case 0x4C://��
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
    case 0x49://ǰ
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
        LCD_DrawFullRect(448,160,576,319,  Black, 1);
        LCD_str(448,160,"��λ����",32,Red,Black);
        hxd3c_measure_levels(17);
        hxd3c_measure_levels(18);
        hxd3c_measure_levels(19);
        break;
      }
    }
  }
  else//������0λ
  {
    switch(hxd3c_jiwei_flag)
    {
    case 0x00://��λΪ0
      {
        LCD_str(521,352,"��˾����",32,Red,Black);
        break;
      }
    case 0x29://ǰǣ
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(19);
        LCD_DrawFullRect( hxd3c_TP[19][0],   hxd3c_TP[19][1],   hxd3c_TP[19][2],   hxd3c_TP[19][3],  Red, 0);
        
        
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
        for(n=0;n<15;n++)
        {
          if(((*p)>= hxd3c_jiwei_qv[n])&&((*p)< hxd3c_jiwei_qv[n+1]))
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
      
    case 0x2C://��ǣ
      {
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(17);
        LCD_DrawFullRect( hxd3c_TP[17][0],   hxd3c_TP[17][1],   hxd3c_TP[17][2],   hxd3c_TP[17][3],  Red, 0);
        
        
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
        for(n=0;n<15;n++)
        {
          if(((*p)>= hxd3c_jiwei_qv[n])&&((*p)< hxd3c_jiwei_qv[n+1]))
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
      
    case 0x19://ǰ��
      {  
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(19);
        LCD_DrawFullRect( hxd3c_TP[19][0],   hxd3c_TP[19][1],   hxd3c_TP[19][2],   hxd3c_TP[19][3],  Red, 0);
        
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
        //        rt_kprintf("jiwei_v=%d\r\n",(*p));
        for(n=0;n<14;n++)
        {
          if(((*p)>= hxd3c_jiwei_zv[n])&&((*p)< hxd3c_jiwei_zv[n+1]))
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
      
    case 0x1C://����
      {  
        LCD_DrawFullRect( 520,   350,   650,   385,  Black, 1);
        for(k=0;k<22;k++)
        {
          LCD_DrawFullRect( hxd3c_TP[k][0],   hxd3c_TP[k][1],   hxd3c_TP[k][2],   hxd3c_TP[k][3],  Blue2, 0);
        }
        hxd3c_measure_levels(17);
        LCD_DrawFullRect( hxd3c_TP[17][0],   hxd3c_TP[17][1],   hxd3c_TP[17][2],   hxd3c_TP[17][3],  Red, 0);
        
        
        p=Get_ADC_V_Value();*p=(rt_int16_t)(9.6*(*p));
        for(n=0;n<14;n++)
        {
          if(((*p)>= hxd3c_jiwei_zv[n])&&((*p)< hxd3c_jiwei_zv[n+1]))
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
        LCD_DrawFullRect(448,160,576,319,  Black, 1);
        LCD_str(448,160,"��λ����",32,Red,Black);
        hxd3c_measure_levels(17);
        hxd3c_measure_levels(18);
        hxd3c_measure_levels(19);
        break;
      }
    }
  }
}
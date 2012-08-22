

#include"analog.h"



rt_uint8_t Scan_Channels[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//扫描通道


char R_value[6]="未测！";

rt_int16_t R=0,V=0;

rt_uint16_t ADCConvertedValue_R[ADC_R_DMA_BufferSize];
rt_uint16_t ADCConvertedValue_V[ADC_V_DMA_BufferSize];

//rt_uint8_t     auto_scan_flag=0x00;
rt_uint8_t     tp_flag=0;



void Set_Scan_Channel(unsigned char x)
{
  if((Scan_Channels[x]>>3)==0)
  {
    GPIO_ResetBits(CD4067_PORT,CD4067_s3);
  }
  else
  {
    GPIO_SetBits(CD4067_PORT,CD4067_s3);
  }
  if(((Scan_Channels[x]&0x04)>>2)==0)
  {
    GPIO_ResetBits(CD4067_PORT,CD4067_s2);
  }
  else
  {
    GPIO_SetBits(CD4067_PORT,CD4067_s2);
  }
  if(((Scan_Channels[x]&0x02)>>1)==0)
  {
    GPIO_ResetBits(CD4067_PORT,CD4067_s1);
  }
  else
  {
    GPIO_SetBits(CD4067_PORT,CD4067_s1);
  }
  if((Scan_Channels[x]&0x01)==0)
  {
    GPIO_ResetBits(CD4067_PORT,CD4067_s0);
  }
  else
  {
    GPIO_SetBits(CD4067_PORT,CD4067_s0);
  }
}


void PowerA_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(PowerA_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = PowerA_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
  GPIO_Init(PowerA_PORT,&GPIO_InitStructure);
  GPIO_ResetBits(PowerA_PORT,PowerA_Pin);
}


void CD4067_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(CD4067_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = CD4067_E|CD4067_s0|CD4067_s1|CD4067_s2|CD4067_s3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
  GPIO_Init(CD4067_PORT,&GPIO_InitStructure);
}


static void delay_nus(rt_int16_t n)
{
  n=n*8;
  while(--n);
}



rt_int16_t *Get_ADC_R_Value()
{
  delay_nus(100);
  rt_uint16_t j=0,i=0,temp=0;
  rt_uint32_t n=0;
  for(j=0;j<ADC_R_DMA_BufferSize;j+=1)
  {
    ADCConvertedValue_R[j]=ltc1865_read_ch(1,0);
//    rt_kprintf("radc=%d\n",ADCConvertedValue_R[j]);
  }
  for(j=0;j<=ADC_R_DMA_BufferSize;j+=1)
  {
    for (i=0;i<ADC_R_DMA_BufferSize-j;i+=1)
    {
      if (ADCConvertedValue_R[i]>ADCConvertedValue_R[i+1])
      {
        temp=ADCConvertedValue_R[i];
        ADCConvertedValue_R[i]=ADCConvertedValue_R[i+1];
        ADCConvertedValue_R[i+1]=temp;
      }
    }
  }
  for(i=ADC_R_DMA_BufferSize>>2;i<(ADC_R_DMA_BufferSize>>2)*3;i+=1)
  {
    n+=ADCConvertedValue_R[i];
  }
//  rt_kprintf("rn=%d\n",n);
  R=(rt_int16_t)(n/32*3298/65356/1.86);
  //R=(rt_int16_t)(R*0.908127208-270.6678445);
  if(R<0)
  {
    R=0;
  }
  
  return &R;
}




rt_int16_t *Get_ADC_V_Value()
{
  delay_nus(100);
  rt_uint16_t j=0,i=0,temp=0;
  rt_uint32_t n=0;
  double ftemp=0;
  for(j=0;j<ADC_V_DMA_BufferSize;j+=1)
  {
    ADCConvertedValue_V[j]=ltc1865_read_ch(1,1);
//    rt_kprintf("vadc=%d\n",ADCConvertedValue_V[j]);
  }
  for(j=0;j<=ADC_V_DMA_BufferSize;j+=1)
  {
    for (i=0;i<ADC_V_DMA_BufferSize-j;i+=1)
    {
      if (ADCConvertedValue_V[i]>ADCConvertedValue_V[i+1])
      {
        temp=ADCConvertedValue_V[i];
        ADCConvertedValue_V[i]=ADCConvertedValue_V[i+1];
        ADCConvertedValue_V[i+1]=temp;
      }
    }
  }
  for(i=ADC_V_DMA_BufferSize>>2;i<(ADC_V_DMA_BufferSize>>2)*3;i+=1)
  {
    n+=ADCConvertedValue_V[i];
  }
//  rt_kprintf("vn=%d\n",n);
  ftemp=((n>>5)*3298)>>16;
  if(ftemp<1)
  {
    ftemp=0;
  }
  else if(ftemp<1500)
  {
    ftemp=ftemp*0.9985+32;
  }
  else
  {
    ftemp=ftemp*1.01978+0.4;
  }
  V=(rt_int16_t)ftemp;
  return &V;  
}

void  
GPIO_config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//gpio2 3 4
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5;//gpio4 5 6
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  
  GPIO_SetBits(GPIOA,GPIO_Pin_1);
  GPIO_ResetBits(GPIOA,GPIO_Pin_2);
  GPIO_ResetBits(GPIOA,GPIO_Pin_3);
  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
  GPIO_ResetBits(GPIOB,GPIO_Pin_5);
  
}

static rt_int16_t *Get_V(void)
{
  delay_nus(100);
  rt_uint16_t j=0,i=0,temp=0;
  rt_uint32_t n=0;
  double ftemp=0;
  for(j=0;j<ADC_V_DMA_BufferSize;j+=1)
  {
    ADCConvertedValue_V[j]=ltc1865_read_ch(1,1);
//    rt_kprintf("vadc=%d\n",ADCConvertedValue_V[j]);
  }
  for(j=0;j<=ADC_V_DMA_BufferSize;j+=1)
  {
    for (i=0;i<ADC_V_DMA_BufferSize-j;i+=1)
    {
      if (ADCConvertedValue_V[i]>ADCConvertedValue_V[i+1])
      {
        temp=ADCConvertedValue_V[i];
        ADCConvertedValue_V[i]=ADCConvertedValue_V[i+1];
        ADCConvertedValue_V[i+1]=temp;
      }
    }
  }
  for(i=ADC_V_DMA_BufferSize>>2;i<(ADC_V_DMA_BufferSize>>2)*3;i+=1)
  {
    n+=ADCConvertedValue_V[i];
  }
//  rt_kprintf("vn=%d\n",n);
  ftemp=((n>>5)*3298)>>16;  
  V=(rt_int16_t)ftemp;
  return &V;
}
void measure_R(void)
{
  GPIO_ResetBits(GPIOA,GPIO_Pin_1);//关断短路MOSFET
  GPIO_SetBits(GPIOA,GPIO_Pin_2);  //闭合继电器
  delay_nus(10000);
  rt_int16_t r;
  float v;
  v=*Get_V();
  r= (rt_int16_t)((2500/v-1.0)*990);
  GPIO_SetBits(GPIOA,GPIO_Pin_1);//MOSFET短路1kohm电阻
  GPIO_ResetBits(GPIOA,GPIO_Pin_2);  //关断继电器
  rt_sprintf(R_value, "%dΩ", r);
  delay_nus(10000);
  rt_kprintf("v=%d\nr=%d\n",v,r);    
#if 0  
  if(r>999)
  {
    
    R_value[5]='\0';
  }
  else
  {
    R_value[4]='\0';
  }
#endif  
}


 
void set_24V(void)
{
  GPIO_SetBits(GPIOA,GPIO_Pin_3); 
}

void reset_24V(void)
{
  GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}

void set_110V(void)
{
  GPIO_SetBits(GPIOA,GPIO_Pin_3);
  GPIO_SetBits(GPIOB,GPIO_Pin_0); 
  GPIO_SetBits(GPIOB,GPIO_Pin_1); 
}

void reset_110V(void)
{
  GPIO_ResetBits(GPIOA,GPIO_Pin_3);
  GPIO_ResetBits(GPIOB,GPIO_Pin_0); 
  GPIO_ResetBits(GPIOB,GPIO_Pin_1); 
}




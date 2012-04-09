

#include"analog.h"



rt_uint8_t Scan_Channels[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//扫描通道


rt_int16_t R=0,V=0;

rt_uint16_t ADCConvertedValue_R[ADC_R_DMA_BufferSize];
rt_uint16_t ADCConvertedValue_V[ADC_V_DMA_BufferSize];

rt_uint8_t     auto_scan_flag=0xff;
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
  R=(rt_int16_t)((n/32*3298/65356*1.00565+10.2712)/1.86);
  R=(rt_int16_t)(R*0.985-280);
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
  V=(rt_int16_t)(n/32*3298/65356);
  V=(rt_int16_t)(V*1.00565+10.2712);
  if(V<0)
  {
    V=0;
  }
  return &V;  
}


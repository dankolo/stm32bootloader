

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


void ADC_GPIO_Config(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  
  
}





void ADC_R_Config(void)
{
  RCC_ADCCLKConfig(RCC_PCLK2_Div8);
  RCC_APB2PeriphClockCmd(ADC_R_RCC, ENABLE);
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitTypeDef ADC_InitStructure;

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC_R, &ADC_InitStructure);

  /* ADC_R regular channel1 configuration */
  ADC_RegularChannelConfig(ADC_R, ADC_Channel_13, 1, ADC_SampleTime_239Cycles5);
  /* ADC_R regular channel2 configuration */
//  ADC_RegularChannelConfig(ADC_R, ADC_Channel_12, 2, ADC_SampleTime_239Cycles5);//

  /* Enable ADC_R DMA */
  ADC_DMACmd(ADC_R, ENABLE);
  /* Enable ADC_R */
  ADC_Cmd(ADC_R, ENABLE);

  /* Enable ADC_R reset calibaration register */
  ADC_ResetCalibration(ADC_R);
  /* Check the end of ADC_R reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC_R));
    /* Start ADC_R calibaration */
  ADC_StartCalibration(ADC_R);
  /* Check the end of ADC_R calibration */
  while(ADC_GetCalibrationStatus(ADC_R));
  /* Start ADC_R Software Conversion */
  ADC_SoftwareStartConvCmd(ADC_R, ENABLE);
}




void ADC_V_Config(void)
{
//  RCC_ADCCLKConfig(RCC_PCLK2_Div4);
  RCC_APB2PeriphClockCmd(ADC_V_RCC, ENABLE);
  /* ADC configuration ------------------------------------------------------*/
  ADC_InitTypeDef ADC_InitStructure;

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC_V, &ADC_InitStructure);

  /* ADC regular channel8 configuration */
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_239Cycles5);
  /* ADC regular channel9 configuration */
  ADC_RegularChannelConfig(ADC_V, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);

  /* Enable ADC_V DMA */
  ADC_DMACmd(ADC_V, ENABLE);
  /* Enable ADC_V */
  ADC_Cmd(ADC_V, ENABLE);

  /* Enable ADC_V reset calibaration register */
  ADC_ResetCalibration(ADC_V);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC_V));
    /* Start ADC_V calibaration */
  ADC_StartCalibration(ADC_V);
  /* Check the end of ADC_V calibration */
  while(ADC_GetCalibrationStatus(ADC_V));
  /* Start ADC_V Software Conversion */
  ADC_SoftwareStartConvCmd(ADC_V, ENABLE);
}


void ADC_R_DMA_Config(void)
{
  RCC_AHBPeriphClockCmd(ADC_R_DMA_RCC, ENABLE);
  DMA_InitTypeDef DMA_InitStructure;

  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(ADC_R_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_R_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue_R;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = ADC_R_DMA_BufferSize;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(ADC_R_DMA_Channel, &DMA_InitStructure);

  /* Enable DMA1 channel1 */
  DMA_Cmd(ADC_R_DMA_Channel, ENABLE);
//  DMA_ITConfig(ADC_R_DMA_Channel,DMA_IT_TC,ENABLE);
}




void ADC_V_DMA_Config(void)
{
  RCC_AHBPeriphClockCmd(ADC_V_DMA_RCC, ENABLE);
  DMA_InitTypeDef DMA_InitStructure;

  /* DMA2 channel5 configuration ----------------------------------------------*/
  DMA_DeInit(ADC_V_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_V_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue_V;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = ADC_V_DMA_BufferSize;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(ADC_V_DMA_Channel, &DMA_InitStructure);

  /* Enable DMA2 channel5 */
  DMA_Cmd(ADC_V_DMA_Channel, ENABLE);
//  DMA_ITConfig(ADC_V_DMA_Channel,DMA_IT_TC,ENABLE);
}




rt_int16_t *Get_ADC_R_Value()
{

  u16 j=0,i=0,temp=0;
  u32 n=0;
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
  R=(rt_int16_t)((double)((n*2492)>>16)/1.86);
  R=(rt_int16_t)(((double)R)*0.98835-245 );
  if(R<0)
  {
    R=0;
  }
//  rt_kprintf("R=%d\r\n",V);
//  ADC_R_Value[0]=R/1000+'0';
//  ADC_R_Value[1]=(R%1000)/100+'0';
//  ADC_R_Value[2]=(R%100)/10+'0';
//  ADC_R_Value[3]=R%10+'0';
  return &R;
}




rt_int16_t *Get_ADC_V_Value()
{

  u16 j=0,i=0;
  vu32 n=0,temp=0;

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
//  rt_kprintf("n=%d\r\n",(n>>4));
  V=(rt_int16_t)((n*2492)>>16)-22;
  n=0;
//ADC_V_Value[0]=V/10000+'0';
//  if(ADC_V_Value[0]=='0')
//  {
//    ADC_V_Value[0]=' ';
//  }
//  ADC_V_Value[1]=(V%10000)/1000+'0';
//  ADC_V_Value[2]='.';
//  ADC_V_Value[3]=(V%1000)/100+'0';
//  ADC_V_Value[4]=(V%100)/10+'0';
//  ADC_V_Value[5]='V';
//  ADC_V_Value[6]='\0';
  if(V<0)
  {
    V=0;
  }
//  rt_kprintf("V=%d\r\n",V);
  return &V;
  
}


void ADC_R_stop(void)
{ 
  ADC_DMACmd(ADC_R, DISABLE);
  ADC_Cmd(ADC_R, DISABLE);
  ADC_SoftwareStartConvCmd(ADC_R, DISABLE);
}


void ADC_V_stop(void)
{ 
  ADC_DMACmd(ADC_V, DISABLE);
  ADC_Cmd(ADC_V, DISABLE);
  ADC_SoftwareStartConvCmd(ADC_V, DISABLE);
}
void ADC_R_Restart(void)
{ 
  ADC_DMACmd(ADC_R, ENABLE);
  ADC_Cmd(ADC_R, ENABLE);
  ADC_SoftwareStartConvCmd(ADC_R, ENABLE);
}
void ADC_V_Restart(void)
{ 
  ADC_DMACmd(ADC_V, ENABLE);
  ADC_Cmd(ADC_V, ENABLE);
  ADC_SoftwareStartConvCmd(ADC_V, ENABLE);
}







#include "commonality.h"


struct tm time_now;
unsigned char time_buffer[20]="2010-11-13 20:47:30";

unsigned char ADC_Value[12];

vu16 ADCConvertedValue[1024];

void delay_nus(vu32 nCount)
{
  u16 TIMCounter = nCount;
  TIM_Cmd(TIM2, ENABLE);
  TIM_SetCounter(TIM2, TIMCounter);
  while (TIMCounter)
  {
    TIMCounter = TIM_GetCounter(TIM2);
  }
  TIM_Cmd(TIM2, DISABLE);
}

void delay_long(void)
{
  unsigned long x=0xffff;
    while(x>0)
    {--x;}
}


unsigned char *Get_ADC1_Value()
{

  u16 j=0,i=0;
  vu32 k=0,n=0,temp=0;

  for(j=0;j<=1024;j+=2)
  {
    for (i=0;i<1024-j;i+=2)
    {
      if (ADCConvertedValue[i]>ADCConvertedValue[i+2])
      {
        temp=ADCConvertedValue[i];
        ADCConvertedValue[i]=ADCConvertedValue[i+2];
        ADCConvertedValue[i+2]=temp;
      }
    }
  }
  for(i=256;i<768;i+=2)
  {
    n+=(vu32)ADCConvertedValue[i+2];
  }
//  printf("___%d,",n);
  k= (vu32)(n/256*1000/4095*3.332/10/0.196);// n/256*1000/4095*3.332/10/0.196;
  n=0;
  ADC_Value[0]=k/1000+'0';
  ADC_Value[1]='.';
    ADC_Value[2]=(k%1000)/100+'0';
      ADC_Value[3]=(k%100)/10+'0';
        ADC_Value[4]=k%10+'0';
          ADC_Value[5]='\0';
  if(ADC_Value[0]=='1'&&ADC_Value[2]=='6')
  {
  ADC_Value[0]='O';
  ADC_Value[1]='p';
    ADC_Value[2]='e';
      ADC_Value[3]='n';
        ADC_Value[4]='!';
          ADC_Value[5]='\0';
  }

  for(j=0;j<=1024;j+=2)
  {
    for (i=0;i<1024-j;i+=2)
    {
      if (ADCConvertedValue[i]>ADCConvertedValue[i+2])
      {
        temp=ADCConvertedValue[i];
        ADCConvertedValue[i]=ADCConvertedValue[i+2];
        ADCConvertedValue[i+2]=temp;
      }
    }
  }
  for(i=257;i<768;i+=2)
  {
    n+=ADCConvertedValue[i+2];
  }
//  printf("%d\t\r",n);
  k=(vu32)(n/256*1000/4095*3.332);// n/256/4095*3.332*1000;
//  printf("%d\t\r",k);
  n=0;
  ADC_Value[6]=k/1000+'0';
  ADC_Value[7]='.';
    ADC_Value[8]=(k%1000)/100+'0';
      ADC_Value[9]=(k%100)/10+'0';
        ADC_Value[10]=k%10+'0';
          ADC_Value[11]='\0';
  return ADC_Value;
}



void ADC1_Config(void)
{
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitTypeDef ADC_InitStructure;

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 2;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel8 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_239Cycles5);
  /* ADC1 regular channel9 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_239Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
    /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void ADC1_DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1024;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);

  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
}

void ADC1_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PB.00 (ADC Channel8 9) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}



void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;
  //使能外部晶振
  RCC_HSEConfig(RCC_HSE_ON);
  //等待外部晶振稳定
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  //如果外部晶振启动成功，则进行下一步操作
  if (HSEStartUpStatus==SUCCESS)
  {
    //FLASH时序控制
    //推荐值：SYSCLK = 0~24MHz   Latency=0
    //        SYSCLK = 24~48MHz  Latency=1
    //        SYSCLK = 48~72MHz  Latency=2
    FLASH_SetLatency(FLASH_Latency_2);
    //开启FLASH预取指功能
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    //预分频2 HSE25M/5=5M
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    //锁相环2 5M*8=40M
    RCC_PLL2Cmd(DISABLE);
    RCC_PLL2Config(RCC_PLL2Mul_8);
    //开启锁相环2
    RCC_PLL2Cmd(ENABLE);
    //预分频1 40M/5=8M
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2,RCC_PREDIV1_Div5);
    //PLL设置 8M*9 = 72MHz
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
    //USB时钟
    RCC_OTGFSCLKConfig(RCC_OTGFSCLKSource_PLLVCO_Div3);
    RCC_PLL3Cmd(DISABLE);
    RCC_PLL3Config(RCC_PLL3Mul_10);
    RCC_PLL3Cmd(ENABLE);
    //以太网时钟MII模式
    RCC_MCOConfig(RCC_MCO_XT1);
    //设置HCLK（AHB时钟）=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    //PCLK1(APB1) = HCLK/2
    RCC_PCLK1Config(RCC_HCLK_Div2);
    //PCLK2(APB2) = HCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);
    //ADC时钟72M/6
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    //启动PLL
    RCC_PLLCmd(ENABLE);
    //等待PLL稳定
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    //系统时钟SYSCLK来自PLL输出
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    //切换时钟后等待系统时钟稳定
    while (RCC_GetSYSCLKSource()!=0x08);
  }
  return;
}



void NVIC_Config(void)
{
#ifdef RAM_DEBUG
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0);
#endif
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//优先级分到第0组 总共5组		
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //使用外部中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//阶级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 //阶层0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


}


void EXTI_Config(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  // Configure EXTI Line5 to generate an interrupt on falling edge
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);//PC5作为外部中断引
}
void TP_EXTI_DISABLE(void)
{
  (*((uint32_t*)0x40010400))=(*((uint32_t*)0x40010400))&~(1<<5);
}
void TP_EXTI_ENABLE(void)
{
  (*((uint32_t*)0x40010400))=(*((uint32_t*)0x40010400))|1<<5;
}

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

void USART1_Init()
{
  /* USARTx configured as follow:
        - BaudRate = 9600 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable UART clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init( GPIOA, &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(USART1, &USART_InitStructure);

  /*********************************************/
  //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  /*********************************************/

  /* Enable USART */
  USART_Cmd(USART1, ENABLE);
}

void CD4067_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
  GPIO_Init(GPIOD,&GPIO_InitStructure);

}




void draw_choosemodel(void)
{
  ili9320_Clear(Black);//清屏
  ili9320_PutCN(104,0,"选择实验型号",Cyan,Black);
  ili9320_writestr(0, 16, "SS4G_TKS9",Cyan,Black);
  ili9320_writestr(0, 64, "TKS14A_I",Cyan,Black);
  ili9320_writestr(0, 112, "TKS14A_II",Cyan,Black);
  ili9320_writestr(0, 160, "TKS15A_I",Cyan,Black);
  ili9320_writestr(0, 208, "TKS15A_II",Cyan,Black);
  ili9320_writestr(104, 16, "SS7E_QS1_3",Cyan,Black);
  ili9320_writestr(104, 64, "TKS231_1_II",Cyan,Black);
  ili9320_writestr(104, 112, "TTKS31",Cyan,Black);
  ili9320_writestr(104, 160, "TKS32",Cyan,Black);
//  ili9320_writestr(104, 208, "   ",Cyan,Black);
//  ili9320_writestr(216, 16, "   ",Cyan,Black);
//  ili9320_writestr(216, 64, "  ",Cyan,Black);
//  ili9320_writestr(216, 112, "  I",Cyan,Black);
//  ili9320_writestr(216, 160, "  ",Cyan,Black);
  write_str16(216, 160, "设置时间",Cyan,Black);
}


unsigned char *get_time_now()
{

  time_now = Time_GetCalendarTime();//获得当前时间
  //转换年月日时分秒
  time_buffer[0]=time_now.tm_year/1000+'0';
  time_buffer[1]=(time_now.tm_year%1000)/100+'0';
  time_buffer[2]=(time_now.tm_year%100)/10+'0';
  time_buffer[3]=time_now.tm_year%10+'0';
  //年
  time_buffer[5]=((time_now.tm_mon+1)%100)/10+'0';
  time_buffer[6]=(time_now.tm_mon+1)%10+'0';
  //月,时间戳是0-11,显示+1
  time_buffer[8]=(time_now.tm_mday%100)/10+'0';
  time_buffer[9]=time_now.tm_mday%10+'0';
  //日
  time_buffer[11]=(time_now.tm_hour%100)/10+'0';
  time_buffer[12]=time_now.tm_hour%10+'0';
  //时
  time_buffer[14]=(time_now.tm_min%100)/10+'0';
  time_buffer[15]=time_now.tm_min%10+'0';
  //分
  time_buffer[17]=(time_now.tm_sec%100)/10+'0';
  time_buffer[18]=time_now.tm_sec%10+'0';
  //秒

  return time_buffer;
}

void LCD_Set_Time(unsigned char *set_buffer)
{
  time_now.tm_year = (*set_buffer-'0')*1000+(*(set_buffer+1)-'0')*100+(*(set_buffer+2)-'0')*10+(*(set_buffer+3)-'0');
  time_now.tm_mon =  (*(set_buffer+5)-'0')*10+(*(set_buffer+6)-'0'-1);
  time_now.tm_mday = (*(set_buffer+8)-'0')*10+(*(set_buffer+9)-'0');
  time_now.tm_hour = (*(set_buffer+11)-'0')*10+(*(set_buffer+12)-'0');
  time_now.tm_min =  (*(set_buffer+14)-'0')*10+(*(set_buffer+15)-'0');
  time_now.tm_sec =  (*(set_buffer+17)-'0')*10+(*(set_buffer+18)-'0');
  Time_SetCalendarTime(time_now);
}

unsigned int time_coordinate[14][4]={
{84,5,92,20},{92,5,100,20},{100,5,108,20},{108,5,116,20},
{124,5,132,20},{132,5,140,20},
{148,5,156,20},{156,5,164,20},
{172,5,180,20},{180,5,188,20},
{196,5,204,20},{204,5,212,20},
{220,5,228,20},{228,5,235,20},
};
unsigned int action_tp[5][4]={
{130,20,190,80},{60,90,120,150},{130,90,190,150},{200,90,260,150},{130,160,190,220}
};//up,left,ok,right,down
enum action{up,left,ok,right,down};
unsigned char time_set_flag=0,key_flag=0xff;
unsigned char time_bit[14]={0,1,2,3,5,6,8,9,11,12,14,15,17,18};
void draw_time_manger(void)
{
  BMP_view((const XCHAR*)"/",(const XCHAR*)"time.bmp",0,239);
  ili9320_writestr(84,5,get_time_now(),Cyan,Black);
}


void time_manager(int x,int y)
{
//  printf("\r\nx=%d,y=%d",x,y);
  unsigned char n;
  for(n=0;n<5;n++)
  {
    if(x>action_tp[n][0]&&x<action_tp[n][2]&&y>action_tp[n][1]&&y<action_tp[n][3])
    {
      key_flag=n;
    }
  }
//  printf("\r\n%d",n);
  switch(key_flag)
  {
  case up:
    {
//      printf("\r\nup");
      if((time_buffer[time_bit[time_set_flag]]=='0')||(time_buffer[time_bit[time_set_flag]]>'0')&&(time_buffer[time_bit[time_set_flag]]<'9'))
      {
        time_buffer[time_bit[time_set_flag]]+=1;
        ili9320_writestr(84,5,time_buffer,Cyan,Black);
        GUI_Rectangle(time_coordinate[time_set_flag][0],time_coordinate[time_set_flag][1],time_coordinate[time_set_flag][2],time_coordinate[time_set_flag][3],Red,0);
      }
      else
      {
        time_buffer[time_bit[time_set_flag]]='0';
        ili9320_writestr(84,5,time_buffer,Cyan,Black);
        GUI_Rectangle(time_coordinate[time_set_flag][0],time_coordinate[time_set_flag][1],time_coordinate[time_set_flag][2],time_coordinate[time_set_flag][3],Red,0);
      }
      break;
    }
  case left:
    {
//      printf("\r\nleft");
      if(time_set_flag>0&&time_set_flag<=13)
      {
        time_set_flag-=1;
        ili9320_writestr(84,5,time_buffer,Cyan,Black);
        GUI_Rectangle(time_coordinate[time_set_flag][0],time_coordinate[time_set_flag][1],time_coordinate[time_set_flag][2],time_coordinate[time_set_flag][3],Red,0);
      }
      else
      {
        time_set_flag=0;
        ili9320_writestr(84,5,time_buffer,Cyan,Black);
        GUI_Rectangle(time_coordinate[time_set_flag][0],time_coordinate[time_set_flag][1],time_coordinate[time_set_flag][2],time_coordinate[time_set_flag][3],Red,0);
      }
      break;
    }
  case ok:
    {
//      printf("\r\nok");
      LCD_Set_Time(time_buffer);
      ili9320_writestr(84,5,time_buffer,Cyan,Black);
      break;
    }
  case right:
    {
//      printf("\r\nright");
      if((time_set_flag==0)||(time_set_flag>0)&&(time_set_flag<13))
      {
        time_set_flag+=1;
        ili9320_writestr(84,5,time_buffer,Cyan,Black);
        GUI_Rectangle(time_coordinate[time_set_flag][0],time_coordinate[time_set_flag][1],time_coordinate[time_set_flag][2],time_coordinate[time_set_flag][3],Red,0);
      }
      else
      {
        time_set_flag=0;
        ili9320_writestr(84,5,time_buffer,Cyan,Black);
        GUI_Rectangle(time_coordinate[time_set_flag][0],time_coordinate[time_set_flag][1],time_coordinate[time_set_flag][2],time_coordinate[time_set_flag][3],Red,0);
      }
      break;
    }
  case down:
    {
//      printf("\r\ndown");
      if((time_buffer[time_bit[time_set_flag]]>'0')&&(time_buffer[time_bit[time_set_flag]]<='9'))
      {
        time_buffer[time_bit[time_set_flag]]-=1;
        ili9320_writestr(84,5,time_buffer,Cyan,Black);
        GUI_Rectangle(time_coordinate[time_set_flag][0],time_coordinate[time_set_flag][1],time_coordinate[time_set_flag][2],time_coordinate[time_set_flag][3],Red,0);
      }
      else
      {
        time_buffer[time_bit[time_set_flag]]='0';
        ili9320_writestr(84,5,time_buffer,Cyan,Black);
        GUI_Rectangle(time_coordinate[time_set_flag][0],time_coordinate[time_set_flag][1],time_coordinate[time_set_flag][2],time_coordinate[time_set_flag][3],Red,0);
      }
      break;
    }
  default:break;
  }
}


#include "touch.h"



void Touch_Config(void) 
{ 
  GPIO_InitTypeDef  GPIO_InitStructure; 
  //GPIOC AFIO clock enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  //SPI1 Remap enable
//  GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE );

  //Configure SPI1 pins: SCK and MOSI 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽输出
  GPIO_Init(GPIOA,&GPIO_InitStructure); 

  //Configure SPI1 pins: MISO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //上拉输入
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  //Configure TP_PINS:TP_CS PF10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
  GPIO_Init(GPIOF,&GPIO_InitStructure);	
 
  
  /***PB10->TOUCH-INT***/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_10);
   
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);//PB10作为外部中断引 

  // SPI1 Config
  //SPI1 Periph clock enable 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
  /* DISABLE SPI1 必须先禁止*/
  SPI_Cmd(SPI1, DISABLE);
  SPI_InitTypeDef   SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //SPI_NSS_Hard
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
  SPI_InitStructure.SPI_CRCPolynomial = 7; 
  SPI_Init(SPI1,&SPI_InitStructure); 

  // SPI1 enable  
  SPI_Cmd(SPI1,ENABLE);  
}

unsigned char SPI_WriteByte(unsigned char data) 
{ 
 unsigned char Data = 0; 

   //Wait until the transmit buffer is empty 
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET); 
  // Send the byte  
  SPI_I2S_SendData(SPI1,data); 

   //Wait until a data is received 
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET); 
  // Get the received data 
  Data = SPI_I2S_ReceiveData(SPI1); 

  // Return the shifted data 
  return Data; 
}  
void SpiDelay(unsigned int DelayCnt)
{
 unsigned int i;
 for(i=0;i<DelayCnt;i++);
}

int16_t TPReadX(void)
{ 
   u16 x=0;
   TP_CS();
   SpiDelay(10);
   SPI_WriteByte(CHX);
   SpiDelay(10);
   x=SPI_WriteByte(0x00);
   x<<=8;
   x+=SPI_WriteByte(0x00);
   SpiDelay(10);
   TP_DCS(); 
   x = x>>3;
   return (x);
}

int16_t TPReadY(void)
{
  u16 y=0;
  TP_CS();
  SpiDelay(10);
  SPI_WriteByte(CHY);
  SpiDelay(10);
  y=SPI_WriteByte(0x00);
  y<<=8;
  y+=SPI_WriteByte(0x00);
  SpiDelay(10);
  TP_DCS();
  y = y>>3; 
  return (y);
}


int16_t  TP_MeasureX(void) 
{
  unsigned char t=0,t1,count=0;
  int16_t databuffer[16]={0};//数据组
  int16_t temp=0,X=0;
  uint32_t sum=0;
  while(/*GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0&&*/count<16)//循环读数10次
  {
    databuffer[count]=TPReadX();
    count++;
  }
  if(count==16)//一定要读到10次数据,否则丢弃
  {
    do//将数据X升序排列
    {
      t1=0;
      for(t=0;t<count-1;t++)
      {
        if(databuffer[t]>databuffer[t+1])//升序排列
        {
          temp=databuffer[t+1];
          databuffer[t+1]=databuffer[t];
          databuffer[t]=temp;
          t1=1;
        }
      }
    }
    while(t1);
    for(t=4;t<12;t++)
    {
      sum+=databuffer[t];
    }
    //X=sum/8;
    X=799-(int16_t)((sum/8-210)*0.2130);
  }
  return(X);  
}

int16_t  TP_MeasureY(void) 
{
  unsigned char t=0,t1,count=0;
  int16_t databuffer[16]={0};//数据组
  int16_t temp=0,Y=0;
  uint32_t sum=0;
  while(/*GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0&&*/count<16)	//循环读数10次
  {
    databuffer[count]=TPReadY();
    count++;
  }
  if(count==16)//一定要读到10次数据,否则丢弃
  {
    do//将数据X升序排列
    {
      t1=0;
      for(t=0;t<count-1;t++)
      {
        if(databuffer[t]>databuffer[t+1])//升序排列
        {
          temp=databuffer[t+1];
          databuffer[t+1]=databuffer[t];
          databuffer[t]=temp;
          t1=1; 
        }
      }
    }
    while(t1);
    for(t=4;t<12;t++)
    {
      sum+=databuffer[t];
    }
    //Y=sum/8;
    Y=(int16_t)((sum/8-340)*0.13575);
  }
  return(Y); 
}



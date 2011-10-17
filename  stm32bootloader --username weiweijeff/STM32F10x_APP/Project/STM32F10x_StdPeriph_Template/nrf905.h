#ifndef __NRF905_H
#define __NRF905_H


#include "stm32f10x_conf.h"
#include "stm32f10x.h"

//�ر�SPI_CS
#define     SPI_DIS              GPIO_SetBits(GPIOA,GPIO_Pin_4)
//ʹ��SPI_CS
#define     SPI_EN               GPIO_ResetBits(GPIOA,GPIO_Pin_4)
//ģ���ϵ�ʹ��
#define     NRF905_POWERON       GPIO_SetBits(GPIOD,GPIO_Pin_4)
//
#define     NRF905_POWEROFF      GPIO_ResetBits(GPIOD,GPIO_Pin_4)
//����ΪTXģʽ
#define     SET_TX               GPIO_SetBits(GPIOD,GPIO_Pin_2)
//����ΪRXģʽ
#define     SET_RX               GPIO_ResetBits(GPIOD,GPIO_Pin_2)
//�շ�ʹ��
#define     TRX_EN               GPIO_SetBits(GPIOD,GPIO_Pin_3)
//
#define     TRX_DIS              GPIO_ResetBits(GPIOD,GPIO_Pin_3)
//=====================================================
//CD,DR,AMΪ״̬�˿�,P2.0,P2.1,P2.2����Ϊ
//����˿�
//=====================================================
//#define     CD  //�����ز����
//�ȴ����ݾ���
#define     WaitDRReady() while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)==0)
//��ȡDR
#define     READ_DR       GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)
//��ȡAM
#define     READ_AM       GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)

//=====================================================
//nRF905 SPI���нӿ�ָ������
//
//=====================================================
//û��Read RX_ADDRSS command�ĵ�ַ,��ô������ȡ????
#define     WC	      0x00		// Write configuration register command
#define     RC	      0x10 		// Read  configuration register command
#define     WTP	      0x20 		// Write TX Payload  command
#define     RTP	      0x21		// Read  TX Payload  command
#define     WTA	      0x22		// Write TX Address  command
#define     RTA	      0x23		// Read  TX Address  command
#define     RRP	      0x24		// Read  RX Payload  command


unsigned char TxBuf[32]={1,2,3,4,5,6,7,8,9};
unsigned char RxBuf[32];
//=====================================================
//RF-Configuration Register
//���üĴ�����10 bytes
//=====================================================



/*******************************************************************************
*******************************************************************************/



typedef struct RFconfig
{
    unsigned char n;
    
    unsigned char buf[10];
    
}RFconfig;
//=====================================================
RFconfig  RxTxconf =
{
	10,
	0x4c,  
	0x3c,     //���ط�,433.2MHz,6dBm,����ģʽ
	0x44,     //�շ���4�ֽڵ�ַ���
	0x20,
	0x20,     //�շ���Ч���ݿ��32λ
	0xcc,
	0xcc,
	0xcc,
	0xcc,     //���ջ���ַ 
	0x18      //16λCRCУ��,����У��,����16MHz,û���ⲿʱ��
};


void NRF905_Init(void) 
{ 
  GPIO_InitTypeDef  GPIO_InitStructure; 
  //GPIOA AFIO clock enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD| RCC_APB2Periph_AFIO, ENABLE);
  //SPI1  Remap enable
  //GPIO_PinRemapConfig(GPIO_Remap_SPI1 , ENABLE );
  
  //Configure DR 0  AM 1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
  GPIO_Init(GPIOD,&GPIO_InitStructure);
  
  //Configure TX_EN 2 TRX_CE 3  PWR_UP 4 led 7
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4|GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
  GPIO_Init(GPIOD,&GPIO_InitStructure);	

  //Configure SPI1  pins: SCK MISO and MOSI 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //�����������
  GPIO_Init(GPIOA,&GPIO_InitStructure); 

  
  //Configure SPI1_NSS(CS) 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
  GPIO_Init(GPIOA,&GPIO_InitStructure);	 
  
  
  // SPI1  Config
  //SPI1  Periph clock enable 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);
  /* DISABLE SPI1  �����Ƚ�ֹ*/
  SPI_Cmd(SPI1 , DISABLE);
  SPI_InitTypeDef   SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
  SPI_InitStructure.SPI_CRCPolynomial = 7; 
  SPI_Init(SPI1 ,&SPI_InitStructure); 

  // SPI1 enable  
  SPI_Cmd(SPI1 ,ENABLE);  
}

unsigned char NRF905_SPI_ReadWrite(unsigned char data) 
{ 
  //Wait until the transmit buffer is empty 
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET); 
  // Send the byte  
  SPI_I2S_SendData(SPI1,data); 
   //Wait until a data is received 
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET); 
  
  
  // Return the shifted data 
  return SPI_I2S_ReceiveData(SPI1); 
} 


//=====================================================
//����ͨ��SPI�ӿ���905���üĴ���д��������Ϣ
//=====================================================
void Config905(void)
{
    unsigned int i;
    SPI_EN;
    NRF905_SPI_ReadWrite(WC);
    for(i=0;i<RxTxconf.n;i++)
    {
        NRF905_SPI_ReadWrite(RxTxconf.buf[i]);
    }
    SPI_DIS;
}


//=====================================================
//ʹ��905��������
//
//=====================================================
void TxPacket(void)
{
    unsigned int i;
    SPI_EN;
    NRF905_SPI_ReadWrite(WTP);
    for(i=0;i<32;i++)
    {
        NRF905_SPI_ReadWrite(TxBuf[i]);
    }
    SPI_DIS;
    //Delay_100us(1);//
    SPI_EN;
    NRF905_SPI_ReadWrite(WTA);
    for(i=0;i<4;i++)
    {
        NRF905_SPI_ReadWrite(RxTxconf.buf[i+5]);
    }
    SPI_DIS;
    TRX_EN;
    //Delay_100us(1);//
    TRX_DIS;
}
//=====================================================
//ʹ��905��������
//
//=====================================================
void RxPacket(void)
{
    unsigned char i;
    TRX_DIS;                      //����905�������ģʽ
    SPI_EN;
    NRF905_SPI_ReadWrite(RRP);                 //׼����ȡ���յ�������
    for(i=0;i<32;i++)
    {
        RxBuf[i] = NRF905_SPI_ReadWrite(0xff);       //ͨ��SPI�ڴ�905��ȡ����
    }
    SPI_DIS;
    while(READ_DR||READ_AM);
    TRX_EN;  
    
}
//=====================================================
//����905Ϊ����ģʽ
//
//=====================================================
void SetTxMode(void)
{
  NRF905_POWERON;
  SET_TX;
  TRX_EN;
  //Delay_100us(10);                         //delay for mode change(>=650us)
}
//=====================================================
//����905Ϊ����ģʽ
//
//=====================================================
void SetRxMode(void)
{
  NRF905_POWERON;
  SET_RX;
  TRX_EN;
  //Delay_100us(10);                         //delay for mode change(>=650us)
}
void SetStandbyMode(void)
{
  NRF905_POWERON;
  TRX_DIS;
}
#endif
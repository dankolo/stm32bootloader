


#include"ltc1865.h"


static void delay_nus(rt_int16_t n)
{
  n=n*8;
  while(--n);
}



static void ltc1865_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIO Periph clock */
  RCC_APB2PeriphClockCmd(LTC1865_GPIO_CLK | LTC1865_GPIO_CLK,ENABLE);
  
  /* Configure SPI pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = LTC1865_SPI_PIN_SCK | LTC1865_SPI_PIN_MISO | LTC1865_SPI_PIN_MOSI;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(LTC1865_SPI_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = LTC1865_PIN_CONV;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LTC1865_GPIO, &GPIO_InitStructure);
}



static void ltc1865_spi_config(void)
{
  SPI_InitTypeDef SPI_InitStructure;

  /* Enable SPI1 Periph clock */
  RCC_APB2PeriphClockCmd(LTC1865_SPI_CLK,ENABLE);


  /*------------------------ SPI1 configuration ------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS  = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;/* 72M/64=1.125M */
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;

  SPI_I2S_DeInit(LTC1865_SPI);
  SPI_Init(LTC1865_SPI, &SPI_InitStructure);

  /* Enable SPI_MASTER */
  SPI_Cmd(LTC1865_SPI, ENABLE);
  SPI_CalculateCRC(LTC1865_SPI, DISABLE);
}



static uint8_t ltc1865_read_wite_byte(uint8_t wdata)
{
  while(SPI_I2S_GetFlagStatus(LTC1865_SPI, SPI_I2S_FLAG_TXE) == RESET);		// Transmit buffer empty?  
  SPI_I2S_SendData(LTC1865_SPI, wdata);		                                        // send 1 byte data
  while(SPI_I2S_GetFlagStatus(LTC1865_SPI, SPI_I2S_FLAG_RXNE) == RESET);	        //Receive buffer not empty?
  return SPI_I2S_ReceiveData(LTC1865_SPI);
}



static void ltc1865_conv(rt_uint8_t a)
{
  if(a)
  {
    GPIO_SetBits(LTC1865_GPIO, LTC1865_PIN_CONV);
  }
  else
  {
    GPIO_ResetBits(LTC1865_GPIO, LTC1865_PIN_CONV);
  }
}

void ltc1865_init(void)
{
  ltc1865_gpio_config();
  ltc1865_spi_config();
}
//mode 1:SINGLE-ENDED 0:DIFFERENTIAL 
//ch:0/1

rt_uint16_t ltc1865_read_ch(rt_uint8_t mode ,rt_uint8_t ch)
{
  rt_uint16_t data=0;

  ltc1865_conv(0);
  delay_nus(10);
  ltc1865_read_wite_byte(((mode&0x01)<<7)|((ch&0x01)<<6));
  delay_nus(10);
  ltc1865_conv(1);
  delay_nus(10);
  ltc1865_conv(0);
  delay_nus(10);
  data=ltc1865_read_wite_byte(0xff);
  data=(data<<8)|(ltc1865_read_wite_byte(0xff));
  ltc1865_conv(1);
//  data=(data*3298)>>16;
//  rt_kprintf("adc=%d\n",data);
  return data;
}

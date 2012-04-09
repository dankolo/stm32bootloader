
#include "stm32f10x.h"
#include <rtthread.h>
#include "vs1053b.h"




uint16_t    sci_mode=0x0800;

void vs1053b_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIO Periph clock */
  RCC_APB2PeriphClockCmd(VS1053B_GPIO_CLK | VS1053B_GPIO_CLK,ENABLE);
  
  /* Configure SPI pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = VS1053B_SPI_PIN_SCK | VS1053B_SPI_PIN_MISO | VS1053B_SPI_PIN_MOSI;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(VS1053B_SPI_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = VS1053B_PIN_XDCS | VS1053B_PIN_XCS | VS1053B_PIN_XRESET;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(VS1053B_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin =  VS1053B_PIN_DREQ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(VS1053B_GPIO, &GPIO_InitStructure);
}

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* DMA IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void VS1053B_SPI_DMA_Config(uint32_t addr)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    DMA_InitTypeDef DMA_InitStructure;

    /* DMA Channel configuration ----------------------------------------------*/
    DMA_Cmd(VS1053B_SPI_DMA, DISABLE);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(VS1053B_SPI_DR_ADDRESS);
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32) addr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(VS1053B_SPI_DMA, &DMA_InitStructure);

    /* Enable SPI DMA Tx request */
    SPI_I2S_DMACmd(VS1053B_SPI, SPI_I2S_DMAReq_Tx, ENABLE);

//    DMA_ITConfig(VS1053B_SPI_DMA, DMA_IT_TC, ENABLE);
    DMA_Cmd(VS1053B_SPI_DMA, ENABLE);
}


void vs1053b_spi_config(void)
{
  SPI_InitTypeDef SPI_InitStructure;

  /* Enable SPI1 Periph clock */
  RCC_APB2PeriphClockCmd(VS1053B_SPI_CLK,ENABLE);


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

  SPI_I2S_DeInit(VS1053B_SPI);
  SPI_Init(VS1053B_SPI, &SPI_InitStructure);

  /* Enable SPI_MASTER */
  SPI_Cmd(VS1053B_SPI, ENABLE);
  SPI_CalculateCRC(VS1053B_SPI, DISABLE);
}

//GPIO_Pin: VS1053B_PIN_XDCS    VS1053B_PIN_XCS    VS1053B_PIN_XRESET    VS1053B_PIN_DREQ
//status:   SET    RESET
void vs1053b_cs(uint16_t GPIO_Pin, FlagStatus status)
{
  if(status==SET)
  {
    GPIO_SetBits(VS1053B_GPIO, GPIO_Pin);
  }
  else
  {
    GPIO_ResetBits(VS1053B_GPIO, GPIO_Pin);
  }
}

static uint8_t vs1053b_read_wite_byte(uint8_t wdata)
{
  while(SPI_I2S_GetFlagStatus(VS1053B_SPI, SPI_I2S_FLAG_TXE) == RESET);		// Transmit buffer empty?  
  SPI_I2S_SendData(VS1053B_SPI, wdata);		                                        // send 1 byte data
  while(SPI_I2S_GetFlagStatus(VS1053B_SPI, SPI_I2S_FLAG_RXNE) == RESET);	        //Receive buffer not empty?
  return SPI_I2S_ReceiveData(VS1053B_SPI);
}

void vs1053b_write_data(uint8_t data)
{
  vs1053b_cs(VS1053B_PIN_XCS,SET);
  vs1053b_cs(VS1053B_PIN_XDCS,RESET);
  vs1053b_read_wite_byte(data);
  vs1053b_cs(VS1053B_PIN_XDCS,SET);
}


void vs1053b_write_reg(uint8_t reg_add, uint16_t reg_value)
{
  vs1053b_cs(VS1053B_PIN_XDCS,SET);
  vs1053b_cs(VS1053B_PIN_XCS,RESET);
  vs1053b_read_wite_byte(SCI_WRITE_COMMAND);
  vs1053b_read_wite_byte(reg_add);
  vs1053b_read_wite_byte(reg_value>>8);
  vs1053b_read_wite_byte(reg_value&0x00ff);
  vs1053b_cs(VS1053B_PIN_XCS,SET);
}



uint16_t vs1053b_read_reg(uint8_t reg_add)
{
  uint16_t reg_value=0;
  vs1053b_cs(VS1053B_PIN_XDCS,SET);
  vs1053b_cs(VS1053B_PIN_XCS,RESET);
  vs1053b_read_wite_byte(SCI_READ_COMMAND);
  vs1053b_read_wite_byte(reg_add);
  reg_value=vs1053b_read_wite_byte(0x00);
  reg_value=(reg_value<<8)|(vs1053b_read_wite_byte(0x00));
  vs1053b_cs(VS1053B_PIN_XCS,SET);
  rt_kprintf("add:%x,value:%x\r\n",reg_add,reg_value);
  return reg_value;
}


//GPIO_Pin: VS1053B_PIN_XDCS    VS1053B_PIN_XCS    VS1053B_PIN_XRESET    VS1053B_PIN_DREQ
//status:   SET    RESET

void vs1053b_init(void)
{
  vs1053b_gpio_config();
  vs1053b_spi_config();
  
  vs1053b_cs(VS1053B_PIN_XRESET, RESET);
  rt_thread_delay(5);
  vs1053b_cs(VS1053B_PIN_XDCS, SET);
  vs1053b_cs(VS1053B_PIN_XCS, SET);

  vs1053b_cs(VS1053B_PIN_XRESET, SET);
  while(vs1053b_dreq==0);
  vs1053b_write_reg(SCI_MODE_ADDRESS,0x0804);
  while(vs1053b_dreq==0);
  vs1053b_write_reg(SCI_CLOCKF_ADDRESS,0x9800);
  vs1053b_write_reg(SCI_AUDATA_ADDRESS,0XBB81);
  vs1053b_write_reg(SCI_VOL_ADDRESS,0x0101);
  vs1053b_write_reg(SCI_BASS_ADDRESS,0x0055);
  
#if 0  
  vs1053b_write_reg(SCI_MODE_ADDRESS,0x0820);
  while(vs1053b_dreq==0);
  vs1053b_cs(VS1053B_PIN_XDCS, RESET);
  vs1053b_read_wite_byte(0x53);
  vs1053b_read_wite_byte(0xef);
  vs1053b_read_wite_byte(0x6e);
  vs1053b_read_wite_byte(0x25);
  vs1053b_read_wite_byte(0x00);
  vs1053b_read_wite_byte(0x00);
  vs1053b_read_wite_byte(0x00);
  vs1053b_read_wite_byte(0x00);
  rt_thread_delay(1000);
  vs1053b_read_wite_byte(0x45);
  vs1053b_read_wite_byte(0x78);
  vs1053b_read_wite_byte(0x69);
  vs1053b_read_wite_byte(0x74);
  vs1053b_read_wite_byte(0x00);
  vs1053b_read_wite_byte(0x00);
  vs1053b_read_wite_byte(0x00);
  vs1053b_read_wite_byte(0x00);
  
  vs1053b_write_reg(SCI_MODE_ADDRESS,0x0802);
#endif 

}







#include <finsh.h>
#include <dfs_posix.h>
#include "stm32f10x.h"







char file_buffer0[512]={0};
char file_buffer1[512]={0};
uint8_t m,n,buffer0_empty,buffer1_empty,buffer_flag=0;
uint16_t buffer_shift=0;



#if 0

void audio_send_thread_entry(void* parameter)
{
  int fd;
  int length;
  /* 只读打开进行数据校验 */
  fd = open("/audio.mp3", O_RDONLY, 0);  
  length = read(fd, file_buffer0, 512);
  length = read(fd, file_buffer1, 512);
  buffer1_empty=0;
  buffer0_empty=0;
  
  vs1053b_init();
  vs1053b_cs(VS1053B_PIN_XCS,SET);
  vs1053b_cs(VS1053B_PIN_XDCS,RESET);
  
  while(1)
  {
    if(buffer0_empty)
    {
      length = read(fd, file_buffer0, 512);
      buffer0_empty=0;
    }
     if(buffer1_empty)
    {
      length = read(fd, file_buffer1, 512);
      buffer1_empty=0;
    }
    if(length<0)
    {
      close(fd);
    }
    if(vs1053b_dreq&&(SPI_I2S_GetFlagStatus(VS1053B_SPI,SPI_I2S_FLAG_TXE)))
    {
      
      if(buffer_flag==0)
      {
        VS1053B_SPI_DMA_Config(*(file_buffer0+buffer_shift));
      }
      else
      {
        VS1053B_SPI_DMA_Config(*(file_buffer1+buffer_shift));
      }
      buffer_shift+=32;
      if(buffer_shift==512)
      {
        buffer_shift=0;
        if(buffer_flag==0)
        {
          buffer0_empty=1;
          buffer_flag=1;
        }
        else
        {
          buffer1_empty=1;
          buffer_flag=0;
        }
      }
    }
  }
}

#endif


#if 0
void audio_send_thread_entry(void* parameter)
{
  int fd;
  int length;
  /* 只读打开进行数据校验 */
  fd = open("/audio.mp3", O_RDONLY, 0);  
  length = read(fd, file_buffer0, 512);
  buffer0_empty=0;
  
  vs1053b_init();
  vs1053b_cs(VS1053B_PIN_XCS,SET);
  vs1053b_cs(VS1053B_PIN_XDCS,RESET);
  u8 n;
  while(1)
  {
    if(buffer0_empty)
    {
      length = read(fd, file_buffer0, 512);
      buffer0_empty=0;
    }
    if(length<0)
    {
      close(fd);
      return;
    }
    if(vs1053b_dreq)
    {
      for(n=0;n<32;n++)
      {
        vs1053b_read_wite_byte(file_buffer0[buffer_shift]);
        buffer_shift+=1;
      }
    }
      if(buffer_shift==512)
      {
        buffer_shift=0;
          buffer0_empty=1;
      }
    
  }
}
#endif




#if 1
void audio_send_thread_entry(void* parameter)
{
  int fd;
  int length;
  /* 只读打开进行数据校验 */
  fd = open("/audio.mp3", O_RDONLY, 0);  
  length = read(fd, file_buffer0, 512);
  
  buffer0_empty=0;
//  NVIC_Configuration();
  vs1053b_init();
  vs1053b_cs(VS1053B_PIN_XCS,SET);
  vs1053b_cs(VS1053B_PIN_XDCS,RESET);
  char *p;
  p=file_buffer0;
  u8 n=0;
  while(1)
  {
    if(buffer0_empty)
    {
      length = read(fd, file_buffer0, 512);
      buffer0_empty=0;
    }
    if(length<0)
    {
      close(fd);
      return;
    }
    if(vs1053b_dreq)
    {
//      for(n=0;n<32;n++)
      {
        VS1053B_SPI_DMA_Config((uint32_t)(p+buffer_shift));
        buffer_shift+=1;
      }
      
 //     rt_thread_delay(200);
//      rt_kprintf("%x\r\n",(p+buffer_shift));
    }
    
   
      if(buffer_shift==512)
      {
        buffer_shift=0;
          buffer0_empty=1;
      }
  }
}

void DMA1_Channel3_IRQHandler(void)
{


    /* enter interrupt */
    rt_interrupt_enter();
    if(DMA_GetFlagStatus(DMA1_FLAG_TE3))
    {
      rt_kprintf("dma_te\r\n");
    }
    
    DMA_ClearFlag(DMA1_FLAG_GL3|DMA1_FLAG_TC3);
    DMA_Cmd(VS1053B_SPI_DMA, DISABLE);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
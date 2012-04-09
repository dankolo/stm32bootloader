#ifndef __VS1053B_H
#define __VS1053B_H


//                  SCI registers, prefix SCI_						
//  Reg	Type	Reset	Time1	Abbrev[bits]	Description	
//  0x0	rw	0x4800	80	CLKI4	        MODE Mode control  	                      模式控制
//  0x1	rw	0x000C3	80	CLKI	        STATUS Status of VS1053b 	              VS1053b的状态
//  0x2	rw	0	80	CLKI	        BASS Built-in bass/treble control 	      内建的低音/高音控制
//  0x3	rw	0	1200	XTALI5	        CLOCKF Clock freq + multiplier	              时钟频率加乘数
//  0x4	rw	0	100	CLKI	        DECODE_TIME Decode time in seconds	      解码时间长度〈秒〉
//  0x5	rw	0	450	CLKI2	        AUDATA Misc. audio data 	              各种音频数据
//  0x6	rw	0	100	CLKI	        WRAM RAM write/read  	                      RAM 写/读
//  0x7	rw	0	100	CLKI	        WRAMADDR Base address for RAM/write/read      RAM 写/读的基扯
//  0x8	r	0	80	CLKI	        HDAT0 Stream header data 0	              流的数据标头0
//  0x9	r	0	80	CLKI	        HDAT1 Stream header data 1	              流的数据标头1
//  0xA	rw	0	210	CLKI2	        AIADDR Start address of application	      应用程序的起始地址
//  0xB	rw	0	80	CLKI	        VOL Volume control  	音量控制
//  0xC	rw	0	80	CLKI2	        AICTRL0 Application control register 0	应用程序控制寄存器0
//  0xD	rw	0	80	CLKI2	        AICTRL1 Application control register 1	应用程序位制寄存器1
//  0xE	rw	0	80	CLKI2	        AICTRL2 Application control register 2	应用程序控制寄存器2
//  0xF	rw	0	80	CLKI2	        AICTRL3 Application control register 3	应用程序位制寄存器3


#define		SCI_MODE_ADDRESS		0x0
#define		SCI_STATUS_ADDRESS		0x1
#define		SCI_BASS_ADDRESS		0x2
#define		SCI_CLOCKF_ADDRESS		0x3
#define		SCI_DECODE_TIME_ADDRESS		0x4
#define		SCI_AUDATA_ADDRESS		0x5
#define		SCI_WRAM_ADDRESS		0x6
#define		SCI_WRAMADDR_ADDRESS		0x7
#define		SCI_HDAT0_ADDRESS		0x8
#define		SCI_HDAT1_ADDRESS		0x9
#define		SCI_AIADDR_ADDRESS		0xA
#define		SCI_VOL_ADDRESS		        0xB
#define		SCI_AICTRL0_ADDRESS		0xC
#define		SCI_AICTRL1_ADDRESS		0xD
#define		SCI_AICTRL2_ADDRESS		0xE
#define		SCI_AICTRL3_ADDRESS		0xF



#define SM_DIFF         			0x01   
#define SM_JUMP         			0x02   
#define SM_RESET        			0x04   
#define SM_OUTOFWAV     			0x08   
#define SM_PDOWN        			0x10   
#define SM_TESTS        			0x20   
#define SM_STREAM       			0x40   
#define SM_PLUSV        			0x80   
#define SM_DACT         			0x100   
#define SM_SDIORD       			0x200   
#define SM_SDISHARE     			0x400   
#define SM_SDINEW       			0x800   
#define SM_ADPCM        			0x1000   
#define SM_ADPCM_HP     			0x2000


#define SCI_READ_COMMAND                        0X03
#define SCI_WRITE_COMMAND                       0X02



#define VS1053B_SPI                   SPI1
#define VS1053B_SPI_CLK               RCC_APB2Periph_SPI1

#define VS1053B_SPI_DMA		DMA1_Channel3
#define VS1053B_SPI_DMA_IRQ	DMA1_Channel3_IRQn
#define VS1053B_SPI_RCC_AHB	RCC_AHBPeriph_DMA1
#define VS1053B_SPI_DR_ADDRESS  0x4001300c


#define VS1053B_SPI_GPIO              GPIOA
#define VS1053B_SPI_GPIO_CLK          RCC_APB2Periph_GPIOA  
#define VS1053B_SPI_PIN_SCK           GPIO_Pin_5
#define VS1053B_SPI_PIN_MISO          GPIO_Pin_6
#define VS1053B_SPI_PIN_MOSI          GPIO_Pin_7


#define VS1053B_GPIO                  GPIOC
#define VS1053B_GPIO_CLK              RCC_APB2Periph_GPIOC
#define VS1053B_PIN_XDCS              GPIO_Pin_0
#define VS1053B_PIN_DREQ              GPIO_Pin_1
#define VS1053B_PIN_XRESET            GPIO_Pin_2
#define VS1053B_PIN_XCS               GPIO_Pin_3




#define vs1053b_dreq                 (GPIO_ReadInputDataBit(VS1053B_GPIO, VS1053B_PIN_DREQ))




void vs1053b_dma_isr(void);
void vs1053b_init(void);

void audio_send_thread_entry(void* parameter);







#endif
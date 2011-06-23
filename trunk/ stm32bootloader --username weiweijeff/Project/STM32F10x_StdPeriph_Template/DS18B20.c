#define _DS18B20_LOCAL
#include "ds18b20.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
//把下面这段复制到主程序
/**************************************************************************/
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//  TIM_TimeBaseStructure.TIM_Period = 1;                 //自动装载
//  TIM_TimeBaseStructure.TIM_Prescaler = 72;       //72M分频率到1MHz
//  TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;  //向下计数
//  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
/**************************************************************************/
uint8_t Temperature[5]="00.0";

void delay_nus(vu32 nCount)
{
  u16 TIMCounter = nCount;
  TIM_Cmd(TIM4, ENABLE);
  TIM_SetCounter(TIM4, TIMCounter);
  while (TIMCounter)
  {
    TIMCounter = TIM_GetCounter(TIM4);
  }
  TIM_Cmd(TIM4, DISABLE);
}

/*******************************************************************************
*******************************************************************************/
//单总线上的所有处理均从初始化开始
void init_1820()  
{  
    DIR_1WIRE_OUT();
    SET_OP_1WIRE();   
    CLR_OP_1WIRE();  
    delay_nus(500);    //480us以上  
    SET_OP_1WIRE();  
    DIR_1WIRE_IN();  
    delay_nus(30);     //15~60us  
    while(CHECK_IP_1WIRE());  
    DIR_1WIRE_OUT();  
    SET_OP_1WIRE();  
    delay_nus(100);   //60~240us  
}

void DS18B20_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

        // PA8-DQ
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  DS18B20_BIT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}


/*
指令                    代码
Read ROM(读ROM)         [33H]
Match ROM(匹配ROM)      [55H]
Skip ROM(跳过ROM]       [CCH]
Search ROM(搜索ROM)     [F0H]
Alarm search(告警搜索)  [ECH]

指令                                                         代码
Write Scratchpad(写暂存存储器)         [4EH]
Read Scratchpad(读暂存存储器)         [BEH]
Copy Scratchpad(复制暂存存储器) [48H]
Convert Temperature(温度变换)         [44H]
Recall EPROM(重新调出)                         [B8H]
Read Power supply(读电源)                 [B4H]
*/  
void write_1820(u8 x)  
{     
    u16 i;  
   
        for(i=0; i<8; i++)  
    {  
               CLR_OP_1WIRE();
               if(x & 0x01)    //写数据了，先写低位的！
                       SET_OP_1WIRE();  
               else  
                       CLR_OP_1WIRE();  
                x>>=1;
               delay_nus(30);   //15~60us  
               SET_OP_1WIRE();  
    }  
    SET_OP_1WIRE();  
}  
u8 read_1820(void)  
{      
        u16 i;
        u8 x = 0;
       
        DIR_1WIRE_OUT();
    for(i=0; i<8; i++)  
    {  
            CLR_OP_1WIRE();  
            x >>= 1;
                SET_OP_1WIRE();  
            DIR_1WIRE_IN();
            //读数据,从低位开始  
            if(CHECK_IP_1WIRE())  
                    x |= 0x80;
            delay_nus(100); //60~120us      
            DIR_1WIRE_OUT();  
    }
    return (x);  
}   

/*
        返回值是温度
        格式s,s,s,s, s,b6,b5,b4, b3,b2,b1,b0, b-1,b-2,b-3,b-4
        转换为十进制
        温度 T = (int)val*10/16;
        放大了10倍，个位是小数部分。
       

*/
void DS18B20_Convert(void)                //温度转换
{
     init_1820();        //复位18b20  
     write_1820(0xcc);   // 发出转换命令  
     write_1820(0x44);
}

u16 DS18B20_Read(void)                   //读取温度值
{  
    u16 res;
    init_1820();  
    write_1820(0xcc);  //发出读命令  
    write_1820(0xbe);  
    res=read_1820();  //读数据  
    res+=(u16)read_1820()<<8;  
    Temperature[0]=res/160+'0';
    Temperature[1]=res/16%10+'0';
    Temperature[2]='.';
    Temperature[3]=res*10/16%10+'0';
    Temperature[4]='\0';
    return res;
}
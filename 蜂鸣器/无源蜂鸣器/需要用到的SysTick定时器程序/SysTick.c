#include "SysTick.h"

static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数
static u32 fac_s=0;               //s延时倍乘数

//初始化延迟函数
//SYSTICK的时钟固定为AHB时钟的1/8
//SYSCLK:系统时钟频率

void SysTick_Init(u8 SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;					
	fac_ms=(u16)fac_us*1000;
  fac_s=(u32)fac_ms*1000;	
}								    

void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
}

void delay_ms(u16 nms)
{	 		  	  

  while( nms-- != 0)
	{
		delay_us(1000);	//调用1000微秒的延时
	}	
	
} 

void delay_s(u16 nns)
{
  while( nns-- != 0)
	{
		delay_ms(1000);	//调用1000毫秒的延时
	}	
}

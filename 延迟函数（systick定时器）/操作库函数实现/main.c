#include "stm32f10x_systick.h"

/*systick 初始化*/
void systick_Init()
{
   SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);  
}


/*systick 用库函数实现us级延时*/
void delay_us(u32 us)
{
    SysTick_SetReload(((9*us < 0xffffffff)?9*us:0xffffffff));
    SysTick_CounterCmd(SysTick_Counter_Clear);   
    SysTick_CounterCmd(SysTick_Counter_Enable);  
    while(SysTick_GetFlagStatus(SysTick_FLAG_COUNT) != SET);  /*程序里面要使用看门狗。注意！*/
    SysTick_CounterCmd(SysTick_Counter_Disable); 
    SysTick_CounterCmd(SysTick_Counter_Clear);
}


/*systick 实现ms级延时*/
void delay_ms(u32 ms)
{
	while (ms-- != 0)
	{
		delay_us(1000);	//??1000?????
	}
}


/*systick 实现s级延时*/
void delay_s(u32 s)
{
	while (s-- != 0)
	{
		delay_ms(1000);
	}
}


int main()
{
	systick_Init();
	while(1)
	{
		delay_us(500000);
	}
}

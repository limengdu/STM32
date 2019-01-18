#include "stm32f10x.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "time.h"
#include "stm32f10x_it.h"

extern u16 time1;
extern u16 time2;

int main()
{
	u8 i;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	TIM4_Init(1000-1,72-1);  //定时1ms
	
	while(1)
	{
		i++;
        if(time1==500)  //500ms计时实现有关操作
			{
				  ;
            }
        if(time2==1000) //1s计时实现有关操作
			{
				;
            }
		if(i%20==0)//状态灯
		    {
				led1=!led1;
		    }
		delay_ms(10);	
	}
}

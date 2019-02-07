/* Includes ------------------------------------------------------------------*/
#include "timer.h"

/*******************************************************************************
* 函 数 名         : Timerx_Init
* 函数功能		   : TIM1初始化配置、中断服务NVIC配置
* 输    入         : 无
* 输    出         : 无
* 说    明         : 这里时钟选择为APB2 72Mhz，而APB1为36M
                     arr：自动重装值。
                     psc：时钟预分频数
                     这里使用的是TIM1，定时时间t=arr*(psc*1/APB2(72Mhz))
					 
*                             黎孟度心血之作                                   *
*******************************************************************************/
void Timerx_Init(u16 arr,u16 psc)
{   
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	TIM_DeInit(TIM1);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //TIM1时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr;
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值，计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1); 
	//设置用来作为TIMx时钟频率除数的预分频值，10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM1,TIM_IT_Update | TIM_IT_Trigger,ENABLE);
	//使能指定的TIM1中断
    //TIM_IT_Update：TIM1中断源
    //TIM_IT_Trigger：TIM1触发中断源 
		
	TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);            //中断组0
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;         //TIM1中断  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级3级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);
	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器							 
}



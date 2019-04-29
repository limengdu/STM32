/* Includes ------------------------------------------------------------------*/
#include "timer.h"

/*******************************************************************************
* 函 数 名         : TIM3_Int_Init
* 函数功能		   : 定时器TIM3作为心跳定时器
* 输    入         : arr和psc
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值——计数到10为1ms
	TIM_TimeBaseStructure.TIM_Period = arr;

    //设置用来作为TIMx时钟频率除数的预分频值——10Khz的计数频率
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	
	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	
	//TIM向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
 
	//使能或者失能指定的TIM中断
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;             //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQ通道被使能
	
	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
}


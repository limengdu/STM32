/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/*******************************************************************************
* 函 数 名         : GPIOCLK_Init
* 函数功能		   : 使能所有GPIO时钟
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void GPIOCLK_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG , ENABLE);
}



/*******************************************************************************
* 函 数 名         : NVIC_TIM2Configuration
* 函数功能		   : NVIC中断配置
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
static void NVIC_TIM2Configuration(void)
{ 
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //配置中断线TIM2
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能NVIC

    NVIC_Init(&NVIC_InitStructure);                            //初始化NVIC
}

/*******************************************************************************
* 函 数 名         : TIM2_Init
* 函数功能		   : 定时器TIM2初始化
* 输    入         : 无
* 输    出         : 无
*                             黎孟度心血之作                                   *
*******************************************************************************/
void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//开启时钟

    TIM_TimeBaseStructure.TIM_Period = (100 - 1);
	//设置自动装载的计数值CNT，计数从0开始，周期为1ms
	
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
	//设置预分频系数，当由于为0时表示不分频所以要减1
	
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	//设置分频系数

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//设置向上计数模式
	
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//初始化定时器2

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	//清除TIM2溢出中断标志

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//打开溢出中断

    TIM_Cmd(TIM2, ENABLE);  
	//计数器使能，开始工作

    NVIC_TIM2Configuration();
	//NVIC初始化
}





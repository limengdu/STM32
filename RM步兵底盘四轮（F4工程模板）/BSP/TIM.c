/**
  ******************************************************************************
  * @file    TIM.c
  * @author  Liang Yuhao
  * @version V1.0
  * @date    
  * @brief   TIM应用函数接口
  ******************************************************************************
  */

#include "TIM.h"

//TIM_SetComparex_f *const TIM_SetComparex[4] = {
//	TIM_SetCompare1,
//	TIM_SetCompare2,
//	TIM_SetCompare3,
//	TIM_SetCompare4
//};

/**
  * @brief  基本定时器TIM6作为计数模式初始化
  * @param  prescaler 				时钟预分频
  *			period					定时器重装载寄存器的值
  *			定时器定时频率：系统时钟频率/预分频/重装载值
  * @retval None
  */
void TIM6_CounterMode(u16 prescaler, u16 period){
	//使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  
	/* 配置时基结构体 */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(TIM6, ENABLE);
	//使能定时器
	TIM_Cmd(TIM6, ENABLE);
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	NVIC_Config(TIM6_DAC_IRQn, 1, 0);
	
}



/**
  * @brief  基本定时器TIM7作为计数模式初始化
  * @param  prescaler 				时钟预分频
  *			period					定时器重装载寄存器的值
  *			定时器定时频率：系统时钟频率/预分频/重装载值
  * @retval None
  */
void TIM7_CounterMode(u16 prescaler, u16 period){
	//使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
  
	/* 配置时基结构体 */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(TIM7, ENABLE);
	//使能定时器
	TIM_Cmd(TIM7, ENABLE);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	NVIC_Config(TIM7_IRQn, 0, 1);
	
}



/**
  * @brief  TIM12_GPIO初始化
  * @param  None
  * @retval None
  */
static void TIM12_GPIOInit(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(TIM12_CH1_GPIO_CLK | TIM12_CH2_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
#if TIM12_CH1_ENABLE
	GPIO_InitStructure.GPIO_Pin = TIM12_CH1_Pin;
	GPIO_Init(TIM12_CH1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM12_CH1_GPIO_PORT,TIM12_CH1_PINSOURCE, GPIO_AF_TIM12);
#endif
#if TIM12_CH2_ENABLE
	GPIO_InitStructure.GPIO_Pin = TIM12_CH2_Pin;
	GPIO_Init(TIM12_CH2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM12_CH2_GPIO_PORT,TIM12_CH2_PINSOURCE, GPIO_AF_TIM12);
#endif
	
}



/**
  * @brief  TIM12作为PWM输出初始化
  * @param  prescaler 	时钟预分频
  *			period		定时器重装载寄存器的值
  *			Pulse		占空比，最大为重装载的值
  *			定时器定时频率：系统时钟频率/预分频/重装载值
  * @retval None
  */
void TIM12_PWMOutput(u16 prescaler, u16 period, u16 Pulse){
	//IO初始化
	TIM12_GPIOInit();
	
	//使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
  
	/* 配置时基结构体 */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//配置定时器时钟分频   TIM12_PWMOutput(89, 19999,1000);
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);
	
	/*配置输出比较结构体*/
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
#if TIM12_CH1_ENABLE
	//初始化为对应通道的输出，通道1
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);
#endif
#if TIM12_CH2_ENABLE
	//初始化为对应通道的输出，通道1
	TIM_OC2Init(TIM12, &TIM_OCInitStructure);
#endif
	//使能定时器
	TIM_Cmd(TIM12, ENABLE);
	
}





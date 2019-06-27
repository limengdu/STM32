/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#include <rtthread.h>
#include <stm32f10x.h>
#include "tim.h"

/*-------------------------------------------------------------------------------
函数名称：TIM2_Configuration
函数描述：舵机接口设置（TIM2） /PA1
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM2_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	                                                      				
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_1;			   								// PA1 TIM2_CH2
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF_PP;          					
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  
	
  TIM_TimeBaseStructure.TIM_Period     		= Servo_Period - 1; 				// 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler  		= 144 - 1; 									// 设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 						// 设置时钟分频，这里采用不分频，即可以简单设置为0
	TIM_TimeBaseStructure.TIM_CounterMode	  = TIM_CounterMode_Up; 			// TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM1;							// 选择定时器模式，TIM脉冲宽度调制模式1 （在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为有效电平，否则为无效电平）aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2d0a2tuZC9hcnRpY2xlL2RldGFpbHMvMzkyOTYxNTE=
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				// 比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_Low;						// 输出比较极性低 （即有效电平为低电平）
	TIM_OCInitStructure.TIM_Pulse 			= 0;														// 指定要加载到寄存器的脉冲值
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);														// 根据结构体信息进行初始化
	
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  									// 使能定时器TIM2在CCR2上的预装载值
	TIM_ARRPreloadConfig(TIM2, ENABLE);																	// 使能TIM2在ARR上的预装载寄存器
	TIM_Cmd(TIM2, ENABLE);																							// 使能定时器TIM2
}

/*-------------------------------------------------------------------------------
函数名称：TIM8_Configuration
函数描述：TIM8四通道分别输出PWM1/PWM2,对应引脚为PC6/PC7
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM8_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

	/* GPIO、外设时钟设定 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

	/*	GPIO参数设定 */
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_6 | GPIO_Pin_7;    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       								// 20纳秒周期（GPIO）
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;       
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	 
	/* 定时器参数设定 */
	TIM_TimeBaseStructure.TIM_Prescaler 				= 0;												// 设置预分频值
	TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up;				// 向上计数模式
	TIM_TimeBaseStructure.TIM_Period 						= PWMPeriod - 1;						// 设置自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;							// 设置时钟分割(若没有特殊情况，默认为TIM_CKD_DIV1。TIM_ClockDivision的作用就是在未分频之前 根据要求建立新的分频器，确定定时器，确定一定的延时时间，在此时间内完成一定预期的功能)  aHR0cDovL2Jsb2cuc2luYS5jb20uY24vcy9ibG9nXzc2YzU0NTM5MDEwMG92ZmouaHRtbA==
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;												// 仅高级定时器有该项(用于重复计数，该项是重复溢出0次才给一个溢出中断) 
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);													// 根据指定的参数初始化TIM8					
	
	/* 定时器PWM模式参数设定 */
	TIM_OCInitStructure.TIM_OCMode 				= TIM_OCMode_PWM2;								// TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputState_Enable;					// 使能指定TIM输出比较状态
	TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Disable;				// 禁用指定TIM互补输出比较状态
	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_Low;							// TIM输出极性低
	TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;						// TIM8输出比较N极性高

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);												
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	
	TIM_SetCompare1(TIM8, 0);                                               // TIM8->CCR1 = 0;  TIM8的CCR1位初始化为0
	TIM_SetCompare2(TIM8, 0);																								// TIM8->CCR2 = 0; 	TIM8的CCR2位初始化为0
 
	TIM_Cmd(TIM8, ENABLE);															// 使能定时器TIM8
	TIM_CtrlPWMOutputs(TIM8, ENABLE);										// PWM输出使能
}

/*-------------------------------------------------------------------------------
函数名称：TIM_Init
函数描述：针对指定TIM定时器进行使用前的初始化
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void rt_hw_tim_init(void)
{
	TIM2_Configuration();
	TIM8_Configuration();																										// TIM8配置初始化
}

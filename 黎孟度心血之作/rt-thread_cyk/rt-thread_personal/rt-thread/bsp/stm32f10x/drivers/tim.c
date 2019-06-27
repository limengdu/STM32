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
�������ƣ�TIM2_Configuration
��������������ӿ����ã�TIM2�� /PA1
�����������
���ز�������
��    ע����
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
	
  TIM_TimeBaseStructure.TIM_Period     		= Servo_Period - 1; 				// ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler  		= 144 - 1; 									// ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 						// ����ʱ�ӷ�Ƶ��������ò���Ƶ�������Լ�����Ϊ0
	TIM_TimeBaseStructure.TIM_CounterMode	  = TIM_CounterMode_Up; 			// TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM1;							// ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ1 �������ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2d0a2tuZC9hcnRpY2xlL2RldGFpbHMvMzkyOTYxNTE=
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				// �Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_Low;						// ����Ƚϼ��Ե� ������Ч��ƽΪ�͵�ƽ��
	TIM_OCInitStructure.TIM_Pulse 			= 0;														// ָ��Ҫ���ص��Ĵ���������ֵ
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);														// ���ݽṹ����Ϣ���г�ʼ��
	
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  									// ʹ�ܶ�ʱ��TIM2��CCR2�ϵ�Ԥװ��ֵ
	TIM_ARRPreloadConfig(TIM2, ENABLE);																	// ʹ��TIM2��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM2, ENABLE);																							// ʹ�ܶ�ʱ��TIM2
}

/*-------------------------------------------------------------------------------
�������ƣ�TIM8_Configuration
����������TIM8��ͨ���ֱ����PWM1/PWM2,��Ӧ����ΪPC6/PC7
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM8_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

	/* GPIO������ʱ���趨 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

	/*	GPIO�����趨 */
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_6 | GPIO_Pin_7;    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       								// 20�������ڣ�GPIO��
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;       
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	 
	/* ��ʱ�������趨 */
	TIM_TimeBaseStructure.TIM_Prescaler 				= 0;												// ����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_CounterMode 			= TIM_CounterMode_Up;				// ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period 						= PWMPeriod - 1;						// �����Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;							// ����ʱ�ӷָ�(��û�����������Ĭ��ΪTIM_CKD_DIV1��TIM_ClockDivision�����þ�����δ��Ƶ֮ǰ ����Ҫ�����µķ�Ƶ����ȷ����ʱ����ȷ��һ������ʱʱ�䣬�ڴ�ʱ�������һ��Ԥ�ڵĹ���)  aHR0cDovL2Jsb2cuc2luYS5jb20uY24vcy9ibG9nXzc2YzU0NTM5MDEwMG92ZmouaHRtbA==
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;												// ���߼���ʱ���и���(�����ظ��������������ظ����0�βŸ�һ������ж�) 
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);													// ����ָ���Ĳ�����ʼ��TIM8					
	
	/* ��ʱ��PWMģʽ�����趨 */
	TIM_OCInitStructure.TIM_OCMode 				= TIM_OCMode_PWM2;								// TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputState_Enable;					// ʹ��ָ��TIM����Ƚ�״̬
	TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Disable;				// ����ָ��TIM��������Ƚ�״̬
	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_Low;							// TIM������Ե�
	TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;						// TIM8����Ƚ�N���Ը�

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);												
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	
	TIM_SetCompare1(TIM8, 0);                                               // TIM8->CCR1 = 0;  TIM8��CCR1λ��ʼ��Ϊ0
	TIM_SetCompare2(TIM8, 0);																								// TIM8->CCR2 = 0; 	TIM8��CCR2λ��ʼ��Ϊ0
 
	TIM_Cmd(TIM8, ENABLE);															// ʹ�ܶ�ʱ��TIM8
	TIM_CtrlPWMOutputs(TIM8, ENABLE);										// PWM���ʹ��
}

/*-------------------------------------------------------------------------------
�������ƣ�TIM_Init
�������������ָ��TIM��ʱ������ʹ��ǰ�ĳ�ʼ��
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void rt_hw_tim_init(void)
{
	TIM2_Configuration();
	TIM8_Configuration();																										// TIM8���ó�ʼ��
}

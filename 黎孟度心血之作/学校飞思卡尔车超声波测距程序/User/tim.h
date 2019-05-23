/*-------------------------------------------------------------------------------
文件名称：tim.h
文件描述：定时器相关功能函数（用于舵机，电机，周期循环事件等）。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __TIM_H
#define	__TIM_H

#include "stm32f10x.h"

#define PWMPeriod      	 7200			  	// 4500 16kHZ  7200 10kHZ
#define TIM6_Period      1000
#define TIM7_Period      1000


void TIM2_Configuration(void);
void TIM3_Configuration(void);				// 该通用定时器设置为编码器模式
void TIM6_Configuration(void);				// 该基础定时器，用于周期循环事件
void TIM7_Configuration(void);				// 该基础定时器，用于周期循环事件
void TIM8_Configuration(void);				// 该高级定时器设置为PWM模式
void TIM_Init(void);									// 指定定时器进行初始化

#endif

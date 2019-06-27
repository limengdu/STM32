#ifndef __TIM_H
#define	__TIM_H

#include <rtthread.h>
#include "steering_engine.h"

#define PWMPeriod      	 7200			  	// 4500 16kHZ  7200 10kHZ


void TIM8_Configuration(void);				// 该高级定时器设置为PWM模式
void rt_hw_tim_init(void);									// 指定定时器进行初始化

#endif

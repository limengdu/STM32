#ifndef __TIM_H
#define	__TIM_H

#include <rtthread.h>
#include "steering_engine.h"

#define PWMPeriod      	 7200			  	// 4500 16kHZ  7200 10kHZ


void TIM8_Configuration(void);				// �ø߼���ʱ������ΪPWMģʽ
void rt_hw_tim_init(void);									// ָ����ʱ�����г�ʼ��

#endif

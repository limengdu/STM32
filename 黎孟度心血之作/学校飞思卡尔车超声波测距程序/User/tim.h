/*-------------------------------------------------------------------------------
�ļ����ƣ�tim.h
�ļ���������ʱ����ع��ܺ��������ڶ�������������ѭ���¼��ȣ���
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __TIM_H
#define	__TIM_H

#include "stm32f10x.h"

#define PWMPeriod      	 7200			  	// 4500 16kHZ  7200 10kHZ
#define TIM6_Period      1000
#define TIM7_Period      1000


void TIM2_Configuration(void);
void TIM3_Configuration(void);				// ��ͨ�ö�ʱ������Ϊ������ģʽ
void TIM6_Configuration(void);				// �û�����ʱ������������ѭ���¼�
void TIM7_Configuration(void);				// �û�����ʱ������������ѭ���¼�
void TIM8_Configuration(void);				// �ø߼���ʱ������ΪPWMģʽ
void TIM_Init(void);									// ָ����ʱ�����г�ʼ��

#endif

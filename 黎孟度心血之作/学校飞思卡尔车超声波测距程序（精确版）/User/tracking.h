
/*-------------------------------------------------------------------------------
�ļ����ƣ�tracking.h
�ļ�������Ѳ��������غ궨�弰�书�ܺ���������    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __TRACKING_H
#define __TRACKING_H

#include "stm32f10x.h"

#define S1_Tracking GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)
#define S2_Tracking GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define S3_Tracking GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define S4_Tracking GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define S5_Tracking GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)

void Tracking_Init(void);
void Tracking_Control(void);

#endif

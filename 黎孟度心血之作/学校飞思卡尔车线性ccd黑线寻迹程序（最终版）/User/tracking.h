
/*-------------------------------------------------------------------------------
文件名称：tracking.h
文件描述：巡线外设相关宏定义及其功能函数声明。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
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

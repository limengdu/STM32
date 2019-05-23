/*-------------------------------------------------------------------------------
文件名称：key.h
文件描述：按键宏定义，及其相关功能函数声明。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define KEY2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define KEY3 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)

#define __key_1 	1
#define __key_2		2
#define __key_3		3

typedef enum {REL_SET = 0, UN_REL_SET = !REL_SET} KEY_RELEASE_Status;

void KEY_Init(void);
u8 KEY_Scan(void);

#endif

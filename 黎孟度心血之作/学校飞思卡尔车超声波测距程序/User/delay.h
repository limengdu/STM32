/*-------------------------------------------------------------------------------
文件名称：delay.h
文件描述：精准延时（非定时器） 的相关功能函数声明。     
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H 			

#include "stm32f10x.h"
	 
//void Delay_Init(void);
//void Delay_ms(u16 nms);
//void Delay_us(u32 nus);
void Delay_us(__IO u32 nTime);
void Delay_ms(__IO u32 nTime);

#endif

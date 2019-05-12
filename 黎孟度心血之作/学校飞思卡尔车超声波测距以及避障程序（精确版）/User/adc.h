/*-------------------------------------------------------------------------------
文件名称：adc.h
文件描述：ADC相关宏及其功能函数声明。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __ADC_H
#define __ADC_H	

#include "sys.h"

#define ADC_CH_x	ADC_Channel_10			// ADC 通道10

void ADC1_Mode_Configure(void);
u16 Get_ADC(u8 ch);
u16 Get_ADC_Average(u8 times);

#endif 













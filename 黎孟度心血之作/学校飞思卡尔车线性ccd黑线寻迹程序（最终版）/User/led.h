/*-------------------------------------------------------------------------------
文件名称：led.h
文件描述：LED功能函数声明及其相关宏定义。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#include "sys.h"

#define LED1_OFF  GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define LED1_ON 	GPIO_ResetBits(GPIOA,GPIO_Pin_12)

#define LED2_OFF 	GPIO_SetBits(GPIOD,GPIO_Pin_3)
#define LED2_ON  	GPIO_ResetBits(GPIOD,GPIO_Pin_3)


#define LED1 PAout(12)				// PA12
#define LED2 PDout(3)					// PD3	

void LED_Init(void);
void LED_State(void);

#endif

/*-------------------------------------------------------------------------------
文件名称：ultrasonic.h
文件描述：超声波测距模块相关宏定义及其函数声明。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include "stm32f10x.h"
#include "sys.h"

#define EN_school_code    0                           //进行代码选择：学校代码
#define EN_limengdu_code  1                           //进行代码选择：自己的代码


#define TIM5_Period 				10000											// 注意周期数量不能设置太少

#define ULTRASONIC_PORT     GPIOA
#define ULTRASONIC_CLK      RCC_APB2Periph_GPIOA
#define ULTRASONIC_TRIG     GPIO_Pin_10								// 超声波模块控制端(Trig)
#define ULTRASONIC_ECHO     GPIO_Pin_0								// 超声波模块接收端(Echo)
 
#define TRIG_SEND  					PAout(10) 								
#define ECHO_RECEIVE  			PAin(0)

#define PROCESSING_DATA																// 进行简单的数据处理(用于提高数据测量结果的稳定性)

#define max(a,b)						((a)>(b) ? (a) : (b))
#define min(a,b)						((a)<(b) ? (a) : (b))


#if EN_school_code
void Ultrasonic_Trig(void);
void Ultrasonic_Measure(void);
#endif

#if EN_limengdu_code

#define Echo_PORTSOURCE  GPIO_PortSourceGPIOA
#define Echo_PINSOURCE   GPIO_PinSource0
#define Echo_EXITLINE    EXTI_Line0
#define Echo_IRQCH       EXTI0_IRQn

#define Trig_RESET       GPIO_SetBits(ULTRASONIC_PORT , ULTRASONIC_TRIG)
#define Trig_SET         GPIO_ResetBits(ULTRASONIC_PORT , ULTRASONIC_TRIG)

#define Echo             GPIO_ReadInputDataBit(ULTRASONIC_PORT, ULTRASONIC_ECHO)

extern volatile unsigned int distance_cm;//当前距离
void Time4Init(void);
void UltraSoundInit(void);
void GetDistanceDelay(void);
void Distance(void);
#endif

void Ultrasonic_Init(void);

#endif

/*-------------------------------------------------------------------------------
�ļ����ƣ�ultrasonic.h
�ļ����������������ģ����غ궨�弰�亯��������
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include "stm32f10x.h"
#include "sys.h"

#define EN_school_code    0                           //���д���ѡ��ѧУ����
#define EN_limengdu_code  1                           //���д���ѡ���Լ��Ĵ���


#define TIM5_Period 				10000											// ע������������������̫��

#define ULTRASONIC_PORT     GPIOA
#define ULTRASONIC_CLK      RCC_APB2Periph_GPIOA
#define ULTRASONIC_TRIG     GPIO_Pin_10								// ������ģ����ƶ�(Trig)
#define ULTRASONIC_ECHO     GPIO_Pin_0								// ������ģ����ն�(Echo)
 
#define TRIG_SEND  					PAout(10) 								
#define ECHO_RECEIVE  			PAin(0)

#define PROCESSING_DATA																// ���м򵥵����ݴ���(����������ݲ���������ȶ���)

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

extern volatile unsigned int distance_cm;//��ǰ����
void Time4Init(void);
void UltraSoundInit(void);
void GetDistanceDelay(void);
void Distance(void);
#endif

void Ultrasonic_Init(void);

#endif

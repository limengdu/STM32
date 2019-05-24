/*-------------------------------------------------------------------------------
�ļ����ƣ�led.h
�ļ�������LED���ܺ�������������غ궨�塣    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
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

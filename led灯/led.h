#ifndef _led_H
#define _led_H

#include "stm32f10x.h"

#define LED_PORT_RCC   RCC_APB2Periph_GPIOX     //�޸ģ�����LED��Ӧ��ʱ��λ
#define LED_PORT       GPIOX                    //�޸ģ�IO��
#define LED_PIN        GPIO_Pin_X               //�޸ģ����ű��


void LED_Init(void);

#endif








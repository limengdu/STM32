#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f10x.h"

#define BEEP_PORT_RCC   RCC_APB2Periph_GPIOX     //�޸ģ�����BEEP��Ӧ��ʱ��λ
#define BEEP_PORT       GPIOX                    //�޸ģ�IO��
#define BEEP_PIN        GPIO_Pin_X               //�޸ģ����ű��


void BEEP_Init(void);

#endif








#ifndef ENCODER_H
#define ENCODER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�

void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
int Read_Encoder(u8 TIMX);

#endif

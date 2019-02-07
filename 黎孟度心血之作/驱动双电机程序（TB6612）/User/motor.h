#ifndef __MOTOR_H
#define __MOTOR_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

void MOTOR_GPIO_Config(void);
void TIM2_PWM_Init(void);
static void TIM2_GPIO_Config(void);
static void TIM2_Mode_Config(void);

#endif

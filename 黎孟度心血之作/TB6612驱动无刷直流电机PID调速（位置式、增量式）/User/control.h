#ifndef CONTROL_H
#define CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h" 

#define PWMA  TIM1 -> CCR1
#define COMPARE_VALUE 7100

void MOTOR_CONTROL(int moto1);
int myabs(int a);
void Xianfu_Pwm(int *moto_value,int compare_value);

#endif

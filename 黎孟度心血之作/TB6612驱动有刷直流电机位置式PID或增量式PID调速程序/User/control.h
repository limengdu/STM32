#ifndef CONTROL_H
#define CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h" 

//�����PWM����ΪCCR����Ҫ���û������PWM�Ķ�ʱ�������õ���ʲôͨ�����趨
#define PWMA  TIM1 -> CCR1    //PWMAͨ��TIM1��ͨ��CH1�����PWMA��ֵ��CCR1ֵ
#define PWMB  TIM1 -> CCR4    //PWMBͨ��TIM1��ͨ��CH4�����PWMA��ֵ��CCR4ֵ

//�޷��趨Ϊ7100����PWM��ֵ���ɴ���7100��һ��PWM����Ϊ7200
#define COMPARE_VALUE 7100

void MOTOR_CONTROL1(int moto1);
void MOTOR_CONTROL2(int moto2);
int myabs(int a);
void Xianfu_Pwm(int *moto_value,int compare_value);

#endif

#ifndef CONTROL_H
#define CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h" 

//这里的PWM定义为CCR几需要看用户在输出PWM的定时器中配置的是什么通道来设定
#define PWMA  TIM1 -> CCR1    //PWMA通过TIM1的通道CH1输出，PWMA的值即CCR1值
#define PWMB  TIM1 -> CCR4    //PWMB通过TIM1的通道CH4输出，PWMA的值即CCR4值

//限幅设定为7100，即PWM的值不可大于7100，一个PWM周期为7200
#define COMPARE_VALUE 7100

void MOTOR_CONTROL1(int moto1);
void MOTOR_CONTROL2(int moto2);
int myabs(int a);
void Xianfu_Pwm(int *moto_value,int compare_value);

#endif

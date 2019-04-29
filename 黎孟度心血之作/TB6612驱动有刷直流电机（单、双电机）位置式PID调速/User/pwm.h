#ifndef PWM_H
#define PWM_H

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>

#define MOTOR_TIMx                 TIM1
#define MOTOR_TIM_APBxClock        RCC_APB2PeriphClockCmd
#define MOTOR_TIM_CLK              RCC_APB2Periph_TIM1

#define MOTOR_TIM_GPIO_APBxClock   RCC_APB2PeriphClockCmd
#define MOTOR_TIM_GPIO_CLK         RCC_APB2Periph_GPIOA
#define MOTOR_TIM_CH1_PORT         GPIOA
#define MOTOR_TIM_CH1_PIN          GPIO_Pin_8

#define MOTOR_TIM_CH4_PORT         GPIOA
#define MOTOR_TIM_CH4_PIN          GPIO_Pin_11

void PWM_GPIO_Config(void);
void PWM_TIMx_Config(void);
void TIMx_PWM_Init(void);

#endif

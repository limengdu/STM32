#ifndef PWM_H
#define PWM_H

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>

#define DCMOTOR_BRUSH_TIMx                       TIM1
#define DCMOTOR_BRUSH_TIM_APBxClock_FUN          RCC_APB2PeriphClockCmd
#define DCMOTOR_BRUSH_TIM_CLK                    RCC_APB2Periph_TIM1

#define DCMOTOR_BRUSH_TIM_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define DCMOTOR_BRUSH_TIM_GPIO_CLK               (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB)
#define DCMOTOR_BRUSH_TIM_CH1_PORT               GPIOA
#define DCMOTOR_BRUSH_TIM_CH1_PIN                GPIO_Pin_8

#define DCMOTOR_BRUSH_TIM_CH1N_PORT              GPIOB
#define DCMOTOR_BRUSH_TIM_CH1N_PIN               GPIO_Pin_13

void PWM_GPIO_Config(void);
void PWM_TIMx_Config(void);
void TIMx_PWM_Init(void);

#endif

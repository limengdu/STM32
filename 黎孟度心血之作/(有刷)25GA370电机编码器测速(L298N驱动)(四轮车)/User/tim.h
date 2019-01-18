#ifndef __DCMOTOR_BRUSH_TIM_H__
#define __DCMOTOR_BRUSH_TIM_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include <stm32f10x.h>

/* 类型定义 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/
/*
 *         YS-F1Pro开发板专门预留电机控制接口              本例程合适使用接口
 *  TIM1_CH1  --  PA8         TIM1_CH1N  --  PB13                 Y
 *  TIM1_CH2  --  PA9         TIM1_CH2N  --  PB14                 Y
 *  TIM1_CH3  --  PA10        TIM1_CH3N  --  PB15                 Y
 *  TIM1_BKIN --  PB12
 *  TIM3_CH3  --  PB0
 *  TIM3_CH4  --  PB1
 *  TIM3_ETR  --  PD2
 *
 */
#define DCMOTOR_BRUSH_TIMx                       TIM1
#define DCMOTOR_BRUSH_TIM_APBxClock_FUN          RCC_APB2PeriphClockCmd
#define DCMOTOR_BRUSH_TIM_CLK                    RCC_APB2Periph_TIM1

#define DCMOTOR_BRUSH_TIM_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define DCMOTOR_BRUSH_TIM_GPIO_CLK               (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB)
#define DCMOTOR_BRUSH_TIM_CH1_PORT               GPIOA
#define DCMOTOR_BRUSH_TIM_CH1_PIN                GPIO_Pin_8
#define DCMOTOR_BRUSH_TIM_CH2_PORT               GPIOA
#define DCMOTOR_BRUSH_TIM_CH2_PIN                GPIO_Pin_9
#define DCMOTOR_BRUSH_TIM_CH3_PORT               GPIOA
#define DCMOTOR_BRUSH_TIM_CH3_PIN                GPIO_Pin_10

#define DCMOTOR_BRUSH_TIM_CH1N_PORT              GPIOB
#define DCMOTOR_BRUSH_TIM_CH1N_PIN               GPIO_Pin_13
#define DCMOTOR_BRUSH_TIM_CH2N_PORT              GPIOB
#define DCMOTOR_BRUSH_TIM_CH2N_PIN               GPIO_Pin_14
#define DCMOTOR_BRUSH_TIM_CH3N_PORT              GPIOB
#define DCMOTOR_BRUSH_TIM_CH3N_PIN               GPIO_Pin_15

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/

void DCMOTOR_BRUSH_TIMx_PWM_Init(void);
void DCMOTOR_25GA370_Contrl(uint8_t number,uint8_t direction,uint16_t speed);

#endif	/* __DCMOTOR_BRUSH_TIM_H__ */

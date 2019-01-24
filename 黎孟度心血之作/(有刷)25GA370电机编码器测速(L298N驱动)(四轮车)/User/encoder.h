#ifndef __ENCODER_TIM_H__
#define __ENCODER_TIM_H__

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>

/*
 *  预留控制接口                                          编码器合适使用接口
 *  TIM1_CH1  --  PA8         TIM1_CH1N  --  PB13                 
 *  TIM1_CH2  --  PA9         TIM1_CH2N  --  PB14                 
 *  TIM1_CH3  --  PA10        TIM1_CH3N  --  PB15                 
 *  TIM1_BKIN --  PB12
 *  TIM3_CH3  --  PB0                                             Y
 *  TIM3_CH4  --  PB1                                             Y
 *  TIM3_ETR  --  PD2
 *
 */
#define ENCODER_TIMx                       TIM3
#define ENCODER_TIM_APBxClock_FUN          RCC_APB1PeriphClockCmd
#define ENCODER_TIM_CLK                    RCC_APB1Periph_TIM3
#define ENCODER_TIM_Period                 0xFFFF           //定时器重载值65535
#define ENCODER_TIM_Prescaler              (72-1)  

#define ENCODER_TIM_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define ENCODER_TIM_GPIO_CLK               RCC_APB2Periph_GPIOB
#define ENCODER_TIM_PORT                   GPIOB
#define ENCODER_TIM_PIN                    GPIO_Pin_0

#define ENCODER_TIM_Channel_x              TIM_Channel_3    //通道3
#define ENCODER_TIM_IT_CCx                 TIM_IT_CC3
#define ENCODER_TIM_GetCapturex_FUN        TIM_GetCapture3

#define ENCODER_TIMx_IRQn                  TIM3_IRQn        //中断
#define ENCODER_TIMx_IRQHandler            TIM3_IRQHandler

#define ENCODER_TIM_ICPolarity             TIM_ICPolarity_Rising//测量的起始边沿

void TIMx_DCmotor_ENCODER_Init(void);

#endif	


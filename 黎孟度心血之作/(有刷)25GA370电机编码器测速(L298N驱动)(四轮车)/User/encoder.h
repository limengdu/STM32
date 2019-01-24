#ifndef __ENCODER_TIM_H__
#define __ENCODER_TIM_H__

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>

/*
 *  Ԥ�����ƽӿ�                                          ����������ʹ�ýӿ�
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
#define ENCODER_TIM_Period                 0xFFFF           //��ʱ������ֵ65535
#define ENCODER_TIM_Prescaler              (72-1)  

#define ENCODER_TIM_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define ENCODER_TIM_GPIO_CLK               RCC_APB2Periph_GPIOB
#define ENCODER_TIM_PORT                   GPIOB
#define ENCODER_TIM_PIN                    GPIO_Pin_0

#define ENCODER_TIM_Channel_x              TIM_Channel_3    //ͨ��3
#define ENCODER_TIM_IT_CCx                 TIM_IT_CC3
#define ENCODER_TIM_GetCapturex_FUN        TIM_GetCapture3

#define ENCODER_TIMx_IRQn                  TIM3_IRQn        //�ж�
#define ENCODER_TIMx_IRQHandler            TIM3_IRQHandler

#define ENCODER_TIM_ICPolarity             TIM_ICPolarity_Rising//��������ʼ����

void TIMx_DCmotor_ENCODER_Init(void);

#endif	


#ifndef _TIM_H
#define _TIM_H

#include "user_common.h"

/********TIM12_Pin_define********/
#define TIM12_CH1_GPIO_CLK          RCC_AHB1Periph_GPIOH
#define TIM12_CH1_GPIO_PORT         GPIOH
#define TIM12_CH1_Pin          	 	GPIO_Pin_6
#define TIM12_CH1_PINSOURCE			GPIO_PinSource6
#define TIM12_CH1_ENABLE			1

#define TIM12_CH2_GPIO_CLK          RCC_AHB1Periph_GPIOH
#define TIM12_CH2_GPIO_PORT         GPIOH
#define TIM12_CH2_Pin          	 	GPIO_Pin_9
#define TIM12_CH2_PINSOURCE			GPIO_PinSource9
#define TIM12_CH2_ENABLE			1
/********TIM12_Pin_define_END********/

void TIM6_CounterMode(u16 prescaler, u16 period);
void TIM7_CounterMode(u16 prescaler, u16 period);
void TIM12_PWMOutput(u16 prescaler, u16 period, u16 Pulse);
static void TIM12_GPIOInit(void);

#endif

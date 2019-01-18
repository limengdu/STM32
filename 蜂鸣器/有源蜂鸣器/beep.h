#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f10x.h"

#define BEEP_PORT_RCC   RCC_APB2Periph_GPIOX     //修改：开启BEEP对应的时钟位
#define BEEP_PORT       GPIOX                    //修改：IO口
#define BEEP_PIN        GPIO_Pin_X               //修改：引脚标号


void BEEP_Init(void);

#endif








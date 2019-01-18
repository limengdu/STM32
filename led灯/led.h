#ifndef _led_H
#define _led_H

#include "stm32f10x.h"

#define LED_PORT_RCC   RCC_APB2Periph_GPIOX     //修改：开启LED对应的时钟位
#define LED_PORT       GPIOX                    //修改：IO口
#define LED_PIN        GPIO_Pin_X               //修改：引脚标号


void LED_Init(void);

#endif








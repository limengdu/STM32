#ifndef _key_H
#define _key_H

#define GPIO_KEY_RCC   RCC_APB2Periph_GPIOX  //修改：按键所在的时钟
#define KEY_PORT_PIN   GPIO_Pin_X            //修改：按键对应的引脚标号
#define KEY_MODE       GPIO_Mode_IPU         //上拉输入（常规按键一般的输入模式，按键原接地）
//#define KEY_MODE     GPIO_Mode_IPD         //下拉输入（如果是一些像复位按键一样原来就接高电平的按键，可以使用下拉输入模式）
#define KEY_PORT       GPIOX                 //修改：按键对应的IO口

void KEY_Init(void);

#endif





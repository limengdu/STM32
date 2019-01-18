#ifndef __BEEP_H
#define __BEEP_H	 

#define BEEP_PORT	GPIOX	       //修改：定义蜂鸣器IO接口
#define BEEP_PIN	GPIO_Pin_X	   //修改：定义蜂鸣器引脚号


void BEEP_Init(void);              //初始化
void BEEP_1(void);                 //响一声


#endif

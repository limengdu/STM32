#ifndef __LED_H
#define __LED_H

#include "user_common.h"

void LED_GPIO_Config(void);

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_7)
#define LED1_OFF		   digitalHi(GPIOE,GPIO_Pin_7)
#define LED1_ON			   digitalLo(GPIOE,GPIO_Pin_7)



#endif /*__GPIO_H*/

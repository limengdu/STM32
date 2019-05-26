#ifndef __LED_H
#define __LED_H

#include "user_common.h"

void LED_GPIO_Config(void);

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_7)
#define LED1_OFF		   digitalHi(GPIOE,GPIO_Pin_7)
#define LED1_ON			   digitalLo(GPIOE,GPIO_Pin_7)
#define LED_Pin        GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8



#endif /*__GPIO_H*/

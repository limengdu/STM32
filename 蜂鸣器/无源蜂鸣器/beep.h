#ifndef __BEEP_H
#define __BEEP_H	 

#define BEEP_PORT	GPIOX	       //�޸ģ����������IO�ӿ�
#define BEEP_PIN	GPIO_Pin_X	   //�޸ģ�������������ź�


void BEEP_Init(void);              //��ʼ��
void BEEP_1(void);                 //��һ��


#endif

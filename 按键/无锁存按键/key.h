#ifndef _key_H
#define _key_H

#define GPIO_KEY_RCC   RCC_APB2Periph_GPIOX  //�޸ģ��������ڵ�ʱ��
#define KEY_PORT_PIN   GPIO_Pin_X            //�޸ģ�������Ӧ�����ű��
#define KEY_MODE       GPIO_Mode_IPU         //�������루���水��һ�������ģʽ������ԭ�ӵأ�
//#define KEY_MODE     GPIO_Mode_IPD         //�������루�����һЩ��λ����һ��ԭ���ͽӸߵ�ƽ�İ���������ʹ����������ģʽ��
#define KEY_PORT       GPIOX                 //�޸ģ�������Ӧ��IO��

void KEY_Init(void);

#endif





#ifndef _key_H
#define _key_H

#define GPIO_KEY_RCC   RCC_APB2Periph_GPIOX                          //�޸ģ��������ڵ�ʱ��
#define KEY_PORT_PIN   GPIO_Pin_X|GPIO_Pin_X|GPIO_Pin_X              //�޸ģ�������Ӧ�����ű��
#define KEY_UP_PIN     GPIO_Pin_X                                    //�޸�
#define KEY_MODE       GPIO_Mode_IPU                                 //�������루���水��һ�������ģʽ������ԭ�ӵأ�
#define KEY_SET_MODE   GPIO_Mode_IPD                                 //�������루�����һЩ��λ����һ��ԭ���ͽӸߵ�ƽ�İ���������ʹ����������ģʽ��
#define KEY_PORT       GPIOX                                         //�޸ģ�������Ӧ��IO��

#define KEY_LEFT_Pin    GPIO_Pin_X                                   //�޸�
#define KEY_DOWN_Pin    GPIO_Pin_X                                   //�޸�
#define KEY_RIGHT_Pin   GPIO_Pin_X                                   //�޸�
#define KEY_UP_Pin      GPIO_Pin_X                                   //�޸�

//ʹ��λ����������
#define K_UP    PXin(X)                                              //�޸�
#define K_DOWN  PXin(X)                                              //�޸�
#define K_LEFT  PXin(X)                                              //�޸�
#define K_RIGHT PXin(X)                                              //�޸�

//��ȡ���Źܿڶ��� 
//#define K_UP      GPIO_ReadInputDataBit(KEY_PORT,KEY_UP_Pin)
//#define K_DOWN    GPIO_ReadInputDataBit(KEY_PORT,KEY_DOWN_Pin)
//#define K_LEFT    GPIO_ReadInputDataBit(KEY_PORT,KEY_LEFT_Pin)
//#define K_RIGHT   GPIO_ReadInputDataBit(KEY_PORT,KEY_RIGHT_Pin)

//�����������ֵ��ͨ������ֵ����ĳ������
#define KEY_UP     1
#define KEY_DOWN   2
#define KEY_LEFT   3
#define KEY_RIGHT  4  


void KEY_Init(void);

#endif





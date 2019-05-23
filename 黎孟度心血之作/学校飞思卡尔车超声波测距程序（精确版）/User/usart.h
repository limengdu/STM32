/*-------------------------------------------------------------------------------
�ļ����ƣ�usart.h
�ļ��������������õ���غ궨�塢�����������ü����ж����ù��ܺ�����    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>

#define 						EN_USART2_RX												

#define             USART_BAUD_RATE                       115200

#define             USARTx                            		USART2
#define             USART_APBxClock_FUN                   RCC_APB1PeriphClockCmd												// ����ʱ��ʹ�ܺ��� (*)
#define             USART_CLK                             RCC_APB1Periph_USART2												  // APB1�����µ�USART2
#define             USART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd												// GPIOʱ��ʹ�ܺ��� (*)
#define             USART_GPIO_CLK                        RCC_APB2Periph_GPIOA   												// APB2�����µ�GPIOA
#define             USART_TX_PORT                         GPIOA   
#define             USART_TX_PIN                          GPIO_Pin_2
#define             USART_RX_PORT                         GPIOA   
#define             USART_RX_PIN                          GPIO_Pin_3
#define             USART_IRQ                             USART2_IRQn
#define             USART_INT_FUN                         USART2_IRQHandler

void USARTx_Init(void);

#endif

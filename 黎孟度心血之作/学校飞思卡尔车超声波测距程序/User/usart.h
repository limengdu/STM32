/*-------------------------------------------------------------------------------
文件名称：usart.h
文件描述：串口配置等相关宏定义、声明串口配置及其中断配置功能函数。    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>

#define 						EN_USART2_RX												

#define             USART_BAUD_RATE                       115200

#define             USARTx                            		USART2
#define             USART_APBxClock_FUN                   RCC_APB1PeriphClockCmd												// 串口时钟使能函数 (*)
#define             USART_CLK                             RCC_APB1Periph_USART2												  // APB1总线下的USART2
#define             USART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd												// GPIO时钟使能函数 (*)
#define             USART_GPIO_CLK                        RCC_APB2Periph_GPIOA   												// APB2总线下的GPIOA
#define             USART_TX_PORT                         GPIOA   
#define             USART_TX_PIN                          GPIO_Pin_2
#define             USART_RX_PORT                         GPIOA   
#define             USART_RX_PIN                          GPIO_Pin_3
#define             USART_IRQ                             USART2_IRQn
#define             USART_INT_FUN                         USART2_IRQHandler

void USARTx_Init(void);

#endif

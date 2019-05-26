#ifndef __USART_H
#define __USART_H

#include "user_common.h"

#define USART1_BUFFLEN	255
#define USART2_BUFFLEN	255

/********USART1_Pin_define********/
#define USART1_TX_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define USART1_TX_GPIO_PORT         GPIOB
#define USART1_TX_Pin          	 	  GPIO_Pin_6
#define USART1_TX_PINSOURCE			    GPIO_PinSource6

#define USART1_RX_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define USART1_RX_GPIO_PORT         GPIOB
#define USART1_RX_Pin           	  GPIO_Pin_7
#define USART1_RX_PINSOURCE			    GPIO_PinSource7
/********USART1_Pin_define_END********/

/********USART1_DMA_define********/
#define USART1_RX_ADDR						  (uint32_t)(&USART1->DR)	//串口1数据寄存器地址
#define USART1_RX_DMA_CHANNEL        DMA_Channel_4		//DMA通道号
#define USART1_RX_DMA_STREAM         DMA2_Stream2		//DMA数据流
/********USART1_DMA_define_END********/

/********USART2_Pin_define********/
#define USART2_TX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART2_TX_GPIO_PORT         GPIOD
#define USART2_TX_Pin          	 	       GPIO_Pin_5
#define USART2_TX_PINSOURCE			    GPIO_PinSource5

#define USART2_RX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART2_RX_GPIO_PORT         GPIOD
#define USART2_RX_Pin           	  GPIO_Pin_6
#define USART2_RX_PINSOURCE			    GPIO_PinSource6
/********USART2_Pin_define_END********/

/********USART2_DMA_define********/
#define USART2_RX_ADDR						  (uint32_t)(&USART2->DR)	//串口1数据寄存器地址
#define USART2_RX_DMA_CHANNEL        DMA_Channel_4		//DMA通道号
#define USART2_RX_DMA_STREAM         DMA1_Stream5		//DMA数据流
/********USART2_DMA_define_END********/

/********USART3_Pin_define********/
#define USART3_TX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART3_TX_GPIO_PORT         GPIOD
#define USART3_TX_Pin          	 	GPIO_Pin_8
#define USART3_TX_PINSOURCE			GPIO_PinSource8

#define USART3_RX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART3_RX_GPIO_PORT         GPIOD
#define USART3_RX_Pin           	GPIO_Pin_9
#define USART3_RX_PINSOURCE			GPIO_PinSource9
/********USART3_Pin_define_END********/

/********USART3_DMA_define********/
#define USART3_RX_ADDR						(uint32_t)(&USART3->DR)	//串口1数据寄存器地址
#define USART3_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART3_RX_DMA_STREAM           		DMA1_Stream1		//DMA数据流
/********USART3_DMA_define_END********/

/********USART6_Pin_define********/
#define USART6_TX_GPIO_CLK          RCC_AHB1Periph_GPIOG
#define USART6_TX_GPIO_PORT         GPIOG
#define USART6_TX_Pin          	 	  GPIO_Pin_14
#define USART6_TX_PINSOURCE			    GPIO_PinSource14

#define USART6_RX_GPIO_CLK          RCC_AHB1Periph_GPIOG
#define USART6_RX_GPIO_PORT         GPIOG
#define USART6_RX_Pin           	  GPIO_Pin_9
#define USART6_RX_PINSOURCE			    GPIO_PinSource9
/********USART6_Pin_define_END********/

/********USART6_DMA_define********/
#define USART6_RX_ADDR						  (uint32_t)(&USART6->DR)	//串口1数据寄存器地址
#define USART6_RX_DMA_CHANNEL        DMA_Channel_5		//DMA通道号
#define USART6_RX_DMA_STREAM         DMA2_Stream1		//DMA数据流
/********USART6_DMA_define_END********/


extern char USART2_buff[USART2_BUFFLEN];
extern uint8_t USART2_Pointer;

void USART1_QuickInit(uint32_t USART_BaudRate);
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);


void USART2_QuickInit(uint32_t USART_BaudRate);
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize);


void USART3_QuickInit(uint32_t USART_BaudRate);
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize);


void USART6_QuickInit(uint32_t USART_BaudRate);
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize);

void USART_sendChar(USART_TypeDef* USARTx, char ch);
void USART_setPort(USART_TypeDef* USARTx);
	

#endif /* __USART_H */

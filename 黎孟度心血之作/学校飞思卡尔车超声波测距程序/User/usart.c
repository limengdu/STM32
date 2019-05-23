/*-------------------------------------------------------------------------------
文件名称：usart.c
文件描述：串口配置及其中断配置功能函数。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "usart.h"

/*-------------------------------------------------------------------------------
函数名称：USARTx_Init
函数描述：初始化串口基本配置参数
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void USARTx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	USART_GPIO_APBxClock_FUN(USART_GPIO_CLK, ENABLE);																// 第1步：打开GPIO和USART部件的时钟
	USART_APBxClock_FUN(USART_CLK, ENABLE);
	
	USART_DeInit(USARTx);  																													// 第2步：串口复位,复位串口2
	
	GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;																			// 第3步：将USART Tx的GPIO配置为推挽复用模式 ,将USART Rx的GPIO配置为浮空输入模式（GPIO端口设置模式）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_PORT, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = USART_BAUD_RATE;														// 第4步：设置串口初始化参数
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									// 收发模式
	USART_Init(USARTx, &USART_InitStructure);																				// 串口初始化

	/* 
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
	*/
	

#ifdef EN_USART2_RX
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);													  			// 使能接收中断																									  // 第5步：初始化NVIC并开启中断
#endif

	USART_Cmd(USARTx, ENABLE);																											// 使能串口 
	
/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USARTx, USART_FLAG_TC);     																		// 清发送完成标志，Transmission Complete flag
}











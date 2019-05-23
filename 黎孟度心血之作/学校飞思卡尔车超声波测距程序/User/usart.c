/*-------------------------------------------------------------------------------
�ļ����ƣ�usart.c
�ļ��������������ü����ж����ù��ܺ�����
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "usart.h"

/*-------------------------------------------------------------------------------
�������ƣ�USARTx_Init
������������ʼ�����ڻ������ò���
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void USARTx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	USART_GPIO_APBxClock_FUN(USART_GPIO_CLK, ENABLE);																// ��1������GPIO��USART������ʱ��
	USART_APBxClock_FUN(USART_CLK, ENABLE);
	
	USART_DeInit(USARTx);  																													// ��2�������ڸ�λ,��λ����2
	
	GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;																			// ��3������USART Tx��GPIO����Ϊ���츴��ģʽ ,��USART Rx��GPIO����Ϊ��������ģʽ��GPIO�˿�����ģʽ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_PORT, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = USART_BAUD_RATE;														// ��4�������ô��ڳ�ʼ������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									// �շ�ģʽ
	USART_Init(USARTx, &USART_InitStructure);																				// ���ڳ�ʼ��

	/* 
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	

#ifdef EN_USART2_RX
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);													  			// ʹ�ܽ����ж�																									  // ��5������ʼ��NVIC�������ж�
#endif

	USART_Cmd(USARTx, ENABLE);																											// ʹ�ܴ��� 
	
/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USARTx, USART_FLAG_TC);     																		// �巢����ɱ�־��Transmission Complete flag
}











/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/*******************************************************************************
* �� �� ��         : DEBUG_USART_Init
* ��������		   : ���ص��Դ��ڲ�������
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void DEBUG_USART_Init(void)
{
  //����ṹ�����
  GPIO_InitTypeDef GPIO_InitStructure;
  //����USART��ʼ���ṹ�����
  USART_InitTypeDef USART_InitStructure;
  //ʹ��USARTʱ��
  DEBUG_USARTx_ClockCmd(DEBUG_USARTx_CLK,ENABLE);
  DEBUG_USARTx_GPIO_ClockCmd(DEBUG_USARTx_TX_CLK | DEBUG_USARTx_RX_CLK 
	                                              | RCC_APB2Periph_AFIO,ENABLE);
  //ʹ��USART����GPIOʱ��
  
  //����USART����GPIO��ʼ��
  GPIO_InitStructure.GPIO_Pin =  DEBUG_USARTx_TX_PIN;
  //�趨USART���Ͷ�ӦIO���
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  //�趨USART���Ͷ�ӦIOģʽ�������������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //�趨USART���Ͷ�ӦIO�������ٶ� ��GPIO_Speed_50MHz
  GPIO_Init(DEBUG_USARTx_TX_PORT, &GPIO_InitStructure); 
  //��ʼ��USART���Ͷ�ӦIO   
  
  GPIO_InitStructure.GPIO_Pin = DEBUG_USARTx_RX_PIN;
  //�趨USART���ն�ӦIO���
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //�趨USART���Ͷ�ӦIOģʽ����������
  //����û�����¸�ֵ�ĳ�Աʹ���봮�ڷ�����ͬ����
  GPIO_Init(DEBUG_USARTx_RX_PORT, &GPIO_InitStructure);	
  //��ʼ��USART���ն�ӦIO
			
  //USART������������
  USART_InitStructure.USART_BaudRate = DEBUG_USARTx_BAUDRATE;
  //USART������:115200
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  //USART�ֳ�(��Чλ)��8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  //USARTֹͣλ��1λ
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  //USARTУ��λ����
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  //USARTӲ������������(Ӳ���źſ��ƴ���ֹͣ)����
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  //USART����ģʽʹ�ܣ�������պͷ���
  USART_Init(DEBUG_USARTx, &USART_InitStructure);
  //��ʼ��USART
	
  USART_Cmd(DEBUG_USARTx, ENABLE);
  //ʹ��USART
}

/*******************************************************************************
* �� �� ��         : fputc
* ��������		   : �ض���c�⺯��printf��USARTx
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
int fputc(int ch, FILE *f)
{
  USART_SendData(DEBUG_USARTx, (uint8_t) ch);
  //����һ���ֽ����ݵ����Դ���
  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);	
  //�ȴ��������ݷ������	
  return (ch);
}

/*******************************************************************************
* �� �� ��         : fgetc
* ��������		   : �ض���c�⺯��getchar,scanf��USARTx
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
int fgetc(FILE *f)
{
  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);
  //�ȴ�������������
  return (int)USART_ReceiveData(DEBUG_USARTx);
}



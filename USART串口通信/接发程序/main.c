#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "usart.h"


int main (void)//������
{
	u8 a;
	//��ʼ������
	RCC_Configuration(); //ʱ������

	USART1_Init(115200); //���ڳ�ʼ���������ǲ����ʣ�

	//��ѭ��
	while(1)
	{
		//��ѯ��ʽ����
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET)//��ѯ���ڴ������־λ
		{  
			a =USART_ReceiveData(USART1);//��ȡ���յ�������
			printf("%c",a); //���յ������ݷ��ͻص���		  
	    }
		 
	}
}




/*
���������塿
u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8     a; //����8λ�޷��ű���a
vu32     a; //�����ױ��32λ�޷��ű���a
vu16     a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32     a; //����ֻ����32λ�޷��ű���a
uc16     a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

#define ONE  1   //�궨��

delay_us(1); //��ʱ1΢��
delay_ms(1); //��ʱ1����
delay_s(1); //��ʱ1��

*/




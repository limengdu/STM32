#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"


int main (void)//������
{
	u8 a;
	u8 key;
	//��ʼ������
	RCC_Configuration(); //ʱ������
	LED_Init();//LED��ʼ��
	KEY_Init();//������ʼ��
	USART1_Init(115200); //���ڳ�ʼ���������ǲ����ʣ�

	//��ѭ��
	while(1)
	{

		//��ѯ��ʽ���գ�������ӳ����󣬿�����Ҫ���Ͷ�����ݲ���ʵ�����Ϊ�˱������������������ǿ��Դ򿪴��ڵ��жϺ���
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET)//��ѯ���ڴ������־λ
			{ 
			a =USART_ReceiveData(USART1);//��ȡ���յ�������
			switch (a)
			{
				case '0':
					GPIO_SetBits(LED_PORT,GPIO_Pin_0); //LED1����
					printf("%c:LED1 OFF ",a); //���յ������ݷ��ͻص���
					break;
				case '1':
					GPIO_ResetBits(LED_PORT,GPIO_Pin_0); //LED1����
					printf("%c:LED1 ON ",a); //���յ������ݷ��ͻص���
					break;
				case '2':
					led2 = 1;                 //LED2����
					printf("%c:LED2 OFF ",a); //���յ������ݷ��ͻص���
					break;
				case '3':
					led2 = 0;                 //LED2����
					printf("%c:LED2 ON ",a); //���յ������ݷ��ͻص���
					break;
				default:
					break;
			}		  
		}

//��������(ע�����ﲻ���Է����жϷ������У���Ϊû�з����жϵ��������Խ����ж�)
        key=KEY_Scan(0);   //ɨ�谴��
		switch(key)
		{
			case KEY_UP: printf("KEY_UP");break;      //����K_UP����    ����D2ָʾ��
			case KEY_DOWN: printf("KEY_DOWN");break;    //����K_DOWN����  Ϩ��D2ָʾ��
			case KEY_LEFT: printf("KEY_LEFT");break;    //����K_LEFT����  ����D3ָʾ��
			case KEY_RIGHT: printf("KEY_RIGHT");break;   //����K_RIGHT���� Ϩ��D3ָʾ��
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




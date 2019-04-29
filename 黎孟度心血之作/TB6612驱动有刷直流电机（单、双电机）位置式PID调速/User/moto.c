#include "moto.h"

/*******************************************************************************
* �� �� ��         : MOTO_Config
* ��������		   : ����tb6612��Ӧ���IO����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         �����߼����ת��״̬��Ĭ��״̬��ע��B���IO����
________________________________________________________________________________
    |  AIN1(PB11)  AIN2(PB12)  PWMA(PA8)   A01       A02       ���ת������  |
    |  �ߵ�ƽ(1)   �͵�ƽ(0)      1      �������  �������    ��ת(˳ʱ��)  |
    |  BIN1(PB14)  BIN2(PB15)  PWMB(PB13)  B01       B02       ���ת������  |
    |  �ߵ�ƽ(1)   �͵�ƽ(0)      1      �������  �������    ��ת(˳ʱ��)  |
________________________________________________________________________________
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void MOTO_Config(void)
{
	//����һ��GPIO_InitTypeDef���͵Ľṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//����GPIOB������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
	//ѡ��Ҫ���Ƶ�GPIOB����													   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 
	                              | GPIO_Pin_14 | GPIO_Pin_15
	                              ;
	//��������ģʽΪͨ���������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	//������������Ϊ50MHz
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	//���ÿ⺯������ʼ��GPIOB
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	//�͵�ƽ��ȷ����ʼ״̬�µ������ֹͣ״̬
	GPIO_SetBits(GPIOB,GPIO_Pin_11 | GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_14 | GPIO_Pin_15);
}





/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "encoder.h"
#include "control.h"
#include "pid.h"
#include "usart.h"


extern int Encoder_Left;                     //����������������
extern int Encoder_Right;

int Moto1;
int Moto2;

int Target_position1=0;              //�趨���1��Ŀ���ٶ�
int Target_position2=20;              //�趨���2��Ŀ���ٶ�

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
	//���ָ����TIM3�жϷ������
		{	
			Encoder_Left=Read_Encoder(2);           //����������ֵ��������
			Encoder_Right=Read_Encoder(4);          //����������ֵ��������
			
			Moto1=LocPIDCalc_PID1(Encoder_Left,Target_position1);
			MOTOR_CONTROL1(Moto1);
			Xianfu_Pwm(&Moto1,COMPARE_VALUE);
			
			Moto2=LocPIDCalc_PID2(Encoder_Right,Target_position2);
			MOTOR_CONTROL2(Moto2);
			Xianfu_Pwm(&Moto2,COMPARE_VALUE);
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIM3���жϴ�����λ
}


#if EN_USART1   //USART2ʹ��������ѡ��
void USART1_IRQHandler(void)//����1�жϷ�����򣨹̶��ĺ����������޸ģ�
{ 	
	u8 Res;
	//�������ַ������յ�USART1_RX_BUF[]�ĳ���(USART1_RX_STA&0x3FFF)�����ݵĳ��ȣ��������س���
	//��(USART1_RX_STA&0xC000)Ϊ��ʱ��ʾ���ݽ�����ɣ��������ն��ﰴ�»س�����
	//����������д�ж�if(USART1_RX_STA&0xC000)��Ȼ���USART1_RX_BUF[]���飬����0x0d 0x0a���ǽ�����
	//ע���������������괮�����ݺ�Ҫ��USART1_RX_STA��0
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		printf("%c",Res); //���յ��������� a���ű��� ���ͻص���		
		if((USART1_RX_STA&0x8000)==0)//����δ���
		{			
			if(USART1_RX_STA&0x4000)//���յ���0x0d
			{				
				if(Res!=0x0a)USART1_RX_STA=0;//���մ���,���¿�ʼ
				else USART1_RX_STA|=0x8000;	//��������� 
			}
			else//��û�յ�0X0D
			{ 					
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ; //���յ������ݷ�������
					USART1_RX_STA++;	//���ݳ��ȼ�����1
					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
	} 
} 
#endif


/*******************************************************************************
* �� �� ��         : USART2_IRQHandler
* ��������		   : USART2�жϷ�����
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
#if EN_USART2   //USART2ʹ��������ѡ��
void USART2_IRQHandler(void)//����2�жϷ�����򣨹̶��ĺ����������޸ģ�
{ 	
	u8 Res;
	//�������ַ������յ�USART2_RX_BUF[]�ĳ���(USART2_RX_STA&0x3FFF)�����ݵĳ��ȣ��������س���
	//��(USART2_RX_STA&0xC000)Ϊ��ʱ��ʾ���ݽ�����ɣ��������ն��ﰴ�»س�����
	//����������д�ж�if(USART2_RX_STA&0xC000)��Ȼ���USART2_RX_BUF[]���飬����0x0d 0x0a���ǽ�����
	//ע���������������괮�����ݺ�Ҫ��USART2_RX_STA��0
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{  		
		Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		printf("%c",Res); //���յ��������� a���ű��� ���ͻص���		
		if((USART2_RX_STA&0x8000)==0)//����δ���
		{			
			if(USART2_RX_STA&0x4000)//���յ���0x0d
			{				
				if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
				else USART2_RX_STA|=0x8000;	//��������� 
			}
			else//��û�յ�0X0D
			{ 					
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ; //���յ������ݷ�������
					USART2_RX_STA++;	//���ݳ��ȼ�����1
					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
	} 
} 
#endif


/*******************************************************************************
* �� �� ��         : USART3_IRQHandler
* ��������		   : USART3�жϷ�����
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
#if EN_USART3   //USART2ʹ��������ѡ��
void USART3_IRQHandler(void)
{ 	
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//�����ж�
	{  
		Res =USART_ReceiveData(USART3);//��ȡ���յ�������
		if(Res=='S'){//�ж������Ƿ���STOP��ʡ�Զ�ȡS��			
			USART3_RX_STA=1;//�����STOP���־λΪ1	  
		}else if(Res=='K'){//�ж������Ƿ���OK��ʡ�Զ�ȡK��			
			USART3_RX_STA=2;//�����OK���־λΪ2	  
		}   		 
	}
} 
#endif




/********************** (C) COPYRIGHT 2019 GCUwildwolfteam *********************
**********************************END OF FILE**********************************/

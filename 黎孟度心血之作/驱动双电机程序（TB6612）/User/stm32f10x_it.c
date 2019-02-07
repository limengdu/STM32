/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "control.h"
#include "timer.h"

int time=0;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* �� �� ��         : main
* ��������		   : TIM1�жϣ�PWM�������
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void TIM1_IRQHandler(void)                             //TIM1�ж�
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���TIM1�жϷ������
	{
		time++;                                        //PWMֵ����
		if(time<500)
			{
				MOTOR_CONTROL(time);	               //�����������
			}
		else if(time>500)
			{ 
				time=-time;                            //��ת���PWMֵ
				MOTOR_CONTROL(time);                   //�����������
			}
		else if(time>1000)                             //�޷�
			{
				time=0;                                //PWMֵ����
			}		
	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);        //���TIMx���жϴ�����λ
}


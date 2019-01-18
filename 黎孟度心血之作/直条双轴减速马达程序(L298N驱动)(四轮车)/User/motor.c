/* Includes ------------------------------------------------------------------*/
#include "motor.h"
#include "tim.h"
#include "stm32f10x.h"

/*******************************************************************************
* �� �� ��         : MotorGPIO_Configuration
* ��������		   : ���õ��GPIO
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void MotorGPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_F_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(FRONT_LEFT_F_GPIO, &GPIO_InitStructure);    
	
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_B_PIN;	
	GPIO_Init(FRONT_LEFT_B_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_F_PIN;	
	GPIO_Init(FRONT_RIGHT_F_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_B_PIN;	
	GPIO_Init(FRONT_RIGHT_B_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_F_PIN;	
	GPIO_Init(BEHIND_LEFT_F_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_B_PIN;	
	GPIO_Init(BEHIND_LEFT_B_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_F_PIN;	
	GPIO_Init(BEHIND_RIGHT_F_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_B_PIN;	
	GPIO_Init(BEHIND_RIGHT_B_GPIO, &GPIO_InitStructure);  
}

/*******************************************************************************
* �� �� ��         : CarMove
* ��������		   : ����ռ�ձ��������ת��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void CarMove(void)
{   
	
	 BEHIND_RIGHT_EN;    //ʹ�����ҵ��
	
 //��ǰ�֣������������ߵ���ֱ���һ�����������������ֲ������ɣ�
//	if(front_left_speed_duty > 0)//��ǰ
//	{
//		if(speed_count < front_left_speed_duty)
//		{
//			FRONT_LEFT_GO;
//		}
//	    else
//		{
//			FRONT_LEFT_STOP;
//		}
//	}
//	else if(front_left_speed_duty < 0)//���
//	{
//		if(speed_count < (-1)*front_left_speed_duty)
//		{
//			FRONT_LEFT_BACK;
//		}
//		else
//		{
//			FRONT_LEFT_STOP;
//		}
//	}
//	else                //ֹͣ
//	{
//		FRONT_LEFT_STOP;
//	}
	
	//��ǰ�֣������������ߵ���ֱ���һ���������ұ�����ǰ�ֲ������ɣ�
	if(front_right_speed_duty > 0)//��ǰ
	{
		if(speed_count < front_right_speed_duty) 
		{                      //speed_count���Ϊ50��front_right_speed_dutyΪ40
			FRONT_RIGHT_GO;    
		}
		else                   //��10ms��ֹͣʱ��,��Ϊ���ա���ʱ��
		{
			FRONT_RIGHT_STOP;  
		}
		//ֹͣ�������ǲ���ƽ���ٶ�
		//����˼·��ͨ����ʱ�������жϣ�ͨ��ʱ����ڵ��ռ�ձ�ʵ�ֵ���
	}
	else if(front_right_speed_duty < 0)//���
	{
		if(speed_count < (-1)*front_right_speed_duty)
		{
			FRONT_RIGHT_BACK;
		}
		else                //ֹͣ
		{
			FRONT_RIGHT_STOP;
		}
	}
	else                //ֹͣ
	{
		FRONT_RIGHT_STOP;
	}
	
	//�����
	if(behind_left_speed_duty > 0)//��ǰ
	{
		if(speed_count < behind_left_speed_duty)
		{
			BEHIND_LEFT_GO;
		}	
		else                //ֹͣ
		{
			BEHIND_LEFT_STOP;
		}
	}
	else if(behind_left_speed_duty < 0)//���
	{
		if(speed_count < (-1)*behind_left_speed_duty)
		{
			BEHIND_LEFT_BACK;
		}	
		else                //ֹͣ
		{
			BEHIND_LEFT_STOP;
		}
	}
	else                //ֹͣ
	{
		BEHIND_LEFT_STOP;
	}
	
//	//�Һ���
//	if(behind_right_speed_duty > 0)//��ǰ
//	{
//		if(speed_count < behind_right_speed_duty)
//		{
//			BEHIND_RIGHT_GO;
//		}	
//	    else                //ֹͣ
//		{
//			BEHIND_RIGHT_STOP;
//		}
//	}
//	else if(behind_right_speed_duty < 0)//���
//	{
//		if(speed_count < (-1)*behind_right_speed_duty)
//		{
//			BEHIND_RIGHT_BACK;
//		}	
//	    else                //ֹͣ
//		{
//			BEHIND_RIGHT_STOP;
//		}
//	}
//	else                //ֹͣ
//	{
//		BEHIND_RIGHT_STOP;
//	}
}

/*******************************************************************************
* �� �� ��         : CarGo
* ��������		   : С��ǰ��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void CarGo(void)
{
	//front_left_speed_duty=SPEED_DUTY;
	front_right_speed_duty=SPEED_DUTY; // ����
	behind_left_speed_duty=SPEED_DUTY; //�ҵ��
	//behind_right_speed_duty=SPEED_DUTY;
}

/*******************************************************************************
* �� �� ��         : CarBack
* ��������		   : С������
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void CarBack(void)
{
	front_left_speed_duty=-SPEED_DUTY;
	front_right_speed_duty=-SPEED_DUTY;
	behind_left_speed_duty=-SPEED_DUTY;
	behind_right_speed_duty=-SPEED_DUTY;
}

/*******************************************************************************
* �� �� ��         : CarRight
* ��������		   : С����ת
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void CarRight(void)
{
	front_left_speed_duty=-SPEED_DUTY/2;
	front_right_speed_duty=SPEED_DUTY;
	behind_left_speed_duty=-SPEED_DUTY/2;
	behind_right_speed_duty=SPEED_DUTY+10;//���Ӻ���������
}

/*******************************************************************************
* �� �� ��         : CarLeft
* ��������		   : С����ת
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void CarLeft(void)
{
	front_left_speed_duty=SPEED_DUTY;
	front_right_speed_duty=-SPEED_DUTY/2;
	behind_left_speed_duty=SPEED_DUTY+10;//���Ӻ���������
	behind_right_speed_duty=-SPEED_DUTY/2;
}
/*��Ҫʵ��С����ת����ת���ߺ��ˣ�����Ҫ����Ӧ�����ŵ���ʱ��TIM2�жϷ�������
�У�������CarMove();֮�󡣻���Ҫע�����Ҫ��ԭ��CarGo();ע�͵�*/

/*******************************************************************************
* �� �� ��         : CarStop
* ��������		   : С��ֹͣ
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void CarStop(void)
{
	front_left_speed_duty=0;
	front_right_speed_duty=0;
	behind_left_speed_duty=0;
	behind_right_speed_duty=0;
}

/*******************************************************************************
* �� �� ��         : MotorInit
* ��������		   : �����ʼ��
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void MotorInit(void)
{
	MotorGPIO_Configuration();
	CarStop();
}



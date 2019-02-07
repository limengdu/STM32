/* Includes ------------------------------------------------------------------*/
#include "control.h"
#include "motor.h"

/*******************************************************************************
* �� �� ��         : MOTOR_CONTROL
* ��������		   : �������tb6612�߼�����
* ��    ��         : ��
* ��    ��         : ��
*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
void MOTOR_CONTROL(int Voltage)
{
	if(Voltage>0)
	{
	    GPIO_SetBits(GPIOB, GPIO_Pin_14 );		   //�������ģ��AIN1�� PB14		    
        GPIO_ResetBits(GPIOB, GPIO_Pin_15 );       //�������ģ��AIN2�� PB15	

		GPIO_SetBits(GPIOB, GPIO_Pin_13 );		   //�������ģ��BIN1�� PB13		    
        GPIO_ResetBits(GPIOB, GPIO_Pin_12 );       //�������ģ��BIN2�� PB12	
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_15 );		   //�������ģ��AIN1�� PB14			    
        GPIO_ResetBits(GPIOB, GPIO_Pin_14 );       //�������ģ��AIN2�� PB15	
  
		GPIO_SetBits(GPIOB, GPIO_Pin_12 );		   //�������ģ��BIN1�� PB12		    
        GPIO_ResetBits(GPIOB, GPIO_Pin_13 );       //�������ģ��BIN2�� PB13	
			
		Voltage=-Voltage;		
	}
	TIM_SetCompare3(TIM2,Voltage);
	//TIM2��Voltage�Աȣ�����ͬ��ת���Σ�����PWMռ�ձ�
	TIM_SetCompare4(TIM2,Voltage);
	//TIM3��Voltage�Աȣ�����ͬ��ת���Σ�����PWMռ�ձ�
}

/***************************TB6612������������߼���****************************
                   AIN1  AIN2  BIN1  BIN2  PWMA  PWMB  A01/A02
                    1     0     1     0      1     1    ��ת
                    0     1     0     1      1     1    ��ת
                    1     1     1     1      1     1    ɲ��
                    0     0     0     0      1     1    ����ͣ��
                    X     X     X     X      0     0    ɲ��
*******************************************************************************/


/*-------------------------------------------------------------------------------
�ļ����ƣ�task_scheduler.h
�ļ����������������ع��ܺ������塣
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "task_scheduler.h"
#include "barrier.h"
#include "encoder.h"
#include "control.h"
#include "ccdcontrol.h"
	 
u8 The_Task_Flag;
extern __IO int32_t PWM_Duty;

int c;

void Task_Init_Scheduler(void)
{
//	Delay_Init();															// ϵͳ��ʱ��ʼ��
	SysTick_Init();														// ϵͳ�δ�ʱ����ʼ��
	LED_Init();																// LED��ʼ��
	USARTx_Init();														// USART��ʼ��
	KEY_Init();																// KEY��ʼ��
	TIM_Init();																// Timer��ʼ��
	OLED_Init();	                 					  // OLED��ʼ�� ģ��SPI/Ӳ��SPI 
	Tracking_Init();													// Ѳ�������ʼ��
	CCD_Init();																// CCD��ʼ��
	#if EN_school_code
	Ultrasonic_Init();												// �����������ʼ��
	#endif
	#if EN_limengdu_code
	UltraSoundInit();
	#endif
	
	LED_State();
	Delay_ms(100);
	
	PWM_Duty = 0;
  MotorSpeedSetOne(PWM_Duty);  							// 0%
	PID_ParamInit();													// PID ������ʼ��
	
//	TIM_Init();															// Timer��ʼ��
}

void Task_Start_Scheduler(void)
{
	u32 Task_run;
	 
	Task_run = Tim7_counter % 10;
	switch (Task_run)
	{
		case  1: Task_Time(1);
						 if(The_Task_Flag == 1)
						 {
							 RD_TSL();
							 Find_CCD_Middle(); 					// ��ȡ����
							 Task_Exit();
						 }
						 
						 #if EN_school_code
						 Ultrasonic_Measure();
						 if(c == 2)
						 {
							 Ultcontrol();
							 ccdcon();
						 }
						 #endif
						 
						 #if EN_limengdu_code
						 Distance();
						 if(c == 2)
						 {
							 Ultcontrol();
						 }
						 #endif
						 
						 break;
			
		case  2: Task_Time(1);
						 if(The_Task_Flag == 1)
						 {
							 //Speed_Measurement(3);															// ��ʹ����TIM6�����������������
							 //Ultrasonic_Measure();
							 Task_Exit();
						 }
						 break;
						 
		case  3: break;
			
		default: break;
	}	
	
	Freescale_Control_Kernel(master);	
}

void Task_Time(u32 num)
{
	static u32 counter;
	
	counter++;
	if(counter == num)
	{
		Task_Enter();
		counter = 0;
	}
}

void Task_Enter(void)
{
	The_Task_Flag = 1;
}

void Task_Exit(void)
{
	The_Task_Flag = 0;
}

/*-------------------------------------------------------------------------------
文件名称：task_scheduler.h
文件描述：任务管理相关功能函数定义。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
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
//	Delay_Init();															// 系统延时初始化
	SysTick_Init();														// 系统滴答定时器初始化
	LED_Init();																// LED初始化
	USARTx_Init();														// USART初始化
	KEY_Init();																// KEY初始化
	TIM_Init();																// Timer初始化
	OLED_Init();	                 					  // OLED初始化 模拟SPI/硬件SPI 
	Tracking_Init();													// 巡线外设初始化
	CCD_Init();																// CCD初始化
	#if EN_school_code
	Ultrasonic_Init();												// 超声波外设初始化
	#endif
	#if EN_limengdu_code
	UltraSoundInit();
	#endif
	
	LED_State();
	Delay_ms(100);
	
	PWM_Duty = 0;
  MotorSpeedSetOne(PWM_Duty);  							// 0%
	PID_ParamInit();													// PID 参数初始化
	
//	TIM_Init();															// Timer初始化
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
							 Find_CCD_Middle(); 					// 提取中线
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
							 //Speed_Measurement(3);															// 因使用了TIM6，所以这里进行屏蔽
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

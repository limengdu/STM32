/*-------------------------------------------------------------------------------
�ļ����ƣ�task_scheduler.h
�ļ����������������ع��ܺ���������
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __TASK_SCHEDULER_H
#define __TASK_SCHEDULER_H

#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "tim.h"
#include "control.h"
#include "key.h"
#include "show.h"
#include "oled.h"
#include "encoder.h"
#include "steering_engine.h"
#include "tracking.h"
#include "systick.h"
#include "pid.h"
#include "motor.h"
#include "ultrasonic.h"
#include "ccd.h"

extern EncoderType GetEncoder;
extern u16 Tim7_counter;
extern u8 *master;

void Task_Init_Scheduler(void);
void Task_Start_Scheduler(void);
void Task_Time(u32 num);
void Task_Enter(void);
void Task_Exit(void);

#endif

/*-------------------------------------------------------------------------------
文件名称：task_scheduler.h
文件描述：任务管理相关功能函数声明。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
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

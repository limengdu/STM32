/*-------------------------------------------------------------------------------
文件名称：motor.h
文件描述：电机相关宏定义及其函数声明。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __MOTOR_H
#define	__MOTOR_H

#include "stm32f10x.h"
#include "stdlib.h"

//#define MOTOR_CONTROLL_WAY

#define PWMPeriod      		7200			// 4500 16kHZ  7200 10kHZ
#define PWMLOSS         	1					// 为1时，表示支持100%输出。 aHR0cHM6Ly96aGlkYW8uYmFpZHUuY29tL3F1ZXN0aW9uLzE2NDM0ODYwMTEyMzY5MTUxODAuaHRtbA==

#define MotorOneForward  	0
#define MotorOneBack     	1
#define MotorSpdZero     	0

void MotorSpeedSetOne(s32 MotorSpeed);

#endif

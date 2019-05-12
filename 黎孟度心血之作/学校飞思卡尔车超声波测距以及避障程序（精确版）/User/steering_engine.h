/*-------------------------------------------------------------------------------
文件名称：steering_engine.h
文件描述：舵机相关宏定义及其功能函数的声明。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __STEERING_ENGINE_H
#define __STEERING_ENGINE_H

#include "stm32f10x.h"

#define Servo_Period 			10000						//舵机周期

void Set_Joint_Angle(float angle);

#endif

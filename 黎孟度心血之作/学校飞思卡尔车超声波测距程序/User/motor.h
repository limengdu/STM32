/*-------------------------------------------------------------------------------
�ļ����ƣ�motor.h
�ļ������������غ궨�弰�亯��������
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __MOTOR_H
#define	__MOTOR_H

#include "stm32f10x.h"
#include "stdlib.h"

//#define MOTOR_CONTROLL_WAY

#define PWMPeriod      		7200			// 4500 16kHZ  7200 10kHZ
#define PWMLOSS         	1					// Ϊ1ʱ����ʾ֧��100%����� aHR0cHM6Ly96aGlkYW8uYmFpZHUuY29tL3F1ZXN0aW9uLzE2NDM0ODYwMTEyMzY5MTUxODAuaHRtbA==

#define MotorOneForward  	0
#define MotorOneBack     	1
#define MotorSpdZero     	0

void MotorSpeedSetOne(s32 MotorSpeed);

#endif

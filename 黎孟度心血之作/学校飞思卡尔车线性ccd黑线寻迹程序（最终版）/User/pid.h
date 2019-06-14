/*-------------------------------------------------------------------------------
文件名称：pid.h
文件描述：PID控制相关头文件
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"

typedef struct
{
  __IO int32_t  SetPoint;                                 // 设定目标 Desired Value
  __IO float    SumError;                                 // 误差累计
  __IO float    Proportion;                               // 比例常数 Proportional Const
  __IO float    Integral;                                 // 积分常数 Integral Const
  __IO float    Derivative;                               // 微分常数 Derivative Const
  __IO int      LastError;                                // Error[-1]
  __IO int      PrevError;                                // Error[-2]
}PID_TypeDef;

/*************************************/
// 定义PID相关宏
// 这三个参数设定对电机运行影响非常大
// PID参数跟采样时间息息相关
/*************************************/
#define  SPD_P_DATA      0.3f       										  // P参数
#define  SPD_I_DATA      0.1f        											// I参数
#define  SPD_D_DATA      0.1f        											// D参数

#define  TARGET_SPEED    100.0f       										// 目标速度   

/* 私有变量 ------------------------------------------------------------------*/
//__IO int32_t Spd_Pulse;            											  // 编码器捕获值 Pulse
//__IO int32_t LastSpd_Pulse;          											// 上一次编码器捕获值 Pulse
//__IO int32_t Spd_PPS;                											// 速度值 Pulse/Sample
//__IO float Spd_RPM;                  											// 速度值 r/m

void PID_ParamInit(void) ;
//int32_t ABS_SpdPIDCalc(float NextPoint);
int32_t INC_SpdPIDCalc(float NextPoint);

#endif

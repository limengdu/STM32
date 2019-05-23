/*-------------------------------------------------------------------------------
文件名称：encoder.h
文件描述：编码器相关功能函数声明。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __ENCODER_H
#define	__ENCODER_H

#include "stm32f10x.h"

#define PI 3.141592653589793

#define WHEEL_GEAR 				76 													// 车轮齿轮齿数
#define ENCODER_GEAR 			26													// 编码器齿轮齿数
#define DIAMETER_WHEEL 		50													// 车轮直径(mm)

#define EncoderPeriod  	 	500   											// 基于OMRON 型号为E6A2-CW3C的500线 AB双向编码器（对其进行四倍频）
#define ENCODER_RESOLUTION	(4*EncoderPeriod)					// 4倍频,同时使用CH1,CH2
#define prd     ENCODER_RESOLUTION										// 编码器旋转一个圈的脉冲数
#define Vbreak  60*ENCODER_RESOLUTION/10							// 基于OMRON 型号为E6A2-CW3C的最高响应频率下的速度为3600r/min = 60r/s = 6r/0.1s  12000脉冲/周期(100ms)

typedef enum {UN_Ready = 0, Ready = !UN_Ready} Get_Ready_Flag;

extern float V_motor_speed;
extern float R_motor_speed;
extern float R_encoder_speed;

typedef struct
{
	__IO s16 V3;											 		  // 当前编码器的脉冲增量（本次编码器总脉冲数 - 上一次编码器总脉冲数）
	__IO s16 cnt3;													// 当前编码器的脉冲计数值
	__IO s16 rcnt3;										  		// 当前编码器的旋转圈数
	__IO s32 CNT3;													// 当前编码器的总脉冲数
}EncoderType;

void Get_Encoder(void);
void Speed_Measurement(u8 TIMx);

#endif 

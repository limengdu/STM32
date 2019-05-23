/*-------------------------------------------------------------------------------
�ļ����ƣ�encoder.h
�ļ���������������ع��ܺ���������
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __ENCODER_H
#define	__ENCODER_H

#include "stm32f10x.h"

#define PI 3.141592653589793

#define WHEEL_GEAR 				76 													// ���ֳ��ֳ���
#define ENCODER_GEAR 			26													// ���������ֳ���
#define DIAMETER_WHEEL 		50													// ����ֱ��(mm)

#define EncoderPeriod  	 	500   											// ����OMRON �ͺ�ΪE6A2-CW3C��500�� AB˫�����������������ı�Ƶ��
#define ENCODER_RESOLUTION	(4*EncoderPeriod)					// 4��Ƶ,ͬʱʹ��CH1,CH2
#define prd     ENCODER_RESOLUTION										// ��������תһ��Ȧ��������
#define Vbreak  60*ENCODER_RESOLUTION/10							// ����OMRON �ͺ�ΪE6A2-CW3C�������ӦƵ���µ��ٶ�Ϊ3600r/min = 60r/s = 6r/0.1s  12000����/����(100ms)

typedef enum {UN_Ready = 0, Ready = !UN_Ready} Get_Ready_Flag;

extern float V_motor_speed;
extern float R_motor_speed;
extern float R_encoder_speed;

typedef struct
{
	__IO s16 V3;											 		  // ��ǰ���������������������α������������� - ��һ�α���������������
	__IO s16 cnt3;													// ��ǰ���������������ֵ
	__IO s16 rcnt3;										  		// ��ǰ����������תȦ��
	__IO s32 CNT3;													// ��ǰ����������������
}EncoderType;

void Get_Encoder(void);
void Speed_Measurement(u8 TIMx);

#endif 

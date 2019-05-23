/*-------------------------------------------------------------------------------
�ļ����ƣ�pid.h
�ļ�������PID�������ͷ�ļ�
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"

typedef struct
{
  __IO int32_t  SetPoint;                                 // �趨Ŀ�� Desired Value
  __IO float    SumError;                                 // ����ۼ�
  __IO float    Proportion;                               // �������� Proportional Const
  __IO float    Integral;                                 // ���ֳ��� Integral Const
  __IO float    Derivative;                               // ΢�ֳ��� Derivative Const
  __IO int      LastError;                                // Error[-1]
  __IO int      PrevError;                                // Error[-2]
}PID_TypeDef;

/*************************************/
// ����PID��غ�
// �����������趨�Ե������Ӱ��ǳ���
// PID����������ʱ��ϢϢ���
/*************************************/
#define  SPD_P_DATA      0.3f       										  // P����
#define  SPD_I_DATA      0.1f        											// I����
#define  SPD_D_DATA      0.1f        											// D����

#define  TARGET_SPEED    100.0f       										// Ŀ���ٶ�   

/* ˽�б��� ------------------------------------------------------------------*/
//__IO int32_t Spd_Pulse;            											  // ����������ֵ Pulse
//__IO int32_t LastSpd_Pulse;          											// ��һ�α���������ֵ Pulse
//__IO int32_t Spd_PPS;                											// �ٶ�ֵ Pulse/Sample
//__IO float Spd_RPM;                  											// �ٶ�ֵ r/m

void PID_ParamInit(void) ;
//int32_t ABS_SpdPIDCalc(float NextPoint);
int32_t INC_SpdPIDCalc(float NextPoint);

#endif

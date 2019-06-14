/*-------------------------------------------------------------------------------
�ļ����ƣ�pid.c
�ļ�������PID������صĹ��ܺ���
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "pid.h"

/* PID�ṹ�� */
PID_TypeDef  sPID;               													// PID�����ṹ��

/*-------------------------------------------------------------------------------
�������ƣ�PID_ParamInit
����������PID������ʼ��
�����������
���ز�������
��    ע��
---------------------------------------------------------------------------------*/
void PID_ParamInit(void)
{
    sPID.LastError 	= 0;               														// Error[-1]
    sPID.PrevError  = 0;              														// Error[-2]
    sPID.Proportion = SPD_P_DATA; 																// �������� Proportional Const
    sPID.Integral 	= SPD_I_DATA;   															// ���ֳ��� Integral Const
    sPID.Derivative = SPD_D_DATA; 																// ΢�ֳ��� Derivative Const
    sPID.SetPoint 	= TARGET_SPEED;     													// �趨Ŀ�� Desired Value
}

/*-------------------------------------------------------------------------------
�������ƣ�INC_SpdPIDCalc
����������λ��ʽ�ٶȻ�PID�������
�����������ǰ������
���ز�����Ŀ�������
��    ע��
---------------------------------------------------------------------------------*/
//int32_t ABS_SpdPIDCalc(float LastPoint)
//{
//  float iError,dError;
//  iError = sPID.SetPoint - LastPoint; 														// ƫ��

//  if((iError<0.2f )&& (iError>-0.2f))
//    iError = 0.0f;

//  sPID.SumError += iError; 																				// ����
////  /* �趨�������� */
////  if(sPID.SumError >= (TARGET_SPEED*30.0f))
////     sPID.SumError  = (TARGET_SPEED*30.0f);
////  if(sPID.SumError <= -(TARGET_SPEED*30.0f))
////    sPID.SumError = -(TARGET_SPEED*30.0f);

//  dError = iError - sPID.LastError; 															// ΢��
//  sPID.LastError = iError;
//  return (int32_t)(sPID.Proportion * iError 											// ������
//  + sPID.Integral * (float)sPID.SumError 													// ������
//  + sPID.Derivative * dError);																	  // ΢����
//}

/*-------------------------------------------------------------------------------
�������ƣ�ABS_SpdPIDCalc
��������������ʽ�ٶȻ�PID�������
�����������ǰ������
���ز�����Ŀ�������
��    ע��
---------------------------------------------------------------------------------*/
int32_t INC_SpdPIDCalc(float ActualPoint)
{
  float iError,iIncpid;
  iError = (float)sPID.SetPoint - ActualPoint; 										// ƫ��

  if((iError<0.2f )&& (iError>-0.2f))
    iError = 0.0f;

  iIncpid=(sPID.Proportion * iError)                 							// E[k]��
              -(sPID.Integral * sPID.LastError)              			// E[k-1]��
              +(sPID.Derivative * sPID.PrevError);  							// E[k-2]��

  sPID.PrevError = sPID.LastError;                    						// �洢�������´μ���
  sPID.LastError = iError;
  return(iIncpid);                                    						// ��������ֵ
}

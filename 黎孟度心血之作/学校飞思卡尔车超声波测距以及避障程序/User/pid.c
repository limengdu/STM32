/*-------------------------------------------------------------------------------
文件名称：pid.c
文件描述：PID控制相关的功能函数
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#include "pid.h"

/* PID结构体 */
PID_TypeDef  sPID;               													// PID参数结构体

/*-------------------------------------------------------------------------------
函数名称：PID_ParamInit
函数描述：PID参数初始化
输入参数：无
返回参数：无
备    注：
---------------------------------------------------------------------------------*/
void PID_ParamInit(void)
{
    sPID.LastError 	= 0;               														// Error[-1]
    sPID.PrevError  = 0;              														// Error[-2]
    sPID.Proportion = SPD_P_DATA; 																// 比例常数 Proportional Const
    sPID.Integral 	= SPD_I_DATA;   															// 积分常数 Integral Const
    sPID.Derivative = SPD_D_DATA; 																// 微分常数 Derivative Const
    sPID.SetPoint 	= TARGET_SPEED;     													// 设定目标 Desired Value
}

/*-------------------------------------------------------------------------------
函数名称：INC_SpdPIDCalc
函数描述：位置式速度环PID控制设计
输入参数：当前控制量
返回参数：目标控制量
备    注：
---------------------------------------------------------------------------------*/
//int32_t ABS_SpdPIDCalc(float LastPoint)
//{
//  float iError,dError;
//  iError = sPID.SetPoint - LastPoint; 														// 偏差

//  if((iError<0.2f )&& (iError>-0.2f))
//    iError = 0.0f;

//  sPID.SumError += iError; 																				// 积分
////  /* 设定积分上限 */
////  if(sPID.SumError >= (TARGET_SPEED*30.0f))
////     sPID.SumError  = (TARGET_SPEED*30.0f);
////  if(sPID.SumError <= -(TARGET_SPEED*30.0f))
////    sPID.SumError = -(TARGET_SPEED*30.0f);

//  dError = iError - sPID.LastError; 															// 微分
//  sPID.LastError = iError;
//  return (int32_t)(sPID.Proportion * iError 											// 比例项
//  + sPID.Integral * (float)sPID.SumError 													// 积分项
//  + sPID.Derivative * dError);																	  // 微分项
//}

/*-------------------------------------------------------------------------------
函数名称：ABS_SpdPIDCalc
函数描述：增量式速度环PID控制设计
输入参数：当前控制量
返回参数：目标控制量
备    注：
---------------------------------------------------------------------------------*/
int32_t INC_SpdPIDCalc(float ActualPoint)
{
  float iError,iIncpid;
  iError = (float)sPID.SetPoint - ActualPoint; 										// 偏差

  if((iError<0.2f )&& (iError>-0.2f))
    iError = 0.0f;

  iIncpid=(sPID.Proportion * iError)                 							// E[k]项
              -(sPID.Integral * sPID.LastError)              			// E[k-1]项
              +(sPID.Derivative * sPID.PrevError);  							// E[k-2]项

  sPID.PrevError = sPID.LastError;                    						// 存储误差，用于下次计算
  sPID.LastError = iError;
  return(iIncpid);                                    						// 返回增量值
}

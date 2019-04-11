#include "pid.h"

void IncPID_Init(void)   //PID参数初始化
{
	sptr->SumError = 0;
	sptr->LastError = 0;  //Error[-1]
	sptr->PrevError = 0;  //Error[-2]
	sptr->Proportion = 0; //比例常数 Proportional Const
	sptr->Integral = 0;   //积分常数Integral Const
	sptr->Derivative = 0; //微分常数 Derivative Const
	sptr->SetPoint = 0;
}

//增量式PID控制设计
int IncPIDCalc(int NextPoint)
{
	register int iError, iIncpid;
	//当前误差
	iError = sptr->SetPoint - NextPoint;
	//增量计算
	iIncpid = sptr->Proportion * iError //E[k]项
	          - sptr->Integral * sptr->LastError //E[k－1]项
	          + sptr->Derivative * sptr->PrevError; //E[k－2]项
	//存储误差，用于下次计算
	sptr->PrevError = sptr->LastError;
	sptr->LastError = iError;
	//返回增量值
	return(iIncpid);
}


//位置式PID控制设计
unsigned int LocPIDCalc(int NextPoint)
{
	register int iError,dError;
	iError = sptr->SetPoint - NextPoint; //偏差
	sptr->SumError += iError; //积分
	dError = iError - sptr->LastError; //微分
	sptr->LastError = iError;
	
	return(sptr->Proportion * iError //比例项
	       + sptr->Integral * sptr->SumError //积分项
	       + sptr->Derivative * dError); //微分项
}








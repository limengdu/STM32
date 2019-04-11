#ifndef PID_H
#define PID_H

#include "stm32f10x.h"

typedef struct PID   //数据结构
{
	int SetPoint;      //设定目标 Desired Value
	long SumError;     //误差累计
	double Proportion; //比例常数 Proportional Const
	double Integral;   //积分常数 Integral Const
	double Derivative; //微分常数 Derivative Const
	int LastError;     //Error[-1]
	int PrevError;     //Error[-2]
}PID;

static PID sPID;
static PID *sptr = &sPID;


void IncPID_Init(void);
int IncPIDCalc(int NextPoint);
unsigned int LocPIDCalc(int NextPoint);

#endif


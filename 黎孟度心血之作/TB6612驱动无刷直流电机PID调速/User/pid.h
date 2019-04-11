#ifndef PID_H
#define PID_H

#include "stm32f10x.h"

typedef struct PID   //���ݽṹ
{
	int SetPoint;      //�趨Ŀ�� Desired Value
	long SumError;     //����ۼ�
	double Proportion; //�������� Proportional Const
	double Integral;   //���ֳ��� Integral Const
	double Derivative; //΢�ֳ��� Derivative Const
	int LastError;     //Error[-1]
	int PrevError;     //Error[-2]
}PID;

static PID sPID;
static PID *sptr = &sPID;


void IncPID_Init(void);
int IncPIDCalc(int NextPoint);
unsigned int LocPIDCalc(int NextPoint);

#endif


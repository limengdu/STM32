#include "pid.h"

void IncPID_Init(void)   //PID������ʼ��
{
	sptr->SumError = 0;
	sptr->LastError = 0;  //Error[-1]
	sptr->PrevError = 0;  //Error[-2]
	sptr->Proportion = 0; //�������� Proportional Const
	sptr->Integral = 0;   //���ֳ���Integral Const
	sptr->Derivative = 0; //΢�ֳ��� Derivative Const
	sptr->SetPoint = 0;
}

//����ʽPID�������
int IncPIDCalc(int NextPoint)
{
	register int iError, iIncpid;
	//��ǰ���
	iError = sptr->SetPoint - NextPoint;
	//��������
	iIncpid = sptr->Proportion * iError //E[k]��
	          - sptr->Integral * sptr->LastError //E[k��1]��
	          + sptr->Derivative * sptr->PrevError; //E[k��2]��
	//�洢�������´μ���
	sptr->PrevError = sptr->LastError;
	sptr->LastError = iError;
	//��������ֵ
	return(iIncpid);
}


//λ��ʽPID�������
unsigned int LocPIDCalc(int NextPoint)
{
	register int iError,dError;
	iError = sptr->SetPoint - NextPoint; //ƫ��
	sptr->SumError += iError; //����
	dError = iError - sptr->LastError; //΢��
	sptr->LastError = iError;
	
	return(sptr->Proportion * iError //������
	       + sptr->Integral * sptr->SumError //������
	       + sptr->Derivative * dError); //΢����
}








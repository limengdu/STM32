#ifndef PID_H
#define PID_H

//ʹ����һ��PID���ڶ�Ӧ��PID�㷨�á�1��
#define EN_IncPIDCalc  1        //����ʽPID
#define EN_LocPIDCalc  0        //λ��ʽPID

#if EN_LocPIDCalc   //λ��ʽPID�㷨ʹ��������ѡ��
int LocPIDCalc_PID1 (int Encoder,int Target);
int LocPIDCalc_PID2 (int Encoder,int Target);
#endif

#if EN_IncPIDCalc   //����ʽPID�㷨ʹ��������ѡ��
int IncPIDCalc_PID1 (int Encoder,int Target);
int IncPIDCalc_PID2 (int Encoder,int Target);
#endif

#endif

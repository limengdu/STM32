#ifndef PID_H
#define PID_H

//ʹ����һ��PID���ڶ�Ӧ��PID�㷨�á�1��
#define EN_IncPIDCalc  0        //����ʽPID
#define EN_LocPIDCalc  1        //λ��ʽPID

int LocPIDCalc_PID (int Encoder,int Target);


#endif


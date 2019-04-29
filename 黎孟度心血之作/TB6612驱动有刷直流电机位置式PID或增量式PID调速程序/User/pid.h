#ifndef PID_H
#define PID_H

//使用哪一种PID则在对应的PID算法置“1”
#define EN_IncPIDCalc  1        //增量式PID
#define EN_LocPIDCalc  0        //位置式PID

#if EN_LocPIDCalc   //位置式PID算法使用与屏蔽选择
int LocPIDCalc_PID1 (int Encoder,int Target);
int LocPIDCalc_PID2 (int Encoder,int Target);
#endif

#if EN_IncPIDCalc   //增量式PID算法使用与屏蔽选择
int IncPIDCalc_PID1 (int Encoder,int Target);
int IncPIDCalc_PID2 (int Encoder,int Target);
#endif

#endif

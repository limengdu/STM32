#ifndef PID_H
#define PID_H

//使用哪一种PID则在对应的PID算法置“1”
#define EN_IncPIDCalc  0        //增量式PID
#define EN_LocPIDCalc  1        //位置式PID

int LocPIDCalc_PID (int Encoder,int Target);


#endif


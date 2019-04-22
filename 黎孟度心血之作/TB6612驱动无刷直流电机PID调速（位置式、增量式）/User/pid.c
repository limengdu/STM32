#include "pid.h"
#include "stm32f10x.h"

/*******************************************************************************
* 函 数 名         : MOTOR_CONTROL
* 函数功能		   : 位置式PI控制器
* 输    入         : 编码器测量位置信息，目标位置
* 输    出         : 电机PWM
* 说    明         ：
根据位置式离散PID公式 
pwm = Kp*e(k) + Ki*∑e(k) + Kd[e(k)-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,……,k;
pwm代表输出

*                             黎孟度心血之作                                   *
*******************************************************************************/
int LocPIDCalc_PID (int Encoder,int Target)
{ 	
	 float Kp=10.0,Ki=10.0,Kd=100.0,EX_Bias=0.0;	
	 static int Bias,Pwm,Integral_bias,Differential_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Integral_bias+=Bias;	             //求出偏差的积分
	 Differential_bias=Bias-EX_Bias;     //求出偏差的微分
	 Pwm=Kp*Bias+Ki*Integral_bias+Kd*Differential_bias;       //位置式PI控制器
	 EX_Bias=Bias;                       //记录前一次偏差
	 return Pwm;                         //增量输出
}







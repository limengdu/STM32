/* Includes ------------------------------------------------------------------*/
#include "pid.h"

/*******************************************************************************
* 函 数 名         : LocPIDCalc_PID1
* 函数功能		   : 位置式PID控制器/位置式PI控制器
* 输    入         : 编码器测量速度信息，目标速度
* 输    出         : 电机PWMA
* 说    明         ：
*根据位置式离散PID公式 
pwm = Kp*e(k) + Ki*∑e(k) + Kd[e(k)-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,……,k;
pwm代表输出
*由于不同的电机的Kp、Ki和Kd的值也不尽相同，所以有多少个电机就需要多少个PID算法
*对于普通电机，PI算法就已经够用，因此这里提供PID算法以及PI算法供用户选择使用

*                             黎孟度心血之作                                   *
*******************************************************************************/
int LocPIDCalc_PID1 (int Encoder,int Target)
{ 	
	 //位置式PID算法
	 static float Kp=10.0 , Ki=17.0 , Kd=5.0 , EX_Bias=0.0;	
	 static int Bias,Pwm,Integral_bias,Differential_bias;
	 Bias = Encoder - Target;                //计算偏差Bias
	 Integral_bias += Bias;	                 //求出偏差的积分Integral_bias
	 Differential_bias = Bias - EX_Bias;     //求出偏差的微分Differential_bias
	 Pwm = Kp*Bias + Ki*Integral_bias + Kd*Differential_bias;//位置式PID控制器
	 EX_Bias = Bias;                         //记录前一次偏差EX_Bias
	 return Pwm;                             //输出PWM
	
	 //位置式PI算法
//	 float Kp=10 , Ki=17;	
//	 static int Bias,Pwm,Integral_bias;
//	 Bias = Encoder - Target;                //计算偏差Bias
//	 Integral_bias += Bias;	                 //求出偏差的积分Integral_bias
//	 Pwm = Kp*Bias + Ki*Integral_bias;       //位置式PI控制器
//	 return Pwm;                             //输出PWM
}


/*******************************************************************************
* 函 数 名         : LocPIDCalc_PID2
* 函数功能		   : 位置式PID控制器/位置式PI控制器
* 输    入         : 编码器测量速度信息，目标速度
* 输    出         : 电机PWMB
* 说    明         ：
*根据位置式离散PID公式 
pwm = Kp*e(k) + Ki*∑e(k) + Kd[e(k)-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,……,k;
pwm代表输出
*由于不同的电机的Kp、Ki和Kd的值也不尽相同，所以有多少个电机就需要多少个PID算法
*对于普通电机，PI算法就已经够用，因此这里提供PID算法以及PI算法供用户选择使用

*                             黎孟度心血之作                                   *
*******************************************************************************/
int LocPIDCalc_PID2 (int Encoder,int Target)
{ 	
	 //位置式PID算法
	 static float Kp=10.0 , Ki=17.0 , Kd=5.0 , EX_Bias=0.0;	
	 static int Bias,Pwm,Integral_bias,Differential_bias;
	 Bias = Encoder - Target;                //计算偏差Bias
	 Integral_bias += Bias;	                 //求出偏差的积分Integral_bias
	 Differential_bias = Bias - EX_Bias;     //求出偏差的微分Differential_bias
	 Pwm = Kp*Bias + Ki*Integral_bias + Kd*Differential_bias;//位置式PID控制器
	 EX_Bias = Bias;                         //记录前一次偏差EX_Bias
	 return Pwm;                             //输出PWM
	
	 //位置式PI算法
//	 float Kp=10 , Ki=17;	
//	 static int Bias,Pwm,Integral_bias;
//	 Bias = Encoder - Target;                //计算偏差Bias
//	 Integral_bias += Bias;	                 //求出偏差的积分Integral_bias
//	 Pwm = Kp*Bias + Ki*Integral_bias;       //位置式PI控制器
//	 return Pwm;                             //输出PWM
}

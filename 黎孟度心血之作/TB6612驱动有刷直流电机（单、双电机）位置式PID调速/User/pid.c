#include "pid.h"

int LocPIDCalc_PID1 (int Encoder,int Target)
{ 	
//	 static float Kp=10.0 , Ki=17.0 , Kd=5.0 , EX_Bias=0.0;	
//	 static int Bias,Pwm,Integral_bias,Differential_bias;
//	 Bias = Target - Encoder;                //计算偏差
//	 Integral_bias += Bias;	             //求出偏差的积分
//	 Differential_bias = Bias - EX_Bias;     //求出偏差的微分
//	 Pwm = Kp*Bias + Ki*Integral_bias + Kd*Differential_bias;//位置式PI控制器
//	 EX_Bias = Bias;                       //记录前一次偏差
//	 return Pwm;                         //增量输出
	
	 float Kp=10,Ki=17;	
	 static int Bias,Pwm,Integral_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Integral_bias+=Bias;	               //求出偏差的积分
	 Pwm=Kp*Bias+Ki*Integral_bias;       //位置式PI控制器
	 return Pwm;                         //增量输出
}


int LocPIDCalc_PID2 (int Encoder,int Target)
{ 	
	 static float Kp=10.0 , Ki=17.0 , Kd=5.0 , EX_Bias=0.0;	
	 static int Bias,Pwm,Integral_bias=0,Differential_bias;
	 Bias=Encoder-Target;              //计算偏差
	 Integral_bias += Bias;	             //求出偏差的积分
	 Differential_bias = Bias - EX_Bias;     //求出偏差的微分
	 Pwm = Kp*Bias + Ki*Integral_bias + Kd*Differential_bias;//位置式PI控制器
	 EX_Bias=Bias;                       //记录前一次偏差
	 return Pwm;                         //增量输出
	
//	 float Kp=10,Ki=17;	
//	 static int Bias,Pwm,Integral_bias;
//	 Bias=Encoder-Target;                //计算偏差
//	 Integral_bias+=Bias;	               //求出偏差的积分
//	 Pwm=Kp*Bias+Ki*Integral_bias;       //位置式PI控制器
//	 return Pwm;                         //增量输出
}

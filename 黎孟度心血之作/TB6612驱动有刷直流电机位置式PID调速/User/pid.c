/* Includes ------------------------------------------------------------------*/
#include "pid.h"

/*******************************************************************************
* �� �� ��         : LocPIDCalc_PID1
* ��������		   : λ��ʽPID������/λ��ʽPI������
* ��    ��         : �����������ٶ���Ϣ��Ŀ���ٶ�
* ��    ��         : ���PWMA
* ˵    ��         ��
*����λ��ʽ��ɢPID��ʽ 
pwm = Kp*e(k) + Ki*��e(k) + Kd[e(k)-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,����,k;
pwm�������
*���ڲ�ͬ�ĵ����Kp��Ki��Kd��ֵҲ������ͬ�������ж��ٸ��������Ҫ���ٸ�PID�㷨
*������ͨ�����PI�㷨���Ѿ����ã���������ṩPID�㷨�Լ�PI�㷨���û�ѡ��ʹ��

*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
int LocPIDCalc_PID1 (int Encoder,int Target)
{ 	
	 //λ��ʽPID�㷨
	 static float Kp=10.0 , Ki=17.0 , Kd=5.0 , EX_Bias=0.0;	
	 static int Bias,Pwm,Integral_bias,Differential_bias;
	 Bias = Encoder - Target;                //����ƫ��Bias
	 Integral_bias += Bias;	                 //���ƫ��Ļ���Integral_bias
	 Differential_bias = Bias - EX_Bias;     //���ƫ���΢��Differential_bias
	 Pwm = Kp*Bias + Ki*Integral_bias + Kd*Differential_bias;//λ��ʽPID������
	 EX_Bias = Bias;                         //��¼ǰһ��ƫ��EX_Bias
	 return Pwm;                             //���PWM
	
	 //λ��ʽPI�㷨
//	 float Kp=10 , Ki=17;	
//	 static int Bias,Pwm,Integral_bias;
//	 Bias = Encoder - Target;                //����ƫ��Bias
//	 Integral_bias += Bias;	                 //���ƫ��Ļ���Integral_bias
//	 Pwm = Kp*Bias + Ki*Integral_bias;       //λ��ʽPI������
//	 return Pwm;                             //���PWM
}


/*******************************************************************************
* �� �� ��         : LocPIDCalc_PID2
* ��������		   : λ��ʽPID������/λ��ʽPI������
* ��    ��         : �����������ٶ���Ϣ��Ŀ���ٶ�
* ��    ��         : ���PWMB
* ˵    ��         ��
*����λ��ʽ��ɢPID��ʽ 
pwm = Kp*e(k) + Ki*��e(k) + Kd[e(k)-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,����,k;
pwm�������
*���ڲ�ͬ�ĵ����Kp��Ki��Kd��ֵҲ������ͬ�������ж��ٸ��������Ҫ���ٸ�PID�㷨
*������ͨ�����PI�㷨���Ѿ����ã���������ṩPID�㷨�Լ�PI�㷨���û�ѡ��ʹ��

*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
int LocPIDCalc_PID2 (int Encoder,int Target)
{ 	
	 //λ��ʽPID�㷨
	 static float Kp=10.0 , Ki=17.0 , Kd=5.0 , EX_Bias=0.0;	
	 static int Bias,Pwm,Integral_bias,Differential_bias;
	 Bias = Encoder - Target;                //����ƫ��Bias
	 Integral_bias += Bias;	                 //���ƫ��Ļ���Integral_bias
	 Differential_bias = Bias - EX_Bias;     //���ƫ���΢��Differential_bias
	 Pwm = Kp*Bias + Ki*Integral_bias + Kd*Differential_bias;//λ��ʽPID������
	 EX_Bias = Bias;                         //��¼ǰһ��ƫ��EX_Bias
	 return Pwm;                             //���PWM
	
	 //λ��ʽPI�㷨
//	 float Kp=10 , Ki=17;	
//	 static int Bias,Pwm,Integral_bias;
//	 Bias = Encoder - Target;                //����ƫ��Bias
//	 Integral_bias += Bias;	                 //���ƫ��Ļ���Integral_bias
//	 Pwm = Kp*Bias + Ki*Integral_bias;       //λ��ʽPI������
//	 return Pwm;                             //���PWM
}

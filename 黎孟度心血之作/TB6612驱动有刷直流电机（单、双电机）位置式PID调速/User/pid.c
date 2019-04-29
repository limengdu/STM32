#include "pid.h"

int LocPIDCalc_PID1 (int Encoder,int Target)
{ 	
//	 static float Kp=10.0 , Ki=17.0 , Kd=5.0 , EX_Bias=0.0;	
//	 static int Bias,Pwm,Integral_bias,Differential_bias;
//	 Bias = Target - Encoder;                //����ƫ��
//	 Integral_bias += Bias;	             //���ƫ��Ļ���
//	 Differential_bias = Bias - EX_Bias;     //���ƫ���΢��
//	 Pwm = Kp*Bias + Ki*Integral_bias + Kd*Differential_bias;//λ��ʽPI������
//	 EX_Bias = Bias;                       //��¼ǰһ��ƫ��
//	 return Pwm;                         //�������
	
	 float Kp=10,Ki=17;	
	 static int Bias,Pwm,Integral_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Integral_bias+=Bias;	               //���ƫ��Ļ���
	 Pwm=Kp*Bias+Ki*Integral_bias;       //λ��ʽPI������
	 return Pwm;                         //�������
}


int LocPIDCalc_PID2 (int Encoder,int Target)
{ 	
	 static float Kp=10.0 , Ki=17.0 , Kd=5.0 , EX_Bias=0.0;	
	 static int Bias,Pwm,Integral_bias=0,Differential_bias;
	 Bias=Encoder-Target;              //����ƫ��
	 Integral_bias += Bias;	             //���ƫ��Ļ���
	 Differential_bias = Bias - EX_Bias;     //���ƫ���΢��
	 Pwm = Kp*Bias + Ki*Integral_bias + Kd*Differential_bias;//λ��ʽPI������
	 EX_Bias=Bias;                       //��¼ǰһ��ƫ��
	 return Pwm;                         //�������
	
//	 float Kp=10,Ki=17;	
//	 static int Bias,Pwm,Integral_bias;
//	 Bias=Encoder-Target;                //����ƫ��
//	 Integral_bias+=Bias;	               //���ƫ��Ļ���
//	 Pwm=Kp*Bias+Ki*Integral_bias;       //λ��ʽPI������
//	 return Pwm;                         //�������
}

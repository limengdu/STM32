/* Includes ------------------------------------------------------------------*/
#include "pid.h"


#if EN_LocPIDCalc   //λ��ʽPID�㷨ʹ��������ѡ��
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
#endif


#if EN_IncPIDCalc   //����ʽPID�㷨ʹ��������ѡ��
/*******************************************************************************
* �� �� ��         : IncPIDCalc_PID1
* ��������		   : ����ʽPID������/����ʽPI������
* ��    ��         : �����������ٶ���Ϣ��Ŀ���ٶ�
* ��    ��         : ���PWMA
* ˵    ��         ��
*��������ʽ��ɢPID��ʽ 
pwm += Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
*���ڲ�ͬ�ĵ����Kp��Ki��Kd��ֵҲ������ͬ�������ж��ٸ��������Ҫ���ٸ�PID�㷨
*������ͨ�����PI�㷨���Ѿ����ã���������ṩPID�㷨�Լ�PI�㷨���û�ѡ��ʹ��

*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
int IncPIDCalc_PID1 (int Encoder,int Target)
{ 	
     //����ʽPID�㷨
	 float Kp=10 , Ki=10 , Kd=3;	
	 static int Bias,Pwm,Last_bias1,Last_bias2;
	 Bias = Encoder - Target;                //����ƫ��Bias
	 Pwm += Kp*(Bias-Last_bias1) + Ki*Bias + Kd*(Bias-2*Last_bias1+Last_bias2);//����ʽPID������
	 Last_bias2 = Last_bias1;                //��������һ��ƫ��Last_bias2
	 Last_bias1 = Bias;	                     //������һ��ƫ��Last_bias1
	 return Pwm;                             //�������
	
	 //����ʽPI�㷨
//   float Kp=10 , Ki=10;	
//	 static int Bias,Pwm,Last_bias;
//	 Bias = Encoder - Target;                //����ƫ��Bias
//	 Pwm += Kp*(Bias-Last_bias) + Ki*Bias;   //����ʽPI������
//	 Last_bias = Bias;	                     //������һ��ƫ��Last_bias
//	 return Pwm;                             //�������
}


/*******************************************************************************
* �� �� ��         : IncPIDCalc_PID2
* ��������		   : ����ʽPID������/����ʽPI������
* ��    ��         : �����������ٶ���Ϣ��Ŀ���ٶ�
* ��    ��         : ���PWMB
* ˵    ��         ��
*��������ʽ��ɢPID��ʽ 
pwm += Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
*���ڲ�ͬ�ĵ����Kp��Ki��Kd��ֵҲ������ͬ�������ж��ٸ��������Ҫ���ٸ�PID�㷨
*������ͨ�����PI�㷨���Ѿ����ã���������ṩPID�㷨�Լ�PI�㷨���û�ѡ��ʹ��

*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
int IncPIDCalc_PID2 (int Encoder,int Target)
{ 	     
     //����ʽPID�㷨
	 float Kp=10 , Ki=10 , Kd=3;	
	 static int Bias,Pwm,Last_bias1,Last_bias2;
	 Bias = Encoder - Target;                //����ƫ��Bias
	 Pwm += Kp*(Bias-Last_bias1) + Ki*Bias + Kd*(Bias-2*Last_bias1+Last_bias2);//����ʽPID������
	 Last_bias2 = Last_bias1;                //��������һ��ƫ��Last_bias2
	 Last_bias1 = Bias;	                     //������һ��ƫ��Last_bias1
	 return Pwm;                             //�������
	
	 //����ʽPI�㷨
//   float Kp=10 , Ki=10;	
//	 static int Bias,Pwm,Last_bias;
//	 Bias = Encoder - Target;                //����ƫ��Bias
//	 Pwm += Kp*(Bias-Last_bias) + Ki*Bias;   //����ʽPI������
//	 Last_bias = Bias;	                     //������һ��ƫ��Last_bias
//	 return Pwm;                             //�������
}

#endif


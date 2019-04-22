#include "pid.h"
#include "stm32f10x.h"

/*******************************************************************************
* �� �� ��         : MOTOR_CONTROL
* ��������		   : λ��ʽPI������
* ��    ��         : ����������λ����Ϣ��Ŀ��λ��
* ��    ��         : ���PWM
* ˵    ��         ��
����λ��ʽ��ɢPID��ʽ 
pwm = Kp*e(k) + Ki*��e(k) + Kd[e(k)-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,����,k;
pwm�������

*                             ���϶���Ѫ֮��                                   *
*******************************************************************************/
int LocPIDCalc_PID (int Encoder,int Target)
{ 	
	 float Kp=10.0,Ki=10.0,Kd=100.0,EX_Bias=0.0;	
	 static int Bias,Pwm,Integral_bias,Differential_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Integral_bias+=Bias;	             //���ƫ��Ļ���
	 Differential_bias=Bias-EX_Bias;     //���ƫ���΢��
	 Pwm=Kp*Bias+Ki*Integral_bias+Kd*Differential_bias;       //λ��ʽPI������
	 EX_Bias=Bias;                       //��¼ǰһ��ƫ��
	 return Pwm;                         //�������
}







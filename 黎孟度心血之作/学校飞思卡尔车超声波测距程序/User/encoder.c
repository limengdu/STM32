/*-------------------------------------------------------------------------------
�ļ����ƣ�encoder.c
�ļ���������������ع��ܺ�����
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#include "task_scheduler.h"
#include "tim.h"
//#include "pid.h"

EncoderType GetEncoder;
float R_motor_speed;
float V_motor_speed;
float R_encoder_speed;
extern __IO int32_t Spd_PPS;

/*-------------------------------------------------------------------------------
�������ƣ�Get_Encoder
������������ȡ���������ݹ��ܺ���
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void Get_Encoder(void)
{
  s32 CNT3_temp, CNT3_last;
 
  GetEncoder.cnt3 = TIM3 -> CNT;																			// ��ȡ��������������
  CNT3_last 			= GetEncoder.CNT3;						
  CNT3_temp 			= GetEncoder.rcnt3 * prd + GetEncoder.cnt3; 				// ������������ prd=EncoderPeriod
  GetEncoder.V3 	= CNT3_temp - CNT3_last;														// ������������
  	
	while (GetEncoder.V3 > Vbreak)				 															// ��ֹ���������ӦƵ���µ�ת��(3600r/min)
  {							      
		GetEncoder.rcnt3--;					      
		CNT3_temp = GetEncoder.rcnt3 * prd + GetEncoder.cnt3;
		GetEncoder.V3 = CNT3_temp - CNT3_last;		 
  }							     
  while (GetEncoder.V3 < -Vbreak)			   															// ��ֹ���������ӦƵ���µ�ת��(3600r/min)
  {							      
		GetEncoder.rcnt3++;					      
		CNT3_temp = GetEncoder.rcnt3 * prd + GetEncoder.cnt3;
		GetEncoder.V3 = CNT3_temp - CNT3_last;		 
  }
  GetEncoder.CNT3 = CNT3_temp;																				// ���汾�α���������������
	
	/* PID */
	Spd_PPS = GetEncoder.V3;
}

/*-------------------------------------------------------------------------------
�������ƣ�Speed_Measurement
������������λʱ���ȡ������������ת������ʵ�ֵĲ��ٹ��ܺ���
�����������ʱ�����
���ز�������
��    ע��V = w*r =  2*PI*r*n;
				  ���ٶ� = ���ٶ� * �뾶 = 2 * Բ���� * �뾶 * ת��;
---------------------------------------------------------------------------------*/
void Speed_Measurement(u8 TIMx)
{  
   switch(TIMx)
	 {
		 case 3:  Get_Encoder();
						  R_encoder_speed = (float)GetEncoder.V3/ENCODER_RESOLUTION *10;							// ��ת�٣����� ����ֵ/s����Ϊ�����ʱ�䵥λ����ʱ�䣨100ms/�Σ�������100ms/�� * 10 = 1s/��
							R_motor_speed = (float)R_encoder_speed/(WHEEL_GEAR/ENCODER_GEAR);						// ��ת�٣����� r/s���������ÿ���Ȧ��
							V_motor_speed = (float)R_motor_speed * (PI * DIAMETER_WHEEL);								// �����ٶȣ����� mm/s���������ÿ�����ƶ��ľ���ֵ
							break;	
		 
		 default: break;
	 }
	 	 
//	/* �����ٶ�λ��(Ȧ��r) */
//	printf("���벶��ֵ��%d  ", GetEncoder.cnt3);																																	// �����ǰ����ֵ
//	printf("������Ȧ����%.3f r  ", (float)((float)GetEncoder.CNT3/ENCODER_RESOLUTION));														// ���ʵ�ʱ�������ת��Ȧ��
//	printf("����Ȧ����%.3f r  ", (float)((float)GetEncoder.CNT3/ENCODER_RESOLUTION*ENCODER_GEAR/WHEEL_GEAR));			// ���ʵ�ʳ�����ת��Ȧ�� 
//	/* �ٶȵ�λ��r/s */
//	printf("��������ת�ٶȣ�%.3f r/s  ", R_encoder_speed);																												// ���ʵ�ʱ�������ת���ٶ�
//	printf("���٣�%.3f mm/s  \r\n", V_motor_speed);																																// ���ʵ�ʳ���
}

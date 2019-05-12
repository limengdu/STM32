/*-------------------------------------------------------------------------------
文件名称：encoder.c
文件描述：编码器相关功能函数。
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
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
函数名称：Get_Encoder
函数描述：获取编码器数据功能函数
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Get_Encoder(void)
{
  s32 CNT3_temp, CNT3_last;
 
  GetEncoder.cnt3 = TIM3 -> CNT;																			// 获取编码器计数读数
  CNT3_last 			= GetEncoder.CNT3;						
  CNT3_temp 			= GetEncoder.rcnt3 * prd + GetEncoder.cnt3; 				// 计算总脉冲数 prd=EncoderPeriod
  GetEncoder.V3 	= CNT3_temp - CNT3_last;														// 计算脉冲增量
  	
	while (GetEncoder.V3 > Vbreak)				 															// 防止超出最高响应频率下的转速(3600r/min)
  {							      
		GetEncoder.rcnt3--;					      
		CNT3_temp = GetEncoder.rcnt3 * prd + GetEncoder.cnt3;
		GetEncoder.V3 = CNT3_temp - CNT3_last;		 
  }							     
  while (GetEncoder.V3 < -Vbreak)			   															// 防止超出最高响应频率下的转速(3600r/min)
  {							      
		GetEncoder.rcnt3++;					      
		CNT3_temp = GetEncoder.rcnt3 * prd + GetEncoder.cnt3;
		GetEncoder.V3 = CNT3_temp - CNT3_last;		 
  }
  GetEncoder.CNT3 = CNT3_temp;																				// 保存本次编码器的总脉冲数
	
	/* PID */
	Spd_PPS = GetEncoder.V3;
}

/*-------------------------------------------------------------------------------
函数名称：Speed_Measurement
函数描述：单位时间读取编码器计数并转换，所实现的测速功能函数
输入参数：定时器编号
返回参数：无
备    注：V = w*r =  2*PI*r*n;
				  线速度 = 角速度 * 半径 = 2 * 圆周率 * 半径 * 转速;
---------------------------------------------------------------------------------*/
void Speed_Measurement(u8 TIMx)
{  
   switch(TIMx)
	 {
		 case 3:  Get_Encoder();
						  R_encoder_speed = (float)GetEncoder.V3/ENCODER_RESOLUTION *10;							// （转速）量纲 脉冲值/s，因为这里的时间单位捕获时间（100ms/次），所以100ms/次 * 10 = 1s/次
							R_motor_speed = (float)R_encoder_speed/(WHEEL_GEAR/ENCODER_GEAR);						// （转速）量纲 r/s，求出车轮每秒的圈数
							V_motor_speed = (float)R_motor_speed * (PI * DIAMETER_WHEEL);								// （线速度）量纲 mm/s，求出车轮每秒所移动的距离值
							break;	
		 
		 default: break;
	 }
	 	 
//	/* 计算速度位置(圈数r) */
//	printf("输入捕获值：%d  ", GetEncoder.cnt3);																																	// 输出当前捕获值
//	printf("编码器圈数：%.3f r  ", (float)((float)GetEncoder.CNT3/ENCODER_RESOLUTION));														// 输出实际编码器旋转的圈数
//	printf("车轮圈数：%.3f r  ", (float)((float)GetEncoder.CNT3/ENCODER_RESOLUTION*ENCODER_GEAR/WHEEL_GEAR));			// 输出实际车轮旋转的圈数 
//	/* 速度单位是r/s */
//	printf("编码器旋转速度：%.3f r/s  ", R_encoder_speed);																												// 输出实际编码器旋转的速度
//	printf("车速：%.3f mm/s  \r\n", V_motor_speed);																																// 输出实际车速
}

#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H	 
#include "sys.h"
#include "delay.h"


#define STEP_MOTOR_PORT	GPIOB	//定义IO接口所在组
#define STEP_MOTOR_A	GPIO_Pin_3	//定义IO接口
#define STEP_MOTOR_B	GPIO_Pin_4	//定义IO接口
#define STEP_MOTOR_C	GPIO_Pin_8	//定义IO接口
#define STEP_MOTOR_D	GPIO_Pin_9	//定义IO接口



void STEP_MOTOR_Init(void);//初始化
void STEP_MOTOR_OFF (void);//断电状态
void STEP_MOTOR_4S (u8 speed);//固定位置（制动）
void STEP_MOTOR_4R (u8 speed);
void STEP_MOTOR_4L (u8 speed);
void STEP_MOTOR_8R (u8 speed);
void STEP_MOTOR_8L (u8 speed);


		 				    
#endif

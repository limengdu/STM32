/**
  ******************************************************************************
  * @file    Cloud_control.c
  * @author Liang Yuhao
  * @version V1.0
  * @date    
  * @brief   云台控制函数接口
  ******************************************************************************
  */
  
  
#include "Cloud_control.h"

Cloud_t Cloud;
/**
  * @brief  设置M6623电机电流值（id号为5,6），M2006电机电流值（id 7）
  * @param  iqyaw 	对应yaw轴电机的电流值，范围-5000~0~5000
  *			iqpitch	对应pitch轴电机的电流值，范围-5000~0~5000
  *			iq7，拨弹电机电流值，范围-10000~0~10000
  * @retval None
  */
void Cloud_setCurrent(int16_t iqyaw, int16_t iqpitch, int16_t iq7, int16_t iq8){

	uint8_t data[8];
	
	//数据格式详见说明书P32
	data[0] = iqyaw >> 8;
	data[1] = iqyaw;
	data[2] = iqpitch >> 8;
	data[3] = iqpitch;
	data[4] = iq7 >> 8;
	data[5] = iq7;
	data[6] = iq8 >> 8;
	data[7] = iq8;
	
	CAN_SendData(CAN1, CAN_ID_STD, 0x1FF, data);
	
}	



/**
  * @brief  云台初始化，配置参数并归位云台
  * @param  None
  * @retval None
  */
void Cloud_Init(void){
	
	Cloud.LpfAttFactor = 0.05f;
	Cloud.targetYawRaw = Cloud.targetYawLPF = M6623s[0].totalAngle;
	Cloud.targetPitchRaw = Cloud.targetPitchLPF = M6623s[1].totalAngle;
	
  Shoot_Init();
	//云台pitch轴电机pid
	PositionPID_paraReset(&M6623s[1].pid_speed, -10.0f, 1.0f, -12.0f, 4000, 100);
	PositionPID_paraReset(&M6623s[1].pid_angle, 1.5f, 1.0f, 0.0f, 500, 0);
	//云台yaw轴电机pid
	PositionPID_paraReset(&M6623s[0].pid_speed, -15.0f, 20.0f, 0.0f, 4000, 800);
	PositionPID_paraReset(&M6623s[0].pid_angle, 2.0f, 1.0f, 1.0f, 500, 0);
	M6623_setTargetAngle(M6623_YAW, Cloud.targetYawRaw);
	M6623_setTargetAngle(M6623_PITCH, Cloud.targetPitchRaw);
	
	//云台方向闭环
	Cloud.IMUtargetYawRaw = Cloud.IMUtargetYawLPF = Cloud_IMU.totalYaw;
	Cloud.IMUtargetPitchRaw = Cloud.IMUtargetPitchLPF = Cloud_IMU.eular.pitch;

//	PositionPID_paraReset(&Cloud.YawAttitude_pid, -1.5f, 0.0f, 0.0f, 500, 0);
//	PositionPID_paraReset(&Cloud.YawSpeed_pid, -80.0f, 0.0f, -60.0f, 4000, 0);
	PositionPID_paraReset(&Cloud.YawAttitude_pid, -0.9f, 0.0f, -0.5f, 500, 500);
	PositionPID_paraReset(&Cloud.YawSpeed_pid, -60.0f, -0.6f, -5.0f, 4000, 500);
	//Pitch
	PositionPID_paraReset(&Cloud.RollAttitude_pid, -2.0f, 0.0f, 0.0f, 500, 0);
	PositionPID_paraReset(&Cloud.RollSpeed_pid, -60.0f, 0.0f, -40.0f, 4000, 0);
 	PositionPID_paraReset(&Chassis.FollowYawAttitude_pid, 3.5f, 0.0f, 15.0f, 4500, 500);
	//拨盘初始化
//	IncrementalPID_paraReset(&M2006s[0].pid_speed, 1.8f, 0.18f, 0.0f, 6000, 2000);
//	PositionPID_paraReset(&M2006s[0].pid_angle, 0.3f, 0.0f, 0.8f, 2000, 500);
	//摩擦轮初始化
//  TIM12_PWMOutput(89, 19999,1000);
}	



/**
  * @brief  强制设置云台IMU坐标（绕过缓冲）
  * @param[in]  posYaw
  *				posPitch
  * @retval None
  */
void Cloud_setIMUPosForced(float posYaw, float posPitch){
	Cloud.IMUtargetYawLPF = Cloud.IMUtargetYawRaw = posYaw;
	Cloud.IMUtargetPitchLPF = Cloud.IMUtargetPitchRaw = posPitch;
}

/**
  * @brief  获取云台Yaw旋转角度（以右为0点）右负左正
  * @param[in]  None
  * @retval 角度
  */
float Cloud_getYawAngleWithRight(void){
	return (M6623s[0].totalAngle - Cloud_Yaw_Min)/22.75f;
}

/**
  * @brief  获取云台Pitch旋转角度（以下为0点）下负上正
  * @param[in]  None
  * @retval 角度
  */
float Cloud_getPitchAngleWithDown(void){
	return (M6623s[1].totalAngle - Cloud_Pitch_Min)/22.75f;
}

/**
  * @brief  获取云台Yaw旋转角度（以中心为0点）
  * @param[in]  None
  * @retval 角度
  */
float Cloud_getYawAngleWithCenter(void){
	return (M6623s[0].totalAngle - Cloud_Yaw_Center)/22.75f;
}

/**
  * @brief  强制设置云台机械坐标（绕过缓冲区）
  * @param[in]  posYaw
  *				posPitch
  * @retval None
  */
void Cloud_setAbsPosForced(float posYaw, float posPitch){
	Cloud.targetYawLPF = Cloud.targetYawRaw = posYaw;
	Cloud.targetPitchLPF = Cloud.targetPitchRaw = posPitch;
}

/**
  * @brief  云台控制处理
  * @param[in]  delta_yaw		航向角变化量
  *				delta_pitch		俯仰角变化量
  *				shoot	射击使能
  *				mode	模式 - 除Status_ControlOFF外，其他正常控制
  * @retval None
  */
void Cloud_processing(float delta_yaw, float delta_pitch, uint8_t mode){

	Cloud_setIMUPosForced(Cloud_IMU.totalYaw, Cloud_IMU.eular.roll);
	
	if(mode == ControlMode_OFF||  Cloud_IMU.offLineFlag){
		Cloud_setAbsPosForced(M6623s[0].totalAngle, M6623s[1].totalAngle);
		Cloud_setCurrent(0, 0, 0, 0);
		return;
	}
	
	if(dr16_data.offLineFlag){
		delta_yaw = delta_pitch = 0.0f;
		fric_turnOff();
	}
	
		Cloud.targetYawRaw -= delta_yaw;
	  Cloud.targetPitchRaw -= delta_pitch;
	
	//云台限幅begin
	if(Cloud.targetYawRaw > Cloud_Yaw_Max){
		Cloud.targetYawRaw = Cloud_Yaw_Max;
	}
	if(Cloud.targetYawRaw < Cloud_Yaw_Min){
		Cloud.targetYawRaw = Cloud_Yaw_Min;
	}
	if(Cloud.targetPitchRaw > Cloud_Pitch_Max){
		Cloud.targetPitchRaw = Cloud_Pitch_Max;
	}
	if(Cloud.targetPitchRaw < Cloud_Pitch_Min) {
		Cloud.targetPitchRaw = Cloud_Pitch_Min;
	}
	//云台限幅end
	
	//平滑处理begin
	Filter_IIRLPF(&Cloud.targetYawRaw, &Cloud.targetYawLPF, Cloud.LpfAttFactor);
	Filter_IIRLPF(&Cloud.targetPitchRaw, &Cloud.targetPitchLPF, Cloud.LpfAttFactor);
	//平滑处理end
	
	M6623_setTargetAngle(M6623_YAW, Cloud.targetYawLPF);
	M6623_setTargetAngle(M6623_PITCH, Cloud.targetPitchLPF);
	
	Shoot_processing();
	
	/*************PID计算****************/
		//YAW轴PID
		float M6623s_YawOPIDOut = Position_PID(&M6623s[0].pid_angle, M6623s[0].targetAngle, M6623s[0].totalAngle);
		//速度PID计算(内环)
		M6623s[0].outCurrent = Position_PID(&M6623s[0].pid_speed, M6623s_YawOPIDOut, Cloud_IMU.gyro.z);
		//清标志位
		M6623s[0].infoUpdateFlag = 0;
		
		//角度PID计算(外环)
		//PITCH轴PID
		int M6623s_PIDOut = Position_PID(&M6623s[1].pid_angle, M6623s[1].targetAngle, M6623s[1].totalAngle);
		//速度PID计算(内环)
		M6623s[1].outCurrent = Position_PID(&M6623s[1].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.y);
		//清标志位
		M6623s[1].infoUpdateFlag = 0;				
	
		//设定电机电流值
		Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, M2006s[0].outCurrent, 0);
	
}




/**
  * @brief  云台控制处理-带IMU模式
  * @param[in]  delta_yaw		航向角变化量
  *				delta_pitch		俯仰角变化量
  *				shoot	射击使能
  *				mode	模式 - 除Status_ControlOFF外，其他正常控制
  * @retval None
  */
void Cloud_processing_WithIMU(float delta_yaw, float delta_pitch, uint8_t mode){
    
	  Cloud.targetYawLPF = Cloud.targetYawRaw = M6623s[0].totalAngle;

		if(mode == ControlMode_OFF || Cloud_IMU.offLineFlag){
		//以当前位置为下次启动位置，防炸
		Cloud_setIMUPosForced(Cloud_IMU.totalYaw, Cloud_IMU.eular.roll);
		Cloud.targetPitchLPF = Cloud.targetPitchRaw = M6623s[1].totalAngle;
		Cloud_setCurrent(0, 0, 0, 0);
		return;
	  }
		
		if(dr16_data.offLineFlag){
		delta_yaw = delta_pitch = 0.0f;
		fric_turnOff();
	}
		
/*************传入增加量****************/
		Cloud.IMUtargetYawRaw += delta_yaw/30.0f;
	  Cloud.targetPitchRaw -= delta_pitch;

		Cloud_IMU.infoUpdateFlag = 0;

/*************左右上下限幅****************/

		//计算云台IMU最大角度(右)
		Cloud.IMUYawAngleMax = Cloud_IMU.totalYaw + Cloud_getYawAngleWithRight();
		//计算云台IMU最小角度(左)
		Cloud.IMUYawAngleMin = Cloud_IMU.totalYaw - (M6623_AngleToDEG(Cloud_Yaw_delta) - Cloud_getYawAngleWithRight());
		//计算云台IMU最大角度(下)
		Cloud.IMUPitchAngleMax = Cloud_IMU.eular.roll + Cloud_getPitchAngleWithDown();
		//计算云台IMU最小角度(上)
		Cloud.IMUPitchAngleMin = Cloud_IMU.eular.roll - (M6623_AngleToDEG(Cloud_Pitch_delta) - Cloud_getPitchAngleWithDown());
	
/*************云台限幅begin****************/

		if(Cloud_IMU.totalYaw > Cloud.IMUYawAngleMax){
			if(delta_yaw < 0.0f){
				Cloud.IMUtargetYawRaw += delta_yaw/30.0f;
			}
			else{
				Cloud.IMUtargetYawRaw = Cloud.IMUYawAngleMax;
			}
		}
		else if(Cloud_IMU.totalYaw < Cloud.IMUYawAngleMin){
			if(delta_yaw > 0.0f){
				Cloud.IMUtargetYawRaw += delta_yaw/30.0f;
			}
			else{
				Cloud.IMUtargetYawRaw = Cloud.IMUYawAngleMin;
			}
		}
/*************云台限幅end****************/
		
/*************平滑处理****************/
		Filter_IIRLPF(&Cloud.IMUtargetYawRaw, &Cloud.IMUtargetYawLPF, 0.4);
		Filter_IIRLPF(&Cloud.targetPitchRaw, &Cloud.targetPitchLPF, 0.1);
		
		M6623_setTargetAngle(M6623_PITCH, Cloud.targetPitchLPF);

			Shoot_processing();
		
/*************PID计算****************/
		//YAW轴PID
		float M6623s_YawOPIDOut = Position_PID(&Cloud.YawAttitude_pid, Cloud.IMUtargetYawLPF, Cloud_IMU.totalYaw);
		//速度PID计算(内环)
		M6623s[0].outCurrent = Position_PID(&Cloud.YawSpeed_pid, M6623s_YawOPIDOut, Cloud_IMU.gyro.z);
		//清标志位
		M6623s[0].infoUpdateFlag = 0;
		
		//角度PID计算(外环)
		//PITCH轴PID
		int M6623s_PIDOut = Position_PID(&M6623s[1].pid_angle, M6623s[1].targetAngle, M6623s[1].totalAngle);
		//速度PID计算(内环)
		M6623s[1].outCurrent = Position_PID(&M6623s[1].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.y);
		//清标志位
		M6623s[1].infoUpdateFlag = 0;
		
    Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, M2006s[0].outCurrent, 0);

}





/********************************************************************单独拨盘控制部分*******************************************************************************/

///**
//  * @brief  底盘初始化，配置参数
//  * @param  None
//  * @retval None
//  */
//void Bullet_Init(void){
//	
//	IncrementalPID_paraReset(&M2006s[0].pid_speed, 1.8f, 0.18f, 0.0f, 6000, 2000);
//	PositionPID_paraReset(&M2006s[0].pid_angle, 0.3f, 0.0f, 0.8f, 2000, 500);

//}	


//void Bullet_processing(float Bullet_Speed){

//	float Temp_Bullet_Speed;
//	
//  Temp_Bullet_Speed = Bullet_Speed;
//	
//	M2006s[0].outCurrent = Incremental_PID(&M2006s[0].pid_speed, Temp_Bullet_Speed, M2006s[0].realSpeed);
//	
//	Cloud_setCurrent(0, 0, M2006s[0].outCurrent, 0);
//	
//}


//void Bullet_pulling(uint8_t Temp_shoot){

//	if(Temp_shoot && M2006s[0].loadFinish){
//		M2006s[0].addAngle += M2006_LOADANGLE;
//	}

//	if(M2006s[0].infoUpdateFlag == 1){
//	static uint8_t M2006s_blocking = 0;
//	M2006s[0].loadFinish = 0;

//	//角度PID计算(外环)
//	int M2006s_PIDOut = Position_PID(&M2006s[0].pid_angle, M2006s[0].addAngle, M2006s[0].realAngle + (8192*M2006s[0].turnCount));
//	//速度PID计算(内环)
//	M2006s[0].outCurrent = Incremental_PID(&M2006s[0].pid_speed, M2006s_PIDOut, M2006s[0].realSpeed);
//	
//	//卡弹处理
//	if(abs(M2006s[0].outCurrent)>5500){
//		if(!M2006s_blocking){
//			//卡弹后反转到原来位置
//			M2006s[0].addAngle -= M2006_LOADANGLE*2;
//			M2006s_blocking = 1;
//		}
//	}
//	
//	//拨弹完毕判断
//	if(abs(M2006s[0].pid_angle.err)<600 && M2006s[0].realSpeed == 0){
//		M2006s[0].loadFinish = 1;
//		M2006s_blocking = 0;
//	}
//	//清零防炸
//	if(M2006s[0].turnCount>100){
//		M2006s[0].addAngle -= (8192*M2006s[0].turnCount);
//		M2006s[0].turnCount = 0;

//	}

//	
//	//清标志位
//	M2006s[0].infoUpdateFlag = 0;
//}
///*************M2006_END****************/

////设定电机电流值
//Cloud_setCurrent(0, 0, M2006s[0].outCurrent, 0);
//	
//}

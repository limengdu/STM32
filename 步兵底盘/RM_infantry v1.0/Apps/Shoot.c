/**
  ******************************************************************************
  * @file    Shoot.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   弹丸发♂射控制函数接口
  ******************************************************************************
  */
  
  
#include "Shoot.h"

shootGun_t Gun;

TIM_SetComparex_f *const TIM_SetComparex[4] = {
	TIM_SetCompare1,
	TIM_SetCompare2,
	TIM_SetCompare3,
	TIM_SetCompare4
};


const uint16_t FricSpeed[3] = { 1600, 2000, 2000, };		//不同射速摩擦轮转速

const uint16_t Shoot_Freq[4] = { 6,		//0级不存在的
								 6,
								 7,
								 8,};		//每级步兵射击频率
/**
  * @brief  射击参数初始化
  * @param[in]  None
  * @retval None
  */
void Shoot_Init(void){
	Gun.fricReady = 0;
	Gun.shootFlag = 0;
	Gun.heatOverflowFlag = 0;
	Gun.fricSpeedLevel = FricSpeedLevel_20MPS;
//	Gun.fricTargetSpeedRaw = FricSpeed[FricSpeedLevel_20MPS];
	Gun.fricTargetSpeedRaw =1400;

	//摩擦轮90M/90/20000=50HZ
	TIM12_PWMOutput(89, 19999,1000);
  
	
	//拨弹电机pid
	PositionPID_paraReset(&M2006s[0].pid_speed, 1.5f, 0.04f, 0.0f, 8000, 2000);
	PositionPID_paraReset(&M2006s[0].pid_angle, 0.3f, 0.0f, 0.8f, 4000, 500);
	
}

/**
  * @brief  开摩擦轮
  * @param[in]  None
  * @retval None
  */
void fric_turnOn(void){
	static uint16_t Count = 1000;
	fricMotor_setSpeed(Count);
	Count += 15;
	if(Count > Gun.fricTargetSpeedRaw){
		fricMotor_setSpeed(Gun.fricTargetSpeedRaw);
		Count = 1000;
		Gun.fricReady = 1;
		Gun.shootFlag = 0;
	}
}


/**
  * @brief  关摩擦轮
  * @param[in]  None
  * @retval None
  */
void fric_turnOff(void){
	fricMotor_setSpeed(1000);
	Gun.fricReady = 0;
	Gun.shootFlag = 0;
}

/**
  * @brief  设置摩擦轮电机速度
  * @param  speed 	电机速度，范围1000~2000
  * @retval None
  */
void fricMotor_setSpeed(uint16_t speed){
	if(speed < FRICMOTOR_SPEEDMIN) speed = FRICMOTOR_SPEEDMIN;
	if(speed > FRICMOTOR_SPEEDMAX) speed = FRICMOTOR_SPEEDMAX;
	
	TIM_SetComparex[0](TIM12, speed);
	TIM_SetComparex[1](TIM12, speed);
	
}	


//int test = 0;

void Shoot_processing(void){
	 static uint16_t freqCounter = 0;
	 if(ControlStatus.ControlMode == ControlMode_OFF /*|| M2006*/){
		//以当前位置为下次启动位置，防炸
		M2006s[0].turnCount = 0;
		M2006s[0].targetAngle = M2006s[0].totalAngle = M2006s[0].realAngle;
		return;
	}
	 
	 Gun.shootFreq=Shoot_Freq[1] ;
	 
	 if(freqCounter++ > 100/Gun.shootFreq){
		 Gun.shootReady = 1;
		 freqCounter = 0;
	 }
	 
	 //有请求拨弹且拨弹电机到位
	if(Gun.shootFlag && M2006s[0].loadFinish){
		if(!Gun.fricReady){
			//摩擦轮没启动则启动
			fric_turnOn();
		}
		else{
			fricMotor_setSpeed(Gun.fricTargetSpeedRaw);
			if(Gun.shootReady ){
				//没超热量则拨弹射击
				M2006s[0].targetAngle += M2006_LOADANGLE;
				freqCounter = 0;
				Gun.shootReady = 0;
			}
			Gun.shootFlag = 0;
		}
	}
	
	/*************M2006_BEGIN****************/
	if(M2006s[0].infoUpdateFlag){
		static uint8_t M2006s_blocking = 0;
		M2006s[0].loadFinish = 0;

		//角度PID计算(外环)
		int M2006s_PIDOut = Position_PID(&M2006s[0].pid_angle, M2006s[0].targetAngle, M2006s[0].totalAngle);
		//速度PID计算(内环)
		M2006s[0].outCurrent = Position_PID(&M2006s[0].pid_speed, M2006s_PIDOut, M2006s[0].realSpeed);
		static int blockCounter = 0;
		//卡弹处理
		if(abs(M2006s[0].outCurrent)>6200 && abs(M2006s[0].realSpeed) < 50 && blockCounter++>50){
			if(!M2006s_blocking){
				//卡弹后反转到原来位置
				M2006s[0].targetAngle -= M2006_LOADANGLE*2;
				M2006s_blocking = 1;
			}
		}
		
		//拨弹完毕判断
		if(abs(M2006s[0].pid_angle.err) < 8000 /*&& abs(M2006s[0].realSpeed) < 220*/){
			M2006s[0].loadFinish = 1;
			M2006s_blocking = 0;
			blockCounter = 0;
		}
		//清零防炸
		if(abs(M2006s[0].turnCount) > 100){
			M2006s[0].targetAngle -= (8192*M2006s[0].turnCount);
			M2006s[0].turnCount = 0;
		}

		
		//清标志位
		M2006s[0].infoUpdateFlag = 0;
	}
	/*************M2006_END****************/
	
}


#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <stdbool.h>
#include <stdint.h>

#pragma anon_unions

/* ������ */
typedef struct {
		float x;                 //������X�᷽������
		float y;                 //������Y�᷽������
		float z;                 //������Z�᷽������
}Vector_t;

typedef struct {
	float Roll;                 //ROLL�᷽��
	float Pitch;                //PITCH�᷽��
	float Yaw;                  //YAW�᷽��
}Eular_t;

typedef struct{
	Vector_t Gyro;               //����������          
	Eular_t  EularDate;          //ŷ��������     
	float lastYaw;               //��һ��YAW������    
	float totalYaw;
	int16_t ImuTurnCount;
	uint8_t ImuDevStatus;
	uint8_t ImuInfoUpdateFlag;
	uint16_t ImuInfoUpdateFrame;
	uint8_t ImuOffLineFlag;
}GY_IMU_t;

/* PID���� */
typedef struct{
	float Target; 			        //�趨Ŀ��ֵ
	float Measured; 				    //����ֵ
	float err; 						      //����ƫ��ֵ
	float err_last; 				    //��һ��ƫ��
	float err_beforeLast; 			//���ϴ�ƫ��
	float Kp, Ki, Kd;				    //Kp, Ki, Kd����ϵ��
	float pwm; 						      //pwm���
	uint32_t MaxOutput;				  //����޷�
  uint32_t IntegralLimit;			//�����޷� 
}incrementalpid_t;

typedef struct{
	float Target; 					    //�趨Ŀ��ֵ
	float Measured; 				    //����ֵ
	float err; 						      //����ƫ��ֵ
	float err_last; 				    //��һ��ƫ��
	float integral_err; 			  //����ƫ��֮��
	float Kp, Ki, Kd;				    //Kp, Ki, Kd����ϵ��
	float pwm; 						      //pwm���
	uint32_t MaxOutput;				  //����޷�
  uint32_t IntegralLimit;			//�����޷� 
}positionpid_t;


/* ���̵�� */
typedef struct{
	uint16_t realAngle;			    //�������Ļ�е�Ƕ�
	int16_t  realSpeed;			    //���������ٶ�
	int16_t  realCurrent;		    //��������ʵ�ʵ���
	uint8_t  temperture;        //�������ĵ���¶�
	int16_t  targetCurrent;			//Ŀ�����
	int16_t  targetSpeed;			  //Ŀ���ٶ�
	uint16_t targetAngle;			  //Ŀ��Ƕ�
	int16_t  outCurrent;				//�������
	incrementalpid_t pid;		    //���pid
	uint8_t  M3508InfoUpdateFlag;		  //��Ϣ��ȡ���±�־
	uint16_t M3508InfoUpdateFrame;	  //֡��
	uint8_t  M3508OffLineFlag;		    //�豸���߱�־
}M3508s_t;


/* �����˶� */
typedef struct{
	float targetXRaw;		//����x��ԭʼ����
	float targetYRaw;		//����y��ԭʼ����
	float targetZRaw;		//����z��ԭʼ����
	float LpfAttFactor;		//�����˲�ϵ��
	float targetXLPF;		//����x���˲�������
	float targetYLPF;		//����y���˲�������
	float targetZLPF;		//����z���˲�������
	float speedLimit;		//�����ٶ�����
	float FollowtargetYawRaw;	//����Ŀ��Yaw�������̨ԭʼ����
	float FollowtargetYawLPF;	//����Yaw�������̨�˲�������
	positionpid_t FollowYawAttitude_pid;		//����Yaw�������̨pid
	uint8_t mode;								//���̿���ģʽ
	uint8_t swingFlag;							//Ť����־λ
	float swingSpeed;					//Ť���ٶ�
	uint8_t PowerOverflowFlag;					//�����ʱ�־λ
}Chassis_t;


/* ң�� */
typedef struct {
	struct{
		int16_t ch0;
		int16_t ch1;
		int16_t ch2;
		int16_t ch3;
		uint8_t s_left;
		uint8_t s_right;
	}rc;
	
	struct{
		int16_t x;
		int16_t y;
		int16_t z;
	
		uint8_t keyLeft;
		uint8_t keyRight;
		
	}mouse;
	
	union {
		uint16_t key_code;
		struct{
			bool press_W:1;
			bool press_S:1;
			bool press_A:1;
			bool press_D:1;
			bool press_Shift:1;
			bool press_Ctrl:1;
			bool press_Q:1;
			bool press_E:1;
			
			bool press_R:1;
			bool press_F:1;
			bool press_G:1;
			bool press_Z:1;
			bool press_X:1;
			bool press_C:1;
			bool press_V:1;
			bool press_B:1;
		};
	}keyBoard;
	
	uint16_t DR16InfoUpdateFrame;	//֡��
	uint8_t DR16OffLineFlag;		//�豸���߱�־
}DR16_DBUS_DATA_t;


typedef enum{
	ControlMode_ByRC = 3,
	ControlMode_ByPC = 1,
	ControlMode_OFF = 2,
}ControlMode_e;

typedef enum{
	ControlMode_Mid = 3,
	ControlMode_High = 1,
	ControlMode_Low = 2,
}Mode_e;

typedef enum{
	SpecialMode_Normal = 0,
	SpecialMode_BigSymbol = 2,	//���ģʽ
	SpecialMode_UPBridge = 3,	//����ģʽ
	SpecialMode_Supply = 4, 	//����վģʽ
}SpecialMode_t;

typedef struct{
	uint8_t ControlLeft;
	uint8_t ControlRight;			//����ģʽ
}ControlStatus_t;



typedef struct {
	float x;
	float y;
	float radian;
	float degrees;
	float distance;
}rocker_t;





typedef void TIM_SetComparex_f(TIM_TypeDef* TIMx, uint32_t Compare);


#endif /* __TYPEDEFS_H */

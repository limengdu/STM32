#include "user_code.h"

void Init(void){

	LED_GPIO_Config();             //LED����
  KEY_GPIO_Config();             //��������
	CAN1_QuickInit();              //CAN���ٳ�ʼ��
	DR16_receiverInit();           //ң��������������
  delay_ms(2000);                //��һ��
  Chassis_Init();                //�������̳�ʼ��
	USART2_QuickInit(9600);        //USART2��ʼ��������pc�˷��ͣ����յ�����Ϣ
	TIM6_CounterMode(89, 9999);    //��ʱ��TIM6��ʼ������֪�����������  

}


void Test(void){
	
//		ANO_Send_Data_V1(-M3508s[0].targetSpeed, -M3508s[0].realSpeed,M3508s[1].targetSpeed,M3508s[1].realSpeed);
//		ANO_Send_Data_V2(-M3508s[0].targetSpeed, -M3508s[0].realSpeed,M3508s[1].targetSpeed,M3508s[1].realSpeed);
//		ANO_Send_Data_V3(-M3508s[0].targetSpeed, -M3508s[0].realSpeed,M3508s[1].targetSpeed,M3508s[1].realSpeed);

}



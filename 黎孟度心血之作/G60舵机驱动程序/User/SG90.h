#ifndef __SG90_H
#define __SG90_H

/* Includes ------------------------------------------------------------------*/
#include "Sys.h"
#include "delay.h"

#define SE_PORT	GPIOA	    //����IO�ӿ�
#define SE_OUT	GPIO_Pin_4	//����IO�ӿ�

void SG90_Init(void);       //SG90�����ʼ��
void SG90_angle(u8 a);      //����Ƕ�����
		 				    
#endif

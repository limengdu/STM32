#ifndef __TIM_H_
#define __TIM_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"  

//�������IO���� 
/* 
FRONT_LEFT_F_PIN	PG13	��ǰǰ��IO
FRONT_LEFT_B_PIN	PG11	��ǰ����IO

FRONT_RIGHT_F_PIN	PC11	��ǰǰ��IO
FRONT_RIGHT_B_PIN	PD0	    ��ǰ����IO

BEHIND_LEFT_F_PIN	PD6	    ���ǰ��IO
BEHIND_LEFT_B_PIN	PG9	    ������IO

�Һ�������������IO�����Ϊ��·ʹ��EN1��EN2���ߵ�ƽ��Ч
BEHIND_RIGHT_F_PIN	PD4	    �ҵ��ʹ��IO
BEHIND_RIGHT_B_PIN	PD2	    ����ʹ��IO
 */
#define FRONT_LEFT_F_PIN    GPIO_Pin_13
#define FRONT_LEFT_F_GPIO   GPIOG
#define FRONT_LEFT_F_SET    GPIO_SetBits(FRONT_LEFT_F_GPIO , FRONT_LEFT_F_PIN)
#define FRONT_LEFT_F_RESET  GPIO_ResetBits(FRONT_LEFT_F_GPIO , FRONT_LEFT_F_PIN)

#define FRONT_LEFT_B_PIN    GPIO_Pin_11
#define FRONT_LEFT_B_GPIO   GPIOG
#define FRONT_LEFT_B_SET    GPIO_SetBits(FRONT_LEFT_B_GPIO , FRONT_LEFT_B_PIN)
#define FRONT_LEFT_B_RESET  GPIO_ResetBits(FRONT_LEFT_B_GPIO , FRONT_LEFT_B_PIN)

#define FRONT_RIGHT_F_PIN   GPIO_Pin_11
#define FRONT_RIGHT_F_GPIO  GPIOC
#define FRONT_RIGHT_F_SET   GPIO_SetBits(FRONT_RIGHT_F_GPIO , FRONT_RIGHT_F_PIN)
#define FRONT_RIGHT_F_RESET GPIO_ResetBits(FRONT_RIGHT_F_GPIO , FRONT_RIGHT_F_PIN)

#define FRONT_RIGHT_B_PIN   GPIO_Pin_0
#define FRONT_RIGHT_B_GPIO  GPIOD
#define FRONT_RIGHT_B_SET   GPIO_SetBits(FRONT_RIGHT_B_GPIO , FRONT_RIGHT_B_PIN)
#define FRONT_RIGHT_B_RESET GPIO_ResetBits(FRONT_RIGHT_B_GPIO , FRONT_RIGHT_B_PIN)

#define BEHIND_LEFT_F_PIN   GPIO_Pin_6
#define BEHIND_LEFT_F_GPIO  GPIOD
#define BEHIND_LEFT_F_SET   GPIO_SetBits(BEHIND_LEFT_F_GPIO , BEHIND_LEFT_F_PIN)
#define BEHIND_LEFT_F_RESET GPIO_ResetBits(BEHIND_LEFT_F_GPIO , BEHIND_LEFT_F_PIN)

#define BEHIND_LEFT_B_PIN   GPIO_Pin_9
#define BEHIND_LEFT_B_GPIO  GPIOG
#define BEHIND_LEFT_B_SET   GPIO_SetBits(BEHIND_LEFT_B_GPIO , BEHIND_LEFT_B_PIN)
#define BEHIND_LEFT_B_RESET GPIO_ResetBits(BEHIND_LEFT_B_GPIO , BEHIND_LEFT_B_PIN)

#define BEHIND_RIGHT_F_PIN  GPIO_Pin_4
#define BEHIND_RIGHT_F_GPIO GPIOD
#define BEHIND_RIGHT_F_SET  GPIO_SetBits(BEHIND_RIGHT_F_GPIO , BEHIND_RIGHT_F_PIN)
#define BEHIND_RIGHT_F_RESET GPIO_ResetBits(BEHIND_RIGHT_F_GPIO , BEHIND_RIGHT_F_PIN)

#define BEHIND_RIGHT_B_PIN  GPIO_Pin_2
#define BEHIND_RIGHT_B_GPIO GPIOD
#define BEHIND_RIGHT_B_SET  GPIO_SetBits(BEHIND_RIGHT_B_GPIO , BEHIND_RIGHT_B_PIN)
#define BEHIND_RIGHT_B_RESET GPIO_ResetBits(BEHIND_RIGHT_B_GPIO , BEHIND_RIGHT_B_PIN)


//����
/* 
�ٶ�������	FRONT_RIGHT_S_PIN	PA11
�ٶ�������	FRONT_LEFT_S_PIN	PA12
 */
#define FRONT_RIGHT_S_PIN  GPIO_Pin_11
#define FRONT_RIGHT_S_GPIO GPIOA
#define FRONT_RIGHT_S_IO GPIO_ReadInputDataBit(FRONT_RIGHT_S_GPIO, FRONT_RIGHT_S_PIN)

#define FRONT_LEFT_S_PIN  GPIO_Pin_12
#define FRONT_LEFT_S_GPIO GPIOA
#define FRONT_LEFT_S_IO GPIO_ReadInputDataBit(FRONT_LEFT_S_GPIO, FRONT_LEFT_S_PIN)

//��ǰ
#define FRONT_LEFT_GO      FRONT_LEFT_F_SET; FRONT_LEFT_B_RESET//ǰ��
#define FRONT_LEFT_BACK    FRONT_LEFT_F_RESET; FRONT_LEFT_B_SET//����
#define FRONT_LEFT_STOP    FRONT_LEFT_F_RESET; FRONT_LEFT_B_RESET//ֹͣ

//��ǰ
#define FRONT_RIGHT_GO     FRONT_RIGHT_F_SET;  FRONT_RIGHT_B_RESET
#define FRONT_RIGHT_BACK   FRONT_RIGHT_F_RESET;FRONT_RIGHT_B_SET
#define FRONT_RIGHT_STOP   FRONT_RIGHT_F_RESET;FRONT_RIGHT_B_RESET

//���
#define BEHIND_LEFT_GO     BEHIND_LEFT_F_SET;BEHIND_LEFT_B_RESET
#define BEHIND_LEFT_BACK   BEHIND_LEFT_F_RESET;BEHIND_LEFT_B_SET
#define BEHIND_LEFT_STOP   BEHIND_LEFT_F_RESET;BEHIND_LEFT_B_RESET

//�Һ�
#define BEHIND_RIGHT_GO    BEHIND_RIGHT_F_SET;BEHIND_RIGHT_B_RESET
#define BEHIND_RIGHT_BACK  BEHIND_RIGHT_F_RESET;BEHIND_RIGHT_B_SET
#define BEHIND_RIGHT_STOP  BEHIND_RIGHT_F_RESET;BEHIND_RIGHT_B_RESET

#define BEHIND_RIGHT_EN    BEHIND_RIGHT_F_SET;BEHIND_RIGHT_B_SET        
/*С�������������߸���һ����������������������ֻ��Ҫ�����ƣ�
�ұߵ��ֻ����ǰ���ƣ����ｫ�Һ������ƽŵ����ʹ��*/

#define SPEED_DUTY 25   //��ռ����ֵ,��ֵԽ��,�ٶ�Խ��,ֵ���ɳ���speed_count��ֵ

//ָ���
#define COMM_STOP  'I'             //ֹͣ
#define COMM_UP    'A'             //ǰ��
#define COMM_DOWN  'B'             //����
#define COMM_LEFT  'C'             //��ת
#define COMM_RIGHT 'D'             //��ת

extern unsigned char tick_5ms;     //5ms����������Ϊ�������Ļ�������
extern unsigned char tick_1ms;     //1ms����������Ϊ����Ļ���������
extern unsigned int speed_count;   //ռ�ձȼ�����

void IRIN_Configuration(void);
void TIM2_Init(void);
void GPIOCLK_Init(void);

#endif


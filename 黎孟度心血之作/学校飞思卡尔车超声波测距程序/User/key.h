/*-------------------------------------------------------------------------------
�ļ����ƣ�key.h
�ļ������������궨�壬������ع��ܺ���������    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define KEY2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define KEY3 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)

#define __key_1 	1
#define __key_2		2
#define __key_3		3

typedef enum {REL_SET = 0, UN_REL_SET = !REL_SET} KEY_RELEASE_Status;

void KEY_Init(void);
u8 KEY_Scan(void);

#endif

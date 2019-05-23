/*-------------------------------------------------------------------------------
�ļ����ƣ�show.h
�ļ�������OLED��ʾ����ʾ��ع��ܺ���������   
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __SHOW_H
#define __SHOW_H

#include "stm32f10x.h"
#include "oled.h"

void OLED_Show(void);
void OLED_Speed_Show(void);
#ifdef CCD_OLED
	void OLED_DrawPoint_Shu(u8 x,u8 y,u8 t);
	void OLED_Show_CCD(void);
#endif

#endif

/*-------------------------------------------------------------------------------
�ļ����ƣ�ccd.h
�ļ�����������CCDģ����غ꼰�书�ܺ���������    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __CCD_H
#define __CCD_H	

#include "sys.h"

#define TSL_CLK   PCout(1)   //CLK 
#define TSL_SI    PCout(2)   //SI  

void Dly_us(void);
void RD_TSL(void) ;   
void CCD_Init(void);
void Find_CCD_Middle(void);

#endif

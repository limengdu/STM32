/*-------------------------------------------------------------------------------
�ļ����ƣ�datascope_gui.h
�ļ��������������Խ�������ݴ��书�ܺ�����������   
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __DATASCOPE_GUI_H
#define __DATASCOPE_GUI_H

extern unsigned char DataScope_OutPut_Buffer[42];	   									// ������֡���ݻ�����

void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // дͨ��������������֡���ݻ�����
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // ����֡�������ɺ��� 

#endif 

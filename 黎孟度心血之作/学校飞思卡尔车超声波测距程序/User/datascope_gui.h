/*-------------------------------------------------------------------------------
文件名称：datascope_gui.h
文件描述：辅助调试界面的数据传输功能函数的声明。   
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __DATASCOPE_GUI_H
#define __DATASCOPE_GUI_H

extern unsigned char DataScope_OutPut_Buffer[42];	   									// 待发送帧数据缓存区

void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // 写通道数据至待发送帧数据缓存区
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // 发送帧数据生成函数 

#endif 

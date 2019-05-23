/*-------------------------------------------------------------------------------
文件名称：MemoryList.h
文件描述：内存表通信数据    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __MEMORYLIST_H
#define __MEMORYLIST_H

#include "stm32f10x.h"

#pragma	pack(1)																																				// 对齐方式为1字节，不能修改。

/* ------------------------- +> List Start <+ --------------------------------- */  	// 内存表起始描述符
typedef struct
{
	u8 __Data_Start;																																		// 数据帧头
	u8 __Cmd_Code;																																			// 控制指令
	u16 __Data_Length;																																	// 数据长度
 /*********************保留区参数，此处用于添加用户要求通讯的参数*******************/ 	
	char direction[10];																																	// 舵机方向控制（前、后、左、右）
 /*******************************************************************************/ 
	u8 __Parity_Code;																																		// 数据校验码（奇校验）
	u8 __Data_End;																																			// 数据帧尾
}MemoryList_STM32_Type;																													  		// 内存表类型，新建后根据该内存表对应的控制器而命名，例如：MemoryList_xxx_Type，此处xxx为控制器的名字
/* ------------------------- +> List  End  <+ --------------------------------- */  	// 内存表结束描述符

#pragma pack()																	 																			// 对齐方式为默认，不能修改。

#endif

//通信协议的一般格式：“帧头 + 命令码 + 长度 + 数据 + 校验 + 帧尾”
//0x55 + 0x00 + sizeof(data[x]) + data[x] + 奇校验 + 0xaa





































/*---------------------------------------------------------------------------------------------------------------------------------------------
aHR0cDovL25vdGUueW91ZGFvLmNvbS9ub3Rlc2hhcmU/aWQ9YzI2OTc4MGIzMWIxZDU0ZDEyMjg5OTQ2MzM1YzVhZTUmc3ViPTEwRUY5RDdDQjZDMDQwQjBBRDQ2RTg1NjZDQTc3QTM5
aHR0cDovL25vdGUueW91ZGFvLmNvbS9ub3Rlc2hhcmU/aWQ9NmUwNGFkOGIzN2UwM2RjNjViN2Y2OTQ0NjQ5MzVmZjU=
aHR0cDovL25vdGUueW91ZGFvLmNvbS9ub3Rlc2hhcmU/aWQ9NmQ0YmFlODYzNzljZmY2YWYxNTYzNTI4OWMzMmVkNTgmc3ViPUFBMThCNzA3NUY5NjQwNTRBREJGN0NDNTNGRDYwNzYw
aHR0cDovL25vdGUueW91ZGFvLmNvbS9ub3Rlc2hhcmU/aWQ9MmI1Njc2NTJiODFkNTVlYTZlYjBmYWE4MTI0NmQyYzQmc3ViPUM1QjVFRERDMzQ5QjRCQjFBOTdGNjBFMzc0MzE0NDFG
----------------------------------------------------------------------------------------------------------------------------------------------*/

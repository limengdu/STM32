/*-------------------------------------------------------------------------------
�ļ����ƣ�MemoryList.h
�ļ��������ڴ��ͨ������    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __MEMORYLIST_H
#define __MEMORYLIST_H

#include "stm32f10x.h"

#pragma	pack(1)																																				// ���뷽ʽΪ1�ֽڣ������޸ġ�

/* ------------------------- +> List Start <+ --------------------------------- */  	// �ڴ����ʼ������
typedef struct
{
	u8 __Data_Start;																																		// ����֡ͷ
	u8 __Cmd_Code;																																			// ����ָ��
	u16 __Data_Length;																																	// ���ݳ���
 /*********************�������������˴���������û�Ҫ��ͨѶ�Ĳ���*******************/ 	
	char direction[10];																																	// ���������ƣ�ǰ�������ң�
 /*******************************************************************************/ 
	u8 __Parity_Code;																																		// ����У���루��У�飩
	u8 __Data_End;																																			// ����֡β
}MemoryList_STM32_Type;																													  		// �ڴ�����ͣ��½�����ݸ��ڴ���Ӧ�Ŀ����������������磺MemoryList_xxx_Type���˴�xxxΪ������������
/* ------------------------- +> List  End  <+ --------------------------------- */  	// �ڴ�����������

#pragma pack()																	 																			// ���뷽ʽΪĬ�ϣ������޸ġ�

#endif

//ͨ��Э���һ���ʽ����֡ͷ + ������ + ���� + ���� + У�� + ֡β��
//0x55 + 0x00 + sizeof(data[x]) + data[x] + ��У�� + 0xaa





































/*---------------------------------------------------------------------------------------------------------------------------------------------
aHR0cDovL25vdGUueW91ZGFvLmNvbS9ub3Rlc2hhcmU/aWQ9YzI2OTc4MGIzMWIxZDU0ZDEyMjg5OTQ2MzM1YzVhZTUmc3ViPTEwRUY5RDdDQjZDMDQwQjBBRDQ2RTg1NjZDQTc3QTM5
aHR0cDovL25vdGUueW91ZGFvLmNvbS9ub3Rlc2hhcmU/aWQ9NmUwNGFkOGIzN2UwM2RjNjViN2Y2OTQ0NjQ5MzVmZjU=
aHR0cDovL25vdGUueW91ZGFvLmNvbS9ub3Rlc2hhcmU/aWQ9NmQ0YmFlODYzNzljZmY2YWYxNTYzNTI4OWMzMmVkNTgmc3ViPUFBMThCNzA3NUY5NjQwNTRBREJGN0NDNTNGRDYwNzYw
aHR0cDovL25vdGUueW91ZGFvLmNvbS9ub3Rlc2hhcmU/aWQ9MmI1Njc2NTJiODFkNTVlYTZlYjBmYWE4MTI0NmQyYzQmc3ViPUM1QjVFRERDMzQ5QjRCQjFBOTdGNjBFMzc0MzE0NDFG
----------------------------------------------------------------------------------------------------------------------------------------------*/

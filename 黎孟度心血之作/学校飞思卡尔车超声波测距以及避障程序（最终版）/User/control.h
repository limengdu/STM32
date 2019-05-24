/*-------------------------------------------------------------------------------
�ļ����ƣ�control.h
�ļ���������˼�������ܳ����ƺ���ͷ�ļ�    
��    ע������ƽ̨���ڻ�������ѧ����ѧԺ ��е����ʵ������Ӳ��ƽ̨_V1.0 RC
ά����Ա��Science
��    �䣺565369157@qq.com
---------------------------------------------------------------------------------*/
#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f10x.h"   
#include <stdbool.h>
#include "MemoryList.h"

//#define USE_KEYBOARD
//#define USE_KEY
#define USE_KEY_PID
//#define USE_AUTO

/*��ȡ����ָ��ֵ�ͳ������ԣ������ڸò���*/
#define GetMemAddr(mem) ((unsigned int)(      &mem ))														// ��ȡ�ڴ���ַ�ĺ�
#define GetMemSize(mem) ((unsigned int)(sizeof(mem)))														// ��ȡ�ڴ���ȵĺ�

//GetAddrAreaA(mem, headPara, lastPara)��ָ��Ҫ���ʵ��ڴ��ĵ�ַ��Ϊ����  headPara�� lastPara������
//GetAddrAreaA(mem, headPara          )��ָ��Ҫ���ʵ��ڴ��ĵ�ַ��Ϊ����  headPara���ڴ�����������
//GetAddrAreaA(mem,           lastPara)��ָ��Ҫ���ʵ��ڴ��ĵ�ַ��Ϊ�����ڴ��ʼ��  lastPara������
#define GetAddrAreaA(mem, headPara, lastPara) ((unsigned int)((unsigned char*)(&mem.headPara) - (unsigned char*)(&mem))), (sizeof(mem.lastPara) + (unsigned int)((unsigned char*)(&mem.lastPara) - (unsigned char*)(&mem.headPara)))
#define GetAddrAreaB(mem, headPara          ) ((unsigned int)((unsigned char*)(&mem.headPara) - (unsigned char*)(&mem))), (sizeof(mem         ) - (unsigned int)((unsigned char*)(&mem.headPara) - (unsigned char*)(&mem         )))
#define GetAddrAreaC(mem,           lastPara) ((unsigned int)                                                 0x0000000), (sizeof(mem.lastPara) + (unsigned int)((unsigned char*)(&mem.lastPara) - (unsigned char*)(&mem         )))

/*��ȡ��CommInfoQueue�����������������ڸò���*/
#define GetCommInfoSize(commInfoQueue) (sizeof(commInfoQueue) / sizeof(commInfoQueue[0]))
 																				
void Freescale_Device_Init(void);
void Freescale_Control_Kernel(u8* pLocalMemoryList);

#endif

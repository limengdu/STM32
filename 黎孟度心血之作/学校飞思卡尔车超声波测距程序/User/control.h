/*-------------------------------------------------------------------------------
文件名称：control.h
文件描述：飞思卡尔智能车控制核心头文件    
备    注：测试平台基于华南理工大学广州学院 机械工程实验中心硬件平台_V1.0 RC
维护人员：Science
邮    箱：565369157@qq.com
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

/*获取参数指针值和长度属性，仅用于该步骤*/
#define GetMemAddr(mem) ((unsigned int)(      &mem ))														// 获取内存表地址的宏
#define GetMemSize(mem) ((unsigned int)(sizeof(mem)))														// 获取内存表长度的宏

//GetAddrAreaA(mem, headPara, lastPara)，指定要访问的内存表的地址区为：从  headPara到 lastPara的区域
//GetAddrAreaA(mem, headPara          )，指定要访问的内存表的地址区为：从  headPara到内存表结束的区域
//GetAddrAreaA(mem,           lastPara)，指定要访问的内存表的地址区为：从内存表开始到  lastPara的区域
#define GetAddrAreaA(mem, headPara, lastPara) ((unsigned int)((unsigned char*)(&mem.headPara) - (unsigned char*)(&mem))), (sizeof(mem.lastPara) + (unsigned int)((unsigned char*)(&mem.lastPara) - (unsigned char*)(&mem.headPara)))
#define GetAddrAreaB(mem, headPara          ) ((unsigned int)((unsigned char*)(&mem.headPara) - (unsigned char*)(&mem))), (sizeof(mem         ) - (unsigned int)((unsigned char*)(&mem.headPara) - (unsigned char*)(&mem         )))
#define GetAddrAreaC(mem,           lastPara) ((unsigned int)                                                 0x0000000), (sizeof(mem.lastPara) + (unsigned int)((unsigned char*)(&mem.lastPara) - (unsigned char*)(&mem         )))

/*获取在CommInfoQueue的数据数量，仅用于该步骤*/
#define GetCommInfoSize(commInfoQueue) (sizeof(commInfoQueue) / sizeof(commInfoQueue[0]))
 																				
void Freescale_Device_Init(void);
void Freescale_Control_Kernel(u8* pLocalMemoryList);

#endif

#ifndef __FLASH_H
#define __FLASH_H 			

#include "sys.h"
 
void FLASH_W(u32 add,u16 dat1,u16 dat2); //切记在这里补齐形参数
u16 FLASH_R(u32 add);

#endif





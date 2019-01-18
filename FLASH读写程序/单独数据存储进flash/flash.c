#include "stm32f10x.h"
#include "flash.h"

//FLASH写入数据
void FLASH_W(u32 add,u16 dat)//参数1：32位FLASH地址。参数2：16位数据
{
//	 RCC_HSICmd(ENABLE); //读写flash需要打开内部或外部高速时钟，如果前面已经有程序已经打开时钟，则这里可以注释掉
	 FLASH_Unlock();  //解锁FLASH编程擦除控制器（为防止flash操作出现错误，每次写入flash需要先解锁）
     FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位（标志位：用来判断相应操作是否已经执行或者实践是否发生）
     FLASH_ErasePage(add);     //擦除指定地址页（先擦除才能写入）
     FLASH_ProgramHalfWord(add,dat); //从指定页的addr地址开始写
     FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
     FLASH_Lock();    //锁定FLASH编程擦除控制器
}

//FLASH读出数据
u16 FLASH_R(u32 add)//参数1：32位读出FLASH地址。返回值：16位数据
{ 
	u16 a;
    a = *(u16*)(add);//从指定页的addr地址开始读
    return a;
}


#include "stm32f10x.h"
#include "flash.h"
#include "sys.h"

#define FLASH_START_ADDR  0x0801f000	  //写入的起始地址

int main()
{
	u16 a;
	RCC_Configuration();

	//掉电之后读取FLASH地址的内容，并把数据输入给GPIOX
	a = FLASH_R(FLASH_START_ADDR);//从指定页的地址读FLASH
	GPIO_Write(GPIOX,a); //直接数值操作将变量值写入LED
	
	while(1)
	{
		FLASH_W(FLASH_START_ADDR,a); //从指定页的地址写入FLASH
	}
}

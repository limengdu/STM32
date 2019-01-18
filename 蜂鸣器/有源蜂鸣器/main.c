#include "stm32f10x.h"
#include "beep.h"


int main()

{
	BEEP_Init();

	while (1)
	{
		GPIO_ResetBits(BEEP_PORT,BEEP_PIN);//注意这里不可以使蜂鸣器长时间处于开启状态！！请适时断开电源！！
	}

}
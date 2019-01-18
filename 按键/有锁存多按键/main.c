//此模板通过不同按键实现不同操作
#include "system.h"
#include "SysTick.h"
#include "key.h"


int main()
{
	u8 key;
	SysTick_Init(72);
	KEY_Init();

	while (1)
	{
		key = KEY_Scan(0);            //将按键判断结果赋值给变量key
		switch (key)
		{
		case KEY_UP: XXX; break;      //当按下KEY_UP按键时，执行XXX操作，跳出switch结构
		case KEY_DOWN: XXX; break;    //当按下KEY_DOWN按键时，执行XXX操作，跳出switch结构
		case KEY_LEFT: XXX; break;    //当按下KEY_LEFT按键时，执行XXX操作，跳出switch结构
		case KEY_RIGHT: XXX; break;   //当按下KEY_RIGHT按键时，执行XXX操作，跳出switch结构
		}
	}
}



//��ģ��ͨ����ͬ����ʵ�ֲ�ͬ����
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
		key = KEY_Scan(0);            //�������жϽ����ֵ������key
		switch (key)
		{
		case KEY_UP: XXX; break;      //������KEY_UP����ʱ��ִ��XXX����������switch�ṹ
		case KEY_DOWN: XXX; break;    //������KEY_DOWN����ʱ��ִ��XXX����������switch�ṹ
		case KEY_LEFT: XXX; break;    //������KEY_LEFT����ʱ��ִ��XXX����������switch�ṹ
		case KEY_RIGHT: XXX; break;   //������KEY_RIGHT����ʱ��ִ��XXX����������switch�ṹ
		}
	}
}



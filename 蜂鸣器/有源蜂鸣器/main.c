#include "stm32f10x.h"
#include "beep.h"


int main()

{
	BEEP_Init();

	while (1)
	{
		GPIO_ResetBits(BEEP_PORT,BEEP_PIN);//ע�����ﲻ����ʹ��������ʱ�䴦�ڿ���״̬��������ʱ�Ͽ���Դ����
	}

}
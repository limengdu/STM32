#include "stm32f10x.h"
#include "flash.h"
#include "sys.h"

#define FLASH_START_ADDR  0x0801f000	  //д�����ʼ��ַ

int main()
{
	u16 a,b;
	RCC_Configuration();

	//����֮���ȡFLASH��ַ�����ݣ��������������GPIOX
	a = FLASH_R(FLASH_START_ADDR);//��ָ��ҳ�ĵ�ַ��FLASH
	b = FLASH_R(FLASH_START_ADDR+1);

	GPIO_Write(GPIOX, a); //ֱ����ֵ����������ֵд��LED
	GPIO_Write(GPIOX, b);
	
	while(1)
	{
		FLASH_W(FLASH_START_ADDR,a,b); //��ָ��ҳ�ĵ�ַд��FLASH
	}
}



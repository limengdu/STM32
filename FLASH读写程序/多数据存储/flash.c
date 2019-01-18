#include "stm32f10x.h"
#include "flash.h"

//FLASHд������
void FLASH_W(u32 add,u16 dat1,u16 dat2)//����1��32λFLASH��ַ������2��16λ���ݣ�����3:16λ���ݣ�����������������16λ�βμ��ɣ�
{
//	 RCC_HSICmd(ENABLE); //��дflash��Ҫ���ڲ����ⲿ����ʱ�ӣ����ǰ���Ѿ��г����Ѿ���ʱ�ӣ����������ע�͵�
	 FLASH_Unlock();  //����FLASH��̲�����������Ϊ��ֹflash�������ִ���ÿ��д��flash��Ҫ�Ƚ�����
     FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//�����־λ����־λ�������ж���Ӧ�����Ƿ��Ѿ�ִ�л���ʵ���Ƿ�����
     FLASH_ErasePage(add);     //����ָ����ַҳ���Ȳ�������д�룩
     FLASH_ProgramHalfWord(add,dat1); //��ָ��ҳ��addr��ַ��ʼд��dat1����
	 FLASH_ProgramHalfWord(add, dat2);//��ָ��ҳ��addr��ַ��ʼд��dat2����
     FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//�����־λ
     FLASH_Lock();    //����FLASH��̲���������
}

//FLASH��������
u16 FLASH_R(u32 add)//����1��32λ����FLASH��ַ������ֵ��16λ����
{ 
	u16 a;
    a = *(u16*)(add);//��ָ��ҳ��addr��ַ��ʼ��
    return a;
}




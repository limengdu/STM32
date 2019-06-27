#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */ /*<-----------------------------RT-Thread�ں˲���----------------------------->*/ 

#define RT_NAME_MAX 8																// �ں˶���������󳤶ȣ����ڸó��ȵ����ƶ��ಿ�ֻᱻ�Զ��õ�
#define RT_ALIGN_SIZE 4 														// �ֽڶ���ʱ�趨������ֽڸ�������ʹ��ALIGN(RT_ALIGN_SIZE)�����ֽڶ���
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32										// RT-Thread ֧�ֶ��ٸ����ȼ���Ĭ��Ϊ32
#define RT_TICK_PER_SECOND 1000											// ����ϵͳÿ�����ж��ٸ�����ϵͳ��ʱ�����ڣ�Ĭ��Ϊ 1000 tick����ϵͳÿ��ʱ������tick = 1ms
#define RT_USING_OVERFLOW_CHECK											// ���ջ�Ƿ������δ������ر�
#define RT_USING_HOOK																// ����ú��ʾ�������Ӻ�����ʹ�ã�δ������ر�
#define RT_USING_IDLE_HOOK
#define RT_IDEL_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 256									// �����˿����̵߳�ջ��С
#define RT_DEBUG																		// ����ú꿪��debugģʽ��δ������ر�
#define RT_DEBUG_COLOR

/* Inter-Thread communication */ /*<-----------------------------�̼߳�ͬ����ͨ�Ų��֣��ò��ֻ�ʹ�õ��Ķ������ź��������������¼������䡢��Ϣ���С��źŵȣ�----------------------------->*/ 

#define RT_USING_SEMAPHORE													// ����ú�ɿ����ź�����ʹ�ã�δ������ر�
#define RT_USING_MUTEX															// ����ú�ɿ�����������ʹ�ã�δ������ر�
#define RT_USING_EVENT															// ����ú�ɿ����¼�����ʹ�ã�δ������ر�
#define RT_USING_MAILBOX														// ����ú�ɿ��������ʹ�ã�δ������ر�
#define RT_USING_MESSAGEQUEUE												// ����ú�ɿ�����Ϣ���е�ʹ�ã�δ������ر�
#define RT_USING_SIGNALS                            // ����ú�ɿ����źŵ�ʹ�ã�δ������ر�

/* Memory Management */ /*<-----------------------------�ڴ������----------------------------->*/ 

#define RT_USING_MEMPOOL														// ����ú�ɿ�����̬�ڴ�ص�ʹ�ã�δ������ر�
#define RT_USING_MEMHEAP	 													// ����ú�ɿ��������������ڴ��ƴ�ӵ�ʹ�ã�δ������ر�
#define RT_USING_SMALL_MEM													// ����ú�ɿ�������С�ڴ�����㷨��δ������ر�
#define RT_USING_HEAP																// ����ú�ɿ����ѵ�ʹ�ã�δ������ر�

/* Kernel Device Object */ /*<-----------------------------�ں��豸����----------------------------->*/ 

#define RT_USING_DEVICE															// ��ʾ������ϵͳ�豸��ʹ�ã�ʹ���豸����
#define RT_USING_CONSOLE	 												  // ����ú�ɿ���ϵͳ����̨�豸��ʹ�ã�δ������ر�
#define RT_CONSOLEBUF_SIZE 128											// �������̨�豸�Ļ�������С
#define RT_CONSOLE_DEVICE_NAME "uart2"							// ����̨�豸������
#define RT_VER_NUM 0x40000
#define ARCH_ARM
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M3

/* RT-Thread Components */ /*<-----------------------------RT-thread���----------------------------->*/ 

#define RT_USING_COMPONENTS_INIT 										// ����ú꿪���Զ���ʼ�����ƣ�δ������ر�
#define RT_USING_USER_MAIN													// ����ú꣬������Ӧ�����Ϊmain����
#define RT_MAIN_THREAD_STACK_SIZE 2048							// ����main�̵߳�ջ��С
#define RT_MAIN_THREAD_PRIORITY 10

/* C++ features */


/* Command shell */ /*<-----------------------------�������ն�----------------------------->*/ 

#define RT_USING_FINSH 															// ����ú�ɿ���ϵͳFinSH���Թ��ߵ�ʹ�ã�δ������ر�
#define FINSH_THREAD_NAME "tshell"									// ����ϵͳFinSHʱ�������߳����ƶ���Ϊtshell
#define FINSH_USING_HISTORY													// ����ϵͳFinSHʱ��ʹ����ʷ����
#define FINSH_HISTORY_LINES 5												// ����ϵͳFinSHʱ������ʷ���������Ķ���
#define FINSH_USING_SYMTAB													// ����ϵͳFinSHʱ������ú꿪��ʹ��Tab����δ������ر�
#define FINSH_USING_DESCRIPTION											
#define FINSH_THREAD_PRIORITY 20										// ����ϵͳFinSHʱ��������̵߳����ȼ�
#define FINSH_THREAD_STACK_SIZE 4096								// ����ϵͳFinSHʱ��������̵߳�ջ��С
#define FINSH_CMD_SIZE 80														// ����ϵͳFinSHʱ�����������ַ�����
#define FINSH_USING_MSH															// ����ϵͳFinSHʱ������ú꿪��MSH����
#define FINSH_USING_MSH_DEFAULT											// ����ϵͳFinSHʱ������MSH����ʱ������ú�Ĭ��ʹ��MSH����
#define FINSH_USING_MSH_ONLY												// ����ϵͳFinSHʱ������ú꣬��ʹ��MSH����
#define FINSH_ARG_MAX 10

/* Device virtual file system */ /*<-----------------------------�����ļ�ϵͳ----------------------------->*/ 


/* Device Drivers */ /*<-----------------------------�豸����----------------------------->*/ 

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_USING_PIN

/* Using WiFi */ /*<-----------------------------ʹ��wiFi----------------------------->*/ 


/* Using USB */ /*<-----------------------------ʹ��USB----------------------------->*/ 


/* POSIX layer and C standard library */ /*<-----------------------------ʹ��POSIX���C��׼��----------------------------->*/ 

#define RT_USING_LIBC

/* Network */ /*<-----------------------------ʹ������----------------------------->*/ 

/* Socket abstraction layer */ /*<-----------------------------ʹ���׽��ֳ����----------------------------->*/ 


/* light weight TCP/IP stack */ /*<-----------------------------ʹ��������TCP/IPջ----------------------------->*/ 


/* Modbus master and slave stack */ /*<-----------------------------ʹ��Modbus����ջ----------------------------->*/ 


/* AT commands */ /*<-----------------------------ʹ��AT����----------------------------->*/ 


/* VBUS(Virtual Software BUS) */ /*<-----------------------------ʹ�������������----------------------------->*/ 


/* Utilities */ /*<-----------------------------ʵ�ù���----------------------------->*/ 


/* ARM CMSIS */ /*<-----------------------------ʹ��ARM ΢����������ӿڱ�׼----------------------------->*/ 


/* RT-Thread online packages */ /*<-----------------------------ʹ��RT-thread �������������----------------------------->*/ 

/* IoT - internet of things */ /*<-----------------------------ʹ��������----------------------------->*/ 


/* Wi-Fi */ /*<-----------------------------ʹ��Wi-Fi----------------------------->*/ 

/* Marvell WiFi */ /*<-----------------------------ʹ��Marvell WiFi----------------------------->*/ 


/* Wiced WiFi */ /*<-----------------------------ʹ��Wiced WiFi----------------------------->*/ 


/* IoT Cloud */ /*<-----------------------------ʹ���������ƶ�----------------------------->*/ 


/* security packages */ /*<-----------------------------ʹ�ð�ȫ�����----------------------------->*/ 


/* language packages */ /*<-----------------------------ʹ�����������----------------------------->*/ 


/* multimedia packages */ /*<-----------------------------ʹ�ö�ý�������----------------------------->*/ 


/* tools packages */ /*<-----------------------------ʹ�ù��������----------------------------->*/ 


/* system packages */ /*<-----------------------------ʹ��ϵͳ�����----------------------------->*/ 


/* peripheral libraries and drivers */ /*<-----------------------------ʹ����������������----------------------------->*/ 


/* miscellaneous packages */ /*<-----------------------------ʹ�����������----------------------------->*/ 


/* samples: kernel and components samples */ /*<-----------------------------ʾ��:�ں˺����ʾ��----------------------------->*/ 

#define SOC_FAMILY_STM32
#define SOC_SERIES_STM32F1

/* Hardware Drivers Config */ /*<-----------------------------Ӳ��������������----------------------------->*/ 

#define SOC_STM32F103VE

/* Onboard Peripheral Drivers */ /*<-----------------------------������������----------------------------->*/ 

#define BSP_USING_USB_TO_USART

/* On-chip Peripheral Drivers */ /*<-----------------------------Ƭ��������������----------------------------->*/ 

#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART2

/* Board extended module Drivers */ /*<-----------------------------��չģ����������----------------------------->*/ 


#endif

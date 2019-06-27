#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */ /*<-----------------------------RT-Thread内核部分----------------------------->*/ 

#define RT_NAME_MAX 8																// 内核对象名称最大长度，大于该长度的名称多余部分会被自动裁掉
#define RT_ALIGN_SIZE 4 														// 字节对齐时设定对齐的字节个数。常使用ALIGN(RT_ALIGN_SIZE)进行字节对齐
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32										// RT-Thread 支持多少个优先级，默认为32
#define RT_TICK_PER_SECOND 1000											// 操作系统每秒钟有多少个操作系统的时钟周期，默认为 1000 tick，即系统每个时钟周期tick = 1ms
#define RT_USING_OVERFLOW_CHECK											// 检查栈是否溢出，未定义则关闭
#define RT_USING_HOOK																// 定义该宏表示开启钩子函数的使用，未定义则关闭
#define RT_USING_IDLE_HOOK
#define RT_IDEL_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 256									// 定义了空闲线程的栈大小
#define RT_DEBUG																		// 定义该宏开启debug模式，未定义则关闭
#define RT_DEBUG_COLOR

/* Inter-Thread communication */ /*<-----------------------------线程间同步与通信部分（该部分会使用到的对象有信号量、互斥量、事件、邮箱、消息队列、信号等）----------------------------->*/ 

#define RT_USING_SEMAPHORE													// 定义该宏可开启信号量的使用，未定义则关闭
#define RT_USING_MUTEX															// 定义该宏可开启互斥量的使用，未定义则关闭
#define RT_USING_EVENT															// 定义该宏可开启事件集的使用，未定义则关闭
#define RT_USING_MAILBOX														// 定义该宏可开启邮箱的使用，未定义则关闭
#define RT_USING_MESSAGEQUEUE												// 定义该宏可开启消息队列的使用，未定义则关闭
#define RT_USING_SIGNALS                            // 定义该宏可开启信号的使用，未定义则关闭

/* Memory Management */ /*<-----------------------------内存管理部分----------------------------->*/ 

#define RT_USING_MEMPOOL														// 定义该宏可开启静态内存池的使用，未定义则关闭
#define RT_USING_MEMHEAP	 													// 定义该宏可开启两个或以上内存堆拼接的使用，未定义则关闭
#define RT_USING_SMALL_MEM													// 定义该宏可开启开启小内存管理算法，未定义则关闭
#define RT_USING_HEAP																// 定义该宏可开启堆的使用，未定义则关闭

/* Kernel Device Object */ /*<-----------------------------内核设备对象----------------------------->*/ 

#define RT_USING_DEVICE															// 表示开启了系统设备的使用，使用设备驱动
#define RT_USING_CONSOLE	 												  // 定义该宏可开启系统控制台设备的使用，未定义则关闭
#define RT_CONSOLEBUF_SIZE 128											// 定义控制台设备的缓冲区大小
#define RT_CONSOLE_DEVICE_NAME "uart2"							// 控制台设备的名称
#define RT_VER_NUM 0x40000
#define ARCH_ARM
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M3

/* RT-Thread Components */ /*<-----------------------------RT-thread组件----------------------------->*/ 

#define RT_USING_COMPONENTS_INIT 										// 定义该宏开启自动初始化机制，未定义则关闭
#define RT_USING_USER_MAIN													// 定义该宏，启设置应用入口为main函数
#define RT_MAIN_THREAD_STACK_SIZE 2048							// 定义main线程的栈大小
#define RT_MAIN_THREAD_PRIORITY 10

/* C++ features */


/* Command shell */ /*<-----------------------------命令行终端----------------------------->*/ 

#define RT_USING_FINSH 															// 定义该宏可开启系统FinSH调试工具的使用，未定义则关闭
#define FINSH_THREAD_NAME "tshell"									// 开启系统FinSH时：将该线程名称定义为tshell
#define FINSH_USING_HISTORY													// 开启系统FinSH时：使用历史命令
#define FINSH_HISTORY_LINES 5												// 开启系统FinSH时：对历史命令行数的定义
#define FINSH_USING_SYMTAB													// 开启系统FinSH时：定义该宏开启使用Tab键，未定义则关闭
#define FINSH_USING_DESCRIPTION											
#define FINSH_THREAD_PRIORITY 20										// 开启系统FinSH时：定义该线程的优先级
#define FINSH_THREAD_STACK_SIZE 4096								// 开启系统FinSH时：定义该线程的栈大小
#define FINSH_CMD_SIZE 80														// 开启系统FinSH时：定义命令字符长度
#define FINSH_USING_MSH															// 开启系统FinSH时：定义该宏开启MSH功能
#define FINSH_USING_MSH_DEFAULT											// 开启系统FinSH时：开启MSH功能时，定义该宏默认使用MSH功能
#define FINSH_USING_MSH_ONLY												// 开启系统FinSH时：定义该宏，仅使用MSH功能
#define FINSH_ARG_MAX 10

/* Device virtual file system */ /*<-----------------------------虚拟文件系统----------------------------->*/ 


/* Device Drivers */ /*<-----------------------------设备驱动----------------------------->*/ 

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_USING_PIN

/* Using WiFi */ /*<-----------------------------使用wiFi----------------------------->*/ 


/* Using USB */ /*<-----------------------------使用USB----------------------------->*/ 


/* POSIX layer and C standard library */ /*<-----------------------------使用POSIX层和C标准库----------------------------->*/ 

#define RT_USING_LIBC

/* Network */ /*<-----------------------------使用网络----------------------------->*/ 

/* Socket abstraction layer */ /*<-----------------------------使用套接字抽象层----------------------------->*/ 


/* light weight TCP/IP stack */ /*<-----------------------------使用轻量级TCP/IP栈----------------------------->*/ 


/* Modbus master and slave stack */ /*<-----------------------------使用Modbus主从栈----------------------------->*/ 


/* AT commands */ /*<-----------------------------使用AT命令----------------------------->*/ 


/* VBUS(Virtual Software BUS) */ /*<-----------------------------使用虚拟软件总线----------------------------->*/ 


/* Utilities */ /*<-----------------------------实用工具----------------------------->*/ 


/* ARM CMSIS */ /*<-----------------------------使用ARM 微控制器软件接口标准----------------------------->*/ 


/* RT-Thread online packages */ /*<-----------------------------使用RT-thread 在线网络软件包----------------------------->*/ 

/* IoT - internet of things */ /*<-----------------------------使用物联网----------------------------->*/ 


/* Wi-Fi */ /*<-----------------------------使用Wi-Fi----------------------------->*/ 

/* Marvell WiFi */ /*<-----------------------------使用Marvell WiFi----------------------------->*/ 


/* Wiced WiFi */ /*<-----------------------------使用Wiced WiFi----------------------------->*/ 


/* IoT Cloud */ /*<-----------------------------使用物联网云端----------------------------->*/ 


/* security packages */ /*<-----------------------------使用安全软件包----------------------------->*/ 


/* language packages */ /*<-----------------------------使用语言软件包----------------------------->*/ 


/* multimedia packages */ /*<-----------------------------使用多媒体软件包----------------------------->*/ 


/* tools packages */ /*<-----------------------------使用工具软件包----------------------------->*/ 


/* system packages */ /*<-----------------------------使用系统软件包----------------------------->*/ 


/* peripheral libraries and drivers */ /*<-----------------------------使用外设库和驱动程序----------------------------->*/ 


/* miscellaneous packages */ /*<-----------------------------使用其它软件包----------------------------->*/ 


/* samples: kernel and components samples */ /*<-----------------------------示例:内核和组件示例----------------------------->*/ 

#define SOC_FAMILY_STM32
#define SOC_SERIES_STM32F1

/* Hardware Drivers Config */ /*<-----------------------------硬件驱动程序配置----------------------------->*/ 

#define SOC_STM32F103VE

/* Onboard Peripheral Drivers */ /*<-----------------------------板载外设驱动----------------------------->*/ 

#define BSP_USING_USB_TO_USART

/* On-chip Peripheral Drivers */ /*<-----------------------------片上外设驱动程序----------------------------->*/ 

#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART2

/* Board extended module Drivers */ /*<-----------------------------扩展模块驱动程序----------------------------->*/ 


#endif

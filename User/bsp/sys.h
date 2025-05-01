#ifndef __SYS_H__
#define __SYS_H__

#include "main.h"
#include "stm32f407xx.h"
#include <stdio.h>

#define __IO volatile
#define __I  volatile const
/*
 *@brief:系统支持ucos
    *@note: 0,不支持ucos
            1,支持ucos
*/
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持UCOS

//定义一些常用的数据类型短关键字 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;
 
typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  
 
typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;
 
typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   
 
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
 
typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 
 
typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;
 
typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  
 
 
 
void delay_us(uint32_t _us);
void delay_ms(uint32_t _ms);
void delay_1ms(uint32_t ms);
void delay_1us(uint32_t us);
 
//位带操作
#define BIT_ADDR(byte_offset,bitnum)  (volatile unsigned long*)(0x42000000 + (byte_offset * 32) + (bitnum * 4))

// 计算GPIOB寄存器的位带别名区地址
#define GPIOA_OCTL_OFFSET ((GPIOA_BASE + 0x14) - 0x40000000)
#define GPIOB_OCTL_OFFSET ((GPIOB_BASE + 0x14) - 0x40000000)
#define GPIOC_OCTL_OFFSET ((GPIOC_BASE + 0x14) - 0x40000000)
#define GPIOD_OCTL_OFFSET ((GPIOD_BASE + 0x14) - 0x40000000)
#define GPIOE_OCTL_OFFSET ((GPIOE_BASE + 0x14) - 0x40000000)
#define GPIOF_OCTL_OFFSET ((GPIOF_BASE + 0x14) - 0x40000000)
#define GPIOG_OCTL_OFFSET ((GPIOG_BASE + 0x14) - 0x40000000)

#define GPIOA_ISTAT_OFFSET ((GPIOA_BASE + 0x10) - 0x40000000)
#define GPIOB_ISTAT_OFFSET ((GPIOB_BASE + 0x10) - 0x40000000)
#define GPIOC_ISTAT_OFFSET ((GPIOC_BASE + 0x10) - 0x40000000)
#define GPIOD_ISTAT_OFFSET ((GPIOD_BASE + 0x10) - 0x40000000)
#define GPIOE_ISTAT_OFFSET ((GPIOE_BASE + 0x10) - 0x40000000)
#define GPIOF_ISTAT_OFFSET ((GPIOF_BASE + 0x10) - 0x40000000)
#define GPIOG_ISTAT_OFFSET ((GPIOG_BASE + 0x10) - 0x40000000)


// 定义输出和输入宏
#define PAin(n)     *(BIT_ADDR(GPIOA_ISTAT_OFFSET,n))   // PA输入
#define PBin(n)     *(BIT_ADDR(GPIOB_ISTAT_OFFSET,n))   // PB输入
#define PCin(n)     *(BIT_ADDR(GPIOC_ISTAT_OFFSET,n))   // PC输入
#define PDin(n)     *(BIT_ADDR(GPIOD_ISTAT_OFFSET,n))   // PD输入
#define PEin(n)     *(BIT_ADDR(GPIOE_ISTAT_OFFSET,n))   // PE输入
#define PFin(n)     *(BIT_ADDR(GPIOF_ISTAT_OFFSET,n))   // PF输入
#define PGin(n)     *(BIT_ADDR(GPIOG_ISTAT_OFFSET,n))   // PG输入

#define PAout(n)    *(BIT_ADDR(GPIOA_OCTL_OFFSET,n))    // PA输出
#define PBout(n)    *(BIT_ADDR(GPIOB_OCTL_OFFSET,n))    // PB输出
#define PCout(n)    *(BIT_ADDR(GPIOC_OCTL_OFFSET,n))    // PC输出
#define PDout(n)    *(BIT_ADDR(GPIOD_OCTL_OFFSET,n))    // PD输出
#define PEout(n)    *(BIT_ADDR(GPIOE_OCTL_OFFSET,n))    // PE输出
#define PFout(n)    *(BIT_ADDR(GPIOF_OCTL_OFFSET,n))    // PF输出
#define PGout(n)    *(BIT_ADDR(GPIOG_OCTL_OFFSET,n))    // PG输出

#endif

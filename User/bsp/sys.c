#include "sys.h"
#include "bsp_dwt.h"
#define SYSCLK 168000000

/**
 -  @brief  用内核的 systick 实现的微妙延时
 -  @note   None
 -  @param  _us:要延时的us数
 -  @retval None
*/
void delay_us(uint32_t us)
{
    float delay_seconds = (float)us / 1000000.0f;
    DWT_Delay(delay_seconds);
}

// void delay_us(uint32_t _us)
// {
//     uint32_t ticks;
//     uint32_t told, tnow, tcnt = 0;
 
//     // 计算需要的时钟数 = 延迟微秒数 * 每微秒的时钟数
//     ticks = _us * (SYSCLK / 1000000);
 
//     // 获取当前的SysTick值
//     told = SysTick->VAL;
 
//     while (1)
//     {
//         // 重复刷新获取当前的SysTick值
//         tnow = SysTick->VAL;
 
//         if (tnow != told)
//         {
//             if (tnow < told)
//                 tcnt += told - tnow;
//             else
//                 tcnt += SysTick->LOAD - tnow + told;
 
//             told = tnow;
 
//             // 如果达到了需要的时钟数，就退出循环
//             if (tcnt >= ticks)
//                 break;
//         }
//     }
// }

/**
 -  @brief  调用用内核的 systick 实现的毫秒延时
 -  @note   None
 -  @param  _ms:要延时的ms数
 -  @retval None
*/
void delay_ms(uint32_t _ms) { delay_us(_ms * 1000); }
 
void delay_1ms(uint32_t ms) { delay_us(ms * 1000); }
 
void delay_1us(uint32_t us) { delay_us(us); }



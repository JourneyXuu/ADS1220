/**
 ******************************************************************************
 * @file	bsp_dwt.c
 * @author  Wang Hongxi
 * @version V1.1.0
 * @date    2022/3/8
 * @brief
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
#include "bsp_dwt.h"
// 系统时间结构体
DWT_Time_t SysTime;

// CPU 频率相关参数
static uint32_t CPU_FREQ_Hz;       // CPU 频率 (Hz)
static uint32_t CPU_FREQ_Hz_ms;    // CPU 频率每毫秒的周期数
static uint32_t CPU_FREQ_Hz_us;    // CPU 频率每微秒的周期数

// DWT 计数器溢出计数
static uint32_t CYCCNT_RountCount;
static uint32_t CYCCNT_LAST;       // 上一次读取的 CYCCNT 值
uint64_t CYCCNT64;                 // 64位的累计计数值


// 更新 DWT 计数器溢出计数的内部函数
static void DWT_CNT_Update(void);


/**
 * @brief   初始化 DWT 模块
 * @param   CPU_Freq_mHz: CPU 频率 (MHz)
 * @note    使能 DWT 外设并初始化相关参数
 */
void DWT_Init(uint32_t CPU_Freq_mHz)
{
    /* 使能DWT外设 */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    /* DWT CYCCNT寄存器计数清0 */
    DWT->CYCCNT = (uint32_t)0u;

    /* 使能Cortex-M DWT CYCCNT寄存器 */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    CPU_FREQ_Hz = CPU_Freq_mHz * 1000000;
    CPU_FREQ_Hz_ms = CPU_FREQ_Hz / 1000;
    CPU_FREQ_Hz_us = CPU_FREQ_Hz / 1000000;
    CYCCNT_RountCount = 0;
}

/**
 * @brief   获取两次采样之间的时间差（秒）
 * @param   cnt_last: 上次采样的 CYCCNT 值指针
 * @return  时间差（秒）
 * @note    使用浮点数返回时间差
 */
float DWT_GetDeltaT(uint32_t *cnt_last)
{
    volatile uint32_t cnt_now = DWT->CYCCNT;
    float dt = ((uint32_t)(cnt_now - *cnt_last)) / ((float)(CPU_FREQ_Hz));
    *cnt_last = cnt_now;

    DWT_CNT_Update();

    return dt;
}

/**
 * @brief   获取两次采样之间的时间差（秒），使用双精度浮点数
 * @param   cnt_last: 上次采样的 CYCCNT 值指针
 * @return  时间差（秒）
 * @note    使用双精度浮点数返回时间差
 */
double DWT_GetDeltaT64(uint32_t *cnt_last)
{
    volatile uint32_t cnt_now = DWT->CYCCNT;
    double dt = ((uint32_t)(cnt_now - *cnt_last)) / ((double)(CPU_FREQ_Hz));
    *cnt_last = cnt_now;

    DWT_CNT_Update();

    return dt;
}

/**
 * @brief   更新系统时间
 * @note    根据 DWT 计数器更新系统时间（秒、毫秒、微秒）
 */
void DWT_SysTimeUpdate(void)
{
    volatile uint32_t cnt_now = DWT->CYCCNT;
    static uint64_t CNT_TEMP1, CNT_TEMP2, CNT_TEMP3;

    DWT_CNT_Update();

    CYCCNT64 = (uint64_t)CYCCNT_RountCount * (uint64_t)UINT32_MAX + (uint64_t)cnt_now;
    CNT_TEMP1 = CYCCNT64 / CPU_FREQ_Hz;
    CNT_TEMP2 = CYCCNT64 - CNT_TEMP1 * CPU_FREQ_Hz;
    SysTime.s = CNT_TEMP1;
    SysTime.ms = CNT_TEMP2 / CPU_FREQ_Hz_ms;
    CNT_TEMP3 = CNT_TEMP2 - SysTime.ms * CPU_FREQ_Hz_ms;
    SysTime.us = CNT_TEMP3 / CPU_FREQ_Hz_us;
}

/**
 * @brief   获取当前时间（秒）
 * @return  当前时间（秒）
 * @note    返回浮点数表示的秒数
 */
float DWT_GetTimeline_s(void)
{
    DWT_SysTimeUpdate();

    float DWT_Timelinef32 = SysTime.s + SysTime.ms * 0.001f + SysTime.us * 0.000001f;

    return DWT_Timelinef32;
}

/**
 * @brief   获取当前时间（毫秒）
 * @return  当前时间（毫秒）
 * @note    返回浮点数表示的毫秒数
 */
float DWT_GetTimeline_ms(void)
{
    DWT_SysTimeUpdate();

    float DWT_Timelinef32 = SysTime.s * 1000 + SysTime.ms + SysTime.us * 0.001f;

    return DWT_Timelinef32;
}


/**
 * @brief   获取当前时间（微秒）
 * @return  当前时间（微秒）
 * @note    返回 64 位整数表示的微秒数
 */
uint64_t DWT_GetTimeline_us(void)
{
    DWT_SysTimeUpdate();

    uint64_t DWT_Timelinef32 = SysTime.s * 1000000 + SysTime.ms * 1000 + SysTime.us;

    return DWT_Timelinef32;
}

/**
 * @brief   内部函数：更新 DWT 计数器溢出计数
 * @note    如果 CYCCNT 发生溢出，则增加溢出计数
 */
static void DWT_CNT_Update(void)
{
    volatile uint32_t cnt_now = DWT->CYCCNT;

    if (cnt_now < CYCCNT_LAST)
        CYCCNT_RountCount++;//溢出

    CYCCNT_LAST = cnt_now;
}

/**
 * @brief   延时函数
 * @param   Delay: 延时时长（秒）
 * @note    使用 DWT 计数器实现精确延时
 */
void DWT_Delay(float Delay)
{
    uint32_t tickstart = DWT->CYCCNT;
    float wait = Delay;

    while ((DWT->CYCCNT - tickstart) < wait * (float)CPU_FREQ_Hz)
    {
    }
}





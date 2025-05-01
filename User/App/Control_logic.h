#ifndef __CONTROL_LOGIC_H__
#define __CONTROL_LOGIC_H__

#include "main.h"
#include "tim.h"
#include "gpio.h"

typedef struct{
    volatile uint32_t counter;//当前计数值
    uint8_t isRunning;
} DelayTimer;

extern DelayTimer delayTimer;


void Delay_Timer(uint32_t millseconds);
uint8_t checkDelayTimer(void);


#endif 











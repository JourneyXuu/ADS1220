#ifndef __TJC_H__
#define __TJC_H__

#include "main.h"
#include "usart.h"



extern volatile uint8_t Task_Flag; //事件标志位,5道题
extern volatile uint8_t Selected_Chess;
extern volatile uint8_t Selected_Board;
extern volatile uint8_t break_flag;//退出任务标志位



void  TJC_UART_UnPack(uint8_t *dma_buffer);



#endif



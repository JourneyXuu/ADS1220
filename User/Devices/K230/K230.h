#ifndef __K230_H__
#define __K230_H__

#include "main.h"
#include "usart.h"

volatile extern uint8_t Step_Board;
volatile extern uint8_t Step_Board2;
extern uint8_t Test_Step;

void  K230_UART_UnPack(uint8_t *dma_buffer);



#endif



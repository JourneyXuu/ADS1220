 #ifndef __BSP_UART_H
 #define __BSP_UART_H


 #include "main.h"
 #include "usart.h"
 #include "dma.h"


 #include <stdio.h>
 #include <stdbool.h>
 #include <stdint.h>

 /*通用任务结构体*/
 typedef struct{
     uint8_t task;
     uint8_t chess_ID;
     uint8_t board_ID;
 }Task_Command;

 /*  数据包头包尾、最大长度 */
 #define PACKET_HEADER 0xAA
 #define PACKET_FOOTER 0x55

 #define DMA_BUFFER 128

 extern  uint8_t rx2_buffer[DMA_BUFFER];
 extern  uint8_t rx3_buffer[DMA_BUFFER];
 extern  uint8_t rx6_buffer[DMA_BUFFER];


 #define MAX_PACKET_LENGTH   64   // 根据实际需求调整

 /* 解析状态机状态 */
 typedef enum {
     RX_WAIT_HEADER,     // 等待包头
     RX_RECEIVING,       // 接收数据中
     RX_COMPLETE         // 包接收完成
 } RxState;
 
 /* 接收控制结构体 */
 typedef struct {
     RxState state;           // 当前状态
     uint8_t buffer[MAX_PACKET_LENGTH]; // 数据缓存
     uint16_t index;          // 数据存储位置
 } UART_RxHandler;
 
extern UART_RxHandler tjc_rx_handler ;
extern UART_RxHandler k230_rx_handler ;



 int fputc(int ch, FILE *f);

 void usart6_SendCmd(uint8_t *cmd,uint8_t len);
 void usart3_SendCmd(uint8_t *cmd,uint8_t len);
 void usart2_SendCmd(uint8_t *cmd,uint8_t len);

 
 
 
 #endif 




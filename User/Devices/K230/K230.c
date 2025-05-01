#include "K230.h"
#include "bsp_uart.h"
#include <string.h>

volatile uint8_t Step_Board = 0;
volatile uint8_t Step_Board2 = 0;

uint8_t Test_Step = 0;

extern DMA_HandleTypeDef hdma_usart6_rx;


void  K230_UART_UnPack(uint8_t *dma_buffer)
{
    uint8_t data;
    for (uint16_t i = 0; i < MAX_PACKET_LENGTH; i++) 
    {
        data = dma_buffer[i];   
            switch (k230_rx_handler.state) {
                case RX_WAIT_HEADER:
                    if (data == PACKET_HEADER) { // 检测到包头
                        k230_rx_handler.index = 0;// 直接重置索引，不存储包头
                        k230_rx_handler.state = RX_RECEIVING;
                    }
                    break;

                case RX_RECEIVING:
                    if (data == PACKET_FOOTER) { // 检测到包尾
                        //检测到包尾时不存储包尾，直接进行数据有效性检查。
                        // 数据有效性检查（可添加CRC校验）
                        if (k230_rx_handler.index >= 1) { // 最小有效包长度判断
                            Step_Board =  k230_rx_handler.buffer[0];
                            Step_Board2 = k230_rx_handler.buffer[1];    //第六题，从Board移动到Board2
                        }
                        
                        k230_rx_handler.state = RX_COMPLETE;
                    } else {
                        if (k230_rx_handler.index < MAX_PACKET_LENGTH - 1) {
                            k230_rx_handler.buffer[k230_rx_handler.index++] = data;
                        } else { // 数据超长处理
                            k230_rx_handler.state = RX_WAIT_HEADER;
                        }
                    }
                    break;

                case RX_COMPLETE: // 完成一帧接收后复位状态机
                default:
                    k230_rx_handler.state = RX_WAIT_HEADER;
                    memset(k230_rx_handler.buffer, 0, sizeof(k230_rx_handler.buffer));
                    k230_rx_handler.index = 0;
                    break;
            }
    }
    HAL_UARTEx_ReceiveToIdle_DMA(&huart6, dma_buffer, DMA_BUFFER); // 启用空闲中断接收
    __HAL_DMA_DISABLE_IT(&hdma_usart6_rx, DMA_IT_HT);          

}

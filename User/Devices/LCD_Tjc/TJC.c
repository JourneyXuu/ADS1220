#include "TJC.h"
#include "bsp_uart.h"
#include <string.h>

volatile uint8_t Task_Flag = 0; //事件标志位,5道题
volatile uint8_t Selected_Chess = 0;
volatile uint8_t Selected_Board = 0;
volatile uint8_t break_flag = 0;//退出任务标志位

extern DMA_HandleTypeDef hdma_usart3_rx;

/*  
 *@陶晶驰串口屏数据处理(基于状态机的不定长数据处理函数)
*/

void  TJC_UART_UnPack(uint8_t *dma_buffer)
{
    uint8_t data;
    for (uint16_t i = 0; i < MAX_PACKET_LENGTH; i++) 
    {
        data = dma_buffer[i];   
            switch (tjc_rx_handler.state) {
                case RX_WAIT_HEADER:
                    if (data == PACKET_HEADER) { // 检测到包头
                        tjc_rx_handler.index = 0;// 直接重置索引，不存储包头
                        tjc_rx_handler.state = RX_RECEIVING;
                    }
                    break;

                case RX_RECEIVING:
                    if (data == PACKET_FOOTER) { // 检测到包尾
                        //检测到包尾时不存储包尾，直接进行数据有效性检查。
                        // 数据有效性检查（可添加CRC校验）
                        if (tjc_rx_handler.index >= 2) { // 最小有效包长度判断
                            Task_Flag    = tjc_rx_handler.buffer[0];
                            Selected_Chess = tjc_rx_handler.buffer[1];
                            Selected_Board = tjc_rx_handler.buffer[2];
                            break_flag = tjc_rx_handler.buffer[3];
                        }
                        
                        tjc_rx_handler.state = RX_COMPLETE;
                    } else {
                        if (tjc_rx_handler.index < MAX_PACKET_LENGTH - 1) {
                            tjc_rx_handler.buffer[tjc_rx_handler.index++] = data;
                        } else { // 数据超长处理
                            tjc_rx_handler.state = RX_WAIT_HEADER;
                        }
                    }
                    break;

                case RX_COMPLETE: // 完成一帧接收后复位状态机
                default:
                    tjc_rx_handler.state = RX_WAIT_HEADER;
                    memset(tjc_rx_handler.buffer, 0, sizeof(tjc_rx_handler.buffer));
                    tjc_rx_handler.index = 0;
                    break;
            }
    }

    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, dma_buffer, DMA_BUFFER); // 启用空闲中断接收
    __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);          

}


#include "USART_Callback.h"
#include "bsp_uart.h"
#include "TJC.h"
#include "K230.h"


extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart6_rx;

/**
  * @brief  串口空闲中断回调函数
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance == USART2)
    
    {
        HAL_GPIO_TogglePin(GPIOD, LED_3_Pin);
    }
    else if(huart == &huart3)
    {
        HAL_GPIO_TogglePin(GPIOD, LED_3_Pin);
        TJC_UART_UnPack(rx3_buffer);
    }
    else if(huart == &huart6)
    {
        HAL_GPIO_TogglePin(GPIOD, LED_3_Pin);
        K230_UART_UnPack(rx6_buffer);
    }

}

/**
  * @brief  串口接收中断回调函数
  */
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if(huart == &huart2)
    {
        // CH010_HI91_Init();
        // hi91_data.eorror_check++;
    }
    if(huart == &huart3)
    {
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx3_buffer, DMA_BUFFER); // 启用空闲中断接收
        __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);          
    }
    if(huart == &huart6)
    {
        HAL_UARTEx_ReceiveToIdle_DMA(&huart6, rx6_buffer, DMA_BUFFER); // 启用空闲中断接收
        __HAL_DMA_DISABLE_IT(&hdma_usart6_rx, DMA_IT_HT);   
    }


}






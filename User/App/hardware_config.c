#include "hardware_config.h"
#include "bsp_dwt.h"
#include "bsp_uart.h"
#include "usart.h"
#include "control.h"

extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart6_rx;

void HardwareConfig(void)
{		
	DWT_Init(168);

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //开启PWM输出

	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rx2_buffer, DMA_BUFFER); // 启用空闲中断接收
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx3_buffer, DMA_BUFFER);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart6, rx6_buffer, DMA_BUFFER); 

    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);                      // 关闭DMA传输过半中断
    __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);                      // 关闭DMA传输过半中断
    __HAL_DMA_DISABLE_IT(&hdma_usart6_rx, DMA_IT_HT);                      // 关闭DMA传输过半中断

    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim3);  ///主任务跑在定时器3，频率高，注释掉方便调试
		HAL_TIM_Base_Start_IT(&htim4);

    //使能电机
    EmmEN_Init();
}



 #include "bsp_uart.h"
 #include "hardware_config.h"

// /*DMA接收缓存区*/
 uint8_t rx2_buffer[DMA_BUFFER] = {0};
 uint8_t rx3_buffer[DMA_BUFFER] = {0};
 uint8_t rx6_buffer[DMA_BUFFER] = {0};


UART_RxHandler tjc_rx_handler = {RX_WAIT_HEADER, {0}, 0};
UART_RxHandler k230_rx_handler = {RX_WAIT_HEADER, {0}, 0};;

/*  
 * @brief   串口6发送数据(K230用)
*/
void usart6_SendCmd(uint8_t *cmd,uint8_t len)
{
    volatile uint8_t i = 0;
    for(i = 0; i < len; i++)
    {
    HAL_UART_Transmit(&huart6,&cmd[i],1,HAL_MAX_DELAY);
    }
}
/*  
 * @brief   串口3发送数据(串口屏幕用)
*/
void usart3_SendCmd(uint8_t *cmd,uint8_t len)
{
    volatile uint8_t i = 0;
    for(i = 0; i < len; i++)
    {
    HAL_UART_Transmit(&huart3,&cmd[i],1,HAL_MAX_DELAY);
    }
}
/*  
 * @brief   串口2发送数据(步进用)
*/
void usart2_SendCmd(uint8_t *cmd,uint8_t len)
{
    volatile uint8_t i = 0;
    for(i = 0; i < len; i++)
    {
    HAL_UART_Transmit(&huart2,&cmd[i],1,HAL_MAX_DELAY);
    }
}
/*
@bief:串口1调试printf重定向
*/
int fputc(int ch, FILE *f){
	uint8_t temp[1] = {ch};
	HAL_UART_Transmit(&huart1,temp,1,2);
	return ch; 
}



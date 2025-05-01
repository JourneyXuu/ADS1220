#include "emm42_uart.h"
#include "bsp_uart.h"

// 串口发送函数
void UART_Send(uint8_t *data, uint16_t size)
{
      HAL_UART_Transmit(&huart2, data, size, HAL_MAX_DELAY);
		// HAL_UART_Transmit(&huart6, data, size, HAL_MAX_DELAY);
}

// 电机使能
void Motor_Enable(uint8_t address) 
{
   uint8_t cmd[] = {address, MOTOR_ENABLE_CMD, 0xAB, 0x01, 0x00, 0x6B};
   UART_Send(cmd, sizeof(cmd));
}

// 电机失能
void Motor_Disable(uint8_t address) 
{
   uint8_t cmd[] = {address, MOTOR_DISABLE_CMD, 0xAB, 0x00, 0x00, 0x6B};
   UART_Send(cmd, sizeof(cmd));
}

// 设置电机速度
void Motor_SetSpeed(uint8_t address, Motor_DirectionTypeDef direction, 
										uint16_t speed, uint16_t acceleration) 
{
   uint8_t cmd[] = 
		{
       address,
       MOTOR_SPEED_CMD,
       (uint8_t)direction,
       (uint8_t)(speed >> 8),
       (uint8_t)speed,
       (uint8_t)acceleration,
       0x00,
       0x6B
   };
   UART_Send(cmd, sizeof(cmd));
}

// 设置电机位置
void Motor_SetPosition(uint8_t address, Motor_DirectionTypeDef direction, 
											 uint16_t speed, uint16_t acceleration, uint32_t position) 
{
   uint8_t cmd[] = 
		{
       address,
       MOTOR_POSITION_CMD,
       (uint8_t)direction,
       (uint8_t)(speed >> 8),
       (uint8_t)speed,
       (uint8_t)acceleration,
       (uint8_t)(position >> 24),
       (uint8_t)(position >> 16),
       (uint8_t)(position >> 8),
       (uint8_t)position,
				0x00,
       0x00,
       0x6B
   };
   UART_Send(cmd, sizeof(cmd));
}

// 停止电机
void Motor_Stop(uint8_t address) {
   uint8_t cmd[] = {address, MOTOR_STOP_CMD, 0x98, 0x00, 0x6B};
   UART_Send(cmd, sizeof(cmd));
}

// 同步电机
void Motor_Sync(uint8_t address) {
   uint8_t cmd[] = {address, MOTOR_SYNC_CMD, 0x66, 0x6B};
   UART_Send(cmd, sizeof(cmd));
}

// 设置原点
void Motor_SetOrigin(uint8_t address) {
   uint8_t cmd[] = {address, MOTOR_SET_ORIGIN_CMD, 0x88, 0x01, 0x6B};
   UART_Send(cmd, sizeof(cmd));
}

// 触发回零
void Motor_TriggerOrigin(uint8_t address) {
   uint8_t cmd[] = {address, MOTOR_TRIGGER_ORIGIN_CMD, 0x00, 0x00, 0x6B};
   UART_Send(cmd, sizeof(cmd));
}

// 读取电机状态
uint8_t Motor_ReadStatus(uint8_t address) {
   uint8_t cmd[] = {address, MOTOR_READ_STATUS_CMD, 0x6B};
   uint8_t response[4];
   UART_Send(cmd, sizeof(cmd));
   HAL_UART_Receive(&huart2, response, sizeof(response), HAL_MAX_DELAY);
   return response[2]; // 返回状态字节
}

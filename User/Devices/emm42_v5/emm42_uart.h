#ifndef __EMM42_UART_H
#define __EMM42_UART_H

#include "main.h"
#include "usart.h"

#include <string.h>


// 电机参数设置
#define SBUDIVISION        			16		//步进电机细分数


// 电机控制命令
#define MOTOR_ENABLE_CMD        	0xF3
#define MOTOR_DISABLE_CMD      		0xF3
#define MOTOR_SPEED_CMD         	0xF6
#define MOTOR_POSITION_CMD     	  0xFD
#define MOTOR_STOP_CMD         		0xFE
#define MOTOR_SYNC_CMD          	0xFF
#define MOTOR_SET_ORIGIN_CMD    	0x93
#define MOTOR_TRIGGER_ORIGIN_CMD 	0x9A
#define MOTOR_READ_STATUS_CMD   	0x3B



// 电机状态
typedef enum {
   MOTOR_STATUS_IDLE,
   MOTOR_STATUS_RUNNING,
   MOTOR_STATUS_STOPPED,
   MOTOR_STATUS_ERROR
} Motor_StatusTypeDef;

// 电机方向
typedef enum {
   MOTOR_DIR_CW,
   MOTOR_DIR_CCW
} Motor_DirectionTypeDef;

// 电机控制结构体
typedef struct {
   uint8_t address;
   Motor_StatusTypeDef status;
   Motor_DirectionTypeDef direction;
   uint16_t speed;
   uint16_t acceleration;
   uint32_t position;
} Motor_ControlTypeDef;

// 函数声明
void Motor_Enable(uint8_t address);
void Motor_Disable(uint8_t address);
void Motor_SetSpeed(uint8_t address, Motor_DirectionTypeDef direction, uint16_t speed, uint16_t acceleration);
void Motor_SetPosition(uint8_t address, Motor_DirectionTypeDef direction, uint16_t speed, uint16_t acceleration, uint32_t position);
void Motor_Stop(uint8_t address);
void Motor_Sync(uint8_t address);
void Motor_SetOrigin(uint8_t address);
void Motor_TriggerOrigin(uint8_t address);
uint8_t Motor_ReadStatus(uint8_t address);

#endif /* __EMM42_UART_H */

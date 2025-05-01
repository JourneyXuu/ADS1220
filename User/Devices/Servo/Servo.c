#include "Servo.h"
#include "gpio.h"


float Up_angle = 60;
float Down_angle = 128;
/*
 *@舵机旋转角度0-180度
 *note: 0.5ms（0度）[1%占空比*20000] ~ 2.5ms（180度）[5%占空比]
*/
void Servo(float angle)
{
    //0-200
    //180-1000
    float Compare = 0;
    Compare = angle / 180 * 2000 + 500;

    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, Compare);
}

void Servo_Up(void){Servo(Up_angle);}
void Servo_Down(void){Servo(Down_angle);}

//电磁铁控制
void Magnet_On(void){HAL_GPIO_WritePin(Magnet_GPIO_Port, Magnet_Pin, GPIO_PIN_SET);}
void Magnet_Off(void){HAL_GPIO_WritePin(Magnet_GPIO_Port, Magnet_Pin, GPIO_PIN_RESET);}

//蜂鸣器控制
void Beep_On(void){HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_SET);}
void Beep_Off(void){HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_RESET);}

void LED_Task_On(void){        HAL_GPIO_WritePin(GPIOD, LED_2_Pin, GPIO_PIN_SET);}
void LED_Task_Off(void){       HAL_GPIO_WritePin(GPIOD, LED_2_Pin, GPIO_PIN_RESET);}

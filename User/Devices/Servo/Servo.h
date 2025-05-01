#ifndef __SERVO_H__
#define __SERVO_H__

#include "main.h"
#include "tim.h"

void Servo(float angle);
void Servo_Up(void);
void Servo_Down(void);
void Magnet_On(void);
void Magnet_Off(void);

void LED_Task_On(void);
void LED_Task_Off(void);
#endif





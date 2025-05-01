#include "Control_logic.h"

uint16_t TimeCount = 0;
uint8_t TimeUseFlag = 0;

DelayTimer delayTimer = {0};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim2)//1ms中断
    {
        if(delayTimer.isRunning && delayTimer.counter > 0)
        {
            delayTimer.counter --;
        }
    }
    if(htim == &htim3)//10ms中断
    {

    }
    if(htim == &htim4)
    {
        HAL_GPIO_TogglePin(LED_Board_GPIO_Port, LED_Board_Pin);
   }

}
/*
 *@brief  延时定时器初始化
*/
void Delay_Timer(uint32_t millseconds)
{
    delayTimer.counter = millseconds;
    delayTimer.isRunning = 1;
}

/*
 *@@brief  在while循环中判断延时是否结束
*/
uint8_t checkDelayTimer(void)
{
    if(delayTimer.counter == 0)
    {
        return 1;
    }
    else return 0;
}





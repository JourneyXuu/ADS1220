#include "control.h"
#include "sys.h"  // 添加在调用 osDelay() 的文件顶部
#include "Emm_V5.h"
#include "emm42_uart.h"
#include "Servo.h"
#include "Control_logic.h"


uint16_t velocity = 300;
uint16_t acc = 0;
uint8_t raf = 1;//使用绝对位置模式


void Disable_ALL(void)
{
   Emm_V5_En_Control(1,false,false);  Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_En_Control(2,false,false);  Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_En_Control(3,false,false);  Delay_Timer(10);while(!checkDelayTimer());
}


/*
 *@brief:回零
*/
void control_to_zero(void)
{
   Emm_V5_Pos_Control(1, 0, velocity, acc, 0, raf, 1); Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_Pos_Control(2, 1, velocity, acc, 0, raf, 1); Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_Pos_Control(3, 1, velocity, acc, 0, raf, 1); Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_Synchronous_motion(0); Delay_Timer(10);while(!checkDelayTimer());// 广播地址0触发
}

/*
 *@brief:记忆回零位置
*/
void Remembei_Zero(void) 
{
   Emm_V5_Reset_CurPos_To_Zero(01);Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_Reset_CurPos_To_Zero(02);Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_Reset_CurPos_To_Zero(03);Delay_Timer(10);while(!checkDelayTimer());
}


/*  
*@brief: 控制三电机运动x,y三轴
*note:   电机1、2控制x方向，电机3控制y方向
*@param: x_distance:    电机1、2运动距离
*@param: dir_X:         电机1、2运动方向 
*@param: y_distance:    电机3运动距离
*@param: dir_y:         电机3运动方向
*note:如果发送失败则重新发送命令
*/
void control_t(uint32_t x_distance,uint32_t y_distance)
{
   Emm_V5_Pos_Control(1, 0, velocity, acc, x_distance, raf, 1); Delay_Timer(10);while(!checkDelayTimer());// 多机同步标志位置1
   Emm_V5_Pos_Control(2, 1, velocity, acc, x_distance, raf, 1); Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_Pos_Control(3, 1, velocity, acc, y_distance, raf, 1); Delay_Timer(10);while(!checkDelayTimer());
   Emm_V5_Synchronous_motion(0); 
}

/*
 *@brief:使能三电机
*/
void EmmEN_Init(void)
{
   Emm_V5_En_Control(1,true,false);  Delay_Timer(10);while(!checkDelayTimer());//电机1使能，关闭多机同步 
   Emm_V5_En_Control(2,true,false);  Delay_Timer(10);while(!checkDelayTimer());//电机2使能
   Emm_V5_En_Control(3,true,false);  Delay_Timer(10);while(!checkDelayTimer());//电机3使能
}

/*单个电机的测试标志位*/
//  #define TestMotor1 
// #define TestMotor2 
// #define TestMotor3 
// #define TestMultiMotor 
// #define TestServo
// #define TestMagnet 
#define TestChess
// #define TestChessToBoard
/*
*@brief：控制三地址电机多机同步
*@note：电机1、2控制x方向，电机3控制y方向
*@param: 
*@return:none
*/
void Emm_Test(void)
{
   control_to_zero();//上电必须回零，记得断电前也重新回零


   // uint8_t rxCount = 0;
   // float test_speed = 1500.f;
   // uint8_t test_raf = 0; //0为相对位置，1为绝对位置

/* 不启用多机标志，单独测试单个电机*/
   #ifdef TestMotor1
   Emm_V5_En_Control(1,true,false);delay_ms(10);//电机1使能，关闭多机同步
   Emm_V5_Vel_Control(1, 0, 1000, 10, 0);delay_ms(10);//速度模式：方向CW，速度1000RPM，加速度10
   delay_ms(500);
   Emm_V5_Vel_Control(1, 0, 0, 10, 0);delay_ms(10);//速度模式：方向CW，速度1000RPM，加速度10

   #endif

   #ifdef TestMotor2
   Emm_V5_En_Control(2,true,false);delay_ms(10);//电机2使能，关闭多机同步
   Emm_V5_Vel_Control(2, 0, 1000, 10, 0);delay_ms(10);//速度模式：方向CW，速度1000RPM，加速度10
   delay_ms(500);
   Emm_V5_Vel_Control(2, 0, 0, 10, 0);delay_ms(10);//速度模式：方向CW，速度1000RPM，加速度10

   #endif

   #ifdef TestMotor3
   Emm_V5_En_Control(3,true,false);delay_ms(10);//电机3使能，关闭多机同步
   Emm_V5_Vel_Control(3, 0, 1000, 10, 0);delay_ms(10);//速度模式：方向CW，速度1000RPM，加速度10
   delay_ms(500);
   Emm_V5_Vel_Control(3, 0, 0, 10, 0);delay_ms(10);//速度模式：方向CW，速度1000RPM，加速度10

   #endif

/* 启用多机标志*/
   #ifdef TestMultiMotor
   Emm_V5_En_Control(1,true,true);  delay_ms(10);//电机1使能，开启多机同步 
   Emm_V5_En_Control(2,true,true);  delay_ms(10);//电机2使能，开启多机同步
   Emm_V5_En_Control(3,true,true);  delay_ms(10);//电机3使能，开启多机同步
   //位置模式，方向CW，速度1000RPM，加速度0（不使用加减速直接启动），脉冲数3200（16细分下发送3200个脉冲电机转一圈），相对运动
   Emm_V5_Pos_Control(1, 0, 1000, 50, 3200, 0, 1); delay_ms(10);// 多机同步标志位置1
   Emm_V5_Pos_Control(2, 0, 1000, 50, 3200, 0, 1); delay_ms(10);// 多机同步标志位置1
   Emm_V5_Pos_Control(3, 0, 1000, 50, 3200, 0, 1); delay_ms(10);// 多机同步标志位置1
   Emm_V5_Synchronous_motion(0); delay_ms(10);// 广播地址0触发
   #endif

   #ifdef TestServo
   Servo_Down();
   // delay_ms(1000);
   // Servo_Up();
   // delay_ms(1000);
   #endif

   #ifdef TestMagnet
   Magnet_On();
   #endif


   #ifdef TestChess 
   /*10个棋子点*/
	// EmmEN_Init();
   // delay_ms(1000);
   // Servo_Up();
   // delay_ms(1000);

	// control_t(chess_position[0].x,chess_position[0].y);
   // control_t(chess_position[1].x,chess_position[1].y);
   // control_t(chess_position[2].x,chess_position[2].y);
   // control_t(chess_position[3].x,chess_position[3].y);
   // control_t(chess_position[4].x,chess_position[4].y);
   // control_t(chess_position[5].x,chess_position[5].y);
   // control_t(chess_position[6].x,chess_position[6].y);
   // control_t(chess_position[7].x,chess_position[7].y);
   // control_t(chess_position[8].x,chess_position[8].y);
   // control_t(chess_position[9].x,chess_position[9].y);

   /*9个棋盘点*/
   // control_t(board_position[0].x,board_position[0].y);
   // control_t(board_position[1].x,board_position[1].y);
   // control_t(board_position[2].x,board_position[2].y);
   // control_t(board_position[3].x,board_position[3].y);
   // control_t(board_position[4].x,board_position[4].y);
   // control_t(board_position[5].x,board_position[5].y);
   // control_t(board_position[6].x,board_position[6].y);
   // control_t(board_position[7].x,board_position[7].y);
   // control_t(board_position[8].x,board_position[8].y);
   
   /*旋转9个棋盘点*/
   // control_t(board_rotate_position[0].x,board_rotate_position[0].y);
   // control_t(board_rotate_position[1].x,board_rotate_position[1].y);
   // control_t(board_rotate_position[2].x,board_rotate_position[2].y);
   // control_t(board_rotate_position[3].x,board_rotate_position[3].y);
   // control_t(board_rotate_position[4].x,board_rotate_position[4].y);
   // control_t(board_rotate_position[5].x,board_rotate_position[5].y);
   // control_t(board_rotate_position[6].x,board_rotate_position[6].y);
   // control_t(board_rotate_position[7].x,board_rotate_position[7].y);
   // control_t(board_rotate_position[8].x,board_rotate_position[8].y);

   // Place_Chess(1,1);
   // Return_Chess(1,9);

   #endif

   #ifdef TestChessToBoard
   // Emm_V5_En_Control(03,false,false);//失能电机3
   // Emm_V5_Origin_Set_O(03,true);//电机3记忆棋盘位置
   Place_Chess(1,1);
   #endif




}

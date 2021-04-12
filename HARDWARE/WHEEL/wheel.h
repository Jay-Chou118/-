#ifndef __WHEEL
    #define __WHEEL
//控制轮子的定时器
#include "sys.h"

#define Forward_RightUp    TIM9->CCR1   //TIM9->CCR1
#define Retreat_RightUp    TIM9->CCR2   //TIM9->CCR2

#define Forward_RightDown  TIM4->CCR3	//TIM4->CCR3
#define Retreat_RightDown  TIM4->CCR4	//TIM4->CCR4

#define Forward_LeftUp     TIM4->CCR2  
#define Retreat_LeftUp     TIM4->CCR1

#define Forward_LeftDown   TIM5->CCR3   //TIM5->CCR3
#define Retreat_LeftDown   TIM5->CCR4   //TIM5->CCR4
//控制轮子的定时器
void go_forward(int speed,int to_time);
void go_rear(int speed,int to_time);
void go_left(int speed,int to_time);
void go_right(int speed,int to_time);
void go_clockwise(int speed,int to_time);
void MotorDrive_GPIO_Config(void);
void go_counter_clockwise(int speed,int to_time);
void go_ward(u8 kk,int speed,int to_time);
void go_squint(int speed,int to_time);
void go_forward_laser(int speed,int to_stop);
void set_moto (int  speed,int cut);
void motor(u8 kk,int pwm_l,int pwm_r);
#endif





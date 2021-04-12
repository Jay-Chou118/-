#ifndef _DATA_TYPE_H
#define _DATA_TYPE_H
#include "sys.h"


#define MODE_FORWARD 1
#define MODE_RETREAT 2
#define MODE_RIGHT   3
#define MODE_LEFT    4
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define USART_REC_LEN2  			200  	//定义最大接收字节数 200
#define USART2_MAX_SEND_LEN		200					//最大发送缓存字节数
#define REAR 0xaa
#define FORWARD 0x55
#define LEFT 0x96
#define RIGHT 0x69
#define RECLOCKWISE 0xa5
#define CLOCKWISE 0x5a
#define SPEED_BASE 200//轮子基础运转参数
#define SPEED_LOW 100//慢速pwm
#define SPEED_MINI 500//中速pwm
#define TURN_CLK 950//旋转延时

#define STEERINGENGINE1 TIM2->CCR1//爪子的马达
#define STEERINGENGINE2 TIM2->CCR2
#define SteeringEngine_Grap   TIM12->CCR1
#define SteeringEngine_Rotary TIM12->CCR1
#define STEERINGENGINE3 TIM3->CCR1
#define STEERINGENGINE4 TIM3->CCR2
typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelSpeed_Type;  // 轮子速度。




typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelDeadSpace_Type; //反转死区时间

typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelCircleCount_Type; // 编码器圈速

typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelFlag_Type; // 轮子运动状态

typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelLastFlag_Type; // 轮子上次运动状态


typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
    int Stop;
} DeadTimer_Type; // 死区

typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
    int Stop;
} DeadTimerFlag_Type; // 死区


typedef struct
{
    float Distance1;
    float Distance2;
    int Flag;
    int Timer;
} HC_sr04_Type; //  超声波

typedef struct
{
    int X;
    int Y;
} WedgeColor_Type; // 物块坐标

typedef struct
{
    int X;
    int Y;
    int State;

} CurrentCoord_Type; // 当前坐标

typedef struct
{
    int Timer;
    int Flag;
    int Ready;
} DRV8825_Type; //   步进电机

typedef struct
{
    int Light1;
    int Light2;
    int Light3;
    int Light4;
    int Light5;
    int Light6;
    int Light7;
} InfaredTube_Type; //   红外对管

typedef struct
{
    int X;
    int Y;
    int Flag_X;
    int Flag_Y;
} CoordVariasionFlag_Type; //   步进电机


typedef struct
{
    int Grap;
    int Rotary;
    int Screw;
    int Grap_Flag;
    int Rotary_Flag;
    int Screw_Flag;

} SteeringEngineSpeed_Type; // 舵机运动速度

typedef struct
{
    int ForwardRightUp;
    int ForwardRightDown;
    int ForwardLeftUp;
    int ForwardLeftDown;
    int RetreatRightUp;
    int RetreatRightDown;
    int RetreatLeftUp;
    int RetreatLeftDown;
} WheelSpeedTIM_Type;  // 轮子速度。


typedef struct
{
    int Steeringgenine1;
    int Steeringgenine2;
    int Steeringgenine3;
    int Steeringgenine4;

} SteeringGenine_Type;  // 舵机PWM



enum PID_MODE
{
    PID_INC = 0,    //增量式
    PID_POS,        //位置式
};


typedef struct PID 
{ 
	int16_t  SetPoint;               //设定目标 Desired Value 	 
	int32_t  SumError;               //误差累计  	 
	float    Proportion;          //比例常数 Proportional Const 	 
	float    Integral;            //积分常数 Integral Const 	 
	float    Derivative;          //微分常数 Derivative Const 	  
	int16_t  LastError;               //Error[-1]  
	int16_t  PrevError;               //Error[-2] 
} PID; 



#endif




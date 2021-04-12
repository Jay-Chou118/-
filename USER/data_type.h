#ifndef _DATA_TYPE_H
#define _DATA_TYPE_H
#include "sys.h"


#define MODE_FORWARD 1
#define MODE_RETREAT 2
#define MODE_RIGHT   3
#define MODE_LEFT    4
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define USART_REC_LEN2  			200  	//�����������ֽ��� 200
#define USART2_MAX_SEND_LEN		200					//����ͻ����ֽ���
#define REAR 0xaa
#define FORWARD 0x55
#define LEFT 0x96
#define RIGHT 0x69
#define RECLOCKWISE 0xa5
#define CLOCKWISE 0x5a
#define SPEED_BASE 200//���ӻ�����ת����
#define SPEED_LOW 100//����pwm
#define SPEED_MINI 500//����pwm
#define TURN_CLK 950//��ת��ʱ

#define STEERINGENGINE1 TIM2->CCR1//צ�ӵ����
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
} WheelSpeed_Type;  // �����ٶȡ�




typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelDeadSpace_Type; //��ת����ʱ��

typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelCircleCount_Type; // ������Ȧ��

typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelFlag_Type; // �����˶�״̬

typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
} WheelLastFlag_Type; // �����ϴ��˶�״̬


typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
    int Stop;
} DeadTimer_Type; // ����

typedef struct
{
    int RightUp;
    int RightDown;
    int LeftUp;
    int LeftDown;
    int Stop;
} DeadTimerFlag_Type; // ����


typedef struct
{
    float Distance1;
    float Distance2;
    int Flag;
    int Timer;
} HC_sr04_Type; //  ������

typedef struct
{
    int X;
    int Y;
} WedgeColor_Type; // �������

typedef struct
{
    int X;
    int Y;
    int State;

} CurrentCoord_Type; // ��ǰ����

typedef struct
{
    int Timer;
    int Flag;
    int Ready;
} DRV8825_Type; //   �������

typedef struct
{
    int Light1;
    int Light2;
    int Light3;
    int Light4;
    int Light5;
    int Light6;
    int Light7;
} InfaredTube_Type; //   ����Թ�

typedef struct
{
    int X;
    int Y;
    int Flag_X;
    int Flag_Y;
} CoordVariasionFlag_Type; //   �������


typedef struct
{
    int Grap;
    int Rotary;
    int Screw;
    int Grap_Flag;
    int Rotary_Flag;
    int Screw_Flag;

} SteeringEngineSpeed_Type; // ����˶��ٶ�

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
} WheelSpeedTIM_Type;  // �����ٶȡ�


typedef struct
{
    int Steeringgenine1;
    int Steeringgenine2;
    int Steeringgenine3;
    int Steeringgenine4;

} SteeringGenine_Type;  // ���PWM



enum PID_MODE
{
    PID_INC = 0,    //����ʽ
    PID_POS,        //λ��ʽ
};


typedef struct PID 
{ 
	int16_t  SetPoint;               //�趨Ŀ�� Desired Value 	 
	int32_t  SumError;               //����ۼ�  	 
	float    Proportion;          //�������� Proportional Const 	 
	float    Integral;            //���ֳ��� Integral Const 	 
	float    Derivative;          //΢�ֳ��� Derivative Const 	  
	int16_t  LastError;               //Error[-1]  
	int16_t  PrevError;               //Error[-2] 
} PID; 



#endif




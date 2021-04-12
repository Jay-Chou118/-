#include "data_type.h"
#include "sys.h"
u8 data_send[4]={0xaa,0x55,0x01,0x03,};//发送数据，开启openmv通信
char colors[3]={0,0,0};

u8 key_flag=0;
HC_sr04_Type Hc_sr04 = {50, 50, 0, 0}; // 定义超声波变量
int data[14];
int SportState  = 0;
int CurrentVariasion_X;
int CurrentVariasion_Y;
int left_red=0;//左边的红外灯亮的位置
int right_red=0;//右边的红外灯亮的位置
int forward_red=0;//前面的红外灯亮的位置
int QR_FIST=0;
int QR_NEXT=0;
int QR_FIST2=0;
int QR_NEXT2=0;
int QR_FIST3=0;
int QR_NEXT3=0;
//int temp=0;
//int temp_next=0;


int x_poor=0;
u8 line_mode=0;

WedgeColor_Type Wedge_Reg	     = {3, 7};
WedgeColor_Type Wedge_Blue	     = {5, 7};
WedgeColor_Type Wedge_Green	     = {7, 7};
WedgeColor_Type Ready_Point		 = {2, 6};  // 测试点
CurrentCoord_Type CurrentCoord   = {8, 0, 0};
WedgeColor_Type ObjectiveTable = {3, 1};

InfaredTube_Type InfaredTube_X_F = {0, 0, 0, 0, 0, 0, 0};		//红外对管
InfaredTube_Type InfaredTube_X_R = {0, 0, 0, 0, 0, 0, 0};
InfaredTube_Type InfaredTube_Y = {0, 0, 0, 0, 0, 0, 0};
CoordVariasionFlag_Type CoordVariasionFlag = {1, 1, 1, 1};
SteeringEngineSpeed_Type SteeringEngineSpeed = {1, 1, 1, 1, 1, 1};
DeadTimerFlag_Type DeadTimerFlag   = {0, 0, 0, 0, 0};
DeadTimer_Type     DeadTimer       = {0, 0, 0, 0, 0};
WheelSpeedTIM_Type WheelSpeedTIM = {0, 0, 0, 0, 0, 0, 0, 0}; // 速度 过度值
WheelSpeedTIM_Type WheelSpeedCurrent = {0, 0, 0, 0, 0, 0}; // 当前速度
SteeringGenine_Type Steeringgenine_Current = {0, 0, 0, 0};		//舵机当前值
SteeringGenine_Type Steeringgenine_Expect = {0, 0, 0, 0}; //舵机期望值
int Steering_Test[4] = {1600, 1500, 0, 500};
u16 USART_RX_STA = 0;     //接收状态标记
u16 USART2_RX_STA = 0;
u8 USART_RX_BUF[USART_REC_LEN];
u8 USART2_RX_BUF[USART_REC_LEN2];
u8 color=0;

int Steering_Flag = 0;
int Steering_Time = 0;
int Steering_Mode = 0;
int DeadFlagCoefficence_X = 1;
int DeadFlagCoefficence_Y = 1;
WheelDeadSpace_Type WheelDeadSpace = {0, 0, 0, 0};
int Light_X = 0, Unlight_X = 0;
int Light_Y = 0, Unlight_Y = 0;
int Coord_X_Flag = 0;
__align(8) u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	//发送缓冲,最大USART3_MAX_SEND_LEN字节//对齐，确保发送不乱码
WheelSpeed_Type WheelSpeed = {0, 0, 0, 0}; //初始化轮子速度
int run_flag;
//int F_B_NUM[4]={0,2100,4300,6300};//前进和后退的延时，pwm=100
int F_B_NUM[6]={0,40,70,100,140,170};//前进和后退的延时，pwm=500
int L_R_NUM[4]={0,2100,4300,6300};//前进和后退的延时，pwm=100

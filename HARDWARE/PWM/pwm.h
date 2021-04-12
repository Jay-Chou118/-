#ifndef __PWM
#define __PWM
#include "sys.h"
#define PWM3   TIM2->CCR1  //第三个舵机
#define PWM2   TIM2->CCR2  //第二个舵机
#define PWM4   TIM3->CCR1  //第四个舵机   
/*
以上三个舵机，全部减小才可以往外伸。
						 增大往回缩。
*/
#define PWM1   TIM3->CCR2  //第一个舵机   张开增大，闭合减小。

#define PWM5   TIM1->CCR1  //第五个舵机	顺时针减小，逆时针增大。
#define  CLOSE  1650
#define  OPEN  2000
#define POINT1 2210
#define POINT2 1650
#define POINT3 980
#define POINT4 4250
#define Scan 3700
#define GETPOINTL 5000
#define GETPOINTR 3700
void TIM5_PWM_Init(u32 arr,u32 psc);
void TIM4_PWM_Init(u32 arr,u32 psc);
void TIM9_PWM_Init(u32 arr,u32 psc);
//void TIM12_PWM_Init(u32 arr,u32 psc);
//void TIM8_PWM_Init(u32 arr,u32 psc);
//void TIM1_PWM_Init(u32 arr,u32 psc);
void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM2_PWM_Init(u32 arr,u32 psc);
void TIM1_PWM_Init(u32 arr,u32 psc);
void Servo_set(int a,int b,int c,int d,int e);

void Scan_QR(void);

void PUT1(void);
void PUT2(void);
void PUT3(void);

void GETRED_up1(void);//夹上层
void GETRED_up2(void);
void GETRED_up3(void);
void GETGREEN_up1(void);
void GETGREEN_up2(void);
void GETGREEN_up3(void);
void GETBLUE_up1(void);
void GETBLUE_up2(void);
void GETBLUE_up3(void);

void GETRED_down1(void);//夹下层
void GETRED_down2(void);
void GETRED_down3(void);
void GETGREEN_down1(void);
void GETGREEN_down2(void);
void GETGREEN_down3(void);
void GETBLUE_down1(void);
void GETBLUE_down2(void);
void GETBLUE_down3(void);

void PUTRED_floor(void);//放地上
void PUTGREEN_floor(void);
void PUTBLUE_floor(void);

void GETRED_floor(void);//从地上夹起
void GETGREEN_floor(void);
void GETBLUE_floor(void);

void PUTRED_up(void);//放在载物台上
void PUTGREEN_up(void);
void PUTBLUE_up(void);

void PUTRED_down(void);//最后放在地上
void PUTGREEN_down(void);
void PUTBLUE_down(void);	

#endif





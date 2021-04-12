#ifndef __PWM
#define __PWM
#include "sys.h"
#define PWM3   TIM2->CCR1  //���������
#define PWM2   TIM2->CCR2  //�ڶ������
#define PWM4   TIM3->CCR1  //���ĸ����   
/*
�������������ȫ����С�ſ��������졣
						 ������������
*/
#define PWM1   TIM3->CCR2  //��һ�����   �ſ����󣬱պϼ�С��

#define PWM5   TIM1->CCR1  //��������	˳ʱ���С����ʱ������
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

void GETRED_up1(void);//���ϲ�
void GETRED_up2(void);
void GETRED_up3(void);
void GETGREEN_up1(void);
void GETGREEN_up2(void);
void GETGREEN_up3(void);
void GETBLUE_up1(void);
void GETBLUE_up2(void);
void GETBLUE_up3(void);

void GETRED_down1(void);//���²�
void GETRED_down2(void);
void GETRED_down3(void);
void GETGREEN_down1(void);
void GETGREEN_down2(void);
void GETGREEN_down3(void);
void GETBLUE_down1(void);
void GETBLUE_down2(void);
void GETBLUE_down3(void);

void PUTRED_floor(void);//�ŵ���
void PUTGREEN_floor(void);
void PUTBLUE_floor(void);

void GETRED_floor(void);//�ӵ��ϼ���
void GETGREEN_floor(void);
void GETBLUE_floor(void);

void PUTRED_up(void);//��������̨��
void PUTGREEN_up(void);
void PUTBLUE_up(void);

void PUTRED_down(void);//�����ڵ���
void PUTGREEN_down(void);
void PUTBLUE_down(void);	

#endif





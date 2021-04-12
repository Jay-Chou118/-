#include "pwm.h"
#include "sys.h"
#include "delay.h"
#include "wheel.h"
#include "data_type.h"
#include "location.h"


#define PWM3   TIM2->CCR1  //���������
#define PWM2   TIM2->CCR2  //�ڶ������
#define PWM4   TIM3->CCR1  //���ĸ���� 
#define PWM1   TIM3->CCR2  //��һ�����
#define PWM5   TIM1->CCR1  //��������	

int Servo1=2000;				//���1�Ƕ�
int Servo2=2200;				//���2�Ƕ�
int Servo3=2100;				//���3�Ƕ�
int Servo4=1600;				//���4�Ƕ�
int Servo5=4250;				//���5�Ƕ�PWM1=750;PWM2=260;PWM3=750 ;PWM4=250;PWM5=800;delay_ms(999);

void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM1ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTFʱ��	
		
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOD,&GPIO_InitStructure);              //��ʼ��PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
		
		//��ʼ��TIM4 Channel PWMģʽ	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1		
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1
		
		TIM_CtrlPWMOutputs(TIM4,ENABLE);
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM14
 
										  
}

void TIM9_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM1ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTFʱ��	
		
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
		
		//��ʼ��TIM4 Channel PWMģʽ	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1
		TIM_OC2Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1
		
		TIM_CtrlPWMOutputs(TIM9,ENABLE);
	
	TIM_Cmd(TIM9, ENABLE);  //ʹ��TIM14
										  
}

//PA0��PA1�Ѿ���ʹ���ˣ�����ֻ����2��3
void TIM5_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM1ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
		
		//��ʼ��TIM4 Channel PWMģʽ	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //
		TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //
		
		TIM_CtrlPWMOutputs(TIM5,ENABLE);
	
	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM14
										  
}


void TIM2_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM1ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
		
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
		
		//��ʼ��TIM4 Channel PWMģʽ	 
		TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1

		
		TIM_CtrlPWMOutputs(TIM2,ENABLE);

		TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM14
	 TIM2->CCR1  =  Servo3;					//��3�����
		 TIM2->CCR2  = Servo2;		//��2�����
//	 TIM2->CCR1  =  2000;					//��3�����
//		 TIM2->CCR2  = 1700;		//��2�����
 		
}

void TIM3_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM1ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
		
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
		
		//��ʼ��TIM4 Channel PWMģʽ	 
		TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1

		
		TIM_CtrlPWMOutputs(TIM3,ENABLE);
	
		TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM14
 
		 TIM3->CCR1  =  Servo4;					//��4�������
		 TIM3->CCR2  = Servo1;		//��1�����
// TIM3->CCR1  =  1800;					//��4�������
//		 TIM3->CCR2  = Servo1;		//��1�����
}
void TIM1_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTFʱ��	
		
		
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
		
		//��ʼ��TIM4 Channel PWMģʽ	 
		TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 4OC1
		

		
		TIM_CtrlPWMOutputs(TIM1,ENABLE);

		TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM14
			 TIM1->CCR1  = Servo5;	//��5�����
//					 TIM1->CCR1  = 3600;	//��5�����
}	 
void Servo_set(int a,int b,int c,int d,int e)
{
	while(1)
	{
		if(Servo1==a&&Servo2==b&&Servo3==c&&Servo4==d&&Servo5==e)
			break;
		else
		{
			if(Servo1<a)
				PWM1=Servo1++;
			if(Servo1>a)
				PWM1=Servo1--;
			
			if(Servo2<b)
				PWM2=Servo2++;
			if(Servo2>b)
				PWM2=Servo2--;
			
			if(Servo3<c)
				PWM3=Servo3++;
			if(Servo3>c)
				PWM3=Servo3--;
			
			if(Servo4<d)
				PWM4=Servo4++;
			if(Servo4>d)
				PWM4=Servo4--;
			
			if(Servo5<e)
				Servo5=Servo5+5;
				PWM5=Servo5;
			if(Servo5>e)
				Servo5=Servo5-5;
				PWM5=Servo5;
		}
		delay_ms(1);	delay_us(500);
	}
	delay_ms(50);
}



void Scan_QR()
{
	Servo_set(OPEN,2300,2300,1450,Scan);
	
}

void PUT1(void)
{
  Servo_set(CLOSE,2500,2050,1800,POINT4);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2500,2050,1800,POINT1);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2300,2050,1500,POINT1);	//�½�
  Servo_set(OPEN,2300,2050,1500,POINT1);	delay_ms(1000);//�ſ�
	Servo_set(OPEN,2500,2050,1800,POINT1);	delay_ms(1000);//��߻�е��
	Servo_set(OPEN,2500,2050,1800,POINT4);//ת����̬
  Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬

}

void PUT2(void)
{
	Servo_set(CLOSE,2300,2050,1600,POINT4);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2300,2050,1750,POINT2);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2300,2050,1400,POINT2);	delay_ms(1000);//�½�
	Servo_set(CLOSE,2300,2050,1500,POINT2);	delay_ms(1000);//
  Servo_set(OPEN,2300,2050,1500,POINT2);	delay_ms(1000);//�ſ�
	Servo_set(OPEN,2300,2050,1750,POINT2);	delay_ms(1000);//��߻�е��
	Servo_set(OPEN,2300,2050,1750,POINT4);//ת����̬
  Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬
}

void PUT3(void)
{    
	   Servo_set(CLOSE,2300,2050,1600,POINT4);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2300,2050,1750,POINT3);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2300,2050,1400,POINT3);	//�½�
	  Servo_set(CLOSE,2350,2050,1500,POINT3);	delay_ms(1000);//xiajiAN
  Servo_set(OPEN,2350,2050,1500,POINT3);	delay_ms(1000);//�ſ�
	Servo_set(OPEN,2500,2050,1750,POINT3);	delay_ms(1000);//��߻�е��
	Servo_set(OPEN,2400,1950,1700,POINT4);//ת����̬
  Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬
}
void GETRED_up1(void)//���ϲ��  //���Գ����м�
{
  Servo_set(OPEN,2050,2050,1400,GETPOINTR);	delay_ms(1000);//���
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2050,2050,1400,GETPOINTR);	//�պ�צ��
	go_ward(REAR,300,630);
	back_center_lap();
	PUT1();
}

void GETRED_up2(void)
{
  Servo_set(OPEN,2100,2200,1600,POINT4);	delay_ms(1000);//���
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2100,2200,1600,POINT4);	//�պ�צ��
	go_ward(REAR,300,630);
	back_center_lap();
	   PUT1();
}
void GETRED_up3(void)
{
   Servo_set(OPEN,2050,2050,1400,GETPOINTL);	delay_ms(1000);//�б�״̬
	   go_forward_laser(300,60);
	   back_center_lap();
  	 Servo_set(CLOSE,2050,2050,1400,GETPOINTL);	//�պ�צ��
	   go_ward(REAR,300,600);
	   back_center_lap();
	   PUT1();
}
void GETGREEN_up1(void)
{
  Servo_set(OPEN,2050,2050,1400,GETPOINTR);	delay_ms(1000);//���
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2050,2050,1400,GETPOINTR);	//�պ�צ��
	go_ward(REAR,300,630);
	back_center_lap();
     PUT2();
}
void GETGREEN_up2(void)
{
     Servo_set(OPEN,2100,2200,1600,POINT4);	delay_ms(1000);//���
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2100,2200,1600,POINT4);	//�պ�צ��
	go_ward(REAR,300,630);
	back_center_lap();
	   PUT2();
}
void GETGREEN_up3(void)
{
     Servo_set(OPEN,2050,2050,1400,GETPOINTL);	delay_ms(1000);//�б�״̬
	   go_forward_laser(300,60);
	   back_center_lap();
  	 Servo_set(CLOSE,2050,2050,1400,GETPOINTL);	//�պ�צ��
	   go_ward(REAR,300,600);
	   back_center_lap();
	   PUT2();

}
void GETBLUE_up1(void)
{
    Servo_set(OPEN,2050,2050,1400,GETPOINTR);	delay_ms(1000);//���
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2050,2050,1400,GETPOINTR);	//�պ�צ��
	go_ward(REAR,300,630);
	back_center_lap();
     PUT3();
}
void GETBLUE_up2(void)
{
    Servo_set(OPEN,2100,2200,1600,POINT4);	delay_ms(1000);//���
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2100,2200,1600,POINT4);	//�պ�צ��
	go_ward(REAR,300,630);
	back_center_lap();
	   PUT3();
}
void GETBLUE_up3(void)
{
    Servo_set(2050,2050,1900,1400,GETPOINTL);	delay_ms(1000);//�б�״̬
	   go_forward_laser(300,60);
	   back_center_lap();
  	 Servo_set(CLOSE,2050,2050,1400,GETPOINTL);	//�պ�צ��
	   go_ward(REAR,300,600);
	   back_center_lap();
	   PUT3();

}

void GETRED_down1(void)//���²�
{
     Servo_set(OPEN,1540,2250,1110,3850);	delay_ms(1000);//���
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,3850);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT1();
}

void GETRED_down2(void)
{
     Servo_set(OPEN,1550,2250,1110,POINT4);	delay_ms(1000);//���
	   go_forward_laser(200,80);
	   Servo_set(CLOSE,1550,2250,1110,POINT4);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT1();
}
void GETRED_down3(void)
{
     Servo_set(OPEN,1540,2250,1110,4850);	delay_ms(1000);//���
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,4850);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT1();
}
void GETGREEN_down1(void)
{
  Servo_set(OPEN,1540,2250,1110,3850);	delay_ms(1000);//���
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,3850);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT2();
}

void GETGREEN_down2(void)
{
     Servo_set(OPEN,1550,2250,1110,POINT4);	delay_ms(1000);//���
	   go_forward_laser(200,80);
	   Servo_set(CLOSE,1550,2250,1110,POINT4);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT2();
}
void GETGREEN_down3(void)
{ 
     Servo_set(OPEN,1540,2250,1110,4850);	delay_ms(1000);//���
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,4850);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT2();

}

void GETBLUE_down1(void)
{
  Servo_set(OPEN,1540,2250,1110,3850);	delay_ms(1000);//���
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,3850);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT3();
}
void GETBLUE_down2(void)
{
     Servo_set(OPEN,1550,2250,1110,POINT4);	delay_ms(1000);//���
	   go_forward_laser(200,80);
	   Servo_set(CLOSE,1550,2250,1110,POINT4);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT3();

}
void GETBLUE_down3(void)
{
     Servo_set(2100,1540,2250,1110,4850);	delay_ms(1000);//���
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,4850);	delay_ms(1000);//�պ�
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT3();
}

void PUTRED_floor(void)//�ŵ���
{
	Servo_set(OPEN,2500,1950,1700,POINT1);	delay_ms(1000);//ת����һ��λ�õ��Ͽ�
	
	Servo_set(OPEN,2500,1900,1450,POINT1);	delay_ms(1000);//�½�
  Servo_set(CLOSE,2500,1900,1450,POINT1);	delay_ms(1000);//�պ�צ��
	Servo_set(CLOSE,2500,1950,1700,POINT1);	delay_ms(1000);//��߻�е��
	Servo_set(CLOSE,1900,1950,1700,4250);	delay_ms(1000);//ת���ŵĵ�3��λ�õ��Ͽ�+ת��
	Servo_set(CLOSE,1750,2420,1200,4250);	delay_ms(1000);//���»�е��
 	Servo_set(OPEN,1750,2420,1200,4250);	delay_ms(1000);//�ſ�צ��	//�ſ�צ��
	go_ward(REAR,300,300);
	Servo_set(OPEN,2250,1950,1300,POINT4);delay_ms(5);
	go_forward_laser(300,30);
	back_center_lap();


}
void PUTGREEN_floor(void)
{
 		Servo_set(OPEN,2300,2050,1600,POINT4);	delay_ms(1000);//ת����3��λ�õ��Ͽ�
  Servo_set(OPEN,2300,2050,1750,POINT2);	delay_ms(1000);//
	Servo_set(OPEN,2450,1950,1400,POINT2);	//�½�
	
  Servo_set(CLOSE,2450,1950,1400,POINT2);	delay_ms(1000);//�ſ�
  Servo_set(CLOSE,2300,2050,1750,POINT2);	delay_ms(1000);//�պ�צ��

	Servo_set(CLOSE,2300,2050,1750,POINT4);	delay_ms(1000);//ת����̬����
		Servo_set(CLOSE,2100,2200,1600,POINT4);	delay_ms(1000);//ת����̬����
	Servo_set(CLOSE,1900,2000,1050,GETPOINTR);delay_ms(1000);
	 
	Servo_set(OPEN,1900,2000,1050,GETPOINTR);delay_ms(1000);//�ſ�צ��
	 	 
	Servo_set(OPEN,2000,2100,1500,GETPOINTR);
	Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬  
	
	
}
void PUTBLUE_floor(void)
{

	Servo_set(OPEN,2500,1950,1700,POINT3);	delay_ms(1000);//ת����һ��λ�õ��Ͽ�
	
	Servo_set(OPEN,2500,1900,1450,POINT3);	delay_ms(1000);//�½�
  Servo_set(CLOSE,2500,1900,1450,POINT3);	delay_ms(1000);//�պ�צ��
	Servo_set(CLOSE,2500,1950,1700,POINT3);	delay_ms(1000);//��߻�е��
	Servo_set(CLOSE,2500,1950,1700,4900);	delay_ms(1000);//ת���ŵĵ�3��λ�õ��Ͽ�+ת��
	Servo_set(CLOSE,1900,2000,1050,4900);delay_ms(1000);
	 
	Servo_set(OPEN,1900,2000,1050,4900);delay_ms(1000);//�ſ�צ��
	 	 
	Servo_set(OPEN,2000,2100,1500,4900);
	Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬  


}
void GETRED_floor(void)//�ӵ��ϼ���
{
	go_ward(REAR,300,300);
Servo_set(OPEN,1750,2420,1200,POINT4);	delay_ms(1000);
	go_forward_laser(300,20);
	back_center_lap();
  Servo_set(CLOSE,1750,2420,1200,POINT4);	//�պ�צ��
  Servo_set(CLOSE,2500,2050,1800,POINT4);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2500,2050,1800,POINT1);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2400,2050,1500,POINT1);	//�½�
  Servo_set(OPEN,2400,2050,1500,POINT1);	delay_ms(1000);//�ſ�
	Servo_set(OPEN,2500,2050,1800,POINT1);	delay_ms(1000);//��߻�е��
	Servo_set(OPEN,2500,2050,1800,POINT4);//ת����̬
  Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬
	

}

void GETGREEN_floor(void)
{
		go_ward(REAR,300,300);
  Servo_set(2200,1900,2000,1050,3700);	delay_ms(5);//ת����̬����

	go_forward_laser(300,20);
	back_center_lap();
  Servo_set(CLOSE,1900,2000,1050,3700);	//�պ�צ��
	  PUT2();

}
void GETBLUE_floor(void)
{
	go_ward(REAR,300,300);
 Servo_set(OPEN,1900,2000,1050,4900);delay_ms(1000);//�ſ�צ��//ת����̬����
	go_forward_laser(300,20);
	back_center_lap();
 Servo_set(CLOSE,1900,2000,1050,4900);	//�պ�צ��
  Servo_set(CLOSE,2500,2050,1800,POINT4);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2500,2050,1800,1030);	//ת����һ��λ�õ��Ͽ�
	Servo_set(CLOSE,2400,2050,1500,1030);	//�½�
  Servo_set(OPEN,2400,2050,1500,1030);	delay_ms(1000);//�ſ�
	Servo_set(OPEN,2500,2050,1800,1030);	delay_ms(1000);//��߻�е��
	Servo_set(OPEN,2500,2050,1800,POINT4);//ת����̬
  Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬
	
}
void PUTRED_up(void)//��������̨��
{
		go_forward_laser(200,80);
	
		Servo_set(OPEN,2500,1950,1700,POINT1);	delay_ms(1000);//ת����һ��λ�õ��Ͽ�
	
	Servo_set(OPEN,2500,1900,1450,POINT1);	delay_ms(1000);//�½�
  Servo_set(CLOSE,2500,1900,1450,POINT1);	delay_ms(1000);//�պ�צ��
	Servo_set(CLOSE,2500,1950,1700,POINT1);	delay_ms(1000);//��߻�е��
	Servo_set(CLOSE,1900,1950,1700,4250);	delay_ms(1000);//ת���ŵĵ�3��λ�õ��Ͽ�+ת��
	Servo_set(CLOSE,1750,2100,1100,4250);	delay_ms(1000);//���»�е��
	Servo_set(OPEN,1750,2100,1100,POINT4);delay_ms(1000);
   Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬

}
void PUTGREEN_up(void)
{
	
		Servo_set(OPEN,2300,2050,1600,POINT4);	delay_ms(1000);//ת����3��λ�õ��Ͽ�
  Servo_set(OPEN,2300,2050,1750,POINT2);	delay_ms(1000);//
	Servo_set(OPEN,2450,1950,1400,POINT2);	//�½�
	
  Servo_set(CLOSE,2450,1950,1400,POINT2);	delay_ms(1000);//�ſ�
  Servo_set(CLOSE,2300,2050,1750,POINT2);	delay_ms(1000);//�պ�צ��

	Servo_set(CLOSE,2300,2050,1750,POINT4);	delay_ms(1000);//ת����̬����
		Servo_set(CLOSE,2100,2200,1600,POINT4);	delay_ms(1000);//ת����̬����
	Servo_set(CLOSE,1750,2100,1100,3900);	delay_ms(1000);//���»�е��
	Servo_set(OPEN,1750,2100,1100,3900);delay_ms(1000);

	Servo_set(OPEN,2000,2100,1500,3900);
	Servo_set(OPEN,2100,2200,1600,POINT4);//ת����̬  
	
	
 
}
void PUTBLUE_up(void)
{
	Servo_set(OPEN,2500,1950,1700,POINT3);	delay_ms(1000);//ת����һ��λ�õ��Ͽ�
	Servo_set(OPEN,2500,1900,1450,POINT3);	delay_ms(1000);//�½�
  Servo_set(CLOSE,2500,1900,1450,POINT3);	delay_ms(1000);//�պ�צ��
	Servo_set(CLOSE,2500,1950,1700,POINT3);	delay_ms(1000);//��߻�е��
	Servo_set(CLOSE,2500,1950,1700,4850);	delay_ms(1000);//ת���ŵĵ�3��λ�õ��Ͽ�+ת��
		Servo_set(CLOSE,2100,2200,1600,4850);//ת����̬ 
	Servo_set(CLOSE,1750,2100,1100,4850);delay_ms(5);
	Servo_set(OPEN,1750,2100,1100,4850);delay_ms(5);
 //�ſ�צ��
  Servo_set(OPEN,2250,1900,1300,4850);	//ת����̬
  Servo_set(OPEN,2250,1900,1300,POINT4);	//ת����̬
}
void PUTRED_down(void)
{
		go_forward_laser(200,55);
Servo_set(OPEN,2500,1800,1000,POINT3);	delay_ms(5);//ת����3��λ�õ��Ͽ�
  Servo_set(OPEN,2400,1900,1350,POINT3);	delay_ms(5);//�½�
  Servo_set(CLOSE,2400,1900,1350,POINT3);	delay_ms(5);//�պ�צ��
	Servo_set(CLOSE,2500,1900,1000,POINT3);	delay_ms(5);//��߻�е��
	Servo_set(CLOSE,2500,1900,1000,4400);	delay_ms(5);//ת����̬����
	Servo_set(CLOSE,2300,1700,1100,4400);	delay_ms(5);//ת����̬����
	Servo_set(CLOSE,1500,2300,1700,4400);delay_ms(5);
  Servo_set(OPEN,1500,2300,1700,4400);delay_ms(5);	//�ſ�צ��
	go_ward(REAR,300,30);
		back_center_lap();
	Servo_set(OPEN,2250,1950,1300,POINT4);delay_ms(5);
go_forward_laser(200,55);
}
void PUTGREEN_down(void)
{
 Servo_set(OPEN,2500,1800,1000,POINT2);	delay_ms(5);//ת����3��λ�õ��Ͽ�
  Servo_set(OPEN,2400,1900,1350,POINT2);	delay_ms(5);//�½�
  Servo_set(CLOSE,2400,1900,1350,POINT2);	delay_ms(5);//�պ�צ��
	Servo_set(CLOSE,2500,1900,1000,POINT2);	delay_ms(5);//��߻�е��
	Servo_set(CLOSE,2500,1900,1000,POINT4);	delay_ms(5);//ת����̬����
	Servo_set(CLOSE,2300,1700,1100,POINT4);	delay_ms(5);//ת����̬����
	Servo_set(CLOSE,1700,2000,1800,3800);delay_ms(5);
	Servo_set(OPEN,1700,2000,1800,3800);delay_ms(5);//�ſ�צ��
	Servo_set(OPEN,1900,2000,1800,3800);delay_ms(5);
  Servo_set(OPEN,2250,1950,1300,3800);delay_ms(5);
	Servo_set(OPEN,2250,1950,1300,POINT4);delay_ms(5);
}
void PUTBLUE_down(void)
{
Servo_set(OPEN,2500,1800,1000,POINT1);	delay_ms(5);//ת����3��λ�õ��Ͽ�
  Servo_set(OPEN,2400,1900,1350,POINT1);	delay_ms(5);//�½�
  Servo_set(CLOSE,2400,1900,1350,POINT1);	delay_ms(5);//�պ�צ��
	Servo_set(CLOSE,2500,1900,1000,POINT1);	delay_ms(5);//��߻�е��
	Servo_set(CLOSE,2500,1900,1000,POINT4);	delay_ms(5);//ת����̬����
	Servo_set(CLOSE,2300,1700,1100,POINT4);	delay_ms(5);//ת����̬����
  Servo_set(CLOSE,1700,2000,1800,5000);delay_ms(5);
	Servo_set(OPEN,1700,2000,1800,5000);delay_ms(5);//�ſ�צ��
	Servo_set(OPEN,1900,2000,1800,5000);delay_ms(5);
  Servo_set(OPEN,2250,1950,1300,5000);delay_ms(5);
	Servo_set(OPEN,2250,1950,1300,POINT4);delay_ms(5);
	go_ward(REAR,300,30);
		back_center_lap();
}


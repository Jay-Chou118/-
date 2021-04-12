#include "pwm.h"
#include "sys.h"
#include "delay.h"
#include "wheel.h"
#include "data_type.h"
#include "location.h"


#define PWM3   TIM2->CCR1  //第三个舵机
#define PWM2   TIM2->CCR2  //第二个舵机
#define PWM4   TIM3->CCR1  //第四个舵机 
#define PWM1   TIM3->CCR2  //第一个舵机
#define PWM5   TIM1->CCR1  //第五个舵机	

int Servo1=2000;				//舵机1角度
int Servo2=2200;				//舵机2角度
int Servo3=2100;				//舵机3角度
int Servo4=1600;				//舵机4角度
int Servo5=4250;				//舵机5角度PWM1=750;PWM2=260;PWM3=750 ;PWM4=250;PWM5=800;delay_ms(999);

void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM1时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTF时钟	
		
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//初始化定时器4
		
		//初始化TIM4 Channel PWM模式	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1		
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1
		
		TIM_CtrlPWMOutputs(TIM4,ENABLE);
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM14
 
										  
}

void TIM9_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM1时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTF时钟	
		
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//初始化定时器4
		
		//初始化TIM4 Channel PWM模式	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1
		TIM_OC2Init(TIM9, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1
		
		TIM_CtrlPWMOutputs(TIM9,ENABLE);
	
	TIM_Cmd(TIM9, ENABLE);  //使能TIM14
										  
}

//PA0和PA1已经被使用了，所以只能用2和3
void TIM5_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM1时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化定时器4
		
		//初始化TIM4 Channel PWM模式	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //
		TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //
		
		TIM_CtrlPWMOutputs(TIM5,ENABLE);
	
	TIM_Cmd(TIM5, ENABLE);  //使能TIM14
										  
}


void TIM2_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM1时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
		
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//初始化定时器4
		
		//初始化TIM4 Channel PWM模式	 
		TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1

		
		TIM_CtrlPWMOutputs(TIM2,ENABLE);

		TIM_Cmd(TIM2, ENABLE);  //使能TIM14
	 TIM2->CCR1  =  Servo3;					//第3个舵机
		 TIM2->CCR2  = Servo2;		//第2个舵机
//	 TIM2->CCR1  =  2000;					//第3个舵机
//		 TIM2->CCR2  = 1700;		//第2个舵机
 		
}

void TIM3_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM1时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
		
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器4
		
		//初始化TIM4 Channel PWM模式	 
		TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1

		
		TIM_CtrlPWMOutputs(TIM3,ENABLE);
	
		TIM_Cmd(TIM3, ENABLE);  //使能TIM14
 
		 TIM3->CCR1  =  Servo4;					//第4个舵机·
		 TIM3->CCR2  = Servo1;		//第1个舵机
// TIM3->CCR1  =  1800;					//第4个舵机·
//		 TIM3->CCR2  = Servo1;		//第1个舵机
}
void TIM1_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTF时钟	
		
		
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//GPIOD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
		GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PF9
			
		TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化定时器4
		
		//初始化TIM4 Channel PWM模式	 
		TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OutputNState= TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 4OC1
		

		
		TIM_CtrlPWMOutputs(TIM1,ENABLE);

		TIM_Cmd(TIM1, ENABLE);  //使能TIM14
			 TIM1->CCR1  = Servo5;	//第5个舵机
//					 TIM1->CCR1  = 3600;	//第5个舵机
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
  Servo_set(CLOSE,2500,2050,1800,POINT4);	//转到第一个位置的上空
	Servo_set(CLOSE,2500,2050,1800,POINT1);	//转到第一个位置的上空
	Servo_set(CLOSE,2300,2050,1500,POINT1);	//下降
  Servo_set(OPEN,2300,2050,1500,POINT1);	delay_ms(1000);//张开
	Servo_set(OPEN,2500,2050,1800,POINT1);	delay_ms(1000);//提高机械臂
	Servo_set(OPEN,2500,2050,1800,POINT4);//转到初态
  Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态

}

void PUT2(void)
{
	Servo_set(CLOSE,2300,2050,1600,POINT4);	//转到第一个位置的上空
	Servo_set(CLOSE,2300,2050,1750,POINT2);	//转到第一个位置的上空
	Servo_set(CLOSE,2300,2050,1400,POINT2);	delay_ms(1000);//下降
	Servo_set(CLOSE,2300,2050,1500,POINT2);	delay_ms(1000);//
  Servo_set(OPEN,2300,2050,1500,POINT2);	delay_ms(1000);//张开
	Servo_set(OPEN,2300,2050,1750,POINT2);	delay_ms(1000);//提高机械臂
	Servo_set(OPEN,2300,2050,1750,POINT4);//转到初态
  Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态
}

void PUT3(void)
{    
	   Servo_set(CLOSE,2300,2050,1600,POINT4);	//转到第一个位置的上空
	Servo_set(CLOSE,2300,2050,1750,POINT3);	//转到第一个位置的上空
	Servo_set(CLOSE,2300,2050,1400,POINT3);	//下降
	  Servo_set(CLOSE,2350,2050,1500,POINT3);	delay_ms(1000);//xiajiAN
  Servo_set(OPEN,2350,2050,1500,POINT3);	delay_ms(1000);//张开
	Servo_set(OPEN,2500,2050,1750,POINT3);	delay_ms(1000);//提高机械臂
	Servo_set(OPEN,2400,1950,1700,POINT4);//转到初态
  Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态
}
void GETRED_up1(void)//从上层夹  //测试出夹中间
{
  Servo_set(OPEN,2050,2050,1400,GETPOINTR);	delay_ms(1000);//伸臂
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2050,2050,1400,GETPOINTR);	//闭合爪子
	go_ward(REAR,300,630);
	back_center_lap();
	PUT1();
}

void GETRED_up2(void)
{
  Servo_set(OPEN,2100,2200,1600,POINT4);	delay_ms(1000);//伸臂
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2100,2200,1600,POINT4);	//闭合爪子
	go_ward(REAR,300,630);
	back_center_lap();
	   PUT1();
}
void GETRED_up3(void)
{
   Servo_set(OPEN,2050,2050,1400,GETPOINTL);	delay_ms(1000);//夹臂状态
	   go_forward_laser(300,60);
	   back_center_lap();
  	 Servo_set(CLOSE,2050,2050,1400,GETPOINTL);	//闭合爪子
	   go_ward(REAR,300,600);
	   back_center_lap();
	   PUT1();
}
void GETGREEN_up1(void)
{
  Servo_set(OPEN,2050,2050,1400,GETPOINTR);	delay_ms(1000);//伸臂
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2050,2050,1400,GETPOINTR);	//闭合爪子
	go_ward(REAR,300,630);
	back_center_lap();
     PUT2();
}
void GETGREEN_up2(void)
{
     Servo_set(OPEN,2100,2200,1600,POINT4);	delay_ms(1000);//伸臂
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2100,2200,1600,POINT4);	//闭合爪子
	go_ward(REAR,300,630);
	back_center_lap();
	   PUT2();
}
void GETGREEN_up3(void)
{
     Servo_set(OPEN,2050,2050,1400,GETPOINTL);	delay_ms(1000);//夹臂状态
	   go_forward_laser(300,60);
	   back_center_lap();
  	 Servo_set(CLOSE,2050,2050,1400,GETPOINTL);	//闭合爪子
	   go_ward(REAR,300,600);
	   back_center_lap();
	   PUT2();

}
void GETBLUE_up1(void)
{
    Servo_set(OPEN,2050,2050,1400,GETPOINTR);	delay_ms(1000);//伸臂
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2050,2050,1400,GETPOINTR);	//闭合爪子
	go_ward(REAR,300,630);
	back_center_lap();
     PUT3();
}
void GETBLUE_up2(void)
{
    Servo_set(OPEN,2100,2200,1600,POINT4);	delay_ms(1000);//伸臂
	go_forward_laser(300,60);
	back_center_lap();
  Servo_set(CLOSE,2100,2200,1600,POINT4);	//闭合爪子
	go_ward(REAR,300,630);
	back_center_lap();
	   PUT3();
}
void GETBLUE_up3(void)
{
    Servo_set(2050,2050,1900,1400,GETPOINTL);	delay_ms(1000);//夹臂状态
	   go_forward_laser(300,60);
	   back_center_lap();
  	 Servo_set(CLOSE,2050,2050,1400,GETPOINTL);	//闭合爪子
	   go_ward(REAR,300,600);
	   back_center_lap();
	   PUT3();

}

void GETRED_down1(void)//夹下层
{
     Servo_set(OPEN,1540,2250,1110,3850);	delay_ms(1000);//伸臂
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,3850);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT1();
}

void GETRED_down2(void)
{
     Servo_set(OPEN,1550,2250,1110,POINT4);	delay_ms(1000);//伸臂
	   go_forward_laser(200,80);
	   Servo_set(CLOSE,1550,2250,1110,POINT4);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT1();
}
void GETRED_down3(void)
{
     Servo_set(OPEN,1540,2250,1110,4850);	delay_ms(1000);//伸臂
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,4850);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT1();
}
void GETGREEN_down1(void)
{
  Servo_set(OPEN,1540,2250,1110,3850);	delay_ms(1000);//伸臂
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,3850);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT2();
}

void GETGREEN_down2(void)
{
     Servo_set(OPEN,1550,2250,1110,POINT4);	delay_ms(1000);//伸臂
	   go_forward_laser(200,80);
	   Servo_set(CLOSE,1550,2250,1110,POINT4);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT2();
}
void GETGREEN_down3(void)
{ 
     Servo_set(OPEN,1540,2250,1110,4850);	delay_ms(1000);//伸臂
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,4850);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT2();

}

void GETBLUE_down1(void)
{
  Servo_set(OPEN,1540,2250,1110,3850);	delay_ms(1000);//伸臂
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,3850);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT3();
}
void GETBLUE_down2(void)
{
     Servo_set(OPEN,1550,2250,1110,POINT4);	delay_ms(1000);//伸臂
	   go_forward_laser(200,80);
	   Servo_set(CLOSE,1550,2250,1110,POINT4);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT3();

}
void GETBLUE_down3(void)
{
     Servo_set(2100,1540,2250,1110,4850);	delay_ms(1000);//伸臂
	   go_forward_laser(200,85);
	   Servo_set(1600,1540,2250,1110,4850);	delay_ms(1000);//闭合
	   go_ward(REAR,300,500);
	   back_center_lap();
	   PUT3();
}

void PUTRED_floor(void)//放地上
{
	Servo_set(OPEN,2500,1950,1700,POINT1);	delay_ms(1000);//转到第一个位置的上空
	
	Servo_set(OPEN,2500,1900,1450,POINT1);	delay_ms(1000);//下降
  Servo_set(CLOSE,2500,1900,1450,POINT1);	delay_ms(1000);//闭合爪子
	Servo_set(CLOSE,2500,1950,1700,POINT1);	delay_ms(1000);//提高机械臂
	Servo_set(CLOSE,1900,1950,1700,4250);	delay_ms(1000);//转到放的第3个位置的上空+转臂
	Servo_set(CLOSE,1750,2420,1200,4250);	delay_ms(1000);//放下机械臂
 	Servo_set(OPEN,1750,2420,1200,4250);	delay_ms(1000);//张开爪子	//张开爪子
	go_ward(REAR,300,300);
	Servo_set(OPEN,2250,1950,1300,POINT4);delay_ms(5);
	go_forward_laser(300,30);
	back_center_lap();


}
void PUTGREEN_floor(void)
{
 		Servo_set(OPEN,2300,2050,1600,POINT4);	delay_ms(1000);//转到第3个位置的上空
  Servo_set(OPEN,2300,2050,1750,POINT2);	delay_ms(1000);//
	Servo_set(OPEN,2450,1950,1400,POINT2);	//下降
	
  Servo_set(CLOSE,2450,1950,1400,POINT2);	delay_ms(1000);//张开
  Servo_set(CLOSE,2300,2050,1750,POINT2);	delay_ms(1000);//闭合爪子

	Servo_set(CLOSE,2300,2050,1750,POINT4);	delay_ms(1000);//转到初态过渡
		Servo_set(CLOSE,2100,2200,1600,POINT4);	delay_ms(1000);//转到初态过渡
	Servo_set(CLOSE,1900,2000,1050,GETPOINTR);delay_ms(1000);
	 
	Servo_set(OPEN,1900,2000,1050,GETPOINTR);delay_ms(1000);//张开爪子
	 	 
	Servo_set(OPEN,2000,2100,1500,GETPOINTR);
	Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态  
	
	
}
void PUTBLUE_floor(void)
{

	Servo_set(OPEN,2500,1950,1700,POINT3);	delay_ms(1000);//转到第一个位置的上空
	
	Servo_set(OPEN,2500,1900,1450,POINT3);	delay_ms(1000);//下降
  Servo_set(CLOSE,2500,1900,1450,POINT3);	delay_ms(1000);//闭合爪子
	Servo_set(CLOSE,2500,1950,1700,POINT3);	delay_ms(1000);//提高机械臂
	Servo_set(CLOSE,2500,1950,1700,4900);	delay_ms(1000);//转到放的第3个位置的上空+转臂
	Servo_set(CLOSE,1900,2000,1050,4900);delay_ms(1000);
	 
	Servo_set(OPEN,1900,2000,1050,4900);delay_ms(1000);//张开爪子
	 	 
	Servo_set(OPEN,2000,2100,1500,4900);
	Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态  


}
void GETRED_floor(void)//从地上夹起
{
	go_ward(REAR,300,300);
Servo_set(OPEN,1750,2420,1200,POINT4);	delay_ms(1000);
	go_forward_laser(300,20);
	back_center_lap();
  Servo_set(CLOSE,1750,2420,1200,POINT4);	//闭合爪子
  Servo_set(CLOSE,2500,2050,1800,POINT4);	//转到第一个位置的上空
	Servo_set(CLOSE,2500,2050,1800,POINT1);	//转到第一个位置的上空
	Servo_set(CLOSE,2400,2050,1500,POINT1);	//下降
  Servo_set(OPEN,2400,2050,1500,POINT1);	delay_ms(1000);//张开
	Servo_set(OPEN,2500,2050,1800,POINT1);	delay_ms(1000);//提高机械臂
	Servo_set(OPEN,2500,2050,1800,POINT4);//转到初态
  Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态
	

}

void GETGREEN_floor(void)
{
		go_ward(REAR,300,300);
  Servo_set(2200,1900,2000,1050,3700);	delay_ms(5);//转到初态过渡

	go_forward_laser(300,20);
	back_center_lap();
  Servo_set(CLOSE,1900,2000,1050,3700);	//闭合爪子
	  PUT2();

}
void GETBLUE_floor(void)
{
	go_ward(REAR,300,300);
 Servo_set(OPEN,1900,2000,1050,4900);delay_ms(1000);//张开爪子//转到初态过渡
	go_forward_laser(300,20);
	back_center_lap();
 Servo_set(CLOSE,1900,2000,1050,4900);	//闭合爪子
  Servo_set(CLOSE,2500,2050,1800,POINT4);	//转到第一个位置的上空
	Servo_set(CLOSE,2500,2050,1800,1030);	//转到第一个位置的上空
	Servo_set(CLOSE,2400,2050,1500,1030);	//下降
  Servo_set(OPEN,2400,2050,1500,1030);	delay_ms(1000);//张开
	Servo_set(OPEN,2500,2050,1800,1030);	delay_ms(1000);//提高机械臂
	Servo_set(OPEN,2500,2050,1800,POINT4);//转到初态
  Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态
	
}
void PUTRED_up(void)//放在载物台上
{
		go_forward_laser(200,80);
	
		Servo_set(OPEN,2500,1950,1700,POINT1);	delay_ms(1000);//转到第一个位置的上空
	
	Servo_set(OPEN,2500,1900,1450,POINT1);	delay_ms(1000);//下降
  Servo_set(CLOSE,2500,1900,1450,POINT1);	delay_ms(1000);//闭合爪子
	Servo_set(CLOSE,2500,1950,1700,POINT1);	delay_ms(1000);//提高机械臂
	Servo_set(CLOSE,1900,1950,1700,4250);	delay_ms(1000);//转到放的第3个位置的上空+转臂
	Servo_set(CLOSE,1750,2100,1100,4250);	delay_ms(1000);//放下机械臂
	Servo_set(OPEN,1750,2100,1100,POINT4);delay_ms(1000);
   Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态

}
void PUTGREEN_up(void)
{
	
		Servo_set(OPEN,2300,2050,1600,POINT4);	delay_ms(1000);//转到第3个位置的上空
  Servo_set(OPEN,2300,2050,1750,POINT2);	delay_ms(1000);//
	Servo_set(OPEN,2450,1950,1400,POINT2);	//下降
	
  Servo_set(CLOSE,2450,1950,1400,POINT2);	delay_ms(1000);//张开
  Servo_set(CLOSE,2300,2050,1750,POINT2);	delay_ms(1000);//闭合爪子

	Servo_set(CLOSE,2300,2050,1750,POINT4);	delay_ms(1000);//转到初态过渡
		Servo_set(CLOSE,2100,2200,1600,POINT4);	delay_ms(1000);//转到初态过渡
	Servo_set(CLOSE,1750,2100,1100,3900);	delay_ms(1000);//放下机械臂
	Servo_set(OPEN,1750,2100,1100,3900);delay_ms(1000);

	Servo_set(OPEN,2000,2100,1500,3900);
	Servo_set(OPEN,2100,2200,1600,POINT4);//转到初态  
	
	
 
}
void PUTBLUE_up(void)
{
	Servo_set(OPEN,2500,1950,1700,POINT3);	delay_ms(1000);//转到第一个位置的上空
	Servo_set(OPEN,2500,1900,1450,POINT3);	delay_ms(1000);//下降
  Servo_set(CLOSE,2500,1900,1450,POINT3);	delay_ms(1000);//闭合爪子
	Servo_set(CLOSE,2500,1950,1700,POINT3);	delay_ms(1000);//提高机械臂
	Servo_set(CLOSE,2500,1950,1700,4850);	delay_ms(1000);//转到放的第3个位置的上空+转臂
		Servo_set(CLOSE,2100,2200,1600,4850);//转到初态 
	Servo_set(CLOSE,1750,2100,1100,4850);delay_ms(5);
	Servo_set(OPEN,1750,2100,1100,4850);delay_ms(5);
 //张开爪子
  Servo_set(OPEN,2250,1900,1300,4850);	//转到初态
  Servo_set(OPEN,2250,1900,1300,POINT4);	//转到初态
}
void PUTRED_down(void)
{
		go_forward_laser(200,55);
Servo_set(OPEN,2500,1800,1000,POINT3);	delay_ms(5);//转到第3个位置的上空
  Servo_set(OPEN,2400,1900,1350,POINT3);	delay_ms(5);//下降
  Servo_set(CLOSE,2400,1900,1350,POINT3);	delay_ms(5);//闭合爪子
	Servo_set(CLOSE,2500,1900,1000,POINT3);	delay_ms(5);//提高机械臂
	Servo_set(CLOSE,2500,1900,1000,4400);	delay_ms(5);//转到初态过渡
	Servo_set(CLOSE,2300,1700,1100,4400);	delay_ms(5);//转到初态过渡
	Servo_set(CLOSE,1500,2300,1700,4400);delay_ms(5);
  Servo_set(OPEN,1500,2300,1700,4400);delay_ms(5);	//张开爪子
	go_ward(REAR,300,30);
		back_center_lap();
	Servo_set(OPEN,2250,1950,1300,POINT4);delay_ms(5);
go_forward_laser(200,55);
}
void PUTGREEN_down(void)
{
 Servo_set(OPEN,2500,1800,1000,POINT2);	delay_ms(5);//转到第3个位置的上空
  Servo_set(OPEN,2400,1900,1350,POINT2);	delay_ms(5);//下降
  Servo_set(CLOSE,2400,1900,1350,POINT2);	delay_ms(5);//闭合爪子
	Servo_set(CLOSE,2500,1900,1000,POINT2);	delay_ms(5);//提高机械臂
	Servo_set(CLOSE,2500,1900,1000,POINT4);	delay_ms(5);//转到初态过渡
	Servo_set(CLOSE,2300,1700,1100,POINT4);	delay_ms(5);//转到初态过渡
	Servo_set(CLOSE,1700,2000,1800,3800);delay_ms(5);
	Servo_set(OPEN,1700,2000,1800,3800);delay_ms(5);//张开爪子
	Servo_set(OPEN,1900,2000,1800,3800);delay_ms(5);
  Servo_set(OPEN,2250,1950,1300,3800);delay_ms(5);
	Servo_set(OPEN,2250,1950,1300,POINT4);delay_ms(5);
}
void PUTBLUE_down(void)
{
Servo_set(OPEN,2500,1800,1000,POINT1);	delay_ms(5);//转到第3个位置的上空
  Servo_set(OPEN,2400,1900,1350,POINT1);	delay_ms(5);//下降
  Servo_set(CLOSE,2400,1900,1350,POINT1);	delay_ms(5);//闭合爪子
	Servo_set(CLOSE,2500,1900,1000,POINT1);	delay_ms(5);//提高机械臂
	Servo_set(CLOSE,2500,1900,1000,POINT4);	delay_ms(5);//转到初态过渡
	Servo_set(CLOSE,2300,1700,1100,POINT4);	delay_ms(5);//转到初态过渡
  Servo_set(CLOSE,1700,2000,1800,5000);delay_ms(5);
	Servo_set(OPEN,1700,2000,1800,5000);delay_ms(5);//张开爪子
	Servo_set(OPEN,1900,2000,1800,5000);delay_ms(5);
  Servo_set(OPEN,2250,1950,1300,5000);delay_ms(5);
	Servo_set(OPEN,2250,1950,1300,POINT4);delay_ms(5);
	go_ward(REAR,300,30);
		back_center_lap();
}


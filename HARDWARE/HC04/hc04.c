#include "hc04.h"
#include "stm32f4xx.h"
#include "delay.h"
//准备了3个获取渠道，实际上用到的只有两个，所以可以去掉一个，现在暂时不去掉
void GPIO_Configuration()  
{  
  GPIO_InitTypeDef  GPIO_InitStructure; 
    
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);  
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   
  GPIO_Init(GPIOD, &GPIO_InitStructure);   
}  


void GPIO_HC_04_Configuration()  
{  
  GPIO_InitTypeDef  GPIO_InitStructure; 
    
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
		
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
	  GPIO_Init(GPIOB, &GPIO_InitStructure); 

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	   
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 	 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   
	  GPIO_Init(GPIOE, &GPIO_InitStructure);  

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
}  


void EXTIX_HC_04_Init_0(void)//实际上这个用不到，因为只有两个超声波
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource9);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void EXTIX_HC_04_Init_1(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void EXTIX_HC_04_Init_2(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource11);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
}
int reg3 = 0;
void Hc_sr_04_Init_D8()
{
	GPIO_SetBits(GPIOD,GPIO_Pin_8); 		 
	delay_us(20);		                    
	GPIO_ResetBits(GPIOD,GPIO_Pin_8);
	
}
void Hc_sr_04_Init_E15()
{
	GPIO_SetBits(GPIOE,GPIO_Pin_15); 		 
	delay_us(20);		                    
	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
	delay_us(20);
}
void Hc_sr_04_Init_C2()
{
	GPIO_SetBits(GPIOC,GPIO_Pin_2); 		 
	delay_us(20);		                    
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	delay_us(20);
}

void TIM8_Count_Init()  //使用TIM8作为计数器，记录时间
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  //999+1 =1000
	TIM_TimeBaseStructure.TIM_Prescaler = 83;  //83+1= 84分频   -> 2M
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM8, ENABLE);
	//暂时先关闭TIM8时钟，等全部初始化结束后正式使用定时器前再开启
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, DISABLE);
	
}


//PB11 output     PE15 input
void GPIO_HC_04_Configuration_before()  
{  
    GPIO_InitTypeDef  GPIO_InitStructure; 
    
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);


	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 	 //输入
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	 // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   
	  GPIO_Init(GPIOE, &GPIO_InitStructure); 


}

//PA0 output     PC2 input
void GPIO_HC_04_Configuration_after()
{	
	  
    GPIO_InitTypeDef  GPIO_InitStructure; 	 
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
		
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	   


	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
}  



float distance_test()   //测量物台到小车前端的距离；
{
	
	float distance = 0.00;
	unsigned int time = 0;
	
	TIM8_Count_Init();
	GPIO_HC_04_Configuration_before();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	while(1)
	{
		TIM_Cmd(TIM8, ENABLE);
		before_TRIG_H;
		delay_us(15);
		before_TRIG_L;
		while(before_ECHO == 0);
		TIM_SetCounter(TIM8, 0);
		while(before_ECHO == 1);
		TIM_Cmd(TIM8, DISABLE);
		time = TIM_GetCounter(TIM8);
		distance = time * 0.017/2;
		//printf("Distance = %.2fcm\n", distance);
		//delay_ms(500);//更改延时时间，求得平均值；确保稳定
	}
	return distance;
}







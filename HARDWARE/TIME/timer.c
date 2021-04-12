#include "timer.h"
#include "sys.h"
#include "data_type.h"
#include "us100.h"

//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
extern vu16 USART2_RX_STA;
extern WheelDeadSpace_Type WheelDeadSpace;
extern DeadTimerFlag_Type DeadTimerFlag;
extern HC_sr04_Type Hc_sr04;
extern DRV8825_Type DRV8825;
extern CoordVariasionFlag_Type CoordVariasionFlag;
extern SteeringEngineSpeed_Type SteeringEngineSpeed;
extern DeadTimer_Type     DeadTimer       ;
extern char time_base_flag;
extern int  time_base;
extern int Steering_Flag;
extern int Steering_Time;
extern int PID_LOCK ;
extern int DeadFlagCoefficence_X;
extern int DeadFlagCoefficence_Y;
//这个时钟是给wifi用的，用于接收wifi模块的数据
//通用定时器中断初始化
//这里始终选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数		 
void TIM7_Int_Init(u16 arr,u16 psc)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);//TIM7时钟使能    
	
	//定时器TIM7初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //使能指定的TIM7中断,允许更新中断

	 	  
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
}
	 
//TimerFlag_Type TimerFlag ={0,0,0,0};
//定时器7中断服务程序		    
void TIM7_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		USART2_RX_STA|=1<<15;	//标记接收完成
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIM7更新中断标志    
		TIM_Cmd(TIM7, DISABLE);  //关闭TIM7 
	}	    
}
void TIM14_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  ///使能TIM3时钟
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM14,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM14,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM8_TRG_COM_TIM14_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void TIM13_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM13,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM13,DISABLE);//先关掉计数
	NVIC_InitStructure.NVIC_IRQChannel=TIM8_UP_TIM13_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
void EXTI9_5_IRQHandler(void)
{		
	
     if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
		TIM_Cmd(TIM13, ENABLE);                                             
		Hc_sr04.Flag++;  
		while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9));	                  
		TIM_Cmd(TIM13, DISABLE);		
		Hc_sr04.Distance1=TIM13->CNT*5*2*34/2000.0;									 
		TIM13->CNT=0;
	    EXTI_ClearITPendingBit(EXTI_Line9);  
   }
	
   
}

void EXTI0_IRQHandler(void)
{		
	
     if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		TIM_Cmd(TIM13, ENABLE);                                             
		Hc_sr04.Flag++;  
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));	                  
		TIM_Cmd(TIM13, DISABLE);		
		Hc_sr04.Distance1=TIM13->CNT*5*2*34/2000.0;									 
		TIM13->CNT=0;
	    EXTI_ClearITPendingBit(EXTI_Line0);  
   }
   
}

void EXTI15_10_IRQHandler(void)
{		
	    
//   if(EXTI_GetITStatus(EXTI_Line10) != RESET)
//	{
//		CoordVariasion();
//	    EXTI_ClearITPendingBit(EXTI_Line10);  
//   }
	
   if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
		TIM_Cmd(TIM13, ENABLE);                                             
		Hc_sr04.Flag++;  
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11));	                  
		TIM_Cmd(TIM13, DISABLE);		
		Hc_sr04.Distance2=TIM13->CNT*5*2*34/2000.0;									 
		TIM13->CNT=0;
	    EXTI_ClearITPendingBit(EXTI_Line11);  
   }
   
}



void TIM8_UP_TIM13_IRQHandler(void)
{
	

    if(TIM_GetITStatus(TIM13,TIM_IT_Update)==SET)
    {       
		
    }
    TIM_ClearITPendingBit(TIM13,TIM_IT_Update); 
}





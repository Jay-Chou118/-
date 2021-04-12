#include "timer.h"
#include "sys.h"
#include "data_type.h"
#include "us100.h"

//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
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
//���ʱ���Ǹ�wifi�õģ����ڽ���wifiģ�������
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʼ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��		 
void TIM7_Int_Init(u16 arr,u16 psc)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);//TIM7ʱ��ʹ��    
	
	//��ʱ��TIM7��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM7�ж�,��������ж�

	 	  
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
}
	 
//TimerFlag_Type TimerFlag ={0,0,0,0};
//��ʱ��7�жϷ������		    
void TIM7_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	 			   
		USART2_RX_STA|=1<<15;	//��ǽ������
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //���TIM7�����жϱ�־    
		TIM_Cmd(TIM7, DISABLE);  //�ر�TIM7 
	}	    
}
void TIM14_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM14,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM14,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM8_TRG_COM_TIM14_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
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
	TIM_Cmd(TIM13,DISABLE);//�ȹص�����
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





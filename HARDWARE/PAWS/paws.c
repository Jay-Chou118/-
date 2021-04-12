#include "paws.h"
#include "pwm.h"
#include "timer.h"
#include "sys.h"
#include "data_type.h"
extern int Steering_Test[4];



void SteeringEngine_Change()
{
	
	//SteeringEngine_PWM_PID();
		TIM2_PWM_Init(20000-1,84-1); 
	TIM3_PWM_Init(20000-1,84-1);
	
//	TIM1_PWM_Init(20000-1,168-1);
//	TIM8_PWM_Init(20000-1,168-1);
	STEERINGENGINE1 = Steering_Test[0];//缺螺丝那个
	STEERINGENGINE2 = Steering_Test[1];//抓取的地方
	STEERINGENGINE3 = Steering_Test[2];//第一个
	STEERINGENGINE4 = Steering_Test[3];//底座

}

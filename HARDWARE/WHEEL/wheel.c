#include "wheel.h"
#include "data_type.h"
#include "timer.h"
#include "delay.h"
#include "us100.h"

extern WheelSpeed_Type WheelSpeed;
extern WheelSpeedTIM_Type WheelSpeedCurrent;
extern int forward_red;//前面的红外灯亮的位置
void WheelDrive_TIM_TEST()
{
		
		Forward_LeftDown  = WheelSpeedCurrent.ForwardLeftDown ;
		Retreat_LeftDown  = WheelSpeedCurrent.RetreatLeftDown ;
		Forward_LeftUp    = WheelSpeedCurrent.ForwardLeftUp   ;
	    Retreat_LeftUp    = WheelSpeedCurrent.RetreatLeftUp   ;
		Forward_RightDown = WheelSpeedCurrent.ForwardRightDown;
		Retreat_RightDown = WheelSpeedCurrent.RetreatRightDown;
		Forward_RightUp   = WheelSpeedCurrent.ForwardRightUp  ;
		Retreat_RightUp   = WheelSpeedCurrent.RetreatRightUp  ;
}
void MotorDrive_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启驱动板上引脚相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
		/*配置DIR*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	         //选择要控制的GPIO引脚
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     //设置引脚模式为推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置速率为50MHz
		GPIO_Init(GPIOD, &GPIO_InitStructure);	     //调用库函数，初始化GPIO   
		
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
}
//向后移动
void go_rear(int speed,int to_time){
			Forward_LeftDown = speed;		//左后轮  -1000~1000
			Retreat_LeftDown  =0;
			 Forward_LeftUp=speed    ;  
			 Retreat_LeftUp=0 ;
			Forward_RightDown = speed;		
			Retreat_RightDown  =0;
			 Forward_RightUp=speed    ;  
			 Retreat_RightUp=0 ;
					delay_ms(to_time);
	if(to_time>0){
					delay_ms(to_time);
					go_rear(0,0);//自己调用自己
}
}
//向前移动
void go_forward(int speed,int to_time){
			Forward_LeftDown = 0;		//左后轮  -1000~1000
			Retreat_LeftDown  =speed;
			 Forward_LeftUp=0    ;  
			 Retreat_LeftUp=speed ;
			Forward_RightDown = 0;		
			Retreat_RightDown  =speed;
			 Forward_RightUp=0    ;  
			 Retreat_RightUp=speed ;
	if(to_time>0){
					delay_ms(to_time);
					go_forward(0,0);//自己调用自己
}
	

}
//向左移动
void go_left(int speed,int to_time){
			Forward_LeftDown = 0;		//左后轮  -1000~1000
			Retreat_LeftDown  =speed;
			 Forward_LeftUp=0    ;  
			 Retreat_LeftUp=speed ;
			Forward_RightDown = speed;		
			Retreat_RightDown  =0;
			 Forward_RightUp=speed    ;  
			 Retreat_RightUp=0 ;
	if(to_time>0){
	
					delay_ms(to_time);
							go_left(0,0);//自己调用自己

}
}
//向右移动
void go_right(int speed,int to_time)
{
			Forward_LeftDown =speed;		//左后轮  -1000~1000
			Retreat_LeftDown  =0;
			 Forward_LeftUp=0   ;  
			 Retreat_LeftUp=speed ;
			Forward_RightDown = 0;		
			Retreat_RightDown  =speed;
			 Forward_RightUp=speed    ;  
			 Retreat_RightUp=0 ;
	if(to_time>0){
	
					delay_ms(to_time);
									go_right(0,0);//自己调用自己

}
}
//逆时针
void go_counter_clockwise(int speed,int to_time)

{
			Forward_LeftDown =0;		//左后轮  -1000~1000
			Retreat_LeftDown  =speed;
			 Forward_LeftUp=0   ;  
			 Retreat_LeftUp=speed ;
			Forward_RightDown = speed;		
			Retreat_RightDown  =0;
			 Forward_RightUp=speed    ;  
			 Retreat_RightUp=0 ;
	if(to_time>0){
					delay_ms(to_time);
											go_clockwise(0,0);//自己调用自己

}
}
//顺时针
void go_clockwise(int speed,int to_time)
{
			Forward_LeftDown =speed;		//左后轮  -1000~1000
			Retreat_LeftDown  =0;
			 Forward_LeftUp=speed   ;  
			 Retreat_LeftUp=0 ;
			Forward_RightDown = 0;		
			Retreat_RightDown  =speed;
			 Forward_RightUp=0    ;  
			 Retreat_RightUp=speed ;
	if(to_time>0){
					delay_ms(to_time);
													go_counter_clockwise(0,0);//自己调用自己
}
}
//45°走
void go_squint(int speed,int to_time)
{Forward_LeftDown =speed;		//左后轮  -1000~1000
			Retreat_LeftDown  =0;
			 Forward_LeftUp=0   ;  
			 Retreat_LeftUp=0 ;
			Forward_RightDown = 0;		
			Retreat_RightDown  =0;
			 Forward_RightUp=0    ;  
			 Retreat_RightUp=speed ;
	if(to_time>0){
					delay_ms(to_time);
													go_squint(0,0);//自己调用自己
}}
//任何方向的移动




void go_ward(u8 kk,int speed,int to_time)
{
	int i;
	u8 get=1;
	u8 spon;
	for(i=0;i<8;i++){
		spon=((get<<i)&kk)>>i;
		switch(i){
			case 0:if(spon){Forward_LeftDown =speed;}else{Forward_LeftDown =0;}; break;
			case 1:if(spon){Retreat_LeftDown =speed;}else{Retreat_LeftDown =0;}; break;
			case 2:if(spon){Forward_LeftUp =speed;}else{Forward_LeftUp =0;}; break;
			case 3:if(spon){Retreat_LeftUp =speed;}else{Retreat_LeftUp =0;}; break;
			case 4:if(spon){Forward_RightDown =speed;}else{Forward_RightDown =0;}; break;
			case 5:if(spon){Retreat_RightDown =speed;}else{Retreat_RightDown =0;}; break;
			case 6:if(spon){Forward_RightUp =speed;}else{Forward_RightUp =0;}; break;
			case 7:if(spon){Retreat_RightUp =speed;}else{Retreat_RightUp =0;}; break;
		}
	}
	if(to_time>0){
					delay_ms(to_time);
													go_ward(0,0,0);//自己调用自己
}
}
void set_moto (int  speed,int cut){
			Retreat_LeftDown = 0;		//左后轮  -1000~1000
			Forward_LeftDown  =speed+cut;
			Retreat_LeftUp=0    ;  
			Forward_LeftUp=speed+cut ;
			Retreat_RightDown = 0;		
			Forward_RightDown  =speed-cut;
			Retreat_RightUp=0    ;  
			Forward_RightUp=speed-cut ;
}
void go_forward_laser(int speed,int to_stop)
{
		int status;
//		VL53L1_RangingMeasurementData_t rangingData;
		u16 range_last = 0;
		int cut=0;
		int bro=0;
	int monitor;
		while(1){
			bro++;
					Down_Load_InfaredTube_number();
switch (forward_red){
					case 1:cut=-70; break;
					case 2:cut=-70; break;
					case 3:cut=-70; break;
					case 4:cut=0; break;//第一个需要调的地方！！！！！！！！！
					case 5:cut=70; break;
					case 6:cut=70; break;
					case 7:cut=70; break;
}
	set_moto(speed,cut);
//		if(read_isDataReady()){//读取激光是否准备好
//				status = VL53L1_GetRangingMeasurementData(&dev, &rangingData);
//				if(status==0)
//				{
//																return;

//					range_last = rangingData.RangeMilliMeter * 0.1f;	/*单位cm*/	//记得增加激光数据筛选，可以上下限幅和取多次平均
//					
//						if (range_last<to_stop){
//							if(monitor==3){
//											go_ward(0,0,0);//停下
//											status = VL53L1_ClearInterruptAndStartMeasurement(&dev);
//											return;
//							}
//							monitor++;
//						}
//				}
//				status = VL53L1_ClearInterruptAndStartMeasurement(&dev);
//	}
							delay_ms(10);
if(bro>to_stop){
																					go_ward(0,0,0);//停下
return;
}
	}
}





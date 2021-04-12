#include "wheel.h"
#include "data_type.h"
#include "timer.h"
#include "delay.h"
#include "us100.h"

extern WheelSpeed_Type WheelSpeed;
extern WheelSpeedTIM_Type WheelSpeedCurrent;
extern int forward_red;//ǰ��ĺ��������λ��
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
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*������������������ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
		/*����DIR*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	         //ѡ��Ҫ���Ƶ�GPIO����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     //��������ģʽΪ�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //��������Ϊ50MHz
		GPIO_Init(GPIOD, &GPIO_InitStructure);	     //���ÿ⺯������ʼ��GPIO   
		
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
}
//����ƶ�
void go_rear(int speed,int to_time){
			Forward_LeftDown = speed;		//�����  -1000~1000
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
					go_rear(0,0);//�Լ������Լ�
}
}
//��ǰ�ƶ�
void go_forward(int speed,int to_time){
			Forward_LeftDown = 0;		//�����  -1000~1000
			Retreat_LeftDown  =speed;
			 Forward_LeftUp=0    ;  
			 Retreat_LeftUp=speed ;
			Forward_RightDown = 0;		
			Retreat_RightDown  =speed;
			 Forward_RightUp=0    ;  
			 Retreat_RightUp=speed ;
	if(to_time>0){
					delay_ms(to_time);
					go_forward(0,0);//�Լ������Լ�
}
	

}
//�����ƶ�
void go_left(int speed,int to_time){
			Forward_LeftDown = 0;		//�����  -1000~1000
			Retreat_LeftDown  =speed;
			 Forward_LeftUp=0    ;  
			 Retreat_LeftUp=speed ;
			Forward_RightDown = speed;		
			Retreat_RightDown  =0;
			 Forward_RightUp=speed    ;  
			 Retreat_RightUp=0 ;
	if(to_time>0){
	
					delay_ms(to_time);
							go_left(0,0);//�Լ������Լ�

}
}
//�����ƶ�
void go_right(int speed,int to_time)
{
			Forward_LeftDown =speed;		//�����  -1000~1000
			Retreat_LeftDown  =0;
			 Forward_LeftUp=0   ;  
			 Retreat_LeftUp=speed ;
			Forward_RightDown = 0;		
			Retreat_RightDown  =speed;
			 Forward_RightUp=speed    ;  
			 Retreat_RightUp=0 ;
	if(to_time>0){
	
					delay_ms(to_time);
									go_right(0,0);//�Լ������Լ�

}
}
//��ʱ��
void go_counter_clockwise(int speed,int to_time)

{
			Forward_LeftDown =0;		//�����  -1000~1000
			Retreat_LeftDown  =speed;
			 Forward_LeftUp=0   ;  
			 Retreat_LeftUp=speed ;
			Forward_RightDown = speed;		
			Retreat_RightDown  =0;
			 Forward_RightUp=speed    ;  
			 Retreat_RightUp=0 ;
	if(to_time>0){
					delay_ms(to_time);
											go_clockwise(0,0);//�Լ������Լ�

}
}
//˳ʱ��
void go_clockwise(int speed,int to_time)
{
			Forward_LeftDown =speed;		//�����  -1000~1000
			Retreat_LeftDown  =0;
			 Forward_LeftUp=speed   ;  
			 Retreat_LeftUp=0 ;
			Forward_RightDown = 0;		
			Retreat_RightDown  =speed;
			 Forward_RightUp=0    ;  
			 Retreat_RightUp=speed ;
	if(to_time>0){
					delay_ms(to_time);
													go_counter_clockwise(0,0);//�Լ������Լ�
}
}
//45����
void go_squint(int speed,int to_time)
{Forward_LeftDown =speed;		//�����  -1000~1000
			Retreat_LeftDown  =0;
			 Forward_LeftUp=0   ;  
			 Retreat_LeftUp=0 ;
			Forward_RightDown = 0;		
			Retreat_RightDown  =0;
			 Forward_RightUp=0    ;  
			 Retreat_RightUp=speed ;
	if(to_time>0){
					delay_ms(to_time);
													go_squint(0,0);//�Լ������Լ�
}}
//�κη�����ƶ�




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
													go_ward(0,0,0);//�Լ������Լ�
}
}
void set_moto (int  speed,int cut){
			Retreat_LeftDown = 0;		//�����  -1000~1000
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
					case 4:cut=0; break;//��һ����Ҫ���ĵط�������������������
					case 5:cut=70; break;
					case 6:cut=70; break;
					case 7:cut=70; break;
}
	set_moto(speed,cut);
//		if(read_isDataReady()){//��ȡ�����Ƿ�׼����
//				status = VL53L1_GetRangingMeasurementData(&dev, &rangingData);
//				if(status==0)
//				{
//																return;

//					range_last = rangingData.RangeMilliMeter * 0.1f;	/*��λcm*/	//�ǵ����Ӽ�������ɸѡ�����������޷���ȡ���ƽ��
//					
//						if (range_last<to_stop){
//							if(monitor==3){
//											go_ward(0,0,0);//ͣ��
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
																					go_ward(0,0,0);//ͣ��
return;
}
	}
}





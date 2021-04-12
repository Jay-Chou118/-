#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "us100.h"
#include "GUI.h"
#include "Lcd_Driver.h"
#include "TFT_demo.h"
#include "data_type.h"
#include "timer.h"
#include "hc04.h"
#include "wifi_base.h"
#include "wheel.h"
#include "pwm.h"
#include "location.h"
#include "key.h"
#include "paws.h"
#include "user_main.h"
#include "choise.h"

extern int F_B_NUM[];
extern int L_R_NUM[];
extern u8 color;
extern int QR_FIST,QR_NEXT;
extern int  QR_NEXT2,QR_FIST2;

//extern InfaredTube_Type InfaredTube_X_F ;
//extern InfaredTube_Type InfaredTube_X_R ;
//extern InfaredTube_Type InfaredTube_Y ;
//extern HC_sr04_Type Hc_sr04 ;
//extern u16 USART2_RX_STA;         		//接收状态标记
//extern u8  USART2_RX_BUF[USART_REC_LEN2]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符



int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2//切记这样的话，主和副都不能超过3
    delay_init(168);      //初始化延时函数
   Lcd_Init();	 //1.44寸液晶屏--初始化配置
	    uart_init(115200);		//初始化串口波特率为115200

    Lcd_Clear(RED);//清屏
    InfaredTube_GPIO_Config();//初始化21路光电循迹调用的io口
    GPIO_HC_04_Configuration() ;//初始化超声波测距的io
    EXTIX_HC_04_Init_2();//初始化PB11中断
    EXTIX_HC_04_Init_1();//初始化中断PA0中断
    TIM13_Int_Init(1000 - 1, 168 - 1); //初始化计数器TIM13
	//	inint_wifi();//初始化wifi
  TIM4_PWM_Init(1000 - 1, 168 - 1);	//168M/168=1Mhz的计数频率,重装载值1000，所以PWM频率为 1M/1000=1Khz.
    TIM5_PWM_Init(1000 - 1, 168 - 1);
    TIM9_PWM_Init(1000 - 1, 168 - 1);	//168M/168=1Mhz的计数频率,重装载值1000，所以PWM频率为 1M/1000=1Khz
    MotorDrive_GPIO_Config();//轮子使能
		TIM2_PWM_Init(19999,83);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.  CRR/1990+1=占空比
	TIM3_PWM_Init(19999,83);
	TIM1_PWM_Init(19999,83);
	KEY_Init();//按键初始化
	    Lcd_Clear(BLUE);//清屏

//    delay_ms(10000);
//		go_forward(100);
//		    delay_ms(5000);

//	go_left(100);
//		    delay_ms(5000);

//	go_right(100);
//		    delay_ms(5000);

//	go_rear(100);
//		go_clockwise(100);
//	printf("!!!!!!!");

while(1){
		
	//printf("!!!!!!!");


	
	if(KEY_Scan()){
			
		 //Servo_set(OPEN,2050,2050,1400,GETPOINTR);	delay_ms(1000);
		 //Servo_set(CLOSE,2050,2050,1400,GETPOINTL);	//闭合爪子
		//GETRED_up1();
//		back_center_lap();
//		GETRED_up1();
		//Servo_set(CLOSE,2050,2050,1400,GETPOINTR);
		//getup_red_1();
		//Servo_set(OPEN,2100,1800,1100,4100);while(1);
		//Servo_set(OPEN,2100,1800,1100,4700);delay_ms(500);
		//Servo_set(OPEN,2100,1800,1100,5000);delay_ms(500);
		//Scan_QR();
		//delay_ms(500);
		//QR_code(); 
   //Gui_DrawFont_GBK16(8,0,BLUE,GRAY0,"111");
		 // Servo_set(1300,1700,2050,1900,4200);	delay_ms(1000);//伸臂
   //PUTCENTRE_down2();
	//	 PUTRIGHT_down2();
	//	 PUTLEFT_down2();
		// GETCENTRE_down2();
		 //GETRIHGHT_down2();
		//GETLEFT_down2();
    //GETCENTRE_DOWN();
	//	GETLEFT_DOWN();
		
	//	PUTCENTRE_UP();
		//PUTLEFT_UP();
	// GETLEFT_floor();
	//
//  Servo_set(1300,2500,1900,1200,2500);	delay_ms(1000);//转到第3个位置的上空
//  Servo_set(1300,2500,2100,1350,2500);	delay_ms(1000);//下降
//  Servo_set(1050,2500,2100,1350,2500);	delay_ms(1000);//闭合爪子
//	Servo_set(1050,2500,2100,1100,2500);	delay_ms(1000);//提高机械臂
//	Servo_set(1050,2400,1900,1200,4600);	delay_ms(1000);//转到初态过渡
//	//Servo_set(1250,2400,2200,1200,4600);	//转到初态
//	Servo_set(1050,1700,1900,1200,4600);//伸臂	
//  Servo_set(1050,1400,2250,1900,4600);	delay_ms(1000);//伸臂
//	Servo_set(1050,1750,2250,1900,4600);	delay_ms(1000);//伸臂	
//  Servo_set(1300,1750,2250,1900,4600);	delay_ms(1000);//张开		
//	Servo_set(1300,2400,2200,1200,4600);	delay_ms(1000);//回到初态
//	  Lcd_Clear(RED);//清屏
//		back_center_lap();
//		delay_ms(1000);
	//			go_ward(FORWARD,SPEED_LOW,F_B_NUM[1]+1075);
//				delay_ms(500);
//go_ward(RIGHT,SPEED_BASE,3000);
//				back_center_lap();
//go_ward(RECLOCKWISE,SPEED_BASE,TURN_CLK);
//go_forward_laser(200,10000);
	
	//get4();
	//choise_1();
	//back_center_lap();
	//Servo_set(OPEN,2150,2000,1300,4450);
	//PUT1();
	//Scan_QR();
	//QR_code();
	Sys_Run();
//star_go();back_center_lap();go_ward(CLOCKWISE,300,770);back_center_lap();break;
	//go_ward(LEFT,500,500);go_ward(REAR,500,100);back_center_lap();go_home();break;

//star_go();	
//go_ward(CLOCKWISE,300,770);		
//		go_forward_laser(SPEED_MINI,10);
//		go_ward(REAR,500,100);
//		back_center_lap();

while(1){
	
//			Gui_DrawFont_GBK16(8,0,BLUE,GRAY0,"111");
	
	
/*	if(temp==0&QR_FIST2!=0 & QR_FIST2!=111)
		{
			temp=QR_FIST2;
		}
			if(temp_next==0&QR_NEXT2!=0 & QR_NEXT2!=111){
			temp_next=QR_NEXT2;
		}
		
			Gui_DrawFont_Num32(82,20,RED,GRAY0,((temp)%100)%10);
			Gui_DrawFont_Num32(40,20,RED,GRAY0,(temp/10)%10);
			Gui_DrawFont_Num32(0,20,RED,GRAY0,(temp/100));	
	
			Gui_DrawFont_GBK24(50,60,RED,GRAY2,"+");
	
			Gui_DrawFont_Num32(82,90,RED,GRAY0,((temp_next)%100)%10);
			Gui_DrawFont_Num32(40,90,RED,GRAY0,(temp_next/10)%10);
			Gui_DrawFont_Num32(0,90,RED,GRAY0,(temp_next/100));*/
		
//	Gui_DrawFont_Num32(80,80,RED,GRAY0,QR_NEXT2-((QR_NEXT2)%100)-((QR_NEXT2)%100)%10);

//					delay_ms(500);

}
}
}

}


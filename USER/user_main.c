#include "user_main.h"
#include "data_type.h"
#include "sys.h"
#include "paws.h"
#include "wifi.h"
#include "location.h"
#include "wheel.h"
#include "delay.h"
#include "pwm.h"
#include "usart.h"
#include "Choise.h"
#include "GUI.h"
#include "Lcd_Driver.h"

extern int F_B_NUM[];
extern int L_R_NUM[];

extern int run_flag;
void Sys_Run(void ){
	run_flag=10;//初始化flag

//	SteeringEngine_Change();
while(1){
		switch (run_flag){
			case 11:star_go();run_flag=11;delay_ms(500);back_center_lap();break;//走出出发点，到1.1
			case 10:Scan_QR();run_flag++;break;
			case 12:run_flag++;/*伸臂*/Scan_QR();/*QR_code()*/;Gui_DrawFont_Num32(82,20,RED,GRAY0,1);Gui_DrawFont_Num32(40,20,RED,GRAY0,3);Gui_DrawFont_Num32(0,20,RED,GRAY0,2);	Gui_DrawFont_GBK24(50,60,RED,GRAY2,"+");Gui_DrawFont_Num32(82,90,RED,GRAY0,((132)%100)%10);Gui_DrawFont_Num32(40,90,RED,GRAY0,(132/10)%10);Gui_DrawFont_Num32(0,90,RED,GRAY0,(132/100));break;//openmv二维码识别程序
			case 13:go_ward(RECLOCKWISE,300,730);/*左转*/;back_center_lap();delay_ms(500);go_forward_laser(SPEED_MINI,F_B_NUM[1]);back_center_lap();run_flag++;break;
			case 14:go_ward(CLOCKWISE,300,730);back_center_lap();run_flag=20;break;
			//case 14:go_ward(CLOCKWISE,300,730);back_center_lap();run_flag=20;break;
			case 20:go_ward(FORWARD,SPEED_LOW,F_B_NUM[3]);run_flag+=10;back_center_lap();break;
			case 30:go_forward_laser(SPEED_MINI,F_B_NUM[3]);run_flag+=10;back_center_lap();break;
			case 40:go_ward(CLOCKWISE,300,770);run_flag=41;back_center_lap();delay_ms(500);break;
			case 41:go_ward(FORWARD,500,270);run_flag++;delay_ms(1000);/*back_center_lap();*/break;
			
//			case 42:GETRIGHT_up2();run_flag++;delay_ms(1000);//根据opmv获取的数据夹取，假设红绿蓝分别被定义为123，openmv获取的数据为321+123，则该行为先抓取蓝色
//		  case 43:GETCENTRE_up2();run_flag++; delay_ms(1000);  //根据opmv获取的数据夹取，假设红绿蓝分别被定义为123，openmv获取的数据为321+123，则该行为先抓取绿色
//		  case 44:GETLEFT_up2(); run_flag=46; delay_ms(1000);//根据opmv获取的数据夹取，假设红绿蓝分别被定义为123，openmv获取的数据为321+123，则该行为先抓取红色
			case 42:get4();getup_red_1();GETRED_up1();run_flag=46;break;//夹取物块//213+123
			case 43:get4();getup_green_1();GETGREEN_up2();run_flag++;break;
			case 44:get4();getup_bule_1();GETGREEN_up3();run_flag=46;break;
		//	case 45:go_ward(REAR,500,270);run_flag++;delay_ms(1000);back_center_lap();/*back_center_lap();*/break;
			case 46:go_ward(RECLOCKWISE,300,770);run_flag++;back_center_lap();break;
			case 47:go_ward(RECLOCKWISE,300,770);run_flag=50;back_center_lap();break;
			case 50:go_forward_laser(SPEED_MINI,F_B_NUM[2]);run_flag+=10;back_center_lap();break;
			case 60:go_ward(CLOCKWISE,300,770);run_flag=61;back_center_lap();break;
			case 61:PUTRED_floor();run_flag++;delay_ms(1000);/*back_center_lap();*/break;
      case 62:PUTGREEN_floor();run_flag++;delay_ms(1000);break;
	 		case 63:PUTBLUE_floor();run_flag++;delay_ms(1000);break;
			case 64:GETRED_floor();run_flag++;delay_ms(1000);break;
			case 65:GETGREEN_floor();run_flag++;delay_ms(1000);break;
			case 66:GETBLUE_floor();run_flag=71;delay_ms(1000);break;
//			case 64:PUTLEFT_down2();run_flag++;break;
//  		case 65:GETCENTRE_down2();run_flag++;break;
//  		case 66:GETRIHGHT_down2();run_flag++;break;
//			case 67:GETLEFT_down2();run_flag=71;break;
			//case 70:go_ward(REAR,500,200);run_flag++;delay_ms(1000);back_center_lap();break;	
			case 71:go_ward(RECLOCKWISE,300,750);run_flag=80;back_center_lap();break;
			case 80:go_forward_laser(SPEED_MINI,75);run_flag+=10;back_center_lap();break;
			case 90:go_ward(RECLOCKWISE,300,770);run_flag+=10;back_center_lap();delay_ms(1000);break;
			case 100:go_forward_laser(SPEED_MINI,F_B_NUM[2]);run_flag+=10;back_center_lap();break;
			case 110:go_ward(CLOCKWISE,300,770);run_flag=111;back_center_lap();delay_ms(1000);break;
			case 111:go_ward(FORWARD,500,300);run_flag++;delay_ms(1000);/*back_center_lap();*/break;
	   	case 112:PUTRED_up();run_flag++;break;
			case 113:PUTGREEN_up();run_flag++;break;
			case 114:PUTBLUE_up();run_flag=115;break;
			case 115:go_ward(REAR,500,300);run_flag++;delay_ms(1000);back_center_lap();/*back_center_lap();*/break;
			case 116:go_ward(RECLOCKWISE,300,770);run_flag++;back_center_lap();delay_ms(1000);break;
			case 117:go_ward(RECLOCKWISE,300,770);run_flag=120;back_center_lap();delay_ms(1000);break;
			case 120:go_forward_laser(SPEED_MINI,F_B_NUM[4]);run_flag+=10;back_center_lap();break;
			case 130:go_ward(RECLOCKWISE,300,770);run_flag+=10;back_center_lap();delay_ms(1000);break;
			case 140:go_forward_laser(SPEED_MINI,F_B_NUM[2]);run_flag++;back_center_lap();break;
			case 141:go_ward(CLOCKWISE,300,770);run_flag=143;back_center_lap();delay_ms(1000);break;
	//		case 142:go_ward(FORWARD,500,200);run_flag++;delay_ms(1000);/*back_center_lap();*/break;
		
			case 143:get4();getdown_red_1();GETRED_up1();run_flag=46;break;//夹取物块//213+123
			case 144:get4();getdown_green_1();GETGREEN_up2();run_flag++;break;
			case 145:get4();getdown_bule_1();GETGREEN_up3();run_flag=46;break;
		//	case 146:go_ward(REAR,500,200);run_flag++;delay_ms(1000);back_center_lap();/*back_center_lap();*/break;
			case 147:go_ward(RECLOCKWISE,300,770);run_flag++;back_center_lap();break;
			case 148:go_ward(RECLOCKWISE,300,770);run_flag=150;back_center_lap();break;
				case 150:go_forward_laser(SPEED_MINI,F_B_NUM[2]);run_flag+=10;back_center_lap();break;
			case 160:go_ward(CLOCKWISE,300,770);run_flag=162;back_center_lap();break;
	//		case 161:go_ward(FORWARD,500,200);run_flag=162;delay_ms(1000);/*back_center_lap();*/break;
//			case 162:	PUTCENTRE_down2();run_flag++;break;
//			case 163:PUTRIGHT_down2();run_flag++;break;
//			case 164:PUTLEFT_down2();run_flag++;break;
//			case 165:GETCENTRE_down2();run_flag++;break;
//			case 166:GETRIHGHT_down2();run_flag++;break;
//			case 167:GETLEFT_down2();run_flag=171;break;
		//	case 170:go_ward(REAR,500,200);run_flag++;delay_ms(1000);back_center_lap();break;	
			case 171:go_ward(RECLOCKWISE,300,770);run_flag=180;back_center_lap();break;
			case 180:go_forward_laser(SPEED_MINI,75);run_flag+=10;back_center_lap();break;
			case 190:go_ward(RECLOCKWISE,300,770);run_flag+=10;back_center_lap();delay_ms(1000);break;
			case 200:go_forward_laser(SPEED_MINI,F_B_NUM[2]);run_flag+=10;back_center_lap();break;
			case 210:go_ward(CLOCKWISE,300,770);run_flag++;back_center_lap();delay_ms(1000);break;
			case 211:go_ward(FORWARD,500,200);run_flag++;delay_ms(1000);/*back_center_lap();*/break;
//			case 212:PUTRIGHT_UP();run_flag++;break;
//			case 213:PUTCENTRE_UP();run_flag++;break;
//			case 214:PUTLEFT_UP();run_flag++;break;
case 215:go_ward(REAR,500,200);run_flag++;delay_ms(1000);back_center_lap();break;

			case 216:go_ward(RECLOCKWISE,300,770);run_flag=220;back_center_lap();delay_ms(1000);break;
			case 220:go_forward_laser(SPEED_MINI,F_B_NUM[2]);run_flag+=10;back_center_lap();break;
			case 230:go_ward(LEFT,500,500);go_ward(REAR,500,100);back_center_lap();go_home();run_flag+=10;break;
			default:return;
			
			
			
			
			
			
		
		}
}
}


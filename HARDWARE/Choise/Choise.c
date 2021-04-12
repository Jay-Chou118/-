#include "stm32f4xx.h"
#include "choise.h"
#include "pwm.h"
#include "string.h"
#include "delay.h"
extern int QR_FIST2;
extern int QR_NEXT2;


extern u8 color;

char QR[]="123+321";
int chance;
int get_color;
int chance1;
int chance2;
int red1=1;
int bule1=1;
int green1=1;
int red2=1;
int bule2=1;
int green2=1;


void getup_red_1()//抓取上层红色
{
	switch(red1){
		
		case 1:Servo_set(OPEN,2100,1800,1100,4200);;delay_ms(500);if(color==1){GETRED_up1();}  else{red1++;}break;
		case 2:Servo_set(OPEN,2100,1800,1100,4700);delay_ms(500);if(color==1){GETRED_up2();}  else{red1++;}break;
		case 3: Servo_set(OPEN,2100,1800,1100,5000);delay_ms(500);if(color==1){GETRED_up3();}  else{red1=1;}break;
	}
	

}
	



void getup_green_1()//抓取上层绿色
{
	
switch(green1){
		case 1: 
						Servo_set(OPEN,2100,1800,1100,4100);delay_ms(500);if(color==2){GETGREEN_up1();}  else{green1++;}break;
		case 2:
						Servo_set(OPEN,2100,1800,1100,4700);delay_ms(500);if(color==2){GETGREEN_up2();}  else{green1++;}break;
		case 3:
						 Servo_set(OPEN,2100,1800,1100,5000);delay_ms(500);if(color==2){GETGREEN_up3();}  else{green1=1;}break;
	}
		

}
	
void getup_bule_1()//抓取上层蓝色
{
	
switch(bule1){
		case 1:
						Servo_set(OPEN,2100,1800,1100,4100);delay_ms(500);	if(color==3){GETBLUE_up1();}  else{bule1++;}break;
		case 2:
						Servo_set(OPEN,2100,1800,1100,4700);delay_ms(500);	if(color==3){GETBLUE_up2();}  else{bule1++;}break;
		case 3:
						Servo_set(OPEN,2100,1800,1100,5000);delay_ms(500);	if(color==3){GETBLUE_up3();}  else{bule1=1;}break;
	}

}
	
void getdown_red_1()//抓取下层红色
{

	switch(red2){
		
			case 1:
							Servo_set(OPEN,2100,1800,1000,4100);delay_ms(500);	if(color==1){GETRED_down1();}  else{red1++;}break;
			case 2:
							Servo_set(OPEN,2100,1850,1000,4700);delay_ms(500);	if(color==1){GETRED_down2();}  else{red1++;}break;
			case 3:
							Servo_set(OPEN,2100,1800,1000,5000);delay_ms(500);	if(color==1){GETRED_down3();}  else{red1=1;}break;
	}
	
}

void getdown_green_1()//抓取下层绿色
{
	switch(green2){
		case 1:
						Servo_set(OPEN,2100,1800,1000,4100);delay_ms(500);if(color==2){GETGREEN_down1();}  else{green1++;}break;
		case 2:
						Servo_set(OPEN,2100,1850,1000,4700);delay_ms(500);if(color==2){GETGREEN_down2();}  else{green1++;}break;
		case 3:
						Servo_set(OPEN,2100,1800,1000,5000);delay_ms(500);if(color==2){GETGREEN_down3();}  else{green1=1;}break;
	}
		

}


void getdown_bule_1()//抓取下层蓝色
{
	switch(bule2){
			case 1:
							Servo_set(OPEN,2100,1800,1000,4100);delay_ms(500);if(color==3){GETBLUE_down1();}  else{bule1++;}break;
			case 2:	
						Servo_set(OPEN,2100,1850,1000,4700);delay_ms(500);if(color==3){GETBLUE_down2();}  else{bule1++;}break;
			case 3:	
							Servo_set(OPEN,2100,1800,1000,5000);delay_ms(500);if(color==3){GETBLUE_down3();}  else{bule1=1;}break;
	}


}

/*void get1(){
if(QR=="123+123"&&"123+132"&&"123+213"&&"123+231"&&"123+312"&&"123+321"){chance1=10;}
else if(QR=="132+123"&&"132+132"&&"132+213"&&"132+231"&&"132+312"&&"132+321"){chance1=11;}
else if(QR=="213+123"&&"213+132"&&"213+213"&&"213+231"&&"213+312"&&"213+321"){chance1=20;}
else if(QR=="231+123"&&"231+132"&&"231+213"&&"231+231"&&"231+312"&&"231+321"){chance1=21;}
else if(QR=="312+123"&&"312+132"&&"312+213"&&"312+231"&&"312+312"&&"312+321"){chance1=30;}
else(opmvQR1="321+123"&&"321+132"&&"321+213"&&"321+231"&&"321+312"&&"321+321") {chance1=31;}		
}//根据二维码判断上层


	void get2(){
	if(QR=="123+123"&&"132+123"&&"213+123"&&"231+123"&&"312+123"&&"321+123"){chance2=10;}
	else if(QR=="123+132"&&"132+132"&&"213+132"&&"231+132"&&"312+132"&&"321+132"){chance2=11;}
	else if(QR=="123+213"&&"132+213"&&"213+213"&&"231+213"&&"312+213"&&"321+213"){chance2=20;}
	else if(QR=="123+231"&&"132+231"&&"213+231"&&"231+231"&&"312+231"&&"321+231"){chance2=21;}
	else if(QR=="123+312"&&"132+312"&&"213+312"&&"231+312"&&"312+312"&&"321+312"){chance2=30;}
	else (opmvQR2="123+321"&&"132+321"&&"213+321"&&"231+321"&&"312+321"&&"321+321"){chance2=31;}
	
	}//根据二维码判断下层*/
//				int QR1=123,QR2=321;
void set_chance2(int *chance_addrs,int chance_number){
		*chance_addrs=chance_number;
}

void get3(int judge,int mode){
				switch (judge){
					case 123:set_chance2((mode)? &chance1:&chance2,10);break;
					case 132:set_chance2((mode)? &chance1:&chance2,11);break;
					case 213:set_chance2((mode)? &chance1:&chance2,20);break;
					case 231:set_chance2((mode)? &chance1:&chance2,21);break;
					case 312:set_chance2((mode)? &chance1:&chance2,30);break;
					default:set_chance2((mode)? &chance1:&chance2,31);break;
				}
			}
void	get4()
	{
		get3(QR_FIST2,1);
		get3(QR_NEXT2,0);
		//printf("chance1=%d,chance2%d",chance1,chance2);
	}
		
		
		
void choise_1(){
switch(chance1)
	{case 10:getup_red_1();getup_green_1();getup_bule_1();
	case 11:getup_red_1();getup_bule_1();getup_green_1();
	case 20:getup_green_1();getup_red_1();getup_bule_1();
	case 21:getup_green_1();getup_bule_1();getup_red_1();
	case 30:getup_bule_1();getup_red_1();getup_green_1();
	case 31:getup_bule_1();getup_green_1();getup_red_1();
}//根据二维码判断上层夹取顺序
	}
void choise_2(){
switch(chance2)
	{
		case 10:getdown_red_1();getdown_green_1();getdown_bule_1();
		case 11:getdown_red_1();getdown_bule_1();getdown_green_1();
	case 20:getdown_green_1();getdown_bule_1();getdown_red_1();
	case 21:getdown_green_1();getdown_red_1();getdown_bule_1();
	case 30:getdown_bule_1();getup_red_1();getdown_green_1();
	case 31:getdown_bule_1();getup_green_1();getdown_red_1();
}
	//根据二维码判断下层夹取顺序

}

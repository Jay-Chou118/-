#include "location.h"
#include "sys.h"
#include "us100.h"
#include "data_type.h"
#include "wifi_base.h"
#include "wheel.h"
#include "delay.h"
#define SP 120
extern u8 line_mode;
extern int x_poor;//x������ĺ��������λ�õĲ�ֵ
extern int left_red;//��ߵĺ��������λ��
extern int right_red;//�ұߵĺ��������λ��
extern int forward_red;//ǰ��ĺ��������λ��

u8 math_x_poor(void){
	Down_Load_InfaredTube_number();
	x_poor=left_red-right_red;
}
u8 fact_line_mode(void)//������ƫ�����
{
	if(!(left_red*right_red==0)){
		if (left_red<4 && right_red<4){
		line_mode=1; //ƫ��ͼ�еĵ�1�����
	}else if (left_red>4 && right_red>4){
				line_mode=2; //ƫ��ͼ�еĵ�2�����
	}else if (left_red<4 && right_red>4){
				line_mode=3; //ƫ��ͼ�еĵ�3�����
	}else if (left_red>4 && right_red<4){
				line_mode=4; //ƫ��ͼ�еĵ�4�����
	}else if (left_red==4&& right_red<4){
				line_mode=5; //ƫ��ͼ�еĵ�5�����
	}else if (right_red==4&& left_red<4){
				line_mode=6; //ƫ��ͼ�еĵ�6�����
	}else if (left_red==4&& right_red>4){
				line_mode=7; //ƫ��ͼ�еĵ�5�����
	}else if (right_red==4&& left_red>4){
				line_mode=8; //ƫ��ͼ�еĵ�6�����
	}
	
	}else{
	line_mode=0;
	}



}
int back_center(void)
{
	Down_Load_InfaredTube_number();//��������ǰ����λ����ڸ�λ��
	math_x_poor();//��ȡƫ��ֵ
	if (x_poor==0){//���ҵ��ڸǵĵط�һ����ֻ��Ҫ��ǰ��������ƶ�
		if (left_red>4){
		go_ward(REAR,SP,50);
		}else if (left_red<4){
								go_ward(FORWARD,SP,50);
		}else if (left_red==4){
				switch(forward_red){
					case 1:go_ward(RIGHT,SP,50); break;
					case 2:go_ward(RIGHT,SP,50); break;
					case 3:go_ward(RIGHT,SP,50); break;
					case 4:return 0; break;
					case 5:go_ward(LEFT,SP,50); break;
					case 6:go_ward(LEFT,SP,50); break;
					case 7:go_ward(LEFT,SP,50); break;
		}}
		}else{
			fact_line_mode();
			switch(line_mode){
					case 1:go_ward(FORWARD,SP,50); break;
					case 2:go_ward(REAR,SP,50); break;
					case 3:go_ward(RECLOCKWISE,SP,50); break;
					case 4:go_ward(CLOCKWISE,SP,50); break;
					case 5:go_ward(CLOCKWISE,SP,50); break;
					case 6:go_ward(RECLOCKWISE,SP,50); break;
					case 7:go_ward(RECLOCKWISE,SP,50); break;
					case 8:go_ward(CLOCKWISE,SP,50); break;
	}
	}
		return 1; 
}
void back_center_lap(void){
						for(int i=0;i<700;i++){

												    while(back_center())
    {
		}
	}
										delay_ms(200);

												for(int i=0;i<300;i++){

												    while(back_center())
    {
		}
	}
																						delay_ms(500);
												for(int i=0;i<100;i++){

												    while(back_center())
    {
		}
	}
}

void star_go()
{
		delay_ms(1000);
				go_ward(FORWARD,550,570);//12V->500
				delay_ms(500);
				go_ward(RIGHT,250,1050);//1100
}
void go_home()
{
				go_ward(FORWARD,500,450);
				delay_ms(500);
				go_ward(LEFT,500,300);
}


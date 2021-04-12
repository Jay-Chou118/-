#include "location.h"
#include "sys.h"
#include "us100.h"
#include "data_type.h"
#include "wifi_base.h"
#include "wheel.h"
#include "delay.h"
#define SP 120
extern u8 line_mode;
extern int x_poor;//x轴两侧的红外灯亮的位置的差值
extern int left_red;//左边的红外灯亮的位置
extern int right_red;//右边的红外灯亮的位置
extern int forward_red;//前面的红外灯亮的位置

u8 math_x_poor(void){
	Down_Load_InfaredTube_number();
	x_poor=left_red-right_red;
}
u8 fact_line_mode(void)//遇到的偏移情况
{
	if(!(left_red*right_red==0)){
		if (left_red<4 && right_red<4){
		line_mode=1; //偏移图中的第1种情况
	}else if (left_red>4 && right_red>4){
				line_mode=2; //偏移图中的第2种情况
	}else if (left_red<4 && right_red>4){
				line_mode=3; //偏移图中的第3种情况
	}else if (left_red>4 && right_red<4){
				line_mode=4; //偏移图中的第4种情况
	}else if (left_red==4&& right_red<4){
				line_mode=5; //偏移图中的第5种情况
	}else if (right_red==4&& left_red<4){
				line_mode=6; //偏移图中的第6种情况
	}else if (left_red==4&& right_red>4){
				line_mode=7; //偏移图中的第5种情况
	}else if (right_red==4&& left_red>4){
				line_mode=8; //偏移图中的第6种情况
	}
	
	}else{
	line_mode=0;
	}



}
int back_center(void)
{
	Down_Load_InfaredTube_number();//载入左右前三个位点的遮盖位置
	math_x_poor();//获取偏差值
	if (x_poor==0){//左右灯遮盖的地方一样，只需要向前或者向后移动
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


#include "us100.h"
#include "sys.h"
#include "data_type.h"
#include "wifi_base.h"
extern int left_red;//左边的红外灯亮的位置
extern int right_red;//右边的红外灯亮的位置
extern int forward_red;//前面的红外灯亮的位置
extern InfaredTube_Type InfaredTube_X_F ;
extern InfaredTube_Type InfaredTube_X_R ;
extern InfaredTube_Type InfaredTube_Y ;
extern CurrentCoord_Type CurrentCoord ;
extern int SportState;
extern int CurrentVariasion_X;
extern int CurrentVariasion_Y;
extern CoordVariasionFlag_Type CoordVariasionFlag;
extern int Light_X,Unlight_X;
extern int Light_Y,Unlight_Y;
extern int Coord_X_Flag;
void InfaredTube_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启驱动板上引脚相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
		/*配置DIR*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_7|GPIO_Pin_0|GPIO_Pin_10;	         //选择要控制的GPIO引脚
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;     //设置引脚模式为推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置速率为50MHz
		GPIO_Init(GPIOD, &GPIO_InitStructure);	     //调用库函数，初始化GPIO  

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_10;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_14;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_12;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

}





void InfaredTube_Read(void)
{
	InfaredTube_X_F.Light1 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);
	InfaredTube_X_F.Light2 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	InfaredTube_X_F.Light3 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7);
	InfaredTube_X_F.Light4 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3);
	InfaredTube_X_F.Light5 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1);
	InfaredTube_X_F.Light6 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12);
	InfaredTube_X_F.Light7 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10);
	
	InfaredTube_Y.Light1 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10);
	InfaredTube_Y.Light2 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8);
	InfaredTube_Y.Light3 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
	InfaredTube_Y.Light4 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
	InfaredTube_Y.Light5 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
	InfaredTube_Y.Light6 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11);
	InfaredTube_Y.Light7 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0);
	
	InfaredTube_X_R.Light7 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4);
	InfaredTube_X_R.Light6 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8);
	InfaredTube_X_R.Light5 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10);
	InfaredTube_X_R.Light4 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12);
	InfaredTube_X_R.Light3 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14);
	InfaredTube_X_R.Light2 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
	InfaredTube_X_R.Light1 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
	
//	
//		InfaredTube_X_R.Light1 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4);
//	InfaredTube_X_R.Light2 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8);
//	InfaredTube_X_R.Light3 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10);
//	InfaredTube_X_R.Light4 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12);
//	InfaredTube_X_R.Light5 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14);
//	InfaredTube_X_R.Light6 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
//	InfaredTube_X_R.Light7 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
}

int InfaredTube_Transform(InfaredTube_Type a,int* buf_data)
{
int *p = (int *)&a;
int i;
for(i=0; i<sizeof(a)/sizeof(int); i++)
{
    if ((*p++)==1){

				*buf_data=i+1;
//				u3_printf("buf_data:%d",*buf_data);

		}
}
//	memset(&a,0,sizeof(InfaredTube_X_R));//结构体清零

}
void original_red_data(void)
{
	left_red=0;
	right_red=0;
forward_red=0;

}
void Down_Load_InfaredTube_number(void){
	InfaredTube_Read();
		InfaredTube_Transform(InfaredTube_X_F,&left_red);
			InfaredTube_Transform(InfaredTube_X_R,&right_red);
			InfaredTube_Transform(InfaredTube_Y,&forward_red);
//	u3_printf("left_red:%d",left_red);
//		u3_printf("right_red:%d",right_red);
//	u3_printf("forward_red:%d",forward_red);


//		memset(&InfaredTube_X_F,0,sizeof(InfaredTube_X_R));//结构体清零
//		memset(&InfaredTube_X_R,0,sizeof(InfaredTube_X_R));//结构体清零
//		memset(&InfaredTube_Y,0,sizeof(InfaredTube_X_R));//结构体清零

//		u3_printf("forward_red:%d",forward_red);


}














#include "key.h"
#include "delay.h" 
#include "data_type.h"
extern u8 key_flag;
//////////////////////////////////////////////////////////////////////////////////	 

// STM32F407开发板
//按键输入驱动代码	   
							  
////////////////////////////////////////////////////////////////////////////////// 	 

//按键初始化函数
//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，WKUP按下 --对应K1按键

u8 KEY_Scan()
{	 
//	if(mode)key_up=1;  //支持连按		  
	if(WK_UP==0)
	{
		delay_ms(100);//去抖动 
		if(WK_UP==0)return 1;
		
	}	    
 	return 0;// 无按键按下
}





















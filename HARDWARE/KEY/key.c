#include "key.h"
#include "delay.h" 
#include "data_type.h"
extern u8 key_flag;
//////////////////////////////////////////////////////////////////////////////////	 

// STM32F407������
//����������������	   
							  
////////////////////////////////////////////////////////////////////////////////// 	 

//������ʼ������
//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��WKUP���� --��ӦK1����

u8 KEY_Scan()
{	 
//	if(mode)key_up=1;  //֧������		  
	if(WK_UP==0)
	{
		delay_ms(100);//ȥ���� 
		if(WK_UP==0)return 1;
		
	}	    
 	return 0;// �ް�������
}





















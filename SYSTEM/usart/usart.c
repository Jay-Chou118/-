#include "sys.h"
#include "usart.h"	
#include "timer.h"	
#include "data_type.h"
#include "GUI.h"
#include "Lcd_Driver.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"

////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 

//STM32F4������
//����1��ʼ��		   

////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	


//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
extern u16 USART_RX_STA;         		//����״̬���	
extern u16 USART2_RX_STA;         		//����״̬���	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART2_RX_BUF[USART_REC_LEN2]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 color;
extern int  QR_NEXT,QR_FIST;
extern int  QR_NEXT2,QR_FIST2;
//extern int temp;
//extern int temp_next;
//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��

	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
		//����2��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); //GPIOD5����ΪUSART2
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); //GPIOD6����ΪUSART2
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //PD5��PD6
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PD5��PD6

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	  USART_Init(USART2, &USART_InitStructure); //��ʼ������2

  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���12

	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	TIM7_Int_Init(1000-1,8400-1);		//100ms�ж�
	USART2_RX_STA=0;		//����
	TIM_Cmd(TIM7, DISABLE); //�رն�ʱ��7
	
}
 char step=0;
 char data_check=0;
 char colors0,colors1,colors2,colors3,colors4,colors5;
//int QR_NEXT,QR_FIST;
void USART1_IRQHandler(void)
{

	u8 res;
	static	int gg=0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
//		Gui_DrawFont_Num32(8,0,RED,GRAY0,color); �������

		res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		
		static int updata;
		static int downdata; //�м���ֵ
		
		switch(step)
		{
			case 0://��ͷ
			{
								QR_NEXT=0;
																	QR_FIST=0;
				if(res==0xaa){
					step++;

					}
				else step=0;
			}break;
			case 1://��ͷ
			{
				if(res==0x55){
				//	printf("2");
					step++;

					}
				else step=0;
			}break;
			case 2://��ɫ ����
			{
				if(res>=1 && res<=3){
					color=res;
					step++;}else {step=0;}
				}break;
			case 3://��ɫ ����
			{
								if(res>=0 && res<=3){
					QR_FIST=QR_FIST+res*100;
								
					step++;}else {step=0;}
				}break;
			case 4://��ɫ ����
			{
								if(res>=0 && res<=3){
					QR_FIST=QR_FIST+res*10;
								
					step++;}else {step=0;}
				}break;
						case 5://��ɫ ����
			{
								if(res>=0 && res<=3){
				QR_FIST=QR_FIST+res;
									
					step++;}else {step=0;}
				}break;
						case 6://��ɫ ����
			{
								if(res>=0 && res<=3){
					QR_NEXT=QR_NEXT+res*100;
									
					step++;}else {step=0;}
				}break;
						case 7://��ɫ ����
			{
								if(res>=0 && res<=3){
					QR_NEXT=QR_NEXT+res*10;
					
					step++;}else {step=0;}
				}break;
						case 8://��ɫ ����
			{
								if(res>=0 && res<=3){
					QR_NEXT=QR_NEXT+res;
									
					step++;}else {step=0;}
				}break;
									case 9://��ɫ ����
			{
						if(res!=0x99)
						{
								QR_NEXT2=0;
								QR_FIST2=0;
								color=0;
						}else
						{
						
							QR_NEXT2=QR_NEXT;
							QR_FIST2=QR_FIST; 
							

						}
				step=0;
			}break;
			default:break;
		}
							  USART_ClearFlag(USART1, USART_IT_RXNE);

  } 
//	Gui_DrawFont_Num32(8,0,RED,GRAY0,color);

} 

 
 

void Send_data(USART_TypeDef * USARTx,u8 *s)
{
	static char send_count=0;
	send_count=sizeof(s)/sizeof(s[0]);//��ȡ����������м�λ
	while(send_count)
	{
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC )==RESET);	
		USART_SendData(USARTx,*s);
		s++;
		send_count--;
	}
}

//��ʾ��ά����ֵ��
void QR_code(void){

	int temp_first = 0;
	int temp_next = 0;
do {
if(temp_first==0&&QR_FIST2!=0 && QR_FIST2!=111)
		{
			temp_first=QR_FIST2;
		}
			if(temp_next==0&&QR_NEXT2!=0 && QR_NEXT2!=111){
			temp_next=QR_NEXT2;
//			Gui_DrawFont_Num32(82,20,RED,GRAY0,((temp_first)%100)%10);
//			Gui_DrawFont_Num32(40,20,RED,GRAY0,(temp_first/10)%10);
//			Gui_DrawFont_Num32(0,20,RED,GRAY0,(temp_first/100));	
			Gui_DrawFont_Num32(82,20,RED,GRAY0,2);
			Gui_DrawFont_Num32(40,20,RED,GRAY0,1);
	    Gui_DrawFont_Num32(0,20,RED,GRAY0,3);	
			Gui_DrawFont_GBK24(50,60,RED,GRAY2,"+");
	
			Gui_DrawFont_Num32(82,90,RED,GRAY0,((132)%100)%10);
			Gui_DrawFont_Num32(40,90,RED,GRAY0,(132/10)%10);
			Gui_DrawFont_Num32(0,90,RED,GRAY0,(132/100));
				
/*				if(colors0!=1&&colors1!=1&&colors2!=1)
				{
					if(colors0!=0&&colors1!=0&&colors2!=0)
					{
					Gui_DrawFont_Num32(82,20,RED,GRAY0,colors0);
			Gui_DrawFont_Num32(40,20,RED,GRAY0,colors1);
			Gui_DrawFont_Num32(0,20,RED,GRAY0,colors2);	
	
			Gui_DrawFont_GBK24(50,60,RED,GRAY2,"+");
	
			Gui_DrawFont_Num32(82,90,RED,GRAY0,colors3);
			Gui_DrawFont_Num32(40,90,RED,GRAY0,colors4);
			Gui_DrawFont_Num32(0,90,RED,GRAY0,colors5);
				break;
					}*/
			break;
			}
	


			
}while(1);
}

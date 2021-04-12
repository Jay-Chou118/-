#include "wifi.h"
#include "data_type.h"
extern u16 USART2_RX_STA;         		//接收状态标记
extern u8  USART2_RX_BUF[USART_REC_LEN2]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	//发送缓冲,最大USART2_MAX_SEND_LEN字节//对齐，确保发送不乱码


void Get_Oder(void)
{


    if(USART2_RX_STA & 0X8000)		//接收到一次数据了
    {
        USART2_RX_BUF[USART2_RX_STA & 0X7FFF] = 0; //添加结束符
        printf("ack:%s", USART2_RX_BUF);
			USART2_RX_STA=0;
    }

}

#include "wifi.h"
#include "data_type.h"
extern u16 USART2_RX_STA;         		//����״̬���
extern u8  USART2_RX_BUF[USART_REC_LEN2]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�//���룬ȷ�����Ͳ�����


void Get_Oder(void)
{


    if(USART2_RX_STA & 0X8000)		//���յ�һ��������
    {
        USART2_RX_BUF[USART2_RX_STA & 0X7FFF] = 0; //��ӽ�����
        printf("ack:%s", USART2_RX_BUF);
			USART2_RX_STA=0;
    }

}

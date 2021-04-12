#include "wifi_base.h"
#include "sys.h"
#include "data_type.h"
#include "delay.h"

extern u16 USART2_RX_STA;         		//����״̬���
extern u8  USART2_RX_BUF[USART_REC_LEN2]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�//���룬ȷ�����Ͳ�����
const u8* portnum = "7070";
const u8* wifista_ssid = "mFi_03F772";			//·����SSID��
const u8* wifista_password = "1234567890"; 	//��������
const u8* ipbuf = "192.168.0.101"; 	//ip

//ATK-ESP8266���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
u8* atk_8266_check_cmd(u8 *str)
{

    char *strx = 0;

    if(USART2_RX_STA & 0X8000)		//���յ�һ��������
    {
        USART2_RX_BUF[USART2_RX_STA & 0X7FFF] = 0; //��ӽ�����
        printf("ack:%s", USART2_RX_BUF);
        strx = strstr((const char*)USART2_RX_BUF, (const char*)str);
    }

    return (u8*)strx;
}

//����3,printf ����
//ȷ��һ�η������ݲ�����USART2_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt, ...)
{
    u16 i, j;
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char*)USART2_TX_BUF, fmt, ap);
    va_end(ap);
    i = strlen((const char*)USART2_TX_BUF); //�˴η������ݵĳ���

    for(j = 0; j < i; j++) //ѭ����������
    {
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); //�ȴ��ϴδ������

        USART_SendData(USART2, (uint8_t)USART2_TX_BUF[j]); 	 //�������ݵ�����3
    }

}
//��ATK-ESP8266��������
//cmd:���͵������ַ���
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
u8 atk_8266_send_cmd(u8 *cmd, u8 *ack, u16 waittime)
{
    u8 res = 0;
    USART2_RX_STA = 0;

    u3_printf("%s\r\n", cmd);	//��������

    if(ack && waittime)		//��Ҫ�ȴ�Ӧ��
    {
        while(--waittime)	//�ȴ�����ʱ
        {
            delay_ms(10);

            if(USART2_RX_STA & 0X8000) //���յ��ڴ���Ӧ����
            {
                if(atk_8266_check_cmd(ack))
                {
//                    printf("ack:%s\r\n", (u8*)ack);
                    break;//�õ���Ч����
                }

                USART2_RX_STA = 0;
            }
        }

        if(waittime == 0)res = 1;
    }

    return res;
}

void inint_wifi(void)
{
    u8 p[80];
    u3_printf("+++");	//ֹͣ��͸
    delay_ms(1500);
    atk_8266_send_cmd("AT+CWMODE=3", "OK", 50);		//����WIFI STAģʽ
    sprintf((char*)p, "AT+CWJAP=\"%s\",\"%s\"", wifista_ssid, wifista_password); //�������߲���:ssid,����
    while(atk_8266_send_cmd(p, "OK", 300));					//����Ŀ��·����,���һ��IP
    atk_8266_send_cmd("AT+CIPMUX=0", "OK", 20); //������ģʽ
    sprintf((char*)p, "AT+CIPSTART=\"TCP\",\"%s\",%s", (u8*)ipbuf, (u8*)portnum);
    atk_8266_send_cmd(p, "OK", 200);
    atk_8266_send_cmd("AT+CIPMODE=1", "OK", 200);    //����ģʽΪ��͸��
    atk_8266_send_cmd("AT+CIPSEND", "OK", 20);     //��ʼ͸��
	u3_printf("����");

}

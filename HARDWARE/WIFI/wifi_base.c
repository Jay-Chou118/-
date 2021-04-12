#include "wifi_base.h"
#include "sys.h"
#include "data_type.h"
#include "delay.h"

extern u16 USART2_RX_STA;         		//接收状态标记
extern u8  USART2_RX_BUF[USART_REC_LEN2]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	//发送缓冲,最大USART2_MAX_SEND_LEN字节//对齐，确保发送不乱码
const u8* portnum = "7070";
const u8* wifista_ssid = "mFi_03F772";			//路由器SSID号
const u8* wifista_password = "1234567890"; 	//连接密码
const u8* ipbuf = "192.168.0.101"; 	//ip

//ATK-ESP8266发送命令后,检测接收到的应答
//str:期待的应答结果
//返回值:0,没有得到期待的应答结果
//    其他,期待应答结果的位置(str的位置)
u8* atk_8266_check_cmd(u8 *str)
{

    char *strx = 0;

    if(USART2_RX_STA & 0X8000)		//接收到一次数据了
    {
        USART2_RX_BUF[USART2_RX_STA & 0X7FFF] = 0; //添加结束符
        printf("ack:%s", USART2_RX_BUF);
        strx = strstr((const char*)USART2_RX_BUF, (const char*)str);
    }

    return (u8*)strx;
}

//串口3,printf 函数
//确保一次发送数据不超过USART2_MAX_SEND_LEN字节
void u3_printf(char* fmt, ...)
{
    u16 i, j;
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char*)USART2_TX_BUF, fmt, ap);
    va_end(ap);
    i = strlen((const char*)USART2_TX_BUF); //此次发送数据的长度

    for(j = 0; j < i; j++) //循环发送数据
    {
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); //等待上次传输完成

        USART_SendData(USART2, (uint8_t)USART2_TX_BUF[j]); 	 //发送数据到串口3
    }

}
//向ATK-ESP8266发送命令
//cmd:发送的命令字符串
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 atk_8266_send_cmd(u8 *cmd, u8 *ack, u16 waittime)
{
    u8 res = 0;
    USART2_RX_STA = 0;

    u3_printf("%s\r\n", cmd);	//发送命令

    if(ack && waittime)		//需要等待应答
    {
        while(--waittime)	//等待倒计时
        {
            delay_ms(10);

            if(USART2_RX_STA & 0X8000) //接收到期待的应答结果
            {
                if(atk_8266_check_cmd(ack))
                {
//                    printf("ack:%s\r\n", (u8*)ack);
                    break;//得到有效数据
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
    u3_printf("+++");	//停止穿透
    delay_ms(1500);
    atk_8266_send_cmd("AT+CWMODE=3", "OK", 50);		//设置WIFI STA模式
    sprintf((char*)p, "AT+CWJAP=\"%s\",\"%s\"", wifista_ssid, wifista_password); //设置无线参数:ssid,密码
    while(atk_8266_send_cmd(p, "OK", 300));					//连接目标路由器,并且获得IP
    atk_8266_send_cmd("AT+CIPMUX=0", "OK", 20); //单链接模式
    sprintf((char*)p, "AT+CIPSTART=\"TCP\",\"%s\",%s", (u8*)ipbuf, (u8*)portnum);
    atk_8266_send_cmd(p, "OK", 200);
    atk_8266_send_cmd("AT+CIPMODE=1", "OK", 200);    //传输模式为：透传
    atk_8266_send_cmd("AT+CIPSEND", "OK", 20);     //开始透传
	u3_printf("连接");

}

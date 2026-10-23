#include "delay.h"
#include "usart.h" 
#include "led.h"
#include "relay.h"
#include "dht11.h"
#include "string.h"
#include "stdio.h"

/************************************************
 SR602演示程序
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
************************************************/

//串口数据包长度
u16 USART1_RX_LEN = 0;       //接收计数器
u16 USART2_RX_LEN = 0;       //接收计数器 
u16 USART3_RX_LEN = 0;       //接收计数器 
u16 RS485_RX_LEN = 0;       //接收计数器

char alarm[] = {"alarm\n"};
char safety[] = {"safty\n"};
int main(void)
{
    u8 temperaturez;//定义1个无符号的整型数据，存储温度的整数部分
    u8 temperaturex;//定义1个无符号的整型数据，存储温度的小数部分
    
    u8 humidityz;        //定义1个无符号的整形数据，储存湿度的整数部分
    u8 humidityx;     //定义1个无符号的整形数据，储存湿度的小数部分

    char txbuf[20];//定义一个字符型的数组，用于存储最后先发送的内容，T:25.12℃,H:38.16%RH
    
    
    //初始化
    LED_Init();            //LED初始化
  USART1_init(9600);        //串口初始化
    delay_init(); //延时函数初始化
    DHT11_Init();     //DHT11引脚初始化
    
    
    //读取温度值
    while(1)
    {
        if(DHT11_Read_Data(&temperaturez,&temperaturex,&humidityz,&humidityx)==0)//函数返回值为 0 时，代表数据读取成功
        {sprintf(txbuf,"T:%d.%d C  H:%d.%d %%RH \r\n",temperaturez,temperaturex,humidityz,humidityx);//温湿度存储到字符数组 txbuf
        USART1_Send_String((u8*) txbuf);  //串口1打印温湿度数据
            if(temperaturez >29)
            {
                USART1_Send_String((u8*)alarm);            //打印alarm
            }
        }
    delay_ms(1000);        //休息1s
    }
}
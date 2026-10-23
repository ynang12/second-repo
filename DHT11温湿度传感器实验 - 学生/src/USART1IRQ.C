#include "delay.h"
#include "usart.h" 

u16 uart_sent_counter = 0x30;
extern u16 USART1_RX_STA;
extern u8 USART1_RX_BUF[USART_REC_LEN];
/************************************************
 EX-TKS系统网关板
 串口实验 
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
************************************************/
 int main(void)
 {
	u16 t;  
	u16 len;	
//	u16 times=0;
	
	delay_init();	    	 //延时函数初始化	  
	uart1_init(115200);					//初始化串口1	
	uart1_initIRQ();	 
 	while(1)
	{
		if(USART1_RX_STA&0x8000)
		{					   
			len=USART1_RX_STA&0x3fff;//得到此次接收到的数据长度
			//printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART1_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}			
			//printf("\r\n\r\n");//插入换行
			USART1_RX_STA=0;
		}	
	}	 
}

#include "delay.h"
#include "usart.h" 

u16 uart_sent_counter = 0x30;
	
/************************************************
 EX-TKS系统网关板
 串口实验 
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
************************************************/
 int main(void)
 {
	delay_init();	    	 //延时函数初始化	  
	uart1_init(115200);					//初始化串口1	
 	while(1)
	{
		USART_SendData(USART1, uart_sent_counter++);//向串口1发送数据 	
		delay_ms(1000);	
		if(uart_sent_counter == 0x3A) uart_sent_counter = 0x30;
	}	 
}

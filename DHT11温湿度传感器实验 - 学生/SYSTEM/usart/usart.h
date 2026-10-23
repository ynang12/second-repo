#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 


#define USART_REC_LEN  			300  	//定义最大接收字节数 300

#define RS485_TX_MODE 	GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define RS485_RX_MODE		GPIO_ResetBits(GPIOA,GPIO_Pin_8)
	  	
//定义各个串口接收缓存区	
extern u8 USART1_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u8 USART2_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u8 USART3_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u8 RS485_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

//接收状态，接收完一帧数据包（小于200字节）
extern u16 USART1_RX_STA ;       //接收状态标记	  
extern u16 USART2_RX_STA ;       //接收状态标记	  
extern u16 USART3_RX_STA;       //接收状态标记	  
extern u16 RS485_RX_STA;       //接收状态标记	

//串口数据包长度
extern u16 USART1_RX_LEN;       //有效数据包长度
extern u16 USART2_RX_LEN;       //有效数据包长度
extern u16 USART3_RX_LEN;       //有效数据包长度
extern u16 RS485_RX_LEN;       //有效数据包长度

//如果想串口中断接收，请不要注释以下宏定义
//串口USART1配置函数（初始化）
void USART1_init(u32 bound);
void USART2_init(u32 bound);
void USART3_init(u32 bound);
void UART4_init(u32 bound);
void RS485_init(u32 bound);
/**********************************************************
串口发送函数
***********************************************************/
void USART1_Send_Byte(u8 Data) ;
void USART1_Send_String(u8 *Data);
void USART1_Send_BUF(u8 *buf,u8 len) ;
void USART2_Send_Byte(u8 Data);
void USART2_Send_String(u8 *Data);
void USART2_Send_BUF(u8 *buf,u8 len);
void USART3_Send_Byte(u8 Data);
void USART3_Send_String(u8 *Data);
void USART3_Send_BUF(u8 *buf,u8 len);
void UART4_Send_Byte(u8 Data);
void UART4_Send_String(u8 *Data);
void UART4_Send_BUF(u8 *buf,u8 len);
void RS485_Send_Byte(u8 Data);
void RS485_Send_String(u8 *Data);
void RS485_Send_BUF(u8 *buf,u8 len);
#endif



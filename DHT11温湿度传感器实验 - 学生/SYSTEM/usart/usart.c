#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
/************************************************
EX-CM3-A
串口驱动
技术支持：18034701190
淘宝店铺：http://iotedu.taobao.com 
作者：EXIOT
************************************************/   

//定义各个串口接收缓存区	
u8 USART1_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u8 USART2_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u8 USART3_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u8 RS485_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

//接收状态，接收完一帧数据包（小于300字节）
u16 USART1_RX_STA = 0;       //接收状态标记	  
u16 USART2_RX_STA = 0;       //接收状态标记	  
u16 USART3_RX_STA = 0;       //接收状态标记	  
u16 RS485_RX_STA = 0;       //接收状态标记

//串口接收计数器
u16 USART1_RX_counter = 0;       //接收计数器
u16 USART2_RX_counter = 0;       //接收计数器 
u16 USART3_RX_counter = 0;       //接收计数器 
u16 UART4_RX_counter = 0;       //接收计数器


//串口USART1配置函数（初始化）
void USART1_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟（TX1:A9;RX1:A10）

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         		 					//USART1 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 					//复用推免输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 							//A端口
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         	 					//USART1 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   				//复用开漏输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);		         	 						//A端口
 
	USART_InitStructure.USART_BaudRate = bound;											//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;							//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//无流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
 
	USART_Init(USART1, &USART_InitStructure);												//初始化USART1
	USART1_RX_LEN = 0;
	USART1_RX_STA = 0;
	USART1_RX_counter = 0;
	//USART1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //允许接收中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);									//允许IDLE中断

	USART_Cmd(USART1, ENABLE); 																			//使能USART1	
} 


//串口USART2配置函数（初始化）
void USART2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟（TX2:A2;RX2:A3）

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         		 					//USART1 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 					//复用推免输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 							//A端口
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	         	 					//USART1 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   				//复用开漏输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);		         	 						//A端口
 
	USART_InitStructure.USART_BaudRate = bound;											//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;							//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//无流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
 
	USART_Init(USART2, &USART_InitStructure);												//初始化USART2
 
	//USART2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                  //允许接收中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);									//允许IDLE中断

	USART_Cmd(USART2, ENABLE); 																			//使能USART2	
}  

//串口USART3配置函数（初始化）
void USART3_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟（TX3:B10;RX3:B11）

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         		 					//USART3 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 					//复用推免输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);		    		 							//A端口
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	         	 					//USART3 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   				//复用开漏输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);		         	 						//A端口
 
	USART_InitStructure.USART_BaudRate = bound;											//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;							//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//无流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
 
	USART_Init(USART3, &USART_InitStructure);												//初始化USART3
 
	//USART2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                  //允许接收中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);									//允许IDLE中断

	USART_Cmd(USART3, ENABLE); 																			//使能USART3
}

//串口UART4配置函数（初始化）
void UART4_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//使能UART4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能GPIOB时钟（TX4:C10;RX4:C11）

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         		 					//USART4 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 					//复用推免输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);		    		 							//A端口
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	         	 					//USART4 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   				//复用开漏输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);		         	 						//C端口
 
	USART_InitStructure.USART_BaudRate = bound;											//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;							//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//无流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
 
	USART_Init(UART4, &USART_InitStructure);												//初始化USART4
 
	//USART2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);                  //允许接收中断
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);									//允许IDLE中断

	USART_Cmd(UART4, ENABLE); 																			//使能USART3	
}

//RS485初始化
void RS485_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟（A8）
	
	//RS485输入输出控制引脚配置：A8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);//RS485为接收模式	
	
	UART4_init(bound);	
}
/**********************************************************
串口1接收中断函数
***********************************************************/
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //
	{
		USART1_RX_BUF[USART1_RX_counter] = USART_ReceiveData(USART1);	//读取接收到的数据	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART1_RX_counter++;
  }	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  //
	{
		USART1_RX_LEN = USART1_RX_counter;
		USART1_RX_STA = 1;//正确接收到一包数据
		USART1->SR;
		USART1->DR;
		USART1_RX_counter = 0;
  } 	
}

/**********************************************************
串口2接收中断函数
***********************************************************/
void USART2_IRQHandler(void)                	//串口2中断服务程序
{
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //
	{
		USART2_RX_BUF[USART2_RX_counter] = USART_ReceiveData(USART2);	//读取接收到的数据	
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		USART2_RX_counter++;
  }	
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)  //
	{
		USART2_RX_LEN = USART2_RX_counter;
		USART2->SR;
		USART2->DR;
		USART2_RX_counter = 0;
		USART2_RX_STA = 1;//正确接收到一包数据
  } 	
}

/**********************************************************
串口3接收中断函数
***********************************************************/
void USART3_IRQHandler(void)                	//串口3中断服务程序
{
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //
	{
		USART3_RX_BUF[USART3_RX_counter] = USART_ReceiveData(USART3);	//读取接收到的数据	
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		USART3_RX_counter++;
  }	
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //
	{
		USART3_RX_LEN = USART3_RX_counter;
		USART3->SR;
		USART3->DR;
		USART3_RX_counter = 0;
		USART3_RX_STA = 1;//正确接收到一包数据
  } 	
}

/**********************************************************
串口4接收中断函数
***********************************************************/
void UART4_IRQHandler(void)                	//串口4中断服务程序
{
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //
	{
		RS485_RX_BUF[UART4_RX_counter] = USART_ReceiveData(UART4);	//读取接收到的数据
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		UART4_RX_counter++;
  }	
	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  //
	{
		RS485_RX_LEN = UART4_RX_counter;
		UART4->SR;
		UART4->DR;
		UART4_RX_counter = 0;
		RS485_RX_STA = 1;//正确接收到一包数据
  } 	
}

/**********************************************************
串口1发送函数
***********************************************************/
void USART1_Send_Byte(u8 Data) //发送一个字节
{
	USART_SendData(USART1,Data);
	while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
}

void USART1_Send_String(u8 *Data) //发送字符串
{
	USART_ClearFlag(USART1, USART_FLAG_TC );
	while(*Data)
	USART1_Send_Byte(*Data++);
}

void USART1_Send_BUF(u8 *buf,u8 len) //发送数据包
{
	u8 i;
	USART_ClearFlag(USART1, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			USART1_Send_Byte(*(buf+i));
	}
}

/**********************************************************
串口2发送函数
***********************************************************/
void USART2_Send_Byte(u8 Data) //发送一个字节
{
	USART_SendData(USART2,Data);
	while( USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET );
}

void USART2_Send_String(u8 *Data) //发送字符串
{
	USART_ClearFlag(USART2, USART_FLAG_TC);
	while(*Data)
	USART2_Send_Byte(*Data++);
}

void USART2_Send_BUF(u8 *buf,u8 len) //发送数据包
{
	u8 i;
	USART_ClearFlag(USART2, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			USART2_Send_Byte(*(buf+i));
	}
}

/**********************************************************
串口3发送函数
***********************************************************/
void USART3_Send_Byte(u8 Data) //发送一个字节
{
	USART_SendData(USART3,Data);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
}

void USART3_Send_String(u8 *Data) //发送字符串
{
	USART_ClearFlag(USART3, USART_FLAG_TC );
	while(*Data)
	USART3_Send_Byte(*Data++);
}

void USART3_Send_BUF(u8 *buf,u8 len) //发送数据包
{
	u8 i;
	USART_ClearFlag(USART3, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			USART3_Send_Byte(*(buf+i));
	}
}

/**********************************************************
串口4发送函数
***********************************************************/
void UART4_Send_Byte(u8 Data) //发送一个字节
{
	//GPIO_SetBits(GPIOA,GPIO_Pin_8);//RS485为发送模式	
	USART_SendData(UART4,Data);
	while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );
}

void UART4_Send_String(u8 *Data) //发送字符串
{
	USART_ClearFlag(UART4, USART_FLAG_TC );
	while(*Data)
	UART4_Send_Byte(*Data++);
}

void UART4_Send_BUF(u8 *buf,u8 len) //发送数据包
{
	u8 i;
	USART_ClearFlag(UART4, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			UART4_Send_Byte(*(buf+i));
	}
}

//RS485接口发送函数
void RS485_Send_Byte(u8 Data) //发送一个字节
{
	RS485_TX_MODE;//RS485为发送模式	
	USART_SendData(UART4,Data);
	while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );
	RS485_RX_MODE;//RS485为接收模式	
}

void RS485_Send_String(u8 *Data) //发送字符串
{
	RS485_TX_MODE;//RS485为发送模式	
	USART_ClearFlag(UART4, USART_FLAG_TC );
	while(*Data)
	UART4_Send_Byte(*Data++);
	RS485_RX_MODE;//RS485为接收模式	
}

void RS485_Send_BUF(u8 *buf,u8 len) //发送数据包
{
	u8 i;
	RS485_TX_MODE;//RS485为发送模式	
	USART_ClearFlag(UART4, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			UART4_Send_Byte(*(buf+i));
	}
	RS485_RX_MODE;//RS485为接收模式	
}

#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif

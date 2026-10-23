#ifndef __RELAY_H
#define __RELAY_H	

#include "sys.h"
/************************************************
 EX-CM3-A
 继电器驱动
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
************************************************/  

#define RELAY1 	1				//A11
#define RELAY2 	2				//A12

#define CLOSE 	0			//继电器闭合
#define BREAK 	1			//继电器断开

void RELAY_Init(void);
void Relay_Control(u8 relay,u8 state);
#endif

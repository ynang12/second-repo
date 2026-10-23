#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
/************************************************
 EX-CM3-A
 led驱动
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
************************************************/  

#define RLED 1	//D3-PB5
#define YLED 2	//D4-PB4
#define GLED 4	//D6-PB3

void LED_Init(void);
void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Turn_ON_LED(u8 led);
void Turn_OFF_LED(u8 led);
void RLED_ON(void);
void YLED_ON(void);
void GLED_ON(void);
void RLED_OFF(void);
void YLED_OFF(void);
void GLED_OFF(void);		 				    
#endif

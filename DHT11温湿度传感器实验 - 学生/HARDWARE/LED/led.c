#include "led.h"

/************************************************
 EX-CM3-A
 led驱动
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
************************************************/  

//初始化PB3\4\5为输出口
//LED IO初始化
void LED_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure; 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);// PB3\PB4\PA15重映射作为普通IO。	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB 
	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);						 //PB.3/4/5 输出高（灯灭）	
}

//取反GPIO
void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if(GPIO_ReadOutputDataBit(GPIOx,GPIO_Pin))
	{
		GPIO_ResetBits(GPIOx,GPIO_Pin); 	
	}
	else
	{
		GPIO_SetBits(GPIOx,GPIO_Pin); 	
	}
}

void Turn_ON_LED(u8 led)
{
	if(led & RLED)GPIO_ResetBits(GPIOB,GPIO_Pin_5);	
	if(led & YLED)GPIO_ResetBits(GPIOB,GPIO_Pin_4);	
	if(led & GLED)GPIO_ResetBits(GPIOB,GPIO_Pin_3);	
}

void Turn_OFF_LED(u8 led)
{
	if(led & RLED)GPIO_SetBits(GPIOB,GPIO_Pin_5);	
	if(led & YLED)GPIO_SetBits(GPIOB,GPIO_Pin_4);	
	if(led & GLED)GPIO_SetBits(GPIOB,GPIO_Pin_3);	
}

void RLED_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);						 //
}

void YLED_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);						 //
}

void GLED_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);						 //
}

void RLED_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //
}

void YLED_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_4);						 //
}

void GLED_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_3);						 //
}


 

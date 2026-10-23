#include "relay.h"


void RELAY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟（A11;A12）
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	//IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 			//根据设定参数初始化GPIOB 
	GPIO_ResetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12);					//继电器默认处于常闭状态
}

//继电器控制函数
void Relay_Control(u8 relay,u8 state)
{
	if(relay == RELAY1)
	{
		if(state == CLOSE){
			GPIO_SetBits(GPIOA,GPIO_Pin_11);							//继电器1闭合
		}
		else if(state == BREAK){
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);						//继电器1断开
		}	
	}
	else if(relay == RELAY2)
	{
		if(state == CLOSE){
			GPIO_SetBits(GPIOA,GPIO_Pin_12);							//继电器2闭合
		}
		else if(state == BREAK){
			GPIO_ResetBits(GPIOA,GPIO_Pin_12);						//继电器2断开
		}
	}
}



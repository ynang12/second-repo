#include "iosensor.h"


//SR602初始化
void IO_SENSOR_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟（PB2）

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         		 					//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;   		 					//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);		    		 							//B端口
} 

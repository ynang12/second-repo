#ifndef __IOSENSOR_H
#define __IOSENSOR_H	 
#include "sys.h"

/************************************************
 传感器扩展板
 IO传感器驱动
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
 ************************************************/  
 
 
 
#define READ_IO_SENSOR() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)
#define IOH 1
#define IOL 0

void IO_SENSOR_INIT(void);  

 #endif
 
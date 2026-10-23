#ifndef __DHT11_H
#define __DHT11_H	

#include "sys.h"
/************************************************
 EX-CM3-A
 继电器驱动
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
************************************************/  

#define DHT11_IO_IN(){GPIOB->CRL&=0XFFFFF0FF;GPIOB->CRL|=8<<8;}
#define DHT11_IO_OUT(){GPIOB->CRL&=0XFFFFF0FF;GPIOB->CRL|=3<<8;}
////IO 操作函数
#define DHT11_DQ_OUT PBout(2) //数据端口 PB2
#define DHT11_DQ_IN PBin(2) //数据端口 PB2
u8 DHT11_Init(void);//初始化 DHT11
u8 DHT11_Read_Data(u8 *tempz,u8 *tempx,u8 *humiz,u8 *humix);
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在 DHT11
void DHT11_Rst(void);//复位 DHT11

#endif

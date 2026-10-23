#include "dht11.h"
#include "delay.h"
/************************************************
EX-CM3-A/B
DHT11 驱动---PB2
技术支持： 18034701190
淘宝店铺： http://iotedu.taobao.com
作者： EXIOT
************************************************/
//复位 DHT11
void DHT11_Rst(void)
{
DHT11_IO_OUT(); //SET OUTPUT
DHT11_DQ_OUT=0; //拉低 DQ
delay_ms(20); //拉低至少 18ms
DHT11_DQ_OUT=1; //DQ=1
delay_us(30); //主机拉高 20~40us
}
//等待 DHT11 的回应
//返回 1:未检测到 DHT11 的存在
//返回 0:存在
u8 DHT11_Check(void)
{
u8 retry=0;
DHT11_IO_IN();//SET INPUT
while (DHT11_DQ_IN&&retry<100)//DHT11 会拉低 40~80us
{
retry++;
delay_us(1);
};
if(retry>=100)return 1;
else retry=0;
while (!DHT11_DQ_IN&&retry<100)//DHT11 拉低后会再次拉高40~80us
	{
retry++;
delay_us(1);
};
if(retry>=100)return 1;
return 0;
}
//从 DHT11 读取一个位
//返回值： 1/0
u8 DHT11_Read_Bit(void)
{
u8 retry=0;
while(DHT11_DQ_IN&&retry<100)//等待变为低电平
{
retry++;
delay_us(1);
}
retry=0;
while(!DHT11_DQ_IN&&retry<100)//等待变高电平
{
retry++;
delay_us(1);
}
delay_us(40);//等待 40us
if(DHT11_DQ_IN)return 1;
else return 0;
}
//从 DHT11 读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)
{
u8 i,dat;
dat=0;
for (i=0;i<8;i++)
{
dat<<=1;
dat|=DHT11_Read_Bit();
}
return dat;
}
//从 DHT11 读取一次数据
//temp:温度值(范围:0~50° )
//humi:湿度值(范围:20%~90%)
//返回值： 0,正常;1,读取失败
u8 DHT11_Read_Data(u8 *tempz,u8 *tempx,u8 *humiz,u8 *humix)
{
u8 buf[5];
u8 i;
DHT11_Rst();
if(DHT11_Check()==0)
{
for(i=0;i<5;i++)//读取 40 位数据
{
buf[i]=DHT11_Read_Byte();
}
if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
{
  *humiz=buf[0];
	*humix=buf[1];
	*tempz=buf[2];
	*tempx=buf[3];
}
}else return 1;
return 0;
}
//初始化 DHT11 的 IO 口 DQ 同时检测 DHT11 的存在
//返回 1:不存在
//返回 0:存在
u8 DHT11_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//使能 PB 端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//PB2 端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 IO 口
	GPIO_SetBits(GPIOB,GPIO_Pin_11); //PG11 输出高
	DHT11_Rst(); //复位 DHT11
	return DHT11_Check();//等待 DHT11 的回应
}
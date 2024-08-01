#ifndef	__INFRARED_H
#define	__INFRARED_H
#define uchar unsigned char
#define uint unsigned int	//类型转义

//************* 红外遥控 ***************
extern bit irpro_ok,irok;
extern uchar IRcord[];
extern uchar irdata[];
extern uchar irtime;					//红外用全局变量

void Ir_work(void);
void Ircordpro(void);
void delay(uint z);		//延时
void IRInit();		//串口+定时器初始化


				
#endif
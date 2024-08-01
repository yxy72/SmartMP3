/*********************************************************************************
* 【作    者】：	清翔电子:向量
* 【版    本】：	V1.0
* 【网    站】：	http://www.qxmcu.com/ 
* 【淘宝店铺】：	http://qxmcu.taobao.com/
* 【实验平台】：	清翔 QX-MCS51 单片机开发板
* 【外部晶振】： 	11.0592mhz	
* 【主控芯片】： 	STC89C52
* 【编译环境】： 	Keil μVisio4	
* 【程序功能】： 	4*4矩阵键盘与4位独立键盘识别		   			            			    
* 【使用说明】： 	按下矩阵键盘和独立键盘任意键，数码管显示相应数值
					初始显示“-”横
**********************************************************************************/
#include <STC12C5A60S2.h>//包含51头文件
#include <intrins.h>//包含移位标准库函数头文件

#define uint unsigned int
#define uchar unsigned char

uchar num;//数码管显示的值
uchar KeyValue = 20;//按键值 显示-





/*====================================
函数	： delay(uint z)
参数	：z 延时毫秒设定，取值范围0-65535
返回值	：无
描述	：12T/Fosc11.0592M毫秒级延时
====================================*/
void delay11(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 
/*====================================
函数	：KeyScan()
参数	：无
返回值	：无
描述	：4*4矩阵键盘与独立键盘扫描
按键按下KeyValue全局变量值发生相应变化
====================================*/
void KeyScan()
{
	//4*4矩阵键盘扫描
	P3 = 0XF0;//列扫描
	if(P3 != 0XF0)//判断按键是否被按下
	{
		delay11(10);//软件消抖10ms
		if(P3 != 0XF0)//判断按键是否被按下
		{
			switch(P3) //判断那一列被按下
			{
				case 0xe0:	KeyValue = 0;	break;//第一列被按下
				case 0xd0:	KeyValue = 1;	break;//第二列被按下
				case 0xb0:	KeyValue = 2;	break;//第三列被按下
				case 0x70:	KeyValue = 3;	break;//第四列被按下 
			}
			P3 = 0X0F;//行扫描
			switch(P3) //判断那一行被按下
			{
				case 0x0e:	KeyValue = KeyValue;	break;//第一行被按下
				case 0x0d:	KeyValue = KeyValue + 4;	break;//第二行被按下
				case 0x0b:	KeyValue = KeyValue + 8;	break;//第三行被按下
				case 0x07:	KeyValue = KeyValue + 12;	break;//第四行被按下 
			}
			while(P3 != 0X0F);//松手检测	
			done = 1;
		}
	}


}


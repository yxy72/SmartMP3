/*=============Uart.c=================
	串口相关
====================================*/
#include <STC12C5A60S2.h>
#include "Uart.h"
#include "value.h"
void Uart_init(){
	TMOD |= 0X20;		//T1  方式2  ，8位   自动重装   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600
	TR1=1; 		  // 定时器1启动  
	SM0=0;	    // 设置串口的工作模式
	SM1=1; 	    // 方式1
	REN=1; 		 	// 允许串口接收数据 	 
	ES=1; 	    // 串口中断应许 
}
void uart_rx() interrupt 4 using 3{	 
	EA=0; 
	if((RsPoint<RsBuf_N)&&RI){ 
		RI=0;
		if(SBUF=='O')
			RsPoint=0;
		RsBuf[RsPoint++]=SBUF;
  }
	EA=1;
}

void SendASC(unsigned char d){
	SBUF=d;
	while(!TI);
	TI=0;
}
void SendOrder(unsigned char *str){
	while(*str!=0xff){
		SendASC(*str) ;
		str++;
	}
}
void Uart2_init(){                //9600bps@11.0592MHz      
	AUXR |= 0x08;                //使能波特率倍速位S2SMOD：（波特率加倍）
	S2CON = 0x50;                //8位数据,可变波特率
	AUXR &= 0xFB;                //独立波特率发生器时钟为Fosc/12,即12T      
	BRT = 0xFA;                //设定独立波特率发生器重装值     
	AUXR |= 0x10;                //启动独立波特率发生器
}


void Uart2_SendASC(unsigned char date){//自己改下名称 不要一样

	S2BUF=date;
	while((S2CON&0X02)==0);
	S2CON&=~0X02;              //清除发送标志位

}

void Uart2_SendOrder(unsigned char *p){   //串口2发送一个字符串
	while(*p!='\0'){
		Uart2_SendASC(*p);
		p++;
	}
}


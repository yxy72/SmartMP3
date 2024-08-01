/*==============IR.c=================
	红外接收处理，外部中断0
====================================*/
#include "STC12C5A60S2.h"
#include "IR.h"
#include "value.h"
#define uchar unsigned char
#define uint unsigned int	//类型转义
bit irok;
//bit lightOn = 1;
//uchar pwmSort = 0;
uchar IRcord[4];
uchar irdata[33];
uchar irtime;	//红外用全局变量
uint i7 = 0;
//uint i8 = 0;
void Ir_work(void)//红外键值散转程序
{   
		switch(IRcord[2]){    //判断按键键码值
		case 0x16:IR_Option = irPP;break; 		
		case 0x18:IR_Option = irUp; break;		
		case 0x08:IR_Option = irLeft; break; 	 
		case 0x1C:IR_Option = irOK; break;		
		case 0x5A:IR_Option = irRight; break;		
		case 0x52:IR_Option = irdown; break;  	
		case 0x07:IR_Option = num7; 	break;	
		case 0x15:IR_Option = num8;	break;	
		case 0x09:IR_Option = num9;			break;	
		case 0x44:IR_Option = num4;	break;	
		case 0x40:IR_Option = num5;break;	                      
		case 0x43:IR_Option = num6;break;	
		case 0x45:IR_Option = num1;		break;	
		case 0x46:IR_Option = num2;				break;	
		case 0x47:IR_Option = num3;	break;
		case 0x19:IR_Option = num0;break;	
		case 0x0D:IR_Option = irReturn;break;	
		default :break; 
		}
		delay(1); 
		IRDone = 1;
}
void Ircordpro(void)//红外码值处理函数
{ 
	uchar i, j, k,cord,value;
	k=1;
	for(i=0;i<4;i++) {			//处理4个字节
		for(j=1;j<=8;j++) {		//处理1个字节8位
			cord=irdata[k];
			if(cord>7)			//大于某值为1，这个和晶振有绝对关系，这里使用12M计算，此值可以有一定误差
			value=value|0x80;
			if(j<8) {
				value>>=1;
			}
			k++;
		}
		IRcord[i]=value;
		value=0;     
	} 
	Ir_work();
}

void delay(uint z)		//@11.0592MHz
{
	uchar i, j;
	i = 11,j = 190;
	while(z--) {
		do {
			while (--j);
		} while (--i);
	}
}

//定时器0
void IRInit() {

	IT0 = 1;					//指定外部中断0下降沿触发，INT0 (P3.2)
 	EX0 = 1;					//使能外部中断
	//定时器0 对应interrupt 1
	TMOD|=0x02;					//定时器0工作方式2，TH0是重装值，TL0是初值	
	TH0=0x00;TL0=0x00;			//初始化值	
	ET0=1;						//定时器0中断打开
	TR0=1;						//定时器0开关打开

}
void EX0_ISR (void) interrupt 0 //外部中断0服务函数
{
	static uchar i;             //接收红外信号处理
	static bit startflag;       //是否开始处理标志位
if(!v_IR)
	return;
if(!IRProcessOK)
	return;
	if(startflag) {                        
		if(irtime<63&&irtime>=33) { //引导码 TC9012的头码，9ms+4.5ms
            i=0;
		}
		irdata[i]=irtime;//存储每个电平的持续时间，用于以后判断是0还是1
		irtime=0;
		i++;
		if(i==33) {
  			irok=1;i=0;
			Ircordpro();
			irok=0;
  		}
	} else {
		irtime=0;
		startflag=1;
	}
}

void time0() interrupt 1
{
	TR0=0;
	irtime++;  //人家说什么红外中断计时里不能加东西，不然影响红外，确实。所以把原本执行的语句弄到PCA定时器（LED.c）去了。
	TR0=1;   
}
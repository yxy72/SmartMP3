/*=============LED.c=================
	全彩/呼吸灯生成、主时间中断
====================================*/
#include <STC12C5A60S2.h>
#include "LED.h"
#include "value.h"
#define value1 (11059pTimeOverL/12/PWMTOver)
bit lightOn = 1;
#define u8 unsigned char

unsigned int mainTime = 0;
unsigned int value;
unsigned int i8 = 0;
unsigned int shakeCNT = 0;
u8 pwmSort = 0;
u8 pwmTime = 0,flag = 1;
u8 PWM_T = 0;   //占空比控制变
u8 CrrLedMode;
u8 redOnPause;
u8 powerOn = 1,powerOff,pinOn,pinOff;//便于共阴共阳LED切换使用 powerOn = [0共阴/1共阳]
u8 pTimeOver = 200,PWMTOver = 75;

unsigned char RG=1,GB=0,BR=0;
void shining();
void breath();


void Init_PWM()         //  PWM功能的初始化
{
	CCON = 0;
	CL = 0;
	CH = 0;
	CMOD = 0X00;
	value = 72;//5MS  46080 50MS  72=0.078125ms  
	CCAP1L = value;
	CCAP1H = value>>8;
	value +=72;
	CCAPM1 = 0x49;
	CR = 1;
	mainTime=0;
	
	PPCA = 1;	//IP寄存器^7
	IPH |= 0x80;	//设置IPH寄存器和IP寄存器使得PCA中断成为【最高优先级】（呼吸灯给爷 永！远！不！断！）
	
	CrrLedMode = ledMode;
	
	redOnPause = !v_PP;
	
	
	
	powerOff = !powerOn;
	pinOn = !powerOn;
	pinOff = !pinOn;
	
	LED_Power = powerOn; LED_R = pinOn; LED_B = LED_G = pinOff;
	
} 
 
void MAIN_TIME() interrupt 7{	//全局主要时间中断
	CCF1 = 0;
	CCAP1L = value;
	CCAP1H = value>>8;
	value+=72;
	

	
	//进度条处理
	if(v_PP){
		mainTime++;
		if(mainTime==12800){ //0.078125*12800=1S
			mainTime = 0;
			if(v_timeSec_now != v_timeSec_total)
					v_timeSec_now++;
				else{
					playReachEnd1 = 1;
					
				}
				currentSecPaint = 1;
		}
	}
	
	//给爷振慢点！
	if(hasShaken){
		shakeCNT++;
		if(shakeCNT == 25600+6400){
			shakeCNT = 0;
			hasShaken = 0;
			canShake = 1;
		}
	}
	
	//LED处理
	if(CrrLedMode == ledMode){
		if(CrrLedMode == 1){
			if(redOnPause != (!v_PP)){
				redOnPause = !v_PP;
				if(redOnPause){
					LED_R = pinOn;LED_G = pinOff;
				}else
					LED_R = pinOff;
			}
			if(!redOnPause)
				breath();
		}else if(CrrLedMode == 2){
			if(redOnPause != (!v_PP)){
				redOnPause = !v_PP;
				if(!v_PP){
					LED_G = LED_B = pinOff; LED_R = pinOn;
				}
			}
			if(!redOnPause)
				shining();
			else{
				LED_G = LED_B = pinOff; LED_R  = pinOn;
			}
		}
	}else if(CrrLedMode != ledMode){
		CrrLedMode = ledMode;
		if(CrrLedMode == 0){
			LED_Power = powerOff ; LED_R = LED_G = LED_B = pinOff;
		}else if(CrrLedMode == 1){
			pwmTime = 0;flag = 1;
			PWM_T = 0; 
			LED_Power = powerOn ;
			if(!v_PP){
				LED_G = LED_B = pinOff;LED_R = pinOn;
			}
		}else if(CrrLedMode == 2){
			LED_Power = powerOn; 
			pwmTime = 0;flag = 1;
			PWM_T = 0;
			RG = 1;GB = 0;BR = 0;
		}
	}
	
	
	
	

	
}

void shining(){
		if(RG){
			pwmTime++;    						//每次定时器溢出加1
			if(pwmTime==pTimeOver){   			//PWM周期 PWMTOver个单位
				pwmTime=0;  						//使t=0，开始新的PWM周期
				LED_R = 1 ;  	//输出端口
				LED_G = 0;
				
				if(flag)
					PWM_T++;
				else
					PWM_T--;
				if(PWM_T==pTimeOver){
					 pwmTime = 0;flag = 1;
					 PWM_T = 0;   //占空比控制变
						RG = 0;GB = 1;
						return;
					
				}
				else if(PWM_T == 1)
					flag = 1;
			}
			if(pwmTime == PWM_T){ 			 //按照当前占空比切换输出为高电平 
					LED_R = 0 ;  	//输出端口
					LED_G = 1;
			}	
		}else if(GB){
			pwmTime++;    						//每次定时器溢出加1
			if(pwmTime==pTimeOver){   			//PWM周期 PWMTOver个单位
				pwmTime=0;  						//使t=0，开始新的PWM周期
				LED_G = 1 ;  	//输出端口
				LED_B = 0;
				
				if(flag)
					PWM_T++;
				else
					PWM_T--;
				if(PWM_T==pTimeOver){
					 pwmTime = 0;flag = 1;
					 PWM_T = 0;   //占空比控制变
						GB = 0;BR = 1;
						return;
					
				}
				else if(PWM_T == 1)
					flag = 1;
			}
			if(pwmTime == PWM_T){ 			 //按照当前占空比切换输出为高电平 
					LED_G = 0 ;  	//输出端口
					LED_B = 1;
			}	
		}else if(BR){
			pwmTime++;    						//每次定时器溢出加1
			if(pwmTime==pTimeOver){   			//PWM周期 PWMTOver个单位
				pwmTime=0;  						//使t=0，开始新的PWM周期
				LED_B = 1 ;  	//输出端口
				LED_R = 0;
				
				if(flag)
					PWM_T++;
				else
					PWM_T--;
				if(PWM_T==pTimeOver){
					 pwmTime = 0;flag = 1;
					 PWM_T = 0;   //占空比控制变
						BR = 0;RG = 1;
						return;
					
				}
				else if(PWM_T == 1)
					flag = 1;
			}
			if(pwmTime == PWM_T){ 			 //按照当前占空比切换输出为高电平 
					LED_B = 0 ;  	//输出端口
					LED_R = 1;
			}	
		}    
}

void breath(){
	pwmTime++;    						//每次定时器溢出加1
	if(pwmTime==pTimeOver){   			//PWM周期 PWMTOver个单位
		pwmTime=0;  						//使t=0，开始新的PWM周期
		LED_G = 1 ;  	//输出端口
				
		if(flag)
			PWM_T++;
		else
			PWM_T--;
		if(PWM_T==pTimeOver)
			flag = 0;
		else if(PWM_T == PWMTOver)
			flag = 1;
	}
	if(pwmTime == PWM_T){ 			 //按照当前占空比切换输出为高电平 
		LED_G = 0 ;  	//输出端口
	}	
}
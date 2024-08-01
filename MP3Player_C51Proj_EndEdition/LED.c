/*=============LED.c=================
	ȫ��/���������ɡ���ʱ���ж�
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
u8 PWM_T = 0;   //ռ�ձȿ��Ʊ�
u8 CrrLedMode;
u8 redOnPause;
u8 powerOn = 1,powerOff,pinOn,pinOff;//���ڹ�������LED�л�ʹ�� powerOn = [0����/1����]
u8 pTimeOver = 200,PWMTOver = 75;

unsigned char RG=1,GB=0,BR=0;
void shining();
void breath();


void Init_PWM()         //  PWM���ܵĳ�ʼ��
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
	
	PPCA = 1;	//IP�Ĵ���^7
	IPH |= 0x80;	//����IPH�Ĵ�����IP�Ĵ���ʹ��PCA�жϳ�Ϊ��������ȼ����������Ƹ�ү ����Զ�������ϣ���
	
	CrrLedMode = ledMode;
	
	redOnPause = !v_PP;
	
	
	
	powerOff = !powerOn;
	pinOn = !powerOn;
	pinOff = !pinOn;
	
	LED_Power = powerOn; LED_R = pinOn; LED_B = LED_G = pinOff;
	
} 
 
void MAIN_TIME() interrupt 7{	//ȫ����Ҫʱ���ж�
	CCF1 = 0;
	CCAP1L = value;
	CCAP1H = value>>8;
	value+=72;
	

	
	//����������
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
	
	//��ү�����㣡
	if(hasShaken){
		shakeCNT++;
		if(shakeCNT == 25600+6400){
			shakeCNT = 0;
			hasShaken = 0;
			canShake = 1;
		}
	}
	
	//LED����
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
			pwmTime++;    						//ÿ�ζ�ʱ�������1
			if(pwmTime==pTimeOver){   			//PWM���� PWMTOver����λ
				pwmTime=0;  						//ʹt=0����ʼ�µ�PWM����
				LED_R = 1 ;  	//����˿�
				LED_G = 0;
				
				if(flag)
					PWM_T++;
				else
					PWM_T--;
				if(PWM_T==pTimeOver){
					 pwmTime = 0;flag = 1;
					 PWM_T = 0;   //ռ�ձȿ��Ʊ�
						RG = 0;GB = 1;
						return;
					
				}
				else if(PWM_T == 1)
					flag = 1;
			}
			if(pwmTime == PWM_T){ 			 //���յ�ǰռ�ձ��л����Ϊ�ߵ�ƽ 
					LED_R = 0 ;  	//����˿�
					LED_G = 1;
			}	
		}else if(GB){
			pwmTime++;    						//ÿ�ζ�ʱ�������1
			if(pwmTime==pTimeOver){   			//PWM���� PWMTOver����λ
				pwmTime=0;  						//ʹt=0����ʼ�µ�PWM����
				LED_G = 1 ;  	//����˿�
				LED_B = 0;
				
				if(flag)
					PWM_T++;
				else
					PWM_T--;
				if(PWM_T==pTimeOver){
					 pwmTime = 0;flag = 1;
					 PWM_T = 0;   //ռ�ձȿ��Ʊ�
						GB = 0;BR = 1;
						return;
					
				}
				else if(PWM_T == 1)
					flag = 1;
			}
			if(pwmTime == PWM_T){ 			 //���յ�ǰռ�ձ��л����Ϊ�ߵ�ƽ 
					LED_G = 0 ;  	//����˿�
					LED_B = 1;
			}	
		}else if(BR){
			pwmTime++;    						//ÿ�ζ�ʱ�������1
			if(pwmTime==pTimeOver){   			//PWM���� PWMTOver����λ
				pwmTime=0;  						//ʹt=0����ʼ�µ�PWM����
				LED_B = 1 ;  	//����˿�
				LED_R = 0;
				
				if(flag)
					PWM_T++;
				else
					PWM_T--;
				if(PWM_T==pTimeOver){
					 pwmTime = 0;flag = 1;
					 PWM_T = 0;   //ռ�ձȿ��Ʊ�
						BR = 0;RG = 1;
						return;
					
				}
				else if(PWM_T == 1)
					flag = 1;
			}
			if(pwmTime == PWM_T){ 			 //���յ�ǰռ�ձ��л����Ϊ�ߵ�ƽ 
					LED_B = 0 ;  	//����˿�
					LED_R = 1;
			}	
		}    
}

void breath(){
	pwmTime++;    						//ÿ�ζ�ʱ�������1
	if(pwmTime==pTimeOver){   			//PWM���� PWMTOver����λ
		pwmTime=0;  						//ʹt=0����ʼ�µ�PWM����
		LED_G = 1 ;  	//����˿�
				
		if(flag)
			PWM_T++;
		else
			PWM_T--;
		if(PWM_T==pTimeOver)
			flag = 0;
		else if(PWM_T == PWMTOver)
			flag = 1;
	}
	if(pwmTime == PWM_T){ 			 //���յ�ǰռ�ձ��л����Ϊ�ߵ�ƽ 
		LED_G = 0 ;  	//����˿�
	}	
}
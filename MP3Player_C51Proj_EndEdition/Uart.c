/*=============Uart.c=================
	�������
====================================*/
#include <STC12C5A60S2.h>
#include "Uart.h"
#include "value.h"
void Uart_init(){
	TMOD |= 0X20;		//T1  ��ʽ2  ��8λ   �Զ���װ   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600
	TR1=1; 		  // ��ʱ��1����  
	SM0=0;	    // ���ô��ڵĹ���ģʽ
	SM1=1; 	    // ��ʽ1
	REN=1; 		 	// �����ڽ������� 	 
	ES=1; 	    // �����ж�Ӧ�� 
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
	AUXR |= 0x08;                //ʹ�ܲ����ʱ���λS2SMOD���������ʼӱ���
	S2CON = 0x50;                //8λ����,�ɱ䲨����
	AUXR &= 0xFB;                //���������ʷ�����ʱ��ΪFosc/12,��12T      
	BRT = 0xFA;                //�趨���������ʷ�������װֵ     
	AUXR |= 0x10;                //�������������ʷ�����
}


void Uart2_SendASC(unsigned char date){//�Լ��������� ��Ҫһ��

	S2BUF=date;
	while((S2CON&0X02)==0);
	S2CON&=~0X02;              //������ͱ�־λ

}

void Uart2_SendOrder(unsigned char *p){   //����2����һ���ַ���
	while(*p!='\0'){
		Uart2_SendASC(*p);
		p++;
	}
}


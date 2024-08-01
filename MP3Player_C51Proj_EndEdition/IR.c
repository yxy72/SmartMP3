/*==============IR.c=================
	������մ����ⲿ�ж�0
====================================*/
#include "STC12C5A60S2.h"
#include "IR.h"
#include "value.h"
#define uchar unsigned char
#define uint unsigned int	//����ת��
bit irok;
//bit lightOn = 1;
//uchar pwmSort = 0;
uchar IRcord[4];
uchar irdata[33];
uchar irtime;	//������ȫ�ֱ���
uint i7 = 0;
//uint i8 = 0;
void Ir_work(void)//�����ֵɢת����
{   
		switch(IRcord[2]){    //�жϰ�������ֵ
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
void Ircordpro(void)//������ֵ������
{ 
	uchar i, j, k,cord,value;
	k=1;
	for(i=0;i<4;i++) {			//����4���ֽ�
		for(j=1;j<=8;j++) {		//����1���ֽ�8λ
			cord=irdata[k];
			if(cord>7)			//����ĳֵΪ1������;����о��Թ�ϵ������ʹ��12M���㣬��ֵ������һ�����
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

//��ʱ��0
void IRInit() {

	IT0 = 1;					//ָ���ⲿ�ж�0�½��ش�����INT0 (P3.2)
 	EX0 = 1;					//ʹ���ⲿ�ж�
	//��ʱ��0 ��Ӧinterrupt 1
	TMOD|=0x02;					//��ʱ��0������ʽ2��TH0����װֵ��TL0�ǳ�ֵ	
	TH0=0x00;TL0=0x00;			//��ʼ��ֵ	
	ET0=1;						//��ʱ��0�жϴ�
	TR0=1;						//��ʱ��0���ش�

}
void EX0_ISR (void) interrupt 0 //�ⲿ�ж�0������
{
	static uchar i;             //���պ����źŴ���
	static bit startflag;       //�Ƿ�ʼ�����־λ
if(!v_IR)
	return;
if(!IRProcessOK)
	return;
	if(startflag) {                        
		if(irtime<63&&irtime>=33) { //������ TC9012��ͷ�룬9ms+4.5ms
            i=0;
		}
		irdata[i]=irtime;//�洢ÿ����ƽ�ĳ���ʱ�䣬�����Ժ��ж���0����1
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
	irtime++;  //�˼�˵ʲô�����жϼ�ʱ�ﲻ�ܼӶ�������ȻӰ����⣬ȷʵ�����԰�ԭ��ִ�е����Ū��PCA��ʱ����LED.c��ȥ�ˡ�
	TR0=1;   
}
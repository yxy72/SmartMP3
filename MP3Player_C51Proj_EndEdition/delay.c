#include <intrins.h>
#include "delay.h"
#include "value.h"
void DelaySend(u8 ifName){
	unsigned char i, j, k;//����BY8001-16P����ģ��˵���飬������ָ������20ms����
	if(ifName){//�������ּ��400ms
		i = 17;
		j = 208;
		k = 27;
		do
		{
			do
			{
				while (--k);
			} while (--j);
		} while (--i);
	}else{//�������ݼ��50ms
		i = 5;
		j = 52;
		k = 195;
		do
		{
			do
			{
				while (--k);
			} while (--j);
		} while (--i);
	}
}
void Delay20ms(){		//@11.0592MHz
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void WaitGpuDone(){
	while(Usart_BUSY);
}
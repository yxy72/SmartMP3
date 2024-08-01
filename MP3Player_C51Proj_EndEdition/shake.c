/*=============shake.c================
	摇晃切歌处理，外部中断1
====================================*/
#include <STC12C5A60S2.h>
#include "shake.h"
#include "value.h"
#include "delay.h"

void ShakeInterrupt() interrupt 2{
	if(!v_SK)
		return;
	if(IN0 == 0 && canShake){
		shakeNext = 1;
		canShake = 0;
		hasShaken = 1;
	}
	
}	 
void shake_Init(){
	EX1 = 1;
	IT1 = 1;
} 

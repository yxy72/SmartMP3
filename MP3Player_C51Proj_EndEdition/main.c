/*==========MP3音乐播放器============
	芯片：STC12C5A60S2
	晶振：11.0592MHz
	串口：9600bps
	引脚：IN0 = P3^3; （震荡）
				IRIN = P3^2;（红外）
				UART1_RXD = P3^0;
				UART1_TXD = P3^1;（MP3_TF模块）
				UART2_RXD = P1^2;
				UART2_TXD = P1^3;（串口屏）
	电源：USB/5V2A稳压源
	硬件：BY8001-16P/5W扬声器/UsartgGpu 26BK-PTF 
	开发：杨鑫宇 严雅岚  叶子强
/*=============main.c================
	程序主入口
====================================*/
#include "operation.h"
#include "value.h"
#include "GpuUI.h"
#include "delay.h"
#include "gpuOrder.h"
#include "mp3Order.h"
void main(){
	
	InitAll();
	//主线程消息队列
	while(1){
		keyScan();
		if(keyDone){	//按键，待处理
			keyDone = 0;
			ProcessKEY_IR(0);
		}
		if(IRDone && IRProcessOK){	//红外，待处理
			IRDone = 0;
			ProcessKEY_IR(1);
		}
		if(shakeNext){	//振荡，待处理
			shakeNext = 0;
			shakeProcess();
		}
		if(currentTimePaint&& currentSecPaint){	//用于绘制播放时长进度条，待处理
			currentSecPaint = 0;
			GpuOrder_PlayAreaRepaint(timeCurrentR);
		}
		if(playReachEnd1){	//用于检测播放结束的自动刷新，待处理
			playReachEnd1 = 0;
			reachEndProcess();
		}
	}
}


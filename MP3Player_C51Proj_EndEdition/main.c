/*==========MP3���ֲ�����============
	оƬ��STC12C5A60S2
	����11.0592MHz
	���ڣ�9600bps
	���ţ�IN0 = P3^3; ���𵴣�
				IRIN = P3^2;�����⣩
				UART1_RXD = P3^0;
				UART1_TXD = P3^1;��MP3_TFģ�飩
				UART2_RXD = P1^2;
				UART2_TXD = P1^3;����������
	��Դ��USB/5V2A��ѹԴ
	Ӳ����BY8001-16P/5W������/UsartgGpu 26BK-PTF 
	������������ �����  Ҷ��ǿ
/*=============main.c================
	���������
====================================*/
#include "operation.h"
#include "value.h"
#include "GpuUI.h"
#include "delay.h"
#include "gpuOrder.h"
#include "mp3Order.h"
void main(){
	
	InitAll();
	//���߳���Ϣ����
	while(1){
		keyScan();
		if(keyDone){	//������������
			keyDone = 0;
			ProcessKEY_IR(0);
		}
		if(IRDone && IRProcessOK){	//���⣬������
			IRDone = 0;
			ProcessKEY_IR(1);
		}
		if(shakeNext){	//�񵴣�������
			shakeNext = 0;
			shakeProcess();
		}
		if(currentTimePaint&& currentSecPaint){	//���ڻ��Ʋ���ʱ����������������
			currentSecPaint = 0;
			GpuOrder_PlayAreaRepaint(timeCurrentR);
		}
		if(playReachEnd1){	//���ڼ�ⲥ�Ž������Զ�ˢ�£�������
			playReachEnd1 = 0;
			reachEndProcess();
		}
	}
}


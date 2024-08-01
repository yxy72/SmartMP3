/*===========operation.c==============
	供调用接口函数
====================================*/
#include <STC12C5A60S2.h>
#include "operation.h"
#include "value.h"
#include "shake.h"
#include "IR.h"
#include "mp3Order.h"
#include "gpuOrder.h"
#include "delay.h"
#include "Uart.h"
#include "LED.h"
/*====================================
	全局初始化
====================================*/
void InitAll(){
	canShake = 0;
	P0M1 |= 0x00;P0M0 |= 0x01;//由于要将P0^0作为SK的VCC，设置为大电流推挽输出。
	shake_Init();	//先初始化一堆东西
	Uart_init();
	Uart2_init();
	IRInit(); 
	Init_PWM();
	
	EA = 1;
	DelaySend(1);	//再看一会标题界面
	DelaySend(1);
	DelaySend(1);	
	
	canShake = 1;
	GpuOrder(gpuStr_MainMenu);	// 最后加载主菜单
	GpuOrder_menuMainSelect(select6_mainMenu+1);
	GpuOeder_MenuIconRepaint();
	
	setPlayMode(2);//设置模式为单曲循环
}
/*====================================
	独立按键监测
====================================*/
void keyScan(){
	if(P20==0){
		Delay20ms();
		if(P20==0){
			Key_Option = vol_m;
			keyDone = 1;
		}while(!P20);
	}else if(P21==0){
		Delay20ms();
		if(P21==0){
			Key_Option = ch_min;
			keyDone = 1;
		}while(!P21);
	}else if(P22==0){
		Delay20ms();
		if(P22==0){
			Key_Option = preT;
			keyDone = 1;
		}while(!P22);
	}else if(P23==0){
		Delay20ms();
		if(P23==0){
			Key_Option = PP;
			keyDone = 1;
		}while(!P23);
	}else if(P24==0){
		Delay20ms();
		if(P24==0){
			Key_Option = nextT;
			keyDone = 1;
		}while(!P24);
	}else if(P25==0){
		Delay20ms();
		if(P25==0){
			Key_Option = ch_plus;
			keyDone = 1;
		}while(!P25);
	}else if(P26==0){
		Delay20ms();
		if(P26==0){
			Key_Option = vol_p;
			keyDone = 1;
		}while(!P26);
	}else if(P27==0){
		Delay20ms();
		if(P27==0){
			Key_Option = Return;
			keyDone = 1;
		}while(!P27);
	}
}
/*====================================
	播放到达尾声
====================================*/
void playEndNeedRepaint(){
	switch(playMode){
		case 0:
			currentSecPaint = 1;
			MP3Order(play);GpuOrder_menuPlaySelect(select8_playMenu);
			GpuOrder_PlayAreaRepaint(ppR);
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
	
	}
}

/*====================================
	保存设置与歌曲信息于SBUF
====================================*/
u8 acsiiToChar(u8 ascii){
	if(ascii>=0x30 && ascii<=0x39)
		return (ascii - 0x30);
	else if(ascii>=0x41 && ascii<=0x46)
		return (ascii - 0x41 + 10);
	else if(ascii>=0x61 && ascii<=0x66)
		return (ascii - 0x61 + 10);	
	return '0';
}
u16 groupToDec(){//2cfd
	return acsiiToChar(RsBuf[2])*16*16*16 + acsiiToChar(RsBuf[3])*16*16 + acsiiToChar(RsBuf[4])*16 + acsiiToChar(RsBuf[5]);
}
void Save_Setting_Info(u8 kind){
	u16 decChar = groupToDec();
	switch(kind){
		case msg_vol:
			v_song_volume = decChar;//*10/3;
			break;
		case msg_songs_num:
			v_songs_total = decChar;
			break;
		case msg_current_time:
			v_timeSec_now = decChar;
			break;
		case msg_total_time:
			v_timeSec_total = decChar;
			break;
		case msg_crrSort:
			v_Crrsort = decChar;
			break;
	}
}
/*====================================
	获取设置与歌曲信息至SBUF
====================================*/
void Seek_Setting_Info(u8 kind){
	//msg_vol, msg_songs_num, msg_current_time, msg_total_time, msg_song_name	
	switch(kind){
		case msg_vol:
			SendOrder(VOL);
			DelaySend(0);
			break;
		case msg_songs_num:
			SendOrder(tf_file_num);
			DelaySend(0);
			break;
		case msg_current_time:
			SendOrder(curr_time);
			DelaySend(0);
			break;
		case msg_total_time:
			SendOrder(total_time);
			DelaySend(0);
			break;
		case msg_crrSort:
			SendOrder(crrSort);
			DelaySend(0);
			break;
	}
}
/*====================================
	获取并保存 设置与歌曲信息
====================================*/
void Update_Setting_Info(u8 kind){

	Seek_Setting_Info(kind);
	Save_Setting_Info(kind);
}
void Update_songsName(){
	SendOrder(song_name);
	DelaySend(1);
	v_song_name[0] = RsBuf[2];
	v_song_name[1] = RsBuf[3];
	v_song_name[2] = RsBuf[4];
	v_song_name[3] = RsBuf[5];
	v_song_name[4] = RsBuf[6];
	v_song_name[5] = RsBuf[7];
	v_song_name[6] = RsBuf[10];
	v_song_name[7] = RsBuf[11];
	v_song_name[8] = RsBuf[12];
}
/*====================================
	发送MP3串口指令
====================================*/
void MP3Order(uchar *str){
	SendOrder(str);
	DelaySend(0);
}
void playSongSort(uchar sort){
	SendOrder(PlaySongN(sort));
	DelaySend(0);
}
void setSongVoice(uchar sort){
	SendOrder(SetVoiceN(sort));
	DelaySend(0);
}
void setPlayMode(uchar sort){
	SendOrder(SetModeN(sort));
	DelaySend(0);
}
/*====================================
	发送GPU串口指令
====================================*/
void GpuOrder_NoDelay(uchar *str){
	Uart2_SendOrder(str);
}
void GpuOrder(uchar *str){
	Uart2_SendOrder(str);
	WaitGpuDone();
}
void GpuOrder_menuMainSelect(u8 sort){
	Uart2_SendOrder(GpuStr_MenuSelect(sort+0x30));
	WaitGpuDone();
}
void GpuOrder_menuPlaySelect(u8 sort){
	Uart2_SendOrder(GpuStr_MenuPlaySelect(sort));
	WaitGpuDone();
}
void GpuOrder_menuModeSelect(u8 sort){
	Uart2_SendOrder(GpuStr_ModeSelect(sort));
	WaitGpuDone();
}
void GpuOrder_menuSelectSelect(u8 sort){
	Uart2_SendOrder(GpuStr_selectSelect(sort));
	WaitGpuDone();
}
void GpuOrder_SongNumRepaint(u8 sort){
	Uart2_SendOrder(GpuStr_SongNumRepaint(sort));
	WaitGpuDone();
}
void GpuOrder_menuSelectSongSort(u8 sort){
	Uart2_SendOrder(GpuStr_menuSelectSongSort(sort));
	WaitGpuDone();
}
void GpuOrder_menuConfigRepaint(){
	
	if(select3_ConfMenu==0){
		if(v_SK){
			if(v_IR){
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(0,5,9));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(0,5,11));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(0,5,13));
			}else{
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(2,5,9));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(2,5,11));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(2,5,13));
			}
		}else{
			if(v_IR){
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(0,7,9));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(0,7,11));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(0,7,13));
			}else{
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(2,7,9));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(2,7,11));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(2,7,13));
			}
		}
	}else if(select3_ConfMenu==1){
		if(v_SK){
			if(v_IR){
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,4,9));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,4,11));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,4,13));
			}else{
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,4,9));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,4,11));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,4,13));
			}
		}else{
			if(v_IR){
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,6,9));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,6,11));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,6,13));
			}else{
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,6,9));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,6,11));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,6,13));
			}
		}
	}else if(select3_ConfMenu==2){
		if(v_SK){
			if(v_IR){
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,5,8));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,5,10));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,5,12));
			}else{
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,5,8));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,5,10));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,5,12));
			}
		}else{
			if(v_IR){
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,7,8));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,7,10));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(1,7,12));
			}else{
				if(ledMode ==0)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,7,8));
				else if(ledMode == 1)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,7,10));
				else if(ledMode == 2)
					Uart2_SendOrder(GpuStr_ConfigSelect(3,7,12));
			}
		}
	}
	
	
	
	
	WaitGpuDone();
}
void GpuOrder_PlayAreaRepaint(u8 sort){
	switch(sort){
		case volR:
			GpuOrder(GpuStr_setVoice());
			break;
		case ppR:
			if(v_PP)
				GpuOrder("SPG(44);\r\n");
			else
				GpuOrder("SPG(45);\r\n");
			break;
		case PPR:
			if(!v_PP){
				currentSecPaint = 0;
				Update_Setting_Info(msg_current_time);
				MP3Order(pause);
							
			}else{
				currentSecPaint = 1;
				Update_Setting_Info(msg_current_time);	
				MP3Order(play);
						
			}
			break;
		case crrSR_nameR:
			GpuOrder(GpuStr_setSortandName());
			break;
		case timeAllR:
			GpuOrder(GpuStr_setTotalSec());
			break;
		case timeCurrentR:
			GpuOrder(GpuStr_setCrrSec());
			break;
		case nextSR:
			v_timeSec_now = 0;	
			GpuOrder_PlayAreaRepaint(ppR);
			Update_songsName();
			Update_Setting_Info(msg_crrSort);
			GpuOrder_PlayAreaRepaint(crrSR_nameR);
		
			Update_Setting_Info(msg_current_time);
			GpuOrder_PlayAreaRepaint(timeCurrentR);
		
			Update_Setting_Info(msg_total_time);
			GpuOrder_PlayAreaRepaint(timeAllR);
			
			
			
					
			break;
		case nextTR:
			GpuOrder_PlayAreaRepaint(timeCurrentR);
			break;
	
	}
}
void GpuOeder_MenuIconRepaint(){
	if(v_silence){
		switch(playMode){
			case 0:
				GpuOrder_NoDelay(GpuStr_MainIconShow(1));
				GpuOrder(GpuStr_MainIconShow(2));
				break;
			case 1:
				GpuOrder_NoDelay(GpuStr_MainIconShow(1));
				GpuOrder(GpuStr_MainIconShow(3));
				break;
			case 2:
				GpuOrder_NoDelay(GpuStr_MainIconShow(1));
				GpuOrder(GpuStr_MainIconShow(4));
				break;
			case 3:
				GpuOrder_NoDelay(GpuStr_MainIconShow(1));
				GpuOrder(GpuStr_MainIconShow(5));
				break;
		}
	}else{
		switch(playMode){
			case 0:
				GpuOrder_NoDelay(GpuStr_MainIconShow(0));
				GpuOrder(GpuStr_MainIconShow(2));
				break;
			case 1:
				GpuOrder_NoDelay(GpuStr_MainIconShow(0));
				GpuOrder(GpuStr_MainIconShow(3));
				break;
			case 2:
				GpuOrder_NoDelay(GpuStr_MainIconShow(0));
				GpuOrder(GpuStr_MainIconShow(4));
				break;
			case 3:
				GpuOrder_NoDelay(GpuStr_MainIconShow(0));
				GpuOrder(GpuStr_MainIconShow(5));
				break;
		}
	}
}
void shakeProcess(){
	EX1 = 0;
	if(menuMode == menu_play){
		v_PP = 1;
		MP3Order(CH_Plus);
		GpuOrder_PlayAreaRepaint(nextSR);
	}
	EX1 = 1;
}

void reachEndProcess(){
	if(playMode == 0){
		if(menuMode == menu_play){
			playReachEnd2 = 1;
			v_PP = 0;
			GpuOrder_menuPlaySelect(select8_playMenu);
			GpuOrder_PlayAreaRepaint(PPR);
			GpuOrder_PlayAreaRepaint(ppR);
		}else{
			v_PP = 0;
			playReachEnd2 = 1;
		}
	}else if(playMode==1 ||playMode==2 ||playMode==3  ){
		v_PP = 1;
		if(menuMode == menu_play)
			GpuOrder_PlayAreaRepaint(nextSR);
	}
}
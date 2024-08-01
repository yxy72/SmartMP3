#ifndef _VALUE_h_
#define _VALUE_h_

#include <STC12C5A60S2.h>
#define u8 unsigned char 
#define u16 unsigned short
#define RsBuf_N 150

sbit IN0 = P3^3; 					//震荡感应器数据线
sbit IRIN = P3^2;         //红外接收器数据线
sbit OLED_SCL = P2^1;			//时钟 D0（SCLK）
sbit OLED_SDIN = P2^0;		//D1（MOSI） 数据
//sbit MP3_BUSY = P1^0;
sbit Usart_BUSY = P1^1;
sbit LED_Power = P1^0;
sbit LED_R = P1^5;
sbit LED_G = P1^6;
sbit LED_B = P1^7;
sbit SK_VCC = P0^0;

enum Option{
	num1,num2,num3,num4,num5,num6,num7,num8,num9,//0-9
	irPP,num0,irReturn,
	irUp,irLeft,irRight,irdown,irOK
};

enum MENU{
	menu_main, menu_play, menu_select, menu_mode, menu_config,menu_about
};
enum MenuMain_KeyName{
	up = 2,down = 6,confirm = 4,left = 3,right = 5
};
enum MenuPlay_KeyName{
	vol_m=1, ch_min=2, preT=3, PP=4, nextT=5, ch_plus=6, vol_p=7, Return=8
};
//enum MenuSelect_KeyName{
//	up = 2,down = 6,confirm = 4,
//};
enum MenuSelect0_KeyName{
	s_up = 3,s_down = 5,s_left =2,s_right = 6
};
enum MenuConfig_KeyName{
	//up = 2,down = 6
	Switch = 4,
};
enum SaveMessages{
	msg_vol, msg_songs_num, msg_current_time, msg_total_time, msg_song_name,msg_crrSort,
};
enum RepaintEnum{
	volR,ppR,ppIconR,crrSR_nameR,timeAllR,timeCurrentR,nextSR,nextTR,PPR,
};
extern u8 *OPTION[];
extern u8 menuMode;
extern u8 keyDone;
extern u8 IRDone;
extern u8 Key_Option;
extern u8 IR_Option;
extern u8 currentTimePaint;
extern u8 currentSecPaint;
extern u8 select3;//0,1,2
extern u8 select2;//0,1,2
extern u8 select6_mainMenu;
extern u8 select8_playMenu;
extern u8 select4_modeMenu;
extern u8 select3_ConfMenu;
extern u8 select2_SelectMenu;
extern u8 songSort;
extern u8 tempVoice;
extern u8 IRProcessOK;
extern u8 KeyProcessOK;
extern u8 playMode;
extern u8 ledMode;
extern u8 playReachEnd1;
extern u8 playReachEnd2;
extern u8 shakeNext;
extern u8 RsPoint;
extern u8 xdata RsBuf[];
extern u8 pwmVal[];   //  CCAP1H值的分配，为了实现不同的占空比

extern u8 canShake;		//v_SK开启后，能切歌
extern u8 hasShaken;	//v_SK开启后，切歌动作已执行


extern unsigned short v_timeSec_now;
extern unsigned short v_timeSec_total;
extern unsigned char v_PP;//0停止1播放中
extern unsigned char v_song_volume;
extern unsigned char v_song_name[];
extern unsigned char v_IR;
extern unsigned char v_SK;
extern unsigned char v_songs_total;
extern unsigned char v_silence;
extern unsigned char v_Crrsort;


#endif
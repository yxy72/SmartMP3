/*=============value.c================
	���ȫ�ֱ���
====================================*/
#include "value.h"

u8 menuMode = 0;
u8 IR_Option = 0;	//21��������� IRKEY1 - IRKEY21
u8 Key_Option = 0;
u8 select3 = 0;//����λѡ
u8 select2 = 0;//���λѡ
u8 songSort = 1;
u8 currentTimePaint = 0;
u8 currentSecPaint = 0;
u8 IRDone = 0;
u8 keyDone = 0;
u8 tempVoice = 0;
u8 IRProcessOK = 1;
u8 KeyProcessOK = 1;
u8 playMode = 1;
u8 ledMode = 1;//0���1������2ȫ�ʽ���
u8 shakeNext = 0;
u8 RsPoint = 0;
u8 select6_mainMenu=0;
u8 select8_playMenu=0;
u8 select4_modeMenu=0;
u8 select3_ConfMenu=0;
u8 select2_SelectMenu=0;
u8 pwmVal[15]={16,32,48,64,80,96,112,128,144,160,176,192,208,224,240};   //  CCAP1Hֵ�ķ��䣬Ϊ��ʵ�ֲ�ͬ��ռ�ձ�

u8 playReachEnd1 = 0;
u8 playReachEnd2 = 0;

u8 canShake = 1;		//v_SK���������и�
u8 hasShaken = 0;	//v_SK�������и趯����ִ��


unsigned short v_timeSec_now = 0;
unsigned short v_timeSec_total = 600;
unsigned char v_PP = 0;//0ֹͣ1������
unsigned char v_song_volume = 12;//0-30
unsigned char v_song_name[9];
unsigned char v_IR = 1;
unsigned char v_SK = 1;
unsigned char v_songs_total;
unsigned char v_silence = 0;
unsigned char xdata RsBuf[RsBuf_N] = "--------------";	//���崮�ڽ������ݻ�����
unsigned char v_Crrsort=0;

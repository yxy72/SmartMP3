/*============paint.c===============
	绘制与重绘
====================================*/
#ifndef _PAINT_C_
#define	 _PAINT_C_

#include <STC12C5A60S2.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include <intrins.h>
#include "oled.h"
#include "value.h"
unsigned char devMenuPlay = 8;
void menuMain_Paint(){
	u8 dev1 = 40,dev2 = 8;
	OLED_Clear(); 
	OLED_ShowCHinese(0+dev1,0,0);   //第1行
	OLED_ShowCHinese(16+dev1,0,1);
	OLED_ShowCHinese(32+dev1,0,2); 
	OLED_ShowCHinese(0,1,12);
	OLED_ShowCHinese(16,1,12);	
	OLED_ShowCHinese(96,1,12);  
	OLED_ShowCHinese(112,1,12);
	
	OLED_ShowCHinese(16+dev2,2,3);  	 //第2行
	OLED_ShowCHinese(32+dev2,2,4);
	OLED_ShowCHinese(48+dev2,2,5);
	
	OLED_ShowCHinese(16+dev2,4,6);  	 //第3行
	OLED_ShowCHinese(32+dev2,4,7);
	OLED_ShowCHinese(48+dev2,4,8);
	OLED_ShowCHinese(64+dev2,4,9);
	 
	OLED_ShowCHinese(16+dev2,6,10);  	 //第4行显示
	OLED_ShowCHinese(32+dev2,6,11);

}
void Select2_Paint(){
	u8 dev2 = 8;
	switch(select3){
		case 0:	OLED_ShowCHinese(dev2,4,23);
						OLED_ShowCHinese(dev2,6,23);
						OLED_ShowCHinese(dev2,2,13);break;
		case 1:	OLED_ShowCHinese(dev2,2,23);
						OLED_ShowCHinese(dev2,6,23);
						OLED_ShowCHinese(dev2,4,13);break;
	
	}
}
void Select3_Paint(){
	u8 dev2 = 8;
	switch(select3){
		case 0:	OLED_ShowCHinese(dev2,4,23);
						OLED_ShowCHinese(dev2,6,23);
						OLED_ShowCHinese(dev2,2,13);break;
		case 1:	OLED_ShowCHinese(dev2,2,23);
						OLED_ShowCHinese(dev2,6,23);
						OLED_ShowCHinese(dev2,4,13);break;
		case 2:	OLED_ShowCHinese(dev2,4,23);
						OLED_ShowCHinese(dev2,2,23);
						OLED_ShowCHinese(dev2,6,13);break;
	
	}
}
void playItem_Paint(u8 key){
	
	switch(key){
		case 4:
			OLED_ShowCHinese(48+devMenuPlay,6,23);//空白图形
			if(v_PP)
				OLED_ShowCHinese(48+devMenuPlay,6,24);//暂停图形
			else
				OLED_ShowCHinese(48+devMenuPlay,6,18);//播放图形
			
			
			break;
		
	
	}
}
void playArea_Paint(u8 areaSort){
	
	switch(areaSort){
		case 0://播放/暂停文字重绘
			OLED_ShowCHinese(0,0,23);   
			OLED_ShowCHinese(16,0,23); 
			
			if(v_PP){
				OLED_ShowCHinese(0,0,3);   
				OLED_ShowCHinese(16,0,4);
			}else{
				OLED_ShowCHinese(0,0,25);   
				OLED_ShowCHinese(16,0,26);
			}
			break;
		case 1://音量重绘
			
			if(v_song_volume == 30){
				OLED_ShowString(96,0,"    ",16); 
				OLED_ShowString(96,0,"100%",16);
			}else{
				OLED_ShowString(96,0,"    ",16);
				OLED_ShowChar(96,0,v_song_volume/3*10/10 + 0x30,16);
				OLED_ShowChar(104,0,v_song_volume/3*10%10 + 0x30,16);
				OLED_ShowChar(112,0,'%',16);
			}
			break;
		case 2://歌曲总时长重绘
			OLED_ShowCHinese(48,2,23);  
			OLED_ShowCHinese(72,2,23); 
		
			OLED_ShowChar(48,2,v_timeSec_total/60/10 + 0x30,16);
			OLED_ShowChar(56,2,v_timeSec_total/60%10 + 0x30,16);
			OLED_ShowChar(72,2,v_timeSec_total%60/10 + 0x30,16);
			OLED_ShowChar(80,2,v_timeSec_total%60%10 + 0x30,16);
			break;
		case 3://歌曲当前时长秒数重绘
			//OLED_ShowString(0,2,"  ",16);//123456 78	
			OLED_ShowString(24,2,"  ",16);//123456 78	
			//OLED_ShowChar(0,2,v_timeSec_now/60/10 + 0x30,16);
			//OLED_ShowChar(8,2,v_timeSec_now/60%10 + 0x30,16);
			OLED_ShowChar(24,2,v_timeSec_now%60/10 + 0x30,16);
			OLED_ShowChar(32,2,v_timeSec_now%60%10 + 0x30,16);
			break;
		case 4://歌名重绘
			OLED_ShowString(0,4,"      ~.",16);//123456 78
			OLED_ShowChar(0,4,v_song_name[0],16);
			OLED_ShowChar(8,4,v_song_name[1],16);
			OLED_ShowChar(16,4,v_song_name[2],16);
			OLED_ShowChar(24,4,v_song_name[3],16);
			OLED_ShowChar(32,4,v_song_name[4],16);
			OLED_ShowChar(40,4,v_song_name[5],16);
		
			OLED_ShowChar(48,4,'~',16);
			OLED_ShowChar(56,4,'.',16);
		
			OLED_ShowChar(64,4,v_song_name[6],16);
			OLED_ShowChar(72,4,v_song_name[7],16);
			OLED_ShowChar(80,4,v_song_name[8],16);
			break;
		case 5://SD Card多少首歌？
			OLED_ShowString(104,0,"  ",16);//123456 78
			OLED_ShowChar(104,0,v_songs_total/10 + 0x30,16);
			OLED_ShowChar(112,0,v_songs_total%10 + 0x30,16);
			break;
		
		case 6://播放模式重绘
			OLED_ShowString(64,4,"        ",16);
			if(playMode == 0){
				OLED_ShowCHinese(64,4,52);
				OLED_ShowCHinese(80,4,53);
				OLED_ShowCHinese(96,4,54);
				OLED_ShowCHinese(112,4,55);
			}else if(playMode == 1){
				OLED_ShowCHinese(64,4,52);
				OLED_ShowCHinese(80,4,53);
				OLED_ShowCHinese(96,4,56);
				OLED_ShowCHinese(112,4,57);
			}else if(playMode == 2){
				OLED_ShowCHinese(64,4,58);
				OLED_ShowCHinese(80,4,59);
				OLED_ShowCHinese(96,4,56);
				OLED_ShowCHinese(112,4,57);
			}else if(playMode == 3){
				OLED_ShowCHinese(64,4,60);
				OLED_ShowCHinese(80,4,61);
				OLED_ShowCHinese(96,4,56);
				OLED_ShowCHinese(112,4,57);
			}
			break;
		case 7://静音吗?
			OLED_ShowString(64,6,"   ",16);
			if(v_silence){
				OLED_ShowString(64,6,"ON",16);
			}else{
				OLED_ShowString(64,6,"OFF",16);
			}
			
			break;
		case 8://歌曲当前时长分钟数重绘
			OLED_ShowString(0,2,"  ",16);//123456 78	
			//OLED_ShowString(24,2,"  ",16);//123456 78	
			OLED_ShowChar(0,2,v_timeSec_now/60/10 + 0x30,16);
			OLED_ShowChar(8,2,v_timeSec_now/60%10 + 0x30,16);
			//OLED_ShowChar(24,2,v_timeSec_now%60/10 + 0x30,16);
			//OLED_ShowChar(32,2,v_timeSec_now%60%10 + 0x30,16);
	}
}
void menuPlay_Paint(){
	
	OLED_Clear(); 
	
	OLED_ShowCHinese(0,0,3);   //第1行
	OLED_ShowCHinese(16,0,4);
	OLED_ShowCHinese(32,0,14); 
	OLED_ShowString(64,0,"VOL:   %",16); 

	OLED_ShowString(0,2,"00:00/00:00",16); 
	//48 56 64 72 80
  //0  0  :  0  0
	OLED_ShowCHinese(96+devMenuPlay,2,22);
	
	
	OLED_ShowString(0,4,"loading...",16); 
	
	OLED_ShowCHinese(0+devMenuPlay,6,15);  	 //第4行显示
	OLED_ShowCHinese(16+devMenuPlay,6,16);
	OLED_ShowCHinese(32+devMenuPlay,6,17);
	OLED_ShowCHinese(48+devMenuPlay,6,18);
	OLED_ShowCHinese(64+devMenuPlay,6,19);
	OLED_ShowCHinese(80+devMenuPlay,6,20);
	OLED_ShowCHinese(96+devMenuPlay,6,21);
	
}

void menuSelect_Paint(){
	
	u8 dev2 = 8;
	OLED_Clear(); 
	OLED_ShowCHinese(32,0,6);   //第1行
	OLED_ShowCHinese(48,0,7);
	OLED_ShowCHinese(64,0,8); 
	OLED_ShowCHinese(80,0,9); 

	
	
	OLED_ShowCHinese(24,4,48);  	 //第2行
	OLED_ShowCHinese(40,4,49);
	OLED_ShowChar(56,4,':',16);
	OLED_ShowCHinese(64,4,52);
	OLED_ShowCHinese(80,4,53);
	OLED_ShowCHinese(96,4,54);
	OLED_ShowCHinese(112,4,55);
	
	
	OLED_ShowCHinese(24,2,6);  	 //第3行
	OLED_ShowCHinese(40,2,7);
	OLED_ShowCHinese(56,2,8);
	OLED_ShowCHinese(72,2,9);
	
	OLED_ShowCHinese(24,6,50);  	 //第4行显示
	OLED_ShowCHinese(40,6,51);
	OLED_ShowChar(56,6,':',16);
	OLED_ShowString(64,6,"OFF",16); 
	
	OLED_ShowString(0,0,"---",16); 
	OLED_ShowString(104,0,"---",16); 
	
}
void menuSetting_Paint(){
	
	u8 dev2 = 8;
	OLED_Clear(); 
	//OLED_ShowCHinese(32,0,6);   //第1行
	OLED_ShowCHinese(48,0,10);
	OLED_ShowCHinese(64,0,11); 
	//OLED_ShowCHinese(80,0,9); 

	
	
	OLED_ShowCHinese(24,2,34);  	 //第2行
	OLED_ShowCHinese(40,2,35);
	OLED_ShowCHinese(56,2,36);
	OLED_ShowCHinese(72,2,37);
	OLED_ShowChar(88,2,':',16);

	
	OLED_ShowCHinese(24,4,38);  	 //第3行
	OLED_ShowCHinese(40,4,39);
	OLED_ShowCHinese(56,4,40);
	OLED_ShowCHinese(72,4,6);
	OLED_ShowChar(88,4,':',16);
	
	OLED_ShowCHinese(24,6,27);  	 //第4行显示
	OLED_ShowCHinese(40,6,28);
	
	
	OLED_ShowString(0,0,"-----",16); 
	OLED_ShowString(88,0,"-----",16); 
	
}

void confArea_Paint(u8 areaSort){
	switch(areaSort){
		case 0:	
			OLED_ShowString(96,2,"   ",16); 
			if(v_IR){
				OLED_ShowString(96,2,"ON",16); 
			}else{
				OLED_ShowString(96,2,"OFF",16); 
			}
			break;
		case 1:
			OLED_ShowString(96,4,"   ",16); 
			if(v_SK){
				OLED_ShowString(96,4,"ON",16); 
			}else{
				OLED_ShowString(96,4,"OFF",16); 
			}
			break;
	}
}
void menuSelect0_Paint(){
	
	OLED_Clear(); 
	
	OLED_ShowCHinese(0,0,8);   //第1行
	OLED_ShowCHinese(16,0,9);
	OLED_ShowCHinese(32,0,32); 
	OLED_ShowCHinese(48,0,33); 

	OLED_ShowString(80,0,"SD:",16);
	
	OLED_ShowChar(52,3,songSort/10 + 0x30,16);
	OLED_ShowChar(68,3,songSort%10 + 0x30,16);
	OLED_ShowCHinese(48,5,42);
	OLED_ShowCHinese(64,5,42);
	
	  	 //第4行显示
	OLED_ShowCHinese(16+devMenuPlay,6,43);
	OLED_ShowCHinese(32+devMenuPlay,6,45);
	OLED_ShowCHinese(48+devMenuPlay,6,47);
	OLED_ShowCHinese(64+devMenuPlay,6,46);
	OLED_ShowCHinese(80+devMenuPlay,6,44);

	
}
void Select0Area_Paint(u8 areaSort){
	switch(areaSort){
		case 0:	
			OLED_ShowString(48,5,"  ",16);
			OLED_ShowString(64,5,"  ",16);
			if(select2){
				OLED_ShowCHinese(48,5,42);
			}else{
				OLED_ShowCHinese(64,5,42);
			}
			OLED_ShowCHinese(32+devMenuPlay,6,45);
			OLED_ShowCHinese(48+devMenuPlay,6,47);
			OLED_ShowCHinese(64+devMenuPlay,6,46);
			break;
		case 1:
			OLED_ShowChar(52,3,' ',16);
			OLED_ShowChar(68,3,' ',16);
			OLED_ShowChar(52,3,songSort/10 + 0x30,16);
			OLED_ShowChar(68,3,songSort%10 + 0x30,16);
			break;
	}
}

#endif
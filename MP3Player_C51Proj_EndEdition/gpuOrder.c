#include "gpuOrder.h"
#include "value.h"
/*===============gpuOrder.c==================
	串口屏指令字符串配置
	需要使用配套的上位机软件设置串口屏工程文件。
============================================*/
u8* gpuStr_MainMenu = "SPG(34);\r\n";
u8* gpuStr_PlayMenu = "SPG(35);\r\n";
u8* gpuStr_ModeMenu = "PIC(0,0,12);\r\n";
u8* gpuStr_SelectMenu = "PIC(0,0,28);PS16(3,109,41,'--',15);\r\n";
u8* gpuStr_ModeConfig = "PIC(0,0,19);\r\n";
u8* gpuStr_ModeAbout = "PIC(0,0,32);\r\n";

u8 gpuStr_Voice0[] = "ICON(320,13,4,2,1,1);PS24(1,350,15,'0% ',15);\r\n";//0:36
u8 gpuStr_Voice[] = "ICON(320,13,4,2,1,0);PS24(1,350,15,'0% ',15);\r\n";//0:36
u8 gpuStr_totalSec[] = "PS16(1,348,176,'00:00',15);\r\n";//暂停！选中 0:17
u8 gpuStr_CrrSec[] = "PS16(1,298,176,'00:00/',15);PIC(12,175,11);PIC(015,175,5);\r\n";//暂停！选中 0:17 15-285
u8 gpuStr_CrrSort[] = "PS16(1,26,37,'00',15);PS16(1,50,37,'......~.mp3',15);\r\n";//暂停！选中 0:17 15-285

u8* gpuStr_P1S[] = {"SPG(36);\r\n","SPG(37);\r\n","SPG(38);\r\n","SPG(39);\r\n","SPG(40);\r\n","SPG(41);\r\n","SPG(42);\r\n", "SPG(43);\r\n"};
u8* gpuStr_P0S[] = {"SPG(47);\r\n","SPG(48);\r\n","SPG(49);\r\n","SPG(50);\r\n","SPG(51);\r\n","SPG(52);\r\n","SPG(53);\r\n", "SPG(54);\r\n"};
u8* gpuStr_mainMenuIcon[] = {"ICON(37,148,18,6,1,0);","ICON(37,148,18,6,1,1);","ICON(325,60,18,6,1,2);\r\n","ICON(325,60,18,6,1,3);\r\n","ICON(325,60,18,6,1,4);\r\n","ICON(325,60,18,6,1,5);\r\n"};



u8* GpuStr_setSortandName(){
	gpuStr_CrrSort[14] = v_Crrsort/10 + 0x30;
	gpuStr_CrrSort[15] = v_Crrsort%10 + 0x30;
	
	gpuStr_CrrSort[36] = v_song_name[0];
	gpuStr_CrrSort[37] = v_song_name[1];
	gpuStr_CrrSort[38] = v_song_name[2];
	gpuStr_CrrSort[39] = v_song_name[3];
	gpuStr_CrrSort[40] = v_song_name[4];
	gpuStr_CrrSort[41] = v_song_name[5];
	gpuStr_CrrSort[44] = v_song_name[6];
	gpuStr_CrrSort[45] = v_song_name[7];
	gpuStr_CrrSort[46] = v_song_name[8];
	
	return gpuStr_CrrSort;
}
u8* GpuStr_SongNumRepaint(u8 a){
	u8 command[] = "PS16(3,109,41,'--',15);\r\n";
	if(!(a/10)){
		command[15]=' ';
		command[16]=a%10+0x30;
	}else{
		command[15]=a/10+0x30;
		command[16]=a%10+0x30;
	}
	return command;
}
u8* GpuStr_MenuSelect(u8 a){
	u8 command[] = "W8SE(0);SBC(0);\r\n";
	command[5]=a;
	return command;
}
u8* GpuStr_ConfigSelect(u8 a,u8 b,u8 c){
	u8 command[] = "ICON(106,50,34,1,14,x);ICON(106,85,34,1,14,x);ICON(106,120,34,1,14,xx);\r\n";
	command[20] = a + 0x30;
	command[43] = b + 0x30;
	command[67] = c/10 + 0x30;
	command[68] = c%10 + 0x30;
	return command;
}
u8* GpuStr_selectSelect(u8 a){
	u8 command[] = "PIC(165,140,31);\r\n";
	command[13] = a + 0x30;
	return command;
}
u8* GpuStr_ModeSelect(u8 a){
	u8 command[] = "PIC(83,45,13);\r\n";
	command[11]=a+3+0x30;
	return command;
}
u8* GpuStr_menuSelectSongSort(u8 a){
	u8 command[] = "ISTR(164,90,29,'08');\r\n";
	command[16]=a/10+0x30;
	command[17]=a%10+0x30;
	return command;
}
u8* GpuStr_MainIconShow(u8 kind){
	return gpuStr_mainMenuIcon[kind];
}
u8* GpuStr_MenuPlaySelect(u8 a){
	
	if(!v_PP){
		return gpuStr_P1S[a];
	}else{
		return gpuStr_P0S[a];
	}
}
u8* GpuStr_setVoice(){
	if(v_song_volume == 0)
		return gpuStr_Voice0;
	else{
		gpuStr_Voice[36] = v_song_volume/3*10/10 + 0x30;
		gpuStr_Voice[37] = '0';
		gpuStr_Voice[38] = '%';
		return gpuStr_Voice;
	}
	
}
u8* GpuStr_setTotalSec(){
	gpuStr_totalSec[16] = v_timeSec_total/60/10 + 0x30;
	gpuStr_totalSec[17] = v_timeSec_total/60%10 + 0x30;
	gpuStr_totalSec[19] = v_timeSec_total%60/10 + 0x30;
	gpuStr_totalSec[20] = v_timeSec_total%60%10 + 0x30;
	return gpuStr_totalSec;
}

u8* GpuStr_setCrrSec(){
	unsigned short a;
	gpuStr_CrrSec[16] = v_timeSec_now/60/10 + 0x30;
	gpuStr_CrrSec[17] = v_timeSec_now/60%10 + 0x30;
	gpuStr_CrrSec[19] = v_timeSec_now%60/10 + 0x30;
	gpuStr_CrrSec[20] = v_timeSec_now%60%10 + 0x30;
	
	a = 15+(float)v_timeSec_now/(float)v_timeSec_total*270;

	gpuStr_CrrSec[47] = a/100 + 0x30;
	gpuStr_CrrSec[48] = a/10%10 + 0x30;
	gpuStr_CrrSec[49] = a%10 + 0x30;
	return gpuStr_CrrSec;
}


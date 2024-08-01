/*============MenuUI.c===============
	菜单UI界面生成
====================================*/
#include <STC12C5A60S2.h>
#include "mp3Order.h"
#include "value.h"
#include "operation.h"

void KeyProcess(){
	KeyProcessOK = 0;
	switch(menuMode){
		case menu_main:
			switch(Key_Option){
				case up :
					select3 = (select3+2)%3; OLED_SelcetPaint(1);
					break;
				case down:
					select3 = (select3+1)%3; OLED_SelcetPaint(1);
					break;
				case confirm:
					if(select3 == 0){
						menuMode = menu_play;
						OLED_PlayPaint();
						currentTimePaint=1;
						OLED_playItem_Paint(PP);
						OLED_playArea_RePaint(0);
						Update_Setting_Info(msg_vol);
						OLED_playArea_RePaint(1);
						Update_Setting_Info(msg_current_time);
						OLED_playArea_RePaint(3);
						Update_Setting_Info(msg_total_time);
						OLED_playArea_RePaint(2);
						Update_songsName();
						OLED_playArea_RePaint(4);
					}
					else if(select3 == 1){
						select3 = 0;
						menuMode = menu_select;
						OLED_SelectPaint();
						OLED_SelcetPaint(1);
					}
					else if(select3 == 2){
						select3 = 0;
						OLED_SettingsPaint();
						menuMode = menu_config;
						OLED_SelcetPaint(1);
						OLED_settingArea_RePaint(0);
						OLED_settingArea_RePaint(1);
					}
					break;
				default:
					break;
			}
			break;
				
		case menu_play:
			switch(Key_Option){
				case vol_m:
					v_song_volume = v_song_volume-3;
					if(v_song_volume<0)
						v_song_volume = 0;
					setSongVoice(v_song_volume);
					OLED_playArea_RePaint(1);
					break;
				case ch_min:
					MP3Order(CH_Min);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case preT:
					MP3Order(pre_Time);
					Update_Setting_Info(msg_current_time);
					OLED_playArea_RePaint(3);
					break;
				case PP:
					if(v_PP){
						MP3Order(pause);
						v_PP = 0;
					}else{
						MP3Order(play);
						v_PP = 1;
						Update_songsName();
						OLED_playArea_RePaint(4);
					}
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_Setting_Info(msg_current_time);
					OLED_playArea_RePaint(3);
					OLED_playArea_RePaint(0);
					break;
				case nextT:
					MP3Order(next_Time);
					Update_Setting_Info(msg_current_time);
					OLED_playArea_RePaint(3);
					break;
				case ch_plus:
					MP3Order(CH_Plus);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case vol_p:
					v_song_volume = v_song_volume+3;
					if(v_song_volume>30)
						v_song_volume = 30;
					setSongVoice(v_song_volume);
					OLED_playArea_RePaint(1);
					break;
				case Return:
					currentTimePaint=0;
					menuMode = menu_main;	OLED_MainPaint();
					OLED_SelcetPaint(1);
					break;
			}
			break;
		
		case menu_select:
			switch(Key_Option){
				case up :
					select3 = (select3+2)%3; OLED_SelcetPaint(1);
					break;
				case down:
					select3 = (select3+1)%3; OLED_SelcetPaint(1);
					break;
				case confirm:
					if(select3 == 0){
						OLED_Select0Paint();
						menuMode = menu_select_0;	
						OLED_selectSongArea_RePaint(0);
						Update_Setting_Info(msg_songs_num);
						OLED_playArea_RePaint(5);	
					}
					else if(select3 == 1){
						playMode = (playMode+1)%4; 
						OLED_playArea_RePaint(6);
						if(playMode == 0){
							setPlayMode(4);
						}
						else if(playMode == 1)
							setPlayMode(2);
						else if(playMode == 2)
							setPlayMode(1);
						else if(playMode == 3)
							setPlayMode(3);
					}
					else if(select3 == 2){
						if(v_silence){
						v_silence = 0;
						v_song_volume = tempVoice;
						setSongVoice(v_song_volume);
						}else{
						v_silence = 1;
						tempVoice = v_song_volume;
						v_song_volume = 0;
						setSongVoice(0);
						}
						OLED_playArea_RePaint(7);
					}
					break;
				case Return:
					menuMode = menu_main;
					OLED_MainPaint();
					select3 = 0;
					OLED_SelcetPaint(1);
					break;
			}
			break;
		
		case menu_select_0:
			switch(Key_Option){
				case s_right :
				case s_left:
					select2 = (select2+1)%2; OLED_selectSongArea_RePaint(0);
					break;
				case s_up:
					if(select2){
						songSort = ((songSort/10+1)*10 + songSort%10)%100;
					}else{
						if(songSort == 99)
							songSort =1;
						else
							songSort = (songSort+1)%100;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case s_down:
					if(select2){
						songSort = (((songSort/10-1)*10 + songSort%10)+100)%100;
					}else{
						if(songSort == 1)
							songSort = 99;
						else
							songSort = (songSort-1+100)%100;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case confirm:
					select2 = 0;
					playSongSort(songSort);
					break;
				case Return:
					menuMode = menu_select;
					select3 = 0;
					OLED_SelectPaint();
					OLED_SelcetPaint(1);
					break;
			}
			break;
		
		case menu_select_1:
			switch(Key_Option){
				case up :
				case down:
					;
					break;
				case confirm:
					if(select2 == 0)
						;
					else if(select2 == 1)
						;
					select2 = 0;
					break;
				case Return:
					;
					break;
				}
			break;
		
		case menu_config :
			switch(Key_Option){
				case up :
					select3 = (select3+2)%3; OLED_SelcetPaint(1);
					break;
				case down:
					select3 = (select3+1)%3; OLED_SelcetPaint(1);
					break;
				case confirm:
					if(select3 == 0){
						if(v_IR){
							v_IR = 0;
							OLED_settingArea_RePaint(0);
						}else{
							v_IR = 1;
							OLED_settingArea_RePaint(0);
						}
					}else if(select3 == 1){
						if(v_SK ==1){
							v_SK = 0;
							EX1 = 0;
							OLED_settingArea_RePaint(1);
						}else{
							v_SK = 1;
							EX1 = 1;
							OLED_settingArea_RePaint(1);
						}
					}else if(select3 == 2){
						select3 = 0;
						menuMode = menu_main;	OLED_MainPaint();
						OLED_SelcetPaint(1);
					}
					break;
				case Return:
					menuMode = menu_main;
					OLED_MainPaint();
					select3 = 0;
					OLED_SelcetPaint(1);
					break;
			}
			break;
		
		default:break;
	}
	KeyProcessOK = 1;
}

void ShakeProcess(){
	MP3Order(CH_Plus);
	Update_Setting_Info(msg_total_time);
	Update_songsName();
	v_timeSec_now = 0;
	v_PP = 1;
	OLED_playItem_Paint(PP);
	OLED_playArea_RePaint(0);
	OLED_playArea_RePaint(2);
	OLED_playArea_RePaint(4);
}

void IRProcess(){
	IRProcessOK = 0;
	switch(menuMode){
		case menu_main:
			switch(IR_Option){
				case pre_time: select3 = (select3+2)%3; OLED_SelcetPaint(1);
					break;
				case next_time: select3 = (select3+1)%3; OLED_SelcetPaint(1);
					break;
				case CH1:
					if(select3 == 0){
						menuMode = menu_play;
						OLED_PlayPaint();
						currentTimePaint=1;
						OLED_playItem_Paint(PP);
						OLED_playArea_RePaint(0);
						Update_Setting_Info(msg_vol);
						OLED_playArea_RePaint(1);
						Update_Setting_Info(msg_current_time);
						OLED_playArea_RePaint(3);
						Update_Setting_Info(msg_total_time);
						OLED_playArea_RePaint(2);
						Update_songsName();
						OLED_playArea_RePaint(4);
					}
					else if(select3 == 1){
						select3 = 0;
						menuMode = menu_select;
						OLED_SelectPaint();
						OLED_SelcetPaint(1);
					}
					else if(select3 == 2){
						select3 = 0;
						OLED_SettingsPaint();
						menuMode = menu_config;
						OLED_SelcetPaint(1);
						OLED_settingArea_RePaint(0);
						OLED_settingArea_RePaint(1);
					}
					break;
				case vol_min:
					v_song_volume = v_song_volume-3;
					if(v_song_volume<0)
						v_song_volume = 0;
					setSongVoice(v_song_volume);
					break;
				case CH_min:
					MP3Order(CH_Min);
					v_timeSec_now = 0;
					v_PP = 1;
					break;
				case play_pause:
					if(v_PP){
						MP3Order(pause);
						v_PP = 0;
					}else{
						MP3Order(play);
						v_PP = 1;
					}
					break;
				case CH_plus:
					MP3Order(CH_Plus);
					v_timeSec_now = 0;
					v_PP = 1;
					break;
				case vol_plus:
					v_song_volume = v_song_volume+3;
					if(v_song_volume>30)
						v_song_volume = 30;
					setSongVoice(v_song_volume);
					break;
				case music0:
					if(v_silence){
						v_silence = 0;
						v_song_volume = tempVoice;
						setSongVoice(v_song_volume);
					}else{
						v_silence = 1;
						tempVoice = v_song_volume;
						v_song_volume = 0;
						setSongVoice(0);
					}
				break;
				case music1:	
					MP3Order(play_no1);
					break;
				case music2:	
					MP3Order(play_no2);
					break;
				case music3:	
					MP3Order(play_no3);
					break;
				case music4:	
					MP3Order(play_no4);
					break;
				case music5:	
					MP3Order(play_no5);
					break;
				case music6:	
					MP3Order(play_no6);
					break;
				case music7:	
					MP3Order(play_no7);
					break;
				case music8:	
					MP3Order(play_no8);
					break;
				case music9:	
					MP3Order(play_no9);
					break;
				
				default:break;
				}
		break;
	case menu_play:
		switch(IR_Option){
				case vol_min:
					v_song_volume = v_song_volume-3;
					if(v_song_volume<0)
						v_song_volume = 0;
					setSongVoice(v_song_volume);
					OLED_playArea_RePaint(1);
					break;
				
				case CH_min:
					MP3Order(CH_Min);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case pre_time:
					MP3Order(pre_Time);
					Update_Setting_Info(msg_current_time);
					OLED_playArea_RePaint(3);
					break;
				case play_pause:
					if(v_PP){
						MP3Order(pause);
						v_PP = 0;
					}else{
						MP3Order(play);
						v_PP = 1;
						Update_songsName();
						OLED_playArea_RePaint(4);
					}
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_Setting_Info(msg_current_time);
					OLED_playArea_RePaint(3);
					OLED_playArea_RePaint(0);
					break;
				case CH1:
					if(v_PP==1){
						MP3Order(pause);
						v_PP = 0;
					}else{
						MP3Order(play);
						v_PP = 1;
						Update_songsName();
						OLED_playArea_RePaint(4);
					}
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_Setting_Info(msg_current_time);
					OLED_playArea_RePaint(3);
					OLED_playArea_RePaint(0);
					break;
				case next_time:
					MP3Order(next_Time);
					Update_Setting_Info(msg_current_time);
					OLED_playArea_RePaint(3);
					break;
				case CH_plus:
					MP3Order(CH_Plus);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case vol_plus:
					v_song_volume = v_song_volume+3;
					if(v_song_volume>30)
						v_song_volume = 30;
					setSongVoice(v_song_volume);
					OLED_playArea_RePaint(1);
					break;
				case exit:
					currentTimePaint=0;
					menuMode = menu_main;	OLED_MainPaint();
					OLED_SelcetPaint(1);
					
					break;
				case music0:
					if(v_silence){
						v_silence = 0;
						v_song_volume = tempVoice;
						setSongVoice(v_song_volume);
						OLED_playArea_RePaint(1);
					}else{
						v_silence = 1;
						tempVoice = v_song_volume;
						v_song_volume = 0;
						setSongVoice(0);
						OLED_playArea_RePaint(1);
					}
				case music1:	
					MP3Order(play_no1);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case music2:	
					MP3Order(play_no2);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case music3:	
					MP3Order(play_no3);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case music4:	
					MP3Order(play_no4);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case music5:	
					MP3Order(play_no5);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case music6:	
					MP3Order(play_no6);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case music7:	
					MP3Order(play_no7);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case music8:	
					MP3Order(play_no8);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				case music9:	
					MP3Order(play_no9);
					v_timeSec_now = 0;
					Update_Setting_Info(msg_total_time);
					OLED_playArea_RePaint(2);
					v_PP = 1;
					OLED_playItem_Paint(PP);
					OLED_playArea_RePaint(0);
					Update_songsName();
					OLED_playArea_RePaint(4);
					break;
				}
			break;

	case menu_select:
			switch(IR_Option){
				case pre_time :
					select3 = (select3+2)%3; OLED_SelcetPaint(1);
					break;
				case next_time:
					select3 = (select3+1)%3; OLED_SelcetPaint(1);
					break;
				case CH1:
					if(select3 == 0){
						OLED_Select0Paint();
						menuMode = menu_select_0;	
						OLED_selectSongArea_RePaint(0);
						Update_Setting_Info(msg_songs_num);
						OLED_playArea_RePaint(5);
					}
					else if(select3 == 1){
						playMode = (playMode+1)%4; 
						OLED_playArea_RePaint(6);
						if(playMode == 0){
							setPlayMode(4);
						}
						else if(playMode == 1)
							setPlayMode(2);
						else if(playMode == 2)
							setPlayMode(1);
						else if(playMode == 3)
							setPlayMode(3);
					}
					else if(select3 == 2){
						if(v_silence){
						v_silence = 0;
						v_song_volume = tempVoice;
						setSongVoice(v_song_volume);
						}else{
						v_silence = 1;
						tempVoice = v_song_volume;
						v_song_volume = 0;
						setSongVoice(0);
						}
						OLED_playArea_RePaint(7);
					}
					break;
				case exit:
					menuMode = menu_main;
					OLED_MainPaint();
					select3 = 0;
					OLED_SelcetPaint(1);
					break;
				case vol_min:
					MP3Order(VOL_Min);
					break;
				case CH_min:
					MP3Order(CH_Min);
					v_timeSec_now = 0;
					v_PP = 1;
					break;
				case play_pause:
					if(v_PP){
						MP3Order(pause);
						v_PP = 0;
					}else{
						MP3Order(play);
						v_PP = 1;
					}
					break;
				case CH_plus:
					MP3Order(CH_Plus);
					v_timeSec_now = 0;
					v_PP = 1;
					break;
				case vol_plus:
					MP3Order(VOL_Plus);
					break;
				case music0:
					if(v_silence){
						v_silence = 0;
						v_song_volume = tempVoice;
						setSongVoice(v_song_volume);
					}else{
						v_silence = 1;
						tempVoice = v_song_volume;
						v_song_volume = 0;
						setSongVoice(0);
					}
					break;
				case music1:	
					MP3Order(play_no1);
					break;
				case music2:	
					MP3Order(play_no2);
					break;
				case music3:	
					MP3Order(play_no3);
					break;
				case music4:	
					MP3Order(play_no4);
					break;
				case music5:	
					MP3Order(play_no5);
					break;
				case music6:	
					MP3Order(play_no6);
					break;
				case music7:	
					MP3Order(play_no7);
					break;
				case music8:	
					MP3Order(play_no8);
					break;
				case music9:	
					MP3Order(play_no9);
					break;
				}
			break;
		case menu_select_0:
			switch(IR_Option){
				case pre_time :
				case next_time:
					select2 = (select2+1)%2; OLED_selectSongArea_RePaint(0);
					break;
				case _200_plus:
					if(select2){
						songSort = ((songSort/10+1)*10 + songSort%10)%100;
					}else{
						if(songSort == 99)
							songSort =1;
						else
							songSort = (songSort+1)%100;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case _100_plus:
					if(select2){
						songSort = (((songSort/10-1)*10 + songSort%10)+100)%100;
					}else{
						if(songSort == 1)
							songSort = 99;
						else
							songSort = (songSort-1+100)%100;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music0:	
					if(select2){
						songSort = songSort%10;
					}else{
						if(songSort/10)
							songSort = songSort/10;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music1:	
					if(select2){
						songSort = 10 + songSort%10;
					}else{
						songSort = songSort/10 + 1;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music2:	
					if(select2){
						songSort = 20 + songSort%10;
					}else{
						songSort = songSort/10 + 2;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music3:	
					if(select2){
						songSort = 30 + songSort%10;
					}else{
						songSort = songSort/10 + 3;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music4:	
					if(select2){
						songSort = 40 + songSort%10;
					}else{
						songSort = songSort/10 + 4;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music5:	
					if(select2){
						songSort = 50 + songSort%10;
					}else{
						songSort = songSort/10 + 5;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music6:	
					if(select2){
						songSort = 60 + songSort%10;
					}else{
						songSort = songSort/10 + 6;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music7:	
					if(select2){
						songSort = 70 + songSort%10;
					}else{
						songSort = songSort/10 + 7;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music8:	
					if(select2){
						songSort = 80 + songSort%10;
					}else{
						songSort = songSort/10 + 8;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case music9:	
					if(select2){
						songSort = 90 + songSort%10;
					}else{
						songSort = songSort/10 + 9;
					}
					OLED_selectSongArea_RePaint(1);
					break;
				case CH1:
					select2 = 0;
					playSongSort(songSort);
					break;
				case exit:
					menuMode = menu_select;
					select3 = 0;
					OLED_SelectPaint();
					OLED_SelcetPaint(1);
					break;
				case vol_min:
					MP3Order(VOL_Min);
					break;
				case CH_min:
					MP3Order(CH_Min);
					v_timeSec_now = 0;
					v_PP = 1;
					break;
				case play_pause:
					if(v_PP){
						MP3Order(pause);
						v_PP = 0;
					}else{
						MP3Order(play);
						v_PP = 1;
					}
					break;
				case CH_plus:
					MP3Order(CH_Plus);
					v_timeSec_now = 0;
					v_PP = 1;
					break;
				case vol_plus:
					MP3Order(VOL_Plus);
					break;
				}
			break;
	
		case menu_select_1:
			switch(Key_Option){
				case up :
				case down:
				;
					break;
				case confirm:
					if(select2 == 0)
						;
					else if(select2 == 1)
						;
					select2 = 0;
					break;
				case Return:
					;
					break;
				}
			break;
		
		case menu_config :
			switch(IR_Option){
				case pre_time :
					select3 = (select3+2)%3; OLED_SelcetPaint(1);
					break;
				case next_time:
					select3 = (select3+1)%3; OLED_SelcetPaint(1);
					break;
				case CH1:
					if(select3 == 0){
						if(v_IR){
							v_IR = 0;
							OLED_settingArea_RePaint(0);
						}else{
							v_IR = 1;
							OLED_settingArea_RePaint(0);
						}
					}else if(select3 == 1){
						if(v_SK ==1){
							v_SK = 0;
							EX1 = 0;
							OLED_settingArea_RePaint(1);
						}else{
							v_SK = 1;
							EX1 = 1;
							OLED_settingArea_RePaint(1);;
						}
					}else if(select3 == 2){
						select3 = 0;
						menuMode = menu_main;	OLED_MainPaint();
						OLED_SelcetPaint(1);
					}
					break;
				case exit:
					menuMode = menu_main;
					OLED_MainPaint();
					select3 = 0;
					OLED_SelcetPaint(1);
					break;
				case vol_min:
					MP3Order(VOL_Min);
					break;
				case CH_min:
					MP3Order(CH_Min);
					v_timeSec_now = 0;
					v_PP = 1;
					break;
				case play_pause:
					if(v_PP){
						MP3Order(pause);
						v_PP = 0;
					}else{
						MP3Order(play);
						v_PP = 1;
					}
					break;
				case CH_plus:
					MP3Order(CH_Plus);
					v_timeSec_now = 0;
					v_PP = 1;
					break;
				case vol_plus:
					MP3Order(VOL_Plus);
					break;
				case music0:
					if(v_silence){
						v_silence = 0;
						v_song_volume = tempVoice;
						setSongVoice(v_song_volume);
					}else{
						v_silence = 1;
						tempVoice = v_song_volume;
						v_song_volume = 0;
						setSongVoice(0);
					}
				break;
				case music1:	
					MP3Order(play_no1);
					break;
				case music2:	
					MP3Order(play_no2);
					break;
				case music3:	
					MP3Order(play_no3);
					break;
				case music4:	
					MP3Order(play_no4);
					break;
				case music5:	
					MP3Order(play_no5);
					break;
				case music6:	
					MP3Order(play_no6);
					break;
				case music7:	
					MP3Order(play_no7);
					break;
				case music8:	
					MP3Order(play_no8);
					break;
				case music9:	
					MP3Order(play_no9);
					break;
				}
			break;
		
		default:break;				
	}
	IRProcessOK = 1;
	IR_Option = 30;
}







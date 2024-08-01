/*============GpuUI.c===============
	菜单UI界面生成
====================================*/
#include <STC12C5A60S2.h>
#include "mp3Order.h"
#include "value.h"
#include "operation.h"
#include "GpuUI.h"
#include "gpuOrder.h"
#define u8 unsigned char

void ProcessKEY_IR(u8 KEY_IR){
	IRProcessOK = 0;
	//menu_main, menu_play, menu_select, menu_mode, menu_config,menu_about
	switch(menuMode){
		case menu_main:
			if(!KEY_IR){
				/*====================================
					主菜单MenuMain 按键
				====================================*/
				switch(Key_Option){
					case up:
					case down:
						select6_mainMenu = (select6_mainMenu+3)%6;
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
					case left:
						select6_mainMenu = (select6_mainMenu+5)%6;
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
					case right:
						select6_mainMenu = (select6_mainMenu+1)%6;
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
					case confirm:
						switch(select6_mainMenu){
							case 0:	menuMode = menu_play;//播放器
							        GpuOrder(gpuStr_PlayMenu);                                                                                                                      
											GpuOrder_menuPlaySelect(select8_playMenu);
											Update_Setting_Info(msg_vol);	
											GpuOrder_PlayAreaRepaint(volR);
											
							
											GpuOrder_PlayAreaRepaint(ppR);
											Update_Setting_Info(msg_total_time);
											GpuOrder_PlayAreaRepaint(timeAllR);
											Update_Setting_Info(msg_current_time);
											GpuOrder_PlayAreaRepaint(timeCurrentR);
											
											Update_Setting_Info(msg_crrSort);
											Update_songsName();
							
											GpuOrder_PlayAreaRepaint(crrSR_nameR);
											currentTimePaint = 1;
								break;
							case 1:	menuMode = menu_select;//歌曲选择
							        GpuOrder(gpuStr_SelectMenu);  
											GpuOrder_menuSelectSelect(select2_SelectMenu);
											GpuOrder_menuSelectSongSort(songSort);
											Update_Setting_Info(msg_songs_num);
											GpuOrder_SongNumRepaint(v_songs_total);
								break;
							case 2:	menuMode = menu_mode;//模式选择
							        GpuOrder(gpuStr_ModeMenu);  
											GpuOrder_menuModeSelect(select4_modeMenu = playMode);
								break;
							case 3:	if(v_silence){//静音
												v_silence = 0;
												if(tempVoice == 0)
													tempVoice = 15;
												v_song_volume = tempVoice;
												GpuOeder_MenuIconRepaint();
												setSongVoice(v_song_volume);
											}else{
												v_silence = 1;
												tempVoice = v_song_volume;
												v_song_volume = 0;
												GpuOeder_MenuIconRepaint();
												setSongVoice(0);
											}
											
								break;
							case 4:	menuMode = menu_config;//设置面板
							        GpuOrder(gpuStr_ModeConfig);  
											GpuOrder_menuConfigRepaint();
								break;
							case 5:	menuMode = menu_about;//关于
							        GpuOrder(gpuStr_ModeAbout);  
								break;
							
						}
						break;
				}
			}else{
				/*====================================
					主菜单MenuMain 红外
				====================================*/
				switch(IR_Option){
					case irUp:
					case irdown:
						select6_mainMenu = (select6_mainMenu+3)%6;
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
					case irLeft:
						select6_mainMenu = (select6_mainMenu+5)%6;
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
					case irRight:
						select6_mainMenu = (select6_mainMenu+1)%6;
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
					case irPP:
						if(playReachEnd2){
							playReachEnd2 = 0;v_timeSec_now = 0;MP3Order(play);
							v_PP = 1;
							IRProcessOK = 1; return;
						}
						v_PP = !v_PP;
						if(!v_PP)
							MP3Order(pause);
						else
							MP3Order(play);
						break;
					case irOK:
						switch(select6_mainMenu){
							case 0:	menuMode = menu_play;//播放器
							        GpuOrder(gpuStr_PlayMenu);                                                                                                                      
											GpuOrder_menuPlaySelect(select8_playMenu);
											Update_Setting_Info(msg_vol);	
											GpuOrder_PlayAreaRepaint(volR);
											
							
											GpuOrder_PlayAreaRepaint(ppR);
											Update_Setting_Info(msg_total_time);
											GpuOrder_PlayAreaRepaint(timeAllR);
											Update_Setting_Info(msg_current_time);
											GpuOrder_PlayAreaRepaint(timeCurrentR);
											
											Update_Setting_Info(msg_crrSort);
											Update_songsName();
											GpuOrder_PlayAreaRepaint(crrSR_nameR);
											currentTimePaint = 1;
								break;
							case 1:	menuMode = menu_select;//歌曲选择
							        GpuOrder(gpuStr_SelectMenu);  
											GpuOrder_menuSelectSelect(select2_SelectMenu);
											GpuOrder_menuSelectSongSort(songSort);
											Update_Setting_Info(msg_songs_num);
											GpuOrder_SongNumRepaint(v_songs_total);
								break;
							case 2:	menuMode = menu_mode;//模式选择
							        GpuOrder(gpuStr_ModeMenu);  
											GpuOrder_menuModeSelect(select4_modeMenu = playMode);
								break;
							case 3:	if(v_silence){//静音
												v_silence = 0;
												if(tempVoice == 0)
													tempVoice = 15;
												v_song_volume = tempVoice;
												GpuOeder_MenuIconRepaint();
												setSongVoice(v_song_volume);
											}else{
												v_silence = 1;
												tempVoice = v_song_volume;
												v_song_volume = 0;
												GpuOeder_MenuIconRepaint();
												setSongVoice(0);
											}
								break;
							case 4:	menuMode = menu_config;//设置面板
							        GpuOrder(gpuStr_ModeConfig);  
											GpuOrder_menuConfigRepaint();
								break;
							case 5:	menuMode = menu_about;//关于
							        GpuOrder(gpuStr_ModeAbout);  
								break;
						
						}
						break;
					
				}
			}
			break;
		
			
		
		case menu_play:
			if(!KEY_IR){
				/*====================================
					播放菜单PlayMenu 按键
				====================================*/
				switch(Key_Option){
					case vol_m:
						select8_playMenu = Key_Option - 1;
						v_song_volume = v_song_volume-3;
						GpuOrder_menuPlaySelect(select8_playMenu);
						if(v_song_volume<0)
							v_song_volume = 0;
						if(v_song_volume==0)
							v_silence = 1;
						GpuOrder_PlayAreaRepaint(volR);
						setSongVoice(v_song_volume);
						break;
					case ch_min:
						v_PP = 1;
						select8_playMenu = Key_Option - 1;
						GpuOrder_menuPlaySelect(select8_playMenu);
						MP3Order(CH_Min);
						GpuOrder_PlayAreaRepaint(nextSR);
						break;
					case preT:
						select8_playMenu = Key_Option - 1;
						GpuOrder_menuPlaySelect(select8_playMenu);
						MP3Order(pre_Time);
						Update_Setting_Info(msg_current_time);
						break;
					case PP:
						if(playReachEnd2){
							playReachEnd2 = 0;v_timeSec_now = 0;
							v_PP = 1;
							select8_playMenu = Key_Option - 1;
							GpuOrder_menuPlaySelect(select8_playMenu);
							playEndNeedRepaint();
							IRProcessOK = 1; return;
						}
					
						v_PP = !v_PP;
						select8_playMenu = Key_Option - 1;
						GpuOrder_menuPlaySelect(select8_playMenu);
						GpuOrder_PlayAreaRepaint(ppR);
						GpuOrder_PlayAreaRepaint(PPR);
						

						break;
					case nextT:
						select8_playMenu = Key_Option - 1;
						GpuOrder_menuPlaySelect(select8_playMenu);
						MP3Order(next_Time);
						Update_Setting_Info(msg_current_time);
						break;
					case ch_plus:
						v_PP = 1;
						select8_playMenu = Key_Option - 1;
						GpuOrder_menuPlaySelect(select8_playMenu);
						MP3Order(CH_Plus);
						GpuOrder_PlayAreaRepaint(nextSR);
						break;
					case vol_p:
						select8_playMenu = Key_Option - 1;
						GpuOrder_menuPlaySelect(select8_playMenu);
						v_song_volume = v_song_volume+3;
						if(v_song_volume>30)
							v_song_volume = 30;
						if(v_song_volume>0)
							v_silence = 0;
						GpuOrder_PlayAreaRepaint(volR);
						setSongVoice(v_song_volume);
						
						break;
					case Return:
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						currentTimePaint = 0;
						break;
				}
			
			

			}else{
				/*====================================
					播放菜单PlayMenu 红外
				====================================*/
				switch(IR_Option){
					case irPP:
						if(playReachEnd2){
							playReachEnd2 = 0;v_timeSec_now = 0;
							v_PP = 1;
							playEndNeedRepaint();
							IRProcessOK = 1; return;
						}
						v_PP = !v_PP;
						GpuOrder_menuPlaySelect(select8_playMenu);
						GpuOrder_PlayAreaRepaint(ppR);
						GpuOrder_PlayAreaRepaint(PPR);
						break;
					case irUp:
					case irLeft:
						select8_playMenu = (select8_playMenu+7)%8;
						GpuOrder_menuPlaySelect(select8_playMenu);
						break;
					case irRight:
					case irdown:
						select8_playMenu = (select8_playMenu+1)%8;
						GpuOrder_menuPlaySelect(select8_playMenu);
						break;
					case irOK:
						
						switch(select8_playMenu){
							case 0:
								GpuOrder_menuPlaySelect(select8_playMenu);
								v_song_volume = v_song_volume-3;
								if(v_song_volume<0)
									v_song_volume = 0;
								if(v_song_volume==0)
									v_silence = 1;
								GpuOrder_PlayAreaRepaint(volR);
								setSongVoice(v_song_volume);
								break;
							case 1:
								v_PP = 1;
								GpuOrder_menuPlaySelect(select8_playMenu);
								MP3Order(CH_Min);
								GpuOrder_PlayAreaRepaint(nextSR);
								break;
							case 2:
								GpuOrder_menuPlaySelect(select8_playMenu);
								MP3Order(pre_Time);
								Update_Setting_Info(msg_current_time);
								break;
							case 3:
								if(playReachEnd2){
									playReachEnd2 = 0;v_timeSec_now = 0;
									v_PP = 1;
									playEndNeedRepaint();
									IRProcessOK = 1; return;
								}
								v_PP = !v_PP;
								GpuOrder_menuPlaySelect(select8_playMenu);
								GpuOrder_PlayAreaRepaint(ppR);
								GpuOrder_PlayAreaRepaint(PPR);

								break;
							case 4:
								GpuOrder_menuPlaySelect(select8_playMenu);
								MP3Order(next_Time);
								Update_Setting_Info(msg_current_time);
								break;
							case 5:
								v_PP = 1;
								GpuOrder_menuPlaySelect(select8_playMenu);
								MP3Order(CH_Plus);
								GpuOrder_PlayAreaRepaint(nextSR);
								break;
							case 6:
								GpuOrder_menuPlaySelect(select8_playMenu);
								v_song_volume = v_song_volume+3;
								if(v_song_volume>30)
									v_song_volume = 30;
								if(v_song_volume>0)
									v_silence = 0;
								GpuOrder_PlayAreaRepaint(volR);
								setSongVoice(v_song_volume);
								break;
							case 7:
								menuMode = menu_main;
								GpuOrder(gpuStr_MainMenu);
								GpuOrder_menuMainSelect(select6_mainMenu+1);
								currentTimePaint = 0;
								GpuOeder_MenuIconRepaint();
								break;	
						}
						break;
					case irReturn:
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						currentTimePaint = 0;
						GpuOeder_MenuIconRepaint();
						break;
				}
			}
			break;
		
		
		
			
		case menu_mode:
			if(!KEY_IR){
				/*====================================
					模式选择菜单ModeMenu 按键
				====================================*/
				switch(Key_Option){
					case preT://上箭头
						select4_modeMenu = (select4_modeMenu+3)%4;
						GpuOrder_menuModeSelect(select4_modeMenu);
						break;
					case nextT://下箭头
						select4_modeMenu = (select4_modeMenu+1)%4;
						GpuOrder_menuModeSelect(select4_modeMenu);
						break;
					case confirm:
						playMode = select4_modeMenu;
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						if(playMode == 0)
							setPlayMode(4);
						else if(playMode == 1)
							setPlayMode(2);
						else if(playMode == 2)
							setPlayMode(1);
						else if(playMode == 3)
							setPlayMode(3);
						break;
					case Return:
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
				}
			}else{
				/*====================================
					模式选择菜单ModeMenu 红外
				====================================*/
				switch(IR_Option){
					case irPP:
						if(playReachEnd2){
							playReachEnd2 = 0;v_timeSec_now = 0;MP3Order(play);
							v_PP = 1;
							IRProcessOK = 1; return;
						}
						v_PP = !v_PP;
						if(!v_PP)
							MP3Order(pause);
						else
							MP3Order(play);
						break;
					case irUp:
					case irLeft:
						select4_modeMenu = (select4_modeMenu+3)%4;
						GpuOrder_menuModeSelect(select4_modeMenu);
						break;
					case irdown:
					case irRight:
						select4_modeMenu = (select4_modeMenu+1)%4;
						GpuOrder_menuModeSelect(select4_modeMenu);
						break;
					case irOK:
						playMode = select4_modeMenu;
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						if(playMode == 0)
							setPlayMode(4);
						else if(playMode == 1)
							setPlayMode(2);
						else if(playMode == 2)
							setPlayMode(1);
						else if(playMode == 3)
							setPlayMode(3);
						break;
					case irReturn:
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
				}
			}
			break;
		
		
		
		case menu_config:
			if(!KEY_IR){
				/*====================================
					设置菜单ConfigMenu 按键
				====================================*/
				switch(Key_Option){
					case preT://上箭头
						select3_ConfMenu = (select3_ConfMenu+2)%3;
						GpuOrder_menuConfigRepaint();
						break;
					case nextT://下箭头
						select3_ConfMenu = (select3_ConfMenu+1)%3;
						GpuOrder_menuConfigRepaint();
						break;
					case confirm:
						if(select3_ConfMenu==0)
							v_IR = !v_IR;
						else if(select3_ConfMenu==1){
							v_SK = !v_SK;
							if(v_SK){
								canShake = 0;
								hasShaken = 1;//上电延时，否则切歌
							}
							SK_VCC = !SK_VCC;
							
						}else if(select3_ConfMenu==2){
							if(ledMode==0)
								ledMode = 1;
							else if(ledMode==1)
								ledMode = 2;
							else if(ledMode==2)
								ledMode = 0;
							}
						GpuOrder_menuConfigRepaint();
						break;
					case Return:
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
				}
			}else{
				/*====================================
					设置菜单ConfigMenu 红外
				====================================*/
				switch(IR_Option){
					case irPP:
						if(playReachEnd2){
							playReachEnd2 = 0;v_timeSec_now = 0;MP3Order(play);
							v_PP = 1;
							IRProcessOK = 1; return;
						}
						v_PP = !v_PP;
						if(!v_PP)
							MP3Order(pause);
						else
							MP3Order(play);
						break;
					case irUp:
					case irLeft:
						select3_ConfMenu = (select3_ConfMenu+2)%3;
						GpuOrder_menuConfigRepaint();
						break;
					case irdown:
					case irRight:
						select3_ConfMenu = (select3_ConfMenu+1)%3;
						GpuOrder_menuConfigRepaint();
						break;
					case irOK:
						if(select3_ConfMenu==0)
							v_IR = !v_IR;
						else if(select3_ConfMenu==1){
							v_SK = !v_SK;
							if(v_SK){
								canShake = 0;
								hasShaken = 1;//上电延时，否则切歌
							}
							SK_VCC = !SK_VCC;
						}
						else if(select3_ConfMenu==2){
							if(ledMode==0)
								ledMode = 1;
							else if(ledMode==1)
								ledMode = 2;
							else if(ledMode==2)
								ledMode = 0;
							}
						GpuOrder_menuConfigRepaint();
						break;
					case irReturn:
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
				}
			}
			break;
		
		case menu_select:
			if(!KEY_IR){
				/*====================================
					歌曲选择菜单SelectMenu 按键
				====================================*/
				switch(Key_Option){
					case preT://上箭头，数字-1
						if(!select2_SelectMenu){
							songSort = (((songSort/10-1)*10 + songSort%10)+100)%100;
						}else{
							if(songSort == 1)
								songSort = 99;
							else
								songSort = (songSort-1+100)%100;
						}
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case nextT://下箭头，数字+1
						if(!select2_SelectMenu){
							songSort = ((songSort/10+1)*10 + songSort%10)%100;
						}else{
							if(songSort == 99)
								songSort =1;
							else
								songSort = (songSort+1)%100;
						}
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case ch_min://左箭头
					case ch_plus://右箭头
						select2_SelectMenu = (select2_SelectMenu+1)%2;
						GpuOrder_menuSelectSelect(select2_SelectMenu);
						break;
					case confirm:
						playSongSort(songSort);
						v_PP = 1;
						break;
					case Return:
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
				}
			}else{
				/*====================================
					歌曲选择菜单SelectMenu 红外
				====================================*/
				switch(IR_Option){
					case irPP:
						if(playReachEnd2){
							playReachEnd2 = 0;v_timeSec_now = 0;MP3Order(play);
							v_PP = 1;
							IRProcessOK = 1; return;
						}
						v_PP = !v_PP;
						if(!v_PP)
							MP3Order(pause);
						else
							MP3Order(play);
						break;
					case irUp:
						if(!select2_SelectMenu){
							songSort = (((songSort/10-1)*10 + songSort%10)+100)%100;
						}else{
							if(songSort == 1)
								songSort = 99;
							else
								songSort = (songSort-1+100)%100;
						}
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case irLeft:
					case irRight:
						select2_SelectMenu = (select2_SelectMenu+1)%2;
						GpuOrder_menuSelectSelect(select2_SelectMenu);
						break;
					case irdown:
						if(!select2_SelectMenu)
							songSort = ((songSort/10+1)*10 + songSort%10)%100;
						else
							if(songSort == 99)
								songSort =1;
							else
								songSort = (songSort+1)%100;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num0:	
						if(!select2_SelectMenu){
							if(songSort%10)
								songSort = songSort%10;
						}else{
							if(songSort/10)
								songSort = (songSort/10)*10;
						}
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num1:	
						if(!select2_SelectMenu)
							songSort = 10 + songSort%10;
						else
							songSort = songSort/10*10 + 1;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num2:	
						if(!select2_SelectMenu)
							songSort = 20 + songSort%10;
						else
							songSort = songSort/10*10 + 2;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num3:	
						if(!select2_SelectMenu)
							songSort = 30 + songSort%10;
						else
							songSort = songSort/10*10 + 3;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num4:	
						if(!select2_SelectMenu)
							songSort = 40 + songSort%10;
						else
							songSort = songSort/10*10 + 4;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num5:	
						if(!select2_SelectMenu)
							songSort = 50 + songSort%10;
						else
							songSort = songSort/10*10 + 5;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num6:	
						if(!select2_SelectMenu)
							songSort = 60 + songSort%10;
						else
							songSort = songSort/10*10 + 6;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num7:	
						if(!select2_SelectMenu)
							songSort = 70 + songSort%10;
						else
							songSort = songSort/10*10 + 7;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num8:	
						if(!select2_SelectMenu)
							songSort = 80 + songSort%10;
						else
							songSort = songSort/10*10 + 8;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case num9:	
						if(!select2_SelectMenu)
							songSort = 90 + songSort%10;
						else
							songSort = songSort/10*10 + 9;
						GpuOrder_menuSelectSongSort(songSort);
						break;
					case irOK:
						playSongSort(songSort);
						v_PP = 1;
						break;
					case irReturn:
						menuMode = menu_main;
						GpuOrder(gpuStr_MainMenu);
						GpuOeder_MenuIconRepaint();
						GpuOrder_menuMainSelect(select6_mainMenu+1);
						break;
				}
			}
			break;
		
		case menu_about:
			if(!KEY_IR){
				/*====================================
					关于About 按键
				====================================*/
				if(Key_Option == Return){
					menuMode = menu_main;
					GpuOrder(gpuStr_MainMenu);
					GpuOeder_MenuIconRepaint();
					GpuOrder_menuMainSelect(select6_mainMenu+1);
				}
			}else{
				/*====================================
					关于About 红外
				====================================*/
				if(IR_Option == irReturn||IR_Option == irOK){
					menuMode = menu_main;
					GpuOrder(gpuStr_MainMenu);
					GpuOeder_MenuIconRepaint();
					GpuOrder_menuMainSelect(select6_mainMenu+1);
				}else if(IR_Option == irPP){
						if(playReachEnd2){
							playReachEnd2 = 0;v_timeSec_now = 0;MP3Order(play);
							v_PP = 1;
							IRProcessOK = 1; return;
						}
						v_PP = !v_PP;
						if(!v_PP)
							MP3Order(pause);
						else
							MP3Order(play);
					}
			}
			
			break;
	}
	IRProcessOK = 1;
	IR_Option = 127;
}
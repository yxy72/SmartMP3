#ifndef _OPERATION_h_
#define _OPERATION_
#define  u8 unsigned char
u8 xdata RsBuf[];	
extern void Save_Setting_Info(u8 kind);
extern void Seek_Setting_Info(u8 kind);
extern void MP3Order(u8 *str);
extern void OLED_PlayPaint();
extern void Update_Setting_Info(u8 kind);
extern void Update_songsName();
extern void playSongSort(u8 sort);
extern void setSongVoice(u8 sort);
extern void setPlayMode(u8 sort);
extern void InitAll();
extern void keyScan();
extern void GpuOrder_menuMainSelect(u8 sort);
extern void GpuOrder_menuPlaySelect(u8 sort);
extern void GpuOrder_menuModeSelect(u8 sort);
extern void GpuOrder_PlayAreaRepaint(u8 sort);
extern void GpuOrder_menuConfigRepaint();
extern void GpuOrder_menuSelectSelect(u8 sort);
extern void GpuOrder_menuSelectSongSort(u8 sort);
extern void GpuOrder_SongNumRepaint(u8 sort);
extern void GpuOeder_MenuIconRepaint();
extern void playEndNeedRepaint();
extern void GpuOrder(u8 *str);
extern void shakeProcess();
extern void reachEndProcess();
#endif
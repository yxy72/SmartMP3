#ifndef _GPUORDER_
#define	 _GPUORDER_

#define u8 unsigned char
	
extern u8* gpuStr_MainMenu;
extern u8* gpuStr_PlayMenu;
extern u8* gpuStr_ModeMenu;
extern u8* gpuStr_ModeConfig;
extern u8* gpuStr_SelectMenu;
extern u8* gpuStr_ModeAbout;

extern u8* GpuStr_setVoice();
extern u8* GpuStr_MenuSelect(u8 a);
extern u8* GpuStr_MenuPlaySelect(u8 a);
extern u8* GpuStr_ModeSelect(u8 a);
extern u8* GpuStr_ConfigSelect(u8 a,u8 b,u8 c);
extern u8* GpuStr_MainIconShow(u8 kind);
extern u8* GpuStr_setTotalSec();
extern u8* GpuStr_setCrrSec();
extern u8* GpuStr_setSortandName();
extern u8* GpuStr_selectSelect(u8 a);
extern u8* GpuStr_menuSelectSongSort(u8 a);
extern u8* GpuStr_SongNumRepaint(u8 a);
#endif

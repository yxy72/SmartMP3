#ifndef _MP3ORDER_
#define	 _MP3ORDER_

#define uchar unsigned char 

extern uchar code play[];
extern uchar code pause[];
extern uchar code stop[];
extern uchar code CH_Plus[];
extern uchar code CH_Min[];
extern uchar code VOL_Plus[];
extern uchar code VOL_Min[];
extern uchar code pre_Time[];
extern uchar code next_Time[];
extern uchar code play_status[];//0=stop 1=play 2=pause 3=next_Time 4=pre_Time
extern uchar code VOL[];//0~30
extern uchar code tf_file_num[];//file number of TF card
extern uchar code curr_time[];//current time of the song
extern uchar code total_time[];//total time of the song
extern uchar code song_name[];//name of the song
extern uchar code play_no1[];
extern uchar code play_no2[];
extern uchar code play_no3[];
extern uchar code play_no4[];
extern uchar code play_no5[];
extern uchar code play_no6[];
extern uchar code play_no7[];
extern uchar code play_no8[];
extern uchar code play_no9[];
extern uchar* SetModeN (uchar a);
extern uchar* PlaySongN(uchar a);
extern uchar* SetVoiceN(uchar a);
extern uchar code crrSort[];

#endif

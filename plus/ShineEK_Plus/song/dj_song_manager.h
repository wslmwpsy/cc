#pragma once

#include "song_info.h"

#define DJ_SONG_MAX_COUNT 20

class dj_song_manager
{
public:
	dj_song_manager(void);
	~dj_song_manager(void);

	/*
	功能：增加dj歌曲
	参数：
	    dj_song_info;DJ歌曲信息
	返回值：
	    true：成功
		false：失败
	*/
	bool add_dj_song(song_info &dj_song_info);

	/*
	功能：得到下一首播放的dj歌曲
	参数：
	    dj_song_info;DJ歌曲信息
	返回值：
	    true：成功
		false：失败
	*/
	bool get_next_play_dj_song(song_info &dj_song_info);

	/*
	功能：得到dj歌曲数目
	参数：
	    void
	返回值：
	    实际的dj歌曲数目
	*/
	int get_dj_song_count(void);

private:
	song_info m_dj_song_info[DJ_SONG_MAX_COUNT];
	int m_dj_song_count;      //dj歌曲数
	int m_cur_play_dj_number; //当前播放的dj歌曲编号
};

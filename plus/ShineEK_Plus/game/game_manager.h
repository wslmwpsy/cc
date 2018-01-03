#pragma once

#include "..\message.h"

#define SHOW_GAME_MAX_COUNT   6   //游戏的最大显示数

class game_manager
{
public:
	game_manager(void);
	~game_manager(void);
	/*
	功能：搜索所有的游戏
	参数：
	    path：游戏路径
	返回值：
	    void
	*/
	void search_game(TCHAR *path);

	/*
	功能：得到要播放的游戏路径
	参数：
	    path：游戏路径
		select_number：选择的编号
	返回值：
	    true：成功
		false：失败
	*/
	bool get_select_game_path(TCHAR *path,int select_number);

private:
	int m_game_total_count;                             //游戏总数
	SONG_GAME_STRUCT m_game_info[SHOW_GAME_MAX_COUNT];  //存储游戏信息
};

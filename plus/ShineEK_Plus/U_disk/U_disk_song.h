#pragma once

#include "../song/song_info.h"
#include "../message.h"
#include "../song/video_play_manager.h"

#include <string>
using namespace std;

#define U_DISK_SONG_MAX_COUNT    90

class U_disk_song
{
public:
	U_disk_song(void);
	~U_disk_song(void);
	/*
	功能：搜索歌曲
	参数：
	    U_path：U盘路径
		page_row_count：页显示的行数
	返回值：
	    true：成功
		flase：失败
	*/
	bool search_U_disk_song(TCHAR *U_path,int page_row_count);
	
	/*
	功能：得到三屏数据
	参数：
	    song_string：返回的歌曲字符串
		page_operate：页操作类型
	返回值：
	    true：成功
		false：失败
	*/
	bool make_U_disk_song_xml_list(std::wstring &song_xml_string,video_play_manager &video_manager,PAGE_OPERATE page_operate,std::wstring &default_color,std::wstring &select_color,std::wstring &playing_color);

	/*
	功能：得到选择的歌曲
	参数：
	    select_number：选中的编号
		U_song_info：返回的歌曲信息
	返回值：
	    true:成功
		false：失败
	*/
	bool get_U_disk_song_info(song_info &U_song_info,int select_number);

	/*
	功能：得到歌曲数及页码数
	参数：
	   song_count：歌曲数
	   page_count：页数
	   cur_page_number：当前页编号
   返回值：
       true：成功
	   false：失败
	*/
	bool get_song_row_and_page_count(int &song_count,int &page_count,int &cur_page_number);

private:
	SONG_GAME_STRUCT m_U_disk_song[U_DISK_SONG_MAX_COUNT];//U盘歌曲
	int m_song_total_count;                               //歌曲总数
	int m_list_show_row_count;                            //列表显示的函数
	int m_total_page_count;                               //总的页数
	int m_cur_show_page_number;                           //当前显示的页数
	int m_song_volume;                                    //歌曲音量
};

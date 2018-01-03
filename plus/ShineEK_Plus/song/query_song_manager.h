#pragma once

#ifndef _QUERY_SONG_MANAGER_H_
#define _QUERY_SONG_MANAGER_H_

#include "song_info.h"
#include "song_Variable.h"
#include "..\song\video_play_manager.h"
#include "..\message.h"

#include <string>

using namespace std;

class query_song_manager
{
public:
	query_song_manager(void);
	~query_song_manager(void);

	/*
	功能：把查询结果赋值给歌曲列表
	参数：
	    query_song_result：查询的结果
		result_item_number：查询出来的字段数
		page_count:总共的页数
		cur_page_number：当前页的编号
	返回值：
	    true：成功
		false：失败
	*/
	bool set_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number,int page_show_row_count);
	bool set_song_recorder_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number);
	bool set_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number);
	bool set_test_or_select_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,bool test_song);
	bool set_syn_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums);
	bool set_handheld_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums);
	bool set_handheld_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums);
	bool set_recommend_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int nPos,bool singer_song);
	bool set_song_all_recorder_list(std::wstring query_song_result[],int result_item_number,int result_column_nums);
	bool set_listen_recommend_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums, song_info *songinfo);

	/*
	功能：组织节目单的xml文件给flash界面
	参数：
	    song_list_xml：组成的节目单xml形式的字符串
		video_manager：播放的视频管理类
		color：文字颜色
	返回值：
	   true：成功
	   false:失败
	*/
	bool make_song_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_show_row_count,FLASH_SONG_SHOW_MODE song_show_mode,int page_index);
	bool make_movie_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_show_row_count);
	bool make_test_song_list_xml(std::wstring &song_list_xml);
	bool make_song_list_one_xml(song_info &song_information,int song_number,video_play_manager &video_manager,TCHAR *playing_song_number,TCHAR *song_show_info,FLASH_SONG_SHOW_MODE song_show_mode,int picture_number,int page_index);
	bool make_recommend_song_list(std::wstring &song_list_xml,video_play_manager &video_manager);
	bool make_recorder_song_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_index);
	bool make_music_enjoy_list_xml(std::wstring  &song_list_xml,video_play_manager &video_manager, ST_MUSIC_ENJOY *pSme, int count);
	/*
	功能：初始化变量
	参数：
	    NULL
	返回值：
	    void
	*/
	void initialized_variables(void);
	
	/*
	功能：通过下标得到某首歌的歌曲信息
	参数：
	    song_suffix：歌曲下标
		song_infomation：返回的歌曲信息
	返回值：
	    song_info：歌曲信息
	*/
	 bool get_song_info(int song_suffix,song_info &song_infomation);
	 bool get_recorder_song_info(TCHAR* song_number,song_info &song_infomation);
	 bool get_recorder_song_info(int song_suffix,song_info &song_infomation);
	 bool get_test_or_select_song_info(int song_suffix,song_info &song_infomation,bool test_song);
	 bool get_select_song_info(TCHAR *song_number,song_info &song_infomation);
	 bool get_select_movie_info(TCHAR *song_number,song_info &song_infomation);
	 bool get_handheld_song_info(int song_suffix,song_info &song_infomation);


	 /*
	 功能：测试歌曲优先
	 参数：
	     number：要优先的编号
	 返回值：
	     true：成功
		 false：失败
	 */
	 bool test_song_priority(int number);

	 /*
	 功能：设置区分显示show_movie_name
	 参数：
	     number：要优先的编号
	 返回值：
	     true：成功
		 false：失败
	 */
	 void set_show_movie_name_flag(bool flag){m_theme_or_classification = flag;}
	 bool get_show_movie_name_flag(){return m_theme_or_classification;}

private:
	//查询出来的歌曲列表信息结果
	song_info pre_page_song_list[PAGE_SHOW_MAX_ROW_COUNT];  //前一页
	song_info cur_page_song_list[PAGE_SHOW_MAX_ROW_COUNT];  //当前页
	song_info next_page_song_list[PAGE_SHOW_MAX_ROW_COUNT]; //下一页

	song_info test_page_song_list[SELECT_SONG_MAX_COUNT];  //测试页或选择歌曲列表
	song_info m_movie_list[SELECT_SONG_MAX_COUNT];         //用于同步电影的列表
	song_info m_handheld_song_list[HANDHELD_PAGE_SHOW_ROW_COUNT]; //手持歌曲列表
	song_info m_recommend_song_list[RECOMMAND_SONG_INFO_COUNT];   //推荐歌曲列表
	song_info m_recorder_song_list[RECORDER_SHOW_PAGE_COUNT];   //录音页面

	bool song_list_exist;               //歌曲列表是否存在
	TCHAR m_singer_picture_path[256];   //歌星图片路径
	TCHAR m_song_picture_path[256];     //歌曲图片路径
	TCHAR m_singer_sex_picture_path[256];//歌星性别图片路径
	bool m_no_moive_name_show_lyric;    //没有电影名显示歌词

	//歌曲查询时，限制的行数
	int m_page_show_row_count;
	std::wstring m_default_song_color;   //默认歌曲颜色
	std::wstring m_playing_song_color;   //正播放歌曲的颜色
	std::wstring m_select_song_color;    //选择歌曲颜色
	bool m_theme_or_classification;		 //用于区分theme和classification , 显示show_movie_name
};

#endif


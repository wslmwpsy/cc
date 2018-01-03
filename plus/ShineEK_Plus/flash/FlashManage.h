#pragma once

#include "../message.h"

#include <vector>
using namespace std;

class CFlashManage
{
public:
	CFlashManage(void);
	~CFlashManage(void);

	/*
	功能：页面改变
	参数：
		request:返回的结果
		array_size：返回结果的数组大小
	    page_id:页面的ID
		language：使用的语言
	返回值：
	    true:成功
		false:失败
	*/
	bool page_change(TCHAR *request,int array_size,int page_id,int language,FLASH_SONG_SHOW_MODE song_show_mode);

	/*
	功能：记录页的索引
	参数：
		page_index：页的索引
	返回值：
		true:成功
		false：失败
	*/
	bool write_page_index(int page_index);
	/*
	功能：返回上一个页的索引
	参数：
		NULL
	返回值：
		成功：上一页的页索引
		现在是首页：-1
	*/
	int get_pre_page_index();

	/*
	功能：返回最后页的索引
	参数：
		NULL
	返回值：
		成功：最后页的索引
		现在是首页：-1
	*/
	int get_last_page_index();

	/*
	功能：得到页面的名字
	参数：
	    page_index：页面索引
	    name：页面名字
	返回值：
	    true：成功
		false：失败
	*/
	bool get_page_name(int page_index,TCHAR *page_name,FLASH_SONG_SHOW_MODE song_show_mode);

	/*
	功能：组织回调函数的字符串
	参数：
		request：返回的结果
		array_size：返回结果的数组大小
		command:操作名称
		args：参数
		page_operate_type：页操作类型
	返回值：
		true：成功
		false:失败
	*/
	bool make_request(TCHAR *request,int array_size,const TCHAR *command,const TCHAR *args);
	bool make_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type,FLASH_SONG_SHOW_MODE song_show_mode);
	bool make_singer_request(TCHAR *request,int array_size,const TCHAR *command,const TCHAR *args,bool refresh,int page_index,int page_operate_type);
	bool make_select_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type,FLASH_SONG_SHOW_MODE song_show_mode);
	bool make_recommend_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index);
	bool make_maiba_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type);
	bool make_maiba_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,const TCHAR* flagname,int page_operate_type);
	bool make_web_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index);
	bool make_music_enjoy_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type);
	bool make_trend_list_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type);

private:
	vector<int> screen_index;  //保存点击过的页索引，用于返回上一页，存储的页数不能超多 PAGE_MAX_NUMBER个
};

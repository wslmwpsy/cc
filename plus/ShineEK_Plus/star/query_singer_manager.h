#pragma once

#include "singer_variable.h"
#include "singer_info.h"

class query_singer_manager
{
public:
	query_singer_manager(void);
	~query_singer_manager(void);
	/*
	功能：把查询结果赋值给歌星列表
	参数：
		query_song_result：查询的结果
		result_item_number：查询出来的字段数
		page_count:总共的页数
		cur_page_number：当前页的编号
	返回值：
	true：成功
	false：失败
	*/
	bool set_singer_list(std::wstring query_singer_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number);
	bool set_handheld_singer_list(std::wstring query_singer_result[],int result_item_number,int result_column_nums);

	/*
	功能：组织节目单的xml文件给flash界面
	参数：
		song_list_xml：组成的节目单xml形式的字符串
	返回值：
		true：成功
		false:失败
	*/
	bool make_singer_list_xml(std::wstring &singer_list_xml);
	/*
	功能：初始化变量
	参数：
		NULL
	返回值：
		void
	*/
	void initialized_variables(void);
	/*
	功能：通过下标得到某个歌星的信息
	参数：
	    suffix:下标
	返回值：
	    singer_info：歌星的信息类
	*/
	singer_info get_singer_info(int suffix);
	singer_info get_handheld_singer_info(int suffix);

	/*
	功能：得到歌星图片路径
	参数：
	    path：歌星图片路径
	返回值：
	    true：成功
		false：失败
	*/
	bool get_star_picture_path(TCHAR *path);

	/*
	功能：通过歌星名字组织xml字符串
	参数：
	    singer_info_class：歌星信息类
		picture_number：解密的图片编号
		singer_xml：组织好的歌星字符串
	返回值：
	    true：成功
		false：失败
	*/
	bool make_singer_xml_by_name(singer_info &singer_info_class,int picture_number,TCHAR *singer_xml);

	void set_singer_page_show_row_count(int count) {m_singer_page_show_row_count = count; }

private:
	//查询出来的演唱者信息
	singer_info pre_page_singer_list[SINGER_PAGE_SHOW_ROW_COUNT_MAX];  //前一页
	singer_info cur_page_singer_list[SINGER_PAGE_SHOW_ROW_COUNT_MAX]; //当前页
	singer_info next_page_singer_list[SINGER_PAGE_SHOW_ROW_COUNT_MAX]; //下一页

	singer_info m_handheld_singer_list[SINGER_PAGE_SHOW_ROW_COUNT_MAX];  //手持用的

	bool singer_list_exist;                    //演唱者列表是否存在
	TCHAR m_star_picture_path[256];            //歌星图片路径
	std::wstring m_singer_name_default_color;  //歌星名字的默认颜色

	int m_singer_page_show_row_count;

};

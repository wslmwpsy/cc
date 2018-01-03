#pragma once
#include "song_info.h"
#include "../database/DBDataTypeDef.h"
#include "..\message.h"

#define SELECT_SONG_MAX_COUNT   99

class select_song_manager
{
public:
	select_song_manager(void);
	~select_song_manager(void);

	/*
	功能：初始化
	参数：
	    m_wnd：父窗口句柄
	返回值：
	    void
	*/
	void initialize(HWND m_wnd);
	/*
	功能：得到要播放的歌曲
	参数
	    song:歌曲的基本信息
	返回值：
	    true：成功
		false：失败	   
	*/
    bool get_play_song(song_info& song);
	//得到测机歌曲
	bool get_play_test_song(song_info& song);
	//通过下标得到测机歌曲
	bool get_test_song_by_suffix(song_info& song,int song_suffix);

	/*
	功能：得到下一首歌曲信息
	参数：
	    song:歌曲基本信息
	返回值：
	    true：成功
		false：失败
	*/
	bool get_next_song(song_info &song);
	/*
	功能：选择的歌曲是否为空
	参数：
	    void
	返回值：
	    true：空，没有歌曲了
		false：还有歌曲可播放
	*/
	bool empty();
	/*
	功能：返回总的选择的歌曲数
	参数：
	    void
	返回值：
	    选择的歌曲数
	*/
	int get_select_song_count(int count_type=0);
	
	/*
	功能：返回总的已唱歌曲数
	参数：
		void
	返回值：
		已唱的歌曲数
	*/
	int get_sing_song_count(void);

	/*
	功能：添加选择的歌曲
	参数：
	    song：歌曲信息类
		priority：是否优先
	返回值：
	    true：成功
		false：失败
	*/
	bool add_select_song(song_info &song,bool priority);
	/*
	功能：增加演唱的歌曲
	参数：
	    song:歌曲信息类
	返回值：
	    true：成功
		false：失败
	*/
	bool add_sing_song(song_info &song);

	/*
	功能：修改已选中的下载/更新标示
	参数：
	    song_id:歌曲id
	返回值：
	    true：成功
		false：失败
	*/
	bool modify_down_load_select_song(TCHAR * song_id,TCHAR* server_path,int server_pos,TCHAR* relative_path = NULL);


	/*
	功能：组织已唱或已选歌曲显示的字符串
	参数：
	    song_list_xml：要显示的xml字符串
		song_type：要显示已选歌曲还是已唱歌曲
		page_operate：页操作
	返回值：
	    true：成功
		false：失败
	*/
	bool make_song_list_xml(std::wstring &song_list_xml,enum SHOW_SONG_LIST_TYPE song_type,enum PAGE_OPERATE page_operate,FLASH_SONG_SHOW_MODE song_show_mode,int page_index);
	bool make_song_list_one_xml(song_info &song_information,int song_number,TCHAR *song_show_info,FLASH_SONG_SHOW_MODE song_show_mode,enum SHOW_SONG_LIST_TYPE song_type,int picture_number);

	/*
	功能：得到已唱或已选的页行信息
	参数：
		row：总的行数
		cur_page_number：当前页的编号
		total_page_count：总的页数
		song_type：要显示已选歌曲还是已唱歌曲
	返回值：
		true：成功
		false：失败
	*/
	bool get_page_row_info(int &row,int &cur_page_number,int &total_page_count,enum SHOW_SONG_LIST_TYPE song_type);

	/*
	功能：删除选择的某个歌曲
	参数：
	    song_number：歌曲的编号
		relative_position：相对位置：ture  绝对位置：false
	返回值：
	    成功：删除的歌曲编号
		失败：-1
	*/
	int delete_select_song(int song_number,bool relative_position);
	int delete_select_song_by_id(TCHAR *song_id);

	/*
	功能：得到选择歌曲的绝对位置
	参数：
		 song_number：歌曲的编号
	返回值：
	   绝对位置
	*/
	int get_select_song_absolute_position(int song_number);

	/*
	功能：优先选择的歌曲
	参数：
	    song_number：歌曲的编号
		relative_position：相对位置：ture  绝对位置：false
	返回值：
	     成功：优先的歌曲编号
		失败：-1
	*/
	int priority_select_song(int song_number,bool relative_position);

	/*
	功能：拖动排序已选的歌曲
	参数：
		nOrigin：歌曲的编号
		nDestination:目标位置（绝对位置）
		relative_position：拖动的歌曲是否是相对位置：ture  绝对位置：false
	返回值：
		成功：优先的歌曲编号
		失败：-1
	*/
	int drag_sort_select_song(int nOrigin, int nDestination, bool relative_position);

	bool random_sort_select_song();
	/*
	功能：通过下标得到歌曲信息
	参数：
	    song_information[out]：歌曲信息
	    star_suffix[in]：选择的个性下标
	返回值：
	    true：成功
		false：失败
	*/
	bool get_select_song_information(song_info &song_information, int star_suffix,bool relative_position);

	/*
	功能：通过下标得到歌曲信息
	参数：
		song_information[out]：歌曲信息
		select_suffix[in]：选择的个性下标
	返回值：
		true：成功
		false：失败
	*/
	bool get_sing_song_information(song_info &song_information,int select_suffix,bool relative_position);

	/*
	功能：对选择的歌曲交换位置
	参数：
	    first_switch_pos：第一个要交换的位置
		sencond_switch_pos：第二个交换的位置
		change_page_switch：该改变了页之后的交换
	返回值：
	    true：成功
		false：失败
	*/
	bool select_song_switch_position(int first_switch_pos,int second_switch_pos,bool change_page_switch);

	/*
	功能：通过歌曲ID，查询某首歌曲，是否存在于已选歌曲中
	参数：
	    song_id：歌曲的ID
		play_number：该歌曲所处的播放顺序
	返回值：
	    true：存在
		false：不存在
	*/
	bool query_select_song_by_id(TCHAR *song_id,int &play_number, bool isDown = true);

	/*
	功能：通过歌曲ID，查询某首歌曲，是否存在于已选歌曲中
	参数：
	    song_id：歌曲的ID
		play_number：该歌曲所处的播放顺序
	返回值：
	    true：存在
		false：不存在
	*/
	bool query_select_song_by_id_ex(TCHAR *song_id,int &play_number);

	/*
	功能：改变当前显示的页数
	参数：
	    page_number：要显示的页数
	返回值：
	    void
	*/
	void set_show_page_number(int page_number);

	/*
	功能：清空选择的歌曲
	参数：
	   void
   返回值：
       void
	*/
	void clear_select_song(bool clear_sing);

	/*
	功能：得到测试歌曲的名字
	参数：
	    cur_song_name：当前歌曲的名字
		next_song_name：下一个歌曲的名字
	返回值：
	    true：成功
		false：失败
	*/
	bool get_test_song_name(TCHAR *cur_song_name,TCHAR *next_song_name);

	/*
	功能：设置测试歌曲播放的是上一首还是下一首
	参数：
	    next_song：true：下一首， false：上一首
	返回值：
	    void
	*/
	void set_test_song_play_order(bool next_song);

	/*
	功能：改变页插入
	参数：
	    pre_page：true：向前一页插入，false：向后一页插入
		src_position：相对于当页的歌曲编号
		first_page_insert：true：第一次页插入，false：不是第一次
		change_song_xml：返回的歌曲xml
	返回值：
	   true：成功
	   false：失败
	*/
	bool change_page_insert(bool pre_page,int src_position,bool first_page_insert,std::wstring &change_song_xml);

	/*
	功能：得到要闪动的item编号
	参数：
	    void
	返回值：
	     要闪动的编号
	*/
	int get_flicker_item_number(void);

	/*
	功能：打乱已选歌曲
	参数：
	    void
	返回值：
	    void
	*/
	void mess_selected_song(void);

private:
	song_info select_song[SELECT_SONG_MAX_COUNT];   //选择的歌曲
	int select_song_count;                          //目前选择的歌曲数
	song_info sing_song[SELECT_SONG_MAX_COUNT];     //已唱的歌曲
	int sing_song_count;                            //已唱歌曲的数

	int cur_show_page_number;                       //当前显示的页数
	int total_page_number;                          //总的页数

	int m_cur_page_first_position;                  //翻页插入时，当前页的首位置
	int m_song_insert_position;                     //歌曲的插入位置

	int cur_select_test_song_number;                //当前选择的测试歌曲下标
	bool m_test_next_song;                          //测试下一个歌曲

	
	int m_page_show_row_count;                     //每页可以显示的行数

	TCHAR m_sing_song_number[128];                  //已唱的歌曲编号

	std::wstring m_default_song_row_color;         //默认歌曲颜色
	std::wstring m_select_song_row_color;          //选择歌曲颜色
	bool m_no_moive_name_show_lyric;               //没有电影名显示歌词

	TCHAR m_singer_picture_path[256];              //歌星图片路径
	TCHAR m_song_picture_path[256];                //歌曲图片路径
	TCHAR m_singer_sex_picture_path[256];          //歌星性别图片路径

	//父窗口句柄
	HWND m_parent_handle; 
};

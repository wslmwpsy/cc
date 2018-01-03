#pragma once

#include "song_Variable.h"
#include "public_video_manager.h"
#include "select_song_manager.h"
#include "..\ministry_of_culture\VodADInterface.h"
#include "dj_song_manager.h"

class video_play_manager
{
public:
	video_play_manager(void);
	~video_play_manager(void);

	/*
	功能：初始化
	参数：
		m_wnd：父窗口句柄
	返回值：
		void
	*/
	void initialize(HWND m_wnd,TCHAR *ip);

	/*
	功能：得到要播放的视频
	参数：
	    video_info：视频信息
		ad_item：广告类
		play_ad：是否播放广告
	返回值：
	    1：歌曲
		0：广告
		-1：失败
	*/
	int get_next_play_video(song_info& video_info,AD_ITEM_CULTURE *ad_item,bool play_ad);
	
	/*
	功能：得到下一个要播放的歌曲
	参数：
	    song：歌曲基本信息类
	返回值：
	    true：成功
		false：失败
	*/
	bool get_next_play_song(song_info& song);

	/*
	功能：设置正在播放的视频
	参数：
	    video_info：视频信息类
	返回值：
	    true：成功
		false：失败
	*/
	bool set_playing_video(song_info &video_info);

	/*
	功能：得到正在播放的视频
	参数：
	    video_info：视频信息
	返回值：
	    true：成功
		false：失败
	*/
	bool get_playing_video(song_info &video_info);
	/*
	功能：插入选中的歌曲到已选歌曲管理类中
	参数;
	    song_information：歌曲信息类
		priority：是否优先
	返回值：
	    true：成功
		false：失败
	*/
	bool add_select_song(song_info &song_information,bool priority);

	/*
	功能：把已唱的歌曲放到已唱歌曲列表中
	参数：
	    song_information：歌曲基本信息类
	返回值：
	    true：成功
		false：失败
	*/
	bool add_sing_song(song_info &song_information);

	/*
	功能：修改当前下载/更新标示
	参数：
		song_id:歌曲id
	返回值：
		true:成功
		false:失败
	*/
	bool modify_down_load_select_song(TCHAR* song_id,TCHAR* server_path,int server_pos,TCHAR* relative_path = NULL);


	/*
	功能：返回目前播放器所处的状态
	参数：
	    void
	返回值：
	    PLAYER_PLAY_STATE：播放系统目前所处的状态
	*/
	enum PLAYER_PLAY_STATE get_player_cur_state(void);
	enum PLAYER_PLAY_STATE get_player_next_state(void);

	/*
	功能：改变播放器的状态
	参数：
		player_state：播放器的状态
	返回值：
		true：成功
		false：失败
	*/
	bool set_player_cur_state(enum PLAYER_PLAY_STATE player_state);
	bool set_player_next_state(enum PLAYER_PLAY_STATE player_state);

	/*
	功能：组织歌曲显示的字符串
	参数：
		song_list_xml：要显示的xml字符串
		song_type：要显示已选歌曲还是已唱歌曲
		page_operate：页操作
	返回值：
		true：成功
		false：失败
	*/
	bool make_song_list_xml(std::wstring &song_list_xml,enum SHOW_SONG_LIST_TYPE song_type,enum PAGE_OPERATE page_operate,FLASH_SONG_SHOW_MODE song_show_mode,int page_index);

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
	功能：得到要播放的音频文件路径
	参数：
		wave_type：混合音频类型
		audio_path：音频路径
		picture_path：图片路径
		soft_code：软解
	返回值：
		true：成功
		false：失败
	*/
	bool get_atmosphere_wave_info(int wave_type,TCHAR *audio_path,TCHAR *picture_path,bool soft_code);
	
	/*
	功能：得到已选歌曲的总数
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
		star_suffix[in]：选择的歌曲下标
		relative_position：相对位置：true  绝对位置：false
	返回值：
		true：成功
		false：失败
	*/
	bool get_select_song_information(song_info &song_information, int star_suffix,bool relative_position);

	/*
	功能：通过下标得到歌曲信息
	参数：
		song_information[out]：歌曲信息
		select_suffix[in]：选择的歌曲下标
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
	功能：得到要播放的环境音频的文件路径
	参数：
		wave_type：混合音频类型
		path：路径
	返回值：
		true：成功
		false：失败
	*/
	bool get_environment_wave_info(int wave_type,TCHAR *path);

	/*
	功能：得到是否可以被切换掉
	参数：
	    void
	返回值：
	    true：允许切掉
		false：不允许切掉
	*/
	bool video_allow_cut(void);

	/*
	功能：通过歌曲ID，查询某首歌曲，是否存在于已选歌曲中
	参数：
		song_id：歌曲的ID
		play_number：该歌曲所处的播放顺序
	返回值：
		true：存在
		false：不存在
	*/
	bool query_select_song_by_id(TCHAR *song_id,int &play_number,bool isDown = true);

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
	功能：通过下标得到测机歌曲
	参数：
	    song：歌曲信息
		song_suffix：歌曲的下标
	返回值：
	    true：成功
		false：失败
	*/
	bool get_test_song_by_suffix(song_info& song,int song_suffix);

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
	功能：得到dj歌曲数目
	参数：
		void
	返回值：
		实际的dj歌曲数目
	*/
	int get_dj_song_count(void);

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
	功能：通过歌曲名字，查询歌曲信息
	参数：
		db_query_class：数据库查询类
	返回值：
		void
	*/
	void query_idlesse_song_info(DB_Query &db_query_class);

	/*
	功能：打乱已选歌曲
	参数：
	    void
	返回值：
	    void
	*/
	void mess_selected_song(void);

	/*
	功能：返回当前空闲的索引
	参数：
	返回值：
	   int
	*/
	int get_cur_idlesse_video_number();

	/*
	功能：设置当前空闲的索引
	参数：
		number
	返回值：
	   void
	*/
	void set_cur_idlesse_video_number(int number);

	/*
	功能：设置空闲歌曲按照时间播放空闲
	参数：
		number:索引值
	返回值：
	*/
	void set_cur_idlesse_list();

private:
	enum PLAYER_PLAY_STATE player_cur_state;      //播放器当前所处的状态
	enum PLAYER_PLAY_STATE player_next_state;     //播放器所处的下一个状态
	public_video_manager m_public_video_manager;  //公共视频管理的类
	select_song_manager m_select_song_manager;    //以选或已唱歌曲管理类
	song_info m_playing_video;                    //正在播放的视频
	dj_song_manager m_dj_song_manager;            //dj歌曲播放管理类
	bool playing_video_exist;                     //是否存在正在播放的视频

	//ad
	bool m_allow_cut;                            //广告是否允许切掉
	bool m_first_begin_ad;                       //第一个开机广告
};

#pragma once

#include "player/player_manager.h"
#include "database/DBQuery.h"
#include "flash/FlashPlayer.h"
#include "flash/FlashManage.h"
#include "song/query_song_manager.h"
#include "com/inherit_com.h"
#include "ChildWnd.h"
#include "osd/osd_play_manager.h"
#include "tape/audio.h"
#include "common/llock.h"
#include "screen_saver/screen_saver_window.h"
#include "star/query_singer_manager.h"
#include "handwriting/handwriting.h" 
#include "bomb/bomb.h"
#include "ad/AD_manager.h"
#include "doorplate_machine/DoorplateWnd.h"
#include "service_picture/show_service_picture.h"
#include "U_disk/U_disk_song.h"
#include "game/game_manager.h"
#include "common/mac_address.h"
#include "flash/PageData.h"
#include "audio_effect/AudioEffect.h"
#include "mysql/MySQL_DB.h"
#include "QR_Encode/QR_Encode.h"
#include "lyricSearch/SearchLyric.h"
#include "os/XWinVer.h"
#include "tape/mixerlib.h"
#include "http/http.h"
#include "member/memeber_song_manager.h"
#include "json/json.h"
#include <fstream>
#include "html/HtmlCtrl.h"

#include <queue>

#include "dbsql/DbSQL.h"
#include "film/query_film_manager.h"
#include "PluginsEx.h"

#include "RTCOMDLL/RTCOMDLL.h"
#include "RTCOMDLL/RTCOMDLL_Data.h"
#include "lyric/LyricManager.h"
#include "trendlist/TrendListManager.h"
#include "InterScreen/InterScreenManager.h"
#include "screenflash/TransparentWnd.h"
#include "PassManager/PassManager.h"

#include "lyric/ParseLyricsForKSC.h"

#include "common/zlib.h"
#include "common/XUnzip.h"
#include <direct.h>
#include "CommLib/http.h"
#include "ShineAxBrowse/CDShineAxBrowse.h"

#define VIDEO_SHOW_FULL_SCREEN

#define SLEEP_FOR Sleep(25)

//定义SQL Server结构体
typedef struct struct_show_cube_song{
	int id;
	wstring song_id;
	wstring song_name;
	wstring singer_id1;
	wstring singer_id2;
	wstring singer_id3;
	wstring singer_id4;
	wstring song_add_datetime;
	wstring serv_path1;
	wstring serv_path2;
	wstring serv_path3;
	wstring song_relative_path;
	wstring song_wechat_url;
	int song_type;
	int theme_type;
	int language;
	int song_name_word;
	wstring song_name_spell;
	int song_version;
	wstring file_format;
	wstring song_name_tip;
	wstring lyric;
	wstring singer_name;
	int reserve_1;
	int reserve_2;
	int reserve_3;
	int reserve_4;
	int reserve_5;
	wstring reserve_6;
	wstring reserve_7;
	wstring reserve_8;
	wstring reserve_9;
	wstring reserve_10;
	wstring reserve_11;
	wstring reserve_12;
	wstring reserve_13;
	wstring reserve_14;
	wstring reserve_15;
	wstring reserve_16;
	wstring reserve_17;
	wstring reserve_18;
	wstring reserve_19;
	wstring reserve_20;
}SHOW_CUBE_SONG, *LP_SHOW_CUBE_SONG;

typedef struct struct_show_cube_singer
{
	int id;
	wstring singer_id;
	wstring singer_name;
	wstring singer_picture;
	wstring datatime;
	wstring singer_name_spell;
	int singer_name_count;
	wstring singer_wechat_url;
	int singer_type;
	int singer_sex;
	int singer_region;
	wstring singer_introduction;
	int reserve_1;
	int reserve_2;
	int reserve_3;
	int reserve_4;
	int reserve_5;
	wstring reserve_6;
	wstring reserve_7;
	wstring reserve_8;
	wstring reserve_9;
	wstring reserve_10;
	wstring reserve_11;
	wstring reserve_12;
	wstring reserve_13;
	wstring reserve_14;
	wstring reserve_15;
}SHOW_CUBE_SINGER, *LP_SHOW_CUBE_SINGER;

typedef vector<LP_SHOW_CUBE_SONG> SHOW_CUBE_SONG_VEC;
typedef vector<LP_SHOW_CUBE_SINGER> SHOW_CUBE_SINGER_VEC;

//*****************************照片mv结构体*********************************
typedef struct tag_imageInfo{
	wstring imageUrl; //图片地址
	int Orientation; //方向
}Image_Info, *LPImage_Info;
//照片mv结构体
typedef struct st_picture_mv{
	song_info songInfo;		//歌曲信息
	int priority;			//是否优先 0：插入 1：优先
	TCHAR callDelUrl[2048]; //删除服务器上的照片文件夹
	vector<Image_Info> imageInfoVec; //照片路径的数组
	int itemplate;
	string guid;
	st_picture_mv(){
		songInfo.initialized_variables();
		priority = 0;
		memset(callDelUrl, 0x00, sizeof(callDelUrl));
		imageInfoVec.clear();
		itemplate = 0;
		guid = "";
	}
}ST_PICTURE_MV, *LPST_PICTURE_MV;

using namespace shine;
using namespace dagexing;
using namespace std;

// Cflashktv10Wnd
#define MAX_MENBER_NUM  500
#define PK_MEMBER_SIZE  500

//发送pk会员数据
typedef struct PK_MEMBER_DATA
{
	TCHAR ipaddress[256];   //发送的ip地址
	TCHAR name[256];      //会员名字
	TCHAR nsex[2];              //性别 1、男，2、女
	TCHAR nstatus[10];           //状态 0、空闲，1、正在pk 
	TCHAR nBoxIp[256];          //盒子ip
	int  nPort;               //打流端口
}PK_MEMBER_DATA;

enum video_dating_status{
	VD_IDLE, //空闲
	VD_BUSY, //忙碌
	VD_NOTDISTURB, //免打扰
	VD_CLOSE_ROOM //关房，退出
};
typedef struct video_dating
{
	TCHAR name[MAX_PATH];	//名字  包房名 or 微信名
	TCHAR ip[32];			//客户端ip地址
	int ncharacter;			//角色 1、靓仔 2、靓妹 3、大叔 4、御姐 5、帅哥 6、美女 7、男神 8、女神 9、正太 10、萝莉
	int nstatus;			//状态 0、空闲 1、忙碌 2、免打扰
}VIDEO_DATING, *P_VIDEO_DATING;

class Cflashktv10Wnd : public CWnd
{
	DECLARE_DYNAMIC(Cflashktv10Wnd)

	//定义向盒子请求数据的结构
	typedef struct REQUEST_BOX_DATA
	{
		Cflashktv10Wnd *pThis;
		TCHAR request_data[1024];   //ip
		int nPort;				 //端口号
	}REQUEST_BOX_DATA;

public:
	Cflashktv10Wnd();
	virtual ~Cflashktv10Wnd();
	BOOL CreateWnd();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	//flash function
	//flash界面的消息响应函数
	void FlashCallShockwaveflash(LPCTSTR request);

	/*
	功能：处理flash界面发送过来的消息
	参数：
		command：操作
		args：传递过来的参数
	返回值：
		void
	*/
	void flash_message_call(const TCHAR *command,const TCHAR *args);
	void flash_message_call_ex(const TCHAR *command,const TCHAR *args);

	//flash响应的分函数,划分成各个模块
	//歌曲
	void flash_message_call_function(int function_code,int lpara=0,bool recv_msg=false);
	void flash_message_call_song_pinyin(select_expr &table_select_expr,const TCHAR *args);
	void flash_message_call_song_query(select_expr &table_select_expr,const TCHAR *args,SONG_LANGUAGE query_language);
	void flash_message_call_song_japanese(select_expr &table_select_expr,const TCHAR *args);
	void flash_message_call_singer_japanese(const TCHAR *args);
	void flash_message_call_language(const TCHAR *args);
	void flash_message_call_song_word_count(select_expr &table_select_expr,const TCHAR *args);
	void flash_message_call_theme(const TCHAR *args);
	void flash_message_call_era(const TCHAR *args);
	void flash_message_call_new_theme(const TCHAR *args);
	void flash_message_call_song_version(const TCHAR *args);
	void flash_message_call_singer_sex(const TCHAR *args);
	void flash_message_call_new_song(const TCHAR *args);
	void flash_message_call_file_format(const TCHAR* args);
	bool flash_message_call_song_sort_song();

	void flash_message_call_voice_china();   //好声音
	void flash_message_call_cloud_song();

	//戏曲分类查询
	void flash_message_call_opera(const TCHAR *args);
	//@priority：是否优先 number_type:歌的类型  0，点歌  1.下载 2.更新
	void flash_message_call_select_song(const TCHAR *args,bool priority,bool singed_page,bool priority_type,int number_type=0);
	void flash_message_call_maiba_song(const TCHAR *args,bool priority,bool singed_page);
	void flash_message_call_maiba_song(MAIBA_SONG_INFO_STU &maiba_song_info);
	void flash_message_call_dekaron_song(const TCHAR *args,bool priority,bool singed_page);
	void flash_message_call_recorder_select_song(const TCHAR* args,bool priority);
	void flash_message_call_arena_song(MAIBA_HEIGHT_RANKING &maiba_song_info);
	void flash_message_call_music_enjoy(int page_code, const TCHAR *args);
	
	//从网络取一条数据
	void flash_message_call_get_web_select_song(const TCHAR* args);

	void flash_message_call_U_disk_select_song(const TCHAR *args);
	void flash_message_call_recommend_select_song(const TCHAR* args);
	//预览页面选中歌曲
	void flash_message_call_preview_select_song(bool priority);
	//添加为私人歌曲，@preview_song：收藏的是否是预览歌曲
	void flash_message_call_person_song(const TCHAR *args,bool preview_song);
	//预览歌曲
	void flash_message_call_preview_song(const TCHAR *args);
	//播放网络视频
	void flash_message_call_www_music(const TCHAR *preview_path);
	//预览控制
	void flash_message_call_preview_control(const TCHAR *args);
	void flash_message_call_preview_change_play_pos(const TCHAR *args);
	//会员歌曲拼音查询
	void flash_message_call_member_song_pinyin(const TCHAR *args);
	//蒙文输入意见调查
	void flash_message_call_mongolia_input_opinion(const TCHAR *args);
	//献花，
	void flash_message_call_flowers_song(const TCHAR *args,bool preview_song);

	//歌星
	void flash_message_call_singer_pinyin(const TCHAR *args);
	void flash_message_call_singer_query(const TCHAR *args,SONG_LANGUAGE query_language);
	void flash_message_call_singer_word_count(const TCHAR *args);
	void flash_message_call_singer_region(const TCHAR *args);
	void flash_message_call_singer_sex_ex(const TCHAR *args);
	void flash_message_call_singer_select(const TCHAR *args);
	void flash_message_call_singer_clear_all(const TCHAR *args);
	//歌曲跳转到歌星
	void flash_message_call_song_singer(const TCHAR *args);

	//页面跳转
	void flash_message_call_page_jump(int page_number, bool allow_repeat=false);

	//测试列表优先
	void flash_message_call_test_priority(const TCHAR *args);

	//把所有测试歌曲放到已选中
	void flash_message_call_save_test_song(void);
	//记录测试结果
	bool flash_message_call_save_test_result(const TCHAR *args);
	//检索面板改变
	void flash_message_call_query_board_change(const TCHAR *args);
	//手写字选择
	void flash_message_call_select_recognize_word(const TCHAR *args);
	//会员注册,登录
	void flash_message_call_member_login(const TCHAR *args);
	//改变手写语言
	void flash_message_call_change_handwriting_language(const TCHAR *args);
	//具体的服务图片展示
	void flash_message_call_service(const TCHAR *args);

	//酒水软件
	void flash_message_call_drinks(void);
	//消费查询外挂软件
	void flash_message_call_consume(void);
	//电影故事情节
	void flash_message_call_movie_story(const TCHAR *args,bool memory_state);
	//电影拼音查询
	void flash_message_call_movie_pinyin(const TCHAR *args);
	void flash_message_call_movie_query(const TCHAR *args,SONG_LANGUAGE query_language);
	void flash_message_call_movie_japanese(const TCHAR *args);
	//电影字数查询
	void flash_message_call_movie_word_count(const TCHAR *args);
	//意见调查结果
	void flash_message_call_survey_result(int question_number,const TCHAR *args);
	//提示书写意见或号码
	void flash_message_call_surver_tip_message(const TCHAR *args);
	//书写定制歌曲信息或号码
	void flash_message_call_custom_tip_message(const TCHAR* args); 
	//提交意见
	void flash_message_call_submit_opinion(const TCHAR *args);

	void flash_message_call_submit_custom_song(const TCHAR* args);
	//手写意见调查的联系方式
	void flash_message_call_write_phone(const TCHAR *args);
	//手写定制歌曲的联系方式
	void flash_message_call_custom_phone(const TCHAR* args);
	//录音
	void flash_message_call_recorder_audio(const TCHAR *args);
	//半自动录音开启录音
	void flash_message_call_recorder_audio_type(const TCHAR *args,bool recv_msg);
	//系统管理
	void flash_message_call_system_manager(const TCHAR *args);
	//重复选同一首歌曲时，进行提示
	void flash_message_call_select_song_tip(const TCHAR *args);
	//编号点歌
	void flash_message_call_number_select_song(const TCHAR *args);

	//查询的类别
	void flash_message_call_query_song_type(const TCHAR* args);

	//具体的麦霸相关的信息
	void flash_message_call_maiba(enum MAIBA_TYPE maiba_type,const TCHAR *args);
	 
	/*
	功能：刻盘
	参数：
		args：需要刻盘的编号
	返回值：
		void
	*/
	void flash_message_call_submit_recorder_song(const TCHAR *args);

	
	/*
	功能：分享
	参数：
		args：需要分享的编号
	返回值：
		void
	*/
	void flash_message_call_share_recorder_audio(const TCHAR *args, bool recv_msg);
	static UINT share_audio_file_thread(LPVOID pPara);
	UINT share_audio_file_to_internet(void);

	void flash_message_call_share_area_recorder_audio(MAIBA_HEIGHT_RANKING &maiba_share_info);
	void flash_message_call_share_web_song(MAIBA_SONG_INFO_STU &maiba_song_info);
	/*
	功能：查询测试歌曲，并显示到测机界面上
	参数：
		void
	返回值;
	   true：成功
	   false：失败
	*/
	bool test_song_query_show_data(void);
	
	/*
	功能：得到显卡的信息，包括起始坐标和分辨率
	参数：
		device_number：设备编号
		position_x：起始X坐标
		position_y：起始Y坐标
		width：宽度
		height：高度
	返回值：
		true：成功
		false：失败
	*/
	bool get_display_device_settings(int device_number,int &position_x,int &position_y,int &width,int &height);

	/*
	播放逻辑：静音时，判断是否取消静音
	bChange:若为true，直接取消静音
	*/
	bool DealMuteState(bool bChange = false);
	/*
	功能：设置显示器的分辨率
	参数：
		device_number：设备编号
		start_x：起始X坐标
		start_y：起始Y坐标
		width：宽度
		height：高度
	返回值：
		void
	*/
	bool set_display_device_resolution(int device_number,int start_x,int start_y,int width,int height);

	/*
	功能：自动隐藏或显示window的任务栏
	参数：
		hide：隐藏或显示的标示  true：隐藏  false：显示
	返回值：
		void
	*/
	void hide_window_task_bar(bool hide);

	/*
	功能：删除过期的日志
	参数：
		void
	返回值：
		void
	*/
	void delete_expire_log(void);

	/*
	功能：删除录音文件
	参数：
		void
	返回值：
		void
	*/
	void delete_recorder_file(void);

	/*
	功能：一个辅助线程
	参数：
		pParam：传递的参数
	返回值：
		UINT
	*/
	static UINT assistant_thread(LPVOID pParam);

	//数据库线程
	static UINT DB_thread(LPVOID pParam);

	/*
	功能：接收后台发送过来的开关房数据线程
	参数：
		pParam：传递的参数
	返回值：
		UINT
	*/
	static UINT recv_server_data_thread(LPVOID pParam);


	/*
	功能：接受后台发送的开关房数据
	参数：
		void
	返回值：
		UINT
	*/
	UINT recv_server_data(void);

		/*
	功能：接受广播消息数据
	参数：
		void
	返回值：
		UINT
	*/
	static UINT recv_server_voice_china_udp_thread(LPVOID pParam);
	
	UINT recv_server_voice_china_udp(void);

	bool shine_parse_voice_china_data(char* recv_data);
	/*
	功能：检测加密狗和发送数据给前置机
	参数：
		parent_hwnd：父句柄
	返回值：
		UINT
	*/
	UINT find_dog_and_precomputer(HWND parent_hwnd);

	/*
	功能：显示flash界面
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool show_flash_interface(void);
	/*
	功能：打开中控盒串口
	参数：
		void
	返回值：
		void
	*/
	void open_control_box_com(void);

	/*
	功能：显示logo
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool show_logo_osd(void);

	/*
	功能：显示下一副logo图片
	参数：
		reload：重新载入
	返回值：
		void
	*/
	void show_next_logo_osd(bool reload);

	/*
	功能：在flash上显示滚动字幕
	参数：
		text：要显示的文字
		place_notic:是否显示公告
	返回值：
		void
	*/
	void show_text_on_flash(const TCHAR *text,bool place_notice=false);

	/*
	功能：主flash的函数调用
	参数：
		request：发送给flash的信息
	返回值：
		true：成功
		false：失败
	*/
	bool flash_player_call_function(TCHAR *request);

	/*
	功能：播放下一个视频
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool play_next_video(void);

	/*
	功能：发送主被控数据
	参数：
		data：要发送的数据
		data_len：数据长度
	返回值：
		true：成功
		false：失败
	*/
	bool send_master_slave_data(TCHAR *wide_data,char *multile_data,int data_len=0);
	bool send_master_slave_data_udp(TCHAR *wide_data,char *multile_data,int data_len,char *ip,u_short port);

	void send_light_control_udp(LINGHT_CONTROL light_control_data);

	/*
	功能：开始录音
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool start_recorder_audio(void);

	/*
	功能：停止录音
	参数：
		play_next：播放下一个视频
	返回值：
		void
	*/
	int stop_recorder_audio(bool play_next,bool MixerAudio,bool play_finish);

	/*
	功能：重新显示当前页
	参数：
		requery：重新检索
	返回值：
		true：成功
		false：失败
	*/
	bool refresh_screen_list(bool requery=false);
	//刷新歌曲屏幕列表
	bool refresh_song_screen_list(void);
	bool refresh_movie_screnn_list(void);

	/*
	功能：录入录音信息到数据库中
	参数：
		void
	返回值：
		void
	*/
	void insert_recorder_song_into_database(void);

	/*
	功能：显示已选或已唱的歌曲
	参数：
		song_type：已唱还是已选歌曲
		page_operate：页操作，上下翻页
		page_operate_type：页操作类型标示  说明：左划屏：1 右划屏：2   点上页按钮：3  点下页按钮：4  第一页或当前页：0

	返回值：
		true：成功
		false：失败
	*/
	bool show_select_or_sing_song(enum SHOW_SONG_LIST_TYPE song_type,enum PAGE_OPERATE page_operate,int page_operate_type);
	bool show_recorder_arena_song(enum PAGE_OPERATE page_operate,int page_operate_type, int maibaType = -1);

	/*
		显示网络麦霸数据
	*/
	bool flash_show_maiba_song();

	/*
	功能：flash上显示提示信息
	参数：
		msg_code：要显示的内容编码
	返回值：
		void
	*/
	void flash_show_tip_message_chVip(TCHAR *tip_msg);
	void flash_show_tip_message_vip(int msg_code,bool back_tip=false);
	void flash_show_tip_message(int msg_code,bool back_tip=false);
	void flash_show_tip_message(TCHAR *tip_msg);

	/*
	功能：停止控制osd和广告的背景osd logo
	参数：
		void
	返回值：
		void
	*/
	void stop_control_osd_logo(void);

	/*
	功能：发送控制码给主被控机
	参数：
		control_code：控制码
	返回值：
		void
	*/
	void send_master_slave_control_code(int control_code);

	/*
	功能：显示控制功能的OSD图片
	参数：
		show_content：显示的内容
	返回值：
		true：成功
		false：失败
	*/
	bool show_control_osd(enum OSD_SHOW_CONTENT show_content);

	/*
	功能：显示音量条
	参数：
		bar_flag：标示
	返回值：
		void
	*/
	void show_volume_bar_on_tv(VOLUMN_BAR_FLAG bar_flag);

	/*
	功能：记录发送给前置机的信息
	参数：
		ad_type：广告类型
	返回值：
		void
	*/
	void set_precomputer_send_info(enum PRECOMPUTER_SEND_TYPE ad_type);

	/*
	功能：拷贝发送给前置机的信息给发送结构体
	参数：
		ad_type：广告类型
	返回值：
		void
	*/
	void copy_precomputer_send_info(enum PRECOMPUTER_SEND_TYPE ad_type);
	void copy_precomputer_video_send_info();

	/*
	功能：得到控制文字
	参数：
		text：要是的文字
	返回值：
		true：成功
		false：失败
	*/
	bool get_control_text(enum OSD_SHOW_CONTENT show_content,TCHAR *text);

	/*
	功能：页面改变
	参数：
		page_code：页面标示码
		page_init：页面要进行初始化
	返回值：
		true：成功
		false：失败
	*/
	bool page_change(int page_code,bool page_init=true);
	bool page_change_init(void);
	bool page_change_function(int page_code);

	/*
	功能：根据条件查询数据库的歌曲表，并显示到flash界面上
	参数:
		table_select_expr：歌曲选择表达式
		group_item：分组字段
		order_item:排序字段和排序模式
		page_expr:是否是页面跳转时的查询
	返回值：
		true:成功
		false：失败
	*/
	bool song_query_show_data(select_expr &table_select_expr,bool bShowTip=true,bool page_expr=false, bool show_movie_name = false);
	//返回值：0：失败 1：第一次查询成功  2：第二次查询成功
	int song_query_two_show_data(select_expr &table_select_expr,int condition_number=0,query_condition *src_query_condition=NULL);
	//成员歌曲
	bool member_song_query_show_data(void);
	//查询阳光秀吧的歌曲
	bool song_query_show_data_by_sql_server();
	/*
	功能：查询录音歌曲表，并显示到flash界面上
	参数：
	   void
   返回值：
	   true：成功
	   false：失败
	*/
	bool song_recorder_query_show_data(PAGE_OPERATE page_operate = FIRST_PAGE_OPERATE);
	bool song_recorder_query_all_show_data(void);
	/*
	功能：查询录音歌曲表，并显示到flash界面上
	参数：
	   void
   返回值：
	   true：成功
	   false：失败
	*/
	bool song_recorder_query_show_data_by_id(TCHAR *pargs);

	/*
	功能：发送请求的服务到消息系统和中控盒
	参数：
		service_content：服务的内容
	返回值：
		void
	*/
	void send_request_service(int button_number,TCHAR *service_content);

	/*
	功能：发送消息给消息系统
	参数：
		message：具体的消息内容
	返回值：
		void
	*/
	bool send_message_to_msg_server(TCHAR *message);

	/*
	功能：发送消息的线程
	参数：
		pParam：传递的参数
	返回值：
		UINT
	*/
	static UINT send_message_thread(LPVOID pParam);

	/*
	功能：发送消息到服务器的函数
	参数：
		void
	返回值：
		UINT
	*/
	bool send_message_function(void);

	/*
	功能：启动控制osd显示时间的定时器
	参数：
		void
	返回值：
		void
	*/
	void set_control_osd_show_timer(void);

	/*
	功能：启动控制bmp图片显示时间的定时器
	参数：
		show_time：显示时间
	返回值：
		void
	*/
	void set_bmp_picture_show_timer(int show_time);
	void set_score_show_timer(int show_time);

	/*
	功能：更新flash控制按钮的状态
	参数：
		void
	返回值：
		void
	*/
	void update_flash_control_button(void);

	/*
	功能：更新音效数值
	参数：
		void
	返回值：
		void
	*/
	void update_flash_audio_info(void);

	/*
	功能：显示flash上的滚动文字
	参数：
		void
	返回值：
		定时器的时间间隔
	*/
	int timer_show_flash_text(void);

	/*
	功能：显示电视上的滚动文字
	参数：
		void
	返回值：
		定时器的时间间隔
	*/
	int timer_show_tv_text(void);

	/*
	功能：更改flash的背景图片
	参数：
		void
	返回值：
		定时器的时间间隔
	*/
	int timer_show_flash_background_picture(void);

	/*
	功能：在flash上显示logo
	参数：
		void
	返回值：
		定时器的时间间隔
	*/
	int timer_show_flash_logo(void);

	/*
	功能：在电视上显示logo
	参数：
		void
	返回值：
		定时器的时间间隔
	*/
	int timer_show_tv_logo(void);

	/*
	功能：显示图片屏保
	参数：
		void
	返回值：
		void
	*/
	void timer_show_pictrue_screen_saver(void);

	/*
	功能：显示视频屏保
	参数：
		void
	返回值：
		void
	*/
	void timer_show_video_screen_saver(void);
	void show_video_screen_saver(void);

	/*
	功能：显示文字在电视上
	参数：
		text：要显示的文字
		scroll_mode：滚动模式
		scroll_count：滚动次数

	返回值：
		true：成功
		false：失败
	*/
	bool play_osd_text(TCHAR *text,enum OSD_PLAY_MODE scroll_mode,int scroll_count);

	/*
	功能：显示或退出视频屏保
	参数：
		void
	返回值：
		void
	*/
	void show_quit_video_screen_saver(void);

	/*
	功能：返回点歌界面
	参数：
		void
	返回值：
		void
	*/
	void return_select_song_window(void);

	/*
	功能：隐藏所有窗口
	参数：
	   void
   返回值：
	  void
	*/
	void hide_sub_window(void);

	/*
	功能：视频播放窗口在屏切窗口上显示
	参数：
		void
	返回值：
		void
	*/
	void switch_screen_show_video_window(void);

	/*
	功能：预览视频窗口显示
	*/
	void preview_screen_show_video_window(void);

	/*
	功能：显示上下首歌曲名字的滚动字幕
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool show_song_name(void);

	/*
	功能：开房
	参数：
		void
	返回值：
		void
	*/
	void ktv_open_room(void);

	/*
	功能：保存当前已选歌曲的编号
	参数：
		path：要保存的服务器路径
	返回值：
		void
	*/
	void save_select_song_number(TCHAR *path);

	/*
	功能：得到选中歌曲ID
	参数：
		song_ID：歌曲编号
	返回值：
		true：成功
		false：失败
	*/
	bool get_select_song_number(TCHAR *song_ID);

	/*
	功能：换房时，得到选择的歌曲，并录入到已选中
	参数：
		path：服务器路径
	返回值：
		true:得到歌曲
		false:没有
	*/
	bool get_select_song_from_server(TCHAR *path);

	/*
	功能：同步选择歌曲
	参数：
		clear_song：清空已选
		song_ID：歌曲编号
	返回值：
		true：成功
		false：失败
	*/
	bool syn_select_song(bool clear_song,TCHAR *song_ID);

	/*
	功能：发送测机信息，给测机界面
	参数：
		void
	返回值：
		void
	*/
	void send_test_song_info(void);

	/*
	功能：自动测试函数
	参数：
		void
	返回值：
		void
	*/
	void auto_test_software(void);

	/*
	功能：播放环境音
	参数：
		audio_number：环境音的编号
		show_logo：显示控制logo
	返回值：
		true：成功
		false：失败
	*/
	bool play_environment_audio(int audio_number,bool show_logo=true);

	/*
	功能：改变灯光
	参数：
		light_number：灯光编码
		recv_msg：接受的消息
	返回值;
		void
	*/
	void change_room_light(int light_number,bool recv_msg);

	/*
	改变静音或暂停时的灯光状态
	nState:0(取消静音或暂停状态)
			1(静音状态)
			2（暂停状态）
	*/
	void change_light_state(int nState);
	/*
	功能：改变空调和排风
	参数：
		air_condition：空调档位或排风
	返回值：
		void
	*/
	void change_air_condition_function(int air_condition);

	/*
	功能：播放气氛音频
	参数：
		wave_type：音频类型
	返回值：
		void
	*/
	void play_atmosphere_audio(int wave_type);

	/*
	功能：停止wav音频
	参数：
	   void
	返回值：
		void
	*/
	void stop_environment_audio(void);

	/*
	功能：根据条件查询数据库歌星表，并显示到flash界面上
	参数:
		void
	返回值：
		true:成功
		false：失败
	*/
	bool singer_query_show_data(void);

	/*
	功能：解析flash发送过来的坐标字符串
	参数：
		Coordinate：坐标
		x_position：x位置
		y_position：y位置
		width:宽度
		height：高度
	返回值：
		true：成功
		false：失败
	*/
	bool parse_coordinate_string(const TCHAR *coordinate,int &x,int &y,int &width,int &height);

	/*
	功能：清空手写显示的字
	参数：
		void
	返回值：
		void
	*/
	void clear_handwriting_recognizer_word(void);

	/*
	功能：清空手写选择的字
	参数：
		void
	返回值
		void
	*/
	void clear_handwriting_select_word(void);
	
	/*
	功能：查询手写的联想字
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool query_handwriting_association_word(void);

	/*
	功能：得到手写联想可以显示的字
	参数：
		result_string：结果字符串
		array_size：数组大小
		query_word：查询条件中的字
	返回值：
		true：成功
		false：失败
	*/
	bool get_handwriting_assocition_word(std::wstring result_string[],int array_size,const TCHAR *query_word);

	/*
	功能：显示手写的联想字
	参数：
		page_operate：页操作
	返回值：
		void
	*/
	void show_association_word(int page_operate);

	/*
	功能：清空所有条件
	参数：
		void
	返回值：
		void
	*/
	void clear_all_query_condition(void);
	
	/*
	功能：根据页面不同，清空条件
	参数：
		void
	返回值：
		void
	*/
	void clear_query_condition_by_page(void);

	/*
	功能：初始化所有检索条件
	参数：
	   void
   返回值：
	   void
	*/
	void query_board_init(void);

	/*
		功能：弹出dj对话框
	*/
	void show_pop_up_dj_window();

	/*
	功能：根据页面不同，清空查询条件，并初始化
	参数：
		clear_list：是否清空列表 true：清空 false：不清空
	返回值：
		void
	*/
	void clear_query_condition_by_page_and_init(bool clear_list);

	/*
	功能：显示字母到窗口
	参数：
		NULL
	返回值：
		void
	*/
	void show_letter_window(const TCHAR *letter);
	void show_query_letter(const TCHAR *letter,SONG_LANGUAGE query_language);

	/*
	功能：当查询结果为空时，进行提示
	参数：
		void
	返回值：
		void
	*/
	void show_no_match_result_tip(bool back_tip=false);

	/*
	功能：发送消息到后台的线程
	参数：
		pParam：传递的参数
	返回值：
		UINT
	*/
	static UINT send_msg_to_back_server_thread(LPVOID pParam);

	/*
	功能：发送本级IP和机器名给服务器
	参数：
		void
	返回值：
		true：成功
		flase：失败
	*/
	bool send_local_ip_name_to_server(void);

	/*
	功能：发送请求开房消息给服务器
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool send_request_open_room_to_server(void);

	/*
	功能：发送消息给开关房服务器
	参数：
		msg：要发送的消息
	返回值：
		ture：成功
		false：失败
	*/
	bool send_msg_to_back_server(char *msg);

	
	/*
	功能：发送消息给设置规则系统
	参数：
		msg：要发送的消息
	返回值：
		ture：成功
		false：失败
	*/
	bool send_msg_to_set_maiba_rule(TCHAR *msg);
	static UINT send_data_to_maiba_rule_thread(LPVOID pParam);


	/*
	功能：接收后台发送过来的消息线程
	参数：
		pParam：传递的参数
	返回值：
		UINT
	*/
	static UINT recv_server_msg_udp_thread(LPVOID pParam);
	static UINT recv_server_msg_tcp_thread(LPVOID pParam);

	/*
	功能：接受后台发送的消息数据
	参数：
		void
	返回值：
		UINT
	*/
	UINT recv_server_msg_udp(void);
	UINT recv_server_msg_tcp(void);

	/*
		功能：给后台发送消息数据
		参数：
			void
		返回值：
			void
	*/
	static UINT send_server_msg_tcp_thread(LPVOID pParam);
	UINT send_server_msg_tcp(TCHAR* msg);



	/*
	功能：关机预处理
	参数：
		void
	返回值：
		void
	*/
	void exit_window_pretreat(void);

	/*
	功能：关机
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool shutdown_computer(void);

	/*
	功能：重新启动计算机
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool reboot_computer(void);

	/*
	功能：电视osd是否播放完成
	参数：
		void
	返回值：
		true：播放完成
		flase：没有播放完成
	*/
	bool tv_osd_play_finish(void);

	/*
	功能：显示图片屏保
	参数：
		path：屏保图片路径
	返回值：
		true：成功
		false：失败
	*/
	bool show_picture_screen_save(TCHAR *path);

	/*
	功能：退出屏保
	参数：
		void
	返回值：
		void
	*/
	void quit_screen_save(void);

	/*
	功能：密码功能判断
	参数：
		args：密码
	返回值：
		void
	*/
	void password_function_judgement(const TCHAR *args);

	/*
		功能:生成ipad密码
	*/
	void Generate_function_encode();

	/*
	功能:发送二维码给flash
	*/
	void flash_message_call_encode(const TCHAR *args);

	/*
		功能：发送微信点歌二维码
	*/
	void flash_message_call_wechat();


	/*
	功能：生成二维码图片
	参数：
	strData:生成的文字
	strPath:生成图片存储的路径
	返回值：
	true:成功
	false:失败
	*/
	bool Generate_encode_picture(LPCSTR strData,CString strPath);

	/*
	功能：会员注册
	参数：
		name：会员名字
		password：会员密码
	返回值：
		true：成功
		false：失败
	*/
	bool member_register(const TCHAR *name,const TCHAR *password);

	/*
	功能：会员登录
	参数：
		name：会员名字
		password：会员密码
	返回值：
		-1:用户名不存在
		0：密码错误
		1：登录成功
	*/
	int member_login(const TCHAR *name,const TCHAR *password);

	/*
	功能：显示会员登录的错误提示
	参数：
	   error_code：错误码
   返回值：
	   void
	*/
	void member_show_error_tip(int error_code);

	/*
	功能：显示会员登录的错误提示
	参数：
	   error_msg：错误信息
   返回值：
	   void
	*/
	void member_show_error_tip(TCHAR* error_msg);

	/*
	功能：删除录音歌曲提示
	参数：
	   error_msg：错误信息
   返回值：
	   void
	*/
	void record_delete_show_error_tip(int error_code, int laste_error_code, TCHAR *song_name = L"");

	/*
	功能：提示
	参数：
	   error_msg：错误信息
   返回值：
	   void
	*/
	void show_error_tip(int error_code, TCHAR *fun);

	/*
	功能：修改密码
	参数：
	   name：用户名
	   old_password：旧密码
	   new_password：新密码
   返回值：
	   true：成功
	   false：失败
	*/
	bool member_change_password(const TCHAR *name,const TCHAR *old_password,const TCHAR *new_password);

	/*
	功能：使用智能拼音功能
	参数：
		void
	返回值：
		void
	*/
	void use_smart_pinyin(void);

	/*
	功能：得到智能拼音可以显示的字符
	参数：
		result_string：结果字符串
		array_size：数组大小
		query_letter：查询条件中的字符
		select_letter：可以选择的字符
		select_letter_count：可以选择的字符个数
	返回值：
		true：成功
		false：失败
	*/
	bool get_show_letter(std::wstring result_string[],int array_size,const TCHAR *query_letter,TCHAR select_letter[],int &select_letter_count);

	/*
	功能：智能拼音中，屏蔽不能查询的字符
	参数：
		select_letter：可以选择的字符
		select_letter_count：可以选择的字符个数
	返回值：
		true：成功
		false：失败
	*/
	bool flash_yinpin_hide_letter(TCHAR *select_letter,int select_letter_count);
	//显示所有字母
	bool flash_yinpin_show_all_letter(void);

	/*
	功能：播放点歌端的图片广告
	参数：
		void
	返回值
		void
	*/
	void play_pc_AD_picture(void);

	/*
	功能：播放墙面板图片广告
	参数：
		void
	返回值
		void
	*/
	void play_wall_panel_AD_picture(void);

	/*
	功能：设置播放进度条的位置
	参数：
		void
	返回值：
		void
	*/
	void set_play_progress_bar_pos(void);
	//预览歌曲
	void set_preview_song_play_progress(void);

	/*
	功能：显示帮助信息
	参数：
		void
	返回值：
		void
	*/
	void show_help_info(void);

	/*
	功能：歌曲上下翻页操作
	参数：
		table_select_expr：歌曲选择表达式
		page_operate：页操作
		operate_type：操作类型  上下页还是划屏  说明：左划屏：1 右划屏：2   点上页按钮：3  点下页按钮：4  第一页或当前页：0
	返回值：
		true：成功
		false：失败
	*/
	bool song_pre_next_page_change(select_expr &table_select_expr, int page_operate,int operate_type);
	bool movie_pre_next_page_change(int page_operate,int operate_type);
	bool member_song_pre_next_page_change(int page_operate,int operate_type);
	bool song_recorder_pre_next_page_change(int page_operate,int operate_type);
	
	/*
	功能：歌星上下翻页操作
	参数：
		page_operate：页操作
		operate_type：操作类型  上下页还是划屏  说明：左划屏：1 右划屏：2   点上页按钮：3  点下页按钮：4  第一页或当前页：0
	返回值：
		true：成功
		false：失败
	*/
	bool singer_pre_next_page_change(int page_operate,int operate_type);

	/*
	功能：电影插入到已选列表
	参数：
	返回值：
		true：成功
		false：失败
	*/
	bool flash_message_call_select_film();

	/*
	功能：根据目前所处的状态，决定选择的歌曲是直接播放还是插入到播放列表
	参数：
		song_information：歌曲信息类
		priority：是否优先
		page_index:当前页面
		recv_msg：接受的消息
	返回值：
		true：成功
		false：失败
	*/
	bool play_or_insert_select_list(song_info &song_information,bool priority,bool recv_msg=false);


	/*
	功能：改变选中歌曲的颜色
	参数：
		song_information：歌曲信息
		number：选中的编号
		priority:是否优先
	返回值：
		void
	*/
	void chang_select_song_color(song_info &song_information,int number,bool priority);

	/*
	功能：发送数据到后台的服务程序，格式：Message&SONG_ID;%s$END  说明：Message&开始符号 $END结束符号，中间是主体内容
	参数：
		data：要发送的数据
	返回值：
		void
	*/
	void send_data_to_service_udp(TCHAR *data);

	/*
	功能：查找歌词
	参数：
		in_lyric_path：歌词文件路径
		in_lyric_index_path：歌词索引文件路径
		out_lyric：输出的歌词
	返回值： 
		true：成功
		false：失败
	*/
	bool decrypt_song_lyric(const TCHAR *in_lyric_path,const TCHAR *in_lyric_index_path,const TCHAR *in_song_id,TCHAR *out_lyric);

	/*
	功能：清理歌词中的双引号，并把标点符号转化成换行
	参数：
		lyric：歌词
	返回值：
		true：成功
		false：失败
	*/
	bool song_lyric_replace(TCHAR *lyric);

	/*
	功能：写串口数据
	参数：
		com_send_flag：串口码标示
		adjust_count：调整次数
	返回值：
		true：成功
		false失败
	*/
	bool write_com_data(COM_SEND_VALUE_FLAG com_send_flag, int adjust_count=0, bool auto_light = true, int light = -1);

	/*
	功能：得到图片的高度和宽度
	参数：
	   image_path：图片路径
	   width：图片的宽度
	   height：图片的高度
	返回值：
		true：成功
		false：失败
	*/
	bool get_image_resolution(TCHAR *image_path,int &width,int &height);

	/*
	功能：显示墙面板图片
	参数：
	   void
   返回值：
	  true：成功
	  false：失败
	*/
	bool show_wall_panel_image(void);

	/*
	功能：解密歌星图片
	参数：
		picture_path[in,out]:图片路径
	返回值：
		true：成功
		false：失败
	*/
	bool decrypt_star_picture(TCHAR *picture_path,bool flag);

	/*
	功能：显示歌星资料
	参数：
		star_name：歌星名字
	返回值：
		void
	*/
	void show_singer_introduction(const TCHAR *star_name);

	/*
	功能：通过选择歌曲界面或已唱歌曲页面的歌星跳转到歌星界面
	参数：
		selet_song_page：true：选择歌曲页面，false：已唱歌曲页面
		agrs:选择的歌星编号
	返回值：
		true：成功
		false：失败
	*/
	bool flash_message_call_select_sing_page_to_singer(const TCHAR *args,bool select_song_page);

	/*
	功能：显示歌星的歌曲和资料
	参数：
	   star_name：歌星名字
	   singer_sex：歌星性别
	   star_region：歌星国籍
   返回值：
	  true：成功
	  false：失败
	*/
	bool show_singer_song_introduction(TCHAR *star_name,TCHAR *star_sex,TCHAR *star_region);

	/*
	功能：通过歌星名得到歌星图片
	参数：
		singer_name：歌星名字
		singer_sex：歌星性别
		image_path：图片路径
	返回值：
		true：成功
		false：失败
	*/
	bool get_singer_image_path(const TCHAR *star_name,TCHAR *star_sex,TCHAR *star_region,TCHAR *image_path);

	/*
	功能：显示歌星的图片和资料
	参数：
		star_name：歌星名字
		singer_sex：歌星性别
		star_region：歌星国籍
	返回值：
		true：成功
		false：失败
	*/
	bool show_singer_image_introduction(const TCHAR *star_name,TCHAR *star_sex,TCHAR *star_region);

	/*
	功能：通过编号得到显卡的信息，显卡的设备名
	参数：
		device_index[in]：显卡设备索引
		display_name[out]：显卡的设备名
	返回值：
	   true：成功
	   false：失败
	*/
	bool get_display_monitor_info(int device_index,TCHAR *display_name);

	/*
	功能：更新已选歌曲数目
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool update_select_song_count(void);

	/*
	功能：进入下一页时，保存一些必要数据，用于返回
	参数：
	返回值：
		true：成功
		false:失败
	*/
	bool save_data_copy();
	
	/*
	功能：返回时，把保存的副本赋值回来
	参数：
	返回值：
		true：成功
		false：失败
	*/
	bool resume_data_copy();

	/*
	功能：优先选择的歌曲
	参数：
		args：选择的歌曲编号
		recv_msg：是否是接受到的主被控消息
	返回值：
		true：成功
		false：失败
	*/
	bool flash_message_call_priority_select_song(const TCHAR *args,bool recv_msg=false);

	/*
	功能：拖动排序已选的歌曲
	参数：
		nOrigin：选择的歌曲编号（绝对位置）
		nDestination: 目标位置（绝对位置）
		recv_msg：是否是接受到的主被控消息
	返回值：
		true：成功
		false：失败
	*/
	bool flash_message_call_drag_sort_select_song(int nOrigin, int nDestination, bool recv_msg=false);

	bool flash_message_call_random_sort_select_song();
	/*
	功能：从消息的掩码中得到改变的驱动盘符
	参数：
		mask：掩码
	返回值
		改变的盘符
	*/
	unsigned long FirstDriveFromMask (DWORD mask);

	/*
	功能：显示服务图片
	参数：
		page_operate：页操作
	返回值：
		true：成功
		false：失败
	*/
	bool show_service_image(SERVICE_PICTRUE_PAGE_OPERATE page_operate, TCHAR *interface_name = L"");

	/*
	功能：启用外挂程序
	参数：
		path;外挂程序路径
		show_flag：显示模式
		process_id：进程的id
	返回值：
		true：成功
		false：失败
	*/
	bool start_plug_in_process(const TCHAR *path,WORD show_flag,DWORD &process_id);
	bool start_plug_in_processEx(const TCHAR *path,WORD show_flag,DWORD &process_id, PROCESS_INFORMATION &process_info,
						DWORD flag = STARTF_USESHOWWINDOW, DWORD dwX = 0, DWORD dwY = 0,
						DWORD dwWidth = 0, DWORD dwHeight = 0);

	/*
	功能：判断一个进程是否在运行
	参数：
		process_name：进程的名字
		process_id：进程的id
	返回值：
		true：在运行
		false：停止运行
	*/
	bool check_process_run_state(TCHAR *process_name=NULL,DWORD process_id=-1);

	/*
	功能：终止某一个进程
	参数：
		：进程的名称
	返回值：
		true：成功
		false：失败
	*/
	bool teminate_process(TCHAR *process_name,DWORD process_id=-1);

	/*
	功能：显示U盘歌曲
	参数：
	   void
	返回值：
		void
	*/
	void show_U_disk_song(void);

	/*
	功能：U盘歌曲上下页改变
	参数：
		page_operate:页操作码
		operate_type：操作类型  上下页还是划屏  说明：左划屏：1 右划屏：2   点上页按钮：3  点下页按钮：4  第一页或当前页：0
	返回值：
		void
	*/
	void U_disk_song_pre_next_page(PAGE_OPERATE page_operate,int operate_type);

	/*
	功能：根据条件查询数据库的电影表，并显示到flash界面上
	参数：
	   void
   返回值：
	  true：成功
	  false：失败
	*/
	bool movie_query_show_data(void);
	bool movie_query_detail_data(void);
	/*
	功能：播放选择的flash游戏
	参数：
		args：选择的编号
	返回值：
		void
	*/
	void play_select_game(const TCHAR *args);

	/*
	功能：PC上切换视频
	参数：
		args:选择的视频类型
		time_protect:时间保护
	返回值：
		void
	*/
	void flash_message_call_switch_screen_pc(const TCHAR *args,bool time_protect);

	/*
	功能：视频同步到电视
	参数：
		args:选择的编号
	返回值：
	   void
	*/
	void video_synchro_to_TV(const TCHAR *args);

	/*
	功能：显示歌曲数及其页数
	参数：
	   row：歌曲数
	   page_count：总的页数
	   cur_page_number：当前页数
   返回值：
	   void
	*/
	void show_row_and_page_count(TCHAR *refresh_page,int row,int page_count,int cur_page_number);

	/*
	功能：显示其它意见
	参数：
		data：意见
	返回值：
		void
	*/
	void flash_show_others_opinion(const TCHAR *data,bool focus);

	/*
	功能：显示联系电话
	参数：
	   data：电话
   返回值：
	   void
	*/
	void flash_show_contact_phone(const TCHAR *data,bool focus);

	void flash_show_custom_phone(const TCHAR *data,bool focus);

	/*
	功能：清空调查结果
	参数：
		void
	返回值：
		void
	*/
	void flash_clear_surver_result(void);

	/*
	功能：电子调查页面清空
	参数：
	   void
   返回值：
	  void
	*/
	void page_proposal_clear(void);

	/*
		功能: 定制歌曲页面清空
		参数：
		   void
		返回值：
		   void
	*/
	void page_custom_clear(void);

	/*
		功能：显示定制歌曲名称
		参数:  
		返回值:
			void
	*/
	void flash_show_custom_song(const TCHAR* data,int song_nmuber,bool focus);

	/*
	功能：会员管理
	参数：
		args：管理标示
	返回值;
	   void
	*/
	void flash_message_call_member_manager(const TCHAR *args);

 

	/*
	功能：显示会员管理输入的文本
	参数：
		textbox_number：输入框的编号
		text：输入的文本
	返回值：
		void
	*/
	void show_member_manager_input_text(int textbox_number,TCHAR *text);

	/*
	功能：改变会员管理页面的会员操作
	参数：
		state：状态 状态说明：1：登录 2：注册 3：修改密码 4:会员注册手机号
	返回值：
		void
	*/
	void change_member_manage_state(int state);

	/*
	功能：清空会员管理页面输入的信息
	参数：
	    void
	返回值：
	    void
	*/
	void clear_member_manage_input_text(void);

	/*
		功能：注册时是否进行跳转
	*/
	void member_register_dialog_page_jump(TCHAR* command,TCHAR* tip_message, bool jump_state);

	/*
	功能：显示密码框的内容
	参数：
		text：要显示的密码
	返回值：
		true：成功
		false：失败
	*/
	bool show_system_manage_code(const TCHAR *text);

	/*
	功能：显示密码框
	参数：
		void
	返回值：
		void
	*/
	void show_password_window(void);

	/*
	功能：发布画图板图片到电视上
	参数：
		x：坐标
		y：坐标
		width：宽度
		heigth：高度
	返回值：
		true：成功
		false：失败
	*/
	bool show_drawing_image_to_tv(void);
	bool show_image_to_tv(TCHAR *path);

	/*
	功能：得到某格式图片的编码
	参数：
	   format：图片格式
	   pClisid：对应图片格式的编码
   返回值：
	   true：成功
	   false：失败
	*/
	bool GetEncoderClsid(LPCWSTR format,  CLSID*  pClsid);

	/*
	功能：在电视中间显示图片
	参数：
		path：图片路径
		alignment_mode：图片对齐方式
		show_time：显示时间
		lyric_link：歌词连接标示
		song_tip：下一首提示
	返回值：
		void
	*/
	void show_picture_on_tv(TCHAR* path,OSDAlignment alignment_mode,int show_time,bool lyric_link,bool song_tip);

	void show_recorder_picture_on_tv();

	/*
	功能：删除选择的歌曲
	参数：
	   song_number：选择的要删除歌曲的编号
	   recv_msg：接收到的主被控消息
   返回值：
	   true：成功
	   false：失败
	*/
	bool flash_message_call_delete_select_song(const TCHAR *song_number,bool recv_msg=false); 
	//删除录的歌曲
	bool flash_message_call_delete_recorder_song(const TCHAR *song_number);
	//删除会员歌曲
	void flash_message_call_delete_person_song(const TCHAR *args);
	void flash_message_call_clear_person_song(void);
	void flash_message_call_delete_private_song(const TCHAR* args);

	//删除录音歌曲
	bool flash_message_call_delete_recorder_song_by_id(const TCHAR *song_number);

	
	/*
	功能：显示或取消屏显
	参数：
		show:显示：true  不显示：false
	返回值：
		void
	*/
	void screen_show_visible(bool show);

	/*
	功能：得到主被控的功能
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool get_master_slave_function(void);

	/*
	功能：主被控线程
	参数：
		pParam：传递的参数
	返回值：
		UINT
	*/
	static UINT master_slave_control_thread(LPVOID pParam);

	/*
	功能：接受主被控数据
	参数：
		void
	返回值：
		UINT
	*/
	UINT recv_master_slave_control_data(void);

	/*
	功能：通过ID得到歌曲信息
	参数：
		song_id：歌曲id
		query_song_info:歌曲信息
		video_type：歌曲类型
	返回值：
		true：成功
		false：失败
	*/
	bool get_song_info_by_id(const TCHAR *song_id,song_info &query_song_info,PLAY_SONG_TYPE video_type);
	//电影的
	bool get_movie_info_by_id(const TCHAR *song_id,song_info &query_song_info,PLAY_SONG_TYPE video_type);
	bool get_film_info_by_id(const TCHAR *song_id, song_info &query_song_info);
	//录音的
	bool get_record_song_info_by_id(const TCHAR *song_id,song_info &query_song_info,PLAY_SONG_TYPE video_type); 

	/*
	功能：告知flash显示已选还是已唱文字
	参数：
		page_code：页码
	返回值:
		void
	*/
	void inform_flash_show_select_or_sing_text(int page_code);

	/*
	功能：重值一些按钮状态，比如歌星地区，语言等
	参数：
		void
	返回值：
		void
	*/
	void set_flash_button_state(TCHAR *command,int button_number);
	/*
	功能：设置按钮高亮状态
	参数：
		init_state：是否要恢复成初始状态
	返回值：
	   void
	*/
	void set_button_highlight_state(bool init_state);

	/*
	功能：清空显示列表
	参数：
	   void
   返回值：
	   void
	*/
	void clear_show_list(void);

	/*
	功能：保存录音音频到U盘
	参数：
		 pParam：线程传递的参数
	返回值：
		void
	*/
	static UINT save_data_to_U_disk_thread(LPVOID pParam);
	void save_data_to_U_disk(void);

	/*
	功能：改变音效
	参数：
		audio_effect：选中的音效
	返回值：
		void
	*/
	void change_audio_effect(int audio_effect);

	/*
	功能：改变音乐音效
	参数：
		audio_effect：选中的音效
	返回值：
		void
	*/
	void change_music_sound(int music_sound);

	/*
	功能：显示视频窗口
	参数：
		void
	返回值：
		void
	*/
	void pc_show_video_window(void);

	/*
	功能：告知flash是否显示灯光、音效等子窗口
	参数：
		void
	返回值：
		void
	*/
	void show_control_sub_window(void);

	/*
	功能：显示复选框
	参数：
		show：显示还是隐藏 true：显示  false：隐藏
	返回值：
		void
	*/
	void show_check_window(bool show);

	/*
	功能：更改系统信息
	参数：
		args：传递过来的参数
	返回值：
		void
	*/
	void change_system_info(const TCHAR *args);

	/*
	功能：显示系统信息
	参数：
		textbox_number：输入框编号
		text：显示内容
	返回值：
		void
	*/
	void show_system_info_input_text(int textbox_number,const TCHAR *text);

	/*
	功能：显示计算机名字和IP地址
	参数：
	  void
   返回值：
	   void
	*/
	void show_local_computer_name_IP(void);

	/*
	功能：系统信息的键盘输入
	参数：
		args：选择的参数
	返回值：
		void
	*/
	void system_info_keyboard_input(const TCHAR *agrs);

	/*
	功能：通过数据库的song表得到6个服务器路径
	参数：
		void
	返回值：
		void
	*/
	void get_server_path_by_db(void);

	/*
	功能：检测网络状况
	参数：
		void
	返回值：
		void
	*/
	void check_net_status(void);

	/*
	功能：实现换肤
	参数：
		args：版本
	返回值：
		void
	*/
	void change_flash_skin(const TCHAR *args);

	/*
	功能：显示印象页
	参数：
		void
	返回值：
		void
	*/
	void show_screen_top_image(void);
	/*
	功能：打开大厅或电视视频失败之后，回到歌曲视频
	参数：
		void
	返回值：
		void
	*/
	void switch_screen_play_song_video(void);

	/*
	功能：改变歌曲显示方式
	参数：
		args：传递过来的参数
	返回值：
		void
	*/
	void change_song_show_mode(const TCHAR *args);

	/*
	功能：显示选歌动画提示
	参数：
	   void
   返回值：
	   void
	*/
	void show_select_song_animation(void);

	/*
	功能：删除前一个连接，增加新的连接
	参数：
		server_number：服务器编号
	返回值：
		void
	*/
	void change_link_server_number(int server_number);

	/*
	功能：预览下一个已选或空闲歌曲
	参数：
		void
	返回值：
		void
	*/
	void preview_next_song(void);

	/*
	功能：改变手写窗口位置
	参数：
		void
	返回值：
		void
	*/
	void move_handwriting_window_pos(void);

	/*
	功能：改变手写板颜色
	参数：
	   void
   返回值：
	   void
	*/
	void change_handwriting_window_color(void);

	/*
	功能：打开或关闭预览音频
	参数：
	   void
   返回值：
	   void
	*/
	void open_preview_audio(void);

	/*
	功能：发送正播放歌曲信息给手持设备
	参数：
		void
	返回值：
		void
	*/
	void send_playing_song_to_handheld(void);

	/*
	功能：发送已选歌曲信息给手持设备
	参数：
	   void
   返回值：
	   void
	*/
	void send_select_song_to_handheld(void);

	/*
	功能：发送已唱歌曲信息给手持设备
	参数：
	   void
   返回值：
	   void
	*/
	void send_sing_song_to_handheld(void);

	
		/*
	功能：发送录音歌曲信息给移动设备
	参数：
	   void
   返回值：
	   void
	*/
	void send_tape_song_to_pad(void);

	/*
	功能：发送查询歌曲信息给手持设备
	参数：
	   page_operate：页操作码
	   page_row_count：如果是第一页就是行数，上下页就是当前页数
   返回值：
	   void
	*/
	void send_query_song_to_handheld(int page_operate,int page_row_count);
	void send_query_singer_to_handheld(int page_operate,int page_row_count);
	void send_query_movie_to_handheld(int page_operate,int page_row_count);

	/*
	功能：组织发送给手持的一条歌曲信息
	参数：
		send_song_info：歌曲信息
		song_number：歌曲编号
		send_data：要发送的数据
	返回值：
		true：成功
		false：失败
	*/
	bool make_send_handheld_song_info(song_info &send_song_info,int song_number,TCHAR *send_data);
	bool make_send_handheld_movie_info(song_info &send_song_info,int movie_number,TCHAR *send_data);

	/*
	功能：改变语言
	参数：
	   args：参数
   返回值：
	   void
	*/
	void flash_message_call_change_language(const TCHAR *args);

	/*
	功能：改变目前使用的语言
	参数：
		void
	返回值：
		void
	*/
	void change_flash_show_language(void);

	/*
	功能：换肤初始化
	参数：
		void
	返回值：
		void
	*/
	void change_skin_init(void);

	/*
	功能：显示弹出页面
	参数：
	   args：弹出页面标示
   返回值：
	   void
	*/
	void show_pop_up_page(const TCHAR *args);

	/*
	功能：通过手持的sql语句查询数据，然后发送给手持
	参数：
		recv_data：接受的sql语句
	返回值：
		void
	*/
	void query_song_by_handheld_sql(char *recv_data);
	void query_singer_by_handheld_sql(char *recv_data);
	void query_movie_by_handheld_sql(char *recv_data);

	/*
	功能：控制操作的时间保护
	参数：
	   operate_code：操作码
	返回值：
	   true：进行保护，终止该操作
	   false：可以进行该操作
	*/
	bool protect_control_operate(int operate_code);

	/*
	功能：启动IE程序
	参数：
		void
	返回值：
	   void
	*/
	void start_IE_software(void);

	/*
	功能：播放完一首歌曲进行打分
	参数：
		mark_score：分数
	返回值：
		true：成功
		false：失败
	*/
	bool make_mark_for_singer(int mark_score);

	/*
	功能：使用视点文件方式开关房
	参数：
	   void
   返回值：
	   void
	*/
	void use_file_open_room(void);

	/*
	功能：为了使用索引，增加查询速度，所以改变查询方式
	参数：
		select_condition：查询条件
		condition_suffix：条件下标
		column_name：列的名字
		max_char：最大的字符
		spell_query：true拼音查询  false：手写查询
	返回值：
		void
	*/
	void change_query_mode(query_condition select_condition[],int condition_suffix,TCHAR *column_name,TCHAR *max_char,bool spell_query);

	/*
	功能：通过图片初始化Image类
	参数：
		void
	返回值：
		void
	*/
	void create_osd_image(void);

	/*
	功能：生成歌曲提示图片
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool save_song_tip_osd(void);
	bool save_score_tip_osd(int total_score,int average_similarity,int average_intact,int average_stability,int total_calories);
	bool save_music_enjoy_osd(const TCHAR* src_path, TCHAR* des_path);

	/*
	功能：显示歌曲提示图片
	参数：
	   void
   返回值：
	   true：成功
	   false：失败
	*/
	bool show_song_tip_osd(void);

	/*
	功能：快进快退视频
	参数：
		args：百分比
	返回值：
		void
	*/
	void set_video_play_pos(const TCHAR *args);

	/*
	功能：发送键盘码值给互动游戏
	参数：
		keybd_code：键盘码值
	返回值：
		void
	*/
	void send_keybd_code_to_game(int keybd_code);

	/*
	功能：发送检索面板图片给flash
	参数：
		void
   返回值：
	   void
	*/
	void send_query_panel_to_flash(void);

	/*
	功能：发送屏切图片给flash
	参数：
		void
	返回值：
		void
	*/
	void send_pinqie_image_to_flash(void);

	/*
	功能：发送帮助图片到flash
	参数：
		void
	返回值：
		void
	*/
	void send_big_help_image_to_flash(void);

	/*
	功能：发送国旗图片
	参数：
		void
	返回值：
		void
	*/
	void send_national_flag_to_flash(void);

	/*
	功能：发送意见调查图片
	参数：
	   void
   返回值：
	  void
	*/
	void send_opinion_image_to_flash(void);

	/*
	功能：取消呼叫服务
	参数：
		void
	返回值：
		void
	*/
	void cancel_call_service(void);

	/*
	功能：发送服务按钮状态
	参数：
		button_number：按钮标识
		button_state：按钮状态
	返回值：
	   void
	*/
	void send_service_button_state(int button_number,int button_state);

	/*
	功能：发送灯光按钮状态
	参数：
		void
	返回值：
	   void
	*/
	void send_light_button_state(void);

	/*
	功能：发送评分按钮状态
	参数：
		void
	返回值：
	   void
	*/
	void send_score_button_state(int state = 0);

	/*
	功能：发送音效按钮状态
	参数：
	   void
   返回值：
	   void
   */
	void send_audio_effect_button_state(void);

	/*
	功能：发送音效按钮状态
	参数：
	   void
   返回值：
	   void
   */
	void send_music_sound_button_state(void);

	/*
	功能：发送手写语言按钮状态
	参数：
		void
	返回值：
		void
	*/
	void send_ink_language_button_state(void);

	/*
	功能：发送环境音效按钮状态
	参数：
	   void
   返回值：
	   void
   */
	void send_environment_audio_button_state(void);

	/*
		功能：发送原伴唱按钮状态
		参数：
			void
		返回值：
			void
	*/
	void send_accompany_original_button_state(void);


	/*
	功能：读取提示信息
	参数：
		file_name：文件名
	返回值：
		void
	*/
	void read_tip_text(TCHAR *file_name);

	/*
	功能：隐藏内嵌酒水页面
	参数：
	   void
   返回值：
	  void
	*/
	void hide_plug_in_drinks(void);

	/*
	功能：得到包房信息
	参数：
		room_info：包房信息
	返回值：
		true：成功
		false：失败
	*/
	bool get_room_info(TCHAR *room_info);

	/*
	功能：门牌机显示滚动文字
	参数：
		scroll_text：滚动的文字
		scroll_count：滚动次数
	返回值：
		void
	*/
	void doorplate_show_scroll_text(TCHAR *scroll_text,int scroll_count);

	/*
	功能：发送呼叫服务状态给门牌机
	参数：
		service_state：服务状态  true：呼叫 false：取消呼叫
	返回值：
		void
	*/
	void send_service_state_to_doorplate(bool service_state);

	/*
	功能：显示屏切页面的提示信息
	参数：
	   void
   返回值：
	   void
	*/
	void show_video_page_tip_msg(void);

	/*
	功能：设置导唱按钮状态
	参数：
	   show_state：状态
   返回值：
	   void
	*/
	void set_guid_song_button_state(bool show_state);

	/*
	功能：更新排序按钮状态
	参数：
		void
	返回值：
	   void
	*/
	void update_sort_button_state(void);

		/*
	功能：设置按钮状态
	参数：
	   show_state：状态
   返回值：
	   void
	*/
	void set_button_show_state(enum BUTTON_STATE button_flag,bool show_state);

	/*
	功能：设置排序方式
	参数：
	   void
   返回值：
	  void
	*/
	void set_query_sort_mode(void);

	/*
	功能：判断软解窗口是否移动
	参数：
	   void
   返回值：
	   void
	*/
	void judge_soft_window_move(void);

	/*
	功能：发送公司logo到flash界面
	参数：
		void
	返回值：
		void
	*/
	void send_ktv_logo_to_flash(void);

	/*
	功能：发送检索页面的检索条件给flash
	参数：
	   void
   返回值：
	   void
	*/
	void send_query_condition_text_to_flash(void);

	/*
	功能：设置键盘输入类型
	参数：
	   keyboard_type：键盘类型
   返回值：
	  void
	*/
	void set_keyboard_type(int keyboard_type);
	/*
	功能：显示微博系统
	参数：
	   void
   返回值：
	   void
	*/
	void show_weibo_system(void);

	/*
	功能：调整软解窗口位置
	参数：
	   left_pos：起始X坐标
		width：窗口宽度
	返回值：
		void
	*/
	void adjust_soft_window_width(int &left_pos,int &width);

	/*
	功能：调整软解窗口位置
	参数：
	   left_pos：起始X坐标
		width：窗口宽度
		height:窗口的高度
	返回值：
		void
	*/
	void adjust_soft_window_width(int &left_pos,int &width,int &height);


	/*
	功能：得到微博图片宽度
	参数：
	   void
   返回值：
	   void
	*/
	void Get_weibo_image_width(void);

	/*
	功能：连接服务器
	*/
	bool connect_server();

	static UINT recvData_thread(LPVOID pParam);    //消息线程

	void recv_pk_server_data();   //接收服务器发来的数据

	/********************************视频交友****************************************/	
	/*
	功能：视频交友，接收服务器或者其他包房的交友消息
	*/
	bool recv_serv_or_room_msg();
	static UINT recv_video_dating_thread(LPVOID pParam);    //消息线程
	void recv_video_dating_server_data();   //接收服务器发来的数据
	void send_server_video_dating_data(video_dating_status istatus, bool init = false);	//发送视频交友的信息到服务器
	void send_vd_three_screen_data(int page_operate,int operate_type);
	/*
	功能：得到视频交友共有多少页
	*/
	int get_video_dating_page_total();
	/*
	功能：视频交友上下翻页操作
	参数：
	page_operate：页操作
	operate_type：操作类型  上下页还是划屏  说明：左划屏：1 右划屏：2   点上页按钮：3  点下页按钮：4  第一页或当前页：0
	返回值：	 
	*/
	void record_vd_current_page(int operate_type);
	/*
	功能：组织xml发给flash
	*/
	void make_video_dating_list(std::wstring &pk_list_xml);
	void connect_video_dating(TCHAR* connect_ip,TCHAR *send_msg);  //发送消息给对方ip
	void parse_client_video_dating(TCHAR* data);
	void send_video_dating_info_to_flash();
	void accept_vd_invitation(int nFlags);   //接受对方邀请/取消对方邀请 1、邀请。0，取消
	/************************************************************************/


	/*
	功能：发送pk数据给服务器
	参数：
		iFlags:发送pk会员的状态，0、注销，1、登陆
	*/
	void send_pk_data_to_server(int iFlags); 

	bool GetHostIP(char *local_ip);  //得到本机ip

	void send_pk_three_screen_data(int page_operate,int operate_type);

	/*
	功能：pk会员上下翻页操作
	参数：
	page_operate：页操作
	operate_type：操作类型  上下页还是划屏  说明：左划屏：1 右划屏：2   点上页按钮：3  点下页按钮：4  第一页或当前页：0
	返回值：
	 
	*/
	void record_pk_current_page(int operate_type);

	/*
	功能：组织xml发给flash
	*/
	void make_pk_member_list(std::wstring &pk_list_xml);

	/*
	功能：得到会员共有多少页
	*/
	int get_pk_memeber_page_total();
	 
	void parse_recv_data(TCHAR* data);  //解析服务器发过来的数据 

	void parse_recv_video_dating_data(TCHAR* data); //解析视频交友服务器发来的数据
	
	void accept_invitation(int nFlags);   //接受对方邀请/取消对方邀请 1、邀请。0，取消

	void send_date_to_invitation();   //发送邀请给对方(本机ip，)

	void connect_inviation(TCHAR* connect_ip,TCHAR *send_msg);  //发送消息给对方ip 

	void establish_video_connection(TCHAR* data);//解析对方发过来的数据

	/*
	功能：连接本机的盒子，给本机和对方pc机打流
	参数：
		local_ip:本机ip
		other_ip:对方pc机ip
		local_port:本机打流端口
		other_port:对方打流
	*/
	void send_data_to_video_box_start(TCHAR* local_ip,TCHAR* other_ip);

	/*
	功能：停止向pc打流
	*/
	void send_data_to_video_box_stop(TCHAR* boxIP);

	/*
	功能：退出时，关闭视频转播盒一些操作
	*/
	void close_video_box();

	/*
		功能：是否启用pk功能
		返回值：
		true:启用
		false：不启用
	*/
	bool get_use_pk_function();  

	/*
		功能：是否启用视频交友功能
		返回值：
		true:启用
		false：不启用
	*/
	bool get_use_video_dating_function();  

	/*
	功能：判断是否重新生成验证码
	参数：
		无
	返回值：
		true:生成
		false:不生成
	*/
	bool judge_generate_encode();


	/*
		功能：设置PK时，叠加视频OSD图片
		参数:
			无
		返回值:
			无
	*/

	void set_pk_video_osd_picture();

	/*
	功能：发送房间状态给移动点歌服务端
	参数：
		void
	返回值：
		void
	*/
	void send_room_state_to_ipad_server(void);

	/*
		功能:向微博发送歌名数据(正在播放，下一首)
		参数:
			play_song:正在播放
			next_song:下一首
		返回值:
			void
	*/
	void send_song_name_data_to_weibo(TCHAR* play_song,TCHAR* next_song);

	/*
		功能:微博程序发送广告数据
		参数:
			ad_text:广告文字
		返回值:
			void
	*/
	void send_ad_data_to_weibo(TCHAR* ad_text);

	/*
	功能：绘制文字到图片
	参数：
	   draw_handle;绘制句柄
	   x:起始位置X
	   y:起始位置Y
	   width：宽度
	   height：高度
	   font_color：字体颜色
	   font：字体
	   text：绘制的文字
	*/
	bool draw_text_to_image(Graphics &draw_handle,int x,int y,int width,int height,StringAlignment horizontal_alignment,Color font_color,Font &text_font,TCHAR *text);


	/*
	功能：绘制图片到绘制区域
	参数：
		draw_handle：绘制句柄
		x:起始位置x
		y:起始位置y
		path：图片路径
	*/
	bool draw_image_to_offscreen(Graphics &draw_handle,int x,int y,TCHAR *path);

		/*
	功能：判断是否显示墙面版
	参数：
	   void
   返回值
	   true:成功
	   false:失败
	*/
	bool show_wall_panel_interface(void);

	
	/*
	功能：合成音频
	参数：
		void
	返回值：
		UINT
	*/
	UINT mixer_audio(void);

	/*
	功能：混合音频线程
	参数：
		pParam：传递的参数
	返回值：
		UINT
	*/
	static UINT mixer_audio_thread(LPVOID pParam);

	/*
		功能：开启/关闭导唱功能
		参数：
		返回值：
			void
	*/
	void exit_enter_guid_song(bool guid_song);

	/*
	功能：发送分享二维码图片给flash
	参数：
		url：分享网址
	返回值：
		void
	*/
	void send_share_url_image_to_flash(TCHAR *url);

	
	/*
	功能：缩放图片
	参数：
		des_path：存储图片路径
		src_path：源始图片路径
		format：图片格式
	返回值：
		true：成功
		false：失败
	*/
	bool zoom_image(TCHAR *des_path,int des_width,int des_height,TCHAR *src_path,TCHAR *format,int cut_width,int cut_height);
 
		/*
	功能：传输录音歌曲数给flash
	参数：
		void
	返回值：
		void
	*/
	void send_tape_audio_count_to_flash(void);

	/*
	功能：通过滑动条改变页数
	参数：
		args:要显示的页数
	返回值：
		true：成功
		false：失败
	*/
	bool flash_message_call_change_show_page(const TCHAR *args);

	//查询数据线程
	static UINT query_data_thread(LPVOID pParam);

	
	/*
	功能：根据当前的歌星id 得到当前歌曲的相关信息
	参数
	song_id:歌曲id
	返回值

	*/
	bool recommand_song_by_song_id();


	//查询top_song 表里的前十条数据
	static UINT query_recommand_top_song_thread(LPVOID pParam);

	/*
		功能：得到排行榜前十的数据
		参数：
			query_sql:当前页面的查询条件

	*/
	bool recommand_song_by_top_song();

	/*
		功能：得到当前歌曲信息的推荐歌曲
		参数:
			issue_year:       年份
			language:         语言
			song_theme:       歌曲类型
			singer_sex:       歌星性别
			singer_region_new:歌星区域 
			song_name:        歌曲名
			singer_name:      歌星姓名
		返回值：

	*/
	bool get_recommend_song_info(const TCHAR* issue_year,const TCHAR *language,const TCHAR* song_theme,const TCHAR* singer_sex,
		const TCHAR* singer_region_new,const TCHAR *song_name,const TCHAR* singer_name,const TCHAR* song_id);

	/*
		发送推荐歌曲数据给flash界面
	*/
	bool flash_message_call_recommend_song();

	/*
		功能：通过收藏的歌曲id，查询出歌曲
		参数：
			song_id_list：歌曲编号
	*/
	bool song_query_member_data_by_id(std::wstring song_id_list);
	
	/*
		功能：发送公告函数
		参数：
			place_notice:场所的公告

	*/
	bool flash_message_call_place_notice();


	/*
		功能：解析web服务器发过来的规则
		参数：
			recv_data:数据
			rule_falgs:规则标示 1：自由pk 2：擂台pk
			nFalgs: 0，接受服务器发过来的数据  1,有数据发送给flash
		返回值：
			ture：成功
			false：失败
	*/
	bool parse_arena_rule_info(char* recv_data,int rule_falgs,int nFalgs);
	bool parse_arena_rule_info_ex(char* recv_data,int rule_falgs);


	/*
		功能：解析K歌分享、发现麦霸发过来的数据
		参数：
			recv_data:接受发过来的数据
	*/
	bool parse_maiba_song_info(char* recv_data);  //K歌分享、发现麦霸  (网络数据)


	bool parse_maiba_arena_info(char* recv_data);   //没有了
	bool parse_server_arena_song(char* recv_data, int flag);//擂台PK, 暂时没有了


	/*
		功能: 发送包房名称和排名
	*/
	void flash_message_call_room_name_ranking();
	void parse_message_call_room_ranking(char* recv_data);
	
	/*
		功能：得到微信的二维码
		参数：
			wechat_number:微信码
		返回值：
	*/
	void get_wechat_song_encode_number(char * wechat_data);

	/*
	2015-2-9 18:01:53--LTL
	功能：发送移动验证码给被控机
	参数：
	    flag: 0：麦霸  1：微信
	返回值：
	    void
	*/
	void send_mobile_code_to_slave(int flag);
	/*
		功能：根据歌曲id查询得到推荐歌曲数据线程
		参数：
		pParam：传递的参数
		返回值：
		UINT
	*/
	static UINT query_recommend_song_thread(LPVOID pParam);

	/*
		功能：给盒子发送数据库
		参数：
			pParam:线程传递参数
		返回值
			void
	*/ 
	static UINT send_data_to_box_thread(LPVOID pParam);
	void send_db_to_box(void);

	/*
		功能：向盒子请求数据
		参数：
			request_date: 数据
			nport:数据
		返回值：
			void
	*/
	static UINT send_data_to_box_tcp_thread(LPVOID pParam);
	void send_data_to_box_tcp();
	
	/*
		功能：发送数据线程
	*/
	static UINT send_order_data_thread(LPVOID pParam);
	void send_order_data_function_data(TCHAR *request_data,int nPort);

	/*
		功能：通过线程发送数据
		参数：
			request_data:数据
			nPort:端口
	*/
	void thread_send_to_box_tcp_function(const TCHAR* request_data,int nPort);

	/*
		功能：flash发送麦霸数据
		参数：
			maiba_type：麦霸的类型 
	*/
	bool flash_message_call_maiba_pk_data(PAGE_OPERATE page_operate_type);

	

	void maiba_pk_data_test();



	//组织xml数据
	bool make_recorder_arena_song_list_xml(std::wstring& song_list_xml,enum PAGE_OPERATE page_operate);


	/***************************************************
		计算一个文件的md5(2G一下文件)
	name文件路径
	md5_buff计算出来的md5的值
	****************************************************/
	int get_file_md5(char *name,char *md5_buff);

	bool show_handwrite_select_result(void);
	
	bool show_pinyin_select_result(void);

	/*
		功能：判断当前歌曲是否存在已选中,是否到当前页面可以重复点击
		参数：
			song_number:歌曲id
			page_index:当前页面
		返回值：
			true:不可重复点击,false:可以重复点击
	*/
	bool repeat_select_song(TCHAR* song_number,int page_index);

	/*
		功能：删除map中的存在歌曲
		参数：
			song_number:歌曲id
		返回值：
			void
	*/
	void delete_repeat_select_song(song_info &select_song_info);

	/*
		功能：挑战页面时改变所有map中的值
		参数：
			page_inde:当前页面
		返回值：
			void
	*/
	void change_repeat_select_song(int page_indxe);


	/*
		功能：设置当前的版本和加密狗到期时间
		参数：
			void
		返回值：
			void
	*/
	void set_system_version_date();

	/*
	功能：解析主控发送过来的录音数据，存入数据库
	参数：
		record_info：录音信息
	返回值：
		true：成功
		false：失败
	*/
	bool save_record_info_to_db(TCHAR *record_info);


		/*
		功能：解析如果是擂台歌曲信息
		参数：
			recv_date: 接受发过来的信息
		返回值:
			void
	*/
	void parse_arena_song_info(TCHAR* song_id);


	/*
		功能：发送会员数据给flash
	*/
	void flash_message_calll_memeber_info();



	/*
		功能：判断用户是否已经登录了
	*/
	bool judge_memeber_is_login();

	/*
		功能：读取酒水数据发送给flash
	*/
	bool flash_message_call_read_drinks_data();
	bool flash_message_call_drinks_data(char* data,TCHAR* drink_path);

	/*
		功能：是否解析网络数据
	*/
	bool judge_parse_request_web_data(TCHAR* webflags);

	/*
		功能：组织下载文件地址
	*/
	static UINT recv_date_from_box_tcp_thread(LPVOID pParam);
	void recv_data_from_box_tcp();

	/*
		功能：解析出头像的名称
		参数：
			down_addr:下载地址
			down_type:解析类型  1，头像  2，地址
			local_path:本地路径
	*/
	bool parse_memeber_head_picture_name(IN const TCHAR* down_addr,OUT TCHAR* local_path,IN int down_type);


	/*
		功能：清除所有的会员信息
	*/
	bool clear_all_member_show_info();


	/*
	 功能：显示单句分数和提示语
	 参数：
		 score:单句分数
	返回值：
		void
	*/
	void show_sing_score(int score);

	/*
	功能：合成评分图片部分
	参数：	nScore：总分
			nSimilarity：相似度(声准)
			nStability：稳定度(音准)
			nIntact：完整度
	返回值：
			true：成功
	*/
	bool compose_score_image(int nScore, int nSimilarity, int nStability, int nIntact, TCHAR *pImgPath);
	/*
	功能：显示单句评分（总分，相似度(声准)，稳定度(音准)，完整度）
	参数：nScore：总分
		  nSimilarity：相似度(声准)
		  nStability：稳定度(音准)
		  nIntact：完整度
	返回值：
		  true：成功
	*/
	bool show_single_score(int nScore, int nSimilarity, int nStability, int nIntact);
	/*显示评分动画flash*/
	void show_score_video_flash();
	/*发送给flash控件*/
	bool flash_message_call_score_tv(int nScore, int nSimilarity, int nStability, int nIntact);
	/*
		功能：发送数据给服务端，标示是否分享成功
		参数：
			song_number：歌曲id
	*/
	void share_success_send_to_server(TCHAR *song_number);

	/*
		功能：解析得到点播歌曲的信息(网络服务器)
	*/
	void parse_message_call_maiba_song(char* recv_data);

	void parse_message_call_arena_one_song(char* recv_data);
	

	/*
		功能：请求头像的图片
		参数：
			void
		返回值:
			void
	*/
	void request_head_picture_function();


	/*
		功能：组织会员字符串，发给被控
		参数：
			void
		返回值:
			void
	*/
	void send_master_slave_data_vip_info();


	/*
		功能：解析主控发过来的数据并进行赋值
		参数：
			recv_data：会员数据
		返回值:
			void
	*/
	void parse_master_slave_data_vip_info(TCHAR* recv_data);

	/*
		功能：发送显示会员信息
		参数：
			void
		返回值:
			void
	*/
	void flash_message_call_show_member_vip();

	/*
		功能：服务器推送歌曲
		参数：
			recv_data：接受到的数据
		返回值：
			void
	*/
	void flash_message_call_service_push_song(char* recv_data);

	void flash_message_call_service_share_success(char * recv_data);

	void start_software_on_close();

	static UINT flash_message_call_service_barrage(LPVOID pParam);


	/*
	功能：发送分享成功标示给规则服务器
	参数：
		void
	返回值：
		UINT
	*/
	UINT song_share_success(void);
	static UINT song_share_success_thread(LPVOID pParam);

	/*
		功能：多线程启动IPAD服务程
	*/
	UINT start_ipad_service(void);
	static UINT start_ipad_service_thread(LPVOID pParam);

	/*
		功能:分享得给规则服务器
	*/
	void share_song_to_rale_server(TCHAR * song_id,TCHAR* URL);


	void get_dekaron_song_url_id(const TCHAR* song_id,TCHAR* url_id);

	/*
	功能：计算评分结果
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool compute_socre_result(void);

	/*
	功能：播放评分视频
	参数：
		void
	返回值：
		true：成功
		false：失败
	*/
	bool play_score_video(void);

	/*
		功能:发送udp歌曲分数广播
		参数：
			socre:分数
			video_info:当前歌曲视频
		返回值：
			void
	*/
	void send_socre_data_to_room_udp(int socre,song_info &video_info);
	/*
		功能:返回音乐欣赏的json数据
		参数：
			video_info:当前歌曲视频
		返回值：
			void
	*/
	void song_query_show_data_json(int page_code);
	void parse_song_enjoy_json(Json::Value &info, TCHAR *path_name);
	/*
		功能:根据ID获取到要查询到的歌曲信息并发送给屌丝(xs)
		参数：
			video_info:当前歌曲视频
		返回值：
			void
	*/
	bool song_query_show_data_by_id(select_expr &table_select_expr,bool page_expr, TCHAR *args);

	

	/*
	功能：flash发送音乐欣赏数据
	参数：
		maiba_type：麦霸的类型 
	*/
	bool flash_message_call_music_enjoy_data(int page_code, bool binit = true);

	/*
		从服务器下载该歌曲
		down_type: 下载类型
	*/
	void dwon_song_file_to_server(const TCHAR* args, int down_type);

	/*
		判断当前下载歌曲在map中是否存在
	*/

	bool judge_down_song_map_by_id(TCHAR * song_id);

	/*
		得到当前的下载完毕的歌曲,修改标示
	*/
	void down_song_file_success(char *down_data);

	/*
		发送flash一个空的列表
	*/
	void send_to_flash_empty_list(bool flag = true); //true : 歌曲 false : 歌星

	/*
		功能：设置视频交友时，叠加视频OSD图片
		参数:
			无
		返回值:
			无
	*/

	void set_music_enjoy_osd_show(int flag);

	/*
		功能：设置视频交友时，显示并叠加图片
		参数:
			无
		返回值:
			无
	*/
	void set_music_enjoy_osd_by_songinfo();
	/*
	功能：显示平台音乐歌头信息osd
	参数：无
	返回值：无
	*/
	void set_music_enjoy_osd();
	/*
	功能：消除平台音乐歌头信息及歌词osd
	参数：无
	返回值：无
	*/
	void stop_music_enjoy_osd();
	/*
		功能：广西视翰的Callback函数
		参数:
			无
		返回值:
			无
	*/
	static UINT Cdecl_Callback(LPTOOL_DATA_RECORD lpTdr);

	/*
		功能：播放DLNA功能
		参数:
			无
		返回值:
			无
	*/
	void PlayDLNAFunction();

	/*
		功能：接收主被控文件
		参数:
			无
		返回值:
			无
	*/
	static UINT recv_master_slave_file(LPVOID param);

	/*
		功能：发送主被控文件
		参数:
			无
		返回值:
			无
	*/
	UINT send_master_slave_file(TCHAR *path);
	/*
		功能：初始化COM相关
		参数：无
		返回值：无
	*/
	void InitCom();
	/*
		功能：加载设备索引
		参数：无
		返回值：无
	*/
	void ReloadEqIndex(void);
	
	/*
		功能：初始化卡拉OK
		参数：无
		返回值：无
	*/
	void InitKaraoke();

	void show_tv_picture_path(int tvcount);
	/*
		功能：主控接收到的麦霸规则发送被控
		参数：send_data发送的规则信息
	*/
	int send_maiba_rule_to_master(char* send_data);
	/*
	功能：对已选择歌曲进行位置交换
	参数：
	    agrs:交换位置的两个索引，中间用冒号分开
	返回值：
	    true：成功
		false：失败
	*/
	//bool flash_message_call_select_song_switch(const TCHAR *args);

	/*yzg add*/
	/*控制flash音量*/
	bool flash_message_call_flash_volume(int nPageCode);

	/*****************显示异形flash***************************/
	vector<CTransparentWnd *> m_vecTransparentWnd;
	CTransparentWnd *m_pWnd;
	/*显示异形Flash*/
	void show_screen_flash_wnd(SCREEN_FLASH_TYPE en_screen_flash_type);

	/*播放flash*/
	bool PlayScreenFlash(CTransparentWnd * pWnd, CWnd *pParent, TCHAR *pwFlashPath, CRect rtWnd, CRect rtFlash, UINT wndId = NULL, UINT flashId = NULL);
	/*停止flash*/
	bool destroy_screen_flash_wnd();
	/*定时器*/
	void set_screen_flash_timer(int show_time);
	/******************互动场景屏***************************/
	/*互动场景屏配置发送给flash*/
	bool flash_message_call_inter_screen_config();
	/*发码给flash*/
	bool flash_message_call_show_inter_screen(int page_code);
	/*广告图片201*/
	bool flash_message_call_ad_pic();
	/*横形频谱301*/
	bool flash_message_call_horizontal_frequency();
	/*树形频谱302*/
	bool flash_message_call_vertical_frequency();
	/*歌星图片401*/
	bool flash_message_call_singer_pic();
	/*节目图片402*/
	bool flash_message_call_program_pic();
	/*已选列表501*/
	bool flash_message_call_selected_song_list();
	/*推荐列表502*/
	bool flash_message_call_recommend_song_list();
	/*活动展示601*/
	bool flash_message_call_activity();
	/*榜单602*/
	bool flash_message_call_ranking_list();
	/*获奖实时信息603*/
	bool flash_message_call_award_info();
	/*广告字幕701*/
	bool flash_message_call_ad_caption(TCHAR *caption);
	/*活动字幕702*/
	bool flash_message_call_activity_caption(TCHAR *caption);
	/*节目信息703*/
	bool flash_message_call_program_info(TCHAR *caption);
	/*组织活动信息*/
	bool organise_arena_rule_info(TCHAR* command,int rule_falgs);
	/*遍历图片*/
	bool search_pic(CString strPath, CString &strData, int &nFileCnt);
	/*单视频*/
	bool show_single_video_inter_screen(int page_code);
	/*双视频*/
	bool show_double_video_inter_screen(int page_code);
	/*单辅助视频*/
	bool show_assist_video_inter_screen(int page_code);
	/*
	功能：上下滚动条信息（横版频谱、字幕信息（歌曲、广告、活动、游戏）、场景装饰）
	参数：nMode:模式 bLeft:是否为左列表
	*/
	bool show_scroll_info(int nMode, bool bTop = true);
	/*
	功能：左右列表信息（广告图片、竖版频谱、歌星图片、节目图片、已选列表、活动、榜单）
	参数：nMode:模式 bLeft:是否为左列表
	*/
	bool show_list_info(int nMode, bool bLeft = true);
	/*
	功能：显示视频窗口（节目视频、转播视频、视频广告、互动游戏（比例为16：9））
	参数：nMode:模式 bLeft:是否为左列表
	*/
	bool show_wnd_info(int page_code, int nMode, bool bMaster = true);
	///////////////////////////////////////////////////*

	/************************************潮流榜单****************************/
	//读取榜单文件，获取歌曲信息
	static UINT read_trend_list(LPVOID param);
	//解析json数据
	bool parse_trend_list_json(Json::Value &info);
	//组织数据xml
	bool make_trend_list_xml(wstring &strTotalXml);
	//显示榜单信息
	void flash_message_call_trend_list(int page_code, const TCHAR *args);
	void flash_message_call_trend_list_data(int page_code, bool binit = true);
	////////////////////////////////////////////////////////////////////////////
	/*************************挑战大咖*******************************************/
	// 开始挑战
	bool start_challenge_star(int nIndex, const TCHAR* pSongIndex);
	// 互动场景屏开始倒计时
	bool flash_message_call_challenge_count_down(int nFlag = 0);
	// 开始播放挑战成功/失败动画 bResult:true成功
	bool flash_message_call_start_result(bool bResult);
	// 互动场景屏跳转到挑战歌曲flash页面
	bool flash_message_call_challenging();
	// 发送当前挑战歌曲信息给flash
	bool flash_message_call_current_challenge_song(TCHAR *singer_path, int nIndex);
	// 发送分数进度
	bool flash_message_call_challenging_score(int score);
	//点歌界面显示挑战大咖
	bool flash_message_call_challenge_star();
	//发送挑战大咖规则
	bool flash_message_call_challenge_star_rule();
	//发送歌曲信息
	bool flash_message_call_challenge_star_song(enum PAGE_OPERATE page_operate, bool bInit);
	bool make_challenge_star_song_sub_xml(TCHAR* pSubData, enum PAGE_OPERATE page_operate, bool bInit);
	//发送页码信息
	bool flash_message_call_challenge_star_page_info(enum PAGE_OPERATE page_operate, bool bInit);
	//////////////////////////////////////////////////////////////////////////////
	/************************百秒夺奖*************************************/
	/*将接收的关卡信息从临时容器复制到操作时的容器中*/
	bool copy_pass_info();
	/*总关卡数接口*/
	bool flash_message_call_across_pass_count();
	/*PC主页面*/
	bool flash_message_call_main_pass_pc(bool bBgMusic = true);
	/*PC端选择关卡页面*/
	bool flash_message_call_select_pass_song_pc(enum PAGE_OPERATE page_operate, bool bInit);
	/*组织3页歌曲信息的xml数据*/
	bool make_pass_song_sub_xml(TCHAR* pSubData, enum PAGE_OPERATE page_operate);
	/*下一页信息*/
	bool flash_message_call_pass_song_next_page_pc(int nIndex);
	/*开始夺奖按钮*/
	bool flash_message_call_start_pass_pc();
	/*开始倒计时和冰块增长的接口*/
	bool flash_message_call_start_countdown();
	/*电视端主页面*/
	bool flash_message_call_main_pass_tv(int nFlag = 0);
	/*下一页提示*/
	bool flash_message_call_pass_next_page_tv();
	/*电视端倒计时*/
	bool flash_message_call_pass_count_down();
	/*tv开始挑战*/
	bool flash_message_call_start_pass_tv();
	/*播放闯关歌曲*/
	bool start_pass_tv();
	/*发送给flash完整度 相似度 稳定度*/
	bool flash_message_call_sound_effect(int nIntact, int nSimilarity, int nStability);
	/*同时达到扔锤子条件时随机扔 返回值0完整度 1相似度 2稳定度*/
	int get_sound_effect_index(int nSource);
	/*挑战结果动画*/
	bool flash_message_call_across_pass_result(bool bResult);
	/*电视端退出夺奖界面，flash停止定时器*/
	bool falsh_message_call_exit_across_pass_tv();
	//////////////////////////////////////////////////////////////
	/*//////////////////////互动游戏/////////////////////////////*/
	/*生成互动游戏二维码图片*/
	bool generate_active_game_encode();
	/*解析json数据，获取玩家信息*/
	bool parse_active_game_player_info(const char *pInfo);
	/*电视端flash*/
	bool flash_message_call_active_game_tv(int nFlag = 0);
	/*声音*/
	/*玩家信息nFlag:0全部发送  1发送场景屏 2发送软解屏*/
	bool flash_message_call_player_info(int nFlag = 0);
	/*发送骰子点数信息  a,b */
	bool flash_message_call_dice_number(int nNumber1, int nNumber2);
	/*获取声音标示*/
	bool get_dice_result_sound(int nDice, TCHAR *pResult);
	/*正在摇骰子的玩家高亮*/
	bool flash_message_call_player_high_light(TCHAR* pInfo);
	/**/
	bool active_game_flash_call_function(TCHAR *request);
	/**/
	bool active_game_soft_flash_call_function(TCHAR *request);
	//////////////////////////////////////////////////////////////
	////微信互动-弹幕/////////////////
	/*生成二维码图片*/
	bool generate_wechat_barrage_encode();
	/*创建弹幕窗口*/
	void create_wechat_interaction_wnd();
	/*销毁弹幕窗口*/
	void destroy_wechat_interaction_wnd();
	/*弹幕二维码图片路径*/
	bool flash_message_call_wechat_barrage_pic_path();
	/*弹幕开启/关闭*/
	bool flash_message_call_wechat_barrage_open(bool bOpen);
	/*弹幕显示模式（nMode 0：包房 1：场所）*/
	bool flash_message_call_wechat_barrage_mode(int nMode);
	/*显示弹幕信息的线程*/
	static UINT show_wechat_barrage_info_thread(LPVOID pParam);
	UINT show_wechat_barrage_info();
	/*解析弹幕信息的线程*/
	static UINT parse_wechat_barrage_info_thread(LPVOID pParam);
	/*弹幕显示信息(内容，颜色，字号大小，速度，次数)*/
	bool flash_message_call_wechat_barrage_info(BARRAGE_INFO *pInfo);

	/////////////////
	//**************************************************微信互动
	//处理活动线程
	static UINT wechat_message_thread(LPVOID pParam);
	/////////////////////////////////////////////////////*/
	/***********微信互动-礼物（魔法表情）*********************/
	//创建窗口及flash播放控件
	void create_wechat_gift_wnd();
	//销毁窗口及flash播放控件
	void destroy_wechat_gift_wnd();
	/*显示礼物（魔法表情）信息的线程*/
	static UINT show_wechat_gift_info_thread(LPVOID pParam);
	UINT show_wechat_gift_info();
	//显示礼物（魔法表情）bFlag:是否需要加载微信用户信息
	bool flash_message_call_wechat_gift_info(WECHAT_MESSAGE *pInfo, bool bFlag = false);

	/*******************************************************/
	/********************************网络文件的支持****************************************/
	/*//下载文件函数 - 只有单线程使用
	int down(const char* url, const char* local);

	//下载文件函数 - 只有单线程使用
	int down(const TCHAR* url, const TCHAR* local);

	//get http link - 只有单线程使用
	bool getUrl(char* url);

	//post http link - 只有单线程使用
	bool postUrl(char* url);
	*/
	//zip文件的解压
	bool unzip(CString csPath, CString csDir, CString &strFileName);
	////////////////////////////////////////////////////////////////////////////

	//****************************************听音识曲
	//听音识曲初始化信息
	void flash_message_call_listen_know_song(int args);
	//听音识曲 - 发送到电视屏flash
	void listen_flash_call_function(const TCHAR *request);
	//听音识曲 - 发送到软解电视屏flash
	void listen_flash_soft_call_function(const TCHAR *request);
	//查询所有四音轨歌曲个数线程
	//查询数据线程
	static UINT query_listen_song_info_tmp_thread(LPVOID pParam);
	//查询四首歌曲
	bool query_listen_song_info_tmp();
	bool copy_listen_song_info();
	//显示听音识曲的答案
	bool show_listen_question_answer();
	//获得听音识曲的其他三个答案
	bool listen_get_question_answer(const TCHAR *song_id);

	/*
		功能：得到当前歌曲信息的推荐歌曲
		参数:
			issue_year:       年份
			language:         语言
			song_theme:       歌曲类型
			singer_sex:       歌星性别
			singer_region_new:歌星区域 
			song_name:        歌曲名
			singer_name:      歌星姓名
		返回值：

	*/
	bool liste_get_recommend_song_info(const TCHAR* issue_year,const TCHAR *language,const TCHAR* song_theme,const TCHAR* singer_sex,
		const TCHAR* singer_region_new,const TCHAR *song_name,const TCHAR* singer_name,const TCHAR* song_id);
	//创建听音识曲窗口
	bool create_listen_song();
	//销毁听音识曲窗口
	void destroy_listen_song();
	////////////////////////////////////////////////////////////////听音识曲-end*/
	
	//爱秀直播组列表
	wstring make_video_show_flash_list(const int curr_page);

	//创建浏览器
	void CreateAxBrowse(CString csUrl);
	//销毁浏览器
	void DestroyAxBrowse();
	//设置URL
	void SetAxBrowseUrl(CString csUrl);

	/********************************秀秀mv****************************************/
	//接收服务管理器发送过来的照片mv数据
	bool picture_mv_data_to_flash(const char *data);
	//照片mv的显示 type:0 2个flash type:1 主flash  type:2副flash
	void picture_mv_play_song(song_info* songinfo, int type = 0);
	//照片mv回掉函数
	static UINT lyrics_Callback(PLAYLYRICSSTATE modeObj);
	//照片mv窗口的创建 0:返回成功 1:窗口已存在
	long create_picture_mv_wnd();
	//照片mv窗口的销毁
	long destroy_picture_mv_wnd();
	//解析
	int parse_video_show_data(const TCHAR* local_path);
	/////////////////////////////////////////////////////////////////////////////////////////

	//************************************云加歌显示进度
	static UINT cloud_song_down_progress(LPVOID pParam); //显示云歌曲下载进度条
	void send_cloud_song_progress_to_flash(song_info &song_information, int progress);
	//////////////////////////////////////*/

	// -- 重要函数，因做全场景屏功能，flash采用exe，需要socket通信
	static UINT RecvFlashDataParseData(LPVOID pParam);
	static void SendFlashDataBySocket(const TCHAR* _pStr);
	static void SendFlashDataBySocket(const char* _pStr);
	//初始化exe版的flash
	void InitFlashByExe();
	//全景屏-照片推送
	void flash_message_call_active_game_scene(const TCHAR* pScene);
	//“你可能喜欢”按钮开光状态
	bool flash_message_call_might_like_button(bool bOpen);
	/*
	被控端收到主控端进入/离开活动页面，显示/遮挡被控端点歌界面
	nPageCode:当前活动页面码
	bShow:是否显示遮挡页（true：显示）
	*/
	bool ShowOrHideCoverPage(int nPageCode, bool bShow = false);
	/*
	将遮挡图片发送给flash
	bShow:是否显示遮挡页（true：显示）
	*/
	bool flash_message_call_slave_cover_image(bool bShow = true);
	/*
	向被控端发送显示/隐藏遮挡图片的消息
	bShow:是否显示遮挡页（true：显示）
	*/
	bool send_master_slave_cover_iamge_data(bool bShow, int nPageCode);

	//*********************道奇电影
	static UINT DaoqiMovieCommunicateThread(LPVOID pParam);
	static UINT DaoQiMsgControlFunc(LPVOID pParam);
	UINT DaoqiMovieCommunicate();
	void MsgControlFunction(enMovieMsgContent enMMC = MMCMSG_DEFAULT);
	long SendDaoQiSystemMsg(const LPMOVIE_MSG_CONTROL lpMMCtrl);
	/////////////////////////*/
	//关闭电视端活动页面
	void CloseActivePageOnTv();

	//爱秀直播-线程下载图片
	static UINT uVideoShowDownFileThread(LPVOID pParam);
	void VideoShowDownFile();
private:
	//原有pc端的分辨率
	//bool m_use_fixed_resolution;        //使用固定的1280*768的分辨率
	int m_first_display_src_width;      //原始的分辨率
	int m_first_display_src_height;     //原始的分辨率

	//screen分辨率和坐标
	int m_first_display_x;              //第一块显卡的起始x坐标
	int m_first_display_y;              //第一块显卡的起始y坐标
	int m_first_display_width;          //第一块显卡的宽度
	int m_first_display_height;         //第一块显卡的高度

	int m_second_display_number;        //第二块显卡的编号
	int m_sencond_display_x;            //第二块显卡的起始x坐标
	int m_sencond_display_y;            //第二块显卡的起始y坐标
	int m_sencond_display_width;        //第二块显卡的宽度
	int m_sencond_display_height;       //第二块显卡的高度
	bool m_second_display_exist;        //第二个显卡存在标示

	int m_third_display_x;              //第三块显卡的起始x坐标
	int m_third_display_y;              //第三块显卡的起始y坐标
	int m_third_display_width;          //第三块显卡的宽度
	int m_third_display_height;         //第三块显卡的高度

	int m_four_display_x;               //第四块显卡的起始x坐标
	int m_four_display_y;               //第四块显卡的起始y坐标
	int m_four_display_width;           //第四块显卡的宽度
	int m_four_display_height;          //第四块显卡的高度

	int m_five_display_x;               //第五块显卡的起始x坐标
	int m_five_display_y;               //第五块显卡的起始y坐标
	int m_five_display_width;           //第五块显卡的宽度
	int m_five_display_height;          //第五块显卡的高度

	int m_six_display_x;               //第六块显卡的起始x坐标
	int m_six_display_y;               //第六块显卡的起始y坐标
	int m_six_display_width;           //第六块显卡的宽度
	int m_six_display_height;          //第六块显卡的高度

	//图片
	Image  *m_song_tip_image;           //下一首提示信息图片
	bool m_show_song_tip_osd;           //显示歌曲提示的osd标识
	Image *m_number_image;              //数字图片

	//flash
	PC_STATE m_pc_state;                        //点歌终端目前所处的状态
	bool m_precheckout_state;                   //预结账状态
	CFlashPlayer m_flash_player;                //flash播放器
	new_flash_player m_controlbar_flash_player; //控制条flash播放器
	BOOL m_controlbar_flash_player_exist;       //子flash播放器存在
	new_flash_player m_test_flash_player;       //测机播放器
	BOOL m_test_flash_player_exist;             //测机播放器存在
	game_flash_player m_local_game_flash_player;      //游戏播放器
	BOOL m_local_game_flash_player_exist;             //游戏播放器是否存在
	CFlashManage m_flash_manage;                //flash管理类
	bool m_flash_screen_init_finish;            //flash界面初始化完成
	bool m_lock_window;                         //锁定点歌软件屏幕
	TCHAR m_image_page_path[256];               //形象页图片路径
	TCHAR m_video_bg_path[256];                 //屏切视频背景
	TCHAR m_ktv_test_number[64];                //测机的工号
	std::wstring m_ktv_test_password;           //测机器密码
	bool m_start_test;                          //开始测试标示
	int m_auto_test_number;                     //自动测试编号
	int m_page_show_row_count;                  //歌曲查询时，限制的行数
	bool m_flash_show_logo;                     //指示flash上要显示logo还是要取消logo
	bool m_use_open_room_function;              //使用密码或后台开房控制
	std::wstring m_ink_song_lyric;              //手写歌曲的歌词
	bool m_use_smart_pinyin;                    //使用智能拼音
	bool m_page_allow_back;                     //页面允许返回
	bool m_allow_play_dj;                       //是否允许播放dj
	std::wstring m_allow_play_dj_time;			//播放DJ允许的时间
	bool m_show_start_image;                    //显示形象页
	TCHAR m_cur_interface_version[256];         //当前页面版本
	std::wstring m_japanese_enlish_stroke;      //日语检索中的英语笔画
	SONG_LANGUAGE m_query_panel_language;       //检索面板的语言
	int m_singer_class_mode;                    //歌星分类方式 0：旧分类方式 1：新分类方式
	TCHAR m_select_popup_window_number[32];     //选择的弹出窗口编号
	bool m_start_lyric_link;                    //开始歌词接龙
	bool m_save_selected_song_to_server;        //保存已选歌曲到服务器
	std::wstring m_play_movie_password;         //播放电影密码
	bool m_allow_play_movie;                    //允许播放电影
	int	 m_movie_row_count;						//电影分页每页数量
	bool m_show_song_total_count;               //显示歌曲总数
	bool m_call_service_state;                  //呼叫服务状态
	int m_click_service_button_number;          //点击的服务按钮编号
	bool m_pc_allow_cancel_service;             //pc是否允许取消服务
	int  m_track_mode;                          //音轨模式

	//button state
	int m_singer_region_button_number;          //歌星区域选中的按钮编号
	int m_language_button_number;               //语言选中的按钮编号
	int m_new_theme_button_number;              //新主题选中的按钮编号
	int m_class_button_number;                  //分类选中的按钮编号
	int m_new_song_button_number;               //新歌选中的按钮编号
	int m_opera_button_number;                  //戏曲选中的按钮编号
	int m_video_button_number;                  //视频选中的按钮编号
	int m_word_count_button_number;             //字数选中的按钮编号
	int m_year_button_number;                   //年代选中的按钮编号
	int m_movie_button_number;                  //电影选中的按钮编号
	int m_song_version_button_number;           //歌曲版本选中的按钮编号
	int m_singer_sex_button_number;             //歌星性别选中的按钮编号
	int m_button_number_copy[PAGE_MAX_NUMBER][12]; //保存页面高亮按钮编号

	//old button state
	int m_old_word_count_button_number;             //上一次字数选中的按钮编号

#ifdef DON_GUAN_K_PLUS
	bool m_language_slow_dancer;
#endif // DON_GUAN_K_PLUS
	
	//song show mode
	FLASH_SONG_SHOW_MODE m_song_show_mode;      //歌曲显示方式

	//system
	char  m_send_room_name[32];                 //用于存储发送给前置机的包房编号
	char  m_send_room_ip[32];                   //多字节ip地址
	TCHAR m_room_ip[32];                        //宽字节ip地址
	TCHAR m_show_room_name[128];                //显示的包房号
	
	//player
	player_manager m_player_manager;            //播放器管理
	bool m_replay;                              //重唱
	bool m_cancel_mute;                         //取消静音
	bool m_is_playing_video_ad;                 //记录正在播放的是不是视频广告
	int m_song_count_after_close_room;          //关房之后，允许播放的歌曲数
	int m_play_song_count_after_close_room;     //关房之后，已经播放的歌曲数
	PlAY_VIDEO_TYPE pc_play_video_type;         //pc上播放的视频类型
	PlAY_VIDEO_TYPE tv_play_video_type;         //电视上播放的视频类型
	bool m_check_video_file_exist;              //每首歌曲都检测文件是否存在
	bool m_adjust_amplifier_volume;             //调节公放音量，否则调节卡的音量
	long m_pre_play_pos;                        //记录前一个播放位置
	long m_preview_pre_play_pos;                //预览歌曲的前一个播放位置 
	bool m_full_screen_show;                    //软解状态下是否全屏显示
	bool m_pip_show;                            //画中画显示和关闭的标示
	bool m_check_video_exist;                   //每首歌曲都检测文件是否存在
	bool m_play_song_before_open_room;          //开房之前，是否允许播放歌曲
	int m_link_server_number;                   //要连接的服务器编号
	int m_pre_link_server_number;               //前一个连接的服务器编号
	bool m_use_load_balance;                    //使用负载均衡
	bool m_lock_public_video_volume;            //锁定空闲歌曲音量
	int m_replay_mode;                          //0:单曲重播一次  1：单曲循环播放
	int m_sigma_card_output_mode;               //神龙卡输出方式  0:VGA  1:复合端子 2：YUV  3：RGB
	bool m_screen_show_video;                   //使用软屏切
	int m_play_song_total_time;					//上一首歌曲播放的时长

	//TV
	std::wstring m_tv_server_ip[TV_CHANNEL_COUNT]; //电视服务器IP
	int m_tv_channel[TV_CHANNEL_COUNT];            //电视的6个频道
	TCHAR m_tv_live_url[256];                   //电视正在播放的地址
	bool m_tv_topbox_mode;                      //电视转播采用机顶盒模式
	int m_tv_play_mode;							//播放模式，1.单播，2.组播
	int m_tv_show_count;                        //开启电视频道个数
	std::wstring m_tv_name[8];                  //电视频道名字
	//song play manager
	video_play_manager m_video_play_manager;    //视频播放管理
	
	//database
	DB_Query m_db_query;                        //数据库查询类
	query_song_manager m_query_song_manager;    //查询出来的歌曲管理类
	query_singer_manager m_query_singer_manager;//查询出来的歌星管理类

	//sql server 2005
	Db_sql m_sql_server_db;
	query_film_manager	m_film_manager;			//SQL Server电影数据库类
	bool m_sunshine_show_db;
	int m_nFilePraiseCnt;					//每次开房后电影好评总数

	//好声音
	Db_sql m_sql_server_voice_db;
	bool m_voice_china_db;

	TCHAR m_db_order_item[256];                 //数据库查询排行字段
	TCHAR m_song_order_item_copy[PAGE_MAX_NUMBER][256];   //歌曲的排行字段副本
	TCHAR m_server_ip[6][32];                   //服务器的IP地址
	bool m_use_obscure_query;                   //模糊查询标识 true：启用 false：不启用
	TCHAR m_max_unicode_char[2];                //unicode的最大字符

	//osd
	osd_play_manager m_osd_play_manager;        //osd的播放管理
	int m_control_osd_show_time;                //控制osd的显示时间
	int m_tv_logo_x;                            //电视上logo的x坐标
	int m_tv_logo_y;                            //电视上logo的y坐标
	bool m_tv_show_ad_logo;                     //电视上显示广告logo和停止广告logo的标示
	int  m_tv_show_dog_tip_info;                //电视上显示加密狗欢迎词
	TCHAR m_dog_tip_info[256];                  //狗的提示信息
	bool m_tv_osd_allow_cut;                    //电视上的osd是否允许切掉
	bool m_show_vertical_volumn_bar;            //显示垂直音量条

	//screensaver
	screen_saver_window m_screen_saver_window;  //屏保窗口
	bool m_screen_saver_window_exist;           //屏保窗口是否存在
	bool m_pc_show_screen_saver;                //显示屏保
	bool m_show_video_screen_saver;             //显示视频屏保
	bool m_show_screen_saver_state;             //显示屏保状态
	bool m_show_screen_saver_state_activity;	//参加活动时的屏保状态
	CTimer m_start_screen_saver_timer;          //启动屏保的时间
	CTimer m_switch_screen_saver_timer;         //屏保间隔时间
	bool m_show_ad_screen_saver;                //显示的是广告屏保
	int m_start_screen_saver_time;              //启动屏保的时间
	bool m_start_video_screen_saver;            //目前启动的是视频屏保
	bool m_screen_to_flash_timer;				//是否弹出屏保
	bool m_creen_to_flash_show;					//记录当前屏保的状态

	//com
	inherit_com m_inherit_com;                  //串口类
	inherit_com m_inherit_bak_com;              //备份的中控盒串口类
	inherit_com m_inherit_three_com;            //继承的第三个串口

	//message
	char m_send_message[1024];                  //要发送的消息
	char m_msg_server_ip[2][64];                //消息服务器的IP
	int m_msg_server_count;                     //消息服务器的个数

	//子窗口
	CChildWnd m_screen_show_window;            //显示器屏幕显示窗口，即软屏切
	bool m_screen_show_window_exist;           //指示屏幕显示窗口是否创建成功
	CChildWnd m_sub_screen_show_window;        //子显示器屏幕显示窗口
	CChildWnd m_lobby_live_window;             //大厅直播的窗口
	bool m_lobby_live_window_exist;            //大厅直播窗口是否存在
	CChildWnd m_preview_window;                //预览窗口
	bool m_preview_window_exist;               //预览窗口是否存在
	CChildWnd m_tv_window;					   //电视直播的窗口
	bool m_tv_window_exist;                    //电视直播的窗口是否存在
	CChildWnd m_soft_decode_window;            //软解窗口
	bool m_soft_decode_window_exist;           //软解窗口存在
	bool m_use_soft_active_flash;			   //是否启用软解窗口flash
	CChildWnd m_second_tv_window;              //第二个电视窗口
	bool m_second_tv_window_exist;             //第二个电视窗口是否存在
	CChildWnd m_screen_msquare_window;         //m平方的图片窗口
	bool m_screen_msquare_window_exist;        //指示图片窗口是否创建成功
	CChildWnd m_soft_decode_window_child;            //软解窗口子窗口，用于播放视频
	bool m_soft_decode_window_child_exist;           //软解窗口子窗口存在

	int m_msquare_left_top_x;                    //图片窗口的上面的x坐标
	int m_msquare_left_top_y;                    //图片窗口的上面的y坐标
	int m_msquare_right_button_x;                //图片窗口的下面的x坐标
	int m_msquare_right_button_y;                //图片窗口的下面的y坐标
	int m_msqure_width;
	int m_msquer_height;

	int m_video_left_top_x;                    //视频窗口的上面的x坐标
	int m_video_left_top_y;                    //视频窗口的上面的y坐标
	int m_video_right_button_x;                //视频窗口的下面的x坐标
	int m_video_right_button_y;                //视频窗口的下面的y坐标

	int m_switch_screen_left_top_x;            //屏切视频窗口的上面的x坐标
	int m_switch_screen_left_top_y;            //屏切视频窗口的上面的y坐标
	int m_switch_screen_right_button_x;        //屏切视频窗口的下面的x坐标
	int m_switch_screen_right_button_y;        //屏切视频窗口的下面的y坐标

	int m_handwriting_window_left_x;           //手写窗口的上面的x坐标
	int m_handwriting_window_top_y;            //手写窗口的上面的y坐标
	int m_handwriting_window_right_x;          //手写窗口右面的x坐标
	int m_handwriting_window_bottom_y;         //手写窗口下面的y坐标

	int m_vice_screen_left_top_x;                    //视频窗口的上面的x坐标
	int m_vice_screen_left_top_y;                    //视频窗口的上面的y坐标
	int m_vice_screen_right_button_x;                //视频窗口的下面的x坐标
	int m_vice_screen_right_button_y;                //视频窗口的下面的y坐标

	//墙面板
	CChildWnd m_wall_panel_window;             //墙面板窗口
	new_flash_player m_wall_panel_flash_player;//墙面板flash播放器
	BOOL m_wall_panel_flash_player_exist;      //墙面板flash播放器标示
	bool m_wall_panel_window_exist;            //墙面板窗口是否存在
	inherit_com m_wall_panel_screen_com1;      //墙面板触摸屏的串口类
	inherit_com m_wall_panel_screen_com2;      //墙面板触摸屏的串口类
	inherit_com m_wall_panel_screen_com3;      //墙面板触摸屏的串口类
	inherit_com m_wall_panel_screen_com4;      //墙面板触摸屏的串口类
	int m_wall_panel_screen_left_x;            //墙面板左上角的X坐标
	int m_wall_panel_screen_top_y;             //墙面板左上角的Y坐标
	int m_wall_panel_screen_right_x;           //墙面板右下角的X坐标
	int m_wall_panel_screen_bottom_y;          //墙面板右下角的Y坐标
	int m_wall_panel_image_width;              //墙面板图片的宽度
	int m_wall_panel_image_height;             //墙面板图片的高度
	bool m_wall_panel_image_show;              //墙面板图片显示状态
	int m_show_wall_panel_image_time;          //隐藏墙面板图片的时间，单位是秒
	WALL_PANEL_SHOW_MODE m_wall_panel_show_mode;//墙面板显示模式
	
	//预览歌曲
	bool m_preview_allow_play_song_db;         //预览允许播放歌曲库
	song_info m_preview_song_info;             //选中的预览歌曲
	int m_preview_left_top_x;                  //预览视频窗口的上面的x坐标
	int m_preview_left_top_y;                  //预览视频窗口的上面的y坐标
	int m_preview_right_bottom_x;              //预览视频窗口的下面的x坐标
	int m_preview_right_bottom_y;              //预览视频窗口的下面的y坐标

	//DLNA预览
	int m_dlna_preview_left_top_x;                  //预览视频窗口的上面的x坐标
	int m_dlna_preview_left_top_y;                  //预览视频窗口的上面的y坐标
	int m_dlna_preview_right_bottom_x;              //预览视频窗口的下面的x坐标
	int m_dlna_preview_right_bottom_y;              //预览视频窗口的下面的y坐标

	//slave_screen
	CChildWnd m_slave_parent_window;           //被控窗口的父窗体
	bool m_slave_parent_window_exist;          //被控窗口的父窗体存在
	CChildWnd m_slave_video_window;            //被控视频窗口
	bool m_slave_video_window_exist;           //被控视频窗口是否存在
	new_flash_player m_slave_window_flash_player;//被控视频窗口上的控制按钮播放器
	bool m_slave_window_flash_player_exist;    // 被控视频窗口上的控制按钮播放器是否存在
	inherit_com m_bar_touch_screen_com;        //吧台触摸屏的串口类
	int m_slave_screen_left_top_x;             //左上角的X坐标
	int m_slave_screen_left_top_y;             //左上角的Y坐标
	int m_slave_screen_right_bottom_x;         //右下角的X坐标
	int m_slave_screen_right_bottom_y;         //右下角的Y坐标

	//副屏的显示
	CChildWnd m_vice_screen_window;				//副屏窗口的父窗体
	int m_vice_screen_window_exist;			//副屏窗口的父窗体是否存在
	new_flash_player m_vice_screen_flash_player;//墙面板flash播放器
	BOOL m_vice_screen_flash_player_exist;      //墙面板flash播放器标示
	BOOL m_vice_screen_flash_show;				//副屏是否显示
	TCHAR m_szvice_screen_msg[2048];			//传给flash消息

	//test machine
	bool m_use_test_function;                  //是否启用测机功能，true：启用 false：不启用

	//light
	bool m_song_light_control;                 //是否启用每首歌曲的灯控码
	TCHAR m_select_ligth_buttom[256];          //选中的灯光按钮
	bool m_recv_no_send_light_code;            //接受的不发送灯光码
	bool m_memory_light_state;                 //记忆灯光状态
	bool m_song_light_lock;                    //是否锁定灯控码
	int m_song_light_lock_value;			   //锁定时的灯控码值

	//audio effect
	bool m_song_audio_effect;                  //是否启用每首歌曲的音效码
	int m_cur_audio_effect_value;              //当前音效值

	bool m_song_audio_effect_lock;              //是否锁定音效码
	int m_lock_audio_effect_value;               //锁定是的音效码
	int m_lock_function_code_value;                  //锁定是的音效码值

	//music sound
	//bool m_song_music_sound;                  //是否启用每首歌曲的音效码
	int m_cur_music_sound_value;              //当前音效值

	//音调
	bool m_control_change_tone;                //启用控件变调
	int m_send_volumn_amplifier_code_count;    //发送调音功放码的次数

	//environment_audio
	int m_select_environment_button_number;    //选中的环境音效按钮编号

	//原版唱高亮编号 
	int m_select_song_accompany_original;		//原版唱弹出按钮高亮

	//recorder
	CAudio m_tape_audio;                       //录音类
	bool m_is_recording;                       //录音状态
	bool m_need_record_flag;                   //默认是否开启录音标示 true:开启 false:不开启
	int m_record_type;                       //当前的录音类型 0,半自动录音  1，全自动录音
	int m_open_record_type;						   //全自动录音  0,全自动录音关闭 1.全自动录音开启
	int m_enable_record;						//是否启用录音
	int m_are_memorices;						//记忆录音 0:不记忆 1:记忆
	bool m_record_btn_state;					//录音按钮状态 true:开启 false:关闭

	song_info m_song_recorder;                 //录音歌曲信息
	unsigned int m_record_audio_number;        //录音歌曲的编号
	void* m_recorder_handle;                   //录音对象句柄
	TCHAR m_noise_path[256];                   //噪音文件路径
	std::wstring m_recorder_dir;               //录音文件保存路径
	std::wstring m_recorder_web_dir;           //录音文件保存的网络路径
	std::deque<RECORD_SONG_INFO> m_wav_info_deque;  //录音文件信息
	TCHAR m_music_wave_path[256];                   //存储伴奏文件路径
	TCHAR m_voice_wave_path[256];                   //人声文件存储路径
	//TCHAR m_tape_mp3_name[256];                     //录音mp3文件名
	int m_tape_mode;                                //录音模式  0：音效器混和伴奏   1：软件混合伴奏
	CHttp_old m_http_service;                           //http服务
	song_info m_share_audio_info;                   //分享的音频信息 

	//分享发给服务器
	std::deque<SONG_SHARE_SUCCESS>m_song_share_success;		//分享给服务器
	int m_connect_rule_server_count;             //请求规则服务器的次数，请求5次不成功，就不在请求

	//lock
	llock m_send_master_slave_lock;            //发送主被控数据的锁
	llock m_cloud_song_lock;				   //云加歌下载歌曲是否成功的锁
	llock m_barrage_lock;
	llock m_call_fun_lock;

	//timer 定时器标示
	UINT_PTR show_logo_timer_identifier;             //动画显示logo的定时器标示
	UINT_PTR show_control_osd_timer_identifier;      //显示控制osd logo的定时器标示
	UINT_PTR show_bmp_picture_timer_identifier;      //显示bmp图片的定时器标示
	UINT_PTR show_score_timer_identifier;            //显示分数定时器标示
	UINT_PTR show_flash_text_timer_identifier;       //在flash上显示滚动字幕的定时器标示
	UINT_PTR show_tv_text_timer_identifier;          //在电视上显示滚动字幕的定时器标示
	UINT_PTR show_flash_background_timer_identifier; //更换flash背景的定时器标示
	UINT_PTR show_flash_logo_timer_identifier;       //在flash上显示logo的定时器标示
	UINT_PTR show_tv_logo_timer_identifier;          //在电视上显示logo的定时器标示
	UINT_PTR show_screen_saver_timer_identifier;     //显示屏保的定时器
	UINT_PTR common_timer_identifier;                //公用定时器
	UINT_PTR check_file_timer_identifier;            //检测文件是否存在的定时器
	UINT_PTR check_mysql_timer_identifier;           //检查mysql的定时器句柄
	UINT_PTR auto_test_timer_identifier;             //自动测试定时器
	UINT_PTR hide_check_window_timer_identifier;     //隐藏歌曲复选框的定时器句柄
	UINT_PTR show_popup_window_timer_identifier;     //显示弹出窗口的定时器句柄
	UINT_PTR show_wall_panel_image_timer_identifier; //显示墙面板图片的定时器句柄
	UINT_PTR check_pk_content_timer_identifier;                       //检查pk是否连接
	UINT_PTR show_pk_accept_window_time_identifier;    //是否隐藏pk邀请对话框
	UINT_PTR record_noise_timer_identifier;          //录制噪音定时器
	UINT_PTR request_head_picture_timer_identifier;  //请求图片定时器
	UINT_PTR show_screen_to_flash_timer_identifier; 
	UINT_PTR show_music_enjoy_lyric_timer_identifier;
	UINT_PTR show_screen_timer_identifier;			 //显示屏幕flash动画
	UINT_PTR maiba_rule_timer_identifier;
	UINT_PTR maiba_song_list_timer_identifier;
	UINT_PTR m_close_room_timer_identifier;			//手动开房后自动关房的计时器
	UINT_PTR m_destroy_gift_wnd_timer_identifier;

	int m_nCloseRoomTimeSpace;//关房时间间隔（分钟为单位）

	//scroll text
	TCHAR m_dog_welcome[1024];                        //狗的欢迎词
	TCHAR m_client_welcome[1024];                     //客户的欢迎词
	TCHAR m_msg_welcome[1024];                        //消息的欢迎词
	int m_msg_welcome_scroll_count;                   //消息欢迎词的滚动次数
	FLASH_SCROLL_WELCOME_TYPE m_welcome_text_type;    //欢迎词的类型

	//master_slave_control
	int m_master_slave_control_flag;                 //0:不启用 1：主控机 2：被控机
	char m_master_control_ip[64];                    //主控机IP地址
	char m_slave_control_ip[SLAVE_COMPUTER_MAX_COUNT][64]; //被控机的IP地址

	//os
	bool m_hide_taskbar;                             //隐藏任务栏
	TCHAR m_work_path[256];                          //工作路径

	//thread
	bool m_thread_run;                               //检测线程是否在运行
	CWinThread *m_thread_handle;                     //线程句柄
	HANDLE m_assistant_thread_event_handle;          //用于线程结束的事件句柄
	HANDLE m_server_thread_event_handle;             //接受开关房的线程事件句柄
	HANDLE m_upd_msg_thread_event_handle;            //接受udp服务器消息的线程句柄
	HANDLE m_tcp_msg_thread_event_handle;            //接受tcp服务器消息的线程句柄
	HANDLE m_master_slave_event_handle;              //主被控线程句柄
	HANDLE m_box_thread_event_handle;                //盒子事件
	
	//dog
	enum DOG_TYPE m_dog_type;                        //使用的加密狗的类型
	bool m_find_dog_success;                         //检测加密狗成功

	//drinks
	bool m_open_drinks;                              //打开酒水功能
	bool m_show_drinks_state;                        //酒水软件启动状态 
	DWORD m_drinks_process_id;                       //酒水进程的id
	bool m_ktv_software_min;                         //酒水启动之后软件是否最小化  true：最小化 false：不最小化
	bool m_use_plug_in_drinks;                       //启用内嵌酒水
	new_flash_player m_drinks_flash_player;          //酒水软件播放器
	bool m_drinks_flash_player_exist;                //酒水播放器是否存在
	DWORD m_consume_process_id;                      //消费进程的id
	//特殊需求
	HWND m_drinks_window_handle;                    //酒水窗口的句柄

	//server
	std::wstring m_server_path;                      //服务器的路径
	TCHAR m_save_song_file_path[256];                //保存歌曲ID文件路径
	char m_back_server_ip[64];                       //后台服务器IP，即开关房服务器IP
	char m_service_server_ip[64];                    //后台服务程序所在的服务器IP
	std::wstring m_music_enjoy_path;				 //音乐欣赏服务器路径

	//time
	CTimer m_cut_song_timer;                         //切歌曲定时器，防止频繁操作
	CTimer m_avoid_cut_timer;                        //全局的防止频繁切换的定时器
	CTimer m_play_AD_timer;                          //播放广告的定时器
	CTimer m_wall_panel_timer;                       //墙面板图片隐藏的定时器
	CTimer m_preview_control_timer;                  //预览控制快进快退定时器
	CTimer m_load_balance_timer;                     //负载均衡定时器
	CTimer m_recv_ps2_timer;                         //接受ps2消息的定时器
	CTimer m_seek_video_timer;                       //设置视频位置定时器
	CTimer m_interative_game_timer;                  //互动游戏的定时器
	CTimer video_switch_timer;                       //屏切窗口视频切换定时器

	CTimer m_span_total_timer;						 //统计间隔时间定时器
	CTimer m_music_enjoy_lyric_timer;				// 平台音乐歌词显示定时器
	//handwriting
	handwriting m_handwriting_window;                //手写窗口
	bool m_handwriting_window_exist;                 //手写窗口是否存在
	bool m_show_handwriting_window;                  //显示手写窗口
	CString m_recognition_result[INK_RECOGNIZE_ALTERNATE_NUMS];  //手写识别的字
	TCHAR m_handwriting_association_word[HANDWRITING_ASSOCIATION_WORD_COUNT][4]; //手写联想的字
	int m_association_word_count;                   //手写联想的字数
	int m_cur_association_word_page;                //联想字显示的页码
	int m_ink_language_button_number;               //正在识别的手写语言按钮编号
	bool m_handwriting_window_show_hide;            //标示手写窗口，弹出坏境是否隐藏

	//bomb
	bomb m_shine_bomb;                              //炸弹类
	TCHAR m_make_bomb_code1[32];                    //生成的第一组炸弹验证码
	TCHAR m_make_bomb_code2[32];                    //生成的第二组炸弹验证码
	bool m_first_code_success;                      //第一组密钥成功
	bool m_stop_dog_bomb;                           //停狗炸弹
	bool m_first_stop_dog_code_success;             //第一个停狗的码成功
	TCHAR m_dog_time_active_code[128];              //狗的激活时间码

	//member
	bool m_member_already_login;                    //会员是否已经登录
	TCHAR m_member_name[128];                        //会员的名字
	TCHAR m_member_password[32];                    //会员的密码
	TCHAR m_member_old_password[32];                //会员旧密码
	TCHAR m_member_ok_password[32];                 //会员的确认密码
	TCHAR m_memeber_phone_number[32];               //会员的手机号
	TCHAR m_phone_check_code[256];                 //手机验证码
	int m_member_song_count;                        //会员歌曲数
	int m_member_input_type;                        //要输入的内容类型 密码还是用户名
	int m_member_manage_state;                      //会员管理状态  1，登录  

	int m_login_memebere_count;                     //登录会员的个数
	int m_activate_vip_button;                     //当前激活的会员
	int m_pre_activate_vip_button;                 //上一次激活会员
	memeber_song_manager m_memeber_manage[MEMBER_LOGIN_COUNT];          //会员管理 
	int m_member_sign_out_number;                  //会员退出标示
		
	//AD
	int m_play_AD_time_elapse;                      //播放广告的时间间隔
	AD_manager m_pc_AD_manager;                     //PC点歌界面广告管理类
	AD_manager m_game_AD_manager;                   //游戏界面上广告管理类
	AD_manager m_wall_panel_AD_manager;             //墙面板上广告管理类

	//选歌提示
	bool m_allow_repeat_select_song;                //允许重复选歌 
	song_info m_select_song_info;                   //选择的歌曲信息
	bool m_select_song_priority;                    //选择的歌曲是否优先
	int m_select_song_number;                       //选择的歌曲编号
	bool m_check_window_state;                      //复选窗口状态  true：显示 false：隐藏


	bool m_user_select_song;                        //标识用户已经选择过歌曲
	std::wstring m_default_song_name_color;         //默认歌曲名字的颜色
	std::wstring m_select_song_name_color;          //选中歌曲名字的颜色
	std::wstring m_playing_song_name_color;         //正播放歌曲名字的颜色

	//doorplate machine
	CDoorplateWnd m_doorplate_window;               //门牌机窗口
	bool m_doorplate_window_exist;                  //门牌机窗口是否存在
	new_flash_player m_doorplate_flash_player;      //门牌机flash播放器
	bool m_doorplate_init_success;                  //门牌机初始化成功
	inherit_com m_doorplate_com;                    //门牌机串口
	int m_doorplate_left_top_x;                     //左上角的X坐标
	int m_doorplate_left_top_y;                     //左上角的Y坐标
	int m_doorplate_right_bottom_x;                 //右下角的X坐标
	int m_doorplate_right_bottom_y;                 //右下角的Y坐标
	bool m_doorplate_show_scroll_text;              //门牌机显示滚动文字

	//device or piece of media
	bool m_have_device_insert;                     //有设备插入
	TCHAR m_logical_disk_drive;                    //插入的逻辑盘符
	U_disk_song m_play_U_disk_song;                //播放U盘歌曲

	//picture show
	show_service_picture m_show_service_picture;  //显示服务图片的类

	//game
	game_manager m_game_manager;                  //游戏管理类

	//opinion survey
	TCHAR m_surver_question[SURVER_QUESTION_COUNT][256];   //调查的问题
	int m_satisfaction_degree[SURVER_QUESTION_COUNT];      //满意度
	std::wstring m_others_opinion;                         //其他建议
	std::wstring m_contact_phone;                          //联系电话
	bool m_input_box_show_help[2];                         //输入框显示帮助状态

	//定制歌曲
	std::wstring m_custom_song[CUSTOM_SONG_COUNT]; //定制歌曲个数
	std::wstring m_custom_phone;                     //定制歌曲联系人电话
	int m_custom_input_fouce;                        //判断是那个处于激活状态

	//code
	std::wstring m_input_code;                    //客户输入的密码
	CTimer m_password_timer;                      //密码定时器
	int m_click_count;                            //点击的次数

	//painting
	int m_painting_area_left_x;                   //绘图区域的坐标
	int m_painting_area_top_y;                    
	int m_painting_area_right_x;
	int m_painting_area_bottom_y;

	//save recording audio
	bool m_is_saving_audio;                      //正在保存录音音频到U盘
	int m_select_save_song_number;               //要保存的歌曲编号

	//system info
	ADAPTER_INFO m_adapter_info;                 //适配器信息
	TCHAR m_local_computer_name[256];            //本地计算机名字
	int m_system_info_input_type;                //要输入的系统信息类型  0：计算机名  1：IP地址

	//互动游戏
	bool m_use_Interactive_game;                 //是否启用互动游戏
	CChildWnd m_game_window;                     //游戏窗口
	new_flash_player m_game_flash_player;        //游戏播放器
	bool m_game_flash_player_exist;              //游戏播放器窗口是否存在
	int m_show_game_window_number;               //显示游戏的窗口编号 0：独立窗口  1：软解窗口   2：墙面板窗口
	bool m_game_full_screen_show;                //游戏在软解中全屏显示
	TCHAR m_interactive_game_page[256];          //互动游戏的页名称
	int  m_interactive_game_idless_time;         //互动游戏允许的空闲时间

	//广告屏幕
	CChildWnd m_AD_window;                       //广告窗口
	new_flash_player m_AD_flash_player;          //广告播放器
	bool m_AD_flash_player_exist;                //广告播放器窗口是否存在

	//msg
	bool m_use_new_msg_system;                   //启用新的消息系统

	//包房文件
	TCHAR m_room_file_path[256];                 //包房文件路径
	int m_room_file_type;                        //包房文件类型

	//界面类型
	SCREEN_TYPE m_interface_type;                //界面类型 横版 竖版
	

	//audio effect adjust
	CAudioEffect  m_audio_effect_window;         //音效窗口
	BOOL m_audio_effect_window_exist;            //音效窗口是否创建成功
	DWORD m_audio_effect_progress_id;            //音效器进程ID

	//mysql
	CMySQL_DB  m_mysql_db;                      //mysql数据库类
	char m_mysql_server_path[256];              //mysql服务器路径
	bool m_mysql_open_success;                  //mysql数据库打开成功标示

	//sort
	TCHAR m_show_sort_mode[256];                //显示的排序方式，实际方式正好相反
	wstring m_show_sort_init_mode;

	//ipad
	TCHAR m_ipad_login_code[32];                //ipad的登录验证码

	//导唱
	bool m_enter_guide_song;                    //进入导唱

	//是否开启导唱的OSD  
	bool m_show_guide_osd;

	//weibo
	int m_weibo_display_number;                 //微博使用的显卡编号
	int m_weibo_show_mode;                      //微博显示方式
	int m_weibo_image_width;                    //微博图片宽度
	DWORD m_weibo_process_id;                   //微博进程ID
	
	int m_weibo_version_number;                 //微博的版本号
	int m_weibo_image_top_height;               //显示电视屏幕上面的高度


	//PK
	bool m_open_pk;                            //是否开启pk功能
	int m_pk_textbox_focus;                    //0,用户焦点; 1,是密码焦点
	bool m_pk_login_member;                    //pk会员是否登录
	bool m_brecvData_thread;                   //接收数据线程
	TCHAR m_recv_pk_data[102400];              //接收的数据   
	TCHAR m_pk_name[128];                      //会员的名字
	TCHAR m_pk_password[32];                   //会员的密码
	int m_pk_menber_sex;                       //1、男 2、女 
	int m_pk_member_total;                     //统计共有多少个会员
	int m_pk_page_num;                         //记录当前是第多少页
	TCHAR m_pk_invitationIP[256];              //发送邀请的ip地址
	int  m_pk_invitationPort;                   //发送邀请的打流端口
	TCHAR m_pk_acceptIP[256];                  //接收ip
	int   m_pk_acceptPort;                     //接收打流端口
	bool m_pk_receive_video;                  //是否接收对方视频
	int m_pk_member_witch_one;                 //记录是哪一个会员邀请我
	bool m_b_pk_connect;						 //是否建立连接 
	TCHAR m_pk_local_video_ip[256];                  //连接本机板子的ip,配置文件读出
	int m_pk_local_video_port;                //给我端口打流的端口,配置文件读出
	bool m_b_pk_invitation;                 //判断是否是邀请方
	int m_n_Syn_count;                     //计数
	TCHAR m_pk_other_boxIP[256];      //对方盒子ip
 
	PK_MEMBER_DATA m_pk_information;	//自己的pk信息
	PK_MEMBER_DATA  m_send_member_data[MAX_MENBER_NUM];  //接收服务器发过来的pk会员数据
	bool m_pk_info_show_pc;         //是否到电视上显示视频邀请PK
	TCHAR m_pk_info_tip_msg[256];   //PK在电视上显示的提升信息

	bool m_pk_show_video;           //是否显示自己的视频框
	int m_audio_volume;             //对唱的音量

	CRect m_rectPosition0;         //设置对唱视频对方位置
	CRect m_rectPosition1;         //设置对唱视频自己位置
	int   m_pk_hardware_mode;      //PK硬件连接模式

	TCHAR m_encode_picture_path[256];   //二维码图片路径
	bool  m_ipad_ecode_again;                   //是否重新生成二维码

	//modify:2012-9-4 Yangzhenglun 增加是否启用移动点歌
	bool m_use_mobile_vod;                       //是否启用移动点歌
	int m_show_tv_mobile_tip;                    //电视上显示移动的提示信息   0，什么都不显示，1.显示ipad点歌提示，2.显示微信点歌提示  3.两个提示都显示

	CSearchLyric m_lyricSrarch;         //歌词检索类

	//os
	CXWinVersion m_window_version;              //window版本

	//mark
	SCORE_SYSTEM m_use_score_system;            //使用的打分系统
	//bool m_start_init_success;                  //开启讯飞评分是否成功
	//阳光评分
	int m_score_intact;                         //评分完整度总合
	int m_score_similarity;                     //相似度
	int m_score_stability;                      //稳定度
	int m_score_decibel;                        //声音分贝数
	int m_total_calories;                       //消耗的卡路里
	int m_lyric_total_sentences;                //歌词的总句数
	int m_shine_total_score;                    //总的得分
	new_flash_player m_soft_score_flash_player;      //显示评分结果的flash播放器
	bool m_soft_load_score_flash_success;            //加载分数flash成功
	new_flash_player m_score_flash_player;
	bool m_load_score_flash_success;
	bool m_bScoreFlashFinish;					//评分flash初始化完成标准
	TCHAR m_score_song_info[256];               //评分歌曲
	TCHAR m_next_song_info[256];                //下一首歌曲
	bool m_is_scoring;                          //正在评分标识
	bool m_bScoring;							//正在评分中
	
	//参数
	TCHAR m_thread_para[256];                   //线程参数

	//歌曲推荐
	int m_recommend_song_count;                   //实际推荐的歌曲数目

	TCHAR m_recommedn_song_id[256];  //推荐歌曲id

	//麦霸PK 
	std::wstring  m_place_notice_info; //场所里的公告.
	bool m_exist_arena_song;    //是否存在擂台歌曲
	song_info m_arena_song_info;      //擂台歌曲信息

	  
	int m_maiba_pk_type;     //pk的类型，1.自由pk  2.擂台pk
	int m_maiba_pk_count;    //数据条数
	MAIBA_SONG_INFO_STU m_maiba_song_info[MAX_MAIBA_PK_COUNT];   //网络歌曲信息
	MAIBA_RULE_INFO  m_maiba_rule_arena_info[MAIBA_RULE_COUNT];  //麦霸pk规则信息
	int m_maiba_number_button;            //麦霸按钮的高亮和记录当前选择的类型
	int m_maiba_request_page;            //麦霸请求页面
	MAIBA_TYPE m_maiba_current_request_type;  //当前请求麦霸的类型
	char m_set_maiba_rule_ip[64];                       //后台服务器IP，即开关房服务器IP
	std::wstring m_maiba_rule_info_list[MAIBA_RULE_COUNT];   //存储设置麦霸pk的信息 
	bool m_request_arena_one_song;          //判断是点击挑战麦霸点播或者是分享，true:是播放歌曲，false:是分享歌曲
	TCHAR m_request_arena_song_id[256];     //判断是点击挑战麦霸点播或者是分享的歌曲id

 
	bool m_use_area_pk;                     //判断是否启用了挑战麦霸
	bool m_use_find_maiba_pk;              //判断是否启用了发现麦霸功能
	MAIBA_HEIGHT_RANKING m_maiba_song_list[MAIBA_HEIGHT_RANKING_LIST];  //麦霸高分榜数据
	int m_maiba_song_list_count;    //高分榜的数据总个数 
	int m_maiba_total_page_number;  //总共的页数
	int m_maiba_current_page_number;   //麦霸当前页数
	
	REQUEST_SONG_TYPE m_request_song_type;   //麦霸请求歌曲类型
	int m_web_song_total_count;    //总的条数
	int m_web_total_page_nmuber;   //总的页码
	int m_web_current_page_number;		//当前的页数

	bool m_set_free_pk;              //是否设置了自由pK
	bool m_set_dekaron_pk;           //是否设置了挑战麦霸
	bool m_set_ranking_plite;		 //是否设置了上榜有礼
	bool m_set_challenge_star;		 //是否设置了挑战大咖
	bool m_set_across_pass;			 //是否设置了百秒夺奖

	SOCKET m_load_song_db_socket;     //盒子socket
	sockaddr_in m_load_song_db_addr;

	TCHAR m_wechat_song_encode[256];  //微信点歌的登录码
	TCHAR m_wechat_song_path[256];   //微信点歌二维码路径
	int m_wechat_button_number;        //微信点歌高亮

	map<wstring,int>m_select_page_Map; //存储数据的map<选择歌曲id,选择时的页面>
	
	bool m_server_pop_up_window;    //点击服务是否弹出对话框
	std::wstring m_default_song_row_color; //歌曲的颜色

	bool m_recorder_exist_video_path;   //判断当前歌曲是否是网络录歌

	SOCKET m_box_send_socket;
	TCHAR m_request_data[1024];


	//第三方灯控码
	LINGHT_CONTROL m_linght_control;

	//音乐欣赏
	ST_MUSIC_ENJOY m_music_enjoy[100];
	int m_music_enjoy_count;
	TCHAR m_szMusicEnjoyBkVideo[4][MAX_PATH];	//音乐欣赏背景视频路径

	//浏览器
	CHtmlCtrl m_html_ctrl;
	BOOL m_html_ctrl_exist;
	bool m_show_html_ctrl;

	//记录删除录音文件的索引
	std::wstring m_delete_record_idx;

	std::wstring m_maiba_ranking_info;                 //擂台pk的高分榜

	std::wstring m_video_index;
	std::wstring m_pre_theme_name;

	VIDEO_DATING m_video_dating_info;						 //当前视频交友的信息
	VIDEO_DATING m_server_video_dating_data[MAX_MENBER_NUM]; //视频交友的服务器的列表
	TCHAR m_recv_video_dating_data[102400];					 //接收视频交友的数据  
	int m_video_dating_total;								 //统计共有多少个视频朋友
	int m_vd_page_num;										 //记录当前是第多少页
	int m_vd_send_idx;										 //发送邀请的索引
	VIDEO_DATING m_video_dating_accept_info;				 //接收到视频邀请的信息
	CRect m_rectPosition_myself;							 //视频交友自己的位置
	CRect m_rectPosition_otherside;							 //视频交友对方的位置
	bool m_video_dating_show;								 //是否开通视频交友功能

	bool m_show_score_in_screen;							 //是否在电视上显示评分

	//被控机空闲歌曲点歌时，不切歌-------By_v.cai_2015/02/05 15:07
	bool m_idless_song_switching;

	bool m_allow_show_cloud_song;

	//caizw add for 显示平分线标记
	int m_default_show_score_line;
	vector<wstring> m_down_song_vec;	 //存储数据的下载歌曲数据的vec

	SHOW_CUBE_SONG_VEC m_show_cube_song_vec; //阳光秀吧歌曲数组
	SHOW_CUBE_SINGER_VEC m_show_cube_singer_vec; //阳光秀吧歌星数组

	//广西视翰DLNA功能
	PluginsEx m_PluginsEx;
	TCHAR m_GxShine_dll[2][MAX_PATH];
	static Cflashktv10Wnd *pThis; 
	bool m_is_open_dlna; //是否开启DLNA功能
	int m_dlna_already_play_time;
	LPTDLNA_URL_DATA m_lpDlna_url_data;

	int m_default_auto_light; //自动灯光默认值

	int m_film_video_button_state;//发送初始时按钮高亮

	// 对欣赏音乐原伴唱切换的控制变量（mp3格式）
	IPropSet		*m_IRTCOMAPI;
	IPropSet20065	*m_IRTCOMAPI_20065;
	IPropSet20068	*m_IRTCOMAPI_20068;
	IPropSet20082	*m_IRTCOMAPI_20082;
	bool			m_bIRTCOMAPISuccess;// 初始化是否成功的标志
 	ULONG			m_ulIndex;			// 保存当前默认声卡索引

  	bool m_song_show_video_picture; //显示歌曲视频or显示图片
	bool m_vice_screen_show_flag;
	bool m_recv_active_flag;
	
  	TCHAR m_vc_show_song_or_singer[256];   //秀立方页面显示歌曲or歌星
  	bool m_voice_singer;

	CLyricManager m_lyricManager;
	double		m_dLyricLastTime;	//歌词持续时间，用于暂停时
	bool		m_bFlag;			//歌词显示位置标志（true上行，flash下行）
	bool		m_bBegin;			//歌词显示是否为刚开始

	//是否已经告诉flash显示四音轨
	bool m_first_open_four_track;
	bool m_is_open_four_track; //判断是否启用四音轨，从加密狗过来

	bool m_b_share_recv_msg;	//K歌分享，是否是收到的消息
	std::wstring m_str_slave_recorder_song_id;//被控点击K歌分享时，记录下此时歌曲ID

	bool m_bBubble;		//推荐歌曲是否产生气泡（点歌时显示，切歌时不显示气泡，只发送推荐歌曲给互动场景屏）
	bool m_bMightLike;	//可能喜欢的开关状态（true:开启）
	/*******************************潮流榜单************************/
	std::vector<CTrendListManager> m_vec_TrendListManager;
	std::wstring m_str_trend_list_path;				 //潮流榜单文件路径
	////////////////////////////////////////////////////////
	/************************互动场景屏************************/
	CInterScreenManager m_inter_screen_manager;				//管理类
	INTER_SCREEN_CAPTION	m_inter_screen_caption;			//互动场景屏字幕信息
	bool m_inter_screen_exist;								//互动场景屏是否开启
	int m_inter_screen_mode;								//互动场景屏模式
	int m_show_activity_wnd;								//互动场景屏活动窗口位置
	bool m_activity_wnd_full_screen;							//互动场景屏活动窗口是否全屏
	CChildWnd m_inter_screen_window;						//互动场景屏窗口的父窗口
	bool m_inter_screen_window_exist;						//互动场景屏窗口的父窗口是否存在
	new_flash_player m_inter_screen_flash_player;			//互动场景屏主flash播放器
	bool m_inter_screen_flash_player_exist;					//互动场景屏主flash播放器标示
	bool m_inter_screen_flash_show;							//主flash播放器是否显示
	CRect m_rt_flash_player;								//窗口位置

	bool m_inter_screen_soft_exist;							//未启用软解屏但启用场景屏时，主窗口用软解视频窗口
	CChildWnd m_master_show_window;							//互动场景屏中主视频/游戏窗口
	bool m_b_master_show_window_exist;						//
	CRect m_rt_master;										//相对场景屏窗口位置

	CChildWnd m_slave_show_window;							//互动场景屏中辅视频/游戏窗口
	bool m_b_slave_show_window_exist;						//
	CRect m_rt_slave;										//相对场景屏窗口位置

	CChildWnd m_activity_video_wnd;							//活动视频窗口(指的是播放第二电视的视频窗口)
	bool m_bactivity_video_wnd_exist;						//

	CRect m_rtRelativeActivityWnd;							//活动Flash窗口位置（相对场景屏坐标）
	CRect m_rtAbsoluteActivityWnd;							//活动Flash窗口位置（全局绝对坐标）
	CRect m_rtPassVideoWnd;									//闯关时视频位置
	CRect m_rtPassVideoWndSoft;								//软解闯关时视频位置
	/////////////////////////////////////////////////////////////////////////////////
	CRect m_rt_soft_activity;				//软解屏的Flash窗口位置（绝对坐标）
	/******************************挑战大咖*****************************/
	CTransparentWnd *m_StarTransparentWnd;			//挑战大咖透明窗口
	std::vector<CHALLENGE_STAR_IFNO>	m_vec_challenge_star_info;//挑战歌曲
	bool	m_bChallengeStarFinish;	//flash初始化完成的标志
	int		m_nFlashFinishCnt;		//完成个数
	bool	m_b_challenge_begin;	//挑战开始的标志
	bool	m_b_challenging;		//正在挑战的标志
	int		m_nChallengeIndex;		//歌曲索引
	int		m_nCurrentScore;		//当前分数
	int		m_nCurrentTotalScore;	//当前所唱总分数
	int		m_nSingCount;			//已唱句数
	int		m_nChallengeSongCount;	//挑战歌曲总个数
	int m_nChallengeSongPageCount;	//总共的页数
	int m_nCurrentChallengeSongPage;   //当前页数
	CTransparentWnd *m_StarSoftTransparentWnd;			//软解挑战大咖透明窗口
	/////////////////////////////////////////////////////////////
	/***********************百秒夺奖*********************************/
	vector<CPassManager>	m_vec_pass_tmp;	//临时存放关卡信息的容器
	vector<CPassManager>	m_vec_pass;//关卡类
// 	CTransparentWnd * m_PassTransparentWnd;//透明窗口
	new_flash_player m_AcrossPassFlashPlayer;//
	bool m_bAcrossPassFlashPlayerExist;		//互动场景屏主flash播放器标示
// 	CTransparentWnd * m_PassSoftTransparentWnd;//软解透明窗口
	new_flash_player m_AcrossPassSoftFlashPlayer;//
	bool m_bAcrossPassSoftFlashPlayerExist;		//flash播放器标示
	PASS_STATE m_pass_state[10];					//保存上次退出时的关卡状态
	bool m_bFirstLyric;							//是否唱的第一句歌词

	bool m_bAcrossPassFlashFinish;	//flash初始化完成
	bool m_bAcrossPassing;	//闯关状态(true正在闯关)
	bool m_bInPageAcrossPass;	//是否在百秒夺奖界面
	int m_nTotalPassCount;		//总关卡数
	int m_nCurPassIndex;			//当前关卡索引0-n
	int m_nCurSongIndex;			//歌曲索引
	int m_nCurPageCode;		//当前所处的活动页面

	int m_nIntactCount;		//连续达到分数的完整度次数
	int m_nSimilarityCount;		//连续达到分数的相似度次数
	int m_nStabilityCount;		//连续达到分数的稳定度次数
	int m_nContinueCount;	//达到分数的连续次数可以扔锤子
	int m_nGoalScore;		//扔锤子的目标分数
	int m_nIceInitCount;			//初始冰块数量
	int m_nIceAddSecond ;		//冰块增加的时间间隔
	/////////////////////////////////////////////////////////////////
	/*//////////////////////互动游戏/////////////////////////////*/
	bool m_bActiveGameFlashFinish;	//互动游戏flash初始化完成
	bool m_bActiveGaming;			//正在互动游戏中
	char m_szActiveGameIp[16];		//活动ip
	TCHAR m_szActiveGameUrl[256];	//二维码URL
	TCHAR m_szPicFilePath[256];	//二维码图片本地存放路径
	int m_nPlayerCount;	//当前参与游戏人数
	int	m_nPlayerIndex;		//当前投骰子索引 （0-5）
	int	m_nDiceNumber;		//当前投出骰子的值
	vector<GAME_PLAYER_INFO> m_vecGamePlayer;	//参与游戏的人员信息
	TCHAR m_szClientIp[256];					//服务器ip

	new_flash_player m_active_game_flash_player;//flash播放器
	bool m_active_game_flash_player_exist;		//flash播放器存在

	new_flash_player m_active_game_soft_flash_player;//软解flash播放器
	bool m_active_game_soft_flash_player_exist;		//软解flash播放器存在

	//////////////////////////////////////////////////////////////
	//微信互动-弹幕
	bool m_bWechatInteractionFlashFinish;		//flash 初始化完成的标志
	CTransparentWnd *m_pWechatInteractionSoftTransparentWnd;			//软解微信互动-弹幕透明窗口
	bool m_wechat_interaction_soft_flash_player_exist;		//软解flash播放器存在

	CTransparentWnd *m_pWechatInteractionTransparentWnd;			//软解微信互动-弹幕透明窗口
	bool m_wechat_interaction_flash_player_exist;		//软解flash播放器存在

	int m_nBarrageFlashFinishCnt;							//初始化完成个数

	bool m_bWechatBarrageOpen;									//弹幕是否开启
	int m_nWechatBarrageMode;									//弹幕模式（0：包房信息 1：场所信息）
	char m_szWechatBarrageIp[16];								//弹幕配置ip
	TCHAR m_szWechatBarrageUrl[256];			//二维码URL
	TCHAR m_szWechatBarragePicFilePath[256];	//二维码图片本地存放路径
	llock m_wechat_barrage_lock;
	deque<BARRAGE_INFO> m_deque_barrage_info;				//存放弹幕信息的队列
	int m_nFontSizeMin;		//字体大小
	int m_nFontSizeMax;
	////*/
	/*////////////微信互动-礼物（魔法表情）///////////*/
	bool m_bWechatGiftFlashFinish;			//flash初始化完成的标志
	CTransparentWnd *m_pWechatGiftSoftTransparentWnd;	//软解微信互动-礼物透明窗口
	new_flash_player m_WechatGiftFlashPlayer;	//软解flash播放器
	bool m_bWechatGiftFlashPlayerExist;			//软解flash播放器存在
	llock m_wechat_gift_lock;
	deque<WECHAT_MESSAGE> m_deque_wechat_message;				//存放礼物信息的队列
	bool m_bWechatGiftPrepare;				//礼物准备中（播放准备动画）
	bool m_bWechatGiftSending;				//礼物发送中（播放礼物动画或者失败动画）
	///////////////////*/
	/*照片推送*/
	int m_nPicturePlayTime;			//照片显示时长（单位：秒）
	///*/
	//视频秀场 - 在软解屏中嵌入html，直接访问www网络
	BOOL m_video_show_exist;
	vector<ST_VIDEO_SHOW*> m_st_video_show_vec;
	int m_video_show_current_page;
	int m_video_show_count_page;

	CDShineAxBrowse m_ocxShAxBrowse;
	CWnd *m_pBrowseWnd;
#ifdef VIDEO_SHOW_FULL_SCREEN
	bool m_video_show_wnd_exist;
#endif // VIDEO_SHOW_FULL_SCREEN	

	//听音识曲
	vector<wstring> m_listen_reward_vec;			//奖励数组
	vector<wstring> m_listen_song_info_vec;			//服务器歌曲列表数组
	int m_iCount_down;								//时间限制
	vector<song_info> m_vec_listen_song_info_temp;  //临时闯关歌曲
	vector<song_info> m_vec_listen_song_info;		//闯关歌曲
	llock m_listen_song_lock;
	vector<wstring> m_answer_vec;					//答案
	int m_nListenPassCount;							//关卡个数
	new_flash_player m_listen_flash_page_tv;		//电视端flash窗口
	BOOL m_listen_flash_page_tv_exist;				//听音识曲窗口存在
	int m_iCurrent_pass;							//当前第几关
	song_info m_listen_song_info[10];				//关卡播放的歌曲信息
	song_info m_listen_song_info_answer[3];			//答案的其他三个
	int m_listen_answer_index;
	wstring m_ksc_lyrics_path;
	new_flash_player m_listen_flash_page_tv_soft;		//软解电视端flash窗口
	BOOL m_listen_flash_page_tv_soft_exist;				//软解听音识曲窗口存在
	bool m_bListenSongFlashFinish;						//听音识曲flash初始化完成

	//秀秀mv
	new_flash_player m_picture_mv_wind;				//秀秀mv电视端flash窗口
	BOOL m_picture_mv_wind_exist;					//秀秀mv电视段flash窗口是否存在
	vector<ST_PICTURE_MV*> m_st_picture_mv_vec;		//当前秀秀mv歌曲的结构变量
	wstring	m_picture_mv_server_ip;					//秀秀mv服务器ip
	string	m_picture_mv_curr_guid;					//当前播放秀秀mv的guid
	CParseLyricsForKSC	m_parse_lyics_ksc;			//ksc歌词对象
	LPKaraokeKSC m_lpKaraokeKSC;					//初始化后返回的歌词对象
	new_flash_player m_picture_mv_wind_soft;			//软解秀秀mv电视端flash窗口
	BOOL m_picture_mv_wind_soft_exist;					//软解秀秀mv电视段flash窗口是否存在
	song_info m_piture_mv_songInfo;
	bool m_bPictureMvFlashFinish;					//秀秀mvflash初始化完成

	bool m_use_audio_effect;

	//机器访问服务器的序列号
	int m_server_manually_val;

	//flash 进程启动后的信息
	DWORD m_flash_process_id;
	PROCESS_INFORMATION m_flash_process_info;
	/*提高分数的比例A（A为0-100）,为0时不提升
	说明：若得到总分为S，比例为A，最后提升后的总分为T，则
	0<S && S<=50 时，T = S + S*A%;
	50<S && S<=80时，T = S + (100-S)*A%;
	80<S && S<=100时，T = S;
	*/
	int m_nScoreIncreaseRate;
	// 平台音乐相关
	CTimer m_timerMusicEnjoy;	//间隔时间的定时器
	double m_dMusicEnjoySpace;//定时器开始后的间隔时间
	int m_nMusicEnjoyWidth;		//平台音乐歌词显示的屏幕宽度
	int m_nMusicEnjoyHeight;	//平台音乐歌词显示的屏幕高度

//#ifdef DALIAN_MATSA_EK_PLUS
	/*******************************************************
	每次开房后，活动（挑战大咖、百秒夺奖、听音识曲）奖励重新计算次数
	挑战大咖：所有歌曲的奖励相同，仅能领取一次
	百秒夺奖：只在最后一关设置奖励，仅能领取一次
	听音识曲：只在最后一关设置奖励，仅能领取一次
	*********************************************************/
	bool m_bCSGetAward;			//挑战大咖(ChallengeStar)是否领取过奖励
	bool m_bAPGetAward;			//百秒夺奖(AcrossPass)是否领取过奖励
	bool m_bLSGetAward;			//听音识曲(ListenSong)是否领取过奖励
//#endif
	//add by yzg 2015-12-09
	//电视转播中，不创建秀秀mv
	bool m_bInPageVideo;
	//通讯对象
	CHTTP m_http_obj;

	//默认音轨 0:主旋伴奏 1:原版伴奏 2:原唱 3:人声倒唱
	int m_default_track;

	//*********************道奇电影
	fd_set m_DaoQiMovieFd_set;
	/////////////////////////*/

	int m_open_full_screen;
};
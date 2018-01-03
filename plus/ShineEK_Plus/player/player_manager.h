#pragma once

#include "player.h"
#include "../song/song_info.h"
#include "player_hard.h"
#include "../message.h"

#include <Mmsystem.h>

class player_manager
{
public:
	player_manager(void);
	~player_manager(void);
	/*
	功能：注册播放器控件
	参数:
	    path：安装路径
	返回值：
	   void
	*/
	void register_player_ocx(TCHAR *path);
	/*
	功能：卸载播放控件
	参数：
	    void
	返回值：
	    void
	*/
	void unregister_player_ocx(void);
	/*
	功能：创建播放器
	参数：
	    void
	返回值：
	    true：成功
		false：失败
	*/
	bool create_player(CWnd *parent_wnd);
	/*
	功能：初始化
	参数：
	    window_exist：显示窗口是否存在
		show_handle：显示窗口的句柄
	返回值：
	    true：成功
		false：失败
	*/
	bool initialize(bool window_exist,HWND show_handle,HWND parent_handle);
	void init_osd(void);

	/*
	功能：显示或关闭窗口视频
	参数：
	    show_video：显示视频。1：显示 0：关闭
	返回值：
	    void
	*/
	void show_screen_video(bool show_video);

	/*
	功能：设置软解
	参数：
	    hwnd：软解窗口句柄
	返回值：
	　　
	*/
	long set_soft_decode_function(HWND hwnd);

	/*
	功能：设置被控视频窗口的句柄
	参数：
	    hwnd：窗口句柄
	返回值：
	*/
	long set_slave_video_handle(HWND hwnd);

	/*
	功能：是否同步显示电视视频
	参数：
	    show_tv_video：显示电视视频：ture，否则：false
	返回值：
	    true：成功
		false：失败
	*/
	bool pc_show_tv_video(bool show_tv_video);

	/*
	功能：停止所有的播放并释放播放控件
	参数：
	　　void
   返回值：
       void
	*/
	void destroy_player(void);

	/*
	功能：设置视频文件
	参数：
		video_info：视频信息
		link_server：连接的服务器编号
	返回值：
		true：成功
		false：失败
	*/ 
	bool set_video_file(song_info &video_info,int &link_server,TCHAR* music_save_path,TCHAR *voice_save_path,bool is_scoring,int use_guid = 1);

	/*
	功能：设置视频文件
	参数：
		video_info：视频信息
		link_server：连接的服务器编号
	返回值：
		true：成功
		false：失败
	*/ 
	bool set_video_file(song_info &video_info,TCHAR *szVideoPath);

	/*
		功能：设置播放模式
	*/

	bool set_video_tape_mode(int tape_mode);

	/*
	功能：设置广告视频文件
	参数：
	    path：路径
	返回值：
	    true：成功
		false：失败
	*/
	bool set_ad_video_file(TCHAR *path);

	/*
	功能：播放视频文件
	参数：
	    cancel_mute：取消静音，true：取消静音，fasle：不取消
		kalaok_track：原唱
		lock_public_volume：锁定公共歌曲音量
	返回值：
	    true：成功
		false：失败
	*/
	bool play_video_file(bool cancel_mute,bool kalaok_track,bool lock_public_volume);
	/*
	功能：开始播放
	参数：
	    void
	返回值：
	    void
	*/
	void play(void);
	/*
	功能：暂停
	参数：
		void
	返回值：
		void
	*/
	void pause(void);
	/*
	功能：停止
	参数：
		void
	返回值：
		void
	*/
	void stop(void);

	/*
	功能：重唱
	参数：
	    void
	返回值：
		void
	*/
	bool replay(TCHAR* music_save_path,TCHAR *voice_save_path,bool use_guid=false);

	/*
	功能：静音
	参数：
	    void
	返回值：
	    void
	*/
	void mute(void);
	
	/*
	功能：播放或者暂停
	参数：
	    void
	返回值;
	    void
	*/
	void play_or_pause(void);
	/*
	功能：改变原伴唱
	参数：
	    void
	返回值：
	    void
	*/
	void change_channel(void);
	void change_channel(long guid_track);

	/*
	功能：解析主控机发送过来的按钮状态字符串
	参数：
	    list_xml：传过来的字符串
	返回值：
	   true：成功
	   flase：失败
	*/
	bool parse_panel_list_xml(TCHAR *list_xml);

	/*
	功能：组织flash播放按钮的状态字符串
	参数：
	   list_xml：组织好的播放面板字符串
   返回值：
       true：成功
	   false：失败
	*/
	bool make_panel_list_xml(TCHAR *list_xml);

	/*
	功能：组织音量数值信息
	参数：
	    list_xml：组织好的音量字符串
	返回值：
	    true：成功
		false：失败
	*/
	bool make_volume_list_xml(TCHAR *list_xml);

	/*
	功能：测机的控制条按钮状态
	参数：
		list_xml：组织好的播放面板字符串
	返回值：
		true：成功
		false：失败
	*/
	bool make_control_bar_list_xml(TCHAR *list_xml);

	/*
	功能：改变欣赏状态
	参数：
	    void
	返回值：
	    true：成功
		false：失败
	*/
	bool change_enjoyment_state(void);

	/*
	功能：显示文字
	参数：
	    background_color：背景
		text_info：文字信息
		play_var：播放时用到的一些变量
	返回值：
	    true：成功
	    false：失败
	*/
	bool play_text_osd(const TCHAR* background_color, const text_osd_info& text_info, const play_variable& play_var);

	/*
	功能：显示控制文字
	参数：
	    text:要显示的文字
		color：文字颜色
		x_pos：x起始坐标
		y_pos：y起始坐标
	返回值：
	    true：成功
		false：失败
	*/
	bool play_control_text_osd(TCHAR *text,long color,long x_pos,long y_pos,long lIndex = 2L);
	/**/
	bool stop_play_control_text_osd(long lIndex);
	/*
	功能：播放控制功能图片
	参数：
	    path：图片路径
		x_pos：横坐标
		y_pos：纵坐标
	返回值：
	    true：成功
		false失败
	*/
	bool play_control_osd(const TCHAR *path,int x_pos,int y_pos);

	/*
	功能：停止控制功能OSD图片的播放
	参数：
	    void
	返回值：
	    void
	*/
	void stop_control_osd(void);
	/*
	功能：播放osd logo
	参数：
	    path：log路径
		index：索引
		x_pos：横坐标
		y_pos：纵坐标
		first_logo：第一张logo图片
	返回值：
	   true：成功
	   false：失败
	*/
	bool play_logo_osd(TCHAR *path,int index,int x_pos,int y_pos,bool first_logo);

	/*
	功能：播放广告osd logo
	参数：
	    path：路径
		logo_layer：logo所处的层
	返回值：
	    true：成功
		false：失败
	*/
	bool play_ad_logo_osd(TCHAR *path,int logo_layer);

	/*
	功能：播放BMP图片
	参数：
	    path：bmp图片路径
		play_var：播放时用到的一些变量
		alignment_mode：对齐方式
	返回值：
	    true：成功
		false：失败
	*/
	bool play_bmp_osd(TCHAR *path,play_variable &play_var,OSDAlignment alignment_mode);
	bool play_score_osd(TCHAR *path,play_variable &play_var,OSDAlignment alignment_mode);

	/*
	功能：显示墙面板图片
	参数：
	   path：图片路径
   返回值：
       void
	*/
	void show_wall_panel_picture(TCHAR *path);

	/*
	功能：隐藏墙面板图片
	参数：
	    void
	返回值：
	　　void
	*/
	void hide_wall_panel_picture(void);

	/*
	功能：停止播放BMP osd
	参数：
		void
	返回值：
		void
	*/
	void stop_bmp_osd(void);
	void stop_score_osd(void);

	/*
	功能：停止播放osd logo
	参数：
	    void
	返回值：
	    void
	*/
	void stop_logo_osd(void);

	/*
	功能：停止播放广告osd logo
	参数：
		logo_layer：logo所处的层
	返回值：
		void
	*/
	void stop_ad_logo_osd(int logo_layer);


	//查询播放器的各种状态
	bool is_playing(void);

	/*
	功能：改变歌曲的音量
	参数：
	    change_flag：音量改变标示
	返回值：
	    true：成功
		false：失败
	*/
	bool change_music_volume(enum VOLUME_CHANGE_FLAG change_flag,int set_volume=50);

	/*
	功能：改变麦克风的音量
	参数：
	    change_flag：音量改变标示
		set_volume：改变的音量
	返回值：
	    目前麦克风音量的大小
	*/
	int change_microphone_volume(enum VOLUME_CHANGE_FLAG change_flag,int set_volume=50);

	/*
	功能：改变音调
	参数：
	    change_flag：音调改变标示
		tune_value：音调值
		control_change_tone：控件改变音调
	返回值：
	    目前音调大小
	*/
	int change_tune(enum TUNE_CHANGE_FLAG change_flag,int tune_value,bool control_change_tone);

	/*
	功能：改变混响
	参数：
	   change_flag：混响改变标示
   返回值：
       目前混响大小
	*/
	int change_reverberation(enum REVERBERATION_CHANGE_FLAG change_flag);

	/*
	功能：播放音频，和视频混合播放
	参数：
	    wave_path：音频路径
		loop：循环
		music_out：原音输出
	返回值：
	    true：成功
		false：失败
	*/
	bool play_wave_mixer_audio(TCHAR *wave_path,int loop,int music_out);

	/*
	功能：停止播放混合音
	参数：
	    void
	返回值：
	    void
	*/
	void stop_wave_mixer_audio(void);

	/*
	功能：改变DJ状态
	参数：
	    void
	返回值：
	    void
	*/
	void change_DJ_state(void);

	/*
	功能：得到是否要播放DJ
	参数：
	    void
	返回值：
	    true：播放DJ
		false：不播放DJ
	*/
	bool is_play_DJ(void);

	/*
	功能：得到原伴唱的状态
	参数：
	   void
   返回值：
       true：原唱
	   false：伴唱
	*/
	bool get_channel();
	long get_guid_channel();
	void set_guid_channel(long track){ guid_track = 0;}

	/*
	功能：是否是欣赏状态
	参数：
	    void
	返回值：
	    true：欣赏状态
		false：非欣赏状态
	*/
	bool is_enjoyment(void);

	/*
	功能：是否在静音
	参数：
	   void
   返回值：
       true：静音
	   false：非静音
	*/
	bool is_mute(void);

	/*
	功能：检测是否在播放视频广告
	参数：
	    void
	返回值：
	    true：播放视频广告
		false：播放歌曲
	*/
	bool is_play_video_ad(void);

	/*
	功能：向播放控件发送命令
	参数：
	    cmd：命令
		flag：标示
		value：值
	返回值：
	    结果
	*/
	long send_command(long cmd, long flag, long value);

	/*
	功能：得到当前播放位置
	参数：
	    void
	返回值：
	    播放的位置,得到的是百分比
	*/
	long get_cur_play_pos(void);

	/*
	功能：预览或大厅直播打开功能
	参数：
	    pMedia：媒体路径
		hwnd：显示设备句柄
	返回值：
	   1：成功
	   0：失败
	*/
	long preview_open(LPCTSTR pMedia, long hwnd);

	/*
	功能：预览或大厅直播关闭功能
	参数：
	    void
	返回值：
		1：成功
	   0：失败
	*/
	long preview_close();

	//pk
	/*
	功能：开始pk
	参数：
		n: 0或1
		pMedia:路径
	*/
	long Live_Open(long n, LPCTSTR pMedia);

	/*
	功能：结束pk
	参数：
	n: 0或1
	*/
	long Live_Close(long n);
	/*功能:*/
	long Live_Control(long n, long nCode, long argv0, long argv1);

	/*
	功能：预览或大厅直播关闭功能
	参数：
	    nCode：控制码
		argv0,argv1：参数
	返回值：
		1：成功
	   0：失败
	*/
	long preview_control(long nCode, long argv0, long argv1);

	/*
	功能：打开电视直播
	参数：
	    pDev：设备标示字符串,默认：NULL，自动找第一块电视卡
	    hwnd：显示窗口句柄
		nSignal：电视制式
	返回值：
	    1：成功
	   0：失败
	*/
	long TV_open(LPCTSTR pDev, long hwnd, long nSignal);

	/*
	功能：关闭电视直播
	参数：
		void
	返回值：
		1：成功
	   0：失败
	*/
	long TV_close();

	/*
	功能：发送控制信息给电视直播
	参数：
		nCode：控制码
		argv0,argv1：参数
	返回值：
		1：成功
	   0：失败
	*/
	long TV_control(long nCode, long argv0, long argv1);

	/*
	功能：得到音量、音调
	参数：
	    music_volume：音乐的音量
	    microphone_volume：麦克风的音量
		tune：音调
	返回值：
	   true：成功
	   false：失败
	*/
	bool get_volume_tune(int &music_volume,int &microphone_volume,int &tune);

	/*
	功能：得到音乐音量的最大值最小值步长
	参数：
		music_max：音量的最大值
		music_min：音量的最小值
		music_step：音量的步长
	返回值：
		true：成功
		false：失败
	*/
	bool get_music_volume_info(int &music_max,int &music_min,int &music_step);

	/*
	功能：得到麦克音量的最大值最小值步长
	参数：
		microphone_max：音量的最大值
		microphone_min：音量的最小值
		microphone_step：音量的步长
	返回值：
		true：成功
		false：失败
	*/
	bool get_microphone_volume_info(int &microphone_max,int &microphone_min,int &microphone_step);

	/*
	功能：得到播放器的状态
	参数：
	    void
	返回值：
	   状态
	*/
	int get_player_state(void);

	/*
	功能：得到文件的播放时长
	参数：
	    void
	返回值：
	   秒，总的播放时长
	*/
	long get_total_time_length();	

	/*
	功能：得到当前播放的时长
	参数：
	　　void
    返回值：
	    秒，当前播放的时长
	*/
	long get_play_time_length();

	/*
	功能：调整播放位置
	参数：
	    pos：百分比
	返回值：
	   void
	*/
	void seek(long pos);

	/*
	功能：设置控制代码
	参数：
	   flag：标示
	   value：设置的值
   返回值
       true：成功
	   false：失败
	*/
	bool Set(long flag, long value);
	
	/*
	功能：声音淡入淡出
	参数：
	   uTimerID：定时器的ID
	   uMsg：消息
	   dwUser：用户标示
	   dw1,dw2：参数
   返回值：
      void
	*/
	static void WINAPI volume_callback(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

	/*
	功能：得到电视播放text osd的状态
	参数：
	    void
	返回值;
	    1：正播放
		0：播放完成
	*/
	int get_text_osd_play_state();
	
	/*
	功能：得到正播放的视频类型
	参数：
		void
	返回值：
		播放的视频类型
	*/
	PLAY_SONG_TYPE get_playing_video_type(void);

	/*
	功能：设置正播放的视频类型
	参数：
		video_type：视频类型
	返回值：
		void
	*/
	void set_playing_video_type(PLAY_SONG_TYPE video_type);

	/*
	功能：计算实际设置给电脑的音量
	参数：
	   void
   返回值
       实际设置音量
	*/
	int compute_sound_card_volume(void);

	/*
	功能：正播放歌曲视频路径
	参数：
	    path：歌曲路径
	返回值：
	    true：成功
		false：失败
	*/
	bool get_playing_song_video_path(TCHAR *path);

	/*
	功能：采用淡出的方式输入音乐音量
	参数：
	    void
	返回值：
	    void
	*/
	void output_music_volume(void);

	/*
	功能：设置助唱功能的声卡名字和启用评分功能
	参数：
	    void
	返回值：
	   void
	*/
	void set_help_sing_and_mark(SCORE_SYSTEM use_score_system);

		/*
	功能：开启和关闭评分
	参数：
	   state：评分状态   true-开启评分  false-关闭评分
   返回值：
       true：成功
	   false：失败
	*/
	bool open_score(SCORE_SYSTEM use_score_system,bool state);


	/*
	功能：设置助唱音轨
	参数：
	    void
	返回值：
	    void
	*/
	void set_help_sing_track(int command, bool use_guid=false);

	/*
	功能：得到分数
	参数;
	    void
	返回值：
	    打的分数
	*/
	int get_sing_score(void);

	/*
	功能：关闭文件
	参数：
	    void
	返回值：
	   void
	*/
	void close_video_file(void);

	/*
	功能：得到正在播放的视频
	参数：
	    video_info：视频信息
	返回值：
	    true：成功
		false：失败
	*/
	bool get_playing_video(song_info &video_info);

	bool get_channel_memory();

	// 获取静音前的显示音量
	bool get_card_amplifier_volume_temp(int &nVolume);
	/*
	功能：启用导唱
	参数：
	    void
		is_original:是否是导唱音轨  true导唱,false为原唱
	返回值：
	    void
	*/
	//void enter_guid_song(void);
	void enter_guid_song(bool is_original);

	/*
	功能：退出导唱
	参数：
	   void
   返回值：
       void
	*/
	void exit_guid_song(void);

	/*
	功能：是否显示评分线
	参数：
	   void
   返回值：
       void
	*/
	void set_show_score_line(bool line = false);

	/*
	功能：把主程序句柄赋给filter控件，filter控件存在增辉的插件中
	参数：
	   HWND:主程序句柄
   返回值：
       void
	*/
	void Set_fre_spectrumsitify_hwnd(HWND hwnd);

	/*
	功能：把频谱值赋值给filter控件
	参数：
	   spec:频谱段值
   返回值：
       void
	*/
	void Set_fre_spectrumsitify_spec(int spec);

	void set_use_song_mark(bool flag);
	 
	//设置手动负载均衡服务器
	void set_server_link_index(int link_idx){m_server_manually = link_idx;}
private:
	song_info m_playing_song_info; //当前正在播放的歌曲信息
	bool m_playing;       //是否正在播放，否则暂停
	bool m_channel;	      // 原唱/伴唱，true为原唱。每次切换歌曲时将自动转为伴唱
	bool m_enjoyment;     // 欣赏，表示始终播放原唱
	bool m_play_DJ;       //是否在播放DJ true：是，false：否
	bool m_mute;          //静音
	int  m_song_volume;         //歌曲音量 0---100
	int  m_microphone_volume;   //麦克风的音量  0----100
	int  m_tune;                //音调大小 -5-----5

	int m_card_amplifier_volume;         //卡或公放的音量，即显示的音量
	int m_card_amplifier_volume_temp;	 //静音前，卡或公放的音量，即显示的音量（提前保存）
	int m_cur_card_song_volume;          //当前实际设置给卡的音量
	int m_volume_adjust_percentage;      //音量调节百分比
	bool m_adjust_amplifier;             //调节公放音量，否则调节卡的音量
	int m_card_default_value;            //当使用调节公放音量时，卡一直使用每首歌曲的默认值
	int m_idle_song_volume;              //空闲歌曲音量
	int m_default_tv_volume;			 //默认电视音量

	int m_select_song_volume;            //选择歌曲音量，用于播放空闲歌曲之后，恢复默认记忆

	bool m_volume_memory;         //音量记忆
	bool m_channel_memory;        //原伴唱记忆

	int m_music_volume_max;       //音乐音量的最大值
	int m_music_volume_min;       //音乐音量的最小值
	int m_music_volume_step;      //音乐音量的步长

	int m_microphone_volume_max;  //麦克风音量的最大值
	int m_microphone_volume_min;  //麦克风音量的最小值
	int m_microphone_volume_step; //麦克风音量的步长

	int m_tune_max;               //音调的最大值
	int m_tune_min;               //音调的最小值
	int m_tune_step;              //音调的步长
	int m_tune_original;          //原始的音调

	bool m_show_video_window_exist; //pc上显示视频的窗口是否存在
	HWND m_video_window_handle;   //pc上显示视频窗口的句柄
	HWND m_parent_window_handle;  //父窗口句柄

	bool m_use_stream_control_service; //使用流控服务
	bool m_check_file_exist;           //每次都检查文件是否存在

	//混响
	int m_reverberation_default_value; //混响默认值
	int m_reverberation_min_value;     //混响最小值
	int m_reverberation_max_value;     //混响最大值
	int m_reverberation_step;          //混响的步长
	int m_reverberation_value;         //混响值

	TCHAR m_playing_song_path[256];    //正在播放的歌曲路径
	PLAY_SONG_TYPE m_pre_video_type;   //前一首歌曲的视频类型

	//助唱
	bool m_use_help_sing;              //使用助唱功能
	std::wstring m_help_sing_card_name;//助唱使用的声卡名字

	int m_tape_mode;

	//mark
	bool m_use_song_mark;              //启用打分功能

	//广告参数
	bool m_play_video_ad;              //是否在播放视频广告
	TCHAR m_video_ad_path[256];        //视频广告路径
	bool m_show_score_line;

	int m_server_manually; //手动负载均衡
	long guid_track;
};

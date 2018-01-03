#include "StdAfx.h"
#include ".\player_manager.h"
#include "..\common\Register.h"
#include "..\file\config_file.h"
#include "..\file\log.h"
#include "..\folder_name.h"
#include "..\parserxml\ParserXml.h"
#include "..\common\Mixer.h"

player *m_player=NULL;          //视频播放器
int m_timer_cur_set_volume=0;   //定时器当前设置的音量
int m_timer_max_set_volume=0;   //定时器应该设置的最大音量
MMRESULT m_timer_identifier=0;  //定时器的句柄

#pragma warning(disable: 4311)

player_manager::player_manager(void)
{
	m_player = NULL;
	m_playing = true;
	m_channel=true;
	m_enjoyment=false;
	m_mute=false;
	m_song_volume=0;         //歌曲音量 
	m_microphone_volume=0;   //麦克风的音量
	m_tune=0;
	m_play_DJ = false;
	m_music_volume_max=100;     //音乐音量的最大值
	m_music_volume_min=0;     //音乐音量的最小值
	m_music_volume_step=5;    //音乐音量的补偿

	m_microphone_volume_max=100;  //麦克风音量的最大值
	m_microphone_volume_min=0;  //麦克风音量的最小值
	m_microphone_volume_step=5; //麦克风音量的补偿

	m_tune_max=5;               //音调的最大值
	m_tune_min=-5;               //音调的最小值
	m_tune_step=1;              //音调的步长
	m_tune_original=0;
	m_play_video_ad = false;
	memset(m_playing_song_path,0x0,sizeof(m_playing_song_path));
	memset(m_video_ad_path,0x0,sizeof(m_video_ad_path));
	m_show_video_window_exist = false;
	m_video_window_handle = NULL;
	m_use_stream_control_service=false;
	m_check_file_exist=false;
	m_timer_identifier=0;
	m_reverberation_default_value=5; //混响默认值
	m_reverberation_min_value=0;     //混响最小值
	m_reverberation_max_value=10;     //混响最大值
	m_reverberation_value=5;         //混响值
	m_channel_memory=false;
	m_use_help_sing=false;
	m_pre_video_type=PLAY_SONG_TYPE_RECORDER_SONG;
	m_use_song_mark=false;
	m_select_song_volume=0;
	m_show_score_line = false;
	m_server_manually = -1;
	guid_track = 0;
}

player_manager::~player_manager(void)
{
	if (m_player)
	{
		m_player->stop_all();
		delete m_player;
		m_player = NULL;
	}
	if (0!=m_timer_identifier)
	{
		timeKillEvent(m_timer_identifier);
		m_timer_identifier=0;
	}
}

void player_manager::register_player_ocx(TCHAR *path)
{
	TCHAR ax_dir[256];
	int result=0;

	memset(ax_dir,0x0,sizeof(ax_dir));

	swprintf(ax_dir,L"%s\\%s",path,g_folder_name[12]);
	//注册播放器控件
	result = register_ocx(L"hplayerua.ocx",false);
	//注册破解控件
	result = register_ocx(L"LT.dll",false);
	//注册flash播放控件
	result = register_ocx(L"Flash10c.ocx",false);
	//注册ax控件
	result = register_ax_control(ax_dir);
}

void player_manager::unregister_player_ocx(void)
{
	int result=0;

	result = unregister_ocx(L"hplayerua.ocx");
	result = unregister_ocx(L"LT.dll");
}

bool player_manager::create_player(CWnd *parent_wnd)
{
	bool result=false;

	if (m_player)
	{
		m_player->destory();
		delete m_player;
		m_player = NULL;
	}
	m_player = new player_hard;
	if (NULL==m_player)
	{
		return false;
	}
	result = m_player->create(parent_wnd);
	if (!result)
	{
		m_player->destory();
		delete m_player;
		m_player = NULL;
		return false;
	}

	return true;
}

bool player_manager::initialize(bool window_exist,HWND show_handle,HWND parent_handle)
{
	config_file_manager config_file;
	bool result=false;

	//记录参数
	m_show_video_window_exist = window_exist;
	m_video_window_handle = show_handle;
	m_parent_window_handle = parent_handle;

	if (m_player)
	{
		//初始化播放控件
		result = m_player->initialize();
		
        if (m_show_video_window_exist)
		{
			//改变卡的解码方式，支持混合音
			result = m_player->VODEnableDbDisplay(1);
			if (result)
			{
				m_player->VODSetScreenWindow((long)(m_video_window_handle));
				m_player->VODShowScreenVideo(1);
			}
		}
		else
		{
			m_player->VODShowScreenVideo(0);
		}
		//改变卡的解码方式，支持混合音
		result = m_player->VODEnableDbDisplay(1);
		if (result)
		{
			m_player->VODSetScreenWindow((long)(m_video_window_handle));
		}
		if (m_show_video_window_exist)
		{
			m_player->VODShowScreenVideo(1);
		}
		else
		{
			m_player->VODShowScreenVideo(0);
		}

		//初始化osd
		result = m_player->InitOSD();
		if (!result)
		{
			WriteLog(__FL__, L"初始化OSD失败");
		}
	}
	else
	{
		WriteLog(__FL__, L"m_player为空！");
	}
	//初始化参数
	m_music_volume_max = config_file.read_integer(L"amplifier",L"music_volume_max",100);
	m_music_volume_min = config_file.read_integer(L"amplifier",L"music_volume_min",0);
	m_music_volume_step = config_file.read_integer(L"amplifier",L"music_volume_step",5);

	m_microphone_volume_max = config_file.read_integer(L"amplifier",L"microphone_volume_max",100);
	m_microphone_volume_min = config_file.read_integer(L"amplifier",L"microphone_volume_min",0);
	m_microphone_volume_step = config_file.read_integer(L"amplifier",L"microphone_volume_step",5);
	m_microphone_volume = config_file.read_integer(L"amplifier",L"microphone_volume",50);

	m_tune_max = config_file.read_integer(L"amplifier",L"tune_max",5);
	m_tune_min = config_file.read_integer(L"amplifier",L"tune_min",-5);
	m_tune_step = config_file.read_integer(L"amplifier",L"tune_step",1);
	m_tune_original = config_file.read_integer(L"amplifier",L"tune",0);
	m_tune = m_tune_original;

	//混响
	m_reverberation_default_value = config_file.read_integer(L"reverberation",L"reverberation_default_value",50);
	m_reverberation_min_value = config_file.read_integer(L"reverberation",L"reverberation_min_value",0);
	m_reverberation_max_value = config_file.read_integer(L"reverberation",L"reverberation_max_value",100);
	m_reverberation_step = config_file.read_integer(L"reverberation",L"reverberation_step",5);
	m_reverberation_value = m_reverberation_default_value;

	//音乐音量调节百分比
	m_volume_adjust_percentage=config_file.read_integer(L"amplifier",L"volume_adjust_percentage",100);
	m_adjust_amplifier = config_file.read_boolean(L"amplifier",L"adjust_amplifier_volume",false);
	//得到音量的默认值
	m_card_default_value = config_file.read_integer(L"amplifier",L"amplifier_volume",50);
	m_card_amplifier_volume = m_card_default_value;
	m_cur_card_song_volume = m_card_amplifier_volume;

	//得到空闲歌曲音量
	m_idle_song_volume = config_file.read_integer(L"public_video",L"idlesse_volume",50);

	//得到电视的音量
	m_default_tv_volume = config_file.read_integer(L"amplifier",L"default_tv_volume",50);
	
	//音量是否记忆
	m_volume_memory = config_file.read_boolean(L"amplifier",L"volume_memory",false);
	if(m_volume_memory)
	{
		WriteLog(__FL__, L"使用音量记忆功能");
	}
	//声道记忆
	m_channel_memory = config_file.read_boolean(L"amplifier",L"channel_memory",false);
	if (m_channel_memory)
	{
		WriteLog(__FL__, L"使用原伴唱记忆功能");
	}

	//使用流控服务
	m_use_stream_control_service = config_file.read_boolean(L"control",L"use_stream_control_service",false);
	if(m_use_stream_control_service)
	{
		WriteLog(__FL__, L"使用流控服务");
	}

	//是否每次都检测文件存在
	m_check_file_exist = config_file.read_boolean(L"control",L"check_file_exist",false);
	if (m_check_file_exist)
	{
		WriteLog(__FL__, L"启用检测文件是否存在的机制");
	}
	//助唱
	m_use_help_sing = config_file.read_boolean(L"help_sing",L"use_help_sing",false);
	m_help_sing_card_name = config_file.read_string(L"help_sing",L"help_sing_card",L"");

	/*
	//启用打分功能
	m_use_song_mark = config_file.read_boolean(L"mark",L"use_mark",false);
	if (m_use_song_mark)
	{
		WriteLog(__FL__, L"启用歌曲打分功能");
	}*/

	return result;
}

void player_manager::init_osd(void)
{
	m_player->InitOSD();

	return;
}

void player_manager::show_screen_video(bool show_video)
{
	try
	{
		bool result=false;
		if (NULL==m_player)
		{
			return ;
		}
		//if (!m_show_video_window_exist)
		//{
			//如果没有启动软屏切，直接返回
		//	return;
		//}
		if (show_video)
		{
			m_player->VODShowScreenVideo(1);
		}
		else
		{
			m_player->VODShowScreenVideo(0);
		}
	}
	catch (...)
	{
		
	}
}

long player_manager::set_soft_decode_function(HWND hwnd)
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->set_soft_decode(hwnd);
}

long player_manager::set_slave_video_handle(HWND hwnd)
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->set_slave_video_window(hwnd);
}

bool player_manager::pc_show_tv_video(bool show_tv_video)
{
	try
	{
		bool result=false;
		if (NULL==m_player)
		{
			return false;
		}

		if (m_show_video_window_exist && show_tv_video)
		{
			//改变卡的解码方式，支持混合音
			result = m_player->VODEnableDbDisplay(1);
			if (result)
			{
				m_player->VODShowScreenVideo(1);
				m_player->VODSetScreenWindow((long)(m_video_window_handle));
			}
		}
		else
		{
			result = m_player->VODEnableDbDisplay(0);
			if (result)
			{
				m_player->VODShowScreenVideo(0);
			}
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void player_manager::destroy_player(void)
{
	if (m_player)
	{
		m_player->destory();
	}

	return;
}

bool player_manager::set_video_tape_mode(int tape_mode)
{
	m_tape_mode = tape_mode;

	return true;
}

bool player_manager::set_video_file(song_info &video_info, TCHAR *szVideoPath)
{
	//记录当前正在播放的视频信息
	m_playing_song_info = video_info;

	if (m_player)
	{
		long result = 0;
		//关闭文件
		m_player->close_file();

		m_player->set_play_file_path(szVideoPath);
		//保存设置的视频文件路径
		memset(m_playing_song_path,0x0,sizeof(m_playing_song_path));
		_tcscpy(m_playing_song_path, szVideoPath);

		set_help_sing_track(SD_ORIGNAL_AUDIO, false);

		//导唱默认关闭，设置导唱之前，必须设置原唱音轨
		m_player->Set(SD_GUIDE_ONOFF,0);
		//默认音量是0
		m_player->Set(SD_GUIDE_VOLUME,0);

		//打开视频文件
		result = m_player->open_file();
		if (result<=0)
		{
			return false;
		}

		set_help_sing_track(SD_GUIDE_AUDIO, false);

		//播放歌曲提示osd
		SendMessage(m_parent_window_handle,DM_PLAY_SONG_TIP_MESSAGE,NULL,NULL);
	}
	return true;
} 
bool player_manager::set_video_file(song_info &video_info,int &link_server,TCHAR* music_save_path,TCHAR *voice_save_path,bool is_scoring,int use_guid)
{
	if (m_player)
	{
		TCHAR wave_path[256];
		long result=0;
		TCHAR file_path[256];
		bool ret=false;
		enum PLAY_SONG_TYPE song_type;
		TCHAR video_stream_path[256];
		TCHAR music_wave_path[256];
		TCHAR channel_track[256];

		memset(file_path,0x0,sizeof(file_path));
		memset(wave_path,0x0,sizeof(wave_path));
		memset(video_stream_path,0x0,sizeof(video_stream_path));
		memset(music_wave_path,0x0,sizeof(music_wave_path));
		memset(channel_track,0x0,sizeof(channel_track));

		//设置是否播放广告标识
		m_play_video_ad = false;

		//记录当前正在播放的视频信息
		m_playing_song_info = video_info;
		//先停止播放的视频，然后在设置要播放视频文件的路径
		//m_player->stop();

		//设置手动负载均衡 -- add by caizw
		m_playing_song_info.set_server_manually_idx(m_server_manually);

		//关闭文件
		m_player->close_file();
		if(m_use_stream_control_service)
		{
			//使用流控服务
			TCHAR song_number[128];
			TCHAR server_ip[32];

			memset(song_number,0x0,sizeof(song_number));
			memset(server_ip,0x0,sizeof(server_ip));

			//得到歌曲编号
			ret = m_playing_song_info.get_song_id(song_number);
			if (!ret || (0==_tcscmp(song_number,L"")))
			{
				return false;
			}
			//得到服务IP
			ret = m_playing_song_info.get_server_ip(server_ip);
			if (!ret || (0==_tcscmp(server_ip,L"")))
			{
				return false;
			}
			swprintf(video_stream_path,L"vod:// %s @ %s",song_number,server_ip+2);
			//设置流式文件路径
			m_player->set_play_file_path(video_stream_path);
			WriteLog(__FL__, L"设置流式文件路径");
			WriteLog(__FL__, video_stream_path);
		}
		else
		{
			//得到视频文件的路径
			ret = m_playing_song_info.get_path(file_path,m_check_file_exist,link_server);		

			if (!ret || (0==_tcscmp(file_path,L"")))
			{
				WriteLog(__FL__, L"获得文件路径出错");
				return false;
			}

			//设置视频文件的路径
			WriteLog(__FL__, L"设置的文件路径");
			WriteLog(__FL__, file_path);	

			m_player->set_play_file_path(file_path);
			//保存设置的视频文件路径
			memset(m_playing_song_path,0x0,sizeof(m_playing_song_path));
			_tcscpy(m_playing_song_path,file_path);
		}
		//设置录音文件
		song_type = m_playing_song_info.get_video_type();
		if (PLAY_SONG_TYPE_RECORDER_SONG==song_type)
		{
			//如果是录的歌曲，要同时播放录音
			result = m_playing_song_info.get_wave_path(wave_path);
			if (result && _tcscmp(wave_path, L"") != 0)
			{
				m_player->SetGszWavFileName(wave_path);
			}            
		}//add by yzg @2015-5-29
		else if (PLAY_MUSIC_ENJOY == song_type)
		{
			//如果是音乐欣赏歌曲，要同时播放MP3歌曲
			result = m_playing_song_info.get_song_relative_path(wave_path);
			if (result && _tcscmp(wave_path, L"") != 0 && PathFileExists(wave_path))
			{
				m_player->SetGszWavFileName(wave_path);
			}
		}//add end
#ifndef ONLY_PLAY_KARAOKE_TRACK  //只播放原唱音轨
		if (m_channel_memory&&(PLAY_SONG_TYPE_IDLESSE==song_type))
		{
			//如果是空闲歌曲，采用了声道记忆去掉欣赏状态
			m_enjoyment = false;
		}
#endif
		//2011-12-02 modify ，因为每首歌曲都要启用导唱，所以必须设置原唱音轨
		//if (m_use_song_mark || (m_use_help_sing && (!m_help_sing_card_name.empty())))
		{
			//启用了打分功能、助唱功能、导唱功能，设置原唱音轨
			//
			//set_help_sing_track(SD_ORIGNAL_AUDIO, use_guid);
			set_help_sing_track(SD_ORIGNAL_AUDIO, false);   //人声导唱
			if (1 == use_guid)
			{
			   set_help_sing_track(SD_GUIDE_AUDIO, true);   //旋律导唱
			}
			//set_help_sing_track(SD_GUIDE_AUDIO, false);
		}
		//导唱默认关闭，设置导唱之前，必须设置原唱音轨
		m_player->Set(SD_GUIDE_ONOFF,0);
		//默认音量是0
		m_player->Set(SD_GUIDE_VOLUME,0);
		//只有已选歌曲才保存伴奏
		if ((0!=_tcscmp(voice_save_path,L"")) && (PLAY_SONG_TYPE_SELECT_SONG==m_playing_song_info.get_video_type()))
		{
			m_player->Set(SD_SET_RECORD_FILE,(long)voice_save_path);
			WriteLog(__FL__, L"设置已选歌曲保存伴奏的路径:");
			WriteLog(__FL__, voice_save_path);
		}else{
			WriteLog(__FL__, L"没有设置已选歌曲保存伴奏的路径");
		}

		if ((0!=_tcscmp(music_save_path,L""))&&(PLAY_SONG_TYPE_SELECT_SONG==m_playing_song_info.get_video_type()))
		{
			//得到伴奏音轨
			result = m_playing_song_info.get_channel_track(false,channel_track);
			if (result)
			{
				//转化成整形
				if (_tcscmp(channel_track, L"左")==0)
				{
					//设置成左声道
					_tcscpy(channel_track,L"L");
				}
				else if (_tcscmp(channel_track, L"右")==0)
				{
					//设置成右声道
					_tcscpy(channel_track,L"R");
				}
			}

			//设置录音文件保存路径
			if (1 == m_tape_mode  && PLAY_SONG_TYPE_SELECT_SONG == song_type/*&& PLAY_SONG_TYPE_RECORDER_SONG==song_type*/)
			{	
				swprintf(music_wave_path,L"%s=%s",channel_track,music_save_path);
				m_player->Set(SD_DUMP_AUDIO,(long)music_wave_path);
				WriteLog(__FL__, L"设置已选歌曲保存的路径:");
				WriteLog(__FL__, music_wave_path);
			}else{
				WriteLog(__FL__, L"没有设置已选歌曲保存的路径");
			}
		}
		if (is_scoring&&(PLAY_SONG_TYPE_SELECT_SONG==m_playing_song_info.get_video_type()))   //如果正在评分
		{
			//选择歌曲评分
			open_score(SCORE_SYSTEM_SHINE,true);
			//open_score(SCORE_SYSTEM_SHINE,m_use_song_mark);
		}
		else
		{
			//空闲歌曲不评分
			open_score(SCORE_SYSTEM_SHINE,false);
		}
		//打开视频文件
		result = m_player->open_file();
		if (result<=0)
		{
			return false;
		}

		//播放歌曲提示osd
		SendMessage(m_parent_window_handle,DM_PLAY_SONG_TIP_MESSAGE,NULL,NULL);
	}
	return true;
}

void player_manager::set_help_sing_track(int command, bool use_guid)
{
	try
	{
		bool result=false;
		TCHAR channel_track[256];
		TCHAR kalaoke_track[256];
		TCHAR vocal_track[256];

		memset(channel_track,0x0,sizeof(channel_track));
		memset(kalaoke_track, 0x0, sizeof(kalaoke_track));
		memset(vocal_track, 0x0, sizeof(vocal_track));

		
		if (use_guid)
		{
			//旋律导唱
			result = m_playing_song_info.get_guid_track(channel_track);
			if (0 == _tcscmp(channel_track, L"0") || (0 == _tcscmp(channel_track, L"5")))
			{
				return;
			}
			memset(channel_track, 0x0, sizeof(channel_track));
			_tcscpy(channel_track, L"3");
		}
		else
		{
			//人声导唱
			m_playing_song_info.get_channel_track(true, vocal_track);
		    m_playing_song_info.get_channel_track(false, kalaoke_track);
			if (0 == _tcscmp(vocal_track, kalaoke_track))
			{
				return;
			}
			_tcscpy(channel_track, vocal_track);
		}

		//if (result)
		{
			//转化成整形
			if (_tcscmp(channel_track, L"左")==0)
			{
				//设置成左声道
				m_player->Set(command,'L');
			}
			else if (_tcscmp(channel_track, L"右")==0)
			{
				//设置成右声道
				m_player->Set(command,'R');
			}
			else
			{
				int volume_track = _ttoi(channel_track);
				if (volume_track < 0)
				{
					volume_track = 2;
				}
				//设置音轨
				m_player->Set(command,volume_track);
			}
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}

bool player_manager::set_ad_video_file(TCHAR *path)
{
	if (m_player)
	{
		long result=0;
		bool ret=false;

		//设置是否播放广告标识
		m_play_video_ad = true;
		//保存广告路径
		memset(m_video_ad_path,0x0,sizeof(m_video_ad_path));
		_tcscpy(m_video_ad_path,path);

		//先停止播放的视频，然后在设置要播放视频文件的路径
		//m_player->stop();
		m_player->close_file();
		//设置视频文件的路径
		m_player->set_play_file_path(path);
		//打开视频文件
		result = m_player->open_file();
		if (result<=0)
		{
			return false;
		}
	}
	return true;
}

bool player_manager::play_video_file(bool cancel_mute,bool kalaok_track,bool lock_public_volume)
{
	if (m_player)
	{
		long result=0;
		TCHAR channel_track[16];
		long video_property=0;
		PLAY_SONG_TYPE playing_video_type;

		memset(channel_track,0x0,sizeof(channel_track));

		//开始播放
		m_player->play();
		//得到正播放的视频类型
		playing_video_type = get_playing_video_type();

		m_playing=true;
		if (m_play_video_ad)
		{
			//播放广告的默认值
			m_channel = true;
			m_song_volume = m_idle_song_volume;
			
			if (!m_volume_memory || (lock_public_volume&&(PLAY_SONG_TYPE_IDLESSE==playing_video_type)))
			{
				//如果不记忆就用设置的值，如果锁定公共音量，空闲歌曲也不记忆
				//m_card_amplifier_volume = m_song_volume;   //2011-12-29 modify
				m_card_amplifier_volume = (m_music_volume_max+m_music_volume_min)/2;
			}

			//得到实际要设置给卡的音量
			m_cur_card_song_volume = compute_sound_card_volume();

			if (!m_mute || !cancel_mute)
			{
				//取消静音，采用淡出的方式输出音量
				output_music_volume();
			}
			else
			{
				m_player->set_volume(0,0);
				m_mute=true;
			}
		}
		else
		{
			if (m_enjoyment||kalaok_track)
			{
				//欣赏状态，原唱
				m_channel = true;
			}
			else
			{
				//否则都是伴唱开始
				m_channel = false;
			}
			//设置音轨
			result = m_playing_song_info.get_channel_track(m_channel,channel_track);
			if (result)
			{
				//转化成整形
				if (_tcscmp(channel_track, L"左")==0)
				{
					//设置成左声道
					m_player->balance(2);
				}
				else if (_tcscmp(channel_track, L"右")==0)
				{
					//设置成右声道
					m_player->balance(1);
				}
				else
				{
					int volume_track = _ttoi(channel_track);
					if (volume_track < 0)
					{
						if (m_channel)
						{
							// 原唱不能为负值
							volume_track = 2;
						}
						else
						{
							// 伴唱不能为负值
							volume_track = 1;
						}
					}
					//设置音轨
					m_player->set_track(volume_track);
				}
			}
			//得到音量
			m_song_volume = m_playing_song_info.get_volume(m_channel);
			if(m_song_volume<=0)
			{
				//录音回放没有声音
				//如果歌曲音量不存在就采用空闲歌曲音量
				m_song_volume = m_idle_song_volume + 20;
				if (m_song_volume > 100)
				{
					m_song_volume = 90;
				}				
				//m_song_volume = 60;
			}

			//判断当前是否是播放电视
			if(PLAY_TV == playing_video_type)
			{
				//如果当前是播放电视
				m_song_volume = m_default_tv_volume;
			}

			//按照最大最小值，计算一下百分比
			m_song_volume = m_music_volume_min+m_song_volume*(m_music_volume_max-m_music_volume_min)/100;

			if (PLAY_SONG_TYPE_SELECT_SONG==m_pre_video_type)
			{
				//前一视频是选择的歌曲要记录最后的音量
				m_select_song_volume = m_card_amplifier_volume;
			}
			
			if (PLAY_SCORE_VIDEO!=playing_video_type)
			{
				//如果是打分视频，不改变音量，打分视频和前一个视频，看为一个整体
				if (lock_public_volume)
				{
					//锁定空闲视频
					if (m_volume_memory&&(PLAY_SONG_TYPE_IDLESSE!=m_pre_video_type)&&(PLAY_SONG_TYPE_IDLESSE!=playing_video_type)&&(m_select_song_volume>0))
					{
						//记忆,采用上一首已选歌曲音量
                        m_card_amplifier_volume = m_select_song_volume;
					}
					else
					{
						//不记忆,采用数据库音量
						//m_card_amplifier_volume = m_song_volume;   //2011-12-29 modify
						m_card_amplifier_volume = (m_music_volume_max+m_music_volume_min)/2;
					}
				}
				else
				{
					//不锁定空闲音量
					if (!m_volume_memory|| m_adjust_amplifier)
					{
						//如果不记忆就用设置的值，如果锁定公共音量，空闲歌曲也不记忆
						//m_card_amplifier_volume = m_song_volume;   //2011-12-29 modify
						m_card_amplifier_volume = (m_music_volume_max+m_music_volume_min)/2;
					}
				}
				//保存前一个视频类型
				m_pre_video_type = playing_video_type;
			}
			//得到实际要设置给卡的音量
			m_cur_card_song_volume = compute_sound_card_volume();

			//if (!m_mute || cancel_mute)
			if (!m_mute)
			{
				//取消静音，采用淡出的方式输出音量
				output_music_volume();
			}
			else
			{
				m_player->set_volume(0,0);
				m_mute=true;
			}	

			//设置饱和度
			video_property = m_playing_song_info.get_video_saturation();
			if (video_property>10)
			{
				m_player->set_saturation(video_property);
			}
			//设置亮度
			video_property = m_playing_song_info.get_video_luminance();
			if (video_property>10)
			{
				m_player->set_bright(video_property);
			}
			//设置对比度
			video_property = m_playing_song_info.get_video_contrast();
			if (video_property>10)
			{
				m_player->set_contrast(video_property);
			}
		}
	}
	return true;
}

void player_manager::play(void)
{
	if (m_player)
	{
		m_player->play();
	}
	m_playing=true;
	return;
}

void player_manager::pause(void)
{
	if (m_player)
	{
		m_player->pause();
	}
	m_playing=false;
	return;
}

void player_manager::stop(void)
{
	if (m_player)
	{
		m_player->stop();
		m_player->close_file();
		m_playing=false;
	}
	return;
}

void player_manager::play_or_pause(void)
{
	bool result=false;

	if (m_playing)
	{
		//正在播放,暂停
		pause();
	}
	else
	{
		result = is_mute();
		if (!result)
		{
			//不是静音，要先静音，然后采用淡出的方式输出
			mute();
		}
		//暂停，开始播放
		play();
		if (!result && m_mute)
		{
			//取消静音，采用淡出的方式输出音量
			output_music_volume();
		}
	}

	return;
}

bool player_manager::replay(TCHAR* music_save_path,TCHAR *voice_save_path,bool use_guid)
{
	if (m_player)
	{
		long result=0;
		TCHAR file_path[256];
		bool ret=false;
		TCHAR channel_track[256];
		TCHAR music_wave_path[256];
		TCHAR wave_path[256];
		enum PLAY_SONG_TYPE song_type;

		memset(file_path,0x0,sizeof(file_path));
		memset(channel_track,0x0,sizeof(channel_track));
		memset(music_wave_path,0x0,sizeof(music_wave_path));
		memset(wave_path,0x0,sizeof(wave_path));

		//得到当前正在播放的视频文件路径
		if (m_play_video_ad)
		{
			//广告
			_tcscpy(file_path,m_video_ad_path);
		}
		else
		{
			//普通歌曲
			_tcscpy(file_path,m_playing_song_path);
		}

		//设置录音文件
		song_type = m_playing_song_info.get_video_type();
		if (PLAY_SONG_TYPE_RECORDER_SONG==song_type)
		{
			//如果是录的歌曲，要同时播放录音
			result = m_playing_song_info.get_wave_path(wave_path);
			if (result)
			{
				m_player->SetGszWavFileName(wave_path);
			}            
		}//add by yzg @2015-5-29
		else if (PLAY_MUSIC_ENJOY == song_type)
		{
			//如果是音乐欣赏歌曲，要同时播放MP3歌曲
			result = m_playing_song_info.get_song_relative_path(wave_path);
			if (result && _tcscmp(wave_path, L"") != 0 && PathFileExists(wave_path))
			{
				m_player->SetGszWavFileName(wave_path);
			}
		}//add end

		//先停止播放的视频，然后在设置要播放视频文件的路径
		//m_player->stop();
		m_player->close_file();
		//设置视频文件的路径
		m_player->set_play_file_path(file_path);
		//2011-12-02 modify ，因为每首歌曲都要启用导唱，所以必须设置原唱音轨
		//if (m_use_song_mark || (m_use_help_sing && (!m_help_sing_card_name.empty())))
		{
			//启用了打分功能、助唱功能、导唱功能，设置原唱音轨
			//set_help_sing_track(SD_ORIGNAL_AUDIO, use_guid);
			set_help_sing_track(SD_ORIGNAL_AUDIO, false);
			//set_help_sing_track(SD_GUIDE_AUDIO, false);
		}
		//导唱默认关闭，设置导唱之前，必须设置原唱音轨
		m_player->Set(SD_GUIDE_ONOFF,0);
		//默认音量是0
		m_player->Set(SD_GUIDE_VOLUME,0);
		//只有已选歌曲才保存伴奏
		if (0!=_tcscmp(voice_save_path,L""))
		{
			m_player->Set(SD_SET_RECORD_FILE,(long)voice_save_path);
		}
		if ((0!=_tcscmp(music_save_path,L""))&&(PLAY_SONG_TYPE_SELECT_SONG==m_playing_song_info.get_video_type()))
		{
			//得到伴奏音轨
			result = m_playing_song_info.get_channel_track(false,channel_track);
			if (result)
			{
				//转化成整形
				if (_tcscmp(channel_track, L"左")==0)
				{
					//设置成左声道
					_tcscpy(channel_track,L"L");
				}
				else if (_tcscmp(channel_track, L"右")==0)
				{
					//设置成右声道
					_tcscpy(channel_track,L"R");
				}
			}
			//设置录音文件保存路径
			if (1 == m_tape_mode)
			{	 
				//设置录音文件保存路径
				swprintf(music_wave_path,L"%s=%s",channel_track,music_save_path);
				m_player->Set(SD_DUMP_AUDIO,(long)music_wave_path);

			}

			////设置录音文件保存路径
			//swprintf(music_wave_path,L"%s=%s",channel_track,music_save_path);
			//m_player->Set(SD_DUMP_AUDIO,(long)music_wave_path);
		}
		//打开视频文件
		result = m_player->open_file();
		if (result<0)
		{
			return false;
		}

		set_help_sing_track(SD_GUIDE_AUDIO, use_guid);
		//if (m_mute)
		//{
			//取消静音，采用淡出的方式输出音量
		//	output_music_volume();
		//}
	}
	return true;
}

void player_manager::mute(void)
{
	try
	{
		//杀死原有的定时器
		if (0!=m_timer_identifier)
		{
			timeKillEvent(m_timer_identifier);
			m_timer_identifier=0;
		}

		if (m_mute)
		{
			//取消静音，采用淡出的方式输出音量
			output_music_volume();
			WriteLog(__FL__, L"取消静音");
		}
		else
		{
			//原来是原音，改成静音
			m_mute = true;
			if (m_player)
			{
				m_player->set_volume(0,0);
			}
			WriteLog(__FL__, L"进入静音状态");
		}
	}
	catch (...)
	{
		
	}
	return;
}

void player_manager::change_channel(long guid_track)
{
	//设置音轨
	m_player->set_track(guid_track);
	guid_track = 1;
}

void player_manager::change_channel(void)
{
	bool result=false;
	TCHAR channel_track[16];
	
	memset(channel_track,0x0,sizeof(channel_track));

	WriteLog(__FL__, L"进行音轨切换");

	if (m_channel)
	{
		//目前是原唱，改为伴唱
		m_channel=false;
		m_enjoyment=false;
	}
	else
	{
		//目前是伴唱，改为原唱
		m_channel=true;
		if (m_channel_memory)
		{
			//记忆原伴唱
			m_enjoyment=true;
		}
	}

	//改变音轨
	result = m_playing_song_info.get_channel_track(m_channel,channel_track);
	if (result)
	{
		//转化成整形
		if (_tcscmp(channel_track, L"左")==0)
		{
			//设置成左声道
			m_player->balance(2);
		}
		else if (_tcscmp(channel_track, L"右")==0)
		{
			//设置成右声道
			m_player->balance(1);
		}
		else
		{
			int volume_track = _ttoi(channel_track);
			if (volume_track < 0)
			{
				if (m_channel)
				{
					// 原唱不能为负值
					volume_track = 2;
				}
				else
				{
					// 伴唱不能为负值
					volume_track = 1;
				}
			}
			//设置音轨
			m_player->set_track(volume_track);
		}
	}
	//if (m_mute)
	//{
		//取消静音，采用淡出的方式输出音量
	//	output_music_volume();
	//}

	return;
}

//<invoke name="pubAudioInfo" returntype="xml"><arguments><string><audio_data><data music="2" micro="50" tone="0" /></audio_data></string></arguments></invoke>
//<invoke name="pubMainBtn" returntype="xml"><arguments><string><control_data><data ismute="false" istrack="true" music="40" isplay="false"/></control_data></string></arguments></invoke>
bool player_manager::parse_panel_list_xml(TCHAR *list_xml)
{
	try
	{
		CParserXml parse_xml_class;
		int item_value1=0;
		int item_value2=0;
		int item_value3=0;
		int item_value4=0;
		TCHAR type_flag[256];
		bool result=false;

		memset(type_flag,0x0,sizeof(type_flag));

		//解析xml字符串
		result = parse_xml_class.parse_control_xml(list_xml,item_value1,item_value2,item_value3,item_value4,type_flag);
		if (!result)
		{
			return false;
		}
		if (0==_tcscmp(type_flag,L"pubAudioInfo"))
		{
			m_card_amplifier_volume = item_value1;
			m_microphone_volume = item_value2;
			m_tune = item_value3;
		}
		else
		{
			if (1==item_value1)
			{
				m_mute = true;
			}
			else
			{
				m_mute = false;
			}
			if (1==item_value2)
			{
				m_channel = false;
			}
			else
			{
				m_channel = true;
			}
			m_card_amplifier_volume = item_value3;
			if (1==item_value4)  //界面显示的和实际状态相反
			{
				m_playing = false;
			}
			else
			{
				m_playing = true;
			}
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

/*
<data ismute=”true” istrack=”false” music=”50” isplay=”true”/>
*/

bool player_manager::make_panel_list_xml(TCHAR *list_xml)
{
	try
	{
		if (NULL==list_xml)
		{
			return false;
		}

		TCHAR play_state[64];
		TCHAR track_state[64];
		TCHAR mute_state[64];
		int show_volumn=0;

		memset(play_state,0x0,sizeof(play_state));
		memset(track_state,0x0,sizeof(track_state));
		memset(mute_state,0x0,sizeof(mute_state));

		if (m_playing)
		{
			//现在是播放状态，按钮应该是暂停
			_tcscpy(play_state,L"false");
		}
		else
		{
			//现在时暂停状态，按钮应该是播放
			_tcscpy(play_state,L"true");
		}
		if (m_channel)
		{
			//现在是原唱，按钮应该是伴唱
			_tcscpy(track_state,L"false");
		}
		else
		{
			//现在是伴唱，按钮应该是原唱
			_tcscpy(track_state,L"true");
		}
		if (m_mute)
		{
			//静音
			_tcscpy(mute_state,L"true");
			show_volumn = 0;
		}
		else
		{
            _tcscpy(mute_state,L"false");
			//计算显示的音量
			show_volumn = (m_card_amplifier_volume-m_music_volume_min)*100/(m_music_volume_max-m_music_volume_min);
		}
		
		if (show_volumn<0)
		{
			show_volumn = 0;
		}
		else if (show_volumn>100)
		{
			show_volumn = 100;
		}
		swprintf(list_xml,L"<control_data><data ismute=\"%s\" istrack=\"%s\" music=\"%d\" isplay=\"%s\"/></control_data>",mute_state,track_state,show_volumn,play_state);

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool player_manager::make_volume_list_xml(TCHAR *list_xml)
{
	try
	{
		if (NULL==list_xml)
		{
			return false;
		}
		int show_volumn=0;

		//计算显示的音量
		show_volumn = (m_card_amplifier_volume-m_music_volume_min)*100/(m_music_volume_max-m_music_volume_min);
		if (show_volumn<0)
		{
			show_volumn = 0;
		}
		else if (show_volumn>100)
		{
			show_volumn = 100;
		}
		swprintf(list_xml,L"<audio_data><data music=\"%d\" micro=\"%d\" tone=\"%d\" /></audio_data>",show_volumn,m_microphone_volume,m_tune);
		
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool player_manager::make_control_bar_list_xml(TCHAR *list_xml)
{
	try
	{
		TCHAR value[256];
		int show_volumn=0;

		memset(value,0x0,sizeof(value));

		_tcscpy(list_xml,L"<data><panel_info>");
		if (m_playing)
		{
			//现在是播放状态，按钮应该是暂停
			_tcscat(list_xml,L"<play pause=\"1\" play=\"0\" />");
		}
		else
		{
			//现在时暂停状态，按钮应该是播放
			_tcscat(list_xml,L"<play pause=\"0\" play=\"1\" />");
		}
		if (m_channel)
		{
			//现在是原唱，按钮应该是伴唱
			_tcscat(list_xml,L"<former yuan=\"0\" ban=\"1\" />");
		}
		else
		{
			//现在是伴唱，按钮应该是原唱
			_tcscat(list_xml,L"<former yuan=\"1\" ban=\"0\" />");
		}
		if (m_play_DJ)
		{
			//DJ
			_tcscat(list_xml,L"<dj dj1=\"0\" dj2=\"1\" /> ");
		}
		else
		{
			_tcscat(list_xml,L"<dj dj1=\"1\" dj2=\"0\" /> ");
		}
		if (m_enjoyment)
		{
			//欣赏
			_tcscat(list_xml,L"<enjoy enjoy1=\"0\" enjoy2=\"1\" />");
		}
		else
		{
			_tcscat(list_xml,L"<enjoy enjoy1=\"1\" enjoy2=\"0\" />");
		}
		if (m_mute)
		{
			//静音
			_tcscat(list_xml,L"<mute mute1=\"0\" mute2=\"1\"/></panel_info>");
		}
		else
		{
			_tcscat(list_xml,L"<mute mute1=\"1\" mute2=\"0\"/></panel_info>");
		}

		//计算显示的音量
		show_volumn = (m_card_amplifier_volume-m_music_volume_min)*100/(m_music_volume_max-m_music_volume_min);
		if (show_volumn<0)
		{
			show_volumn = 0;
		}
		else if (show_volumn>100)
		{
			show_volumn = 100;
		}
		swprintf(value,L"<value mic=\"%d\" music=\"%d\" tone=\"%d\" /></data>",m_microphone_volume,show_volumn,m_tune);

		_tcscat(list_xml,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool player_manager::change_enjoyment_state(void)
{
	bool result=false;
	TCHAR channel_track[16];

	memset(channel_track,0x0,sizeof(channel_track));

	if (m_enjoyment)
	{
		//不是欣赏状态就是伴唱，按钮显示原唱
		m_enjoyment = false;
		m_channel = false;
	}
	else
	{
		//欣赏状态就是原唱，按钮式伴唱
		m_enjoyment = true;
		m_channel = true;
	}

	//改变音轨
	result = m_playing_song_info.get_channel_track(m_channel,channel_track);
	if (result)
	{
		//转化成整形
		if (_tcscmp(channel_track, L"左")==0)
		{
			//设置成左声道
			m_player->balance(2);
		}
		else if (_tcscmp(channel_track, L"右")==0)
		{
			//设置成右声道
			m_player->balance(1);
		}
		else
		{
			int volume_track = _ttoi(channel_track);
			if (volume_track < 0)
			{
				if (m_channel)
				{
					// 原唱不能为负值
					volume_track = 2;
				}
				else
				{
					// 伴唱不能为负值
					volume_track = 1;
				}
			}
			//设置音轨
			m_player->set_track(volume_track);
		}
	}
	//if (m_mute)
	//{
		//取消静音，采用淡出的方式输出音量
	//	output_music_volume();
	//}

	return true;
}

bool player_manager::play_text_osd(const TCHAR* background_color, const text_osd_info& text_info, const play_variable& play_var)
{
	if (m_player)
	{
		m_player->PlayTextOSD(background_color,text_info, play_var);
	}
	
	return true;
}
//增加文字osd索引，默认为0 //yzg 2015-6-8
bool player_manager::play_control_text_osd(TCHAR *text,long color,long x_pos,long y_pos,long lIndex)
{
	if (m_player)
	{
		m_player->OSD_GF(text,lIndex, color,x_pos,y_pos);
	}
	return true;
}

bool player_manager::stop_play_control_text_osd(long lIndex)
{
	if (!m_player)
		return false;

	return (m_player->stop_OSD_GF(lIndex)>0)?true:false;
}
bool player_manager::play_control_osd(const TCHAR *path,int x_pos,int y_pos)
{
	if (m_player)
	{
		FILE* fp = _wfopen(path, L"rb");

		if (fp) // 文件存在时才执行以下动作：
		{
			fclose(fp);	
			fp=NULL;
			m_player->PlayControlOSD(path, x_pos, y_pos);
		}
		else
		{
			// 其他情况, 关闭屏显
			m_player->StopControlOSD();
		}
	}

	return true;
}

void player_manager::stop_control_osd(void)
{
	if (m_player)
	{
		m_player->StopControlOSD();
	}
	
	return;
}

bool player_manager::play_logo_osd(TCHAR *path,int index,int x_pos,int y_pos,bool first_logo)
{
	if (first_logo)
	{
		stop_logo_osd();
	}
	if (m_player)
	{
		m_player->PlayOSDLogo(path,index,x_pos,y_pos,first_logo);
	}
	
	return true;
}

bool player_manager::play_ad_logo_osd(TCHAR *path,int logo_layer)
{
	if (m_player)
	{
		m_player->PlayADOSDLogo(path,logo_layer);
	}
	
	return true;
}

bool player_manager::play_bmp_osd(TCHAR *path,play_variable &play_var,OSDAlignment alignment_mode)
{
	if (m_player)
	{
		m_player->PlayBmpOSD(path,play_var,alignment_mode);
	}
	
	return true;
}

bool player_manager::play_score_osd(TCHAR *path,play_variable &play_var,OSDAlignment alignment_mode)
{
	if (m_player)
	{
		m_player->PlayScoreOSD(path,play_var,alignment_mode);
	}

	return true;
}

void player_manager::show_wall_panel_picture(TCHAR *path)
{
	if (m_player)
	{
		m_player->ShowWallPanelOSD(path);
	}
}

void player_manager::hide_wall_panel_picture(void)
{
	if (m_player)
	{
		m_player->HideWallPanelOSD();
	}
}

void player_manager::stop_bmp_osd(void)
{
	if (m_player)
	{
		m_player->StopBMPOSD();
	}
	
	return;
}

void player_manager::stop_score_osd(void)
{
	if (m_player)
	{
		m_player->StopScoreOSD();
	}

	return;
}


void player_manager::stop_logo_osd(void)
{
	if (m_player)
	{
		m_player->StopOSDLogo();
	}
}

void player_manager::stop_ad_logo_osd(int logo_layer)
{
	if (m_player)
	{
		m_player->StopADOSDLogo(logo_layer);
	}
}

bool player_manager::is_playing(void)
{
	return m_playing;
}

bool player_manager::change_music_volume(enum VOLUME_CHANGE_FLAG change_flag,int set_volume)
{
	try
	{
		//杀死定时器
		if (0!=m_timer_identifier)
		{
			timeKillEvent(m_timer_identifier);
			m_timer_identifier=0;
		}

		//记录原有的音量
		m_timer_cur_set_volume = m_cur_card_song_volume;

		switch(change_flag)
		{
		case VOLUME_UP_FLAG:
			{
				m_card_amplifier_volume += m_music_volume_step;
				if (m_card_amplifier_volume>m_music_volume_max)
				{
					m_card_amplifier_volume = m_music_volume_max;
				}	
			}
			break;
		case VOLUME_DOWN_FLAG:
			{
				m_card_amplifier_volume -= m_music_volume_step;
				if (m_card_amplifier_volume<m_music_volume_min)
				{
					m_card_amplifier_volume = m_music_volume_min;
				}
			}
			break;
		case VOLUME_SET_FLAG:  //设置音量
			{
				if (set_volume == 0)
				{
					m_card_amplifier_volume_temp = m_card_amplifier_volume;
				}
				m_card_amplifier_volume = set_volume;
				if (m_card_amplifier_volume<m_music_volume_min)
				{
					m_card_amplifier_volume = m_music_volume_min;
				}
				else if (m_card_amplifier_volume>m_music_volume_max)
				{
					m_card_amplifier_volume = m_music_volume_max;
				}
			}
			break;
		default:
			break;
		}

		//得到实际要设置给卡的音量
		m_cur_card_song_volume = compute_sound_card_volume();

		if (!m_adjust_amplifier)
		{
			//如果不是调整公放音量，就改变卡的音量
			m_timer_max_set_volume = m_cur_card_song_volume;
			//启动定时器，设置音量淡入淡出
			m_timer_identifier = timeSetEvent(200,0,volume_callback,0,TIME_CALLBACK_FUNCTION|TIME_PERIODIC);
		}
		else
		{
			//神龙卡的默认值
			m_player->set_volume(m_card_default_value,m_card_default_value);
		}
		if (set_volume == 0)
		{
			m_mute = true;
		}
		else
		{
			//改成非静音状态
			m_mute = false;
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

int player_manager::change_microphone_volume(enum VOLUME_CHANGE_FLAG change_flag,int set_volume)
{
	switch(change_flag)
	{
	case VOLUME_UP_FLAG:
		{
			m_microphone_volume += m_microphone_volume_step;
			if (m_microphone_volume>m_microphone_volume_max)
			{
				m_microphone_volume = m_microphone_volume_max;
			}
		}
		break;
	case VOLUME_DOWN_FLAG:
		{
			m_microphone_volume -= m_microphone_volume_step;
			if (m_microphone_volume<m_microphone_volume_min)
			{
				m_microphone_volume = m_microphone_volume_min;
			}
		}
		break;
	case VOLUME_SET_FLAG:
		{
			m_microphone_volume = set_volume;
			if (m_microphone_volume>m_microphone_volume_max)
			{
				m_microphone_volume = m_microphone_volume_max;
			}
			else if (m_microphone_volume<m_microphone_volume_min)
			{
				m_microphone_volume = m_microphone_volume_min;
			}
		}
		break;
	default:
		break;
	}
	//返回目前麦克风的实际音量
	return m_microphone_volume;
}

int player_manager::change_tune(enum TUNE_CHANGE_FLAG change_flag,int tune_value,bool control_change_tone)
{
	switch(change_flag)
	{
	case TUNE_UP_FLAG:
		{
			m_tune += m_tune_step;
			if (m_tune>m_tune_max)
			{
				m_tune = m_tune_max;
			}
		}
		break;
	case TUNE_DOWN_FLAG:
		{
			m_tune -= m_tune_step;
			if (m_tune<m_tune_min)
			{
				m_tune = m_tune_min;
			}
		}
		break;
	case TUNE_ORIGINAL_FLAG:
		{
			m_tune = m_tune_original;
		}
		break;
	case TUNE_SET_VALUE_FLAG:
		{
			m_tune = tune_value;
		}
		break;
	default:
		break;
	}

	if (control_change_tone&&m_player)
	{
		m_player->WaveMixer_SetTone(m_tune);
	}

	return m_tune;
}

int player_manager::change_reverberation(enum REVERBERATION_CHANGE_FLAG change_flag)
{
	try
	{
		switch(change_flag)
		{
		case REVERBERATION_UP_FLAG:   //混响加
			{
				m_reverberation_value += m_reverberation_step;
				if (m_reverberation_value>m_reverberation_max_value)
				{
					m_reverberation_value = m_reverberation_max_value;
				}
			}
			break;
		case REVERBERATION_DOWN_FLAG: //混响减
			{
				m_reverberation_value -= m_reverberation_step;
				if (m_reverberation_value<m_reverberation_min_value)
				{
					m_reverberation_value = m_reverberation_min_value;
				}
			}
			break;
		default:
			break;
		}

		return m_reverberation_value;
	}
	catch (...)
	{
		
	}

	return m_reverberation_value;
}

bool player_manager::play_wave_mixer_audio(TCHAR *wave_path,int loop,int music_out)
{
	try
	{
		long result=0;

		if (m_player)
		{
			result = m_player->WaveMixer_Play(wave_path,loop,music_out);
		}
		
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void player_manager::stop_wave_mixer_audio(void)
{
	try
	{
		long result=0;

		if (m_player)
		{
			result = m_player->WaveMixer_Stop();
		}       
	}
	catch (...)
	{
		
	}
	return;
}

void player_manager::change_DJ_state(void)
{
	if (m_play_DJ)
	{
		m_play_DJ = false;
	}
	else
	{
		m_play_DJ = true;
	}

	return;
}

bool player_manager::is_play_DJ(void)
{
	return m_play_DJ;
}

bool player_manager::get_channel(void)
{
	return m_channel;
}

long player_manager::get_guid_channel()
{
	return guid_track;
}

bool player_manager::is_enjoyment(void)
{
	return m_enjoyment;
}

bool player_manager::is_mute(void)
{
	return m_mute;
}

bool player_manager::is_play_video_ad(void)
{
	return m_play_video_ad;
}

long player_manager::send_command(long cmd, long flag, long value)
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->command(cmd,flag,value);
}

long player_manager::get_cur_play_pos(void)
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->get_current_pos();
}

long player_manager::preview_open(LPCTSTR pMedia, long hwnd)
{
	if ((NULL==m_player)||(NULL==pMedia)||(0==_tcscmp(pMedia,L"")))
	{
		return 0;
	}
	return m_player->preview_open(pMedia,hwnd);
}


long player_manager::preview_close()
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->preview_close();
}

long player_manager::preview_control(long nCode, long argv0, long argv1)
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->preview_control(nCode,argv0,argv1);
}

long player_manager::Live_Open(long n, LPCTSTR pMedia)
{
	if ((NULL==m_player)||(NULL==pMedia)||(0==_tcscmp(pMedia,L"")))
	{
		return 0;
	}

	return m_player->Live_Open(n,pMedia);
}

long player_manager::Live_Close(long n)
{
	if (NULL == m_player)
	{
		return 0;
	}

	return m_player->Live_Close(n);
}

long player_manager::Live_Control(long n, long nCode, long argv0, long argv1)
{
	if (NULL == m_player)
	{
		return 0;
	}
	return m_player->Live_Control(n,nCode,argv0,argv1);
}

long player_manager::TV_open(LPCTSTR pDev, long hwnd, long nSignal)
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->TV_open(pDev,hwnd,nSignal);
}

long player_manager::TV_close()
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->TV_close();
}

long player_manager::TV_control(long nCode, long argv0, long argv1)
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->TV_control(nCode,argv0,argv1);
}

bool player_manager::get_volume_tune(int &music_volume,int &microphone_volume,int &tune)
{
	music_volume = m_card_amplifier_volume;
	microphone_volume = m_microphone_volume;
	tune = m_tune;
	return true;
}

bool player_manager::get_card_amplifier_volume_temp(int &nVolume)
{
	nVolume = m_card_amplifier_volume_temp;
	return true;
}

bool player_manager::get_music_volume_info(int &music_max,int &music_min,int &music_step)
{
	try
	{
		music_max = m_music_volume_max;
		music_min = m_music_volume_min;
		music_step = m_music_volume_step;
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool player_manager::get_microphone_volume_info(int &microphone_max,int &microphone_min,int &microphone_step)
{
	try
	{
		microphone_max = m_microphone_volume_max;
		microphone_min = m_microphone_volume_min;
		microphone_step = m_microphone_volume_step;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

int player_manager::get_player_state(void)
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->get_state();
}

long player_manager::get_total_time_length()
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->get_total_time_length();
}

long player_manager::get_play_time_length()
{
	if (NULL==m_player)
	{
		return 0;
	}
	return m_player->get_play_time_length();
}

void player_manager::seek(long pos)
{
	if (NULL==m_player)
	{
		return ;
	}
	return m_player->seek(pos);
}

bool player_manager::Set(long flag, long value)
{
	if (NULL==m_player)
	{
		return false;
	}
	return m_player->Set(flag,value);
}

int player_manager::get_text_osd_play_state()
{
	return m_player->get_text_osd_play_state();
}

void WINAPI player_manager::volume_callback(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	try
	{
		int adjust_range=0;

		//计算调节的幅度
		adjust_range =  m_timer_max_set_volume/15;
		if (adjust_range<4)
		{
			adjust_range = 4;
		}
		//计算每次调节音量
		m_timer_cur_set_volume += adjust_range;
		if (m_timer_cur_set_volume>=m_timer_max_set_volume)
		{
			m_timer_cur_set_volume = m_timer_max_set_volume;
			//杀死定时器
			if (0!=m_timer_identifier)
			{
				timeKillEvent(m_timer_identifier);
				m_timer_identifier=0;
			}
		}
		//设置音量
		if (m_player)
		{
			m_player->set_volume(m_timer_cur_set_volume,m_timer_cur_set_volume);
		}

		//同时设置主线程音量
		CMixer mix;
		mix.SetVolume(CMixer::SPEAKERS, m_timer_cur_set_volume);
	}
	catch (...)
	{
		
	}
	return;
}

PLAY_SONG_TYPE player_manager::get_playing_video_type(void)
{
	return m_playing_song_info.get_video_type();
}

void player_manager::set_playing_video_type(PLAY_SONG_TYPE video_type)
{
	m_playing_song_info.set_video_type(video_type);

	return;
}

int player_manager::compute_sound_card_volume(void)
{
	int lr_volume=0;
	int mid_volume = (m_music_volume_max+m_music_volume_min)/2;
	int half_value = (m_music_volume_max-m_music_volume_min)/2;

	if (m_adjust_amplifier)
	{
		//调整功放，神龙卡就用歌曲默认值
		lr_volume = m_song_volume;
	}
	else
	{
		//通过歌曲默认音量计算神龙卡音量
		if ((0==m_card_amplifier_volume)||(m_music_volume_min==m_card_amplifier_volume))
		{
			lr_volume = 0;
		}
		else if (m_card_amplifier_volume<=mid_volume)
		{
			//公式：(歌曲音量-歌曲音量*(50-神龙卡音量（默认50）)/50)*百分比
			lr_volume = (m_song_volume-(m_song_volume-m_music_volume_min)*(mid_volume-m_card_amplifier_volume)/half_value)*m_volume_adjust_percentage/100;
		}
		else
		{
			//公式：(歌曲音量+（歌曲最大音量-歌曲音量）*（神龙卡音量-50）/50)*百分比
			lr_volume = (m_song_volume+(m_music_volume_max-m_song_volume)*(m_card_amplifier_volume-mid_volume)/half_value)*m_volume_adjust_percentage/100;
		}
	}

	return lr_volume;
}

bool player_manager::get_playing_song_video_path(TCHAR *path)
{
	try
	{
		if (NULL==path)
		{
			return false;
		}
		_tcscpy(path,m_playing_song_path);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void player_manager::output_music_volume(void)
{
	try
	{

		//改为非静音状态
		m_mute=false;

		if (!m_adjust_amplifier)
		{
			//如果不是调整公放音量，就改变卡的音量
			m_timer_max_set_volume = m_cur_card_song_volume;
		}
		else
		{
			//神龙卡的默认值
			//m_timer_max_set_volume = m_card_default_value;
			//调节功放时，每首歌曲设置神龙卡的音量都不一样
			m_timer_max_set_volume = m_cur_card_song_volume;
			m_card_default_value = m_cur_card_song_volume;
		}

		//杀死原有的定时器
		if (0!=m_timer_identifier)
		{
			timeKillEvent(m_timer_identifier);
			m_timer_identifier=0;
		}
		m_timer_cur_set_volume = 0;
		//启动定时器，设置音量淡入淡出
		m_timer_identifier = timeSetEvent(200,0,volume_callback,0,TIME_CALLBACK_FUNCTION|TIME_PERIODIC);

		return;
	}
	catch (...)
	{

	}
	return;
}

void player_manager::set_help_sing_and_mark(SCORE_SYSTEM use_score_system)
{
	try
	{

		if (NULL==m_player)
		{
			return;
		}
		if (m_use_help_sing&&(!m_help_sing_card_name.empty()))
		{
			//启用了助唱功能，设置声卡名字
			m_player->Set(SD_LEADING_AUDIOCARD,(long)m_help_sing_card_name.c_str());
		}

		//启用评分
		open_score(use_score_system,true);
		//open_score(use_score_system,m_use_song_mark);
		return; 
	}
	catch (...)
	{
		
	}
	return;
}


bool player_manager::open_score(SCORE_SYSTEM use_score_system,bool state)
{
	if (m_player&&(SCORE_SYSTEM_SHINE==use_score_system))
	{
		if (state)
		{
			//m_use_song_mark = true;
			//启用打分功能
			m_player->Set(SD_SCORE_ONOFF,1);

			if (m_show_score_line)
			{
				WriteLog(__FL__, L"设置显示平分线!");
				m_player->Set(SD_SET_SCORE_LINE_ONOFF,1);
			}else{
				WriteLog(__FL__, L"设置不显示平分线!");
				m_player->Set(SD_SET_SCORE_LINE_ONOFF,0);
			}
		}
		else
		{
			//m_use_song_mark = false;
			//关闭评分功能
			m_player->Set(SD_SCORE_ONOFF,0);
		}
		return true;
	}

	return false;
}

int player_manager::get_sing_score(void)
{
	int score=-1;

	if (m_use_song_mark)
	{
		//启用了打分功能
		score = m_player->Get(SD_GET_SCORE);
	}

	return score;
}

void player_manager::close_video_file(void)
{
	if (m_player)
	{
		m_player->close_file();
	}
}

bool player_manager::get_playing_video(song_info &video_info)
{
	video_info = m_playing_song_info;

	return true;
}
bool player_manager::get_channel_memory()
{
	return m_channel_memory;
}
void player_manager::enter_guid_song(bool is_original)
{

	try
	{
		if (m_player)
		{
			int volume = 0;

			volume = m_cur_card_song_volume/15;
			if (volume<=0)
			{
				volume = 1;
			}

			set_help_sing_track(SD_GUIDE_AUDIO, is_original);
			//开启导唱
			m_player->Set(SD_GUIDE_ONOFF,1);
			if (is_original)
			{
				volume += 3;
				if (volume >= 10)
				{
					volume = 10;
				}
			}
			else
			{
				volume -= 1;
				if (volume <= 0)
				{
					volume = 1;
				}
			}
			//设置导唱音量
			m_player->Set(SD_GUIDE_VOLUME,volume);
			
		}

		return;
	}
	catch(...)
	{

	}
	return;
}

/*
void player_manager::enter_guid_song(bool is_original)
{

	try
	{
		if (m_player)
		{
			int volume = 0;

			volume = m_cur_card_song_volume/10;
			if (volume<=0)
			{
				volume = 1;
			}
			//set_help_sing_track(false);
			//开启导唱
			m_player->Set(SD_GUIDE_ONOFF,1);
			//设置导唱音量
			m_player->Set(SD_GUIDE_VOLUME,volume);
		}

		return;
	}
	catch(...)
	{

	}
	return;
}
*/

void player_manager::exit_guid_song(void)
{
	try
	{
		if (m_player)
		{
			//退出导唱
			m_player->Set(SD_GUIDE_ONOFF,0);
			//设置导唱音量
			m_player->Set(SD_GUIDE_VOLUME,0);
		}
	}
	catch (...)
	{
		
	}
	return;
}
void player_manager::set_show_score_line(bool line /* = false */)
{
	m_show_score_line = line;
}

void player_manager::Set_fre_spectrumsitify_hwnd(HWND hwnd)
{
	m_player->Set(SD_WP_SetFreSpectrumsitify_HWND, (long)hwnd);
}

void player_manager::Set_fre_spectrumsitify_spec(int spec)
{
	m_player->Set(SD_WP_SetFreSpectrumsitify_Spec, spec);
}

void player_manager::set_use_song_mark(bool flag)
{
	m_use_song_mark = flag;
}
#include "StdAfx.h"
#include ".\player_manager.h"
#include "..\common\Register.h"
#include "..\file\config_file.h"
#include "..\file\log.h"
#include "..\folder_name.h"
#include "..\parserxml\ParserXml.h"
#include "..\common\Mixer.h"

player *m_player=NULL;          //��Ƶ������
int m_timer_cur_set_volume=0;   //��ʱ����ǰ���õ�����
int m_timer_max_set_volume=0;   //��ʱ��Ӧ�����õ��������
MMRESULT m_timer_identifier=0;  //��ʱ���ľ��

#pragma warning(disable: 4311)

player_manager::player_manager(void)
{
	m_player = NULL;
	m_playing = true;
	m_channel=true;
	m_enjoyment=false;
	m_mute=false;
	m_song_volume=0;         //�������� 
	m_microphone_volume=0;   //��˷������
	m_tune=0;
	m_play_DJ = false;
	m_music_volume_max=100;     //�������������ֵ
	m_music_volume_min=0;     //������������Сֵ
	m_music_volume_step=5;    //���������Ĳ���

	m_microphone_volume_max=100;  //��˷����������ֵ
	m_microphone_volume_min=0;  //��˷���������Сֵ
	m_microphone_volume_step=5; //��˷������Ĳ���

	m_tune_max=5;               //���������ֵ
	m_tune_min=-5;               //��������Сֵ
	m_tune_step=1;              //�����Ĳ���
	m_tune_original=0;
	m_play_video_ad = false;
	memset(m_playing_song_path,0x0,sizeof(m_playing_song_path));
	memset(m_video_ad_path,0x0,sizeof(m_video_ad_path));
	m_show_video_window_exist = false;
	m_video_window_handle = NULL;
	m_use_stream_control_service=false;
	m_check_file_exist=false;
	m_timer_identifier=0;
	m_reverberation_default_value=5; //����Ĭ��ֵ
	m_reverberation_min_value=0;     //������Сֵ
	m_reverberation_max_value=10;     //�������ֵ
	m_reverberation_value=5;         //����ֵ
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
	//ע�Ქ�����ؼ�
	result = register_ocx(L"hplayerua.ocx",false);
	//ע���ƽ�ؼ�
	result = register_ocx(L"LT.dll",false);
	//ע��flash���ſؼ�
	result = register_ocx(L"Flash10c.ocx",false);
	//ע��ax�ؼ�
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

	//��¼����
	m_show_video_window_exist = window_exist;
	m_video_window_handle = show_handle;
	m_parent_window_handle = parent_handle;

	if (m_player)
	{
		//��ʼ�����ſؼ�
		result = m_player->initialize();
		
        if (m_show_video_window_exist)
		{
			//�ı俨�Ľ��뷽ʽ��֧�ֻ����
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
		//�ı俨�Ľ��뷽ʽ��֧�ֻ����
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

		//��ʼ��osd
		result = m_player->InitOSD();
		if (!result)
		{
			WriteLog(__FL__, L"��ʼ��OSDʧ��");
		}
	}
	else
	{
		WriteLog(__FL__, L"m_playerΪ�գ�");
	}
	//��ʼ������
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

	//����
	m_reverberation_default_value = config_file.read_integer(L"reverberation",L"reverberation_default_value",50);
	m_reverberation_min_value = config_file.read_integer(L"reverberation",L"reverberation_min_value",0);
	m_reverberation_max_value = config_file.read_integer(L"reverberation",L"reverberation_max_value",100);
	m_reverberation_step = config_file.read_integer(L"reverberation",L"reverberation_step",5);
	m_reverberation_value = m_reverberation_default_value;

	//�����������ڰٷֱ�
	m_volume_adjust_percentage=config_file.read_integer(L"amplifier",L"volume_adjust_percentage",100);
	m_adjust_amplifier = config_file.read_boolean(L"amplifier",L"adjust_amplifier_volume",false);
	//�õ�������Ĭ��ֵ
	m_card_default_value = config_file.read_integer(L"amplifier",L"amplifier_volume",50);
	m_card_amplifier_volume = m_card_default_value;
	m_cur_card_song_volume = m_card_amplifier_volume;

	//�õ����и�������
	m_idle_song_volume = config_file.read_integer(L"public_video",L"idlesse_volume",50);

	//�õ����ӵ�����
	m_default_tv_volume = config_file.read_integer(L"amplifier",L"default_tv_volume",50);
	
	//�����Ƿ����
	m_volume_memory = config_file.read_boolean(L"amplifier",L"volume_memory",false);
	if(m_volume_memory)
	{
		WriteLog(__FL__, L"ʹ���������书��");
	}
	//��������
	m_channel_memory = config_file.read_boolean(L"amplifier",L"channel_memory",false);
	if (m_channel_memory)
	{
		WriteLog(__FL__, L"ʹ��ԭ�鳪���书��");
	}

	//ʹ�����ط���
	m_use_stream_control_service = config_file.read_boolean(L"control",L"use_stream_control_service",false);
	if(m_use_stream_control_service)
	{
		WriteLog(__FL__, L"ʹ�����ط���");
	}

	//�Ƿ�ÿ�ζ�����ļ�����
	m_check_file_exist = config_file.read_boolean(L"control",L"check_file_exist",false);
	if (m_check_file_exist)
	{
		WriteLog(__FL__, L"���ü���ļ��Ƿ���ڵĻ���");
	}
	//����
	m_use_help_sing = config_file.read_boolean(L"help_sing",L"use_help_sing",false);
	m_help_sing_card_name = config_file.read_string(L"help_sing",L"help_sing_card",L"");

	/*
	//���ô�ֹ���
	m_use_song_mark = config_file.read_boolean(L"mark",L"use_mark",false);
	if (m_use_song_mark)
	{
		WriteLog(__FL__, L"���ø�����ֹ���");
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
			//���û�����������У�ֱ�ӷ���
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
			//�ı俨�Ľ��뷽ʽ��֧�ֻ����
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
	//��¼��ǰ���ڲ��ŵ���Ƶ��Ϣ
	m_playing_song_info = video_info;

	if (m_player)
	{
		long result = 0;
		//�ر��ļ�
		m_player->close_file();

		m_player->set_play_file_path(szVideoPath);
		//�������õ���Ƶ�ļ�·��
		memset(m_playing_song_path,0x0,sizeof(m_playing_song_path));
		_tcscpy(m_playing_song_path, szVideoPath);

		set_help_sing_track(SD_ORIGNAL_AUDIO, false);

		//����Ĭ�Ϲرգ����õ���֮ǰ����������ԭ������
		m_player->Set(SD_GUIDE_ONOFF,0);
		//Ĭ��������0
		m_player->Set(SD_GUIDE_VOLUME,0);

		//����Ƶ�ļ�
		result = m_player->open_file();
		if (result<=0)
		{
			return false;
		}

		set_help_sing_track(SD_GUIDE_AUDIO, false);

		//���Ÿ�����ʾosd
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

		//�����Ƿ񲥷Ź���ʶ
		m_play_video_ad = false;

		//��¼��ǰ���ڲ��ŵ���Ƶ��Ϣ
		m_playing_song_info = video_info;
		//��ֹͣ���ŵ���Ƶ��Ȼ��������Ҫ������Ƶ�ļ���·��
		//m_player->stop();

		//�����ֶ����ؾ��� -- add by caizw
		m_playing_song_info.set_server_manually_idx(m_server_manually);

		//�ر��ļ�
		m_player->close_file();
		if(m_use_stream_control_service)
		{
			//ʹ�����ط���
			TCHAR song_number[128];
			TCHAR server_ip[32];

			memset(song_number,0x0,sizeof(song_number));
			memset(server_ip,0x0,sizeof(server_ip));

			//�õ��������
			ret = m_playing_song_info.get_song_id(song_number);
			if (!ret || (0==_tcscmp(song_number,L"")))
			{
				return false;
			}
			//�õ�����IP
			ret = m_playing_song_info.get_server_ip(server_ip);
			if (!ret || (0==_tcscmp(server_ip,L"")))
			{
				return false;
			}
			swprintf(video_stream_path,L"vod:// %s @ %s",song_number,server_ip+2);
			//������ʽ�ļ�·��
			m_player->set_play_file_path(video_stream_path);
			WriteLog(__FL__, L"������ʽ�ļ�·��");
			WriteLog(__FL__, video_stream_path);
		}
		else
		{
			//�õ���Ƶ�ļ���·��
			ret = m_playing_song_info.get_path(file_path,m_check_file_exist,link_server);		

			if (!ret || (0==_tcscmp(file_path,L"")))
			{
				WriteLog(__FL__, L"����ļ�·������");
				return false;
			}

			//������Ƶ�ļ���·��
			WriteLog(__FL__, L"���õ��ļ�·��");
			WriteLog(__FL__, file_path);	

			m_player->set_play_file_path(file_path);
			//�������õ���Ƶ�ļ�·��
			memset(m_playing_song_path,0x0,sizeof(m_playing_song_path));
			_tcscpy(m_playing_song_path,file_path);
		}
		//����¼���ļ�
		song_type = m_playing_song_info.get_video_type();
		if (PLAY_SONG_TYPE_RECORDER_SONG==song_type)
		{
			//�����¼�ĸ�����Ҫͬʱ����¼��
			result = m_playing_song_info.get_wave_path(wave_path);
			if (result && _tcscmp(wave_path, L"") != 0)
			{
				m_player->SetGszWavFileName(wave_path);
			}            
		}//add by yzg @2015-5-29
		else if (PLAY_MUSIC_ENJOY == song_type)
		{
			//������������͸�����Ҫͬʱ����MP3����
			result = m_playing_song_info.get_song_relative_path(wave_path);
			if (result && _tcscmp(wave_path, L"") != 0 && PathFileExists(wave_path))
			{
				m_player->SetGszWavFileName(wave_path);
			}
		}//add end
#ifndef ONLY_PLAY_KARAOKE_TRACK  //ֻ����ԭ������
		if (m_channel_memory&&(PLAY_SONG_TYPE_IDLESSE==song_type))
		{
			//����ǿ��и�������������������ȥ������״̬
			m_enjoyment = false;
		}
#endif
		//2011-12-02 modify ����Ϊÿ�׸�����Ҫ���õ��������Ա�������ԭ������
		//if (m_use_song_mark || (m_use_help_sing && (!m_help_sing_card_name.empty())))
		{
			//�����˴�ֹ��ܡ��������ܡ��������ܣ�����ԭ������
			//
			//set_help_sing_track(SD_ORIGNAL_AUDIO, use_guid);
			set_help_sing_track(SD_ORIGNAL_AUDIO, false);   //��������
			if (1 == use_guid)
			{
			   set_help_sing_track(SD_GUIDE_AUDIO, true);   //���ɵ���
			}
			//set_help_sing_track(SD_GUIDE_AUDIO, false);
		}
		//����Ĭ�Ϲرգ����õ���֮ǰ����������ԭ������
		m_player->Set(SD_GUIDE_ONOFF,0);
		//Ĭ��������0
		m_player->Set(SD_GUIDE_VOLUME,0);
		//ֻ����ѡ�����ű������
		if ((0!=_tcscmp(voice_save_path,L"")) && (PLAY_SONG_TYPE_SELECT_SONG==m_playing_song_info.get_video_type()))
		{
			m_player->Set(SD_SET_RECORD_FILE,(long)voice_save_path);
			WriteLog(__FL__, L"������ѡ������������·��:");
			WriteLog(__FL__, voice_save_path);
		}else{
			WriteLog(__FL__, L"û��������ѡ������������·��");
		}

		if ((0!=_tcscmp(music_save_path,L""))&&(PLAY_SONG_TYPE_SELECT_SONG==m_playing_song_info.get_video_type()))
		{
			//�õ���������
			result = m_playing_song_info.get_channel_track(false,channel_track);
			if (result)
			{
				//ת��������
				if (_tcscmp(channel_track, L"��")==0)
				{
					//���ó�������
					_tcscpy(channel_track,L"L");
				}
				else if (_tcscmp(channel_track, L"��")==0)
				{
					//���ó�������
					_tcscpy(channel_track,L"R");
				}
			}

			//����¼���ļ�����·��
			if (1 == m_tape_mode  && PLAY_SONG_TYPE_SELECT_SONG == song_type/*&& PLAY_SONG_TYPE_RECORDER_SONG==song_type*/)
			{	
				swprintf(music_wave_path,L"%s=%s",channel_track,music_save_path);
				m_player->Set(SD_DUMP_AUDIO,(long)music_wave_path);
				WriteLog(__FL__, L"������ѡ���������·��:");
				WriteLog(__FL__, music_wave_path);
			}else{
				WriteLog(__FL__, L"û��������ѡ���������·��");
			}
		}
		if (is_scoring&&(PLAY_SONG_TYPE_SELECT_SONG==m_playing_song_info.get_video_type()))   //�����������
		{
			//ѡ���������
			open_score(SCORE_SYSTEM_SHINE,true);
			//open_score(SCORE_SYSTEM_SHINE,m_use_song_mark);
		}
		else
		{
			//���и���������
			open_score(SCORE_SYSTEM_SHINE,false);
		}
		//����Ƶ�ļ�
		result = m_player->open_file();
		if (result<=0)
		{
			return false;
		}

		//���Ÿ�����ʾosd
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
			//���ɵ���
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
			//��������
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
			//ת��������
			if (_tcscmp(channel_track, L"��")==0)
			{
				//���ó�������
				m_player->Set(command,'L');
			}
			else if (_tcscmp(channel_track, L"��")==0)
			{
				//���ó�������
				m_player->Set(command,'R');
			}
			else
			{
				int volume_track = _ttoi(channel_track);
				if (volume_track < 0)
				{
					volume_track = 2;
				}
				//��������
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

		//�����Ƿ񲥷Ź���ʶ
		m_play_video_ad = true;
		//������·��
		memset(m_video_ad_path,0x0,sizeof(m_video_ad_path));
		_tcscpy(m_video_ad_path,path);

		//��ֹͣ���ŵ���Ƶ��Ȼ��������Ҫ������Ƶ�ļ���·��
		//m_player->stop();
		m_player->close_file();
		//������Ƶ�ļ���·��
		m_player->set_play_file_path(path);
		//����Ƶ�ļ�
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

		//��ʼ����
		m_player->play();
		//�õ������ŵ���Ƶ����
		playing_video_type = get_playing_video_type();

		m_playing=true;
		if (m_play_video_ad)
		{
			//���Ź���Ĭ��ֵ
			m_channel = true;
			m_song_volume = m_idle_song_volume;
			
			if (!m_volume_memory || (lock_public_volume&&(PLAY_SONG_TYPE_IDLESSE==playing_video_type)))
			{
				//���������������õ�ֵ����������������������и���Ҳ������
				//m_card_amplifier_volume = m_song_volume;   //2011-12-29 modify
				m_card_amplifier_volume = (m_music_volume_max+m_music_volume_min)/2;
			}

			//�õ�ʵ��Ҫ���ø���������
			m_cur_card_song_volume = compute_sound_card_volume();

			if (!m_mute || !cancel_mute)
			{
				//ȡ�����������õ����ķ�ʽ�������
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
				//����״̬��ԭ��
				m_channel = true;
			}
			else
			{
				//�����ǰ鳪��ʼ
				m_channel = false;
			}
			//��������
			result = m_playing_song_info.get_channel_track(m_channel,channel_track);
			if (result)
			{
				//ת��������
				if (_tcscmp(channel_track, L"��")==0)
				{
					//���ó�������
					m_player->balance(2);
				}
				else if (_tcscmp(channel_track, L"��")==0)
				{
					//���ó�������
					m_player->balance(1);
				}
				else
				{
					int volume_track = _ttoi(channel_track);
					if (volume_track < 0)
					{
						if (m_channel)
						{
							// ԭ������Ϊ��ֵ
							volume_track = 2;
						}
						else
						{
							// �鳪����Ϊ��ֵ
							volume_track = 1;
						}
					}
					//��������
					m_player->set_track(volume_track);
				}
			}
			//�õ�����
			m_song_volume = m_playing_song_info.get_volume(m_channel);
			if(m_song_volume<=0)
			{
				//¼���ط�û������
				//����������������ھͲ��ÿ��и�������
				m_song_volume = m_idle_song_volume + 20;
				if (m_song_volume > 100)
				{
					m_song_volume = 90;
				}				
				//m_song_volume = 60;
			}

			//�жϵ�ǰ�Ƿ��ǲ��ŵ���
			if(PLAY_TV == playing_video_type)
			{
				//�����ǰ�ǲ��ŵ���
				m_song_volume = m_default_tv_volume;
			}

			//���������Сֵ������һ�°ٷֱ�
			m_song_volume = m_music_volume_min+m_song_volume*(m_music_volume_max-m_music_volume_min)/100;

			if (PLAY_SONG_TYPE_SELECT_SONG==m_pre_video_type)
			{
				//ǰһ��Ƶ��ѡ��ĸ���Ҫ��¼��������
				m_select_song_volume = m_card_amplifier_volume;
			}
			
			if (PLAY_SCORE_VIDEO!=playing_video_type)
			{
				//����Ǵ����Ƶ�����ı������������Ƶ��ǰһ����Ƶ����Ϊһ������
				if (lock_public_volume)
				{
					//����������Ƶ
					if (m_volume_memory&&(PLAY_SONG_TYPE_IDLESSE!=m_pre_video_type)&&(PLAY_SONG_TYPE_IDLESSE!=playing_video_type)&&(m_select_song_volume>0))
					{
						//����,������һ����ѡ��������
                        m_card_amplifier_volume = m_select_song_volume;
					}
					else
					{
						//������,�������ݿ�����
						//m_card_amplifier_volume = m_song_volume;   //2011-12-29 modify
						m_card_amplifier_volume = (m_music_volume_max+m_music_volume_min)/2;
					}
				}
				else
				{
					//��������������
					if (!m_volume_memory|| m_adjust_amplifier)
					{
						//���������������õ�ֵ����������������������и���Ҳ������
						//m_card_amplifier_volume = m_song_volume;   //2011-12-29 modify
						m_card_amplifier_volume = (m_music_volume_max+m_music_volume_min)/2;
					}
				}
				//����ǰһ����Ƶ����
				m_pre_video_type = playing_video_type;
			}
			//�õ�ʵ��Ҫ���ø���������
			m_cur_card_song_volume = compute_sound_card_volume();

			//if (!m_mute || cancel_mute)
			if (!m_mute)
			{
				//ȡ�����������õ����ķ�ʽ�������
				output_music_volume();
			}
			else
			{
				m_player->set_volume(0,0);
				m_mute=true;
			}	

			//���ñ��Ͷ�
			video_property = m_playing_song_info.get_video_saturation();
			if (video_property>10)
			{
				m_player->set_saturation(video_property);
			}
			//��������
			video_property = m_playing_song_info.get_video_luminance();
			if (video_property>10)
			{
				m_player->set_bright(video_property);
			}
			//���öԱȶ�
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
		//���ڲ���,��ͣ
		pause();
	}
	else
	{
		result = is_mute();
		if (!result)
		{
			//���Ǿ�����Ҫ�Ⱦ�����Ȼ����õ����ķ�ʽ���
			mute();
		}
		//��ͣ����ʼ����
		play();
		if (!result && m_mute)
		{
			//ȡ�����������õ����ķ�ʽ�������
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

		//�õ���ǰ���ڲ��ŵ���Ƶ�ļ�·��
		if (m_play_video_ad)
		{
			//���
			_tcscpy(file_path,m_video_ad_path);
		}
		else
		{
			//��ͨ����
			_tcscpy(file_path,m_playing_song_path);
		}

		//����¼���ļ�
		song_type = m_playing_song_info.get_video_type();
		if (PLAY_SONG_TYPE_RECORDER_SONG==song_type)
		{
			//�����¼�ĸ�����Ҫͬʱ����¼��
			result = m_playing_song_info.get_wave_path(wave_path);
			if (result)
			{
				m_player->SetGszWavFileName(wave_path);
			}            
		}//add by yzg @2015-5-29
		else if (PLAY_MUSIC_ENJOY == song_type)
		{
			//������������͸�����Ҫͬʱ����MP3����
			result = m_playing_song_info.get_song_relative_path(wave_path);
			if (result && _tcscmp(wave_path, L"") != 0 && PathFileExists(wave_path))
			{
				m_player->SetGszWavFileName(wave_path);
			}
		}//add end

		//��ֹͣ���ŵ���Ƶ��Ȼ��������Ҫ������Ƶ�ļ���·��
		//m_player->stop();
		m_player->close_file();
		//������Ƶ�ļ���·��
		m_player->set_play_file_path(file_path);
		//2011-12-02 modify ����Ϊÿ�׸�����Ҫ���õ��������Ա�������ԭ������
		//if (m_use_song_mark || (m_use_help_sing && (!m_help_sing_card_name.empty())))
		{
			//�����˴�ֹ��ܡ��������ܡ��������ܣ�����ԭ������
			//set_help_sing_track(SD_ORIGNAL_AUDIO, use_guid);
			set_help_sing_track(SD_ORIGNAL_AUDIO, false);
			//set_help_sing_track(SD_GUIDE_AUDIO, false);
		}
		//����Ĭ�Ϲرգ����õ���֮ǰ����������ԭ������
		m_player->Set(SD_GUIDE_ONOFF,0);
		//Ĭ��������0
		m_player->Set(SD_GUIDE_VOLUME,0);
		//ֻ����ѡ�����ű������
		if (0!=_tcscmp(voice_save_path,L""))
		{
			m_player->Set(SD_SET_RECORD_FILE,(long)voice_save_path);
		}
		if ((0!=_tcscmp(music_save_path,L""))&&(PLAY_SONG_TYPE_SELECT_SONG==m_playing_song_info.get_video_type()))
		{
			//�õ���������
			result = m_playing_song_info.get_channel_track(false,channel_track);
			if (result)
			{
				//ת��������
				if (_tcscmp(channel_track, L"��")==0)
				{
					//���ó�������
					_tcscpy(channel_track,L"L");
				}
				else if (_tcscmp(channel_track, L"��")==0)
				{
					//���ó�������
					_tcscpy(channel_track,L"R");
				}
			}
			//����¼���ļ�����·��
			if (1 == m_tape_mode)
			{	 
				//����¼���ļ�����·��
				swprintf(music_wave_path,L"%s=%s",channel_track,music_save_path);
				m_player->Set(SD_DUMP_AUDIO,(long)music_wave_path);

			}

			////����¼���ļ�����·��
			//swprintf(music_wave_path,L"%s=%s",channel_track,music_save_path);
			//m_player->Set(SD_DUMP_AUDIO,(long)music_wave_path);
		}
		//����Ƶ�ļ�
		result = m_player->open_file();
		if (result<0)
		{
			return false;
		}

		set_help_sing_track(SD_GUIDE_AUDIO, use_guid);
		//if (m_mute)
		//{
			//ȡ�����������õ����ķ�ʽ�������
		//	output_music_volume();
		//}
	}
	return true;
}

void player_manager::mute(void)
{
	try
	{
		//ɱ��ԭ�еĶ�ʱ��
		if (0!=m_timer_identifier)
		{
			timeKillEvent(m_timer_identifier);
			m_timer_identifier=0;
		}

		if (m_mute)
		{
			//ȡ�����������õ����ķ�ʽ�������
			output_music_volume();
			WriteLog(__FL__, L"ȡ������");
		}
		else
		{
			//ԭ����ԭ�����ĳɾ���
			m_mute = true;
			if (m_player)
			{
				m_player->set_volume(0,0);
			}
			WriteLog(__FL__, L"���뾲��״̬");
		}
	}
	catch (...)
	{
		
	}
	return;
}

void player_manager::change_channel(long guid_track)
{
	//��������
	m_player->set_track(guid_track);
	guid_track = 1;
}

void player_manager::change_channel(void)
{
	bool result=false;
	TCHAR channel_track[16];
	
	memset(channel_track,0x0,sizeof(channel_track));

	WriteLog(__FL__, L"���������л�");

	if (m_channel)
	{
		//Ŀǰ��ԭ������Ϊ�鳪
		m_channel=false;
		m_enjoyment=false;
	}
	else
	{
		//Ŀǰ�ǰ鳪����Ϊԭ��
		m_channel=true;
		if (m_channel_memory)
		{
			//����ԭ�鳪
			m_enjoyment=true;
		}
	}

	//�ı�����
	result = m_playing_song_info.get_channel_track(m_channel,channel_track);
	if (result)
	{
		//ת��������
		if (_tcscmp(channel_track, L"��")==0)
		{
			//���ó�������
			m_player->balance(2);
		}
		else if (_tcscmp(channel_track, L"��")==0)
		{
			//���ó�������
			m_player->balance(1);
		}
		else
		{
			int volume_track = _ttoi(channel_track);
			if (volume_track < 0)
			{
				if (m_channel)
				{
					// ԭ������Ϊ��ֵ
					volume_track = 2;
				}
				else
				{
					// �鳪����Ϊ��ֵ
					volume_track = 1;
				}
			}
			//��������
			m_player->set_track(volume_track);
		}
	}
	//if (m_mute)
	//{
		//ȡ�����������õ����ķ�ʽ�������
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

		//����xml�ַ���
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
			if (1==item_value4)  //������ʾ�ĺ�ʵ��״̬�෴
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
<data ismute=��true�� istrack=��false�� music=��50�� isplay=��true��/>
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
			//�����ǲ���״̬����ťӦ������ͣ
			_tcscpy(play_state,L"false");
		}
		else
		{
			//����ʱ��ͣ״̬����ťӦ���ǲ���
			_tcscpy(play_state,L"true");
		}
		if (m_channel)
		{
			//������ԭ������ťӦ���ǰ鳪
			_tcscpy(track_state,L"false");
		}
		else
		{
			//�����ǰ鳪����ťӦ����ԭ��
			_tcscpy(track_state,L"true");
		}
		if (m_mute)
		{
			//����
			_tcscpy(mute_state,L"true");
			show_volumn = 0;
		}
		else
		{
            _tcscpy(mute_state,L"false");
			//������ʾ������
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

		//������ʾ������
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
			//�����ǲ���״̬����ťӦ������ͣ
			_tcscat(list_xml,L"<play pause=\"1\" play=\"0\" />");
		}
		else
		{
			//����ʱ��ͣ״̬����ťӦ���ǲ���
			_tcscat(list_xml,L"<play pause=\"0\" play=\"1\" />");
		}
		if (m_channel)
		{
			//������ԭ������ťӦ���ǰ鳪
			_tcscat(list_xml,L"<former yuan=\"0\" ban=\"1\" />");
		}
		else
		{
			//�����ǰ鳪����ťӦ����ԭ��
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
			//����
			_tcscat(list_xml,L"<enjoy enjoy1=\"0\" enjoy2=\"1\" />");
		}
		else
		{
			_tcscat(list_xml,L"<enjoy enjoy1=\"1\" enjoy2=\"0\" />");
		}
		if (m_mute)
		{
			//����
			_tcscat(list_xml,L"<mute mute1=\"0\" mute2=\"1\"/></panel_info>");
		}
		else
		{
			_tcscat(list_xml,L"<mute mute1=\"1\" mute2=\"0\"/></panel_info>");
		}

		//������ʾ������
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
		//��������״̬���ǰ鳪����ť��ʾԭ��
		m_enjoyment = false;
		m_channel = false;
	}
	else
	{
		//����״̬����ԭ������ťʽ�鳪
		m_enjoyment = true;
		m_channel = true;
	}

	//�ı�����
	result = m_playing_song_info.get_channel_track(m_channel,channel_track);
	if (result)
	{
		//ת��������
		if (_tcscmp(channel_track, L"��")==0)
		{
			//���ó�������
			m_player->balance(2);
		}
		else if (_tcscmp(channel_track, L"��")==0)
		{
			//���ó�������
			m_player->balance(1);
		}
		else
		{
			int volume_track = _ttoi(channel_track);
			if (volume_track < 0)
			{
				if (m_channel)
				{
					// ԭ������Ϊ��ֵ
					volume_track = 2;
				}
				else
				{
					// �鳪����Ϊ��ֵ
					volume_track = 1;
				}
			}
			//��������
			m_player->set_track(volume_track);
		}
	}
	//if (m_mute)
	//{
		//ȡ�����������õ����ķ�ʽ�������
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
//��������osd������Ĭ��Ϊ0 //yzg 2015-6-8
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

		if (fp) // �ļ�����ʱ��ִ�����¶�����
		{
			fclose(fp);	
			fp=NULL;
			m_player->PlayControlOSD(path, x_pos, y_pos);
		}
		else
		{
			// �������, �ر�����
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
		//ɱ����ʱ��
		if (0!=m_timer_identifier)
		{
			timeKillEvent(m_timer_identifier);
			m_timer_identifier=0;
		}

		//��¼ԭ�е�����
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
		case VOLUME_SET_FLAG:  //��������
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

		//�õ�ʵ��Ҫ���ø���������
		m_cur_card_song_volume = compute_sound_card_volume();

		if (!m_adjust_amplifier)
		{
			//������ǵ��������������͸ı俨������
			m_timer_max_set_volume = m_cur_card_song_volume;
			//������ʱ���������������뵭��
			m_timer_identifier = timeSetEvent(200,0,volume_callback,0,TIME_CALLBACK_FUNCTION|TIME_PERIODIC);
		}
		else
		{
			//��������Ĭ��ֵ
			m_player->set_volume(m_card_default_value,m_card_default_value);
		}
		if (set_volume == 0)
		{
			m_mute = true;
		}
		else
		{
			//�ĳɷǾ���״̬
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
	//����Ŀǰ��˷��ʵ������
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
		case REVERBERATION_UP_FLAG:   //�����
			{
				m_reverberation_value += m_reverberation_step;
				if (m_reverberation_value>m_reverberation_max_value)
				{
					m_reverberation_value = m_reverberation_max_value;
				}
			}
			break;
		case REVERBERATION_DOWN_FLAG: //�����
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

		//������ڵķ���
		adjust_range =  m_timer_max_set_volume/15;
		if (adjust_range<4)
		{
			adjust_range = 4;
		}
		//����ÿ�ε�������
		m_timer_cur_set_volume += adjust_range;
		if (m_timer_cur_set_volume>=m_timer_max_set_volume)
		{
			m_timer_cur_set_volume = m_timer_max_set_volume;
			//ɱ����ʱ��
			if (0!=m_timer_identifier)
			{
				timeKillEvent(m_timer_identifier);
				m_timer_identifier=0;
			}
		}
		//��������
		if (m_player)
		{
			m_player->set_volume(m_timer_cur_set_volume,m_timer_cur_set_volume);
		}

		//ͬʱ�������߳�����
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
		//�������ţ����������ø���Ĭ��ֵ
		lr_volume = m_song_volume;
	}
	else
	{
		//ͨ������Ĭ��������������������
		if ((0==m_card_amplifier_volume)||(m_music_volume_min==m_card_amplifier_volume))
		{
			lr_volume = 0;
		}
		else if (m_card_amplifier_volume<=mid_volume)
		{
			//��ʽ��(��������-��������*(50-������������Ĭ��50��)/50)*�ٷֱ�
			lr_volume = (m_song_volume-(m_song_volume-m_music_volume_min)*(mid_volume-m_card_amplifier_volume)/half_value)*m_volume_adjust_percentage/100;
		}
		else
		{
			//��ʽ��(��������+�������������-����������*������������-50��/50)*�ٷֱ�
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

		//��Ϊ�Ǿ���״̬
		m_mute=false;

		if (!m_adjust_amplifier)
		{
			//������ǵ��������������͸ı俨������
			m_timer_max_set_volume = m_cur_card_song_volume;
		}
		else
		{
			//��������Ĭ��ֵ
			//m_timer_max_set_volume = m_card_default_value;
			//���ڹ���ʱ��ÿ�׸�����������������������һ��
			m_timer_max_set_volume = m_cur_card_song_volume;
			m_card_default_value = m_cur_card_song_volume;
		}

		//ɱ��ԭ�еĶ�ʱ��
		if (0!=m_timer_identifier)
		{
			timeKillEvent(m_timer_identifier);
			m_timer_identifier=0;
		}
		m_timer_cur_set_volume = 0;
		//������ʱ���������������뵭��
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
			//�������������ܣ�������������
			m_player->Set(SD_LEADING_AUDIOCARD,(long)m_help_sing_card_name.c_str());
		}

		//��������
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
			//���ô�ֹ���
			m_player->Set(SD_SCORE_ONOFF,1);

			if (m_show_score_line)
			{
				WriteLog(__FL__, L"������ʾƽ����!");
				m_player->Set(SD_SET_SCORE_LINE_ONOFF,1);
			}else{
				WriteLog(__FL__, L"���ò���ʾƽ����!");
				m_player->Set(SD_SET_SCORE_LINE_ONOFF,0);
			}
		}
		else
		{
			//m_use_song_mark = false;
			//�ر����ֹ���
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
		//�����˴�ֹ���
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
			//��������
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
			//���õ�������
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
			//��������
			m_player->Set(SD_GUIDE_ONOFF,1);
			//���õ�������
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
			//�˳�����
			m_player->Set(SD_GUIDE_ONOFF,0);
			//���õ�������
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
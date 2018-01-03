#include "StdAfx.h"
#include ".\public_video_manager.h"
#include "..\file\file.h"
#include "..\file\config_file.h"
#include "..\folder_name.h"
#include "..\file\log.h"
#include <tchar.h>
#include <afx.h>

extern select_expr song_select_expr;

public_video_manager::public_video_manager(void)
{
	cur_idlesse_video_number=0;
	memset(m_idlesse_video_directory,0x0,sizeof(m_idlesse_video_directory));
	memset(m_install_path,0x0,sizeof(m_install_path));
	memset(m_atmosphere_video_path,0x0,sizeof(m_atmosphere_video_path));
	m_idlesse_video_volume = 0;
	m_idless_by_time_idx = -1;
	m_idlesse_video_type = false;
}

public_video_manager::~public_video_manager(void)
{
}

bool public_video_manager::initialize(TCHAR *ip)
{
	try
	{
		config_file_manager config_file;
		std::wstring folder_name;
		TCHAR video_path[256];
		int volume=0;
		TCHAR *install_path=NULL;
		CFileFind file_find;
		BOOL result=FALSE;
		CString file_path;
		CString file_title;

		cur_idlesse_video_number=0;
		m_idlesse_video_total_count=0;
		default_idlesse_video_count = 0;
		memset(m_idlesse_video_directory,0x0,sizeof(m_idlesse_video_directory));
		//��ʼ��
		begin_video.initialized_variables();
		for (int m=0;m<IDLESSE_VIDEO_MAX_NUMBER;m++)
		{
			idlesse_video[m].initialized_variables();
		}
		for (int m=0;m<IDLESSE_VIDEO_MAX_NUMBER;m++)
		{
			default_idlesse_video[m].initialized_variables();
		}
		end_video.initialized_variables();

		//�õ���װ·��
		GetModuleFileName(NULL, m_install_path, sizeof(m_install_path));
		install_path = _tcsrchr(m_install_path, _T('\\'));
		if (install_path)
		{
			install_path[0] = '\0';
		}

		m_relay_parameter = config_file.read_integer(L"room", L"set_relay_parameter", 0);
		//������Ƶ����
		m_idlesse_video_volume = config_file.read_integer(L"public_video",L"idlesse_volume",50);
		//2010-02-022 modifiy ���Է��ʷ������ϵĿ��и���
		folder_name = config_file.read_string(L"server",L"idlesse_video_path",L"");
		if (folder_name.empty())
		{
			//���Ϊ�գ����ʱ���·��
			//����·��
			swprintf(m_idlesse_video_directory,L"%s\\%s",m_install_path,g_folder_name[1]);
		}
		else
		{
			//2010-06-09 modify ֧�ֶ��������·��
			TCHAR server_video_path[6][256];
			int server_video_path_count=0;
			const TCHAR *pre_split_symbol=NULL;
			const TCHAR *split_symbol=NULL;
			int last_ip_value=0;
			int use_video_path=0;

			for (int i=0;i<6;i++)
			{
				memset(server_video_path[i],0x0,sizeof(server_video_path[i]));
			}

			//Ӣ�ķֺ��Ƿָ���
			split_symbol = _tcschr(folder_name.c_str(),';');
			if (split_symbol)
			{
				//���������·��������ip����һ��
				pre_split_symbol = folder_name.c_str();
				//��ʼ����
				split_symbol = _tcschr(pre_split_symbol,';');
				while (split_symbol&&(server_video_path_count<6))
				{
					_tcsncpy(server_video_path[server_video_path_count],pre_split_symbol,split_symbol-pre_split_symbol);
					server_video_path_count++;
					pre_split_symbol = split_symbol+1;
					split_symbol = _tcschr(pre_split_symbol,';');
				}
				//��¼���һ��·��
				if (server_video_path_count<6)
				{
					_tcscpy(server_video_path[server_video_path_count],pre_split_symbol);
					server_video_path_count++;
				}
				//����IP�����һ���ֽ�ѡ��һ�����и���������·��
				TCHAR *last_ip_byte = _tcsrchr(ip,'.');
				if (last_ip_byte)
				{
					swscanf(last_ip_byte+1,L"%d",&last_ip_value);
				}
				//����Ҫʹ�õķ�����·��
				if (server_video_path_count<=0)
				{
					use_video_path = 0;
				}
				else
				{
					use_video_path = last_ip_value%server_video_path_count;
				}
				_tcscpy(m_idlesse_video_directory,server_video_path[use_video_path]);
				//���������·��������ʹ�ñ���·��
				if (!PathFileExists(m_idlesse_video_directory))
				{
					//����·��
					swprintf(m_idlesse_video_directory,L"%s\\%s",m_install_path,g_folder_name[1]);
				}
			}
			else
			{
				//���ʷ�����·������һһ��
				_tcscpy(m_idlesse_video_directory,folder_name.c_str());
			}
		}

		//��Ƶ·����ʼ��
		memset(video_path,0x0,sizeof(video_path));
		swprintf(video_path,L"%s\\*.*",m_idlesse_video_directory);
		result = file_find.FindFile(video_path);
		while (result)
		{
			result = file_find.FindNextFile();

			if (file_find.IsCompressed()||file_find.IsDirectory()||file_find.IsDots()||file_find.IsHidden())
			{
				continue;
			}
			else if (file_find.IsSystem()||file_find.IsTemporary())
			{
				continue;
			}

			file_title = file_find.GetFileTitle();
			file_path = file_find.GetFilePath();
			if (L"��ʼ"==file_title)
			{
				begin_video.set_song_name(L"��ʼ");
				begin_video.set_local_path(file_path.GetBuffer(0));
			}
			else if (L"����"==file_title)
			{
				end_video.set_song_name(L"����");
				end_video.set_local_path(file_path.GetBuffer(0));
			}
			else
			{
				if (m_relay_parameter == 0) //�������Ҫʹ�ÿ���·������ֵ
				{
					//������и������ļ���
					default_idlesse_video[default_idlesse_video_count].set_song_name(file_title.GetBuffer(0));
					//������и������ļ�·��
					default_idlesse_video[default_idlesse_video_count].set_local_path(file_path.GetBuffer(0));
					//��������
					default_idlesse_video[default_idlesse_video_count].set_accompany_volume(m_idlesse_video_volume);
					default_idlesse_video[default_idlesse_video_count].set_karaoke_volume(m_idlesse_video_volume);
					//��������
					default_idlesse_video[default_idlesse_video_count].set_video_type(PLAY_SONG_TYPE_IDLESSE);
					default_idlesse_video_count++;
					if (default_idlesse_video_count>=IDLESSE_VIDEO_MAX_NUMBER)
					{
						break;
					}
				}
			}
		}

		//����ֱ��·��
		if (m_relay_parameter != 0)
		{
			idlesse_video[m_idlesse_video_total_count].set_video_type(PLAY_TV);
			TCHAR tv_url[MAX_PATH] = {0x00};
			int tv_play_mode = config_file.read_integer(L"TV", L"tv_play_mode", 2);
			bool topbox_mode = config_file.read_boolean(L"topbox_mode", L"TV", true);
			TCHAR sel_server_ip[32] = {0x00};
			TCHAR sel_server_port[16] = {0x00};
			swprintf(sel_server_ip, L"server_ip%d", m_relay_parameter);
			swprintf(sel_server_port, L"channel%d", m_relay_parameter);
			wstring server_ip = config_file.read_string(L"TV", sel_server_ip, L"");
			int server_port = config_file.read_integer(L"TV", sel_server_port, 0);
			if (topbox_mode)
			{
				if (tv_play_mode == TV_GROUP_PLAY_MODE)
				{
					swprintf(tv_url,L"shn://%s:%d",server_ip.c_str(),server_port);
				}else{
					//swprintf(tv_url,L"shn://%d@%s:4360",server_ip.c_str(),server_port);
					swprintf(tv_url,L"shn://%d@%s:4360",server_port, server_ip.c_str());
				}
			}
			else{
				swprintf(tv_url,L"hik://%d@%s",server_ip.c_str(),server_port);
			}
			idlesse_video[m_idlesse_video_total_count].set_local_path(tv_url);
			m_idlesse_video_total_count++;
		}else{
			for (int n = 0; n < default_idlesse_video_count; n++)
			{
				idlesse_video[n] = default_idlesse_video[n];
			}
			m_idlesse_video_total_count = default_idlesse_video_count;
		}

		//�õ�����·��
		swprintf(m_atmosphere_video_path,L"%s\\%s",m_install_path,g_folder_name[13]);
		//�õ�������Ƶ��·��
		swprintf(m_environment_audio_path,L"%s\\%s",m_install_path,g_folder_name[14]);

		//����
		volume = config_file.read_integer(L"public_video",L"begin_volume",50);
		begin_video.set_accompany_volume(volume);
		begin_video.set_karaoke_volume(volume);
		//��������
		begin_video.set_video_type(PLAY_SONG_TYPE_IDLESSE);

		//������������
		volume = config_file.read_integer(L"public_video",L"end_volume",50);
		end_video.set_accompany_volume(volume);
		end_video.set_karaoke_volume(volume);
		//��������
		end_video.set_video_type(PLAY_SONG_TYPE_IDLESSE);

		m_idless_by_time_count = 0;

		//�Ƿ�������ʱ�����ÿ��и���
		int open_idl_by_time = config_file.read_integer(L"idlesse_by_time", L"idless_time_open", 0);
		if (open_idl_by_time == 1) //����
		{
			wstring strIdlesse = config_file.read_string(L"idlesse_by_time", L"idlesse_time", L"");
			while (strIdlesse != L"")
			{
				int nPos = strIdlesse.find(L";");
				wstring strItem = strIdlesse.substr(0, nPos);
				
				strItem += L":";

				int idx = 0;
				while(strItem != L"")
				{
					int nSubPos = strItem.find(L":");
					wstring strSubItem = strItem.substr(0, nSubPos);
					switch(idx)
					{
					case 0:
						{
							m_idless_by_time[m_idless_by_time_count].iBegin = _ttoi(strSubItem.c_str());
						}
						break;
					case 1:
						{
							m_idless_by_time[m_idless_by_time_count].iEnd = _ttoi(strSubItem.c_str());
						}
						break;
					case 2:
						{
							//��Ƶ·����ʼ��
							memset(video_path,0x0,sizeof(video_path));
							swprintf(video_path,L"%s\\*.*",strSubItem.c_str());
							result = file_find.FindFile(video_path);
							int nCount = 0;
							while (result)
							{
								result = file_find.FindNextFile();

								if (file_find.IsCompressed()||file_find.IsDirectory()||file_find.IsDots()||file_find.IsHidden())
								{
									continue;
								}
								else if (file_find.IsSystem()||file_find.IsTemporary())
								{
									continue;
								}

								file_title = file_find.GetFileTitle();
								file_path = file_find.GetFilePath();
								m_idless_by_time[m_idless_by_time_count].SongInfo[nCount].set_song_name(file_title.GetBuffer(0));
								//������и������ļ�·��
								m_idless_by_time[m_idless_by_time_count].SongInfo[nCount].set_local_path(file_path.GetBuffer(0));
								//��������
								m_idless_by_time[m_idless_by_time_count].SongInfo[nCount].set_accompany_volume(m_idlesse_video_volume);
								m_idless_by_time[m_idless_by_time_count].SongInfo[nCount].set_karaoke_volume(m_idlesse_video_volume);
								//��������
								m_idless_by_time[m_idless_by_time_count].SongInfo[nCount].set_video_type(PLAY_SONG_TYPE_IDLESSE);
								nCount++;
								if (nCount>=IDLESSE_VIDEO_MAX_NUMBER)
								{
									break;
								}
							}
							m_idless_by_time[m_idless_by_time_count].iCount = nCount;
						}
						break;
					}
					idx++;
					strItem = strItem.erase(0, nSubPos + 1);
				}
				m_idless_by_time_count++;
				strIdlesse = strIdlesse.erase(0, nPos + 1);
			}
		}
		//�رղ���
		file_find.Close();
	}
	catch (...)
	{
		
	}
	return false;
}

void public_video_manager::query_idlesse_song_info(DB_Query &db_query_class)
{
	try
	{
		query_condition temp_song_query_condition[1];
		std::wstring *result_set=NULL;
		int row=0;
		int value=0;
		TCHAR song_name[256];
		bool result=false;

		if (m_relay_parameter > 0)
		{
			idlesse_video[0].set_song_id(L"999901");
			idlesse_video[0].set_song_name(L"ֱ��");
			idlesse_video[0].set_video_type(PLAY_SONG_TYPE_IDLESSE);
			return;
		}

		//����ռ�
		result_set = new std::wstring[song_select_expr.result_column_nums];
		if (NULL==result_set)
		{
			return;
		}
		for (int i=0;i<m_idlesse_video_total_count;i++)
		{
			//�õ����и�������
			memset(song_name,0x0,sizeof(song_name));
			result = idlesse_video[i].get_song_name(song_name);
			if (!result || (_tcslen(song_name)>=16))
			{
				continue;
			}
			//�ò�ѯ����
			temp_song_query_condition[0].column_name = L"song_id";
			temp_song_query_condition[0].operation_symbols = L"=\'";
			temp_song_query_condition[0].expression = song_name;
			temp_song_query_condition[0].wildcard = L"\'";

			//�õ�������Ϣ
			row = db_query_class.query_db_get_table_data(result_set,song_select_expr.result_column_expr.c_str(),temp_song_query_condition,1,song_select_expr.result_column_nums,1,0);
			if (row<=0)
			{
				continue;
			}

			//����xml���õ�������Ϣ �����ͱ���·��Ҫ����ԭ�еĲ����滻
			idlesse_video[i].set_song_id(result_set[0].c_str());
			idlesse_video[i].set_accompany_sing_track(result_set[1].c_str());
			idlesse_video[i].set_karaoke_track(result_set[2].c_str());
			idlesse_video[i].set_guid_track(result_set[3].c_str());
			idlesse_video[i].set_song_name(result_set[4].c_str());
			idlesse_video[i].set_movie_name(result_set[5].c_str());
			value = 0;
			swscanf(result_set[6].c_str(),L"%d",&value);
			idlesse_video[i].set_song_sort(value);
			//value = 0;
			//swscanf(result_set[7].c_str(),L"%d",&value);
			//idlesse_video[i].set_accompany_volume(value);
			//value = 0;
			//swscanf(result_set[8].c_str(),L"%d",&value);
			//idlesse_video[i].set_karaoke_volume(value);
			idlesse_video[i].set_language(result_set[9].c_str());
			idlesse_video[i].set_song_type(result_set[10].c_str());
			idlesse_video[i].set_singer_name(result_set[11].c_str());
			idlesse_video[i].set_singer_sex(result_set[12].c_str());
			idlesse_video[i].set_song_version(result_set[13].c_str());
			value = 0;
			swscanf(result_set[14].c_str(),L"%d",&value);
			idlesse_video[i].set_light_control_set(value);
			value = 0;
			swscanf(result_set[15].c_str(),L"%d",&value);
			idlesse_video[i].set_audio_effect_code(value);
			idlesse_video[i].set_file_format(result_set[16].c_str());
			//idlesse_video[i].set_local_path(result_set[17].c_str());
			idlesse_video[i].set_server_path1(result_set[18].c_str());
			idlesse_video[i].set_server_path2(result_set[19].c_str());
			idlesse_video[i].set_server_path3(result_set[20].c_str());
			idlesse_video[i].set_server_path4(result_set[21].c_str());
			idlesse_video[i].set_server_path5(result_set[22].c_str());
			idlesse_video[i].set_server_path6(result_set[23].c_str());
			idlesse_video[i].set_song_relative_path(result_set[24].c_str());
			value = 0;
			swscanf(result_set[25].c_str(),L"%d",&value);
			idlesse_video[i].set_video_saturation(value);
			value = 0;
			swscanf(result_set[26].c_str(),L"%d",&value);
			idlesse_video[i].set_video_luminance(value);
			value = 0;
			swscanf(result_set[27].c_str(),L"%d",&value);
			idlesse_video[i].set_video_contrast(value);
            idlesse_video[i].set_lyric(result_set[28].c_str());
			idlesse_video[i].set_culture_code(result_set[29].c_str());
			idlesse_video[i].set_preview_path(result_set[30].c_str());
			idlesse_video[i].set_video_type(PLAY_SONG_TYPE_IDLESSE);
		}
		
		if (result_set)
		{
			//�ͷſռ�
			delete []result_set;
			result_set = NULL;
		}
	}
	catch (...)
	{
		
	}
	return;
}

bool public_video_manager::get_begin_video(song_info& video_info)
{
	video_info = begin_video;

	return true;
}

bool public_video_manager::get_end_video(song_info& video_info)
{
	video_info = end_video;
	return true;
}

bool public_video_manager::get_idlesse_video(song_info& video_info)
{
	try
	{
		BOOL result=FALSE;

		if (m_idlesse_video_total_count<=0)
		{
			//û�п��и����Ͳ��ò���
			WriteLog(__FL__, L"û�п��и����Ͳ��ò���");
			return false;
		}

		//���и�����ż�飬��1-99
		if (cur_idlesse_video_number<0)
		{
			cur_idlesse_video_number=0;
		}
		else if (cur_idlesse_video_number>=m_idlesse_video_total_count)
		{
			cur_idlesse_video_number = m_idlesse_video_total_count-1;
		}

	    //�õ�Ҫ���ŵĿ�����Ƶ
		video_info = idlesse_video[cur_idlesse_video_number];
		//����Ĭ����Ч����׼
		video_info.set_audio_effect_code(1);
		//����Ĭ�ϵƹ⣺��׼
		video_info.set_light_control_set(1);

		//���и����������
		cur_idlesse_video_number++;
		cur_idlesse_video_number %= m_idlesse_video_total_count;
		
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool public_video_manager::get_atmosphere_wave_info(int wave_type,TCHAR *audio_path,TCHAR *picture_path,bool soft_code)
{
	try
	{
		if ((NULL==audio_path)||(NULL==picture_path))
		{
			return false;
		}
		//��ߵ���ֵ = ����������ֵ+1000
		int wave_number = wave_type + 1000;
		switch(wave_number)
		{
		case WAVE_ATMOSPHERE_APPLAUSE:    //����
			{
				swprintf(audio_path,L"%s\\����.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\����.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\����.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_CHEER:       //����
			{
				swprintf(audio_path,L"%s\\������.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\������.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\������.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_OUTCRY:      //����
			{
				swprintf(audio_path,L"%s\\����.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\����.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\����.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_WHISTLE:     //��
			{
				swprintf(audio_path,L"%s\\��.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\��.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\��.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_HAOZAN:     //����
			{
				swprintf(audio_path,L"%s\\����.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\����.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\����.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_SHIHUA:     //ʯ��
			{
				swprintf(audio_path,L"%s\\ʯ��.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\ʯ��.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\ʯ��.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_XIANHUA:     //�׻�
			{
				swprintf(audio_path,L"%s\\�׻�.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\�׻�.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\�׻�.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_TUXIE:     //��Ѫ
			{
				swprintf(audio_path,L"%s\\��Ѫ.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\��Ѫ.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\��Ѫ.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_FEIWEN:     //����
			{
				swprintf(audio_path,L"%s\\����.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\����.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\����.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_XINSUI:     //����
			{
				swprintf(audio_path,L"%s\\����.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\����.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\����.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_HAIXIU:     //����
			{
				swprintf(audio_path,L"%s\\����.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\����.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\����.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_ZADAN:     //�ҵ�
			{
				swprintf(audio_path,L"%s\\�ҵ�.wav",m_atmosphere_video_path);
				if (soft_code)
				{
					swprintf(picture_path,L"%s\\�ҵ�.gif",m_atmosphere_video_path);
				}
				else
				{
					swprintf(picture_path,L"%s\\�ҵ�.bmp",m_atmosphere_video_path);
				}
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_LEFT_FRUM1:   //��һ��
			{
				swprintf(audio_path,L"%s\\��һ��.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_LEFT_CYMBAL1:  //��һ��
			{
				swprintf(audio_path,L"%s\\��һ��.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_LEFT_CYMBAL2: //�����
			{
				swprintf(audio_path,L"%s\\�����.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_RIGHT_CYMBAL2: //�Ҷ���
			{
				swprintf(audio_path,L"%s\\�Ҷ���.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_RIGHT_CYMBAL1: //��һ��
			{
				swprintf(audio_path,L"%s\\��һ��.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_PRE_FRUM:      //ǰ���
			{
				swprintf(audio_path,L"%s\\ǰ���.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_LEFT_FRUM2:   //�����
			{
				swprintf(audio_path,L"%s\\�����.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_RIGHT_FRUM2:   //�Ҷ���
			{
				swprintf(audio_path,L"%s\\�Ҷ���.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_RIGHT_FRUM1:   //��һ��
			{
				swprintf(audio_path,L"%s\\��һ��.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM_KIT_MIDDLE_FRUM: //�м�Ĺ�
			{
				swprintf(audio_path,L"%s\\�й�.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK1:       //���ٺڼ������𣬹�15����
			{
				swprintf(audio_path,L"%s\\��1.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK2:
			{
				swprintf(audio_path,L"%s\\��2.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK3:
			{
				swprintf(audio_path,L"%s\\��3.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK4:
			{
				swprintf(audio_path,L"%s\\��4.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK5:
			{
				swprintf(audio_path,L"%s\\��5.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK6:
			{
				swprintf(audio_path,L"%s\\��6.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK7:
			{
				swprintf(audio_path,L"%s\\��7.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK8:
			{
				swprintf(audio_path,L"%s\\��8.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK9:
			{
				swprintf(audio_path,L"%s\\��9.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK10:
			{
				swprintf(audio_path,L"%s\\��10.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK11:
			{
				swprintf(audio_path,L"%s\\��11.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK12:
			{
				swprintf(audio_path,L"%s\\��12.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK13:
			{
				swprintf(audio_path,L"%s\\��13.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK14:
			{
				swprintf(audio_path,L"%s\\��14.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_BLACK15:
			{
				swprintf(audio_path,L"%s\\��15.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE1: //���ٰ׼������𣬹�21����
			{
				swprintf(audio_path,L"%s\\��1.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE2:
			{
				swprintf(audio_path,L"%s\\��2.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE3:
			{
				swprintf(audio_path,L"%s\\��3.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE4:
			{
				swprintf(audio_path,L"%s\\��4.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE5:
			{
				swprintf(audio_path,L"%s\\��5.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE6:
			{
				swprintf(audio_path,L"%s\\��6.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE7:
			{
				swprintf(audio_path,L"%s\\��7.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE8:
			{
				swprintf(audio_path,L"%s\\��8.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE9:
			{
				swprintf(audio_path,L"%s\\��9.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE10:
			{
				swprintf(audio_path,L"%s\\��10.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE11:
			{
				swprintf(audio_path,L"%s\\��11.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE12:
			{
				swprintf(audio_path,L"%s\\��12.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE13:
			{
				swprintf(audio_path,L"%s\\��13.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE14:
			{
				swprintf(audio_path,L"%s\\��14.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE15:
			{
				swprintf(audio_path,L"%s\\��15.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE16:
			{
				swprintf(audio_path,L"%s\\��16.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE17:
			{
				swprintf(audio_path,L"%s\\��17.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE18:
			{
				swprintf(audio_path,L"%s\\��18.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE19:
			{
				swprintf(audio_path,L"%s\\��19.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE20:
			{
				swprintf(audio_path,L"%s\\��20.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_PIANO_WHITE21:
			{
				swprintf(audio_path,L"%s\\��21.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_MARACAS:
			{
				swprintf(audio_path,L"%s\\ɳ��.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_HANDBELL:
			{
				swprintf(audio_path,L"%s\\����.wav",m_atmosphere_video_path);
			}
			break;
		case WAVE_ATMOSPHERE_DRUM:
			{
				swprintf(audio_path,L"%s\\��.wav",m_atmosphere_video_path);
			}
			break;
		default:
			break;
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool public_video_manager::get_environment_wave_info(int wave_type,TCHAR *path)
{
	try
	{
		TCHAR wave_path[256];

		if (NULL==path)
		{
			return false;
		}

		memset(wave_path,0x0,sizeof(wave_path));

		switch(wave_type)
		{
		case 1:
			{
				swprintf(wave_path,L"%s\\����.wav",m_environment_audio_path);
			}
			break;
		case 2:
			{
				swprintf(wave_path,L"%s\\�ɻ���.wav",m_environment_audio_path);
			}
			break;
		case 3:
			{
				swprintf(wave_path,L"%s\\��·��.wav",m_environment_audio_path);
			}
			break;
		case 4:
			{
				swprintf(wave_path,L"%s\\��վ.wav",m_environment_audio_path);
			}
			break;
		case 5:
			{
				swprintf(wave_path,L"%s\\�齫.wav",m_environment_audio_path);
			}
			break;
		case 6:
			{
				swprintf(wave_path,L"%s\\����.wav",m_environment_audio_path);
			}
			break;
		case 0:
		default:
			{

			}
			break;
		}
		
		_tcscpy(path,wave_path);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void public_video_manager::set_cur_idlesse_list()
{
	//��õ�ǰʱ��
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(L"%H%M");
	int iCurTime = _ttoi(strTime);

	//�ж��Ƿ�����ʱ�������ƿ��и���
	if (m_idless_by_time_count > 0)
	{
		bool bflag = true;
		for (int i = 0; i < m_idless_by_time_count; i++)
		{
			if(m_idless_by_time[i].iBegin <= iCurTime && m_idless_by_time[i].iEnd > iCurTime && m_idless_by_time_idx != i)
			{
				for (int m=0;m<IDLESSE_VIDEO_MAX_NUMBER;m++)
				{
					idlesse_video[m].initialized_variables();
				}

				//idlesse_video = m_idless_by_time[i].SongInfo;
				for (int n = 0; n < m_idless_by_time[i].iCount; n++)
				{
					idlesse_video[n] = m_idless_by_time[i].SongInfo[n];
				}
				m_idlesse_video_total_count = m_idless_by_time[i].iCount;
				m_idless_by_time_idx = i;
			}

			if(m_idless_by_time[i].iBegin < iCurTime && m_idless_by_time[i].iEnd > iCurTime)
			{
				bflag = false;
				m_idlesse_video_type = true;
			}
		}

		if (bflag && m_idlesse_video_type)
		{
			m_idlesse_video_type = false;
			for (int m=0;m<IDLESSE_VIDEO_MAX_NUMBER;m++)
			{
				idlesse_video[m].initialized_variables();
			}
			m_idlesse_video_total_count = default_idlesse_video_count;
			for (int n = 0; n < default_idlesse_video_count; n++)
			{
				idlesse_video[n] = default_idlesse_video[n];
			}
		}
	}
}
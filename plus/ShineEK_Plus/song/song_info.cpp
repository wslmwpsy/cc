#include "stdafx.h"
#include ".\song_info.h"
#include "..\common\ping.h"
#include "..\common\StringCodeConversion.h"
#include "..\common\string_function.h"
#include "..\message.h"

extern FLASH_USE_LANGUAGE g_flash_use_language; //flashʹ�õ�����

song_info::song_info(void)
{
	initialized_variables();
}

song_info::~song_info(void)
{
}

void song_info::initialized_variables(void)
{
	try
	{
		memset(song_id,0x0,sizeof(song_id));				//�������
		memset(accompany_sing_track,0x0,sizeof(accompany_sing_track));	//�����鳪���죨������������4�����죩
		memset(karaoke_track,0x0,sizeof(karaoke_track));			//����ԭ�����죨������������4�����죩
		memset(guid_track,0x0,sizeof(guid_track));
		memset(m_song_name,0x0,sizeof(m_song_name));	    	//��������
		memset(m_movie_name,0x0,sizeof(m_movie_name));
		m_song_sort = 0;
		accompany_volume=0;			//�鳪����
		karaoke_volume=0;				//ԭ������
		language=SONG_LANGUAGE_ALL;	//���֣�������������Ӣ���ա�����

		memset(song_type,0x0,sizeof(song_type));			//���֣����硢ͨ�ס���÷Ϸ��..��

		memset(singer_name,0x0,sizeof(singer_name));			//������

		memset(singer_sex,0x0,sizeof(singer_sex));
		song_version=SONG_VERSION_UNKNOWN;	//�����İ汾�ţ��羰��MTV��������ڡ��ݳ��ᡢ���
		light_control_set=0;			//�����ڵƿص�����
		audio_effect_code=0;
		file_format=SONG_FORMAT_UNKNOWN;	//�ļ���ʽ
		memset(local_path,0x0,sizeof(local_path));			//���صĸ���·���������ڵ����棩

		server_path[0][0]=L'\0';		//����������·�����磺\\server��

		server_path[1][0]=L'\0';		//����������·�����磺\\server��

		server_path[2][0]=L'\0';		//����������·�����磺\\server��

		server_path[3][0]=L'\0';		//����������·�����磺\\server��

		server_path[4][0]=L'\0';		//����������·�����磺\\server��

		server_path[5][0]=L'\0';		//����������·�����磺\\server��

		memset(song_relative_path,0x0,sizeof(song_relative_path));  //��������·������·��1..�������������·�����磺\jp01\000001.mpg��

		video_saturation=0;			//������Ƶ�ı��Ͷ�
		video_luminance=0;			//������Ƶ������

		video_contrast=0;				//������Ƶ�ĶԱȶ�
		memset(m_lyric,0x0,sizeof(m_lyric));				//�������
		memset(culture_code,0x0,sizeof(culture_code));		//�Ļ�������

		memset(preview_path,0x0,sizeof(preview_path));		//Ԥ��·�������ڸ���Ԥ����
		memset(recorder_video_path,0x0,sizeof(recorder_video_path));            //������Ƶ·��
		memset(recorder_wave_path,0x0,sizeof(recorder_wave_path));              //¼����Ƶ·��	
		memset(recorder_datatime,0x0,sizeof(recorder_datatime));                //¼��������
		recorder_exist_video_path = false;                     //�Ƿ��¼�������ĸ�����Ƶ

		recorder_start_time = 0;                                                //��ʼʱ��	
		memset(movie_region,0x0,sizeof(movie_region));        //��Ӱ�Ĺ�����
		memset(language_ab,0x0,sizeof(language_ab));
		memset(singer_id1,0x0,sizeof(singer_id1));           //����id1
		memset(singer_id2,0x0,sizeof(singer_id2));           //����id2
		memset(singer_id3,0x0,sizeof(singer_id3));			 //����id3
		memset(singer_id4,0x0,sizeof(singer_id4));			 //����id3
		memset(file_version,0x0,sizeof(file_version));		 //�����汾�� 1.0
		recorder_score = 0;                                   //¼������
		movie_story = 0;                                      //��Ӱ�Ĺ������

		video_type=PLAY_SONG_TYPE_SELECT_SONG;                                  //��Ƶ���ͣ�0������ѡ��ĸ���  1��¼������

		music_enjoy = 0;

		down_update_song = 0;

		flash_page_code = -1;
		
// 		memset(m_lyric_path, 0x0, sizeof(m_lyric_path));	//���·��
		memset(m_song_bk_path, 0x0, sizeof(m_song_bk_path));//����·��
		
		m_server_manually_index = -1;
	}
	catch (...)
	{

	} 	
}

bool song_info::set_recorder_exist_video_path(bool value)
{
	try
	{
		recorder_exist_video_path = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_song_id(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(song_id))
		{
			return false;
		}
		memset(song_id,0x0,sizeof(song_id));
		wcscpy(song_id,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_accompany_sing_track(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(accompany_sing_track))
		{
			return false;
		}
		wcscpy(accompany_sing_track,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_karaoke_track(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(karaoke_track))
		{
			return false;
		}
		wcscpy(karaoke_track,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_guid_track(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(guid_track))
		{
			return false;
		}
		wcscpy(guid_track,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_song_name(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(m_song_name))
		{
			return false;
		}
		wcscpy(m_song_name,value);
		//ɾ�������ַ�
		flash_replace_special_char(m_song_name);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_movie_name(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(m_movie_name))
		{
			return false;
		}
		wcscpy(m_movie_name,value);
		//ɾ�������ַ�
		flash_replace_special_char(m_movie_name);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_song_sort(int value)
{
	try
	{
		m_song_sort = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_accompany_volume(int value)
{
	try
	{
		accompany_volume = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_karaoke_volume(int value)
{
	try
	{
		karaoke_volume = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_language(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}

		_tcscpy(language_ab, L"��");
		if (value == 0)
		{
			language = SONG_LANGUAGE_ALL;
		}
		else if (_tcsicmp(value, L"1") == 0) //����
		{
			language = SONG_LANGUAGE_CHINESE;
		}
		else if (_tcsicmp(value, L"2") == 0) //����
		{
			language = SONG_LANGUAGE_YUE;
			_tcscpy(language_ab, L"��");
		}
		else if (_tcsicmp(value, L"3") == 0) //���� ������

		{
			language = SONG_LANGUAGE_MINNAN;
			_tcscpy(language_ab, L"��");
		}
		else if (_tcsicmp(value, L"4") == 0) //Ӣ��
		{
			language = SONG_LANGUAGE_ENGLISH;
			_tcscpy(language_ab, L"Ӣ");
		}
		else if (_tcsicmp(value, L"6") == 0) //����
		{
			language = SONG_LANGUAGE_JAPANESE;
			_tcscpy(language_ab, L"��");
		}
		else if (_tcsicmp(value, L"5") == 0) //���� ���ﱱ ������

		{
			language = SONG_LANGUAGE_KOREAN;
			_tcscpy(language_ab, L"��");
		}
		else if (_tcsicmp(value, L"8") == 0) //̩��
		{
			language = SONG_LANGUAGE_THAI;
			_tcscpy(language_ab, L"̩");
		}
		else if (_tcsicmp(value,L"9")==0)  //����
		{
			language = SONG_LANGUAGE_MONGOLIA;
			_tcscpy(language_ab,L"��");
		}
		else if (_tcsicmp(value,L"10")==0) //����
		{
			language = SONG_LANGUAGE_RUSSIAN;
			_tcscpy(language_ab,L"��");
		}
		else if (0==_tcsicmp(value,L"����"))
		{
			language = SONG_LANGUAGE_OTHERS;
			_tcscpy(language_ab,L"����");
		}
		//����Ϊ��Ӱ����


		else if (_tcsnicmp(value, L"�й�", sizeof(L"�й�") / sizeof(TCHAR) ) == 0)
		{
			language = SONG_LANGUAGE_CHINESE;
			_tcscpy(language_ab, L"��");
		}
		else
		{
			if (_tcslen(value) > 1)
				_tcsncpy(language_ab, value, 1);
			language = SONG_LANGUAGE_ALL;
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_song_type(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(song_type))
		{
			return false;
		}
		wcscpy(song_type,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_singer_name(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(singer_name))
		{
			return false;
		}
		wcscpy(singer_name,value);
		//ɾ�������ַ�
		flash_replace_special_char(singer_name);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_singer_sex(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(singer_sex))
		{
			return false;
		}
		wcscpy(singer_sex,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_song_version(const TCHAR *value)
{
	try
	{
		if(NULL==value)
		{
			return false;
		}

		if (value == 0)
		{
			song_version = SONG_VERSION_UNKNOWN;
		}
		else if ((_tcsicmp(value, L"1") == 0))  //MTV
		{
			song_version = SONG_VERSION_MTV;
		}
		else if ((_tcsicmp(value, L"2") == 0)) //�羰
		{
			song_version = SONG_VERSION_VIEW;
		}
		else if (_tcsicmp(value, L"5") == 0)  //����  �������
		{
			song_version = SONG_VERSION_STORY;
		}
		else if (_tcsicmp(value, L"4") == 0) //����
		{
			song_version = SONG_VERSION_PERSON;
		}
		else if (_tcsicmp(value, L"3") == 0) //�ݳ���  �ݳ�
		{
			song_version = SONG_VERSION_CONCERT;
		}
		else if (_tcsicmp(value, L"7") == 0) //���Ͱ� ����
		{
			song_version = SONG_VERSION_ENJOY;
		}
		else if ((_tcsicmp(value, L"6") == 0) || (_tcsicmp(value, L"8") == 0)) //Ӱ�Ӱ� Ӱ�����
		{
			song_version = SONG_VERSION_MOVIE;
		}
		else if (_tcsicmp(value,L"10") == 0)  //����
		{
			song_version = SONG_VERSION_DJ;
		}
		else if (_tcsicmp(value,L"11") == 0)  //����
		{
			song_version = SONG_VERSION_DANCE;
		}
		else if (_tcsicmp(value,L"VCD") == 0)  //VCD
		{
			song_version = SONG_VERSION_VCD;
		}
		else if (_tcsicmp(value,L"DVD") == 0)  //DVD
		{
			song_version =  SONG_VERSION_DVD;
		}
		else if (_tcsicmp(value,L"HD") == 0)  //HD
		{
			song_version = SONG_VERSION_HD;
		}
		else if (_tcsicmp(value,L"13") == 0)  //�ٶ�
		{
			song_version = SONG_VERSION_BAIDU;
		}
		else if (_tcsicmp(value,L"14") == 0)  //QQ
		{
			song_version = SONG_VERSION_QQ;
		}
		else if (_tcsicmp(value,L"15") == 0)  //�ṷ
		{
			song_version = SONG_VERSION_KUGOU;
		}
		else if (_tcsicmp(value,L"16") == 0)  //����
		{
			song_version = SONG_VERSION_KUWO;
		}
		else
		{
			song_version = SONG_VERSION_UNKNOWN;
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_light_control_set(int value)
{
	try
	{
		light_control_set = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_audio_effect_code(int value)
{
	try
	{
		audio_effect_code = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_file_format(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}

		TCHAR szMpeg1[5][8] = { L"MPG", L"MPG1", L"MPG-1", L"MPEG1", L"MPEG-1" };
		TCHAR szMpeg2[4][8] = {        L"MPG2", L"MPG-2", L"MPEG2", L"MPEG-2" };

		int i;
		for (i=0; i<(sizeof(szMpeg1)/sizeof(szMpeg1[0])); i++)
		{
			if (_tcsicmp(value, szMpeg1[i]) == 0)
			{
				file_format = SONG_FORMAT_MPEG_1;
				return true;
			}
		}
		for (i=0; i<(sizeof(szMpeg2)/sizeof(szMpeg2[0])); i++)
		{
			if (_tcsicmp(value, szMpeg2[i]) == 0)
			{
				file_format = SONG_FORMAT_MPEG_2;
				return true;
			}
		}
		file_format = SONG_FORMAT_UNKNOWN;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_local_path(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(local_path))
		{
			return false;
		}
		wcscpy(local_path,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_server_path1(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(server_path[0]))
		{
			return false;
		}
		wcscpy(server_path[0],value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_server_path2(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(server_path[0]))
		{
			return false;
		}
		wcscpy(server_path[1],value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_server_path3(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(server_path[0]))
		{
			return false;
		}
		wcscpy(server_path[2],value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_server_path4(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(server_path[0]))
		{
			return false;
		}
		wcscpy(server_path[3],value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_server_path5(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(server_path[0]))
		{
			return false;
		}
		wcscpy(server_path[4],value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_server_path6(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(server_path[0]))
		{
			return false;
		}
		wcscpy(server_path[5],value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_song_relative_path(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(song_relative_path))
		{
			return false;
		}
		wcscpy(song_relative_path,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_video_saturation(int value)
{
	try
	{
		video_saturation = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_video_luminance(int value)
{
	try
	{
		video_luminance = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_video_contrast(int value)
{
	try
	{
		video_contrast = value;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_lyric(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*_tcslen(value)>=sizeof(m_lyric))
		{
			return false;
		}
		_tcscpy(m_lyric,value);
		//ɾ�������ַ�
		flash_replace_special_char(m_lyric);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

// bool song_info::set_lyric_path(const TCHAR *value)
// {
// 	try
// 	{
// 		if (NULL==value)
// 		{
// 			return false;
// 		}
// 		if (2*wcslen(value)>=sizeof(m_lyric_path))
// 		{
// 			return false;
// 		}
// 		wcscpy(m_lyric_path,value);
// 
// 		return true;
// 	}
// 	catch (...)
// 	{
// 
// 	}
// 	return false;
// }
// 
bool song_info::set_song_bk_path(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(m_song_bk_path))
		{
			return false;
		}
		wcscpy(m_song_bk_path,value);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_culture_code(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(culture_code))
		{
			return false;
		}
		wcscpy(culture_code,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_preview_path(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(preview_path))
		{
			return false;
		}
		wcscpy(preview_path,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_recorder_video_path(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(recorder_video_path))
		{
			return false;
		}
		wcscpy(recorder_video_path,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_recorder_wave_path(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(recorder_wave_path))
		{
			return false;
		}
		wcscpy(recorder_wave_path,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_recorder_start_time(int value)
{
	recorder_start_time = value;
	return true;
}

bool song_info::set_recorder_datatime(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(recorder_datatime))
		{
			return false;
		}
		_tcscpy(recorder_datatime,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool song_info::set_recorder_score(int value)
{
	try
	{
		recorder_score = value;
		return true;
	}
	catch (...)
	{

	}
	return false;
}
bool song_info::set_movie_region(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(movie_region))
		{
			return false;
		}
		_tcscpy(movie_region,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_movie_story(int value)
{
	movie_story = value;

	return true;
}


bool song_info::set_singer_id1(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(singer_id1))
		{
			return false;
		}
		wcscpy(singer_id1,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::set_singer_id2(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(singer_id2))
		{
			return false;
		}
		wcscpy(singer_id2,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}
bool song_info::set_singer_id3(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(singer_id3))
		{
			return false;
		}
		wcscpy(singer_id3,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}
bool song_info::set_singer_id4(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(singer_id4))
		{
			return false;
		}
		wcscpy(singer_id4,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}
bool song_info::set_file_version(const TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (2*wcslen(value)>=sizeof(file_version))
		{
			return false;
		}
		wcscpy(file_version,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool song_info::get_song_language(TCHAR *song_language)
{
	if (NULL==song_language)
	{
		return false;
	}
	switch (language)
	{
	case SONG_LANGUAGE_CHINESE:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"����");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_YUE:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"����");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_MINNAN:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"����");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_ENGLISH:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"Ӣ��");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_JAPANESE:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"����");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_KOREAN:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"����");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_THAI:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"̩");
				}
				break;
			default:
				wcscpy(song_language,L"̩��");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_MONGOLIA:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"����");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_RUSSIAN:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"����");
				break;
			}
		}
		break;
	default:
	case SONG_LANGUAGE_ALL:
	case SONG_LANGUAGE_OTHERS:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //����
				{
					wcscpy(song_language,L"��");
				}
				break;
			default:
				wcscpy(song_language,L"����");
				break;
			}
		}
		break;
	}

	return true;
}

bool song_info::get_handheld_song_language(TCHAR *song_language)
{
	if (NULL==song_language)
	{
		return false;
	}
	switch (language)
	{
	case SONG_LANGUAGE_ALL:
		wcscpy(song_language,L" ");
		break;
	case SONG_LANGUAGE_CHINESE:
		wcscpy(song_language,L"����");
		break;
	case SONG_LANGUAGE_YUE:
		wcscpy(song_language,L"����");
		break;
	case SONG_LANGUAGE_MINNAN:
		wcscpy(song_language,L"������");
		break;
	case SONG_LANGUAGE_ENGLISH:
		wcscpy(song_language,L"Ӣ��");
		break;
	case SONG_LANGUAGE_JAPANESE:
		wcscpy(song_language,L"����");
		break;
	case SONG_LANGUAGE_KOREAN:
		wcscpy(song_language,L"����");
		break;
	case SONG_LANGUAGE_THAI:
		wcscpy(song_language,L"̩��");
		break;
	case SONG_LANGUAGE_MONGOLIA:
		wcscpy(song_language,L"����");
		break;
	case SONG_LANGUAGE_RUSSIAN:
		wcscpy(song_language,L"����");
		break;
	case SONG_LANGUAGE_OTHERS:
		wcscpy(song_language,L"����");
		break;
	default:
		break;
	}

	return true;
}

const TCHAR* song_info::get_language_string()
{
	switch (language)
	{
	default:
	case SONG_LANGUAGE_ALL: return L"";
	case SONG_LANGUAGE_CHINESE: return L"����";
	case SONG_LANGUAGE_YUE: return L"����";
	case SONG_LANGUAGE_MINNAN: return L"������";
	case SONG_LANGUAGE_ENGLISH: return L"Ӣ��";
	case SONG_LANGUAGE_JAPANESE: return L"����";
	case SONG_LANGUAGE_KOREAN: return L"����";
	case SONG_LANGUAGE_THAI: return L"̩��";
	case SONG_LANGUAGE_MONGOLIA:  return L"����";
	case SONG_LANGUAGE_RUSSIAN:   return L"����";
	}
}

bool song_info::get_song_name(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,m_song_name);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_moive_name(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,m_movie_name);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

int song_info::get_song_sort(void)
{
	return m_song_sort;
}

bool song_info::get_singer_name(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,singer_name);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_singer_sex(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,singer_sex);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_song_version(TCHAR *value,int &version)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		switch(song_version)
		{
		default:
		case SONG_VERSION_UNKNOWN:    //δ֪
			{
				wcscpy(value,L"δ֪");
				version = SONG_VERSION_UNKNOWN;
			}
			break;
		case SONG_VERSION_CONCERT:	  //�ݳ���

			{
				wcscpy(value,L"�ݳ���");
				version = SONG_VERSION_CONCERT;
			}
			break;
		case SONG_VERSION_ENJOY:      //���Ͱ�

			{
				wcscpy(value,L"����");
				version = SONG_VERSION_ENJOY;
			}
			break;
		case SONG_VERSION_MTV:	      //MTV
			{
				wcscpy(value,L"MTV");
				version = SONG_VERSION_MTV;
			}
			break;
		case SONG_VERSION_VIEW:	      //�羰
			{
				wcscpy(value,L"�羰");
				version = SONG_VERSION_VIEW;
			}
			break;
		case SONG_VERSION_STORY:	  //�������
			{
				wcscpy(value,L"����");
				version = SONG_VERSION_STORY;
			}
			break;
		case SONG_VERSION_PERSON:	  //����
			{
				wcscpy(value,L"����");
				version = SONG_VERSION_PERSON;
			}
			break;
		case SONG_VERSION_MOVIE:   //Ӱ�Ӱ� Ӱ�����
			{
				_tcscpy(value,L"Ӱ��");
				version = SONG_VERSION_MOVIE;
			}
			break;
		case SONG_VERSION_DJ://����
			{
				_tcscpy(value,L"����");
				version = SONG_VERSION_DJ;
			}
			break;
		case SONG_VERSION_DANCE://����
			{
				_tcscpy(value,L"����");
				version = SONG_VERSION_DANCE;
			}
			break;
		case SONG_VERSION_VCD:   //VCD
			{
				_tcscpy(value,L"VCD");
				version = SONG_VERSION_VCD;
			}
			break;
		case SONG_VERSION_DVD: //DVD
			{
				_tcscpy(value,L"DVD");
				version = SONG_VERSION_DVD;
			}
			break;
		case SONG_VERSION_HD://HD
			{
				_tcscpy(value,L"����");
				version = SONG_VERSION_HD;
			}
			break;
		case SONG_VERSION_BAIDU://HD
			{
				_tcscpy(value,L"�ٶ�����");
				version = SONG_VERSION_BAIDU;
			}
			break;
		case SONG_VERSION_QQ://HD
			{
				_tcscpy(value,L"QQ����");
				version = SONG_VERSION_QQ;
			}
			break;
		case SONG_VERSION_KUGOU://HD
			{
				_tcscpy(value,L"�ṷ����");
				version = SONG_VERSION_KUGOU;
			}
			break;
		case SONG_VERSION_KUWO://HD
			{
				_tcscpy(value,L"��������");
				version = SONG_VERSION_KUWO;
			}
			break;
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_song_id(TCHAR *value)
{
	try
	{
		if ((NULL==value)||(0==_tcscmp(song_id,L"")))
		{
			return false;
		}
		wcscpy(value,song_id);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_path(TCHAR *value,bool check_file_exist,int &link_server)
{
	try
	{
		TCHAR path[256];
		string_conversion string_conv;
		char server_ip[256];
		int server_sort=0;

		memset(path,0x0,sizeof(path));

		if (PLAY_SONG_TYPE_RECORDER_SONG==video_type)
		{
			//¼����Ƶ·���Ƕ�����һ���ֶ�
			if (0==_tcscmp(recorder_video_path,L""))
			{
				return false;
			}
			_tcscpy(value,recorder_video_path);
			//���ӷ���������ó�-1����ʾ���Ƿ�����·��
			link_server = -1;
			return true;
		}
		else if (PLAY_MUSIC_ENJOY == video_type)
		{
			if (0==_tcscmp(song_relative_path,L""))
			{
				return false;
			}
			_tcscpy(value,song_relative_path);
			//������Ƶ�ļ�·��//yzg
			_tcscpy(value, m_song_bk_path);

			//���ӷ���������ó�-1����ʾ���Ƿ�����·��
			link_server = -1;
			return true;
		}
		else
		{
			//����·�����ȣ�������·����֮
			if ((0!=_tcscmp(local_path,L""))&&((0==_tcsncmp(local_path,L"hik:",4))||(0==_tcsncmp(local_path,L"udp:",4))||(0==_tcsncmp(local_path,L"shn:",4))||(PathFileExists(local_path))))
			{
				_tcscpy(value,local_path);
				//���ӷ���������ó�-1����ʾ���Ƿ�����·��
				link_server = -1;
				return true;
			}

			//�����ֶ������� -- add by caizw
			if (m_server_manually_index > -1) //���������
			{
				//�õ�����·��
				if ((0!=_tcscmp(server_path[m_server_manually_index],L""))&&(0!=_tcscmp(song_relative_path,L"")))
				{
					if (check_file_exist && (0!=_tcsncmp(server_path[m_server_manually_index],L"udp:",4)))
					{
						//2010-08-25 add
						//�������ļ��Ƿ���ڣ���ǰpingһ�·������Ƿ����
						memset(server_ip,0x0,sizeof(server_ip));
						string_conv.widechar_to_multibyte(server_path[m_server_manually_index],server_ip,sizeof(server_ip));
						unsigned long roundtrip_time = ping(server_ip+2,500);
						if (roundtrip_time>=500)
						{
							return false;
						}
					}
					swprintf(path,L"%s%s",server_path[m_server_manually_index],song_relative_path);
					if (check_file_exist && (0!=_tcsncmp(path,L"udp:",4)))
					{
						//����ļ��Ƿ����
						if (PathFileExists(path))
						{
							//�ж�һ���ļ��Ƿ����
							_tcscpy(value,path);
							//����ѡ��ķ��������
							link_server = m_server_manually_index;
							return true;
						}
					}
					else
					{
						//�����
						_tcscpy(value,path);
						//����ѡ��ķ��������
						link_server = m_server_manually_index;
						return true;
					}
				}
				return false;
			}

			//������һ��6��·��
			for (int i=0;i<6;i++)
			{
				memset(path,0x0,sizeof(path));

				//�õ�Ҫ���ʵķ��������
				server_sort = (link_server+i)%6;
				//�õ�����·��
				if ((0!=_tcscmp(server_path[server_sort],L""))&&(0!=_tcscmp(song_relative_path,L"")))
				{
					if (check_file_exist && (0!=_tcsncmp(server_path[server_sort],L"udp:",4)))
					{
						//2010-08-25 add
						//�������ļ��Ƿ���ڣ���ǰpingһ�·������Ƿ����
						memset(server_ip,0x0,sizeof(server_ip));
						string_conv.widechar_to_multibyte(server_path[server_sort],server_ip,sizeof(server_ip));
						unsigned long roundtrip_time = ping(server_ip+2,500);
						if (roundtrip_time>=500)
						{
							continue;
						}
					}
					swprintf(path,L"%s%s",server_path[server_sort],song_relative_path);
					if (check_file_exist && (0!=_tcsncmp(path,L"udp:",4)))
					{
						//����ļ��Ƿ����
						if (PathFileExists(path))
						{
							//�ж�һ���ļ��Ƿ����
							_tcscpy(value,path);
							//����ѡ��ķ��������
							link_server = server_sort;
							return true;
						}
					}
					else
					{
						//�����
						_tcscpy(value,path);
						//����ѡ��ķ��������
						link_server = server_sort;
						return true;
					}
				}
			}
		}

		return false;
	}
	catch (...)
	{

	}
	return false;	
}

bool song_info::get_server_ip(TCHAR *value)
{
	try
	{
		TCHAR song_path[256];

		memset(song_path,0x0,sizeof(song_path));

		if (PLAY_SONG_TYPE_RECORDER_SONG==video_type)
		{
			//¼����Ƶ·���Ƕ�����һ���ֶ�


			if (0==_tcscmp(recorder_video_path,L""))
			{
				return false;
			}
			//�������������IP
			_tcscpy(song_path,recorder_video_path);
			_tcschr(song_path+3,'\\')[0]='\0';
			_tcscpy(value,song_path);			
			return true;
		}
		else
		{
			//������һ��6��·��


			for (int i=0;i<6;i++)
			{
				if ((0!=_tcscmp(server_path[i],L"")) && (0!=_tcscmp(song_relative_path,L"")))
				{
					_tcscpy(value,server_path[i]);
					return true;
				}
			}
		}

		return false;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_channel_track(bool channel,TCHAR *channel_track)
{
	try
	{
		if (channel)
		{
			//ԭ������
			if (0!=_tcscmp(karaoke_track,L""))
			{
				_tcscpy(channel_track,karaoke_track);
			}
			else
			{
				return false;
			}
		}
		else
		{
			//�鳪����
			if (0!=_tcscmp(accompany_sing_track,L""))
			{
				_tcscpy(channel_track,accompany_sing_track);
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_preview_channel_track(bool channel,byte &channel_track)
{
	try
	{
		TCHAR song_track[16];
		memset(song_track,0x0,sizeof(song_track));

		if (channel)
		{
			//ԭ������
			if (0!=_tcscmp(karaoke_track,L""))
			{
				_tcscpy(song_track,karaoke_track);
			}
			else
			{
				return false;
			}
		}
		else
		{
			//�鳪����
			if (0!=_tcscmp(accompany_sing_track,L""))
			{
				_tcscpy(song_track,accompany_sing_track);
			}
			else
			{
				return false;
			}
		}
		//ת��������


		if (_tcscmp(song_track, L"��")==0)
		{
			channel_track = 'L';
		}
		else if (_tcscmp(song_track, L"��")==0)
		{
			channel_track = 'R';
		}
		else
		{
			channel_track = _ttoi(song_track);
			if (channel_track < 0)
			{
				if (channel)
				{
					// ԭ������Ϊ��ֵ


					channel_track = 2;
				}
				else
				{
					// �鳪����Ϊ��ֵ


					channel_track = 1;
				}
			}
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

enum SONG_FORMAT song_info::get_file_format(void)
{
	return file_format;
}

bool song_info::get_file_format_string(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		switch(file_format)
		{
		case SONG_FORMAT_MPEG_1:
			{
				_tcscpy(value,L"MPG1");
			}
			break;
		case SONG_FORMAT_MPEG_2:
		default:
			{
				_tcscpy(value,L"MPG2");
			}
			break;
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

int song_info::get_volume(bool channel)
{
	int volume=0;

	if (channel)
	{
		//ԭ������
		volume = karaoke_volume;
	}
	else
	{
		//�鳪����
		volume = accompany_volume;
	}

	return volume;
}

bool song_info::get_lyric(TCHAR *lyric)
{
	try
	{
		if (NULL==lyric)
		{
			return false;
		}
		_tcscpy(lyric,m_lyric);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

// bool song_info::get_lyric_path(TCHAR *lyric_path)
// {
// 	try
// 	{
// 		if (NULL==lyric_path)
// 		{
// 			return false;
// 		}
// 		_tcscpy(lyric_path,m_lyric_path);
// 		return true;
// 	}
// 	catch (...)
// 	{
// 
// 	}
// 	return false;
// }
// 
bool song_info::get_song_bk_path(TCHAR *song_bk_path)
{
	try
	{
		if (NULL==song_bk_path)
		{
			return false;
		}
		_tcscpy(song_bk_path,m_song_bk_path);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_culture_code(TCHAR *code)
{
	try
	{
		if (NULL==code)
		{
			return false;
		}
		_tcscpy(code,culture_code);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_video_path(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,recorder_video_path);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_wave_path(TCHAR *value)
{
	try
	{
		if ((NULL==value) || (0==_tcscmp(recorder_wave_path,L"")))
		{
			return false;
		}
		_tcscpy(value,recorder_wave_path);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

int song_info::get_recorder_start_time(void)
{
	return recorder_start_time;
}

bool song_info::get_recorder_datetime(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,recorder_datatime);
		return true;
	}
	catch (...)
	{

	}
	return false;
}


int song_info::get_recorder_score()
{
	try
	{
		return recorder_score;
	}
	catch (...)
	{

	}
	return false;
}



void song_info::set_video_type(enum PLAY_SONG_TYPE select_video_type)
{
	video_type = select_video_type;
}

enum PLAY_SONG_TYPE song_info::get_video_type(void)
{
	return video_type;
}

bool song_info::get_movie_region(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,movie_region);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

int song_info::get_movie_story(void)
{
	return movie_story;
}

bool song_info::get_movie_story(TCHAR *value)
{
	if (NULL==value)
	{
		return false;
	}
	switch(movie_story)
	{
	case 1:
		{
			_tcscpy(value,L"����Ƭ");
		}
		break;
	case 2:
		{
			_tcscpy(value,L"����Ƭ");
		}
		break;
	case 3:
		{
			_tcscpy(value,L"ϲ��Ƭ");
		}
		break;
	case 4:
		{
			_tcscpy(value,L"ս��Ƭ");
		}
		break;
	case 5:
		{
			_tcscpy(value,L"����Ƭ");
		}
		break;
	case 6:
		{
			_tcscpy(value,L"�ƻ�Ƭ");
		}
		break;
	case 7:
		{
			_tcscpy(value,L"�ֲ�Ƭ");
		}
		break;
	case 8:
		{
			_tcscpy(value,L"����Ƭ");
		}
		break;
	case 9:
		{
			_tcscpy(value,L"����Ƭ");
		}
		break;
	case 10:
		{
			_tcscpy(value,L"����Ƭ");
		}
		break;
	case 11:
		{
			_tcscpy(value,L"����");
		}
		break;
	case 12:
		{
			_tcscpy(value,L"СƷ");
		}
		break;
	case 13:
		{
			_tcscpy(value,L"���ͻ");
		}
		break;
	case 14:
		{
			_tcscpy(value,L"�ݳ���");
		}
		break;
	case 15:
		{
			_tcscpy(value,L"��˾�");
		}
		break;
	default:
		{
			_tcscpy(value,L"δ  ֪");
		}
		break;
	}
	return true;
}

bool song_info::get_accompany_sing_track(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,accompany_sing_track);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_karaoke_track(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,karaoke_track);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_guid_track(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,guid_track);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

int song_info::get_accompany_volume(void)
{
	return accompany_volume;
}

int song_info::get_karaoke_volume(void)
{
	return karaoke_volume;
}

int song_info::get_light_control_set(void)
{
	return light_control_set;
}

int song_info::get_audio_effect_code(void)
{
	return audio_effect_code;
}

bool song_info::get_local_path(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,local_path);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_all_server_path(TCHAR value[][256])
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		for (int i=0;i<6;i++)
		{
			_tcscpy(value[i],server_path[i]);
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_song_relative_path(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,song_relative_path);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

int song_info::get_video_saturation(void)
{
	return video_saturation;
}

int song_info::get_video_luminance(void)
{
	return video_luminance;
}

int song_info::get_video_contrast(void)
{
	return video_contrast;
}

bool song_info::get_preview_path(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		_tcscpy(value,preview_path);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_singer_id1(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,singer_id1);
		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool song_info::get_singer_id2(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,singer_id2);
		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool song_info::get_singer_id3(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,singer_id3);
		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool song_info::get_singer_id4(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,singer_id4);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_song_type(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,song_type);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_file_version(TCHAR *value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,file_version);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool song_info::get_recorder_exist_video_path()
{
	return recorder_exist_video_path;
}

bool song_info::set_music_enjoy(int value){
	music_enjoy = value;
	return true;
}

int song_info::get_music_enjoy(){
	return music_enjoy;
}

bool song_info::set_down_update_song(int update_song)
{
	try
	{
		down_update_song = update_song;

		return true;
	}
	catch (...)
	{

	}

	return false;
}
int song_info::get_down_update_song()
{
	try
	{
		return down_update_song;
	}
	catch (...)
	{

	}

	return 0;
}

void song_info::set_flash_page_code(int page_code)
{
	flash_page_code = page_code;
	return;
}

int song_info::get_flash_page_code()
{
	return flash_page_code;
}
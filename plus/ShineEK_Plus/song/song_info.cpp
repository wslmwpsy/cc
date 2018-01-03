#include "stdafx.h"
#include ".\song_info.h"
#include "..\common\ping.h"
#include "..\common\StringCodeConversion.h"
#include "..\common\string_function.h"
#include "..\message.h"

extern FLASH_USE_LANGUAGE g_flash_use_language; //flash使用的语言

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
		memset(song_id,0x0,sizeof(song_id));				//歌曲编号
		memset(accompany_sing_track,0x0,sizeof(accompany_sing_track));	//歌曲伴唱音轨（分左右声道和4种音轨）
		memset(karaoke_track,0x0,sizeof(karaoke_track));			//歌曲原唱音轨（分左右声道和4种音轨）
		memset(guid_track,0x0,sizeof(guid_track));
		memset(m_song_name,0x0,sizeof(m_song_name));	    	//歌曲名称
		memset(m_movie_name,0x0,sizeof(m_movie_name));
		m_song_sort = 0;
		accompany_volume=0;			//伴唱音量
		karaoke_volume=0;				//原唱音量
		language=SONG_LANGUAGE_ALL;	//语种（国、粤、闽、英、日、韩）

		memset(song_type,0x0,sizeof(song_type));			//曲种（京剧、通俗、黄梅戏…..）

		memset(singer_name,0x0,sizeof(singer_name));			//歌星名

		memset(singer_sex,0x0,sizeof(singer_sex));
		song_version=SONG_VERSION_UNKNOWN;	//歌曲的版本号（风景、MTV、故事情节、演唱会、人物）
		light_control_set=0;			//现用于灯控的设置
		audio_effect_code=0;
		file_format=SONG_FORMAT_UNKNOWN;	//文件格式
		memset(local_path,0x0,sizeof(local_path));			//本地的歌曲路径（多用于单机版）

		server_path[0][0]=L'\0';		//歌曲服务器路径（如：\\server）

		server_path[1][0]=L'\0';		//歌曲服务器路径（如：\\server）

		server_path[2][0]=L'\0';		//歌曲服务器路径（如：\\server）

		server_path[3][0]=L'\0';		//歌曲服务器路径（如：\\server）

		server_path[4][0]=L'\0';		//歌曲服务器路径（如：\\server）

		server_path[5][0]=L'\0';		//歌曲服务器路径（如：\\server）

		memset(song_relative_path,0x0,sizeof(song_relative_path));  //歌曲具体路径，与路径1..组成完整的网络路径（如：\jp01\000001.mpg）

		video_saturation=0;			//歌曲视频的饱和度
		video_luminance=0;			//歌曲视频的亮度

		video_contrast=0;				//歌曲视频的对比度
		memset(m_lyric,0x0,sizeof(m_lyric));				//歌曲歌词
		memset(culture_code,0x0,sizeof(culture_code));		//文化部编码

		memset(preview_path,0x0,sizeof(preview_path));		//预览路径（用于歌曲预览）
		memset(recorder_video_path,0x0,sizeof(recorder_video_path));            //歌曲视频路径
		memset(recorder_wave_path,0x0,sizeof(recorder_wave_path));              //录的音频路径	
		memset(recorder_datatime,0x0,sizeof(recorder_datatime));                //录音的日期
		recorder_exist_video_path = false;                     //是否存录音歌曲的歌曲视频

		recorder_start_time = 0;                                                //开始时间	
		memset(movie_region,0x0,sizeof(movie_region));        //电影的归属地
		memset(language_ab,0x0,sizeof(language_ab));
		memset(singer_id1,0x0,sizeof(singer_id1));           //歌星id1
		memset(singer_id2,0x0,sizeof(singer_id2));           //歌星id2
		memset(singer_id3,0x0,sizeof(singer_id3));			 //歌星id3
		memset(singer_id4,0x0,sizeof(singer_id4));			 //歌星id3
		memset(file_version,0x0,sizeof(file_version));		 //歌曲版本号 1.0
		recorder_score = 0;                                   //录音分数
		movie_story = 0;                                      //电影的故事情节

		video_type=PLAY_SONG_TYPE_SELECT_SONG;                                  //视频类型，0：正常选择的歌曲  1：录音歌曲

		music_enjoy = 0;

		down_update_song = 0;

		flash_page_code = -1;
		
// 		memset(m_lyric_path, 0x0, sizeof(m_lyric_path));	//歌词路径
		memset(m_song_bk_path, 0x0, sizeof(m_song_bk_path));//背景路径
		
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
		//删除特殊字符
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
		//删除特殊字符
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

		_tcscpy(language_ab, L"国");
		if (value == 0)
		{
			language = SONG_LANGUAGE_ALL;
		}
		else if (_tcsicmp(value, L"1") == 0) //国语
		{
			language = SONG_LANGUAGE_CHINESE;
		}
		else if (_tcsicmp(value, L"2") == 0) //粤语
		{
			language = SONG_LANGUAGE_YUE;
			_tcscpy(language_ab, L"粤");
		}
		else if (_tcsicmp(value, L"3") == 0) //闽南 闽南语

		{
			language = SONG_LANGUAGE_MINNAN;
			_tcscpy(language_ab, L"闽");
		}
		else if (_tcsicmp(value, L"4") == 0) //英语
		{
			language = SONG_LANGUAGE_ENGLISH;
			_tcscpy(language_ab, L"英");
		}
		else if (_tcsicmp(value, L"6") == 0) //日语
		{
			language = SONG_LANGUAGE_JAPANESE;
			_tcscpy(language_ab, L"日");
		}
		else if (_tcsicmp(value, L"5") == 0) //韩语 韩语北 韩语南

		{
			language = SONG_LANGUAGE_KOREAN;
			_tcscpy(language_ab, L"韩");
		}
		else if (_tcsicmp(value, L"8") == 0) //泰语
		{
			language = SONG_LANGUAGE_THAI;
			_tcscpy(language_ab, L"泰");
		}
		else if (_tcsicmp(value,L"9")==0)  //蒙语
		{
			language = SONG_LANGUAGE_MONGOLIA;
			_tcscpy(language_ab,L"蒙");
		}
		else if (_tcsicmp(value,L"10")==0) //俄语
		{
			language = SONG_LANGUAGE_RUSSIAN;
			_tcscpy(language_ab,L"俄");
		}
		else if (0==_tcsicmp(value,L"其他"))
		{
			language = SONG_LANGUAGE_OTHERS;
			_tcscpy(language_ab,L"其他");
		}
		//以下为电影定义


		else if (_tcsnicmp(value, L"中国", sizeof(L"中国") / sizeof(TCHAR) ) == 0)
		{
			language = SONG_LANGUAGE_CHINESE;
			_tcscpy(language_ab, L"国");
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
		//删除特殊字符
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
		else if ((_tcsicmp(value, L"2") == 0)) //风景
		{
			song_version = SONG_VERSION_VIEW;
		}
		else if (_tcsicmp(value, L"5") == 0)  //故事  故事情节
		{
			song_version = SONG_VERSION_STORY;
		}
		else if (_tcsicmp(value, L"4") == 0) //人物
		{
			song_version = SONG_VERSION_PERSON;
		}
		else if (_tcsicmp(value, L"3") == 0) //演唱会  演唱
		{
			song_version = SONG_VERSION_CONCERT;
		}
		else if (_tcsicmp(value, L"7") == 0) //欣赏版 欣赏
		{
			song_version = SONG_VERSION_ENJOY;
		}
		else if ((_tcsicmp(value, L"6") == 0) || (_tcsicmp(value, L"8") == 0)) //影视版 影视题材
		{
			song_version = SONG_VERSION_MOVIE;
		}
		else if (_tcsicmp(value,L"10") == 0)  //迪曲
		{
			song_version = SONG_VERSION_DJ;
		}
		else if (_tcsicmp(value,L"11") == 0)  //舞曲
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
		else if (_tcsicmp(value,L"13") == 0)  //百度
		{
			song_version = SONG_VERSION_BAIDU;
		}
		else if (_tcsicmp(value,L"14") == 0)  //QQ
		{
			song_version = SONG_VERSION_QQ;
		}
		else if (_tcsicmp(value,L"15") == 0)  //酷狗
		{
			song_version = SONG_VERSION_KUGOU;
		}
		else if (_tcsicmp(value,L"16") == 0)  //酷我
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
		//删除特殊字符
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
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"Х");
				}
				break;
			default:
				wcscpy(song_language,L"国语");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_YUE:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"Х");
				}
				break;
			default:
				wcscpy(song_language,L"粤语");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_MINNAN:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"Х");
				}
				break;
			default:
				wcscpy(song_language,L"闽语");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_ENGLISH:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"А");
				}
				break;
			default:
				wcscpy(song_language,L"英语");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_JAPANESE:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"Я");
				}
				break;
			default:
				wcscpy(song_language,L"日语");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_KOREAN:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"С");
				}
				break;
			default:
				wcscpy(song_language,L"韩语");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_THAI:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"泰");
				}
				break;
			default:
				wcscpy(song_language,L"泰语");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_MONGOLIA:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"М");
				}
				break;
			default:
				wcscpy(song_language,L"蒙语");
				break;
			}
		}
		break;
	case SONG_LANGUAGE_RUSSIAN:
		{
			switch(g_flash_use_language)
			{
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"О");
				}
				break;
			default:
				wcscpy(song_language,L"俄语");
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
			case FLASH_LANGUAGE_MONGOLIA:  //蒙语
				{
					wcscpy(song_language,L"外");
				}
				break;
			default:
				wcscpy(song_language,L"外语");
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
		wcscpy(song_language,L"国语");
		break;
	case SONG_LANGUAGE_YUE:
		wcscpy(song_language,L"粤语");
		break;
	case SONG_LANGUAGE_MINNAN:
		wcscpy(song_language,L"闽南语");
		break;
	case SONG_LANGUAGE_ENGLISH:
		wcscpy(song_language,L"英语");
		break;
	case SONG_LANGUAGE_JAPANESE:
		wcscpy(song_language,L"日语");
		break;
	case SONG_LANGUAGE_KOREAN:
		wcscpy(song_language,L"韩语");
		break;
	case SONG_LANGUAGE_THAI:
		wcscpy(song_language,L"泰语");
		break;
	case SONG_LANGUAGE_MONGOLIA:
		wcscpy(song_language,L"蒙语");
		break;
	case SONG_LANGUAGE_RUSSIAN:
		wcscpy(song_language,L"俄语");
		break;
	case SONG_LANGUAGE_OTHERS:
		wcscpy(song_language,L"外语");
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
	case SONG_LANGUAGE_CHINESE: return L"国语";
	case SONG_LANGUAGE_YUE: return L"粤语";
	case SONG_LANGUAGE_MINNAN: return L"闽南语";
	case SONG_LANGUAGE_ENGLISH: return L"英语";
	case SONG_LANGUAGE_JAPANESE: return L"日语";
	case SONG_LANGUAGE_KOREAN: return L"韩语";
	case SONG_LANGUAGE_THAI: return L"泰语";
	case SONG_LANGUAGE_MONGOLIA:  return L"蒙语";
	case SONG_LANGUAGE_RUSSIAN:   return L"俄语";
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
		case SONG_VERSION_UNKNOWN:    //未知
			{
				wcscpy(value,L"未知");
				version = SONG_VERSION_UNKNOWN;
			}
			break;
		case SONG_VERSION_CONCERT:	  //演唱会

			{
				wcscpy(value,L"演唱会");
				version = SONG_VERSION_CONCERT;
			}
			break;
		case SONG_VERSION_ENJOY:      //欣赏版

			{
				wcscpy(value,L"欣赏");
				version = SONG_VERSION_ENJOY;
			}
			break;
		case SONG_VERSION_MTV:	      //MTV
			{
				wcscpy(value,L"MTV");
				version = SONG_VERSION_MTV;
			}
			break;
		case SONG_VERSION_VIEW:	      //风景
			{
				wcscpy(value,L"风景");
				version = SONG_VERSION_VIEW;
			}
			break;
		case SONG_VERSION_STORY:	  //故事情节
			{
				wcscpy(value,L"故事");
				version = SONG_VERSION_STORY;
			}
			break;
		case SONG_VERSION_PERSON:	  //人物
			{
				wcscpy(value,L"人物");
				version = SONG_VERSION_PERSON;
			}
			break;
		case SONG_VERSION_MOVIE:   //影视版 影视题材
			{
				_tcscpy(value,L"影视");
				version = SONG_VERSION_MOVIE;
			}
			break;
		case SONG_VERSION_DJ://迪曲
			{
				_tcscpy(value,L"迪曲");
				version = SONG_VERSION_DJ;
			}
			break;
		case SONG_VERSION_DANCE://舞曲
			{
				_tcscpy(value,L"舞曲");
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
				_tcscpy(value,L"高清");
				version = SONG_VERSION_HD;
			}
			break;
		case SONG_VERSION_BAIDU://HD
			{
				_tcscpy(value,L"百度音乐");
				version = SONG_VERSION_BAIDU;
			}
			break;
		case SONG_VERSION_QQ://HD
			{
				_tcscpy(value,L"QQ音乐");
				version = SONG_VERSION_QQ;
			}
			break;
		case SONG_VERSION_KUGOU://HD
			{
				_tcscpy(value,L"酷狗音乐");
				version = SONG_VERSION_KUGOU;
			}
			break;
		case SONG_VERSION_KUWO://HD
			{
				_tcscpy(value,L"酷我音乐");
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
			//录音视频路径是独立的一个字段
			if (0==_tcscmp(recorder_video_path,L""))
			{
				return false;
			}
			_tcscpy(value,recorder_video_path);
			//连接服务器编号置成-1，表示不是服务器路径
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
			//背景视频文件路径//yzg
			_tcscpy(value, m_song_bk_path);

			//连接服务器编号置成-1，表示不是服务器路径
			link_server = -1;
			return true;
		}
		else
		{
			//本地路径优先，服务器路径次之
			if ((0!=_tcscmp(local_path,L""))&&((0==_tcsncmp(local_path,L"hik:",4))||(0==_tcsncmp(local_path,L"udp:",4))||(0==_tcsncmp(local_path,L"shn:",4))||(PathFileExists(local_path))))
			{
				_tcscpy(value,local_path);
				//连接服务器编号置成-1，表示不是服务器路径
				link_server = -1;
				return true;
			}

			//设置手动服务器 -- add by caizw
			if (m_server_manually_index > -1) //如果设置了
			{
				//得到访问路径
				if ((0!=_tcscmp(server_path[m_server_manually_index],L""))&&(0!=_tcscmp(song_relative_path,L"")))
				{
					if (check_file_exist && (0!=_tcsncmp(server_path[m_server_manually_index],L"udp:",4)))
					{
						//2010-08-25 add
						//如果检测文件是否存在，提前ping一下服务器是否存在
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
						//检测文件是否存在
						if (PathFileExists(path))
						{
							//判断一下文件是否存在
							_tcscpy(value,path);
							//返回选择的服务器编号
							link_server = m_server_manually_index;
							return true;
						}
					}
					else
					{
						//不检测
						_tcscpy(value,path);
						//返回选择的服务器编号
						link_server = m_server_manually_index;
						return true;
					}
				}
				return false;
			}

			//服务器一共6个路径
			for (int i=0;i<6;i++)
			{
				memset(path,0x0,sizeof(path));

				//得到要访问的服务器编号
				server_sort = (link_server+i)%6;
				//得到访问路径
				if ((0!=_tcscmp(server_path[server_sort],L""))&&(0!=_tcscmp(song_relative_path,L"")))
				{
					if (check_file_exist && (0!=_tcsncmp(server_path[server_sort],L"udp:",4)))
					{
						//2010-08-25 add
						//如果检测文件是否存在，提前ping一下服务器是否存在
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
						//检测文件是否存在
						if (PathFileExists(path))
						{
							//判断一下文件是否存在
							_tcscpy(value,path);
							//返回选择的服务器编号
							link_server = server_sort;
							return true;
						}
					}
					else
					{
						//不检测
						_tcscpy(value,path);
						//返回选择的服务器编号
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
			//录音视频路径是独立的一个字段


			if (0==_tcscmp(recorder_video_path,L""))
			{
				return false;
			}
			//分离出来服务器IP
			_tcscpy(song_path,recorder_video_path);
			_tcschr(song_path+3,'\\')[0]='\0';
			_tcscpy(value,song_path);			
			return true;
		}
		else
		{
			//服务器一共6个路径


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
			//原唱音轨
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
			//伴唱音轨
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
			//原唱音轨
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
			//伴唱音轨
			if (0!=_tcscmp(accompany_sing_track,L""))
			{
				_tcscpy(song_track,accompany_sing_track);
			}
			else
			{
				return false;
			}
		}
		//转化成整形


		if (_tcscmp(song_track, L"左")==0)
		{
			channel_track = 'L';
		}
		else if (_tcscmp(song_track, L"右")==0)
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
					// 原唱不能为负值


					channel_track = 2;
				}
				else
				{
					// 伴唱不能为负值


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
		//原唱音量
		volume = karaoke_volume;
	}
	else
	{
		//伴唱音量
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
			_tcscpy(value,L"动作片");
		}
		break;
	case 2:
		{
			_tcscpy(value,L"爱情片");
		}
		break;
	case 3:
		{
			_tcscpy(value,L"喜剧片");
		}
		break;
	case 4:
		{
			_tcscpy(value,L"战争片");
		}
		break;
	case 5:
		{
			_tcscpy(value,L"剧情片");
		}
		break;
	case 6:
		{
			_tcscpy(value,L"科幻片");
		}
		break;
	case 7:
		{
			_tcscpy(value,L"恐怖片");
		}
		break;
	case 8:
		{
			_tcscpy(value,L"动画片");
		}
		break;
	case 9:
		{
			_tcscpy(value,L"另类片");
		}
		break;
	case 10:
		{
			_tcscpy(value,L"文艺片");
		}
		break;
	case 11:
		{
			_tcscpy(value,L"相声");
		}
		break;
	case 12:
		{
			_tcscpy(value,L"小品");
		}
		break;
	case 13:
		{
			_tcscpy(value,L"大型活动");
		}
		break;
	case 14:
		{
			_tcscpy(value,L"演唱会");
		}
		break;
	case 15:
		{
			_tcscpy(value,L"公司活动");
		}
		break;
	default:
		{
			_tcscpy(value,L"未  知");
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
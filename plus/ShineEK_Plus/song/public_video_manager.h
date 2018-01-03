#pragma once

#include "song_info.h"
#include "..\database\DBQuery.h"

//空闲视频最大数
#define IDLESSE_VIDEO_MAX_NUMBER     100

typedef struct st_time
{
	int iBegin;
	int iEnd;
	int iCount;
	song_info SongInfo[IDLESSE_VIDEO_MAX_NUMBER];
	st_time()
	{
		iBegin = 0;
		iEnd = 0;
		iCount = 0;
		for (int m=0;m<IDLESSE_VIDEO_MAX_NUMBER;m++)
		{
			SongInfo[m].initialized_variables();
		}
	}
}IDLESSE_BY_TIME;

class public_video_manager
{
public:
	public_video_manager(void);
	~public_video_manager(void);

	/*
	功能：初始化成员变量
	参数：
	    void
	返回值：
	    true：成功
		false：失败
	*/
	bool initialize(TCHAR *ip);

	/*
	功能：通过歌曲名字，查询歌曲信息
	参数：
	    db_query_class：数据库查询类
	返回值：
	    void
	*/
	void query_idlesse_song_info(DB_Query &db_query_class);

	/*
	功能：得到开始视频信息
	参数：
	    video_info：视频信息
	返回值：
		true：成功
		false：失败
	*/
	bool get_begin_video(song_info& video_info);
	/*
	功能：得到结束视频
	参数：
	    video_info：视频信息
	返回值：
		true：成功
		false：失败
	*/
	bool get_end_video(song_info& video_info);
	/*
	功能：得到空闲视频
	参数：
	    video_info：视频信息
	返回值：
		true：成功
		false：失败
	*/
	bool get_idlesse_video(song_info& video_info);

	/*
	功能：得到要播放的气氛音频文件路径
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
	功能：获得当前播放的空闲歌曲的索引
	参数：		
	返回值：
	    索引值
	*/
	int get_cur_idlesse_video_number(){return cur_idlesse_video_number;}

	/*
	功能：设置当前播放的空闲歌曲的索引
	参数：
		number:索引值
	返回值：
	    
	*/
	void set_cur_idlesse_video_number(int number){cur_idlesse_video_number = number;}

	/*
	功能：设置空闲歌曲按照时间播放空闲
	参数：
		number:索引值
	返回值：
	*/
	void set_cur_idlesse_list();

private:
	song_info begin_video;                             //开始视频
	song_info end_video;                               //结束视频
	song_info idlesse_video[IDLESSE_VIDEO_MAX_NUMBER]; //空闲视频
	int cur_idlesse_video_number;                      //空闲视频编号，从1-99，中间不能间断
	int m_idlesse_video_total_count;                   //空闲视频歌曲总数
	TCHAR m_idlesse_video_directory[256];              //公视路径
	TCHAR m_install_path[256];                         //安装路径
	TCHAR m_atmosphere_video_path[256];                //气氛音频路径
	TCHAR m_environment_audio_path[256];               //环境音频路劲
	int m_idlesse_video_volume;                        //空闲视频的音量
	int m_relay_parameter;

	IDLESSE_BY_TIME m_idless_by_time[IDLESSE_VIDEO_MAX_NUMBER];
	int m_idless_by_time_count;
	int m_idless_by_time_idx;
	song_info default_idlesse_video[IDLESSE_VIDEO_MAX_NUMBER];
	int default_idlesse_video_count;
	bool m_idlesse_video_type;
};

#ifndef _SONG_INFO_H_
#define _SONG_INFO_H_

#include "song_Variable.h"

#include <string>
#include <shlwapi.h>

using namespace std;

class song_info
{
public:
	song_info(void);
	~song_info(void);

	void initialized_variables(void);

	//所有参数的赋值操作
	bool set_song_id(const TCHAR *value);
	bool set_accompany_sing_track(const TCHAR *value);
	bool set_karaoke_track(const TCHAR *value);
	bool set_guid_track(const TCHAR *value);
	bool set_song_name(const TCHAR *value);
	bool set_movie_name(const TCHAR *value);
	bool set_song_sort(int value);
	bool set_accompany_volume(int value);
	bool set_karaoke_volume(int value);
	bool set_language(const TCHAR *value);
	bool set_song_type(const TCHAR *value);
	bool set_singer_name(const TCHAR *value);
	bool set_singer_sex(const TCHAR *value);
	bool set_song_version(const TCHAR *value);
	bool set_light_control_set(int value);
	bool set_audio_effect_code(int value);
	bool set_file_format(const TCHAR *value);
	bool set_local_path(const TCHAR *value);
	bool set_server_path1(const TCHAR *value);
	bool set_server_path2(const TCHAR *value);
	bool set_server_path3(const TCHAR *value);
	bool set_server_path4(const TCHAR *value);
	bool set_server_path5(const TCHAR *value);
	bool set_server_path6(const TCHAR *value);
	bool set_song_relative_path(const TCHAR *value);
	bool set_video_saturation(int value);
	bool set_video_luminance(int value);
	bool set_video_contrast(int value);
	bool set_lyric(const TCHAR *value);
// 	bool set_lyric_path(const TCHAR *value);//设置歌词文件路径
	bool set_song_bk_path(const TCHAR *value);//设置背景视频路径
	bool set_culture_code(const TCHAR *value);
	bool set_preview_path(const TCHAR *value);
	bool set_recorder_video_path(const TCHAR *value);
	bool set_recorder_wave_path(const TCHAR *value);
	bool set_recorder_start_time(int value);
	bool set_recorder_datatime(const TCHAR *value);
	bool set_movie_region(const TCHAR *value);
	bool set_movie_story(int value);
	void set_video_type(enum PLAY_SONG_TYPE select_video_type);
	bool set_singer_id1(const TCHAR *value);
	bool set_singer_id2(const TCHAR *value);
	bool set_singer_id3(const TCHAR *value);
	bool set_singer_id4(const TCHAR *value);
	bool set_file_version(const TCHAR *value); 
	bool set_recorder_score(int value);
	bool set_recorder_exist_video_path(bool value);
	bool set_music_enjoy(int value);
	bool set_down_update_song(int down_update_song);
	void set_flash_page_code(int page_code);

	bool get_song_id(TCHAR *value);
	bool get_accompany_sing_track(TCHAR *value);
	bool get_karaoke_track(TCHAR *value);
	bool get_guid_track(TCHAR *value);
	bool get_song_name(TCHAR *value);
	bool get_moive_name(TCHAR *value);
	int get_song_sort(void);
	int get_accompany_volume(void);
	int get_karaoke_volume(void);
	bool get_song_language(TCHAR *song_language);
	bool get_handheld_song_language(TCHAR *song_language);
	const TCHAR* get_language_string();
	bool get_singer_name(TCHAR *value);
	bool get_singer_sex(TCHAR *value);
	bool get_song_version(TCHAR *value,int &version);
	int get_light_control_set(void);
	int get_audio_effect_code(void);
	bool get_local_path(TCHAR *value);
	bool get_all_server_path(TCHAR value[][256]);
	bool get_song_relative_path(TCHAR *value);	
	int get_video_saturation(void);
	int get_video_luminance(void);
	int get_video_contrast(void);
	bool get_lyric(TCHAR *lyric);
// 	bool get_lyric_path(TCHAR *lyric_path);//获取歌词文件存放路径
	bool get_song_bk_path(TCHAR *song_bk_path);//获取背景视频存放路径
	bool get_culture_code(TCHAR *code);
	bool get_preview_path(TCHAR *value);
	bool get_singer_id1(TCHAR *value);
	bool get_singer_id2(TCHAR *value);
	bool get_singer_id3(TCHAR *value);
	bool get_singer_id4(TCHAR *value);
	bool get_file_version(TCHAR *value); 
	bool get_recorder_exist_video_path();
	int  get_down_update_song();
	bool get_song_type(TCHAR *value);
	int get_flash_page_code();

	/*
	功能：从所有路径中，得到一个路径，进行播放
	参数：
	value：得到的路径
	check_file_exist：检测文件是否存在
	link_server：连接的服务器
	返回值：
	true：成功
	false：失败
	*/
	bool get_path(TCHAR *value,bool check_file_exist,int &link_server);

	/*
	功能：从所有服务器中，得到服务IP
	参数：
	value：得到的路径
	返回值：
	true：成功
	false：失败
	*/
	bool get_server_ip(TCHAR *value);

	/*
	功能：得到音轨
	参数;
	channel[in]：原唱还是伴唱音轨。true：原唱 false:伴唱
	channel_track[out]：输出的音轨
	返回值：
	true：成功
	false:失败
	*/
	bool get_channel_track(bool channel,TCHAR *channel_track);
	bool get_preview_channel_track(bool channel,byte &channel_track);

	/*
	功能：得到文件的格式
	参数：
	void
	返回值：
	SONG_FORMAT：文件的格式
	*/
	enum SONG_FORMAT get_file_format(void);
	bool get_file_format_string(TCHAR *value);

	/*
	功能：得到音量
	参数：
	channel[in]：原唱还是伴唱音量。true：原唱 false:伴唱
	返回值：
	音量
	*/
	int get_volume(bool channel);


	bool get_video_path(TCHAR *value);
	bool get_wave_path(TCHAR *value);
	int get_recorder_start_time(void);
	bool get_recorder_datetime(TCHAR *value);
	int get_recorder_score(void);
	enum PLAY_SONG_TYPE get_video_type(void);
	bool get_movie_region(TCHAR *value);
	int get_movie_story(void);
	bool get_movie_story(TCHAR *value);
	int get_music_enjoy();
	void set_server_manually_idx(int idx){m_server_manually_index = idx;}
private:
	TCHAR song_id[128];				//歌曲编号
	TCHAR accompany_sing_track[4];	//歌曲伴唱音轨（分左右声道和4种音轨）
	TCHAR karaoke_track[4];			//歌曲原唱音轨（分左右声道和4种音轨）
	TCHAR guid_track[4];            //歌曲导唱音轨
	TCHAR m_song_name[256];	    	//歌曲名称
	TCHAR m_movie_name[256];        //歌曲对应的电影名字
	int m_song_sort;                //歌曲排序
	int	accompany_volume;			//伴唱音量
	int karaoke_volume;				//原唱音量
	enum SONG_LANGUAGE language;	//语种（国、粤、闽、英、日、韩）
	TCHAR song_type[16];			//曲种（京剧、通俗、黄梅戏…..）
	TCHAR singer_name[64];			//歌星名
	TCHAR singer_sex[64];           //歌星性别
	enum SONG_VERSION song_version;	//歌曲的版本号（风景、MTV、故事情节、演唱会、人物）
	int light_control_set;			//现用于灯控的设置
	int audio_effect_code;          //音效码值
	enum SONG_FORMAT file_format;	//文件格式
	TCHAR local_path[128];			//本地的歌曲路径（多用于单机版）
	TCHAR server_path[6][64];		//歌曲服务器路径（如：\\server）
	TCHAR song_relative_path[128];  //歌曲具体路径，与路径1..组成完整的网络路径（如：\jp01\000001.mpg）
	int	video_saturation;			//歌曲视频的饱和度
	int	video_luminance;			//歌曲视频的亮度
	int	video_contrast;				//歌曲视频的对比度
	TCHAR m_lyric[256];			    //歌曲歌词
	TCHAR culture_code[128];			//文化部编码
	TCHAR preview_path[128];		//预览路径（用于歌曲预览）

	TCHAR singer_id1[24];           //歌星id1
	TCHAR singer_id2[24];           //歌星id2
	TCHAR singer_id3[24];			//歌星id3
	TCHAR singer_id4[24];			//歌星id3
	TCHAR file_version[24];			//歌曲版本号 1.0

	//保存录音使用的字段
	TCHAR recorder_video_path[128]; //歌曲视频路径
	TCHAR recorder_wave_path[128];  //录的音频路径
	int recorder_start_time;        //开始时间
	TCHAR recorder_datatime[32];    //录音的日期
	int recorder_score;                //录音分数
	bool recorder_exist_video_path;        //录音文件视频路径是否存在
	enum PLAY_SONG_TYPE video_type; //视频类型，0：正常选择的歌曲  1：录音歌曲

	//电影附加字段
	TCHAR movie_region[64];         //电影的归属地
	int movie_story;                //电影的故事情节

	//为了操作方便，记录一些值
	TCHAR language_ab[16];          //语言的缩写，只保留一个字
	int music_enjoy;				//音乐欣赏的标记 0：为其他平台 1：为音乐欣赏平台
	int down_update_song;           //当前歌曲是否是下载歌曲 0:本地歌曲 1:下载歌曲 2:更新歌曲
	int flash_page_code;
	
// 	TCHAR m_lyric_path[256];		//歌词文件路径
	TCHAR m_song_bk_path[256];		//背景视频路径

	int m_server_manually_index;
};


#endif

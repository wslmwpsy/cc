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

	//���в����ĸ�ֵ����
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
// 	bool set_lyric_path(const TCHAR *value);//���ø���ļ�·��
	bool set_song_bk_path(const TCHAR *value);//���ñ�����Ƶ·��
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
// 	bool get_lyric_path(TCHAR *lyric_path);//��ȡ����ļ����·��
	bool get_song_bk_path(TCHAR *song_bk_path);//��ȡ������Ƶ���·��
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
	���ܣ�������·���У��õ�һ��·�������в���
	������
	value���õ���·��
	check_file_exist������ļ��Ƿ����
	link_server�����ӵķ�����
	����ֵ��
	true���ɹ�
	false��ʧ��
	*/
	bool get_path(TCHAR *value,bool check_file_exist,int &link_server);

	/*
	���ܣ������з������У��õ�����IP
	������
	value���õ���·��
	����ֵ��
	true���ɹ�
	false��ʧ��
	*/
	bool get_server_ip(TCHAR *value);

	/*
	���ܣ��õ�����
	����;
	channel[in]��ԭ�����ǰ鳪���졣true��ԭ�� false:�鳪
	channel_track[out]�����������
	����ֵ��
	true���ɹ�
	false:ʧ��
	*/
	bool get_channel_track(bool channel,TCHAR *channel_track);
	bool get_preview_channel_track(bool channel,byte &channel_track);

	/*
	���ܣ��õ��ļ��ĸ�ʽ
	������
	void
	����ֵ��
	SONG_FORMAT���ļ��ĸ�ʽ
	*/
	enum SONG_FORMAT get_file_format(void);
	bool get_file_format_string(TCHAR *value);

	/*
	���ܣ��õ�����
	������
	channel[in]��ԭ�����ǰ鳪������true��ԭ�� false:�鳪
	����ֵ��
	����
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
	TCHAR song_id[128];				//�������
	TCHAR accompany_sing_track[4];	//�����鳪���죨������������4�����죩
	TCHAR karaoke_track[4];			//����ԭ�����죨������������4�����죩
	TCHAR guid_track[4];            //������������
	TCHAR m_song_name[256];	    	//��������
	TCHAR m_movie_name[256];        //������Ӧ�ĵ�Ӱ����
	int m_song_sort;                //��������
	int	accompany_volume;			//�鳪����
	int karaoke_volume;				//ԭ������
	enum SONG_LANGUAGE language;	//���֣�������������Ӣ���ա�����
	TCHAR song_type[16];			//���֣����硢ͨ�ס���÷Ϸ��..��
	TCHAR singer_name[64];			//������
	TCHAR singer_sex[64];           //�����Ա�
	enum SONG_VERSION song_version;	//�����İ汾�ţ��羰��MTV��������ڡ��ݳ��ᡢ���
	int light_control_set;			//�����ڵƿص�����
	int audio_effect_code;          //��Ч��ֵ
	enum SONG_FORMAT file_format;	//�ļ���ʽ
	TCHAR local_path[128];			//���صĸ���·���������ڵ����棩
	TCHAR server_path[6][64];		//����������·�����磺\\server��
	TCHAR song_relative_path[128];  //��������·������·��1..�������������·�����磺\jp01\000001.mpg��
	int	video_saturation;			//������Ƶ�ı��Ͷ�
	int	video_luminance;			//������Ƶ������
	int	video_contrast;				//������Ƶ�ĶԱȶ�
	TCHAR m_lyric[256];			    //�������
	TCHAR culture_code[128];			//�Ļ�������
	TCHAR preview_path[128];		//Ԥ��·�������ڸ���Ԥ����

	TCHAR singer_id1[24];           //����id1
	TCHAR singer_id2[24];           //����id2
	TCHAR singer_id3[24];			//����id3
	TCHAR singer_id4[24];			//����id3
	TCHAR file_version[24];			//�����汾�� 1.0

	//����¼��ʹ�õ��ֶ�
	TCHAR recorder_video_path[128]; //������Ƶ·��
	TCHAR recorder_wave_path[128];  //¼����Ƶ·��
	int recorder_start_time;        //��ʼʱ��
	TCHAR recorder_datatime[32];    //¼��������
	int recorder_score;                //¼������
	bool recorder_exist_video_path;        //¼���ļ���Ƶ·���Ƿ����
	enum PLAY_SONG_TYPE video_type; //��Ƶ���ͣ�0������ѡ��ĸ���  1��¼������

	//��Ӱ�����ֶ�
	TCHAR movie_region[64];         //��Ӱ�Ĺ�����
	int movie_story;                //��Ӱ�Ĺ������

	//Ϊ�˲������㣬��¼һЩֵ
	TCHAR language_ab[16];          //���Ե���д��ֻ����һ����
	int music_enjoy;				//�������͵ı�� 0��Ϊ����ƽ̨ 1��Ϊ��������ƽ̨
	int down_update_song;           //��ǰ�����Ƿ������ظ��� 0:���ظ��� 1:���ظ��� 2:���¸���
	int flash_page_code;
	
// 	TCHAR m_lyric_path[256];		//����ļ�·��
	TCHAR m_song_bk_path[256];		//������Ƶ·��

	int m_server_manually_index;
};


#endif

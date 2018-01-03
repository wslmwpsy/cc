#pragma once

#include "song_info.h"
#include "..\database\DBQuery.h"

//������Ƶ�����
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
	���ܣ���ʼ����Ա����
	������
	    void
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool initialize(TCHAR *ip);

	/*
	���ܣ�ͨ���������֣���ѯ������Ϣ
	������
	    db_query_class�����ݿ��ѯ��
	����ֵ��
	    void
	*/
	void query_idlesse_song_info(DB_Query &db_query_class);

	/*
	���ܣ��õ���ʼ��Ƶ��Ϣ
	������
	    video_info����Ƶ��Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_begin_video(song_info& video_info);
	/*
	���ܣ��õ�������Ƶ
	������
	    video_info����Ƶ��Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_end_video(song_info& video_info);
	/*
	���ܣ��õ�������Ƶ
	������
	    video_info����Ƶ��Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_idlesse_video(song_info& video_info);

	/*
	���ܣ��õ�Ҫ���ŵ�������Ƶ�ļ�·��
	������
	    wave_type�������Ƶ����
		audio_path����Ƶ·��
		picture_path��ͼƬ·��
		soft_code�����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_atmosphere_wave_info(int wave_type,TCHAR *audio_path,TCHAR *picture_path,bool soft_code);

	/*
	���ܣ��õ�Ҫ���ŵĻ�����Ƶ���ļ�·��
	������
		wave_type�������Ƶ����
		path��·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_environment_wave_info(int wave_type,TCHAR *path);

	/*
	���ܣ���õ�ǰ���ŵĿ��и���������
	������		
	����ֵ��
	    ����ֵ
	*/
	int get_cur_idlesse_video_number(){return cur_idlesse_video_number;}

	/*
	���ܣ����õ�ǰ���ŵĿ��и���������
	������
		number:����ֵ
	����ֵ��
	    
	*/
	void set_cur_idlesse_video_number(int number){cur_idlesse_video_number = number;}

	/*
	���ܣ����ÿ��и�������ʱ�䲥�ſ���
	������
		number:����ֵ
	����ֵ��
	*/
	void set_cur_idlesse_list();

private:
	song_info begin_video;                             //��ʼ��Ƶ
	song_info end_video;                               //������Ƶ
	song_info idlesse_video[IDLESSE_VIDEO_MAX_NUMBER]; //������Ƶ
	int cur_idlesse_video_number;                      //������Ƶ��ţ���1-99���м䲻�ܼ��
	int m_idlesse_video_total_count;                   //������Ƶ��������
	TCHAR m_idlesse_video_directory[256];              //����·��
	TCHAR m_install_path[256];                         //��װ·��
	TCHAR m_atmosphere_video_path[256];                //������Ƶ·��
	TCHAR m_environment_audio_path[256];               //������Ƶ·��
	int m_idlesse_video_volume;                        //������Ƶ������
	int m_relay_parameter;

	IDLESSE_BY_TIME m_idless_by_time[IDLESSE_VIDEO_MAX_NUMBER];
	int m_idless_by_time_count;
	int m_idless_by_time_idx;
	song_info default_idlesse_video[IDLESSE_VIDEO_MAX_NUMBER];
	int default_idlesse_video_count;
	bool m_idlesse_video_type;
};

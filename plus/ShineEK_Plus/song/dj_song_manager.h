#pragma once

#include "song_info.h"

#define DJ_SONG_MAX_COUNT 20

class dj_song_manager
{
public:
	dj_song_manager(void);
	~dj_song_manager(void);

	/*
	���ܣ�����dj����
	������
	    dj_song_info;DJ������Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool add_dj_song(song_info &dj_song_info);

	/*
	���ܣ��õ���һ�ײ��ŵ�dj����
	������
	    dj_song_info;DJ������Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_next_play_dj_song(song_info &dj_song_info);

	/*
	���ܣ��õ�dj������Ŀ
	������
	    void
	����ֵ��
	    ʵ�ʵ�dj������Ŀ
	*/
	int get_dj_song_count(void);

private:
	song_info m_dj_song_info[DJ_SONG_MAX_COUNT];
	int m_dj_song_count;      //dj������
	int m_cur_play_dj_number; //��ǰ���ŵ�dj�������
};

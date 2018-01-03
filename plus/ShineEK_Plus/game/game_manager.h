#pragma once

#include "..\message.h"

#define SHOW_GAME_MAX_COUNT   6   //��Ϸ�������ʾ��

class game_manager
{
public:
	game_manager(void);
	~game_manager(void);
	/*
	���ܣ��������е���Ϸ
	������
	    path����Ϸ·��
	����ֵ��
	    void
	*/
	void search_game(TCHAR *path);

	/*
	���ܣ��õ�Ҫ���ŵ���Ϸ·��
	������
	    path����Ϸ·��
		select_number��ѡ��ı��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_select_game_path(TCHAR *path,int select_number);

private:
	int m_game_total_count;                             //��Ϸ����
	SONG_GAME_STRUCT m_game_info[SHOW_GAME_MAX_COUNT];  //�洢��Ϸ��Ϣ
};

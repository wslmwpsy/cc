#pragma once

#include "../song/song_info.h"
#include "../message.h"
#include "../song/video_play_manager.h"

#include <string>
using namespace std;

#define U_DISK_SONG_MAX_COUNT    90

class U_disk_song
{
public:
	U_disk_song(void);
	~U_disk_song(void);
	/*
	���ܣ���������
	������
	    U_path��U��·��
		page_row_count��ҳ��ʾ������
	����ֵ��
	    true���ɹ�
		flase��ʧ��
	*/
	bool search_U_disk_song(TCHAR *U_path,int page_row_count);
	
	/*
	���ܣ��õ���������
	������
	    song_string�����صĸ����ַ���
		page_operate��ҳ��������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool make_U_disk_song_xml_list(std::wstring &song_xml_string,video_play_manager &video_manager,PAGE_OPERATE page_operate,std::wstring &default_color,std::wstring &select_color,std::wstring &playing_color);

	/*
	���ܣ��õ�ѡ��ĸ���
	������
	    select_number��ѡ�еı��
		U_song_info�����صĸ�����Ϣ
	����ֵ��
	    true:�ɹ�
		false��ʧ��
	*/
	bool get_U_disk_song_info(song_info &U_song_info,int select_number);

	/*
	���ܣ��õ���������ҳ����
	������
	   song_count��������
	   page_count��ҳ��
	   cur_page_number����ǰҳ���
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool get_song_row_and_page_count(int &song_count,int &page_count,int &cur_page_number);

private:
	SONG_GAME_STRUCT m_U_disk_song[U_DISK_SONG_MAX_COUNT];//U�̸���
	int m_song_total_count;                               //��������
	int m_list_show_row_count;                            //�б���ʾ�ĺ���
	int m_total_page_count;                               //�ܵ�ҳ��
	int m_cur_show_page_number;                           //��ǰ��ʾ��ҳ��
	int m_song_volume;                                    //��������
};

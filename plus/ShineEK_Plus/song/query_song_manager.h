#pragma once

#ifndef _QUERY_SONG_MANAGER_H_
#define _QUERY_SONG_MANAGER_H_

#include "song_info.h"
#include "song_Variable.h"
#include "..\song\video_play_manager.h"
#include "..\message.h"

#include <string>

using namespace std;

class query_song_manager
{
public:
	query_song_manager(void);
	~query_song_manager(void);

	/*
	���ܣ��Ѳ�ѯ�����ֵ�������б�
	������
	    query_song_result����ѯ�Ľ��
		result_item_number����ѯ�������ֶ���
		page_count:�ܹ���ҳ��
		cur_page_number����ǰҳ�ı��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number,int page_show_row_count);
	bool set_song_recorder_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number);
	bool set_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number);
	bool set_test_or_select_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,bool test_song);
	bool set_syn_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums);
	bool set_handheld_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums);
	bool set_handheld_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums);
	bool set_recommend_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int nPos,bool singer_song);
	bool set_song_all_recorder_list(std::wstring query_song_result[],int result_item_number,int result_column_nums);
	bool set_listen_recommend_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums, song_info *songinfo);

	/*
	���ܣ���֯��Ŀ����xml�ļ���flash����
	������
	    song_list_xml����ɵĽ�Ŀ��xml��ʽ���ַ���
		video_manager�����ŵ���Ƶ������
		color��������ɫ
	����ֵ��
	   true���ɹ�
	   false:ʧ��
	*/
	bool make_song_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_show_row_count,FLASH_SONG_SHOW_MODE song_show_mode,int page_index);
	bool make_movie_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_show_row_count);
	bool make_test_song_list_xml(std::wstring &song_list_xml);
	bool make_song_list_one_xml(song_info &song_information,int song_number,video_play_manager &video_manager,TCHAR *playing_song_number,TCHAR *song_show_info,FLASH_SONG_SHOW_MODE song_show_mode,int picture_number,int page_index);
	bool make_recommend_song_list(std::wstring &song_list_xml,video_play_manager &video_manager);
	bool make_recorder_song_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_index);
	bool make_music_enjoy_list_xml(std::wstring  &song_list_xml,video_play_manager &video_manager, ST_MUSIC_ENJOY *pSme, int count);
	/*
	���ܣ���ʼ������
	������
	    NULL
	����ֵ��
	    void
	*/
	void initialized_variables(void);
	
	/*
	���ܣ�ͨ���±�õ�ĳ�׸�ĸ�����Ϣ
	������
	    song_suffix�������±�
		song_infomation�����صĸ�����Ϣ
	����ֵ��
	    song_info��������Ϣ
	*/
	 bool get_song_info(int song_suffix,song_info &song_infomation);
	 bool get_recorder_song_info(TCHAR* song_number,song_info &song_infomation);
	 bool get_recorder_song_info(int song_suffix,song_info &song_infomation);
	 bool get_test_or_select_song_info(int song_suffix,song_info &song_infomation,bool test_song);
	 bool get_select_song_info(TCHAR *song_number,song_info &song_infomation);
	 bool get_select_movie_info(TCHAR *song_number,song_info &song_infomation);
	 bool get_handheld_song_info(int song_suffix,song_info &song_infomation);


	 /*
	 ���ܣ����Ը�������
	 ������
	     number��Ҫ���ȵı��
	 ����ֵ��
	     true���ɹ�
		 false��ʧ��
	 */
	 bool test_song_priority(int number);

	 /*
	 ���ܣ�����������ʾshow_movie_name
	 ������
	     number��Ҫ���ȵı��
	 ����ֵ��
	     true���ɹ�
		 false��ʧ��
	 */
	 void set_show_movie_name_flag(bool flag){m_theme_or_classification = flag;}
	 bool get_show_movie_name_flag(){return m_theme_or_classification;}

private:
	//��ѯ�����ĸ����б���Ϣ���
	song_info pre_page_song_list[PAGE_SHOW_MAX_ROW_COUNT];  //ǰһҳ
	song_info cur_page_song_list[PAGE_SHOW_MAX_ROW_COUNT];  //��ǰҳ
	song_info next_page_song_list[PAGE_SHOW_MAX_ROW_COUNT]; //��һҳ

	song_info test_page_song_list[SELECT_SONG_MAX_COUNT];  //����ҳ��ѡ������б�
	song_info m_movie_list[SELECT_SONG_MAX_COUNT];         //����ͬ����Ӱ���б�
	song_info m_handheld_song_list[HANDHELD_PAGE_SHOW_ROW_COUNT]; //�ֳָ����б�
	song_info m_recommend_song_list[RECOMMAND_SONG_INFO_COUNT];   //�Ƽ������б�
	song_info m_recorder_song_list[RECORDER_SHOW_PAGE_COUNT];   //¼��ҳ��

	bool song_list_exist;               //�����б��Ƿ����
	TCHAR m_singer_picture_path[256];   //����ͼƬ·��
	TCHAR m_song_picture_path[256];     //����ͼƬ·��
	TCHAR m_singer_sex_picture_path[256];//�����Ա�ͼƬ·��
	bool m_no_moive_name_show_lyric;    //û�е�Ӱ����ʾ���

	//������ѯʱ�����Ƶ�����
	int m_page_show_row_count;
	std::wstring m_default_song_color;   //Ĭ�ϸ�����ɫ
	std::wstring m_playing_song_color;   //�����Ÿ�������ɫ
	std::wstring m_select_song_color;    //ѡ�������ɫ
	bool m_theme_or_classification;		 //��������theme��classification , ��ʾshow_movie_name
};

#endif


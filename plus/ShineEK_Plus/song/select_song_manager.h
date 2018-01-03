#pragma once
#include "song_info.h"
#include "../database/DBDataTypeDef.h"
#include "..\message.h"

#define SELECT_SONG_MAX_COUNT   99

class select_song_manager
{
public:
	select_song_manager(void);
	~select_song_manager(void);

	/*
	���ܣ���ʼ��
	������
	    m_wnd�������ھ��
	����ֵ��
	    void
	*/
	void initialize(HWND m_wnd);
	/*
	���ܣ��õ�Ҫ���ŵĸ���
	����
	    song:�����Ļ�����Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��	   
	*/
    bool get_play_song(song_info& song);
	//�õ��������
	bool get_play_test_song(song_info& song);
	//ͨ���±�õ��������
	bool get_test_song_by_suffix(song_info& song,int song_suffix);

	/*
	���ܣ��õ���һ�׸�����Ϣ
	������
	    song:����������Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_next_song(song_info &song);
	/*
	���ܣ�ѡ��ĸ����Ƿ�Ϊ��
	������
	    void
	����ֵ��
	    true���գ�û�и�����
		false�����и����ɲ���
	*/
	bool empty();
	/*
	���ܣ������ܵ�ѡ��ĸ�����
	������
	    void
	����ֵ��
	    ѡ��ĸ�����
	*/
	int get_select_song_count(int count_type=0);
	
	/*
	���ܣ������ܵ��ѳ�������
	������
		void
	����ֵ��
		�ѳ��ĸ�����
	*/
	int get_sing_song_count(void);

	/*
	���ܣ����ѡ��ĸ���
	������
	    song��������Ϣ��
		priority���Ƿ�����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool add_select_song(song_info &song,bool priority);
	/*
	���ܣ������ݳ��ĸ���
	������
	    song:������Ϣ��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool add_sing_song(song_info &song);

	/*
	���ܣ��޸���ѡ�е�����/���±�ʾ
	������
	    song_id:����id
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool modify_down_load_select_song(TCHAR * song_id,TCHAR* server_path,int server_pos,TCHAR* relative_path = NULL);


	/*
	���ܣ���֯�ѳ�����ѡ������ʾ���ַ���
	������
	    song_list_xml��Ҫ��ʾ��xml�ַ���
		song_type��Ҫ��ʾ��ѡ���������ѳ�����
		page_operate��ҳ����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool make_song_list_xml(std::wstring &song_list_xml,enum SHOW_SONG_LIST_TYPE song_type,enum PAGE_OPERATE page_operate,FLASH_SONG_SHOW_MODE song_show_mode,int page_index);
	bool make_song_list_one_xml(song_info &song_information,int song_number,TCHAR *song_show_info,FLASH_SONG_SHOW_MODE song_show_mode,enum SHOW_SONG_LIST_TYPE song_type,int picture_number);

	/*
	���ܣ��õ��ѳ�����ѡ��ҳ����Ϣ
	������
		row���ܵ�����
		cur_page_number����ǰҳ�ı��
		total_page_count���ܵ�ҳ��
		song_type��Ҫ��ʾ��ѡ���������ѳ�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_page_row_info(int &row,int &cur_page_number,int &total_page_count,enum SHOW_SONG_LIST_TYPE song_type);

	/*
	���ܣ�ɾ��ѡ���ĳ������
	������
	    song_number�������ı��
		relative_position�����λ�ã�ture  ����λ�ã�false
	����ֵ��
	    �ɹ���ɾ���ĸ������
		ʧ�ܣ�-1
	*/
	int delete_select_song(int song_number,bool relative_position);
	int delete_select_song_by_id(TCHAR *song_id);

	/*
	���ܣ��õ�ѡ������ľ���λ��
	������
		 song_number�������ı��
	����ֵ��
	   ����λ��
	*/
	int get_select_song_absolute_position(int song_number);

	/*
	���ܣ�����ѡ��ĸ���
	������
	    song_number�������ı��
		relative_position�����λ�ã�ture  ����λ�ã�false
	����ֵ��
	     �ɹ������ȵĸ������
		ʧ�ܣ�-1
	*/
	int priority_select_song(int song_number,bool relative_position);

	/*
	���ܣ��϶�������ѡ�ĸ���
	������
		nOrigin�������ı��
		nDestination:Ŀ��λ�ã�����λ�ã�
		relative_position���϶��ĸ����Ƿ������λ�ã�ture  ����λ�ã�false
	����ֵ��
		�ɹ������ȵĸ������
		ʧ�ܣ�-1
	*/
	int drag_sort_select_song(int nOrigin, int nDestination, bool relative_position);

	bool random_sort_select_song();
	/*
	���ܣ�ͨ���±�õ�������Ϣ
	������
	    song_information[out]��������Ϣ
	    star_suffix[in]��ѡ��ĸ����±�
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_select_song_information(song_info &song_information, int star_suffix,bool relative_position);

	/*
	���ܣ�ͨ���±�õ�������Ϣ
	������
		song_information[out]��������Ϣ
		select_suffix[in]��ѡ��ĸ����±�
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_sing_song_information(song_info &song_information,int select_suffix,bool relative_position);

	/*
	���ܣ���ѡ��ĸ�������λ��
	������
	    first_switch_pos����һ��Ҫ������λ��
		sencond_switch_pos���ڶ���������λ��
		change_page_switch���øı���ҳ֮��Ľ���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool select_song_switch_position(int first_switch_pos,int second_switch_pos,bool change_page_switch);

	/*
	���ܣ�ͨ������ID����ѯĳ�׸������Ƿ��������ѡ������
	������
	    song_id��������ID
		play_number���ø��������Ĳ���˳��
	����ֵ��
	    true������
		false��������
	*/
	bool query_select_song_by_id(TCHAR *song_id,int &play_number, bool isDown = true);

	/*
	���ܣ�ͨ������ID����ѯĳ�׸������Ƿ��������ѡ������
	������
	    song_id��������ID
		play_number���ø��������Ĳ���˳��
	����ֵ��
	    true������
		false��������
	*/
	bool query_select_song_by_id_ex(TCHAR *song_id,int &play_number);

	/*
	���ܣ��ı䵱ǰ��ʾ��ҳ��
	������
	    page_number��Ҫ��ʾ��ҳ��
	����ֵ��
	    void
	*/
	void set_show_page_number(int page_number);

	/*
	���ܣ����ѡ��ĸ���
	������
	   void
   ����ֵ��
       void
	*/
	void clear_select_song(bool clear_sing);

	/*
	���ܣ��õ����Ը���������
	������
	    cur_song_name����ǰ����������
		next_song_name����һ������������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_test_song_name(TCHAR *cur_song_name,TCHAR *next_song_name);

	/*
	���ܣ����ò��Ը������ŵ�����һ�׻�����һ��
	������
	    next_song��true����һ�ף� false����һ��
	����ֵ��
	    void
	*/
	void set_test_song_play_order(bool next_song);

	/*
	���ܣ��ı�ҳ����
	������
	    pre_page��true����ǰһҳ���룬false�����һҳ����
		src_position������ڵ�ҳ�ĸ������
		first_page_insert��true����һ��ҳ���룬false�����ǵ�һ��
		change_song_xml�����صĸ���xml
	����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool change_page_insert(bool pre_page,int src_position,bool first_page_insert,std::wstring &change_song_xml);

	/*
	���ܣ��õ�Ҫ������item���
	������
	    void
	����ֵ��
	     Ҫ�����ı��
	*/
	int get_flicker_item_number(void);

	/*
	���ܣ�������ѡ����
	������
	    void
	����ֵ��
	    void
	*/
	void mess_selected_song(void);

private:
	song_info select_song[SELECT_SONG_MAX_COUNT];   //ѡ��ĸ���
	int select_song_count;                          //Ŀǰѡ��ĸ�����
	song_info sing_song[SELECT_SONG_MAX_COUNT];     //�ѳ��ĸ���
	int sing_song_count;                            //�ѳ���������

	int cur_show_page_number;                       //��ǰ��ʾ��ҳ��
	int total_page_number;                          //�ܵ�ҳ��

	int m_cur_page_first_position;                  //��ҳ����ʱ����ǰҳ����λ��
	int m_song_insert_position;                     //�����Ĳ���λ��

	int cur_select_test_song_number;                //��ǰѡ��Ĳ��Ը����±�
	bool m_test_next_song;                          //������һ������

	
	int m_page_show_row_count;                     //ÿҳ������ʾ������

	TCHAR m_sing_song_number[128];                  //�ѳ��ĸ������

	std::wstring m_default_song_row_color;         //Ĭ�ϸ�����ɫ
	std::wstring m_select_song_row_color;          //ѡ�������ɫ
	bool m_no_moive_name_show_lyric;               //û�е�Ӱ����ʾ���

	TCHAR m_singer_picture_path[256];              //����ͼƬ·��
	TCHAR m_song_picture_path[256];                //����ͼƬ·��
	TCHAR m_singer_sex_picture_path[256];          //�����Ա�ͼƬ·��

	//�����ھ��
	HWND m_parent_handle; 
};

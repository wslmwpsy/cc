#pragma once

#include "song_Variable.h"
#include "public_video_manager.h"
#include "select_song_manager.h"
#include "..\ministry_of_culture\VodADInterface.h"
#include "dj_song_manager.h"

class video_play_manager
{
public:
	video_play_manager(void);
	~video_play_manager(void);

	/*
	���ܣ���ʼ��
	������
		m_wnd�������ھ��
	����ֵ��
		void
	*/
	void initialize(HWND m_wnd,TCHAR *ip);

	/*
	���ܣ��õ�Ҫ���ŵ���Ƶ
	������
	    video_info����Ƶ��Ϣ
		ad_item�������
		play_ad���Ƿ񲥷Ź��
	����ֵ��
	    1������
		0�����
		-1��ʧ��
	*/
	int get_next_play_video(song_info& video_info,AD_ITEM_CULTURE *ad_item,bool play_ad);
	
	/*
	���ܣ��õ���һ��Ҫ���ŵĸ���
	������
	    song������������Ϣ��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_next_play_song(song_info& song);

	/*
	���ܣ��������ڲ��ŵ���Ƶ
	������
	    video_info����Ƶ��Ϣ��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_playing_video(song_info &video_info);

	/*
	���ܣ��õ����ڲ��ŵ���Ƶ
	������
	    video_info����Ƶ��Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_playing_video(song_info &video_info);
	/*
	���ܣ�����ѡ�еĸ�������ѡ������������
	����;
	    song_information��������Ϣ��
		priority���Ƿ�����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool add_select_song(song_info &song_information,bool priority);

	/*
	���ܣ����ѳ��ĸ����ŵ��ѳ������б���
	������
	    song_information������������Ϣ��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool add_sing_song(song_info &song_information);

	/*
	���ܣ��޸ĵ�ǰ����/���±�ʾ
	������
		song_id:����id
	����ֵ��
		true:�ɹ�
		false:ʧ��
	*/
	bool modify_down_load_select_song(TCHAR* song_id,TCHAR* server_path,int server_pos,TCHAR* relative_path = NULL);


	/*
	���ܣ�����Ŀǰ������������״̬
	������
	    void
	����ֵ��
	    PLAYER_PLAY_STATE������ϵͳĿǰ������״̬
	*/
	enum PLAYER_PLAY_STATE get_player_cur_state(void);
	enum PLAYER_PLAY_STATE get_player_next_state(void);

	/*
	���ܣ��ı䲥������״̬
	������
		player_state����������״̬
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool set_player_cur_state(enum PLAYER_PLAY_STATE player_state);
	bool set_player_next_state(enum PLAYER_PLAY_STATE player_state);

	/*
	���ܣ���֯������ʾ���ַ���
	������
		song_list_xml��Ҫ��ʾ��xml�ַ���
		song_type��Ҫ��ʾ��ѡ���������ѳ�����
		page_operate��ҳ����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool make_song_list_xml(std::wstring &song_list_xml,enum SHOW_SONG_LIST_TYPE song_type,enum PAGE_OPERATE page_operate,FLASH_SONG_SHOW_MODE song_show_mode,int page_index);

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
	���ܣ��õ�Ҫ���ŵ���Ƶ�ļ�·��
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
	���ܣ��õ���ѡ����������
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
		relative_position�����λ�ã�true  ����λ�ã�false
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
	���ܣ��õ��Ƿ���Ա��л���
	������
	    void
	����ֵ��
	    true�������е�
		false���������е�
	*/
	bool video_allow_cut(void);

	/*
	���ܣ�ͨ������ID����ѯĳ�׸������Ƿ��������ѡ������
	������
		song_id��������ID
		play_number���ø��������Ĳ���˳��
	����ֵ��
		true������
		false��������
	*/
	bool query_select_song_by_id(TCHAR *song_id,int &play_number,bool isDown = true);

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
	���ܣ�ͨ���±�õ��������
	������
	    song��������Ϣ
		song_suffix���������±�
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_test_song_by_suffix(song_info& song,int song_suffix);

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
	���ܣ��õ�dj������Ŀ
	������
		void
	����ֵ��
		ʵ�ʵ�dj������Ŀ
	*/
	int get_dj_song_count(void);

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
	���ܣ�ͨ���������֣���ѯ������Ϣ
	������
		db_query_class�����ݿ��ѯ��
	����ֵ��
		void
	*/
	void query_idlesse_song_info(DB_Query &db_query_class);

	/*
	���ܣ�������ѡ����
	������
	    void
	����ֵ��
	    void
	*/
	void mess_selected_song(void);

	/*
	���ܣ����ص�ǰ���е�����
	������
	����ֵ��
	   int
	*/
	int get_cur_idlesse_video_number();

	/*
	���ܣ����õ�ǰ���е�����
	������
		number
	����ֵ��
	   void
	*/
	void set_cur_idlesse_video_number(int number);

	/*
	���ܣ����ÿ��и�������ʱ�䲥�ſ���
	������
		number:����ֵ
	����ֵ��
	*/
	void set_cur_idlesse_list();

private:
	enum PLAYER_PLAY_STATE player_cur_state;      //��������ǰ������״̬
	enum PLAYER_PLAY_STATE player_next_state;     //��������������һ��״̬
	public_video_manager m_public_video_manager;  //������Ƶ�������
	select_song_manager m_select_song_manager;    //��ѡ���ѳ�����������
	song_info m_playing_video;                    //���ڲ��ŵ���Ƶ
	dj_song_manager m_dj_song_manager;            //dj�������Ź�����
	bool playing_video_exist;                     //�Ƿ�������ڲ��ŵ���Ƶ

	//ad
	bool m_allow_cut;                            //����Ƿ������е�
	bool m_first_begin_ad;                       //��һ���������
};

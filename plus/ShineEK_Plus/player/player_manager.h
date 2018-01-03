#pragma once

#include "player.h"
#include "../song/song_info.h"
#include "player_hard.h"
#include "../message.h"

#include <Mmsystem.h>

class player_manager
{
public:
	player_manager(void);
	~player_manager(void);
	/*
	���ܣ�ע�Ქ�����ؼ�
	����:
	    path����װ·��
	����ֵ��
	   void
	*/
	void register_player_ocx(TCHAR *path);
	/*
	���ܣ�ж�ز��ſؼ�
	������
	    void
	����ֵ��
	    void
	*/
	void unregister_player_ocx(void);
	/*
	���ܣ�����������
	������
	    void
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool create_player(CWnd *parent_wnd);
	/*
	���ܣ���ʼ��
	������
	    window_exist����ʾ�����Ƿ����
		show_handle����ʾ���ڵľ��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool initialize(bool window_exist,HWND show_handle,HWND parent_handle);
	void init_osd(void);

	/*
	���ܣ���ʾ��رմ�����Ƶ
	������
	    show_video����ʾ��Ƶ��1����ʾ 0���ر�
	����ֵ��
	    void
	*/
	void show_screen_video(bool show_video);

	/*
	���ܣ��������
	������
	    hwnd����ⴰ�ھ��
	����ֵ��
	����
	*/
	long set_soft_decode_function(HWND hwnd);

	/*
	���ܣ����ñ�����Ƶ���ڵľ��
	������
	    hwnd�����ھ��
	����ֵ��
	*/
	long set_slave_video_handle(HWND hwnd);

	/*
	���ܣ��Ƿ�ͬ����ʾ������Ƶ
	������
	    show_tv_video����ʾ������Ƶ��ture������false
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool pc_show_tv_video(bool show_tv_video);

	/*
	���ܣ�ֹͣ���еĲ��Ų��ͷŲ��ſؼ�
	������
	����void
   ����ֵ��
       void
	*/
	void destroy_player(void);

	/*
	���ܣ�������Ƶ�ļ�
	������
		video_info����Ƶ��Ϣ
		link_server�����ӵķ��������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/ 
	bool set_video_file(song_info &video_info,int &link_server,TCHAR* music_save_path,TCHAR *voice_save_path,bool is_scoring,int use_guid = 1);

	/*
	���ܣ�������Ƶ�ļ�
	������
		video_info����Ƶ��Ϣ
		link_server�����ӵķ��������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/ 
	bool set_video_file(song_info &video_info,TCHAR *szVideoPath);

	/*
		���ܣ����ò���ģʽ
	*/

	bool set_video_tape_mode(int tape_mode);

	/*
	���ܣ����ù����Ƶ�ļ�
	������
	    path��·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_ad_video_file(TCHAR *path);

	/*
	���ܣ�������Ƶ�ļ�
	������
	    cancel_mute��ȡ��������true��ȡ��������fasle����ȡ��
		kalaok_track��ԭ��
		lock_public_volume������������������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool play_video_file(bool cancel_mute,bool kalaok_track,bool lock_public_volume);
	/*
	���ܣ���ʼ����
	������
	    void
	����ֵ��
	    void
	*/
	void play(void);
	/*
	���ܣ���ͣ
	������
		void
	����ֵ��
		void
	*/
	void pause(void);
	/*
	���ܣ�ֹͣ
	������
		void
	����ֵ��
		void
	*/
	void stop(void);

	/*
	���ܣ��س�
	������
	    void
	����ֵ��
		void
	*/
	bool replay(TCHAR* music_save_path,TCHAR *voice_save_path,bool use_guid=false);

	/*
	���ܣ�����
	������
	    void
	����ֵ��
	    void
	*/
	void mute(void);
	
	/*
	���ܣ����Ż�����ͣ
	������
	    void
	����ֵ;
	    void
	*/
	void play_or_pause(void);
	/*
	���ܣ��ı�ԭ�鳪
	������
	    void
	����ֵ��
	    void
	*/
	void change_channel(void);
	void change_channel(long guid_track);

	/*
	���ܣ��������ػ����͹����İ�ť״̬�ַ���
	������
	    list_xml�����������ַ���
	����ֵ��
	   true���ɹ�
	   flase��ʧ��
	*/
	bool parse_panel_list_xml(TCHAR *list_xml);

	/*
	���ܣ���֯flash���Ű�ť��״̬�ַ���
	������
	   list_xml����֯�õĲ�������ַ���
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool make_panel_list_xml(TCHAR *list_xml);

	/*
	���ܣ���֯������ֵ��Ϣ
	������
	    list_xml����֯�õ������ַ���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool make_volume_list_xml(TCHAR *list_xml);

	/*
	���ܣ�����Ŀ�������ť״̬
	������
		list_xml����֯�õĲ�������ַ���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool make_control_bar_list_xml(TCHAR *list_xml);

	/*
	���ܣ��ı�����״̬
	������
	    void
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool change_enjoyment_state(void);

	/*
	���ܣ���ʾ����
	������
	    background_color������
		text_info��������Ϣ
		play_var������ʱ�õ���һЩ����
	����ֵ��
	    true���ɹ�
	    false��ʧ��
	*/
	bool play_text_osd(const TCHAR* background_color, const text_osd_info& text_info, const play_variable& play_var);

	/*
	���ܣ���ʾ��������
	������
	    text:Ҫ��ʾ������
		color��������ɫ
		x_pos��x��ʼ����
		y_pos��y��ʼ����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool play_control_text_osd(TCHAR *text,long color,long x_pos,long y_pos,long lIndex = 2L);
	/**/
	bool stop_play_control_text_osd(long lIndex);
	/*
	���ܣ����ſ��ƹ���ͼƬ
	������
	    path��ͼƬ·��
		x_pos��������
		y_pos��������
	����ֵ��
	    true���ɹ�
		falseʧ��
	*/
	bool play_control_osd(const TCHAR *path,int x_pos,int y_pos);

	/*
	���ܣ�ֹͣ���ƹ���OSDͼƬ�Ĳ���
	������
	    void
	����ֵ��
	    void
	*/
	void stop_control_osd(void);
	/*
	���ܣ�����osd logo
	������
	    path��log·��
		index������
		x_pos��������
		y_pos��������
		first_logo����һ��logoͼƬ
	����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool play_logo_osd(TCHAR *path,int index,int x_pos,int y_pos,bool first_logo);

	/*
	���ܣ����Ź��osd logo
	������
	    path��·��
		logo_layer��logo�����Ĳ�
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool play_ad_logo_osd(TCHAR *path,int logo_layer);

	/*
	���ܣ�����BMPͼƬ
	������
	    path��bmpͼƬ·��
		play_var������ʱ�õ���һЩ����
		alignment_mode�����뷽ʽ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool play_bmp_osd(TCHAR *path,play_variable &play_var,OSDAlignment alignment_mode);
	bool play_score_osd(TCHAR *path,play_variable &play_var,OSDAlignment alignment_mode);

	/*
	���ܣ���ʾǽ���ͼƬ
	������
	   path��ͼƬ·��
   ����ֵ��
       void
	*/
	void show_wall_panel_picture(TCHAR *path);

	/*
	���ܣ�����ǽ���ͼƬ
	������
	    void
	����ֵ��
	����void
	*/
	void hide_wall_panel_picture(void);

	/*
	���ܣ�ֹͣ����BMP osd
	������
		void
	����ֵ��
		void
	*/
	void stop_bmp_osd(void);
	void stop_score_osd(void);

	/*
	���ܣ�ֹͣ����osd logo
	������
	    void
	����ֵ��
	    void
	*/
	void stop_logo_osd(void);

	/*
	���ܣ�ֹͣ���Ź��osd logo
	������
		logo_layer��logo�����Ĳ�
	����ֵ��
		void
	*/
	void stop_ad_logo_osd(int logo_layer);


	//��ѯ�������ĸ���״̬
	bool is_playing(void);

	/*
	���ܣ��ı����������
	������
	    change_flag�������ı��ʾ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool change_music_volume(enum VOLUME_CHANGE_FLAG change_flag,int set_volume=50);

	/*
	���ܣ��ı���˷������
	������
	    change_flag�������ı��ʾ
		set_volume���ı������
	����ֵ��
	    Ŀǰ��˷������Ĵ�С
	*/
	int change_microphone_volume(enum VOLUME_CHANGE_FLAG change_flag,int set_volume=50);

	/*
	���ܣ��ı�����
	������
	    change_flag�������ı��ʾ
		tune_value������ֵ
		control_change_tone���ؼ��ı�����
	����ֵ��
	    Ŀǰ������С
	*/
	int change_tune(enum TUNE_CHANGE_FLAG change_flag,int tune_value,bool control_change_tone);

	/*
	���ܣ��ı����
	������
	   change_flag������ı��ʾ
   ����ֵ��
       Ŀǰ�����С
	*/
	int change_reverberation(enum REVERBERATION_CHANGE_FLAG change_flag);

	/*
	���ܣ�������Ƶ������Ƶ��ϲ���
	������
	    wave_path����Ƶ·��
		loop��ѭ��
		music_out��ԭ�����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool play_wave_mixer_audio(TCHAR *wave_path,int loop,int music_out);

	/*
	���ܣ�ֹͣ���Ż����
	������
	    void
	����ֵ��
	    void
	*/
	void stop_wave_mixer_audio(void);

	/*
	���ܣ��ı�DJ״̬
	������
	    void
	����ֵ��
	    void
	*/
	void change_DJ_state(void);

	/*
	���ܣ��õ��Ƿ�Ҫ����DJ
	������
	    void
	����ֵ��
	    true������DJ
		false��������DJ
	*/
	bool is_play_DJ(void);

	/*
	���ܣ��õ�ԭ�鳪��״̬
	������
	   void
   ����ֵ��
       true��ԭ��
	   false���鳪
	*/
	bool get_channel();
	long get_guid_channel();
	void set_guid_channel(long track){ guid_track = 0;}

	/*
	���ܣ��Ƿ�������״̬
	������
	    void
	����ֵ��
	    true������״̬
		false��������״̬
	*/
	bool is_enjoyment(void);

	/*
	���ܣ��Ƿ��ھ���
	������
	   void
   ����ֵ��
       true������
	   false���Ǿ���
	*/
	bool is_mute(void);

	/*
	���ܣ�����Ƿ��ڲ�����Ƶ���
	������
	    void
	����ֵ��
	    true��������Ƶ���
		false�����Ÿ���
	*/
	bool is_play_video_ad(void);

	/*
	���ܣ��򲥷ſؼ���������
	������
	    cmd������
		flag����ʾ
		value��ֵ
	����ֵ��
	    ���
	*/
	long send_command(long cmd, long flag, long value);

	/*
	���ܣ��õ���ǰ����λ��
	������
	    void
	����ֵ��
	    ���ŵ�λ��,�õ����ǰٷֱ�
	*/
	long get_cur_play_pos(void);

	/*
	���ܣ�Ԥ�������ֱ���򿪹���
	������
	    pMedia��ý��·��
		hwnd����ʾ�豸���
	����ֵ��
	   1���ɹ�
	   0��ʧ��
	*/
	long preview_open(LPCTSTR pMedia, long hwnd);

	/*
	���ܣ�Ԥ�������ֱ���رչ���
	������
	    void
	����ֵ��
		1���ɹ�
	   0��ʧ��
	*/
	long preview_close();

	//pk
	/*
	���ܣ���ʼpk
	������
		n: 0��1
		pMedia:·��
	*/
	long Live_Open(long n, LPCTSTR pMedia);

	/*
	���ܣ�����pk
	������
	n: 0��1
	*/
	long Live_Close(long n);
	/*����:*/
	long Live_Control(long n, long nCode, long argv0, long argv1);

	/*
	���ܣ�Ԥ�������ֱ���رչ���
	������
	    nCode��������
		argv0,argv1������
	����ֵ��
		1���ɹ�
	   0��ʧ��
	*/
	long preview_control(long nCode, long argv0, long argv1);

	/*
	���ܣ��򿪵���ֱ��
	������
	    pDev���豸��ʾ�ַ���,Ĭ�ϣ�NULL���Զ��ҵ�һ����ӿ�
	    hwnd����ʾ���ھ��
		nSignal��������ʽ
	����ֵ��
	    1���ɹ�
	   0��ʧ��
	*/
	long TV_open(LPCTSTR pDev, long hwnd, long nSignal);

	/*
	���ܣ��رյ���ֱ��
	������
		void
	����ֵ��
		1���ɹ�
	   0��ʧ��
	*/
	long TV_close();

	/*
	���ܣ����Ϳ�����Ϣ������ֱ��
	������
		nCode��������
		argv0,argv1������
	����ֵ��
		1���ɹ�
	   0��ʧ��
	*/
	long TV_control(long nCode, long argv0, long argv1);

	/*
	���ܣ��õ�����������
	������
	    music_volume�����ֵ�����
	    microphone_volume����˷������
		tune������
	����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool get_volume_tune(int &music_volume,int &microphone_volume,int &tune);

	/*
	���ܣ��õ��������������ֵ��Сֵ����
	������
		music_max�����������ֵ
		music_min����������Сֵ
		music_step�������Ĳ���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_music_volume_info(int &music_max,int &music_min,int &music_step);

	/*
	���ܣ��õ�������������ֵ��Сֵ����
	������
		microphone_max�����������ֵ
		microphone_min����������Сֵ
		microphone_step�������Ĳ���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_microphone_volume_info(int &microphone_max,int &microphone_min,int &microphone_step);

	/*
	���ܣ��õ���������״̬
	������
	    void
	����ֵ��
	   ״̬
	*/
	int get_player_state(void);

	/*
	���ܣ��õ��ļ��Ĳ���ʱ��
	������
	    void
	����ֵ��
	   �룬�ܵĲ���ʱ��
	*/
	long get_total_time_length();	

	/*
	���ܣ��õ���ǰ���ŵ�ʱ��
	������
	����void
    ����ֵ��
	    �룬��ǰ���ŵ�ʱ��
	*/
	long get_play_time_length();

	/*
	���ܣ���������λ��
	������
	    pos���ٷֱ�
	����ֵ��
	   void
	*/
	void seek(long pos);

	/*
	���ܣ����ÿ��ƴ���
	������
	   flag����ʾ
	   value�����õ�ֵ
   ����ֵ
       true���ɹ�
	   false��ʧ��
	*/
	bool Set(long flag, long value);
	
	/*
	���ܣ��������뵭��
	������
	   uTimerID����ʱ����ID
	   uMsg����Ϣ
	   dwUser���û���ʾ
	   dw1,dw2������
   ����ֵ��
      void
	*/
	static void WINAPI volume_callback(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

	/*
	���ܣ��õ����Ӳ���text osd��״̬
	������
	    void
	����ֵ;
	    1��������
		0���������
	*/
	int get_text_osd_play_state();
	
	/*
	���ܣ��õ������ŵ���Ƶ����
	������
		void
	����ֵ��
		���ŵ���Ƶ����
	*/
	PLAY_SONG_TYPE get_playing_video_type(void);

	/*
	���ܣ����������ŵ���Ƶ����
	������
		video_type����Ƶ����
	����ֵ��
		void
	*/
	void set_playing_video_type(PLAY_SONG_TYPE video_type);

	/*
	���ܣ�����ʵ�����ø����Ե�����
	������
	   void
   ����ֵ
       ʵ����������
	*/
	int compute_sound_card_volume(void);

	/*
	���ܣ������Ÿ�����Ƶ·��
	������
	    path������·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_playing_song_video_path(TCHAR *path);

	/*
	���ܣ����õ����ķ�ʽ������������
	������
	    void
	����ֵ��
	    void
	*/
	void output_music_volume(void);

	/*
	���ܣ������������ܵ��������ֺ��������ֹ���
	������
	    void
	����ֵ��
	   void
	*/
	void set_help_sing_and_mark(SCORE_SYSTEM use_score_system);

		/*
	���ܣ������͹ر�����
	������
	   state������״̬   true-��������  false-�ر�����
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool open_score(SCORE_SYSTEM use_score_system,bool state);


	/*
	���ܣ�������������
	������
	    void
	����ֵ��
	    void
	*/
	void set_help_sing_track(int command, bool use_guid=false);

	/*
	���ܣ��õ�����
	����;
	    void
	����ֵ��
	    ��ķ���
	*/
	int get_sing_score(void);

	/*
	���ܣ��ر��ļ�
	������
	    void
	����ֵ��
	   void
	*/
	void close_video_file(void);

	/*
	���ܣ��õ����ڲ��ŵ���Ƶ
	������
	    video_info����Ƶ��Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_playing_video(song_info &video_info);

	bool get_channel_memory();

	// ��ȡ����ǰ����ʾ����
	bool get_card_amplifier_volume_temp(int &nVolume);
	/*
	���ܣ����õ���
	������
	    void
		is_original:�Ƿ��ǵ�������  true����,falseΪԭ��
	����ֵ��
	    void
	*/
	//void enter_guid_song(void);
	void enter_guid_song(bool is_original);

	/*
	���ܣ��˳�����
	������
	   void
   ����ֵ��
       void
	*/
	void exit_guid_song(void);

	/*
	���ܣ��Ƿ���ʾ������
	������
	   void
   ����ֵ��
       void
	*/
	void set_show_score_line(bool line = false);

	/*
	���ܣ���������������filter�ؼ���filter�ؼ��������ԵĲ����
	������
	   HWND:��������
   ����ֵ��
       void
	*/
	void Set_fre_spectrumsitify_hwnd(HWND hwnd);

	/*
	���ܣ���Ƶ��ֵ��ֵ��filter�ؼ�
	������
	   spec:Ƶ�׶�ֵ
   ����ֵ��
       void
	*/
	void Set_fre_spectrumsitify_spec(int spec);

	void set_use_song_mark(bool flag);
	 
	//�����ֶ����ؾ��������
	void set_server_link_index(int link_idx){m_server_manually = link_idx;}
private:
	song_info m_playing_song_info; //��ǰ���ڲ��ŵĸ�����Ϣ
	bool m_playing;       //�Ƿ����ڲ��ţ�������ͣ
	bool m_channel;	      // ԭ��/�鳪��trueΪԭ����ÿ���л�����ʱ���Զ�תΪ�鳪
	bool m_enjoyment;     // ���ͣ���ʾʼ�ղ���ԭ��
	bool m_play_DJ;       //�Ƿ��ڲ���DJ true���ǣ�false����
	bool m_mute;          //����
	int  m_song_volume;         //�������� 0---100
	int  m_microphone_volume;   //��˷������  0----100
	int  m_tune;                //������С -5-----5

	int m_card_amplifier_volume;         //���򹫷ŵ�����������ʾ������
	int m_card_amplifier_volume_temp;	 //����ǰ�����򹫷ŵ�����������ʾ����������ǰ���棩
	int m_cur_card_song_volume;          //��ǰʵ�����ø���������
	int m_volume_adjust_percentage;      //�������ڰٷֱ�
	bool m_adjust_amplifier;             //���ڹ���������������ڿ�������
	int m_card_default_value;            //��ʹ�õ��ڹ�������ʱ����һֱʹ��ÿ�׸�����Ĭ��ֵ
	int m_idle_song_volume;              //���и�������
	int m_default_tv_volume;			 //Ĭ�ϵ�������

	int m_select_song_volume;            //ѡ��������������ڲ��ſ��и���֮�󣬻ָ�Ĭ�ϼ���

	bool m_volume_memory;         //��������
	bool m_channel_memory;        //ԭ�鳪����

	int m_music_volume_max;       //�������������ֵ
	int m_music_volume_min;       //������������Сֵ
	int m_music_volume_step;      //���������Ĳ���

	int m_microphone_volume_max;  //��˷����������ֵ
	int m_microphone_volume_min;  //��˷���������Сֵ
	int m_microphone_volume_step; //��˷������Ĳ���

	int m_tune_max;               //���������ֵ
	int m_tune_min;               //��������Сֵ
	int m_tune_step;              //�����Ĳ���
	int m_tune_original;          //ԭʼ������

	bool m_show_video_window_exist; //pc����ʾ��Ƶ�Ĵ����Ƿ����
	HWND m_video_window_handle;   //pc����ʾ��Ƶ���ڵľ��
	HWND m_parent_window_handle;  //�����ھ��

	bool m_use_stream_control_service; //ʹ�����ط���
	bool m_check_file_exist;           //ÿ�ζ�����ļ��Ƿ����

	//����
	int m_reverberation_default_value; //����Ĭ��ֵ
	int m_reverberation_min_value;     //������Сֵ
	int m_reverberation_max_value;     //�������ֵ
	int m_reverberation_step;          //����Ĳ���
	int m_reverberation_value;         //����ֵ

	TCHAR m_playing_song_path[256];    //���ڲ��ŵĸ���·��
	PLAY_SONG_TYPE m_pre_video_type;   //ǰһ�׸�������Ƶ����

	//����
	bool m_use_help_sing;              //ʹ����������
	std::wstring m_help_sing_card_name;//����ʹ�õ���������

	int m_tape_mode;

	//mark
	bool m_use_song_mark;              //���ô�ֹ���

	//������
	bool m_play_video_ad;              //�Ƿ��ڲ�����Ƶ���
	TCHAR m_video_ad_path[256];        //��Ƶ���·��
	bool m_show_score_line;

	int m_server_manually; //�ֶ����ؾ���
	long guid_track;
};

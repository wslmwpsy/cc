#pragma once

#include "player/player_manager.h"
#include "database/DBQuery.h"
#include "flash/FlashPlayer.h"
#include "flash/FlashManage.h"
#include "song/query_song_manager.h"
#include "com/inherit_com.h"
#include "ChildWnd.h"
#include "osd/osd_play_manager.h"
#include "tape/audio.h"
#include "common/llock.h"
#include "screen_saver/screen_saver_window.h"
#include "star/query_singer_manager.h"
#include "handwriting/handwriting.h" 
#include "bomb/bomb.h"
#include "ad/AD_manager.h"
#include "doorplate_machine/DoorplateWnd.h"
#include "service_picture/show_service_picture.h"
#include "U_disk/U_disk_song.h"
#include "game/game_manager.h"
#include "common/mac_address.h"
#include "flash/PageData.h"
#include "audio_effect/AudioEffect.h"
#include "mysql/MySQL_DB.h"
#include "QR_Encode/QR_Encode.h"
#include "lyricSearch/SearchLyric.h"
#include "os/XWinVer.h"
#include "tape/mixerlib.h"
#include "http/http.h"
#include "member/memeber_song_manager.h"
#include "json/json.h"
#include <fstream>
#include "html/HtmlCtrl.h"

#include <queue>

#include "dbsql/DbSQL.h"
#include "film/query_film_manager.h"
#include "PluginsEx.h"

#include "RTCOMDLL/RTCOMDLL.h"
#include "RTCOMDLL/RTCOMDLL_Data.h"
#include "lyric/LyricManager.h"
#include "trendlist/TrendListManager.h"
#include "InterScreen/InterScreenManager.h"
#include "screenflash/TransparentWnd.h"
#include "PassManager/PassManager.h"

#include "lyric/ParseLyricsForKSC.h"

#include "common/zlib.h"
#include "common/XUnzip.h"
#include <direct.h>
#include "CommLib/http.h"
#include "ShineAxBrowse/CDShineAxBrowse.h"

#define VIDEO_SHOW_FULL_SCREEN

#define SLEEP_FOR Sleep(25)

//����SQL Server�ṹ��
typedef struct struct_show_cube_song{
	int id;
	wstring song_id;
	wstring song_name;
	wstring singer_id1;
	wstring singer_id2;
	wstring singer_id3;
	wstring singer_id4;
	wstring song_add_datetime;
	wstring serv_path1;
	wstring serv_path2;
	wstring serv_path3;
	wstring song_relative_path;
	wstring song_wechat_url;
	int song_type;
	int theme_type;
	int language;
	int song_name_word;
	wstring song_name_spell;
	int song_version;
	wstring file_format;
	wstring song_name_tip;
	wstring lyric;
	wstring singer_name;
	int reserve_1;
	int reserve_2;
	int reserve_3;
	int reserve_4;
	int reserve_5;
	wstring reserve_6;
	wstring reserve_7;
	wstring reserve_8;
	wstring reserve_9;
	wstring reserve_10;
	wstring reserve_11;
	wstring reserve_12;
	wstring reserve_13;
	wstring reserve_14;
	wstring reserve_15;
	wstring reserve_16;
	wstring reserve_17;
	wstring reserve_18;
	wstring reserve_19;
	wstring reserve_20;
}SHOW_CUBE_SONG, *LP_SHOW_CUBE_SONG;

typedef struct struct_show_cube_singer
{
	int id;
	wstring singer_id;
	wstring singer_name;
	wstring singer_picture;
	wstring datatime;
	wstring singer_name_spell;
	int singer_name_count;
	wstring singer_wechat_url;
	int singer_type;
	int singer_sex;
	int singer_region;
	wstring singer_introduction;
	int reserve_1;
	int reserve_2;
	int reserve_3;
	int reserve_4;
	int reserve_5;
	wstring reserve_6;
	wstring reserve_7;
	wstring reserve_8;
	wstring reserve_9;
	wstring reserve_10;
	wstring reserve_11;
	wstring reserve_12;
	wstring reserve_13;
	wstring reserve_14;
	wstring reserve_15;
}SHOW_CUBE_SINGER, *LP_SHOW_CUBE_SINGER;

typedef vector<LP_SHOW_CUBE_SONG> SHOW_CUBE_SONG_VEC;
typedef vector<LP_SHOW_CUBE_SINGER> SHOW_CUBE_SINGER_VEC;

//*****************************��Ƭmv�ṹ��*********************************
typedef struct tag_imageInfo{
	wstring imageUrl; //ͼƬ��ַ
	int Orientation; //����
}Image_Info, *LPImage_Info;
//��Ƭmv�ṹ��
typedef struct st_picture_mv{
	song_info songInfo;		//������Ϣ
	int priority;			//�Ƿ����� 0������ 1������
	TCHAR callDelUrl[2048]; //ɾ���������ϵ���Ƭ�ļ���
	vector<Image_Info> imageInfoVec; //��Ƭ·��������
	int itemplate;
	string guid;
	st_picture_mv(){
		songInfo.initialized_variables();
		priority = 0;
		memset(callDelUrl, 0x00, sizeof(callDelUrl));
		imageInfoVec.clear();
		itemplate = 0;
		guid = "";
	}
}ST_PICTURE_MV, *LPST_PICTURE_MV;

using namespace shine;
using namespace dagexing;
using namespace std;

// Cflashktv10Wnd
#define MAX_MENBER_NUM  500
#define PK_MEMBER_SIZE  500

//����pk��Ա����
typedef struct PK_MEMBER_DATA
{
	TCHAR ipaddress[256];   //���͵�ip��ַ
	TCHAR name[256];      //��Ա����
	TCHAR nsex[2];              //�Ա� 1���У�2��Ů
	TCHAR nstatus[10];           //״̬ 0�����У�1������pk 
	TCHAR nBoxIp[256];          //����ip
	int  nPort;               //�����˿�
}PK_MEMBER_DATA;

enum video_dating_status{
	VD_IDLE, //����
	VD_BUSY, //æµ
	VD_NOTDISTURB, //�����
	VD_CLOSE_ROOM //�ط����˳�
};
typedef struct video_dating
{
	TCHAR name[MAX_PATH];	//����  ������ or ΢����
	TCHAR ip[32];			//�ͻ���ip��ַ
	int ncharacter;			//��ɫ 1������ 2������ 3������ 4������ 5��˧�� 6����Ů 7������ 8��Ů�� 9����̫ 10������
	int nstatus;			//״̬ 0������ 1��æµ 2�������
}VIDEO_DATING, *P_VIDEO_DATING;

class Cflashktv10Wnd : public CWnd
{
	DECLARE_DYNAMIC(Cflashktv10Wnd)

	//����������������ݵĽṹ
	typedef struct REQUEST_BOX_DATA
	{
		Cflashktv10Wnd *pThis;
		TCHAR request_data[1024];   //ip
		int nPort;				 //�˿ں�
	}REQUEST_BOX_DATA;

public:
	Cflashktv10Wnd();
	virtual ~Cflashktv10Wnd();
	BOOL CreateWnd();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	//flash function
	//flash�������Ϣ��Ӧ����
	void FlashCallShockwaveflash(LPCTSTR request);

	/*
	���ܣ�����flash���淢�͹�������Ϣ
	������
		command������
		args�����ݹ����Ĳ���
	����ֵ��
		void
	*/
	void flash_message_call(const TCHAR *command,const TCHAR *args);
	void flash_message_call_ex(const TCHAR *command,const TCHAR *args);

	//flash��Ӧ�ķֺ���,���ֳɸ���ģ��
	//����
	void flash_message_call_function(int function_code,int lpara=0,bool recv_msg=false);
	void flash_message_call_song_pinyin(select_expr &table_select_expr,const TCHAR *args);
	void flash_message_call_song_query(select_expr &table_select_expr,const TCHAR *args,SONG_LANGUAGE query_language);
	void flash_message_call_song_japanese(select_expr &table_select_expr,const TCHAR *args);
	void flash_message_call_singer_japanese(const TCHAR *args);
	void flash_message_call_language(const TCHAR *args);
	void flash_message_call_song_word_count(select_expr &table_select_expr,const TCHAR *args);
	void flash_message_call_theme(const TCHAR *args);
	void flash_message_call_era(const TCHAR *args);
	void flash_message_call_new_theme(const TCHAR *args);
	void flash_message_call_song_version(const TCHAR *args);
	void flash_message_call_singer_sex(const TCHAR *args);
	void flash_message_call_new_song(const TCHAR *args);
	void flash_message_call_file_format(const TCHAR* args);
	bool flash_message_call_song_sort_song();

	void flash_message_call_voice_china();   //������
	void flash_message_call_cloud_song();

	//Ϸ�������ѯ
	void flash_message_call_opera(const TCHAR *args);
	//@priority���Ƿ����� number_type:�������  0�����  1.���� 2.����
	void flash_message_call_select_song(const TCHAR *args,bool priority,bool singed_page,bool priority_type,int number_type=0);
	void flash_message_call_maiba_song(const TCHAR *args,bool priority,bool singed_page);
	void flash_message_call_maiba_song(MAIBA_SONG_INFO_STU &maiba_song_info);
	void flash_message_call_dekaron_song(const TCHAR *args,bool priority,bool singed_page);
	void flash_message_call_recorder_select_song(const TCHAR* args,bool priority);
	void flash_message_call_arena_song(MAIBA_HEIGHT_RANKING &maiba_song_info);
	void flash_message_call_music_enjoy(int page_code, const TCHAR *args);
	
	//������ȡһ������
	void flash_message_call_get_web_select_song(const TCHAR* args);

	void flash_message_call_U_disk_select_song(const TCHAR *args);
	void flash_message_call_recommend_select_song(const TCHAR* args);
	//Ԥ��ҳ��ѡ�и���
	void flash_message_call_preview_select_song(bool priority);
	//���Ϊ˽�˸�����@preview_song���ղص��Ƿ���Ԥ������
	void flash_message_call_person_song(const TCHAR *args,bool preview_song);
	//Ԥ������
	void flash_message_call_preview_song(const TCHAR *args);
	//����������Ƶ
	void flash_message_call_www_music(const TCHAR *preview_path);
	//Ԥ������
	void flash_message_call_preview_control(const TCHAR *args);
	void flash_message_call_preview_change_play_pos(const TCHAR *args);
	//��Ա����ƴ����ѯ
	void flash_message_call_member_song_pinyin(const TCHAR *args);
	//���������������
	void flash_message_call_mongolia_input_opinion(const TCHAR *args);
	//�׻���
	void flash_message_call_flowers_song(const TCHAR *args,bool preview_song);

	//����
	void flash_message_call_singer_pinyin(const TCHAR *args);
	void flash_message_call_singer_query(const TCHAR *args,SONG_LANGUAGE query_language);
	void flash_message_call_singer_word_count(const TCHAR *args);
	void flash_message_call_singer_region(const TCHAR *args);
	void flash_message_call_singer_sex_ex(const TCHAR *args);
	void flash_message_call_singer_select(const TCHAR *args);
	void flash_message_call_singer_clear_all(const TCHAR *args);
	//������ת������
	void flash_message_call_song_singer(const TCHAR *args);

	//ҳ����ת
	void flash_message_call_page_jump(int page_number, bool allow_repeat=false);

	//�����б�����
	void flash_message_call_test_priority(const TCHAR *args);

	//�����в��Ը����ŵ���ѡ��
	void flash_message_call_save_test_song(void);
	//��¼���Խ��
	bool flash_message_call_save_test_result(const TCHAR *args);
	//�������ı�
	void flash_message_call_query_board_change(const TCHAR *args);
	//��д��ѡ��
	void flash_message_call_select_recognize_word(const TCHAR *args);
	//��Աע��,��¼
	void flash_message_call_member_login(const TCHAR *args);
	//�ı���д����
	void flash_message_call_change_handwriting_language(const TCHAR *args);
	//����ķ���ͼƬչʾ
	void flash_message_call_service(const TCHAR *args);

	//��ˮ���
	void flash_message_call_drinks(void);
	//���Ѳ�ѯ������
	void flash_message_call_consume(void);
	//��Ӱ�������
	void flash_message_call_movie_story(const TCHAR *args,bool memory_state);
	//��Ӱƴ����ѯ
	void flash_message_call_movie_pinyin(const TCHAR *args);
	void flash_message_call_movie_query(const TCHAR *args,SONG_LANGUAGE query_language);
	void flash_message_call_movie_japanese(const TCHAR *args);
	//��Ӱ������ѯ
	void flash_message_call_movie_word_count(const TCHAR *args);
	//���������
	void flash_message_call_survey_result(int question_number,const TCHAR *args);
	//��ʾ��д��������
	void flash_message_call_surver_tip_message(const TCHAR *args);
	//��д���Ƹ�����Ϣ�����
	void flash_message_call_custom_tip_message(const TCHAR* args); 
	//�ύ���
	void flash_message_call_submit_opinion(const TCHAR *args);

	void flash_message_call_submit_custom_song(const TCHAR* args);
	//��д����������ϵ��ʽ
	void flash_message_call_write_phone(const TCHAR *args);
	//��д���Ƹ�������ϵ��ʽ
	void flash_message_call_custom_phone(const TCHAR* args);
	//¼��
	void flash_message_call_recorder_audio(const TCHAR *args);
	//���Զ�¼������¼��
	void flash_message_call_recorder_audio_type(const TCHAR *args,bool recv_msg);
	//ϵͳ����
	void flash_message_call_system_manager(const TCHAR *args);
	//�ظ�ѡͬһ�׸���ʱ��������ʾ
	void flash_message_call_select_song_tip(const TCHAR *args);
	//��ŵ��
	void flash_message_call_number_select_song(const TCHAR *args);

	//��ѯ�����
	void flash_message_call_query_song_type(const TCHAR* args);

	//����������ص���Ϣ
	void flash_message_call_maiba(enum MAIBA_TYPE maiba_type,const TCHAR *args);
	 
	/*
	���ܣ�����
	������
		args����Ҫ���̵ı��
	����ֵ��
		void
	*/
	void flash_message_call_submit_recorder_song(const TCHAR *args);

	
	/*
	���ܣ�����
	������
		args����Ҫ����ı��
	����ֵ��
		void
	*/
	void flash_message_call_share_recorder_audio(const TCHAR *args, bool recv_msg);
	static UINT share_audio_file_thread(LPVOID pPara);
	UINT share_audio_file_to_internet(void);

	void flash_message_call_share_area_recorder_audio(MAIBA_HEIGHT_RANKING &maiba_share_info);
	void flash_message_call_share_web_song(MAIBA_SONG_INFO_STU &maiba_song_info);
	/*
	���ܣ���ѯ���Ը���������ʾ�����������
	������
		void
	����ֵ;
	   true���ɹ�
	   false��ʧ��
	*/
	bool test_song_query_show_data(void);
	
	/*
	���ܣ��õ��Կ�����Ϣ��������ʼ����ͷֱ���
	������
		device_number���豸���
		position_x����ʼX����
		position_y����ʼY����
		width�����
		height���߶�
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_display_device_settings(int device_number,int &position_x,int &position_y,int &width,int &height);

	/*
	�����߼�������ʱ���ж��Ƿ�ȡ������
	bChange:��Ϊtrue��ֱ��ȡ������
	*/
	bool DealMuteState(bool bChange = false);
	/*
	���ܣ�������ʾ���ķֱ���
	������
		device_number���豸���
		start_x����ʼX����
		start_y����ʼY����
		width�����
		height���߶�
	����ֵ��
		void
	*/
	bool set_display_device_resolution(int device_number,int start_x,int start_y,int width,int height);

	/*
	���ܣ��Զ����ػ���ʾwindow��������
	������
		hide�����ػ���ʾ�ı�ʾ  true������  false����ʾ
	����ֵ��
		void
	*/
	void hide_window_task_bar(bool hide);

	/*
	���ܣ�ɾ�����ڵ���־
	������
		void
	����ֵ��
		void
	*/
	void delete_expire_log(void);

	/*
	���ܣ�ɾ��¼���ļ�
	������
		void
	����ֵ��
		void
	*/
	void delete_recorder_file(void);

	/*
	���ܣ�һ�������߳�
	������
		pParam�����ݵĲ���
	����ֵ��
		UINT
	*/
	static UINT assistant_thread(LPVOID pParam);

	//���ݿ��߳�
	static UINT DB_thread(LPVOID pParam);

	/*
	���ܣ����պ�̨���͹����Ŀ��ط������߳�
	������
		pParam�����ݵĲ���
	����ֵ��
		UINT
	*/
	static UINT recv_server_data_thread(LPVOID pParam);


	/*
	���ܣ����ܺ�̨���͵Ŀ��ط�����
	������
		void
	����ֵ��
		UINT
	*/
	UINT recv_server_data(void);

		/*
	���ܣ����ܹ㲥��Ϣ����
	������
		void
	����ֵ��
		UINT
	*/
	static UINT recv_server_voice_china_udp_thread(LPVOID pParam);
	
	UINT recv_server_voice_china_udp(void);

	bool shine_parse_voice_china_data(char* recv_data);
	/*
	���ܣ������ܹ��ͷ������ݸ�ǰ�û�
	������
		parent_hwnd�������
	����ֵ��
		UINT
	*/
	UINT find_dog_and_precomputer(HWND parent_hwnd);

	/*
	���ܣ���ʾflash����
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_flash_interface(void);
	/*
	���ܣ����пغд���
	������
		void
	����ֵ��
		void
	*/
	void open_control_box_com(void);

	/*
	���ܣ���ʾlogo
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_logo_osd(void);

	/*
	���ܣ���ʾ��һ��logoͼƬ
	������
		reload����������
	����ֵ��
		void
	*/
	void show_next_logo_osd(bool reload);

	/*
	���ܣ���flash����ʾ������Ļ
	������
		text��Ҫ��ʾ������
		place_notic:�Ƿ���ʾ����
	����ֵ��
		void
	*/
	void show_text_on_flash(const TCHAR *text,bool place_notice=false);

	/*
	���ܣ���flash�ĺ�������
	������
		request�����͸�flash����Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool flash_player_call_function(TCHAR *request);

	/*
	���ܣ�������һ����Ƶ
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool play_next_video(void);

	/*
	���ܣ���������������
	������
		data��Ҫ���͵�����
		data_len�����ݳ���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool send_master_slave_data(TCHAR *wide_data,char *multile_data,int data_len=0);
	bool send_master_slave_data_udp(TCHAR *wide_data,char *multile_data,int data_len,char *ip,u_short port);

	void send_light_control_udp(LINGHT_CONTROL light_control_data);

	/*
	���ܣ���ʼ¼��
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool start_recorder_audio(void);

	/*
	���ܣ�ֹͣ¼��
	������
		play_next��������һ����Ƶ
	����ֵ��
		void
	*/
	int stop_recorder_audio(bool play_next,bool MixerAudio,bool play_finish);

	/*
	���ܣ�������ʾ��ǰҳ
	������
		requery�����¼���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool refresh_screen_list(bool requery=false);
	//ˢ�¸�����Ļ�б�
	bool refresh_song_screen_list(void);
	bool refresh_movie_screnn_list(void);

	/*
	���ܣ�¼��¼����Ϣ�����ݿ���
	������
		void
	����ֵ��
		void
	*/
	void insert_recorder_song_into_database(void);

	/*
	���ܣ���ʾ��ѡ���ѳ��ĸ���
	������
		song_type���ѳ�������ѡ����
		page_operate��ҳ���������·�ҳ
		page_operate_type��ҳ�������ͱ�ʾ  ˵����������1 �һ�����2   ����ҳ��ť��3  ����ҳ��ť��4  ��һҳ��ǰҳ��0

	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_select_or_sing_song(enum SHOW_SONG_LIST_TYPE song_type,enum PAGE_OPERATE page_operate,int page_operate_type);
	bool show_recorder_arena_song(enum PAGE_OPERATE page_operate,int page_operate_type, int maibaType = -1);

	/*
		��ʾ�����������
	*/
	bool flash_show_maiba_song();

	/*
	���ܣ�flash����ʾ��ʾ��Ϣ
	������
		msg_code��Ҫ��ʾ�����ݱ���
	����ֵ��
		void
	*/
	void flash_show_tip_message_chVip(TCHAR *tip_msg);
	void flash_show_tip_message_vip(int msg_code,bool back_tip=false);
	void flash_show_tip_message(int msg_code,bool back_tip=false);
	void flash_show_tip_message(TCHAR *tip_msg);

	/*
	���ܣ�ֹͣ����osd�͹��ı���osd logo
	������
		void
	����ֵ��
		void
	*/
	void stop_control_osd_logo(void);

	/*
	���ܣ����Ϳ�����������ػ�
	������
		control_code��������
	����ֵ��
		void
	*/
	void send_master_slave_control_code(int control_code);

	/*
	���ܣ���ʾ���ƹ��ܵ�OSDͼƬ
	������
		show_content����ʾ������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_control_osd(enum OSD_SHOW_CONTENT show_content);

	/*
	���ܣ���ʾ������
	������
		bar_flag����ʾ
	����ֵ��
		void
	*/
	void show_volume_bar_on_tv(VOLUMN_BAR_FLAG bar_flag);

	/*
	���ܣ���¼���͸�ǰ�û�����Ϣ
	������
		ad_type���������
	����ֵ��
		void
	*/
	void set_precomputer_send_info(enum PRECOMPUTER_SEND_TYPE ad_type);

	/*
	���ܣ��������͸�ǰ�û�����Ϣ�����ͽṹ��
	������
		ad_type���������
	����ֵ��
		void
	*/
	void copy_precomputer_send_info(enum PRECOMPUTER_SEND_TYPE ad_type);
	void copy_precomputer_video_send_info();

	/*
	���ܣ��õ���������
	������
		text��Ҫ�ǵ�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_control_text(enum OSD_SHOW_CONTENT show_content,TCHAR *text);

	/*
	���ܣ�ҳ��ı�
	������
		page_code��ҳ���ʾ��
		page_init��ҳ��Ҫ���г�ʼ��
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool page_change(int page_code,bool page_init=true);
	bool page_change_init(void);
	bool page_change_function(int page_code);

	/*
	���ܣ�����������ѯ���ݿ�ĸ���������ʾ��flash������
	����:
		table_select_expr������ѡ����ʽ
		group_item�������ֶ�
		order_item:�����ֶκ�����ģʽ
		page_expr:�Ƿ���ҳ����תʱ�Ĳ�ѯ
	����ֵ��
		true:�ɹ�
		false��ʧ��
	*/
	bool song_query_show_data(select_expr &table_select_expr,bool bShowTip=true,bool page_expr=false, bool show_movie_name = false);
	//����ֵ��0��ʧ�� 1����һ�β�ѯ�ɹ�  2���ڶ��β�ѯ�ɹ�
	int song_query_two_show_data(select_expr &table_select_expr,int condition_number=0,query_condition *src_query_condition=NULL);
	//��Ա����
	bool member_song_query_show_data(void);
	//��ѯ������ɵĸ���
	bool song_query_show_data_by_sql_server();
	/*
	���ܣ���ѯ¼������������ʾ��flash������
	������
	   void
   ����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool song_recorder_query_show_data(PAGE_OPERATE page_operate = FIRST_PAGE_OPERATE);
	bool song_recorder_query_all_show_data(void);
	/*
	���ܣ���ѯ¼������������ʾ��flash������
	������
	   void
   ����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool song_recorder_query_show_data_by_id(TCHAR *pargs);

	/*
	���ܣ���������ķ�����Ϣϵͳ���пغ�
	������
		service_content�����������
	����ֵ��
		void
	*/
	void send_request_service(int button_number,TCHAR *service_content);

	/*
	���ܣ�������Ϣ����Ϣϵͳ
	������
		message���������Ϣ����
	����ֵ��
		void
	*/
	bool send_message_to_msg_server(TCHAR *message);

	/*
	���ܣ�������Ϣ���߳�
	������
		pParam�����ݵĲ���
	����ֵ��
		UINT
	*/
	static UINT send_message_thread(LPVOID pParam);

	/*
	���ܣ�������Ϣ���������ĺ���
	������
		void
	����ֵ��
		UINT
	*/
	bool send_message_function(void);

	/*
	���ܣ���������osd��ʾʱ��Ķ�ʱ��
	������
		void
	����ֵ��
		void
	*/
	void set_control_osd_show_timer(void);

	/*
	���ܣ���������bmpͼƬ��ʾʱ��Ķ�ʱ��
	������
		show_time����ʾʱ��
	����ֵ��
		void
	*/
	void set_bmp_picture_show_timer(int show_time);
	void set_score_show_timer(int show_time);

	/*
	���ܣ�����flash���ư�ť��״̬
	������
		void
	����ֵ��
		void
	*/
	void update_flash_control_button(void);

	/*
	���ܣ�������Ч��ֵ
	������
		void
	����ֵ��
		void
	*/
	void update_flash_audio_info(void);

	/*
	���ܣ���ʾflash�ϵĹ�������
	������
		void
	����ֵ��
		��ʱ����ʱ����
	*/
	int timer_show_flash_text(void);

	/*
	���ܣ���ʾ�����ϵĹ�������
	������
		void
	����ֵ��
		��ʱ����ʱ����
	*/
	int timer_show_tv_text(void);

	/*
	���ܣ�����flash�ı���ͼƬ
	������
		void
	����ֵ��
		��ʱ����ʱ����
	*/
	int timer_show_flash_background_picture(void);

	/*
	���ܣ���flash����ʾlogo
	������
		void
	����ֵ��
		��ʱ����ʱ����
	*/
	int timer_show_flash_logo(void);

	/*
	���ܣ��ڵ�������ʾlogo
	������
		void
	����ֵ��
		��ʱ����ʱ����
	*/
	int timer_show_tv_logo(void);

	/*
	���ܣ���ʾͼƬ����
	������
		void
	����ֵ��
		void
	*/
	void timer_show_pictrue_screen_saver(void);

	/*
	���ܣ���ʾ��Ƶ����
	������
		void
	����ֵ��
		void
	*/
	void timer_show_video_screen_saver(void);
	void show_video_screen_saver(void);

	/*
	���ܣ���ʾ�����ڵ�����
	������
		text��Ҫ��ʾ������
		scroll_mode������ģʽ
		scroll_count����������

	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool play_osd_text(TCHAR *text,enum OSD_PLAY_MODE scroll_mode,int scroll_count);

	/*
	���ܣ���ʾ���˳���Ƶ����
	������
		void
	����ֵ��
		void
	*/
	void show_quit_video_screen_saver(void);

	/*
	���ܣ����ص�����
	������
		void
	����ֵ��
		void
	*/
	void return_select_song_window(void);

	/*
	���ܣ��������д���
	������
	   void
   ����ֵ��
	  void
	*/
	void hide_sub_window(void);

	/*
	���ܣ���Ƶ���Ŵ��������д�������ʾ
	������
		void
	����ֵ��
		void
	*/
	void switch_screen_show_video_window(void);

	/*
	���ܣ�Ԥ����Ƶ������ʾ
	*/
	void preview_screen_show_video_window(void);

	/*
	���ܣ���ʾ�����׸������ֵĹ�����Ļ
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_song_name(void);

	/*
	���ܣ�����
	������
		void
	����ֵ��
		void
	*/
	void ktv_open_room(void);

	/*
	���ܣ����浱ǰ��ѡ�����ı��
	������
		path��Ҫ����ķ�����·��
	����ֵ��
		void
	*/
	void save_select_song_number(TCHAR *path);

	/*
	���ܣ��õ�ѡ�и���ID
	������
		song_ID���������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_select_song_number(TCHAR *song_ID);

	/*
	���ܣ�����ʱ���õ�ѡ��ĸ�������¼�뵽��ѡ��
	������
		path��������·��
	����ֵ��
		true:�õ�����
		false:û��
	*/
	bool get_select_song_from_server(TCHAR *path);

	/*
	���ܣ�ͬ��ѡ�����
	������
		clear_song�������ѡ
		song_ID���������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool syn_select_song(bool clear_song,TCHAR *song_ID);

	/*
	���ܣ����Ͳ����Ϣ�����������
	������
		void
	����ֵ��
		void
	*/
	void send_test_song_info(void);

	/*
	���ܣ��Զ����Ժ���
	������
		void
	����ֵ��
		void
	*/
	void auto_test_software(void);

	/*
	���ܣ����Ż�����
	������
		audio_number���������ı��
		show_logo����ʾ����logo
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool play_environment_audio(int audio_number,bool show_logo=true);

	/*
	���ܣ��ı�ƹ�
	������
		light_number���ƹ����
		recv_msg�����ܵ���Ϣ
	����ֵ;
		void
	*/
	void change_room_light(int light_number,bool recv_msg);

	/*
	�ı侲������ͣʱ�ĵƹ�״̬
	nState:0(ȡ����������ͣ״̬)
			1(����״̬)
			2����ͣ״̬��
	*/
	void change_light_state(int nState);
	/*
	���ܣ��ı�յ����ŷ�
	������
		air_condition���յ���λ���ŷ�
	����ֵ��
		void
	*/
	void change_air_condition_function(int air_condition);

	/*
	���ܣ�����������Ƶ
	������
		wave_type����Ƶ����
	����ֵ��
		void
	*/
	void play_atmosphere_audio(int wave_type);

	/*
	���ܣ�ֹͣwav��Ƶ
	������
	   void
	����ֵ��
		void
	*/
	void stop_environment_audio(void);

	/*
	���ܣ�����������ѯ���ݿ���Ǳ�����ʾ��flash������
	����:
		void
	����ֵ��
		true:�ɹ�
		false��ʧ��
	*/
	bool singer_query_show_data(void);

	/*
	���ܣ�����flash���͹����������ַ���
	������
		Coordinate������
		x_position��xλ��
		y_position��yλ��
		width:���
		height���߶�
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool parse_coordinate_string(const TCHAR *coordinate,int &x,int &y,int &width,int &height);

	/*
	���ܣ������д��ʾ����
	������
		void
	����ֵ��
		void
	*/
	void clear_handwriting_recognizer_word(void);

	/*
	���ܣ������дѡ�����
	������
		void
	����ֵ
		void
	*/
	void clear_handwriting_select_word(void);
	
	/*
	���ܣ���ѯ��д��������
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool query_handwriting_association_word(void);

	/*
	���ܣ��õ���д���������ʾ����
	������
		result_string������ַ���
		array_size�������С
		query_word����ѯ�����е���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_handwriting_assocition_word(std::wstring result_string[],int array_size,const TCHAR *query_word);

	/*
	���ܣ���ʾ��д��������
	������
		page_operate��ҳ����
	����ֵ��
		void
	*/
	void show_association_word(int page_operate);

	/*
	���ܣ������������
	������
		void
	����ֵ��
		void
	*/
	void clear_all_query_condition(void);
	
	/*
	���ܣ�����ҳ�治ͬ���������
	������
		void
	����ֵ��
		void
	*/
	void clear_query_condition_by_page(void);

	/*
	���ܣ���ʼ�����м�������
	������
	   void
   ����ֵ��
	   void
	*/
	void query_board_init(void);

	/*
		���ܣ�����dj�Ի���
	*/
	void show_pop_up_dj_window();

	/*
	���ܣ�����ҳ�治ͬ����ղ�ѯ����������ʼ��
	������
		clear_list���Ƿ�����б� true����� false�������
	����ֵ��
		void
	*/
	void clear_query_condition_by_page_and_init(bool clear_list);

	/*
	���ܣ���ʾ��ĸ������
	������
		NULL
	����ֵ��
		void
	*/
	void show_letter_window(const TCHAR *letter);
	void show_query_letter(const TCHAR *letter,SONG_LANGUAGE query_language);

	/*
	���ܣ�����ѯ���Ϊ��ʱ��������ʾ
	������
		void
	����ֵ��
		void
	*/
	void show_no_match_result_tip(bool back_tip=false);

	/*
	���ܣ�������Ϣ����̨���߳�
	������
		pParam�����ݵĲ���
	����ֵ��
		UINT
	*/
	static UINT send_msg_to_back_server_thread(LPVOID pParam);

	/*
	���ܣ����ͱ���IP�ͻ�������������
	������
		void
	����ֵ��
		true���ɹ�
		flase��ʧ��
	*/
	bool send_local_ip_name_to_server(void);

	/*
	���ܣ��������󿪷���Ϣ��������
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool send_request_open_room_to_server(void);

	/*
	���ܣ�������Ϣ�����ط�������
	������
		msg��Ҫ���͵���Ϣ
	����ֵ��
		ture���ɹ�
		false��ʧ��
	*/
	bool send_msg_to_back_server(char *msg);

	
	/*
	���ܣ�������Ϣ�����ù���ϵͳ
	������
		msg��Ҫ���͵���Ϣ
	����ֵ��
		ture���ɹ�
		false��ʧ��
	*/
	bool send_msg_to_set_maiba_rule(TCHAR *msg);
	static UINT send_data_to_maiba_rule_thread(LPVOID pParam);


	/*
	���ܣ����պ�̨���͹�������Ϣ�߳�
	������
		pParam�����ݵĲ���
	����ֵ��
		UINT
	*/
	static UINT recv_server_msg_udp_thread(LPVOID pParam);
	static UINT recv_server_msg_tcp_thread(LPVOID pParam);

	/*
	���ܣ����ܺ�̨���͵���Ϣ����
	������
		void
	����ֵ��
		UINT
	*/
	UINT recv_server_msg_udp(void);
	UINT recv_server_msg_tcp(void);

	/*
		���ܣ�����̨������Ϣ����
		������
			void
		����ֵ��
			void
	*/
	static UINT send_server_msg_tcp_thread(LPVOID pParam);
	UINT send_server_msg_tcp(TCHAR* msg);



	/*
	���ܣ��ػ�Ԥ����
	������
		void
	����ֵ��
		void
	*/
	void exit_window_pretreat(void);

	/*
	���ܣ��ػ�
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool shutdown_computer(void);

	/*
	���ܣ��������������
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool reboot_computer(void);

	/*
	���ܣ�����osd�Ƿ񲥷����
	������
		void
	����ֵ��
		true���������
		flase��û�в������
	*/
	bool tv_osd_play_finish(void);

	/*
	���ܣ���ʾͼƬ����
	������
		path������ͼƬ·��
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_picture_screen_save(TCHAR *path);

	/*
	���ܣ��˳�����
	������
		void
	����ֵ��
		void
	*/
	void quit_screen_save(void);

	/*
	���ܣ����빦���ж�
	������
		args������
	����ֵ��
		void
	*/
	void password_function_judgement(const TCHAR *args);

	/*
		����:����ipad����
	*/
	void Generate_function_encode();

	/*
	����:���Ͷ�ά���flash
	*/
	void flash_message_call_encode(const TCHAR *args);

	/*
		���ܣ�����΢�ŵ���ά��
	*/
	void flash_message_call_wechat();


	/*
	���ܣ����ɶ�ά��ͼƬ
	������
	strData:���ɵ�����
	strPath:����ͼƬ�洢��·��
	����ֵ��
	true:�ɹ�
	false:ʧ��
	*/
	bool Generate_encode_picture(LPCSTR strData,CString strPath);

	/*
	���ܣ���Աע��
	������
		name����Ա����
		password����Ա����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool member_register(const TCHAR *name,const TCHAR *password);

	/*
	���ܣ���Ա��¼
	������
		name����Ա����
		password����Ա����
	����ֵ��
		-1:�û���������
		0���������
		1����¼�ɹ�
	*/
	int member_login(const TCHAR *name,const TCHAR *password);

	/*
	���ܣ���ʾ��Ա��¼�Ĵ�����ʾ
	������
	   error_code��������
   ����ֵ��
	   void
	*/
	void member_show_error_tip(int error_code);

	/*
	���ܣ���ʾ��Ա��¼�Ĵ�����ʾ
	������
	   error_msg��������Ϣ
   ����ֵ��
	   void
	*/
	void member_show_error_tip(TCHAR* error_msg);

	/*
	���ܣ�ɾ��¼��������ʾ
	������
	   error_msg��������Ϣ
   ����ֵ��
	   void
	*/
	void record_delete_show_error_tip(int error_code, int laste_error_code, TCHAR *song_name = L"");

	/*
	���ܣ���ʾ
	������
	   error_msg��������Ϣ
   ����ֵ��
	   void
	*/
	void show_error_tip(int error_code, TCHAR *fun);

	/*
	���ܣ��޸�����
	������
	   name���û���
	   old_password��������
	   new_password��������
   ����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool member_change_password(const TCHAR *name,const TCHAR *old_password,const TCHAR *new_password);

	/*
	���ܣ�ʹ������ƴ������
	������
		void
	����ֵ��
		void
	*/
	void use_smart_pinyin(void);

	/*
	���ܣ��õ�����ƴ��������ʾ���ַ�
	������
		result_string������ַ���
		array_size�������С
		query_letter����ѯ�����е��ַ�
		select_letter������ѡ����ַ�
		select_letter_count������ѡ����ַ�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_show_letter(std::wstring result_string[],int array_size,const TCHAR *query_letter,TCHAR select_letter[],int &select_letter_count);

	/*
	���ܣ�����ƴ���У����β��ܲ�ѯ���ַ�
	������
		select_letter������ѡ����ַ�
		select_letter_count������ѡ����ַ�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool flash_yinpin_hide_letter(TCHAR *select_letter,int select_letter_count);
	//��ʾ������ĸ
	bool flash_yinpin_show_all_letter(void);

	/*
	���ܣ����ŵ��˵�ͼƬ���
	������
		void
	����ֵ
		void
	*/
	void play_pc_AD_picture(void);

	/*
	���ܣ�����ǽ���ͼƬ���
	������
		void
	����ֵ
		void
	*/
	void play_wall_panel_AD_picture(void);

	/*
	���ܣ����ò��Ž�������λ��
	������
		void
	����ֵ��
		void
	*/
	void set_play_progress_bar_pos(void);
	//Ԥ������
	void set_preview_song_play_progress(void);

	/*
	���ܣ���ʾ������Ϣ
	������
		void
	����ֵ��
		void
	*/
	void show_help_info(void);

	/*
	���ܣ��������·�ҳ����
	������
		table_select_expr������ѡ����ʽ
		page_operate��ҳ����
		operate_type����������  ����ҳ���ǻ���  ˵����������1 �һ�����2   ����ҳ��ť��3  ����ҳ��ť��4  ��һҳ��ǰҳ��0
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool song_pre_next_page_change(select_expr &table_select_expr, int page_operate,int operate_type);
	bool movie_pre_next_page_change(int page_operate,int operate_type);
	bool member_song_pre_next_page_change(int page_operate,int operate_type);
	bool song_recorder_pre_next_page_change(int page_operate,int operate_type);
	
	/*
	���ܣ��������·�ҳ����
	������
		page_operate��ҳ����
		operate_type����������  ����ҳ���ǻ���  ˵����������1 �һ�����2   ����ҳ��ť��3  ����ҳ��ť��4  ��һҳ��ǰҳ��0
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool singer_pre_next_page_change(int page_operate,int operate_type);

	/*
	���ܣ���Ӱ���뵽��ѡ�б�
	������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool flash_message_call_select_film();

	/*
	���ܣ�����Ŀǰ������״̬������ѡ��ĸ�����ֱ�Ӳ��Ż��ǲ��뵽�����б�
	������
		song_information��������Ϣ��
		priority���Ƿ�����
		page_index:��ǰҳ��
		recv_msg�����ܵ���Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool play_or_insert_select_list(song_info &song_information,bool priority,bool recv_msg=false);


	/*
	���ܣ��ı�ѡ�и�������ɫ
	������
		song_information��������Ϣ
		number��ѡ�еı��
		priority:�Ƿ�����
	����ֵ��
		void
	*/
	void chang_select_song_color(song_info &song_information,int number,bool priority);

	/*
	���ܣ��������ݵ���̨�ķ�����򣬸�ʽ��Message&SONG_ID;%s$END  ˵����Message&��ʼ���� $END�������ţ��м�����������
	������
		data��Ҫ���͵�����
	����ֵ��
		void
	*/
	void send_data_to_service_udp(TCHAR *data);

	/*
	���ܣ����Ҹ��
	������
		in_lyric_path������ļ�·��
		in_lyric_index_path����������ļ�·��
		out_lyric������ĸ��
	����ֵ�� 
		true���ɹ�
		false��ʧ��
	*/
	bool decrypt_song_lyric(const TCHAR *in_lyric_path,const TCHAR *in_lyric_index_path,const TCHAR *in_song_id,TCHAR *out_lyric);

	/*
	���ܣ��������е�˫���ţ����ѱ�����ת���ɻ���
	������
		lyric�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool song_lyric_replace(TCHAR *lyric);

	/*
	���ܣ�д��������
	������
		com_send_flag���������ʾ
		adjust_count����������
	����ֵ��
		true���ɹ�
		falseʧ��
	*/
	bool write_com_data(COM_SEND_VALUE_FLAG com_send_flag, int adjust_count=0, bool auto_light = true, int light = -1);

	/*
	���ܣ��õ�ͼƬ�ĸ߶ȺͿ��
	������
	   image_path��ͼƬ·��
	   width��ͼƬ�Ŀ��
	   height��ͼƬ�ĸ߶�
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_image_resolution(TCHAR *image_path,int &width,int &height);

	/*
	���ܣ���ʾǽ���ͼƬ
	������
	   void
   ����ֵ��
	  true���ɹ�
	  false��ʧ��
	*/
	bool show_wall_panel_image(void);

	/*
	���ܣ����ܸ���ͼƬ
	������
		picture_path[in,out]:ͼƬ·��
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool decrypt_star_picture(TCHAR *picture_path,bool flag);

	/*
	���ܣ���ʾ��������
	������
		star_name����������
	����ֵ��
		void
	*/
	void show_singer_introduction(const TCHAR *star_name);

	/*
	���ܣ�ͨ��ѡ�����������ѳ�����ҳ��ĸ�����ת�����ǽ���
	������
		selet_song_page��true��ѡ�����ҳ�棬false���ѳ�����ҳ��
		agrs:ѡ��ĸ��Ǳ��
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool flash_message_call_select_sing_page_to_singer(const TCHAR *args,bool select_song_page);

	/*
	���ܣ���ʾ���ǵĸ���������
	������
	   star_name����������
	   singer_sex�������Ա�
	   star_region�����ǹ���
   ����ֵ��
	  true���ɹ�
	  false��ʧ��
	*/
	bool show_singer_song_introduction(TCHAR *star_name,TCHAR *star_sex,TCHAR *star_region);

	/*
	���ܣ�ͨ���������õ�����ͼƬ
	������
		singer_name����������
		singer_sex�������Ա�
		image_path��ͼƬ·��
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_singer_image_path(const TCHAR *star_name,TCHAR *star_sex,TCHAR *star_region,TCHAR *image_path);

	/*
	���ܣ���ʾ���ǵ�ͼƬ������
	������
		star_name����������
		singer_sex�������Ա�
		star_region�����ǹ���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_singer_image_introduction(const TCHAR *star_name,TCHAR *star_sex,TCHAR *star_region);

	/*
	���ܣ�ͨ����ŵõ��Կ�����Ϣ���Կ����豸��
	������
		device_index[in]���Կ��豸����
		display_name[out]���Կ����豸��
	����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool get_display_monitor_info(int device_index,TCHAR *display_name);

	/*
	���ܣ�������ѡ������Ŀ
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool update_select_song_count(void);

	/*
	���ܣ�������һҳʱ������һЩ��Ҫ���ݣ����ڷ���
	������
	����ֵ��
		true���ɹ�
		false:ʧ��
	*/
	bool save_data_copy();
	
	/*
	���ܣ�����ʱ���ѱ���ĸ�����ֵ����
	������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool resume_data_copy();

	/*
	���ܣ�����ѡ��ĸ���
	������
		args��ѡ��ĸ������
		recv_msg���Ƿ��ǽ��ܵ�����������Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool flash_message_call_priority_select_song(const TCHAR *args,bool recv_msg=false);

	/*
	���ܣ��϶�������ѡ�ĸ���
	������
		nOrigin��ѡ��ĸ�����ţ�����λ�ã�
		nDestination: Ŀ��λ�ã�����λ�ã�
		recv_msg���Ƿ��ǽ��ܵ�����������Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool flash_message_call_drag_sort_select_song(int nOrigin, int nDestination, bool recv_msg=false);

	bool flash_message_call_random_sort_select_song();
	/*
	���ܣ�����Ϣ�������еõ��ı�������̷�
	������
		mask������
	����ֵ
		�ı���̷�
	*/
	unsigned long FirstDriveFromMask (DWORD mask);

	/*
	���ܣ���ʾ����ͼƬ
	������
		page_operate��ҳ����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_service_image(SERVICE_PICTRUE_PAGE_OPERATE page_operate, TCHAR *interface_name = L"");

	/*
	���ܣ�������ҳ���
	������
		path;��ҳ���·��
		show_flag����ʾģʽ
		process_id�����̵�id
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool start_plug_in_process(const TCHAR *path,WORD show_flag,DWORD &process_id);
	bool start_plug_in_processEx(const TCHAR *path,WORD show_flag,DWORD &process_id, PROCESS_INFORMATION &process_info,
						DWORD flag = STARTF_USESHOWWINDOW, DWORD dwX = 0, DWORD dwY = 0,
						DWORD dwWidth = 0, DWORD dwHeight = 0);

	/*
	���ܣ��ж�һ�������Ƿ�������
	������
		process_name�����̵�����
		process_id�����̵�id
	����ֵ��
		true��������
		false��ֹͣ����
	*/
	bool check_process_run_state(TCHAR *process_name=NULL,DWORD process_id=-1);

	/*
	���ܣ���ֹĳһ������
	������
		�����̵�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool teminate_process(TCHAR *process_name,DWORD process_id=-1);

	/*
	���ܣ���ʾU�̸���
	������
	   void
	����ֵ��
		void
	*/
	void show_U_disk_song(void);

	/*
	���ܣ�U�̸�������ҳ�ı�
	������
		page_operate:ҳ������
		operate_type����������  ����ҳ���ǻ���  ˵����������1 �һ�����2   ����ҳ��ť��3  ����ҳ��ť��4  ��һҳ��ǰҳ��0
	����ֵ��
		void
	*/
	void U_disk_song_pre_next_page(PAGE_OPERATE page_operate,int operate_type);

	/*
	���ܣ�����������ѯ���ݿ�ĵ�Ӱ������ʾ��flash������
	������
	   void
   ����ֵ��
	  true���ɹ�
	  false��ʧ��
	*/
	bool movie_query_show_data(void);
	bool movie_query_detail_data(void);
	/*
	���ܣ�����ѡ���flash��Ϸ
	������
		args��ѡ��ı��
	����ֵ��
		void
	*/
	void play_select_game(const TCHAR *args);

	/*
	���ܣ�PC���л���Ƶ
	������
		args:ѡ�����Ƶ����
		time_protect:ʱ�䱣��
	����ֵ��
		void
	*/
	void flash_message_call_switch_screen_pc(const TCHAR *args,bool time_protect);

	/*
	���ܣ���Ƶͬ��������
	������
		args:ѡ��ı��
	����ֵ��
	   void
	*/
	void video_synchro_to_TV(const TCHAR *args);

	/*
	���ܣ���ʾ����������ҳ��
	������
	   row��������
	   page_count���ܵ�ҳ��
	   cur_page_number����ǰҳ��
   ����ֵ��
	   void
	*/
	void show_row_and_page_count(TCHAR *refresh_page,int row,int page_count,int cur_page_number);

	/*
	���ܣ���ʾ�������
	������
		data�����
	����ֵ��
		void
	*/
	void flash_show_others_opinion(const TCHAR *data,bool focus);

	/*
	���ܣ���ʾ��ϵ�绰
	������
	   data���绰
   ����ֵ��
	   void
	*/
	void flash_show_contact_phone(const TCHAR *data,bool focus);

	void flash_show_custom_phone(const TCHAR *data,bool focus);

	/*
	���ܣ���յ�����
	������
		void
	����ֵ��
		void
	*/
	void flash_clear_surver_result(void);

	/*
	���ܣ����ӵ���ҳ�����
	������
	   void
   ����ֵ��
	  void
	*/
	void page_proposal_clear(void);

	/*
		����: ���Ƹ���ҳ�����
		������
		   void
		����ֵ��
		   void
	*/
	void page_custom_clear(void);

	/*
		���ܣ���ʾ���Ƹ�������
		����:  
		����ֵ:
			void
	*/
	void flash_show_custom_song(const TCHAR* data,int song_nmuber,bool focus);

	/*
	���ܣ���Ա����
	������
		args�������ʾ
	����ֵ;
	   void
	*/
	void flash_message_call_member_manager(const TCHAR *args);

 

	/*
	���ܣ���ʾ��Ա����������ı�
	������
		textbox_number�������ı��
		text��������ı�
	����ֵ��
		void
	*/
	void show_member_manager_input_text(int textbox_number,TCHAR *text);

	/*
	���ܣ��ı��Ա����ҳ��Ļ�Ա����
	������
		state��״̬ ״̬˵����1����¼ 2��ע�� 3���޸����� 4:��Աע���ֻ���
	����ֵ��
		void
	*/
	void change_member_manage_state(int state);

	/*
	���ܣ���ջ�Ա����ҳ���������Ϣ
	������
	    void
	����ֵ��
	    void
	*/
	void clear_member_manage_input_text(void);

	/*
		���ܣ�ע��ʱ�Ƿ������ת
	*/
	void member_register_dialog_page_jump(TCHAR* command,TCHAR* tip_message, bool jump_state);

	/*
	���ܣ���ʾ����������
	������
		text��Ҫ��ʾ������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_system_manage_code(const TCHAR *text);

	/*
	���ܣ���ʾ�����
	������
		void
	����ֵ��
		void
	*/
	void show_password_window(void);

	/*
	���ܣ�������ͼ��ͼƬ��������
	������
		x������
		y������
		width�����
		heigth���߶�
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool show_drawing_image_to_tv(void);
	bool show_image_to_tv(TCHAR *path);

	/*
	���ܣ��õ�ĳ��ʽͼƬ�ı���
	������
	   format��ͼƬ��ʽ
	   pClisid����ӦͼƬ��ʽ�ı���
   ����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool GetEncoderClsid(LPCWSTR format,  CLSID*  pClsid);

	/*
	���ܣ��ڵ����м���ʾͼƬ
	������
		path��ͼƬ·��
		alignment_mode��ͼƬ���뷽ʽ
		show_time����ʾʱ��
		lyric_link��������ӱ�ʾ
		song_tip����һ����ʾ
	����ֵ��
		void
	*/
	void show_picture_on_tv(TCHAR* path,OSDAlignment alignment_mode,int show_time,bool lyric_link,bool song_tip);

	void show_recorder_picture_on_tv();

	/*
	���ܣ�ɾ��ѡ��ĸ���
	������
	   song_number��ѡ���Ҫɾ�������ı��
	   recv_msg�����յ�����������Ϣ
   ����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool flash_message_call_delete_select_song(const TCHAR *song_number,bool recv_msg=false); 
	//ɾ��¼�ĸ���
	bool flash_message_call_delete_recorder_song(const TCHAR *song_number);
	//ɾ����Ա����
	void flash_message_call_delete_person_song(const TCHAR *args);
	void flash_message_call_clear_person_song(void);
	void flash_message_call_delete_private_song(const TCHAR* args);

	//ɾ��¼������
	bool flash_message_call_delete_recorder_song_by_id(const TCHAR *song_number);

	
	/*
	���ܣ���ʾ��ȡ������
	������
		show:��ʾ��true  ����ʾ��false
	����ֵ��
		void
	*/
	void screen_show_visible(bool show);

	/*
	���ܣ��õ������صĹ���
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_master_slave_function(void);

	/*
	���ܣ��������߳�
	������
		pParam�����ݵĲ���
	����ֵ��
		UINT
	*/
	static UINT master_slave_control_thread(LPVOID pParam);

	/*
	���ܣ���������������
	������
		void
	����ֵ��
		UINT
	*/
	UINT recv_master_slave_control_data(void);

	/*
	���ܣ�ͨ��ID�õ�������Ϣ
	������
		song_id������id
		query_song_info:������Ϣ
		video_type����������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_song_info_by_id(const TCHAR *song_id,song_info &query_song_info,PLAY_SONG_TYPE video_type);
	//��Ӱ��
	bool get_movie_info_by_id(const TCHAR *song_id,song_info &query_song_info,PLAY_SONG_TYPE video_type);
	bool get_film_info_by_id(const TCHAR *song_id, song_info &query_song_info);
	//¼����
	bool get_record_song_info_by_id(const TCHAR *song_id,song_info &query_song_info,PLAY_SONG_TYPE video_type); 

	/*
	���ܣ���֪flash��ʾ��ѡ�����ѳ�����
	������
		page_code��ҳ��
	����ֵ:
		void
	*/
	void inform_flash_show_select_or_sing_text(int page_code);

	/*
	���ܣ���ֵһЩ��ť״̬��������ǵ��������Ե�
	������
		void
	����ֵ��
		void
	*/
	void set_flash_button_state(TCHAR *command,int button_number);
	/*
	���ܣ����ð�ť����״̬
	������
		init_state���Ƿ�Ҫ�ָ��ɳ�ʼ״̬
	����ֵ��
	   void
	*/
	void set_button_highlight_state(bool init_state);

	/*
	���ܣ������ʾ�б�
	������
	   void
   ����ֵ��
	   void
	*/
	void clear_show_list(void);

	/*
	���ܣ�����¼����Ƶ��U��
	������
		 pParam���̴߳��ݵĲ���
	����ֵ��
		void
	*/
	static UINT save_data_to_U_disk_thread(LPVOID pParam);
	void save_data_to_U_disk(void);

	/*
	���ܣ��ı���Ч
	������
		audio_effect��ѡ�е���Ч
	����ֵ��
		void
	*/
	void change_audio_effect(int audio_effect);

	/*
	���ܣ��ı�������Ч
	������
		audio_effect��ѡ�е���Ч
	����ֵ��
		void
	*/
	void change_music_sound(int music_sound);

	/*
	���ܣ���ʾ��Ƶ����
	������
		void
	����ֵ��
		void
	*/
	void pc_show_video_window(void);

	/*
	���ܣ���֪flash�Ƿ���ʾ�ƹ⡢��Ч���Ӵ���
	������
		void
	����ֵ��
		void
	*/
	void show_control_sub_window(void);

	/*
	���ܣ���ʾ��ѡ��
	������
		show����ʾ�������� true����ʾ  false������
	����ֵ��
		void
	*/
	void show_check_window(bool show);

	/*
	���ܣ�����ϵͳ��Ϣ
	������
		args�����ݹ����Ĳ���
	����ֵ��
		void
	*/
	void change_system_info(const TCHAR *args);

	/*
	���ܣ���ʾϵͳ��Ϣ
	������
		textbox_number���������
		text����ʾ����
	����ֵ��
		void
	*/
	void show_system_info_input_text(int textbox_number,const TCHAR *text);

	/*
	���ܣ���ʾ��������ֺ�IP��ַ
	������
	  void
   ����ֵ��
	   void
	*/
	void show_local_computer_name_IP(void);

	/*
	���ܣ�ϵͳ��Ϣ�ļ�������
	������
		args��ѡ��Ĳ���
	����ֵ��
		void
	*/
	void system_info_keyboard_input(const TCHAR *agrs);

	/*
	���ܣ�ͨ�����ݿ��song��õ�6��������·��
	������
		void
	����ֵ��
		void
	*/
	void get_server_path_by_db(void);

	/*
	���ܣ��������״��
	������
		void
	����ֵ��
		void
	*/
	void check_net_status(void);

	/*
	���ܣ�ʵ�ֻ���
	������
		args���汾
	����ֵ��
		void
	*/
	void change_flash_skin(const TCHAR *args);

	/*
	���ܣ���ʾӡ��ҳ
	������
		void
	����ֵ��
		void
	*/
	void show_screen_top_image(void);
	/*
	���ܣ��򿪴����������Ƶʧ��֮�󣬻ص�������Ƶ
	������
		void
	����ֵ��
		void
	*/
	void switch_screen_play_song_video(void);

	/*
	���ܣ��ı������ʾ��ʽ
	������
		args�����ݹ����Ĳ���
	����ֵ��
		void
	*/
	void change_song_show_mode(const TCHAR *args);

	/*
	���ܣ���ʾѡ�趯����ʾ
	������
	   void
   ����ֵ��
	   void
	*/
	void show_select_song_animation(void);

	/*
	���ܣ�ɾ��ǰһ�����ӣ������µ�����
	������
		server_number�����������
	����ֵ��
		void
	*/
	void change_link_server_number(int server_number);

	/*
	���ܣ�Ԥ����һ����ѡ����и���
	������
		void
	����ֵ��
		void
	*/
	void preview_next_song(void);

	/*
	���ܣ��ı���д����λ��
	������
		void
	����ֵ��
		void
	*/
	void move_handwriting_window_pos(void);

	/*
	���ܣ��ı���д����ɫ
	������
	   void
   ����ֵ��
	   void
	*/
	void change_handwriting_window_color(void);

	/*
	���ܣ��򿪻�ر�Ԥ����Ƶ
	������
	   void
   ����ֵ��
	   void
	*/
	void open_preview_audio(void);

	/*
	���ܣ����������Ÿ�����Ϣ���ֳ��豸
	������
		void
	����ֵ��
		void
	*/
	void send_playing_song_to_handheld(void);

	/*
	���ܣ�������ѡ������Ϣ���ֳ��豸
	������
	   void
   ����ֵ��
	   void
	*/
	void send_select_song_to_handheld(void);

	/*
	���ܣ������ѳ�������Ϣ���ֳ��豸
	������
	   void
   ����ֵ��
	   void
	*/
	void send_sing_song_to_handheld(void);

	
		/*
	���ܣ�����¼��������Ϣ���ƶ��豸
	������
	   void
   ����ֵ��
	   void
	*/
	void send_tape_song_to_pad(void);

	/*
	���ܣ����Ͳ�ѯ������Ϣ���ֳ��豸
	������
	   page_operate��ҳ������
	   page_row_count������ǵ�һҳ��������������ҳ���ǵ�ǰҳ��
   ����ֵ��
	   void
	*/
	void send_query_song_to_handheld(int page_operate,int page_row_count);
	void send_query_singer_to_handheld(int page_operate,int page_row_count);
	void send_query_movie_to_handheld(int page_operate,int page_row_count);

	/*
	���ܣ���֯���͸��ֳֵ�һ��������Ϣ
	������
		send_song_info��������Ϣ
		song_number���������
		send_data��Ҫ���͵�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool make_send_handheld_song_info(song_info &send_song_info,int song_number,TCHAR *send_data);
	bool make_send_handheld_movie_info(song_info &send_song_info,int movie_number,TCHAR *send_data);

	/*
	���ܣ��ı�����
	������
	   args������
   ����ֵ��
	   void
	*/
	void flash_message_call_change_language(const TCHAR *args);

	/*
	���ܣ��ı�Ŀǰʹ�õ�����
	������
		void
	����ֵ��
		void
	*/
	void change_flash_show_language(void);

	/*
	���ܣ�������ʼ��
	������
		void
	����ֵ��
		void
	*/
	void change_skin_init(void);

	/*
	���ܣ���ʾ����ҳ��
	������
	   args������ҳ���ʾ
   ����ֵ��
	   void
	*/
	void show_pop_up_page(const TCHAR *args);

	/*
	���ܣ�ͨ���ֳֵ�sql����ѯ���ݣ�Ȼ���͸��ֳ�
	������
		recv_data�����ܵ�sql���
	����ֵ��
		void
	*/
	void query_song_by_handheld_sql(char *recv_data);
	void query_singer_by_handheld_sql(char *recv_data);
	void query_movie_by_handheld_sql(char *recv_data);

	/*
	���ܣ����Ʋ�����ʱ�䱣��
	������
	   operate_code��������
	����ֵ��
	   true�����б�������ֹ�ò���
	   false�����Խ��иò���
	*/
	bool protect_control_operate(int operate_code);

	/*
	���ܣ�����IE����
	������
		void
	����ֵ��
	   void
	*/
	void start_IE_software(void);

	/*
	���ܣ�������һ�׸������д��
	������
		mark_score������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool make_mark_for_singer(int mark_score);

	/*
	���ܣ�ʹ���ӵ��ļ���ʽ���ط�
	������
	   void
   ����ֵ��
	   void
	*/
	void use_file_open_room(void);

	/*
	���ܣ�Ϊ��ʹ�����������Ӳ�ѯ�ٶȣ����Ըı��ѯ��ʽ
	������
		select_condition����ѯ����
		condition_suffix�������±�
		column_name���е�����
		max_char�������ַ�
		spell_query��trueƴ����ѯ  false����д��ѯ
	����ֵ��
		void
	*/
	void change_query_mode(query_condition select_condition[],int condition_suffix,TCHAR *column_name,TCHAR *max_char,bool spell_query);

	/*
	���ܣ�ͨ��ͼƬ��ʼ��Image��
	������
		void
	����ֵ��
		void
	*/
	void create_osd_image(void);

	/*
	���ܣ����ɸ�����ʾͼƬ
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool save_song_tip_osd(void);
	bool save_score_tip_osd(int total_score,int average_similarity,int average_intact,int average_stability,int total_calories);
	bool save_music_enjoy_osd(const TCHAR* src_path, TCHAR* des_path);

	/*
	���ܣ���ʾ������ʾͼƬ
	������
	   void
   ����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool show_song_tip_osd(void);

	/*
	���ܣ����������Ƶ
	������
		args���ٷֱ�
	����ֵ��
		void
	*/
	void set_video_play_pos(const TCHAR *args);

	/*
	���ܣ����ͼ�����ֵ��������Ϸ
	������
		keybd_code��������ֵ
	����ֵ��
		void
	*/
	void send_keybd_code_to_game(int keybd_code);

	/*
	���ܣ����ͼ������ͼƬ��flash
	������
		void
   ����ֵ��
	   void
	*/
	void send_query_panel_to_flash(void);

	/*
	���ܣ���������ͼƬ��flash
	������
		void
	����ֵ��
		void
	*/
	void send_pinqie_image_to_flash(void);

	/*
	���ܣ����Ͱ���ͼƬ��flash
	������
		void
	����ֵ��
		void
	*/
	void send_big_help_image_to_flash(void);

	/*
	���ܣ����͹���ͼƬ
	������
		void
	����ֵ��
		void
	*/
	void send_national_flag_to_flash(void);

	/*
	���ܣ������������ͼƬ
	������
	   void
   ����ֵ��
	  void
	*/
	void send_opinion_image_to_flash(void);

	/*
	���ܣ�ȡ�����з���
	������
		void
	����ֵ��
		void
	*/
	void cancel_call_service(void);

	/*
	���ܣ����ͷ���ť״̬
	������
		button_number����ť��ʶ
		button_state����ť״̬
	����ֵ��
	   void
	*/
	void send_service_button_state(int button_number,int button_state);

	/*
	���ܣ����͵ƹⰴť״̬
	������
		void
	����ֵ��
	   void
	*/
	void send_light_button_state(void);

	/*
	���ܣ��������ְ�ť״̬
	������
		void
	����ֵ��
	   void
	*/
	void send_score_button_state(int state = 0);

	/*
	���ܣ�������Ч��ť״̬
	������
	   void
   ����ֵ��
	   void
   */
	void send_audio_effect_button_state(void);

	/*
	���ܣ�������Ч��ť״̬
	������
	   void
   ����ֵ��
	   void
   */
	void send_music_sound_button_state(void);

	/*
	���ܣ�������д���԰�ť״̬
	������
		void
	����ֵ��
		void
	*/
	void send_ink_language_button_state(void);

	/*
	���ܣ����ͻ�����Ч��ť״̬
	������
	   void
   ����ֵ��
	   void
   */
	void send_environment_audio_button_state(void);

	/*
		���ܣ�����ԭ�鳪��ť״̬
		������
			void
		����ֵ��
			void
	*/
	void send_accompany_original_button_state(void);


	/*
	���ܣ���ȡ��ʾ��Ϣ
	������
		file_name���ļ���
	����ֵ��
		void
	*/
	void read_tip_text(TCHAR *file_name);

	/*
	���ܣ�������Ƕ��ˮҳ��
	������
	   void
   ����ֵ��
	  void
	*/
	void hide_plug_in_drinks(void);

	/*
	���ܣ��õ�������Ϣ
	������
		room_info��������Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_room_info(TCHAR *room_info);

	/*
	���ܣ����ƻ���ʾ��������
	������
		scroll_text������������
		scroll_count����������
	����ֵ��
		void
	*/
	void doorplate_show_scroll_text(TCHAR *scroll_text,int scroll_count);

	/*
	���ܣ����ͺ��з���״̬�����ƻ�
	������
		service_state������״̬  true������ false��ȡ������
	����ֵ��
		void
	*/
	void send_service_state_to_doorplate(bool service_state);

	/*
	���ܣ���ʾ����ҳ�����ʾ��Ϣ
	������
	   void
   ����ֵ��
	   void
	*/
	void show_video_page_tip_msg(void);

	/*
	���ܣ����õ�����ť״̬
	������
	   show_state��״̬
   ����ֵ��
	   void
	*/
	void set_guid_song_button_state(bool show_state);

	/*
	���ܣ���������ť״̬
	������
		void
	����ֵ��
	   void
	*/
	void update_sort_button_state(void);

		/*
	���ܣ����ð�ť״̬
	������
	   show_state��״̬
   ����ֵ��
	   void
	*/
	void set_button_show_state(enum BUTTON_STATE button_flag,bool show_state);

	/*
	���ܣ���������ʽ
	������
	   void
   ����ֵ��
	  void
	*/
	void set_query_sort_mode(void);

	/*
	���ܣ��ж���ⴰ���Ƿ��ƶ�
	������
	   void
   ����ֵ��
	   void
	*/
	void judge_soft_window_move(void);

	/*
	���ܣ����͹�˾logo��flash����
	������
		void
	����ֵ��
		void
	*/
	void send_ktv_logo_to_flash(void);

	/*
	���ܣ����ͼ���ҳ��ļ���������flash
	������
	   void
   ����ֵ��
	   void
	*/
	void send_query_condition_text_to_flash(void);

	/*
	���ܣ����ü�����������
	������
	   keyboard_type����������
   ����ֵ��
	  void
	*/
	void set_keyboard_type(int keyboard_type);
	/*
	���ܣ���ʾ΢��ϵͳ
	������
	   void
   ����ֵ��
	   void
	*/
	void show_weibo_system(void);

	/*
	���ܣ�������ⴰ��λ��
	������
	   left_pos����ʼX����
		width�����ڿ��
	����ֵ��
		void
	*/
	void adjust_soft_window_width(int &left_pos,int &width);

	/*
	���ܣ�������ⴰ��λ��
	������
	   left_pos����ʼX����
		width�����ڿ��
		height:���ڵĸ߶�
	����ֵ��
		void
	*/
	void adjust_soft_window_width(int &left_pos,int &width,int &height);


	/*
	���ܣ��õ�΢��ͼƬ���
	������
	   void
   ����ֵ��
	   void
	*/
	void Get_weibo_image_width(void);

	/*
	���ܣ����ӷ�����
	*/
	bool connect_server();

	static UINT recvData_thread(LPVOID pParam);    //��Ϣ�߳�

	void recv_pk_server_data();   //���շ���������������

	/********************************��Ƶ����****************************************/	
	/*
	���ܣ���Ƶ���ѣ����շ������������������Ľ�����Ϣ
	*/
	bool recv_serv_or_room_msg();
	static UINT recv_video_dating_thread(LPVOID pParam);    //��Ϣ�߳�
	void recv_video_dating_server_data();   //���շ���������������
	void send_server_video_dating_data(video_dating_status istatus, bool init = false);	//������Ƶ���ѵ���Ϣ��������
	void send_vd_three_screen_data(int page_operate,int operate_type);
	/*
	���ܣ��õ���Ƶ���ѹ��ж���ҳ
	*/
	int get_video_dating_page_total();
	/*
	���ܣ���Ƶ�������·�ҳ����
	������
	page_operate��ҳ����
	operate_type����������  ����ҳ���ǻ���  ˵����������1 �һ�����2   ����ҳ��ť��3  ����ҳ��ť��4  ��һҳ��ǰҳ��0
	����ֵ��	 
	*/
	void record_vd_current_page(int operate_type);
	/*
	���ܣ���֯xml����flash
	*/
	void make_video_dating_list(std::wstring &pk_list_xml);
	void connect_video_dating(TCHAR* connect_ip,TCHAR *send_msg);  //������Ϣ���Է�ip
	void parse_client_video_dating(TCHAR* data);
	void send_video_dating_info_to_flash();
	void accept_vd_invitation(int nFlags);   //���ܶԷ�����/ȡ���Է����� 1�����롣0��ȡ��
	/************************************************************************/


	/*
	���ܣ�����pk���ݸ�������
	������
		iFlags:����pk��Ա��״̬��0��ע����1����½
	*/
	void send_pk_data_to_server(int iFlags); 

	bool GetHostIP(char *local_ip);  //�õ�����ip

	void send_pk_three_screen_data(int page_operate,int operate_type);

	/*
	���ܣ�pk��Ա���·�ҳ����
	������
	page_operate��ҳ����
	operate_type����������  ����ҳ���ǻ���  ˵����������1 �һ�����2   ����ҳ��ť��3  ����ҳ��ť��4  ��һҳ��ǰҳ��0
	����ֵ��
	 
	*/
	void record_pk_current_page(int operate_type);

	/*
	���ܣ���֯xml����flash
	*/
	void make_pk_member_list(std::wstring &pk_list_xml);

	/*
	���ܣ��õ���Ա���ж���ҳ
	*/
	int get_pk_memeber_page_total();
	 
	void parse_recv_data(TCHAR* data);  //���������������������� 

	void parse_recv_video_dating_data(TCHAR* data); //������Ƶ���ѷ���������������
	
	void accept_invitation(int nFlags);   //���ܶԷ�����/ȡ���Է����� 1�����롣0��ȡ��

	void send_date_to_invitation();   //����������Է�(����ip��)

	void connect_inviation(TCHAR* connect_ip,TCHAR *send_msg);  //������Ϣ���Է�ip 

	void establish_video_connection(TCHAR* data);//�����Է�������������

	/*
	���ܣ����ӱ����ĺ��ӣ��������ͶԷ�pc������
	������
		local_ip:����ip
		other_ip:�Է�pc��ip
		local_port:���������˿�
		other_port:�Է�����
	*/
	void send_data_to_video_box_start(TCHAR* local_ip,TCHAR* other_ip);

	/*
	���ܣ�ֹͣ��pc����
	*/
	void send_data_to_video_box_stop(TCHAR* boxIP);

	/*
	���ܣ��˳�ʱ���ر���Ƶת����һЩ����
	*/
	void close_video_box();

	/*
		���ܣ��Ƿ�����pk����
		����ֵ��
		true:����
		false��������
	*/
	bool get_use_pk_function();  

	/*
		���ܣ��Ƿ�������Ƶ���ѹ���
		����ֵ��
		true:����
		false��������
	*/
	bool get_use_video_dating_function();  

	/*
	���ܣ��ж��Ƿ�����������֤��
	������
		��
	����ֵ��
		true:����
		false:������
	*/
	bool judge_generate_encode();


	/*
		���ܣ�����PKʱ��������ƵOSDͼƬ
		����:
			��
		����ֵ:
			��
	*/

	void set_pk_video_osd_picture();

	/*
	���ܣ����ͷ���״̬���ƶ��������
	������
		void
	����ֵ��
		void
	*/
	void send_room_state_to_ipad_server(void);

	/*
		����:��΢�����͸�������(���ڲ��ţ���һ��)
		����:
			play_song:���ڲ���
			next_song:��һ��
		����ֵ:
			void
	*/
	void send_song_name_data_to_weibo(TCHAR* play_song,TCHAR* next_song);

	/*
		����:΢�������͹������
		����:
			ad_text:�������
		����ֵ:
			void
	*/
	void send_ad_data_to_weibo(TCHAR* ad_text);

	/*
	���ܣ��������ֵ�ͼƬ
	������
	   draw_handle;���ƾ��
	   x:��ʼλ��X
	   y:��ʼλ��Y
	   width�����
	   height���߶�
	   font_color��������ɫ
	   font������
	   text�����Ƶ�����
	*/
	bool draw_text_to_image(Graphics &draw_handle,int x,int y,int width,int height,StringAlignment horizontal_alignment,Color font_color,Font &text_font,TCHAR *text);


	/*
	���ܣ�����ͼƬ����������
	������
		draw_handle�����ƾ��
		x:��ʼλ��x
		y:��ʼλ��y
		path��ͼƬ·��
	*/
	bool draw_image_to_offscreen(Graphics &draw_handle,int x,int y,TCHAR *path);

		/*
	���ܣ��ж��Ƿ���ʾǽ���
	������
	   void
   ����ֵ
	   true:�ɹ�
	   false:ʧ��
	*/
	bool show_wall_panel_interface(void);

	
	/*
	���ܣ��ϳ���Ƶ
	������
		void
	����ֵ��
		UINT
	*/
	UINT mixer_audio(void);

	/*
	���ܣ������Ƶ�߳�
	������
		pParam�����ݵĲ���
	����ֵ��
		UINT
	*/
	static UINT mixer_audio_thread(LPVOID pParam);

	/*
		���ܣ�����/�رյ�������
		������
		����ֵ��
			void
	*/
	void exit_enter_guid_song(bool guid_song);

	/*
	���ܣ����ͷ����ά��ͼƬ��flash
	������
		url��������ַ
	����ֵ��
		void
	*/
	void send_share_url_image_to_flash(TCHAR *url);

	
	/*
	���ܣ�����ͼƬ
	������
		des_path���洢ͼƬ·��
		src_path��ԴʼͼƬ·��
		format��ͼƬ��ʽ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool zoom_image(TCHAR *des_path,int des_width,int des_height,TCHAR *src_path,TCHAR *format,int cut_width,int cut_height);
 
		/*
	���ܣ�����¼����������flash
	������
		void
	����ֵ��
		void
	*/
	void send_tape_audio_count_to_flash(void);

	/*
	���ܣ�ͨ���������ı�ҳ��
	������
		args:Ҫ��ʾ��ҳ��
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool flash_message_call_change_show_page(const TCHAR *args);

	//��ѯ�����߳�
	static UINT query_data_thread(LPVOID pParam);

	
	/*
	���ܣ����ݵ�ǰ�ĸ���id �õ���ǰ�����������Ϣ
	����
	song_id:����id
	����ֵ

	*/
	bool recommand_song_by_song_id();


	//��ѯtop_song �����ǰʮ������
	static UINT query_recommand_top_song_thread(LPVOID pParam);

	/*
		���ܣ��õ����а�ǰʮ������
		������
			query_sql:��ǰҳ��Ĳ�ѯ����

	*/
	bool recommand_song_by_top_song();

	/*
		���ܣ��õ���ǰ������Ϣ���Ƽ�����
		����:
			issue_year:       ���
			language:         ����
			song_theme:       ��������
			singer_sex:       �����Ա�
			singer_region_new:�������� 
			song_name:        ������
			singer_name:      ��������
		����ֵ��

	*/
	bool get_recommend_song_info(const TCHAR* issue_year,const TCHAR *language,const TCHAR* song_theme,const TCHAR* singer_sex,
		const TCHAR* singer_region_new,const TCHAR *song_name,const TCHAR* singer_name,const TCHAR* song_id);

	/*
		�����Ƽ��������ݸ�flash����
	*/
	bool flash_message_call_recommend_song();

	/*
		���ܣ�ͨ���ղصĸ���id����ѯ������
		������
			song_id_list���������
	*/
	bool song_query_member_data_by_id(std::wstring song_id_list);
	
	/*
		���ܣ����͹��溯��
		������
			place_notice:�����Ĺ���

	*/
	bool flash_message_call_place_notice();


	/*
		���ܣ�����web�������������Ĺ���
		������
			recv_data:����
			rule_falgs:�����ʾ 1������pk 2����̨pk
			nFalgs: 0�����ܷ�����������������  1,�����ݷ��͸�flash
		����ֵ��
			ture���ɹ�
			false��ʧ��
	*/
	bool parse_arena_rule_info(char* recv_data,int rule_falgs,int nFalgs);
	bool parse_arena_rule_info_ex(char* recv_data,int rule_falgs);


	/*
		���ܣ�����K�����������Է�����������
		������
			recv_data:���ܷ�����������
	*/
	bool parse_maiba_song_info(char* recv_data);  //K������������  (��������)


	bool parse_maiba_arena_info(char* recv_data);   //û����
	bool parse_server_arena_song(char* recv_data, int flag);//��̨PK, ��ʱû����


	/*
		����: ���Ͱ������ƺ�����
	*/
	void flash_message_call_room_name_ranking();
	void parse_message_call_room_ranking(char* recv_data);
	
	/*
		���ܣ��õ�΢�ŵĶ�ά��
		������
			wechat_number:΢����
		����ֵ��
	*/
	void get_wechat_song_encode_number(char * wechat_data);

	/*
	2015-2-9 18:01:53--LTL
	���ܣ������ƶ���֤������ػ�
	������
	    flag: 0�����  1��΢��
	����ֵ��
	    void
	*/
	void send_mobile_code_to_slave(int flag);
	/*
		���ܣ����ݸ���id��ѯ�õ��Ƽ����������߳�
		������
		pParam�����ݵĲ���
		����ֵ��
		UINT
	*/
	static UINT query_recommend_song_thread(LPVOID pParam);

	/*
		���ܣ������ӷ������ݿ�
		������
			pParam:�̴߳��ݲ���
		����ֵ
			void
	*/ 
	static UINT send_data_to_box_thread(LPVOID pParam);
	void send_db_to_box(void);

	/*
		���ܣ��������������
		������
			request_date: ����
			nport:����
		����ֵ��
			void
	*/
	static UINT send_data_to_box_tcp_thread(LPVOID pParam);
	void send_data_to_box_tcp();
	
	/*
		���ܣ����������߳�
	*/
	static UINT send_order_data_thread(LPVOID pParam);
	void send_order_data_function_data(TCHAR *request_data,int nPort);

	/*
		���ܣ�ͨ���̷߳�������
		������
			request_data:����
			nPort:�˿�
	*/
	void thread_send_to_box_tcp_function(const TCHAR* request_data,int nPort);

	/*
		���ܣ�flash�����������
		������
			maiba_type����Ե����� 
	*/
	bool flash_message_call_maiba_pk_data(PAGE_OPERATE page_operate_type);

	

	void maiba_pk_data_test();



	//��֯xml����
	bool make_recorder_arena_song_list_xml(std::wstring& song_list_xml,enum PAGE_OPERATE page_operate);


	/***************************************************
		����һ���ļ���md5(2Gһ���ļ�)
	name�ļ�·��
	md5_buff���������md5��ֵ
	****************************************************/
	int get_file_md5(char *name,char *md5_buff);

	bool show_handwrite_select_result(void);
	
	bool show_pinyin_select_result(void);

	/*
		���ܣ��жϵ�ǰ�����Ƿ������ѡ��,�Ƿ񵽵�ǰҳ������ظ����
		������
			song_number:����id
			page_index:��ǰҳ��
		����ֵ��
			true:�����ظ����,false:�����ظ����
	*/
	bool repeat_select_song(TCHAR* song_number,int page_index);

	/*
		���ܣ�ɾ��map�еĴ��ڸ���
		������
			song_number:����id
		����ֵ��
			void
	*/
	void delete_repeat_select_song(song_info &select_song_info);

	/*
		���ܣ���սҳ��ʱ�ı�����map�е�ֵ
		������
			page_inde:��ǰҳ��
		����ֵ��
			void
	*/
	void change_repeat_select_song(int page_indxe);


	/*
		���ܣ����õ�ǰ�İ汾�ͼ��ܹ�����ʱ��
		������
			void
		����ֵ��
			void
	*/
	void set_system_version_date();

	/*
	���ܣ��������ط��͹�����¼�����ݣ��������ݿ�
	������
		record_info��¼����Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool save_record_info_to_db(TCHAR *record_info);


		/*
		���ܣ������������̨������Ϣ
		������
			recv_date: ���ܷ���������Ϣ
		����ֵ:
			void
	*/
	void parse_arena_song_info(TCHAR* song_id);


	/*
		���ܣ����ͻ�Ա���ݸ�flash
	*/
	void flash_message_calll_memeber_info();



	/*
		���ܣ��ж��û��Ƿ��Ѿ���¼��
	*/
	bool judge_memeber_is_login();

	/*
		���ܣ���ȡ��ˮ���ݷ��͸�flash
	*/
	bool flash_message_call_read_drinks_data();
	bool flash_message_call_drinks_data(char* data,TCHAR* drink_path);

	/*
		���ܣ��Ƿ������������
	*/
	bool judge_parse_request_web_data(TCHAR* webflags);

	/*
		���ܣ���֯�����ļ���ַ
	*/
	static UINT recv_date_from_box_tcp_thread(LPVOID pParam);
	void recv_data_from_box_tcp();

	/*
		���ܣ�������ͷ�������
		������
			down_addr:���ص�ַ
			down_type:��������  1��ͷ��  2����ַ
			local_path:����·��
	*/
	bool parse_memeber_head_picture_name(IN const TCHAR* down_addr,OUT TCHAR* local_path,IN int down_type);


	/*
		���ܣ�������еĻ�Ա��Ϣ
	*/
	bool clear_all_member_show_info();


	/*
	 ���ܣ���ʾ�����������ʾ��
	 ������
		 score:�������
	����ֵ��
		void
	*/
	void show_sing_score(int score);

	/*
	���ܣ��ϳ�����ͼƬ����
	������	nScore���ܷ�
			nSimilarity�����ƶ�(��׼)
			nStability���ȶ���(��׼)
			nIntact��������
	����ֵ��
			true���ɹ�
	*/
	bool compose_score_image(int nScore, int nSimilarity, int nStability, int nIntact, TCHAR *pImgPath);
	/*
	���ܣ���ʾ�������֣��ܷ֣����ƶ�(��׼)���ȶ���(��׼)�������ȣ�
	������nScore���ܷ�
		  nSimilarity�����ƶ�(��׼)
		  nStability���ȶ���(��׼)
		  nIntact��������
	����ֵ��
		  true���ɹ�
	*/
	bool show_single_score(int nScore, int nSimilarity, int nStability, int nIntact);
	/*��ʾ���ֶ���flash*/
	void show_score_video_flash();
	/*���͸�flash�ؼ�*/
	bool flash_message_call_score_tv(int nScore, int nSimilarity, int nStability, int nIntact);
	/*
		���ܣ��������ݸ�����ˣ���ʾ�Ƿ����ɹ�
		������
			song_number������id
	*/
	void share_success_send_to_server(TCHAR *song_number);

	/*
		���ܣ������õ��㲥��������Ϣ(���������)
	*/
	void parse_message_call_maiba_song(char* recv_data);

	void parse_message_call_arena_one_song(char* recv_data);
	

	/*
		���ܣ�����ͷ���ͼƬ
		������
			void
		����ֵ:
			void
	*/
	void request_head_picture_function();


	/*
		���ܣ���֯��Ա�ַ�������������
		������
			void
		����ֵ:
			void
	*/
	void send_master_slave_data_vip_info();


	/*
		���ܣ��������ط����������ݲ����и�ֵ
		������
			recv_data����Ա����
		����ֵ:
			void
	*/
	void parse_master_slave_data_vip_info(TCHAR* recv_data);

	/*
		���ܣ�������ʾ��Ա��Ϣ
		������
			void
		����ֵ:
			void
	*/
	void flash_message_call_show_member_vip();

	/*
		���ܣ����������͸���
		������
			recv_data�����ܵ�������
		����ֵ��
			void
	*/
	void flash_message_call_service_push_song(char* recv_data);

	void flash_message_call_service_share_success(char * recv_data);

	void start_software_on_close();

	static UINT flash_message_call_service_barrage(LPVOID pParam);


	/*
	���ܣ����ͷ���ɹ���ʾ�����������
	������
		void
	����ֵ��
		UINT
	*/
	UINT song_share_success(void);
	static UINT song_share_success_thread(LPVOID pParam);

	/*
		���ܣ����߳�����IPAD�����
	*/
	UINT start_ipad_service(void);
	static UINT start_ipad_service_thread(LPVOID pParam);

	/*
		����:����ø����������
	*/
	void share_song_to_rale_server(TCHAR * song_id,TCHAR* URL);


	void get_dekaron_song_url_id(const TCHAR* song_id,TCHAR* url_id);

	/*
	���ܣ��������ֽ��
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool compute_socre_result(void);

	/*
	���ܣ�����������Ƶ
	������
		void
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool play_score_video(void);

	/*
		����:����udp���������㲥
		������
			socre:����
			video_info:��ǰ������Ƶ
		����ֵ��
			void
	*/
	void send_socre_data_to_room_udp(int socre,song_info &video_info);
	/*
		����:�����������͵�json����
		������
			video_info:��ǰ������Ƶ
		����ֵ��
			void
	*/
	void song_query_show_data_json(int page_code);
	void parse_song_enjoy_json(Json::Value &info, TCHAR *path_name);
	/*
		����:����ID��ȡ��Ҫ��ѯ���ĸ�����Ϣ�����͸���˿(xs)
		������
			video_info:��ǰ������Ƶ
		����ֵ��
			void
	*/
	bool song_query_show_data_by_id(select_expr &table_select_expr,bool page_expr, TCHAR *args);

	

	/*
	���ܣ�flash����������������
	������
		maiba_type����Ե����� 
	*/
	bool flash_message_call_music_enjoy_data(int page_code, bool binit = true);

	/*
		�ӷ��������ظø���
		down_type: ��������
	*/
	void dwon_song_file_to_server(const TCHAR* args, int down_type);

	/*
		�жϵ�ǰ���ظ�����map���Ƿ����
	*/

	bool judge_down_song_map_by_id(TCHAR * song_id);

	/*
		�õ���ǰ��������ϵĸ���,�޸ı�ʾ
	*/
	void down_song_file_success(char *down_data);

	/*
		����flashһ���յ��б�
	*/
	void send_to_flash_empty_list(bool flag = true); //true : ���� false : ����

	/*
		���ܣ�������Ƶ����ʱ��������ƵOSDͼƬ
		����:
			��
		����ֵ:
			��
	*/

	void set_music_enjoy_osd_show(int flag);

	/*
		���ܣ�������Ƶ����ʱ����ʾ������ͼƬ
		����:
			��
		����ֵ:
			��
	*/
	void set_music_enjoy_osd_by_songinfo();
	/*
	���ܣ���ʾƽ̨���ָ�ͷ��Ϣosd
	��������
	����ֵ����
	*/
	void set_music_enjoy_osd();
	/*
	���ܣ�����ƽ̨���ָ�ͷ��Ϣ�����osd
	��������
	����ֵ����
	*/
	void stop_music_enjoy_osd();
	/*
		���ܣ������Ӻ���Callback����
		����:
			��
		����ֵ:
			��
	*/
	static UINT Cdecl_Callback(LPTOOL_DATA_RECORD lpTdr);

	/*
		���ܣ�����DLNA����
		����:
			��
		����ֵ:
			��
	*/
	void PlayDLNAFunction();

	/*
		���ܣ������������ļ�
		����:
			��
		����ֵ:
			��
	*/
	static UINT recv_master_slave_file(LPVOID param);

	/*
		���ܣ������������ļ�
		����:
			��
		����ֵ:
			��
	*/
	UINT send_master_slave_file(TCHAR *path);
	/*
		���ܣ���ʼ��COM���
		��������
		����ֵ����
	*/
	void InitCom();
	/*
		���ܣ������豸����
		��������
		����ֵ����
	*/
	void ReloadEqIndex(void);
	
	/*
		���ܣ���ʼ������OK
		��������
		����ֵ����
	*/
	void InitKaraoke();

	void show_tv_picture_path(int tvcount);
	/*
		���ܣ����ؽ��յ�����Թ����ͱ���
		������send_data���͵Ĺ�����Ϣ
	*/
	int send_maiba_rule_to_master(char* send_data);
	/*
	���ܣ�����ѡ���������λ�ý���
	������
	    agrs:����λ�õ������������м���ð�ŷֿ�
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	//bool flash_message_call_select_song_switch(const TCHAR *args);

	/*yzg add*/
	/*����flash����*/
	bool flash_message_call_flash_volume(int nPageCode);

	/*****************��ʾ����flash***************************/
	vector<CTransparentWnd *> m_vecTransparentWnd;
	CTransparentWnd *m_pWnd;
	/*��ʾ����Flash*/
	void show_screen_flash_wnd(SCREEN_FLASH_TYPE en_screen_flash_type);

	/*����flash*/
	bool PlayScreenFlash(CTransparentWnd * pWnd, CWnd *pParent, TCHAR *pwFlashPath, CRect rtWnd, CRect rtFlash, UINT wndId = NULL, UINT flashId = NULL);
	/*ֹͣflash*/
	bool destroy_screen_flash_wnd();
	/*��ʱ��*/
	void set_screen_flash_timer(int show_time);
	/******************����������***************************/
	/*�������������÷��͸�flash*/
	bool flash_message_call_inter_screen_config();
	/*�����flash*/
	bool flash_message_call_show_inter_screen(int page_code);
	/*���ͼƬ201*/
	bool flash_message_call_ad_pic();
	/*����Ƶ��301*/
	bool flash_message_call_horizontal_frequency();
	/*����Ƶ��302*/
	bool flash_message_call_vertical_frequency();
	/*����ͼƬ401*/
	bool flash_message_call_singer_pic();
	/*��ĿͼƬ402*/
	bool flash_message_call_program_pic();
	/*��ѡ�б�501*/
	bool flash_message_call_selected_song_list();
	/*�Ƽ��б�502*/
	bool flash_message_call_recommend_song_list();
	/*�չʾ601*/
	bool flash_message_call_activity();
	/*��602*/
	bool flash_message_call_ranking_list();
	/*��ʵʱ��Ϣ603*/
	bool flash_message_call_award_info();
	/*�����Ļ701*/
	bool flash_message_call_ad_caption(TCHAR *caption);
	/*���Ļ702*/
	bool flash_message_call_activity_caption(TCHAR *caption);
	/*��Ŀ��Ϣ703*/
	bool flash_message_call_program_info(TCHAR *caption);
	/*��֯���Ϣ*/
	bool organise_arena_rule_info(TCHAR* command,int rule_falgs);
	/*����ͼƬ*/
	bool search_pic(CString strPath, CString &strData, int &nFileCnt);
	/*����Ƶ*/
	bool show_single_video_inter_screen(int page_code);
	/*˫��Ƶ*/
	bool show_double_video_inter_screen(int page_code);
	/*��������Ƶ*/
	bool show_assist_video_inter_screen(int page_code);
	/*
	���ܣ����¹�������Ϣ�����Ƶ�ס���Ļ��Ϣ����������桢�����Ϸ��������װ�Σ�
	������nMode:ģʽ bLeft:�Ƿ�Ϊ���б�
	*/
	bool show_scroll_info(int nMode, bool bTop = true);
	/*
	���ܣ������б���Ϣ�����ͼƬ������Ƶ�ס�����ͼƬ����ĿͼƬ����ѡ�б�����񵥣�
	������nMode:ģʽ bLeft:�Ƿ�Ϊ���б�
	*/
	bool show_list_info(int nMode, bool bLeft = true);
	/*
	���ܣ���ʾ��Ƶ���ڣ���Ŀ��Ƶ��ת����Ƶ����Ƶ��桢������Ϸ������Ϊ16��9����
	������nMode:ģʽ bLeft:�Ƿ�Ϊ���б�
	*/
	bool show_wnd_info(int page_code, int nMode, bool bMaster = true);
	///////////////////////////////////////////////////*

	/************************************������****************************/
	//��ȡ���ļ�����ȡ������Ϣ
	static UINT read_trend_list(LPVOID param);
	//����json����
	bool parse_trend_list_json(Json::Value &info);
	//��֯����xml
	bool make_trend_list_xml(wstring &strTotalXml);
	//��ʾ����Ϣ
	void flash_message_call_trend_list(int page_code, const TCHAR *args);
	void flash_message_call_trend_list_data(int page_code, bool binit = true);
	////////////////////////////////////////////////////////////////////////////
	/*************************��ս��*******************************************/
	// ��ʼ��ս
	bool start_challenge_star(int nIndex, const TCHAR* pSongIndex);
	// ������������ʼ����ʱ
	bool flash_message_call_challenge_count_down(int nFlag = 0);
	// ��ʼ������ս�ɹ�/ʧ�ܶ��� bResult:true�ɹ�
	bool flash_message_call_start_result(bool bResult);
	// ������������ת����ս����flashҳ��
	bool flash_message_call_challenging();
	// ���͵�ǰ��ս������Ϣ��flash
	bool flash_message_call_current_challenge_song(TCHAR *singer_path, int nIndex);
	// ���ͷ�������
	bool flash_message_call_challenging_score(int score);
	//��������ʾ��ս��
	bool flash_message_call_challenge_star();
	//������ս�󿧹���
	bool flash_message_call_challenge_star_rule();
	//���͸�����Ϣ
	bool flash_message_call_challenge_star_song(enum PAGE_OPERATE page_operate, bool bInit);
	bool make_challenge_star_song_sub_xml(TCHAR* pSubData, enum PAGE_OPERATE page_operate, bool bInit);
	//����ҳ����Ϣ
	bool flash_message_call_challenge_star_page_info(enum PAGE_OPERATE page_operate, bool bInit);
	//////////////////////////////////////////////////////////////////////////////
	/************************����ά*************************************/
	/*�����յĹؿ���Ϣ����ʱ�������Ƶ�����ʱ��������*/
	bool copy_pass_info();
	/*�ܹؿ����ӿ�*/
	bool flash_message_call_across_pass_count();
	/*PC��ҳ��*/
	bool flash_message_call_main_pass_pc(bool bBgMusic = true);
	/*PC��ѡ��ؿ�ҳ��*/
	bool flash_message_call_select_pass_song_pc(enum PAGE_OPERATE page_operate, bool bInit);
	/*��֯3ҳ������Ϣ��xml����*/
	bool make_pass_song_sub_xml(TCHAR* pSubData, enum PAGE_OPERATE page_operate);
	/*��һҳ��Ϣ*/
	bool flash_message_call_pass_song_next_page_pc(int nIndex);
	/*��ʼ�ά��ť*/
	bool flash_message_call_start_pass_pc();
	/*��ʼ����ʱ�ͱ��������Ľӿ�*/
	bool flash_message_call_start_countdown();
	/*���Ӷ���ҳ��*/
	bool flash_message_call_main_pass_tv(int nFlag = 0);
	/*��һҳ��ʾ*/
	bool flash_message_call_pass_next_page_tv();
	/*���Ӷ˵���ʱ*/
	bool flash_message_call_pass_count_down();
	/*tv��ʼ��ս*/
	bool flash_message_call_start_pass_tv();
	/*���Ŵ��ظ���*/
	bool start_pass_tv();
	/*���͸�flash������ ���ƶ� �ȶ���*/
	bool flash_message_call_sound_effect(int nIntact, int nSimilarity, int nStability);
	/*ͬʱ�ﵽ�Ӵ�������ʱ����� ����ֵ0������ 1���ƶ� 2�ȶ���*/
	int get_sound_effect_index(int nSource);
	/*��ս�������*/
	bool flash_message_call_across_pass_result(bool bResult);
	/*���Ӷ��˳��ά���棬flashֹͣ��ʱ��*/
	bool falsh_message_call_exit_across_pass_tv();
	//////////////////////////////////////////////////////////////
	/*//////////////////////������Ϸ/////////////////////////////*/
	/*���ɻ�����Ϸ��ά��ͼƬ*/
	bool generate_active_game_encode();
	/*����json���ݣ���ȡ�����Ϣ*/
	bool parse_active_game_player_info(const char *pInfo);
	/*���Ӷ�flash*/
	bool flash_message_call_active_game_tv(int nFlag = 0);
	/*����*/
	/*�����ϢnFlag:0ȫ������  1���ͳ����� 2���������*/
	bool flash_message_call_player_info(int nFlag = 0);
	/*�������ӵ�����Ϣ  a,b */
	bool flash_message_call_dice_number(int nNumber1, int nNumber2);
	/*��ȡ������ʾ*/
	bool get_dice_result_sound(int nDice, TCHAR *pResult);
	/*����ҡ���ӵ���Ҹ���*/
	bool flash_message_call_player_high_light(TCHAR* pInfo);
	/**/
	bool active_game_flash_call_function(TCHAR *request);
	/**/
	bool active_game_soft_flash_call_function(TCHAR *request);
	//////////////////////////////////////////////////////////////
	////΢�Ż���-��Ļ/////////////////
	/*���ɶ�ά��ͼƬ*/
	bool generate_wechat_barrage_encode();
	/*������Ļ����*/
	void create_wechat_interaction_wnd();
	/*���ٵ�Ļ����*/
	void destroy_wechat_interaction_wnd();
	/*��Ļ��ά��ͼƬ·��*/
	bool flash_message_call_wechat_barrage_pic_path();
	/*��Ļ����/�ر�*/
	bool flash_message_call_wechat_barrage_open(bool bOpen);
	/*��Ļ��ʾģʽ��nMode 0������ 1��������*/
	bool flash_message_call_wechat_barrage_mode(int nMode);
	/*��ʾ��Ļ��Ϣ���߳�*/
	static UINT show_wechat_barrage_info_thread(LPVOID pParam);
	UINT show_wechat_barrage_info();
	/*������Ļ��Ϣ���߳�*/
	static UINT parse_wechat_barrage_info_thread(LPVOID pParam);
	/*��Ļ��ʾ��Ϣ(���ݣ���ɫ���ֺŴ�С���ٶȣ�����)*/
	bool flash_message_call_wechat_barrage_info(BARRAGE_INFO *pInfo);

	/////////////////
	//**************************************************΢�Ż���
	//�����߳�
	static UINT wechat_message_thread(LPVOID pParam);
	/////////////////////////////////////////////////////*/
	/***********΢�Ż���-���ħ�����飩*********************/
	//�������ڼ�flash���ſؼ�
	void create_wechat_gift_wnd();
	//���ٴ��ڼ�flash���ſؼ�
	void destroy_wechat_gift_wnd();
	/*��ʾ���ħ�����飩��Ϣ���߳�*/
	static UINT show_wechat_gift_info_thread(LPVOID pParam);
	UINT show_wechat_gift_info();
	//��ʾ���ħ�����飩bFlag:�Ƿ���Ҫ����΢���û���Ϣ
	bool flash_message_call_wechat_gift_info(WECHAT_MESSAGE *pInfo, bool bFlag = false);

	/*******************************************************/
	/********************************�����ļ���֧��****************************************/
	/*//�����ļ����� - ֻ�е��߳�ʹ��
	int down(const char* url, const char* local);

	//�����ļ����� - ֻ�е��߳�ʹ��
	int down(const TCHAR* url, const TCHAR* local);

	//get http link - ֻ�е��߳�ʹ��
	bool getUrl(char* url);

	//post http link - ֻ�е��߳�ʹ��
	bool postUrl(char* url);
	*/
	//zip�ļ��Ľ�ѹ
	bool unzip(CString csPath, CString csDir, CString &strFileName);
	////////////////////////////////////////////////////////////////////////////

	//****************************************����ʶ��
	//����ʶ����ʼ����Ϣ
	void flash_message_call_listen_know_song(int args);
	//����ʶ�� - ���͵�������flash
	void listen_flash_call_function(const TCHAR *request);
	//����ʶ�� - ���͵���������flash
	void listen_flash_soft_call_function(const TCHAR *request);
	//��ѯ������������������߳�
	//��ѯ�����߳�
	static UINT query_listen_song_info_tmp_thread(LPVOID pParam);
	//��ѯ���׸���
	bool query_listen_song_info_tmp();
	bool copy_listen_song_info();
	//��ʾ����ʶ���Ĵ�
	bool show_listen_question_answer();
	//�������ʶ��������������
	bool listen_get_question_answer(const TCHAR *song_id);

	/*
		���ܣ��õ���ǰ������Ϣ���Ƽ�����
		����:
			issue_year:       ���
			language:         ����
			song_theme:       ��������
			singer_sex:       �����Ա�
			singer_region_new:�������� 
			song_name:        ������
			singer_name:      ��������
		����ֵ��

	*/
	bool liste_get_recommend_song_info(const TCHAR* issue_year,const TCHAR *language,const TCHAR* song_theme,const TCHAR* singer_sex,
		const TCHAR* singer_region_new,const TCHAR *song_name,const TCHAR* singer_name,const TCHAR* song_id);
	//��������ʶ������
	bool create_listen_song();
	//��������ʶ������
	void destroy_listen_song();
	////////////////////////////////////////////////////////////////����ʶ��-end*/
	
	//����ֱ�����б�
	wstring make_video_show_flash_list(const int curr_page);

	//���������
	void CreateAxBrowse(CString csUrl);
	//���������
	void DestroyAxBrowse();
	//����URL
	void SetAxBrowseUrl(CString csUrl);

	/********************************����mv****************************************/
	//���շ�����������͹�������Ƭmv����
	bool picture_mv_data_to_flash(const char *data);
	//��Ƭmv����ʾ type:0 2��flash type:1 ��flash  type:2��flash
	void picture_mv_play_song(song_info* songinfo, int type = 0);
	//��Ƭmv�ص�����
	static UINT lyrics_Callback(PLAYLYRICSSTATE modeObj);
	//��Ƭmv���ڵĴ��� 0:���سɹ� 1:�����Ѵ���
	long create_picture_mv_wnd();
	//��Ƭmv���ڵ�����
	long destroy_picture_mv_wnd();
	//����
	int parse_video_show_data(const TCHAR* local_path);
	/////////////////////////////////////////////////////////////////////////////////////////

	//************************************�ƼӸ���ʾ����
	static UINT cloud_song_down_progress(LPVOID pParam); //��ʾ�Ƹ������ؽ�����
	void send_cloud_song_progress_to_flash(song_info &song_information, int progress);
	//////////////////////////////////////*/

	// -- ��Ҫ����������ȫ���������ܣ�flash����exe����Ҫsocketͨ��
	static UINT RecvFlashDataParseData(LPVOID pParam);
	static void SendFlashDataBySocket(const TCHAR* _pStr);
	static void SendFlashDataBySocket(const char* _pStr);
	//��ʼ��exe���flash
	void InitFlashByExe();
	//ȫ����-��Ƭ����
	void flash_message_call_active_game_scene(const TCHAR* pScene);
	//�������ϲ������ť����״̬
	bool flash_message_call_might_like_button(bool bOpen);
	/*
	���ض��յ����ض˽���/�뿪�ҳ�棬��ʾ/�ڵ����ض˵�����
	nPageCode:��ǰ�ҳ����
	bShow:�Ƿ���ʾ�ڵ�ҳ��true����ʾ��
	*/
	bool ShowOrHideCoverPage(int nPageCode, bool bShow = false);
	/*
	���ڵ�ͼƬ���͸�flash
	bShow:�Ƿ���ʾ�ڵ�ҳ��true����ʾ��
	*/
	bool flash_message_call_slave_cover_image(bool bShow = true);
	/*
	�򱻿ض˷�����ʾ/�����ڵ�ͼƬ����Ϣ
	bShow:�Ƿ���ʾ�ڵ�ҳ��true����ʾ��
	*/
	bool send_master_slave_cover_iamge_data(bool bShow, int nPageCode);

	//*********************�����Ӱ
	static UINT DaoqiMovieCommunicateThread(LPVOID pParam);
	static UINT DaoQiMsgControlFunc(LPVOID pParam);
	UINT DaoqiMovieCommunicate();
	void MsgControlFunction(enMovieMsgContent enMMC = MMCMSG_DEFAULT);
	long SendDaoQiSystemMsg(const LPMOVIE_MSG_CONTROL lpMMCtrl);
	/////////////////////////*/
	//�رյ��Ӷ˻ҳ��
	void CloseActivePageOnTv();

	//����ֱ��-�߳�����ͼƬ
	static UINT uVideoShowDownFileThread(LPVOID pParam);
	void VideoShowDownFile();
private:
	//ԭ��pc�˵ķֱ���
	//bool m_use_fixed_resolution;        //ʹ�ù̶���1280*768�ķֱ���
	int m_first_display_src_width;      //ԭʼ�ķֱ���
	int m_first_display_src_height;     //ԭʼ�ķֱ���

	//screen�ֱ��ʺ�����
	int m_first_display_x;              //��һ���Կ�����ʼx����
	int m_first_display_y;              //��һ���Կ�����ʼy����
	int m_first_display_width;          //��һ���Կ��Ŀ��
	int m_first_display_height;         //��һ���Կ��ĸ߶�

	int m_second_display_number;        //�ڶ����Կ��ı��
	int m_sencond_display_x;            //�ڶ����Կ�����ʼx����
	int m_sencond_display_y;            //�ڶ����Կ�����ʼy����
	int m_sencond_display_width;        //�ڶ����Կ��Ŀ��
	int m_sencond_display_height;       //�ڶ����Կ��ĸ߶�
	bool m_second_display_exist;        //�ڶ����Կ����ڱ�ʾ

	int m_third_display_x;              //�������Կ�����ʼx����
	int m_third_display_y;              //�������Կ�����ʼy����
	int m_third_display_width;          //�������Կ��Ŀ��
	int m_third_display_height;         //�������Կ��ĸ߶�

	int m_four_display_x;               //���Ŀ��Կ�����ʼx����
	int m_four_display_y;               //���Ŀ��Կ�����ʼy����
	int m_four_display_width;           //���Ŀ��Կ��Ŀ��
	int m_four_display_height;          //���Ŀ��Կ��ĸ߶�

	int m_five_display_x;               //������Կ�����ʼx����
	int m_five_display_y;               //������Կ�����ʼy����
	int m_five_display_width;           //������Կ��Ŀ��
	int m_five_display_height;          //������Կ��ĸ߶�

	int m_six_display_x;               //�������Կ�����ʼx����
	int m_six_display_y;               //�������Կ�����ʼy����
	int m_six_display_width;           //�������Կ��Ŀ��
	int m_six_display_height;          //�������Կ��ĸ߶�

	//ͼƬ
	Image  *m_song_tip_image;           //��һ����ʾ��ϢͼƬ
	bool m_show_song_tip_osd;           //��ʾ������ʾ��osd��ʶ
	Image *m_number_image;              //����ͼƬ

	//flash
	PC_STATE m_pc_state;                        //����ն�Ŀǰ������״̬
	bool m_precheckout_state;                   //Ԥ����״̬
	CFlashPlayer m_flash_player;                //flash������
	new_flash_player m_controlbar_flash_player; //������flash������
	BOOL m_controlbar_flash_player_exist;       //��flash����������
	new_flash_player m_test_flash_player;       //���������
	BOOL m_test_flash_player_exist;             //�������������
	game_flash_player m_local_game_flash_player;      //��Ϸ������
	BOOL m_local_game_flash_player_exist;             //��Ϸ�������Ƿ����
	CFlashManage m_flash_manage;                //flash������
	bool m_flash_screen_init_finish;            //flash�����ʼ�����
	bool m_lock_window;                         //������������Ļ
	TCHAR m_image_page_path[256];               //����ҳͼƬ·��
	TCHAR m_video_bg_path[256];                 //������Ƶ����
	TCHAR m_ktv_test_number[64];                //����Ĺ���
	std::wstring m_ktv_test_password;           //���������
	bool m_start_test;                          //��ʼ���Ա�ʾ
	int m_auto_test_number;                     //�Զ����Ա��
	int m_page_show_row_count;                  //������ѯʱ�����Ƶ�����
	bool m_flash_show_logo;                     //ָʾflash��Ҫ��ʾlogo����Ҫȡ��logo
	bool m_use_open_room_function;              //ʹ��������̨��������
	std::wstring m_ink_song_lyric;              //��д�����ĸ��
	bool m_use_smart_pinyin;                    //ʹ������ƴ��
	bool m_page_allow_back;                     //ҳ��������
	bool m_allow_play_dj;                       //�Ƿ�������dj
	std::wstring m_allow_play_dj_time;			//����DJ�����ʱ��
	bool m_show_start_image;                    //��ʾ����ҳ
	TCHAR m_cur_interface_version[256];         //��ǰҳ��汾
	std::wstring m_japanese_enlish_stroke;      //��������е�Ӣ��ʻ�
	SONG_LANGUAGE m_query_panel_language;       //������������
	int m_singer_class_mode;                    //���Ƿ��෽ʽ 0���ɷ��෽ʽ 1���·��෽ʽ
	TCHAR m_select_popup_window_number[32];     //ѡ��ĵ������ڱ��
	bool m_start_lyric_link;                    //��ʼ��ʽ���
	bool m_save_selected_song_to_server;        //������ѡ������������
	std::wstring m_play_movie_password;         //���ŵ�Ӱ����
	bool m_allow_play_movie;                    //�����ŵ�Ӱ
	int	 m_movie_row_count;						//��Ӱ��ҳÿҳ����
	bool m_show_song_total_count;               //��ʾ��������
	bool m_call_service_state;                  //���з���״̬
	int m_click_service_button_number;          //����ķ���ť���
	bool m_pc_allow_cancel_service;             //pc�Ƿ�����ȡ������
	int  m_track_mode;                          //����ģʽ

	//button state
	int m_singer_region_button_number;          //��������ѡ�еİ�ť���
	int m_language_button_number;               //����ѡ�еİ�ť���
	int m_new_theme_button_number;              //������ѡ�еİ�ť���
	int m_class_button_number;                  //����ѡ�еİ�ť���
	int m_new_song_button_number;               //�¸�ѡ�еİ�ť���
	int m_opera_button_number;                  //Ϸ��ѡ�еİ�ť���
	int m_video_button_number;                  //��Ƶѡ�еİ�ť���
	int m_word_count_button_number;             //����ѡ�еİ�ť���
	int m_year_button_number;                   //���ѡ�еİ�ť���
	int m_movie_button_number;                  //��Ӱѡ�еİ�ť���
	int m_song_version_button_number;           //�����汾ѡ�еİ�ť���
	int m_singer_sex_button_number;             //�����Ա�ѡ�еİ�ť���
	int m_button_number_copy[PAGE_MAX_NUMBER][12]; //����ҳ�������ť���

	//old button state
	int m_old_word_count_button_number;             //��һ������ѡ�еİ�ť���

#ifdef DON_GUAN_K_PLUS
	bool m_language_slow_dancer;
#endif // DON_GUAN_K_PLUS
	
	//song show mode
	FLASH_SONG_SHOW_MODE m_song_show_mode;      //������ʾ��ʽ

	//system
	char  m_send_room_name[32];                 //���ڴ洢���͸�ǰ�û��İ������
	char  m_send_room_ip[32];                   //���ֽ�ip��ַ
	TCHAR m_room_ip[32];                        //���ֽ�ip��ַ
	TCHAR m_show_room_name[128];                //��ʾ�İ�����
	
	//player
	player_manager m_player_manager;            //����������
	bool m_replay;                              //�س�
	bool m_cancel_mute;                         //ȡ������
	bool m_is_playing_video_ad;                 //��¼���ڲ��ŵ��ǲ�����Ƶ���
	int m_song_count_after_close_room;          //�ط�֮�������ŵĸ�����
	int m_play_song_count_after_close_room;     //�ط�֮���Ѿ����ŵĸ�����
	PlAY_VIDEO_TYPE pc_play_video_type;         //pc�ϲ��ŵ���Ƶ����
	PlAY_VIDEO_TYPE tv_play_video_type;         //�����ϲ��ŵ���Ƶ����
	bool m_check_video_file_exist;              //ÿ�׸���������ļ��Ƿ����
	bool m_adjust_amplifier_volume;             //���ڹ���������������ڿ�������
	long m_pre_play_pos;                        //��¼ǰһ������λ��
	long m_preview_pre_play_pos;                //Ԥ��������ǰһ������λ�� 
	bool m_full_screen_show;                    //���״̬���Ƿ�ȫ����ʾ
	bool m_pip_show;                            //���л���ʾ�͹رյı�ʾ
	bool m_check_video_exist;                   //ÿ�׸���������ļ��Ƿ����
	bool m_play_song_before_open_room;          //����֮ǰ���Ƿ������Ÿ���
	int m_link_server_number;                   //Ҫ���ӵķ��������
	int m_pre_link_server_number;               //ǰһ�����ӵķ��������
	bool m_use_load_balance;                    //ʹ�ø��ؾ���
	bool m_lock_public_video_volume;            //�������и�������
	int m_replay_mode;                          //0:�����ز�һ��  1������ѭ������
	int m_sigma_card_output_mode;               //�����������ʽ  0:VGA  1:���϶��� 2��YUV  3��RGB
	bool m_screen_show_video;                   //ʹ��������
	int m_play_song_total_time;					//��һ�׸������ŵ�ʱ��

	//TV
	std::wstring m_tv_server_ip[TV_CHANNEL_COUNT]; //���ӷ�����IP
	int m_tv_channel[TV_CHANNEL_COUNT];            //���ӵ�6��Ƶ��
	TCHAR m_tv_live_url[256];                   //�������ڲ��ŵĵ�ַ
	bool m_tv_topbox_mode;                      //����ת�����û�����ģʽ
	int m_tv_play_mode;							//����ģʽ��1.������2.�鲥
	int m_tv_show_count;                        //��������Ƶ������
	std::wstring m_tv_name[8];                  //����Ƶ������
	//song play manager
	video_play_manager m_video_play_manager;    //��Ƶ���Ź���
	
	//database
	DB_Query m_db_query;                        //���ݿ��ѯ��
	query_song_manager m_query_song_manager;    //��ѯ�����ĸ���������
	query_singer_manager m_query_singer_manager;//��ѯ�����ĸ��ǹ�����

	//sql server 2005
	Db_sql m_sql_server_db;
	query_film_manager	m_film_manager;			//SQL Server��Ӱ���ݿ���
	bool m_sunshine_show_db;
	int m_nFilePraiseCnt;					//ÿ�ο������Ӱ��������

	//������
	Db_sql m_sql_server_voice_db;
	bool m_voice_china_db;

	TCHAR m_db_order_item[256];                 //���ݿ��ѯ�����ֶ�
	TCHAR m_song_order_item_copy[PAGE_MAX_NUMBER][256];   //�����������ֶθ���
	TCHAR m_server_ip[6][32];                   //��������IP��ַ
	bool m_use_obscure_query;                   //ģ����ѯ��ʶ true������ false��������
	TCHAR m_max_unicode_char[2];                //unicode������ַ�

	//osd
	osd_play_manager m_osd_play_manager;        //osd�Ĳ��Ź���
	int m_control_osd_show_time;                //����osd����ʾʱ��
	int m_tv_logo_x;                            //������logo��x����
	int m_tv_logo_y;                            //������logo��y����
	bool m_tv_show_ad_logo;                     //��������ʾ���logo��ֹͣ���logo�ı�ʾ
	int  m_tv_show_dog_tip_info;                //��������ʾ���ܹ���ӭ��
	TCHAR m_dog_tip_info[256];                  //������ʾ��Ϣ
	bool m_tv_osd_allow_cut;                    //�����ϵ�osd�Ƿ������е�
	bool m_show_vertical_volumn_bar;            //��ʾ��ֱ������

	//screensaver
	screen_saver_window m_screen_saver_window;  //��������
	bool m_screen_saver_window_exist;           //���������Ƿ����
	bool m_pc_show_screen_saver;                //��ʾ����
	bool m_show_video_screen_saver;             //��ʾ��Ƶ����
	bool m_show_screen_saver_state;             //��ʾ����״̬
	bool m_show_screen_saver_state_activity;	//�μӻʱ������״̬
	CTimer m_start_screen_saver_timer;          //����������ʱ��
	CTimer m_switch_screen_saver_timer;         //�������ʱ��
	bool m_show_ad_screen_saver;                //��ʾ���ǹ������
	int m_start_screen_saver_time;              //����������ʱ��
	bool m_start_video_screen_saver;            //Ŀǰ����������Ƶ����
	bool m_screen_to_flash_timer;				//�Ƿ񵯳�����
	bool m_creen_to_flash_show;					//��¼��ǰ������״̬

	//com
	inherit_com m_inherit_com;                  //������
	inherit_com m_inherit_bak_com;              //���ݵ��пغд�����
	inherit_com m_inherit_three_com;            //�̳еĵ���������

	//message
	char m_send_message[1024];                  //Ҫ���͵���Ϣ
	char m_msg_server_ip[2][64];                //��Ϣ��������IP
	int m_msg_server_count;                     //��Ϣ�������ĸ���

	//�Ӵ���
	CChildWnd m_screen_show_window;            //��ʾ����Ļ��ʾ���ڣ���������
	bool m_screen_show_window_exist;           //ָʾ��Ļ��ʾ�����Ƿ񴴽��ɹ�
	CChildWnd m_sub_screen_show_window;        //����ʾ����Ļ��ʾ����
	CChildWnd m_lobby_live_window;             //����ֱ���Ĵ���
	bool m_lobby_live_window_exist;            //����ֱ�������Ƿ����
	CChildWnd m_preview_window;                //Ԥ������
	bool m_preview_window_exist;               //Ԥ�������Ƿ����
	CChildWnd m_tv_window;					   //����ֱ���Ĵ���
	bool m_tv_window_exist;                    //����ֱ���Ĵ����Ƿ����
	CChildWnd m_soft_decode_window;            //��ⴰ��
	bool m_soft_decode_window_exist;           //��ⴰ�ڴ���
	bool m_use_soft_active_flash;			   //�Ƿ�������ⴰ��flash
	CChildWnd m_second_tv_window;              //�ڶ������Ӵ���
	bool m_second_tv_window_exist;             //�ڶ������Ӵ����Ƿ����
	CChildWnd m_screen_msquare_window;         //mƽ����ͼƬ����
	bool m_screen_msquare_window_exist;        //ָʾͼƬ�����Ƿ񴴽��ɹ�
	CChildWnd m_soft_decode_window_child;            //��ⴰ���Ӵ��ڣ����ڲ�����Ƶ
	bool m_soft_decode_window_child_exist;           //��ⴰ���Ӵ��ڴ���

	int m_msquare_left_top_x;                    //ͼƬ���ڵ������x����
	int m_msquare_left_top_y;                    //ͼƬ���ڵ������y����
	int m_msquare_right_button_x;                //ͼƬ���ڵ������x����
	int m_msquare_right_button_y;                //ͼƬ���ڵ������y����
	int m_msqure_width;
	int m_msquer_height;

	int m_video_left_top_x;                    //��Ƶ���ڵ������x����
	int m_video_left_top_y;                    //��Ƶ���ڵ������y����
	int m_video_right_button_x;                //��Ƶ���ڵ������x����
	int m_video_right_button_y;                //��Ƶ���ڵ������y����

	int m_switch_screen_left_top_x;            //������Ƶ���ڵ������x����
	int m_switch_screen_left_top_y;            //������Ƶ���ڵ������y����
	int m_switch_screen_right_button_x;        //������Ƶ���ڵ������x����
	int m_switch_screen_right_button_y;        //������Ƶ���ڵ������y����

	int m_handwriting_window_left_x;           //��д���ڵ������x����
	int m_handwriting_window_top_y;            //��д���ڵ������y����
	int m_handwriting_window_right_x;          //��д���������x����
	int m_handwriting_window_bottom_y;         //��д���������y����

	int m_vice_screen_left_top_x;                    //��Ƶ���ڵ������x����
	int m_vice_screen_left_top_y;                    //��Ƶ���ڵ������y����
	int m_vice_screen_right_button_x;                //��Ƶ���ڵ������x����
	int m_vice_screen_right_button_y;                //��Ƶ���ڵ������y����

	//ǽ���
	CChildWnd m_wall_panel_window;             //ǽ��崰��
	new_flash_player m_wall_panel_flash_player;//ǽ���flash������
	BOOL m_wall_panel_flash_player_exist;      //ǽ���flash��������ʾ
	bool m_wall_panel_window_exist;            //ǽ��崰���Ƿ����
	inherit_com m_wall_panel_screen_com1;      //ǽ��崥�����Ĵ�����
	inherit_com m_wall_panel_screen_com2;      //ǽ��崥�����Ĵ�����
	inherit_com m_wall_panel_screen_com3;      //ǽ��崥�����Ĵ�����
	inherit_com m_wall_panel_screen_com4;      //ǽ��崥�����Ĵ�����
	int m_wall_panel_screen_left_x;            //ǽ������Ͻǵ�X����
	int m_wall_panel_screen_top_y;             //ǽ������Ͻǵ�Y����
	int m_wall_panel_screen_right_x;           //ǽ������½ǵ�X����
	int m_wall_panel_screen_bottom_y;          //ǽ������½ǵ�Y����
	int m_wall_panel_image_width;              //ǽ���ͼƬ�Ŀ��
	int m_wall_panel_image_height;             //ǽ���ͼƬ�ĸ߶�
	bool m_wall_panel_image_show;              //ǽ���ͼƬ��ʾ״̬
	int m_show_wall_panel_image_time;          //����ǽ���ͼƬ��ʱ�䣬��λ����
	WALL_PANEL_SHOW_MODE m_wall_panel_show_mode;//ǽ�����ʾģʽ
	
	//Ԥ������
	bool m_preview_allow_play_song_db;         //Ԥ�������Ÿ�����
	song_info m_preview_song_info;             //ѡ�е�Ԥ������
	int m_preview_left_top_x;                  //Ԥ����Ƶ���ڵ������x����
	int m_preview_left_top_y;                  //Ԥ����Ƶ���ڵ������y����
	int m_preview_right_bottom_x;              //Ԥ����Ƶ���ڵ������x����
	int m_preview_right_bottom_y;              //Ԥ����Ƶ���ڵ������y����

	//DLNAԤ��
	int m_dlna_preview_left_top_x;                  //Ԥ����Ƶ���ڵ������x����
	int m_dlna_preview_left_top_y;                  //Ԥ����Ƶ���ڵ������y����
	int m_dlna_preview_right_bottom_x;              //Ԥ����Ƶ���ڵ������x����
	int m_dlna_preview_right_bottom_y;              //Ԥ����Ƶ���ڵ������y����

	//slave_screen
	CChildWnd m_slave_parent_window;           //���ش��ڵĸ�����
	bool m_slave_parent_window_exist;          //���ش��ڵĸ��������
	CChildWnd m_slave_video_window;            //������Ƶ����
	bool m_slave_video_window_exist;           //������Ƶ�����Ƿ����
	new_flash_player m_slave_window_flash_player;//������Ƶ�����ϵĿ��ư�ť������
	bool m_slave_window_flash_player_exist;    // ������Ƶ�����ϵĿ��ư�ť�������Ƿ����
	inherit_com m_bar_touch_screen_com;        //��̨�������Ĵ�����
	int m_slave_screen_left_top_x;             //���Ͻǵ�X����
	int m_slave_screen_left_top_y;             //���Ͻǵ�Y����
	int m_slave_screen_right_bottom_x;         //���½ǵ�X����
	int m_slave_screen_right_bottom_y;         //���½ǵ�Y����

	//��������ʾ
	CChildWnd m_vice_screen_window;				//�������ڵĸ�����
	int m_vice_screen_window_exist;			//�������ڵĸ������Ƿ����
	new_flash_player m_vice_screen_flash_player;//ǽ���flash������
	BOOL m_vice_screen_flash_player_exist;      //ǽ���flash��������ʾ
	BOOL m_vice_screen_flash_show;				//�����Ƿ���ʾ
	TCHAR m_szvice_screen_msg[2048];			//����flash��Ϣ

	//test machine
	bool m_use_test_function;                  //�Ƿ����ò�����ܣ�true������ false��������

	//light
	bool m_song_light_control;                 //�Ƿ�����ÿ�׸����ĵƿ���
	TCHAR m_select_ligth_buttom[256];          //ѡ�еĵƹⰴť
	bool m_recv_no_send_light_code;            //���ܵĲ����͵ƹ���
	bool m_memory_light_state;                 //����ƹ�״̬
	bool m_song_light_lock;                    //�Ƿ������ƿ���
	int m_song_light_lock_value;			   //����ʱ�ĵƿ���ֵ

	//audio effect
	bool m_song_audio_effect;                  //�Ƿ�����ÿ�׸�������Ч��
	int m_cur_audio_effect_value;              //��ǰ��Чֵ

	bool m_song_audio_effect_lock;              //�Ƿ�������Ч��
	int m_lock_audio_effect_value;               //�����ǵ���Ч��
	int m_lock_function_code_value;                  //�����ǵ���Ч��ֵ

	//music sound
	//bool m_song_music_sound;                  //�Ƿ�����ÿ�׸�������Ч��
	int m_cur_music_sound_value;              //��ǰ��Чֵ

	//����
	bool m_control_change_tone;                //���ÿؼ����
	int m_send_volumn_amplifier_code_count;    //���͵���������Ĵ���

	//environment_audio
	int m_select_environment_button_number;    //ѡ�еĻ�����Ч��ť���

	//ԭ�泪������� 
	int m_select_song_accompany_original;		//ԭ�泪������ť����

	//recorder
	CAudio m_tape_audio;                       //¼����
	bool m_is_recording;                       //¼��״̬
	bool m_need_record_flag;                   //Ĭ���Ƿ���¼����ʾ true:���� false:������
	int m_record_type;                       //��ǰ��¼������ 0,���Զ�¼��  1��ȫ�Զ�¼��
	int m_open_record_type;						   //ȫ�Զ�¼��  0,ȫ�Զ�¼���ر� 1.ȫ�Զ�¼������
	int m_enable_record;						//�Ƿ�����¼��
	int m_are_memorices;						//����¼�� 0:������ 1:����
	bool m_record_btn_state;					//¼����ť״̬ true:���� false:�ر�

	song_info m_song_recorder;                 //¼��������Ϣ
	unsigned int m_record_audio_number;        //¼�������ı��
	void* m_recorder_handle;                   //¼��������
	TCHAR m_noise_path[256];                   //�����ļ�·��
	std::wstring m_recorder_dir;               //¼���ļ�����·��
	std::wstring m_recorder_web_dir;           //¼���ļ����������·��
	std::deque<RECORD_SONG_INFO> m_wav_info_deque;  //¼���ļ���Ϣ
	TCHAR m_music_wave_path[256];                   //�洢�����ļ�·��
	TCHAR m_voice_wave_path[256];                   //�����ļ��洢·��
	//TCHAR m_tape_mp3_name[256];                     //¼��mp3�ļ���
	int m_tape_mode;                                //¼��ģʽ  0����Ч����Ͱ���   1�������ϰ���
	CHttp_old m_http_service;                           //http����
	song_info m_share_audio_info;                   //�������Ƶ��Ϣ 

	//������������
	std::deque<SONG_SHARE_SUCCESS>m_song_share_success;		//�����������
	int m_connect_rule_server_count;             //�������������Ĵ���������5�β��ɹ����Ͳ�������

	//lock
	llock m_send_master_slave_lock;            //�������������ݵ���
	llock m_cloud_song_lock;				   //�ƼӸ����ظ����Ƿ�ɹ�����
	llock m_barrage_lock;
	llock m_call_fun_lock;

	//timer ��ʱ����ʾ
	UINT_PTR show_logo_timer_identifier;             //������ʾlogo�Ķ�ʱ����ʾ
	UINT_PTR show_control_osd_timer_identifier;      //��ʾ����osd logo�Ķ�ʱ����ʾ
	UINT_PTR show_bmp_picture_timer_identifier;      //��ʾbmpͼƬ�Ķ�ʱ����ʾ
	UINT_PTR show_score_timer_identifier;            //��ʾ������ʱ����ʾ
	UINT_PTR show_flash_text_timer_identifier;       //��flash����ʾ������Ļ�Ķ�ʱ����ʾ
	UINT_PTR show_tv_text_timer_identifier;          //�ڵ�������ʾ������Ļ�Ķ�ʱ����ʾ
	UINT_PTR show_flash_background_timer_identifier; //����flash�����Ķ�ʱ����ʾ
	UINT_PTR show_flash_logo_timer_identifier;       //��flash����ʾlogo�Ķ�ʱ����ʾ
	UINT_PTR show_tv_logo_timer_identifier;          //�ڵ�������ʾlogo�Ķ�ʱ����ʾ
	UINT_PTR show_screen_saver_timer_identifier;     //��ʾ�����Ķ�ʱ��
	UINT_PTR common_timer_identifier;                //���ö�ʱ��
	UINT_PTR check_file_timer_identifier;            //����ļ��Ƿ���ڵĶ�ʱ��
	UINT_PTR check_mysql_timer_identifier;           //���mysql�Ķ�ʱ�����
	UINT_PTR auto_test_timer_identifier;             //�Զ����Զ�ʱ��
	UINT_PTR hide_check_window_timer_identifier;     //���ظ�����ѡ��Ķ�ʱ�����
	UINT_PTR show_popup_window_timer_identifier;     //��ʾ�������ڵĶ�ʱ�����
	UINT_PTR show_wall_panel_image_timer_identifier; //��ʾǽ���ͼƬ�Ķ�ʱ�����
	UINT_PTR check_pk_content_timer_identifier;                       //���pk�Ƿ�����
	UINT_PTR show_pk_accept_window_time_identifier;    //�Ƿ�����pk����Ի���
	UINT_PTR record_noise_timer_identifier;          //¼��������ʱ��
	UINT_PTR request_head_picture_timer_identifier;  //����ͼƬ��ʱ��
	UINT_PTR show_screen_to_flash_timer_identifier; 
	UINT_PTR show_music_enjoy_lyric_timer_identifier;
	UINT_PTR show_screen_timer_identifier;			 //��ʾ��Ļflash����
	UINT_PTR maiba_rule_timer_identifier;
	UINT_PTR maiba_song_list_timer_identifier;
	UINT_PTR m_close_room_timer_identifier;			//�ֶ��������Զ��ط��ļ�ʱ��
	UINT_PTR m_destroy_gift_wnd_timer_identifier;

	int m_nCloseRoomTimeSpace;//�ط�ʱ����������Ϊ��λ��

	//scroll text
	TCHAR m_dog_welcome[1024];                        //���Ļ�ӭ��
	TCHAR m_client_welcome[1024];                     //�ͻ��Ļ�ӭ��
	TCHAR m_msg_welcome[1024];                        //��Ϣ�Ļ�ӭ��
	int m_msg_welcome_scroll_count;                   //��Ϣ��ӭ�ʵĹ�������
	FLASH_SCROLL_WELCOME_TYPE m_welcome_text_type;    //��ӭ�ʵ�����

	//master_slave_control
	int m_master_slave_control_flag;                 //0:������ 1�����ػ� 2�����ػ�
	char m_master_control_ip[64];                    //���ػ�IP��ַ
	char m_slave_control_ip[SLAVE_COMPUTER_MAX_COUNT][64]; //���ػ���IP��ַ

	//os
	bool m_hide_taskbar;                             //����������
	TCHAR m_work_path[256];                          //����·��

	//thread
	bool m_thread_run;                               //����߳��Ƿ�������
	CWinThread *m_thread_handle;                     //�߳̾��
	HANDLE m_assistant_thread_event_handle;          //�����߳̽������¼����
	HANDLE m_server_thread_event_handle;             //���ܿ��ط����߳��¼����
	HANDLE m_upd_msg_thread_event_handle;            //����udp��������Ϣ���߳̾��
	HANDLE m_tcp_msg_thread_event_handle;            //����tcp��������Ϣ���߳̾��
	HANDLE m_master_slave_event_handle;              //�������߳̾��
	HANDLE m_box_thread_event_handle;                //�����¼�
	
	//dog
	enum DOG_TYPE m_dog_type;                        //ʹ�õļ��ܹ�������
	bool m_find_dog_success;                         //�����ܹ��ɹ�

	//drinks
	bool m_open_drinks;                              //�򿪾�ˮ����
	bool m_show_drinks_state;                        //��ˮ�������״̬ 
	DWORD m_drinks_process_id;                       //��ˮ���̵�id
	bool m_ktv_software_min;                         //��ˮ����֮������Ƿ���С��  true����С�� false������С��
	bool m_use_plug_in_drinks;                       //������Ƕ��ˮ
	new_flash_player m_drinks_flash_player;          //��ˮ���������
	bool m_drinks_flash_player_exist;                //��ˮ�������Ƿ����
	DWORD m_consume_process_id;                      //���ѽ��̵�id
	//��������
	HWND m_drinks_window_handle;                    //��ˮ���ڵľ��

	//server
	std::wstring m_server_path;                      //��������·��
	TCHAR m_save_song_file_path[256];                //�������ID�ļ�·��
	char m_back_server_ip[64];                       //��̨������IP�������ط�������IP
	char m_service_server_ip[64];                    //��̨����������ڵķ�����IP
	std::wstring m_music_enjoy_path;				 //�������ͷ�����·��

	//time
	CTimer m_cut_song_timer;                         //�и�����ʱ������ֹƵ������
	CTimer m_avoid_cut_timer;                        //ȫ�ֵķ�ֹƵ���л��Ķ�ʱ��
	CTimer m_play_AD_timer;                          //���Ź��Ķ�ʱ��
	CTimer m_wall_panel_timer;                       //ǽ���ͼƬ���صĶ�ʱ��
	CTimer m_preview_control_timer;                  //Ԥ�����ƿ�����˶�ʱ��
	CTimer m_load_balance_timer;                     //���ؾ��ⶨʱ��
	CTimer m_recv_ps2_timer;                         //����ps2��Ϣ�Ķ�ʱ��
	CTimer m_seek_video_timer;                       //������Ƶλ�ö�ʱ��
	CTimer m_interative_game_timer;                  //������Ϸ�Ķ�ʱ��
	CTimer video_switch_timer;                       //���д�����Ƶ�л���ʱ��

	CTimer m_span_total_timer;						 //ͳ�Ƽ��ʱ�䶨ʱ��
	CTimer m_music_enjoy_lyric_timer;				// ƽ̨���ָ����ʾ��ʱ��
	//handwriting
	handwriting m_handwriting_window;                //��д����
	bool m_handwriting_window_exist;                 //��д�����Ƿ����
	bool m_show_handwriting_window;                  //��ʾ��д����
	CString m_recognition_result[INK_RECOGNIZE_ALTERNATE_NUMS];  //��дʶ�����
	TCHAR m_handwriting_association_word[HANDWRITING_ASSOCIATION_WORD_COUNT][4]; //��д�������
	int m_association_word_count;                   //��д���������
	int m_cur_association_word_page;                //��������ʾ��ҳ��
	int m_ink_language_button_number;               //����ʶ�����д���԰�ť���
	bool m_handwriting_window_show_hide;            //��ʾ��д���ڣ����������Ƿ�����

	//bomb
	bomb m_shine_bomb;                              //ը����
	TCHAR m_make_bomb_code1[32];                    //���ɵĵ�һ��ը����֤��
	TCHAR m_make_bomb_code2[32];                    //���ɵĵڶ���ը����֤��
	bool m_first_code_success;                      //��һ����Կ�ɹ�
	bool m_stop_dog_bomb;                           //ͣ��ը��
	bool m_first_stop_dog_code_success;             //��һ��ͣ������ɹ�
	TCHAR m_dog_time_active_code[128];              //���ļ���ʱ����

	//member
	bool m_member_already_login;                    //��Ա�Ƿ��Ѿ���¼
	TCHAR m_member_name[128];                        //��Ա������
	TCHAR m_member_password[32];                    //��Ա������
	TCHAR m_member_old_password[32];                //��Ա������
	TCHAR m_member_ok_password[32];                 //��Ա��ȷ������
	TCHAR m_memeber_phone_number[32];               //��Ա���ֻ���
	TCHAR m_phone_check_code[256];                 //�ֻ���֤��
	int m_member_song_count;                        //��Ա������
	int m_member_input_type;                        //Ҫ������������� ���뻹���û���
	int m_member_manage_state;                      //��Ա����״̬  1����¼  

	int m_login_memebere_count;                     //��¼��Ա�ĸ���
	int m_activate_vip_button;                     //��ǰ����Ļ�Ա
	int m_pre_activate_vip_button;                 //��һ�μ����Ա
	memeber_song_manager m_memeber_manage[MEMBER_LOGIN_COUNT];          //��Ա���� 
	int m_member_sign_out_number;                  //��Ա�˳���ʾ
		
	//AD
	int m_play_AD_time_elapse;                      //���Ź���ʱ����
	AD_manager m_pc_AD_manager;                     //PC�������������
	AD_manager m_game_AD_manager;                   //��Ϸ�����Ϲ�������
	AD_manager m_wall_panel_AD_manager;             //ǽ����Ϲ�������

	//ѡ����ʾ
	bool m_allow_repeat_select_song;                //�����ظ�ѡ�� 
	song_info m_select_song_info;                   //ѡ��ĸ�����Ϣ
	bool m_select_song_priority;                    //ѡ��ĸ����Ƿ�����
	int m_select_song_number;                       //ѡ��ĸ������
	bool m_check_window_state;                      //��ѡ����״̬  true����ʾ false������


	bool m_user_select_song;                        //��ʶ�û��Ѿ�ѡ�������
	std::wstring m_default_song_name_color;         //Ĭ�ϸ������ֵ���ɫ
	std::wstring m_select_song_name_color;          //ѡ�и������ֵ���ɫ
	std::wstring m_playing_song_name_color;         //�����Ÿ������ֵ���ɫ

	//doorplate machine
	CDoorplateWnd m_doorplate_window;               //���ƻ�����
	bool m_doorplate_window_exist;                  //���ƻ������Ƿ����
	new_flash_player m_doorplate_flash_player;      //���ƻ�flash������
	bool m_doorplate_init_success;                  //���ƻ���ʼ���ɹ�
	inherit_com m_doorplate_com;                    //���ƻ�����
	int m_doorplate_left_top_x;                     //���Ͻǵ�X����
	int m_doorplate_left_top_y;                     //���Ͻǵ�Y����
	int m_doorplate_right_bottom_x;                 //���½ǵ�X����
	int m_doorplate_right_bottom_y;                 //���½ǵ�Y����
	bool m_doorplate_show_scroll_text;              //���ƻ���ʾ��������

	//device or piece of media
	bool m_have_device_insert;                     //���豸����
	TCHAR m_logical_disk_drive;                    //������߼��̷�
	U_disk_song m_play_U_disk_song;                //����U�̸���

	//picture show
	show_service_picture m_show_service_picture;  //��ʾ����ͼƬ����

	//game
	game_manager m_game_manager;                  //��Ϸ������

	//opinion survey
	TCHAR m_surver_question[SURVER_QUESTION_COUNT][256];   //���������
	int m_satisfaction_degree[SURVER_QUESTION_COUNT];      //�����
	std::wstring m_others_opinion;                         //��������
	std::wstring m_contact_phone;                          //��ϵ�绰
	bool m_input_box_show_help[2];                         //�������ʾ����״̬

	//���Ƹ���
	std::wstring m_custom_song[CUSTOM_SONG_COUNT]; //���Ƹ�������
	std::wstring m_custom_phone;                     //���Ƹ�����ϵ�˵绰
	int m_custom_input_fouce;                        //�ж����Ǹ����ڼ���״̬

	//code
	std::wstring m_input_code;                    //�ͻ����������
	CTimer m_password_timer;                      //���붨ʱ��
	int m_click_count;                            //����Ĵ���

	//painting
	int m_painting_area_left_x;                   //��ͼ���������
	int m_painting_area_top_y;                    
	int m_painting_area_right_x;
	int m_painting_area_bottom_y;

	//save recording audio
	bool m_is_saving_audio;                      //���ڱ���¼����Ƶ��U��
	int m_select_save_song_number;               //Ҫ����ĸ������

	//system info
	ADAPTER_INFO m_adapter_info;                 //��������Ϣ
	TCHAR m_local_computer_name[256];            //���ؼ��������
	int m_system_info_input_type;                //Ҫ�����ϵͳ��Ϣ����  0���������  1��IP��ַ

	//������Ϸ
	bool m_use_Interactive_game;                 //�Ƿ����û�����Ϸ
	CChildWnd m_game_window;                     //��Ϸ����
	new_flash_player m_game_flash_player;        //��Ϸ������
	bool m_game_flash_player_exist;              //��Ϸ�����������Ƿ����
	int m_show_game_window_number;               //��ʾ��Ϸ�Ĵ��ڱ�� 0����������  1����ⴰ��   2��ǽ��崰��
	bool m_game_full_screen_show;                //��Ϸ�������ȫ����ʾ
	TCHAR m_interactive_game_page[256];          //������Ϸ��ҳ����
	int  m_interactive_game_idless_time;         //������Ϸ����Ŀ���ʱ��

	//�����Ļ
	CChildWnd m_AD_window;                       //��洰��
	new_flash_player m_AD_flash_player;          //��沥����
	bool m_AD_flash_player_exist;                //��沥���������Ƿ����

	//msg
	bool m_use_new_msg_system;                   //�����µ���Ϣϵͳ

	//�����ļ�
	TCHAR m_room_file_path[256];                 //�����ļ�·��
	int m_room_file_type;                        //�����ļ�����

	//��������
	SCREEN_TYPE m_interface_type;                //�������� ��� ����
	

	//audio effect adjust
	CAudioEffect  m_audio_effect_window;         //��Ч����
	BOOL m_audio_effect_window_exist;            //��Ч�����Ƿ񴴽��ɹ�
	DWORD m_audio_effect_progress_id;            //��Ч������ID

	//mysql
	CMySQL_DB  m_mysql_db;                      //mysql���ݿ���
	char m_mysql_server_path[256];              //mysql������·��
	bool m_mysql_open_success;                  //mysql���ݿ�򿪳ɹ���ʾ

	//sort
	TCHAR m_show_sort_mode[256];                //��ʾ������ʽ��ʵ�ʷ�ʽ�����෴
	wstring m_show_sort_init_mode;

	//ipad
	TCHAR m_ipad_login_code[32];                //ipad�ĵ�¼��֤��

	//����
	bool m_enter_guide_song;                    //���뵼��

	//�Ƿ���������OSD  
	bool m_show_guide_osd;

	//weibo
	int m_weibo_display_number;                 //΢��ʹ�õ��Կ����
	int m_weibo_show_mode;                      //΢����ʾ��ʽ
	int m_weibo_image_width;                    //΢��ͼƬ���
	DWORD m_weibo_process_id;                   //΢������ID
	
	int m_weibo_version_number;                 //΢���İ汾��
	int m_weibo_image_top_height;               //��ʾ������Ļ����ĸ߶�


	//PK
	bool m_open_pk;                            //�Ƿ���pk����
	int m_pk_textbox_focus;                    //0,�û�����; 1,�����뽹��
	bool m_pk_login_member;                    //pk��Ա�Ƿ��¼
	bool m_brecvData_thread;                   //���������߳�
	TCHAR m_recv_pk_data[102400];              //���յ�����   
	TCHAR m_pk_name[128];                      //��Ա������
	TCHAR m_pk_password[32];                   //��Ա������
	int m_pk_menber_sex;                       //1���� 2��Ů 
	int m_pk_member_total;                     //ͳ�ƹ��ж��ٸ���Ա
	int m_pk_page_num;                         //��¼��ǰ�ǵڶ���ҳ
	TCHAR m_pk_invitationIP[256];              //���������ip��ַ
	int  m_pk_invitationPort;                   //��������Ĵ����˿�
	TCHAR m_pk_acceptIP[256];                  //����ip
	int   m_pk_acceptPort;                     //���մ����˿�
	bool m_pk_receive_video;                  //�Ƿ���նԷ���Ƶ
	int m_pk_member_witch_one;                 //��¼����һ����Ա������
	bool m_b_pk_connect;						 //�Ƿ������� 
	TCHAR m_pk_local_video_ip[256];                  //���ӱ������ӵ�ip,�����ļ�����
	int m_pk_local_video_port;                //���Ҷ˿ڴ����Ķ˿�,�����ļ�����
	bool m_b_pk_invitation;                 //�ж��Ƿ������뷽
	int m_n_Syn_count;                     //����
	TCHAR m_pk_other_boxIP[256];      //�Է�����ip
 
	PK_MEMBER_DATA m_pk_information;	//�Լ���pk��Ϣ
	PK_MEMBER_DATA  m_send_member_data[MAX_MENBER_NUM];  //���շ�������������pk��Ա����
	bool m_pk_info_show_pc;         //�Ƿ񵽵�������ʾ��Ƶ����PK
	TCHAR m_pk_info_tip_msg[256];   //PK�ڵ�������ʾ��������Ϣ

	bool m_pk_show_video;           //�Ƿ���ʾ�Լ�����Ƶ��
	int m_audio_volume;             //�Գ�������

	CRect m_rectPosition0;         //���öԳ���Ƶ�Է�λ��
	CRect m_rectPosition1;         //���öԳ���Ƶ�Լ�λ��
	int   m_pk_hardware_mode;      //PKӲ������ģʽ

	TCHAR m_encode_picture_path[256];   //��ά��ͼƬ·��
	bool  m_ipad_ecode_again;                   //�Ƿ��������ɶ�ά��

	//modify:2012-9-4 Yangzhenglun �����Ƿ������ƶ����
	bool m_use_mobile_vod;                       //�Ƿ������ƶ����
	int m_show_tv_mobile_tip;                    //��������ʾ�ƶ�����ʾ��Ϣ   0��ʲô������ʾ��1.��ʾipad�����ʾ��2.��ʾ΢�ŵ����ʾ  3.������ʾ����ʾ

	CSearchLyric m_lyricSrarch;         //��ʼ�����

	//os
	CXWinVersion m_window_version;              //window�汾

	//mark
	SCORE_SYSTEM m_use_score_system;            //ʹ�õĴ��ϵͳ
	//bool m_start_init_success;                  //����Ѷ�������Ƿ�ɹ�
	//��������
	int m_score_intact;                         //�����������ܺ�
	int m_score_similarity;                     //���ƶ�
	int m_score_stability;                      //�ȶ���
	int m_score_decibel;                        //�����ֱ���
	int m_total_calories;                       //���ĵĿ�·��
	int m_lyric_total_sentences;                //��ʵ��ܾ���
	int m_shine_total_score;                    //�ܵĵ÷�
	new_flash_player m_soft_score_flash_player;      //��ʾ���ֽ����flash������
	bool m_soft_load_score_flash_success;            //���ط���flash�ɹ�
	new_flash_player m_score_flash_player;
	bool m_load_score_flash_success;
	bool m_bScoreFlashFinish;					//����flash��ʼ����ɱ�׼
	TCHAR m_score_song_info[256];               //���ָ���
	TCHAR m_next_song_info[256];                //��һ�׸���
	bool m_is_scoring;                          //�������ֱ�ʶ
	bool m_bScoring;							//����������
	
	//����
	TCHAR m_thread_para[256];                   //�̲߳���

	//�����Ƽ�
	int m_recommend_song_count;                   //ʵ���Ƽ��ĸ�����Ŀ

	TCHAR m_recommedn_song_id[256];  //�Ƽ�����id

	//���PK 
	std::wstring  m_place_notice_info; //������Ĺ���.
	bool m_exist_arena_song;    //�Ƿ������̨����
	song_info m_arena_song_info;      //��̨������Ϣ

	  
	int m_maiba_pk_type;     //pk�����ͣ�1.����pk  2.��̨pk
	int m_maiba_pk_count;    //��������
	MAIBA_SONG_INFO_STU m_maiba_song_info[MAX_MAIBA_PK_COUNT];   //���������Ϣ
	MAIBA_RULE_INFO  m_maiba_rule_arena_info[MAIBA_RULE_COUNT];  //���pk������Ϣ
	int m_maiba_number_button;            //��԰�ť�ĸ����ͼ�¼��ǰѡ�������
	int m_maiba_request_page;            //�������ҳ��
	MAIBA_TYPE m_maiba_current_request_type;  //��ǰ������Ե�����
	char m_set_maiba_rule_ip[64];                       //��̨������IP�������ط�������IP
	std::wstring m_maiba_rule_info_list[MAIBA_RULE_COUNT];   //�洢�������pk����Ϣ 
	bool m_request_arena_one_song;          //�ж��ǵ����ս��Ե㲥�����Ƿ���true:�ǲ��Ÿ�����false:�Ƿ������
	TCHAR m_request_arena_song_id[256];     //�ж��ǵ����ս��Ե㲥�����Ƿ���ĸ���id

 
	bool m_use_area_pk;                     //�ж��Ƿ���������ս���
	bool m_use_find_maiba_pk;              //�ж��Ƿ������˷�����Թ���
	MAIBA_HEIGHT_RANKING m_maiba_song_list[MAIBA_HEIGHT_RANKING_LIST];  //��Ը߷ְ�����
	int m_maiba_song_list_count;    //�߷ְ�������ܸ��� 
	int m_maiba_total_page_number;  //�ܹ���ҳ��
	int m_maiba_current_page_number;   //��Ե�ǰҳ��
	
	REQUEST_SONG_TYPE m_request_song_type;   //��������������
	int m_web_song_total_count;    //�ܵ�����
	int m_web_total_page_nmuber;   //�ܵ�ҳ��
	int m_web_current_page_number;		//��ǰ��ҳ��

	bool m_set_free_pk;              //�Ƿ�����������pK
	bool m_set_dekaron_pk;           //�Ƿ���������ս���
	bool m_set_ranking_plite;		 //�Ƿ��������ϰ�����
	bool m_set_challenge_star;		 //�Ƿ���������ս��
	bool m_set_across_pass;			 //�Ƿ������˰���ά

	SOCKET m_load_song_db_socket;     //����socket
	sockaddr_in m_load_song_db_addr;

	TCHAR m_wechat_song_encode[256];  //΢�ŵ��ĵ�¼��
	TCHAR m_wechat_song_path[256];   //΢�ŵ���ά��·��
	int m_wechat_button_number;        //΢�ŵ�����

	map<wstring,int>m_select_page_Map; //�洢���ݵ�map<ѡ�����id,ѡ��ʱ��ҳ��>
	
	bool m_server_pop_up_window;    //��������Ƿ񵯳��Ի���
	std::wstring m_default_song_row_color; //��������ɫ

	bool m_recorder_exist_video_path;   //�жϵ�ǰ�����Ƿ�������¼��

	SOCKET m_box_send_socket;
	TCHAR m_request_data[1024];


	//�������ƿ���
	LINGHT_CONTROL m_linght_control;

	//��������
	ST_MUSIC_ENJOY m_music_enjoy[100];
	int m_music_enjoy_count;
	TCHAR m_szMusicEnjoyBkVideo[4][MAX_PATH];	//�������ͱ�����Ƶ·��

	//�����
	CHtmlCtrl m_html_ctrl;
	BOOL m_html_ctrl_exist;
	bool m_show_html_ctrl;

	//��¼ɾ��¼���ļ�������
	std::wstring m_delete_record_idx;

	std::wstring m_maiba_ranking_info;                 //��̨pk�ĸ߷ְ�

	std::wstring m_video_index;
	std::wstring m_pre_theme_name;

	VIDEO_DATING m_video_dating_info;						 //��ǰ��Ƶ���ѵ���Ϣ
	VIDEO_DATING m_server_video_dating_data[MAX_MENBER_NUM]; //��Ƶ���ѵķ��������б�
	TCHAR m_recv_video_dating_data[102400];					 //������Ƶ���ѵ�����  
	int m_video_dating_total;								 //ͳ�ƹ��ж��ٸ���Ƶ����
	int m_vd_page_num;										 //��¼��ǰ�ǵڶ���ҳ
	int m_vd_send_idx;										 //�������������
	VIDEO_DATING m_video_dating_accept_info;				 //���յ���Ƶ�������Ϣ
	CRect m_rectPosition_myself;							 //��Ƶ�����Լ���λ��
	CRect m_rectPosition_otherside;							 //��Ƶ���ѶԷ���λ��
	bool m_video_dating_show;								 //�Ƿ�ͨ��Ƶ���ѹ���

	bool m_show_score_in_screen;							 //�Ƿ��ڵ�������ʾ����

	//���ػ����и������ʱ�����и�-------By_v.cai_2015/02/05 15:07
	bool m_idless_song_switching;

	bool m_allow_show_cloud_song;

	//caizw add for ��ʾƽ���߱��
	int m_default_show_score_line;
	vector<wstring> m_down_song_vec;	 //�洢���ݵ����ظ������ݵ�vec

	SHOW_CUBE_SONG_VEC m_show_cube_song_vec; //������ɸ�������
	SHOW_CUBE_SINGER_VEC m_show_cube_singer_vec; //������ɸ�������

	//�����Ӻ�DLNA����
	PluginsEx m_PluginsEx;
	TCHAR m_GxShine_dll[2][MAX_PATH];
	static Cflashktv10Wnd *pThis; 
	bool m_is_open_dlna; //�Ƿ���DLNA����
	int m_dlna_already_play_time;
	LPTDLNA_URL_DATA m_lpDlna_url_data;

	int m_default_auto_light; //�Զ��ƹ�Ĭ��ֵ

	int m_film_video_button_state;//���ͳ�ʼʱ��ť����

	// ����������ԭ�鳪�л��Ŀ��Ʊ�����mp3��ʽ��
	IPropSet		*m_IRTCOMAPI;
	IPropSet20065	*m_IRTCOMAPI_20065;
	IPropSet20068	*m_IRTCOMAPI_20068;
	IPropSet20082	*m_IRTCOMAPI_20082;
	bool			m_bIRTCOMAPISuccess;// ��ʼ���Ƿ�ɹ��ı�־
 	ULONG			m_ulIndex;			// ���浱ǰĬ����������

  	bool m_song_show_video_picture; //��ʾ������Ƶor��ʾͼƬ
	bool m_vice_screen_show_flag;
	bool m_recv_active_flag;
	
  	TCHAR m_vc_show_song_or_singer[256];   //������ҳ����ʾ����or����
  	bool m_voice_singer;

	CLyricManager m_lyricManager;
	double		m_dLyricLastTime;	//��ʳ���ʱ�䣬������ͣʱ
	bool		m_bFlag;			//�����ʾλ�ñ�־��true���У�flash���У�
	bool		m_bBegin;			//�����ʾ�Ƿ�Ϊ�տ�ʼ

	//�Ƿ��Ѿ�����flash��ʾ������
	bool m_first_open_four_track;
	bool m_is_open_four_track; //�ж��Ƿ����������죬�Ӽ��ܹ�����

	bool m_b_share_recv_msg;	//K������Ƿ����յ�����Ϣ
	std::wstring m_str_slave_recorder_song_id;//���ص��K�����ʱ����¼�´�ʱ����ID

	bool m_bBubble;		//�Ƽ������Ƿ�������ݣ����ʱ��ʾ���и�ʱ����ʾ���ݣ�ֻ�����Ƽ�������������������
	bool m_bMightLike;	//����ϲ���Ŀ���״̬��true:������
	/*******************************������************************/
	std::vector<CTrendListManager> m_vec_TrendListManager;
	std::wstring m_str_trend_list_path;				 //�������ļ�·��
	////////////////////////////////////////////////////////
	/************************����������************************/
	CInterScreenManager m_inter_screen_manager;				//������
	INTER_SCREEN_CAPTION	m_inter_screen_caption;			//������������Ļ��Ϣ
	bool m_inter_screen_exist;								//�����������Ƿ���
	int m_inter_screen_mode;								//����������ģʽ
	int m_show_activity_wnd;								//���������������λ��
	bool m_activity_wnd_full_screen;							//����������������Ƿ�ȫ��
	CChildWnd m_inter_screen_window;						//�������������ڵĸ�����
	bool m_inter_screen_window_exist;						//�������������ڵĸ������Ƿ����
	new_flash_player m_inter_screen_flash_player;			//������������flash������
	bool m_inter_screen_flash_player_exist;					//������������flash��������ʾ
	bool m_inter_screen_flash_show;							//��flash�������Ƿ���ʾ
	CRect m_rt_flash_player;								//����λ��

	bool m_inter_screen_soft_exist;							//δ��������������ó�����ʱ���������������Ƶ����
	CChildWnd m_master_show_window;							//����������������Ƶ/��Ϸ����
	bool m_b_master_show_window_exist;						//
	CRect m_rt_master;										//��Գ���������λ��

	CChildWnd m_slave_show_window;							//�����������и���Ƶ/��Ϸ����
	bool m_b_slave_show_window_exist;						//
	CRect m_rt_slave;										//��Գ���������λ��

	CChildWnd m_activity_video_wnd;							//���Ƶ����(ָ���ǲ��ŵڶ����ӵ���Ƶ����)
	bool m_bactivity_video_wnd_exist;						//

	CRect m_rtRelativeActivityWnd;							//�Flash����λ�ã���Գ��������꣩
	CRect m_rtAbsoluteActivityWnd;							//�Flash����λ�ã�ȫ�־������꣩
	CRect m_rtPassVideoWnd;									//����ʱ��Ƶλ��
	CRect m_rtPassVideoWndSoft;								//��ⴳ��ʱ��Ƶλ��
	/////////////////////////////////////////////////////////////////////////////////
	CRect m_rt_soft_activity;				//�������Flash����λ�ã��������꣩
	/******************************��ս��*****************************/
	CTransparentWnd *m_StarTransparentWnd;			//��ս��͸������
	std::vector<CHALLENGE_STAR_IFNO>	m_vec_challenge_star_info;//��ս����
	bool	m_bChallengeStarFinish;	//flash��ʼ����ɵı�־
	int		m_nFlashFinishCnt;		//��ɸ���
	bool	m_b_challenge_begin;	//��ս��ʼ�ı�־
	bool	m_b_challenging;		//������ս�ı�־
	int		m_nChallengeIndex;		//��������
	int		m_nCurrentScore;		//��ǰ����
	int		m_nCurrentTotalScore;	//��ǰ�����ܷ���
	int		m_nSingCount;			//�ѳ�����
	int		m_nChallengeSongCount;	//��ս�����ܸ���
	int m_nChallengeSongPageCount;	//�ܹ���ҳ��
	int m_nCurrentChallengeSongPage;   //��ǰҳ��
	CTransparentWnd *m_StarSoftTransparentWnd;			//�����ս��͸������
	/////////////////////////////////////////////////////////////
	/***********************����ά*********************************/
	vector<CPassManager>	m_vec_pass_tmp;	//��ʱ��Źؿ���Ϣ������
	vector<CPassManager>	m_vec_pass;//�ؿ���
// 	CTransparentWnd * m_PassTransparentWnd;//͸������
	new_flash_player m_AcrossPassFlashPlayer;//
	bool m_bAcrossPassFlashPlayerExist;		//������������flash��������ʾ
// 	CTransparentWnd * m_PassSoftTransparentWnd;//���͸������
	new_flash_player m_AcrossPassSoftFlashPlayer;//
	bool m_bAcrossPassSoftFlashPlayerExist;		//flash��������ʾ
	PASS_STATE m_pass_state[10];					//�����ϴ��˳�ʱ�Ĺؿ�״̬
	bool m_bFirstLyric;							//�Ƿ񳪵ĵ�һ����

	bool m_bAcrossPassFlashFinish;	//flash��ʼ�����
	bool m_bAcrossPassing;	//����״̬(true���ڴ���)
	bool m_bInPageAcrossPass;	//�Ƿ��ڰ���ά����
	int m_nTotalPassCount;		//�ܹؿ���
	int m_nCurPassIndex;			//��ǰ�ؿ�����0-n
	int m_nCurSongIndex;			//��������
	int m_nCurPageCode;		//��ǰ�����Ļҳ��

	int m_nIntactCount;		//�����ﵽ�����������ȴ���
	int m_nSimilarityCount;		//�����ﵽ���������ƶȴ���
	int m_nStabilityCount;		//�����ﵽ�������ȶ��ȴ���
	int m_nContinueCount;	//�ﵽ�������������������Ӵ���
	int m_nGoalScore;		//�Ӵ��ӵ�Ŀ�����
	int m_nIceInitCount;			//��ʼ��������
	int m_nIceAddSecond ;		//�������ӵ�ʱ����
	/////////////////////////////////////////////////////////////////
	/*//////////////////////������Ϸ/////////////////////////////*/
	bool m_bActiveGameFlashFinish;	//������Ϸflash��ʼ�����
	bool m_bActiveGaming;			//���ڻ�����Ϸ��
	char m_szActiveGameIp[16];		//�ip
	TCHAR m_szActiveGameUrl[256];	//��ά��URL
	TCHAR m_szPicFilePath[256];	//��ά��ͼƬ���ش��·��
	int m_nPlayerCount;	//��ǰ������Ϸ����
	int	m_nPlayerIndex;		//��ǰͶ�������� ��0-5��
	int	m_nDiceNumber;		//��ǰͶ�����ӵ�ֵ
	vector<GAME_PLAYER_INFO> m_vecGamePlayer;	//������Ϸ����Ա��Ϣ
	TCHAR m_szClientIp[256];					//������ip

	new_flash_player m_active_game_flash_player;//flash������
	bool m_active_game_flash_player_exist;		//flash����������

	new_flash_player m_active_game_soft_flash_player;//���flash������
	bool m_active_game_soft_flash_player_exist;		//���flash����������

	//////////////////////////////////////////////////////////////
	//΢�Ż���-��Ļ
	bool m_bWechatInteractionFlashFinish;		//flash ��ʼ����ɵı�־
	CTransparentWnd *m_pWechatInteractionSoftTransparentWnd;			//���΢�Ż���-��Ļ͸������
	bool m_wechat_interaction_soft_flash_player_exist;		//���flash����������

	CTransparentWnd *m_pWechatInteractionTransparentWnd;			//���΢�Ż���-��Ļ͸������
	bool m_wechat_interaction_flash_player_exist;		//���flash����������

	int m_nBarrageFlashFinishCnt;							//��ʼ����ɸ���

	bool m_bWechatBarrageOpen;									//��Ļ�Ƿ���
	int m_nWechatBarrageMode;									//��Ļģʽ��0��������Ϣ 1��������Ϣ��
	char m_szWechatBarrageIp[16];								//��Ļ����ip
	TCHAR m_szWechatBarrageUrl[256];			//��ά��URL
	TCHAR m_szWechatBarragePicFilePath[256];	//��ά��ͼƬ���ش��·��
	llock m_wechat_barrage_lock;
	deque<BARRAGE_INFO> m_deque_barrage_info;				//��ŵ�Ļ��Ϣ�Ķ���
	int m_nFontSizeMin;		//�����С
	int m_nFontSizeMax;
	////*/
	/*////////////΢�Ż���-���ħ�����飩///////////*/
	bool m_bWechatGiftFlashFinish;			//flash��ʼ����ɵı�־
	CTransparentWnd *m_pWechatGiftSoftTransparentWnd;	//���΢�Ż���-����͸������
	new_flash_player m_WechatGiftFlashPlayer;	//���flash������
	bool m_bWechatGiftFlashPlayerExist;			//���flash����������
	llock m_wechat_gift_lock;
	deque<WECHAT_MESSAGE> m_deque_wechat_message;				//���������Ϣ�Ķ���
	bool m_bWechatGiftPrepare;				//����׼���У�����׼��������
	bool m_bWechatGiftSending;				//���﷢���У��������ﶯ������ʧ�ܶ�����
	///////////////////*/
	/*��Ƭ����*/
	int m_nPicturePlayTime;			//��Ƭ��ʾʱ������λ���룩
	///*/
	//��Ƶ�㳡 - ���������Ƕ��html��ֱ�ӷ���www����
	BOOL m_video_show_exist;
	vector<ST_VIDEO_SHOW*> m_st_video_show_vec;
	int m_video_show_current_page;
	int m_video_show_count_page;

	CDShineAxBrowse m_ocxShAxBrowse;
	CWnd *m_pBrowseWnd;
#ifdef VIDEO_SHOW_FULL_SCREEN
	bool m_video_show_wnd_exist;
#endif // VIDEO_SHOW_FULL_SCREEN	

	//����ʶ��
	vector<wstring> m_listen_reward_vec;			//��������
	vector<wstring> m_listen_song_info_vec;			//�����������б�����
	int m_iCount_down;								//ʱ������
	vector<song_info> m_vec_listen_song_info_temp;  //��ʱ���ظ���
	vector<song_info> m_vec_listen_song_info;		//���ظ���
	llock m_listen_song_lock;
	vector<wstring> m_answer_vec;					//��
	int m_nListenPassCount;							//�ؿ�����
	new_flash_player m_listen_flash_page_tv;		//���Ӷ�flash����
	BOOL m_listen_flash_page_tv_exist;				//����ʶ�����ڴ���
	int m_iCurrent_pass;							//��ǰ�ڼ���
	song_info m_listen_song_info[10];				//�ؿ����ŵĸ�����Ϣ
	song_info m_listen_song_info_answer[3];			//�𰸵���������
	int m_listen_answer_index;
	wstring m_ksc_lyrics_path;
	new_flash_player m_listen_flash_page_tv_soft;		//�����Ӷ�flash����
	BOOL m_listen_flash_page_tv_soft_exist;				//�������ʶ�����ڴ���
	bool m_bListenSongFlashFinish;						//����ʶ��flash��ʼ�����

	//����mv
	new_flash_player m_picture_mv_wind;				//����mv���Ӷ�flash����
	BOOL m_picture_mv_wind_exist;					//����mv���Ӷ�flash�����Ƿ����
	vector<ST_PICTURE_MV*> m_st_picture_mv_vec;		//��ǰ����mv�����Ľṹ����
	wstring	m_picture_mv_server_ip;					//����mv������ip
	string	m_picture_mv_curr_guid;					//��ǰ��������mv��guid
	CParseLyricsForKSC	m_parse_lyics_ksc;			//ksc��ʶ���
	LPKaraokeKSC m_lpKaraokeKSC;					//��ʼ���󷵻صĸ�ʶ���
	new_flash_player m_picture_mv_wind_soft;			//�������mv���Ӷ�flash����
	BOOL m_picture_mv_wind_soft_exist;					//�������mv���Ӷ�flash�����Ƿ����
	song_info m_piture_mv_songInfo;
	bool m_bPictureMvFlashFinish;					//����mvflash��ʼ�����

	bool m_use_audio_effect;

	//�������ʷ����������к�
	int m_server_manually_val;

	//flash �������������Ϣ
	DWORD m_flash_process_id;
	PROCESS_INFORMATION m_flash_process_info;
	/*��߷����ı���A��AΪ0-100��,Ϊ0ʱ������
	˵�������õ��ܷ�ΪS������ΪA�������������ܷ�ΪT����
	0<S && S<=50 ʱ��T = S + S*A%;
	50<S && S<=80ʱ��T = S + (100-S)*A%;
	80<S && S<=100ʱ��T = S;
	*/
	int m_nScoreIncreaseRate;
	// ƽ̨�������
	CTimer m_timerMusicEnjoy;	//���ʱ��Ķ�ʱ��
	double m_dMusicEnjoySpace;//��ʱ����ʼ��ļ��ʱ��
	int m_nMusicEnjoyWidth;		//ƽ̨���ָ����ʾ����Ļ���
	int m_nMusicEnjoyHeight;	//ƽ̨���ָ����ʾ����Ļ�߶�

//#ifdef DALIAN_MATSA_EK_PLUS
	/*******************************************************
	ÿ�ο����󣬻����ս�󿧡�����ά������ʶ�����������¼������
	��ս�󿧣����и����Ľ�����ͬ��������ȡһ��
	����ά��ֻ�����һ�����ý�����������ȡһ��
	����ʶ����ֻ�����һ�����ý�����������ȡһ��
	*********************************************************/
	bool m_bCSGetAward;			//��ս��(ChallengeStar)�Ƿ���ȡ������
	bool m_bAPGetAward;			//����ά(AcrossPass)�Ƿ���ȡ������
	bool m_bLSGetAward;			//����ʶ��(ListenSong)�Ƿ���ȡ������
//#endif
	//add by yzg 2015-12-09
	//����ת���У�����������mv
	bool m_bInPageVideo;
	//ͨѶ����
	CHTTP m_http_obj;

	//Ĭ������ 0:�������� 1:ԭ����� 2:ԭ�� 3:��������
	int m_default_track;

	//*********************�����Ӱ
	fd_set m_DaoQiMovieFd_set;
	/////////////////////////*/

	int m_open_full_screen;
};
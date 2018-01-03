#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <map>
using namespace std;

//�Ӵ��ڵ�ID
enum CHILD_WINDOW_ID
{
	FLASH_PLAYER_WINDOW_ID = 10001, //flash����������ID
	SUB_FLASH_PLAYER_WINDOW_ID,     //��flash����������ID
	TEST_MACHINE_PLAYER_WINDOW_ID,  //��Ϸflash����������ID
	SCREEN_SHOW_WINDOW_ID,          //��Ļ��ʾ����ID
	SUB_SCREEN_SHOW_WINDOW_ID,      //��Ļ��ʾ���ڵ��Ӵ���ID
	LOBBY_LIVE_WINDOW_ID,           //ֱ������id
	PREVIEW_WINDOW_ID,              //Ԥ������ID
	TV_WINDOW_ID,                   //����ֱ������ID
	SOFT_DECODE_WINDOW_ID,          //��ⴰ�ڵ�ID
	HANDWRITING_OCX_ID,             //��д�ؼ���ID
	HANDWRITING_WINDOW_ID,          //��д���ڵ�ID
	SURVEY_HANDWRITING_WINDOW_ID,   //������д���ڵ�ID
	SLAVE_WINDOW_FLASH_PLAYER_ID,   //������Ƶ���ڵ�flash����������ID
	SLAVE_VIDEO_WINDOW_ID,          //������Ƶ����ID
	GAME_FLASH_PLAYER_WINDOW_ID,    //������Ϸ����ID
	WALL_PANEL_PLAYER_WINDOW_ID,    //ǽ���flash������ID
	DOORPLATE_FLASH_PLAYER_WINDOW_ID,//���ƻ�����ID
	LOCAL_GAME_PLAYER_WINDOW_ID,     //������Ϸ����������ID
	DRINKS_FLASH_PLAYER_WINDOW_ID,   //��Ƕ��ˮflash������
	AUDIO_EFFECT_WINDOW_ID,          //��Ч����ID
	AD_FLASH_PLAYER_WINDOW_ID,       //��洰��ID
	REBOOT_PLAYER_CONTROL_TIMER_EVENT_ID, //�������ſؼ�
	VIDEO_SCREEN_SHOW_WINDOW_ID,        //��Ƶ����ID
	MSQUARE_SCREEN_SHOW_WINDOW_ID,     //Mƽ���Ĵ���
	SCORE_SOFT_FLASH_WINDOW_ID,		//������ϵķ���flash
	SCORE_FLASH_WINDOW_ID,           //����flash����ID
	RECORD_NOISE_TIMER_EVENT_ID,          //¼�������ļ���ʱID
	HTML_CTRL_ID,					 //�������Ŵ��ڵ�ID
	VICE_SCREEN_PLAYER_ID,			 //������ID
	INTER_SCREEN_PLAYER_ID,			//����������flash������ID
	MASTER_SHOW_WINDOW_ID,			//����������������Ƶ����
	SLAVE_SHOW_WINDOW_ID,			//�����������и���Ƶ����
	ACTIVITY_VIDEO_WND_ID,			//�����������л��Ƶ����
	SCREEN_FLASH_WND_ID,			//
	SCREEN_FLASH_PLAYER_ID,				//����flash������
	ACROSS_PASS_PLAYER_ID,			//����άflash������ID
	CHALLENGE_STAR_PLAYER_ID,		//��ս��flash������
	HTML_VIDEO_SHOW_ID,				 //��Ƶ�㳡��html��ID
	LISTEN_PAGE_TV_ID,				 //����ʶ������ID
	PICTURE_MV_TV_ID,				//���Ӷ�
	ACTIVE_GAME_PLAYER_ID,			//������Ϸ
	//���flash
	ACROSS_PASS_SOFT_PLAYER_ID,			//����άflash������ID
	CHALLENGE_STAR_SOFT_PLAYER_ID,		//��ս��flash������
	LISTEN_PAGE_TV_SOFT_ID,				 //����ʶ������ID
	PICTURE_MV_TV_SOFT_ID,				//���Ӷ�
	ACTIVE_GAME_SOFT_PLAYER_ID,			//������Ϸ���flash
	WECHAT_INTERACTION_SOFT_PLAYER_ID,	//΢�Ż���-��Ļ
	WECHAT_INTERACTION_PLAYER_ID,		//
	WECHAT_GIFT_SOFT_PLAYER_ID,			//΢�Ż���-���ħ�����飩
	WECHAT_GIFT_PLAYER_ID,			//
};

//��ʱ����ID
enum TIMER_EVENT_ID
{
	SHOW_LOGO_TIMER_EVENT_ID=101,         //������ʾlogo�Ķ�ʱ��ID
	SHOW_CONTROL_OSD_TIMER_EVENT_ID,      //��ʾ����osd�Ķ�ʱ��ID
	SHOW_BMP_PICTURE_TIMER_EVENT_ID,      //��ʾBMPͼƬ�Ķ�ʱ��ID
	SHOW_SCORE_TIMER_EVENT_ID,            //��ʾ������ʱ��ID
	SHOW_FLASH_TEXT_TIMER_EVENT_ID,       //��flash����ʾ�������ֵĶ�ʱ��ID
	SHOW_TV_TEXT_TIMER_EVENT_ID,          //�ڵ�������ʾ�������ֵĶ�ʱ��ID
	SHOW_FLASH_BACKGROUND_TIMER_EVENT_ID, //����flash����ͼƬ�Ķ�ʱ��ID
	SHOW_FLASH_LOGO_TIMER_EVENT_ID,       //��flash����ʾlogo�Ķ�ʱ��ID
	SHOW_TV_LOGO_TIMER_EVENT_ID,          //�ڵ�������ʾlogo�Ķ�ʱ��ID
	SHOW_SCREEN_SAVER_TIMER_EVENT_ID,     //��ʾ�����Ķ�ʱ��ID
	COMMON_TIMER_EVENT_ID,                //���ö�ʱ��ID
	AUTO_TEST_TIMER_EVENT_ID,             //�Զ����Զ�ʱ��ID
	HIDE_CHECT_WINDOW_TIMER_EVENT_ID,     //���ظ�����ѡ��ʱ��ID
	SHOW_POPUP_WINDOW_TIMER_EVENT_ID,     //��ʾ�������ڵĶ�ʱ��ID
	SHOW_WALL_PANEL_IMAGE_TIMER_EVENT_ID, //��ʾǽ���ͼƬ�Ķ�ʱID
	CHECK_FILE_TIMER_EVENT_ID,            //����ļ��Ƿ���ڵĶ�ʱ��ID
	CHECK_MYSQL_TIMER_EVENT_ID,           //���mysql�����ݿ�
	CHECK_PK_CONNECT_TIMER_EVENT_ID,      //���pk�Ƿ�����
	SHOW_PK_ACCEPT_WINDOW_TIMER_EVENT_ID, //�Ƿ�����pk����Ի���
	REQUEST_HEAD_PICTURE_TIMER_EVENT_ID,          //��ʱ����ͷ������
	SHOW_SCREEN_TO_FLASHS_TIME_EVENT_ID,
	GET_VICE_SCREEN_TO_FLASH_TIME_EVENT_ID, //����������ݶ�ʱID
	SHOW_MUSIC_ENJOY_LYRIC_TIME_EVENT_ID,					//��ʾƽ̨���ָ��
	SHOW_SCREEN_FLASH_TIMER_EVENT_ID,		//��ʾ��Ļ����flash����
	INTER_SCREEN_MAIBA_RULE_TIME_EVENT_ID,		//���������������ʱ��
	INTER_SCREEN_MAIBA_SONG_LIST_TIME_EVENT_ID,	//�������������Ϣ��ʱ��
	CLOSE_ROOM_TIME_SPACE_TIME_EVENT_ID,		//�ֶ��������Զ��ط���ʱ������ʱ��
	DESTROY_GIFT_WND_TIME_EVENT_ID,				
};

//�컮����
enum QUICK_SCROLL_DIRECTION
{
	QUICK_SCROLL_LEFT, //����
	QUICK_SCROLL_RIGHT, //����
};

//�Զ������Ϣ
enum DEFINE_MESSAGE
{
	DM_FLASH_INITIALIZATIONF_FINISH=WM_USER+10,   //flash�����ʼ����ɵ���Ϣ
	DM_CHECK_DOG,                                 //��⹷����Ϣ
	DM_CHECK_PRECOMPUTER,                         //���ǰ�õ���Ϣ
	DM_SCREEN_SAVER_END,                          //��������
	DM_BOX_COM_RECEIVE_MESSAGE,                   //�пغд��ڽ��յ�����Ϣ
	DM_SCREEN_COM_RECEIVE_MESSAGE,                //���������ڽ��ܵ�����Ϣ
	DM_SCREEN_VIDEO_CLICK,                        //��Ļ��Ƶ����
	DM_ADD_SING_SONG,                             //�����ѳ����������ݿ���
	DM_INK_RECOGNITION_FINISH,                    //��дʶ����ɣ����Եõ����
	DM_SUB_WINDOW_MESSAGE,                        //�Ӵ��ڷ��͹�������Ϣ
	DM_RECV_SERVER_DATA,                          //���ܷ��������ط����ݵ���Ϣ
	DM_RECV_SERVER_MSG,                           //���յ���������Ϣ����Ϣ
	DM_MASTER_SLAVE_MESSAGE,                      //��������Ϣ
	DM_WALL_PANEL_COM_RECEIVE_MESSAGE,            //ǽ��崥�������ڽ��ܵ���Ϣ
	DM_SAVE_SELECT_SONG_ID,                       //����ѡ�����ID
	DM_SAVE_U_DISK_SONG,                          //����U�̸���
	DM_DOORPLATE_ROOM_INFO,                       //���ƻ��İ�����Ϣ
	DM_DOORPLATE_COM_RECV_MESSAGE,                //���ƻ����ڽ�����Ϣ
	DM_PLAY_SONG_TIP_MESSAGE,                     //���Ÿ�����ʾ��osd��Ϣ
	DM_MSQURE_WINDOW_CLICK_MESSAGE,                //Mƽ�����Ƹ���������Ϣ
	DM_SHOW_WALL_PANEL_MESSAGE,                   //��ʾǽ������Ϣ      
	
	//��������
	DM_FOOD_HANDLE_MSG=61204,                     //������ˮ�����;������Ϣ
	DM_REAL_DUMP_MESSAGE=61205,                   //��ʵ�ļ��ӹ���Ϣ

	WM_PlayStateChange = WM_USER + 5555,
	WM_MediaPositionChange = WM_USER + 5556,
	WM_MediaVolChange = WM_USER + 5557,
	WM_SoundSpectrumBegin = WM_USER + 5566, //Ƶ�׿�ʼ
	WM_SoundSpectrumData = WM_USER + 5565, //Ƶ������
	WM_SoundSpectrumEnd = WM_USER + 5567, //Ƶ�׽���
	WM_MusicBeat = WM_USER + 5575, //������Ϣ
	WM_PLAYER_HANDLE = 6824, //�ĵ���Ϣ
	WM_NEED_PLAYER_FREDATA = 6825, //���������͸��������Ƿ���ҪƵ������
};


enum DOG_MESSAGE
{
	CONNECT_DOG_FAIL,       //���Ӽ��ܹ�ʧ��
	DOG_LOGIN_CHECK,        //���ܹ�����
	TIMER_CHECK_DOG_FAIL,   //���ڼ����ܹ�ʧ��
	CHECK_DOG_SUCCESS,      //�����ܹ��ɹ�
	SOFTWARE_DOG_VALID_DAY_TIP,  //���������Ч������ʾ
	CONTROL_DOG_VALID_DAY_TIP,   //�ؼ�������Ч������ʾ
};

//����ն�������״̬
enum PC_STATE
{
	SELECT_SONG_STATE,              //���״̬
	CLOSE_ROOM_STATE,               //�ط�״̬
};

//��Ա����״̬
enum MEMBER_MANAGE_STATE
{
	MEMBER_LOGIN_STATE=1,      //��¼
	MEMBER_REGISTER_STATE=2,   //ע��
	MEMBER_CHANGE_PSW_STATE=3, //�޸�����״̬
	MEMBER_REGISTER_PHONE=4,   //K��ע���ֻ���
};

//���ӵĲ���ģʽ
enum TV_PLAY_MODE
{
	TV_SINGLY_PLAY_MODE=1,   //����
	TV_GROUP_PLAY_MODE,      //�鲥

};

//���ŵ���Ƶ����,�����1��ʼ����Ҫ�޸�
enum PlAY_VIDEO_TYPE
{
	VIDEO_TYPE_SONG=1,        //����
	VIDEO_TYPE_LOBBY_LIVE=2,  //����ֱ��
	VIDEO_TYPE_TV=3,          //����
	VIDEO_TYPE_PREVIEW_SONG=4,//Ԥ������
};

//Ԥ�����ſ���
enum PLAY_CONTROL
{
	PLAY_CONTROL_PAGE_CLOSE=1,      //Ԥ��ҳ��ر�
	PLAY_CONTROL_SONG_PRIORITY=2,   //Ԥ������
	PLAY_CONTROL_SONG_MEMBER=3,     //�����ղ�
	PLAY_CONTROL_SONG_SELECT=4,     //�㲥����
	PLAY_CONTROL_FAST_BACKWARD=5,   //����
	PLAY_CONTROL_FAST_FORWARD=6,    //���
};

//��Ա��־
enum MEMBER_FLAG
{
	MEMBER_FLAG_LOGIN_NO=0,    //û�е�¼
	MEMBER_FLAG_LOGIN,			//��¼��
	MEMBER_FLAG_REGISTRATION,   //��ע���
	MEMBER_FLAG_ERROR,			//404 
	MEMBER_FLAG_LOGIN_ERROR,    //��¼1 ʧ��
	MEMBER_FLAG_PHONE_CODE_ERROR,//5 �ֻ���֤�����
	MEMBER_FLAG_PHONE_REGISTER,  //register12 �ֻ�����ע��
};

//flash����ʹ�õ�����
enum FLASH_USE_LANGUAGE
{
	FLASH_LANGUAGE_SIMPLIFIED_CHINESE=0,   //����
	FLASH_LANGUAGE_TRADITIONAL_CHINESE,    //����
	FLASH_LANGUAGE_ENGLISH,                //Ӣ��
	FLASH_LANGUAGE_KOREAN,                 //����
	FLASH_LANGUAGE_JAPANESE,               //����
	FLASH_LANGUAGE_MONGOLIA,               //����
};

//���͸���̨����Ϣ����
enum SEND_BACK_SERVER_MSG_TYPE
{
	BACK_SERVER_MSG_TYPE_IP_NAME,      //����IP�ͻ���������̨
	BACK_SERVER_MSG_TYPE_CLEAN,        //�����巿��Ϣ����̨
	BACK_SERVER_MSG_TYPE_REQUESTOPEN,  //�������󿪷���Ϣ����̨
};

//flash�Ϲ����Ļ�ӭ������
enum FLASH_SCROLL_WELCOME_TYPE
{
	FLASH_WELCOME_TYPE_DOG,    //���Ļ�ӭ��
	FLASH_WELCOME_TYPE_CLIENT, //�ͻ���
	FLASH_WELCOME_TYPE_MSG,    //��Ϣ��
};

//flash�ϸ�������ʾ��ʽ
enum FLASH_SONG_SHOW_MODE
{
	SONG_SHOW_MODE_CARD,      //��Ƭ��ʽ��ʾ����
	SONG_SHOW_MODE_LIST,      //�б�ʽ��ʾ����
};

//ҳ����
enum PAGE_OPERATE
{
	FIRST_PAGE_OPERATE=0, //��һҳ����
	CUR_PAGE_OPERATE,     //��ǰҳ
	PRE_PAGE_OPERATE,     //���Ϸ�ҳ
	NEXT_PAGE_OPERATE,    //���·�ҳ
};

//���Ƿ��෽ʽ
enum SINGER_CLASS_MODE
{
	SINGER_CLASS_MODE_OLD,   //�ɵķ�ʽ
	SINGER_CLASS_MODE_NEW,   //�µķ�ʽ
};

//ǽ�����ʾ��ʽ
enum WALL_PANEL_SHOW_MODE
{
	WALL_PANEL_VIDEO_IMAGE=0,   //��Ƶ����ͼƬ
	WALL_PANEL_VIDEO_FLASH,   //��Ƶ����flash
	WALL_PANEL_IMAGE_FLASH,   //ͼƬ����flash
	WALL_PANEL_VIDEO,         //ֻ��ʾ��Ƶ
};

//��������
enum SCREEN_TYPE
{
	SCREEN_TYPE_HORIZON,   //���
	SCREEN_TYPE_VERTICAL,  //����
};

//��ʾ��������
enum VOLUMN_BAR_FLAG
{
	MUSIC_VOLUMN_BAR,   //����������
	MIC_VOLUMN_BAR,     //���������
};


//��������
enum KEYBOARD_TYPE
{
	KEYBOARD_TYPE_CHINESE,   //���ļ���
	KEYBOARD_TYPE_KOREAN,    //���ļ���
	KEYBOARD_TYPE_JAPANESE,  //���ļ���
};

enum WEIBO_SHOW_MODE
{
	WEIBO_SHOW_MODE_FULL_SCREEN_V=0,    //����ȫ��
	WEIBO_SHOW_MODE_LEFT,               //���
	WEIBO_SHOW_MODE_TOP,                //�ϱ�
	WEIBO_SHOW_MODE_BOTTOM,             //�±�
	WEIBO_SHOW_MODE_RIGHT,              //�ұ�
	WEIBO_SHOW_MODE_FULL_SCREEN_H,      //���ȫ��
};

enum SCORE_SYSTEM
{
	SCORE_SYSTEM_NONE=0,  //û����������ϵͳ
	SCORE_SYSTEM_SHINE,   //������ϵͳ
	SCORE_SYSTEM_XUNFEI,  //Ѷ�ɴ��ϵͳ
};

//�����ظ���������
enum REQUEST_SONG_TYPE
{
	REQUEST_NO = -1,	//û������
	MYRECORDSHARE,		//�ҵķ���
	COUNTRYHOT,			//ȫ�����
	COUNTRYNEW,			//ȫ������
	PLACEHOT,			//�������
	PLACENEW,			//��������
	MYCOLLECTION,		//�ҵ��ղ�()
	FREEPK,				//����pk
	AREAPK,				//��̨pk
	MYPRIVATESONG,       //˽������
	RANKING_POLITE,		//�ϰ�����
};

enum  OPERATE
{
	ENCRYPT,
	DECRYPT,
};

enum BUTTON_STATE
{
	GUID_BUTTON_STATE,  //������ť״̬
	SCORE_BUTTON_STATE, //���ְ�ť״̬
	TAPE_BUTTON_STATE,  //¼����ť״̬
	ENJOY_BUTTON_STATE, //���Ͱ�ť״̬
	ROOM_BUTTON_STATE,  //���ط�״̬
	DJ_BUTTON_STATE,    //DJ����״̬
	MOVIE_BUTTON_STATE, //��Ӱ����״̬
	OPEN_SERVER_WINDOW,  //�Ƿ񵯳�����Ի���
	VIDEO_DATING_STATE, //��Ƶ���Ѱ�ť״̬
	SHOW_CLOUD_SONG_STATE, //��ʾ�ƼӸ�״̬
};

enum MAIBA_TYPE
{
	MAIBA_SHARE,   //K�����
	MAIBA_FIND,		//�������
	MAIBA_DEKARON, //��ս��� 
	PRIVATE_SONG,  //˽������
};

enum PK_HARDWARE_MODE
{
	PK_HARDWARE_MODE_SETBOX = 0,
	PK_HARDWARE_MODE_CAM,
};

//���pk��̨�������Ϣ
typedef struct MAIBARULE
{
	TCHAR activity_type[5];			//�������(1:����pk��2:��̨pk)
	TCHAR start_time[256];				//���ʼʱ��
	TCHAR end_time[256];				//���ʼʱ��
	TCHAR participation_type1[1024];		//���뷽ʽ1
	TCHAR participation_song[256];      //�������
	TCHAR participation_type2[1024];     //���뷽ʽ2
	TCHAR rating_methods[1024];          //���ȷ�ʽ
	TCHAR activities_award1[1024];		 //�����1
	TCHAR activities_award2[1024];		 //�����2
	TCHAR activities_award3[1024];		 //�����3
	TCHAR activities_award4[1024];		 //�����4
	TCHAR activities_award5[1024];		 //�����5
}MAIBARULEINFO;

//�ƿؽṹ��
typedef struct LINGHT_CONTROL 
{
	unsigned int head_flag;  //ͷ��ʶ
	unsigned int order_content; //ָ������
	char order_param[10];  //ָ�����
}LINGHT_CONTROL;

//����ĸ�����Ϸ�ṹ
typedef struct SONG_GAME
{
	TCHAR name[256];      //����
	TCHAR path[256];      //·��
	TCHAR song_number[128];//�������
}SONG_GAME_STRUCT;

typedef struct MAIBA_HEIGHT_RANKING
{
	TCHAR song_id[128];     //����id¼��id
	TCHAR song_name[64];   //��������   
	TCHAR singer_name[32];  //�������� 
	TCHAR score[8];         //����
	TCHAR wave_path[128];		//·��
	TCHAR video_path[125];      
	TCHAR datetime[32];         //¼����ʼʱ��
	TCHAR voice_id[128];    //��������id
	TCHAR member_pic[256];  //��Ա��ͷ��
	TCHAR nick_name[256];   //�û��ǳ�
	TCHAR voice_code[256];
	TCHAR room_name[64]; //������
}MAIBA_HEIGHT_RANKING;


//��Ը��������Ϣ   �׻����ղء�����id ����userid
typedef struct MAIBA_SONG_INFO
{
	TCHAR song_id[256];      //����id
	TCHAR song_name[256];   //��������
	TCHAR singer_name[256];  //������Ϣ
	TCHAR song_score[10];   //��������
	TCHAR member_pic[256];   //��Աͷ��
	TCHAR member_addr[256];  //ͷ���ַ(url)
	TCHAR member_pic_name[256];  //��Աͷ������
	TCHAR listen_count[64];  //��������
	TCHAR flowers_count[64]; //�׻�����
	TCHAR voice_id[256];     //����ΨһId
	TCHAR user_id[256];      //�û�id
	TCHAR recorder_video[256];  //�����Ĵ洢·��
	TCHAR song_down_addrss[256];  //�������ص�ַ
	TCHAR wave_path[256];         //¼���ļ�·��
	TCHAR video_path[256];		//��Ƶ·��
	TCHAR nick_name[256];      //�û��ǳ�
}MAIBA_SONG_INFO_STU;

//��Թ�����Ϣ
typedef struct MAIBA_RULE_INFO
{   
	TCHAR activity_id[256];
	TCHAR song_id[256];
	TCHAR activity_type[256];
	TCHAR start_time[20];
	TCHAR end_time[20];
	TCHAR participation_type1[512];
	TCHAR participation_song[512];
	TCHAR participation_type2[512];
	TCHAR rating_methods[512];
	TCHAR activities_award1[512];
	TCHAR activities_award2[512];
	TCHAR activities_award3[512];
	TCHAR activities_award4[512];
	TCHAR activities_award5[512];
}MAIBA_RULE_INFO;

// ��ս��������Ϣ
typedef struct TAG_CHALLENGE_STAR_IFNO
{
	TCHAR record_song_id[128];     //����id¼��id
	TCHAR song_name[64];   //��������   
	TCHAR singer_name[32];  //�������� 
	TCHAR goal_score[8];			//Ŀ�����
	TCHAR award[128];			//����
	TCHAR score[8];         //����
	TCHAR wave_path[128];		//·��
	TCHAR video_path[125];      
	TCHAR datetime[32];         //¼����ʼʱ��
	TCHAR original_song_id[128];    //��������id
	TCHAR member_pic[256];  //��Ա��ͷ��
	TCHAR nick_name[256];   //�û��ǳ�
	TCHAR voice_code[256];
	TCHAR room_name[64]; //������
	int challenge_times;	//����ս����
	bool bUnable;			//true��������ս
}CHALLENGE_STAR_IFNO, *P_CHALLENGE_STAR_IFNO;

// ����ά����
enum PASS_STATE
{
	UN_ACROSS = 0,	//δ��ս
	READY_ACROSS,	//׼����ʼ
	ACROSSING,		//������ս
	ACROSS_SUCCESS, //��ս�ɹ�
	ACROSS_FAIL,	//��սʧ��
};
typedef struct TAG_HUNDRED_SECONDS_PRIZE_SONG
{
	TCHAR song_id[128];			//����id
	TCHAR song_name[256];		//��������
	TCHAR singer_name[64];		//��������

}HUNDRED_SECONDS_PRIZE_SONG, *P_HUNDRED_SECONDS_PRIZE_SONG;

//������Ƽ������ṹ��
typedef struct SONG_RECOMMEND
{
	TCHAR song_id[256];  //����id
	TCHAR song_name[256];  //��������
	TCHAR singer_name[256];  //��������
}SONG_RECOMMEND_STRUCT;

//����Ľṹ�壬���ڴ洢���͸�ǰ�û�����Ϣ
typedef struct PRECOMPUTER_MESSAGE
{
	char song_id[128];
	char song_name[128];
	time_t start_time;
	unsigned long play_time;
	unsigned char song_type;
}SEND_PRECOMPUTER_MSG;

//�ṹ�壬���ڴ洢���ܹ��򿪵Ĺ���
// �������ֽ�
typedef struct DOGFUNCTION
{
	unsigned int Com1;    //��Ч    
	unsigned int Com2;    //��Ч   
	unsigned int MScreen; //������
	bool AD;               //���
	unsigned int OSDSelect;	//OSD���
	bool preview;         //Ԥ��
	unsigned int Play;    //����
	unsigned int Word;    //���	
	unsigned int Mob;     //����
	unsigned int KY;      //����
	unsigned int Rec;     //¼��
	bool game;            //��Ϸ
	unsigned int MuCard;  //һ���࿨
	unsigned int control; //�����ع���
	bool drinks_software; //��̨����
	unsigned int mouse;   //��깦��
	bool precomputer_check; //�Ƿ���ǰ�û�
} DOG_FUNCTION;

typedef struct USERINFOR
{
	TCHAR Name[64];   // �ͻ�����
	TCHAR Tel[16];    //�绰����
	TCHAR Address[80];//�û����ڵ�,
	TCHAR PostAdd[64];//��ϵ��ʽ
	TCHAR Display[64];//Ҫ��ʾ���û���Ϣ
} USER_INFOR;

typedef struct SELLINFOR
{
	TCHAR oTel[16]; //��ϵ�绰
	TCHAR No[16];   // �����̱��
	TCHAR Name[64]; //����������
	TCHAR Pesonal[16];//��ϵ��
	TCHAR Tel[16];   //�绰
	TCHAR Address[64];//��ϵ��ʽ

} SELL_INFOR;


typedef struct RECORDSONGINFO
{
	TCHAR SongID[128];          //����ID
	TCHAR DateTime[128];        //¼��ʱ��
	TCHAR VoiceWavePath[256];   //������Ƶ�ļ�
	TCHAR MusicWavePath[256];   //������Ƶ�ļ�
	TCHAR mp3Path[256];         //mp3�ļ�·��
	int   DurationTime;         //����ʱ��
}RECORD_SONG_INFO;

typedef struct SONGSHARESUCCESS
{
	TCHAR song_id[128];  //����id
	TCHAR user_name[64]; //�û����� 
	TCHAR nick_name[64]; //�û��ǳ�
	TCHAR member_pic[256]; //��Աͷ��
	TCHAR voice_code[256]; //��ά�������
}SONG_SHARE_SUCCESS;

typedef struct RECOMMAND_SONG_INFO
{   
	TCHAR song_id[256];               //����id
	TCHAR song_name[256];             //��������
	TCHAR song_theme[256];            //��������
	TCHAR singer_id[256];             //����id
	TCHAR issue_year[256];            //�������
	TCHAR language[256];              //��������
	TCHAR singer_sex[256];            //�����Ա� 
	TCHAR singer_name[256];           //�������� 
}RECOMMAND_SONG_INFO;

//�����͸��ǵĻ�����Ϣ
typedef struct ST_MUSIC_ENJOY{
	TCHAR song_id[MAX_PATH];
	TCHAR song_name[MAX_PATH];
	TCHAR singer_id[MAX_PATH];
	TCHAR singer_name[MAX_PATH];
	TCHAR song_cloud_path[MAX_PATH];
	TCHAR song_lyric_cloud_path[MAX_PATH];//���·��
	TCHAR song_bk_path[MAX_PATH];//������Ƶ·��
	int song_top;	//����
	int song_type;	//ƽ̨

	ST_MUSIC_ENJOY(){
		memset(song_id, 0x00, MAX_PATH);
		memset(song_name, 0x00, MAX_PATH);
		memset(singer_id, 0x00, MAX_PATH);
		memset(singer_name, 0x00, MAX_PATH);
		memset(song_cloud_path, 0x00, MAX_PATH);
		memset(song_lyric_cloud_path, 0x00, MAX_PATH);
		memset(song_bk_path, 0x00, MAX_PATH);
		song_top = -1;
		song_type = -1;
	}
}ST_MUSIC_ENJOY;
//�񵥸�����Ϣ
typedef struct Tag_Trend_List_Song_Info
{
	int   nIndex;				//��������������0-9��
	TCHAR szSongId[256];		//����ID
	TCHAR szSongName[256];		//��������
	TCHAR szSingerId[256];		//����ID
	TCHAR szSingerName[256];	//��������

	int song_top;
	int song_type;
}Trend_List_Song_Info,*PTREND_LIST_SONG_INFO;

/************************������������Ϣ******************/
#define TCHAR_LEN		256
//������ʾ��Ϣ
typedef struct Tag_Scroll_Tip_Info
{
	TCHAR szNumber[16];			//��ʾ���
	bool bExist;				//�Ƿ񴴽�
	bool bShow;					//�Ƿ���ʾ
	int  nX;					//���Ͻ�X����
	int  nY;					//���Ͻ�Y����
	int  nWidth;				//���
	int  nHeight;				//�߶�
	TCHAR szInfo[TCHAR_LEN];	//��Ϣ
	TCHAR szPicPath[TCHAR_LEN];	//ͼƬ·��
}Scroll_Tip_Info, *PSCROLL_TIP_INFO;
//�б���ʾ����Ϣ
typedef struct Tag_List_Info
{
	TCHAR szNumber[16];			//��ʾ���
	bool bExist;				//�Ƿ񴴽�
	bool bShow;					//�Ƿ���ʾ
	int  nX;					//���Ͻ�X����
	int  nY;					//���Ͻ�Y����
	int  nWidth;				//���
	int  nHeight;				//�߶�
	TCHAR szInfo[TCHAR_LEN];	//��Ϣ
	TCHAR szPicPath[TCHAR_LEN];	//ͼƬ·��
}List_Info,*PLIST_INFO;
//(��Ƶ/��Ϸ)����
typedef struct Tag_Wnd_Info
{
	TCHAR szNumber[16];			//��ʾ���
	bool bExist;				//�Ƿ񴴽�
	bool bShow;					//�Ƿ���ʾ
	int  nX;					//���Ͻ�X����
	int  nY;					//���Ͻ�Y����
	int  nWidth;				//���
	int  nHeight;				//�߶�
	TCHAR szInfo[TCHAR_LEN];	//��Ϣ
	TCHAR szPicPath[TCHAR_LEN];	//ͼƬ·��
}Wnd_Info,*PWND_INFO;
//������������Ϣ
typedef struct Tag_Inter_Screen_Info
{
	int					n_mode;					//ģʽ��1������Ƶ 2��˫��Ƶ 3����������Ƶ��
	bool				b_exsit;				//
	int					n_show_activity_wnd;		//��ʾ��Ĵ��ڣ�0����������ʾ���wnd_slave������Ч���̶�101�� 
												//				  1����������ʾ���wnd_master������Ч���̶�101����
	bool				b_activity_wnd_full_screen;	//�Ƿ�ȫ����ʾ�����
	int					n_display_number;		//
	int					n_x;		//
	int					n_y;		//
	int					n_width;	//
	int					n_height;	//
	Tag_Scroll_Tip_Info	top_scroll_tip_info;	//�Ϲ�����
	Tag_Scroll_Tip_Info	bottom_scroll_tip_info;	//�¹�����

	Tag_List_Info		left_list_info;			//���б�
	Tag_List_Info		right_list_info;		//���б�

	Tag_Wnd_Info		master_wnd_info;		//������
	Tag_Wnd_Info		slave_wnd_info;			//������
}Inter_Screen_Info,*PINTER_SCREEN_INFO;
//������������Ļ��Ϣ
typedef struct TAG_INTER_SCREEN_CAPTION
{
	TCHAR default_info[256];			//Ĭ����Ļ
	TCHAR ad_info[256];					//�����Ļ
	TCHAR activity_info[256];			//���Ļ
	TCHAR program_info[256];			//��Ŀ��Ļ
	TCHAR challenge_star_info[256];		//��ս����Ļ
	TCHAR across_pass_info[256];		//����ά��Ļ
}INTER_SCREEN_CAPTION,*P_INTER_SCREEN_CAPTION;
/*******************************************************/


//��Ƶ�㳡�ṹ��
typedef struct st_video_show{
	TCHAR uid[MAX_PATH];
	TCHAR picpath[MAX_PATH];
	TCHAR title[1024*10];
	TCHAR toproomid[MAX_PATH];
	TCHAR roomid[MAX_PATH];
	TCHAR popularity[MAX_PATH];
	TCHAR showroomid[MAX_PATH];
	TCHAR channelname[MAX_PATH];
	st_video_show(){
		ZeroMemory(uid, MAX_PATH);
		ZeroMemory(picpath, MAX_PATH);
		ZeroMemory(title, 1024*10);
		ZeroMemory(toproomid, MAX_PATH);
		ZeroMemory(roomid, MAX_PATH);
		ZeroMemory(popularity, MAX_PATH);
		ZeroMemory(showroomid, MAX_PATH);
		ZeroMemory(channelname, MAX_PATH);
	}
}ST_VIDEO_SHOW;

struct FtpFile {
	const char *filename;
	FILE *stream;
};

#define INTER_GAME_PEOPLE_NUMBER			6				//������Ϸ�����������
// ������Ϸ��Ա��Ϣ
typedef struct TAG_GAME_PLAYER_INFO
{
	TCHAR szOpenId[256];				//΢���û���Ψһ��ʶ
	TCHAR szNickName[256];				//΢���ǳ�
	TCHAR szHeadImgUrl[256];		//ͷ��ͼƬ������·��
	TCHAR szHeadImgPath[256];		//ͷ��ͼƬ����·��
	bool bIsLaunch;					//�Ƿ��Ƿ�����
	bool bIsSelf;					//�Ƿ���ҡ����
	TCHAR szOpenTime[256];			//����ʱ��
}GAME_PLAYER_INFO,*P_GAME_PLAYER_INFO;

//��Ļ���Σ���ʹ�õĽṹ��
typedef struct tag_barrage_msg
{
	CWnd *pWnd;
	char szData[20480];
}BARRAGE_MSG, *LPBARRAGE_MSG;

//���յ�iis�����ݣ�תΪinfo
typedef struct tag_barrage_info
{
	wstring strGUID;
	wstring strWechatNickName;	//΢���ǳ�
	wstring strWechatHeadPath;	//ͷ��·��
	wstring strWechatHeadName;	//΢��ͷ������
	wstring strContent;			//����
	wstring strIp;				//��ԴIP
	wstring strColor;			//��ɫ
	int nSpeed;					//�ٶ�
	int nSize;					//�ֺ�
	int nCount;					//����
	std::map<wstring,wstring> keyImageMap;//����<���ƣ�·��>
}BARRAGE_INFO, *LPBARRAGE_INFO;

//�����������ͽṹ��
typedef struct tag_wechat_message{
	char guid[128];			//Ψһ����
	char filename[128];		//�ļ���
	char openid[64];	//΢��id
	char nickname[64];	//΢���ǳ�
	long num;			//�����  8:������Ϣ 9:���ħ�����飩��Ϣ 13:��Ƭ������Ϣ
	long notice_type;	//֪ͨ��Ϣ���� 0:��Ҫ���ز���ʾ���� 1:�����������  2:����ʧ��
	char url[256];		//��ת�����������ص�ַ������������ת�������ϵ�ַ
	char filepath[256];		//�ļ����ر���·��(��Ӧfilename)
	char portrait[256]; //΢��ͷ��
	char portraitpath[256];	//΢��ͷ�񱾵ر���·��
	CWnd *pWnd;			//���
	tag_wechat_message()
	{
		memset(guid, 0x00, sizeof(guid));
		memset(filename, 0x00, sizeof(filename));
		memset(openid, 0x00, sizeof(openid));
		memset(nickname, 0x00, sizeof(nickname));
		num = -1;
		notice_type = -1;
		memset(url, 0x00, sizeof(url));
		memset(filepath, 0x00, sizeof(filepath));
		memset(portrait, 0x00, sizeof(portrait));
		memset(portraitpath, 0x00, sizeof(portraitpath));
	}
}WECHAT_MESSAGE, *LPWECHAT_MESSAGE;

typedef  struct tagDownProfile{
	unsigned int head;/*ָ��ͷ0xaa55aa55*/
	unsigned int order;/*ָ��0x00000001*/
	long long int total;/*�ļ��ܴ�С*/
	long long int done;/*�Ѿ�������ɵ�*/
	int speed;/*�����ٶ�*/
	char name[256];/*�����ļ�������*/
} DOWNPROFILE;

typedef enum en_wechat_type{
	WECHAT_ANIMATION = 8,	//����
	WECHAT_GIFT = 9,		//ħ������
	WECHAT_PICTURE = 13		//��Ƭ����
};

typedef enum en_wechat_return_type{
	WECHAT_RET_OK = 0,		//�����Ѿ�׼�����ˣ����ز�չʾ
	WECHAT_RET_NOTICE = 1,	//������֪ͨ����Ҫ�ڵ���������ʾ
	WECHAT_RET_ERROR = 2	//����û��׼���ã����ˣ���ʾ����ʧ�ܰ�
};

//*******************************�����Ӱ����
#define HEAD_FLAG 0xaa55aa55
//��Ϣ����
typedef enum enMovieMsgType{
	//������Ϣ���� ʹ�ô�����ʱ��ֻ��ʹ��enMovieMsgContent mmc��mmc ������Ч, mssm������Ч��˫���ͣ����ϵͳ->��Ӱϵͳ or ��Ӱϵͳ->���ϵͳ����
	MMT_DIAITAL_MSG,
	//��Ϣϵͳ���� ʹ�ô�����ʱ��ֻ��ʹ��MOVIE_SHOW_SYSTEM_MSG mssm��mmc ������Ч, mssm������Ч��������(���ϵͳ->��Ӱϵͳ)��
	MMT_CHARACTER_MSG
};
//������Ϣ����
typedef enum enMovieMsgContent{
	MMCMSG_DEFAULT,			//Ĭ����Ϣ ��Ч��Ϣ��ֻ��ΪĬ��ֵ
	MMCMSG_OPEN_ROOM,		//����
	MMCMSG_CLOSE_ROOM,		//�ط�
	MMCMSG_SERIVCES,		//����
	MMCMSG_SHOW,			//������ʾ
	MMCMSG_HIDE,			//��������
	MMSMSG_LIGHT_OPEN,		//�ƹ�ȫ��
	MMSMSG_LIGHT_CLOSE,		//�ƹ�ȫ��
};
//��Ϣϵͳ����
typedef struct tag_MovieShowSystemMsg{
	TCHAR szMsgType[16];		//���桢ף���ʡ�Ѱ�����¡�����Ԥ�桢������Ӧ���𾯡��˾�
	TCHAR szShowMode[16];		//��������ʾ�����������ʾ��ͬʱ��ʾ
	TCHAR szContentType[16];	//���֡�ͼƬ����Ƶ��ͼƬ�����֡���Ƶ������
	TCHAR szTextColor[16];		//��ɫ����ɫ����ɫ����ɫ����ɫ����ɫ
	int iScrollCount;			//��������
	TCHAR szContent[2048];		//��Ϣϵͳ��Ϣ����
}MOVIE_SHOW_SYSTEM_MSG, *LPMOVIE_SHOW_SYSTEM_MSG;
//���͸���Ӱ����Ϣ
typedef struct tag_MovieMsgControl
{
	unsigned int head;					//ָ��ͷ0xaa55aa55
	enMovieMsgType mmt;					//��Ϣ����
	enMovieMsgContent mmc;				//������Ϣ����
	MOVIE_SHOW_SYSTEM_MSG mssm;			//��Ϣϵͳ����
}MOVIE_MSG_CONTROL, *LPMOVIE_MSG_CONTROL;

typedef struct tag_FlashMovieMsg{
	CWnd *pWnd;
	MOVIE_MSG_CONTROL lpMMControl;
}FLASHMOVIEMSG, *LPFLASHMOVIEMSG;
////////////////////////////////////*/

#define RECORDER_AUDIO_MIN_FILE_SIZE        4*1204*1024   //¼���ļ����Իطŵ���С�ļ���С
#define MEMBER_MAX_SONG_COUNT               150           //��Ա���������ĸ�����
#define HANDWRITING_ASSOCIATION_WORD_COUNT  100           //��д�����ֵĸ���
#define SURVEY_QUESTION_MAX_COUNT           10            //�������������
#define SURVER_SUGGESTION_MAX_WORD_COUNT    100           //��д������������
#define SLAVE_COMPUTER_MAX_COUNT            8             //���ػ������
#define TV_CHANNEL_COUNT                    8             //����Ƶ����
#define SAMPLE_NUMBER_PER_READ              8192          //ÿ�ζ�ȡ�Ĳ�����
#define MAX_MAIBA_PK_COUNT                  90            //���pK������
#define MAIBA_RULE_COUNT                    6             //��Թ�������
#define MAIBA_HEIGHT_RANKING_LIST           48

const double PLAY_VIDEO_MIN_TIME_LENGTH = 3.0;            //������Ƶ����Сʱ�䳤��
const double AVOID_CUT_MIN_TIME_LENGTH  = 0.4;            //ȫ�ַ�ֹƵ���л�����Сʱ�䳤��
const double PREVIEW_CONTROL_MIN_TIME_LENGTH = 2.0;       //Ԥ�����Ƶ���Сʱ�䳤��
const double UPLOAD_DB_TIME_INTERVAL    = 6666.0;         //�ϴ����ݿ��ʱ����
const double LOAD_BALANCE_TIME_INTERVAL = 240.0;          //���ؾ������Сʱ����

#define RECOMMAND_SONG_INFO_COUNT           10            //�Ƽ������ĸ���

#define SURVER_QUESTION_COUNT             5               //���ӵ���������
#define CUSTOM_SONG_COUNT                 11               //���Ƹ���

#define MEMBER_LOGIN_COUNT                5				  //��Ա��¼����


//���ڸð汾û�У������
#define DM_POSITION                      0x00000020L

//ʵʱƵ�׵Ķ���ֵ
#define SPECTRUM_MAX_COUNT 120
#define SPECTRUM_MAX_VALUE 10000

#define UDP_PROGREES_RADIO			28010					/*UDP�㲥���ؽ���*/

#endif
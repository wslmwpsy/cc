#ifndef _PAGEDATA_H_
#define _PAGEDATA_H_



//������ö����ı䣬ҲҪ��Ӧ�ĸı�PageVariable.h�е�page_call_para[]����
enum FLASH_PAGE_CODE
{
	page_homepage=0,     //��ҳ
	page_title,          //�������
	page_singer,         //���ǵ��
	page_lyric,          //��ʵ��
	page_theme,          //������
	page_top_song,       //��������
	page_new_song,       //�¸��Ƽ�
	page_opera,          //����Ϸ��
	page_assist,         //��������
	page_introduce,      //��������
	page_selected,       //��ѡ����
	page_singed,         //�ѳ�����
	page_game,           //������Ϸ
	page_movie,          //��Ӱ����
	page_recording,      //¼������
	page_video,          //��Ƶת��
	page_U_disk,         //U�̲���
	page_proposal,       //�������
	page_member_manager, //��Ա����
	page_member_song,    //��Ա����
	page_painting,       //�滭
	page_system_manager, //ϵͳ����
	page_preview,        //Ԥ����Ƶ
	page_singer_song,    //������ǵĸ����б�ҳ��
	page_screen_show,    //����ҳ��   û��ʹ��
	page_change_skin,    //����ҳ��
	page_system_info,    //ϵͳ��Ϣ
	page_class,          //�����裬���ɵ�����
	page_language,       //���ֵ��
	page_movie_song,     //Ӱ�ӽ���
	page_era_song,       //�������
	page_number_song,    //��ŵ��
	page_custom_singer,  //�ͻ��Զ���ĸ���
	page_earth,          //����ҳ��
	page_drinks,         //��ˮ
	page_secondary_song, //��������ҳ��
	page_search_song,    //�Ѹ�ҳ��
	page_write,          //��д���
	page_theme_song,     //�������
	page_movieMeun,      //��Ӱ����ҳ��
	page_place_video,    //������Ƶ
	page_concert,        //�ݳ���
	page_ktvExplain,     //��������
	page_room,           //����ʹ���ֲ�
	page_fire,           //����ͼ��
	page_guide,          //����ָ��
	page_pk_manager,   //pk��¼
	page_pk,           //pk����ҳ��
	page_pk_receive,     //pk��������ҳ��
	page_pkjx,          //pk��ѡ
	page_encode,        //�ƶ����
	page_custom_song,  //���Ƹ���
	page_karaoke_home, //����OK��ҳ
	page_word_count,   //�������
	page_jewel_box,      //�ٱ���
	page_hdmi,           //����ר��
	page_kalaok_pk,		 //���pk
	page_kala_share,     //K�����
	page_dekaron_maiba,  //��ս���
	page_find_maiba,	 //�������
	page_help,            //
	page_maiba_login,    //��Ե�¼��ע��
	page_consumer,        //���Ѳ�ѯ
	page_wechat,		  //΢�ŵ��
	page_maiba_register,  //���ע��
	page_home_song,       //��ҳ�ĵ㲥����
	page_enterainment, //��ҳ�����ֻ���
	page_place_raiders, //��ҳ�ĳ�����
	page_aider_function, //��ҳ�ĸ�������
	page_fast_songs_slow_dance, //��������
	page_music_enjoy, //��������
	page_home_theme_song, //��ҳ������
	page_baidu_music, //�ٶ�����
	page_qq_music, //QQ����
	page_kugou_music, //�ṷ����
	page_kuwo_music, //��������
	page_yule_news, //��������
	page_language_change, //�����л�
	page_video_dating,	//��Ƶ����
	page_singing_contest, //�ݳ�����
	page_sb_ranking_polite, //��Ҫ�μ�-�ϰ�����
	page_sb_free_pk,		//��Ҫ�μ�-����PK
	page_sb_challenge_pk,	//��Ҫ�μ�-��̨PK
	page_free_pk_view_list,			//�鿴�� - ����PK
	page_challenge_pk_view_list, //�鿴�� - ��̨PK
	page_new_theme_song,		//���������
	page_close_clear_msg,		//�ط�ʱ�������������
	page_voice_china,       //�й�������
	page_yunadd_song,		//�ƼӸ����ҳ��
	page_phone_push,		//�ֻ�����
	page_phone_push_preview, //�ֻ�����Ԥ��
	page_movie_detail,       //��Ӱ����ҳ
	page_voice_china_singer,  //����������ʾ����
	page_trend_list,		//������ҳ��
	page_challenge_star,					//��ս��
	page_across_pass,				//����ά�����ضᱦ��
	page_video_show,			//��Ƶ�㳡
	page_listen_knowledge_song, //����ʶ��
	page_picture_mv,			//��Ƭmv
	page_active_game,			//������Ϸ
	page_entertainment_programme,			//���ֽ�Ŀ
	page_wechat_barrage,			//΢�Ż���-��Ļ

	PAGE_MAX_NUMBER,     //���ҳ��
};

enum FLASH_SEND_FUNCTION_CODE
{
	//���ټ����Ĺ���

	//����
	//����Ƶ�������ص�����
	RETURN_SELECT_SONG=10, 

	//��ҳ
	PAGE_UP  =60,      //��һҳ
	PAGE_DOWN=61,      //��һҳ
	PAGE_BACK=63,      //ҳ�淵��
	
	//���з���
	CALL_ATTENDANT         =100, //���з���Ա
	CALL_PR_MANAGER        =101, //���ؾ���
	CALL_ACOUSTICS_ENGINEER=102, //����ʦ
	CALL_CLEANER           =103, //����Ա
	CALL_DUTY_MANAGER      =104, //ֵ�ྭ��
	CALL_ORDER_DINNER      =105, //���
	CALL_CUP               =106, //����
	CALL_PAY_MONEY         =107, //��
	CALL_CONSULTION        =108, //��ѯ
	CALL_CANCEL            =115, //ȡ�����з���

	//�������ƹ���
	SONG_NEXT       =120,        //��һ��
	SONG_REPLAY     =121,        //�س�
	SONG_PREVIOUS   =122,        //��һ��
	SONG_ACCOMPANY_ORIGINAL=123, //�鳪��ԭ��
	SONG_PLAY_PAUSE =124,        //���Ż���ͣ
	SONG_MUTE_UNMUTE=125,        //����/ȡ������
	SONG_ENJOYMERT  =127,        //����
	SONG_ORIGINAL   =128,        //ԭ��
	SONG_ACCOMPANY  =129,        //�鳪
	SONG_PLAY       =130,        //����
	SONG_PAUSE      =131,        //��ͣ
	SONG_MUTE       =132,        //����
	SONG_UNMUTE     =133,        //ȡ������


	//����
	MUSIC_VOLUME_UP       =140,  //���ֵ�������
	MUSIC_VOLUME_DOWN     =141,  //���ֵ�������
	MICROPHONE_VOLUME_UP  =142,  //��˷��������
	MICROPHONE_VOLUME_DOWN=143,  //��˷��������
	TUNE_UP               =144,  //������
	TUNE_DOWN             =145,  //������
	TUNE_ORIGINAL         =146,  //ԭ��
	REVERBERATION_DOWN    =147,  //�����
	REVERBERATION_UP      =148,  //�����

	//����
	ATMOSPHERE_APPLAUSE   =160,  //����
	ATMOSPHERE_CHEER      =161,  //����
	ATMOSPHERE_OUTCRY     =162,  //����
	ATMOSPHERE_WHISTLE    =163,  //��

	//��Ч
	AUDIO_EFFECT_STANDARD    =170,  //��׼
	AUDIO_EFFECT_THEATER     =171,  //�糡
	AUDIO_EFFECT_PROFESSIONAL=172,  //����
	AUDIO_EFFECT_MAGIC       =173,  //ħ��
	AUDIO_EFFECT_RESERVE1    =174,  //Ԥ�� �Զ�
	AUDIO_EFFECT_RESERVE2    =175,  //Ԥ��
	AUDIO_EFFECT_RESERVE3    =176,  //Ԥ��
	AUDIO_EFFECT_RESERVE4    =177,  //Ԥ��

	//������
	ENVIRONMENT_AUDIO_CLOSE  =180,  //�رջ�����
	ENVIRONMENT_AUDIO_MEETING=181,  //����
	ENVIRONMENT_AUDIO_AIRPORT=182,  //�ɻ���
	ENVIRONMENT_AUDIO_ROAD   =183,  //��·��
	ENVIRONMENT_AUDIO_STATION=184,  //��վ
	ENVIRONMENT_AUDIO_MAHJONG=185,  //�齫
	ENVIRONMENT_AUDIO_RAIN   =186,  //������
	
	//�ƹ�
	LIGHT_OPEN               =189,  //�ƹ�
	LIGHT_CLOSE              =190,  //�ƹ� �ر�
	LIGHT_STANDARD           =191,  //�ƹ� ��׼
	LIGHT_BACKGROUND         =192,  //�ƹ� ����
	LIGHT_STAGE              =193,  //�ƹ� ��̨
	LIGHT_SCINTILLATION      =194,  //�ƹ� ����
	LIGHT_OPEN1              =195,   //�ƹ�1
	LIGHT_OPEN2              =196,   //�ƹ�2
	LIGHT_OPEN3              =197,   //�ƹ�3
	LIGHT_OPEN4              =198,   //�ƹ�4
	LIGHT_OPEN5              =199,   //�ƹ�5
	LIGHT_OPEN6              =200,   //�ƹ�6
	LIGHT_OPEN7              =201,   //�ƹ�7
	LIGHT_OPEN8              =202,   //�ƹ�8

	ATMOSPHERE_DRUM_KIT_LEFT_FRUM1   =220,   //��һ��
	ATMOSPHERE_DRUM_KIT_LEFT_FRUM2   =221,   //�����
	ATMOSPHERE_DRUM_KIT_MIDDLE_FRUM  =222,   //�м�Ĺ�
	ATMOSPHERE_DRUM_KIT_RIGHT_FRUM2  =223,   //�Ҷ���
	ATMOSPHERE_DRUM_KIT_RIGHT_FRUM1  =224,   //��һ��
	ATMOSPHERE_DRUM_KIT_PRE_FRUM     =225,   //ǰ���
	ATMOSPHERE_DRUM_KIT_LEFT_CYMBAL1 =226,   //��һ��
	ATMOSPHERE_DRUM_KIT_LEFT_CYMBAL2 =227,   //�����
	ATMOSPHERE_DRUM_KIT_RIGHT_CYMBAL2=228,   //�Ҷ���
	ATMOSPHERE_DRUM_KIT_RIGHT_CYMBAL1=229,   //��һ��

	ATMOSPHERE_PIANO_BLACK1 =330,       //���ٺڼ������𣬹�15����
	ATMOSPHERE_PIANO_BLACK2 =331,
	ATMOSPHERE_PIANO_BLACK3 =332,
	ATMOSPHERE_PIANO_BLACK4 =333,
	ATMOSPHERE_PIANO_BLACK5 =334,
	ATMOSPHERE_PIANO_BLACK6 =335,
	ATMOSPHERE_PIANO_BLACK7 =336,
	ATMOSPHERE_PIANO_BLACK8 =337,
	ATMOSPHERE_PIANO_BLACK9 =338,
	ATMOSPHERE_PIANO_BLACK10=339,
	ATMOSPHERE_PIANO_BLACK11=340,
	ATMOSPHERE_PIANO_BLACK12=341,
	ATMOSPHERE_PIANO_BLACK13=342,
	ATMOSPHERE_PIANO_BLACK14=343,
	ATMOSPHERE_PIANO_BLACK15=344,

	ATMOSPHERE_PIANO_WHITE1 =345, //���ٰ׼������𣬹�21����
	ATMOSPHERE_PIANO_WHITE2 =346,
	ATMOSPHERE_PIANO_WHITE3 =347,
	ATMOSPHERE_PIANO_WHITE4 =348,
	ATMOSPHERE_PIANO_WHITE5 =349,
	ATMOSPHERE_PIANO_WHITE6 =350,
	ATMOSPHERE_PIANO_WHITE7 =351,
	ATMOSPHERE_PIANO_WHITE8 =352,
	ATMOSPHERE_PIANO_WHITE9 =353,
	ATMOSPHERE_PIANO_WHITE10=354,
	ATMOSPHERE_PIANO_WHITE11=355,
	ATMOSPHERE_PIANO_WHITE12=356,
	ATMOSPHERE_PIANO_WHITE13=357,
	ATMOSPHERE_PIANO_WHITE14=358,
	ATMOSPHERE_PIANO_WHITE15=359,
	ATMOSPHERE_PIANO_WHITE16=360,
	ATMOSPHERE_PIANO_WHITE17=361,
	ATMOSPHERE_PIANO_WHITE18=362,
	ATMOSPHERE_PIANO_WHITE19=363,
	ATMOSPHERE_PIANO_WHITE20=364,
	ATMOSPHERE_PIANO_WHITE21=365,

	ATMOSPHERE_MARACAS      =390,         //ɳ��
	ATMOSPHERE_HANDBELL     =391,         //����
	ATMOSPHERE_DRUM         =392,         //��
	LYRIC_LINK = 400,                     //��ʽ���

	//�յ��ŷ�
	AIR_CONDITION_STRONG   =422,          //�յ�ǿ
	AIR_CONDITION_MID      =421,          //�յ���
	AIR_CONDITION_WEAK     =420,          //�յ���

	AIR_CONDITION_CLOSE    =430,          //�յ��ر�

	DISCHARGE_AIR_FUNCTION =440,          //�ŷ�


	SHOW_DRAW_IMAG         =460,          //��ʾ���Ƶ�ͼƬ

	ENTER_GUIDE_SONG       =500,          //���뵼�������ɰ��ࣩ
	EXIT_GUIDE_SONG        =501,          //�˳�����



	OPEN_SCORE             =510,          //������
	CLOSE_SCORE            =511,          //�ر�����

	//�»���
	ATMOSPHERE_HAOZAN =531, //����
	ATMOSPHERE_SHIHUA =532, //ʯ��
	ATMOSPHERE_XIANHUA =533,//�׻�
	ATMOSPHERE_TUXUE =534, //��Ѫ
	ATMOSPHERE_FEIWEN =535, //����
	ATMOSPHERE_XINSUI =536, //����
	ATMOSPHERE_HAIXIU =537, //����
	ATMOSPHERE_ZADAN =538, //�ҵ�


	//��Ч
	MUSIC_SOUND_STANDARD    = 550,  //������Ч��׼
	MUSIC_SOUND_THEATER     = 551,  //������Ч�糡
	MUSIC_SOUND_PROFESSIONAL= 552,  //������Ч����
	MUSIC_SOUND_MAGIC       = 553,  //������Чħ��
	MUSIC_SOUND_RESERVE1    = 554,  //������Ч�Զ�
	MUSIC_SOUND_RESERVE2    = 555,  //������ЧԤ��
	MUSIC_SOUND_RESERVE3    = 556,  //������ЧԤ��
	MUSIC_SOUND_RESERVE4    = 557,  //������ЧԤ��

	LIGHT_AUTO_SWITCH		= 600,

	/**
	*
	* 700 - 799 ��ռ�ã��мǡ���ƽ̨΢����Ҫ������
	*
	**/
	MUSIC_VOLUME_MIN = 700,
	MUSIC_VOLUME_MAX = 799,
};

//flash���͵ĵƹ����
enum FLASH_SEND_LIGHT_CODE
{
	FLASH_SEND_LIGHT1,               //�ƹ�1
	FLASH_SEND_LIGHT2,               //�ƹ�2
	FLASH_SEND_LIGHT3,               //�ƹ�3
	FLASH_SEND_LIGHT4,               //�ƹ�4
	FLASH_SEND_LIGHT5,               //�ƹ�5
	FLASH_SEND_LIGHT6,               //�ƹ�6
	FLASH_SEND_LIGHT_STANDARD,       //�ƹ� ��׼
	FLASH_SEND_LIGHT_BACKGROUND,     //�ƹ� ����
	FLASH_SEND_LIGHT_STAGE,          //�ƹ� ��̨
	FLASH_SEND_LIGHT_SCINTILLATION,  //�ƹ� ����
	FLASH_SEND_LIGHT_CLOSE,          //�ƹ� �ر�
	FLASH_SEND_LIGHT_OPEN,           //�ƹ� ��
	FLASH_SEND_LIGHT7,               //�ƹ�7
	FLASH_SEND_LIGHT8,               //�ƹ�8
};

//������
enum FLASH_SEND_ENVIRONMENT_AUDIO_CODE
{
	FLASH_SEND_ENVIRONMENT_AUDIO_CLOSE,  //�رջ�����
	FLASH_SEND_ENVIRONMENT_AUDIO_MEETING,  //����
	FLASH_SEND_ENVIRONMENT_AUDIO_AIRPORT,  //�ɻ���
	FLASH_SEND_ENVIRONMENT_AUDIO_ROAD,     //��·��
	FLASH_SEND_ENVIRONMENT_AUDIO_STATION,  //��վ
	FLASH_SEND_ENVIRONMENT_AUDIO_MAHJONG,  //�齫
	FLASH_SEND_ENVIRONMENT_AUDIO_RAIN,     //������
};

//¼������
enum FLASH_SEND_TAPE_CODE
{
	FLASH_SEND_TAPE_START=1,         //��ʼ¼��
	FLASH_SEND_TAPE_STOP=2,          //ֹͣ¼��
	FLASH_SEND_TAPE_REPLAY=3,        //¼���ط�
};

#endif
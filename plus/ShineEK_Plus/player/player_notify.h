#ifndef _INCLUDE_PLAYER_NOFITY_H
#define _INCLUDE_PLAYER_NOFITY_H


enum PLAYER_NOTIFY
{
	PN_MEDIA_OPENED_SUCCEED,	// ���ļ��ɹ�
	PN_MEDIA_OPENED_FAILED,		// ���ļ�ʧ��

	PN_MEDIA_PLAY_FROZEN,		// ���ſ���
	PN_MEDIA_PLAY_FINISHED,		// �ļ��������

	PN_TV_AUTOTUNE_DONE = 200,	// ���ӿ��Զ�Ѱ̨���, LPARAM = ��Ч̨��

	PN_SRV_RESTARTED    = 300,	// ���ŷ�������
	PN_LYRIC_SCORE      = 400,	// ��������
	PN_LYRIC_SCORE_DONE = 401,	// �������
	PN_LYRIC_SENTENCE   = 402,	// �����ļ�����
	PN_LYRIC_REALTIME_SCORE = 403,	// ʵʱ����
	PN_LYRIC_FIRST_SENTENCE = 404,	// ������ʼ���ŵ�һ��, LPARAM = ��ǰ���Ž���(����)

 	PN_SPECTRUM			= 500,	// ����Ƶ����Ϣ, LPARAM = Ƶ�����ݻ�����ָ��(BYTE����)
};

//
// ������֪ͨ��Ϣ, WPARAM = PLAYER_NOTIFY
//
#define WM_PLAYER_NOTIFY	(WM_APP + 132)

//
// Ԥ��(��������)֪ͨ��Ϣ, WPARAM = PLAYER_NOTIFY
//
#define WM_PREVIEW_NOTIFY	(WM_APP + 133)

//
// ���ӿ�֪ͨ��Ϣ, WPARAM = PLAYER_NOTIFY
//
#define WM_TVCARD_NOTIFY	(WM_APP + 134)

//
// OSD ���󲥷����֪ͨ��Ϣ
// WPARAM ��16 λ= OSD �����
// LPARAM = LoadBmpFile / LoadText ���ص�OSD ����
//
#define WM_OSD_PLAY_DONE    (WM_APP + 135)

// �ڶ�̨���Ӳ��ź���( CSecondTV )֪ͨ��Ϣ
//
#define WM_SECTV_NOTIFY			(WM_APP + 262)

//
// ��������ǰ״̬
//
enum PlayerState
{
	PLAYER_STATE_ERROR	    = 0xFFFF,	// ��ʽ��

	PLAYER_STATE_INIT	    = 0x0000,	// ��ʼ״̬

	PLAYER_STATE_PAUSED	    = 0x0001,	// ��ͣ
	PLAYER_STATE_STOPPED	= 0x0002,	// �������ֹͣ
	PLAYER_STATE_PLAYING	= 0x0004,	// ���ڲ���
	PLAYER_STATE_SEEKING	= 0x0008,
	PLAYER_STATE_STEPPING	= 0x0010,
	PLAYER_STATE_CLOSED  	= 0x0020,	// �ر�

	PLAYER_STATE_OPENING    = 0x0040,   // ���ڴ��ļ�
	PLAYER_STATE_OPENED     = 0x0080,   // ���ļ����
	PLAYER_STATE_WAITING	= 0x0100,	// ���ڵȴ����ļ�

	PLAYER_STATE_READY	= PLAYER_STATE_PAUSED | PLAYER_STATE_STOPPED,
};


//
// ���ź��Ŀ��ƴ���( Get Set )
//
enum PCORE_CONTROL
{
	SDI_AUDIOCOUNTS        = 100,	// �������� (read only)

	SDI_AUDIOINDEX         = 101,	// ��ǰ��Ƶ�����

	SD_VOLUME              = 102,	// ������С

	SD_BALANCE             = 103,	// ����ƽ��, left: -100, center: 0, right: 100

	SD_TIME_FORMAT         = 104,	// ʱ���ʽ SD_TIME_FORMAT_VAL, (֡���롢�ֽ�...)

	SD_PLAY_STATE          = 106,	// ��������ǰ״̬ (read only)

	SD_DISPLAY_TARGET      = 107,	// ��Ƶ��� SD_DISPLAY_TARGET_VAL

	SD_DISPLAY_SIZE        = 108,	// ��Ƶ��ʾ��С

	SD_VIDEO_BRIGHTNESS    = 109,	// ����

	SD_VIDEO_CONTRAST      = 110,	// �Աȶ�

	SD_VIDEO_SATURATION    = 111,	// ���Ͷ�

	SDI_AUDIO_OUTPUT_TYPE  = 112,	// ��Ƶ������� (DIGITAL_AUDIO, AC3_AUDIO, PCM_AUDIO)

	SDI_AUDIO_OUTPUT_MODE  = 113,	// ��Ƶ�����ʽ (RIGHT_ONLY, LEFT_ONLY, STEREO)

	SD_FILE_TYPE           = 114,	// ��ȡ�ļ����� (SD_FILE_TYPE_VAL, read only)

	SD_CLIP_LENGTH         = 115,	// ý����ʱ�� (��λ: ��, read only)

	SD_POSITION            = 116,	// ��ǰ����λ�� (��λ: ��)

	SD_PERCENT             = 117,   // ��ǰ������ɵİٷֱ� ( 0 - 100, read only )

	SD_TVSTANDARD_FALG     = 200,	// ��������Ƶ�����ʽ (SD_TVSTANDARD_FALG_VAL)

	SD_SIGMAOUT_TARGET     = 201,	// ���������Ŀ�� ( Ĭ��TV )
	// 0 = TV, 1 = VGA

	SD_SIGMAOUT_CONNECTOR  = 202,	// �����������ͷ ( Ĭ�ϸ��϶��� )
	// 0 = ���϶���, 1 = YUV, 2 = RGB

	SD_SILENT_DB           = 260,	// ��С�������������ֱ���(0 - 80, Ĭ��60)

	SD_DEINTERLACE_ONOFF   = 261,	// �Ƿ����ⷴ������(CPU ռ���ʻ�����)

	SD_DBG_LOG_PTRF        = 262,	// ���õ�����Ϣ���պ���ָ��

	SD_DBG_LOG_FILE        = 263,   // ������Ϣ�Ƿ�������ļ�(0 = �����, 1 = ���)

	SD_ALWAYS_DSHOW        = 264,	// ʼ��ʹ��dshow ���Ĳ���(0 = �Զ�ѡ�񲥷ź���, 1 = ʼ��ʹ��dshow)

	SD_EQ_ACTIVE           = 265,	// �Ƿ�������Ƶ������(0 = ������, 1 = ����)

	SD_RD_EQ_PARAMS        = 266,	// ��ȡ��Ƶ����������

	SD_WT_EQ_PARAMS        = 267,	// ������Ƶ����������

	SD_DETACHED_PROCESS    = 268,	// �Ƿ��Ƕ����Ĳ��Ž���(1 = ��, 0 = ��, read only)

	SD_OSD_SWAPPER         = 269,	// OSD �����Ϣ������ָ��( read only )

	SD_PLAYSRV_HWND        = 270,	// �������Ž��̵Ŀ��ƴ��ھ��( read only )

	SD_SLAVE_VIDEO_HWND    = 271,	// �㳪̨��Ƶ���ھ��

	SD_PREVIEW_AUDIO_ONOFF = 272,	// ����Ԥ���Ƿ��������

	SD_CPU_IS_SLOW         = 273,	// �Ƿ��������ڵ����û�����

	SD_GET_AUDIO_INDEX     = 274,	// ��ȡ��Ч��������( read only )

	SD_OSD_ON_SLAVE_WND    = 275,	// ���ݳ�̨����ʾOSD

	SD_DISP_VIDEO_HWND     = 300,	// ��ʾ����������Ƶ��ʾ���ھ��

	SD_DISP_VIDEO_SHOW     = 301,	// ��ʾ��������ʾ����������Ƶ (0 = ����, 1 = ��ʾ)

	SD_DISP_VIDEO_ONOFF    = 302,	// �򿪻�ر������й��� ( 0 = �ر�, 1 = ��)

	SD_DUAL_OUTPUT_HWND    = 320,	// ���˫ͷ�����Ƶ���ھ��, NULL ��ʾ�ر�˫ͷ���( ����Ӳ�� )

	SD_WALL_PAD_HWND       = 330,	// ǽ�������Ƶ���ھ��

	// ��������
	SD_SECTV_VIDEO_HWND    = 400,	// �ڶ�̨���ӻ���ʾ��Ƶ���ھ��
	SD_SECTV_MEDIA_SOURCE  = 401,	// �ڶ�̨���ӻ����ŵ�ý��Դ
	SD_SECTV_AUDIO_ONOFF   = 402,	// ѡ��ǰ���������
	SD_SECTV_STOP          = 403,	// �ڶ�̨���ӻ�ֹͣ����

	SD_LEADING_AUDIOCARD   = 420,	// �����쳪��Ƶ�������
	SD_ORIGNAL_AUDIO       = 421,	// ԭ��������Ϣ
	SD_GUIDE_AUDIO         = 434,	// ���õ�������(������ͬSD_ORIGNAL_AUDIO)

	// ԭ��������1 ~ 9
	// ������ʱ����= 'L'
	// ������ʱ����= 'R'
	SD_SCORE_ONOFF         = 422,	// �򿪻�رմ�ֹ���
	SD_GET_SCORE           = 423,	// �õ���������

	SD_GUIDE_ONOFF         = 424,	// �򿪻�رյ�������(���ļ�ǰ������SD_ORIGNAL_AUDIO)
	SD_GUIDE_VOLUME        = 425,	// ��������(0 ~ 10, Ĭ��5)
	SD_SET_RECORD_DEVICE   = 428,	// ����¼���豸��(�����ý�����ϵͳĬ��)
	SD_SET_RECORD_FILE     = 429,	// ����¼���ļ���(OpenFile ǰ����)

	SD_SET_RECORD_CAP_FREQ  = 430,	// ����¼��������
	SD_SET_RECORD_SAVE_FREQ = 431,	// ����¼���ļ�������
	SD_SET_RECORD_PORT      = 432,	// ¼�����ݷ��Ͷ˿�
	SD_SET_SCORE_FILEPATH   = 433,	// ���������ļ������ļ���·��
	SD_SET_SCORE_LINE_ONOFF = 435,	// ������ر���������ʾ(0 = �ر�, 1 = ����)

	SD_SNAPSHOT             = 460,	// �Ե�ǰ������Ƶץͼ

	SD_CUT_BLACK_BORDER     = 461,	// �Ƿ��г���Ƶ�ڱ�

	// -- add by cai : ����ksc��ʺ�Ƶ��
	SD_SET_KSC_FILEPATH     = 480,	// ����ļ�·��
	SD_SET_KSC_FONT         = 481,  // �������(Ĭ������)
	SD_SET_KSC_TEXT_HEIGHT  = 482,	// ����ı��߶�(36-96, Ĭ��64, ��λ����)
	SD_SET_KSC_TEXT_BOLD    = 483,	// ����ı��Ƿ��ô���(Ĭ�Ϸ�)
	SD_SET_KSC_TEXT_Y_POS   = 484,	// ����ı���ֱλ��, �ӵײ�����(Ĭ��120)
	SD_SET_KSC_USE_OSD      = 485,	// �Ƿ���OSD ��ʾ���(Ĭ�Ϸ�, ʹ�ø��Ǵ���)
	SD_SET_KSC_LINE_MODE    = 486,	// ���ø����ģʽ(0 = �Զ�, 1 = ����, 2 = ˫��, Ĭ��0)
	SD_SET_KSC_COLOR_MODE   = 487,  // ���ø����ɫ(0 = �и���, 1 = Ů����)
	SD_SET_KSC_TEXT_X_POS   = 488,	// ����ı�ˮƽλ��(Ĭ��20)
	SD_SET_KSC_TEXT_WIDTH   = 489,	// ����ı��������(Ĭ�ϴ��ڿ��-2*KSC_TEXT_X_POS)

	SD_WP_SetFreSpectrumsitify_HWND = 550, //Ƶ�״��ھ��
	SD_WP_SetFreSpectrumsitify_Spec = 551, //���ô�С��
	SD_WP_ClearUpSinger        = 552,

	SD_SET_MTV_SAVEFILE    = 701,	// ����MTV ¼���ļ�ȫ·����

	// ��ǿ����
	SD_FULL_SIZE_OSD       = 1001,	// ���ȫ��OSD ����
	SD_PREFECT_MB          = 1002,	// �����ֽ��� (MB)
	SD_MUTE_SECONDS        = 1003,	// ���農������
	SD_LOG_DIRECTORY       = 1004,	// ��־�ļ�����Ŀ¼

	SD_FLASH_WAVE_ONOFF    = 1005,	// �򿪻�ر�flash ������� ( 0 = �ر�, 1 = ��)
	SD_DUAL_ROTATE_VIDEO   = 1007,	// �򿪻�ر������Ƶ��ת ( 0 = �ر�, 1 = ��)
	SD_DUMP_AUDIO          = 1008,	// ������Ƶ����(������, �ο�SD_ORIGNAL_AUDIO=�ļ���)

	SD_SET_SPECTRUM			= 1010,	// ����Ƶ�ײ������������Ƶ��(HIWORD = ��������, LOWORD = Ƶ��)

	//ʵʱ����
	SD_REALTIME_SCORE      = 1011,	// ������ر�ʵʱ���� ( 0 = �ر�, 1 = ��, Ĭ�Ϲر�)

	// ��Ƶ��ǿ
	SD_VIDENH_TRAYICON     = 1200,	// �Ƿ���ʾ֪ͨͼ��
	SD_VIDENH_ONOFF        = 1201,	// �򿪻�ر���Ƶ��ǿ
	SD_VIDENH_HALF_ONLY    = 1202,	// ֻ�����Ұ벿��
	SD_VIDENH_LUM          = 1203,	// ����(0 - 256, def = 128)
	SD_VIDENH_CONTRAST     = 1204,	// �Աȶ�(-256 - 256, def = 0)
	SD_VIDENH_HUE          = 1205,	// ɫ��(-180 - 180, def = 0)
	SD_VIDENH_SAT          = 1206,	// ���Ͷ�(0 - 128, def = 64)
	SD_VIDENH_GAMMA        = 1207,	// gamma(1 - 400, def = 100)
	SD_VIDENH_GAMMA_R      = 1208,	// red gamma(1 - 400, def = 100)
	SD_VIDENH_GAMMA_G      = 1209,	// green gamma(1 - 400, def = 100)
	SD_VIDENH_GAMMA_B      = 1210,	// blue gamma(1 - 400, def = 100)
};

enum SD_DISPLAY_TARGET_VAL
{
	SD_DISP_VGA            = 0,
	SD_DISP_TV             = 1,
};

enum SD_TIME_FORMAT_VAL
{
	SD_TIME_FORMAT_UNKNOWN = 0,
	SD_TIME_FORMAT_FRAME   = 1,
	SD_TIME_FORMAT_TIME    = 2,
	SD_TIME_FORMAT_BYTE    = 3,
	SD_TIME_FORMAT_SAMPLE  = 4,
};

enum SD_TVSTANDARD_FALG_VAL
{
	SD_TVSTANDARD_AUTO     = -1,
	SD_TVSTANDARD_NTSC     = 0,
	SD_TVSTANDARD_PAL      = 1,
	SD_TVSTANDARD_PAL60    = 2,
	SD_TVSTANDARD_PALN     = 3,
};

enum SD_FILE_TYPE_VAL
{
	SDF_UNKNOWN            =  -1,	// unknown
	SDF_DIVXFILE           = 200,	// Media type : divx file
	SDF_MPEG4              = 201,	// Media type : mpeg 4
	SDF_MP3                = 202,	// Media type : mp3
	SDF_MPEG1              = 203,	// Media type : mpeg1
	SDF_MPEG2              = 204,	// Media type : mpeg2
	SDF_DVD                = 205,	// Media type : DVD
	SDF_REAL               = 206,	// Media type : Real
	SDF_QT                 = 207,	// Media type : QuickTime
};


//
// Ԥ��(��������) ������
//
enum PREVIEW_CONTROL
{
	PVC_GET_DURATION,				// ��ȡ������ʱ��(��)
	PVC_GET_POSITION,				// ��ȡ��ǰ����λ��(��)
	PVC_GET_TONE,					// ��ȡ��ǰ��������

	PVC_SET_POSITION = 100,			// ���õ�ǰ����λ��(��)

	PVC_SET_INIT_AUDIO,				// ����Ԥ�����ŵ�����(��Ӳ�����ʱ����, ����Preview_Open ǰ���ò���Ч)
	// argv0 = 'L',   ԭ����������
	// argv0 = 'R',   ԭ����������
	// argv0 = 1 ~ 8, ԭ����ָ������(�����ݿ��еõ�)
	// argv0 = -1,    �������κ�����ֱ�Ӳ�����Ƶ(Ĭ��)

	PVC_SET_TONE,					// ����Ԥ����������

	PVC_SET_TVOUT,					// ����Ԥ����Ƶ�ڵ����������ʽ
	// argv0 = 0, ����������ӻ�
	// argv0 = 1, ��������ӻ�
	// argv0 = 2, ͨ�����л���ʽ���������
};


//
// ���ӿ�������
//
enum TV_CONTROL
{
	TVC_GET_CHANNEL,				// ��ȡ��ǰƵ��
	TVC_GET_TVOUT,					// ��ȡ��ǰ��������豸, ����LONG
	//  HIWORD(r) = 0, û�����������
	//  HIWORD(r) = 1, ���������
	//  HIWORD(r) = 2, ͨ�����л���ʽ���������
	//  LOWORD(r) = 0, û���������ʾ��
	//  LOWORD(r) = 1, �������ʾ����Ƶ����
	TVC_GET_DISP_HWND,				// ��ȡ���������Ƶ���ھ��


	TVC_SET_CHANNEL = 100,			// ���õ�ǰƵ��, ���ص�ǰ��Ƶ����
	TVC_SET_CHL_INCREASE,			// ��ǰƵ����һ, ���ص�ǰ��Ƶ����
	TVC_SET_CHL_DECREASE,			// ��ǰƵ����һ, ���ص�ǰ��Ƶ����
	TVC_SET_AUTOTUNE,				// �Զ�Ѱ̨
	TVC_SET_PHYSCONN,				// �����������(PhysicalConnectorType of strmif.h)

	TVC_SET_DISP_HWND,				// ������ʾ�������Ƶ���ھ��(�ڴ򿪵��ӿ�ǰ����)

	TVC_SET_TVOUT,					// ���õ��ӿ��ź����Ŀ��
	// argv0 = 0, ����������ӻ�
	// argv0 = 1, ��������ӻ�
	// argv0 = 2, ͨ�����л���ʽ���������
	// argv1 = 0, ���������ʾ��
	// argv1 = 1, �������ʾ����Ƶ����
};


//�����ı��ʾ
enum VOLUME_CHANGE_FLAG
{
	VOLUME_UP_FLAG,   //������
	VOLUME_DOWN_FLAG, //������
	VOLUME_SET_FLAG,  //��������
};

//�����ı��ʾ
enum TUNE_CHANGE_FLAG
{
	TUNE_UP_FLAG,        //������
	TUNE_DOWN_FLAG,      //������
	TUNE_ORIGINAL_FLAG,  //ԭ��
	TUNE_SET_VALUE_FLAG, //��������
};

//����ı��ʾ
enum REVERBERATION_CHANGE_FLAG
{
	REVERBERATION_UP_FLAG,   //�����
	REVERBERATION_DOWN_FLAG, //�����
};


#endif

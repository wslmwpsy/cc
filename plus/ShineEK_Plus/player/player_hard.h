// player_hard.h
//
// Ӳ�ⲥ����
//

#pragma once

#include "player.h"

//����ʹ�õ�
const int nLayerLargeLogo      = 0;
const int nLayerWelcomeWord    = 1;
const int nLayerVersionInfo1   = 2;
const int nLayerVersionInfo2   = 3;
//����ʱʹ�õ�
const int nLayerText           = 1; //��������
const int nLayerControlText    = 2; //�����ı�osd
const int nLayerADBKLogo       = 3; //���ı���logo
const int nLayerADLogo         = 4; //���logo
const int nLayerOsdControl     = 5; //����logo
const int nLayerLogo           = 6; //��˾logo
const int nLayerBmp            = 7; //�м��λͼ

class player_hard : public player
{
public:
	// ���������
	player_hard();
	virtual ~player_hard();

	// ����������
	bool create(CWnd *parent_wnd);	// �������ſؼ�ʵ��
	void destory();	// ���ٲ��ſؼ�ʵ��
	bool initialize();	// ��ʼ�����ſؼ�
	int  stop_all();		// ȫ��ֹͣ

	void close_device(void);  //�رս�ѹ�� 
	void open_device(void);   //�򿪽�ѹ��
	int device_state() { return 1; }

	long set_soft_decode(HWND soft_hwnd);
	//���ñ�����Ƶ���ھ��
	long set_slave_video_window(HWND video_hwnd);

	void TV();		// TV
	void VGA();
	void TVorVGA();
	

	// ���ſ���
	void play();	// ����
	void stop();	// ֹͣ
	void pause();	// ��ͣ
	void reset();		// ����

	void set_volume(int l, int r);	// ��������
	void balance(int soundtrack);	// ������������
	void set_track(int trackno);	// ��������
	// GetState
	long get_state();

	// �ļ�����
	void set_play_file_path(const TCHAR* s);	// ���ò����ļ���
	long open_file();	// ���ļ�
	void close_file();	// �ر��ļ�

	long command(long cmd, long flag, long value);

	// ���
	void forward();

	// ����
	void backward();
	long get_total_time_length();	// �ܳ���
	long get_current_pos();	// ��ǰλ��,�ٷֱ�
	long get_play_time_length(); //��ǰ���ŵ�ʱ������
	// ��������λ��
	void seek(long pos);

	// �������ȣ�ȡֵ0��1200
	void set_bright(long value);

	// ���ڶԱȶȣ�ȡֵ0��1200
	void set_contrast(long value);

	// ���ڱ��Ͷȣ�ȡֵ0��1000
	void set_saturation(long value);

	/////////////OSD//////////////////////
	bool InitOSD();		// ��ʼ������
	// LoadBmpFile
	long LoadBmpFile(const TCHAR* sBmpFile);
	// SetOSDBuf
	long SetOSDBuf(long iCard, long iOSD, long pOSDBuf);
	// Get Size of osd or screen
	long GetOSDScreenSizeW();
	long GetOSDScreenSizeH();
	long GetOSDSizeW(long pOSDBuf);
	long GetOSDSizeH(long pOSDBuf);

	// SetPlayVarOSD
	long SetPlayVarOSD(long iCard, long iOSD, long play_mode,
		long nRepeat, long iHspeed, long iVSpeed, long nDelayTime,
		long sx, long sy, long ex, long ey);
	

	long PlayOSD(long iCard, long iOSD);
	long StopOSD(long iCard, long iOSD);

	void PlayOSDStartLogo(const TCHAR* sBigLogo, const TCHAR* sWelcome, TCHAR* szOSDTextFont, TCHAR* szName);
	void StopOSDStartLogo(); // �رտ�����ʾ

	void PlayOSDLogo(const TCHAR* sLogo, int Index, int posX,int posY,bool first_logo);
	void StopOSDLogo();

	void PlayADOSDLogo(const TCHAR* logo_path,int logo_layer);
	void StopADOSDLogo(int logo_layer);

	// ��ʼ����ѹ��ע����Ϣ
	bool InitCardRegistry();

	// ��ȡ���֣�����KTV
	void GetWord1(TCHAR* msg);
	// ��ȡ���֣��Ӻ��Ƽ�
	void GetWord2(TCHAR* msg);

	void SetScreenHwnd(long hwnd, int ScX1, int ScX2, int ScY1, int ScY2);
	bool RefreshDrv();
	int get_text_osd_play_state();

	// ��ʾ�ı���OSD
	void PlayTextOSD(const TCHAR* szBackground, const text_osd_info& txtOSD, const play_variable& playVarText);
	void StopOSDText();

	// ��ʾͼƬ(BMP)��OSD
 	void PlayBmpOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode);
	void StopBMPOSD();

	// ��ʾ������OSD
	void PlayScoreOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode);
	void StopScoreOSD();


	//��ʾǽ���ͼƬ
	void ShowWallPanelOSD(const TCHAR* path);
	void HideWallPanelOSD(void);

	// ��ʾ��������
	void PlayControlOSD(const TCHAR* path, int x, int y);
	void StopControlOSD();
	
	void OSD_GF(TCHAR * Text, long lIndex, long fgcl = RGB(255, 0, 0), int x = 0, int y = 90) ;  //������������ʾ�ڵ�����	
	long stop_OSD_GF(long lIndex);//ֹͣ����������ʾ

	//���õ�����ʽ aDD RAOLIANG 
	void SetTvStandard(long flag);
	//����¼���ط� aDD RAOLIANG 2007-10-4
	void SetPlayBack(long flag);

	// �ļ������ط� aDD RAOLIANG 2007-10-4
	void SetGszWavFileName(const TCHAR* s);	// ���ûط��ļ���

	void OSDKeyDown(WPARAM wParam);
	void OSDListChanged(long list);
	void OSDSetSwapper(long swapper);
	void OSDSwitchKTV(long ktv);
	bool VODEnableDbDisplay(long e);
	void VODSetScreenWindow(long hwnd);
	void VODShowScreenVideo(long e);
	long WaveMixer_Play(LPCTSTR sWaveName, long Loop, long fMusicOut);
	long WaveMixer_Stop();
	long WaveMixer_SetTone(long nTone);
	long WaveMixer_GetTone();
	bool Set(long flag, long value);	// Set
	long Get(long flag);


	//Ԥ�������ֱ������
	long preview_open(LPCTSTR pMedia, long hwnd);
	long preview_close();
	long preview_control(long nCode, long argv0, long argv1);

	//pk
	long Live_Open(long n, LPCTSTR pMedia);
	long Live_Close(long n);
	long Live_Control(long n, long nCode, long argv0, long argv1);

	//����ֱ��
	long TV_open(LPCTSTR pDev, long hwnd, long nSignal);
	long TV_close();
	long TV_control(long nCode, long argv0, long argv1);

	bool Ctrl_SetNotifyWindow(long hwndNotify);

protected:
	bool TV_or_VGA;  //���ӻ���VGA��ʾ��ʾ true��VGA false��TV

	// ���ſؼ�
	CShPlayOCX m_hard_player;		// ���ſؼ�(���ý�ѹ��)

	// �������
	bool m_use_osd;	// �Ƿ�ʹ������
	long pOSDBufWelcomeText;  // ��ӭ�ı�
	long pOSDBufVersionText1; // ����汾��Ϣ������KTV
	long pOSDBufVersionText2; // ����汾��Ϣ���Ӻ��Ƽ�
	long pOSDBufBigLogo;	// ��Logo
	TCHAR osd_buf_logo_path[100][256];	// Logo�ļ���·��
	TCHAR ad_osd_logo_path[100][256];   //���logo�ļ���·��

	// OSD������
	long osd_logo_handle[100];       // Logo�ľ��
	long osd_bk_logo_handle;         //����logo�ľ��
	long ad_osd_logo_handle[100];    //���logo�ľ��
    long osd_control_logo_handle;    //�������Եľ��
	long osd_text_handle;	         // �ı����
	long osd_bmp_handle;             //��ʾbmpͼƬ�ľ�� 
	long osd_score_handle;           //�������

	long m_ScreenHwnd;
	int m_ScX1, m_ScX2, m_ScY1, m_ScY2;
	bool bLargeLogoPlaying;
private:
	TCHAR m_install_path[256];  //��װ·��
	TCHAR m_screen_show_folder_name[64]; //��ŵ�����Ļ����ʾͼƬ���ļ�������
};

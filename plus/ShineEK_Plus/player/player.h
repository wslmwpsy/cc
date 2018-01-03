// player.h
//

#pragma once

#include "shplayocx.h"
#include "player_notify.h"
#include "player_data_type.h"
#include "..\common\parser_color.h"

//osd ���뷽ʽ
enum OSDAlignment
{
	OSDAlignmentTop,         //����
	OSDAlignmentCenter,      //�м�
	OSDAlignmentBottom,      //����
	OSDAlignmentRightCenter, //�ұ߾���
	OSDPK,					//pk
	OSDAlignmentCenterTop,
	OSDSCOREPOS,             //����������ʾ��λ��
	OSDSCORELEFTPOS,		 //����OSD������ʾλ��
	OSDAlignmentRightTop,	//���Ͻ�
};

//���öԳ���Ƶ��λ��
enum VIDEO_PIP_POSITION
{
	SD_SET_PIP0_POSITION   = 426,	// ���öԳ���Ƶ0 λ��
	SD_SET_PIP1_POSITION   = 427,	// ���öԳ���Ƶ1 λ��
};

// ���ſؼ������࣬ʵ�������Ӳ��ȵ�ͳһ��װ
class player
{
public:
	virtual ~player() { }

	// ����������
	virtual bool create(CWnd *parent_wnd) = 0;
	virtual void destory() = 0;

	// ״̬����
	virtual bool initialize() = 0;	// ��ʼ�����ſؼ�
	
	virtual void open_device(void) = 0;   //�򿪽�ѹ��
	virtual void close_device(void) = 0;  //�رս�ѹ��
	virtual int  device_state() = 0;  //��ѹ��״̬

	//�������
	virtual long set_soft_decode(HWND soft_hwnd)=0;

	//���ñ�����Ƶ���ھ��
	virtual long set_slave_video_window(HWND video_hwnd)=0;

	//ָ�������������ǲ���tv����vga�����ĿǰĬ�ϲ���tv�ˡ����Ըýӿ������ˡ�
	virtual void TV() = 0;
	virtual void VGA() = 0;
	virtual void TVorVGA() = 0;
		
	// ���ſ���
	virtual void play() = 0;	// ����
	virtual void pause() = 0;	// ��ͣ
	virtual void stop() = 0;	// ֹͣ
	virtual void set_volume(int l, int r) = 0;	// ��������

	virtual void reset() = 0;		// ����
	virtual void balance(int soundtrack) = 0; 	// ������������
	virtual void set_track(int trackno) = 0;	// ��������

	// �ļ�����
	virtual void set_play_file_path(const TCHAR* s) = 0;	// ���ò����ļ���
	virtual long open_file() = 0;	// ���ļ�
	virtual void close_file() = 0;	// �ر��ļ�
		
	// GetState
	virtual long get_state() = 0;
	virtual long command(long cmd, long flag, long value) = 0;	
	
	// ���
	virtual void forward() = 0;

	// ����
	virtual void backward() = 0;

	// ��ȡ����
	virtual long get_total_time_length() = 0;	// �ܳ���
	virtual long get_current_pos() = 0;	// ��ǰλ�ã��ٷֱ�
	virtual long get_play_time_length()=0; //��ǰ���ŵ�ʱ������

	// ��������λ��
	virtual void seek(long pos) = 0;


	// �������ȣ�ȡֵ0��1200
	virtual void set_bright(long value) = 0;

	// ���ڶԱȶȣ�ȡֵ0��1200
	virtual void set_contrast(long value) = 0;

	// ���ڱ��Ͷȣ�ȡֵ0��1000
	virtual void set_saturation(long value) = 0;
	virtual int  stop_all() = 0;

	///////////////////////OSD////////////////////////////////
	virtual bool InitOSD() = 0;	// ��ʼ������
	virtual long PlayOSD( long iCard,long iOSD) = 0;
	virtual bool RefreshDrv() = 0;
	virtual void SetScreenHwnd(long hwnd, int ScX1, int ScX2, int ScY1, int ScY2) = 0;

	//�õ�text osd�Ĳ���״̬
	virtual int  get_text_osd_play_state() = 0;
	virtual long StopOSD(long iCard, long iOSD) = 0;


	virtual void PlayOSDStartLogo(const TCHAR* sBigLogo, const TCHAR* sWelcome, TCHAR* szOSDTextFont, TCHAR* szName) = 0;
	virtual void StopOSDStartLogo() = 0; // �رտ�����ʾ

	//���Ź�˾logo
	virtual void PlayOSDLogo(const TCHAR* sLogo, int Index, int posX,int posY,bool first_logo) = 0;
	virtual void StopOSDLogo() = 0;

	//���Ź��logo
	virtual void PlayADOSDLogo(const TCHAR* logo_path,int logo_layer)=0;
	virtual void StopADOSDLogo(int logo_layer)=0;
	
	// ��ʾ�ı���OSD
	virtual void PlayTextOSD(const TCHAR* szBackground, const text_osd_info& txtOSD, const play_variable& playVarText) = 0;
    virtual void StopOSDText() = 0;
	
	// ��ʾͼƬ(BMP)��OSD
	virtual void PlayBmpOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode) = 0;
	virtual void StopBMPOSD() = 0;

	// ��ʾ������OSD
	virtual void PlayScoreOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode) = 0;
	virtual void StopScoreOSD() = 0;

	//��ʾǽ���ͼƬ
	virtual void ShowWallPanelOSD(const TCHAR* path)=0;
	virtual void HideWallPanelOSD(void)=0;

	// ��ʾ��������
	virtual void PlayControlOSD(const TCHAR* path, int x, int y) = 0;
	virtual void StopControlOSD() = 0;
	virtual void OSD_GF(TCHAR * Text, long lIndex,long fgcl = RGB(255, 0, 0), int x = 0, int y = 90) = 0;  //������������ʾ�ڵ�����
	virtual long stop_OSD_GF(long lIndex) = 0;

	//���õ�����ʽ aDD RAOLIANG 
	virtual void SetTvStandard(long flag) =0;
	
	// �ļ������ط� aDD RAOLIANG 2007-10-4
	virtual void SetGszWavFileName(const TCHAR* s)=0;	// ���ûط��ļ���

	//����¼���ط� aDD RAOLIANG 2007-10-4
	virtual void SetPlayBack(long flag) =0;
	virtual bool Set(long flag, long value) = 0;
	virtual long Get(long flag)=0;


	//�¼ӵ�Ϊ��OSD���
	virtual void OSDKeyDown(WPARAM wParam) = 0;
	virtual void OSDListChanged(long list) = 0;
	virtual void OSDSetSwapper(long swapper) = 0;
	virtual void OSDSwitchKTV(long ktv) = 0;
	virtual bool VODEnableDbDisplay(long e) = 0;
	virtual void VODSetScreenWindow(long hwnd) = 0;
	virtual void VODShowScreenVideo(long e) = 0;

	//��Ƶ����
	virtual long WaveMixer_Play(LPCTSTR sWaveName, long Loop, long fMusicOut) = 0;
	virtual long WaveMixer_Stop() = 0;
	virtual long WaveMixer_SetTone(long nTone) = 0;
	virtual long WaveMixer_GetTone() =0;

	//Ԥ��������ֱ��������
	virtual long preview_open(LPCTSTR pMedia, long hwnd)=0;
	virtual long preview_close()=0;
	virtual long preview_control(long nCode, long argv0, long argv1)=0;
	virtual long Live_Open(long n, LPCTSTR pMedia) = 0;
	virtual long Live_Close(long n) = 0;
	virtual long Live_Control(long n, long nCode, long argv0, long argv1) = 0;

	//����ֱ��
	virtual long TV_open(LPCTSTR pDev, long hwnd, long nSignal)=0;
	virtual long TV_close()=0;
	virtual long TV_control(long nCode, long argv0, long argv1)=0;

	virtual bool Ctrl_SetNotifyWindow(long hwndNotify) = 0;
};

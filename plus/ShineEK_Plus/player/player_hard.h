// player_hard.h
//
// 硬解播放类
//

#pragma once

#include "player.h"

//开机使用的
const int nLayerLargeLogo      = 0;
const int nLayerWelcomeWord    = 1;
const int nLayerVersionInfo1   = 2;
const int nLayerVersionInfo2   = 3;
//运行时使用的
const int nLayerText           = 1; //滚动文字
const int nLayerControlText    = 2; //控制文本osd
const int nLayerADBKLogo       = 3; //广告的背景logo
const int nLayerADLogo         = 4; //广告logo
const int nLayerOsdControl     = 5; //控制logo
const int nLayerLogo           = 6; //公司logo
const int nLayerBmp            = 7; //中间的位图

class player_hard : public player
{
public:
	// 构造和析构
	player_hard();
	virtual ~player_hard();

	// 创建与销毁
	bool create(CWnd *parent_wnd);	// 创建播放控件实例
	void destory();	// 销毁播放控件实例
	bool initialize();	// 初始化播放控件
	int  stop_all();		// 全部停止

	void close_device(void);  //关闭解压卡 
	void open_device(void);   //打开解压卡
	int device_state() { return 1; }

	long set_soft_decode(HWND soft_hwnd);
	//设置被控视频窗口句柄
	long set_slave_video_window(HWND video_hwnd);

	void TV();		// TV
	void VGA();
	void TVorVGA();
	

	// 播放控制
	void play();	// 播放
	void stop();	// 停止
	void pause();	// 暂停
	void reset();		// 重置

	void set_volume(int l, int r);	// 设置音量
	void balance(int soundtrack);	// 设置左右声道
	void set_track(int trackno);	// 设置音轨
	// GetState
	long get_state();

	// 文件操作
	void set_play_file_path(const TCHAR* s);	// 设置播放文件名
	long open_file();	// 打开文件
	void close_file();	// 关闭文件

	long command(long cmd, long flag, long value);

	// 快进
	void forward();

	// 快退
	void backward();
	long get_total_time_length();	// 总长度
	long get_current_pos();	// 当前位置,百分比
	long get_play_time_length(); //当前播放的时长，秒
	// 调整播放位置
	void seek(long pos);

	// 调节亮度，取值0～1200
	void set_bright(long value);

	// 调节对比度，取值0～1200
	void set_contrast(long value);

	// 调节饱和度，取值0～1000
	void set_saturation(long value);

	/////////////OSD//////////////////////
	bool InitOSD();		// 初始化屏显
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
	void StopOSDStartLogo(); // 关闭开机显示

	void PlayOSDLogo(const TCHAR* sLogo, int Index, int posX,int posY,bool first_logo);
	void StopOSDLogo();

	void PlayADOSDLogo(const TCHAR* logo_path,int logo_layer);
	void StopADOSDLogo(int logo_layer);

	// 初始化解压卡注册信息
	bool InitCardRegistry();

	// 获取文字：阳光KTV
	void GetWord1(TCHAR* msg);
	// 获取文字：视翰科技
	void GetWord2(TCHAR* msg);

	void SetScreenHwnd(long hwnd, int ScX1, int ScX2, int ScY1, int ScY2);
	bool RefreshDrv();
	int get_text_osd_play_state();

	// 显示文本到OSD
	void PlayTextOSD(const TCHAR* szBackground, const text_osd_info& txtOSD, const play_variable& playVarText);
	void StopOSDText();

	// 显示图片(BMP)到OSD
 	void PlayBmpOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode);
	void StopBMPOSD();

	// 显示分数到OSD
	void PlayScoreOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode);
	void StopScoreOSD();


	//显示墙面板图片
	void ShowWallPanelOSD(const TCHAR* path);
	void HideWallPanelOSD(void);

	// 显示控制屏显
	void PlayControlOSD(const TCHAR* path, int x, int y);
	void StopControlOSD();
	
	void OSD_GF(TCHAR * Text, long lIndex, long fgcl = RGB(255, 0, 0), int x = 0, int y = 90) ;  //将功放文字显示在电视上	
	long stop_OSD_GF(long lIndex);//停止功放文字显示

	//设置电视制式 aDD RAOLIANG 
	void SetTvStandard(long flag);
	//设置录音回放 aDD RAOLIANG 2007-10-4
	void SetPlayBack(long flag);

	// 文件操作回放 aDD RAOLIANG 2007-10-4
	void SetGszWavFileName(const TCHAR* s);	// 设置回放文件名

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


	//预览或大厅直播功能
	long preview_open(LPCTSTR pMedia, long hwnd);
	long preview_close();
	long preview_control(long nCode, long argv0, long argv1);

	//pk
	long Live_Open(long n, LPCTSTR pMedia);
	long Live_Close(long n);
	long Live_Control(long n, long nCode, long argv0, long argv1);

	//电视直播
	long TV_open(LPCTSTR pDev, long hwnd, long nSignal);
	long TV_close();
	long TV_control(long nCode, long argv0, long argv1);

	bool Ctrl_SetNotifyWindow(long hwndNotify);

protected:
	bool TV_or_VGA;  //电视还是VGA显示标示 true：VGA false：TV

	// 播放控件
	CShPlayOCX m_hard_player;		// 播放控件(采用解压卡)

	// 屏显相关
	bool m_use_osd;	// 是否使用屏显
	long pOSDBufWelcomeText;  // 欢迎文本
	long pOSDBufVersionText1; // 软件版本信息：阳光KTV
	long pOSDBufVersionText2; // 软件版本信息：视翰科技
	long pOSDBufBigLogo;	// 大Logo
	TCHAR osd_buf_logo_path[100][256];	// Logo文件的路径
	TCHAR ad_osd_logo_path[100][256];   //广告logo文件的路径

	// OSD对象句柄
	long osd_logo_handle[100];       // Logo的句柄
	long osd_bk_logo_handle;         //背景logo的句柄
	long ad_osd_logo_handle[100];    //广告logo的句柄
    long osd_control_logo_handle;    //控制屏显的句柄
	long osd_text_handle;	         // 文本句柄
	long osd_bmp_handle;             //显示bmp图片的句柄 
	long osd_score_handle;           //分数句柄

	long m_ScreenHwnd;
	int m_ScX1, m_ScX2, m_ScY1, m_ScY2;
	bool bLargeLogoPlaying;
private:
	TCHAR m_install_path[256];  //安装路径
	TCHAR m_screen_show_folder_name[64]; //存放电视屏幕上显示图片的文件夹名字
};

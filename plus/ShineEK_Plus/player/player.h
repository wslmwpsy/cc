// player.h
//

#pragma once

#include "shplayocx.h"
#include "player_notify.h"
#include "player_data_type.h"
#include "..\common\parser_color.h"

//osd 对齐方式
enum OSDAlignment
{
	OSDAlignmentTop,         //上面
	OSDAlignmentCenter,      //中间
	OSDAlignmentBottom,      //下面
	OSDAlignmentRightCenter, //右边居中
	OSDPK,					//pk
	OSDAlignmentCenterTop,
	OSDSCOREPOS,             //分数评语显示的位置
	OSDSCORELEFTPOS,		 //分数OSD分数显示位置
	OSDAlignmentRightTop,	//右上角
};

//设置对唱视频的位置
enum VIDEO_PIP_POSITION
{
	SD_SET_PIP0_POSITION   = 426,	// 设置对唱视频0 位置
	SD_SET_PIP1_POSITION   = 427,	// 设置对唱视频1 位置
};

// 播放控件操作类，实现软解与硬解等的统一封装
class player
{
public:
	virtual ~player() { }

	// 创建与销毁
	virtual bool create(CWnd *parent_wnd) = 0;
	virtual void destory() = 0;

	// 状态控制
	virtual bool initialize() = 0;	// 初始化播放控件
	
	virtual void open_device(void) = 0;   //打开解压卡
	virtual void close_device(void) = 0;  //关闭解压卡
	virtual int  device_state() = 0;  //解压卡状态

	//设置软解
	virtual long set_soft_decode(HWND soft_hwnd)=0;

	//设置被控视频窗口句柄
	virtual long set_slave_video_window(HWND video_hwnd)=0;

	//指的是神龙卡，是采用tv还是vga输出。目前默认采用tv了。所以该接口无用了。
	virtual void TV() = 0;
	virtual void VGA() = 0;
	virtual void TVorVGA() = 0;
		
	// 播放控制
	virtual void play() = 0;	// 播放
	virtual void pause() = 0;	// 暂停
	virtual void stop() = 0;	// 停止
	virtual void set_volume(int l, int r) = 0;	// 设置音量

	virtual void reset() = 0;		// 重置
	virtual void balance(int soundtrack) = 0; 	// 设置左右声道
	virtual void set_track(int trackno) = 0;	// 设置音轨

	// 文件操作
	virtual void set_play_file_path(const TCHAR* s) = 0;	// 设置播放文件名
	virtual long open_file() = 0;	// 打开文件
	virtual void close_file() = 0;	// 关闭文件
		
	// GetState
	virtual long get_state() = 0;
	virtual long command(long cmd, long flag, long value) = 0;	
	
	// 快进
	virtual void forward() = 0;

	// 快退
	virtual void backward() = 0;

	// 获取长度
	virtual long get_total_time_length() = 0;	// 总长度
	virtual long get_current_pos() = 0;	// 当前位置，百分比
	virtual long get_play_time_length()=0; //当前播放的时长，秒

	// 调整播放位置
	virtual void seek(long pos) = 0;


	// 调节亮度，取值0～1200
	virtual void set_bright(long value) = 0;

	// 调节对比度，取值0～1200
	virtual void set_contrast(long value) = 0;

	// 调节饱和度，取值0～1000
	virtual void set_saturation(long value) = 0;
	virtual int  stop_all() = 0;

	///////////////////////OSD////////////////////////////////
	virtual bool InitOSD() = 0;	// 初始化屏显
	virtual long PlayOSD( long iCard,long iOSD) = 0;
	virtual bool RefreshDrv() = 0;
	virtual void SetScreenHwnd(long hwnd, int ScX1, int ScX2, int ScY1, int ScY2) = 0;

	//得到text osd的播放状态
	virtual int  get_text_osd_play_state() = 0;
	virtual long StopOSD(long iCard, long iOSD) = 0;


	virtual void PlayOSDStartLogo(const TCHAR* sBigLogo, const TCHAR* sWelcome, TCHAR* szOSDTextFont, TCHAR* szName) = 0;
	virtual void StopOSDStartLogo() = 0; // 关闭开机显示

	//播放公司logo
	virtual void PlayOSDLogo(const TCHAR* sLogo, int Index, int posX,int posY,bool first_logo) = 0;
	virtual void StopOSDLogo() = 0;

	//播放广告logo
	virtual void PlayADOSDLogo(const TCHAR* logo_path,int logo_layer)=0;
	virtual void StopADOSDLogo(int logo_layer)=0;
	
	// 显示文本到OSD
	virtual void PlayTextOSD(const TCHAR* szBackground, const text_osd_info& txtOSD, const play_variable& playVarText) = 0;
    virtual void StopOSDText() = 0;
	
	// 显示图片(BMP)到OSD
	virtual void PlayBmpOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode) = 0;
	virtual void StopBMPOSD() = 0;

	// 显示分数到OSD
	virtual void PlayScoreOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode) = 0;
	virtual void StopScoreOSD() = 0;

	//显示墙面板图片
	virtual void ShowWallPanelOSD(const TCHAR* path)=0;
	virtual void HideWallPanelOSD(void)=0;

	// 显示控制屏显
	virtual void PlayControlOSD(const TCHAR* path, int x, int y) = 0;
	virtual void StopControlOSD() = 0;
	virtual void OSD_GF(TCHAR * Text, long lIndex,long fgcl = RGB(255, 0, 0), int x = 0, int y = 90) = 0;  //将功放文字显示在电视上
	virtual long stop_OSD_GF(long lIndex) = 0;

	//设置电视制式 aDD RAOLIANG 
	virtual void SetTvStandard(long flag) =0;
	
	// 文件操作回放 aDD RAOLIANG 2007-10-4
	virtual void SetGszWavFileName(const TCHAR* s)=0;	// 设置回放文件名

	//设置录音回放 aDD RAOLIANG 2007-10-4
	virtual void SetPlayBack(long flag) =0;
	virtual bool Set(long flag, long value) = 0;
	virtual long Get(long flag)=0;


	//新加的为了OSD点歌
	virtual void OSDKeyDown(WPARAM wParam) = 0;
	virtual void OSDListChanged(long list) = 0;
	virtual void OSDSetSwapper(long swapper) = 0;
	virtual void OSDSwitchKTV(long ktv) = 0;
	virtual bool VODEnableDbDisplay(long e) = 0;
	virtual void VODSetScreenWindow(long hwnd) = 0;
	virtual void VODShowScreenVideo(long e) = 0;

	//音频操作
	virtual long WaveMixer_Play(LPCTSTR sWaveName, long Loop, long fMusicOut) = 0;
	virtual long WaveMixer_Stop() = 0;
	virtual long WaveMixer_SetTone(long nTone) = 0;
	virtual long WaveMixer_GetTone() =0;

	//预览（大厅直播）功能
	virtual long preview_open(LPCTSTR pMedia, long hwnd)=0;
	virtual long preview_close()=0;
	virtual long preview_control(long nCode, long argv0, long argv1)=0;
	virtual long Live_Open(long n, LPCTSTR pMedia) = 0;
	virtual long Live_Close(long n) = 0;
	virtual long Live_Control(long n, long nCode, long argv0, long argv1) = 0;

	//电视直播
	virtual long TV_open(LPCTSTR pDev, long hwnd, long nSignal)=0;
	virtual long TV_close()=0;
	virtual long TV_control(long nCode, long argv0, long argv1)=0;

	virtual bool Ctrl_SetNotifyWindow(long hwndNotify) = 0;
};

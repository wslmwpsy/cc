#pragma once

#include "screen_saver_picture.h"
#include "screen_saver_variable.h"
// screen_saver_window

class screen_saver_window : public CWnd
{
	DECLARE_DYNAMIC(screen_saver_window)

public:
	screen_saver_window();
	virtual ~screen_saver_window();
	//创建显示屏保的窗口
	bool Create(CWnd *parent_wnd,int screen_width,int screen_height);
	
	/*
	功能：得到可以播放的屏保图片路径
	参数：
		path：屏保文件路径
	返回值：
		图片个数
	*/
	int set_screen_saver_path(TCHAR *path);

	/*
	功能：设置广告路径
	参数：
	    path：广告屏保路径
	返回值：
	    true：成功
		false失败
	*/
	bool set_ad_screen_saver_path(TCHAR *path);
	
	/*
	功能：显示屏保
	参数：
	    void
	返回值：
	    void
	*/
	void show_screen_saver(void);
	/*
	功能：隐藏屏保
	参数：
	    void
	返回值：
	    void
	*/
	void hide_screen_saver(void);
	/*
	功能：设置每个屏保的播放时间
	参数：
	    show_time：显示时间
	返回值：
	    void
	*/
	void set_show_time(int show_time);

	/*
	功能：设定显示模式
	参数：
	    void
	返回值：
	    void
	*/
	void set_show_mode(void);

	/*
	功能：绘制区域
	参数：
	    dc:设备上下文句柄
	返回值：
	    void
	*/
	void paint_rect(CPaintDC &dc);

protected:
	DECLARE_MESSAGE_MAP()
private:
	screen_saver_picture  m_screen_saver_picture; //显示屏保的图片类
	bool play_ad_screen_saver;                    //是否播放广告屏保
	TCHAR screen_saver_path[SCREEN_SAVER_MAX_PICTURE_COUNT][256]; //屏保路径
	int m_screen_saver_picture_count;             //屏保的实际图片数
	int m_play_screen_saver_index;                //当前播放的屏保图片索引
	TCHAR ad_screen_saver_path[256];              //广告的屏保路径
	int m_screen_width;                           //屏幕的宽度
	int m_screen_height;                          //屏幕的高度
	bool m_show_screen_saver;                     //显示屏保标示
	CPoint cursor_point;                          //记录旧的光标点
	UINT_PTR repaint_timer_identifier;            //重绘定时器的标示
	UINT_PTR switch_screen_saver_timer_identifier;//更换屏保的定时器标示
	HWND m_parent_handle;                         //父窗体的句柄
	int m_screen_saver_show_time;                  //屏保图片的显示时间
	CRect show_rect,show_rect1;                    //显示区域
	SCREEN_SAVER_SHOW_MODE m_show_mode;            //显示模式
	long add_width;                                 //增加的宽度
	long add_heigth;                                //增加的高度
	bool m_end_paint;                                //完成重绘
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
};



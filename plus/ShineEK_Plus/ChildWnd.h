#pragma once

#include "common/timer.h"

// CChildWnd

class CChildWnd : public CWnd
{
	DECLARE_DYNAMIC(CChildWnd)

public:
	CChildWnd();
	virtual ~CChildWnd();

	bool Create(DWORD dwStyle, RECT& rect, CWnd* pParentWnd, UINT nID, bool transparence = false, unsigned char alpha = 220,bool zoom_in=true);
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
private:
	CWnd *m_parent_wnd;
	bool m_zoom_in;          //允许放到
	CTimer m_zoom_timer;     //视频窗口放大缩小定时器。防止频繁操作
	HWND m_message_handle;   //消息反馈句柄
	TCHAR m_image_path[256]; //图片路径
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
	/*
	功能：设置消息反馈句柄
	参数：
	   hwnd：句柄
   返回值：
       true：成功
	   false：失败
	*/
	bool set_message_handle(HWND hwnd);
	/*
	功能：显示窗口
	参数：
	    cmd_show：显示命令 true：显示 false：隐藏
	返回值：
	    void
	*/
	void show_window(bool cmd_show);

	/*
	功能：设置要显示的图片
	参数：
		path：图片路径
	返回值：
		void
	*/
	void set_show_image(TCHAR *path);

	/*
	功能：显示图片
	参数：
	   void
   返回值：
       void
	*/
	void show_image(void);

	//flash function
	//flash界面的消息响应函数
	void FlashCallShockwaveflash(LPCTSTR request);
};
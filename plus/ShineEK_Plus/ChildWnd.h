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
	bool m_zoom_in;          //����ŵ�
	CTimer m_zoom_timer;     //��Ƶ���ڷŴ���С��ʱ������ֹƵ������
	HWND m_message_handle;   //��Ϣ�������
	TCHAR m_image_path[256]; //ͼƬ·��
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
	/*
	���ܣ�������Ϣ�������
	������
	   hwnd�����
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool set_message_handle(HWND hwnd);
	/*
	���ܣ���ʾ����
	������
	    cmd_show����ʾ���� true����ʾ false������
	����ֵ��
	    void
	*/
	void show_window(bool cmd_show);

	/*
	���ܣ�����Ҫ��ʾ��ͼƬ
	������
		path��ͼƬ·��
	����ֵ��
		void
	*/
	void set_show_image(TCHAR *path);

	/*
	���ܣ���ʾͼƬ
	������
	   void
   ����ֵ��
       void
	*/
	void show_image(void);

	//flash function
	//flash�������Ϣ��Ӧ����
	void FlashCallShockwaveflash(LPCTSTR request);
};
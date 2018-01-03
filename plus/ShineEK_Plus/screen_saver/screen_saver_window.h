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
	//������ʾ�����Ĵ���
	bool Create(CWnd *parent_wnd,int screen_width,int screen_height);
	
	/*
	���ܣ��õ����Բ��ŵ�����ͼƬ·��
	������
		path�������ļ�·��
	����ֵ��
		ͼƬ����
	*/
	int set_screen_saver_path(TCHAR *path);

	/*
	���ܣ����ù��·��
	������
	    path���������·��
	����ֵ��
	    true���ɹ�
		falseʧ��
	*/
	bool set_ad_screen_saver_path(TCHAR *path);
	
	/*
	���ܣ���ʾ����
	������
	    void
	����ֵ��
	    void
	*/
	void show_screen_saver(void);
	/*
	���ܣ���������
	������
	    void
	����ֵ��
	    void
	*/
	void hide_screen_saver(void);
	/*
	���ܣ�����ÿ�������Ĳ���ʱ��
	������
	    show_time����ʾʱ��
	����ֵ��
	    void
	*/
	void set_show_time(int show_time);

	/*
	���ܣ��趨��ʾģʽ
	������
	    void
	����ֵ��
	    void
	*/
	void set_show_mode(void);

	/*
	���ܣ���������
	������
	    dc:�豸�����ľ��
	����ֵ��
	    void
	*/
	void paint_rect(CPaintDC &dc);

protected:
	DECLARE_MESSAGE_MAP()
private:
	screen_saver_picture  m_screen_saver_picture; //��ʾ������ͼƬ��
	bool play_ad_screen_saver;                    //�Ƿ񲥷Ź������
	TCHAR screen_saver_path[SCREEN_SAVER_MAX_PICTURE_COUNT][256]; //����·��
	int m_screen_saver_picture_count;             //������ʵ��ͼƬ��
	int m_play_screen_saver_index;                //��ǰ���ŵ�����ͼƬ����
	TCHAR ad_screen_saver_path[256];              //��������·��
	int m_screen_width;                           //��Ļ�Ŀ��
	int m_screen_height;                          //��Ļ�ĸ߶�
	bool m_show_screen_saver;                     //��ʾ������ʾ
	CPoint cursor_point;                          //��¼�ɵĹ���
	UINT_PTR repaint_timer_identifier;            //�ػ涨ʱ���ı�ʾ
	UINT_PTR switch_screen_saver_timer_identifier;//���������Ķ�ʱ����ʾ
	HWND m_parent_handle;                         //������ľ��
	int m_screen_saver_show_time;                  //����ͼƬ����ʾʱ��
	CRect show_rect,show_rect1;                    //��ʾ����
	SCREEN_SAVER_SHOW_MODE m_show_mode;            //��ʾģʽ
	long add_width;                                 //���ӵĿ��
	long add_heigth;                                //���ӵĸ߶�
	bool m_end_paint;                                //����ػ�
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
};



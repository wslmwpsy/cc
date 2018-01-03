#pragma once

#include "ink_recognition.h"
// handwriting

#define INK_RECOGNIZE_ALTERNATE_NUMS    10    //识别的字数


class handwriting : public CWnd
{
	DECLARE_DYNAMIC(handwriting)

public:
	handwriting();
	virtual ~handwriting();

protected:
	DECLARE_MESSAGE_MAP()
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//创建窗口
	bool Create(DWORD dwStyle, RECT& rect, CWnd* pParentWnd, UINT nID, bool transparence = false, unsigned char alpha = 220,bool zoom_in=true);
	//清空手写板
	bool clear_ink_window(void);
	//改变语言
	bool change_ink_recognize_language(int language);
	//改变画板和画笔颜色
	bool change_handwriting_board_color(COLORREF fore_color,COLORREF background_color,long pen_color);
private:
	ink_recognition m_ink_recognition;   //油墨识别类
	CString m_ink_recognition_result[INK_RECOGNIZE_ALTERNATE_NUMS];   //识别的结果
	COLORREF m_foreground_color;    //前景颜色，即格子的颜色
	COLORREF m_background_color;    //背景颜色
	long m_pen_color;               //画笔颜色
};



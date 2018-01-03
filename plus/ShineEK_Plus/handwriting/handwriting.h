#pragma once

#include "ink_recognition.h"
// handwriting

#define INK_RECOGNIZE_ALTERNATE_NUMS    10    //ʶ�������


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
	//��������
	bool Create(DWORD dwStyle, RECT& rect, CWnd* pParentWnd, UINT nID, bool transparence = false, unsigned char alpha = 220,bool zoom_in=true);
	//�����д��
	bool clear_ink_window(void);
	//�ı�����
	bool change_ink_recognize_language(int language);
	//�ı仭��ͻ�����ɫ
	bool change_handwriting_board_color(COLORREF fore_color,COLORREF background_color,long pen_color);
private:
	ink_recognition m_ink_recognition;   //��īʶ����
	CString m_ink_recognition_result[INK_RECOGNIZE_ALTERNATE_NUMS];   //ʶ��Ľ��
	COLORREF m_foreground_color;    //ǰ����ɫ�������ӵ���ɫ
	COLORREF m_background_color;    //������ɫ
	long m_pen_color;               //������ɫ
};



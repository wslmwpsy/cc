// flashktv10.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������
#include "flashktv10Wnd.h"


// Cflashktv10App:
// �йش����ʵ�֣������ flashktv10.cpp
//

class Cflashktv10App : public CWinApp
{
public:
	Cflashktv10App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
private:
	Cflashktv10Wnd *m_pMainKtv10Wnd;
	ULONG_PTR    gdiplusToken;
	HANDLE m_hAsyn;
};

extern Cflashktv10App theApp;

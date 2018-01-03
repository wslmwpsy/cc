// flashktv10.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"		// 主符号
#include "flashktv10Wnd.h"


// Cflashktv10App:
// 有关此类的实现，请参阅 flashktv10.cpp
//

class Cflashktv10App : public CWinApp
{
public:
	Cflashktv10App();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
private:
	Cflashktv10Wnd *m_pMainKtv10Wnd;
	ULONG_PTR    gdiplusToken;
	HANDLE m_hAsyn;
};

extern Cflashktv10App theApp;

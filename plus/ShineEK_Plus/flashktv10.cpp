// flashktv10.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "flashktv10.h"
#include "flashktv10Wnd.h"
#include ".\flashktv10.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cflashktv10App

BEGIN_MESSAGE_MAP(Cflashktv10App, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cflashktv10App 构造

Cflashktv10App::Cflashktv10App()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 Cflashktv10App 对象

Cflashktv10App theApp;


// Cflashktv10App 初始化

BOOL Cflashktv10App::InitInstance()
{
#ifndef SLAVE_NO_PLAY_VIDEO
	//设置只能打开一个应用程序
	m_hAsyn = OpenSemaphore(SEMAPHORE_ALL_ACCESS,TRUE,L"SHINEKTV10_ZLG");
	if (NULL == m_hAsyn)
	{
		m_hAsyn = CreateSemaphore(NULL,0,1,L"SHINEKTV10_ZLG");
	}
	else
	{
		return FALSE;
	}
#endif
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("北京阳光视翰科技有限公司"));

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	m_pMainKtv10Wnd = NULL;
	m_pMainKtv10Wnd = new Cflashktv10Wnd;
	if (NULL==m_pMainKtv10Wnd)
	{
		return FALSE;
	}
	//创建非模态对话框
	BOOL result = m_pMainKtv10Wnd->CreateWnd();
	if (!result)
	{
		delete m_pMainKtv10Wnd;
		m_pMainKtv10Wnd = NULL;
		return FALSE;
	}
	//显示
	m_pMainKtv10Wnd->ShowWindow(SW_SHOW);
	m_pMainKtv10Wnd->UpdateWindow();
	m_pMainWnd = m_pMainKtv10Wnd;

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	//return FALSE;
	return TRUE;
}

int Cflashktv10App::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_pMainWnd)
	{
		m_pMainWnd = NULL;
	}
	//删除非模态对话框
	if (m_pMainKtv10Wnd)
	{
		delete m_pMainKtv10Wnd;
		m_pMainKtv10Wnd = NULL;
	}
	//释放信号量
	if (m_hAsyn)
	{
		CloseHandle(m_hAsyn);
		m_hAsyn = NULL;
	}

	//关闭gdiplus的环境
	GdiplusShutdown(gdiplusToken);
	return CWinApp::ExitInstance();
}

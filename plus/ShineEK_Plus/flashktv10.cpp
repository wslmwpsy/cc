// flashktv10.cpp : ����Ӧ�ó��������Ϊ��
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


// Cflashktv10App ����

Cflashktv10App::Cflashktv10App()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cflashktv10App ����

Cflashktv10App theApp;


// Cflashktv10App ��ʼ��

BOOL Cflashktv10App::InitInstance()
{
#ifndef SLAVE_NO_PLAY_VIDEO
	//����ֻ�ܴ�һ��Ӧ�ó���
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
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("���������Ӻ��Ƽ����޹�˾"));

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	m_pMainKtv10Wnd = NULL;
	m_pMainKtv10Wnd = new Cflashktv10Wnd;
	if (NULL==m_pMainKtv10Wnd)
	{
		return FALSE;
	}
	//������ģ̬�Ի���
	BOOL result = m_pMainKtv10Wnd->CreateWnd();
	if (!result)
	{
		delete m_pMainKtv10Wnd;
		m_pMainKtv10Wnd = NULL;
		return FALSE;
	}
	//��ʾ
	m_pMainKtv10Wnd->ShowWindow(SW_SHOW);
	m_pMainKtv10Wnd->UpdateWindow();
	m_pMainWnd = m_pMainKtv10Wnd;

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	//return FALSE;
	return TRUE;
}

int Cflashktv10App::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if (m_pMainWnd)
	{
		m_pMainWnd = NULL;
	}
	//ɾ����ģ̬�Ի���
	if (m_pMainKtv10Wnd)
	{
		delete m_pMainKtv10Wnd;
		m_pMainKtv10Wnd = NULL;
	}
	//�ͷ��ź���
	if (m_hAsyn)
	{
		CloseHandle(m_hAsyn);
		m_hAsyn = NULL;
	}

	//�ر�gdiplus�Ļ���
	GdiplusShutdown(gdiplusToken);
	return CWinApp::ExitInstance();
}

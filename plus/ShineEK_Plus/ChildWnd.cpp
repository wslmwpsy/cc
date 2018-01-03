// ChildWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChildWnd.h"
#include ".\childwnd.h"
#include "message.h"

// CChildWnd

IMPLEMENT_DYNAMIC(CChildWnd, CWnd)
CChildWnd::CChildWnd()
{
	m_parent_wnd=NULL;
	m_zoom_in=true;
	//��ʼ��ʱ
	m_zoom_timer.start();
	m_message_handle=0;
	memset(m_image_path,0x0,sizeof(m_image_path));
}

CChildWnd::~CChildWnd()
{
}


BEGIN_MESSAGE_MAP(CChildWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CChildWnd,CWnd)
	ON_EVENT(CChildWnd,SLAVE_WINDOW_FLASH_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,WALL_PANEL_PLAYER_WINDOW_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,GAME_FLASH_PLAYER_WINDOW_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,AD_FLASH_PLAYER_WINDOW_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,SCORE_SOFT_FLASH_WINDOW_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,SCORE_FLASH_WINDOW_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,VICE_SCREEN_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,INTER_SCREEN_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,LISTEN_PAGE_TV_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,PICTURE_MV_TV_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,LISTEN_PAGE_TV_SOFT_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,PICTURE_MV_TV_SOFT_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,ACTIVE_GAME_SOFT_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,ACTIVE_GAME_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,ACROSS_PASS_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)
	ON_EVENT(CChildWnd,ACROSS_PASS_SOFT_PLAYER_ID,197,FlashCallShockwaveflash,VTS_BSTR)
END_EVENTSINK_MAP()

// CChildWnd ��Ϣ�������

bool CChildWnd::Create(DWORD dwStyle, RECT& rect, CWnd* pParentWnd, UINT nID, bool transparence, unsigned char alpha,bool zoom_in)
{
	memset(m_image_path,0x0,sizeof(m_image_path));
	//��¼�¸�����
	m_parent_wnd = pParentWnd;
	m_zoom_in = zoom_in;

	if (transparence)
	{
		CRect rcParent;
		pParentWnd->GetWindowRect(rcParent);
		rect.left += rcParent.left;
		rect.right += rcParent.left;
		rect.top += rcParent.top;
		rect.bottom += rcParent.top;

		dwStyle |= WS_POPUP;
	}
    
	//ע��һ��������
	CString class_name = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS,   \
		::LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	//����һ������
	if (FALSE == CWnd::CreateEx(0, class_name, NULL, dwStyle , rect, pParentWnd, nID))
	{
		return false;
	}

	// Set Transparent window attribute.
	if (transparence)
	{
		SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE, GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000); 
		HINSTANCE hInst = LoadLibrary(L"User32.DLL"); 
		if (hInst)
		{
			typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
			MYFUNC fun = NULL; 
			//ȡ��SetLayeredWindowAttributes����ָ�� 
			fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
			if(fun)fun(this->GetSafeHwnd(), 0, alpha, 2); 
			FreeLibrary(hInst); 
		}
	}

	return true;	
}

LRESULT CChildWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(message)
	{
	case WM_LBUTTONUP:          //���̧������Ӧ
	case DM_SCREEN_VIDEO_CLICK:
		{
			if (m_zoom_in)
			{
				int nID = GetDlgCtrlID();
				//����Ŵ�
				double last_time = m_zoom_timer.last_time();
				if (last_time>AVOID_CUT_MIN_TIME_LENGTH)
				{
					//�������������Ϣ�������壬���зŴ����С
					if (MSQUARE_SCREEN_SHOW_WINDOW_ID == nID)
					{
						::PostMessage(m_parent_wnd->m_hWnd,DM_MSQURE_WINDOW_CLICK_MESSAGE,NULL,NULL);
					}
					else
					{
						::PostMessage(m_parent_wnd->m_hWnd,DM_SCREEN_VIDEO_CLICK,NULL,NULL);
					}
					//���¼�ʱ
					m_zoom_timer.start();
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
		{
			if (m_message_handle)
			{
				//::PostMessage(m_message_handle,message,wParam,lParam);
				::PostMessage(m_message_handle,DM_SHOW_WALL_PANEL_MESSAGE,wParam,lParam);
			}
		}
		break;
	default:
		break;
	}

	return CWnd::WindowProc(message, wParam, lParam);
}

void CChildWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� 
	//CWnd::OnPaint();
	if (0!=_tcscmp(m_image_path,L""))
	{
		//��ʾ
		show_image();
	}
}

bool CChildWnd::set_message_handle(HWND hwnd)
{
	try
	{
		m_message_handle = hwnd;
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void CChildWnd::show_window(bool cmd_show)
{
	try
	{
		CWnd *child_wnd=NULL;

		if (cmd_show)
		{
			//��ʾ
			BringWindowToTop();
			ShowWindow(SW_SHOW);
			Invalidate();
			UpdateWindow();
			//�õ��Ӵ���
			child_wnd = FindWindowEx(m_hWnd,NULL,NULL,NULL);
			if (child_wnd)
			{
				//�Ӵ��ڴ��ڣ�ˢ��һ��
				child_wnd->BringWindowToTop();
				child_wnd->ShowWindow(SW_SHOW);
				child_wnd->Invalidate();
				child_wnd->UpdateWindow();
			}
		}
		else
		{
			//����
			MoveWindow(0,0,0,0);
			ShowWindow(SW_HIDE);
			//�õ��Ӵ���
			child_wnd = FindWindowEx(m_hWnd,NULL,NULL,NULL);
			if (child_wnd)
			{
				//�Ӵ��ڴ��ڣ�����
				child_wnd->ShowWindow(SW_HIDE);
			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

void CChildWnd::FlashCallShockwaveflash(LPCTSTR request)
{
	// TODO: �ڴ˴������Ϣ����������
	try
	{
		if (0!=m_message_handle)
		{
			::SendMessage(m_message_handle,DM_SUB_WINDOW_MESSAGE,(WPARAM)request,NULL);
		}
	}
	catch (...)
	{

	}

	return;
}

void CChildWnd::set_show_image(TCHAR *path)
{
	try
	{
		if (NULL==path)
		{
			return;
		}
		//����ͼƬ·��
		memset(m_image_path,0x0,sizeof(m_image_path));
		_tcscpy(m_image_path,path);

		//��ʾ
		show_image();

		//ˢ����Ļ
		Invalidate(TRUE);
		UpdateWindow();

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void CChildWnd::show_image(void)
{
	try
	{
		Graphics image_graphics(m_hWnd);
		Image *bg_image=NULL;
		CRect window_rect;
		RectF image_rect;
		//���ر���ͼƬ
		bg_image = Image::FromFile(m_image_path);
		if (bg_image)
		{
			//�õ��ͻ�������
			GetClientRect(&window_rect);
			image_rect.X = window_rect.left*1.0f;
			image_rect.Y = window_rect.top*1.0f;
			image_rect.Width = window_rect.Width()*1.0f;
			image_rect.Height = window_rect.Height()*1.0f;
			//����ͼƬ
			image_graphics.DrawImage(bg_image,image_rect,0,0,bg_image->GetWidth()*1.0f,bg_image->GetHeight()*1.0f,UnitPixel);
			//�ͷ�
			delete bg_image;
			bg_image = NULL;
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}
// ChildWnd.cpp : 实现文件
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
	//开始计时
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

// CChildWnd 消息处理程序

bool CChildWnd::Create(DWORD dwStyle, RECT& rect, CWnd* pParentWnd, UINT nID, bool transparence, unsigned char alpha,bool zoom_in)
{
	memset(m_image_path,0x0,sizeof(m_image_path));
	//记录下父窗体
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
    
	//注册一个窗口类
	CString class_name = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS,   \
		::LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	//创建一个窗口
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
			//取得SetLayeredWindowAttributes函数指针 
			fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
			if(fun)fun(this->GetSafeHwnd(), 0, alpha, 2); 
			FreeLibrary(hInst); 
		}
	}

	return true;	
}

LRESULT CChildWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(message)
	{
	case WM_LBUTTONUP:          //鼠标抬起在响应
	case DM_SCREEN_VIDEO_CLICK:
		{
			if (m_zoom_in)
			{
				int nID = GetDlgCtrlID();
				//允许放大
				double last_time = m_zoom_timer.last_time();
				if (last_time>AVOID_CUT_MIN_TIME_LENGTH)
				{
					//鼠标点击，发送消息给父窗体，进行放大和缩小
					if (MSQUARE_SCREEN_SHOW_WINDOW_ID == nID)
					{
						::PostMessage(m_parent_wnd->m_hWnd,DM_MSQURE_WINDOW_CLICK_MESSAGE,NULL,NULL);
					}
					else
					{
						::PostMessage(m_parent_wnd->m_hWnd,DM_SCREEN_VIDEO_CLICK,NULL,NULL);
					}
					//重新计时
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
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 
	//CWnd::OnPaint();
	if (0!=_tcscmp(m_image_path,L""))
	{
		//显示
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
			//显示
			BringWindowToTop();
			ShowWindow(SW_SHOW);
			Invalidate();
			UpdateWindow();
			//得到子窗口
			child_wnd = FindWindowEx(m_hWnd,NULL,NULL,NULL);
			if (child_wnd)
			{
				//子窗口存在，刷新一下
				child_wnd->BringWindowToTop();
				child_wnd->ShowWindow(SW_SHOW);
				child_wnd->Invalidate();
				child_wnd->UpdateWindow();
			}
		}
		else
		{
			//隐藏
			MoveWindow(0,0,0,0);
			ShowWindow(SW_HIDE);
			//得到子窗口
			child_wnd = FindWindowEx(m_hWnd,NULL,NULL,NULL);
			if (child_wnd)
			{
				//子窗口存在，隐藏
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
	// TODO: 在此处添加消息处理程序代码
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
		//保存图片路径
		memset(m_image_path,0x0,sizeof(m_image_path));
		_tcscpy(m_image_path,path);

		//显示
		show_image();

		//刷新屏幕
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
		//加载背景图片
		bg_image = Image::FromFile(m_image_path);
		if (bg_image)
		{
			//得到客户端区域
			GetClientRect(&window_rect);
			image_rect.X = window_rect.left*1.0f;
			image_rect.Y = window_rect.top*1.0f;
			image_rect.Width = window_rect.Width()*1.0f;
			image_rect.Height = window_rect.Height()*1.0f;
			//绘制图片
			image_graphics.DrawImage(bg_image,image_rect,0,0,bg_image->GetWidth()*1.0f,bg_image->GetHeight()*1.0f,UnitPixel);
			//释放
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
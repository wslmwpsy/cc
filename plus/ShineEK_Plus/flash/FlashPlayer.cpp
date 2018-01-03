// FlashControl.cpp
//
// 扩展Flash控件
//

#include "StdAfx.h"
#include "FlashPlayer.h"
#include "../file/log.h"

#pragma warning(disable: 4312 4311)

CFlashPlayer* CFlashPlayer::pPlayerThis = 0;
game_flash_player* game_flash_player::pGameThis=0;  //游戏窗口
bool m_intercept_flash_msg=true;   //拦截flash消息，找到加密狗了才响应

CFlashPlayer::CFlashPlayer()
{
	if(NULL==pPlayerThis)
	{
		pPlayerThis = this;
    	m_proc = NULL;
	}
	m_intercept_flash_msg=true;
}

CFlashPlayer::~CFlashPlayer()
{
}

void CFlashPlayer::change_intercept_msg_flag(bool flag)
{
    m_intercept_flash_msg = flag;
}

void CFlashPlayer::EnableNotification()
{
	m_proc = (FARPROC)GetWindowLong(m_hWnd, GWL_WNDPROC);
	if (0!=m_proc)
	{
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)Proc);
	}
}

LRESULT CFlashPlayer::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	try
	{
		if (NULL==pPlayerThis)
		{
			return 0;
		}

		if (IsWindow(pPlayerThis->m_hWnd) == FALSE)
		{
			return 0;
		}

		CWnd* pParent = pPlayerThis->GetParent();

		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:	// 将鼠标点击事件传回父窗口
		case WM_MOUSEMOVE:      //屏蔽鼠标移动事件
			{
				LRESULT result=0;

				if (!m_intercept_flash_msg)  //拦截flash的鼠标消息
				{
					// 执行默认处理
					result = CallWindowProc((WNDPROC)pPlayerThis->m_proc, hWnd, uMsg, wParam, lParam);
				}
				
				// 若存在父窗口，则将消息传递上去
				if (pParent && (NULL!=pParent->m_hWnd))
				{
					int xPos = LOWORD(lParam);
					int yPos = HIWORD(lParam);

					CRect rc, rcParent;
					pPlayerThis->GetWindowRect(rc);
					pParent->GetWindowRect(rcParent);

					lParam = MAKELONG(xPos+(rc.left-rcParent.left), yPos+(rc.top-rcParent.top));

					pParent->PostMessage(uMsg, wParam, lParam);
				}
				return result;
			}
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
			{
				//LRESULT result = CallWindowProc((WNDPROC)pThis->m_proc, hWnd, uMsg, wParam, lParam);
				if (pParent && (NULL!=pParent->m_hWnd))
				{
					pParent->PostMessage(uMsg, wParam, lParam);
				}
				return 0;
			}
		case WM_KEYUP:
		case WM_KEYDOWN:
		case WM_CHAR:
			{
				LRESULT result = CallWindowProc((WNDPROC)pPlayerThis->m_proc, hWnd, uMsg, wParam, lParam);
				if (pParent && (NULL!=pParent->m_hWnd))
				{
					pParent->PostMessage(uMsg, wParam, lParam);
				}
				return result;
			} 
		default:	// 处理缺省操作
			return CallWindowProc((WNDPROC)pPlayerThis->m_proc, hWnd, uMsg, wParam, lParam);
		}
	}
	catch (...)
	{
		//WriteLog(__FL__, L"flash player的消息处理");
	}
	return 0;
}


game_flash_player::game_flash_player()
{
	if(NULL==pGameThis)
	{
		pGameThis = this;
		m_game_proc = NULL;
	}
}

game_flash_player::~game_flash_player()
{

}

void game_flash_player::EnableNotification(void)
{
    m_game_proc = (FARPROC)GetWindowLong(m_hWnd, GWL_WNDPROC);
	if (0!=m_game_proc)
	{
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)GameWndProc);
	}

	return;
}

LRESULT game_flash_player::GameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	try
	{
		if (NULL==pGameThis)
		{
			return 0;
		}

		if (IsWindow(pGameThis->m_hWnd) == FALSE)
		{
			return 0;
		}

		CWnd* pParent = pGameThis->GetParent();

		switch (uMsg)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			{
				LRESULT result = CallWindowProc((WNDPROC)pGameThis->m_game_proc, hWnd, uMsg, wParam, lParam);
				if (pParent && (NULL!=pParent->m_hWnd))
				{
					pParent->PostMessage(uMsg, wParam, lParam);
				}
				return result;
			}
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
			{
				//屏蔽右键
				return 0;
			}
		default:	// 处理缺省操作
			return CallWindowProc((WNDPROC)pGameThis->m_game_proc, hWnd, uMsg, wParam, lParam);
		}
	}
	catch (...)
	{
	}
	return 0;
}

new_flash_player::new_flash_player()
{

}

new_flash_player::~new_flash_player()
{

}
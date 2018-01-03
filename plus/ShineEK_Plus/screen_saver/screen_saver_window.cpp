// screen_saver_window.cpp : 实现文件
//

#include "stdafx.h"
#include "screen_saver_window.h"
#include ".\screen_saver_window.h"
#include "..\message.h"

#include <io.h>


// screen_saver_window

IMPLEMENT_DYNAMIC(screen_saver_window, CWnd)
screen_saver_window::screen_saver_window()
{
	play_ad_screen_saver = false;                    //是否播放广告屏保
	for (int i=0;i<SCREEN_SAVER_MAX_PICTURE_COUNT;i++)
	{
		memset(screen_saver_path[i],0x0,sizeof(screen_saver_path[i]));                 //屏保路径
	}
	memset(ad_screen_saver_path,0x0,sizeof(ad_screen_saver_path));              //广告的屏保路径
	m_screen_width = 0;
	m_screen_height = 0;
	repaint_timer_identifier=0;
	switch_screen_saver_timer_identifier=0;
	m_screen_saver_picture_count=0;
	m_play_screen_saver_index=0;
	add_width=0;                                 //增加的宽度
	add_heigth=0;                                //增加的高度
	m_end_paint=false;
}

screen_saver_window::~screen_saver_window()
{
}

// screen_saver_window 消息处理程序
BEGIN_MESSAGE_MAP(screen_saver_window, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


bool screen_saver_window::Create(CWnd *parent_wnd,int screen_width,int screen_height)
{
	HCURSOR hCursor = LoadCursor(NULL, NULL);
	// 创建主窗口
	BOOL bRet = CreateEx(0, AfxRegisterWndClass(NULL, hCursor, NULL, NULL),
		NULL, WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
		CRect(0, 0, screen_width, screen_height), parent_wnd, 0, NULL);
	m_screen_saver_picture.set_screen_rect(screen_width, screen_height);
	m_screen_width = screen_width;
	m_screen_height = screen_height;
	m_parent_handle = parent_wnd->m_hWnd;
	//得到增加比
	switch(m_screen_width)
	{
	case 1280:
		if (m_screen_height == 768)
		{
			add_width = 5;
			add_heigth = 3;
		}

		if (m_screen_height == 800)
		{
			add_width = 8;
			add_heigth = 5;
		}
		break;
	case 1440:
		if (m_screen_height == 900)
		{
			add_width = 8;
			add_heigth = 5;
		}
		break;
	case 900:
		if (m_screen_height == 1440)
		{
			add_width = 5;
			add_heigth = 8;
		}
		break;
	case 768:
		if (m_screen_height == 1280)
		{
			add_width = 3;
			add_heigth = 5;
		}
		else
		{
			add_width = 3;
			add_heigth = 4;
		}
		break;
	case 600:
		{
			add_width = 3;
			add_heigth = 4;
		}
		break;
	default:
		{
			add_width = 3;
			add_heigth = 4;
		}
		break;
	}
	if (bRet)
	{
		return true;
	}

	return false;;
}

int screen_saver_window::set_screen_saver_path(TCHAR *path)
{
	try
	{
		TCHAR file_path[256];
		BOOL result=false;
		intptr_t search_handle = -1;
		int char_pos=0;
		struct _wfinddata_t findData;

		memset(&findData, 0, sizeof(findData));
		
		swprintf(file_path,L"%s\\*.*",path);
		search_handle = _wfindfirst(file_path, &findData);
		if (-1!=search_handle)
		{
			do
			{
				const TCHAR* p = _tcsrchr(findData.name, '.');
				if(p != NULL && p != 0)
				{
					if ((_tcsicmp(p, L".jpg") == 0)	|| (_tcsicmp(p, L".bmp") == 0))	
					{

						swprintf(screen_saver_path[m_screen_saver_picture_count], L"%s\\%s",path,findData.name);
						m_screen_saver_picture_count ++;

						//如果超过最大数就不继续查找文件
						if(m_screen_saver_picture_count >= SCREEN_SAVER_MAX_PICTURE_COUNT)
							break;					
					}
				}
				memset(&findData, 0, sizeof(findData));
			}while (0==_wfindnext(search_handle, &findData));
		}
		
		//关闭文件查找
		_findclose(search_handle);
		
		return m_screen_saver_picture_count;
	}
	catch (...)
	{
		
	}
	return 0;
}

bool screen_saver_window::set_ad_screen_saver_path(TCHAR *path)
{
	try
	{
		if (NULL==path)
		{
			return false;
		}
		
		memset(ad_screen_saver_path,0x0,sizeof(ad_screen_saver_path));
		_tcscpy(ad_screen_saver_path,path);
		//设定显示模式
		set_show_mode();
		play_ad_screen_saver=true;
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void screen_saver_window::show_screen_saver(void)
{
	try
	{
		ShowWindow(SW_SHOW);
		//得到当前坐标
		GetCursorPos(&cursor_point);
		SetCursor(NULL);
		//启动重绘定时器
		repaint_timer_identifier = SetTimer(REPAINT_TIMER_EVENT_ID,50,NULL);
		m_show_screen_saver = true;
		if (!play_ad_screen_saver)
		{
			//设定显示模式
			set_show_mode();
			//启动定时器更新屏保
			switch_screen_saver_timer_identifier = SetTimer(SWITCH_SCREEN_SAVER_TIMER_EVENT_ID,m_screen_saver_show_time*1000,NULL);
		}

		return ;
	}
	catch (...)
	{
		
	}
	return ;
}

void screen_saver_window::hide_screen_saver(void)
{
	try
	{
		//杀死定时器
		if (0!=repaint_timer_identifier)
		{
			KillTimer(repaint_timer_identifier);
			repaint_timer_identifier=0;
		}
		if (0!=switch_screen_saver_timer_identifier)
		{
			KillTimer(switch_screen_saver_timer_identifier);
			switch_screen_saver_timer_identifier = 0;
		}
		//释放资源
		m_screen_saver_picture.unload_picture();
		ShowWindow(SW_HIDE);
		m_show_screen_saver = false;
		play_ad_screen_saver = false;
		::PostMessage(m_parent_handle,DM_SCREEN_SAVER_END,NULL,NULL);
	}
	catch (...)
	{
		
	}
	return;
}
LRESULT screen_saver_window::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(message)
	{		
	case WM_MOUSEMOVE:

		{
			int x_pos=0;
			int y_pos=0;

			x_pos = LOWORD(lParam);
			y_pos = HIWORD(lParam);
			if ((x_pos-cursor_point.x>20)||(x_pos-cursor_point.x<-20))
			{
				hide_screen_saver();
				return 0;
				break;
			}
			if ((y_pos-cursor_point.y>20)||(y_pos-cursor_point.y<-20))
			{
				hide_screen_saver();
				return 0;
				break;
			}
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_KEYDOWN:
		{
			hide_screen_saver();
			return 0;
		}
		break;
	default:
		break;
	}

	return CWnd::WindowProc(message, wParam, lParam);
}

void screen_saver_window::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	if(!m_show_screen_saver)
	{
		return;
	}

	if (play_ad_screen_saver)
	{
		m_screen_saver_picture.unload_picture();
		m_screen_saver_picture.Load(ad_screen_saver_path);
	}
	else
	{
		m_screen_saver_picture.unload_picture();
		m_screen_saver_picture.Load(screen_saver_path[m_play_screen_saver_index]);
		
	}
	//绘制区域
	paint_rect(dc);
	// 不为绘图消息调用 CWnd::OnPaint()
}

void screen_saver_window::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nIDEvent)
	{
	case REPAINT_TIMER_EVENT_ID:  //重绘定时器
		{
			if (!m_end_paint)
			{
				Invalidate();
			}
			break;
		}
	case SWITCH_SCREEN_SAVER_TIMER_EVENT_ID:  //切换屏保图片的定时器
		{
			//设定显示模式
			set_show_mode();
			m_play_screen_saver_index++;
			m_play_screen_saver_index %= m_screen_saver_picture_count;
		}
		break;
	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}


void screen_saver_window::set_show_time(int show_time)
{
	m_screen_saver_show_time = show_time;
	return;
}

void screen_saver_window::set_show_mode(void)
{
	//得到随机的显示模式
	int show_mode=0;

	//图片改变，需要重新绘制
	m_end_paint =false;

    show_mode = rand()/(RAND_MAX/SCREEN_SAVER_SHOW_MODE_COUNT+1);
	if (m_show_mode == (SCREEN_SAVER_SHOW_MODE)show_mode)
	{
		show_mode = rand()/(RAND_MAX/SCREEN_SAVER_SHOW_MODE_COUNT+1);
	}
	m_show_mode = (SCREEN_SAVER_SHOW_MODE)show_mode;
	//取消四周扩展的屏保模式
	if ((SCREEN_SAVER_CENTER_TO_AROUND==m_show_mode)||(SCREEN_SAVER_ZOON_IN==m_show_mode))
	{
		m_show_mode = SCREEN_SAVER_NO_ANIMATION;
	}
	switch(m_show_mode)
	{
	default:
	case SCREEN_SAVER_NO_ANIMATION:   //直接显示没有动画效果
		{
			show_rect.left = 0;
			show_rect.right = m_screen_width;
			show_rect.top = 0;
			show_rect.bottom=m_screen_height;
		}
		break;
	case SCREEN_SAVER_RIGHT_TO_LEFT:  //从右到左
		{
			show_rect.left = m_screen_width;
			show_rect.right = m_screen_width+16;
			show_rect.top = 0;
			show_rect.bottom=m_screen_height;
		}
		break;
	case SCREEN_SAVER_LEFT_TO_RIGHT:  //从左到右
		{
			show_rect.left = -16;
			show_rect.right = 0;
			show_rect.top = 0;
			show_rect.bottom=m_screen_height;
		}
		break;
	case SCREEN_SAVER_MIDDLE_TO_SIDES_X: //水平方向从中间到两边
		{
			show_rect.left = m_screen_width/2;
			show_rect.right = m_screen_width/2+16;
			show_rect.top = 0;
			show_rect.bottom=m_screen_height;

			show_rect1.left = m_screen_width/2-16;
			show_rect1.right = m_screen_width/2;
			show_rect1.top = 0;
			show_rect1.bottom=m_screen_height;

		}
		break;
	case SCREEN_SAVER_MIDDLE_TO_SIDES_Y: //垂直方向从中间到两边
		{
			show_rect.left = 0;
			show_rect.right = m_screen_width;
			show_rect.top = m_screen_height/2;
			show_rect.bottom=m_screen_height/2+16;

			show_rect1.left = 0;
			show_rect1.right = m_screen_width;
			show_rect1.top = m_screen_height/2-16;
			show_rect1.bottom=m_screen_height/2;
		}
		break;
	case SCREEN_SAVER_CENTER_TO_AROUND: //从中心到四周
	case SCREEN_SAVER_ZOON_IN:          //放大
		{
			show_rect.left = m_screen_width / 2;
			show_rect.top = m_screen_height / 2 - add_heigth *4;
			show_rect.right = m_screen_width / 2;
			show_rect.bottom = m_screen_height / 2 + add_heigth *4;
		}
		break;
	}
	return;
}

void screen_saver_window::paint_rect(CPaintDC &dc)
{
	switch(m_show_mode)
	{
    default:
	case SCREEN_SAVER_NO_ANIMATION:   //直接显示没有动画效果
		{
			show_rect.left = 0;
			show_rect.right = m_screen_width;
			show_rect.top = 0;
			show_rect.bottom=m_screen_height;

			//显示图片
			m_screen_saver_picture.Show(dc.m_hDC,show_rect,SCREEN_SAVER_NO_ANIMATION);

			//结束绘制
			m_end_paint = true;
		}
		break;
	case SCREEN_SAVER_RIGHT_TO_LEFT: //从右到左
		{
			if (show_rect.left>=0)
			{
				show_rect.left -=16;
				show_rect.right -=16;
				//显示图片
				m_screen_saver_picture.Show(dc.m_hDC,show_rect,SCREEN_SAVER_RIGHT_TO_LEFT);
			}
			else
			{
				//结束绘制
				m_end_paint = true;
			}
		}
		break;
	case SCREEN_SAVER_LEFT_TO_RIGHT: //从左到右
		{
			if (show_rect.right<=m_screen_width)
			{
				show_rect.left +=16;
				show_rect.right +=16;
				//显示图片
				m_screen_saver_picture.Show(dc.m_hDC,show_rect,SCREEN_SAVER_LEFT_TO_RIGHT);
			}
			else
			{
				//结束绘制
				m_end_paint = true;
			}
			
		}
		break;
	case SCREEN_SAVER_MIDDLE_TO_SIDES_X: //水平方向从中间到两边
		{
			if (show_rect.left>=0)
			{
				show_rect.left -= 16;
				show_rect.right -= 16;
			}
			if (show_rect1.right<=m_screen_width)
			{
				show_rect1.left += 16;
				show_rect1.right += 16;
			}
			//显示图片
			m_screen_saver_picture.Show(dc.m_hDC,show_rect,SCREEN_SAVER_MIDDLE_TO_SIDES_X);
			m_screen_saver_picture.Show(dc.m_hDC,show_rect1,SCREEN_SAVER_MIDDLE_TO_SIDES_X);
			if ((show_rect.left<=0) && (show_rect1.right>=m_screen_width))
			{
				//结束绘制
				m_end_paint = true;
			}
		}
		break;
	case SCREEN_SAVER_MIDDLE_TO_SIDES_Y: //垂直方向从中间到两边
		{
			if (show_rect.top>=0)
			{
				show_rect.top -= 16;
				show_rect.bottom -= 16;
			}
			if (show_rect1.bottom<=m_screen_height)
			{
				show_rect1.top += 16;
				show_rect1.bottom += 16;
			}
			//显示图片
			m_screen_saver_picture.Show(dc.m_hDC,show_rect,SCREEN_SAVER_MIDDLE_TO_SIDES_Y);
			m_screen_saver_picture.Show(dc.m_hDC,show_rect1,SCREEN_SAVER_MIDDLE_TO_SIDES_Y);
			if ((show_rect.top<=0) && (show_rect1.bottom>=m_screen_height))
			{
				//结束绘制
				m_end_paint = true;
			}
		}
		break;
	case SCREEN_SAVER_CENTER_TO_AROUND: //从中心到四周
		{
			if ((show_rect.top>=0)||(show_rect.right<=m_screen_width) )
			{
				show_rect.left -= add_width*4;
				show_rect.right += add_width*4;
				show_rect.top -= add_heigth*4;
				show_rect.bottom += add_heigth*4;

				//左面区
				show_rect1.left = show_rect.left;
				show_rect1.right = show_rect1.left + add_width*4;
				show_rect1.top = show_rect.top;
				show_rect1.bottom=show_rect.bottom;
				m_screen_saver_picture.Show(dc.m_hDC,show_rect1,SCREEN_SAVER_CENTER_TO_AROUND);

				//右面
				show_rect1.left = show_rect.right - add_width*4;
				show_rect1.right = show_rect.right;
				show_rect1.top = show_rect.top;
				show_rect1.bottom=show_rect.bottom;
				m_screen_saver_picture.Show(dc.m_hDC,show_rect1,SCREEN_SAVER_CENTER_TO_AROUND);

				//上面
				show_rect1.left = show_rect.left + add_width*4;
				show_rect1.right = show_rect.right - add_width*4;
				show_rect1.top = show_rect.top;
				show_rect1.bottom=show_rect1.top + add_heigth*4;
				m_screen_saver_picture.Show(dc.m_hDC,show_rect1,SCREEN_SAVER_CENTER_TO_AROUND);

				//下面
				show_rect1.left = show_rect.left + add_width*4;
				show_rect1.right = show_rect.right - add_width*4;
				show_rect1.top = show_rect.bottom - add_heigth*4;
				show_rect1.bottom=show_rect.bottom;
				m_screen_saver_picture.Show(dc.m_hDC,show_rect1,SCREEN_SAVER_CENTER_TO_AROUND);

			}
			else
			{
				//结束绘制
				m_end_paint = true;
			}
		}
		break;
    case SCREEN_SAVER_ZOON_IN://放大
		{
			if ((show_rect.left>=0)||(show_rect.top>=0))
			{
				show_rect.left -= add_width*4;
				show_rect.right += add_width*4;
				show_rect.top -= add_heigth*4;
				show_rect.bottom += add_heigth*4;

				m_screen_saver_picture.Show(dc.m_hDC,show_rect,SCREEN_SAVER_ZOON_IN);
			}
			else
			{
				//结束绘制
				m_end_paint = true;
			}
		}
		break;
	}
}
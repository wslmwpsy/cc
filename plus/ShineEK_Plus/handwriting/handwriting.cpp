// handwriting.cpp : 实现文件
//

#include "stdafx.h"
#include "handwriting.h"
#include ".\handwriting.h"
#include "..\message.h"
#include "..\file\config_file.h"
#include "..\common\parser_color.h"

// handwriting

IMPLEMENT_DYNAMIC(handwriting, CWnd)
handwriting::handwriting()
{
}

handwriting::~handwriting()
{
}


BEGIN_MESSAGE_MAP(handwriting, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// handwriting 消息处理程序


LRESULT handwriting::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(message)
	{
		case MSG_INK_COLLECTOR_STROKE: //收集器完成一笔画，发送的消息
			{
				//识别文字
				m_ink_recognition.on_recognizer();
				//得到识别的结果
				m_ink_recognition.get_recognize_result(m_ink_recognition_result);
				//把识别的结果发送给父窗口
				CWnd *parent_wnd = GetParent();
				::PostMessage(parent_wnd->m_hWnd,DM_INK_RECOGNITION_FINISH,NULL,(LPARAM)m_ink_recognition_result);
			}
			break;
		default:
			break;
	}

	return CWnd::WindowProc(message, wParam, lParam);
}

int handwriting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	try
	{
		config_file_manager config_file;

		//得到格子的颜色
		m_foreground_color = config_file.read_integer(L"handwriting",L"line_color",4792714);
		//得到背景颜色
		m_background_color = config_file.read_integer(L"handwriting",L"background_color",2363714);
		//得到画笔颜色
		m_pen_color = config_file.read_integer(L"handwriting",L"pen_color",187622);

		//初始化手写控件
		CRect rect;
		GetClientRect(&rect);
		m_ink_recognition.init_ink_control(m_hWnd,INK_RECOGNIZE_ALTERNATE_NUMS,rect.left,rect.right,rect.top,rect.bottom);
		//设置画笔属性
		m_ink_recognition.set_pen_attribute(m_pen_color,120.0);
	}
	catch (...)
	{
		
	}
	return 0;
}

bool handwriting::Create(DWORD dwStyle, RECT& rect, CWnd* pParentWnd, UINT nID, bool transparence, unsigned char alpha,bool zoom_in)
{
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

	if (FALSE == CWnd::CreateEx(0, AfxRegisterWndClass(NULL), NULL, dwStyle , rect, pParentWnd, nID))
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

bool handwriting::clear_ink_window(void)
{
	return m_ink_recognition.clear_window();
}

bool handwriting::change_ink_recognize_language(int language)
{
	return m_ink_recognition.set_language((enum INK_RECOGNIZER_LANGUAGE)language);
}

void handwriting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	try
	{
		//填充背景
		CRect rect;     
		GetClientRect(rect);
		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = m_foreground_color;


		//刷背景
		CBrush brush;
		brush.CreateSolidBrush(m_background_color);
		dc.SelectObject(brush);
		//画格子
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, m_foreground_color);
		dc.SelectObject(&pen);
		dc.Rectangle(rect);
		pen.DeleteObject();

		pen.CreatePen(PS_DASHDOT,1,&logBrush);
		dc.SelectObject(&pen);
		dc.MoveTo(rect.left,rect.top);
		dc.LineTo(rect.right,rect.bottom);

		dc.MoveTo(rect.right,rect.top);
		dc.LineTo(rect.left,rect.bottom);

		dc.MoveTo(rect.left,rect.bottom/2);
		dc.LineTo(rect.right,rect.bottom/2);

		dc.MoveTo(rect.right/2,rect.top);
		dc.LineTo(rect.right/2,rect.bottom);
		pen.DeleteObject();

		brush.DeleteObject();
	}
	catch (...)
	{

	}
	// 不为绘图消息调用 CWnd::OnPaint()
}


bool handwriting::change_handwriting_board_color(COLORREF fore_color,COLORREF background_color,long pen_color)
{
	try
	{
		//保存改变的颜色
		m_foreground_color = fore_color;
		m_background_color = background_color;
		m_pen_color = pen_color;

		//设置画笔属性
		m_ink_recognition.set_pen_attribute(m_pen_color,120.0);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}
// handwriting.cpp : ʵ���ļ�
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



// handwriting ��Ϣ�������


LRESULT handwriting::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(message)
	{
		case MSG_INK_COLLECTOR_STROKE: //�ռ������һ�ʻ������͵���Ϣ
			{
				//ʶ������
				m_ink_recognition.on_recognizer();
				//�õ�ʶ��Ľ��
				m_ink_recognition.get_recognize_result(m_ink_recognition_result);
				//��ʶ��Ľ�����͸�������
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

	// TODO:  �ڴ������ר�õĴ�������
	try
	{
		config_file_manager config_file;

		//�õ����ӵ���ɫ
		m_foreground_color = config_file.read_integer(L"handwriting",L"line_color",4792714);
		//�õ�������ɫ
		m_background_color = config_file.read_integer(L"handwriting",L"background_color",2363714);
		//�õ�������ɫ
		m_pen_color = config_file.read_integer(L"handwriting",L"pen_color",187622);

		//��ʼ����д�ؼ�
		CRect rect;
		GetClientRect(&rect);
		m_ink_recognition.init_ink_control(m_hWnd,INK_RECOGNIZE_ALTERNATE_NUMS,rect.left,rect.right,rect.top,rect.bottom);
		//���û�������
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
			//ȡ��SetLayeredWindowAttributes����ָ�� 
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
	// TODO: �ڴ˴������Ϣ����������
	try
	{
		//��䱳��
		CRect rect;     
		GetClientRect(rect);
		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = m_foreground_color;


		//ˢ����
		CBrush brush;
		brush.CreateSolidBrush(m_background_color);
		dc.SelectObject(brush);
		//������
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
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
}


bool handwriting::change_handwriting_board_color(COLORREF fore_color,COLORREF background_color,long pen_color)
{
	try
	{
		//����ı����ɫ
		m_foreground_color = fore_color;
		m_background_color = background_color;
		m_pen_color = pen_color;

		//���û�������
		m_ink_recognition.set_pen_attribute(m_pen_color,120.0);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}
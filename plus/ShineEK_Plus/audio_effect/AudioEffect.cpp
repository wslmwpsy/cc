// AudioEffect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AudioEffect.h"
#include ".\audioeffect.h"
#include "..\parserxml\Markup.h"
#include "..\file\config_file.h"
#include "..\message.h"
#include "..\file\log.h"

#include <shlwapi.h>
// CAudioEffect

IMPLEMENT_DYNAMIC(CAudioEffect, CWnd)
CAudioEffect::CAudioEffect()
{
}

CAudioEffect::~CAudioEffect()
{
}


BEGIN_MESSAGE_MAP(CAudioEffect, CWnd)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



// CAudioEffect ��Ϣ�������


LRESULT CAudioEffect::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			if (m_response_mouse_event)
			{
				//���ڶ�ȡ���ݣ���Ҫ��Ӧ�κ�����¼�
				break;
			}

			//�õ������x,y����
			m_mouse_click_point.x = LOWORD(lParam);
			m_mouse_click_point.y = HIWORD(lParam);
			//�����߳��ж�����¼�
			AfxBeginThread(CAudioEffect::reponse_mouse_thread,this);
		}
		break;
	default:
		break;
	}

	return CWnd::WindowProc(message, wParam, lParam);
}

UINT CAudioEffect::reponse_mouse_thread(LPVOID pParam)
{
	CAudioEffect *pThis = reinterpret_cast<CAudioEffect *>(pParam);

	return pThis->reponse_mouse_event();
}

UINT CAudioEffect::reponse_mouse_event(void)
{
	//���ñ�ʾ
	m_response_mouse_event =true;

	try
	{
		TCHAR control_number[256];
		TCHAR control_type[256];
		TCHAR group_flag[256];
		int radio_value=0;
		int min_value=0;
		int max_value=0;
		bool result=false;

		//����Ƿ���а�ť
		result = check_click_control_number(m_mouse_click_point,control_number,control_type,group_flag,radio_value,min_value,max_value);
		if (result)
		{
			//��Ӧ��Ӧ�¼�
			reponse_control_event(control_number,control_type,group_flag,radio_value,min_value,max_value);
		}
	}
	catch (...)
	{
		
	}

	//���ñ�ʾ
	m_response_mouse_event =false;

	return 0;
}

void CAudioEffect::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (Ok==m_audio_effect_image->GetLastStatus())
	{
		//�ͷſռ�
		delete m_audio_effect_image;
		m_audio_effect_image = NULL;
	}
	if (Ok==m_slider_bar_image->GetLastStatus())
	{
		delete m_slider_bar_image;
		m_slider_bar_image = NULL;
	}
	if (Ok==m_disable_effect_image->GetLastStatus())
	{
		delete m_disable_effect_image;
		m_disable_effect_image=NULL;
	}
	if (Ok==m_highlight_status_image->GetLastStatus())
	{
		delete m_highlight_status_image;
		m_highlight_status_image=NULL;
	}
	if (Ok==m_draw_image->GetLastStatus())
	{
		delete m_draw_image;
		m_draw_image=NULL;
	}

	CWnd::OnClose();
}

int CAudioEffect::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	config_file_manager config_file;
	RECT client_rect;
	int image_width=0;
	int image_heith=0;
	int com_number=0;
	std::wstring com_para;
	bool result=false;
	int timer_elapse=0;
	std::wstring item_value;
	TCHAR path[256];

	try
	{
		//��ʼ�������ļ�
		config_file.init(L"audio_effect\\config.ini");
		//����ͼƬ��С�޸Ĵ���
		GetClientRect(&client_rect);

		m_audio_effect_image = Image::FromFile(m_src_image_path);
		if (m_audio_effect_image&&(Ok==m_audio_effect_image->GetLastStatus()))
		{
			image_width = m_audio_effect_image->GetWidth();
			image_heith = m_audio_effect_image->GetHeight();
			//�ƶ�����λ��
			MoveWindow(client_rect.left+(client_rect.right-client_rect.left-image_width)/2,client_rect.top+(client_rect.bottom-client_rect.top-image_heith)/2,image_width,image_heith);
			//��¡һ�����Ƶ�ͼ
			m_draw_image = m_audio_effect_image->Clone();
		}
		//����slider������
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\audio_effect\\bar.jpg",m_work_path);
		m_slider_bar_image = Image::FromFile(path);
		//��������ͼƬ
		item_value = config_file.read_string(L"setting",L"disable_bg_image",L"");
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
		m_disable_effect_image = Image::FromFile(path);
		//���ظ���ͼƬ
		item_value = config_file.read_string(L"setting",L"highlight_image",L"");
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
		m_highlight_status_image = Image::FromFile(path);

		//�򿪴���
		com_number = config_file.read_integer(L"setting",L"com_port",1);
		com_para = config_file.read_string(L"setting",L"comm_parameter",L"9600,N,8,1");
		result = m_audio_effect_com.open(com_number,com_para.c_str());
		result = m_audio_effect_com.is_open();
		if (result)
		{
			WriteLog(__FL__, L"��Ч�����ڴ򿪳ɹ�");
		}
		else
		{
			WriteLog(__FL__, L"��Ч�����ڴ�ʧ��");
		}

		//������ʱ�������ʹ�������
		timer_elapse = config_file.read_integer(L"setting",L"send_elapse",100);
		if (timer_elapse<100)
		{
			timer_elapse = 100;
		}
		SetTimer(1,timer_elapse,NULL);

		return 0;
	}
	catch (...)
	{

	}
	return 0;
}

BOOL CAudioEffect::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam,TCHAR *server_path)
{
	// TODO: �ڴ����ר�ô����/����û���
	config_file_manager config_file;
	bool result=false;
	std::wstring item_value;
	

	memset(m_work_path,0x0,sizeof(m_work_path));
	memset(m_config_path,0x0,sizeof(m_config_path));
	memset(m_skin_config_path,0x0,sizeof(m_skin_config_path));
	memset(m_protocol_config_path,0x0,sizeof(m_protocol_config_path));
	memset(m_connect_command,0x0,sizeof(m_connect_command));
	m_connect_command_len = 0;
	memset(m_idless_command,0x0,sizeof(m_idless_command));
	memset(m_tip_message,0x0,sizeof(m_tip_message));
	memset(m_upload_server_path,0x0,sizeof(m_upload_server_path));
	m_idless_command_len = 0;
	m_connect_success=false;
	m_response_mouse_event=false;

	//�õ�����·��
	GetModuleFileName(NULL,m_work_path,sizeof(m_work_path));
	PathRemoveFileSpec(m_work_path);
	//��ʼ�������ļ�
	config_file.init(L"audio_effect\\config.ini");
	//���������·��
	_tcscpy(m_upload_server_path,server_path);

	//�Ƿ�������Ч����
	swprintf(m_config_path,L"%s\\audio_effect\\config.ini",m_work_path);
	result = config_file.read_boolean(L"setting",L"use_audio_effect",false);
	if (!result)
	{
		return FALSE;
	}
	//�õ�Ƥ�������ļ���
	item_value = config_file.read_string(L"setting",L"skin_config",L"");
	swprintf(m_skin_config_path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
	//�õ�����Э���ļ���
	item_value = config_file.read_string(L"setting",L"Protocol_file0",L"");
	swprintf(m_protocol_config_path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
	//�õ�ԭʼͼƬ·��
	item_value = config_file.read_string(L"setting",L"bg_image",L"");
	swprintf(m_src_image_path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
	
	//��ȡ��������
	item_value = config_file.read_string(L"setting",L"connect_command",L"");
	if (!item_value.empty())
	{
		parse_com_value(item_value.c_str(),m_connect_command,m_connect_command_len);
	}
	//��������
	item_value = config_file.read_string(L"setting",L"idless_command",L"");
	if (!item_value.empty())
	{
		parse_com_value(item_value.c_str(),m_idless_command,m_idless_command_len);
	}

	return CWnd::CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, lpParam);
}

void CAudioEffect::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	Graphics draw_graphics(m_hWnd);
	RectF show_rect;
	REAL image_width=0.0f;
	REAL image_heith=0.0f;

	//����ͼ
	draw_window();

	image_width = m_draw_image->GetWidth()*1.0f;
	image_heith = m_draw_image->GetHeight()*1.0f;
	show_rect.X = 0.0f;
	show_rect.Y = 0.0f;
	show_rect.Width = image_width;
	show_rect.Height = image_heith;
	//�ػ���
	draw_graphics.DrawImage(m_draw_image,show_rect,0,0,image_width,image_heith,UnitPixel);

	return;
}

void CAudioEffect::draw_window(void)
{
	try
	{
		if (Ok!=m_draw_image->GetLastStatus())
		{
			return;
		}
		Graphics audio_effect_graphics(m_draw_image);
		CMarkup parse_xml;
		REAL image_width=0.0f;
		REAL image_heith=0.0f;
		RectF show_rect;

		if (Ok==m_audio_effect_image->GetLastStatus())
		{
			image_width = m_audio_effect_image->GetWidth()*1.0f;
			image_heith = m_audio_effect_image->GetHeight()*1.0f;
			//���Ʊ���ͼ
			show_rect.X = 0;
			show_rect.Y = 0;
			show_rect.Width = image_width;
			show_rect.Height = image_heith;
			Status image_status = audio_effect_graphics.DrawImage(m_audio_effect_image,show_rect,0,0,image_width,image_heith,UnitPixel);
			//��ʾ����
			show_control_value(audio_effect_graphics);
			//���Ʋ��ɲ�������͸�������
			draw_disable_highlight_rect(audio_effect_graphics);
		}
	}
	catch (...)
	{

	}

	return;
}

bool CAudioEffect::show_control_value(Graphics &text_graphic)
{
	try
	{
        CMarkup parse_xml_markup;
		CMarkup pares_skin_xml;
		std::wstring item_value;
		std::wstring control_number;
		int control_left=0;
		int control_top=0;
		int control_right=0;
		int control_bottom=0;
		bool result=false;
		Font myFont(L"΢���ź�",16,FontStyleRegular);
		StringFormat text_format;
        SolidBrush text_brush(Color(255,255,255,255));
		RectF show_rect;
		int max_value=0;
		int min_value=0;
		int cur_value=0;
		config_file_manager config_file;

		text_format.SetAlignment(StringAlignmentCenter);
		text_format.SetLineAlignment(StringAlignmentCenter);

		//����Э���xml
		result = parse_xml_markup.Load(m_protocol_config_path);
		if (!result)
		{
			return false;
		}
		parse_xml_markup.ResetPos();
		result = parse_xml_markup.FindChildElem();
		if (!result)
		{
			return false;
		}
		parse_xml_markup.IntoElem();
		//����Ƥ����xml
		result = pares_skin_xml.Load(m_skin_config_path);
		if (!result)
		{
			return false;
		}
		pares_skin_xml.ResetPos();
		result = pares_skin_xml.FindChildElem();
		if (!result)
		{
			return false;
		}
		pares_skin_xml.IntoElem();
		do 
		{
			//�޸�edit����ʾֵ
			item_value = parse_xml_markup.GetAttrib(L"edit_show_key");
			if (!item_value.empty())
			{
				pares_skin_xml.ResetMainPos();
				do 
				{
					control_number = pares_skin_xml.GetAttrib(L"key");
					if (item_value==control_number)
					{
						//�õ���ʾ����
						item_value = pares_skin_xml.GetAttrib(L"rect");
						swscanf(item_value.c_str(),L"%d,%d,%d,%d",&control_left,&control_top,&control_right,&control_bottom);
						show_rect.X = control_left*1.0f;
						show_rect.Y = control_top*1.0f;
						show_rect.Width = (control_right-control_left)*1.0f;
						show_rect.Height = (control_bottom-control_top)*1.0f;
						//�õ�Ҫ��ʾ��ֵ
						control_number = parse_xml_markup.GetAttrib(L"cur_value");
						item_value = parse_xml_markup.GetAttrib(L"show_value");
						if (!item_value.empty())
						{
							int src_value=0;
							int change_value=0;
							TCHAR show_value[256];
							
							memset(show_value,0x0,sizeof(show_value));

							//��ʾ��ֵ�����ø���Ч����ֵ��һ������Ҫ����
							if (0==_tcsncmp(item_value.c_str(),L"N",1))
							{
								//�ۼ�һ������ֵ
								swscanf(control_number.c_str(),L"%d",&src_value);
								swscanf(item_value.c_str()+2,L"%d",&change_value);
								swprintf(show_value,L"%d",src_value+change_value);
								control_number.assign(show_value);
							}
							else
							{
								//���ļ���ȡ��ʾ��ֵ
								_tcscpy(show_value,L"audio_effect\\");
								_tcscpy(show_value+_tcslen(show_value),item_value.c_str()+2);
								//�������ļ��ж�ȡ
								config_file.init(show_value);
								control_number = config_file.read_string(L"CorrespondValue",control_number.c_str(),L"");
							}
						}
						//��ʾ
						text_graphic.DrawString(control_number.c_str(),-1,&myFont,show_rect,&text_format,&text_brush);
						break;
					}
					result = pares_skin_xml.FindElem();
				} while (result);
			}
			//�޸�slider��ֵ
			item_value = parse_xml_markup.GetAttrib(L"slider_show_key");
			if (!item_value.empty())
			{
				pares_skin_xml.ResetMainPos();
				do 
				{
					control_number = pares_skin_xml.GetAttrib(L"key");
					if (item_value==control_number)
					{
						//�õ���ʾ����
						item_value = pares_skin_xml.GetAttrib(L"rect");
						swscanf(item_value.c_str(),L"%d,%d,%d,%d",&control_left,&control_top,&control_right,&control_bottom);
						item_value = pares_skin_xml.GetAttrib(L"max_value");
						swscanf(item_value.c_str(),L"%d",&max_value);
						item_value = pares_skin_xml.GetAttrib(L"min_value");
						swscanf(item_value.c_str(),L"%d",&min_value);
						item_value = parse_xml_markup.GetAttrib(L"cur_value");
						swscanf(item_value.c_str(),L"%d",&cur_value);
						//��ʾ
						int tmp = m_slider_bar_image->GetHeight();
						tmp = m_slider_bar_image->GetWidth();
						text_graphic.DrawImage(m_slider_bar_image,control_left+2,control_bottom-(cur_value-min_value)*(control_bottom-control_top)/(max_value-min_value)-3,0,0,m_slider_bar_image->GetWidth(),m_slider_bar_image->GetHeight(),UnitPixel);

						break;
					}
					result = pares_skin_xml.FindElem();
				} while (result);
			}

			result = parse_xml_markup.FindElem();
		} while (result);


		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool CAudioEffect::draw_disable_highlight_rect(Graphics &text_graphic)
{
	try
	{
		CMarkup parse_xml_markup;
		std::wstring item_value;
		bool result=false;
		int control_left=0;
		int control_top=0;
		int control_right=0;
		int control_bottom=0;
		RectF control_rect;
		bool return_result=false;
		TCHAR cur_value[256];
		Font myFont(L"΢���ź�",24,FontStyleRegular);
		StringFormat text_format;
		SolidBrush text_brush(Color(255,255,215,0));

		text_format.SetAlignment(StringAlignmentCenter);
		text_format.SetLineAlignment(StringAlignmentCenter);

		result = parse_xml_markup.Load(m_skin_config_path);
		if (!result)
		{
			return false;
		}
		parse_xml_markup.ResetPos();
		result = parse_xml_markup.FindChildElem();
		if (!result)
		{
			return false;
		}
		parse_xml_markup.IntoElem();
		do 
		{
			memset(cur_value,0x0,sizeof(cur_value));

			//�õ��ؼ�����
			item_value = parse_xml_markup.GetAttrib(L"rect");
			if (!item_value.empty())
			{
				swscanf(item_value.c_str(),L"%d,%d,%d,%d",&control_left,&control_top,&control_right,&control_bottom);
				control_rect.X = control_left*1.0f;
				control_rect.Y = control_top*1.0f;
				control_rect.Width = (control_right-control_left)*1.0f;
				control_rect.Height = (control_bottom-control_top)*1.0f;

				//�鿴�ؼ��Ƿ�ɲ���
				item_value = parse_xml_markup.GetAttrib(L"enable");
				if (0!=_tcscmp(item_value.c_str(),L"true"))
				{
					//���Ʋ��ɲ�������
					text_graphic.DrawImage(m_disable_effect_image,control_rect,control_rect.X,control_rect.Y,control_rect.Width,control_rect.Height,UnitPixel);
				}
				else
				{
					//���Ƹ�������
					item_value = parse_xml_markup.GetAttrib(L"type");
					if (0==_tcscmp(item_value.c_str(),L"radio"))
					{
						//��ѡ
						//�õ�����
						item_value = parse_xml_markup.GetAttrib(L"group_flag");
						//ͨ�����ţ��õ�radio��ѡ��ֵ
						get_control_cur_value(item_value.c_str(),cur_value);
						//�õ���ǰ��ѡ��ֵ
						item_value = parse_xml_markup.GetAttrib(L"order");
						if (0==_tcscmp(item_value.c_str(),cur_value))
						{
							//radio�ı�ŵ��ڵ�ǰѡ��ֵ������
							text_graphic.DrawImage(m_highlight_status_image,control_rect,control_rect.X,control_rect.Y,control_rect.Width,control_rect.Height,UnitPixel);
						}
					}
					else if (0==_tcscmp(item_value.c_str(),L"checkbox"))
					{
						//��ѡ��
						//�õ�����
						item_value = parse_xml_markup.GetAttrib(L"group_flag");
						//ͨ�����ţ��õ�checkbox��ֵ
						get_control_cur_value(item_value.c_str(),cur_value);
						if (0==_tcscmp(cur_value,L"1"))
						{
							//ѡ��״̬
							text_graphic.DrawImage(m_highlight_status_image,control_rect,control_rect.X,control_rect.Y,control_rect.Width,control_rect.Height,UnitPixel);
						}
					}
				}
				//�Ƿ�����ʾ��Ϣ��ʾ��
				item_value = parse_xml_markup.GetAttrib(L"type");
				if (0==_tcscmp(item_value.c_str(),L"msg_tip_static"))
				{
					if (0!=_tcscmp(m_tip_message,L""))
					{
						text_graphic.DrawString(m_tip_message,-1,&myFont,control_rect,&text_format,&text_brush);
					}
				}
				else if (0==_tcscmp(item_value.c_str(),L"connect_tip_static"))
				{
					if (m_connect_success)
					{
						//���ӳɹ�
						text_graphic.DrawString(L"���ӳɹ�",-1,&myFont,control_rect,&text_format,&text_brush);
					}
					else
					{
						//ʧ��
						text_graphic.DrawString(L"δ����",-1,&myFont,control_rect,&text_format,&text_brush);
					}
				}
			}

			//��һ���ֵܽ��
			result = parse_xml_markup.FindElem();

		} while (result);

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CAudioEffect::get_control_cur_value(const TCHAR *group_number,TCHAR *cur_value)
{
	try
	{
		CMarkup parse_xml_markup;
		std::wstring item_value;
		bool result=false;

		result = parse_xml_markup.Load(m_protocol_config_path);
		if (!result)
		{
			return false;
		}
		parse_xml_markup.ResetPos();
		result = parse_xml_markup.FindChildElem();
		if (!result)
		{
			return false;
		}
		parse_xml_markup.IntoElem();
		do
		{
			item_value = parse_xml_markup.GetAttrib(L"group_flag");
			if (0==_tcscmp(item_value.c_str(),group_number))
			{
				//���ʾ��ͬ���õ���ǰֵ
				item_value = parse_xml_markup.GetAttrib(L"cur_value");
				_tcscpy(cur_value,item_value.c_str());

				break;
			}
			//�õ���һ�����
			result = parse_xml_markup.FindElem();
		}while(result);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool CAudioEffect::check_click_control_number(POINT &click_point,TCHAR *control_number,TCHAR *control_type,TCHAR *group_flag,int &radio_value,int &min_value,int &max_value)
{
	try
	{
		CMarkup parse_xml_markup;
		std::wstring item_value;
		bool result=false;
		int control_left=0;
		int control_top=0;
		int control_right=0;
		int control_bottom=0;
		CRect control_rect;
		bool return_result=false;

		result = parse_xml_markup.Load(m_skin_config_path);
		if (!result)
		{
			return false;
		}
		parse_xml_markup.ResetPos();
		result = parse_xml_markup.FindChildElem();
		if (!result)
		{
			return false;
		}
		parse_xml_markup.IntoElem();
		do 
		{
			//�õ��ؼ�����
			item_value = parse_xml_markup.GetAttrib(L"enable");
			if (0==_tcscmp(item_value.c_str(),L"true"))
			{
				//�ؼ����Բ���
				item_value = parse_xml_markup.GetAttrib(L"rect");
				swscanf(item_value.c_str(),L"%d,%d,%d,%d",&control_left,&control_top,&control_right,&control_bottom);
				control_rect.left = control_left;
				control_rect.top = control_top;
				control_rect.right = control_right;
				control_rect.bottom = control_bottom;
				if(control_rect.PtInRect(click_point))
				{
					//���пؼ�,�õ���������
					item_value = parse_xml_markup.GetAttrib(L"key");
					_tcscpy(control_number,item_value.c_str());
					item_value = parse_xml_markup.GetAttrib(L"type");
					_tcscpy(control_type,item_value.c_str());
					item_value = parse_xml_markup.GetAttrib(L"group_flag");
					_tcscpy(group_flag,item_value.c_str());
					item_value = parse_xml_markup.GetAttrib(L"order");
					swscanf(item_value.c_str(),L"%d",&radio_value);
					item_value = parse_xml_markup.GetAttrib(L"min_value");
					swscanf(item_value.c_str(),L"%d",&min_value);
					item_value = parse_xml_markup.GetAttrib(L"max_value");
					swscanf(item_value.c_str(),L"%d",&max_value);
					item_value = parse_xml_markup.GetAttrib(L"protocol_file");
					if (!item_value.empty())
					{
						//��Э���ļ�
						memset(m_protocol_config_path,0x0,sizeof(m_protocol_config_path));
						swprintf(m_protocol_config_path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
					}
					return_result = true;

					break;
				}
			}

			//��һ���ֵܽ��
			result = parse_xml_markup.FindElem();

		} while (result);


		return return_result;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CAudioEffect::reponse_control_event(TCHAR *control_number,TCHAR *control_type,TCHAR *group_flag,int &radio_value,int &min_value,int &max_value)
{
	try
	{
		CMarkup parse_xml_markup;
		std::wstring item_value;
		bool result=false;
		int change_byte=0;
		int src_value=0;
		int change_value=0;
		int send_value=0;
		unsigned char send_com_data[256];
		int recv_len=0;
		unsigned char recv_data[256];
		int send_buf_len=0;

		result = parse_xml_markup.Load(m_protocol_config_path);
		if (!result)
		{
			return false;
		}
		parse_xml_markup.ResetPos();
		result = parse_xml_markup.FindChildElem();
		if (!result)
		{
			return false;
		}
		parse_xml_markup.IntoElem();
		do 
		{
			memset(send_com_data,0x0,sizeof(send_com_data));
			memset(recv_data,0x0,sizeof(recv_data));

			//���ж����ʾ
			item_value = parse_xml_markup.GetAttrib(L"group_flag");
			if (0==_tcscmp(item_value.c_str(),group_flag))
			{
				//���ʾ��ͬ
				if (0==_tcscmp(control_type,L"button"))
				{
					//�жϿؼ���ʾ�Ƿ���ͬ
					item_value = parse_xml_markup.GetAttrib(L"key");
					if (0==_tcscmp(item_value.c_str(),control_number))
					{
						item_value = parse_xml_markup.GetAttrib(L"write_protocol");
						if (0==_tcscmp(item_value.c_str(),L"exit"))
						{
							//����
							ShowWindow(SW_HIDE);
						}
						else if (0==_tcscmp(item_value.c_str(),L"upload"))
						{
							//�ϴ�
							upload_download_protocol_file(true);
						}
						else if (0==_tcscmp(item_value.c_str(),L"download"))
						{
							//����
							upload_download_protocol_file(false);
						}
						else if (0==_tcscmp(item_value.c_str(),L"read"))
						{
							//��ȡ
							read_audio_effect_value(parse_xml_markup);
						}
						else
						{
							item_value = parse_xml_markup.GetAttrib(L"write_protocol");
							if (!item_value.empty())
							{
								result = parse_com_value(item_value.c_str(),send_com_data,send_buf_len);
								if (result)
								{
									//�޸ķ��͵�ֵ
									item_value = parse_xml_markup.GetAttrib(L"change_byte");
									swscanf(item_value.c_str(),L"%d",&change_byte);
									item_value = parse_xml_markup.GetAttrib(L"cur_value");
									swscanf(item_value.c_str(),L"%d",&src_value);
									item_value = parse_xml_markup.GetAttrib(L"change_value");
									swscanf(item_value.c_str(),L"%d",&change_value);
									send_value = src_value+change_value;
									if (send_value>max_value)
									{
										send_value = max_value;
									}
									else if (send_value<min_value)
									{
										send_value = min_value;
									}
									send_com_data[change_byte-1] = send_value;
									//��������
									m_audio_effect_com.write(send_com_data,send_buf_len);
									//��ȡ����
									for(int i=0;i<2;i++)
									{	//��ȡ
										Sleep(15);
										recv_len = m_audio_effect_com.read(recv_data,sizeof(recv_data));
										if (recv_len>0)
										{
											break;
										}
										//���·���
										m_audio_effect_com.write(send_com_data,send_buf_len);										
									}
								}
								//�޸�ͬ������пؼ���ǰֵ
								parse_xml_markup.ResetMainPos();
								do 
								{
									item_value = parse_xml_markup.GetAttrib(L"group_flag");
									if (0==_tcscmp(item_value.c_str(),group_flag))
									{
										parse_xml_markup.SetAttrib(L"cur_value",send_value);
									}
									//������һ���ֵܽ��
									result = parse_xml_markup.FindElem();
								} while (result);
							}
						}
						break;
					}
				}
				else if(0==_tcscmp(control_type,L"checkbox"))
				{
					item_value = parse_xml_markup.GetAttrib(L"write_protocol");
					if (!item_value.empty())
					{
						result = parse_com_value(item_value.c_str(),send_com_data,send_buf_len);
						if (result)
						{
							//�޸ķ��͵�ֵ
							item_value = parse_xml_markup.GetAttrib(L"change_byte");
							swscanf(item_value.c_str(),L"%d",&change_byte);
							item_value = parse_xml_markup.GetAttrib(L"cur_value");
							if (0==_tcscmp(item_value.c_str(),L"0"))
							{
								send_com_data[change_byte-1] = 1;
								//���õ�ǰֵ
								parse_xml_markup.SetAttrib(L"cur_value",1);
							}
							else
							{
								send_com_data[change_byte-1] = 0;
								//���õ�ǰֵ
								parse_xml_markup.SetAttrib(L"cur_value",0);
							}
							//��������
							m_audio_effect_com.write(send_com_data,send_buf_len);
							//��ȡ����
							for(int i=0;i<2;i++)
							{	//��ȡ
								Sleep(15);
								recv_len = m_audio_effect_com.read(recv_data,sizeof(recv_data));
								if (recv_len>0)
								{
									break;
								}
								//���·���
								m_audio_effect_com.write(send_com_data,send_buf_len);										
							}
						}
					}
					break;
				}
				else if(0==_tcscmp(control_type,L"radio"))
				{
					item_value = parse_xml_markup.GetAttrib(L"write_protocol");
					if (!item_value.empty())
					{
						result = parse_com_value(item_value.c_str(),send_com_data,send_buf_len);
						if (result)
						{
							//�޸ķ��͵�ֵ
							item_value = parse_xml_markup.GetAttrib(L"change_byte");
							swscanf(item_value.c_str(),L"%d",&change_byte);
							send_com_data[change_byte-1] = radio_value;
							//��������
							m_audio_effect_com.write(send_com_data,send_buf_len);
							//��ȡ����
							for(int i=0;i<2;i++)
							{	//��ȡ
								Sleep(15);
								recv_len = m_audio_effect_com.read(recv_data,sizeof(recv_data));
								if (recv_len>0)
								{
									break;
								}
								//���·���
								m_audio_effect_com.write(send_com_data,send_buf_len);										
							}
						}
						//���õ�ǰֵ
						parse_xml_markup.SetAttrib(L"cur_value",radio_value);
					}

					break;
				}
			}
			//��һ���ֵܽ��
			result = parse_xml_markup.FindElem();
		} while (result);

		//���������ļ�
		parse_xml_markup.Save(m_protocol_config_path);

		//�ػ��ƽ���
		PostMessage(WM_PAINT,NULL,NULL);

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CAudioEffect::parse_com_value(const TCHAR *com_value,unsigned char *recv_value,int &buf_len)
{
	try
	{
		TCHAR value[256];
		int com_char=0;
		int char_number=0;

		memset(value,0x0,sizeof(value));

		_tcscpy(value,com_value);

		for (unsigned int i=0;i<_tcslen(value);i+=5)
		{
			com_char=0;
			swscanf(value+i+2,L"%x",&com_char);
			recv_value[char_number] = com_char;
			char_number++;
		}
		//�����ֽ���
		buf_len = char_number;

		return true;
	}
	catch (...) {
	}

	return false;
}
void CAudioEffect::OnTimer(UINT nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 1:   //���ʹ�������
		{
			if (!IsWindowVisible() || m_response_mouse_event)
			{
				//��Ч������ʾ��ʱ�򣬲ŷ���
				break;
			}

			unsigned char recv_data[256];
			int recv_len=0;

			memset(recv_data,0x0,sizeof(recv_data));

			if (!m_connect_success)
			{
				//û�����ӳɹ�����һֱ������������
				m_audio_effect_com.write(m_connect_command,m_connect_command_len);
				//��ȡ����
				recv_len = m_audio_effect_com.read(recv_data,sizeof(recv_data));
				if (recv_len>0)
				{
					m_connect_success = true;
					//�ػ��ƽ���
					PostMessage(WM_PAINT,NULL,NULL);
				}
			}
			else
			{
				//���Ϳ�������
				m_audio_effect_com.write(m_idless_command,m_idless_command_len);
			}
		}
		break;
	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void CAudioEffect::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	if (bShow)
	{
		//��ʾ��ʱ���������ӱ�ʶ
		m_connect_success = false;
	}
	else
	{
		memset(m_tip_message,0x0,sizeof(m_tip_message));
	}
}

bool CAudioEffect::read_audio_effect_value(CMarkup &parse_xml_class)
{
	try
	{
		std::wstring item_value;
		unsigned char send_data[256];
		int buf_len=0;
		bool result=false;
		int recv_value=0;

		if (!m_connect_success)
		{
			memset(m_tip_message,0x0,sizeof(m_tip_message));
			_tcscpy(m_tip_message,L"û�����ӵ���Ч�������ܶ�ȡ����");
			//�ػ��ƽ���
			PostMessage(WM_PAINT,NULL,NULL);
			return false;
		}

		//�ص������
		parse_xml_class.ResetPos();
		result = parse_xml_class.FindChildElem();
		if (!result)
		{
			return false;
		}
		memset(m_tip_message,0x0,sizeof(m_tip_message));
		_tcscpy(m_tip_message,L"���ڶ�ȡ��Ч���Ĵ洢ֵ");
		//�ػ��ƽ���
		PostMessage(WM_PAINT,NULL,NULL);

		parse_xml_class.IntoElem();
		do
		{
			item_value = parse_xml_class.GetAttrib(L"read_protocol");
			if (!item_value.empty())
			{
				memset(send_data,0x0,sizeof(send_data));
				result = parse_com_value(item_value.c_str(),send_data,buf_len);
				if (result)
				{
					//����
					m_audio_effect_com.write(send_data,buf_len);
					memset(send_data,0x0,sizeof(send_data));
					for(int i=0;i<10;i++)
					{
						//��ȡ
						buf_len = m_audio_effect_com.read(send_data,sizeof(send_data));
						if (1==buf_len)
						{
							result = parse_xml_class.SetAttrib(L"cur_value",send_data[0]);
							break;
						}
						Sleep(1);
					}
				}
			}
			//�õ���һ�����
			result = parse_xml_class.FindElem();
		}while(result);

		memset(m_tip_message,0x0,sizeof(m_tip_message));
		_tcscpy(m_tip_message,L"��ȡ��Ч���Ĵ洢ֵ���");

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

void CAudioEffect::upload_download_protocol_file(bool upload_flag)
{
	try
	{
		if (0==_tcscmp(m_upload_server_path,L""))
		{
			return;
		}
		config_file_manager config_file;
		TCHAR path[256];
		TCHAR des_path[256];
		std::wstring file_name;
		TCHAR key_value[256];

		config_file.init(L"audio_effect\\config.ini");

		for (int i=0;i<4;i++)
		{
			memset(path,0x0,sizeof(path));
			memset(des_path,0x0,sizeof(des_path));
			memset(key_value,0x0,sizeof(key_value));

			swprintf(key_value,L"Protocol_file%d",i);
			//�ϴ�Э���ļ���������
			file_name = config_file.read_string(L"setting",key_value,L"");
			if (!file_name.empty())
			{
				swprintf(path,L"%s\\audio_effect\\%s",m_work_path,file_name.c_str());
				swprintf(des_path,L"%s\\%s",m_upload_server_path,file_name.c_str());
				if (upload_flag)
				{
					//�ϴ�
					CopyFile(path,des_path,FALSE);
				}
				else
				{
					//����
					CopyFile(des_path,path,FALSE);
				}
			}
		}

		memset(m_tip_message,0x0,sizeof(m_tip_message));
		if (upload_flag)
		{
			_tcscpy(m_tip_message,L"�ϴ�Э���ļ������������");
		}
		else
		{
			_tcscpy(m_tip_message,L"����Э���ļ����������");
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}
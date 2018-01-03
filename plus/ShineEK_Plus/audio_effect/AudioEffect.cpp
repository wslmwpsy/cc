// AudioEffect.cpp : 实现文件
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



// CAudioEffect 消息处理程序


LRESULT CAudioEffect::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			if (m_response_mouse_event)
			{
				//正在读取数据，不要响应任何鼠标事件
				break;
			}

			//得到点击的x,y坐标
			m_mouse_click_point.x = LOWORD(lParam);
			m_mouse_click_point.y = HIWORD(lParam);
			//启动线程判断鼠标事件
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
	//设置标示
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

		//检测是否点中按钮
		result = check_click_control_number(m_mouse_click_point,control_number,control_type,group_flag,radio_value,min_value,max_value);
		if (result)
		{
			//响应响应事件
			reponse_control_event(control_number,control_type,group_flag,radio_value,min_value,max_value);
		}
	}
	catch (...)
	{
		
	}

	//设置标示
	m_response_mouse_event =false;

	return 0;
}

void CAudioEffect::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (Ok==m_audio_effect_image->GetLastStatus())
	{
		//释放空间
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
		//初始化串口文件
		config_file.init(L"audio_effect\\config.ini");
		//根据图片大小修改窗口
		GetClientRect(&client_rect);

		m_audio_effect_image = Image::FromFile(m_src_image_path);
		if (m_audio_effect_image&&(Ok==m_audio_effect_image->GetLastStatus()))
		{
			image_width = m_audio_effect_image->GetWidth();
			image_heith = m_audio_effect_image->GetHeight();
			//移动窗口位置
			MoveWindow(client_rect.left+(client_rect.right-client_rect.left-image_width)/2,client_rect.top+(client_rect.bottom-client_rect.top-image_heith)/2,image_width,image_heith);
			//克隆一个绘制的图
			m_draw_image = m_audio_effect_image->Clone();
		}
		//加载slider工具条
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\audio_effect\\bar.jpg",m_work_path);
		m_slider_bar_image = Image::FromFile(path);
		//加载遮罩图片
		item_value = config_file.read_string(L"setting",L"disable_bg_image",L"");
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
		m_disable_effect_image = Image::FromFile(path);
		//加载高亮图片
		item_value = config_file.read_string(L"setting",L"highlight_image",L"");
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
		m_highlight_status_image = Image::FromFile(path);

		//打开串口
		com_number = config_file.read_integer(L"setting",L"com_port",1);
		com_para = config_file.read_string(L"setting",L"comm_parameter",L"9600,N,8,1");
		result = m_audio_effect_com.open(com_number,com_para.c_str());
		result = m_audio_effect_com.is_open();
		if (result)
		{
			WriteLog(__FL__, L"音效器串口打开成功");
		}
		else
		{
			WriteLog(__FL__, L"音效器串口打开失败");
		}

		//启动定时器，发送串口数据
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
	// TODO: 在此添加专用代码和/或调用基类
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

	//得到工作路径
	GetModuleFileName(NULL,m_work_path,sizeof(m_work_path));
	PathRemoveFileSpec(m_work_path);
	//初始化配置文件
	config_file.init(L"audio_effect\\config.ini");
	//保存服务器路径
	_tcscpy(m_upload_server_path,server_path);

	//是否启用音效调节
	swprintf(m_config_path,L"%s\\audio_effect\\config.ini",m_work_path);
	result = config_file.read_boolean(L"setting",L"use_audio_effect",false);
	if (!result)
	{
		return FALSE;
	}
	//得到皮肤配置文件名
	item_value = config_file.read_string(L"setting",L"skin_config",L"");
	swprintf(m_skin_config_path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
	//得到配置协议文件名
	item_value = config_file.read_string(L"setting",L"Protocol_file0",L"");
	swprintf(m_protocol_config_path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
	//得到原始图片路径
	item_value = config_file.read_string(L"setting",L"bg_image",L"");
	swprintf(m_src_image_path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
	
	//读取连接命令
	item_value = config_file.read_string(L"setting",L"connect_command",L"");
	if (!item_value.empty())
	{
		parse_com_value(item_value.c_str(),m_connect_command,m_connect_command_len);
	}
	//空闲命令
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
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	Graphics draw_graphics(m_hWnd);
	RectF show_rect;
	REAL image_width=0.0f;
	REAL image_heith=0.0f;

	//绘制图
	draw_window();

	image_width = m_draw_image->GetWidth()*1.0f;
	image_heith = m_draw_image->GetHeight()*1.0f;
	show_rect.X = 0.0f;
	show_rect.Y = 0.0f;
	show_rect.Width = image_width;
	show_rect.Height = image_heith;
	//重绘制
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
			//绘制背景图
			show_rect.X = 0;
			show_rect.Y = 0;
			show_rect.Width = image_width;
			show_rect.Height = image_heith;
			Status image_status = audio_effect_graphics.DrawImage(m_audio_effect_image,show_rect,0,0,image_width,image_heith,UnitPixel);
			//显示数字
			show_control_value(audio_effect_graphics);
			//绘制不可操作区域和高亮区域
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
		Font myFont(L"微软雅黑",16,FontStyleRegular);
		StringFormat text_format;
        SolidBrush text_brush(Color(255,255,255,255));
		RectF show_rect;
		int max_value=0;
		int min_value=0;
		int cur_value=0;
		config_file_manager config_file;

		text_format.SetAlignment(StringAlignmentCenter);
		text_format.SetLineAlignment(StringAlignmentCenter);

		//解析协议的xml
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
		//解析皮肤的xml
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
			//修改edit的显示值
			item_value = parse_xml_markup.GetAttrib(L"edit_show_key");
			if (!item_value.empty())
			{
				pares_skin_xml.ResetMainPos();
				do 
				{
					control_number = pares_skin_xml.GetAttrib(L"key");
					if (item_value==control_number)
					{
						//得到显示区域
						item_value = pares_skin_xml.GetAttrib(L"rect");
						swscanf(item_value.c_str(),L"%d,%d,%d,%d",&control_left,&control_top,&control_right,&control_bottom);
						show_rect.X = control_left*1.0f;
						show_rect.Y = control_top*1.0f;
						show_rect.Width = (control_right-control_left)*1.0f;
						show_rect.Height = (control_bottom-control_top)*1.0f;
						//得到要显示的值
						control_number = parse_xml_markup.GetAttrib(L"cur_value");
						item_value = parse_xml_markup.GetAttrib(L"show_value");
						if (!item_value.empty())
						{
							int src_value=0;
							int change_value=0;
							TCHAR show_value[256];
							
							memset(show_value,0x0,sizeof(show_value));

							//显示的值和设置给音效器的值不一样，需要调整
							if (0==_tcsncmp(item_value.c_str(),L"N",1))
							{
								//累加一定的数值
								swscanf(control_number.c_str(),L"%d",&src_value);
								swscanf(item_value.c_str()+2,L"%d",&change_value);
								swprintf(show_value,L"%d",src_value+change_value);
								control_number.assign(show_value);
							}
							else
							{
								//从文件读取显示的值
								_tcscpy(show_value,L"audio_effect\\");
								_tcscpy(show_value+_tcslen(show_value),item_value.c_str()+2);
								//从配置文件中读取
								config_file.init(show_value);
								control_number = config_file.read_string(L"CorrespondValue",control_number.c_str(),L"");
							}
						}
						//显示
						text_graphic.DrawString(control_number.c_str(),-1,&myFont,show_rect,&text_format,&text_brush);
						break;
					}
					result = pares_skin_xml.FindElem();
				} while (result);
			}
			//修改slider的值
			item_value = parse_xml_markup.GetAttrib(L"slider_show_key");
			if (!item_value.empty())
			{
				pares_skin_xml.ResetMainPos();
				do 
				{
					control_number = pares_skin_xml.GetAttrib(L"key");
					if (item_value==control_number)
					{
						//得到显示区域
						item_value = pares_skin_xml.GetAttrib(L"rect");
						swscanf(item_value.c_str(),L"%d,%d,%d,%d",&control_left,&control_top,&control_right,&control_bottom);
						item_value = pares_skin_xml.GetAttrib(L"max_value");
						swscanf(item_value.c_str(),L"%d",&max_value);
						item_value = pares_skin_xml.GetAttrib(L"min_value");
						swscanf(item_value.c_str(),L"%d",&min_value);
						item_value = parse_xml_markup.GetAttrib(L"cur_value");
						swscanf(item_value.c_str(),L"%d",&cur_value);
						//显示
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
		Font myFont(L"微软雅黑",24,FontStyleRegular);
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

			//得到控件区域
			item_value = parse_xml_markup.GetAttrib(L"rect");
			if (!item_value.empty())
			{
				swscanf(item_value.c_str(),L"%d,%d,%d,%d",&control_left,&control_top,&control_right,&control_bottom);
				control_rect.X = control_left*1.0f;
				control_rect.Y = control_top*1.0f;
				control_rect.Width = (control_right-control_left)*1.0f;
				control_rect.Height = (control_bottom-control_top)*1.0f;

				//查看控件是否可操作
				item_value = parse_xml_markup.GetAttrib(L"enable");
				if (0!=_tcscmp(item_value.c_str(),L"true"))
				{
					//绘制不可操作区域
					text_graphic.DrawImage(m_disable_effect_image,control_rect,control_rect.X,control_rect.Y,control_rect.Width,control_rect.Height,UnitPixel);
				}
				else
				{
					//绘制高亮区域
					item_value = parse_xml_markup.GetAttrib(L"type");
					if (0==_tcscmp(item_value.c_str(),L"radio"))
					{
						//单选
						//得到组编号
						item_value = parse_xml_markup.GetAttrib(L"group_flag");
						//通过组编号，得到radio的选择值
						get_control_cur_value(item_value.c_str(),cur_value);
						//得到当前的选择值
						item_value = parse_xml_markup.GetAttrib(L"order");
						if (0==_tcscmp(item_value.c_str(),cur_value))
						{
							//radio的编号等于当前选择值，高亮
							text_graphic.DrawImage(m_highlight_status_image,control_rect,control_rect.X,control_rect.Y,control_rect.Width,control_rect.Height,UnitPixel);
						}
					}
					else if (0==_tcscmp(item_value.c_str(),L"checkbox"))
					{
						//复选框
						//得到组编号
						item_value = parse_xml_markup.GetAttrib(L"group_flag");
						//通过组编号，得到checkbox的值
						get_control_cur_value(item_value.c_str(),cur_value);
						if (0==_tcscmp(cur_value,L"1"))
						{
							//选中状态
							text_graphic.DrawImage(m_highlight_status_image,control_rect,control_rect.X,control_rect.Y,control_rect.Width,control_rect.Height,UnitPixel);
						}
					}
				}
				//是否是提示信息显示框
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
						//连接成功
						text_graphic.DrawString(L"连接成功",-1,&myFont,control_rect,&text_format,&text_brush);
					}
					else
					{
						//失败
						text_graphic.DrawString(L"未连接",-1,&myFont,control_rect,&text_format,&text_brush);
					}
				}
			}

			//下一个兄弟结点
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
				//组标示相同，得到当前值
				item_value = parse_xml_markup.GetAttrib(L"cur_value");
				_tcscpy(cur_value,item_value.c_str());

				break;
			}
			//得到下一个结点
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
			//得到控件区域
			item_value = parse_xml_markup.GetAttrib(L"enable");
			if (0==_tcscmp(item_value.c_str(),L"true"))
			{
				//控件可以操作
				item_value = parse_xml_markup.GetAttrib(L"rect");
				swscanf(item_value.c_str(),L"%d,%d,%d,%d",&control_left,&control_top,&control_right,&control_bottom);
				control_rect.left = control_left;
				control_rect.top = control_top;
				control_rect.right = control_right;
				control_rect.bottom = control_bottom;
				if(control_rect.PtInRect(click_point))
				{
					//点中控件,得到各个参数
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
						//换协议文件
						memset(m_protocol_config_path,0x0,sizeof(m_protocol_config_path));
						swprintf(m_protocol_config_path,L"%s\\audio_effect\\%s",m_work_path,item_value.c_str());
					}
					return_result = true;

					break;
				}
			}

			//下一个兄弟结点
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

			//先判断组标示
			item_value = parse_xml_markup.GetAttrib(L"group_flag");
			if (0==_tcscmp(item_value.c_str(),group_flag))
			{
				//组标示相同
				if (0==_tcscmp(control_type,L"button"))
				{
					//判断控件标示是否相同
					item_value = parse_xml_markup.GetAttrib(L"key");
					if (0==_tcscmp(item_value.c_str(),control_number))
					{
						item_value = parse_xml_markup.GetAttrib(L"write_protocol");
						if (0==_tcscmp(item_value.c_str(),L"exit"))
						{
							//返回
							ShowWindow(SW_HIDE);
						}
						else if (0==_tcscmp(item_value.c_str(),L"upload"))
						{
							//上传
							upload_download_protocol_file(true);
						}
						else if (0==_tcscmp(item_value.c_str(),L"download"))
						{
							//下载
							upload_download_protocol_file(false);
						}
						else if (0==_tcscmp(item_value.c_str(),L"read"))
						{
							//读取
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
									//修改发送的值
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
									//发送命令
									m_audio_effect_com.write(send_com_data,send_buf_len);
									//读取数据
									for(int i=0;i<2;i++)
									{	//读取
										Sleep(15);
										recv_len = m_audio_effect_com.read(recv_data,sizeof(recv_data));
										if (recv_len>0)
										{
											break;
										}
										//重新发送
										m_audio_effect_com.write(send_com_data,send_buf_len);										
									}
								}
								//修改同组的所有控件当前值
								parse_xml_markup.ResetMainPos();
								do 
								{
									item_value = parse_xml_markup.GetAttrib(L"group_flag");
									if (0==_tcscmp(item_value.c_str(),group_flag))
									{
										parse_xml_markup.SetAttrib(L"cur_value",send_value);
									}
									//查找下一个兄弟结点
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
							//修改发送的值
							item_value = parse_xml_markup.GetAttrib(L"change_byte");
							swscanf(item_value.c_str(),L"%d",&change_byte);
							item_value = parse_xml_markup.GetAttrib(L"cur_value");
							if (0==_tcscmp(item_value.c_str(),L"0"))
							{
								send_com_data[change_byte-1] = 1;
								//设置当前值
								parse_xml_markup.SetAttrib(L"cur_value",1);
							}
							else
							{
								send_com_data[change_byte-1] = 0;
								//设置当前值
								parse_xml_markup.SetAttrib(L"cur_value",0);
							}
							//发送命令
							m_audio_effect_com.write(send_com_data,send_buf_len);
							//读取数据
							for(int i=0;i<2;i++)
							{	//读取
								Sleep(15);
								recv_len = m_audio_effect_com.read(recv_data,sizeof(recv_data));
								if (recv_len>0)
								{
									break;
								}
								//重新发送
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
							//修改发送的值
							item_value = parse_xml_markup.GetAttrib(L"change_byte");
							swscanf(item_value.c_str(),L"%d",&change_byte);
							send_com_data[change_byte-1] = radio_value;
							//发送命令
							m_audio_effect_com.write(send_com_data,send_buf_len);
							//读取数据
							for(int i=0;i<2;i++)
							{	//读取
								Sleep(15);
								recv_len = m_audio_effect_com.read(recv_data,sizeof(recv_data));
								if (recv_len>0)
								{
									break;
								}
								//重新发送
								m_audio_effect_com.write(send_com_data,send_buf_len);										
							}
						}
						//设置当前值
						parse_xml_markup.SetAttrib(L"cur_value",radio_value);
					}

					break;
				}
			}
			//下一个兄弟结点
			result = parse_xml_markup.FindElem();
		} while (result);

		//保存配置文件
		parse_xml_markup.Save(m_protocol_config_path);

		//重绘制界面
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
		//传回字节数
		buf_len = char_number;

		return true;
	}
	catch (...) {
	}

	return false;
}
void CAudioEffect::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 1:   //发送串口数据
		{
			if (!IsWindowVisible() || m_response_mouse_event)
			{
				//音效窗口显示的时候，才发送
				break;
			}

			unsigned char recv_data[256];
			int recv_len=0;

			memset(recv_data,0x0,sizeof(recv_data));

			if (!m_connect_success)
			{
				//没有连接成功，就一直发送连接命令
				m_audio_effect_com.write(m_connect_command,m_connect_command_len);
				//读取数据
				recv_len = m_audio_effect_com.read(recv_data,sizeof(recv_data));
				if (recv_len>0)
				{
					m_connect_success = true;
					//重绘制界面
					PostMessage(WM_PAINT,NULL,NULL);
				}
			}
			else
			{
				//发送空闲命令
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

	// TODO: 在此处添加消息处理程序代码
	if (bShow)
	{
		//显示的时候，设置连接标识
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
			_tcscpy(m_tip_message,L"没有连接到音效器，不能读取数据");
			//重绘制界面
			PostMessage(WM_PAINT,NULL,NULL);
			return false;
		}

		//回到根结点
		parse_xml_class.ResetPos();
		result = parse_xml_class.FindChildElem();
		if (!result)
		{
			return false;
		}
		memset(m_tip_message,0x0,sizeof(m_tip_message));
		_tcscpy(m_tip_message,L"正在读取音效器的存储值");
		//重绘制界面
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
					//发送
					m_audio_effect_com.write(send_data,buf_len);
					memset(send_data,0x0,sizeof(send_data));
					for(int i=0;i<10;i++)
					{
						//读取
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
			//得到下一个结点
			result = parse_xml_class.FindElem();
		}while(result);

		memset(m_tip_message,0x0,sizeof(m_tip_message));
		_tcscpy(m_tip_message,L"读取音效器的存储值完成");

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
			//上传协议文件到服务器
			file_name = config_file.read_string(L"setting",key_value,L"");
			if (!file_name.empty())
			{
				swprintf(path,L"%s\\audio_effect\\%s",m_work_path,file_name.c_str());
				swprintf(des_path,L"%s\\%s",m_upload_server_path,file_name.c_str());
				if (upload_flag)
				{
					//上传
					CopyFile(path,des_path,FALSE);
				}
				else
				{
					//下载
					CopyFile(des_path,path,FALSE);
				}
			}
		}

		memset(m_tip_message,0x0,sizeof(m_tip_message));
		if (upload_flag)
		{
			_tcscpy(m_tip_message,L"上传协议文件到服务器完成");
		}
		else
		{
			_tcscpy(m_tip_message,L"下载协议文件到本机完成");
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}
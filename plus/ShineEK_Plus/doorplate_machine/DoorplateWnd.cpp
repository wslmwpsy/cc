// DoorplateWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DoorplateWnd.h"
#include ".\doorplatewnd.h"
#include "..\folder_name.h"
#include "..\file\config_file.h"
#include "..\common\init_socket.h"
#include "..\common\StringCodeConversion.h"
#include "..\message.h"

#pragma warning(disable: 4244 4018)

enum DOORPLATE_IMAGE_SHOW_MODE
{
	DOORPLATE_IMAGE_NO_ANIMATION,      //ֱ����ʾû�ж���Ч��
	DOORPLATE_IMAGE_RIGHT_TO_LEFT,     //���ҵ���
	DOORPLATE_IMAGE_LEFT_TO_RIGHT,     //������
	DOORPLATE_IMAGE_MIDDLE_TO_SIDES_X, //ˮƽ������м䵽����
	DOORPLATE_IMAGE_MIDDLE_TO_SIDES_Y, //��ֱ������м䵽����
	DOORPLATE_IMAGE_ZOON_IN,           //�Ŵ�

	DOORPLATE_IMAGE_SHOW_MODE_COUNT,   //��ʾģʽ������
};
// CDoorplateWnd

IMPLEMENT_DYNAMIC(CDoorplateWnd, CWnd)
CDoorplateWnd::CDoorplateWnd()
{
	m_doorplate_image=NULL;
}

CDoorplateWnd::~CDoorplateWnd()
{
}


BEGIN_MESSAGE_MAP(CDoorplateWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CDoorplateWnd,CWnd)
	ON_EVENT(CDoorplateWnd,DOORPLATE_FLASH_PLAYER_WINDOW_ID,197,FlashCallShockwavefunction,VTS_BSTR)
END_EVENTSINK_MAP()


// CDoorplateWnd ��Ϣ�������
void CDoorplateWnd::FlashCallShockwavefunction(LPCTSTR request)
{
	// TODO: �ڴ˴������Ϣ����������
	try
	{
		::SendMessage(m_parent_handle,DM_SUB_WINDOW_MESSAGE,(WPARAM)request,NULL);
	}
	catch (...)
	{

	}

	return;
}

bool CDoorplateWnd::Create(RECT& rect,TCHAR *room_name,bool use_drinks,HWND parent_handle)
{
	//save room name
	memset(m_image_room_name,0x0,sizeof(m_image_room_name));
	memset(m_image_room_type,0x0,sizeof(m_image_room_type));                                   //��������
	memset(m_image_open_room_time,0x0,sizeof(m_image_open_room_time));                         //����ʱ��
	memset(m_image_people_count,0x0,sizeof(m_image_people_count));                             //��������
	memset(m_image_consume_money,0x0,sizeof(m_image_consume_money));                           //���ѽ��
	_time64(&m_open_room_time_second);
	if (room_name)
	{
		swprintf(m_image_room_name,L"%s",room_name);
	}
	//�õ���Ļ�Ŀ�Ⱥ͸߶�
	m_doorplate_screen_width = rect.right-rect.left;
	m_doorplate_screen_height = rect.bottom-rect.top;
	//�Ƿ��������ƻ���ˮ
	m_use_drinks_function = use_drinks;
	//�����ھ��
	m_parent_handle = parent_handle;

	//ע��һ��������
	CString class_name = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS,   \
		::LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	//����һ������
	if (FALSE == CWnd::CreateEx(0, class_name, NULL, WS_POPUP|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, rect, NULL, 0))
	{
		return false;
	}

	return true;	
}

int CDoorplateWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	try
	{
		TCHAR work_path[256];
		TCHAR image_path[256];
		CFileFind image_file_find;
		BOOL result=FALSE;
		CString image_file_path;
		config_file_manager config_file;
		int image_show_time=0;  //ÿ��ͼƬ��ʾʱ��

		memset(work_path,0x0,sizeof(work_path));
		memset(image_path,0x0,sizeof(image_path));
		memset(m_doorplate_bg_image_path,0x0,sizeof(m_doorplate_bg_image_path));
		m_doorplate_image_count=0;
		m_cur_show_image_number=0;
		m_image_width = 0;
		m_image_height = 0;
		m_show_image_finish = false;
		m_image_show_mode = DOORPLATE_IMAGE_NO_ANIMATION;
		m_add_height=16;
		m_thread_run=true;
		m_show_image_timer=0;
		m_draw_image_timer=0;
		m_scroll_text_timer=0;

		//�õ�����·��
		GetModuleFileName(NULL,work_path,sizeof(work_path)/sizeof(TCHAR));
		_tcsrchr(work_path,'\\')[0]='\0';

		//get show image
		swprintf(image_path,L"%s\\%s\\*.*",work_path,g_folder_name[17]);
		result = image_file_find.FindFile(image_path);
		while(result)
		{
			result = image_file_find.FindNextFile();

			if (image_file_find.IsDots() || image_file_find.IsDirectory()||image_file_find.IsCompressed()||image_file_find.IsHidden())
			{
				continue;
			}
			if (image_file_find.IsSystem() || image_file_find.IsTemporary())
			{
				continue;
			}

			//�õ��ļ�·��
			image_file_path = image_file_find.GetFilePath();
			m_doorplate_image_path[m_doorplate_image_count].Format(L"%s",image_file_path.GetBuffer(0));
			m_doorplate_image_count++;
			if (m_doorplate_image_count>=DOORPLATE_IMAGE_MAX_COUNT)
			{
				break;
			}
		}
		//close file find
		image_file_find.Close();
		if(m_doorplate_image_count <=0)
		{
			return 0;
		}

		//�õ��Ƿ�ֻ��ʾ������������
		m_only_show_name_type = config_file.read_boolean(L"doorplate_machine",L"show_room_name_type",false);
		if (m_only_show_name_type)
		{
			//�õ���������
			config_file_manager room_file_manager;

			//��ʼ�������ļ�
			room_file_manager.init(L"room_type.ini");
			//�õ���������
			std::wstring  room_type = room_file_manager.read_string(L"room_type",m_image_room_name,L"");
			if (!room_type.empty())
			{
				_tcscpy(m_image_room_type,room_type.c_str());
			}
		}

		//���ֱ���ͼƬ��ʾ����ͻõ�ƬͼƬ��ʾ���򣬰��ջƽ�ָ��߷ָ���0.618
		m_window_frame = config_file.read_integer(L"doorplate_machine",L"show_frame",0);
		if (0==m_window_frame)
		{
			//���ҽṹ

			//���ƻ�����ͼƬ·��
			swprintf(m_doorplate_bg_image_path,L"%s\\%s\\left.png",work_path,g_folder_name[18]);
            //����		
			m_static_image_rect.X = 0;
			m_static_image_rect.Y = 0;
			m_static_image_rect.Width = (int)(m_doorplate_screen_width*0.382f)*1.0f;
			m_static_image_rect.Height = m_doorplate_screen_height*1.0f;

			m_slide_image_rect.X = m_static_image_rect.Width;
			m_slide_image_rect.Y = 0;
			m_slide_image_rect.Width = m_doorplate_screen_width-m_static_image_rect.Width;
			m_slide_image_rect.Height = m_doorplate_screen_height*1.0f;
		}
		else
		{
			//���½ṹ

			//���ƻ�����ͼƬ·��
			swprintf(m_doorplate_bg_image_path,L"%s\\%s\\bottom.png",work_path,g_folder_name[18]);
			//����
			m_slide_image_rect.X = 0.0f;
			m_slide_image_rect.Y = 0.0f;
			m_slide_image_rect.Width = m_doorplate_screen_width*1.0f;
			m_slide_image_rect.Height = m_doorplate_screen_height*0.618f;
			
			m_static_image_rect.X = 0.0f;
			m_static_image_rect.Y = m_slide_image_rect.Height*1.0f;
			m_static_image_rect.Width = m_doorplate_screen_width*1.0f;
			m_static_image_rect.Height = (m_doorplate_screen_height-m_slide_image_rect.Height)*1.0f;
		}

		//�õ�ͼƬ��ʾʱ��
		image_show_time = config_file.read_integer(L"doorplate_machine",L"image_show_time",10);
		if (image_show_time<5)
		{
			image_show_time = 5;
		}
		if (!m_use_drinks_function)
		{
			//no use drinks,start timer
			m_show_image_timer = SetTimer(1,image_show_time*1000,NULL);
			m_draw_image_timer = SetTimer(2,50,NULL);
			//m_scroll_text_timer = SetTimer(3,200,NULL);
		}

		//����һ���̣߳����ܺ�̨���͹���������
		m_thread_run=true;
		AfxBeginThread(CDoorplateWnd::recv_room_data_thread,this);
		//��ʼ��ʱ
		m_update_room_info_timer.start();
	}
	catch (...)
	{
		
	}
	
	return 0;
}

void CDoorplateWnd::OnTimer(UINT nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 1:   //draw current image
		{
			show_next_image();
		}
		break;
	case 2:   //show next image
		{
			double last_time = m_update_room_info_timer.last_time();
			if (last_time>60)
			{
				m_update_room_info_timer.start();
				show_left_image();
			}

			if (!m_show_image_finish)
			{
				//draw image
				paint_image();
			}
		}
		break;
	case 3:   //scroll text
		{
			/*Graphics image_graphics(m_hWnd);
			Font myFont(L"΢���ź�",28);
			RectF layoutRect;
			StringFormat format;
			SolidBrush blackBrush(Color(255,255, 0, 0));
			SolidBrush tranbrush(Color(0,255,0,0));

			static temp_value=0;
			layoutRect.X = -100;
			layoutRect.Y = 0;
			layoutRect.Width = 100+temp_value;
			layoutRect.Height = 100;

			temp_value += 100;

			if (temp_value>2880)
			{
				temp_value = 0;
			}

			image_graphics.SetTextContrast(255);
			format.SetAlignment(StringAlignmentCenter);

			image_graphics.DrawString(L"test scroll text",-1,&myFont,layoutRect,&format,&blackBrush);*/
		}
		break;
	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void CDoorplateWnd::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

	//�����߳�
	m_thread_run=false;

	//kill timer
	if (m_show_image_timer)
	{
		KillTimer(m_show_image_timer);
		m_show_image_timer=0;
	}
	if (m_draw_image_timer)
	{
		KillTimer(m_draw_image_timer);
		m_draw_image_timer=0;
	}
	if (m_scroll_text_timer)
	{
		KillTimer(m_scroll_text_timer);
		m_scroll_text_timer=0;
	}
	if (m_doorplate_image)
	{
		delete m_doorplate_image;
		m_doorplate_image=NULL;
	}
}

void CDoorplateWnd::set_image_show_mode(void)
{
	int show_mode=0;

	//�����ʾģʽ
	show_mode = rand()/(RAND_MAX/DOORPLATE_IMAGE_SHOW_MODE_COUNT+1);
	if (show_mode==m_image_show_mode)
	{
		show_mode++;
	}

	switch(show_mode)
	{
	default:
	case  DOORPLATE_IMAGE_NO_ANIMATION:      //ֱ����ʾû�ж���Ч��
		{
			m_image_show_mode = DOORPLATE_IMAGE_NO_ANIMATION;
			m_show_image_rect=m_slide_image_rect;
		}
		break;
	case DOORPLATE_IMAGE_RIGHT_TO_LEFT:     //���ҵ���
		{
			m_image_show_mode = DOORPLATE_IMAGE_RIGHT_TO_LEFT;
			m_show_image_rect.X = m_slide_image_rect.X+m_slide_image_rect.Width;
			m_show_image_rect.Y =m_slide_image_rect.Y;
			m_show_image_rect.Width = 16.0f;
			m_show_image_rect.Height = m_slide_image_rect.Height;
		}
		break;
	case DOORPLATE_IMAGE_LEFT_TO_RIGHT:     //������
		{
			m_image_show_mode = DOORPLATE_IMAGE_LEFT_TO_RIGHT;
			m_show_image_rect.X = m_slide_image_rect.X-16.0f;
			m_show_image_rect.Width = 16.0f;
			m_show_image_rect.Y = m_slide_image_rect.Y;
			m_show_image_rect.Height = m_slide_image_rect.Height;
		}
		break;
	case DOORPLATE_IMAGE_MIDDLE_TO_SIDES_X: //ˮƽ������м䵽����
		{
			m_image_show_mode = DOORPLATE_IMAGE_MIDDLE_TO_SIDES_X;
			m_show_image_rect.X = m_slide_image_rect.X+m_slide_image_rect.Width/2.0f;
			m_show_image_rect.Width = 8.0f;
			m_show_image_rect.Y = m_slide_image_rect.Y;
			m_show_image_rect.Height = m_slide_image_rect.Height;

			m_show_image_rect1.X = m_slide_image_rect.X+m_slide_image_rect.Width/2.0f-8.0f;
			m_show_image_rect1.Width = 8.0f;
			m_show_image_rect1.Y = m_slide_image_rect.Y;
			m_show_image_rect1.Height = m_slide_image_rect.Height;
		}
		break;
	case DOORPLATE_IMAGE_MIDDLE_TO_SIDES_Y: //��ֱ������м䵽����
		{
			m_image_show_mode = DOORPLATE_IMAGE_MIDDLE_TO_SIDES_Y;
			m_show_image_rect.X = m_slide_image_rect.X;
			m_show_image_rect.Width = m_slide_image_rect.Width;
			m_show_image_rect.Y = m_slide_image_rect.Y+m_slide_image_rect.Height/2.0f;
			m_show_image_rect.Height = 8.0f;

			m_show_image_rect1.X = m_slide_image_rect.X;
			m_show_image_rect1.Width = m_slide_image_rect.Width;
			m_show_image_rect1.Y = m_slide_image_rect.Y+m_slide_image_rect.Height/2.0f-8.0f;
			m_show_image_rect1.Height = 8.0f;
		}
		break;
	case DOORPLATE_IMAGE_ZOON_IN:           //�Ŵ�
		{
			m_image_show_mode = DOORPLATE_IMAGE_ZOON_IN;
			m_show_image_rect.X  = m_slide_image_rect.X+m_slide_image_rect.Width/2.0f;
			m_show_image_rect.Width = 0;
			m_show_image_rect.Y = m_slide_image_rect.Y+m_slide_image_rect.Height/2.0f;
			m_show_image_rect.Height = 0;

			//���ÿ������16������߶�����ֵ
			m_add_height = m_slide_image_rect.Height*16.0f/m_slide_image_rect.Width;
		}
		break;
	}
	return;
}

void CDoorplateWnd::show_next_image(void)
{
	try
	{
		//set image show mode
		set_image_show_mode();

		if (m_cur_show_image_number<0)
		{
			m_cur_show_image_number=0;
		}
		else if(m_cur_show_image_number>=m_doorplate_image_count)
		{
			m_cur_show_image_number = m_doorplate_image_count-1;
		}
		//free src image
		if (m_doorplate_image)
		{
			delete m_doorplate_image;
			m_doorplate_image = NULL;
		}
		//load new image
		m_doorplate_image = Image::FromFile(m_doorplate_image_path[m_cur_show_image_number]);
		if(m_doorplate_image)
		{
			m_image_width = m_doorplate_image->GetWidth()*1.0f;
			m_image_height = m_doorplate_image->GetHeight()*1.0f;
			m_show_image_finish = false;
		}
		m_cur_show_image_number++;
		m_cur_show_image_number %= m_doorplate_image_count;

		//show background image
		show_left_image();
	}
	catch (...)
	{
		
	}
	return;
}

void CDoorplateWnd::paint_image(void)
{
	try
	{
		if (NULL==m_doorplate_image)
		{
			return;
		}
		Graphics image_graphics(m_hWnd);
		REAL m_image_left_x=0.0f;
		REAL m_image_top_y=0.0f;
		REAL m_image_show_width=0.0f;
		REAL m_image_show_height=0.0f;

		switch(m_image_show_mode)
		{
		default:
		case  DOORPLATE_IMAGE_NO_ANIMATION:      //ֱ����ʾû�ж���Ч��
			{
				image_graphics.DrawImage(m_doorplate_image,m_show_image_rect,0,0,m_image_width,m_image_height,UnitPixel);
				m_show_image_finish=true;
			}
			break;
		case DOORPLATE_IMAGE_RIGHT_TO_LEFT:     //���ҵ���
			{
				if (m_show_image_rect.X>m_slide_image_rect.X)
				{
					m_show_image_rect.X -= 16.0f;
					if (m_show_image_rect.X<m_slide_image_rect.X)
					{
						m_show_image_rect.X = m_slide_image_rect.X;
					}
					m_image_left_x = (m_show_image_rect.X-m_slide_image_rect.X)*m_image_width/m_slide_image_rect.Width;
					m_image_show_width = 16.0f*m_image_width/m_slide_image_rect.Width;
					image_graphics.DrawImage(m_doorplate_image,m_show_image_rect,m_image_left_x,0,m_image_show_width,m_image_height,UnitPixel);
				}
				else
				{
					m_show_image_finish = true;
				}
			}
			break;
		case DOORPLATE_IMAGE_LEFT_TO_RIGHT:     //������
			{
				if (m_show_image_rect.X<(m_slide_image_rect.X+m_slide_image_rect.Width))
				{
					m_show_image_rect.X += 16.0f;
					if (m_show_image_rect.X>(m_slide_image_rect.X+m_slide_image_rect.Width))
					{
						m_show_image_rect.X = m_slide_image_rect.X+m_slide_image_rect.Width-16.0f;
						m_show_image_finish = true;
					}
					m_image_left_x = (m_show_image_rect.X-m_slide_image_rect.X)*m_image_width/m_slide_image_rect.Width;
					m_image_show_width = 16.0f*m_image_width/m_slide_image_rect.Width;
					image_graphics.DrawImage(m_doorplate_image,m_show_image_rect,m_image_left_x,0,m_image_show_width,m_image_height,UnitPixel);
				}
				else
				{
					m_show_image_finish = true;
				}
			}
			break;
		case DOORPLATE_IMAGE_MIDDLE_TO_SIDES_X: //ˮƽ������м䵽����
			{
				if (m_show_image_rect.X>m_slide_image_rect.X)
				{
					m_show_image_rect.X -= 8.0f;
					if (m_show_image_rect.X<m_slide_image_rect.X)
					{
						m_show_image_rect.X = m_slide_image_rect.X;
					}
					m_image_left_x = (m_show_image_rect.X-m_slide_image_rect.X)*m_image_width/m_slide_image_rect.Width;
					m_image_show_width = 8.0f*m_image_width/m_slide_image_rect.Width;
					image_graphics.DrawImage(m_doorplate_image,m_show_image_rect,m_image_left_x,0,m_image_show_width,m_image_height,UnitPixel);
				}
				if (m_show_image_rect1.X<(m_slide_image_rect.X+m_slide_image_rect.Width))
				{
					m_show_image_rect1.X += 8.0f;
					if (m_show_image_rect.X>(m_slide_image_rect.X+m_slide_image_rect.Width))
					{
						m_show_image_rect.X = m_slide_image_rect.X+m_slide_image_rect.Width-8.0f;
					}
					m_image_left_x = (m_show_image_rect1.X-m_slide_image_rect.X)*m_image_width/m_slide_image_rect.Width;
					m_image_show_width = 8.0f*m_image_width/m_slide_image_rect.Width;
					image_graphics.DrawImage(m_doorplate_image,m_show_image_rect1,m_image_left_x,0,m_image_show_width,m_image_height,UnitPixel);
				}
				if((m_show_image_rect.X<=m_slide_image_rect.X)&&(m_show_image_rect1.X+8.0f>=(m_slide_image_rect.X+m_slide_image_rect.Width)))
				{
					m_show_image_finish = true;
				}
			}
			break;
		case DOORPLATE_IMAGE_MIDDLE_TO_SIDES_Y: //��ֱ������м䵽����
			{
				if (m_show_image_rect.Y>m_slide_image_rect.Y)
				{
					m_show_image_rect.Y -= 8.0f;
					if (m_show_image_rect.Y<m_slide_image_rect.Y)
					{
						m_show_image_rect.Y = m_slide_image_rect.Y;
					}
					m_image_top_y = (m_show_image_rect.Y-m_slide_image_rect.Y)*m_image_height/m_slide_image_rect.Height;
					m_image_show_height = 8.0f*m_image_height/m_slide_image_rect.Height;
					image_graphics.DrawImage(m_doorplate_image,m_show_image_rect,0,m_image_top_y,m_image_width,m_image_show_height,UnitPixel);
				}
				if (m_show_image_rect1.Y<(m_slide_image_rect.Y+m_slide_image_rect.Height))
				{
					m_show_image_rect1.Y += 8.0f;
					if (m_show_image_rect1.Y>(m_slide_image_rect.Y+m_slide_image_rect.Height))
					{
						m_show_image_rect1.Y = m_slide_image_rect.Y+m_slide_image_rect.Height-8.0f;
					}
					m_image_top_y = (m_show_image_rect1.Y-m_slide_image_rect.Y)*m_image_height/m_slide_image_rect.Height;
					m_image_show_height = 8.0f*m_image_height/m_slide_image_rect.Height;
					image_graphics.DrawImage(m_doorplate_image,m_show_image_rect1,0,m_image_top_y,m_image_width,m_image_show_height,UnitPixel);
				}
				if ((m_show_image_rect.Y<=m_slide_image_rect.Y)&&((m_show_image_rect1.Y+8.0f)>=(m_slide_image_rect.Y+m_slide_image_rect.Height)))
				{
					m_show_image_finish = true;
				}
			}
			break;
		case DOORPLATE_IMAGE_ZOON_IN:           //�Ŵ�
			{
				if (m_show_image_rect.X>m_slide_image_rect.X)
				{
					m_show_image_rect.X -= 8.0f;
					m_show_image_rect.Y -= m_add_height/2.0f;
					m_show_image_rect.Width += 16.0f;
					m_show_image_rect.Height += m_add_height;

					if ((m_show_image_rect.X<m_slide_image_rect.X)||(m_show_image_rect.Y<m_slide_image_rect.Y))
					{
						m_show_image_rect =  m_slide_image_rect;
						m_show_image_finish = true;
					}
					image_graphics.DrawImage(m_doorplate_image,m_show_image_rect,0,0,m_image_width,m_image_height,UnitPixel);
				}
				else
				{
					m_show_image_finish = true;
				}
			}
			break;
		}
	}
	catch (...)
	{
		
	}
	return;
}


void CDoorplateWnd::show_left_image(void)
{
	try
	{
        Graphics image_graphics(m_hWnd);
		Image *bg_image=NULL;
		Font myFont50(L"΢���ź�",50,FontStyleBold);
		Font myFont40(L"΢���ź�",40,FontStyleBold);
		Font myFont35(L"΢���ź�",35,FontStyleRegular);
		Font myFont32(L"΢���ź�",32,FontStyleRegular);
		Font myFont27(L"΢���ź�",27,FontStyleRegular);
		PointF left_point;
		StringFormat text_format;
		SolidBrush text_brush(Color(255,255, 0, 0));
		TCHAR show_text[256];
		REAL line_spacing=0.0f;
		REAL font_width=0.0f;
		FontFamily myFontFamily(L"΢���ź�");
		__time64_t cur_time;
		RectF text_rect;

		//�õ���ǰʱ��
		_time64(&cur_time);

		//���ر���ͼƬ
		bg_image = Image::FromFile(m_doorplate_bg_image_path);
		if (bg_image)
		{
			image_graphics.DrawImage(bg_image,m_static_image_rect,0,0,bg_image->GetWidth()*1.0f,bg_image->GetHeight()*1.0f,UnitPixel);
			//�ͷ�
			delete bg_image;
			bg_image = NULL;
		}
		text_format.SetAlignment(StringAlignmentNear);

		if (0==m_window_frame)
		{
			//���Ҽܹ�
			if (m_only_show_name_type)
			{
				//ֻ��ʾ�������ֺ�����		
				text_format.SetAlignment(StringAlignmentCenter);
				text_format.SetLineAlignment(StringAlignmentCenter);

				//show room name
				text_rect.X = m_static_image_rect.X;
				text_rect.Y = m_static_image_rect.Y+m_static_image_rect.Height/4;
				text_rect.Width = m_static_image_rect.Width;
				text_rect.Height = m_static_image_rect.Height/4;
				text_brush.SetColor(Color(255,255,255,0));
				image_graphics.DrawString(m_image_room_name,-1,&myFont50,text_rect,&text_format,&text_brush);

				//show room type
				text_rect.X = m_static_image_rect.X;
				text_rect.Y = m_static_image_rect.Y+m_static_image_rect.Height*3/5;
				text_rect.Width = m_static_image_rect.Width;
				text_rect.Height = m_static_image_rect.Height/4;
				text_brush.SetColor(Color(255,30,255,0));
				image_graphics.DrawString(m_image_room_type,-1,&myFont40,text_rect,&text_format,&text_brush);			
			}
			else
			{
				//�����м��
				line_spacing = m_static_image_rect.Height*0.65f/7;
				//�õ�����Ŀ��
				font_width = myFont27.GetHeight(&image_graphics)*myFontFamily.GetEmHeight(FontStyleRegular)/myFontFamily.GetLineSpacing(FontStyleRegular);
				if (font_width<=0)
				{
					font_width = 36;
				}

				//show room name
				left_point.X = m_static_image_rect.Width*0.11f;
				left_point.Y = m_static_image_rect.Height*0.35f;
				text_brush.SetColor(Color(255,249,184,184));
				image_graphics.DrawString(L"��������",-1,&myFont35,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_room_name,L""))
				{
					left_point.X += 5*font_width;
					text_brush.SetColor(Color(255,0,255,0));
					image_graphics.DrawString(m_image_room_name,-1,&myFont32,left_point,&text_format,&text_brush);
				}
				//show room type
				left_point.X = m_static_image_rect.Width*0.11f;
				left_point.Y += line_spacing+10;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"�������ͣ�",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_room_type,L""))
				{
					left_point.X += 5*font_width;
					image_graphics.DrawString(m_image_room_type,-1,&myFont27,left_point,&text_format,&text_brush);
				}
				//show open room time
				left_point.X = m_static_image_rect.Width*0.11f;
				left_point.Y += line_spacing;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"����ʱ�䣺",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_open_room_time,L""))
				{
					left_point.X += 5*font_width;
					image_graphics.DrawString(m_image_open_room_time,-1,&myFont27,left_point,&text_format,&text_brush);
				}
				//��������
				left_point.X = m_static_image_rect.Width*0.11f;
				left_point.Y += line_spacing;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"����������",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_people_count,L""))
				{
					left_point.X += 5*font_width;
					image_graphics.DrawString(m_image_people_count,-1,&myFont27,left_point,&text_format,&text_brush);
				}
				//����ʱ��
				left_point.X = m_static_image_rect.Width*0.11f;
				left_point.Y += line_spacing;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"����ʱ����",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_open_room_time,L""))   //�п���ʱ�����ʾ����ʱ��
				{
					memset(show_text,0x0,sizeof(show_text));
					left_point.X += 5*font_width;
					swprintf(show_text,L"%d����",(cur_time-m_open_room_time_second)/60);
					image_graphics.DrawString(show_text,-1,&myFont27,left_point,&text_format,&text_brush);
				}
				//���ѽ��
				left_point.X = m_static_image_rect.Width*0.11f;
				left_point.Y += line_spacing;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"���ѽ�",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_consume_money,L""))
				{
					left_point.X += 5*font_width;
					image_graphics.DrawString(m_image_consume_money,-1,&myFont27,left_point,&text_format,&text_brush);
				}
			}
		}
		else
		{
			//���½ṹ
			if (m_only_show_name_type)
			{
				//ֻ��ʾ�������ֺ�����
				text_format.SetAlignment(StringAlignmentCenter);
				//text_format.SetLineAlignment(StringAlignmentNear);

				//show room name
				text_rect.X = m_static_image_rect.X;
				text_rect.Y = m_static_image_rect.Y+m_static_image_rect.Height*5/16;
				text_rect.Width = m_static_image_rect.Width;
				text_rect.Height = m_static_image_rect.Height/3;
				text_brush.SetColor(Color(255,255,255,0));
				image_graphics.DrawString(m_image_room_name,-1,&myFont50,text_rect,&text_format,&text_brush);

				//show room type
				text_rect.X = m_static_image_rect.X;
				text_rect.Y = m_static_image_rect.Y+m_static_image_rect.Height*9/16;
				text_rect.Width = m_static_image_rect.Width;
				text_rect.Height = m_static_image_rect.Height/3;
				text_brush.SetColor(Color(255,30,255,0));
                image_graphics.DrawString(m_image_room_type,-1,&myFont40,text_rect,&text_format,&text_brush);
			}
			else
			{
				//�õ�����Ŀ��
				font_width = myFont27.GetHeight(&image_graphics)*myFontFamily.GetEmHeight(FontStyleRegular)/myFontFamily.GetLineSpacing(FontStyleRegular);
				if (font_width<=0)
				{
					font_width = 36;
				}

				//show room name
				left_point.X = m_static_image_rect.X + m_static_image_rect.Width*0.10f;
				left_point.Y = m_static_image_rect.Y + m_static_image_rect.Height*0.25f;
				text_brush.SetColor(Color(255,249,184,184));
				image_graphics.DrawString(L"��������",-1,&myFont35,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_room_name,L""))
				{
					left_point.X += 5*font_width;
					text_brush.SetColor(Color(255,0,255,0));
					image_graphics.DrawString(m_image_room_name,-1,&myFont32,left_point,&text_format,&text_brush);
				}
				//show room type
				left_point.X =m_static_image_rect.X + m_static_image_rect.Width*0.10f;
				left_point.Y = m_static_image_rect.Y + m_static_image_rect.Height*0.66f;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"�������ͣ�",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_room_type,L""))
				{
					left_point.X += 5*font_width;
					image_graphics.DrawString(m_image_room_type,-1,&myFont27,left_point,&text_format,&text_brush);
				}

				//show open room time
				left_point.X = m_static_image_rect.X + m_static_image_rect.Width*0.4f;
				left_point.Y = m_static_image_rect.Y + m_static_image_rect.Height*0.45f;;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"����ʱ�䣺",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_open_room_time,L""))
				{
					left_point.X += 5*font_width;
					image_graphics.DrawString(m_image_open_room_time,-1,&myFont27,left_point,&text_format,&text_brush);
				}
				//��������
				left_point.X = m_static_image_rect.X + m_static_image_rect.Width*0.4f;
				left_point.Y = m_static_image_rect.Y + m_static_image_rect.Height*0.66f;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"����������",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_people_count,L""))
				{
					left_point.X += 5*font_width;
					image_graphics.DrawString(m_image_people_count,-1,&myFont27,left_point,&text_format,&text_brush);
				}
				//����ʱ��
				left_point.X = m_static_image_rect.X + m_static_image_rect.Width*0.66f;
				left_point.Y = m_static_image_rect.Y + m_static_image_rect.Height*0.45f;;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"����ʱ����",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_open_room_time,L""))   //�п���ʱ�����ʾ����ʱ��
				{
					memset(show_text,0x0,sizeof(show_text));
					left_point.X += 5*font_width;
					swprintf(show_text,L"%d����",(cur_time-m_open_room_time_second)/60);
					image_graphics.DrawString(show_text,-1,&myFont27,left_point,&text_format,&text_brush);
				}
				//���ѽ��
				left_point.X = m_static_image_rect.X + m_static_image_rect.Width*0.66f;
				left_point.Y = m_static_image_rect.Y + m_static_image_rect.Height*0.66f;
				text_brush.SetColor(Color(255,255,255,255));
				image_graphics.DrawString(L"���ѽ�",-1,&myFont27,left_point,&text_format,&text_brush);
				if (0!=_tcscmp(m_image_consume_money,L""))
				{
					left_point.X += 5*font_width;
					image_graphics.DrawString(m_image_consume_money,-1,&myFont27,left_point,&text_format,&text_brush);
				}
			}
		}
	}
	catch(...)
	{

	}
	return;
}

UINT CDoorplateWnd::recv_room_data_thread(LPVOID pParam)
{
	try
	{
		CDoorplateWnd* pThis = reinterpret_cast<CDoorplateWnd *>(pParam);

		pThis->recv_room_data();

	}
	catch (...)
	{

	}
	return 0;
}

#define SLEEP_FOR Sleep(500)

void CDoorplateWnd::recv_room_data(void)
{
	try
	{
		fd_set socket_set;
		timeval overtime;
		overtime.tv_sec = 0;
		overtime.tv_usec = 10000;
		int result=0;

		//��������ʱ����ʾһ��ͼƬ
		//��ʾ����ͼƬ
		show_left_image();
		//show first image
		show_next_image();

		//��0
		FD_ZERO(&socket_set);

		//create socket
		SOCKET list_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (list_socket < 0) 
		{
			return;
		}
		//����socket����
		struct linger zerolinger;
		zerolinger.l_onoff = 1;
		zerolinger.l_linger = 5;
		setsockopt(list_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));
		int recv_timeout=60000;
		setsockopt(list_socket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&recv_timeout,sizeof(recv_timeout));

		//bind local addr
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		addr.sin_port = ntohs(6666);
		memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
		if (SOCKET_ERROR==bind(list_socket, (struct sockaddr*)&addr, sizeof(sockaddr_in)))
		{
			return;
		}
		//���������
		FD_SET(list_socket,&socket_set);
		while (m_thread_run)
		{
			try
			{
				SLEEP_FOR;

				//��fdSocket���ϵ�һ������fdRead���ݸ�select������
				// �����¼�����ʱ��select�����Ƴ�fdRead������û��δ��I/O�������׽��־����Ȼ�󷵻�
				fd_set fdRead_set = socket_set;
				result = ::select(0,&fdRead_set,NULL,NULL,&overtime);
				if (result<=0)
				{
					continue;
				}
				//ͨ����ԭ��fdSocket������select�������fdRead���ϱȽϣ�
				// ȷ��������Щ�׽�����δ��I/O������һ��������ЩI/O��
				for(int i=0; i<(int)socket_set.fd_count; i++)
				{
					if (FD_ISSET(socket_set.fd_array[i],&fdRead_set))
					{
						//recv data
						char recv_data[2048];
						int recv_len=0;
						sockaddr_in send_addr;
						int nLen = sizeof(send_addr);

						memset(recv_data,0x0,sizeof(recv_data));

						recv_len = ::recvfrom(socket_set.fd_array[i],recv_data,sizeof(recv_data),0,(sockaddr*)&send_addr, &nLen);
						if (recv_len>0)                     //(2)���ܵ�����
						{
							parse_recv_room_data(recv_data);
						}//end if
					}
				}//end for()
			}
			catch (...)
			{

			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

void CDoorplateWnd::parse_recv_room_data(char *recv_data)
{
	try
	{
		//�ַ�����ʽ��Message^$��������@����ʱ��@��������@���ѽ��^&End
		char room_info_data[2048];
		char *pre_split_symbol=NULL;
		char *cur_split_symbol=NULL;
		char temp_data[256];
		string_conversion string_conv;

		memset(room_info_data,0x0,sizeof(room_info_data));

		if (NULL==recv_data)
		{
			return;
		}
		
		strcpy(room_info_data,recv_data);
		//�жϿ�ʼ����
		if (0!=strncmp(room_info_data,"Message^$",9))
		{
			return;
		}
		//�õ�ǰһ���ָ���
		pre_split_symbol = strchr(room_info_data,'$');
		if (NULL==pre_split_symbol)
		{
			return;
		}
		//�õ���������
		pre_split_symbol++;
		cur_split_symbol = strchr(pre_split_symbol,'@');
		if (NULL==cur_split_symbol)
		{
			return;
		}
		memset(temp_data,0x0,sizeof(temp_data));
		memcpy(temp_data,pre_split_symbol,cur_split_symbol-pre_split_symbol);
		string_conv.multibyte_to_widechar(temp_data,m_image_room_type,sizeof(m_image_room_type)/sizeof(TCHAR));
		//����ʱ��
		pre_split_symbol = cur_split_symbol+1;
		cur_split_symbol = strchr(pre_split_symbol,'@');
		if (NULL==cur_split_symbol)
		{
			return;
		}
		memset(temp_data,0x0,sizeof(temp_data));
		memcpy(temp_data,pre_split_symbol,cur_split_symbol-pre_split_symbol);
		string_conv.multibyte_to_widechar(temp_data,m_image_open_room_time,sizeof(m_image_open_room_time)/sizeof(TCHAR));
		//�ѿ���ʱ��ת���ɾ���������
		convert_time_to_second(m_image_open_room_time);
		//��������
		pre_split_symbol = cur_split_symbol+1;
		cur_split_symbol = strchr(pre_split_symbol,'@');
		if (NULL==cur_split_symbol)
		{
			return;
		}
		memset(temp_data,0x0,sizeof(temp_data));
		memcpy(temp_data,pre_split_symbol,cur_split_symbol-pre_split_symbol);
		string_conv.multibyte_to_widechar(temp_data,m_image_people_count,sizeof(m_image_people_count)/sizeof(TCHAR));
		//���ѽ��
		pre_split_symbol = cur_split_symbol+1;
		cur_split_symbol = strchr(pre_split_symbol,'^');
		if (NULL==cur_split_symbol)
		{
			return;
		}
		memset(temp_data,0x0,sizeof(temp_data));
		memcpy(temp_data,pre_split_symbol,cur_split_symbol-pre_split_symbol);
		string_conv.multibyte_to_widechar(temp_data,m_image_consume_money,sizeof(m_image_consume_money)/sizeof(TCHAR));

		if (m_use_drinks_function)
		{
			//���þ�ˮ����
			__time64_t cur_time;
			int consume_time=0;

			//�õ���ǰʱ��
			_time64(&cur_time);

			memset(m_room_info_text,0x0,sizeof(m_room_info_text));
			//��������ʱ��
			consume_time = (cur_time-m_open_room_time_second)/60;
			//��֯�ַ���
			swprintf(m_room_info_text,L"<data><info name=\"%s\" type=\"%s\" open_time=\"%s\" people_count=\"%s\" consume_length=\"%d��\" consume_money=\"%s\"/></data>",m_image_room_name,m_image_room_type,m_image_open_room_time,m_image_people_count,consume_time,m_image_consume_money);
			//���͸�������
			::PostMessage(m_parent_handle,DM_DOORPLATE_ROOM_INFO,NULL,(LPARAM)m_room_info_text);
		}
		else
		{
			//���л滭�����¼�ʱ
			m_update_room_info_timer.start();
			//��ʾ������Ϣ
			show_left_image();
		}

		return;
	}
	catch(...)
	{

	}
	return;
}

void CDoorplateWnd::convert_time_to_second(TCHAR *time)
{
	try
	{
		CTime system_time = CTime::GetCurrentTime();
		int hour=0;
		int minute=0;

		//�õ�������ʱ��
		swscanf(time,L"%d:%d",&hour,&minute);

        CTime open_room_time(system_time.GetYear(),system_time.GetMonth(),system_time.GetDay(),hour,minute,system_time.GetSecond());

		//�õ�����ʱ�� ��
		m_open_room_time_second = open_room_time.GetTime();
	}
	catch (...)
	{
		
	}
	return;
}
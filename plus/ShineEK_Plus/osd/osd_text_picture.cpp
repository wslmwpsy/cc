#include "StdAfx.h"
#include ".\osd_text_picture.h"
#include "..\common\parser_color.h"
#include "..\common\StringCodeConversion.h"
#include "..\common\string_function.h"
#include "..\file\config_file.h"

osd_text_picture::osd_text_picture(void)
{
}

osd_text_picture::~osd_text_picture(void)
{
}

bool osd_text_picture::set_text(TCHAR *text)
{
	if ((NULL==text)||(0==_tcscmp(text,L"")))
	{
		return false;
	}
	m_text_info.Text(text);

	return true;
}

bool osd_text_picture::set_text_color(const TCHAR *text_color)
{
	try
	{
		if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(255,0,0));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(255,255,0));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(0,0,255));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(0,255,0));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(128,128,255));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(255,255,255));
		}
		else if ((*text_color>=_T('0') && *text_color<=_T('9')) || (*text_color>=_T('a') && *text_color<=_T('z')))
		{
			TCHAR color[32];
			memset(color,0x0,sizeof(color));
			_tcscpy(color, text_color);
			m_text_info.TextColor(parse_color(color));
		}
		else
		{
			// Ĭ�ϲ��ú�ɫ
			m_text_info.TextColor(RGB(255,0,0));
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_text_picture::set_text_color(COLORREF text_color)
{
	m_text_info.TextColor(text_color);

	return true;
}

bool osd_text_picture::set_text_font(const TCHAR *text_font)
{
	if ((NULL==text_font)||(0==_tcscmp(text_font,L"")))
	{
		return false;
	}

	m_text_info.TextFont(text_font);

	return true;
}

bool osd_text_picture::set_text_size(int text_size)
{
	m_text_info.TextSize(text_size);

	return true;
}

bool osd_text_picture::set_text_Background_color(const TCHAR *text_color)
{
	try
	{
		if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(255,0,0));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(255,255,0));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(0,0,255));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(0,255,0));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(128,128,255));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(255,255,255));
		}
		else if (_tcsncmp(text_color, L"��ɫ", sizeof("��ɫ") / sizeof(TCHAR)) == 0)  //2010-03-24 add
		{
			m_text_info.ShadeColor(RGB(0,0,0));
		}
		else if ((*text_color>=_T('0') && *text_color<=_T('9')) || (*text_color>=_T('a') && *text_color<=_T('z')))
		{
			TCHAR color[32];
			memset(color,0x0,sizeof(color));
			_tcscpy(color, text_color);
			m_text_info.ShadeColor(parse_color(color));
		}
		else
		{
			// Ĭ�ϲ��ú�ɫ
			m_text_info.ShadeColor(RGB(255,0,0));
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool osd_text_picture::set_message_type(char *message_type)
{
	try
	{
		if (NULL==message_type)
		{
			return false;
		}

		if (strcmp(message_type, "����") == 0)
		{
			m_message_type = MESSAGE_NOTICE;
		}
		else if (strcmp(message_type, "ף����") == 0)
		{
			m_message_type = MESSAGE_BLESSING;
		}
		else if (strcmp(message_type, "Ѱ������") == 0)
		{
			m_message_type = MESSAGE_FOUND_SOME_ONE;
		}
		else if (strcmp(message_type, "����Ԥ��") == 0)
		{
			m_message_type = MESSAGE_PAY_REMANDING;
		}
		else if (strcmp(message_type, "������Ӧ") == 0)
		{
			m_message_type = MESSAGE_SERVICE_ANSWER;
		}
		else if (strcmp(message_type, "��") == 0)
		{
			m_message_type = MESSAGE_FIRE_ALARM;
		}
		else if (strcmp(message_type, "�˾�") == 0)
		{
			m_message_type = MESSAGE_ROBBER_ALARM;
		}
		else
		{
			// Ĭ����Ϊ�����桱
			m_message_type = MESSAGE_NOTICE;
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_text_picture::set_show_mode(const TCHAR *show_mode)
{
	try
	{
		if (NULL==show_mode)
		{
			return false;
		}

		if (_tcsncmp(show_mode, L"��������ʾ", sizeof(L"��������ʾ") / sizeof(TCHAR)) == 0)
		{
			m_show_mode = MESSAGE_SHOW_TV;
		}
		else if (_tcsncmp(show_mode, L"���������ʾ", sizeof(L"���������ʾ") / sizeof(TCHAR)) == 0)
		{
			m_show_mode = MESSAGE_SHOW_COMPUTER;
		}
		else if (_tcsncmp(show_mode, L"ͬʱ��ʾ", sizeof(L"ͬʱ��ʾ") / sizeof(TCHAR)) == 0)
		{
			m_show_mode = MESSAGE_SHOW_BOTH;
		}
		else
		{
			m_show_mode = MESSAGE_SHOW_NONE;
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_text_picture::set_content_type(TCHAR *content_type)
{
	try
	{
		if (NULL==content_type)
		{
			return false;
		}

		if (_tcsncmp(content_type, L"����", sizeof(L"����") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_TEXT;
		}
		else if (_tcsncmp(content_type, L"ͼƬ", sizeof(L"ͼƬ") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_PICTURE;
		}
		else if (_tcsncmp(content_type, L"��Ƶ", sizeof(L"��Ƶ") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_MPG;
		}
		else if (_tcsncmp(content_type, L"ͼƬ������", sizeof(L"ͼƬ������") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_BOTH;
		}
		else if (_tcsncmp(content_type, L"��Ƶ������", sizeof(L"��Ƶ������") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_MPG_BOTH;
		}
		else
		{
			m_content_type = MESSAGE_NONE;
		}
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_text_picture::set_scroll_mode(const TCHAR *scroll_mode,enum MESSAGE_CONTENT_TYPE osd_type)
{
	try
	{
		enum OSD_PLAY_MODE play_mode;

		if (NULL==scroll_mode)
		{
			return false;
		}

		if (_tcsncmp(scroll_mode, L"��̬��ʾ", sizeof(L"��̬��ʾ") / sizeof(TCHAR)) == 0)
		{
			play_mode = OSD_STATIC;
		}
		else if (_tcsncmp(scroll_mode, L"�ҽ����", sizeof(L"�ҽ����") / sizeof(TCHAR)) == 0)
		{
			play_mode = OSD_RIGHT_TO_LEFT;
		}
		else
		{
			// Ĭ�ϲ��á��ҽ�������ķ�ʽ
			play_mode = OSD_RIGHT_TO_LEFT;
		}

		if (MESSAGE_TEXT==osd_type)
		{
			//�������ֵĹ���ģʽ
			m_text_scroll_mode = play_mode;
			m_text_play_variable.play_mode = play_mode;
		}
		else if (MESSAGE_PICTURE==osd_type)
		{
			// ����ͼƬ����ģʽ
			m_picture_scroll_mode = play_mode;
			m_picture_play_variable.play_mode = play_mode;
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_text_picture::set_scroll_mode(enum OSD_PLAY_MODE scroll_mode,enum MESSAGE_CONTENT_TYPE osd_type)
{
	if (MESSAGE_TEXT==osd_type)
	{
		//�������ֵĹ���ģʽ
		m_text_scroll_mode = scroll_mode;
		m_text_play_variable.play_mode = scroll_mode;
	}
	else if (MESSAGE_PICTURE==osd_type)
	{
		// ����ͼƬ����ģʽ
		m_picture_scroll_mode = scroll_mode;
		m_picture_play_variable.play_mode = scroll_mode;
		//��������
		adjust_picture_position();
	}

	return true;
}

bool osd_text_picture::set_scroll_count(TCHAR *scroll_count)
{
	int count=0;
	if (NULL==scroll_count)
	{
		return false;
	}
	count = _ttoi(scroll_count);
	set_scroll_count(count);

	return true;
}

bool osd_text_picture::set_scroll_count(int scroll_count)
{
	if (scroll_count >= 0)
	{
		m_text_play_variable.nRepeat = scroll_count;
		this->m_scroll_count = scroll_count;
	}

	return true;
}

bool osd_text_picture::set_scroll_speed(TCHAR *scroll_speed)
{
	if (NULL==scroll_speed)
	{
		return false;
	}

	int speed = _ttoi(scroll_speed);

	set_scroll_speed(speed);

	return true;
}

bool osd_text_picture::set_scroll_speed(int scroll_speed)
{
	if (scroll_speed>0)
	{
		m_text_play_variable.iVSpeed = scroll_speed;
		m_text_play_variable.iHSpeed = scroll_speed;
		m_picture_play_variable.iVSpeed = scroll_speed;
		m_picture_play_variable.iHSpeed = scroll_speed;
	}

	return true;
}

bool osd_text_picture::set_scroll_position_x(TCHAR *position)
{
	if (NULL==position)
	{
		return false;
	}
	m_text_play_variable.sx = _ttoi(position);

	return true;
}

bool osd_text_picture::set_scroll_position_y(TCHAR *position)
{
	if (NULL==position)
	{
		return false;
	}
	m_text_play_variable.sy = _ttoi(position);

	return true;
}

bool osd_text_picture::set_scroll_position_x(int position)
{
    m_text_play_variable.sx = position;

	return true;
}

bool osd_text_picture::set_scroll_position_y(int position)
{
	m_text_play_variable.sy = position;

	return true;
}

void osd_text_picture::adjust_text_position(int start_x)	// �������ֹ������ͣ�ȷ����ʼ����ֹ����
{
	try
	{
		//Ŀǰֻ֧���ҽ����
		config_file_manager config_file;

		m_text_play_variable.sx = start_x;
		m_text_play_variable.sy = config_file.read_integer(L"osd",L"scroll_text_y",25);
		m_text_play_variable.ex = config_file.read_integer(L"osd",L"scroll_text_x",20);
		m_text_play_variable.ey = config_file.read_integer(L"osd",L"scroll_text_y",25);
	}
	catch (...)
	{	
	}
	return;
}

void osd_text_picture::adjust_picture_position()	// ����ͼƬ�������ͣ�ȷ����ʼ����ֹ����
{
	switch (m_picture_scroll_mode)
	{
	default: // Ĭ��ͬ���ҽ������
	case OSD_RIGHT_TO_LEFT:
		m_picture_play_variable.sx = 720;
		m_picture_play_variable.sy = 20;
		m_picture_play_variable.ex = 0;
		m_picture_play_variable.ey = 0;
		break;
	case OSD_STATIC:		
		{
			m_picture_play_variable.sx = 0;
			m_picture_play_variable.sy = 0;
			m_picture_play_variable.ex = 800;
			m_picture_play_variable.ey = 800;
		}
		break;
	}
	return;
}

bool osd_text_picture::get_text_info(text_osd_info &text_info)
{
	try
	{
		text_info = m_text_info;

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_text_picture::get_text_play_variable(play_variable &play_var)
{
	try
	{
		play_var = m_text_play_variable;
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_text_picture::get_picture_play_variable(play_variable &play_var)
{
	try
	{
		play_var = m_picture_play_variable;
		return true;
	}
	catch (...)
	{

	}
	return false;
}

/*
�����͵���Ϣ�ַ����������µĸ�ʽ�������ڵĲ��֣���"Message^&ף����:���տ��֣�;���������ʾ;����;��ɫ;��̬��ʾ;�ҽ����;3;^&0^&KTV-TEXT^&0"
��ϸ���ͣ����ַ�����Message^&����ͷ��Ȼ��Ϊ��Ϣ���ͣ�����:��������֮��Ϊ��Ϣ���ı����ݣ�����;��������֮��Ϊ�ԡ�;���ָ��Ķ����Ϣ��ʾ�Ĳ���������Ϊ��Ϣ��ʾλ�á��������͡�������ɫ�����ֹ�����ʽ��ͼƬ������ʽ������������֮��Ϊ��^&0^&��������������^&0����
��Ϣ���͵�ȡֵ�������桱����ף���ʡ�����Ѱ�����¡���������Ԥ�桱����������Ӧ�������𾯡������˾�����
��Ϣ��ʾλ�õ�ȡֵ������������ʾ���������������ʾ������ͬʱ��ʾ����
��Ϣ�������͵�ȡֵ�������֡�����ͼƬ������ͼƬ�����֡���
��Ϣ������ɫ��ȡֵ������ɫ��������ɫ��������ɫ��������ɫ��������ɫ��������ɫ����
���ֹ�����ʽ��ȡֵ������̬��ʾ�������ҽ��������������ҳ��������ҽ��ϳ��������Ͻ��³��������½��ϳ�����
ͼƬ������ʽ��ȡֵ������̬��ʾ�������ҽ��������
*/
bool osd_text_picture::parse_msg(const char *msg, LPMOVIE_MSG_CONTROL lpMMCtrl /* = NULL */)
{
	try
	{
		string_conversion str_conv;
		const char *parse_msg=NULL;
		const char *temp=NULL;
		char msg_item[2048];
		TCHAR set_msg_item[2048];

		if (NULL==msg)
		{
			return false;
		}
		parse_msg = msg;
		if (0!=strnicmp(parse_msg,"Message^&",9))
		{
			return false;
		}
		//����9���ֽ�
		parse_msg += 9;

		//����ð��
		temp = strchr(parse_msg,':');
		if (NULL==temp)
		{
			return false;
		}
		//������Ϣ����
		memset(msg_item,0x0,sizeof(msg_item));
		memcpy(msg_item,parse_msg,temp-parse_msg);
		set_message_type(msg_item);

		str_conv.multibyte_to_widechar(msg_item,set_msg_item,sizeof(set_msg_item));
		if (lpMMCtrl != NULL)
		{
			lpMMCtrl->head = HEAD_FLAG;
			lpMMCtrl->mmt = MMT_CHARACTER_MSG;
			_tcscpy(lpMMCtrl->mssm.szMsgType, set_msg_item);
		}		

		for (int i=0;i<7;i++)
		{
			//��һ��ð�ŵ�λ��
			parse_msg = temp+1;
			temp = strchr(parse_msg,';');
			if (NULL==temp)
			{
				temp = strchr(parse_msg,'^');
				if (NULL==temp)
				{
					break;
				}
			}
			memset(msg_item,0x0,sizeof(msg_item));
			if (temp-parse_msg<1)
			{
				continue;
			}
			memcpy(msg_item,parse_msg,temp-parse_msg);
			str_conv.multibyte_to_widechar(msg_item,set_msg_item,sizeof(set_msg_item));
			switch(i)
			{
			case 0:
				{
                    //��������
					flash_replace_special_char(set_msg_item);
                    set_text(set_msg_item);
					if (lpMMCtrl != NULL)
						_tcscpy(lpMMCtrl->mssm.szContent, set_msg_item);
				}
				break;
			case 1:
				{
					//��Ϣ��ʾ��λ��
					set_show_mode(set_msg_item);
					if (lpMMCtrl != NULL)
						_tcscpy(lpMMCtrl->mssm.szShowMode, set_msg_item);
				}
				break;
			case 2:
				{
					//������������
					set_content_type(set_msg_item);
					if (lpMMCtrl != NULL)
						_tcscpy(lpMMCtrl->mssm.szContentType, set_msg_item);
				}
				break;
			case 3:
				{
					//�������ֵ���ɫ
					set_text_color(set_msg_item);
					if (lpMMCtrl != NULL)
						_tcscpy(lpMMCtrl->mssm.szTextColor, set_msg_item);
				}
				break;
			case 4:
				{
					//�������ֵĹ�����ʽ
					set_scroll_mode(OSD_RIGHT_TO_LEFT,MESSAGE_TEXT);
				}
				break;
			case 5:
				{
					//����ͼƬ�Ĺ�����ʽ
					set_scroll_mode(OSD_STATIC,MESSAGE_PICTURE);
				}
				break;
			case 6:
				{
					//���ù�������
					set_scroll_count(set_msg_item);
					if (lpMMCtrl != NULL)
						lpMMCtrl->mssm.iScrollCount = _ttoi(set_msg_item);
				}
				break;
			default:
				break;
			}
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

MESSAGE_SHOW_MODE osd_text_picture::get_show_mode(void)
{
	return m_show_mode;
}

MESSAGE_CONTENT_TYPE osd_text_picture::get_content_type(void)
{
	return m_content_type;
}

MESSAGE_TYPE  osd_text_picture::get_message_type(void)
{
	return m_message_type;
}
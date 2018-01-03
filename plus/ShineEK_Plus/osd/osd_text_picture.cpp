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
		if (_tcsncmp(text_color, L"红色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(255,0,0));
		}
		else if (_tcsncmp(text_color, L"黄色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(255,255,0));
		}
		else if (_tcsncmp(text_color, L"蓝色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(0,0,255));
		}
		else if (_tcsncmp(text_color, L"绿色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(0,255,0));
		}
		else if (_tcsncmp(text_color, L"紫色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.TextColor(RGB(128,128,255));
		}
		else if (_tcsncmp(text_color, L"白色", sizeof("红色") / sizeof(TCHAR)) == 0)
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
			// 默认采用红色
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
		if (_tcsncmp(text_color, L"红色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(255,0,0));
		}
		else if (_tcsncmp(text_color, L"黄色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(255,255,0));
		}
		else if (_tcsncmp(text_color, L"蓝色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(0,0,255));
		}
		else if (_tcsncmp(text_color, L"绿色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(0,255,0));
		}
		else if (_tcsncmp(text_color, L"紫色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(128,128,255));
		}
		else if (_tcsncmp(text_color, L"白色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			m_text_info.ShadeColor(RGB(255,255,255));
		}
		else if (_tcsncmp(text_color, L"黑色", sizeof("黑色") / sizeof(TCHAR)) == 0)  //2010-03-24 add
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
			// 默认采用红色
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

		if (strcmp(message_type, "公告") == 0)
		{
			m_message_type = MESSAGE_NOTICE;
		}
		else if (strcmp(message_type, "祝福词") == 0)
		{
			m_message_type = MESSAGE_BLESSING;
		}
		else if (strcmp(message_type, "寻人启事") == 0)
		{
			m_message_type = MESSAGE_FOUND_SOME_ONE;
		}
		else if (strcmp(message_type, "结帐预告") == 0)
		{
			m_message_type = MESSAGE_PAY_REMANDING;
		}
		else if (strcmp(message_type, "服务响应") == 0)
		{
			m_message_type = MESSAGE_SERVICE_ANSWER;
		}
		else if (strcmp(message_type, "火警") == 0)
		{
			m_message_type = MESSAGE_FIRE_ALARM;
		}
		else if (strcmp(message_type, "匪警") == 0)
		{
			m_message_type = MESSAGE_ROBBER_ALARM;
		}
		else
		{
			// 默认作为“公告”
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

		if (_tcsncmp(show_mode, L"电视上显示", sizeof(L"电视上显示") / sizeof(TCHAR)) == 0)
		{
			m_show_mode = MESSAGE_SHOW_TV;
		}
		else if (_tcsncmp(show_mode, L"计算机上显示", sizeof(L"计算机上显示") / sizeof(TCHAR)) == 0)
		{
			m_show_mode = MESSAGE_SHOW_COMPUTER;
		}
		else if (_tcsncmp(show_mode, L"同时显示", sizeof(L"同时显示") / sizeof(TCHAR)) == 0)
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

		if (_tcsncmp(content_type, L"文字", sizeof(L"文字") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_TEXT;
		}
		else if (_tcsncmp(content_type, L"图片", sizeof(L"图片") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_PICTURE;
		}
		else if (_tcsncmp(content_type, L"视频", sizeof(L"视频") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_MPG;
		}
		else if (_tcsncmp(content_type, L"图片和文字", sizeof(L"图片和文字") / sizeof(TCHAR)) == 0)
		{
			m_content_type = MESSAGE_BOTH;
		}
		else if (_tcsncmp(content_type, L"视频和文字", sizeof(L"视频和文字") / sizeof(TCHAR)) == 0)
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

		if (_tcsncmp(scroll_mode, L"静态显示", sizeof(L"静态显示") / sizeof(TCHAR)) == 0)
		{
			play_mode = OSD_STATIC;
		}
		else if (_tcsncmp(scroll_mode, L"右进左出", sizeof(L"右进左出") / sizeof(TCHAR)) == 0)
		{
			play_mode = OSD_RIGHT_TO_LEFT;
		}
		else
		{
			// 默认采用“右进左出”的方式
			play_mode = OSD_RIGHT_TO_LEFT;
		}

		if (MESSAGE_TEXT==osd_type)
		{
			//设置文字的滚动模式
			m_text_scroll_mode = play_mode;
			m_text_play_variable.play_mode = play_mode;
		}
		else if (MESSAGE_PICTURE==osd_type)
		{
			// 设置图片滚动模式
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
		//设置文字的滚动模式
		m_text_scroll_mode = scroll_mode;
		m_text_play_variable.play_mode = scroll_mode;
	}
	else if (MESSAGE_PICTURE==osd_type)
	{
		// 设置图片滚动模式
		m_picture_scroll_mode = scroll_mode;
		m_picture_play_variable.play_mode = scroll_mode;
		//调整坐标
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

void osd_text_picture::adjust_text_position(int start_x)	// 根据文字滚动类型，确定起始和终止坐标
{
	try
	{
		//目前只支持右进左出
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

void osd_text_picture::adjust_picture_position()	// 根据图片滚动类型，确定起始和终止坐标
{
	switch (m_picture_scroll_mode)
	{
	default: // 默认同“右进左出”
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
所发送的消息字符串采用如下的格式（引号内的部分）："Message^&祝福词:生日快乐！;计算机上显示;文字;绿色;静态显示;右进左出;3;^&0^&KTV-TEXT^&0"
详细解释：以字符串“Message^&”开头，然后为消息类型，至“:”结束，之后为消息的文本内容，至“;”结束；之后为以“;”分隔的多个消息显示的参数，依次为消息显示位置、内容类型、文字颜色、文字滚动方式、图片滚动方式、滚动次数；之后为“^&0^&”＋机器名＋“^&0”。
消息类型的取值：“公告”、“祝福词”、“寻人启事”、“结帐预告”、“服务响应”、“火警”、“匪警”。
消息显示位置的取值：“电视上显示”、“计算机上显示”、“同时显示”。
消息内容类型的取值：“文字”、“图片”、“图片和文字”。
消息文字颜色的取值：“红色”、“黄色”、“蓝色”、“绿色”、“紫色”、“白色”。
文字滚动方式的取值：“静态显示”、“右进左出”、“左进右出”、“右进上出”、“上进下出”、“下进上出”。
图片滚动方式的取值：“静态显示”、“右进左出”。
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
		//后移9个字节
		parse_msg += 9;

		//查找冒号
		temp = strchr(parse_msg,':');
		if (NULL==temp)
		{
			return false;
		}
		//设置消息类型
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
			//加一个冒号的位置
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
                    //文字内容
					flash_replace_special_char(set_msg_item);
                    set_text(set_msg_item);
					if (lpMMCtrl != NULL)
						_tcscpy(lpMMCtrl->mssm.szContent, set_msg_item);
				}
				break;
			case 1:
				{
					//消息显示的位置
					set_show_mode(set_msg_item);
					if (lpMMCtrl != NULL)
						_tcscpy(lpMMCtrl->mssm.szShowMode, set_msg_item);
				}
				break;
			case 2:
				{
					//设置内容类型
					set_content_type(set_msg_item);
					if (lpMMCtrl != NULL)
						_tcscpy(lpMMCtrl->mssm.szContentType, set_msg_item);
				}
				break;
			case 3:
				{
					//设置文字的颜色
					set_text_color(set_msg_item);
					if (lpMMCtrl != NULL)
						_tcscpy(lpMMCtrl->mssm.szTextColor, set_msg_item);
				}
				break;
			case 4:
				{
					//设置文字的滚动方式
					set_scroll_mode(OSD_RIGHT_TO_LEFT,MESSAGE_TEXT);
				}
				break;
			case 5:
				{
					//设置图片的滚动方式
					set_scroll_mode(OSD_STATIC,MESSAGE_PICTURE);
				}
				break;
			case 6:
				{
					//设置滚动次数
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
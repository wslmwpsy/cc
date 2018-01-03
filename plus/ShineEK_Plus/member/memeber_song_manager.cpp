#include "StdAfx.h"
#include "memeber_song_manager.h"
#include "..\common\string_function.h"
#include "..\common\StringCodeConversion.h"
#include "..\parserxml\ParserXml.h" 
#include "..\file\config_file.h"

memeber_song_manager::memeber_song_manager(void)
{
	initialized_variables();
}


memeber_song_manager::~memeber_song_manager(void)
{

}

void memeber_song_manager::initialized_variables(void)
{
	member_flags = MEMBER_FLAG_LOGIN_NO;
	memset(user_name,0x0,sizeof(user_name));  //会员的名字
	memset(user_password,0x0,sizeof(user_password)); //会员密码
	memset(user_sex,0x0,sizeof(user_sex));  //性别
	memset(nick_name,0x0,sizeof(nick_name)); //用户昵称
	memset(user_head,0x0,sizeof(user_head));//用户头像
	memset(member_down_address,0x0,sizeof(member_down_address));
	memset(user_identitycard,0x0,sizeof(user_identitycard));

	config_file_manager config_file;
	string_conversion string_conv;
	
	//服务程序所在的服务器IP
	std::wstring server_ip = config_file.read_string(L"server",L"service_server_ip",L"");
	if (!server_ip.empty())
	{
		//memset(m_service_server_ip,0x0,sizeof(m_service_server_ip));
		//string_conv.widechar_to_multibyte(server_ip.c_str(),m_service_server_ip,sizeof(m_service_server_ip));
		_tcscpy(m_service_server_ip,server_ip.c_str());
	}

	m_member_song_total_count = 0;
	m_member_song_total_page = 0;
	m_member_current_page =1;
}

MEMBER_FLAG memeber_song_manager::get_login_flags()
{
	return (MEMBER_FLAG)member_flags;
}


 

bool memeber_song_manager::set_login_flags(int value)
{
	try
	{
		 member_flags = (MEMBER_FLAG)value;
	}
	catch (...)
	{

	}
	return false;
}


bool memeber_song_manager::set_user_name(const TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(user_name)/2)
		{
			return false;
		}
		memset(user_name,0x0,sizeof(user_name));
		_tcscpy(user_name,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool memeber_song_manager::set_user_password(const TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(user_password)/2)
		{
			return false;
		}
		memset(user_password,0x0,sizeof(user_password));
		_tcscpy(user_password,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool memeber_song_manager::set_user_sex(const TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(user_sex)/2)
		{
			return false;
		}
		memset(user_sex,0x0,sizeof(user_sex));
		_tcscpy(user_sex,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool memeber_song_manager::set_nick_name(const TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(nick_name)/2)
		{
			return false;
		}
		memset(nick_name,0x0,sizeof(nick_name));
		_tcscpy(nick_name,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool memeber_song_manager::set_user_head(const TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(user_head)/2)
		{
			return false;
		}
		memset(user_head,0x0,sizeof(user_head));
		_tcscpy(user_head,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool memeber_song_manager::set_user_identitycard(const TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		if (_tcslen(value)>=sizeof(user_identitycard)/2)
		{
			return false;
		}
		memset(user_identitycard,0x0,sizeof(user_identitycard));
		_tcscpy(user_identitycard,value);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool memeber_song_manager::parse_memeber_head_picture_name(IN TCHAR* down_addr)
{
	try
	{
		TCHAR *install_path = _tcsrchr(down_addr,'/');

		//Pictures/UserPictures/140112302493/s5376bacc-106e-4563-b796-3e28e.jpg
		if (install_path)
		{
			 
		}
		else
		{
			return false;
		} 
		/*_tcscpy(user_head,L"\\\\%s\\face\\",m_service_server_ip);
		_tcscpy(user_head,install_path+1);*/

		swprintf(user_head,L"\\\\%s\\ktv10Service\\face\\%s",m_service_server_ip,install_path+1);
		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool memeber_song_manager::parse_memeber_song_info(char *recv_data,std::wstring &song_id_list)
{
	try
	{
		TCHAR member_song_id[1024*10];
		TCHAR msg_item[256]; //得到当前发过来的类型 
		const TCHAR *parse_msg=NULL;
		const TCHAR *temp=NULL; 
		string_conversion string_con;
		memset(member_song_id,0x0,sizeof(member_song_id));
		bool result = false;
		CMarkup parse_xml_doc;
		std::wstring item_value;
		TCHAR song_id[256];
		int nPos = 0; 

		string_con.utf8_to_widechar(recv_data,member_song_id,sizeof(member_song_id));

		parse_msg = member_song_id+1;
		memset(msg_item,0x0,sizeof(msg_item));
		temp = _tcschr(parse_msg,'$');
		if (!temp)
		{
			return false;
		}
		memset(msg_item,0x0,sizeof(msg_item));
		memcpy(msg_item,parse_msg,(temp-parse_msg)*sizeof(TCHAR));
		swscanf(msg_item,L"COUNT=%d",&m_member_song_total_count);

		if (m_member_song_total_count%48)
		{
			m_member_song_total_page = m_member_song_total_count/48 + 1;
		}
		else
		{
			m_member_song_total_page = m_member_song_total_count/48;
		}

		parse_msg = temp+1;
		temp = _tcschr(parse_msg,'$');
		memset(msg_item,0x0,sizeof(msg_item));
		memcpy(msg_item,parse_msg,(temp-parse_msg)*sizeof(TCHAR));

		parse_msg = temp+1;

		/*MYSTOREINFO $COUNT=100$PLACENEW$
			<song_list>
			<item>
			<song_id>29103</song_id>
			</item>
			</song_list>
			*/

		//解析xml文档
		result =parse_xml_doc.SetDoc(parse_msg);
		if (!result)
		{
			return false;
		}
		parse_xml_doc.ResetPos();   //list
		result = parse_xml_doc.FindChildElem(); 
		if (!result)
		{
			return false;
		}

		parse_xml_doc.IntoElem();  
		result = parse_xml_doc.FindChildElem(); //<item>

		if (!result)
		{
			return false;
		}

		while(true)
		{
			parse_xml_doc.IntoElem();  //song_id
			item_value = parse_xml_doc.GetData(); 
			memset(song_id,0x0,sizeof(song_id));
			//_tcscpy(song_id,item_value.c_str());
			song_id_list += item_value;

			parse_xml_doc.OutOfElem();
			result = parse_xml_doc.FindChildElem();

			nPos++;
			if (nPos>=48 || !result)
			{
				break;
			}

			song_id_list+=L",";
		}


		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool memeber_song_manager::parse_member_info(char *recv_data)
{
	try
	{	
		TCHAR data[1024];
		string_conversion string_con;
		CMarkup parse_xml_doc;
		bool result = false;
		std::wstring item_value; 

		member_flags = MEMBER_FLAG_LOGIN;

		memset(data,0x0,sizeof(data));
		string_con.utf8_to_widechar(recv_data,data,sizeof(data));
		/*
			MEMBERUSERINFO
			<user_info>
			<item> 
			<is_login>true</is_login>
			<login_name>一路顺疯</login_name>
			<nick_name>一路顺疯</nick_name>
			<sex>男</sex>
			< member_addr>Pictures/UserPictures/140112302493/s5376bacc-106e-4563-b796-3e28e.jpg</member_addr>
			<identitycard>43CF50F54A23</identitycard>
			</item>
			</user_info>
		*/
		//解析xml文档
		result =parse_xml_doc.SetDoc(data);
		if (!result)
		{
			return false;
		}
		parse_xml_doc.ResetPos();   //user_info
		result = parse_xml_doc.FindChildElem(); 
		if (!result)
		{
			return false;
		}

		parse_xml_doc.IntoElem();  
		result = parse_xml_doc.FindChildElem(); //<item>
		if (!result)
		{
			return false;
		}
		parse_xml_doc.IntoElem();  //is_login
		item_value = parse_xml_doc.GetData(); 
		if (0 == _tcscmp(item_value.c_str(),L"true"))
		{
			member_flags = MEMBER_FLAG_LOGIN;
		}
		else if (0 ==_tcscmp(item_value.c_str(),L"404"))
		{
			member_flags = MEMBER_FLAG_ERROR;

			return true;
		} 
		else if (0 ==_tcscmp(item_value.c_str(),L"5"))
		{
			member_flags = MEMBER_FLAG_PHONE_CODE_ERROR;
			return true;
		}
		else if (0 ==_tcscmp(item_value.c_str(),L"12"))
		{
			member_flags = MEMBER_FLAG_PHONE_REGISTER;
			return true;
		}
		else
		{
			member_flags = MEMBER_FLAG_LOGIN_NO;

			return true;
		}

		parse_xml_doc.FindElem(); //user_name
		item_value = parse_xml_doc.GetData();
		_tcscpy(user_name,item_value.c_str());

		parse_xml_doc.FindElem();  //nick_name
		item_value = parse_xml_doc.GetData();
		_tcscpy(nick_name,item_value.c_str());

		parse_xml_doc.FindElem();   //user_sex
		item_value = parse_xml_doc.GetData();
		_tcscpy(user_sex,item_value.c_str());

		parse_xml_doc.FindElem();   //member_addr
		item_value = parse_xml_doc.GetData();
		_tcscpy(member_down_address,item_value.c_str());
		//解析得到头像的地址 
		parse_memeber_head_picture_name(member_down_address);


		parse_xml_doc.FindElem();    //identitycard
		item_value = parse_xml_doc.GetData();
		_tcscpy(user_identitycard,item_value.c_str());
 
		//返回<item>
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem();  

		return true;

	}
	catch (...)
	{
		
	}

	return false;
} 

bool memeber_song_manager::get_member_down_address(TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,member_down_address);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool memeber_song_manager::get_user_identitycard(TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,user_identitycard);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool memeber_song_manager::get_user_name(TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,user_name);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool memeber_song_manager::get_user_password(TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,user_password);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool memeber_song_manager::get_user_sex(TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,user_sex);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool memeber_song_manager::get_nick_name(TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,nick_name);
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool memeber_song_manager::get_user_head(TCHAR* value)
{
	try
	{
		if (NULL==value)
		{
			return false;
		}
		wcscpy(value,user_head);
		return true;
	}
	catch (...)
	{

	}
	return false;
} 


int memeber_song_manager::get_total_member_count()
{
	return m_member_song_total_count;
}

int memeber_song_manager::get_total_member_page()
{
	return m_member_song_total_page;
}

int memeber_song_manager::get_current_member_page()
{
	return m_member_current_page;
}

void memeber_song_manager::set_current_member_page(PAGE_OPERATE page_operate/*,int page_number*/)
{
	try
	{ 
		if (FIRST_PAGE_OPERATE == page_operate)
		{
			//第一页数据
		}
		else if (CUR_PAGE_OPERATE == page_operate)
		{
			//当前页
		}
		else if (PRE_PAGE_OPERATE == page_operate)
		{
			//向上翻页
			if (m_member_current_page <= 1)
			{
				m_member_current_page=1;
			}
			else
			{
				m_member_current_page--;
			}
			
		}
		else if (NEXT_PAGE_OPERATE == page_operate)
		{
			//向下翻页
			if (m_member_current_page >= m_member_song_total_page)
			{
				m_member_current_page = m_member_song_total_count;
			}
			else
			{
				m_member_current_page++;
			}
		}

	}
	catch (...)
	{
		
	}
	
	return;
}

#include "StdAfx.h"
#include ".\watch_dog.h"
#include "..\common\StringCodeConversion.h"
#include "..\file\log.h"
#include "..\common\ping.h"

watch_dog::watch_dog(void)
{
	feitian_dog=NULL;
	memset(m_dog_server_ip,0x0,sizeof(m_dog_server_ip));

	feitian_dog = new CDogClient();
	if (NULL==feitian_dog)
	{
		feitian_dog = new CDogClient();
	}
}

watch_dog::~watch_dog(void)
{
	if (feitian_dog)
	{
		delete feitian_dog;
		feitian_dog = NULL;
	}
}

bool watch_dog::set_parameter(const TCHAR* server_ip, int server_port,const TCHAR* module_number,int link_error_number,long timeout,long warn_time)
{
	try
	{
		if (feitian_dog)
		{
			char temp_server_ip[32];
			char temp_module_number[16];
			string_conversion str_conv;
			bool result=false;

			memset(temp_server_ip,0x0,sizeof(temp_server_ip));
			memset(temp_module_number,0x0,sizeof(temp_module_number));

			//unicode转化成多字节字符串
			result = str_conv.widechar_to_multibyte(server_ip,temp_server_ip,sizeof(temp_server_ip));
			if (!result)
			{
				return false;
			}
			//记录狗服务的IP地址
			strcpy(m_dog_server_ip,temp_server_ip);

			//unicode转化成多字节字符串
			result = str_conv.widechar_to_multibyte(module_number,temp_module_number,sizeof(temp_module_number));
			if (!result)
			{
				return false;
			}

			feitian_dog->SetParam(temp_server_ip,server_port,temp_module_number,link_error_number,timeout,warn_time);

			return true;
		}
		return false;
	}
	catch (...)
	{
		
	}

	return false;
}

bool watch_dog::connect_server(void)
{
	try
	{
		bool result=false;
		long roundtrip_time=0;

		if (feitian_dog)
		{
			result = feitian_dog->ConnectServer();
		}

		return result;
	}
	catch (...)
	{
		
	}
	return false;
}

int watch_dog::login_check(long & valid_time,const TCHAR * module_number)
{
	try
	{
		int ret=-1;
		if (feitian_dog)
		{
			char temp_module_number[16];
			string_conversion str_conv;
			bool result=false;

			memset(temp_module_number,0x0,sizeof(temp_module_number));
			//unicode转化成多字节字符串
			result = str_conv.widechar_to_multibyte(module_number,temp_module_number,sizeof(temp_module_number));
			if (!result)
			{
				return false;
			}

			ret = feitian_dog->LoginCheck(valid_time,temp_module_number);
		}
		return ret;
	}
	catch (...)
	{
		
	}

	return false;
}

bool watch_dog::get_data(int file_index, int & data_length , char*  buffer)
{
	try
	{
		int ret=-1;
		if (feitian_dog)
		{
			ret = feitian_dog->GetData(file_index,data_length,buffer);
			if (0==ret)
			{
				//成功
				return true;
			}
		}
		return false;
	}
	catch (...)
	{
		
	}
	return false;
}

int watch_dog::common_check(void)
{
	try
	{
		int result=-1;
		TCHAR log[256];

		if (feitian_dog)
		{
			result = feitian_dog->CommonCheck();
		}

		//记下返回值
		memset(log,0x0,sizeof(log));
		swprintf(log,L"软件定期输出结果D%d",result);
		WriteLog(__FL__, log);

		return result;
	}
	catch (...)
	{

	}
	return -1;
}

bool watch_dog::logout(void)
{
	try
	{
		if (feitian_dog)
		{
			feitian_dog->Logout();
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool watch_dog::add_song_number(long & song_number)
{
	try
	{
		int result=-1;

		if (feitian_dog)
		{
			result = feitian_dog->IncSongs(song_number);
		}
		if (0==result)
		{
			//成功
			return true;
		}
		return false;
	}
	catch (...)
	{

	}
	return false;
}

bool watch_dog::verify_server_time(void)
{
	try
	{
		if (feitian_dog)
		{
			feitian_dog->VerifyTime();
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool watch_dog::get_song_number(long & song_total_number)
{
	try
	{
		int result=-1;

		if (feitian_dog)
		{
			result = feitian_dog->GetSongs(song_total_number);
		}
		if (0==result)
		{
			//成功
			return true;
		}
		return false;
	}
	catch (...)
	{

	}
	return false;
}

bool watch_dog::encode(TCHAR* input_data, TCHAR*  output_data)
{
	try
	{
		int ret=-1;

		if (feitian_dog)
		{
			char *temp_input_data=NULL;
			char *temp_output_data=NULL;
			string_conversion str_conv;
			int byte_size=0;
			bool result=false;

			//得到做字节占用的字节数
			byte_size = str_conv.get_byte_size_of_multibyte(input_data);
			if (byte_size<=0)
			{
				return false;
			}
			temp_input_data = new char[byte_size];
			if (NULL==temp_input_data)
			{
				return false;
			}
			//unicode转化成多字节字符串
			result = str_conv.widechar_to_multibyte(input_data,temp_input_data,byte_size);
			if (!result)
			{
				delete []temp_input_data;
				temp_input_data = NULL;
				return false;
			}

			//得到做字节占用的字节数
			byte_size = str_conv.get_byte_size_of_multibyte(output_data);
			if (byte_size<=0)
			{
				return false;
			}
			temp_output_data = new char[byte_size];
			if (NULL==temp_output_data)
			{
				return false;
			}
			//unicode转化成多字节字符串
			result = str_conv.widechar_to_multibyte(output_data,temp_output_data,byte_size);
			if (!result)
			{
				delete []temp_output_data;
				temp_output_data = NULL;
				return false;
			}

			ret = feitian_dog->Encode(temp_input_data,temp_output_data);
			//释放空间
			if (temp_input_data)
			{
				delete temp_input_data;
				temp_input_data=NULL;
			}
			if (temp_output_data)
			{
				delete temp_output_data;
				temp_output_data=NULL;
			}
		}
		if (0==ret)
		{
			//成功
			return true;
		}
		return false;
	}
	catch (...)
	{

	}
	return false;
}

bool watch_dog::decode(TCHAR* input_data, TCHAR*  output_data)
{
	try
	{
		int ret=-1;

		if (feitian_dog)
		{
			char *temp_input_data=NULL;
			char *temp_output_data=NULL;
			string_conversion str_conv;
			int byte_size=0;
			bool result=false;

			//得到做字节占用的字节数
			byte_size = str_conv.get_byte_size_of_multibyte(input_data);
			if (byte_size<=0)
			{
				return false;
			}
			temp_input_data = new char[byte_size];
			if (NULL==temp_input_data)
			{
				return false;
			}
			//unicode转化成多字节字符串
			result = str_conv.widechar_to_multibyte(input_data,temp_input_data,byte_size);
			if (!result)
			{
				delete []temp_input_data;
				temp_input_data = NULL;
				return false;
			}

			//得到做字节占用的字节数
			byte_size = str_conv.get_byte_size_of_multibyte(output_data);
			if (byte_size<=0)
			{
				return false;
			}
			temp_output_data = new char[byte_size];
			if (NULL==temp_output_data)
			{
				return false;
			}
			//unicode转化成多字节字符串
			result = str_conv.widechar_to_multibyte(output_data,temp_output_data,byte_size);
			if (!result)
			{
				delete []temp_output_data;
				temp_output_data = NULL;
				return false;
			}

			ret = feitian_dog->Decode(temp_input_data,temp_output_data);
			//释放空间
			if (temp_input_data)
			{
				delete temp_input_data;
				temp_input_data=NULL;
			}
			if (temp_output_data)
			{
				delete temp_output_data;
				temp_output_data=NULL;
			}
		}
		if (0==ret)
		{
			//成功
			return true;
		}
		return false;
	}
	catch (...)
	{

	}
	return false;
}

bool watch_dog::active_clock_time(TCHAR*  active_code, long & active_time)
{
	try
	{
		int ret=-1;

		if (feitian_dog)
		{
			char *temp_active_code=NULL;
			string_conversion str_conv;
			int byte_size=0;
			bool result=false;

			//得到做字节占用的字节数
			byte_size = str_conv.get_byte_size_of_multibyte(active_code);
			if (byte_size<=0)
			{
				return false;
			}
			temp_active_code = new char[byte_size];
			if (NULL==temp_active_code)
			{
				return false;
			}
			//unicode转化成多字节字符串
			result = str_conv.widechar_to_multibyte(active_code,temp_active_code,byte_size);
			if (!result)
			{
				delete []temp_active_code;
				temp_active_code = NULL;
				return false;
			}

			ret = feitian_dog->ActiveClockTime(temp_active_code,active_time);
			//释放空间
			if (temp_active_code)
			{
				delete temp_active_code;
				temp_active_code=NULL;
			}
		}
		if (0==ret)
		{
			//成功
			return true;
		}
		return false;
	}
	catch (...)
	{

	}
	return false;
}
#include "StdAfx.h"
#include ".\image_animation_show.h"
#include "..\common\CalendarConvert.h"
#include "..\file\config_file.h"
#include "..\folder_name.h"

#include <shlwapi.h>
#include <string>
using namespace std;

//ȫ�ֵĽڼ��պ��ļ���Ӧ��
//����
#define GREGORIAN_HOLIDAY_COUNT 14
std::wstring g_gregorian_holiday_file_table[GREGORIAN_HOLIDAY_COUNT][2] = {
	{L"01-01",L"����.swf"},
	{L"02-14",L"���˽�.swf"},
	{L"03-08",L"��Ů��.swf"},
	{L"03-12",L"ֲ����.swf"},
	{L"04-01",L"���˽�.swf"},
	{L"05-01",L"�Ͷ���.swf"},
	{L"05-04",L"�й������.swf"},
	{L"06-01",L"��ͯ��.swf"},
	{L"07-01",L"����������.swf"},
	{L"08-01",L"������.swf"},
	{L"09-10",L"��ʦ��.swf"},
	{L"10-01",L"�����.swf"},
	{L"10-31",L"��ʥ��.swf"},
	{L"12-25",L"ʥ����.swf"},
};

//����
#define LUNAR_HOLIDAY_COUNT 5
std::wstring g_lunar_holiday_file_table[LUNAR_HOLIDAY_COUNT][2] = {
	{L"01-15",L"Ԫ����.swf"},
	{L"05-05",L"�����.swf"},
	{L"07-07",L"�й����˽�.swf"},
	{L"08-15",L"�����.swf"},
	{L"09-09",L"������.swf"},
};

image_animation_show::image_animation_show(void)
{
	try
	{
		memset(m_image_path,0x0,sizeof(m_image_path));
		memset(m_default_image_path,0x0,sizeof(m_default_image_path));

		GetModuleFileName(NULL,m_image_path,sizeof(m_image_path));
		_tcsrchr(m_image_path,'\\')[1] = '\0';

		//�õ�����ҳ��·��
		_tcscat(m_image_path,g_folder_name[5]);
	}
	catch (...)
	{
		
	}
}

image_animation_show::~image_animation_show(void)
{
}

void image_animation_show::set_default_image_path(TCHAR *path)
{
	try
	{
		memset(m_default_image_path,0x0,sizeof(m_default_image_path));
		_tcscpy(m_default_image_path,path);
	}
	catch (...)
	{
		
	}
}

bool image_animation_show::get_show_image_animation(TCHAR *path)
{
	try
	{
		CCalendarConvert calendar_convert;
		SYSTEMTIME gregorian_time;
		SYSTEMTIME lunar_time;
		TCHAR month_day[32];
		TCHAR holiday_day[32];
		bool result=false;
		bool ret=false;

		if (NULL==path)
		{
			return false;
		}
		memset(month_day,0x0,sizeof(month_day));

		//�õ�������ϵͳʱ��
		 GetLocalTime(&gregorian_time);
		//�鿴�Ƿ��Ǹ��׽� ���µĵ�����������
		if ((6==gregorian_time.wMonth)&&(0==gregorian_time.wDayOfWeek)&&(gregorian_time.wDay>=15)&&(gregorian_time.wDay<=21))
		{
			memset(path,0x0,sizeof(path));
			swprintf(path,L"%s\\���׽�.swf",m_image_path);
			if (!PathFileExists(path))
			{
				//�����ڣ�ʹ��Ĭ�ϵ� 2010-05-10 modify
				memset(path,0x0,sizeof(path));
				_tcscpy(path,m_default_image_path);
			}
			return true;
		}
		//�鿴�Ƿ���ĸ�׽� ���µĵڶ���������
		if ((5==gregorian_time.wMonth)&&(0==gregorian_time.wDayOfWeek)&&(gregorian_time.wDay>=8)&&(gregorian_time.wDay<=14))
		{
			memset(path,0x0,sizeof(path));
			swprintf(path,L"%s\\ĸ�׽�.swf",m_image_path);
			if (!PathFileExists(path))
			{
				//�����ڣ�ʹ��Ĭ�ϵ�  2010-05-10 modify
				memset(path,0x0,sizeof(path));
				_tcscpy(path,m_default_image_path);
			}
			return true;
		}
		//�õ�����
		swprintf(month_day,L"%02d-%02d",gregorian_time.wMonth,gregorian_time.wDay);
		//�鿴�Ƿ��й����ڼ���
		for (int i=0;i<GREGORIAN_HOLIDAY_COUNT;i++)
		{
			memset(holiday_day,0x0,sizeof(holiday_day));
			_tcscpy(holiday_day,g_gregorian_holiday_file_table[i][0].c_str());
			if (0==_tcscmp(holiday_day,month_day))
			{
				memset(path,0x0,sizeof(path));
				swprintf(path,L"%s\\%s",m_image_path,g_gregorian_holiday_file_table[i][1].c_str());
				if (PathFileExists(path))
				{
					return true;
				}
				else
				{
					memset(path,0x0,sizeof(path));
					_tcscpy(path,m_default_image_path);
					return true;
				}
			}
		}
		//�õ�ũ������
		result = calendar_convert.Gregorian2Lunar(&gregorian_time,&lunar_time,&ret);
		if (result)
		{
			//�õ�����
			memset(month_day,0x0,sizeof(month_day));
			swprintf(month_day,L"%02d-%02d",lunar_time.wMonth,lunar_time.wDay);
			//�鿴�Ƿ���ũ���ڼ���
			for (int i=0;i<LUNAR_HOLIDAY_COUNT;i++)
			{
				memset(holiday_day,0x0,sizeof(holiday_day));
				_tcscpy(holiday_day,g_lunar_holiday_file_table[i][0].c_str());
				if (0==_tcscmp(holiday_day,month_day))
				{
					memset(path,0x0,sizeof(path));
					swprintf(path,L"%s\\%s",m_image_path,g_lunar_holiday_file_table[i][1].c_str());
					if (PathFileExists(path))
					{
						return true;
					}
					else
					{
						memset(path,0x0,sizeof(path));
						_tcscpy(path,m_default_image_path);
						return true;
					}
				}
			}
		}
		//ʹ�ù�������ҳ
		memset(path,0x0,sizeof(path));
		_tcscpy(path,m_default_image_path);
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}
#include "StdAfx.h"
#include ".\show_service_picture.h"

#include <io.h> 

show_service_picture::show_service_picture(void)
{
	for (int i=0;i<MAX_SERVICE_PICTURE_COUNT;i++)
	{
		memset(m_picture_path[i],0x0,sizeof(m_picture_path[i]));
	}
    m_total_picture_count=0;     //总的图片数
	m_cur_show_picture_number=1; //当前正在显示的图片编号
}

show_service_picture::~show_service_picture(void)
{
}

bool show_service_picture::initiate(TCHAR *path)
{
	try
	{
		TCHAR file_path[256];
		BOOL result=false;
		intptr_t search_handle = -1;
		int char_pos=0;
		struct _wfinddata_t findData;

		memset(&findData, 0, sizeof(findData));
		for (int i=0;i<MAX_SERVICE_PICTURE_COUNT;i++)
		{
			memset(m_picture_path[i],0x0,sizeof(m_picture_path[i]));
		}
		m_total_picture_count=0;     //总的图片数
		m_cur_show_picture_number=1; //当前正在显示的图片编号

		swprintf(file_path,L"%s\\*.*",path);
		search_handle = _wfindfirst(file_path, &findData);
		if (-1!=search_handle)
		{
			do
			{
				const TCHAR* p = _tcsrchr(findData.name, '.');
				if(p != NULL && p != 0)
				{
					if ((_tcsicmp(p, L".jpg") == 0)	|| (_tcsicmp(p, L".bmp") == 0)||((_tcsicmp(p, L".png") == 0)))	
					{

						swprintf(m_picture_path[m_total_picture_count], L"%s\\%s",path,findData.name);
						m_total_picture_count++;

						//如果超过最大数就不继续查找文件
						if(m_total_picture_count >= MAX_SERVICE_PICTURE_COUNT)
							break;					
					}
					else if ((_tcsicmp(p, L".swf") == 0))//含有.swf文件直接跳出循环
					{
						swprintf(m_picture_path[0], L"%s\\%s",path,findData.name);
						m_total_picture_count = 1;

						break;	
					}
				}
				memset(&findData, 0, sizeof(findData));
			}while (0==_wfindnext(search_handle, &findData));
		}

		//关闭文件查找
		_findclose(search_handle);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool show_service_picture::get_show_picture(SERVICE_PICTRUE_PAGE_OPERATE page_operate,std::wstring& picture_list_xml)
{
	try
	{
		if(m_total_picture_count<=0)
		{
			return false;
		} 
		TCHAR pictue_temp[256];

		picture_list_xml += L"<pic_list>";
		//组织图片路径
		for (int i =0; i < m_total_picture_count; i++)
		{
			memset(pictue_temp,0x0,sizeof(pictue_temp));
			swprintf(pictue_temp,L"<item>%s</item>",m_picture_path[i]);	
			picture_list_xml += pictue_temp;
		}

		picture_list_xml += L"</pic_list>";
	 
		return true;
	}
	catch (...)
	{
		
	} 

	return false;
}

bool show_service_picture::get_show_picture(SERVICE_PICTRUE_PAGE_OPERATE page_operate,TCHAR *path)
{
	try
	{
		if(m_total_picture_count<=0)
		{
			return false;
		}
		std::wstring picture_xml;
		TCHAR pictue_temp[256];

		picture_xml += L"<pic_list>";
		//组织图片路径
		for (int i =0; i < m_total_picture_count; i++)
		{
			memset(pictue_temp,0x0,sizeof(pictue_temp));
			swprintf(pictue_temp,L"<item>%s</item>",m_picture_path[i]);	
			picture_xml += pictue_temp;
		}

		picture_xml += L"</pic_list>";
		_tcscpy(path,picture_xml.c_str());

		return true;

		switch(page_operate)
		{
		case SERVICE_PICTRUE_PRE_PAGE:  //上一页
			{
				m_cur_show_picture_number--;
				if (m_cur_show_picture_number<1)
				{
					m_cur_show_picture_number = m_total_picture_count;
				}
			}
			break;
		case SERVICE_PICTRUE_NEXT_PAGE:  //下一页
			{
				m_cur_show_picture_number++;
				if (m_cur_show_picture_number>m_total_picture_count)
				{
					m_cur_show_picture_number = 1;
				}
			}
			break;
		case SERVICE_PICTRUE_CUR_PAGE: //当前页
		default:
			break;
		}
		_tcscpy(path,m_picture_path[m_cur_show_picture_number-1]);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool show_service_picture::get_page_info(int &total_page_count, int &show_page_number)
{
	total_page_count = m_total_picture_count;
	show_page_number = m_cur_show_picture_number;

	return true;
}

void show_service_picture::set_show_page_number(int page_number)
{
	m_cur_show_picture_number = page_number;
	if (m_cur_show_picture_number>m_total_picture_count)
	{
		m_cur_show_picture_number = m_total_picture_count;
	}
	if (m_cur_show_picture_number<1)
	{
		m_cur_show_picture_number = 1;
	}
}
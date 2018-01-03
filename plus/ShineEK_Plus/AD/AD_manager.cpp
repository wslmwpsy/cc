#include "StdAfx.h"
#include ".\ad_manager.h"
#include "..\folder_name.h"

AD_manager::AD_manager(void)
{
}

AD_manager::~AD_manager(void)
{
}

void AD_manager::init_picture_ad(const TCHAR *folder_name)
{
	try
	{
		CFileFind picture_ad_find;
		TCHAR ad_path[256];
		TCHAR work_path[256];
		BOOL result=FALSE;
		CString picture_path;

		if (NULL==folder_name)
		{
			return;
		}

		memset(ad_path,0x0,sizeof(ad_path));
		memset(work_path,0x0,sizeof(work_path));
		for (int i=0;i<PICTURE_AD_MAX_COUNT;i++)
		{
			memset(m_picture_ad_path[i],0x0,sizeof(m_picture_ad_path[i]));
		}
		m_picture_ad_total_count=0; 
		m_picture_ad_play_number=0; 

		//得到当前工作路径
		GetModuleFileName(NULL,work_path,sizeof(work_path));
		_tcsrchr(work_path,'\\')[0]='\0';
		//得到广告路径
		swprintf(ad_path,L"%s\\%s\\*.jpg",work_path,folder_name);
		//查找文件
		result = picture_ad_find.FindFile(ad_path);
		while (result)
		{
			result = picture_ad_find.FindNextFile();
			//得到广告路径
			picture_path = picture_ad_find.GetFilePath();
			_tcscpy(m_picture_ad_path[m_picture_ad_total_count],picture_path.GetBuffer(0));
			//图片总数加一
			m_picture_ad_total_count++;
			if (m_picture_ad_total_count>=PICTURE_AD_MAX_COUNT)
			{
				//不能超过最大数
				break;
			}
		}
		//查找关闭
		picture_ad_find.Close();
	}
	catch (...)
	{
		
	}
	return;
}

bool AD_manager::get_next_play_ad_picture(TCHAR *path)
{
	try
	{
		if ((NULL==path)||(0==m_picture_ad_total_count))
		{
			return false;
		}
		//防止越界
		if (m_picture_ad_play_number<0)
		{
			m_picture_ad_play_number = 0;
		}
		if (m_picture_ad_play_number>=m_picture_ad_total_count)
		{
			m_picture_ad_play_number = m_picture_ad_total_count-1;
		}
		//得到要播放的广告图片路径
		_tcscpy(path,m_picture_ad_path[m_picture_ad_play_number]);
		//得到下一个要播放的序号
		m_picture_ad_play_number++;
		m_picture_ad_play_number %= m_picture_ad_total_count;

		return true;
	}
	catch (...)
	{
	}
	return false;
}
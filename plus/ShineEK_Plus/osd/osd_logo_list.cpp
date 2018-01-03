#include "StdAfx.h"
#include ".\osd_logo_list.h"

osd_logo_list::osd_logo_list(void)
{
	initiate();
}

osd_logo_list::~osd_logo_list(void)
{
}

void osd_logo_list::initiate(void)
{
	memset(m_logo_directory,0x0,sizeof(m_logo_directory));   //logo�ļ��е�·��
	for(int i=0;i<100;i++)
	{
		m_logo_path[i][0] = '\0';  //����logo��·�������100��
	}
	m_logo_count = 0;           //logo������
	m_cur_logo_number=-1;      //��ǰ���ŵ�logo���
}

bool osd_logo_list::set_logo_path(TCHAR *logo_directory)
{
	try
	{
		CFileFind file_find;
		TCHAR path[256];
		BOOL result=false;
		CString logo_path;

		if(NULL==logo_directory)
		{
			return false;
		}
		//��ʼ��
		initiate();
		//�����logo�ļ���·��
		_tcscpy(m_logo_directory,logo_directory);
		//ͨ�����ҵķ�ʽ��¼���е�logo�ļ�·��������¼��logo����
		memset(path,0x0,sizeof(path));

		swprintf(path,L"%s\\*.*",logo_directory);
		result = file_find.FindFile(path);
		while (result)
		{
            result = file_find.FindNextFile();
			if (file_find.IsDots() || file_find.IsDirectory() || file_find.IsSystem() || file_find.IsHidden() || file_find.IsCompressed())
			{
				continue;
			}
			//��¼��·��
			logo_path = file_find.GetFilePath();
			_tcscpy(m_logo_path[m_logo_count],logo_path.GetBuffer(0));
			//������һ
			m_logo_count++;

			if (m_logo_count>=KTV_LOGO_MAX_COUNT)
			{
				//��ֹԽ��
				break;
			}
		}
		//�رղ���
		file_find.Close();
		//2013-12-28 add zlg
		if(m_logo_count<=0)
			return false;

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

int osd_logo_list::get_cur_logo_index()
{
	m_cur_logo_number++;
	m_cur_logo_number %= m_logo_count;
	return m_cur_logo_number;
}

bool osd_logo_list::get_logo_file_path(TCHAR *path)
{
	try
	{
		if (NULL==path)
		{
			return false;
		}
		_tcscpy(path,m_logo_path[m_cur_logo_number]);

		return true;
	}
	catch (...)
	{

	}
	return false;
}
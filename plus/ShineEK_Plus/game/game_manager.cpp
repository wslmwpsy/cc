#include "StdAfx.h"
#include ".\game_manager.h"
#include "..\parserxml\ParserXml.h"

game_manager::game_manager(void)
{
}

game_manager::~game_manager(void)
{
}

void game_manager::search_game(TCHAR *path)
{
	try
	{
		CFileFind game_file_find;
		CParserXml parse_xml_class;
		TCHAR find_path[256];
		CString song_path;
		CString song_name;
		BOOL result=FALSE;

		if (NULL==path)
		{
			return;
		}
		memset(find_path,0x0,sizeof(find_path));
		m_game_total_count=0;
		for(int i=0;i<SHOW_GAME_MAX_COUNT;i++)
		{
			memset(m_game_info[i].name,0x0,sizeof(m_game_info[i].name));
			memset(m_game_info[i].path,0x0,sizeof(m_game_info[i].path));
			memset(m_game_info[i].song_number,0x0,sizeof(m_game_info[i].song_number));
		}

		//����·��
		swprintf(find_path,L"%s\\*.swf",path);
		result = game_file_find.FindFile(find_path);
		while(result)
		{
			result = game_file_find.FindNextFile();

			if (game_file_find.IsSystem() || game_file_find.IsDots() || game_file_find.IsDirectory())
			{
				continue;
			}
			if (game_file_find.IsCompressed() || game_file_find.IsHidden() || game_file_find.IsTemporary())
			{
				continue;
			}

			//�õ��ļ���
			song_name = game_file_find.GetFileTitle();
			//�����ļ���
			_tcscpy(m_game_info[m_game_total_count].name,song_name.GetBuffer(0));
			//�õ��ļ�·��
			song_path = game_file_find.GetFilePath();
			//�����ļ�·��
			_tcscpy(m_game_info[m_game_total_count].path,song_path.GetBuffer(0));
			//���������Ӽ�
			m_game_total_count++;
			//�������������ˣ���ֹͣ����
			if (m_game_total_count>=SHOW_GAME_MAX_COUNT)
			{
				break;
			}
		}
		//�ر��ļ�����
		game_file_find.Close();

		//�޸�flash����ʾ����
		result = parse_xml_class.modify_local_game_name(m_game_info);

		return;
	}
	catch (...)
	{
	}
	return;
}

bool game_manager::get_select_game_path(TCHAR *path,int select_number)
{
	try
	{
		if (NULL==path)
		{
			return false;
		}
		if ((select_number<0)||(select_number>=m_game_total_count))
		{
			return false;
		}

		_tcscpy(path,m_game_info[select_number].path);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}
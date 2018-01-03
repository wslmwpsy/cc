#include "stdafx.h"
#include ".\select_song_manager.h"
#include "..\common\string_function.h"
#include "..\file\config_file.h"
#include "..\message.h"
#include "..\flash\PageData.h"
#include "..\star\decrypt_singer_picture.h"
#include "..\folder_name.h"
#include <algorithm>
using namespace std;

extern std::wstring g_all_language[];
extern FLASH_USE_LANGUAGE g_flash_use_language; //flashʹ�õ�����
int random_ (int i) { return std::rand()%i;}

select_song_manager::select_song_manager(void)
{
}

select_song_manager::~select_song_manager(void)
{
}

void select_song_manager::initialize(HWND m_wnd)
{
	config_file_manager config_file;
	TCHAR install_path[256];

	select_song_count=0;
	sing_song_count=0;
	cur_show_page_number=0;
	total_page_number=0;
	cur_select_test_song_number=-1;
	m_test_next_song=true;
#ifdef SAN_JI_SMART_HOME_SYSTEM
	//һ���Է���ȥ 2013-01-27 modify ZHEN
	m_page_show_row_count = SELECT_SONG_MAX_COUNT;
#else
	m_page_show_row_count = config_file.read_integer(L"flash",L"page_show_row_count",7);
#endif
	m_default_song_row_color = config_file.read_string(L"song_name_color",L"default_color",L"0xFFFFFF");       //Ĭ�ϸ�����ɫ
	m_select_song_row_color = config_file.read_string(L"song_name_color",L"select_song_color",L"0xFF9900");    //ѡ�������ɫ
#ifdef SAN_JI_SMART_HOME_SYSTEM
	//����ʾ��� 2013-01-27 modify ZHEN
	m_no_moive_name_show_lyric = false;
#else
	m_no_moive_name_show_lyric = config_file.read_boolean(L"flash",L"no_movie_name_show_lyric",false);
#endif
	m_parent_handle = m_wnd;
	memset(m_sing_song_number,0x0,sizeof(m_sing_song_number));

	//�õ���װ·��
	memset(install_path,0x0,sizeof(install_path));
	GetModuleFileName(NULL, install_path, sizeof(install_path)/sizeof(TCHAR));
	_tcsrchr(install_path, _T('\\'))[0]='\0';
	//�õ�����ͼƬ·��
	memset(m_singer_picture_path,0x0,sizeof(m_singer_picture_path));
	swprintf(m_singer_picture_path,L"%s\\%s",install_path,g_folder_name[0]);
	//�õ�����ͼƬ·��
	memset(m_song_picture_path,0x0,sizeof(m_song_picture_path));
	swprintf(m_song_picture_path,L"%s\\%s",install_path,g_folder_name[25]);
	//�õ������Ա�ͼƬ·��
	memset(m_singer_sex_picture_path,0x0,sizeof(m_singer_sex_picture_path));
	swprintf(m_singer_sex_picture_path,L"%s\\%s",install_path,g_folder_name[35]);
}

bool select_song_manager::get_play_song(song_info& song)
{
	bool result=false;
	int select_pos = -1;  //���Ÿ����ĵ�ǰλ��
	int down_song_flags=0;  //�жϵ�ǰ��ʾ�ǲ������ظ���

	if (select_song_count<=0)
	{
		return false;
	}

	for (int i=0; i<select_song_count;i++)
	{
		down_song_flags = select_song[i].get_down_update_song();
		if (1 == down_song_flags || 2 == down_song_flags)
		{
			continue;
		}
		else
		{
			//�õ����Բ��ŵ�λ��
			select_pos = i;
			break;
		}
	}

	if (-1 == select_pos)
	{
		return false;
	}

	//song = select_song[0];
	song = select_song[select_pos];

	//���ӵ��ѳ���
	result = add_sing_song(song);
	//�����ǰ��
	for (int i=select_pos;i<select_song_count-1;i++)
	{
		select_song[i] = select_song[i+1];
	}
	//���һ����ʼ��
	select_song[select_song_count-1].initialized_variables();
	//������һ
	select_song_count--;

	//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
	::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);

	return true;
}

bool select_song_manager::get_play_test_song(song_info& song)
{
	try
	{
		if (select_song_count<=0)
		{
			return false;
		}
		if (m_test_next_song)
		{
			//��һ��
			cur_select_test_song_number++;
			if (cur_select_test_song_number>=select_song_count)
			{
				cur_select_test_song_number = 0;
			}
		}
		else
		{
			//��һ��
			cur_select_test_song_number--;
			if (cur_select_test_song_number<0)
			{
				cur_select_test_song_number = select_song_count-1;
			}
		}
		
		song = select_song[cur_select_test_song_number];
		
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool select_song_manager::get_test_song_by_suffix(song_info& song,int song_suffix)
{
	try
	{
		if ((select_song_count<=0) || (song_suffix>=select_song_count))
		{
			return false;
		}
		song = select_song[song_suffix];
		
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool select_song_manager::get_next_song(song_info &song)
{
	if (select_song_count<=0)
	{
		return false;
	}
	song = select_song[0];

	return true;
}

bool select_song_manager::empty()
{
	int down_song_flags = 0;

	for (int i=0; i<select_song_count;i++)
	{
		down_song_flags = select_song[i].get_down_update_song();
		if (1 == down_song_flags || 2==down_song_flags)
		{

		}
		else
		{
			//�õ����Բ��ŵ�λ��
			return false;
		}
	}
	/*if (select_song_count<=0)
	{
	return true;
	}*/

	return true;
}

int select_song_manager::get_select_song_count(int count_type)
{
	int down_song_flags = 0;
	int select_pos = 0;

	if (1 == count_type)
	{
		for (int i=0; i<select_song_count;i++)
		{
			down_song_flags = select_song[i].get_down_update_song();
			if (1 == down_song_flags || 2 == down_song_flags)
			{

			}
			else
			{
				select_pos++;
			}
		}

		return select_pos;
	}
	else
	{
		return select_song_count;
	}
}

int select_song_manager::get_sing_song_count(void)
{
	return sing_song_count;
}

bool select_song_manager::add_select_song(song_info &song,bool priority)
{
	try
	{
		bool result=false;

		if (select_song_count>=SELECT_SONG_MAX_COUNT)
		{
			return false;
		}

		if (priority)
		{
			//���ȣ��ŵ���һ��λ��
			if (select_song_count>0)
			{
				for (int i=select_song_count-1;i>=0;i--)
				{
					select_song[i+1] = select_song[i];
				}
				select_song[0] = song;
				select_song_count++;
			}
			else
			{
				//������ֱ�����
				select_song[0] = song;
				select_song_count++;
			}
		}
		else
		{
			//�ŵ����
			if (select_song_count>0)
			{
				select_song[select_song_count] = song;
				select_song_count++;
			}
			else
			{
				//�����ڣ�ֱ�����
				select_song[select_song_count] = song;
				select_song_count++;
			}
		}

		//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
		::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool select_song_manager::add_sing_song(song_info &song)
{
	try
	{
		TCHAR add_song_number[128];
		bool result=false;

		memset(add_song_number,0x0,sizeof(add_song_number));

		//�õ�����ID
		result = song.get_song_id(add_song_number);
		if (result)
		{
			//������Ϣ����ӵ����ݿ���
			memset(m_sing_song_number,0x0,sizeof(m_sing_song_number));
			_tcscpy(m_sing_song_number,add_song_number);
			::PostMessage(m_parent_handle,DM_ADD_SING_SONG,NULL,(LPARAM)m_sing_song_number);
		}

		if (sing_song_count>=SELECT_SONG_MAX_COUNT)
		{
			//�ѳ���������45֮�󣬰����һ���߳�
			sing_song[sing_song_count-1].initialized_variables();
			//������һ
			sing_song_count--;
		}

		//ȫ�����ƶ�һ��λ��
		for (int i=sing_song_count;i>0;i--)
		{
			sing_song[i].initialized_variables();
			sing_song[i] = sing_song[i-1];
		}
		//�Ѹ��ݳ��ķŵ���һ��λ��
		sing_song[0].initialized_variables();
		sing_song[0] = song;
		sing_song_count++;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool select_song_manager::make_song_list_xml(std::wstring &song_list_xml,enum SHOW_SONG_LIST_TYPE song_type,enum PAGE_OPERATE page_operate,FLASH_SONG_SHOW_MODE song_show_mode,int page_index)
{
	try
	{
		TCHAR song_show_info[512];
		int start_suffix=0;
		int end_suffix=0;
		int page_number=0;
		int song_number=0;
		bool result=false;
		int picture_number=0;

		if ((SHOW_SELECT_SONG==song_type)&&(select_song_count<=0))
		{
			//û����ѡ����
			return true;
		}
		if ((SHOW_SING_SONG==song_type)&&(sing_song_count<=0))
		{
			//û���ѳ�����
			return true;
		}

		//����0-132���漴��
		picture_number = rand() / (RAND_MAX / 133 + 1);

		//����ҳ�������Ը�����ʾ��ʽ����������Ϊ��Щҳ��ֻ���б�ʽ
		switch(page_index)
		{
		case page_title:    //�п�Ƭ��ҳ��
		case page_lyric:
		case page_theme_song:
		case page_new_theme_song:
		case page_top_song:
		case page_new_song:
		case page_opera:
		case page_language: 
		case page_selected:
		case page_singed:
		case page_recording:
		case page_member_song:
		case page_class:
		case page_movie_song:     //Ӱ�ӽ���
		case page_era_song:       //�������
		case page_number_song:    //��ŵ��
		case page_write:        //��д���
			break;
		default:  //û�п�Ƭ��ҳ�棬�޸ĳ��б�ʽ
			{
				if(SONG_SHOW_MODE_CARD==song_show_mode)
				{
					song_show_mode = SONG_SHOW_MODE_LIST;
				}
			}
			break;
		}
		//�ı�ҳ��
		switch(page_operate)
		{
		case FIRST_PAGE_OPERATE: //��һҳ
			{
				cur_show_page_number=1;
				if (SHOW_SELECT_SONG==song_type)
				{
					total_page_number = select_song_count/m_page_show_row_count+(select_song_count%m_page_show_row_count?1:0);
				}
				else if (SHOW_SING_SONG==song_type)
				{
					total_page_number = sing_song_count/m_page_show_row_count+(sing_song_count%m_page_show_row_count?1:0);
				}
				else
				{
					return false;
				}

			}
			break;
		case PRE_PAGE_OPERATE:
			{
				cur_show_page_number--;
				if (cur_show_page_number<=0)
				{
					cur_show_page_number = total_page_number;
				}
			}
			break;
		case NEXT_PAGE_OPERATE:
			{
				cur_show_page_number++;
				if (cur_show_page_number>total_page_number)
				{
					cur_show_page_number=1;
				}
			}
			break;
		case CUR_PAGE_OPERATE:
			{
				//��ʾ��ǰҳ��ҳ�벻��
				if (SHOW_SELECT_SONG==song_type)
				{
					total_page_number = select_song_count/m_page_show_row_count+(select_song_count%m_page_show_row_count?1:0);
				}
				else if (SHOW_SING_SONG==song_type)
				{
					total_page_number = sing_song_count/m_page_show_row_count+(sing_song_count%m_page_show_row_count?1:0);
				}
				else
				{
					return false;
				}
				if (cur_show_page_number>total_page_number)
				{
					cur_show_page_number = total_page_number;
				}
				if (cur_show_page_number<1)
				{
					cur_show_page_number = 1;
				}
			}
			break;
		default:
			return false;
		}

		//��֯xml�ַ���
		if (SHOW_SELECT_SONG==song_type)
		{
			//��ѡ����
			page_number = cur_show_page_number-1;
			if (page_number<=0)
			{
				page_number = total_page_number;
			}
			start_suffix = (page_number-1)*m_page_show_row_count;
			if (start_suffix<0)
			{
				start_suffix = 0;
			}
			end_suffix = page_number*m_page_show_row_count-1;
			if (end_suffix>=select_song_count)
			{
				end_suffix = select_song_count-1;
			}
			//��֯ǰһҳ�ˡ�
			song_list_xml += L"<pre_list>";
			for (int i=start_suffix;i<=end_suffix;i++)
			{
				memset(song_show_info,0x0,sizeof(song_show_info));

				//��һҳ��ʾλ��
				if (cur_show_page_number == 1)
				{
					break;
				}else{
					result = make_song_list_one_xml(select_song[i],i+1,song_show_info,song_show_mode,song_type,picture_number);
				}

				if (result)
				{
					song_list_xml += song_show_info;
					picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
				}
			}

			song_list_xml += L"</pre_list><cur_list>";

			//��֯��ǰҳ
			page_number = cur_show_page_number;
			start_suffix = (page_number-1)*m_page_show_row_count;
			if (start_suffix<0)
			{
				start_suffix = 0;
			}
			end_suffix = page_number*m_page_show_row_count-1;
			if (end_suffix>=select_song_count)
			{
				end_suffix = select_song_count-1;
			}
			for (int i=start_suffix;i<=end_suffix;i++)
			{
				memset(song_show_info,0x0,sizeof(song_show_info));

				result = make_song_list_one_xml(select_song[i],i+1,song_show_info,song_show_mode,song_type,picture_number);
				if (result)
				{
					song_list_xml += song_show_info;
					picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
				}
			}

			song_list_xml += L"</cur_list><next_list>";
			//��һҳ
			page_number = cur_show_page_number+1;
			if (page_number>total_page_number)
			{
				page_number = 1;
			}
			start_suffix = (page_number-1)*m_page_show_row_count;
			if (start_suffix<0)
			{
				start_suffix = 0;
			}
			end_suffix = page_number*m_page_show_row_count-1;
			if (end_suffix>=select_song_count)
			{
				end_suffix = select_song_count-1;
			}
			for (int i=start_suffix;i<=end_suffix;i++)
			{
				memset(song_show_info,0x0,sizeof(song_show_info));

				if (cur_show_page_number == total_page_number)
				{
					break;
				}else{
					result = make_song_list_one_xml(select_song[i],i+1,song_show_info,song_show_mode,song_type,picture_number);
				}
				if (result)
				{
					song_list_xml += song_show_info;
					picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
				}
			}

			song_list_xml += L"</next_list>";
		}
		else if (SHOW_SING_SONG==song_type)
		{
			//�ѳ��ĸ���

			//��֯ǰһҳ�ˡ�
			page_number = cur_show_page_number-1;
			if (page_number<=0)
			{
				page_number = total_page_number;
			}
			start_suffix = (page_number-1)*m_page_show_row_count;
			if (start_suffix<0)
			{
				start_suffix = 0;
			}
			end_suffix = page_number*m_page_show_row_count-1;
			if (end_suffix>=sing_song_count)
			{
				end_suffix = sing_song_count-1;
			}
			song_list_xml += L"<pre_list>";
			//��ʼ���������
			song_number = 1;
			for (int i=start_suffix;i<=end_suffix;i++)
			{
				memset(song_show_info,0x0,sizeof(song_show_info));
				if (cur_show_page_number == 1)
				{
					break;
				}
				result = make_song_list_one_xml(sing_song[i],song_number,song_show_info,song_show_mode,song_type,picture_number);
				if (result)
				{
					song_list_xml += song_show_info;
					//��������ۼ�
					song_number++;
					picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
				}
			}

			//��֯��ǰҳ
			page_number = cur_show_page_number;
			start_suffix = (page_number-1)*m_page_show_row_count;
			if (start_suffix<0)
			{
				start_suffix = 0;
			}
			end_suffix = page_number*m_page_show_row_count-1;
			if (end_suffix>=sing_song_count)
			{
				end_suffix = sing_song_count-1;
			}
			song_list_xml += L"</pre_list><cur_list>";
			//��ʼ���������
			song_number = 1;
			for (int i=start_suffix;i<=end_suffix;i++)
			{
				memset(song_show_info,0x0,sizeof(song_show_info));

				result = make_song_list_one_xml(sing_song[i],song_number,song_show_info,song_show_mode,song_type,picture_number);
				if (result)
				{
					song_list_xml += song_show_info;
					//��������ۼ�
					song_number++;
					picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
				}
			}

			//��һҳ
			page_number = cur_show_page_number+1;
			if (page_number>total_page_number)
			{
				page_number = 1;
			}
			start_suffix = (page_number-1)*m_page_show_row_count;
			if (start_suffix<0)
			{
				start_suffix = 0;
			}
			end_suffix = page_number*m_page_show_row_count-1;
			if (end_suffix>=sing_song_count)
			{
				end_suffix = sing_song_count-1;
			}
			song_list_xml += L"</cur_list><next_list>";
			//��ʼ���������
			song_number = 1;
			for (int i=start_suffix;i<=end_suffix;i++)
			{
				memset(song_show_info,0x0,sizeof(song_show_info));
				if (cur_show_page_number == total_page_number)
				{
					break;
				}
				result = make_song_list_one_xml(sing_song[i],song_number,song_show_info,song_show_mode,song_type,picture_number);
				if (result)
				{
					song_list_xml += song_show_info;
					//��������ۼ�
					song_number++;
					picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
				}
			}
			song_list_xml += L"</next_list>";
		}

		return true;

	}
	catch (...)
	{

	}
	return false;
}

bool select_song_manager::make_song_list_one_xml(song_info &song_information,int song_number,TCHAR *song_show_info,FLASH_SONG_SHOW_MODE song_show_mode,enum SHOW_SONG_LIST_TYPE song_type,int picture_number)
{
	try
	{
		TCHAR language[16];
		TCHAR song_name[256];
		TCHAR singer_name[256];
		TCHAR song_id[128];
		TCHAR song_version[256];
		TCHAR singer_image_path[256];
		TCHAR song_image_path[256];
		TCHAR tmp_string[256];
		TCHAR singer_sex[256];
		TCHAR sex_image_path[256];
		bool result=false;
		int play_number=0;
		int song_sort=0;
		decrypt_picture decrypt_singer_song_picture;
		TCHAR movie_name[256];
		TCHAR *split_symbol=NULL;
		int song_down_number=0;  //��ʾ�Ƿ�������/���¸���
		TCHAR show_down_mark[256];  //��ʾ���صı�ʾ

		if (NULL==song_show_info)
		{
			return false;
		}

		memset(language,0x0,sizeof(language));
		memset(song_name,0x0,sizeof(song_name));
		memset(singer_name,0x0,sizeof(singer_name));
		memset(song_id,0x0,sizeof(song_id));
		memset(song_version,0x0,sizeof(song_version));
		memset(singer_image_path,0x0,sizeof(singer_image_path));
		memset(song_image_path,0x0,sizeof(song_image_path));
		memset(movie_name,0x0,sizeof(movie_name));
		memset(tmp_string,0x0,sizeof(tmp_string));
		memset(singer_sex,0x0,sizeof(singer_sex));
		memset(sex_image_path,0x0,sizeof(sex_image_path));
		memset(show_down_mark,0x0,sizeof(show_down_mark));


		song_information.get_song_language(language);
		song_information.get_song_name(song_name);
		song_down_number = song_information.get_down_update_song();
		if (1 == song_down_number)
		{
			_tcscpy(show_down_mark,g_all_language[123].c_str());
		}
		else if (2 == song_down_number)
		{
			_tcscpy(show_down_mark,g_all_language[124].c_str());
		}
		else
		{
			_tcscpy(show_down_mark,L"");
		}
		/* 2011-07-26 modify ֻ��ʾ��� 
		song_information.get_moive_name(movie_name);
		if (m_no_moive_name_show_lyric&&(0==_tcscmp(movie_name,L"")))
		{
			//��Ӱ�����ǿ���ʾ���
			song_information.get_lyric(movie_name);
			//���������ʾ24������ֹԽ��
			movie_name[24] = '\0';
		}*/
		if (m_no_moive_name_show_lyric)
		{
			//��Ӱ�����ǿ���ʾ���
			song_information.get_lyric(tmp_string);
			//���������ʾ12������ֹԽ��
			if (tmp_string[0]<0xff)
			{
				//Ӣ��
				tmp_string[24] = '\0';
				split_symbol = _tcsrchr(tmp_string,' ');
				if (split_symbol)
				{
					split_symbol[0] = '\0';
				}
			}
			else
			{
				//������
				tmp_string[13] = '\0';
			}
			if (_tcslen(tmp_string)>2)
			{
				swprintf(movie_name,L"                                  %s...",tmp_string);
			}
		}
		int nVersion = 0;
		song_information.get_singer_name(singer_name);
		song_information.get_song_id(song_id);
		song_information.get_song_version(song_version,nVersion);
		
		song_sort = song_information.get_song_sort();

		int first_song=0; //song_sort&0x01;    //�׳�
		int hot_song=0;   //song_sort&0x02;    //����
		int maiba_pk=0;	  //song_sort&0x04;   //���pk
		int video_hd = 0;

		first_song = song_sort&0x01;
		hot_song = (song_sort>>1)&0x01;
		maiba_pk = (song_sort>>2)&0x01;

		if (NULL != _tcsstr(song_name,L"����"))
		{
			video_hd = 1;
		}

		//�ж��Ƿ�Ϊ��������ƽ̨
		int music_enjoy = song_information.get_music_enjoy();

		//ͨ�������Ա�õ�����ͼƬ
#ifndef SAN_JI_SMART_HOME_SYSTEM 
		song_information.get_singer_sex(singer_sex);
		if (0==_tcscmp(singer_sex,L"1"))
		{
			swprintf(sex_image_path,L"%s\\image0.png",m_singer_sex_picture_path);
		}
		else if (0==_tcscmp(singer_sex,L"2"))
		{
			swprintf(sex_image_path,L"%s\\image1.png",m_singer_sex_picture_path);
		}
		else if (0==_tcscmp(singer_sex,L"6"))
		{
			swprintf(sex_image_path,L"%s\\image2.png",m_singer_sex_picture_path);
		}
		else if (0==_tcscmp(singer_sex,L"7"))
		{
			swprintf(sex_image_path,L"%s\\image3.png",m_singer_sex_picture_path);
		}
		else if ((0==_tcscmp(singer_sex,L"4"))||(0==_tcscmp(singer_sex,L"5")))
		{
			swprintf(sex_image_path,L"%s\\image4.png",m_singer_sex_picture_path);
		}
		else if (0==_tcscmp(singer_sex,L"3"))
		{
			swprintf(sex_image_path,L"%s\\image5.png",m_singer_sex_picture_path);
		}
		else  //Ĭ��
		{
			swprintf(sex_image_path,L"%s\\image6.png",m_singer_sex_picture_path);
		}
#endif
		//����ǿ�Ƭ��ʽ����Ҫ���ܸ��Ǻ͸���ͼƬ
		if (SONG_SHOW_MODE_CARD==song_show_mode)
		{
			//���ܸ���ͼƬ
			result = decrypt_singer_song_picture.decrypt_singer_picture(singer_name,L"δ֪",picture_number,m_singer_picture_path,singer_image_path);
			if (!result || !PathFileExists(singer_image_path))
			{
				//����Ĭ��ͼƬ
				memset(singer_image_path,0x0,sizeof(singer_image_path));
				swprintf(singer_image_path,L"%s\\default.jpg",m_singer_picture_path);
			}
			picture_number++;
			//���ܸ���ͼƬ
			result = decrypt_singer_song_picture.decrypt_song_picture(song_id,picture_number,m_song_picture_path,song_image_path);
			if (!result || !PathFileExists(song_image_path))
			{
				//����Ĭ��ͼƬ
				memset(song_image_path,0x0,sizeof(song_image_path));
				swprintf(song_image_path,L"%s\\default.jpg",m_song_picture_path);
			}
		}
		
		//�õ�����˳��
		result = query_select_song_by_id(song_id,play_number);
		if (result&&(SHOW_SING_SONG==song_type)&&(0!=_tcscmp(song_name,L"")))
		{
			//�Ѿ���ѡ�У�ֻ���ѳ�����
			if (SONG_SHOW_MODE_LIST==song_show_mode)
			{
				//�б�ʽ
				swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s%d]\" subtitle_txt=\"%s\" singer_txt=\"%s\" color=\"%s\" image_path=\"%s\" song_sort=\"%d\" sex_image=\"%s\" music_enjoy=\"%d\" />",     \
					language,song_version,song_name,g_all_language[4].c_str(),play_number,movie_name,singer_name,m_select_song_row_color.c_str(),singer_image_path,song_sort,sex_image_path, music_enjoy);
			}
			else
			{
				//��Ƭ��ʽ
				swprintf(song_show_info,L"<item lang_txt=\"%s\" song_version=\"%s\" song_number=\"%d\" song_txt=\"%s[%s%d]\" singer_txt=\"%s\" color=\"%s\" singer_image_path=\"%s\" song_image_path=\"%s\" music_enjoy=\"%d\" />",    \
					language,song_version,song_number,song_name,g_all_language[4].c_str(),play_number,singer_name,m_select_song_row_color.c_str(),singer_image_path,song_image_path, music_enjoy);
			}
		}
		else if (0!=_tcscmp(song_name,L""))
		{
			if (SONG_SHOW_MODE_LIST==song_show_mode)
			{
				//�б�ʽ
				if (0 == _tcscmp(show_down_mark,L""))
				{
					swprintf(song_show_info,L"<item id=\"%s\" lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s\" subtitle_txt=\"%s\" singer_txt=\"%s\" color=\"%s\" image_path=\"%s\" song_sort=\"%d\" sex_image=\"%s\" video_type=\"%d\"  hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" music_enjoy=\"%d\" />",     \
						song_id,language,song_version,song_name,movie_name,singer_name,m_default_song_row_color.c_str(),singer_image_path,song_sort,sex_image_path,video_hd,hot_song,first_song,maiba_pk,music_enjoy);
				}else{
					swprintf(song_show_info,L"<item id=\"%s\" lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s]\" subtitle_txt=\"%s\" singer_txt=\"%s\" color=\"%s\" image_path=\"%s\" song_sort=\"%d\" sex_image=\"%s\" video_type=\"%d\"  hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" music_enjoy=\"%d\" />",     \
						song_id,language,song_version,song_name,show_down_mark,movie_name,singer_name,m_default_song_row_color.c_str(),singer_image_path,song_sort,sex_image_path,video_hd,hot_song,first_song,maiba_pk,music_enjoy);					
				}			
			}
			else
			{
				//��Ƭ��ʽ
				swprintf(song_show_info,L"<item id=\"%s\" lang_txt=\"%s\" song_version=\"%s\" song_number=\"%d\" song_txt=\"%s\" singer_txt=\"%s\" color=\"%s\" singer_image_path=\"%s\" song_image_path=\"%s\" video_type=\"%d\"  hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" music_enjoy=\"%d\" />",    \
					song_id,language,song_version,song_number,song_name,singer_name,m_default_song_row_color.c_str(),singer_image_path,song_image_path,video_hd,hot_song,first_song,maiba_pk, music_enjoy);
			}
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool select_song_manager::get_page_row_info(int &row,int &cur_page_number,int &total_page_count,enum SHOW_SONG_LIST_TYPE song_type)
{
	if (SHOW_SELECT_SONG==song_type)
	{
		row = select_song_count;
	}
	else if (SHOW_SING_SONG==song_type)
	{
		row = sing_song_count;
	}
	else
	{
		row = 0;
	}
	total_page_count = total_page_number;
	cur_page_number = cur_show_page_number;
	
	return true;
}

int select_song_manager::delete_select_song(int song_number,bool relative_position)
{
	try
	{
		int arrar_song_number=0;

		if (relative_position)
		{
			//���λ��
			if ((song_number<0)||(song_number>=m_page_show_row_count))
			{
				return -1;
			}
			//�õ�ʵ�������е��±�
			arrar_song_number = (cur_show_page_number-1)*m_page_show_row_count+song_number;
		}
		else
		{
			//����λ��
			arrar_song_number = song_number;
		}

		//�ж��Ƿ�������ֵ
		if (arrar_song_number>=select_song_count)
		{
			return -1;
		}
		for (int i=arrar_song_number;i<select_song_count-1;i++)
		{
			select_song[i] = select_song[i+1];
		}
		select_song[select_song_count-1].initialized_variables();
		//������һ
		select_song_count--;

		//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
		::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);

		return arrar_song_number;
	}
	catch (...)
	{
		
	}
	return false;
}

int select_song_manager::delete_select_song_by_id(TCHAR *song_id)
{
	try
	{
		TCHAR select_song_id[128];
		bool result=false;

		if (NULL==song_id)
		{
			return -1;
		}
		for (int i=0;i<select_song_count;i++)
		{
			memset(select_song_id,0x0,sizeof(select_song_id));

			result = select_song[i].get_song_id(select_song_id);
			if (result && (0==_tcscmp(song_id,select_song_id)))
			{
				//ɾ���ø���������ĸ���ǰ�ƶ�
				for (int j=i;j<select_song_count-1;j++)
				{
					select_song[j].initialized_variables();
					select_song[j] =select_song[j+1];
				}
				select_song[select_song_count-1].initialized_variables();
				//ѡ��ĸ���������һ
				select_song_count--;
				i--;
			}
		}
		//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
		::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);

		return 1;
	}
	catch (...)
	{

	}
	return -1;
}

int select_song_manager::get_select_song_absolute_position(int song_number)
{
	try
	{
		int arrar_song_number=0;

		//���λ��
		if ((song_number<0)||(song_number>=m_page_show_row_count))
		{
			return -1;
		}
		//�õ�ʵ�������е��±�
		arrar_song_number = (cur_show_page_number-1)*m_page_show_row_count+song_number;

		return arrar_song_number;
	}
	catch (...)
	{
		
	}
	return -1;
}

int select_song_manager::priority_select_song(int song_number,bool relative_position)
{
	try
	{
		int array_song_number=0;
		song_info priority_song_info;

		//ת��������ı��
		array_song_number = song_number;

		if (relative_position)
		{
			//���λ��
			if ((song_number<0)||(song_number>=m_page_show_row_count))
			{
				return -1;
			}
			array_song_number = (cur_show_page_number-1)*m_page_show_row_count + song_number;
		}
		else
		{
			//����λ��
			array_song_number = song_number;
		}
		if (0==array_song_number)
		{
			return array_song_number;
		}
		

		//��¼Ҫ���ȵĸ�����Ϣ
		priority_song_info = select_song[array_song_number];
		//ǰ��ĺ���
		for (int i=array_song_number;i>0;i--)
		{
			select_song[i] = select_song[i-1];
		}
		//�����ȵķŵ���һ��λ��
		select_song[0] = priority_song_info;

		//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
		::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);

		//���ȵľ��Ը����ı��
		return array_song_number;

	}
	catch (...)
	{
		
	}
	return false;
}

int select_song_manager::drag_sort_select_song(int nOrigin, int nDestination, bool relative_position)
{
	try
	{
		int array_song_number=0;
		song_info drag_song_info;

		//ת��������ı��
		array_song_number = nOrigin;

		if (relative_position)
		{
			//���λ��
			if ((nOrigin<0)||(nOrigin>=m_page_show_row_count))
			{
				return -1;
			}
			array_song_number = (cur_show_page_number-1)*m_page_show_row_count + nOrigin;
		}
		else
		{
			//����λ��
			array_song_number = nOrigin;
		}
		//��¼Ҫ�϶��ĸ�����Ϣ
		drag_song_info = select_song[array_song_number];
		if (nDestination == array_song_number)
		{
			return array_song_number;
		}
		else if (nDestination < array_song_number)
		{
			//ǰ��ĺ���
			for (int i=array_song_number;i>nDestination;i--)
			{
				select_song[i] = select_song[i-1];
			}
		}
		else if (nDestination > array_song_number)
		{
			//�����ǰ��
			for (int i=array_song_number;i<nDestination;i++)
			{
				select_song[i] = select_song[i+1];
			}
		}
		//���϶��ĸ����ŵ�Ŀ��λ��
		select_song[nDestination] = drag_song_info;

		//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
		::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);

		//���ȵľ��Ը����ı��
		return array_song_number;
	}
	catch (...)
	{
	}
	return false;
}

bool select_song_manager::random_sort_select_song()
{
	try
	{
		int array_song_number=0;
		song_info drag_song_info;

		song_info*   select_song_begin  = select_song;   
		song_info*   select_song_end = select_song + select_song_count;  

		std::srand (unsigned(time(0)));

		// using built-in random generator:
		std::random_shuffle (select_song_begin, select_song_end);

		// using myrandom:
		std::random_shuffle (select_song_begin, select_song_end, random_);

		int i=0;
		for(song_info *p=select_song_begin;p!=select_song_end;p++,i++)   
		{   
			select_song[i] = *p;   
		}   
		//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
		::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);

		//���ȵľ��Ը����ı��
		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool select_song_manager::get_select_song_information(song_info &song_information, int star_suffix,bool relative_position)
{
	try
	{
		int array_song_number=0;
		song_info priority_song_info;

		if (select_song_count <= 0)
		{
			return false;
		}

		if (relative_position)
		{
			//���λ��
			if (star_suffix<0)
			{
				star_suffix = 0;
			}
			else if (star_suffix>=m_page_show_row_count)
			{
				star_suffix = m_page_show_row_count-1;
			}
			array_song_number = (cur_show_page_number-1)*m_page_show_row_count + star_suffix;
		}
		else
		{
			//����λ��
			array_song_number = star_suffix;
		}
		if (array_song_number>=select_song_count)
		{
			return false;
		}
		//�õ�ѡ��ĸ�����Ϣ
		song_information = select_song[array_song_number];

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool select_song_manager::get_sing_song_information(song_info &song_information,int select_suffix,bool relative_position)
{
	try
	{
		int array_song_number=0;
		song_info priority_song_info;

		if (relative_position)
		{
			//���λ��
			if (select_suffix<0)
			{
				select_suffix = 0;
			}
			else if (select_suffix>=m_page_show_row_count)
			{
				select_suffix = m_page_show_row_count-1;
			}
			array_song_number = (cur_show_page_number-1)*m_page_show_row_count + select_suffix;
		}
		else
		{
			//����λ��
			array_song_number = select_suffix;
		}
		
		if (array_song_number>=sing_song_count)
		{
			return false;
		}
		//�õ�ѡ��ĸ�����Ϣ
		song_information = sing_song[array_song_number];

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool select_song_manager::select_song_switch_position(int first_switch_pos,int second_switch_pos,bool change_page_switch)
{
	try
	{
		int first_pos=0;
		int second_pos=0;
		song_info  switch_song;
		
		//�õ���������Ҫ������ʵ��λ��
		if (change_page_switch)
		{
			if ((m_song_insert_position+1)==select_song_count)
			{
				//����ǲ��뵽���һ�����Ͳ�Ҫ��������Ϊ�Ѿ������ˡ�
				return false;
			}
			//�ı���ҳ�Ľ���
			first_pos = m_cur_page_first_position+first_switch_pos-1;
			second_pos = m_cur_page_first_position + second_switch_pos-1;
		}
		else
		{
			//û�иı�ҳ�Ľ���
			first_pos = (cur_show_page_number-1)*m_page_show_row_count+first_switch_pos-1;
			second_pos = (cur_show_page_number-1)*m_page_show_row_count+second_switch_pos-1;
		}
		//��¼����λ��
		m_song_insert_position = second_pos;
		//���㵱ǰ��ʾ��ҳ��
		cur_show_page_number = m_song_insert_position/m_page_show_row_count;
		cur_show_page_number++;
		
		if ((first_pos<0)||(second_pos<0)||(first_pos>=select_song_count)||(second_pos>=select_song_count))
		{
			return false;
		}

		if (first_pos<second_pos)
		{
			//�����ƶ��������������ƶ�
			switch_song = select_song[first_pos];
			for (int i=first_pos;i<second_pos;i++)
			{
				select_song[i]=select_song[i+1];
			}
			select_song[second_pos] = switch_song;
		}
		else
		{
			//�����ƶ��������������ƶ�
			switch_song = select_song[first_pos];
			for (int j=first_pos;j>second_pos;j--)
			{
				select_song[j]=select_song[j-1];
			}
			select_song[second_pos]=switch_song;
		}

		//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
		::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}
bool select_song_manager::query_select_song_by_id_ex(TCHAR *song_id,int &play_number)
{
	try
	{
		TCHAR select_song_id[128];
		bool result=false;

		if (NULL==song_id)
		{
			return false;
		}
		for (int i=0;i<select_song_count;i++)
		{
			memset(select_song_id,0x0,sizeof(select_song_id));
			result = select_song[i].get_song_id(select_song_id);
			if (result)
			{
				if (0==_tcscmp(song_id,select_song_id))
				{
					play_number = i+1;
					return true;
				}
			}
		}

		return false;
	}
	catch (...)
	{
		
	}
	return false;
}
bool select_song_manager::query_select_song_by_id(TCHAR *song_id,int &play_number, bool isDown /* = true */)
{
	try
	{
		TCHAR select_song_id[128];
		bool result=false;
		int play_number_pos = 0;  //����ԤԼ��λ��
		int is_down_update = 0;  //�ж��Ƿ������ػ����

		if (NULL==song_id)
		{
			return false;
		}
		for (int i=0;i<select_song_count;i++)
		{
			memset(select_song_id,0x0,sizeof(select_song_id));
			result = select_song[i].get_song_id(select_song_id);
			is_down_update = select_song[i].get_down_update_song();
			if (result)
			{
				if (1==is_down_update && isDown)
				{
					if (0==_tcscmp(song_id,select_song_id))
					{
						//play_number = i+1;
						play_number = -1;
						return true;
					}
				}
				else if (2==is_down_update && isDown)
				{
					if (0==_tcscmp(song_id,select_song_id))
					{
						//play_number = i+1;
						play_number = -2;
						return true;
					}
				}
				else
				{
					play_number_pos++;
					if (0==_tcscmp(song_id,select_song_id))
					{
						//play_number = i+1;
						play_number = play_number_pos;
						return true;
					}
				}
			}
		}

		return false;
		/*TCHAR select_song_id[128];
		bool result=false;

		if (NULL==song_id)
		{
			return false;
		}
		for (int i=0;i<select_song_count;i++)
		{
			memset(select_song_id,0x0,sizeof(select_song_id));
			result = select_song[i].get_song_id(select_song_id);
			if (result)
			{
				if (0==_tcscmp(song_id,select_song_id))
				{
					play_number = i+1;
					return true;
				}
			}
		}

		return false;*/
	}
	catch (...)
	{
		
	}
	return false;
}

void select_song_manager::set_show_page_number(int page_number)
{
	cur_show_page_number = page_number;
}

void select_song_manager::clear_select_song(bool clear_sing)
{
	try
	{
		//���ѡ�����
		for (int i=0;i<select_song_count;i++)
		{
			select_song[i].initialized_variables();
		}
		select_song_count=0;
		cur_show_page_number=0;
		total_page_number=0;
		//����ݳ�����
		if (clear_sing)
		{
			for (int i=0;i<sing_song_count;i++)
			{
				sing_song[i].initialized_variables();
			}
			sing_song_count=0;
			cur_select_test_song_number=0;
		}

		//��ѡ���������仯��ͨ����Ϣ��ʽ֪ͨ�������Ա����¼�¼��ѡ����ID
		::PostMessage(m_parent_handle,DM_SAVE_SELECT_SONG_ID,NULL,NULL);
	}
	catch (...)
	{
		
	}
	return;
}

bool select_song_manager::get_test_song_name(TCHAR *cur_song_name,TCHAR *next_song_name)
{
	try
	{
		int next_song_number=0;

		if ((cur_select_test_song_number<0)||(cur_select_test_song_number>=select_song_count))
		{
			return false;
		}

		//�õ����Ը�������ǰ����һ�׵ĸ���
		select_song[cur_select_test_song_number].get_song_name(cur_song_name);
		next_song_number = cur_select_test_song_number+1;
		if (next_song_number>=select_song_count)
		{
			next_song_number = 0;
		}
		select_song[next_song_number].get_song_name(next_song_name);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void select_song_manager::set_test_song_play_order(bool next_song)
{
	m_test_next_song = next_song;
}

bool select_song_manager::change_page_insert(bool pre_page,int src_position,bool first_page_insert,std::wstring &change_song_xml)
{
	try
	{
		int insert_position_suffix=0;
		int src_position_suffix=0;
		song_info insert_song_info;
		TCHAR song_show_info[512];
		TCHAR language[16];
		TCHAR song_name[64];
		TCHAR singer_name[64];

		if (pre_page)
		{
			//��ǰһҳ��
			if (first_page_insert)
			{
				//�������λ��
				insert_position_suffix = (cur_show_page_number-1)*m_page_show_row_count-1;
				if (insert_position_suffix<0)
				{
					insert_position_suffix=0;
				}
				m_cur_page_first_position = insert_position_suffix;
				//����ԭ���ľ���λ��
				src_position_suffix = (cur_show_page_number-1)*m_page_show_row_count+src_position-1;
			}
			else
			{
				//�������λ��
				insert_position_suffix = m_cur_page_first_position-1;
				//����ԭ���ľ���λ��
				src_position_suffix = insert_position_suffix+1;
				//��¼�µ�ǰ����λ��
				m_cur_page_first_position--;
			}
			if (insert_position_suffix<0)
			{
				return false;
			}
			//��¼����λ��
			m_song_insert_position = insert_position_suffix;
			//���㵱ǰ��ʾ��ҳ��
			cur_show_page_number = m_song_insert_position/m_page_show_row_count;
			cur_show_page_number++;
			//�ı�λ��
			insert_song_info = select_song[src_position_suffix];
			//����������
			for (int i=src_position_suffix;i>insert_position_suffix;i--)
			{
				select_song[i] = select_song[i-1];
			}
			select_song[insert_position_suffix] = insert_song_info;

			//��֯������ʾ�ַ���
			change_song_xml.clear();
			change_song_xml += L"<data><info rect=\"prepage\">";
			for (int i=insert_position_suffix;i<insert_position_suffix+m_page_show_row_count;i++)
			{
				if (i>=select_song_count)
				{
					//�������һ������ѭ��
					break;
				}
				memset(song_show_info,0x0,sizeof(song_show_info));
				memset(language,0x0,sizeof(language));
				memset(song_name,0x0,sizeof(song_name));
				memset(singer_name,0x0,sizeof(singer_name));

				select_song[i].get_song_language(language);
				select_song[i].get_song_name(song_name);
				select_song[i].get_singer_name(singer_name);

				swprintf(song_show_info,L"<item song=\"%02d %s\" singer=\"%s\" logo=\"\" lang=\"%s\"/>",i+1,song_name,singer_name,language);

				change_song_xml += song_show_info;
			}
			change_song_xml += L"</info></data>";
		}
		else
		{
			//���һҳ��
			if (first_page_insert)
			{
				//�������λ��
				insert_position_suffix = cur_show_page_number*m_page_show_row_count;
				if (insert_position_suffix>=select_song_count)
				{
					insert_position_suffix = select_song_count-1;
				}
				m_cur_page_first_position = insert_position_suffix-m_page_show_row_count+1;
				//����ԭ���ľ���λ��
				src_position_suffix = (cur_show_page_number-1)*m_page_show_row_count+src_position-1;
			}
			else
			{
				//�������λ��
				insert_position_suffix = m_cur_page_first_position+m_page_show_row_count;
				//����ԭ���ľ���λ��
				src_position_suffix = insert_position_suffix-1;
				//��¼�µ�ǰ����λ��
				m_cur_page_first_position++;
			}
			if (insert_position_suffix>=select_song_count)
			{
				//����λ�ô��ڸ�������ʱ��ֹͣ����
				return false;
			}
			//��¼����λ��
			m_song_insert_position = insert_position_suffix;
			//���㵱ǰ��ʾ��ҳ��
			cur_show_page_number = m_song_insert_position/m_page_show_row_count;
			cur_show_page_number++;
			//�ı�λ��
			insert_song_info = select_song[src_position_suffix];
			//����������
			for (int i=src_position_suffix;i<insert_position_suffix;i++)
			{
				select_song[i] = select_song[i+1];
			}
			select_song[insert_position_suffix] = insert_song_info;

			if ((insert_position_suffix==(select_song_count-1)) && (m_page_show_row_count!=src_position))
			{
				//����������һҳ���������κ�һ���ŵ���󶼲�ˢ��
				return false;
			}

			//��֯������ʾ�ַ���
			change_song_xml.clear();
			change_song_xml += L"<data><info rect=\"nextpage\">";
			for (int i=insert_position_suffix-m_page_show_row_count+1;i<=insert_position_suffix;i++)
			{
				if (i>=select_song_count)
				{
					//�������һ������ѭ��
					break;
				}
				memset(song_show_info,0x0,sizeof(song_show_info));
				memset(language,0x0,sizeof(language));
				memset(song_name,0x0,sizeof(song_name));
				memset(singer_name,0x0,sizeof(singer_name));

				select_song[i].get_song_language(language);
				select_song[i].get_song_name(song_name);
				select_song[i].get_singer_name(singer_name);

				swprintf(song_show_info,L"<item song=\"%02d %s\" singer=\"%s\" logo=\"\" lang=\"%s\"/>",i+1,song_name,singer_name,language);

				change_song_xml += song_show_info;
			}
			change_song_xml += L"</info></data>";
		}
		
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

int select_song_manager::get_flicker_item_number(void)
{
	try
	{
		//����ڵ�ǰҳ�ı�ţ���0��ʼ
		return m_song_insert_position%m_page_show_row_count;
	}
	catch (...)
	{
		
	}
	return -1;
}

void select_song_manager::mess_selected_song(void)
{
	try
	{
		int switch_pos=NULL;
		song_info switch_song;

		if (select_song_count<=0)
		{
			return;
		}

		for (int i=0;i<select_song_count;i++)
		{
			//�����漴��
			switch_pos = rand() / (RAND_MAX / select_song_count+1);
			if (switch_pos==i)
			{
				continue;
			}
			//����
			switch_song.initialized_variables();
			switch_song =select_song[i];
			select_song[i].initialized_variables();
			select_song[i] = select_song[switch_pos];
			select_song[switch_pos].initialized_variables();
			select_song[switch_pos] = switch_song;
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}
bool select_song_manager::modify_down_load_select_song(TCHAR * song_id,TCHAR* server_path,int server_pos,TCHAR* relative_path /* = NULL */)
{
	try
	{
		TCHAR select_song_id[256];
		bool result = false;  //��ʾ�Ƿ��ҵ�
		for (int i=0; i< select_song_count;i++)
		{
			memset(select_song_id,0x0,sizeof(select_song_id));
			select_song[i].get_song_id(select_song_id);
			if (0 == _tcscmp(select_song_id,song_id))
			{
				select_song[i].set_down_update_song(0);
				select_song[i].set_local_path(L"0");
				if (1 == server_pos)
				{
					select_song[i].set_server_path1(server_path);
				}
				else if (2 == server_pos)
				{
					select_song[i].set_server_path2(server_path);
				}
				else if (3 == server_pos)
				{
					select_song[i].set_server_path3(server_path);
				}
				else if (4 == server_pos)
				{
					select_song[i].set_server_path4(server_path);
				}
				else if (5 == server_pos)
				{
					select_song[i].set_server_path5(server_path);
				}
				else if (6 == server_pos)
				{
					select_song[i].set_server_path6(server_path);
				}

				if (relative_path != NULL)
				{
					select_song[i].set_song_relative_path(relative_path);
				}
				result = true;
			}
		}

		return result;
	}
	catch (...)
	{

	}

	return false;
}
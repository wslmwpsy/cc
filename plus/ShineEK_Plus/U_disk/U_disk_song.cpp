#include "StdAfx.h"
#include ".\u_disk_song.h"
#include "../file/config_file.h"

//声明其他地方已经定义
extern std::wstring g_all_language[];
extern FLASH_USE_LANGUAGE g_flash_use_language;          //flash使用的语言

U_disk_song::U_disk_song(void)
{
}

U_disk_song::~U_disk_song(void)
{
}

bool U_disk_song::search_U_disk_song(TCHAR *U_path,int page_row_count)
{
	try
	{
		CFileFind U_disk_song_find;
		TCHAR find_path[256];
		CString song_path;
		CString song_name;
		BOOL result=FALSE;
		TCHAR *file_format=NULL;
		TCHAR song_number[128];
		config_file_manager config_file;

		if (NULL==U_path)
		{
			return false;
		}
		memset(find_path,0x0,sizeof(find_path));
		m_song_total_count=0;
		//列表页显示的行数
		m_list_show_row_count = page_row_count;
		m_total_page_count = 0;
		m_cur_show_page_number=1;
		//得到空闲歌曲音量
		m_song_volume=config_file.read_integer(L"public_video",L"idlesse_volume",50);

		for(int i=0;i<U_DISK_SONG_MAX_COUNT;i++)
		{
			memset(m_U_disk_song[i].name,0x0,sizeof(m_U_disk_song[i].name));
			memset(m_U_disk_song[i].path,0x0,sizeof(m_U_disk_song[i].path));
			memset(m_U_disk_song[i].song_number,0x0,sizeof(m_U_disk_song[i].song_number));
		}

		//搜索路径
		swprintf(find_path,L"%s\\*.*",U_path);
		result = U_disk_song_find.FindFile(find_path);
		while(result)
		{
			result = U_disk_song_find.FindNextFile();

			if (U_disk_song_find.IsSystem() || U_disk_song_find.IsDots() || U_disk_song_find.IsDirectory())
			{
				continue;
			}
			if (U_disk_song_find.IsCompressed() || U_disk_song_find.IsHidden() || U_disk_song_find.IsTemporary())
			{
				continue;
			}

			//得到U盘名字
			song_name = U_disk_song_find.GetFileName();
			file_format = _tcsrchr(song_name.GetBuffer(0),'.');
			if (NULL==file_format)
			{
				continue;
			}
			//判断是否是可以播放的视频文件
			if ((0==_tcsicmp(file_format,L".wav"))||(0==_tcsicmp(file_format,L".mp3"))||(0==_tcsicmp(file_format,L".mpg")))
			{
				file_format[0] = '\0';

				//保存文件名
				_tcscpy(m_U_disk_song[m_song_total_count].name,song_name.GetBuffer(0));
				//得到文件路径
                song_path = U_disk_song_find.GetFilePath();
				//保存文件路径
				_tcscpy(m_U_disk_song[m_song_total_count].path,song_path.GetBuffer(0));
				//设置歌曲编号
				memset(song_number,0x0,sizeof(song_number));
				swprintf(song_number,L"U9%010d",m_song_total_count);
				_tcscpy(m_U_disk_song[m_song_total_count].song_number,song_number);
				//歌曲总数加加
				m_song_total_count++;
				//如果大于最大数，就要停止搜索
				if (m_song_total_count>=U_DISK_SONG_MAX_COUNT)
				{
					break;
				}
			}
		}
		//关闭文件查找
		U_disk_song_find.Close();

		//计算总的页数
		m_total_page_count = m_song_total_count/m_list_show_row_count+((m_song_total_count%m_list_show_row_count)?1:0);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool U_disk_song::make_U_disk_song_xml_list(std::wstring &song_xml_string,video_play_manager &video_manager,PAGE_OPERATE page_operate,std::wstring &default_color,std::wstring &select_color,std::wstring &playing_color)
{
	try
	{
		int page_number=0;
		int start_suffix=0;
		int end_suffix=0;
		TCHAR song_show_info[512];
		bool result=false;
		TCHAR playing_song_id[128];
		song_info playing_song_info;
		int play_number=0;

		memset(playing_song_id,0x0,sizeof(playing_song_id));
		playing_song_info.initialized_variables();

		if (m_song_total_count<=0)
		{
			return false;
		}

		memset(playing_song_id,0x0,sizeof(playing_song_id));
		//得到正在播放的歌曲
		result = video_manager.get_playing_video(playing_song_info);
		if (result)
		{
			//存在正在播放的视频
			playing_song_info.get_song_id(playing_song_id);
		}

		//改变页码
		switch(page_operate)
		{
		case FIRST_PAGE_OPERATE: //第一页
			{
				m_cur_show_page_number=1;
			}
			break;
		case PRE_PAGE_OPERATE:
			{
				m_cur_show_page_number--;
				if (m_cur_show_page_number<=0)
				{
					m_cur_show_page_number = m_total_page_count;
				}
			}
			break;
		case NEXT_PAGE_OPERATE:
			{
				m_cur_show_page_number++;
				if (m_cur_show_page_number>m_total_page_count)
				{
					m_cur_show_page_number=1;
				}
			}
			break;
		case CUR_PAGE_OPERATE:
			{
				//显示当前页，页码不变
				if (m_cur_show_page_number>m_total_page_count)
				{
					m_cur_show_page_number = m_total_page_count;
				}
				if (m_cur_show_page_number<1)
				{
					m_cur_show_page_number = 1;
				}
			}
			break;
		default:
			return false;
		}

		//组织前一页了。
		page_number = m_cur_show_page_number-1;
		if (page_number<=0)
		{
			page_number = m_total_page_count;
		}
		start_suffix = (page_number-1)*m_list_show_row_count;
		if (start_suffix<0)
		{
			start_suffix = 0;
		}
		end_suffix = page_number*m_list_show_row_count-1;
		if (end_suffix>=m_song_total_count)
		{
			end_suffix = m_song_total_count-1;
		}
		song_xml_string += L"<pre_list>";
		for (int i=start_suffix;i<=end_suffix;i++)
		{
			//上一页显示位空
			if (m_cur_show_page_number == 1)
			{
				break;
			}else{
				memset(song_show_info,0x0,sizeof(song_show_info));

				if ((0!=_tcscmp(playing_song_id,L""))&&(0==_tcscmp(playing_song_id,m_U_disk_song[i].song_number)))
				{
					//正播放
					swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s[%s]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,   \
						g_all_language[5].c_str(),playing_color.c_str());
				}
				else
				{
					result = video_manager.query_select_song_by_id(m_U_disk_song[i].song_number,play_number);
					if (result)
					{
						//预约
						swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s[%s%d]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,   \
							g_all_language[4].c_str(),play_number,select_color.c_str());
					}
					else
					{
						//没有选择
						swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,default_color.c_str());
					}
				}

				song_xml_string += song_show_info;
			}
		}

		song_xml_string += L"</pre_list><cur_list>";
		//组织当前页
		page_number = m_cur_show_page_number;
		start_suffix = (page_number-1)*m_list_show_row_count;
		if (start_suffix<0)
		{
			start_suffix = 0;
		}
		end_suffix = page_number*m_list_show_row_count-1;
		if (end_suffix>=m_song_total_count)
		{
			end_suffix = m_song_total_count-1;
		}
		for (int i=start_suffix;i<=end_suffix;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));

			if ((0!=_tcscmp(playing_song_id,L""))&&(0==_tcscmp(playing_song_id,m_U_disk_song[i].song_number)))
			{
				//正播放
				swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s[%s]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,   \
					g_all_language[5].c_str(),playing_color.c_str());
			}
			else
			{
				result = video_manager.query_select_song_by_id(m_U_disk_song[i].song_number,play_number);
				if (result)
				{
					//预约
					swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s[%s%d]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,   \
						g_all_language[4].c_str(),play_number,select_color.c_str());
				}
				else
				{
					//没有选择
					swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,default_color.c_str());
				}
			}

			song_xml_string += song_show_info;
		}

		song_xml_string += L"</cur_list><next_list>";
		//下一页
		page_number = m_cur_show_page_number+1;
		if (page_number>m_total_page_count)
		{
			page_number = 1;
		}
		start_suffix = (page_number-1)*m_list_show_row_count;
		if (start_suffix<0)
		{
			start_suffix = 0;
		}
		end_suffix = page_number*m_list_show_row_count-1;
		if (end_suffix>=m_song_total_count)
		{
			end_suffix = m_song_total_count-1;
		}
		for (int i=start_suffix;i<=end_suffix;i++)
		{
			if (m_cur_show_page_number == m_total_page_count)
			{
				break;
			}else{
				memset(song_show_info,0x0,sizeof(song_show_info));

				if ((0!=_tcscmp(playing_song_id,L""))&&(0==_tcscmp(playing_song_id,m_U_disk_song[i].song_number)))
				{
					//正播放
					swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s[%s]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,   \
						g_all_language[5].c_str(),playing_color.c_str());
				}
				else
				{
					result = video_manager.query_select_song_by_id(m_U_disk_song[i].song_number,play_number);
					if (result)
					{
						//预约
						swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s[%s%d]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,   \
							g_all_language[4].c_str(),play_number,select_color.c_str());
					}
					else
					{
						//没有选择
						swprintf(song_show_info,L"<item lang_txt=\"\" edition_txt=\"\" song_txt=\"%s\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",m_U_disk_song[i].name,default_color.c_str());
					}
				}

				song_xml_string += song_show_info;
			}
		}
		song_xml_string += L"</next_list>";

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool U_disk_song::get_U_disk_song_info(song_info &U_song_info,int select_number)
{
	try
	{
		int array_suffix=0;
		int play_pos=0;

		if (m_song_total_count<=0)
		{
			return false;
		}

		//得到数组中的绝对编号
		array_suffix = (m_cur_show_page_number-1)*m_list_show_row_count+select_number;
		if (array_suffix>=m_song_total_count)
		{
			array_suffix = m_song_total_count-1;
		}
		else if (array_suffix<0)
		{
			array_suffix = 0;
		}
		//写入歌曲信息
		U_song_info.set_song_id(m_U_disk_song[array_suffix].song_number);
		U_song_info.set_song_name(m_U_disk_song[array_suffix].name);
		U_song_info.set_local_path(m_U_disk_song[array_suffix].path);
		U_song_info.set_accompany_volume(m_song_volume);
		U_song_info.set_karaoke_volume(m_song_volume);
		//设置视频类型
		U_song_info.set_video_type(PLAY_U_DISK_SONG);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool U_disk_song::get_song_row_and_page_count(int &song_count,int &page_count,int &cur_page_number)
{
	song_count = m_song_total_count;
	page_count = m_total_page_count;
	cur_page_number = m_cur_show_page_number;

	return true;
}
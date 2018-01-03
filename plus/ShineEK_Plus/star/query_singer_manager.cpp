#include "StdAfx.h"
#include ".\query_singer_manager.h"
#include "..\file\config_file.h"
#include "..\star\decrypt_singer_picture.h"
#include "..\folder_name.h"


#include <shlwapi.h>


query_singer_manager::query_singer_manager(void)
{
	TCHAR *install_path=NULL;
	config_file_manager config_file;

	singer_list_exist=false;
	//歌星图片文件夹路径
	memset(m_star_picture_path,0x0,sizeof(m_star_picture_path));

	//得到安装路径
	GetModuleFileName(NULL, m_star_picture_path, sizeof(m_star_picture_path)/sizeof(TCHAR));
	install_path = _tcsrchr(m_star_picture_path, _T('\\'));
	if (install_path)
	{
		install_path[0] = '\0';
	}
	_tcscat(m_star_picture_path,L"\\");
	//得到歌星图片路径
	_tcscat(m_star_picture_path,g_folder_name[0]);

	m_singer_name_default_color = config_file.read_string(L"song_name_color",L"default_color",L"0xFFFFFF");
	
	//初始化三屏数据的变量
	initialized_variables();

	m_singer_page_show_row_count = 0;
}

query_singer_manager::~query_singer_manager(void)
{
}

void query_singer_manager::initialized_variables(void)
{
	for (int i=0;i<SINGER_PAGE_SHOW_ROW_COUNT_MAX;i++)
	{
		pre_page_singer_list[i].initialized_variables();
		cur_page_singer_list[i].initialized_variables();
		next_page_singer_list[i].initialized_variables();
	}
}

bool query_singer_manager::set_singer_list(std::wstring query_singer_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number)
{
	try
	{
		int row=0;
		int value=0;
		float bit_rate=0.0;
		UINT64 file_size=0;
		int i=0;

		if (SINGER_NO_PAGE==page_count)
		{
			//没有查询到符合条件的数据
			singer_list_exist=false;
			return true;
		}
		singer_list_exist = true;

		//赋值前一页的数据
		switch(page_count)
		{
		case SINGER_ONE_PAGE:
			{
				i=0;
			}
			break;
		case SINGER_TWO_PAGE:
			{
				if (SINGER_ONE_PAGE==cur_page_number)
				{
					i=singer_page_show_row_count*result_column_nums;
				}
				else
				{
					i = 0;
				}
			}
			break;
		case SINGER_THREE_PAGE:
			{
				if (SINGER_ONE_PAGE==cur_page_number)
				{
					i=2*m_singer_page_show_row_count*result_column_nums;
				}
				else if(SINGER_TWO_PAGE==cur_page_number)
				{
					i = 0;
				}
				else
				{
					i=m_singer_page_show_row_count*result_column_nums;
				}
			}
			break;
		default:
			{
				i=0;
			}
			break;
		}
		//if (cur_page_number != 1){
			row=0;
			for (;i<result_item_number;i+=result_column_nums)
			{
				//一行行的赋值
				pre_page_singer_list[row].set_singer_id(query_singer_result[i].c_str());
				pre_page_singer_list[row].set_singer_name(query_singer_result[i+1].c_str());
				pre_page_singer_list[row].set_singer_sex(query_singer_result[i+2].c_str());
				pre_page_singer_list[row].set_singer_region(query_singer_result[i+3].c_str());

				row++;
				if (row>=m_singer_page_show_row_count)
				{
					break;
				}
			}
		//}

		//赋值当前页的数据
		switch(page_count)
		{
		case SINGER_ONE_PAGE:
			{
				i=0;
			}
			break;
		case SINGER_TWO_PAGE:
			{
				if (SINGER_ONE_PAGE==cur_page_number)
				{
					i=0;
				}
				else
				{
					i = m_singer_page_show_row_count*result_column_nums;
				}
			}
			break;
		case SINGER_THREE_PAGE:
			{
				if (SINGER_ONE_PAGE==cur_page_number)
				{
					i=0;
				}
				else if(SINGER_TWO_PAGE==cur_page_number)
				{
					i = m_singer_page_show_row_count*result_column_nums;
				}
				else
				{
					i=2*m_singer_page_show_row_count*result_column_nums;
				}
			}
			break;
		default:
			{
				i=m_singer_page_show_row_count*result_column_nums;
			}
			break;
		}
		row=0;
		for (;i<result_item_number;i+=result_column_nums)
		{
			//一行行的赋值
			cur_page_singer_list[row].set_singer_id(query_singer_result[i].c_str());
			cur_page_singer_list[row].set_singer_name(query_singer_result[i+1].c_str());
			cur_page_singer_list[row].set_singer_sex(query_singer_result[i+2].c_str());
			cur_page_singer_list[row].set_singer_region(query_singer_result[i+3].c_str());

			row++;
			if (row>=m_singer_page_show_row_count)
			{
				break;
			}
		}

		//赋值下一页的数据
		switch(page_count)
		{
		case SINGER_ONE_PAGE:
			{
				i=0;
			}
			break;
		case SINGER_TWO_PAGE:
			{
				if (SINGER_ONE_PAGE==cur_page_number)
				{
					i=m_singer_page_show_row_count*result_column_nums;
				}
				else
				{
					i = 0;
				}
			}
			break;
		case SINGER_THREE_PAGE:
			{
				if (SINGER_ONE_PAGE==cur_page_number)
				{
					i=m_singer_page_show_row_count*result_column_nums;
				}
				else if(SINGER_TWO_PAGE==cur_page_number)
				{
					i = 2*m_singer_page_show_row_count*result_column_nums;
				}
				else
				{
					i=0;
				}
			}
			break;
		default:
			{
				i=2*m_singer_page_show_row_count*result_column_nums;
			}
			break;
		}
		//if (cur_page_number != page_count){
			row=0;
			for (;i<result_item_number;i+=result_column_nums)
			{
				//一行行的赋值
				next_page_singer_list[row].set_singer_id(query_singer_result[i].c_str());
				next_page_singer_list[row].set_singer_name(query_singer_result[i+1].c_str());
				next_page_singer_list[row].set_singer_sex(query_singer_result[i+2].c_str());
				next_page_singer_list[row].set_singer_region(query_singer_result[i+3].c_str());

				row++;
				if (row>=m_singer_page_show_row_count)
				{
					break;
				}
			}
	//	}

		return true;
	}
	catch (...)
	{

	}
	return false;
}
bool query_singer_manager::set_handheld_singer_list(std::wstring query_singer_result[],int result_item_number,int result_column_nums)
{
	try
	{
		int row=0;

		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			//一行行的赋值
			m_handheld_singer_list[row].initialized_variables();
			m_handheld_singer_list[row].set_singer_name(query_singer_result[i].c_str());
			m_handheld_singer_list[row].set_singer_sex(query_singer_result[i+1].c_str());
			m_handheld_singer_list[row].set_singer_region(query_singer_result[i+2].c_str());

			row++;
			if (row>=m_singer_page_show_row_count)
			{
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

/*
< pre_list><item singer_txt="张学友" color="#000000"  image_path="" /></ pre_list>

< cur_list><item singer_txt="张学友" color="#000000"  image_path="" /></ cur_list>

< next_list><item singer_txt="张学友" color="#000000"  image_path="" /></ next_list>
*/

bool query_singer_manager::make_singer_list_xml(std::wstring &singer_list_xml)
{
	try
	{
		TCHAR siner_show_info[1024];
		bool result=false;
		int file_number=0;

		//产生0-132的随即数
		file_number = rand() / (RAND_MAX / 133 + 1);

		if (!singer_list_exist)
		{
			return true;
		}

		//组织三屏数据
		//组织前一页了。
		singer_list_xml += L"<pre_list>";
		for (int i=0;i<m_singer_page_show_row_count;i++)
		{
			memset(siner_show_info,0x0,sizeof(siner_show_info));

			file_number++;
			result = make_singer_xml_by_name(pre_page_singer_list[i],file_number,siner_show_info);
			if (result)
			{
				singer_list_xml += siner_show_info;
			}		
		}

		singer_list_xml += L"</pre_list><cur_list>";
		//组织当前页
		for (int i=0;i<m_singer_page_show_row_count;i++)
		{
			memset(siner_show_info,0x0,sizeof(siner_show_info));

			file_number++;
			//result = make_singer_xml_by_name(cur_page_singer_list[i],file_number,siner_show_info,encrypt_singer);
			result = make_singer_xml_by_name(cur_page_singer_list[i],file_number,siner_show_info);
			if (result)
			{
				singer_list_xml += siner_show_info;
			}		
		}

		singer_list_xml += L"</cur_list><next_list>";
		//下一页
		for (int i=0;i<m_singer_page_show_row_count;i++)
		{
			memset(siner_show_info,0x0,sizeof(siner_show_info));

			file_number++;
			//result = make_singer_xml_by_name(next_page_singer_list[i],file_number,siner_show_info,encrypt_singer);
			result = make_singer_xml_by_name(next_page_singer_list[i],file_number,siner_show_info);
			if (result)
			{
				singer_list_xml += siner_show_info;
			}		
		}
		singer_list_xml += L"</next_list>";

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool query_singer_manager::make_singer_xml_by_name(singer_info &singer_info_class,int picture_number,TCHAR *singer_xml)
{
	try
	{		
		TCHAR decrypt_path[256];
		decrypt_picture decrypt_picture_class;
		TCHAR singer_sex[256];
		TCHAR singer_name[256];
		TCHAR singer_id[256];
		bool result=false;

		if (NULL==singer_xml)
		{
			return false;
		}

		
		memset(decrypt_path,0x0,sizeof(decrypt_path));
		memset(singer_sex,0x0,sizeof(singer_sex));
		memset(singer_name,0x0,sizeof(singer_name));
		memset(singer_id,0x0,sizeof(singer_id));

		//得到歌星名字
		result = singer_info_class.get_singer_name(singer_name);
		if (!result || (0==_tcscmp(singer_name,L"")))
		{
			return false;
		}
		//得到歌星性别
		singer_info_class.get_singer_sex(singer_sex);
		singer_info_class.get_singer_id(singer_id);
		//解密歌星图片
	   // result = decrypt_picture_class.decrypt_singer_picture(singer_name,singer_sex,picture_number,m_star_picture_path,decrypt_path);
		 //result = decrypt_picture_class.decrypt_singer_picture(singer_id,singer_sex,picture_number,m_star_picture_path,decrypt_path);
		swprintf(decrypt_path,L"%s\\%s.jpg",m_star_picture_path,singer_id);
		if (!PathFileExists(decrypt_path))
		{
			//采用默认图片
			memset(decrypt_path,0x0,sizeof(decrypt_path));
			swprintf(decrypt_path,L"%s\\default.jpg",m_star_picture_path);
		}

		swprintf(singer_xml,L"<item singer_id=\"%s\" singer_txt=\"%s\" color=\"%s\"  image_path=\"%s\" />",singer_id,singer_name,m_singer_name_default_color.c_str(),decrypt_path);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

singer_info query_singer_manager::get_singer_info(int suffix)
{
	if (suffix<0)
	{
		suffix = 0;
	}
	else if (suffix>=m_singer_page_show_row_count)
	{
		suffix = m_singer_page_show_row_count-1;
	}

	return cur_page_singer_list[suffix];
}

singer_info query_singer_manager::get_handheld_singer_info(int suffix)
{
	if (suffix<0)
	{
		suffix = 0;
	}
	else if (suffix>=m_singer_page_show_row_count)
	{
		suffix = m_singer_page_show_row_count-1;
	}

	return m_handheld_singer_list[suffix];
}

bool query_singer_manager::get_star_picture_path(TCHAR *path)
{
	try
	{
		if (0==_tcscmp(m_star_picture_path,L""))
		{
			return false;
		}
		_tcscpy(path,m_star_picture_path);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}
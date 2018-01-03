#include "StdAfx.h"
#include ".\query_song_manager.h"
#include "..\common\string_function.h"
#include "..\file\config_file.h"
#include "..\message.h"
#include "..\flash\PageData.h"
#include "..\folder_name.h"
#include "..\star\decrypt_singer_picture.h"

extern std::wstring g_all_language[];
extern FLASH_USE_LANGUAGE g_flash_use_language; //flashʹ�õ�����

query_song_manager::query_song_manager(void)
{
	config_file_manager config_file;
	TCHAR install_path[256];

	m_page_show_row_count = config_file.read_integer(L"flash",L"page_show_row_count",7);
	m_default_song_color = config_file.read_string(L"song_name_color",L"default_color",L"0xFFFFFF");       //Ĭ�ϸ�����ɫ
	m_playing_song_color = config_file.read_string(L"song_name_color",L"playing_song_color",L"0xFF0000");  //�����Ÿ�������ɫ
	m_select_song_color = config_file.read_string(L"song_name_color",L"select_song_color",L"0xFF9900");    //ѡ�������ɫ
#ifdef SAN_JI_SMART_HOME_SYSTEM
	//����ʾ��� 2013-01-27 modify ZHEN
	m_no_moive_name_show_lyric = false;
#else
	m_no_moive_name_show_lyric = config_file.read_boolean(L"flash",L"no_movie_name_show_lyric",false);
#endif

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

	initialized_variables();
}

query_song_manager::~query_song_manager(void)
{
}
void query_song_manager::initialized_variables(void)
{
	try
	{
		for (int i=0;i<SELECT_SONG_MAX_COUNT;i++)
		{
			test_page_song_list[i].initialized_variables();
		}
		for (int i=0;i<PAGE_SHOW_MAX_ROW_COUNT;i++)
		{
			pre_page_song_list[i].initialized_variables();
			cur_page_song_list[i].initialized_variables();
			next_page_song_list[i].initialized_variables();
		}
		song_list_exist=false;
	}
	catch (...)
	{
		
	}
	return;
}

bool query_song_manager::set_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number,int page_show_row_count)
{
	try
	{
		int row=0;
		int value=0;
		int i=0;

		if (NO_PAGE==page_count)
		{
			//û�в�ѯ����������������
			song_list_exist=false;
			return true;
		}
		song_list_exist = true;

		//��ֵǰһҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=page_show_row_count*result_column_nums;
				}
				else
				{
					i = 0;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=2*page_show_row_count*result_column_nums;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = 0;
				}
				else
				{
					i=page_show_row_count*result_column_nums;
				}
			}
			break;
		default:
			{
				i=0;
			}
			break;
		}
		//if (cur_page_number != 1)
		//{
			row=0;
			for (;i<result_item_number;i+=result_column_nums)
			{
				//һ���еĸ�ֵ
				pre_page_song_list[row].set_song_id(query_song_result[i].c_str());
				pre_page_song_list[row].set_accompany_sing_track(query_song_result[i+1].c_str());
				pre_page_song_list[row].set_karaoke_track(query_song_result[i+2].c_str());
				pre_page_song_list[row].set_guid_track(query_song_result[i+3].c_str());
				pre_page_song_list[row].set_song_name(query_song_result[i+4].c_str());
				pre_page_song_list[row].set_movie_name(query_song_result[i+5].c_str());
				value = 0;
				swscanf(query_song_result[i+6].c_str(),L"%d",&value);
				pre_page_song_list[row].set_song_sort(value);
				value = 0;
				swscanf(query_song_result[i+7].c_str(),L"%d",&value);
				pre_page_song_list[row].set_accompany_volume(value);
				value = 0;
				swscanf(query_song_result[i+8].c_str(),L"%d",&value);
				pre_page_song_list[row].set_karaoke_volume(value);
				pre_page_song_list[row].set_language(query_song_result[i+9].c_str());
				pre_page_song_list[row].set_song_type(query_song_result[i+10].c_str());
				pre_page_song_list[row].set_singer_name(query_song_result[i+11].c_str());
				pre_page_song_list[row].set_singer_sex(query_song_result[i+12].c_str());
				pre_page_song_list[row].set_song_version(query_song_result[i+13].c_str());
				value = 0;
				swscanf(query_song_result[i+14].c_str(),L"%d",&value);
				pre_page_song_list[row].set_light_control_set(value);
				value = 0;
				swscanf(query_song_result[i+15].c_str(),L"%d",&value);
				pre_page_song_list[row].set_audio_effect_code(value);
				pre_page_song_list[row].set_file_format(query_song_result[i+16].c_str());
				pre_page_song_list[row].set_local_path(query_song_result[i+17].c_str());
				pre_page_song_list[row].set_server_path1(query_song_result[i+18].c_str());
				pre_page_song_list[row].set_server_path2(query_song_result[i+19].c_str());
				pre_page_song_list[row].set_server_path3(query_song_result[i+20].c_str());
				pre_page_song_list[row].set_server_path4(query_song_result[i+21].c_str());
				pre_page_song_list[row].set_server_path5(query_song_result[i+22].c_str());
				pre_page_song_list[row].set_server_path6(query_song_result[i+23].c_str());
				pre_page_song_list[row].set_song_relative_path(query_song_result[i+24].c_str());
				value = 0;
				swscanf(query_song_result[i+25].c_str(),L"%d",&value);
				pre_page_song_list[row].set_video_saturation(value);
				value = 0;
				swscanf(query_song_result[i+26].c_str(),L"%d",&value);
				pre_page_song_list[row].set_video_luminance(value);
				value = 0;
				swscanf(query_song_result[i+27].c_str(),L"%d",&value);
				pre_page_song_list[row].set_video_contrast(value);
				pre_page_song_list[row].set_lyric(query_song_result[i+28].c_str());
				pre_page_song_list[row].set_culture_code(query_song_result[i+29].c_str());
				pre_page_song_list[row].set_preview_path(query_song_result[i+30].c_str());
				pre_page_song_list[row].set_video_type(PLAY_SONG_TYPE_SELECT_SONG);
				pre_page_song_list[row].set_singer_id1(query_song_result[i+31].c_str());
				pre_page_song_list[row].set_singer_id2(query_song_result[i+32].c_str());
				pre_page_song_list[row].set_singer_id3(query_song_result[i+33].c_str());
				pre_page_song_list[row].set_singer_id4(query_song_result[i+34].c_str());
				pre_page_song_list[row].set_file_version(query_song_result[i+35].c_str());

				row++;
				if (row>=page_show_row_count)
				{
					break;
				}
			}
		//}

		//��ֵ��ǰҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=0;
				}
				else
				{
					i = page_show_row_count*result_column_nums;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=0;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = page_show_row_count*result_column_nums;
				}
				else
				{
					i=2*page_show_row_count*result_column_nums;
				}
			}
			break;
		default:
			{
				i=page_show_row_count*result_column_nums;
			}
			break;
		}
		row=0;
		for (;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			cur_page_song_list[row].set_song_id(query_song_result[i].c_str());
			cur_page_song_list[row].set_accompany_sing_track(query_song_result[i+1].c_str());
			cur_page_song_list[row].set_karaoke_track(query_song_result[i+2].c_str());
			cur_page_song_list[row].set_guid_track(query_song_result[i+3].c_str());
			cur_page_song_list[row].set_song_name(query_song_result[i+4].c_str());
			cur_page_song_list[row].set_movie_name(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			cur_page_song_list[row].set_song_sort(value);
			value = 0;
			swscanf(query_song_result[i+7].c_str(),L"%d",&value);
			cur_page_song_list[row].set_accompany_volume(value);
			value = 0;
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			cur_page_song_list[row].set_karaoke_volume(value);
			cur_page_song_list[row].set_language(query_song_result[i+9].c_str());
			cur_page_song_list[row].set_song_type(query_song_result[i+10].c_str());
			cur_page_song_list[row].set_singer_name(query_song_result[i+11].c_str());
			cur_page_song_list[row].set_singer_sex(query_song_result[i+12].c_str());
			cur_page_song_list[row].set_song_version(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			cur_page_song_list[row].set_light_control_set(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			cur_page_song_list[row].set_audio_effect_code(value);
			cur_page_song_list[row].set_file_format(query_song_result[i+16].c_str());
			cur_page_song_list[row].set_local_path(query_song_result[i+17].c_str());
			cur_page_song_list[row].set_server_path1(query_song_result[i+18].c_str());
			cur_page_song_list[row].set_server_path2(query_song_result[i+19].c_str());
			cur_page_song_list[row].set_server_path3(query_song_result[i+20].c_str());
			cur_page_song_list[row].set_server_path4(query_song_result[i+21].c_str());
			cur_page_song_list[row].set_server_path5(query_song_result[i+22].c_str());
			cur_page_song_list[row].set_server_path6(query_song_result[i+23].c_str());
			cur_page_song_list[row].set_song_relative_path(query_song_result[i+24].c_str());
			value = 0;
			swscanf(query_song_result[i+25].c_str(),L"%d",&value);
			cur_page_song_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+26].c_str(),L"%d",&value);
			cur_page_song_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+27].c_str(),L"%d",&value);
			cur_page_song_list[row].set_video_contrast(value);
			cur_page_song_list[row].set_lyric(query_song_result[i+28].c_str());
			cur_page_song_list[row].set_culture_code(query_song_result[i+29].c_str());
			cur_page_song_list[row].set_preview_path(query_song_result[i+30].c_str());
			cur_page_song_list[row].set_video_type(PLAY_SONG_TYPE_SELECT_SONG);
			cur_page_song_list[row].set_singer_id1(query_song_result[i+31].c_str());
			cur_page_song_list[row].set_singer_id2(query_song_result[i+32].c_str());
			cur_page_song_list[row].set_singer_id3(query_song_result[i+33].c_str());
			cur_page_song_list[row].set_singer_id4(query_song_result[i+34].c_str());
			cur_page_song_list[row].set_file_version(query_song_result[i+35].c_str());

			row++;
			if (row>=page_show_row_count)
			{
				break;
			}
		}

		//��ֵ��һҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=page_show_row_count*result_column_nums;
				}
				else
				{
					i = 0;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=page_show_row_count*result_column_nums;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = 2*page_show_row_count*result_column_nums;
				}
				else
				{
					i=0;
				}
			}
			break;
		default:
			{
				i=2*page_show_row_count*result_column_nums;
			}
			break;
		}
		//if (cur_page_number != page_count)
		//{
			row=0;
			for (;i<result_item_number;i+=result_column_nums)
			{
				//һ���еĸ�ֵ
				next_page_song_list[row].set_song_id(query_song_result[i].c_str());
				next_page_song_list[row].set_accompany_sing_track(query_song_result[i+1].c_str());
				next_page_song_list[row].set_karaoke_track(query_song_result[i+2].c_str());
				next_page_song_list[row].set_guid_track(query_song_result[i+3].c_str());
				next_page_song_list[row].set_song_name(query_song_result[i+4].c_str());
				next_page_song_list[row].set_movie_name(query_song_result[i+5].c_str());
				value = 0;
				swscanf(query_song_result[i+6].c_str(),L"%d",&value);
				next_page_song_list[row].set_song_sort(value);
				value = 0;
				swscanf(query_song_result[i+7].c_str(),L"%d",&value);
				next_page_song_list[row].set_accompany_volume(value);
				value = 0;
				swscanf(query_song_result[i+8].c_str(),L"%d",&value);
				next_page_song_list[row].set_karaoke_volume(value);
				next_page_song_list[row].set_language(query_song_result[i+9].c_str());
				next_page_song_list[row].set_song_type(query_song_result[i+10].c_str());
				next_page_song_list[row].set_singer_name(query_song_result[i+11].c_str());
				next_page_song_list[row].set_singer_sex(query_song_result[i+12].c_str());
				next_page_song_list[row].set_song_version(query_song_result[i+13].c_str());
				value = 0;
				swscanf(query_song_result[i+14].c_str(),L"%d",&value);
				next_page_song_list[row].set_light_control_set(value);
				value = 0;
				swscanf(query_song_result[i+15].c_str(),L"%d",&value);
				next_page_song_list[row].set_audio_effect_code(value);
				next_page_song_list[row].set_file_format(query_song_result[i+16].c_str());
				next_page_song_list[row].set_local_path(query_song_result[i+17].c_str());
				next_page_song_list[row].set_server_path1(query_song_result[i+18].c_str());
				next_page_song_list[row].set_server_path2(query_song_result[i+19].c_str());
				next_page_song_list[row].set_server_path3(query_song_result[i+20].c_str());
				next_page_song_list[row].set_server_path4(query_song_result[i+21].c_str());
				next_page_song_list[row].set_server_path5(query_song_result[i+22].c_str());
				next_page_song_list[row].set_server_path6(query_song_result[i+23].c_str());
				next_page_song_list[row].set_song_relative_path(query_song_result[i+24].c_str());
				value = 0;
				swscanf(query_song_result[i+25].c_str(),L"%d",&value);
				next_page_song_list[row].set_video_saturation(value);
				value = 0;
				swscanf(query_song_result[i+26].c_str(),L"%d",&value);
				next_page_song_list[row].set_video_luminance(value);
				value = 0;
				swscanf(query_song_result[i+27].c_str(),L"%d",&value);
				next_page_song_list[row].set_video_contrast(value);
				next_page_song_list[row].set_lyric(query_song_result[i+28].c_str());
				next_page_song_list[row].set_culture_code(query_song_result[i+29].c_str());
				next_page_song_list[row].set_preview_path(query_song_result[i+30].c_str());
				next_page_song_list[row].set_video_type(PLAY_SONG_TYPE_SELECT_SONG);
				next_page_song_list[row].set_singer_id1(query_song_result[i+31].c_str());
				next_page_song_list[row].set_singer_id2(query_song_result[i+32].c_str());
				next_page_song_list[row].set_singer_id3(query_song_result[i+33].c_str());
				next_page_song_list[row].set_singer_id4(query_song_result[i+34].c_str());
				next_page_song_list[row].set_file_version(query_song_result[i+35].c_str());

				row++;
				if (row>=page_show_row_count)
				{
					break;
				}
			}
		//}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool query_song_manager::set_test_or_select_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,bool test_song)
{
	try
	{
		int row=0;
		int value=0;

		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			test_page_song_list[row].set_song_id(query_song_result[i].c_str());
			test_page_song_list[row].set_accompany_sing_track(query_song_result[i+1].c_str());
			test_page_song_list[row].set_karaoke_track(query_song_result[i+2].c_str());
			test_page_song_list[row].set_guid_track(query_song_result[i+3].c_str());
			test_page_song_list[row].set_song_name(query_song_result[i+4].c_str());
			test_page_song_list[row].set_movie_name(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			test_page_song_list[row].set_song_sort(value);
			value = 0;
			swscanf(query_song_result[i+7].c_str(),L"%d",&value);
			test_page_song_list[row].set_accompany_volume(value);
			value = 0;
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			test_page_song_list[row].set_karaoke_volume(value);
			test_page_song_list[row].set_language(query_song_result[i+9].c_str());
			test_page_song_list[row].set_song_type(query_song_result[i+10].c_str());
			test_page_song_list[row].set_singer_name(query_song_result[i+11].c_str());
			test_page_song_list[row].set_singer_sex(query_song_result[i+12].c_str());
			test_page_song_list[row].set_song_version(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			test_page_song_list[row].set_light_control_set(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			test_page_song_list[row].set_audio_effect_code(value);
			test_page_song_list[row].set_file_format(query_song_result[i+16].c_str());
			test_page_song_list[row].set_local_path(query_song_result[i+17].c_str());
			test_page_song_list[row].set_server_path1(query_song_result[i+18].c_str());
			test_page_song_list[row].set_server_path2(query_song_result[i+19].c_str());
			test_page_song_list[row].set_server_path3(query_song_result[i+20].c_str());
			test_page_song_list[row].set_server_path4(query_song_result[i+21].c_str());
			test_page_song_list[row].set_server_path5(query_song_result[i+22].c_str());
			test_page_song_list[row].set_server_path6(query_song_result[i+23].c_str());
			test_page_song_list[row].set_song_relative_path(query_song_result[i+24].c_str());
			value = 0;
			swscanf(query_song_result[i+25].c_str(),L"%d",&value);
			test_page_song_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+26].c_str(),L"%d",&value);
			test_page_song_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+27].c_str(),L"%d",&value);
			test_page_song_list[row].set_video_contrast(value);
			test_page_song_list[row].set_lyric(query_song_result[i+28].c_str());
			test_page_song_list[row].set_culture_code(query_song_result[i+29].c_str());
			test_page_song_list[row].set_preview_path(query_song_result[i+30].c_str());
			test_page_song_list[row].set_video_type(PLAY_SONG_TYPE_SELECT_SONG);

			row++;
			if (test_song && (row>=TEST_PAGE_SHOW_ROW_COUNT))
			{
				break;
			}
			else if (!test_song && (row>=SELECT_SONG_MAX_COUNT))
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

//û���޸��ֳֵĲ�ѯ��������Ҫ�޸ĸò�ѯ����
bool query_song_manager::set_handheld_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums)
{
	try
	{
		int row=0;
		int value=0;

		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			m_handheld_song_list[row].initialized_variables();
			//һ���еĸ�ֵ
			m_handheld_song_list[row].set_song_id(query_song_result[i].c_str());
			m_handheld_song_list[row].set_accompany_sing_track(query_song_result[i+1].c_str());
			m_handheld_song_list[row].set_karaoke_track(query_song_result[i+2].c_str());
			m_handheld_song_list[row].set_song_name(query_song_result[i+3].c_str());
			//�ֳ�û������
			//m_handheld_song_list[row].set_movie_name(query_song_result[i+4].c_str());
			value = 0;
			swscanf(query_song_result[i+4].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_song_sort(value);
			value = 0;
			swscanf(query_song_result[i+5].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_accompany_volume(value);
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_karaoke_volume(value);
			m_handheld_song_list[row].set_language(query_song_result[i+7].c_str());
			m_handheld_song_list[row].set_song_type(query_song_result[i+8].c_str());
			m_handheld_song_list[row].set_singer_name(query_song_result[i+9].c_str());
			//m_handheld_song_list[row].set_singer_sex(query_song_result[i+11].c_str());
			m_handheld_song_list[row].set_song_version(query_song_result[i+10].c_str());
			value = 0;
			swscanf(query_song_result[i+11].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_light_control_set(value);
			//�ֳ�û��������Ч
			//value = 0;
			//swscanf(query_song_result[i+11].c_str(),L"%d",&value);
			//m_handheld_song_list[row].set_audio_effect_code(value);
			m_handheld_song_list[row].set_file_format(query_song_result[i+12].c_str());
			m_handheld_song_list[row].set_local_path(query_song_result[i+13].c_str());
			m_handheld_song_list[row].set_server_path1(query_song_result[i+14].c_str());
			m_handheld_song_list[row].set_server_path2(query_song_result[i+15].c_str());
			m_handheld_song_list[row].set_server_path3(query_song_result[i+16].c_str());
			m_handheld_song_list[row].set_server_path4(query_song_result[i+17].c_str());
			m_handheld_song_list[row].set_server_path5(query_song_result[i+18].c_str());
			m_handheld_song_list[row].set_server_path6(query_song_result[i+19].c_str());
			m_handheld_song_list[row].set_song_relative_path(query_song_result[i+20].c_str());
			value = 0;
			swscanf(query_song_result[i+21].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+22].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+23].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_video_contrast(value);
			m_handheld_song_list[row].set_lyric(query_song_result[i+24].c_str());
			m_handheld_song_list[row].set_culture_code(query_song_result[i+25].c_str());
			m_handheld_song_list[row].set_preview_path(query_song_result[i+26].c_str());
			m_handheld_song_list[row].set_video_type(PLAY_SONG_TYPE_SELECT_SONG);

			row++;
			if (row>=HANDHELD_PAGE_SHOW_ROW_COUNT)
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

bool query_song_manager::set_handheld_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums)
{
	try
	{
		int row=0;
		int value=0;

		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			m_handheld_song_list[row].initialized_variables();
			//һ���еĸ�ֵ
			m_handheld_song_list[row].set_song_id(query_song_result[i].c_str());
			m_handheld_song_list[row].set_song_name(query_song_result[i+1].c_str());
			//ԭ�鳪������ͬ
			value = 0;
			swscanf(query_song_result[i+2].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_accompany_volume(value);
			m_handheld_song_list[row].set_karaoke_volume(value);
			m_handheld_song_list[row].set_movie_region(query_song_result[i+3].c_str());
			value = 0;
			swscanf(query_song_result[i+4].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_movie_story(value);
			m_handheld_song_list[row].set_file_format(query_song_result[i+5].c_str());
			m_handheld_song_list[row].set_local_path(query_song_result[i+6].c_str());
			m_handheld_song_list[row].set_server_path1(query_song_result[i+7].c_str());
			m_handheld_song_list[row].set_server_path2(query_song_result[i+8].c_str());
			m_handheld_song_list[row].set_server_path3(query_song_result[i+9].c_str());
			m_handheld_song_list[row].set_server_path4(query_song_result[i+10].c_str());
			m_handheld_song_list[row].set_server_path5(query_song_result[i+11].c_str());
			m_handheld_song_list[row].set_server_path6(query_song_result[i+12].c_str());
			m_handheld_song_list[row].set_song_relative_path(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+16].c_str(),L"%d",&value);
			m_handheld_song_list[row].set_video_contrast(value);
			m_handheld_song_list[row].set_culture_code(query_song_result[i+17].c_str());
			m_handheld_song_list[row].set_video_type(PLAY_MOVIE);

			row++;
			if (row>=HANDHELD_PAGE_SHOW_ROW_COUNT)
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


bool query_song_manager::set_recommend_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int nPos,bool singer_song)
{
	try
	{
		int row=0;
		int value=0;

		if (singer_song)
		{
			//�Ƿ���������֯����
			for (int i=0; i < RECOMMAND_SONG_INFO_COUNT; i++)
			{
				m_recommend_song_list[i].initialized_variables();
			}		 
		}

		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			m_recommend_song_list[row+nPos].set_song_id(query_song_result[i].c_str());
			m_recommend_song_list[row+nPos].set_accompany_sing_track(query_song_result[i+1].c_str());
			m_recommend_song_list[row+nPos].set_karaoke_track(query_song_result[i+2].c_str());
			m_recommend_song_list[row+nPos].set_guid_track(query_song_result[i+3].c_str());
			m_recommend_song_list[row+nPos].set_song_name(query_song_result[i+4].c_str());
			m_recommend_song_list[row+nPos].set_movie_name(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			m_recommend_song_list[row+nPos].set_song_sort(value);
			value = 0;
			swscanf(query_song_result[i+7].c_str(),L"%d",&value);
			m_recommend_song_list[row+nPos].set_accompany_volume(value);
			value = 0;
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			m_recommend_song_list[row+nPos].set_karaoke_volume(value);
			m_recommend_song_list[row+nPos].set_language(query_song_result[i+9].c_str());
			m_recommend_song_list[row+nPos].set_song_type(query_song_result[i+10].c_str());
			m_recommend_song_list[row+nPos].set_singer_name(query_song_result[i+11].c_str());
			m_recommend_song_list[row+nPos].set_singer_sex(query_song_result[i+12].c_str());
			m_recommend_song_list[row+nPos].set_song_version(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			m_recommend_song_list[row+nPos].set_light_control_set(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			m_recommend_song_list[row+nPos].set_audio_effect_code(value);
			m_recommend_song_list[row+nPos].set_file_format(query_song_result[i+16].c_str());
			m_recommend_song_list[row+nPos].set_local_path(query_song_result[i+17].c_str());
			m_recommend_song_list[row+nPos].set_server_path1(query_song_result[i+18].c_str());
			m_recommend_song_list[row+nPos].set_server_path2(query_song_result[i+19].c_str());
			m_recommend_song_list[row+nPos].set_server_path3(query_song_result[i+20].c_str());
			m_recommend_song_list[row+nPos].set_server_path4(query_song_result[i+21].c_str());
			m_recommend_song_list[row+nPos].set_server_path5(query_song_result[i+22].c_str());
			m_recommend_song_list[row+nPos].set_server_path6(query_song_result[i+23].c_str());
			m_recommend_song_list[row+nPos].set_song_relative_path(query_song_result[i+24].c_str());
			value = 0;
			swscanf(query_song_result[i+25].c_str(),L"%d",&value);
			m_recommend_song_list[row+nPos].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+26].c_str(),L"%d",&value);
			m_recommend_song_list[row+nPos].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+27].c_str(),L"%d",&value);
			m_recommend_song_list[row+nPos].set_video_contrast(value);
			m_recommend_song_list[row+nPos].set_lyric(query_song_result[i+28].c_str());
			m_recommend_song_list[row+nPos].set_culture_code(query_song_result[i+29].c_str());
			m_recommend_song_list[row+nPos].set_preview_path(query_song_result[i+30].c_str());
			m_recommend_song_list[row+nPos].set_video_type(PLAY_SONG_TYPE_SELECT_SONG);
			m_recommend_song_list[row+nPos].set_singer_id1(query_song_result[i+31].c_str());
			m_recommend_song_list[row+nPos].set_singer_id2(query_song_result[i+32].c_str());
			m_recommend_song_list[row+nPos].set_singer_id3(query_song_result[i+33].c_str());
			m_recommend_song_list[row+nPos].set_singer_id4(query_song_result[i+34].c_str());
			m_recommend_song_list[row+nPos].set_file_version(query_song_result[i+35].c_str());

			row++;
			if (singer_song)
			{
				if (row>=result_item_number)
				{
					break;
				}

			}

		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool query_song_manager::set_song_all_recorder_list(std::wstring query_song_result[],int result_item_number,int result_column_nums)
{
	try
	{
		int row=0;
		int value=0; 
	 
		//�Ƿ���������֯����
		for (int i=0; i < RECORDER_SHOW_PAGE_COUNT; i++)
		{
			m_recorder_song_list[i].initialized_variables();
		}		 
		 
		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			m_recorder_song_list[row].set_song_id(query_song_result[i].c_str());
			m_recorder_song_list[row].set_song_name(query_song_result[i+1].c_str());
			m_recorder_song_list[row].set_singer_name(query_song_result[i+2].c_str());
			m_recorder_song_list[row].set_recorder_video_path(query_song_result[i+3].c_str());
			m_recorder_song_list[row].set_culture_code(query_song_result[i+4].c_str());
			m_recorder_song_list[row].set_recorder_wave_path(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			m_recorder_song_list[row].set_recorder_start_time(value);
			m_recorder_song_list[row].set_recorder_datatime(query_song_result[i+7].c_str());
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			m_recorder_song_list[row].set_recorder_score(value);
			m_recorder_song_list[row].set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);

			row++;

			if (row >= RECORDER_SHOW_PAGE_COUNT)
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

bool query_song_manager::set_song_recorder_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number)
{
	try
	{
		int row=0;
		int value=0;
		int i=0;

		if (NO_PAGE==page_count)
		{
			//û�в�ѯ����������������
			song_list_exist=false;
			return true;
		}
		song_list_exist = true;

		//��ֵǰһҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=m_page_show_row_count*result_column_nums;
				}
				else
				{
					i = 0;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=2*m_page_show_row_count*result_column_nums;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = 0;
				}
				else
				{
					i=m_page_show_row_count*result_column_nums;
				}
			}
			break;
		default:
			{
				i=0;
			}
			break;
		}
		row=0;
		for (;i<result_item_number;i+=result_column_nums)
		{
			//if (cur_page_number == 1)
			//{
			//	break;
			//}
			//һ���еĸ�ֵ
			pre_page_song_list[row].set_song_id(query_song_result[i].c_str());
			pre_page_song_list[row].set_song_name(query_song_result[i+1].c_str());
			pre_page_song_list[row].set_singer_name(query_song_result[i+2].c_str());
			pre_page_song_list[row].set_recorder_video_path(query_song_result[i+3].c_str());
			pre_page_song_list[row].set_culture_code(query_song_result[i+4].c_str());
			pre_page_song_list[row].set_recorder_wave_path(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			pre_page_song_list[row].set_recorder_start_time(value);
			pre_page_song_list[row].set_recorder_datatime(query_song_result[i+7].c_str());
			pre_page_song_list[row].set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);
			value = 0;
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			pre_page_song_list[row].set_recorder_score(value);

			row++;
			if (row>=m_page_show_row_count)
			{
				break;
			}
		}

		//��ֵ��ǰҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=0;
				}
				else
				{
					i = m_page_show_row_count*result_column_nums;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=0;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = m_page_show_row_count*result_column_nums;
				}
				else
				{
					i=2*m_page_show_row_count*result_column_nums;
				}
			}
			break;
		default:
			{
				i=m_page_show_row_count*result_column_nums;
			}
			break;
		}
		row=0;
		for (;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			cur_page_song_list[row].set_song_id(query_song_result[i].c_str());
			cur_page_song_list[row].set_song_name(query_song_result[i+1].c_str());
			cur_page_song_list[row].set_singer_name(query_song_result[i+2].c_str());
			cur_page_song_list[row].set_recorder_video_path(query_song_result[i+3].c_str());
			cur_page_song_list[row].set_culture_code(query_song_result[i+4].c_str());
			cur_page_song_list[row].set_recorder_wave_path(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			cur_page_song_list[row].set_recorder_start_time(value);
			cur_page_song_list[row].set_recorder_datatime(query_song_result[i+7].c_str());
			cur_page_song_list[row].set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);
			value = 0;
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			cur_page_song_list[row].set_recorder_score(value);
			row++;
			if (row>=m_page_show_row_count)
			{
				break;
			}
		}

		//��ֵ��һҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=m_page_show_row_count*result_column_nums;
				}
				else
				{
					i = 0;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=m_page_show_row_count*result_column_nums;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = 2*m_page_show_row_count*result_column_nums;
				}
				else
				{
					i=0;
				}
			}
			break;
		default:
			{
				i=2*m_page_show_row_count*result_column_nums;
			}
			break;
		}
		row=0;
		for (;i<result_item_number;i+=result_column_nums)
		{
			//if (cur_page_number == 1 && page_count == 1)
			//{
			//	break;
			//}
			//һ���еĸ�ֵ
			next_page_song_list[row].set_song_id(query_song_result[i].c_str());
			next_page_song_list[row].set_song_name(query_song_result[i+1].c_str());
			next_page_song_list[row].set_singer_name(query_song_result[i+2].c_str());
			next_page_song_list[row].set_recorder_video_path(query_song_result[i+3].c_str());
			next_page_song_list[row].set_culture_code(query_song_result[i+4].c_str());
			next_page_song_list[row].set_recorder_wave_path(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			next_page_song_list[row].set_recorder_start_time(value);
			next_page_song_list[row].set_recorder_datatime(query_song_result[i+7].c_str());
			next_page_song_list[row].set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);
			value = 0;
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			next_page_song_list[row].set_recorder_score(value);
			row++;
			if (row>=m_page_show_row_count)
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

bool query_song_manager::set_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number)
{
	try
	{
		int row=0;
		int value=0;
		int i=0;

		if (NO_PAGE==page_count)
		{
			//û�в�ѯ����������������
			song_list_exist=false;
			return true;
		}
		song_list_exist = true;

		//��ֵǰһҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=m_page_show_row_count*result_column_nums;
				}
				else
				{
					i = 0;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=2*m_page_show_row_count*result_column_nums;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = 0;
				}
				else
				{
					i=m_page_show_row_count*result_column_nums;
				}
			}
			break;
		default:
			{
				i=0;
			}
			break;
		}
		row=0;
		for (;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			pre_page_song_list[row].set_song_id(query_song_result[i].c_str());
			pre_page_song_list[row].set_song_name(query_song_result[i+1].c_str());
			//ԭ�鳪������ͬ
			value = 0;
			swscanf(query_song_result[i+2].c_str(),L"%d",&value);
			pre_page_song_list[row].set_accompany_volume(value);
			pre_page_song_list[row].set_karaoke_volume(value);
			pre_page_song_list[row].set_movie_region(query_song_result[i+3].c_str());
			value = 0;
			swscanf(query_song_result[i+4].c_str(),L"%d",&value);
			pre_page_song_list[row].set_movie_story(value);
			pre_page_song_list[row].set_file_format(query_song_result[i+5].c_str());
			pre_page_song_list[row].set_local_path(query_song_result[i+6].c_str());
			pre_page_song_list[row].set_server_path1(query_song_result[i+7].c_str());
			pre_page_song_list[row].set_server_path2(query_song_result[i+8].c_str());
			pre_page_song_list[row].set_server_path3(query_song_result[i+9].c_str());
			pre_page_song_list[row].set_server_path4(query_song_result[i+10].c_str());
			pre_page_song_list[row].set_server_path5(query_song_result[i+11].c_str());
			pre_page_song_list[row].set_server_path6(query_song_result[i+12].c_str());
			pre_page_song_list[row].set_song_relative_path(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			pre_page_song_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			pre_page_song_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+16].c_str(),L"%d",&value);
			pre_page_song_list[row].set_video_contrast(value);
			pre_page_song_list[row].set_culture_code(query_song_result[i+17].c_str());
			pre_page_song_list[row].set_video_type(PLAY_MOVIE);

			row++;
			if (row>=m_page_show_row_count)
			{
				break;
			}
		}

		//��ֵ��ǰҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=0;
				}
				else
				{
					i = m_page_show_row_count*result_column_nums;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=0;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = m_page_show_row_count*result_column_nums;
				}
				else
				{
					i=2*m_page_show_row_count*result_column_nums;
				}
			}
			break;
		default:
			{
				i=m_page_show_row_count*result_column_nums;
			}
			break;
		}
		row=0;
		for (;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			cur_page_song_list[row].set_song_id(query_song_result[i].c_str());
			cur_page_song_list[row].set_song_name(query_song_result[i+1].c_str());
			//ԭ�鳪������ͬ
			value = 0;
			swscanf(query_song_result[i+2].c_str(),L"%d",&value);
			cur_page_song_list[row].set_accompany_volume(value);
			cur_page_song_list[row].set_karaoke_volume(value);
			cur_page_song_list[row].set_movie_region(query_song_result[i+3].c_str());
			value = 0;
			swscanf(query_song_result[i+4].c_str(),L"%d",&value);
			cur_page_song_list[row].set_movie_story(value);
			cur_page_song_list[row].set_file_format(query_song_result[i+5].c_str());
			cur_page_song_list[row].set_local_path(query_song_result[i+6].c_str());
			cur_page_song_list[row].set_server_path1(query_song_result[i+7].c_str());
			cur_page_song_list[row].set_server_path2(query_song_result[i+8].c_str());
			cur_page_song_list[row].set_server_path3(query_song_result[i+9].c_str());
			cur_page_song_list[row].set_server_path4(query_song_result[i+10].c_str());
			cur_page_song_list[row].set_server_path5(query_song_result[i+11].c_str());
			cur_page_song_list[row].set_server_path6(query_song_result[i+12].c_str());
			cur_page_song_list[row].set_song_relative_path(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			cur_page_song_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			cur_page_song_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+16].c_str(),L"%d",&value);
			cur_page_song_list[row].set_video_contrast(value);
			cur_page_song_list[row].set_culture_code(query_song_result[i+17].c_str());
			cur_page_song_list[row].set_video_type(PLAY_MOVIE);

			row++;
			if (row>=m_page_show_row_count)
			{
				break;
			}
		}

		//��ֵ��һҳ������
		switch(page_count)
		{
		case ONE_PAGE:
			{
				i=0;
			}
			break;
		case TWO_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=m_page_show_row_count*result_column_nums;
				}
				else
				{
					i = 0;
				}
			}
			break;
		case THREE_PAGE:
			{
				if (ONE_PAGE==cur_page_number)
				{
					i=m_page_show_row_count*result_column_nums;
				}
				else if(TWO_PAGE==cur_page_number)
				{
					i = 2*m_page_show_row_count*result_column_nums;
				}
				else
				{
					i=0;
				}
			}
			break;
		default:
			{
				i=2*m_page_show_row_count*result_column_nums;
			}
			break;
		}
		row=0;
		for (;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			next_page_song_list[row].set_song_id(query_song_result[i].c_str());
			next_page_song_list[row].set_song_name(query_song_result[i+1].c_str());
			//ԭ�鳪������ͬ
			value = 0;
			swscanf(query_song_result[i+2].c_str(),L"%d",&value);
			next_page_song_list[row].set_accompany_volume(value);
			next_page_song_list[row].set_karaoke_volume(value);
			next_page_song_list[row].set_movie_region(query_song_result[i+3].c_str());
			value = 0;
			swscanf(query_song_result[i+4].c_str(),L"%d",&value);
			next_page_song_list[row].set_movie_story(value);
			next_page_song_list[row].set_file_format(query_song_result[i+5].c_str());
			next_page_song_list[row].set_local_path(query_song_result[i+6].c_str());
			next_page_song_list[row].set_server_path1(query_song_result[i+7].c_str());
			next_page_song_list[row].set_server_path2(query_song_result[i+8].c_str());
			next_page_song_list[row].set_server_path3(query_song_result[i+9].c_str());
			next_page_song_list[row].set_server_path4(query_song_result[i+10].c_str());
			next_page_song_list[row].set_server_path5(query_song_result[i+11].c_str());
			next_page_song_list[row].set_server_path6(query_song_result[i+12].c_str());
			next_page_song_list[row].set_song_relative_path(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			next_page_song_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			next_page_song_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+16].c_str(),L"%d",&value);
			next_page_song_list[row].set_video_contrast(value);
			next_page_song_list[row].set_culture_code(query_song_result[i+17].c_str());
			next_page_song_list[row].set_video_type(PLAY_MOVIE);

			row++;
			if (row>=m_page_show_row_count)
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

bool query_song_manager::set_syn_movie_list(std::wstring query_song_result[],int result_item_number,int result_column_nums)
{
	try
	{
		int row=0;
		int value=0;

		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			m_movie_list[row].set_song_id(query_song_result[i].c_str());
			m_movie_list[row].set_song_name(query_song_result[i+1].c_str());
			//ԭ�鳪������ͬ
			value = 0;
			swscanf(query_song_result[i+2].c_str(),L"%d",&value);
			m_movie_list[row].set_accompany_volume(value);
			m_movie_list[row].set_karaoke_volume(value);
			m_movie_list[row].set_movie_region(query_song_result[i+3].c_str());
			value = 0;
			swscanf(query_song_result[i+4].c_str(),L"%d",&value);
			m_movie_list[row].set_movie_story(value);
			m_movie_list[row].set_file_format(query_song_result[i+5].c_str());
			m_movie_list[row].set_local_path(query_song_result[i+6].c_str());
			m_movie_list[row].set_server_path1(query_song_result[i+7].c_str());
			m_movie_list[row].set_server_path2(query_song_result[i+8].c_str());
			m_movie_list[row].set_server_path3(query_song_result[i+9].c_str());
			m_movie_list[row].set_server_path4(query_song_result[i+10].c_str());
			m_movie_list[row].set_server_path5(query_song_result[i+11].c_str());
			m_movie_list[row].set_server_path6(query_song_result[i+12].c_str());
			m_movie_list[row].set_song_relative_path(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			m_movie_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			m_movie_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+16].c_str(),L"%d",&value);
			m_movie_list[row].set_video_contrast(value);
			m_movie_list[row].set_culture_code(query_song_result[i+17].c_str());
			m_movie_list[row].set_video_type(PLAY_MOVIE);

			row++;
			if (row>=SELECT_SONG_MAX_COUNT)
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
bool query_song_manager::make_music_enjoy_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager, ST_MUSIC_ENJOY *pSme, int count)
{
	bool result = false;  
	TCHAR song_temp[1024];
	int play_number;
	TCHAR playing_id[256];
	song_info playing_info;

	if (count == 0)
	{
		song_list_xml += L"<song_list></song_list>";
		return false;
	}

	//�õ����ڲ��ŵĸ���
	result = video_manager.get_playing_video(playing_info);
	if (result)
	{
		//�������ڲ��ŵ���Ƶ
		playing_info.get_song_id(playing_id);
	}

	song_list_xml += L"<song_list>";
	for (int i = 0; i < count; i ++)
	{
		memset(song_temp,0x0,sizeof(song_temp));

		if (_tcscmp(pSme[i].song_id, L"") == 0)
		{
			continue;
		}

		//���ڲ��ŵĸ���
		if (_tcscmp(pSme[i].song_id, playing_id) == 0 && _tcscmp(pSme[i].song_id, L"") != 0)
		{
			wsprintf(song_temp, L"<item song_id=\"%s\" song_name=\"%s[%s]\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
				pSme[i].song_id, pSme[i].song_name, g_all_language[5].c_str(), pSme[i].singer_name, pSme[i].song_top, pSme[i].song_type, m_playing_song_color.c_str()); //ƴxml
		}else{
			result = video_manager.query_select_song_by_id(pSme[i].song_id, play_number);
			if (result)
			{
				wsprintf(song_temp, L"<item song_id=\"%s\" song_name=\"%s[%s%d]\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
					pSme[i].song_id, pSme[i].song_name, g_all_language[4].c_str(), play_number, pSme[i].singer_name, pSme[i].song_top, pSme[i].song_type, m_select_song_color.c_str()); //ƴxml
			}else{
				wsprintf(song_temp, L"<item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
					pSme[i].song_id, pSme[i].song_name, pSme[i].singer_name, pSme[i].song_top, pSme[i].song_type, m_default_song_color.c_str()); //ƴxml
			}
		}

		song_list_xml += song_temp;
	}
	song_list_xml += L"</song_list>";
	return true;
}
bool query_song_manager::make_song_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_show_row_count,FLASH_SONG_SHOW_MODE song_show_mode,int page_index)
{
	try
	{
		song_info playing_song_info;
		TCHAR playing_song_id[256];
		TCHAR song_show_info[2048];
		bool result=false;
		int picture_number=0;

		memset(playing_song_id,0x0,sizeof(playing_song_id));

		if (!song_list_exist)
		{
			return true;
		}
		//����ҳ�������Ը�����ʾ��ʽ����������Ϊ��Щҳ��ֻ���б�ʽ
		switch(page_index)
		{
		case page_title:    //�п�Ƭ��ҳ��
		case page_lyric:
		case page_theme:
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
		case page_write:  //��д���
		case page_hdmi:       //����ר��
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

		//�õ����ڲ��ŵĸ���
		result = video_manager.get_playing_video(playing_song_info);
		if (result)
		{
			//�������ڲ��ŵ���Ƶ
			playing_song_info.get_song_id(playing_song_id);
		}

		//����0-132���漴��
		picture_number = rand() / (RAND_MAX / 133 + 1);

		//��֯ǰһҳ
		song_list_xml += L"<pre_list>";
		for (int i=0;i<page_show_row_count;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));

			result = make_song_list_one_xml(pre_page_song_list[i],i+1,video_manager,playing_song_id,song_show_info,song_show_mode,picture_number,page_index);
			if (result)
			{
				song_list_xml += song_show_info;
				picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
			}
		}

		song_list_xml += L"</pre_list><cur_list>";
		//��֯��ǰҳ
		for (int i=0;i<page_show_row_count;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));

			result = make_song_list_one_xml(cur_page_song_list[i],i+1,video_manager,playing_song_id,song_show_info,song_show_mode,picture_number,page_index);
			if (result)
			{
				song_list_xml += song_show_info;
				picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
			}
		}

		song_list_xml += L"</cur_list><next_list>";
		//��һҳ
		for (int i=0;i<page_show_row_count;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));

			result = make_song_list_one_xml(next_page_song_list[i],i+1,video_manager,playing_song_id,song_show_info,song_show_mode,picture_number,page_index);
			if (result)
			{
				song_list_xml += song_show_info;
				picture_number+=2;  //���ڸ���ͼƬ�͸���ͼƬ��ռһ�����
			}
		}
		song_list_xml += L"</next_list>";

		return true;
	}
	catch (...)
	{
	}
	return false;
}

bool query_song_manager::make_song_list_one_xml(song_info &song_information,int song_number,video_play_manager &video_manager,TCHAR *playing_song_number,TCHAR *song_show_info,FLASH_SONG_SHOW_MODE song_show_mode,int picture_number,int page_index)
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
		TCHAR movie_name[256];
		TCHAR singer_sex[256];	
		TCHAR sex_image_path[256];
		TCHAR synthesis_text[256];
		bool result=false;
		int play_number=0;
		int song_sort=0;
		TCHAR tmp_string[256];
		decrypt_picture decrypt_singer_song_picture;
		TCHAR *split_symbol=NULL;
		memset(synthesis_text,0x0,sizeof(synthesis_text));
		TCHAR wave_path[256];
		int recorder_score=0;
		TCHAR down_update[256];
		TCHAR song_type[256];
		TCHAR show_mark_text[256];


		if ((NULL==playing_song_number)||(NULL==song_show_info))
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
		memset(tmp_string,0x0,sizeof(tmp_string));
		memset(singer_sex,0x0,sizeof(singer_sex));
		memset(sex_image_path,0x0,sizeof(sex_image_path));
		memset(movie_name,0x0,sizeof(movie_name));
		memset(wave_path,0x0,sizeof(wave_path));
		memset(song_type, 0x0, sizeof(song_type));
		memset(show_mark_text,0x0,sizeof(show_mark_text));
		 

		song_information.get_song_language(language);
		song_information.get_song_name(song_name);
		if (page_opera==page_index)
		{
			//Ϸ��ҳ�����⴦����ʾ������
			TCHAR *split_symbol = _tcsrchr(song_name,'-');
			if (split_symbol)
			{
				split_symbol[0] = '\0';
			}
			//�õ�����
			memset(movie_name,0x0,sizeof(movie_name));
			song_information.get_moive_name(movie_name);
			if (0!=_tcscmp(movie_name,L""))
			{
				//��ӳ���
				swprintf(song_name+_tcslen(song_name),L"-%s",movie_name);
			}
		}
		int nVersion = 0;
		song_information.get_singer_name(singer_name);
		song_information.get_song_id(song_id);
		song_information.get_song_version(song_version,nVersion);

		//2011-07-26 modify
		if (page_movie_song==page_index || page_new_theme_song==page_index)
		{
			//Ӱ�ӽ�������ʾ��Ӱ����
			memset(movie_name,0x0,sizeof(movie_name));
			song_information.get_moive_name(movie_name);
			//if (m_no_moive_name_show_lyric&&(0==_tcscmp(movie_name,L"")))
			//{
			//	//��Ӱ�����ǿ���ʾ���
			//	song_information.get_lyric(movie_name);
			//	//���������ʾ24������ֹԽ��
			//	movie_name[24] = '\0';
			//}
		}
		else  if (m_no_moive_name_show_lyric)
		{
			//����ҳ�棬��ʾ���
			memset(movie_name,0x0,sizeof(movie_name));
			//��ʾ���
			//if (page_singer_song==page_index)
			//{
			//	song_information.get_lyric(tmp_string);
			//	//���������ʾ12������ֹԽ��
			//	if (tmp_string[0]<0xff)
			//	{
			//		//Ӣ��
			//		tmp_string[28] = '\0';
			//		split_symbol = _tcsrchr(tmp_string,' ');
			//		if (split_symbol)
			//		{
			//			split_symbol[0] = '\0';
			//		}
			//	}
			//	else
			//	{
			//		//������
			//		tmp_string[14] = '\0';
			//	}
			//	if (_tcslen(tmp_string)>2)
			//	{
			//		swprintf(movie_name,L"                                                  %s...",tmp_string);
			//	}
			//}
			//else
			//{
			//	song_information.get_lyric(tmp_string);
			//	//���������ʾ12������ֹԽ��
			//	if (tmp_string[0]<0xff)
			//	{
			//		//Ӣ��
			//		tmp_string[24] = '\0';
			//		split_symbol = _tcsrchr(tmp_string,' ');
			//		if (split_symbol)
			//		{
			//			split_symbol[0] = '\0';
			//		}
			//	}
			//	else
			//	{
			//		//������
			//		tmp_string[13] = '\0';
			//	}
			//	if (_tcslen(tmp_string)>2)
			//	{
			//		swprintf(movie_name,L"                                  %s...",tmp_string);
			//	}
			//}
		} 

		//�õ������ĸ��塢�׳������š����pk
		song_sort = song_information.get_song_sort();
		recorder_score = song_information.get_recorder_score();
		 
		//1  10  100 
		int first_song=0; //song_sort&0x01;    //�׳�
		int hot_song=0;   //song_sort&0x02;    //����
		int maiba_pk=0;	  //song_sort&0x04;   //���pk
		int video_hd = 0;

		first_song = song_sort&0x01;
		hot_song = (song_sort>>1)&0x01;
		maiba_pk = (song_sort>>2)&0x01;

		//�õ���ǰ�Ƿ������ء�����
		song_information.get_local_path(down_update);

		int is_down=0;    // 1 ����
		int is_update=0;  // 10 ����
		/*
		int down_song=_ttoi(down_update);
		is_down = down_song&0x01;
		is_update = (down_song>>1)&0x01;
		*/

		if (_tcscmp(down_update, L"1") == 0)
		{
			is_down = 1;
			is_update = 0;
		}else if (_tcscmp(down_update, L"2") == 0)
		{
			is_down = 0;
			is_update = 1;
		}else{
			is_down = 0;
			is_update = 0;
		}
 
		if (NULL != _tcsstr(song_name,L"����"))
		{
			video_hd = 1;
		}

#ifndef SAN_JI_SMART_HOME_SYSTEM
		//ͨ�������Ա�õ�����ͼƬ
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
		//�ж��Ƿ���¼��ҳ��
		//if (page_recording == page_index)
		//{
		//	//�õ���ǰ�洢��·��
		//	song_information.get_wave_path(wave_path);
		//	if (!PathFileExists(wave_path))   
		//	{ 
		//		_tcscpy(synthesis_text,g_all_language[114].c_str());
		//	}
		//	else
		//	{ 
		//		_tcscpy(synthesis_text,L"");
		//	}
		//}

		//����ǿ�Ƭ��ʽ����Ҫ���ܸ��Ǻ͸���ͼƬ
		/*
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
			*/
		
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
		}

		if ((0!=_tcscmp(playing_song_number,L""))&&(0==_tcscmp(playing_song_number,song_id)))
		{
			//��������ڲ��ŵĸ���
			if (SONG_SHOW_MODE_LIST==song_show_mode)
			{
				//�б�ʽ
				swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s]\" subtitle_txt=\"%s\" singer_txt=\"%s\" color=\"%s\" image_path=\"%s\" song_sort=\"%d\" sex_image=\"\"  synthesis_text=\"%s\" video_type=\"%d\" hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" is_down=\"%d\" is_update=\"%d\" recorder_score=\"%d\"/>",      \
					language,song_version,song_name,g_all_language[5].c_str(),movie_name,singer_name,m_playing_song_color.c_str(),singer_image_path,song_sort,/*sex_image_path,*/synthesis_text,video_hd,hot_song,first_song,maiba_pk,is_down,is_update,recorder_score);
			}
			else
			{
				//��Ƭ��ʽ
				swprintf(song_show_info,L"<item lang_txt=\"%s\" song_version=\"%s\" song_number=\"%d\" song_txt=\"%s[%s]\" singer_txt=\"%s\" color=\"%s\" singer_image_path=\"%s\" song_image_path=\"%s\" synthesis_text=\"%s\" video_type=\"%d\" hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" is_down=\"%d\" is_update=\"%d\" recorder_score=\"%d\"/>",    \
					language,song_version,song_number,song_name,g_all_language[5].c_str(),singer_name,m_playing_song_color.c_str(),singer_image_path,song_image_path,synthesis_text,video_hd,hot_song,first_song,maiba_pk,is_down,is_update, recorder_score);
			}
		}
		else
		{
			result = video_manager.query_select_song_by_id(song_id,play_number);

			//�õ���ǰ�ı�ʾ
			memset(show_mark_text,0x0,sizeof(show_mark_text));

			if (-1 == play_number)
			{
				memset(show_mark_text,0x0,sizeof(show_mark_text));
				_tcscpy(show_mark_text,g_all_language[123].c_str());
			}
			else if (-2 == play_number)
			{
				memset(show_mark_text,0x0,sizeof(show_mark_text));
				_tcscpy(show_mark_text,g_all_language[124].c_str());
			}
			else
			{
				swprintf(show_mark_text,L"%s%d",g_all_language[4].c_str(),play_number);
			}

			if (result&&(0!=_tcscmp(song_name,L"")))
			{
				//�Ѿ���ѡ��
				if (SONG_SHOW_MODE_LIST==song_show_mode)
				{
					//�б�ʽ
					swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s]\" subtitle_txt=\"%s\" singer_txt=\"%s\" color=\"%s\" image_path=\"%s\" song_sort=\"%d\" sex_image=\"\" synthesis_text=\"%s\" video_type=\"%d\" hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" is_down=\"%d\" is_update=\"%d\"  recorder_score=\"%d\"/>",     \
						language,song_version,song_name,show_mark_text,movie_name,singer_name,m_select_song_color.c_str(),singer_image_path,song_sort,/*sex_image_path,*/synthesis_text,video_hd,hot_song,first_song,maiba_pk,is_down,is_update,recorder_score);
				}
				else
				{
					//��Ƭ��ʽ
					swprintf(song_show_info,L"<item lang_txt=\"%s\" song_version=\"%s\" song_number=\"%d\" song_txt=\"%s[%s]\" singer_txt=\"%s\" color=\"%s\" singer_image_path=\"%s\" song_image_path=\"%s\" synthesis_text=\"%s\" video_type=\"%d\" hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" is_down=\"%d\" is_update=\"%d\" recorder_score=\"%d\" />",    \
						language,song_version,song_number,song_name,show_mark_text,singer_name,m_select_song_color.c_str(),singer_image_path,song_image_path,synthesis_text,video_hd,hot_song,first_song,maiba_pk,is_down,is_update,recorder_score);
				}
			}
			else if (0!=_tcscmp(song_name,L""))
			{
				if (SONG_SHOW_MODE_LIST==song_show_mode)
				{
					//�б�ʽ
					swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s\" subtitle_txt=\"%s\" singer_txt=\"%s\" color=\"%s\" image_path=\"%s\" song_sort=\"%d\" sex_image=\"\" synthesis_text=\"%s\" video_type=\"%d\" hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" is_down=\"%d\" is_update=\"%d\"  recorder_score=\"%d\"/>",     \
						language,song_version,song_name,movie_name,singer_name,m_default_song_color.c_str(),singer_image_path,song_sort,/*sex_image_path,*/synthesis_text,video_hd,hot_song,first_song,maiba_pk,is_down,is_update,recorder_score);
				}
				else
				{
					//��Ƭ��ʽ
					swprintf(song_show_info,L"<item lang_txt=\"%s\" song_version=\"%s\" song_number=\"%d\" song_txt=\"%s\" singer_txt=\"%s\" color=\"%s\" singer_image_path=\"%s\" song_image_path=\"%s\" synthesis_text=\"%s\" video_type=\"%d\" hot=\"%d\" first_song=\"%d\" maiba_pk=\"%d\" is_down=\"%d\" is_update=\"%d\"  recorder_score=\"%d\"/>",    \
						language,song_version,song_number,song_name,singer_name,m_default_song_color.c_str(),singer_image_path,song_image_path,synthesis_text,video_hd,hot_song,first_song,maiba_pk,is_down,is_update,recorder_score);
				}
			}
		}
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}


bool query_song_manager::make_recorder_song_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_index)
{
	try
	{

		song_info playing_song_info;
		TCHAR playing_song_id[256];
		TCHAR song_show_info[2048];
		bool result=false;
		int picture_number=0;
		TCHAR song_id[128];

		memset(playing_song_id,0x0,sizeof(playing_song_id));

	
		//�õ����ڲ��ŵĸ���
		result = video_manager.get_playing_video(playing_song_info);
		if (result)
		{
			//�������ڲ��ŵ���Ƶ
			playing_song_info.get_song_id(playing_song_id);
		}

		//����0-132���漴��
		picture_number = rand() / (RAND_MAX / 133 + 1);

		//��֯ǰһҳ
		song_list_xml += L"<pre_list>";
		 

		song_list_xml += L"</pre_list><cur_list>";
		//��֯��ǰҳ
		for (int i=0;i<RECORDER_SHOW_PAGE_COUNT;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));
			memset(song_id,0x0,sizeof(song_id));
			m_recorder_song_list[i].get_song_id(song_id);

			if (0 == _tcscmp(song_id,L""))
			{
				break;
			}

			result = make_song_list_one_xml(m_recorder_song_list[i],i+1,video_manager,playing_song_id,song_show_info,SONG_SHOW_MODE_LIST,picture_number,page_index);
			if (result)
			{
				song_list_xml += song_show_info;
				picture_number++;
			} 
		}

		song_list_xml += L"</cur_list><next_list>";
		 
		song_list_xml += L"</next_list>";

		return true; 
	}
	catch (...)
	{

	}
	return false;
}

bool query_song_manager::make_recommend_song_list(std::wstring &song_list_xml,video_play_manager &video_manager)
{
	try
	{
		song_info playing_song_info;
		TCHAR playing_song_id[256];
		TCHAR song_show_info[1024];
		TCHAR song_name[64];
		TCHAR singer_name[256];
		TCHAR song_id[256];
		TCHAR song_list_id[256];
		bool result = false;
		int play_number=0;

		memset(playing_song_id,0x0,sizeof(playing_song_id));

		//�õ����ڲ��ŵĸ���
		result = video_manager.get_playing_video(playing_song_info);
		if (result)
		{
			//�������ڲ��ŵ���Ƶ
			playing_song_info.get_song_id(playing_song_id);
		}

		song_list_xml += L"<enjoy_list>";

		for (int i=0;i<RECOMMAND_SONG_INFO_COUNT;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));
			memset(song_name,0x0,sizeof(song_name));
			memset(singer_name,0x0,sizeof(singer_name));
			memset(song_id,0x0,sizeof(song_id));
			memset(song_list_id,0x0,sizeof(song_list_id));

			m_recommend_song_list[i].get_song_name(song_name);
			m_recommend_song_list[i].get_singer_name(singer_name);
			m_recommend_song_list[i].get_song_id(song_list_id);

			if (0!=_tcscmp(song_name,L""))
			{

				if ((0!=_tcscmp(playing_song_id,L""))&&(0==_tcscmp(playing_song_id,song_list_id)))
				{
					//��������ڲ��ŵĸ���
					swprintf(song_show_info,L"<item song_id=\"%s\"  txt=\"%s\" singer_txt=\"%s\"  color=\"%s\" />",song_list_id,song_name,singer_name,m_default_song_color.c_str());
				}
				else
				{
					result = video_manager.query_select_song_by_id(song_list_id,play_number);
					//�Ѿ���ѡ��
					if (result)
					{
						swprintf(song_show_info,L"<item song_id=\"%s\" txt=\"%s\" singer_txt=\"%s\"  color=\"%s\" />",song_list_id,song_name,singer_name,m_select_song_color.c_str());
					}
					else
					{
						swprintf(song_show_info,L"<item song_id=\"%s\" txt=\"%s\" singer_txt=\"%s\"  color=\"%s\" />",song_list_id,song_name,singer_name,m_default_song_color.c_str());
					}
				}

				song_list_xml += song_show_info;
			}
		}

		song_list_xml += L"</enjoy_list>";

		return true;
	}
	catch (...)
	{

	}
	return false;
}

/*
�ӿ�����:listsong
�ӿڲ���:<data>
<list>
<item txt="��������1"/>
<item txt="��������1"/>
<item txt="��������1"/>
<item txt="��������1"/>
</list>
</data>
*/
bool query_song_manager::make_test_song_list_xml(std::wstring &song_list_xml)
{
	try
	{
		TCHAR song_show_info[1024];
		TCHAR song_name[64];

		song_list_xml += L"<data><list>";

		for (int i=0;i<TEST_PAGE_SHOW_ROW_COUNT;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));
			memset(song_name,0x0,sizeof(song_name));
			
			test_page_song_list[i].get_song_name(song_name);
			
			if (0!=_tcscmp(song_name,L""))
			{
				swprintf(song_show_info,L"<item txt=\"%s\"/>",song_name);
				song_list_xml += song_show_info;
			}
		}

		song_list_xml += L"</list></data>";

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}


bool query_song_manager::make_movie_list_xml(std::wstring &song_list_xml,video_play_manager &video_manager,int page_show_row_count)
{
	try
	{
		TCHAR song_show_info[512];
		TCHAR movie_name[64];
		TCHAR movie_region[16];
		TCHAR movie_id[128];
		TCHAR movie_story[256];
		bool result=false;
		int play_number=0;
		song_info playing_movie_info;
		TCHAR playing_movie_id[256];

		if (!song_list_exist)
		{
			return true;
		}
		memset(playing_movie_id,0x0,sizeof(playing_movie_id));
		//�õ����ڲ��ŵĸ���
		result = video_manager.get_playing_video(playing_movie_info);
		if (result)
		{
			//�������ڲ��ŵ���Ƶ
			playing_movie_info.get_song_id(playing_movie_id);
		}

		//��֯ǰһҳ
		song_list_xml += L"<pre_list>";
		for (int i=0;i<m_page_show_row_count;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));
			memset(movie_name,0x0,sizeof(movie_name));
			memset(movie_region,0x0,sizeof(movie_region));
			memset(movie_id,0x0,sizeof(movie_id));
			memset(movie_story,0x0,sizeof(movie_story));

			pre_page_song_list[i].get_song_id(movie_id);
			pre_page_song_list[i].get_song_name(movie_name);
			pre_page_song_list[i].get_movie_region(movie_region);
			pre_page_song_list[i].get_movie_story(movie_story);
			
			if ((0!=_tcscmp(playing_movie_id,L""))&&(0==_tcscmp(playing_movie_id,movie_id)))
			{
				//��������ڲ��ŵĸ���
				swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,g_all_language[5].c_str(),m_playing_song_color.c_str());
			}
			else
			{
				result = video_manager.query_select_song_by_id(movie_id,play_number);
				if (result)
				{
					//�Ѿ���ѡ��
					if (0!=_tcscmp(movie_name,L""))
					{
						swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s%d]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,g_all_language[4].c_str(),play_number,m_select_song_color.c_str());
					}
				}
				else
				{
					if (0!=_tcscmp(movie_name,L""))
					{
						swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,m_default_song_color.c_str());
					}
				}
			}

			song_list_xml += song_show_info;
		}

		song_list_xml += L"</pre_list><cur_list>";
		//��֯��ǰҳ
		for (int i=0;i<m_page_show_row_count;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));
			memset(movie_name,0x0,sizeof(movie_name));
			memset(movie_region,0x0,sizeof(movie_region));
			memset(movie_id,0x0,sizeof(movie_id));
			memset(movie_story,0x0,sizeof(movie_story));

			cur_page_song_list[i].get_song_id(movie_id);
			cur_page_song_list[i].get_song_name(movie_name);
			cur_page_song_list[i].get_movie_region(movie_region);
			cur_page_song_list[i].get_movie_story(movie_story);


			if ((0!=_tcscmp(playing_movie_id,L""))&&(0==_tcscmp(playing_movie_id,movie_id)))
			{
				//��������ڲ��ŵĸ���
				swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,g_all_language[5].c_str(),m_playing_song_color.c_str());
			}
			else
			{
				result = video_manager.query_select_song_by_id(movie_id,play_number);
				if (result)
				{
					//�Ѿ���ѡ��
					if (0!=_tcscmp(movie_name,L""))
					{
						swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s%d]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,g_all_language[4].c_str(),play_number,m_select_song_color.c_str());
					}
				}
				else
				{
					if (0!=_tcscmp(movie_name,L""))
					{
						swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,m_default_song_color.c_str());
					}
				}
			}

			song_list_xml += song_show_info;
		}

		song_list_xml += L"</cur_list><next_list>";
		//��һҳ
		for (int i=0;i<m_page_show_row_count;i++)
		{
			memset(song_show_info,0x0,sizeof(song_show_info));
			memset(movie_name,0x0,sizeof(movie_name));
			memset(movie_region,0x0,sizeof(movie_region));
			memset(movie_id,0x0,sizeof(movie_id));
			memset(movie_story,0x0,sizeof(movie_story));

			next_page_song_list[i].get_song_id(movie_id);
			next_page_song_list[i].get_song_name(movie_name);
			next_page_song_list[i].get_movie_region(movie_region);
			next_page_song_list[i].get_movie_story(movie_story);
			

			if ((0!=_tcscmp(playing_movie_id,L""))&&(0==_tcscmp(playing_movie_id,movie_id)))
			{
				//��������ڲ��ŵĸ���
				swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,g_all_language[5].c_str(),m_playing_song_color.c_str());
			}
			else
			{
				result = video_manager.query_select_song_by_id(movie_id,play_number);
				if (result)
				{
					//�Ѿ���ѡ��
					if (0!=_tcscmp(movie_name,L""))
					{
						swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s[%s%d]\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,g_all_language[4].c_str(),play_number,m_select_song_color.c_str());
					}
				}
				else
				{
					if (0!=_tcscmp(movie_name,L""))
					{
						swprintf(song_show_info,L"<item lang_txt=\"%s\" edition_txt=\"%s\" song_txt=\"%s\" singer_txt=\"\" color=\"%s\" image_path=\"\" />",movie_region,movie_story,movie_name,m_default_song_color.c_str());
					}
				}
			}

			song_list_xml += song_show_info;
		}
		song_list_xml += L"</next_list>";

		return true;
	}
	catch (...)
	{

	}
	return false;
}
bool query_song_manager::get_recorder_song_info(int song_suffix,song_info &song_infomation){
	try
	{
		TCHAR song_name[1024];
		bool result=false;

		memset(song_name,0x0,sizeof(song_name));

		if (song_suffix > RECORDER_SHOW_PAGE_COUNT)
		{
			return false;
		}

		memcpy(&song_infomation,&m_recorder_song_list[song_suffix],sizeof(m_recorder_song_list[song_suffix]));
		
		return true;
	}
	catch (...)
	{

	}

	return false;
}
bool query_song_manager::get_recorder_song_info(TCHAR* song_number,song_info &song_infomation)
{
	try
	{
		TCHAR song_name[1024];
		TCHAR song_id[128];
		bool result=false;

		memset(song_name,0x0,sizeof(song_name));
		

		for (int i=0; i< RECORDER_SHOW_PAGE_COUNT;i++)
		{
			memset(song_id,0x0,sizeof(song_id));

			//�õ�id
			m_recorder_song_list[i].get_song_id(song_id);
			if (0 == _tcscmp(song_number,song_id))
			{
				memcpy(&song_infomation,&m_recorder_song_list[i],sizeof(m_recorder_song_list[i]));
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

bool query_song_manager::get_song_info(int song_suffix,song_info &song_infomation)
{
	TCHAR song_name[1024];
	bool result=false;

	memset(song_name,0x0,sizeof(song_name));

	if((song_suffix>=m_page_show_row_count)||(song_suffix<0))
		return false;
	//�õ�������Ϣ
	song_infomation = cur_page_song_list[song_suffix];
	//ͨ���������������������Ƿ����
	result= song_infomation.get_song_name(song_name);
	if (!result || (0==_tcscmp(song_name,L"")))
	{
		return false;
	}

	return true;
}

bool query_song_manager::get_handheld_song_info(int song_suffix,song_info &song_infomation)
{
	TCHAR song_name[1024];
	bool result=false;

	memset(song_name,0x0,sizeof(song_name));

	if((song_suffix>=HANDHELD_PAGE_SHOW_ROW_COUNT)||(song_suffix<0))
		return false;
	//�õ�������Ϣ
	song_infomation = m_handheld_song_list[song_suffix];
	//ͨ���������������������Ƿ����
	result= song_infomation.get_song_name(song_name);
	if (!result || (0==_tcscmp(song_name,L"")))
	{
		return false;
	}

	return true;
}

bool query_song_manager::get_test_or_select_song_info(int song_suffix,song_info &song_infomation,bool test_song)
{
	if(test_song && ((song_suffix>=TEST_PAGE_SHOW_ROW_COUNT)||(song_suffix<0)))
	{
		return false;
	}
	else if (!test_song && ((song_suffix>=SELECT_SONG_MAX_COUNT)||(song_suffix<0)))
	{
		return false;
	}
	song_infomation = test_page_song_list[song_suffix];

	return true;
}

bool query_song_manager::get_select_song_info(TCHAR *song_number,song_info &song_infomation)
{
	TCHAR song_ID[256];
	song_info select_song_info;
	bool result=false;

	for(int i=0;i<SELECT_SONG_MAX_COUNT;i++)
	{
		memset(song_ID,0x0,sizeof(song_ID));
		select_song_info.initialized_variables();

		//�õ�������Ϣ
		select_song_info = test_page_song_list[i];
		//�õ�����ID
		result = select_song_info.get_song_id(song_ID);
		if (result&&(0==_tcscmp(song_ID,song_number)))
		{
			//���������ͬ��ѡ��
			song_infomation = select_song_info;
			return true;
		}
	}

	return false;	
}

bool query_song_manager::get_select_movie_info(TCHAR *song_number,song_info &song_infomation)
{
	TCHAR movie_id[256];
	song_info select_song_info;
	bool result=false;

	for(int i=0;i<SELECT_SONG_MAX_COUNT;i++)
	{
		memset(movie_id,0x0,sizeof(movie_id));
		select_song_info.initialized_variables();

		//�õ�������Ϣ
		select_song_info = m_movie_list[i];
		//�õ�����ID
		result = select_song_info.get_song_id(movie_id);
		if (result&&(0==_tcscmp(movie_id,song_number)))
		{
			//���������ͬ��ѡ��
			song_infomation = select_song_info;

			return true;
		}
	}

	return false;	
}

bool query_song_manager::test_song_priority(int number)
{
	try
	{
		song_info test_song_info;

		//����
		test_song_info = test_page_song_list[number];
		for (int i=number;i>0;i--)
		{
			test_page_song_list[i] = test_page_song_list[i-1];
		}
		test_page_song_list[0] = test_song_info;

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool query_song_manager::set_listen_recommend_song_list(std::wstring query_song_result[],int result_item_number,int result_column_nums, song_info *songinfo)
{
	try
	{
		int row=0;
		int value=0;

		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			songinfo->set_song_id(query_song_result[i].c_str());
			songinfo->set_accompany_sing_track(query_song_result[i+1].c_str());
			songinfo->set_karaoke_track(query_song_result[i+2].c_str());
			songinfo->set_guid_track(query_song_result[i+3].c_str());
			songinfo->set_song_name(query_song_result[i+4].c_str());
			songinfo->set_movie_name(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			songinfo->set_song_sort(value);
			value = 0;
			swscanf(query_song_result[i+7].c_str(),L"%d",&value);
			songinfo->set_accompany_volume(value);
			value = 0;
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			songinfo->set_karaoke_volume(value);
			songinfo->set_language(query_song_result[i+9].c_str());
			songinfo->set_song_type(query_song_result[i+10].c_str());
			songinfo->set_singer_name(query_song_result[i+11].c_str());
			songinfo->set_singer_sex(query_song_result[i+12].c_str());
			songinfo->set_song_version(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			songinfo->set_light_control_set(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			songinfo->set_audio_effect_code(value);
			songinfo->set_file_format(query_song_result[i+16].c_str());
			songinfo->set_local_path(query_song_result[i+17].c_str());
			songinfo->set_server_path1(query_song_result[i+18].c_str());
			songinfo->set_server_path2(query_song_result[i+19].c_str());
			songinfo->set_server_path3(query_song_result[i+20].c_str());
			songinfo->set_server_path4(query_song_result[i+21].c_str());
			songinfo->set_server_path5(query_song_result[i+22].c_str());
			songinfo->set_server_path6(query_song_result[i+23].c_str());
			songinfo->set_song_relative_path(query_song_result[i+24].c_str());
			value = 0;
			swscanf(query_song_result[i+25].c_str(),L"%d",&value);
			songinfo->set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+26].c_str(),L"%d",&value);
			songinfo->set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+27].c_str(),L"%d",&value);
			songinfo->set_video_contrast(value);
			songinfo->set_lyric(query_song_result[i+28].c_str());
			songinfo->set_culture_code(query_song_result[i+29].c_str());
			songinfo->set_preview_path(query_song_result[i+30].c_str());
			songinfo->set_video_type(PLAY_SONG_TYPE_SELECT_SONG);
			songinfo->set_singer_id1(query_song_result[i+31].c_str());
			songinfo->set_singer_id2(query_song_result[i+32].c_str());
			songinfo->set_singer_id3(query_song_result[i+33].c_str());
			songinfo->set_singer_id4(query_song_result[i+34].c_str());
			songinfo->set_file_version(query_song_result[i+35].c_str());

			songinfo++;
			row++;
			if (row>=result_item_number)
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
	/*
	try
	{
		int row=0;
		int value=0;

		//�Ƿ���������֯����
		for (int i=0; i < 3; i++)
		{
			m_listen_recommend_song_list[i].initialized_variables();
		}	

		for (int i=0;i<result_item_number;i+=result_column_nums)
		{
			//һ���еĸ�ֵ
			m_listen_recommend_song_list[row].set_song_id(query_song_result[i].c_str());
			m_listen_recommend_song_list[row].set_accompany_sing_track(query_song_result[i+1].c_str());
			m_listen_recommend_song_list[row].set_karaoke_track(query_song_result[i+2].c_str());
			m_listen_recommend_song_list[row].set_guid_track(query_song_result[i+3].c_str());
			m_listen_recommend_song_list[row].set_song_name(query_song_result[i+4].c_str());
			m_listen_recommend_song_list[row].set_movie_name(query_song_result[i+5].c_str());
			value = 0;
			swscanf(query_song_result[i+6].c_str(),L"%d",&value);
			m_listen_recommend_song_list[row].set_song_sort(value);
			value = 0;
			swscanf(query_song_result[i+7].c_str(),L"%d",&value);
			m_listen_recommend_song_list[row].set_accompany_volume(value);
			value = 0;
			swscanf(query_song_result[i+8].c_str(),L"%d",&value);
			m_listen_recommend_song_list[row].set_karaoke_volume(value);
			m_listen_recommend_song_list[row].set_language(query_song_result[i+9].c_str());
			m_listen_recommend_song_list[row].set_song_type(query_song_result[i+10].c_str());
			m_listen_recommend_song_list[row].set_singer_name(query_song_result[i+11].c_str());
			m_listen_recommend_song_list[row].set_singer_sex(query_song_result[i+12].c_str());
			m_listen_recommend_song_list[row].set_song_version(query_song_result[i+13].c_str());
			value = 0;
			swscanf(query_song_result[i+14].c_str(),L"%d",&value);
			m_listen_recommend_song_list[row].set_light_control_set(value);
			value = 0;
			swscanf(query_song_result[i+15].c_str(),L"%d",&value);
			m_listen_recommend_song_list[row].set_audio_effect_code(value);
			m_listen_recommend_song_list[row].set_file_format(query_song_result[i+16].c_str());
			m_listen_recommend_song_list[row].set_local_path(query_song_result[i+17].c_str());
			m_listen_recommend_song_list[row].set_server_path1(query_song_result[i+18].c_str());
			m_listen_recommend_song_list[row].set_server_path2(query_song_result[i+19].c_str());
			m_listen_recommend_song_list[row].set_server_path3(query_song_result[i+20].c_str());
			m_listen_recommend_song_list[row].set_server_path4(query_song_result[i+21].c_str());
			m_listen_recommend_song_list[row].set_server_path5(query_song_result[i+22].c_str());
			m_listen_recommend_song_list[row].set_server_path6(query_song_result[i+23].c_str());
			m_listen_recommend_song_list[row].set_song_relative_path(query_song_result[i+24].c_str());
			value = 0;
			swscanf(query_song_result[i+25].c_str(),L"%d",&value);
			m_listen_recommend_song_list[row].set_video_saturation(value);
			value = 0;
			swscanf(query_song_result[i+26].c_str(),L"%d",&value);
			m_listen_recommend_song_list[row].set_video_luminance(value);
			value = 0;
			swscanf(query_song_result[i+27].c_str(),L"%d",&value);
			m_listen_recommend_song_list[row].set_video_contrast(value);
			m_listen_recommend_song_list[row].set_lyric(query_song_result[i+28].c_str());
			m_listen_recommend_song_list[row].set_culture_code(query_song_result[i+29].c_str());
			m_listen_recommend_song_list[row].set_preview_path(query_song_result[i+30].c_str());
			m_listen_recommend_song_list[row].set_video_type(PLAY_SONG_TYPE_SELECT_SONG);
			m_listen_recommend_song_list[row].set_singer_id1(query_song_result[i+31].c_str());
			m_listen_recommend_song_list[row].set_singer_id2(query_song_result[i+32].c_str());
			m_listen_recommend_song_list[row].set_singer_id3(query_song_result[i+33].c_str());
			m_listen_recommend_song_list[row].set_singer_id4(query_song_result[i+34].c_str());
			m_listen_recommend_song_list[row].set_file_version(query_song_result[i+35].c_str());

			row++;
			if (row>=result_item_number)
			{
				break;
			}
		}

		return true;
	}
	catch (...)
	{

	}
	return false;*/
}
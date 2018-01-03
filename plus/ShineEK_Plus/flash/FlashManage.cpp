#include "StdAfx.h"
#include ".\flashmanage.h"
#include "PageData.h"
#include "PageVariable.h"
#include "..\parserxml\ParserXml.h"
#include "..\folder_name.h"

#include <Shlwapi.h>

#pragma warning(disable: 4018 4267)

CFlashManage::CFlashManage(void)
{
}

CFlashManage::~CFlashManage(void)
{
}

bool CFlashManage::make_request(TCHAR *request,int array_size,const TCHAR *command,const TCHAR *args)
{
	try
	{
		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==command)||(NULL==args))
		{
			return false;
		}
		//��ֹԽ��
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}
		swprintf(request,L"<invoke name=\"%s\" returntype=\"xml\"><arguments><string>%s</string></arguments></invoke>",command,args);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool CFlashManage::make_select_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type,FLASH_SONG_SHOW_MODE song_show_mode)
{
	try
	{
		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==args))
		{
			return false;
		}
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ֹԽ��
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}
		//�Ƿ������������
		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}
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
		case page_word_count:   //�������
		case page_hdmi:         //����ר��
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

		//��֯�ַ���
		if (SONG_SHOW_MODE_LIST==song_show_mode)
		{
			//�б�
			swprintf(request,L"<invoke name=\"SelectSongList\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
				refresh_screen,page_operate_type,page_call_para[page_index],args);
		}
		else
		{
			//��Ƭ
			swprintf(request,L"<invoke name=\"SelectSongCard\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
				refresh_screen,page_operate_type,page_call_para_card[page_index],args);
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}
bool CFlashManage::make_maiba_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,const TCHAR* flagname,int page_operate_type)
{
	try
	{
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==args))
		{
			return false;
		} 

		//��ֹԽ��
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}

		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}

		//�б� 
		swprintf(request,L"<invoke name=\"%s\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
				flagname, refresh_screen,page_operate_type,flagname,args);


		return true;
	}
	catch (...)
	{

	}

	return false;
}

bool CFlashManage::make_maiba_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type)
{
	try
	{
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==args))
		{
			return false;
		} 

		//��ֹԽ��
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}

		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}

		//�б� 
		swprintf(request,L"<invoke name=\"maiba_song_list\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
			refresh_screen,page_operate_type,page_call_para[page_index],args);


		return true;
	}
	catch (...)
	{

	}

	return false;
}

bool CFlashManage::make_music_enjoy_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type)
{
	try
	{
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==args))
		{
			return false;
		} 

		//��ֹԽ��
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}

		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}

		//�б� 
		swprintf(request,L"<invoke name=\"music_enjoy_list\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
			refresh_screen,page_operate_type,page_call_para[page_index],args);


		return true;
	}
	catch (...)
	{

	}

	return false;
}

bool CFlashManage::make_trend_list_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type)
{
	try
	{
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==args))
		{
			return false;
		} 

		//��ֹԽ��
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}

		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}

		//�б� 
		swprintf(request,L"<invoke name=\"trend_info_data\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
			refresh_screen,page_operate_type,page_call_para[page_index],args);

		return true;
	}
	catch (...)
	{

	}

	return false;
}

bool CFlashManage::make_recommend_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index)
{
	try
	{
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==args))
		{
			return false;
		} 

		//��ֹԽ��
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}

		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}

		//�б�
		swprintf(request,L"<invoke name=\"recommend_song_list\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" >%s</page>%s</data></string></arguments></invoke>",      \
			refresh_screen,page_call_para[page_index],args);


		return true;
	}
	catch (...)
	{

	}

	return false;
}


bool CFlashManage::make_web_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index)
{
	try
	{
		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==args))
		{
			return false;
		}
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ֹԽ��
		int nLen = _tcslen(args);
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}
		//�Ƿ������������
		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}
		 
		swprintf(request,L"<invoke name=\"maiba_song_list\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" >%s</page>%s</data></string></arguments></invoke>",      \
			refresh_screen,page_call_para[page_index],args);
	 

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool CFlashManage::make_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type,FLASH_SONG_SHOW_MODE song_show_mode)
{
	try
	{
		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==args))
		{
			return false;
		}
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ֹԽ��
		int nLen = _tcslen(args);
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}
		//�Ƿ������������
		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}
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
		case page_word_count:   //�������
		case page_hdmi:         //����ר��
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

		//��֯�ַ���
		if (SONG_SHOW_MODE_LIST==song_show_mode)
		{
			//�б�
			swprintf(request,L"<invoke name=\"SongList\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
				refresh_screen,page_operate_type,page_call_para[page_index],args);
		}
		else
		{
			//��Ƭ
			swprintf(request,L"<invoke name=\"SongCard\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
				refresh_screen,page_operate_type,page_call_para_card[page_index],args);
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool CFlashManage::make_singer_request(TCHAR *request,int array_size,const TCHAR *command,const TCHAR *args,bool refresh,int page_index,int page_operate_type)
{
	try
	{
		//��ʽ��<invoke name=\"pagechange\" returntype=\"xml\"><arguments><string><data><pageinfo pagename=\"load_songselect\"/></data></string></arguments></invoke>
		if ((NULL==request)||(NULL==command)||(NULL==args))
		{
			return false;
		}
		TCHAR refresh_screen[256];

		memset(refresh_screen,0x0,sizeof(refresh_screen));

		//��ֹԽ��
		if (_tcslen(args)>=(array_size-100))
		{
			return false;
		}
		//�Ƿ������������
		if (refresh)
		{
			_tcscpy(refresh_screen,L"true");
		}
		else
		{
			_tcscpy(refresh_screen,L"false");
		}
		//��֯�ַ���
		swprintf(request,L"<invoke name=\"%s\" returntype=\"xml\"><arguments><string><data><page isInit=\"%s\" whichType=\"%d\">%s</page>%s</data></string></arguments></invoke>",      \
				command,refresh_screen,page_operate_type,page_call_para[page_index],args);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool CFlashManage::page_change(TCHAR *request,int array_size,int page_id,int language,FLASH_SONG_SHOW_MODE song_show_mode)
{
	try
	{
		bool result=false;

		if (NULL==request)
		{
			return false;
		}
		TCHAR args[256];

		memset(args,0x0,sizeof(args));

		//Ŀǰ�������Ĵ���
		if (SONG_SHOW_MODE_LIST==song_show_mode)
		{
			//�б�
			swprintf(args,L"<data><pageinfo pagename=\"%s\" logo_url=\"\" page_title=\"%s\"/></data>",page_call_para[page_id],g_page_name[page_id].c_str());
		}
		else
		{
			//��Ƭ
			swprintf(args,L"<data><pageinfo pagename=\"%s\" logo_url=\"\" page_title=\"%s\"/></data>",page_call_para_card[page_id],g_page_name[page_id].c_str());
		}
		result = make_request(request,array_size,L"pagechange",args);
		if (result)
		{
			//��¼ҳ������
			write_page_index(page_id);
		}

		return result;
	}
	catch (...)
	{
		
	}
	return false;
}


bool CFlashManage::write_page_index(int page_index)
{
	try
	{
		vector<int>::iterator iter;
		int page_number=0;

		page_number = screen_index.size();
		
		//�����ҳ�����������ڷ���
		if ((!screen_index.empty())&&(page_number>PAGE_MAX_NUMBER))
		{
			iter = screen_index.begin();
			screen_index.erase(iter);
		}
		if (page_homepage==page_index)
		{
			//�ص���ҳ�����ԭ�е�
			screen_index.clear();
		}
		//ҳ����ջ
		if ((page_number>=2) && (page_selected==page_index)&&(page_singed==screen_index.back())&&(page_selected==screen_index.at(page_number-2)))
		{
			//�����ǰҳ����ѡ����һҳ���ѳ�������ҳ����ѡ����ô�ѳ�ҳ���޳����������һҳ������ѡ�ˡ�
			screen_index.pop_back();
		}
		else if((screen_index.empty())||(page_index!=screen_index.back()))
		{
			screen_index.push_back(page_index);
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

int CFlashManage::get_pre_page_index()
{
	try
	{
		if (screen_index.size()<=1)
		{
			//��ǰ����ҳ
			return -1;
		}
		screen_index.pop_back();
		if (screen_index.empty())
		{
			//��ǰ����ҳ
			return -1;
		}

		return screen_index.back();
	}
	catch (...)
	{

	}
	return false;
}

int CFlashManage::get_last_page_index()
{
	try
	{
		if (screen_index.empty())
		{
			//��ǰ����ҳ
			return 0;//��ǰ��-1
		}

		return screen_index.back();
	}
	catch (...)
	{

	}
	return false;
}


bool CFlashManage::get_page_name(int page_index,TCHAR *page_name,FLASH_SONG_SHOW_MODE song_show_mode)
{
	try
	{
		if ((page_index<0)||(page_index>=PAGE_MAX_NUMBER))
		{
			return false;
		}
		if (NULL==page_name)
		{
			return false;
		}

		if (SONG_SHOW_MODE_LIST==song_show_mode)
		{
			//�б�ʽ
			_tcscpy(page_name,page_call_para[page_index]);
		}
		else
		{
			//��Ƭ��Ƭ
			_tcscpy(page_name,page_call_para_card[page_index]);
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}
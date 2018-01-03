#include "StdAfx.h"
#include ".\parserxml.h"
#include ".\..\folder_name.h"

#include <string>

using namespace std;

CParserXml::CParserXml(void)
{
}

CParserXml::~CParserXml(void)
{
}

bool CParserXml::parser_flash_request_xml(const TCHAR *request,TCHAR *command,TCHAR *args)
{
	CMarkup parser_xml_markup;
	MCD_STR value;

	try
	{
		bool result = parser_xml_markup.SetDoc(request);
		if (result)
		{
			//�õ����õĽӿ�����
			parser_xml_markup.FindElem();
			value = parser_xml_markup.GetAttrib(L"name");
			if (MCD_STRISEMPTY(value))
			{
				return false;
			}
			wcscpy(command,MCD_2PCSZ(value));

			//�õ�����
			parser_xml_markup.FindChildElem(L"arguments");
			parser_xml_markup.IntoElem();
			parser_xml_markup.FindChildElem(L"string");
			parser_xml_markup.IntoElem();
			value = parser_xml_markup.GetData();
			if (MCD_STRISEMPTY(value))
			{
				return false;
			}
			wcscpy(args,MCD_2PCSZ(value));

			return true;
		}
	}
	catch (...)
	{
		
	}

	return false;
}

bool CParserXml::test_xml_validity(const TCHAR *xml_string)
{
	try
	{
		CMarkup parser_xml_markup;

		bool result = parser_xml_markup.SetDoc(xml_string);
		if (result)
		{
			return true;
		}
	}
	catch (...)
	{
		
	}
	return false;
}

bool CParserXml::get_screen_type(TCHAR *work_path,SCREEN_TYPE &interface_type,TCHAR *interface_version,FLASH_USE_LANGUAGE &cur_language,TCHAR *config_value)
{
	try
	{
		if ((NULL==work_path)||(NULL==interface_version))
		{
			return false;
		}
		TCHAR path[256];
		CMarkup parse_xml;
		std::wstring item_value;
		bool result=false;

		memset(path,0x0,sizeof(path));

		swprintf(path,L"%s\\%s\\XML\\Config.xml",work_path,g_folder_name[2]);
		//����xml
		result = parse_xml.Load(path);
		if (!result)
		{
			return false;
		}
		//��λ�������
		parse_xml.ResetPos();
		//�õ���������
		result = parse_xml.FindChildElem(L"hvInfo");
		if (result)
		{
			parse_xml.IntoElem();
			item_value = parse_xml.GetAttrib(L"isHorVer");
			if (0==_tcscmp(item_value.c_str(),L"1"))
			{
				//����
				interface_type = SCREEN_TYPE_VERTICAL;
			}
			else
			{
				interface_type = SCREEN_TYPE_HORIZON;
			}
			//�뿪�ӽ��
			parse_xml.OutOfElem();
		}
		//��λ�������
		parse_xml.ResetPos();
		//�õ�����汾������
		result = parse_xml.FindChildElem(L"info");
		if (result)
		{
			parse_xml.IntoElem();
			item_value = parse_xml.GetAttrib(L"version");
			if (!item_value.empty())
			{
				_tcscpy(interface_version,item_value.c_str());
			}
			item_value = parse_xml.GetAttrib(L"langVer");
			if (!item_value.empty())
			{
				if (L"cn"==item_value)
				{
					cur_language = FLASH_LANGUAGE_SIMPLIFIED_CHINESE;
				}
#ifdef MONGOLIA_VERSION
				//else if (0==_tcscmp(args,L"mo"))  //����
				else if (L"tr"==item_value)  //����
				{
					cur_language = FLASH_LANGUAGE_MONGOLIA;
				}
#else
				else if (L"tr"==item_value) //��������
				{
					cur_language = FLASH_LANGUAGE_TRADITIONAL_CHINESE;
				}
#endif
				else if (L"en"==item_value)
				{
					cur_language = FLASH_LANGUAGE_ENGLISH;
				}
				else if (L"jp"==item_value)
				{
					cur_language = FLASH_LANGUAGE_JAPANESE;
				}
				else if (L"kr"==item_value)
				{
					cur_language = FLASH_LANGUAGE_KOREAN;
				}
			}
			//�뿪�ӽ��
			parse_xml.OutOfElem();
		}
		//��λ�������
		parse_xml.ResetPos();
		//�õ�������������ʾ����or����
		result = parse_xml.FindChildElem(L"isVoiceChinaList");
		if (result)
		{
			parse_xml.IntoElem();
			item_value = parse_xml.GetAttrib(L"vc_show_song_or_singer");
			if (!item_value.empty())
			{
				_tcscpy(config_value,item_value.c_str());
			}
			//�뿪�ӽ��
			parse_xml.OutOfElem();
		}
		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

//<invoke name="pubAudioInfo" returntype="xml"><arguments><string><audio_data><data music="2" micro="50" tone="0" /></audio_data></string></arguments></invoke>
//<invoke name="pubMainBtn" returntype="xml"><arguments><string><control_data><data ismute="false" istrack="true" music="40" isplay="false"/></control_data></string></arguments></invoke>
bool CParserXml::parse_control_xml(TCHAR *list_xml,int &out_value1,int &out_value2,int &out_value3,int &out_value4,TCHAR *out_flag)
{
	try
	{
		if ((NULL==list_xml)||(NULL==out_flag))
		{
			return false;
		}
		CMarkup parse_xml;
		bool result=false;
		std::wstring item_value;

		//����xml
		result = parse_xml.SetDoc(list_xml);
		if (!result)
		{
			return false;
		}
		parse_xml.ResetPos();
		result = parse_xml.FindElem();
		if (!result)
		{
			return false;
		}
		//�õ�����
		item_value = parse_xml.GetAttrib(L"name");
		if (item_value.empty())
		{
			return false;
		}
		//��¼��ʶ
		_tcscpy(out_flag,item_value.c_str());
		result = parse_xml.FindChildElem();
		if (!result)
		{
			return false;
		}
		//�����ӽ��
		parse_xml.IntoElem();  //arguments
		result = parse_xml.FindChildElem();
		if (!result)
		{
			return false;
		}
		//�����ӽ��
		parse_xml.IntoElem();  //string
		result = parse_xml.FindChildElem();
		if (!result)
		{
			return false;
		}
		//�����ӽ��
		parse_xml.IntoElem();  //audio_data  control_data
		result = parse_xml.FindChildElem();
		if (!result)
		{
			return false;
		}
		//�����ӽ��
		parse_xml.IntoElem();  //data
		if (0==_tcscmp(out_flag,L"pubAudioInfo"))
		{
			item_value.clear();
			item_value = parse_xml.GetAttrib(L"music");
			out_value1 = _wtoi(item_value.c_str());
			item_value.clear();
			item_value = parse_xml.GetAttrib(L"micro");
			out_value2 = _wtoi(item_value.c_str());
			item_value.clear();
			item_value = parse_xml.GetAttrib(L"tone");
			out_value3 = _wtoi(item_value.c_str());
		}
		else  //pubMainBtn
		{
			item_value.clear();
			item_value = parse_xml.GetAttrib(L"ismute");
			if (0==_tcscmp(item_value.c_str(),L"true"))
			{
				out_value1 = 1;
			}
			else
			{
				out_value1 = 0;
			}
			item_value.clear();
			item_value = parse_xml.GetAttrib(L"istrack");
			if (0==_tcscmp(item_value.c_str(),L"true"))
			{
				out_value2 = 1;
			}
			else
			{
				out_value2 = 0;
			}
			item_value.clear();
			item_value = parse_xml.GetAttrib(L"music");
			out_value3 = _wtoi(item_value.c_str());
			item_value.clear();
			item_value = parse_xml.GetAttrib(L"isplay");
			if (0==_tcscmp(item_value.c_str(),L"true"))
			{
				out_value4 = 1;
			}
			else
			{
				out_value4 = 0;
			}
		}

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool CParserXml::modify_local_game_name(SONG_GAME_STRUCT game_name[])
{
	try
	{
		CMarkup parse_xml;
		TCHAR work_path[256];
		TCHAR language_path[256];
		bool result=false;
		std::wstring item_value;

		memset(work_path,0x0,sizeof(work_path));

		//�õ�����·��
		GetModuleFileName(NULL,work_path,sizeof(work_path));
		_tcsrchr(work_path,'\\')[0] ='\0';

		//��������
		for (int i=0;i<5;i++)
		{
			memset(language_path,0x0,sizeof(language_path));
			switch(i)
			{
			case 0:
				{
					swprintf(language_path,L"%s\\flash_interface\\XML\\language_cn.xml",work_path);
				}
				break;
			case 1:
				{
					swprintf(language_path,L"%s\\flash_interface\\XML\\language_tr.xml",work_path);
				}
				break;
			case 2:
				{
					swprintf(language_path,L"%s\\flash_interface\\XML\\language_en.xml",work_path);
				}
				break;
			case 3:
				{
					swprintf(language_path,L"%s\\flash_interface\\XML\\language_jp.xml",work_path);
				}
				break;
			case 4:
				{
					swprintf(language_path,L"%s\\flash_interface\\XML\\language_kr.xml",work_path);
				}
				break;
			}

			//����xml�ļ�
			result = parse_xml.Load(language_path);
			if (!result)
			{
				continue;
			}
			parse_xml.ResetPos();
			result = parse_xml.FindChildElem();
			if(result)
			{
				//�����ӽ��
				parse_xml.IntoElem();
				while(result)
				{
					item_value = parse_xml.GetAttrib(L"id");
					if (0==_tcscmp(item_value.c_str(),L"10.11.53"))
					{
						parse_xml.SetAttrib(L"text",game_name[0].name);
					}
					else if (0==_tcscmp(item_value.c_str(),L"10.11.54"))
					{
						parse_xml.SetAttrib(L"text",game_name[1].name);
					}
					else if (0==_tcscmp(item_value.c_str(),L"10.11.55"))
					{
						parse_xml.SetAttrib(L"text",game_name[2].name);
					}
					else if (0==_tcscmp(item_value.c_str(),L"10.11.56"))
					{
						parse_xml.SetAttrib(L"text",game_name[3].name);
					}
					else if (0==_tcscmp(item_value.c_str(),L"10.11.57"))
					{
						parse_xml.SetAttrib(L"text",game_name[4].name);
					}
					else if (0==_tcscmp(item_value.c_str(),L"10.11.58"))
					{
						parse_xml.SetAttrib(L"text",game_name[5].name);
					}
					//�����ֵܽ��
					result = parse_xml.FindElem();
				}
				//����
				parse_xml.Save(language_path);
			}
		}

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}
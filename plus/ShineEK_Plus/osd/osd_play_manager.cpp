#include "StdAfx.h"
#include ".\osd_play_manager.h"
#include "..\file\config_file.h"
#include "..\folder_name.h"
#include "..\message.h"
#include "..\file\log.h"

osd_play_manager::osd_play_manager(void)
{
	m_show_osd=true;
	file_attribute=FILE_ATTRIBUTE_NVALID;         //��¼logo�ļ�������
	memset(m_logo_path,0x0,sizeof(m_logo_path));  //logo�ļ���·��
	m_control_osd_x=600;                    //����osd�ĺ�����
	m_control_osd_y=80;                    //����osd��������
	//��ʼ��
	initialize();
}

osd_play_manager::~osd_play_manager(void)
{
}

void osd_play_manager::initialize(void)
{
	try
	{
		config_file_manager config_file;
		std::wstring value;
		int config_value;
		TCHAR *install_path=NULL;

		// ��ȡ������Ļ�Ĳ���
		//�Ƿ���ʾOSD
		m_show_osd = config_file.read_boolean(L"osd",L"show_osd",true);
		//��������
		config_value = config_file.read_integer(L"osd",L"scroll_count",1);
		m_osd_text_picture.set_scroll_count(config_value);
		//�����ٶ�
		config_value = config_file.read_integer(L"osd",L"scroll_speed",100);
		m_osd_text_picture.set_scroll_speed(config_value);
		//������ʽ
		value = config_file.read_string(L"osd",L"scroll_mode",L"�ҽ����");
		m_osd_text_picture.set_scroll_mode(value.c_str(),MESSAGE_TEXT);
		//������ɫ
		value = config_file.read_string(L"osd",L"text_color",L"��ɫ");
		m_osd_text_picture.set_text_color(value.c_str());
		//���屳������ɫ
		value = config_file.read_string(L"osd",L"text_background_color",L"");
		m_osd_text_picture.set_text_Background_color(value.c_str());
		//����
		value = config_file.read_string(L"osd",L"text_font",L"����");
		m_osd_text_picture.set_text_font(value.c_str());
		//����Ĵ�С
		config_value = config_file.read_integer(L"osd",L"text_size",40);
		m_osd_text_picture.set_text_size(config_value);
		//����ͼƬ����
		memset(m_text_background_path,0x0,sizeof(m_text_background_path));
		memset(m_install_path,0x0,sizeof(m_install_path));
		memset(m_text_background_path,0x0,sizeof(m_text_background_path));

		//�õ���װ·��
		GetModuleFileName(NULL, m_install_path, sizeof(m_install_path));
		install_path = _tcsrchr(m_install_path, _T('\\'));
		if (install_path)
		{
			install_path[0] = '\0';
		}
		memset(m_screen_show_folder_name,0x0,sizeof(m_screen_show_folder_name));
		_tcscpy(m_screen_show_folder_name,g_folder_name[6]);
		swprintf(m_text_background_path,L"%s\\%s\\bar.bmp",m_install_path,m_screen_show_folder_name);
		//����osd������
		m_control_osd_x = config_file.read_integer(L"osd",L"control_osd_x",600);
		m_control_osd_y = config_file.read_integer(L"osd",L"control_osd_y",80);
		m_osd_text_picture.adjust_text_position(m_control_osd_x);
		//��ʾ�Ŀ���osd����
		m_show_osd_suit_number = config_file.read_integer(L"osd",L"show_osd_suit",0);
	}
	catch (...)
	{
		
	}
	return;
}

bool osd_play_manager::set_osd_text(TCHAR *text)
{
	try
	{
		if (NULL==text)
		{
			return false;
		}
		return m_osd_text_picture.set_text(text);
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_play_manager::get_background_path(TCHAR *path)
{
	try
	{
		if (!m_show_osd)
		{
			return false;
		}
		_tcscpy(path,m_text_background_path);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_play_manager::get_control_osd_info(enum OSD_SHOW_CONTENT show_content,TCHAR *path,int &x_pos,int &y_pos,bool soft_decode,enum FLASH_USE_LANGUAGE flash_language,bool recorder_osd)
{
	try
	{
		TCHAR picture_name[256];
		TCHAR folder_name_cn[256];
		TCHAR folder_name_en[256];

		memset(picture_name,0x0,sizeof(picture_name));
		memset(folder_name_cn,0x0,sizeof(folder_name_cn));
		memset(folder_name_en,0x0,sizeof(folder_name_en));

		switch(show_content)
		{
		case CONTROL_OSD__PAUSE:  //��ͣ
			{
				_tcscpy(picture_name,L"��ͣ");
			}
			break;
		case CONTROL_OSD__NEXT: //��һ��
			{
				_tcscpy(picture_name,L"��һ��");
			}
			break;
		case CONTROL_OSD__CHANNEL_KALAOK:	// ԭ��
			{
				_tcscpy(picture_name,L"ԭ��");
			}
			break;
		case CONTROL_OSD__CHANNEL_ACCOMPANY:    //�鳪
			{
				_tcscpy(picture_name,L"�鳪");
			}
			break;
		case CONTROL_OSD__RECORD:	// ¼���С���
			{
				_tcscpy(picture_name,L"¼��");
			}
			break;
		case CONTROL_OSD__PLAYBACK:	// �ط��С���
			{
				if (recorder_osd)
				{
					_tcscpy(picture_name,L"�ط�1");
				}
				else
				{
					_tcscpy(picture_name,L"�ط�");
				}	
			}
			break;
		case CONTROL_OSD__VOLUME_UP:	// ����+
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD__VOLUME_DOWN: //����-
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD__VOLUME_MUTE:  //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD__MICROPHONE_VOLUME_UP:   // ��˷�������
			{
				_tcscpy(picture_name,L"���+");
			}
			break;
		case CONTROL_OSD__MICROPHONE_VOLUME_DOWN:   // ��˷�������
			{
				_tcscpy(picture_name,L"���-");
			}
			break;
		case CONTROL_OSD__TUNE_UP:       // ������
			{
				_tcscpy(picture_name,L"����+");
			}
			break;
		case CONTROL_OSD__TUNE_DOWN:     // ������
			{
				_tcscpy(picture_name,L"����-");
			}
			break;
		case CONTROL_OSD__TUNE_ORIGINAL: //ԭ��
			{
				_tcscpy(picture_name,L"��׼��");
			}
			break;
		case CONTROL_OSD__SERVICE:  //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
			//��Ч
		case CONTROL_OSD_AUDIO_EFFECT_STANDARD: //��׼
			{
				_tcscpy(picture_name,L"��Ч��׼");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT_THEATER: //�糡
			{
				_tcscpy(picture_name,L"�糡");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT_PROFESSIONAL: //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT_MAGIC: //ħ��
			{
				_tcscpy(picture_name,L"ħ��");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT: //�Զ�
			{
				_tcscpy(picture_name,L"�Զ�");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT_RESERVE2:
			{
				_tcscpy(picture_name,L"ͨ��");
			}
			break;
		case CONTROL_OSD_ATMOSPHERE_APPLAUSE: //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD_ATMOSPHERE_CHEER:       //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD_ATMOSPHERE_OUTCRY:      //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_HAOZAN: //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_SHIHUA: //ʯ��
			{
				_tcscpy(picture_name,L"ʯ��");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_XIANHUA: //�ʻ�
			{
				_tcscpy(picture_name,L"�ʻ�");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_TUXIE: //��Ѫ
			{
				_tcscpy(picture_name,L"��Ѫ");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_FEIWEN: //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_XINSUI: //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_HAIXIU: //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_ZADAN: //�ҵ�
			{
				_tcscpy(picture_name,L"�ҵ�");
			}
			break;
		case CONTROL_OSD_ATMOSPHERE_WHISTLE:     //��
			{
				_tcscpy(picture_name,L"��");
			}
			break;
            //�ƹ�
		case CONTROL_OSD_LIGHT1:                 //�ƹ�1
			{
				_tcscpy(picture_name,L"light7");
			}
			break;
		case CONTROL_OSD_LIGHT2:                 //�ƹ�2
			{
				_tcscpy(picture_name,L"light8");
			}
			break;
		case CONTROL_OSD_LIGHT3:                 //�ƹ�3
			{
				_tcscpy(picture_name,L"light9");
			}
			break;
		case CONTROL_OSD_LIGHT4:                 //�ƹ�4
			{
				_tcscpy(picture_name,L"light10");
			}
			break;
		case CONTROL_OSD_LIGHT5:                 //�ƹ�5
			{
				_tcscpy(picture_name,L"light11");
			}
			break;
		case CONTROL_OSD_LIGHT6:                 //�ƹ�6
			{
				_tcscpy(picture_name,L"light12");
			}
			break;
		case CONTROL_OSD_LIGHT7:                 //�ƹ�7
			{
				_tcscpy(picture_name,L"light13");
			}
			break;
		case CONTROL_OSD_LIGHT8:                 //�ƹ�8
			{
				_tcscpy(picture_name,L"light14");
			}
			break;
		case CONTROL_OSD_LIGHT_STANDARD:             //�ƹ� ��׼
			{
				_tcscpy(picture_name,L"light3");
			}
			break;
		case CONTROL_OSD_LIGHT__BACKGROUND:           //�ƹ� ����
			{
				_tcscpy(picture_name,L"light4");
			}
			break;
		case CONTROL_OSD_LIGHT__STAGE:                //�ƹ� ��̨
			{
				_tcscpy(picture_name,L"light5");
			}
			break;
		case CONTROL_OSD_LIGHT__SCINTILLATION:        //�ƹ� ����
			{
				_tcscpy(picture_name,L"light6");
			}
			break;
		case CONTROL_OSD_LIGHT_OPEN:                 //�ƹ� ��
			{
				_tcscpy(picture_name,L"light2");
			}
			break;
		case CONTROL_OSD_LIGHT_CLOSE:                //�ƹ� �ر�
			{
				_tcscpy(picture_name,L"light1");
			}
			break;
			//������
		case CONTROL_OSD_ENVIRONMENT_AUDIO_MEETING:   //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_AIRPORT:   //�ɻ���
			{
				_tcscpy(picture_name,L"�ɻ���");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_ROAD:      //��·��
			{
				_tcscpy(picture_name,L"·��");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_STATION:   //��վ
			{
				_tcscpy(picture_name,L"��վ");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_MAHJONG:  //�齫��
			{
				_tcscpy(picture_name,L"�齫");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_RAIN:    //������
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD_REVERBERATION_DOWN:        //�����
			{
				_tcscpy(picture_name,L"����-");
			}
			break;
		case CONTROL_OSD_REVERBERATION_UP:          //�����
			{
				_tcscpy(picture_name,L"����+");
			}
			break;
		case CONTROL_OSD__ENTER_AUTO_SONG:   //���뵼��
			{
				_tcscpy(picture_name,L"���뵼��");
			}
			break;
		case CONTROL_OSD__EXIT_AUTO_SONG:   //�˳�����
			{
				_tcscpy(picture_name,L"�˳�����");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_STRONG:          //�յ�ǿ
			{
				_tcscpy(picture_name,L"ǿ��");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_MID:          //�յ���
			{
				_tcscpy(picture_name,L"�з�");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_WEAK:          //�յ���
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_TEMPERATURE_UP:     //�¶�+
			{
				_tcscpy(picture_name,L"�¶�+");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_TEMPERATURE_DOWN:   //�¶�-
			{
				_tcscpy(picture_name,L"�¶�-");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_CLOSE:          //�յ��ر�
			{
				_tcscpy(picture_name,L"�յ���/��");
			}
			break;
		case CONTROL_OSD_DISCHARGE_AIR_FUNCTION:          //�ŷ�
			{
				_tcscpy(picture_name,L"�ŷ�");
			}
			break;
		case CONTROL_OSD_DISCHARGE_AIR_CLOSE:  //�ŷ�ر�
			{
				_tcscpy(picture_name,L"�ر��ŷ�");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_REFRIGERATION:      //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_HEATING:          //����
			{
				_tcscpy(picture_name,L"����");
			}
			break;
		case CONTROL_OSD_SCORE_OPEN:           //������
			{
				_tcscpy(picture_name,L"��������");
			}
			break;
		case CONTROL_OSD_SCORE_CLOSE:            //�ر�����
			{
				_tcscpy(picture_name,L"�ر�����");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_STANDARD: //������Ч��׼
			{
				_tcscpy(picture_name,L"������Ч��׼");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_THEATER: //������Ч�糡
			{
				_tcscpy(picture_name,L"������Ч�糡");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_PROFESSIONAL: //������Ч����
			{
				_tcscpy(picture_name,L"������Ч����");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_MAGIC: //������Чħ��
			{
				_tcscpy(picture_name,L"������Чħ��");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_RESERVE1: //������Ч�Զ�
			{
				_tcscpy(picture_name,L"������Ч�Զ�");
			}
			break;
		default:
			return false;
		}

		if (soft_decode)
		{
			switch(m_show_osd_suit_number)
			{
			case 0:
				{
					_tcscpy(folder_name_cn,L"cn");
					_tcscpy(folder_name_en,L"en");
				}
				break;
			case 1:
			default:
				{
					_tcscpy(folder_name_cn,L"cn1");
					_tcscpy(folder_name_en,L"en1");
				}
				break;
			}
			//���
			if((FLASH_LANGUAGE_SIMPLIFIED_CHINESE==flash_language)||(FLASH_LANGUAGE_TRADITIONAL_CHINESE==flash_language))
			{
				swprintf(path,L"%s\\%s\\%s\\%s.png",m_install_path,m_screen_show_folder_name,folder_name_cn,picture_name);
			}
			else
			{
				swprintf(path,L"%s\\%s\\%s\\%s.png",m_install_path,m_screen_show_folder_name,folder_name_en,picture_name);
			}
		}
		else
		{
			//Ӳ��
			swprintf(path,L"%s\\%s\\%s.bmp",m_install_path,m_screen_show_folder_name,picture_name);
		}
		//����osd������
		x_pos = m_control_osd_x;
		y_pos = m_control_osd_y;

		WriteLog(__FL__, path);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool osd_play_manager::set_logo_osd_path(TCHAR *path)
{
	try
	{
		DWORD file_attr;
		bool result=false;
		if (NULL==path)
		{
			return false;
		}

		file_attr = GetFileAttributes(path);
		if (INVALID_FILE_ATTRIBUTES==file_attr)
		{
			return false;
		}
		if (FILE_ATTRIBUTE_DIRECTORY & file_attr)
		{
			//���ļ���
			//��¼�ļ�����
			file_attribute = FILE_ATTRIBUTE_DIR;
			result = logo_list.set_logo_path(path);
		}
		else
		{
			//�ǵ����ļ�
			//��¼�ļ�����
			file_attribute = FILE_ATTRIBUTE_FILE;
			_tcscpy(m_logo_path,path);
			result = true;
		}
		return result;
	}
	catch (...)
	{
		
	}

	return false;
}

bool osd_play_manager::get_logo_osd_info(TCHAR *path,int &index)
{
	try
	{
		int cur_index = 0;
		bool result=false;
		TCHAR logo_path[256];

		memset(logo_path,0x0,sizeof(logo_path));

		switch(file_attribute)
		{
		case FILE_ATTRIBUTE_DIR:  //Ŀ¼
			{
				cur_index = logo_list.get_cur_logo_index();
				result = logo_list.get_logo_file_path(logo_path);
				if (!result)
				{
					return false;
				}
                _tcscpy(path,logo_path);
				index = cur_index+1;
			}
			break;
		case FILE_ATTRIBUTE_FILE: //�����ļ�
			{
				_tcscpy(path,m_logo_path);
				index = 1;
			}
			break;
		default:
			break;
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void osd_play_manager::adjust_control_osd_coordinate(int screen_width,int screen_height,bool soft_decode)
{
	if (m_control_osd_x>screen_width)
	{
		if (soft_decode)
		{
			//���
			switch(m_show_osd_suit_number)
			{
			case 0:
				{
					m_control_osd_x = (screen_width-150)/2;
				}
				break;
			case 1:
			default:
				{
					m_control_osd_x = screen_width-210;
				}
				break;
			}
		}
		else
		{
			//Ӳ��
			m_control_osd_x = screen_width-150;
		}
	}
	if ((m_control_osd_y<0)||(m_control_osd_y>screen_height))
	{
		if (soft_decode)
		{
			//���
			switch(m_show_osd_suit_number)
			{
			case 0:
				{
					m_control_osd_y = screen_height/4;
				}
				break;
			case 1:
			default:
				{
					m_control_osd_y = 40;
				}
				break;
			}
		}
		else
		{
			//Ӳ��
			m_control_osd_y = 30;
		}
	}

	//������Ļ����ʼλ��
	if (soft_decode)
	{
		switch(m_show_osd_suit_number)
		{
		case 0:
			{
				m_osd_text_picture.adjust_text_position(screen_width-30);
			}
			break;
		case 1:
		default:
			{
				m_osd_text_picture.adjust_text_position(screen_width-50);
			}
			break;
		}
	}
	else
	{
		m_osd_text_picture.adjust_text_position(screen_width-40);
	}
}
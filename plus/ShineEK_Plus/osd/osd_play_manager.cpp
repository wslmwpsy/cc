#include "StdAfx.h"
#include ".\osd_play_manager.h"
#include "..\file\config_file.h"
#include "..\folder_name.h"
#include "..\message.h"
#include "..\file\log.h"

osd_play_manager::osd_play_manager(void)
{
	m_show_osd=true;
	file_attribute=FILE_ATTRIBUTE_NVALID;         //记录logo文件的属性
	memset(m_logo_path,0x0,sizeof(m_logo_path));  //logo文件的路径
	m_control_osd_x=600;                    //控制osd的横坐标
	m_control_osd_y=80;                    //控制osd的纵坐标
	//初始化
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

		// 读取电视字幕的参数
		//是否显示OSD
		m_show_osd = config_file.read_boolean(L"osd",L"show_osd",true);
		//滚动次数
		config_value = config_file.read_integer(L"osd",L"scroll_count",1);
		m_osd_text_picture.set_scroll_count(config_value);
		//滚动速度
		config_value = config_file.read_integer(L"osd",L"scroll_speed",100);
		m_osd_text_picture.set_scroll_speed(config_value);
		//滚动方式
		value = config_file.read_string(L"osd",L"scroll_mode",L"右进左出");
		m_osd_text_picture.set_scroll_mode(value.c_str(),MESSAGE_TEXT);
		//字体颜色
		value = config_file.read_string(L"osd",L"text_color",L"红色");
		m_osd_text_picture.set_text_color(value.c_str());
		//字体背景的颜色
		value = config_file.read_string(L"osd",L"text_background_color",L"");
		m_osd_text_picture.set_text_Background_color(value.c_str());
		//字体
		value = config_file.read_string(L"osd",L"text_font",L"宋体");
		m_osd_text_picture.set_text_font(value.c_str());
		//字体的大小
		config_value = config_file.read_integer(L"osd",L"text_size",40);
		m_osd_text_picture.set_text_size(config_value);
		//文字图片背景
		memset(m_text_background_path,0x0,sizeof(m_text_background_path));
		memset(m_install_path,0x0,sizeof(m_install_path));
		memset(m_text_background_path,0x0,sizeof(m_text_background_path));

		//得到安装路径
		GetModuleFileName(NULL, m_install_path, sizeof(m_install_path));
		install_path = _tcsrchr(m_install_path, _T('\\'));
		if (install_path)
		{
			install_path[0] = '\0';
		}
		memset(m_screen_show_folder_name,0x0,sizeof(m_screen_show_folder_name));
		_tcscpy(m_screen_show_folder_name,g_folder_name[6]);
		swprintf(m_text_background_path,L"%s\\%s\\bar.bmp",m_install_path,m_screen_show_folder_name);
		//控制osd的坐标
		m_control_osd_x = config_file.read_integer(L"osd",L"control_osd_x",600);
		m_control_osd_y = config_file.read_integer(L"osd",L"control_osd_y",80);
		m_osd_text_picture.adjust_text_position(m_control_osd_x);
		//显示的控制osd组编号
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
		case CONTROL_OSD__PAUSE:  //暂停
			{
				_tcscpy(picture_name,L"暂停");
			}
			break;
		case CONTROL_OSD__NEXT: //下一首
			{
				_tcscpy(picture_name,L"下一首");
			}
			break;
		case CONTROL_OSD__CHANNEL_KALAOK:	// 原唱
			{
				_tcscpy(picture_name,L"原唱");
			}
			break;
		case CONTROL_OSD__CHANNEL_ACCOMPANY:    //伴唱
			{
				_tcscpy(picture_name,L"伴唱");
			}
			break;
		case CONTROL_OSD__RECORD:	// 录音中……
			{
				_tcscpy(picture_name,L"录音");
			}
			break;
		case CONTROL_OSD__PLAYBACK:	// 回放中……
			{
				if (recorder_osd)
				{
					_tcscpy(picture_name,L"回放1");
				}
				else
				{
					_tcscpy(picture_name,L"回放");
				}	
			}
			break;
		case CONTROL_OSD__VOLUME_UP:	// 音量+
			{
				_tcscpy(picture_name,L"增音");
			}
			break;
		case CONTROL_OSD__VOLUME_DOWN: //音量-
			{
				_tcscpy(picture_name,L"减音");
			}
			break;
		case CONTROL_OSD__VOLUME_MUTE:  //静音
			{
				_tcscpy(picture_name,L"静音");
			}
			break;
		case CONTROL_OSD__MICROPHONE_VOLUME_UP:   // 麦克风音量加
			{
				_tcscpy(picture_name,L"麦克+");
			}
			break;
		case CONTROL_OSD__MICROPHONE_VOLUME_DOWN:   // 麦克风音量减
			{
				_tcscpy(picture_name,L"麦克-");
			}
			break;
		case CONTROL_OSD__TUNE_UP:       // 音调加
			{
				_tcscpy(picture_name,L"音调+");
			}
			break;
		case CONTROL_OSD__TUNE_DOWN:     // 音调减
			{
				_tcscpy(picture_name,L"音调-");
			}
			break;
		case CONTROL_OSD__TUNE_ORIGINAL: //原调
			{
				_tcscpy(picture_name,L"标准调");
			}
			break;
		case CONTROL_OSD__SERVICE:  //服务
			{
				_tcscpy(picture_name,L"服务");
			}
			break;
			//音效
		case CONTROL_OSD_AUDIO_EFFECT_STANDARD: //标准
			{
				_tcscpy(picture_name,L"音效标准");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT_THEATER: //剧场
			{
				_tcscpy(picture_name,L"剧场");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT_PROFESSIONAL: //唱将
			{
				_tcscpy(picture_name,L"唱将");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT_MAGIC: //魔音
			{
				_tcscpy(picture_name,L"魔音");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT: //自动
			{
				_tcscpy(picture_name,L"自动");
			}
			break;
		case CONTROL_OSD_AUDIO_EFFECT_RESERVE2:
			{
				_tcscpy(picture_name,L"通俗");
			}
			break;
		case CONTROL_OSD_ATMOSPHERE_APPLAUSE: //鼓掌
			{
				_tcscpy(picture_name,L"鼓掌");
			}
			break;
		case CONTROL_OSD_ATMOSPHERE_CHEER:       //欢呼
			{
				_tcscpy(picture_name,L"欢呼");
			}
			break;
		case CONTROL_OSD_ATMOSPHERE_OUTCRY:      //催眠
			{
				_tcscpy(picture_name,L"催眠");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_HAOZAN: //好赞
			{
				_tcscpy(picture_name,L"好赞");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_SHIHUA: //石化
			{
				_tcscpy(picture_name,L"石化");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_XIANHUA: //鲜花
			{
				_tcscpy(picture_name,L"鲜花");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_TUXIE: //吐血
			{
				_tcscpy(picture_name,L"吐血");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_FEIWEN: //飞吻
			{
				_tcscpy(picture_name,L"飞吻");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_XINSUI: //心碎
			{
				_tcscpy(picture_name,L"心碎");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_HAIXIU: //害羞
			{
				_tcscpy(picture_name,L"害羞");
			}
			break;
		case 	CONTROL_OSD_ATMOSPHERE_ZADAN: //砸蛋
			{
				_tcscpy(picture_name,L"砸蛋");
			}
			break;
		case CONTROL_OSD_ATMOSPHERE_WHISTLE:     //狂汗
			{
				_tcscpy(picture_name,L"狂汗");
			}
			break;
            //灯光
		case CONTROL_OSD_LIGHT1:                 //灯光1
			{
				_tcscpy(picture_name,L"light7");
			}
			break;
		case CONTROL_OSD_LIGHT2:                 //灯光2
			{
				_tcscpy(picture_name,L"light8");
			}
			break;
		case CONTROL_OSD_LIGHT3:                 //灯光3
			{
				_tcscpy(picture_name,L"light9");
			}
			break;
		case CONTROL_OSD_LIGHT4:                 //灯光4
			{
				_tcscpy(picture_name,L"light10");
			}
			break;
		case CONTROL_OSD_LIGHT5:                 //灯光5
			{
				_tcscpy(picture_name,L"light11");
			}
			break;
		case CONTROL_OSD_LIGHT6:                 //灯光6
			{
				_tcscpy(picture_name,L"light12");
			}
			break;
		case CONTROL_OSD_LIGHT7:                 //灯光7
			{
				_tcscpy(picture_name,L"light13");
			}
			break;
		case CONTROL_OSD_LIGHT8:                 //灯光8
			{
				_tcscpy(picture_name,L"light14");
			}
			break;
		case CONTROL_OSD_LIGHT_STANDARD:             //灯光 标准
			{
				_tcscpy(picture_name,L"light3");
			}
			break;
		case CONTROL_OSD_LIGHT__BACKGROUND:           //灯光 背景
			{
				_tcscpy(picture_name,L"light4");
			}
			break;
		case CONTROL_OSD_LIGHT__STAGE:                //灯光 舞台
			{
				_tcscpy(picture_name,L"light5");
			}
			break;
		case CONTROL_OSD_LIGHT__SCINTILLATION:        //灯光 屏闪
			{
				_tcscpy(picture_name,L"light6");
			}
			break;
		case CONTROL_OSD_LIGHT_OPEN:                 //灯光 开
			{
				_tcscpy(picture_name,L"light2");
			}
			break;
		case CONTROL_OSD_LIGHT_CLOSE:                //灯光 关闭
			{
				_tcscpy(picture_name,L"light1");
			}
			break;
			//环境音
		case CONTROL_OSD_ENVIRONMENT_AUDIO_MEETING:   //会议
			{
				_tcscpy(picture_name,L"会议");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_AIRPORT:   //飞机场
			{
				_tcscpy(picture_name,L"飞机场");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_ROAD:      //马路上
			{
				_tcscpy(picture_name,L"路上");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_STATION:   //火车站
			{
				_tcscpy(picture_name,L"火车站");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_MAHJONG:  //麻将中
			{
				_tcscpy(picture_name,L"麻将");
			}
			break;
		case CONTROL_OSD_ENVIRONMENT_AUDIO_RAIN:    //下雨中
			{
				_tcscpy(picture_name,L"下雨");
			}
			break;
		case CONTROL_OSD_REVERBERATION_DOWN:        //混响减
			{
				_tcscpy(picture_name,L"混响-");
			}
			break;
		case CONTROL_OSD_REVERBERATION_UP:          //混响加
			{
				_tcscpy(picture_name,L"混响+");
			}
			break;
		case CONTROL_OSD__ENTER_AUTO_SONG:   //进入导唱
			{
				_tcscpy(picture_name,L"进入导唱");
			}
			break;
		case CONTROL_OSD__EXIT_AUTO_SONG:   //退出导唱
			{
				_tcscpy(picture_name,L"退出导唱");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_STRONG:          //空调强
			{
				_tcscpy(picture_name,L"强风");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_MID:          //空调中
			{
				_tcscpy(picture_name,L"中风");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_WEAK:          //空调弱
			{
				_tcscpy(picture_name,L"弱风");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_TEMPERATURE_UP:     //温度+
			{
				_tcscpy(picture_name,L"温度+");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_TEMPERATURE_DOWN:   //温度-
			{
				_tcscpy(picture_name,L"温度-");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_CLOSE:          //空调关闭
			{
				_tcscpy(picture_name,L"空调开/关");
			}
			break;
		case CONTROL_OSD_DISCHARGE_AIR_FUNCTION:          //排风
			{
				_tcscpy(picture_name,L"排风");
			}
			break;
		case CONTROL_OSD_DISCHARGE_AIR_CLOSE:  //排风关闭
			{
				_tcscpy(picture_name,L"关闭排风");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_REFRIGERATION:      //制冷
			{
				_tcscpy(picture_name,L"制冷");
			}
			break;
		case CONTROL_OSD_AIR_CONDITION_HEATING:          //制热
			{
				_tcscpy(picture_name,L"制热");
			}
			break;
		case CONTROL_OSD_SCORE_OPEN:           //打开评分
			{
				_tcscpy(picture_name,L"开启评分");
			}
			break;
		case CONTROL_OSD_SCORE_CLOSE:            //关闭评分
			{
				_tcscpy(picture_name,L"关闭评分");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_STANDARD: //音乐音效标准
			{
				_tcscpy(picture_name,L"音乐音效标准");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_THEATER: //音乐音效剧场
			{
				_tcscpy(picture_name,L"音乐音效剧场");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_PROFESSIONAL: //音乐音效唱将
			{
				_tcscpy(picture_name,L"音乐音效唱将");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_MAGIC: //音乐音效魔音
			{
				_tcscpy(picture_name,L"音乐音效魔音");
			}
			break;
		case CONTROL_OSD_MUSIC_SOUND_RESERVE1: //音乐音效自动
			{
				_tcscpy(picture_name,L"音乐音效自动");
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
			//软解
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
			//硬解
			swprintf(path,L"%s\\%s\\%s.bmp",m_install_path,m_screen_show_folder_name,picture_name);
		}
		//控制osd的坐标
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
			//是文件夹
			//记录文件属性
			file_attribute = FILE_ATTRIBUTE_DIR;
			result = logo_list.set_logo_path(path);
		}
		else
		{
			//是单个文件
			//记录文件属性
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
		case FILE_ATTRIBUTE_DIR:  //目录
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
		case FILE_ATTRIBUTE_FILE: //单个文件
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
			//软解
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
			//硬解
			m_control_osd_x = screen_width-150;
		}
	}
	if ((m_control_osd_y<0)||(m_control_osd_y>screen_height))
	{
		if (soft_decode)
		{
			//软解
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
			//硬解
			m_control_osd_y = 30;
		}
	}

	//调整字幕的起始位置
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
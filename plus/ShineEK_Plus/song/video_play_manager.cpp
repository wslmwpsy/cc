#include "StdAfx.h"
#include ".\video_play_manager.h"

video_play_manager::video_play_manager(void)
{
}

video_play_manager::~video_play_manager(void)
{
}

void video_play_manager::initialize(HWND m_wnd,TCHAR *ip)
{
	player_cur_state=BEGIN_STATE;
	player_next_state = BEGIN_STATE;
	playing_video_exist=false;
	m_allow_cut=true;
	m_first_begin_ad=true;

	m_public_video_manager.initialize(ip);
	m_select_song_manager.initialize(m_wnd);
}

int video_play_manager::get_next_play_video(song_info& video_info,AD_ITEM_CULTURE *ad_item,bool play_ad)
{
	try
	{
		bool result=false;
		long ad_result=0;

		//记录当前状态
		player_cur_state = player_next_state;
		
		//通过下一个状态取视频，同时改变播放器的下一个状态
		switch(player_next_state)
		{
		case BEGIN_STATE:
			{
				if (play_ad)
				{
					//首先判断是否有文化部的开机广告
					ad_result = get_ADItem_culture(DISPLAY_DEVICE_TV,SCENE_POWER_ON,&ad_item,0);
					if (1==ad_result)
					{
						if (m_first_begin_ad)
						{
							m_allow_cut = false;
							m_first_begin_ad = false;
						}
						else
						{
							m_allow_cut = true;
						}
						//播放文化部的视频
						return 0;
					}
				}

				result = m_public_video_manager.get_begin_video(video_info);
				if (result)
				{
					//记录下正在播放的视频
					m_playing_video = video_info;
					playing_video_exist=true;
				}
				//改变播放器状态
				player_next_state = IDLESSE_STATE;

				if (result)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
			break;
		case END_STATE:
			{
				if (play_ad)
				{
					//首先判断是否有文化部的开机广告
					ad_result = get_ADItem_culture(DISPLAY_DEVICE_TV,SCENE_INTER_MODE,&ad_item,SCENE_INTER_IDLE);
					if (1==ad_result)
					{
						//播放文化部的视频
						//允许切掉
						m_allow_cut = true;
						return 0;
					}
				}

				result = m_public_video_manager.get_end_video(video_info);
				if (result)
				{
					//记录下正在播放的视频
					m_playing_video = video_info;
					playing_video_exist=true;
				}
				//改变播放器状态
				player_next_state = IDLESSE_STATE;

				if (result)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
			break;
		case IDLESSE_STATE:
			{
				if (play_ad)
				{
					//首先判断是否有文化部的开机广告
					ad_result = get_ADItem_culture(DISPLAY_DEVICE_TV,SCENE_INTER_MODE,&ad_item,SCENE_INTER_IDLE);
					if (1==ad_result)
					{
						//播放文化部的视频
						//允许切掉
						m_allow_cut = true;
						return 0;
					}
				}

				result = m_public_video_manager.get_idlesse_video(video_info);
				if (result)
				{
					//记录下正在播放的视频
					m_playing_video = video_info;
					playing_video_exist=true;
				}
				//改变播放器状态
				player_next_state = IDLESSE_STATE;

				if (result)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
			break;
		case PLAY_SONG_STATE:
			{
				bool song_list_empty=false;

				song_list_empty = m_select_song_manager.empty();
				if (song_list_empty)
				{
					if (play_ad)
					{
						//首先判断是否有文化部的开机广告
						ad_result = get_ADItem_culture(DISPLAY_DEVICE_TV,SCENE_INTER_MODE,&ad_item,SCENE_INTER_IDLE);
						if (1==ad_result)
						{
							//播放文化部的视频
							//允许切掉
							m_allow_cut = true;
							return 0;
						}
					}

					//没有选择的歌曲，转到播放结束
					result = m_public_video_manager.get_end_video(video_info);
					if (result)
					{
						//记录下正在播放的视频
						m_playing_video = video_info;
						playing_video_exist=true;
					}
					//改变播放器状态
					player_cur_state = END_STATE;
					player_next_state = IDLESSE_STATE;
				}
				else
				{
					if (play_ad)
					{
						//首先判断是否有文化部的开机广告
						ad_result = get_ADItem_culture(DISPLAY_DEVICE_TV,SCENE_INTER_MODE,&ad_item,SCENE_INTER_HASSONG);
						if (1==ad_result)
						{
							//插播广告不允许切换
							m_allow_cut = false;
							//播放文化部的视频
							return 0;
						}
					}

					result = m_select_song_manager.get_play_song(video_info);
					if (result)
					{
						//记录下正在播放的视频
						m_playing_video = video_info;
						playing_video_exist=true;
					}
					//改变播放器状态
					song_list_empty = m_select_song_manager.empty();
					if (song_list_empty)
					{
						player_next_state = END_STATE;
					}
					else
					{
						player_next_state = PLAY_SONG_STATE;
					}
				}

				if (result)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
			break;
		case PLAY_DJ_STATE: //播放DJ状态
			{
				//得到dj
				result = m_dj_song_manager.get_next_play_dj_song(video_info);
				if (result)
				{
					//记录下正在播放的视频
					m_playing_video = video_info;
					playing_video_exist=true;
					//改变播放器状态
					player_cur_state = PLAY_DJ_STATE;
					player_next_state = PLAY_DJ_STATE;

					return 1;
				}
				else
				{
					return -1;
				}
			}
			break;
		case TEST_SONG_STATE:  //测机状态
			{
				result = m_select_song_manager.get_play_test_song(video_info);
				if (result)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
			break;
		default:
			break;
		}

		return -1;
		
	}
	catch (...)
	{
		
	}
	return -1;
}

bool video_play_manager::get_next_play_song(song_info& song)
{
	return m_select_song_manager.get_next_song(song);
}

bool video_play_manager::set_playing_video(song_info &video_info)
{
	m_playing_video = video_info;
	playing_video_exist=true;

	return true;
}

bool video_play_manager::get_playing_video(song_info &video_info)
{
	if (!playing_video_exist)
	{
		return false;
	}

	video_info = m_playing_video;

	return true;
}

bool video_play_manager::add_select_song(song_info &song_information,bool priority)
{
	return m_select_song_manager.add_select_song(song_information,priority);
}

enum PLAYER_PLAY_STATE video_play_manager::get_player_cur_state(void)
{
	return player_cur_state;
}

enum PLAYER_PLAY_STATE video_play_manager::get_player_next_state(void)
{
	return player_next_state;
}

bool video_play_manager::add_sing_song(song_info &song_information)
{
	return m_select_song_manager.add_sing_song(song_information);
}

bool video_play_manager::modify_down_load_select_song(TCHAR* song_id,TCHAR* server_path,int server_pos,TCHAR* relative_path /* = NULL */)
{
	return m_select_song_manager.modify_down_load_select_song(song_id,server_path,server_pos, relative_path);
}

bool video_play_manager::set_player_cur_state(enum PLAYER_PLAY_STATE player_state)
{
	bool song_exist=false;

	//设置播放器的状态
	player_cur_state = player_state;
	//同时修改下一个状态
	switch(player_cur_state)
	{
	default:
	case BEGIN_STATE:
	case END_STATE:
	case IDLESSE_STATE:
		{
			song_exist = m_select_song_manager.empty();
			if (song_exist)
			{
				player_next_state = IDLESSE_STATE;
			}
			else
			{
				player_next_state = PLAY_SONG_STATE;
			}
		}
		break;
	case PLAY_SONG_STATE:
		{
			song_exist = m_select_song_manager.empty();
			if (song_exist)
			{
				player_next_state = END_STATE;
			}
			else
			{
				player_next_state = PLAY_SONG_STATE;
			}
		}
		break;
	case PLAY_DJ_STATE:
		{
			player_next_state = PLAY_DJ_STATE;
		}
		break;
	case TEST_SONG_STATE:
		{
			player_cur_state = TEST_SONG_STATE;
			player_next_state = TEST_SONG_STATE;
		}
		break;
	}
	return true;
}

bool video_play_manager::set_player_next_state(enum PLAYER_PLAY_STATE player_state)
{
	//设置播放器的下一个状态
	player_next_state = player_state;

	return true;
}

bool video_play_manager::make_song_list_xml(std::wstring &song_list_xml,enum SHOW_SONG_LIST_TYPE song_type,enum PAGE_OPERATE page_operate,FLASH_SONG_SHOW_MODE song_show_mode,int page_index)
{
	return m_select_song_manager.make_song_list_xml(song_list_xml,song_type,page_operate,song_show_mode,page_index);
}

bool video_play_manager::get_page_row_info(int &row,int &cur_page_number,int &total_page_count,enum SHOW_SONG_LIST_TYPE song_type)
{
	return m_select_song_manager.get_page_row_info(row,cur_page_number,total_page_count,song_type);
}

bool video_play_manager::get_atmosphere_wave_info(int wave_type,TCHAR *audio_path,TCHAR *picture_path,bool soft_code)
{
	return m_public_video_manager.get_atmosphere_wave_info(wave_type,audio_path,picture_path,soft_code);
}

int video_play_manager::get_select_song_count(int count_type)
{
	return m_select_song_manager.get_select_song_count(count_type);
}

int video_play_manager::get_sing_song_count(void)
{
	return m_select_song_manager.get_sing_song_count();
}

int video_play_manager::delete_select_song(int song_number,bool relative_position)
{
	return m_select_song_manager.delete_select_song(song_number,relative_position);
}

int video_play_manager::delete_select_song_by_id(TCHAR *song_id)
{
	return m_select_song_manager.delete_select_song_by_id(song_id);
}

int video_play_manager::get_select_song_absolute_position(int song_number)
{
	return m_select_song_manager.get_select_song_absolute_position(song_number);
}

int video_play_manager::priority_select_song(int song_number,bool relative_position)
{
	return m_select_song_manager.priority_select_song(song_number,relative_position);
}

int video_play_manager::drag_sort_select_song(int nOrigin, int nDestination, bool relative_position)
{
	return m_select_song_manager.drag_sort_select_song(nOrigin, nDestination, relative_position);
}

bool video_play_manager::random_sort_select_song()
{
	return m_select_song_manager.random_sort_select_song();
}

bool video_play_manager::get_select_song_information(song_info &song_information, int star_suffix,bool relative_position)
{
	return m_select_song_manager.get_select_song_information(song_information,star_suffix,relative_position);
}

bool video_play_manager::get_sing_song_information(song_info &song_information,int select_suffix,bool relative_position)
{
	return m_select_song_manager.get_sing_song_information(song_information,select_suffix,relative_position);
}

bool video_play_manager::select_song_switch_position(int first_switch_pos,int second_switch_pos,bool change_page_switch)
{
	return m_select_song_manager.select_song_switch_position(first_switch_pos,second_switch_pos,change_page_switch);
}

bool video_play_manager::get_environment_wave_info(int wave_type,TCHAR *path)
{
	return m_public_video_manager.get_environment_wave_info(wave_type,path);
}

bool video_play_manager::video_allow_cut(void)
{
	return m_allow_cut;
}

bool video_play_manager::query_select_song_by_id(TCHAR *song_id,int &play_number,bool isDown /* = true */)
{
	return m_select_song_manager.query_select_song_by_id(song_id,play_number, isDown);
}

bool video_play_manager::query_select_song_by_id_ex(TCHAR *song_id,int &play_number)
{
	return m_select_song_manager.query_select_song_by_id_ex(song_id,play_number);
}

void video_play_manager::set_show_page_number(int page_number)
{
	return m_select_song_manager.set_show_page_number(page_number);
}

void video_play_manager::clear_select_song(bool clear_sing)
{
	return m_select_song_manager.clear_select_song(clear_sing);
}

bool video_play_manager::get_test_song_name(TCHAR *cur_song_name,TCHAR *next_song_name)
{
	return m_select_song_manager.get_test_song_name(cur_song_name,next_song_name);
}

bool video_play_manager::get_test_song_by_suffix(song_info& song,int song_suffix)
{
	return m_select_song_manager.get_test_song_by_suffix(song,song_suffix);
}

bool video_play_manager::add_dj_song(song_info &dj_song_info)
{
	return m_dj_song_manager.add_dj_song(dj_song_info);
}

int video_play_manager::get_dj_song_count(void)
{
	return m_dj_song_manager.get_dj_song_count();
}

void video_play_manager::set_test_song_play_order(bool next_song)
{
	m_select_song_manager.set_test_song_play_order(next_song);
}

bool video_play_manager::change_page_insert(bool pre_page,int src_position,bool first_page_insert,std::wstring &change_song_xml)
{
	return m_select_song_manager.change_page_insert(pre_page,src_position,first_page_insert,change_song_xml);
}

int video_play_manager::get_flicker_item_number(void)
{
	return m_select_song_manager.get_flicker_item_number();
}

void video_play_manager::query_idlesse_song_info(DB_Query &db_query_class)
{
	return m_public_video_manager.query_idlesse_song_info(db_query_class);
}

void video_play_manager::mess_selected_song(void)
{
	return m_select_song_manager.mess_selected_song();
}

int video_play_manager::get_cur_idlesse_video_number()
{
	return m_public_video_manager.get_cur_idlesse_video_number();
}

void video_play_manager::set_cur_idlesse_video_number(int number)
{
	m_public_video_manager.set_cur_idlesse_video_number(number);
}

void video_play_manager::set_cur_idlesse_list()
{
	m_public_video_manager.set_cur_idlesse_list();
}
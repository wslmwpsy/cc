#include "StdAfx.h"
#include ".\dj_song_manager.h"

dj_song_manager::dj_song_manager(void)
{
	m_dj_song_count = 0;
	m_cur_play_dj_number = 0;
}

dj_song_manager::~dj_song_manager(void)
{
}

bool dj_song_manager::add_dj_song(song_info &dj_song_info)
{
	try
	{
		if (m_dj_song_count>=DJ_SONG_MAX_COUNT)
		{
			return false;
		}
		m_dj_song_info[m_dj_song_count]=dj_song_info;
		m_dj_song_count++;
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool dj_song_manager::get_next_play_dj_song(song_info &dj_song_info)
{
	try
	{
		if (m_dj_song_count<=0)
		{
			return false;
		}
		dj_song_info = m_dj_song_info[m_cur_play_dj_number];
		m_cur_play_dj_number++;
		if (m_cur_play_dj_number>=m_dj_song_count)
		{
			m_cur_play_dj_number=0;
		}
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

int dj_song_manager::get_dj_song_count(void)
{
	return m_dj_song_count;
}
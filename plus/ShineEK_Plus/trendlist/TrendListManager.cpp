#include "StdAfx.h"
#include "TrendListManager.h"
#include "..\file\config_file.h"

extern std::wstring g_all_language[];
CTrendListManager::CTrendListManager(void)
{
// 	m_TrendListSongInfo = NULL;

	initdata();
	config_file_manager config_file;
	m_default_song_color = config_file.read_string(L"song_name_color",L"default_color",L"0xFFFFFF");       //默认歌曲颜色
	m_playing_song_color = config_file.read_string(L"song_name_color",L"playing_song_color",L"0xFF0000");  //正播放歌曲的颜色
	m_select_song_color = config_file.read_string(L"song_name_color",L"select_song_color",L"0xFF9900");    //选择歌曲颜色

}

CTrendListManager::~CTrendListManager(void)
{
	freedata();
}

void CTrendListManager::initdata()
{
	m_strName.clear();
	m_strTheme.clear();
	m_strUpdateDate.clear();
	m_nSongCount = 0;
// 	m_TrendListSongInfo = new Tag_Trend_List_Song_Info[10];//每个榜单10首歌
	memset(m_TrendListSongInfo, 0x00, sizeof(Tag_Trend_List_Song_Info)*10);

}
 void CTrendListManager::freedata()
 {
	 m_strName.clear();
	 m_strTheme.clear();
	 m_strUpdateDate.clear();
	 m_nSongCount = 0;
// 	 if (m_TrendListSongInfo != NULL)
// 	 {
// 		 delete [] m_TrendListSongInfo;
// 		 m_TrendListSongInfo = NULL;
// 	 }
 }
bool CTrendListManager::make_trend_list_sub_xml(wstring &strSubXml, video_play_manager &video_manager)
{
	bool result = false;  
	TCHAR szTemp[1024] = {0x0};
	int play_number;
	TCHAR playing_id[256];
	song_info playing_info;

	//得到正在播放的歌曲
	result = video_manager.get_playing_video(playing_info);
	if (result)
	{
		//存在正在播放的视频
		playing_info.get_song_id(playing_id);
	}
	swprintf(szTemp, L"<trend_list_info name=\"%s\" updatetime=\"%s\" imgpath=\"%s\">", m_strName.c_str(),
		m_strUpdateDate.c_str(), m_strImgPath.c_str());

	strSubXml += szTemp;

	if (m_nSongCount == 0)
	{
		strSubXml += L"</trend_list_info>";
		return true;
	}
	for (int i = 0; i < m_nSongCount; i++)
	{
		memset(szTemp,0x0,sizeof(szTemp));

		if (_tcscmp(m_TrendListSongInfo[i].szSongId, L"") == 0)
		{
			continue;
		}

		play_number = 0;
		//正在播放的歌曲
		if (_tcscmp(m_TrendListSongInfo[i].szSongId, playing_id) == 0 && _tcscmp(m_TrendListSongInfo[i].szSongId, L"") != 0)
		{
// 			result = video_manager.query_select_song_by_id(m_TrendListSongInfo[i].szSongId, play_number);
// 			if (result)
// 			{
// 				if (play_number < 0)
// 					wsprintf(szTemp, L"<item song_id=\"%s\" song_name=\"%s[%s]\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
// 					m_TrendListSongInfo[i].szSongId, m_TrendListSongInfo[i].szSongName, g_all_language[5].c_str(), m_TrendListSongInfo[i].szSongName, m_TrendListSongInfo[i].song_top, m_TrendListSongInfo[i].song_type, m_playing_song_color.c_str()); //拼xml
// 				else
// 					wsprintf(szTemp, L"<item song_id=\"%s\" song_name=\"%s[%s%d]\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
// 					m_TrendListSongInfo[i].szSongId, m_TrendListSongInfo[i].szSongName, g_all_language[4].c_str(), play_number, m_TrendListSongInfo[i].szSingerName, m_TrendListSongInfo[i].song_top, m_TrendListSongInfo[i].song_type, m_select_song_color.c_str()); //拼xml
// 			}
// 			else
				wsprintf(szTemp, L"<item song_id=\"%s\" song_name=\"%s[%s]\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
				m_TrendListSongInfo[i].szSongId, m_TrendListSongInfo[i].szSongName, g_all_language[5].c_str(), m_TrendListSongInfo[i].szSingerName, m_TrendListSongInfo[i].song_top, m_TrendListSongInfo[i].song_type, m_playing_song_color.c_str()); //拼xml
		}else{
			result = video_manager.query_select_song_by_id(m_TrendListSongInfo[i].szSongId, play_number);
			if (result)
			{
				if (play_number < 0)
					wsprintf(szTemp, L"<item song_id=\"%s\" song_name=\"%s[%s]\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
						m_TrendListSongInfo[i].szSongId, m_TrendListSongInfo[i].szSongName, g_all_language[123].c_str(), m_TrendListSongInfo[i].szSingerName, m_TrendListSongInfo[i].song_top, m_TrendListSongInfo[i].song_type, m_select_song_color.c_str()); //拼xml
				else
				wsprintf(szTemp, L"<item song_id=\"%s\" song_name=\"%s[%s%d]\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
					m_TrendListSongInfo[i].szSongId, m_TrendListSongInfo[i].szSongName, g_all_language[4].c_str(), play_number, m_TrendListSongInfo[i].szSingerName, m_TrendListSongInfo[i].song_top, m_TrendListSongInfo[i].song_type, m_select_song_color.c_str()); //拼xml
			}else{
				wsprintf(szTemp, L"<item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\" song_top=\"%d\" song_type=\"%d\" color=\"%s\"/>",
					m_TrendListSongInfo[i].szSongId, m_TrendListSongInfo[i].szSongName, m_TrendListSongInfo[i].szSingerName, m_TrendListSongInfo[i].song_top, m_TrendListSongInfo[i].song_type, m_default_song_color.c_str()); //拼xml
			}
		}

		strSubXml += szTemp;
	}
	strSubXml += L"</trend_list_info>";

	return true;
}

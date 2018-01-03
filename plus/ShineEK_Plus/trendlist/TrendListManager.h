#pragma once
#include "../song/song_info.h"
#include "../song/video_play_manager.h"
#include "../message.h"

// //榜单信息
// typedef struct Tag_Trend_List_Info 
// {
// 	TCHAR szName[64];		//名称
// 	TCHAR szTheme[64];		//主题
// 	long  lUpdateDate;		//更新日期
// 
// 
// }TrendListInfo,*TREND_LIST_INFO;
class CTrendListManager
{
public:
	CTrendListManager(void);
	~CTrendListManager(void);

	void initdata();
	void freedata();
	bool make_trend_list_sub_xml(wstring &strSubXml, video_play_manager &video_manager);

public:
	wstring m_strName;				//榜单名称
	wstring m_strTheme;				//榜单主题
	wstring m_strImgPath;			//图片路径
	wstring	m_strUpdateDate;		//更新日期
	song_info m_PlayingSongInfo;	//正在播放的榜单歌曲信息
	Tag_Trend_List_Song_Info m_TrendListSongInfo[10];
	int m_nSongCount;				//歌曲个数

	std::wstring m_default_song_color;   //默认歌曲颜色
	std::wstring m_playing_song_color;   //正播放歌曲的颜色
	std::wstring m_select_song_color;    //选择歌曲颜色
};


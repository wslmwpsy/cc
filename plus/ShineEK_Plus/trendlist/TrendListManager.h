#pragma once
#include "../song/song_info.h"
#include "../song/video_play_manager.h"
#include "../message.h"

// //����Ϣ
// typedef struct Tag_Trend_List_Info 
// {
// 	TCHAR szName[64];		//����
// 	TCHAR szTheme[64];		//����
// 	long  lUpdateDate;		//��������
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
	wstring m_strName;				//������
	wstring m_strTheme;				//������
	wstring m_strImgPath;			//ͼƬ·��
	wstring	m_strUpdateDate;		//��������
	song_info m_PlayingSongInfo;	//���ڲ��ŵİ񵥸�����Ϣ
	Tag_Trend_List_Song_Info m_TrendListSongInfo[10];
	int m_nSongCount;				//��������

	std::wstring m_default_song_color;   //Ĭ�ϸ�����ɫ
	std::wstring m_playing_song_color;   //�����Ÿ�������ɫ
	std::wstring m_select_song_color;    //ѡ�������ɫ
};


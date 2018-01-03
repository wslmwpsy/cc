#pragma once
#include "../file/config_file.h"
#include "../common/StringCodeConversion.h"
#include "../message.h"
#include <vector>

class CInterScreenManager
{
public:
	CInterScreenManager(void);
	~CInterScreenManager(void);

	/**/
	bool ReadConfigFile();
	/*
	解析配置：101,102,201,202
	*/
	bool ParseConfigString(wstring strSour, vector<wstring> &vecDest);
	/*
	nModule:1:滚动条 2:列表 3:窗口
	*/
	bool IsMember(TCHAR *pwszSour, int nModule, bool bFlag = true);
	bool IsOneOfString(TCHAR *pwszSour, vector<wstring> vecDest);
	/**/
	void SetInterScreenInfo(Tag_Inter_Screen_Info *p_inter_screen_info);
	void GetInterScreenInfo(Tag_Inter_Screen_Info *p_inter_screen_info);
	/**/
	void SetScrollTipInfo(Tag_Scroll_Tip_Info *p_scroll_tip_info, bool bTop);
	void GetScrollTipInfo(Tag_Scroll_Tip_Info *p_scroll_tip_info, bool bTop);
	/**/
	void SetListInfo(Tag_List_Info *p_list_info, bool bLeft);
	void GetListInfo(Tag_List_Info *p_list_info, bool bLeft);
	/**/
	void SetWndInfo(Tag_Wnd_Info *p_wnd_info, bool bMaster);
	void GetWndInfo(Tag_Wnd_Info *p_wnd_info, bool bMaster);
public:
	config_file_manager		m_config_manager;			//配置文件管理
	Tag_Inter_Screen_Info	m_inter_screen_info;		//互动场景屏信息
	vector<wstring>			m_vec_scroll_tip_info_top;		//滚动条
	vector<wstring>			m_vec_scroll_tip_info_bottom;	//滚动条
	vector<wstring>			m_vec_list_info_left;			//列表
	vector<wstring>			m_vec_list_info_right;			//列表
	vector<wstring>			m_vec_wnd_info_master;			//窗口
	vector<wstring>			m_vec_wnd_info_slave;			//窗口

	wstring					m_str_scroll_tip_info_top;		//滚动条
	wstring					m_str_scroll_tip_info_bottom;	//滚动条
	wstring					m_str_list_info_left;			//列表
	wstring					m_str_list_info_right;			//列表
	wstring					m_str_wnd_info_master;			//窗口
	wstring					m_str_wnd_info_slave;			//窗口
};


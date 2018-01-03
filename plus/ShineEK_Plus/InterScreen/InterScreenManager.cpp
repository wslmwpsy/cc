#include "StdAfx.h"
#include "InterScreenManager.h"
#include "..\file\log.h"

CInterScreenManager::CInterScreenManager(void)
{
	memset(&m_inter_screen_info, 0x00, sizeof(Tag_Inter_Screen_Info));
	ReadConfigFile();
}

CInterScreenManager::~CInterScreenManager(void)
{
}

bool CInterScreenManager::ReadConfigFile()
{
	m_inter_screen_info.n_mode = m_config_manager.read_integer(L"inter_screen", L"inter_screen_mode", 2);
	m_inter_screen_info.b_exsit = m_config_manager.read_boolean(L"inter_screen", L"open_inter_screen", false);
	m_inter_screen_info.n_display_number = m_config_manager.read_integer(L"display",L"inter_screen_number",3);
	if (m_inter_screen_info.n_mode == 2 || m_inter_screen_info.n_mode == 3)
	{
		m_inter_screen_info.n_show_activity_wnd = m_config_manager.read_integer(L"inter_screen", L"show_activity_wnd", 0);
	}
	else
		m_inter_screen_info.n_show_activity_wnd = 0;
	m_inter_screen_info.b_activity_wnd_full_screen = m_config_manager.read_boolean(L"inter_screen", L"activity_wnd_full_screen", false);
	m_inter_screen_info.n_x = m_config_manager.read_integer(L"inter_screen", L"inter_screen_x", 0);
	m_inter_screen_info.n_y = m_config_manager.read_integer(L"inter_screen", L"inter_screen_y", 0);
	m_inter_screen_info.n_width = m_config_manager.read_integer(L"inter_screen", L"inter_screen_width", 0);
	m_inter_screen_info.n_height = m_config_manager.read_integer(L"inter_screen", L"inter_screen_height", 0);

	TCHAR wszSection[256] = {0x0};
	swprintf(wszSection, L"inter_screen_mode%d", m_inter_screen_info.n_mode);

	if (m_inter_screen_info.n_mode == 1)
	{
		m_str_wnd_info_master = m_config_manager.read_string(wszSection, L"wnd_master", L"");
		ParseConfigString(m_str_wnd_info_master, m_vec_wnd_info_master);
		m_str_scroll_tip_info_top = m_config_manager.read_string(wszSection, L"scroll_tip_top", L"");
		ParseConfigString(m_str_scroll_tip_info_top, m_vec_scroll_tip_info_top);
		m_str_scroll_tip_info_bottom = m_config_manager.read_string(wszSection, L"scroll_tip_bottom", L"");
		ParseConfigString(m_str_scroll_tip_info_bottom, m_vec_scroll_tip_info_bottom);
		m_str_list_info_left = m_config_manager.read_string(wszSection, L"list_left", L"");
		ParseConfigString(m_str_list_info_left, m_vec_list_info_left);
		m_str_list_info_right = m_config_manager.read_string(wszSection, L"list_right", L"");
		ParseConfigString(m_str_list_info_right, m_vec_list_info_right);
	}
	else if (m_inter_screen_info.n_mode == 2)
	{
		m_str_wnd_info_master = m_config_manager.read_string(wszSection, L"wnd_master", L"");
		ParseConfigString(m_str_wnd_info_master, m_vec_wnd_info_master);
		m_str_wnd_info_slave = m_config_manager.read_string(wszSection, L"wnd_slave", L"");
		ParseConfigString(m_str_wnd_info_slave, m_vec_wnd_info_slave);
		m_str_scroll_tip_info_top = m_config_manager.read_string(wszSection, L"scroll_tip_top", L"");
		ParseConfigString(m_str_scroll_tip_info_top, m_vec_scroll_tip_info_top);
		m_str_scroll_tip_info_bottom = m_config_manager.read_string(wszSection, L"scroll_tip_bottom", L"");
		ParseConfigString(m_str_scroll_tip_info_bottom, m_vec_scroll_tip_info_bottom);
	}
	else if (m_inter_screen_info.n_mode == 3)
	{
		m_str_wnd_info_master = m_config_manager.read_string(wszSection, L"wnd_master", L"");
		ParseConfigString(m_str_wnd_info_master, m_vec_wnd_info_master);
		m_str_wnd_info_slave = m_config_manager.read_string(wszSection, L"wnd_slave", L"");
		ParseConfigString(m_str_wnd_info_slave, m_vec_wnd_info_slave);
		m_str_list_info_right = m_config_manager.read_string(wszSection, L"list_right", L"");
		ParseConfigString(m_str_list_info_right, m_vec_list_info_right);
	}

	return true;
}
/**/
void CInterScreenManager::SetInterScreenInfo(Tag_Inter_Screen_Info *p_inter_screen_info)
{
	memcpy(&m_inter_screen_info, p_inter_screen_info, sizeof(Tag_Inter_Screen_Info));
}
void CInterScreenManager::GetInterScreenInfo(Tag_Inter_Screen_Info *p_inter_screen_info)
{
	memcpy(p_inter_screen_info, &m_inter_screen_info, sizeof(Tag_Inter_Screen_Info));
}
/**/
void CInterScreenManager::SetScrollTipInfo(Tag_Scroll_Tip_Info *p_scroll_tip_info, bool bTop)
{
	if (bTop)
		memcpy(&m_inter_screen_info.top_scroll_tip_info, p_scroll_tip_info, sizeof(Tag_Scroll_Tip_Info));
	else
		memcpy(&m_inter_screen_info.bottom_scroll_tip_info, p_scroll_tip_info, sizeof(Tag_Scroll_Tip_Info));
}
void CInterScreenManager::GetScrollTipInfo(Tag_Scroll_Tip_Info *p_scroll_tip_info, bool bTop)
{
	if (bTop)
		memcpy(p_scroll_tip_info, &m_inter_screen_info.top_scroll_tip_info, sizeof(Tag_Scroll_Tip_Info));
	else
		memcpy(p_scroll_tip_info, &m_inter_screen_info.bottom_scroll_tip_info, sizeof(Tag_Scroll_Tip_Info));
}
/**/
void CInterScreenManager::SetListInfo(Tag_List_Info *p_list_info, bool bLeft)
{
	if (bLeft)
		memcpy(&m_inter_screen_info.left_list_info, p_list_info, sizeof(List_Info));
	else
		memcpy(&m_inter_screen_info.right_list_info, p_list_info, sizeof(List_Info));
}
void CInterScreenManager::GetListInfo(Tag_List_Info *p_list_info, bool bLeft)
{
	if (bLeft)
		memcpy(p_list_info, &m_inter_screen_info.left_list_info, sizeof(List_Info));
	else
		memcpy(p_list_info, &m_inter_screen_info.right_list_info, sizeof(List_Info));
}
/**/
void CInterScreenManager::SetWndInfo(Tag_Wnd_Info *p_wnd_info, bool bMaster)
{
	if (bMaster)
		memcpy(&m_inter_screen_info.master_wnd_info, p_wnd_info, sizeof(Wnd_Info));
	else
		memcpy(&m_inter_screen_info.slave_wnd_info, p_wnd_info, sizeof(Wnd_Info));
}
void CInterScreenManager::GetWndInfo(Tag_Wnd_Info *p_wnd_info, bool bMaster)
{
	if (bMaster)
		memcpy(p_wnd_info, &m_inter_screen_info.master_wnd_info, sizeof(Wnd_Info));
	else
		memcpy(p_wnd_info, &m_inter_screen_info.slave_wnd_info, sizeof(Wnd_Info));
}
bool CInterScreenManager::IsMember(TCHAR *pwszSour, int nModule, bool bFlag)
{
	bool bRet1 = false;
	bool bRet2 = false;

	if (nModule == 1)
	{
		//if (bFlag)
			bRet1 = IsOneOfString(pwszSour, m_vec_scroll_tip_info_top);
		//else
			bRet2 = IsOneOfString(pwszSour, m_vec_scroll_tip_info_bottom);
	}
	else if (nModule == 2)
	{
		//if (bFlag)
			bRet1 = IsOneOfString(pwszSour, m_vec_list_info_left);
		//else
			bRet2 = IsOneOfString(pwszSour, m_vec_list_info_right);
	}
	else if (nModule == 3)
	{
		//if (bFlag)
			bRet1 = IsOneOfString(pwszSour, m_vec_wnd_info_master);
		//else
			bRet2 = IsOneOfString(pwszSour, m_vec_wnd_info_slave);
	}
	else
	{
	}
		
	return bRet1||bRet2;
}
bool CInterScreenManager::ParseConfigString(wstring strSour, vector<wstring> &vecDest)
{
	int nIndex = 0;
	const char *pTok = ",";
	char szTmp[256] = {0x0};
	TCHAR wszTmp[256] = {0x00};
	string_conversion string_conv;

	string_conv.widechar_to_multibyte(strSour.c_str(), szTmp, 256);
	char *pTmp = strtok(szTmp, pTok);
	
	while(pTmp)
	{
		memset(wszTmp, 0x00, 256);
		string_conv.multibyte_to_widechar(pTmp, wszTmp, 256);
		vecDest.push_back((wstring)wszTmp);
		pTmp = strtok(NULL, pTok);
		nIndex++;
	}

	return true;
}

bool CInterScreenManager::IsOneOfString(TCHAR *pwszSour, vector<wstring> vecDest)
{
	int nLen = vecDest.size();

	vector<wstring>::iterator iter = vecDest.begin();
	for (; iter != vecDest.end(); ++iter)
	{
		if ((*iter).compare(pwszSour) == 0)
		{
			return true;
		}
	}

	return false;
}
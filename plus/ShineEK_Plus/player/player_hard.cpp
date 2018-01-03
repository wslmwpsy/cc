// player_hard.cpp
//

#include "StdAfx.h"
#include "player_hard.h"
#include "..\file\config_file.h"
#include "..\common\StringCodeConversion.h"
#include "..\folder_name.h"
#include "..\file\log.h"

#pragma warning(disable: 4311)

player_hard::player_hard()
	: m_use_osd(false),
	pOSDBufWelcomeText(0), pOSDBufVersionText1(0), pOSDBufVersionText2(0),
	pOSDBufBigLogo(0), osd_text_handle(0), bLargeLogoPlaying(false),
	osd_control_logo_handle(0),osd_bmp_handle(0),osd_bk_logo_handle(0)
{
	TV_or_VGA = false;
	m_ScreenHwnd = NULL;
	TCHAR *install_path=NULL;

	memset(osd_logo_handle, 0x0, sizeof(osd_logo_handle));
	memset(ad_osd_logo_handle,0x0,sizeof(ad_osd_logo_handle));
	for (int i=0;i<100;i++)
	{
		memset(osd_buf_logo_path[i], 0x0, sizeof(osd_buf_logo_path[i]));
		memset(ad_osd_logo_path[i],0x0,sizeof(ad_osd_logo_path[i]));
	}
	memset(m_install_path,0x0,sizeof(m_install_path));
	memset(m_screen_show_folder_name,0x0,sizeof(m_screen_show_folder_name));

	//得到安装路径
	GetModuleFileName(NULL, m_install_path, sizeof(m_install_path));
	install_path = _tcsrchr(m_install_path, _T('\\'));
	if (install_path)
	{
		install_path[0] = '\0';
	}

	//得到屏显文件夹的名字
	_tcscpy(m_screen_show_folder_name,g_folder_name[6]);
}

player_hard::~player_hard()
{
}

bool player_hard::create(CWnd *parent_wnd)
{
	try
	{
		if (m_hard_player.Create(NULL, WS_CHILD, CRect(0,0,0,0), parent_wnd, 5412) == FALSE)
		{
			return false;
		}
		//设置消息的句柄，消息发送给父窗口
		m_hard_player.Ctrl_SetNotifyWindow((long)parent_wnd->m_hWnd);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void player_hard::destory()
{
	// 停止并关闭播放控件
	stop_all();
}

// 初始化播放控件
bool player_hard::initialize()
{
	try
	{
		long result=false;

		// 初始化解压卡注册信息
		//InitCardRegistry();

		// 检查并初始化解压卡硬件
		m_hard_player.CheckHardware();
		m_hard_player.Stop();
		m_hard_player.CloseFile();
		m_hard_player.CloseDrv();
	
		// 打开硬件，此时控件将检查狗
		result = m_hard_player.OpenDrv();
		if (result < 0)
		{
			return false;
		}
		//m_hard_player.Stop();

		return true;
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
//		WriteLog(__FL__, buffer);
		return false;
	}
	return true;
}

void player_hard::close_device(void)    //关闭解压卡
{
	//停止所有的播放
	stop_all();
	//关闭设备
	m_hard_player.CloseDrv();
	m_hard_player.ResetDriver();

	return;
}

void player_hard::open_device(void)     //打开解压卡
{
    m_hard_player.OpenDrv();		
	return;
}

// 初始化解压卡注册信息
bool player_hard::InitCardRegistry()
{
	// 修改注册表信息
	HKEY hKey;
	DWORD value;
	bool flag = false;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Sigma Designs\\REALmagic\\20", 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
	{
		value = 0;
		if (RegSetValueEx(hKey, L"EnableSpdif", 0, REG_DWORD, (BYTE*)&value, 4) == ERROR_SUCCESS)
		{
			flag = true;
		}
		RegCloseKey(hKey);
	}
		
	flag = false;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Sigma Designs\\REALmagic\\20", 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
	{
		value = 1;
		if (RegSetValueEx(hKey, L"PcmOutputSpdif", 0, REG_DWORD, (BYTE*)&value, 4) == ERROR_SUCCESS)
		{
			flag = true;
		}
		RegCloseKey(hKey);
	}
		
	return flag;
}



bool player_hard::InitOSD()
{
	// 设置色板
	TCHAR palOsd[256];

	memset(palOsd,0x0,sizeof(palOsd));
	swprintf(palOsd,L"%s\\%s\\色板.bmp",m_install_path,m_screen_show_folder_name);

	FILE* fp = _wfopen(palOsd, L"r");
	if (fp == 0)
	{
		return false;
	}
	else
	{
		fclose(fp);
		fp=NULL;
	}
	
	int iret = m_hard_player.InitOSD(1, palOsd, 15);
	
	// 设置使用OSD标志
	//m_use_osd = (iret != -1);
	m_use_osd = true;

	return m_use_osd;
}

int  player_hard::stop_all()
{
	try
	{
		// 停止硬解压卡
		if (m_hard_player)
		{
			short player_state = m_hard_player.GetState();
			if (player_state != PLAYER_STATE_ERROR)
			{
				//停止视频
				m_hard_player.Stop();
				m_hard_player.CloseFile();
				//停止预览视频
				//m_hard_player.Preview_Close();
				//停止电视直播
				// m_hard_player.TV_Close();

				if (m_use_osd)
				{
					//使用osd，关闭所有的osd

					//关闭动态 logo
					StopOSDLogo();
					//停止text
					StopOSDText();
					//关闭控制logo
					StopControlOSD();

					//关闭了所有的osd之后，调用该函数
					m_hard_player.FinishOSD();
					m_use_osd = false;
				}

				//关闭设备
				m_hard_player.CloseDrv();
			}
		}

		return 1;
	}
	catch (...)
	{
		
	}
	return 0;
}

void player_hard::play()
{
	try
	{
		m_hard_player.Play();
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常Play\r\n");
//		WriteLog(__FL__, buffer);
	}
	//m_VideoWindow.m_bPlayState = true;
}

void player_hard::stop()
{
	try
	{
		m_hard_player.Stop();
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常Stop\r\n");
//		WriteLog(__FL__, buffer);
	}
}

void player_hard::pause()
{
	try
	{
		m_hard_player.Pause();
	}
	catch (...) 
	{	
		try
		{
			//m_hard_player.Pause1();
		}
		catch (CException* e) 
		{
			// 写入日志
			TCHAR buffer[256];
			e->GetErrorMessage(buffer, 256);
			_tcscat(buffer, L"   异常Pause1\r\n");
//			WriteLog(__FL__, buffer);
		}
	}
}

void player_hard::reset()
{
	m_hard_player.Reset();
	return;
}

void player_hard::set_volume(int l, int r)
{
	try
	{
		//TCHAR log[256];

	//	memset(log,0x0,sizeof(log));
	//	swprintf(log,L"歌曲音量：%d",l);
	//	WriteLog(__FL__, log);

		m_hard_player.Volume((short)l,(short)r);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常Volume\r\n");
//		WriteLog(__FL__, buffer);
	}
}

void player_hard::balance(int soundtrack)
{
	try
	{
		m_hard_player.Balance(static_cast<short>(soundtrack));
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常Balance\r\n");
//		WriteLog(__FL__, buffer);
	}
}

void player_hard::set_track(int trackno)
{
	try
	{
		m_hard_player.SetTrackNo(static_cast<short>(trackno));
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常SetTrackNo\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

void player_hard::set_play_file_path(const TCHAR* s)
{
	try
	{
		m_hard_player.SetGszFileName(s);		
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常SetGszFileName\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

long player_hard::open_file()
{
	try
	{
		m_hard_player.OpenFile();

		return 1;
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常OpenFile\r\n");
//		WriteLog(__FL__, buffer);
		return 0;
	}			
}

void player_hard::close_file()
{
	try
	{
		m_hard_player.CloseFile();
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常CloseFile\r\n");
//		WriteLog(__FL__, buffer);
	}			
}

long player_hard::set_soft_decode(HWND soft_hwnd)
{
	try
	{
		return m_hard_player.Set(SD_DUAL_OUTPUT_HWND,(long)soft_hwnd);
	}
	catch (...)
	{
		
	}
	return -1;
}

long player_hard::set_slave_video_window(HWND video_hwnd)
{
	try
	{
		return m_hard_player.Set(SD_SLAVE_VIDEO_HWND,(long)video_hwnd);
	}
	catch (...)
	{

	}
	return -1;
}
void player_hard::TV()
{
	try
	{
		m_hard_player.TV();
		TV_or_VGA = false;
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常TV\r\n");
//		WriteLog(__FL__, buffer);
	}			
}

void player_hard::VGA()
{
	try
	{
		m_hard_player.VGA();
		TV_or_VGA = true;
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常VGA\r\n");
//		WriteLog(__FL__, buffer);
	}			
}

void player_hard::TVorVGA()
{
	try
	{
		if (TV_or_VGA)
		{
			m_hard_player.TV();
		}
		else
		{
			m_hard_player.VGA();
		}
		TV_or_VGA = !TV_or_VGA;
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常TV&VGA\r\n");
//		WriteLog(__FL__, buffer);
	}			
}
bool player_hard::Set(long flag, long value)
{
	try
	{
		long result = m_hard_player.Set(flag, value);

		return true;
	}
	catch (...) 
	{
	}
	return false;
}

long player_hard::Get(long flag)
{
	try
	{
		return m_hard_player.Get(flag);
	}
	catch (...)
	{
		
	}
	return -1;
}
long player_hard::LoadBmpFile(const TCHAR* sBmpFile)
{
	try
	{
		return m_hard_player.LoadBmpFile(sBmpFile);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常LoadBmpFile\r\n");
//		WriteLog(__FL__, buffer);
		return 0;
	}			
}

long player_hard::SetOSDBuf(long iCard, long iOSD, long pOSDBuf)
{
	if (!m_use_osd)
		return -1;
	try
	{
		return m_hard_player.SetOSDBuf(iCard, iOSD, pOSDBuf);		
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常SetOSDBuf\r\n");
//		WriteLog(__FL__, buffer);
		return 0;
	}			
}

long player_hard::GetOSDScreenSizeW()
{
	if (!m_use_osd)
		return -1;
	try
	{
		return m_hard_player.GetOSDScreenSizeW();		
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常GetOSDScreenSizeW\r\n");
//		WriteLog(__FL__, buffer);
		return 0;
	}			
}

long player_hard::GetOSDScreenSizeH()
{
	if (!m_use_osd)
		return -1;
	try
	{
		return m_hard_player.GetOSDScreenSizeH();
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常GetOSDScreenSizeH\r\n");
//		WriteLog(__FL__, buffer);
		return 0;
	}	
}

long player_hard::GetOSDSizeW(long pOSDBuf)
{
	if (!m_use_osd)
		return -1;
	try
	{
		return m_hard_player.GetOSDSizeW(pOSDBuf);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常GetOSDSizeW\r\n");
///		WriteLog(__FL__, buffer);
		return 0;
	}		
}

long player_hard::GetOSDSizeH(long pOSDBuf)
{
	if (!m_use_osd)
		return -1;
	try
	{
		return m_hard_player.GetOSDSizeH(pOSDBuf);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常GetOSDSizeH\r\n");
///		WriteLog(__FL__, buffer);
		return 0;
	}	
}

long player_hard::SetPlayVarOSD(long iCard, long iOSD, long play_mode, long nRepeat,
			   long iHspeed, long iVSpeed, long nDelayTime,
			   long sx, long sy, long ex, long ey)
{
	if (!m_use_osd)
	{
		return -1;
	}

	try
	{
		return m_hard_player.SetPlayVarOSD(iCard, iOSD, play_mode, nRepeat,
			iHspeed, iVSpeed, nDelayTime, sx, sy, ex, ey);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常SetPlayVarOSD\r\n");
//		WriteLog(__FL__, buffer);
		return 0;
	}		
}

long player_hard::PlayOSD(long iCard, long iOSD)
{
	if (!m_use_osd)
		return -1;
	return m_hard_player.PlayOSD(iCard, iOSD);
}

long player_hard::StopOSD(long iCard, long iOSD)
{
	if (!m_use_osd)
		return -1;
	return m_hard_player.StopOSD(iCard, iOSD);
}

long player_hard::get_state()
{
	try
	{
		return m_hard_player.GetState();
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常GetState\r\n");
//		WriteLog(__FL__, buffer);
		return -1;
	}		
}

void player_hard::PlayOSDStartLogo(const TCHAR* sBigLogo, const TCHAR* sWelcome, TCHAR* szOSDTextFont, TCHAR* szName)
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;
	
	// 播放大Logo
	try
	{
		pOSDBufBigLogo = m_hard_player.LoadBmpFile(sBigLogo);
		m_hard_player.SetOSDBuf(0, nLayerLargeLogo, pOSDBufBigLogo);
		int x = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(pOSDBufBigLogo)) / 2;
		int y = (m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(pOSDBufBigLogo)) / 2;
		m_hard_player.SetPlayVarOSD(0, nLayerLargeLogo, OSD_STATIC, 1, 0, 0, 0, x, y, 0, 0);
		this->PlayOSD(0, nLayerLargeLogo);

		long FontColor = RGB(255, 255, 255);

		if (_tcsncmp(szOSDTextFont, L"红色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			FontColor = RGB(255,0,0);
		}
		else if (_tcsncmp(szOSDTextFont, L"黄色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			FontColor = RGB(255,255,0);
		}
		else if (_tcsncmp(szOSDTextFont, L"蓝色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			FontColor = RGB(0,0,255);
		}
		else if (_tcsncmp(szOSDTextFont, L"绿色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			FontColor = RGB(0,255,0);
		}
		else if (_tcsncmp(szOSDTextFont, L"紫色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			FontColor = RGB(128,128,255);
		}
		else if (_tcsncmp(szOSDTextFont, L"白色", sizeof("红色") / sizeof(TCHAR)) == 0)
		{
			FontColor = RGB(255,255,255);
		}
		else if ((*szOSDTextFont>='0' && *szOSDTextFont<='9') || (*szOSDTextFont>='a' && *szOSDTextFont<='z'))
		{
			FontColor = parse_color(szOSDTextFont);
		}

		// 播放开机欢迎词
		pOSDBufWelcomeText = m_hard_player.LoadText(sWelcome, FontColor, RGB(0,0,0),
			40, 20, 0, 0, 400, 0, 0, 0, 134, 0, 0, 3, 0, L"宋体");//szOSDTextFont);
		m_hard_player.SetOSDBuf(0, nLayerWelcomeWord,  pOSDBufWelcomeText);
		x = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(pOSDBufWelcomeText)) / 2;
		m_hard_player.SetPlayVarOSD(0, nLayerWelcomeWord, OSD_STATIC, 0, 0, 0, 0, x, 30, 0, 0);
		this->PlayOSD(0, nLayerWelcomeWord);

		TCHAR msg[32];

		memset(msg,0x0,sizeof(msg));

		if (lstrlen(szName) > 1)
		{
			pOSDBufVersionText1 = m_hard_player.LoadText(szName, FontColor, RGB(0,0,0),
				40, 20, 0, 0, 400, 0, 0, 0, 134, 0, 0, 3, 0, L"宋体");//szOSDTextFont);
			m_hard_player.SetOSDBuf(0, nLayerVersionInfo1, pOSDBufVersionText1);
			m_hard_player.SetPlayVarOSD(0, nLayerVersionInfo1, OSD_STATIC, 0, 0, 0, 0, 340 - lstrlen(szName) * 20 , 420, 0, 0);
			this->PlayOSD(0, nLayerVersionInfo1);
		}
		else
		{
			// 显示“阳光KTV”
			GetWord1(msg);
			pOSDBufVersionText1 = m_hard_player.LoadText(msg, FontColor, RGB(0,0,0),
				40, 20, 0, 0, 400, 0, 0, 0, 134, 0, 0, 3, 0, L"宋体");//szOSDTextFont);
			m_hard_player.SetOSDBuf(0, nLayerVersionInfo1, pOSDBufVersionText1);
			m_hard_player.SetPlayVarOSD(0, nLayerVersionInfo1, OSD_STATIC, 0, 0, 0, 0, 60, 420, 0, 0);
			this->PlayOSD(0, nLayerVersionInfo1);

			// 显示“阳光视翰科技”
			GetWord2(msg);
			pOSDBufVersionText2 = m_hard_player.LoadText(msg, FontColor, RGB(0,0,0),
				40, 20, 0, 0, 400, 0, 0, 0, 134, 0, 0, 3, 0, L"宋体");//szOSDTextFont);
			m_hard_player.SetOSDBuf(0, nLayerVersionInfo2, pOSDBufVersionText2);
			m_hard_player.SetPlayVarOSD(0, nLayerVersionInfo2, OSD_STATIC, 0, 0, 0, 0, 500, 420, 0, 0);
			this->PlayOSD(0, nLayerVersionInfo2);
		}
		
		bLargeLogoPlaying = true;
	}
	catch (...)
	{
	}
	return;
}	

void player_hard::GetWord1(TCHAR* msg)
{
	TCHAR* p = reinterpret_cast<TCHAR*>(msg);

#ifdef JIALEDI
	// 嘉乐迪
	p[0] = static_cast<TCHAR>(0x6B27);
	p[1] = static_cast<TCHAR>(0x5170);
	p[2] = static_cast<TCHAR>(0x7279);
	p[3] = 0;	
#else
	// 阳光KTV
	p[0] = static_cast<TCHAR>(0x9633);
	p[1] = static_cast<TCHAR>(0x5149);
	p[2] = static_cast<TCHAR>(0x4B);
	p[3] = static_cast<TCHAR>(0x54);
	p[4] = static_cast<TCHAR>(0x56);
	p[5] = static_cast<TCHAR>(0x00);	
#endif
}

void player_hard::GetWord2(TCHAR* msg)
{
	TCHAR* p = reinterpret_cast<TCHAR*>(msg);

#ifdef JIALEDI
	// 嘉乐迪
	p[0] = static_cast<TCHAR>(0x4FF1);
	p[1] = static_cast<TCHAR>(0x4E50);
	p[2] = static_cast<TCHAR>(0x90E8);
	p[3] = 0;	
#else
	// 阳光视翰科技
	
	p[0] = static_cast<TCHAR>(0x89C6);
	p[1] = static_cast<TCHAR>(0x7FF0);
	p[2] = static_cast<TCHAR>(0x79D1);
	p[3] = static_cast<TCHAR>(0x6280);
	p[4] = 0;
#endif
}

void player_hard::StopOSDStartLogo()
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;

	if (bLargeLogoPlaying == false)
		return;
	
	if (pOSDBufBigLogo)
	{
		m_hard_player.StopOSD(0, nLayerLargeLogo);
		m_hard_player.UnloadOSD(pOSDBufBigLogo);
		pOSDBufBigLogo = 0;
	}
	
	if (pOSDBufWelcomeText)
	{
		m_hard_player.StopOSD(0, nLayerWelcomeWord);
		m_hard_player.UnloadOSD(pOSDBufWelcomeText);
		pOSDBufWelcomeText = 0;
	}
	
	if (pOSDBufVersionText1)
	{
		m_hard_player.StopOSD(0, nLayerVersionInfo1);
		m_hard_player.UnloadOSD(pOSDBufVersionText1);
		pOSDBufVersionText1 = 0;
	}
	
	if (pOSDBufVersionText2)
	{
		m_hard_player.StopOSD(0, nLayerVersionInfo2);
		m_hard_player.UnloadOSD(pOSDBufVersionText2);
		pOSDBufVersionText2 = 0;
	}
	
	if (pOSDBufBigLogo == 0 && pOSDBufVersionText2 == 0 && pOSDBufVersionText1 == 0 && pOSDBufWelcomeText ==0)
	{
		bLargeLogoPlaying = false;
	}
	return;
}

void player_hard::PlayOSDLogo(const TCHAR* sLogo, int Index, int posX,int posY,bool first_logo)
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;
	
	if (bLargeLogoPlaying != false)
	{
		StopOSDStartLogo();
	}

	//先查找，存在就不在LOAD
	if (osd_logo_handle[Index] == 0 || _tcscmp(osd_buf_logo_path[Index], sLogo) != 0)
	{
		long hTemp = m_hard_player.LoadBmpFile(sLogo);
		if (0!=hTemp)
		{
			osd_logo_handle[Index] = hTemp;
			_tcscpy(osd_buf_logo_path[Index], sLogo);
		}
	}
	
	m_hard_player.SetOSDBuf(0, nLayerLogo, osd_logo_handle[Index]);
	if (first_logo)
	{
		m_hard_player.SetPlayVarOSD(0, nLayerLogo, OSD_STATIC, 1, 0, 0, 0, posX, posY, 0, 0);
		this->PlayOSD(0, nLayerLogo);
	}
	
	return;
}


void player_hard::StopOSDLogo()
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;

	m_hard_player.StopOSD(0, nLayerLogo);
	for (int i = 0; i < 100; i++)
	{
		if (osd_logo_handle[i] !=0)
		{
			m_hard_player.UnloadOSD(osd_logo_handle[i]);
			osd_logo_handle[i] = 0;
		}
	}
}

void player_hard::PlayADOSDLogo(const TCHAR* logo_path,int logo_layer)
{
	int index=0;
	bool first_logo=true;
	int x_pos=0;
	int y_pos=0;

	if (!m_use_osd)
		return;

	if (bLargeLogoPlaying != false)
	{
		StopOSDStartLogo();
	}

	if (nLayerADLogo==logo_layer)  //广告logo，在左边中间显示
	{
		//先查找，存在就不在LOAD
		if (ad_osd_logo_handle[index] == 0 || _tcscmp(ad_osd_logo_path[index], logo_path) != 0)
		{
			long hTemp = m_hard_player.LoadBmpFile(logo_path);
			if (0!=hTemp)
			{
				ad_osd_logo_handle[index] = hTemp;
				_tcscpy(ad_osd_logo_path[index], logo_path);
			}
		}

		x_pos = 50;
		y_pos = (m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(ad_osd_logo_handle[index]))/2;

		m_hard_player.SetOSDBuf(0, logo_layer, ad_osd_logo_handle[index]);
		if (first_logo)
		{
			m_hard_player.SetPlayVarOSD(0, logo_layer, OSD_STATIC, 1, 0, 0, 0, x_pos, y_pos, 0, 0);
			this->PlayOSD(0, logo_layer);
		}
	}
	else if (nLayerADBKLogo==logo_layer) //广告的背景logo，在控制osd下显示
	{
		if (0!=osd_bk_logo_handle)
		{
			StopADOSDLogo(logo_layer);
			osd_bk_logo_handle = 0;
		}
		osd_bk_logo_handle = m_hard_player.LoadBmpFile(logo_path);
		
		x_pos = 400;
		y_pos = 80;
		m_hard_player.SetOSDBuf(0, logo_layer, osd_bk_logo_handle);
		m_hard_player.SetPlayVarOSD(0, logo_layer, OSD_STATIC, 1, 0, 0, 0, x_pos, y_pos, 0, 0);
		this->PlayOSD(0, logo_layer);
	}
	
	return;
}

void player_hard::StopADOSDLogo(int logo_layer)
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;

	if (nLayerADLogo==logo_layer)
	{
		m_hard_player.StopOSD(0, nLayerADLogo);
		for (int i = 0; i < 100; i++)
		{
			if (ad_osd_logo_handle[i] !=0)
			{
				m_hard_player.UnloadOSD(ad_osd_logo_handle[i]);
				ad_osd_logo_handle[i] = 0;
			}
		}
	}
	else if (nLayerADBKLogo==logo_layer)
	{
		m_hard_player.StopOSD(0,nLayerADBKLogo);
		m_hard_player.UnloadOSD(osd_bk_logo_handle);
		osd_bk_logo_handle = 0;
	}
}

long player_hard::command(long cmd, long flag, long value)
{
	return m_hard_player.Command(cmd, flag, value);
}

void player_hard::StopOSDText()
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;

	if (bLargeLogoPlaying != false)
	{
		StopOSDStartLogo();
	}

	if (osd_text_handle)
	{
		m_hard_player.StopOSD(0, nLayerText);
		m_hard_player.UnloadOSD(osd_text_handle);
		osd_text_handle = 0;
	}
}

long player_hard::stop_OSD_GF(long lIndex)
{
	if (!m_use_osd)
		return false;

	return m_hard_player.StopOSD(0,lIndex);
}
void player_hard::OSD_GF(TCHAR * Text, long lIndex, long fgcl, int x, int y)   //将功放文字显示在电视
{
	if (!m_use_osd)
		return;

	int StartX=0;
	text_osd_info textOSD;  //字体变量
	static long pOSDBuff = 0;
	string_conversion string_conv;
	
// 	m_hard_player.StopOSD(0,lIndex);
	stop_OSD_GF(lIndex);
	//计算多字节占用的字节数
	int iLen = string_conv.get_byte_size_of_multibyte(Text);
	if (x == 0)
	{
		StartX = 660 - (iLen * 20);
	}
	else if (x == 1)
	{
		StartX = 370 - (iLen * 10);
	}
	else
	{
		StartX = x;
	}
		
	_tcscpy(textOSD.m_text , Text);
	textOSD.fgcl = fgcl;
	textOSD.shcl = RGB (0,0,0); //背景颜色是黑色
	
	textOSD.lf.lfWidth = 20;
	textOSD.lf.lfHeight = 40 ;
	textOSD.lf.lfWeight = 400;
	textOSD.lf.lfEscapement = 0;
	textOSD.lf.lfOrientation = 0;
	textOSD.lf.lfItalic = 0;
	textOSD.lf.lfUnderline = 0;
	textOSD.lf.lfStrikeOut = 0;
	textOSD.lf.lfQuality = 3;
	textOSD.lf.lfCharSet = 134;
	_tcscpy(textOSD.lf.lfFaceName,L"黑体");
	
	pOSDBuff = m_hard_player.LoadText(textOSD.Text(), textOSD.fgcl, textOSD.shcl,
		textOSD.lf.lfHeight, textOSD.lf.lfWidth, textOSD.lf.lfEscapement,
		textOSD.lf.lfOrientation, textOSD.lf.lfWeight, textOSD.lf.lfItalic,
		textOSD.lf.lfUnderline, textOSD.lf.lfStrikeOut,
		textOSD.lf.lfCharSet, textOSD.lf.lfOutPrecision,
		textOSD.lf.lfClipPrecision, textOSD.lf.lfQuality,
		textOSD.lf.lfPitchAndFamily, textOSD.lf.lfFaceName);//L"黑体"

	long lret = m_hard_player.SetOSDBuf(0,lIndex, pOSDBuff);
	lret = m_hard_player.SetPlayVarOSD(0, lIndex, OSD_STATIC, 0, 0, 0, 0, StartX, y, 0, 0);	//90
	this->PlayOSD(0,lIndex);	
}

// 显示文本到OSD
void player_hard::PlayTextOSD(const TCHAR* szBackground, const text_osd_info& txtOSD, const play_variable& playVarText)
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;
	
	if (0!=osd_text_handle)
	{
		StopOSDText();
		osd_text_handle = 0;
	}
	
	if (bLargeLogoPlaying)
	{
		StopOSDStartLogo();
	}

	osd_text_handle = m_hard_player.LoadText(txtOSD.Text(),
		txtOSD.TextColor()/*前景色*/, txtOSD.ShadeColor()/*背景色*/,
		txtOSD.Font().lfHeight, txtOSD.Font().lfWidth, txtOSD.Font().lfEscapement,
		txtOSD.Font().lfOrientation, txtOSD.Font().lfWeight, txtOSD.Font().lfItalic,
		txtOSD.Font().lfUnderline, txtOSD.Font().lfStrikeOut,
		txtOSD.Font().lfCharSet, txtOSD.Font().lfOutPrecision,
		txtOSD.Font().lfClipPrecision, txtOSD.Font().lfQuality,
		txtOSD.Font().lfPitchAndFamily, txtOSD.Font().lfFaceName);
		//如果是滚动字幕 最后加true
	
	if (osd_text_handle > 0)
	{
		m_hard_player.SetOSDBuf(0, nLayerText, osd_text_handle);
		m_hard_player.SetPlayVarOSD(0, nLayerText, playVarText.play_mode, playVarText.nRepeat,
			playVarText.iHSpeed, playVarText.iVSpeed, playVarText.nDelayTime,
			playVarText.sx, playVarText.sy, playVarText.ex, playVarText.ey);
		//如果是滚动字幕 最后加true
		this->PlayOSD(0, nLayerText);
	}

	return;
 }

// 显示图片(BMP)到OSD
void player_hard::PlayBmpOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode)
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;
	
	// OSD对象句柄
	if (osd_bmp_handle != 0)
	{
		m_hard_player.UnloadOSD(osd_bmp_handle);
		osd_bmp_handle = 0;
	}
	
	if (bLargeLogoPlaying != false)
	{
		StopOSDStartLogo();
	}

	int start_x_pos=0;
	int start_y_pos=0;

	FILE* fp = _wfopen(szBmpFilename, L"rb");
	if (fp) // 文件存在时才执行以下动作：
	{
		fclose(fp);
		fp=NULL;		

		osd_bmp_handle = m_hard_player.LoadBmpFile(szBmpFilename);
		if (0!=osd_bmp_handle)
		{
			switch(alignment_mode)
			{
			case OSDAlignmentTop:   //电视顶端
				{
					start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_bmp_handle))/2;
					start_y_pos = 20;
				}
				break;
			case  OSDAlignmentBottom:  //电视底端
				{
					start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_bmp_handle))/2;
					start_y_pos = m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_bmp_handle)-15;
				}
				break;
			case OSDAlignmentRightCenter:  //右边居中
				{
					start_x_pos = m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_bmp_handle)-25;
					start_y_pos = (m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_bmp_handle))/2;
				}
				break;
			case OSDPK:
				{
					start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_bmp_handle))/2;
					start_y_pos = 180;
				}
				break;
			case OSDSCOREPOS:  
				{
					start_x_pos = 50;
					start_y_pos = 185;//(m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_bmp_handle))/2 - 120;
				}
				break;
			case OSDAlignmentCenter:       //电视中间
				{
					start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_bmp_handle))/2;
					start_y_pos = (m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_bmp_handle))/2;
				}
				break;
			case OSDAlignmentRightTop:
				{
					start_x_pos = m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_score_handle)-10;
					start_y_pos = 10;
				}
				break;
			default:
				{
					start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_bmp_handle))/2;
					start_y_pos = (m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_bmp_handle))/2;
				}
				break;
			}
			m_hard_player.SetOSDBuf(0, nLayerBmp, osd_bmp_handle);
			m_hard_player.SetPlayVarOSD(0, nLayerBmp, OSD_STATIC, playVarPic.nRepeat,
				playVarPic.iHSpeed, playVarPic.iVSpeed, playVarPic.nDelayTime,
				start_x_pos, start_y_pos, 0, 0);
			this->PlayOSD(0, nLayerBmp);
		}
	}
	return;
}


// 显示分数到OSD
void player_hard::PlayScoreOSD(const TCHAR* szBmpFilename, const play_variable& playVarPic,OSDAlignment alignment_mode)
{
	try
	{
		// 若不使用屏显，则直接返回
		if (!m_use_osd)
			return;

		// OSD对象句柄
		if (osd_score_handle != 0)
		{
			m_hard_player.UnloadOSD(osd_score_handle);
			osd_score_handle = 0;
		}

		if (bLargeLogoPlaying != false)
		{
			StopOSDStartLogo();
		}

		int start_x_pos=0;
		int start_y_pos=0;

		FILE* fp = _wfopen(szBmpFilename, L"rb");
		if (fp) // 文件存在时才执行以下动作：
		{
			fclose(fp);
			fp=NULL;		

			osd_score_handle = m_hard_player.LoadBmpFile(szBmpFilename);
			if (0!=osd_score_handle)
			{
				switch(alignment_mode)
				{
				case OSDAlignmentTop:   //电视顶端
					{
						start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_score_handle))/2;
						start_y_pos = 20;
					}
					break;
				case  OSDAlignmentBottom:  //电视底端
					{
						start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_score_handle))/2;
						start_y_pos = m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_score_handle)-15;
					}
					break;
				case OSDAlignmentRightCenter:  //右边居中
					{
						start_x_pos = m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_score_handle)-50;
						start_y_pos = 180;
					}
					break;
				case OSDAlignmentCenterTop:    //中间靠上
					{
						start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_score_handle))/2;
						start_y_pos = 90;  //(m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_bmp_handle))/2;
					}
					break;
				case OSDSCORELEFTPOS:  //
					{
						start_x_pos = m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_score_handle)-100;
						start_y_pos = 180;//(m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_score_handle))/2 - 200;
					}
					break;
				case OSDAlignmentCenter:       //电视中间
					{

					}
					break;
				case OSDAlignmentRightTop:
					{
						start_x_pos = m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_score_handle)-50;
						start_y_pos = 30;
					}
					break;
				default:
					{
						start_x_pos = (m_hard_player.GetOSDScreenSizeW() - m_hard_player.GetOSDSizeW(osd_score_handle))/2;
						start_y_pos = (m_hard_player.GetOSDScreenSizeH() - m_hard_player.GetOSDSizeH(osd_score_handle))/2;
					}
					break;
				}
				m_hard_player.SetOSDBuf(0, nLayerADLogo, osd_score_handle);
				m_hard_player.SetPlayVarOSD(0, nLayerADLogo, OSD_STATIC, playVarPic.nRepeat,
					playVarPic.iHSpeed, playVarPic.iVSpeed, playVarPic.nDelayTime,
					start_x_pos, start_y_pos, 0, 0);
				this->PlayOSD(0, nLayerADLogo);
			}
		}

		return;
	}
	catch (...)
	{

	}

	return;
}


//显示墙面板图片
void player_hard::ShowWallPanelOSD(const TCHAR* path)
{
	try
	{
		FILE* fp = _wfopen(path, L"rb");
		if (fp) // 文件存在时才执行以下动作：
		{
			fclose(fp);
			fp=NULL;

			long bmp = m_hard_player.LoadBmpFile(path);
			m_hard_player.SetOSDBuf(3, 0, bmp);
			m_hard_player.UnloadOSD(bmp);
		}	
	}
	catch (...)
	{
		
	}
	return;
}

void player_hard::HideWallPanelOSD(void)
{
	try
	{
        m_hard_player.SetOSDBuf(3, 0, 0);
	}
	catch (...)
	{
		
	}
	return;
}

void player_hard::StopBMPOSD()
{
	m_hard_player.StopOSD(0,nLayerBmp);
	m_hard_player.UnloadOSD(osd_bmp_handle);
	osd_bmp_handle=NULL;
}


void player_hard::StopScoreOSD()
{
	m_hard_player.StopOSD(0,nLayerADLogo);
	m_hard_player.UnloadOSD(osd_score_handle);
	osd_score_handle=NULL;
}


// 显示控制屏显
void player_hard::PlayControlOSD(const TCHAR* path, int x, int y)
{
	// 若不使用屏显，则直接返回
	if (!m_use_osd)
		return;
	
	if (bLargeLogoPlaying != false)
	{
		StopOSDStartLogo();
	}
	
	// 关闭之前的显示
	StopControlOSD();

	//load 新的控制logo
	osd_control_logo_handle = m_hard_player.LoadBmpFile(path);
	m_hard_player.SetOSDBuf(0, nLayerOsdControl, osd_control_logo_handle);
	m_hard_player.SetPlayVarOSD(0, nLayerOsdControl, OSD_STATIC, 0, 0, 0, 0, x, y, x, y);
	this->PlayOSD(0, nLayerOsdControl);

	return;
}

void player_hard::StopControlOSD()
{
	if (!m_use_osd)
		return;	

	// OSD对象句柄
	if (osd_control_logo_handle != 0)
	{
		m_hard_player.StopOSD(0, nLayerOsdControl);
		m_hard_player.UnloadOSD(osd_control_logo_handle);
		osd_control_logo_handle = 0;
	}
}

// 总长度
long player_hard::get_total_time_length()
{
	try
	{
		return m_hard_player.Get(SD_CLIP_LENGTH); // 总长度
	}
	catch (...) 
	{
	}	
	return -1;
}

// 当前位置
long player_hard::get_current_pos()
{
	return m_hard_player.Get(SD_PERCENT); // 当前位置，百分比
}

long player_hard::get_play_time_length()
{
	return m_hard_player.Get(SD_POSITION); // 当前位置，秒
}

// 调整播放位置
void player_hard::seek(long pos)
{
	m_hard_player.Seek(pos);
}

// 调节亮度，取值0～1200
void player_hard::set_bright(long value)
{
	if (value < 0) value = 0;
	if (value > 1200) value = 1200;
	Set(109, value);
}

// 调节对比度，取值0～1200
void player_hard::set_contrast(long value)
{
	if (value < 0) value = 0;
	if (value > 1200) value = 1200;
	Set(110, value);
}

// 调节饱和度，取值0～1000
void player_hard::set_saturation(long value)
{
	if (value < 0) value = 0;
	if (value > 1000) value = 1000;
	Set(111, value);
	
	return;
}

// 快进
void player_hard::forward()
{
	long nTotalSize = this->get_total_time_length();
	long nCurrentPos = this->get_current_pos();

	nCurrentPos += 600000;
	if (nCurrentPos > nTotalSize) nCurrentPos = nTotalSize;

	this->seek(nCurrentPos);
}

// 快退
void player_hard::backward()
{
	long nTotalSize = get_total_time_length();
	long nCurrentPos = get_current_pos();

	nCurrentPos -= 1000000;
	if (nCurrentPos < 0) nCurrentPos = 0;
	
	this->seek(nCurrentPos);
}

int player_hard::get_text_osd_play_state()
{
	if (!m_use_osd)
		return -1;

	if (m_hard_player.GetPlayStateOSD(0, nLayerText) != 0)
	{
		//正在播放text osd
		return 1;
	}
    return 0;
}

bool player_hard::RefreshDrv()
{
	if (m_use_osd)
	{
		for (int i = 0; i < 100; i++)
		{
			if (osd_logo_handle[i] !=0)
			{
				m_hard_player.UnloadOSD(osd_logo_handle[i]);
				osd_logo_handle[i] = 0;
			}
		}
		if (osd_text_handle)
		{
			//m_hard_player.StopOSD(0, 1);
			m_hard_player.UnloadOSD(osd_text_handle);
			osd_text_handle = 0;
		}
		m_hard_player.FinishOSD();
	}
	
	m_hard_player.Stop();
	m_hard_player.CloseFile();
	m_hard_player.CloseDrv();
	m_hard_player.ResetDriver();
	
	if (m_hard_player.OpenDrv() < 0)
	{
		return false;
	}
	m_hard_player.Stop();

	if (m_use_osd)
	{
		InitOSD();
	}
	return true;
}

void player_hard::SetScreenHwnd(long hwnd, int ScX1, int ScX2, int ScY1, int ScY2)
{
	m_ScreenHwnd = hwnd;
	m_ScX1 = ScX1;
	m_ScY1 = ScY1;
	m_ScX2 = ScX2;
	m_ScY2 = ScY2;	
}

//设置电视制式
void player_hard::SetTvStandard(long flag)
{
	if (flag < 0) flag = 0;

	Set(200, flag);
}

//设置录音回放
void player_hard::SetPlayBack(long flag)
{
	if (flag < 0) flag = 0;

	Set(300, flag);
}

void player_hard::SetGszWavFileName(const TCHAR* s)
{
	try
	{
		m_hard_player.SetGszWavFileName(s);		
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常SetGszWavFileName\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

void player_hard::OSDKeyDown(WPARAM wParam)
{
	try
	{
		m_hard_player.OSDKeyDown((long)wParam);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常OSDKeyDown\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

void player_hard::OSDListChanged(long list)
{
	try
	{
		m_hard_player.OSDListChanged(list);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常OSDListChanged\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

void player_hard::OSDSetSwapper(long swapper)
{
	try
	{
		m_hard_player.OSDSetSwapper((long)swapper);		
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常OSDSetSwapper\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

void player_hard::OSDSwitchKTV(long ktv)
{
	try
	{
		m_hard_player.OSDSwitchKTV(ktv);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常OSDSwitchKTV\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

bool player_hard::VODEnableDbDisplay(long e)
{
	try
	{
		m_hard_player.VODEnableDbDisplay(e);
		return true;
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常， 软屏切功能被关闭\r\n");
//		WriteLog(__FL__, buffer);
		return false;
	}		
	return true;
}

void player_hard::VODSetScreenWindow(long hwnd)
{
	try
	{
		m_hard_player.VODSetScreenWindow(hwnd);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常VODSetScreenWindow\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

void player_hard::VODShowScreenVideo(long e)
{
	try
	{
		m_hard_player.VODShowScreenVideo(e);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常VODShowScreenVideo\r\n");
//		WriteLog(__FL__, buffer);
	}		
}

long player_hard::WaveMixer_Play(LPCTSTR sWaveName, long Loop, long fMusicOut)
{	
	try
	{
		return m_hard_player.WaveMixer_Play(sWaveName, Loop, fMusicOut);	
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常WaveMixer_Play\r\n");
//		WriteLog(__FL__, buffer);
	}		
	return 0;
}

bool player_hard::Ctrl_SetNotifyWindow(long hwndNotify)
{
	try
	{
		m_hard_player.Ctrl_SetNotifyWindow(hwndNotify);

		return true;
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常，控件为直接打开播放\r\n");
//		WriteLog(__FL__, buffer);
		return false;
	}		
	return true;
}

long player_hard::WaveMixer_Stop()
{
	try
	{
		return m_hard_player.WaveMixer_Stop();	
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常WaveMixer_Stop\r\n");
//		WriteLog(__FL__, buffer);
	}		
	return 0;
}

long player_hard::WaveMixer_SetTone(long nTone)
{
	try
	{
		return m_hard_player.WaveMixer_SetTone(nTone);
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常WaveMixer_SetTone\r\n");
//		WriteLog(__FL__, buffer);
	}		
	return 0;
}

long player_hard::WaveMixer_GetTone()
{
	try
	{
		return m_hard_player.WaveMixer_GetTone();	
	}
	catch (CException* e) 
	{
		// 写入日志
		TCHAR buffer[256];
		e->GetErrorMessage(buffer, 256);
		_tcscat(buffer, L"   异常WaveMixer_GetTone\r\n");
//		WriteLog(__FL__, buffer);
	}		
	return 0;
}

long player_hard::preview_open(LPCTSTR pMedia, long hwnd)
{
	try
	{
		return m_hard_player.Preview_Open(pMedia,hwnd);
	}
	catch (...)
	{
		
	}
	return -1;
}

long player_hard::Live_Open(long n, LPCTSTR pMedia)
{
	try
	{
		return m_hard_player.Live_Open(n,pMedia);
	}
	catch (...)
	{
		
	}
	return -1;
}

long player_hard::Live_Close(long n)
{
	try
	{
		return m_hard_player.Live_Close(n);
	}
	catch (...)
	{

	}
	return -1;
}

long player_hard::Live_Control(long n, long nCode, long argv0, long argv1)
{
	try
	{
		return m_hard_player.Live_Control(n,nCode,argv0,argv1);
	}
	catch (...)
	{

	}
	return -1;
}

long player_hard::preview_close()
{
	try
	{
		return m_hard_player.Preview_Close();
	}
	catch (...)
	{

	}
	return -1;
}

long player_hard::preview_control(long nCode, long argv0, long argv1)
{
	try
	{
		return m_hard_player.Preview_Control(nCode,argv0,argv1);
	}
	catch (...)
	{

	}
	return -1;
}

long player_hard::TV_open(LPCTSTR pDev, long hwnd, long nSignal)
{
	try
	{
		return m_hard_player.TV_Open(pDev,hwnd,nSignal);
	}
	catch (...)
	{

	}
	return -1;
}

long player_hard::TV_close()
{
	try
	{
		return m_hard_player.TV_Close();
	}
	catch (...)
	{

	}
	return -1;
}

long player_hard::TV_control(long nCode, long argv0, long argv1)
{
	try
	{
		return m_hard_player.TV_Control(nCode,argv0,argv1);
	}
	catch (...)
	{

	}
	return -1;
}

#include "stdafx.h"
#include "flashktv10Wnd.h"
#include "file/config_file.h"
#include "folder_name.h"
#include "file/log.h"
#include "common/string_function.h"
#include "common/StringCodeConversion.h"
#include "common/init_socket.h"
#include "flash/PageData.h"
#include "common/exit_window.h"
#include "common/des.h"
#include "star/decrypt_singer_picture.h"
#include "common/rgb_conv.h"
#include <time.h>
#include <sys/timeb.h>

#include <Tlhelp32.h>
#include <shellapi.h>

#pragma warning(disable: 4267 4018 4311 4244)

#include <sys/types.h>
#include <sys/stat.h>

#pragma comment(lib, "lib\\zlib.lib")

#include <objbase.h>

#include "common/ExifTags.h"

static fd_set g_flash_socket_set; //flash socket fd_set

extern void change_char(TCHAR *ch);

const char* newGUID()
{
	static char buf[64] = {0};
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(buf, sizeof(buf)
			, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
		, guid.Data4[6], guid.Data4[7]
		);
	}
	return (const char*)buf;
}
static const TCHAR* newWGUID()
{
	static TCHAR buf[64] = {0};
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snwprintf(buf, sizeof(buf)
			, L"{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
		, guid.Data4[6], guid.Data4[7]
		);
	}
	return (const TCHAR*)buf;
}

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define RL(x, y) (((x) << (y)) | ((x) >> (32 - (y))))  //x向左循环移y位
#define PP(x) (x<<24)|((x<<8)&0xff0000)|((x>>8)&0xff00)|(x>>24)  //将x高低位互换,例如PP(aabbccdd)=ddccbbaa
#define FF(a, b, c, d, x, s, ac) a = b + (RL((a + F(b,c,d) + x + ac),s))
#define GG(a, b, c, d, x, s, ac) a = b + (RL((a + G(b,c,d) + x + ac),s))
#define HH(a, b, c, d, x, s, ac) a = b + (RL((a + H(b,c,d) + x + ac),s))
#define II(a, b, c, d, x, s, ac) a = b + (RL((a + I(b,c,d) + x + ac),s))
static unsigned A,B,C,D,x[16];   /*i临时变量,len文件长,flen[2]为64位二进制表示的文件初始长度*/
static void md5(){                 /*MD5核心算法,供64轮*/
	static unsigned a,b,c,d;
	a=A,b=B,c=C,d=D;
	/**//* Round 1 */
	FF (a, b, c, d, x[ 0],  7, 0xd76aa478); /**//* 1 */
	FF (d, a, b, c, x[ 1], 12, 0xe8c7b756); /**//* 2 */
	FF (c, d, a, b, x[ 2], 17, 0x242070db); /**//* 3 */
	FF (b, c, d, a, x[ 3], 22, 0xc1bdceee); /**//* 4 */
	FF (a, b, c, d, x[ 4],  7, 0xf57c0faf); /**//* 5 */
	FF (d, a, b, c, x[ 5], 12, 0x4787c62a); /**//* 6 */
	FF (c, d, a, b, x[ 6], 17, 0xa8304613); /**//* 7 */
	FF (b, c, d, a, x[ 7], 22, 0xfd469501); /**//* 8 */
	FF (a, b, c, d, x[ 8],  7, 0x698098d8); /**//* 9 */
	FF (d, a, b, c, x[ 9], 12, 0x8b44f7af); /**//* 10 */
	FF (c, d, a, b, x[10], 17, 0xffff5bb1); /**//* 11 */
	FF (b, c, d, a, x[11], 22, 0x895cd7be); /**//* 12 */
	FF (a, b, c, d, x[12],  7, 0x6b901122); /**//* 13 */
	FF (d, a, b, c, x[13], 12, 0xfd987193); /**//* 14 */
	FF (c, d, a, b, x[14], 17, 0xa679438e); /**//* 15 */
	FF (b, c, d, a, x[15], 22, 0x49b40821); /**//* 16 */

	/**//* Round 2 */
	GG (a, b, c, d, x[ 1],  5, 0xf61e2562); /**//* 17 */
	GG (d, a, b, c, x[ 6],  9, 0xc040b340); /**//* 18 */
	GG (c, d, a, b, x[11], 14, 0x265e5a51); /**//* 19 */
	GG (b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /**//* 20 */
	GG (a, b, c, d, x[ 5],  5, 0xd62f105d); /**//* 21 */
	GG (d, a, b, c, x[10],  9, 0x02441453); /**//* 22 */
	GG (c, d, a, b, x[15], 14, 0xd8a1e681); /**//* 23 */
	GG (b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /**//* 24 */
	GG (a, b, c, d, x[ 9],  5, 0x21e1cde6); /**//* 25 */
	GG (d, a, b, c, x[14],  9, 0xc33707d6); /**//* 26 */
	GG (c, d, a, b, x[ 3], 14, 0xf4d50d87); /**//* 27 */
	GG (b, c, d, a, x[ 8], 20, 0x455a14ed); /**//* 28 */
	GG (a, b, c, d, x[13],  5, 0xa9e3e905); /**//* 29 */
	GG (d, a, b, c, x[ 2],  9, 0xfcefa3f8); /**//* 30 */
	GG (c, d, a, b, x[ 7], 14, 0x676f02d9); /**//* 31 */
	GG (b, c, d, a, x[12], 20, 0x8d2a4c8a); /**//* 32 */

	/**//* Round 3 */
	HH (a, b, c, d, x[ 5],  4, 0xfffa3942); /**//* 33 */
	HH (d, a, b, c, x[ 8], 11, 0x8771f681); /**//* 34 */
	HH (c, d, a, b, x[11], 16, 0x6d9d6122); /**//* 35 */
	HH (b, c, d, a, x[14], 23, 0xfde5380c); /**//* 36 */
	HH (a, b, c, d, x[ 1],  4, 0xa4beea44); /**//* 37 */
	HH (d, a, b, c, x[ 4], 11, 0x4bdecfa9); /**//* 38 */
	HH (c, d, a, b, x[ 7], 16, 0xf6bb4b60); /**//* 39 */
	HH (b, c, d, a, x[10], 23, 0xbebfbc70); /**//* 40 */
	HH (a, b, c, d, x[13],  4, 0x289b7ec6); /**//* 41 */
	HH (d, a, b, c, x[ 0], 11, 0xeaa127fa); /**//* 42 */
	HH (c, d, a, b, x[ 3], 16, 0xd4ef3085); /**//* 43 */
	HH (b, c, d, a, x[ 6], 23, 0x04881d05); /**//* 44 */
	HH (a, b, c, d, x[ 9],  4, 0xd9d4d039); /**//* 45 */
	HH (d, a, b, c, x[12], 11, 0xe6db99e5); /**//* 46 */
	HH (c, d, a, b, x[15], 16, 0x1fa27cf8); /**//* 47 */
	HH (b, c, d, a, x[ 2], 23, 0xc4ac5665); /**//* 48 */

	/**//* Round 4 */
	II (a, b, c, d, x[ 0],  6, 0xf4292244); /**//* 49 */
	II (d, a, b, c, x[ 7], 10, 0x432aff97); /**//* 50 */
	II (c, d, a, b, x[14], 15, 0xab9423a7); /**//* 51 */
	II (b, c, d, a, x[ 5], 21, 0xfc93a039); /**//* 52 */
	II (a, b, c, d, x[12],  6, 0x655b59c3); /**//* 53 */
	II (d, a, b, c, x[ 3], 10, 0x8f0ccc92); /**//* 54 */
	II (c, d, a, b, x[10], 15, 0xffeff47d); /**//* 55 */
	II (b, c, d, a, x[ 1], 21, 0x85845dd1); /**//* 56 */
	II (a, b, c, d, x[ 8],  6, 0x6fa87e4f); /**//* 57 */
	II (d, a, b, c, x[15], 10, 0xfe2ce6e0); /**//* 58 */
	II (c, d, a, b, x[ 6], 15, 0xa3014314); /**//* 59 */
	II (b, c, d, a, x[13], 21, 0x4e0811a1); /**//* 60 */
	II (a, b, c, d, x[ 4],  6, 0xf7537e82); /**//* 61 */
	II (d, a, b, c, x[11], 10, 0xbd3af235); /**//* 62 */
	II (c, d, a, b, x[ 2], 15, 0x2ad7d2bb); /**//* 63 */
	II (b, c, d, a, x[ 9], 21, 0xeb86d391); /**//* 64 */

	A += a;
	B += b;
	C += c;
	D += d;
}

//得到文件的大小
long get_filesize(char *filename)
{
	struct stat     f_stat;
	if (stat(filename, &f_stat) == -1) {
		return -1;
	}
	return (long)f_stat.st_size;
}

void Cflashktv10Wnd::hide_window_task_bar(bool hide) 
{
	try
	{
		int nCmdShow=0; 
		CWnd *pWnd=NULL; 
		LPARAM lParam; 

		//查找任务栏的句柄
		pWnd = CWnd::FindWindow(L"Shell_TrayWnd",NULL);
		if(NULL==pWnd)
		{
			return;
		}
		if(hide == true) 
		{ 
			nCmdShow = SW_HIDE; 
			lParam = ABS_AUTOHIDE | ABS_ALWAYSONTOP; 
		} 
		else 
		{ 
			nCmdShow = SW_SHOW; 
			lParam = ABS_ALWAYSONTOP; 
		} 
		//隐藏或显示任务栏 
		pWnd->ShowWindow(nCmdShow);

		//自动隐藏任务栏
		APPBARDATA apBar; 
		memset(&apBar,0x0,sizeof(apBar)); 
		apBar.cbSize = sizeof(apBar); 
		apBar.hWnd = pWnd->m_hWnd; 
		if(apBar.hWnd != NULL) 
		{ 
			apBar.lParam = lParam; 
			//设置任务栏自动隐藏或显示
			SHAppBarMessage(ABM_SETSTATE, &apBar); 
		} 
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::get_display_monitor_info(int device_index,TCHAR *display_name)
{
	//声明一个函数原型
	typedef DWORD (WINAPI* pfEnumDisplayDevice)( LPCTSTR ,DWORD,PDISPLAY_DEVICE, DWORD);

	pfEnumDisplayDevice pEnumDisplayDevices;
	HINSTANCE  hInstUser32=NULL;
	DISPLAY_DEVICE DispDev; 
	bool result=false;

	if (NULL==display_name)
	{
		return false;
	}

	//加载动态库
	hInstUser32 = LoadLibrary(L"User32.DLL");
	if (NULL==hInstUser32) 
	{
		//加载动态库失败
		return false;  
	}

	// Get the address of the EnumDisplayDevices function
	pEnumDisplayDevices = (pfEnumDisplayDevice)GetProcAddress(hInstUser32,"EnumDisplayDevicesW");
	if(NULL==pEnumDisplayDevices) 
	{
		//释放动态库
		FreeLibrary(hInstUser32);
		return false;
	}

	ZeroMemory(&DispDev, sizeof(DispDev));
	DispDev.cb = sizeof(DispDev); 

	// After the first call to EnumDisplayDevices, 
	// DispDev.DeviceString is the adapter name
	if (pEnumDisplayDevices(NULL, device_index, &DispDev, 0)) 
	{
		//得到显卡的设备名
		_tcscpy(display_name, DispDev.DeviceName);
		
		// After second call, DispDev.DeviceString is the 
		// monitor name for that device 
		//pEnumDisplayDevices(display_name, 0, &DispDev, 0);   

		// In the following, lpszMonitorInfo must be 128 + 1 for 
		// the null-terminator.
		//_tcscpy(display_name, DispDev.DeviceName);
		//hr = StringCchCopy(lpszMonitorInfo, 129, DispDev.DeviceString);

		result = true;
	}
	else
	{
		result = false;
	}
	//释放动态库
	FreeLibrary(hInstUser32);

	return result;
}

bool Cflashktv10Wnd::get_display_device_settings(int device_number,int &position_x,int &position_y,int &width,int &height)
{
	try
	{
		TCHAR display_device[256];
		DEVMODE device_mode; 
		bool result=false;

		ZeroMemory(&device_mode, sizeof(device_mode));
		ZeroMemory(display_device,sizeof(display_device));
		device_mode.dmSize = sizeof(DEVMODE);

		//use default display name
		swprintf(display_device, L"\\\\.\\display%d",device_number);
		//得到显卡的当前设置
		if(FALSE==EnumDisplaySettings(display_device, ENUM_CURRENT_SETTINGS, (DEVMODE*)&device_mode)) 
		{
			//get display name
			result = get_display_monitor_info(device_number-1,display_device);
			if (result)
			{
				if(FALSE==EnumDisplaySettings(display_device, ENUM_CURRENT_SETTINGS, (DEVMODE*)&device_mode)) 
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		//得到起始位置
		position_x = device_mode.dmPosition.x;
		position_y = device_mode.dmPosition.y;
		//得到分辨率
		width = device_mode.dmPelsWidth;
		height = device_mode.dmPelsHeight;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::set_display_device_resolution(int device_number,int start_x,int start_y,int width,int height)
{
	try
	{
		TCHAR display_device[256];
		DEVMODE device_mode; 
		long result=0;


		ZeroMemory( &device_mode, sizeof(device_mode));
		ZeroMemory(display_device,sizeof(display_device));
		device_mode.dmSize = sizeof(DEVMODE);
		device_mode.dmPosition.x = start_x;
		device_mode.dmPosition.y = start_y;
		device_mode.dmPelsWidth = width;
		device_mode.dmPelsHeight = height;
		device_mode.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_POSITION;

		//use default display name
		swprintf(display_device, L"\\\\.\\display%d",device_number);
		//change display resolution
		result = ChangeDisplaySettingsEx(display_device,&device_mode,NULL,CDS_GLOBAL|CDS_UPDATEREGISTRY,NULL);
		if (DISP_CHANGE_SUCCESSFUL==result)
		{
			return true;
		}
		else
		{
			TCHAR szMsg[256] = {0x00};
			swprintf(szMsg, L"强制转换分辨率失败!result = %d", result);
			WriteLog(__FL__, szMsg);

			//get display name
			result = get_display_monitor_info(device_number-1,display_device);
			if (!result)
			{
				return false;
			}
			result = ChangeDisplaySettingsEx(display_device,&device_mode,NULL,CDS_GLOBAL|CDS_UPDATEREGISTRY,NULL);
			if (DISP_CHANGE_SUCCESSFUL==result)
			{
				return true;
			}else{
				TCHAR szMsg[256] = {0x00};
				DWORD dwError = GetLastError();
				swprintf(szMsg, L"第二次强制转换分辨率失败!result = %d", result);
				WriteLog(__FL__, szMsg);
			}
		}

		return false;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::delete_expire_log(void)
{
	try
	{
		CTime ctCurTime;
		CTime ctPreTime;
		CTimeSpan ctsDaySpan(30,0,0,0);
		TCHAR log_path[256];

		memset(log_path,0x0,sizeof(log_path));

		//now time
		ctCurTime = CTime::GetCurrentTime();
		//previous time
		ctPreTime = ctCurTime-ctsDaySpan;

		swprintf(log_path,L"%s\\log",m_work_path);
		if (PathFileExists(log_path))
		{
			CFileFind cLogFileFind;
			BOOL bRet=FALSE;
			CString strFilePath;
			CString strFileName;
			TCHAR szTemp[32];
			int nYear=0;
			int nMonth=0;
			int nDay=0;

			_tcscat(log_path,L"\\*.log");
			bRet = cLogFileFind.FindFile(log_path);
			while (bRet)
			{
				bRet = cLogFileFind.FindNextFile();
				if (cLogFileFind.IsDots() || cLogFileFind.IsDirectory())
				{
					continue;
				}
				//get file path
				strFilePath = cLogFileFind.GetFilePath();
				//get file title
				strFileName = cLogFileFind.GetFileTitle();
				//get file date
				memset(szTemp,0x0,sizeof(szTemp));
				memcpy(szTemp,strFileName.GetBuffer(0)+6,8);
				if (0!=_tcscmp(szTemp,L""))
				{
					nYear = 0;
					swscanf(szTemp,L"%d",&nYear);
				}
				memset(szTemp,0x0,sizeof(szTemp));
				memcpy(szTemp,strFileName.GetBuffer(0)+11,4);
				if (0!=_tcscmp(szTemp,L""))
				{
					nMonth = 0;
					swscanf(szTemp,L"%d",&nMonth);
				}
				memset(szTemp,0x0,sizeof(szTemp));
				memcpy(szTemp,strFileName.GetBuffer(0)+14,4);
				if (0!=_tcscmp(szTemp,L""))
				{
					nDay = 0;
					swscanf(szTemp,L"%d",&nDay);
				}
				if ((nYear<2000) || (nMonth<=0) || (nMonth>12) || (nDay<=0) || (nDay>31))
				{
					DeleteFile(strFilePath);
					continue;
				}
				CTime ctFileTime(nYear,nMonth,nDay,23,59,59);
				if (ctFileTime<ctPreTime)
				{
					//delete file,if this file already expire
					DeleteFile(strFilePath);
				}
			}
			cLogFileFind.Close();
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::delete_recorder_file(void)
{
	try
	{
		config_file_manager config_file;
		TCHAR recorder_path[256];
		CFileFind recorder_file_find;
		BOOL result=FALSE;
		CString file_path;

		memset(recorder_path,0x0,sizeof(recorder_path));

		if (m_recorder_dir.empty())
		{
			return;
		}
		swprintf(recorder_path,L"%s\\*.*",m_recorder_dir.c_str());
		result = recorder_file_find.FindFile(recorder_path);
		while (result)
		{
			result = recorder_file_find.FindNextFile();

			if (recorder_file_find.IsDots() || recorder_file_find.IsDirectory() || recorder_file_find.IsSystem())
			{
				continue;
			}

			//得到文件路径
			file_path = recorder_file_find.GetFilePath();
			//删除该文件
			DeleteFile(file_path);
		}
		//关闭文件查找
		recorder_file_find.Close();
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::show_flash_interface(void)
{
	try
	{
		BOOL result=FALSE;
		CString flash_path;
		TCHAR request[1024];
		TCHAR data[1024];
		int control_bar_height=0;
		CTime system_time = CTime::GetCurrentTime();

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		
		//得到形象页路径
		if (SCREEN_TYPE_VERTICAL==m_interface_type)
		{
			if (0 == _tcscmp(m_cur_interface_version, L"ek800") || 0 == _tcscmp(m_cur_interface_version, L"face800"))
			{
				//竖版
				swprintf(m_image_page_path,L"%s\\%s\\v\\default800.jpg",m_work_path,g_folder_name[5]);
				swprintf(m_video_bg_path,L"%s\\%s\\v\\video_bg800.jpg",m_work_path,g_folder_name[5]);
			}
			else
			{
				//竖版
				swprintf(m_image_page_path,L"%s\\%s\\v\\default720.jpg",m_work_path,g_folder_name[5]);
				swprintf(m_video_bg_path,L"%s\\%s\\v\\video_bg720.jpg",m_work_path,g_folder_name[5]);
			}			
		}
		else
		{
			if (0 == _tcscmp(m_cur_interface_version, L"ek800") || 0 == _tcscmp(m_cur_interface_version, L"face800"))
			{
				//横版
				swprintf(m_image_page_path,L"%s\\%s\\h\\default800.jpg",m_work_path,g_folder_name[5]);
			}
			else
			{
				//竖版
				//横版
				swprintf(m_image_page_path,L"%s\\%s\\h\\default720.jpg",m_work_path,g_folder_name[5]);
			}	

			
		}
		//创建主的flash播放器		
		result = m_flash_player.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,m_first_display_width,m_first_display_height),this,FLASH_PLAYER_WINDOW_ID);
		if (!result)
		{
			return false;
		}
		//重置消息响应函数
		m_flash_player.EnableNotification();
		//自适应宽度
		m_flash_player.put_Scale(L"exactfit");
		SetWindowLong(this->m_hWnd, GWL_STYLE, GetWindowLong(this->m_hWnd, GWL_STYLE) & WS_CAPTION);//去掉标题栏
		//得到flash路径
		if (SCREEN_TYPE_VERTICAL==m_interface_type)
		{
			//竖版
			flash_path.Format(L"%s\\%s\\%sv.swf",m_work_path,g_folder_name[2], m_cur_interface_version);
		}
		else
		{
			//横版
			flash_path.Format(L"%s\\%s\\%sh.swf",m_work_path,g_folder_name[2], m_cur_interface_version);
		}
		m_flash_player.LoadMovie(0,flash_path);

		//WriteLog(__FL__, flash_path);
		m_flash_player.put_WMode(L"transparent");
		m_flash_player.Stop();
		m_flash_player.ShowWindow(SW_SHOW);
		

		//创建子flash播放器
		if (SCREEN_TYPE_VERTICAL==m_interface_type)
		{
			//竖版
			control_bar_height = 170*m_first_display_width/1280;  //按照宽度锁房高度
			//control_bar_height = 146*m_first_display_width/1280;  //按照宽度锁房高度

		}
		else
		{
			control_bar_height = 146;//*m_first_display_width/1280;  //按照宽度锁房高度
			//control_bar_height = 146*m_first_display_width/1280;  //按照宽度锁房高度
		}

		m_controlbar_flash_player_exist = m_controlbar_flash_player.Create(NULL,WS_CHILD,CRect(0,0,m_first_display_width,control_bar_height),this,SUB_FLASH_PLAYER_WINDOW_ID);
		if (m_controlbar_flash_player_exist)
		{
			//得到小面板路径
			flash_path.Format(L"%s\\%s\\miniPanel.swf",m_work_path,g_folder_name[3]);
			m_controlbar_flash_player.LoadMovie(0,flash_path);
			m_controlbar_flash_player.Stop();
			//m_flash_player.put_WMode(L"transparent");
			//m_controlbar_flash_player.put_Scale(L"exactfit");
			m_controlbar_flash_player.ShowWindow(SW_HIDE);
		}

		if (m_use_test_function)
		{
			m_test_flash_player_exist = m_test_flash_player.Create(NULL,WS_CHILD,CRect(m_first_display_x,m_first_display_y,m_first_display_x+m_first_display_width,m_first_display_y+m_first_display_height),this,TEST_MACHINE_PLAYER_WINDOW_ID);
			if (m_test_flash_player_exist)
			{
				//得到测机界面路径，测机复用了该播放器
				flash_path.Format(L"%s\\%s\\waitui.swf",m_work_path,g_folder_name[4]);
				m_test_flash_player.LoadMovie(0,flash_path);
				m_test_flash_player.Stop();
				m_test_flash_player.BringWindowToTop();
				m_test_flash_player.ShowWindow(SW_SHOW);

				//显示图片和文字
				swprintf(data,L"<data><info url=\"%s\" txt=\"系统正在初始化，请等待......\"/></data>",m_image_page_path);
				result = m_flash_manage.make_request(request,sizeof(request)/2,L"bgAndTxt",data);
				if (result)
				{
					m_test_flash_player.CallFunction(request);
				}
			}
		}

		//游戏播放器
		m_local_game_flash_player_exist = m_local_game_flash_player.Create(NULL,WS_CHILD,CRect(0,0,10,10),this,LOCAL_GAME_PLAYER_WINDOW_ID);
		if (m_local_game_flash_player_exist)
		{
			//设置消息处理函数
			m_local_game_flash_player.EnableNotification();
			m_local_game_flash_player.Stop();
			m_local_game_flash_player.put_WMode(L"transparent");
			m_local_game_flash_player.put_Scale(L"exactfit");
			m_local_game_flash_player.ShowWindow(SW_HIDE);
		}
		//内嵌酒水
		if (m_use_plug_in_drinks)
		{
			m_drinks_flash_player_exist = m_drinks_flash_player.Create(NULL,WS_CHILD,CRect(0,0,m_first_display_width,m_first_display_height),this,DRINKS_FLASH_PLAYER_WINDOW_ID);
			if(m_drinks_flash_player_exist)
			{
				m_drinks_flash_player.Stop();
				m_drinks_flash_player.ShowWindow(SW_HIDE);
			}
		}

		return true;
	}
	catch (...)
	{

	}

	return false;
}

void Cflashktv10Wnd::open_control_box_com(void)
{
	try
	{
		config_file_manager config_file;
		bool result=false;

		//对串口进行初始化
		config_file.init(L"com.ini");
		m_use_audio_effect = config_file.read_boolean(L"setting",L"conn_audio_effect",false);
		result = config_file.read_boolean(L"setting",L"com_enable",false);
		if (result)
		{
			//启动串口通讯
			int com_port = config_file.read_integer(L"setting",L"com_port",1);
			std::wstring com_parameter = config_file.read_string(L"setting",L"comm_parameter",L"1200,S,8,1");
			//初始化串口
			m_inherit_com.init_com(m_hWnd,DM_BOX_COM_RECEIVE_MESSAGE,L"com.ini");
			//打开串口
			result = m_inherit_com.open(com_port,com_parameter.c_str());
			result = m_inherit_com.is_open();
			if (result)
			{
				//发送开机初始化串口值
				write_com_data(COM_SEND_POWER_ON);
				WriteLog(__FL__, L"中控盒的串口打开成功");
			}
			else
			{
				WriteLog(__FL__, L"中控盒的串口打开失败");
			}
		}
		//对备份中控盒串口进行初始化
		config_file.init(L"com_second.ini");
		result = config_file.read_boolean(L"setting",L"com_enable",false);
		if (result)
		{
			//启动串口通讯
			int com_port = config_file.read_integer(L"setting",L"com_port",1);
			std::wstring com_parameter = config_file.read_string(L"setting",L"comm_parameter",L"1200,S,8,1");
			//初始化串口
			m_inherit_bak_com.init_com(m_hWnd,DM_BOX_COM_RECEIVE_MESSAGE,L"com_second.ini");
			//打开串口
			result = m_inherit_bak_com.open(com_port,com_parameter.c_str());
			result = m_inherit_bak_com.is_open();
			if (result)
			{
				//发送开机初始化串口值
				write_com_data(COM_SEND_POWER_ON);
				WriteLog(__FL__, L"第二个中控盒的串口打开成功");
			}
			else
			{
				WriteLog(__FL__, L"第二个中控盒的串口打开失败");
			}
		}
		//对备份中控盒串口进行初始化
		config_file.init(L"com_three.ini");
		result = config_file.read_boolean(L"setting",L"com_enable",false);
		if (result)
		{
			//启动串口通讯
			int com_port = config_file.read_integer(L"setting",L"com_port",1);
			std::wstring com_parameter = config_file.read_string(L"setting",L"comm_parameter",L"1200,S,8,1");
			//初始化串口 不接收数据 ZHEN 2013-01-07
			//m_inherit_three_com.init_com(m_hWnd,DM_BOX_COM_RECEIVE_MESSAGE,L"com_three.ini");
			m_inherit_three_com.init_com(m_hWnd,WM_USER,L"com_three.ini");
			//打开串口
			result = m_inherit_three_com.open(com_port,com_parameter.c_str());
			result = m_inherit_three_com.is_open();
			if (result)
			{
				//发送开机初始化串口值
				write_com_data(COM_SEND_POWER_ON);
				WriteLog(__FL__, L"第三个中控盒的串口打开成功");
			}
			else
			{
				WriteLog(__FL__, L"第三个中控盒的串口打开失败");
			}
		}
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::show_logo_osd(void)
{
	try
	{
		TCHAR path[256];
		int index=0;
		bool result=false;
		config_file_manager config_file;

		memset(path,0x0,sizeof(path));

		//读取客户配置
		result = config_file.read_boolean(L"osd",L"show_osd",true);
		if (!result)
		{
			//不显示osd
			return false;
		}

		//得到logo的坐标
		m_tv_logo_x = config_file.read_integer(L"osd",L"tv_logo_x_pos",20);
		m_tv_logo_y = config_file.read_integer(L"osd",L"tv_logo_y_pos",20);

		//公司log文件夹路径
		swprintf(path,L"%s\\%s\\logo",m_work_path,g_folder_name[6]);
		//设置logo路径
		result = m_osd_play_manager.set_logo_osd_path(path);
		if (!result)
		{
			return false;
		}
		//得到第一个要播放的logo信息
		memset(path,0x0,sizeof(path));
		result = m_osd_play_manager.get_logo_osd_info(path,index);
		if (!result)
		{
			return false;
		}
		if (!PathFileExists(path))
		{
			return false;
		}
		//播放logo
		result = m_player_manager.play_logo_osd(path,index,m_tv_logo_x,m_tv_logo_y,true);
		if (!result)
		{
			return false;
		}
		//启动定时器，循环播放
		show_logo_timer_identifier = SetTimer(SHOW_LOGO_TIMER_EVENT_ID,100,NULL);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::show_next_logo_osd(bool reload)
{
	try
	{
		TCHAR path[256];
		int index=0;
		bool result=false;

		memset(path,0x0,sizeof(path));

		if ((!reload)&&m_show_song_tip_osd)
		{
			//显示全屏下一首提示时，不显示场所logo
			WriteLog(__FL__, L"LOGO:显示全屏下一首提示时，不显示场所logo");
			return;
		}

		if (0 == show_logo_timer_identifier)
		{
			WriteLog(__FL__, L"LOGO:定时器的值等于0");
			return;
		}

		if (reload)
		{
			m_player_manager.init_osd();
		}

		//得到下一个要播放的logo信息
		result = m_osd_play_manager.get_logo_osd_info(path,index);
		if (!result)
		{
			WriteLog(__FL__, L"LOGO:获得LOGO路径失败!");
			WriteLog(__FL__, path);
			return;
		}
		//播放logo
		result = m_player_manager.play_logo_osd(path,index,m_tv_logo_x,m_tv_logo_y,reload);
		if (!result)
		{
			WriteLog(__FL__, L"LOGO:播放LOGO失败!");
			WriteLog(__FL__, path);
			return;
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}

bool Cflashktv10Wnd::flash_player_call_function(TCHAR *request)
{
	try
	{
		if (m_flash_screen_init_finish)
		{
			//m_call_fun_lock.lock();
			//只有flash初始化完成之后，才能调用该函数
			m_flash_player.CallFunction(request);
			//m_call_fun_lock.unlock();
			return true;
		}

		return false;
	}
	catch (...)
	{		
	}
	return false;
}

void Cflashktv10Wnd::send_master_slave_control_code(int control_code)
{
	try
	{
		char data[512];

		memset(data,0x0,sizeof(data));

		switch(control_code)
		{
			//呼叫服务
		case CALL_ATTENDANT:       //呼叫服务员
		case CALL_PR_MANAGER:      //公关经理
		case CALL_ACOUSTICS_ENGINEER: //音响师
		case CALL_CLEANER: //保洁员
		case CALL_DUTY_MANAGER: //值班经理
		case CALL_ORDER_DINNER: //点餐
		case CALL_CUP:        //杯子
		case CALL_PAY_MONEY: //买单
		case CALL_CONSULTION: //咨询

			//歌曲控制功能
		case SONG_REPLAY:        //重唱
		case SONG_ACCOMPANY_ORIGINAL: //伴唱或原唱
		case SONG_PLAY_PAUSE:        //播放或暂停
		case SONG_MUTE_UNMUTE:        //静音
		case SONG_ENJOYMERT:        //欣赏
			//音量
		case MUSIC_VOLUME_UP:  //音乐的音量加
		case MUSIC_VOLUME_DOWN:  //音乐的音量减
		case MICROPHONE_VOLUME_UP:  //麦克风的音量加
		case MICROPHONE_VOLUME_DOWN:  //麦克风的音量减
		case TUNE_UP:  //音调增
		case TUNE_DOWN:   //音调减
		case TUNE_ORIGINAL:   //原调
		case REVERBERATION_DOWN:  //混响减
		case REVERBERATION_UP:  //混响加
			//气氛
		case ATMOSPHERE_APPLAUSE:  //鼓掌
		case ATMOSPHERE_CHEER:  //欢呼
		case ATMOSPHERE_OUTCRY:  //催眠
		case ATMOSPHERE_WHISTLE:  //狂汗

		case	ATMOSPHERE_HAOZAN: //好赞
		case	ATMOSPHERE_SHIHUA ://石化
		case	ATMOSPHERE_XIANHUA://献花
		case	ATMOSPHERE_TUXUE : //吐血
		case	ATMOSPHERE_FEIWEN ://飞吻
		case	ATMOSPHERE_XINSUI ://心碎
		case	ATMOSPHERE_HAIXIU ://害羞
		case	ATMOSPHERE_ZADAN ://砸蛋
			//音效
		case AUDIO_EFFECT_STANDARD:  //标准
		case AUDIO_EFFECT_THEATER:  //剧场
		case AUDIO_EFFECT_PROFESSIONAL:  //唱将
		case AUDIO_EFFECT_MAGIC:  //魔音
		case AUDIO_EFFECT_RESERVE1:
		case AUDIO_EFFECT_RESERVE2:
			//环境音
		case ENVIRONMENT_AUDIO_CLOSE:  //关闭环境音
		case ENVIRONMENT_AUDIO_MEETING:  //会议
		case ENVIRONMENT_AUDIO_AIRPORT:  //飞机场
		case ENVIRONMENT_AUDIO_ROAD:  //马路上
		case ENVIRONMENT_AUDIO_STATION:  //火车站
		case ENVIRONMENT_AUDIO_MAHJONG:  //麻将
		case ENVIRONMENT_AUDIO_RAIN:     //下雨中
			//灯光
		case LIGHT_OPEN:  //灯光 开
		case LIGHT_CLOSE:  //灯光 关闭
		case LIGHT_STANDARD:  //灯光 标准
		case LIGHT_BACKGROUND:  //灯光 背景
		case LIGHT_STAGE:  //灯光 舞台
		case LIGHT_SCINTILLATION:  //灯光 屏闪
		case LIGHT_OPEN1:     //灯光1
		case LIGHT_OPEN2:     //灯光1
		case LIGHT_OPEN3:     //灯光1
		case LIGHT_OPEN4:     //灯光1
		case LIGHT_OPEN5:     //灯光1
		case LIGHT_OPEN6:     //灯光1
		case LIGHT_OPEN7:   //灯光1
		case LIGHT_OPEN8:   //灯光1
			//空调
		case AIR_CONDITION_STRONG:       //空调强
		case AIR_CONDITION_MID:          //空调中
		case AIR_CONDITION_WEAK:         //空调弱
		case AIR_CONDITION_CLOSE:        //空调关闭
		case DISCHARGE_AIR_FUNCTION:     //排风

		case MUSIC_SOUND_STANDARD:  //音乐音效标准
		case MUSIC_SOUND_THEATER:  //音乐音效剧场
		case MUSIC_SOUND_PROFESSIONAL:  //音乐音效唱将
		case MUSIC_SOUND_MAGIC:  //音乐音效魔音
		case MUSIC_SOUND_RESERVE1:  //音乐音效自动
		case MUSIC_SOUND_RESERVE2:  //音乐音效预留
		case MUSIC_SOUND_RESERVE3:  //音乐音效预留
		case MUSIC_SOUND_RESERVE4:  //音乐音效预留
		case ENTER_GUIDE_SONG:     //主旋伴奏
		case EXIT_GUIDE_SONG:     //进入导唱
		case LIGHT_AUTO_SWITCH:  //自动灯光
			{
				//转化成字符串
				sprintf(data,"CONTROL%d",control_code);
				//发送控制码
				send_master_slave_data(NULL,data);
			}
			break;
		default:
			break;
		}

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::send_request_service(int button_number,TCHAR *service_content)
{
	try
	{
		TCHAR message[1024];
		bool result=false;

		memset(message,0x0,sizeof(message));

		//设置标识
		m_call_service_state = true;
		//发送给中控盒
		write_com_data(COM_SEND_REQUEST_SERVER);
		//发送给消息服务器
		swprintf(message,L"Message^&系统消息:呼叫%s！;同时显示;文字;^&%s^&%s^&0",service_content,_tcsupr(m_show_room_name),_tcslwr(m_show_room_name));
		
		send_message_to_msg_server(message);

		//显示服务控制osd
		result = show_control_osd(CONTROL_OSD__SERVICE);
		if (result)
		{
			//启动控制osd播放时间的定时器
			set_control_osd_show_timer();
		}
		//界面上提示，服务申请已经发出
		flash_show_tip_message(11);
		//记录按下的服务按钮编号
		m_click_service_button_number = button_number;
		//设置服务按钮状态
		send_service_button_state(button_number,1);
		//发送给门牌机
		send_service_state_to_doorplate(true);

		return;
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::send_message_to_msg_server(TCHAR *message)
{
	try
	{
		string_conversion str_conv;
		int byte_size=0;
		int malloc_size=0;
		bool result=false;

		//首先记录下要发送的消息
		memset(m_send_message,0x0,sizeof(m_send_message));
		
		//判断是否越界
		byte_size = str_conv.get_byte_size_of_multibyte(message);
		malloc_size = sizeof(m_send_message)/sizeof(char);
		if (byte_size>=malloc_size)
		{
			message[malloc_size-10]=_T('\0');
		}
		//转化成多字节
		result = str_conv.widechar_to_multibyte(message,m_send_message,malloc_size);
		if (!result)
		{
			return false;
		}
		//由于要采用TCP方式，为了防止阻塞，采用线程方式
		AfxBeginThread(Cflashktv10Wnd::send_message_thread,this);
		
		return true;
	}
	catch (...)
	{

	}

	return false;
}

UINT Cflashktv10Wnd::send_message_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);

		pThis->send_message_function();
	}
	catch (...)
	{

	}
	return 0;
}

bool Cflashktv10Wnd::send_message_function(void)
{
	try
	{
		for (int i=0;i<m_msg_server_count;i++)
		{
			//得到IP
			if (0==strcmp(m_msg_server_ip[i],""))
			{
				continue;
			}
			if (0==strcmp(m_msg_server_ip[i],m_send_room_ip))
			{
				//如果服务器IP等于本机器IP，不发送，防止自发自收消息
				continue;
			}
			// 创建套节字
			SOCKET send_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(send_socket == INVALID_SOCKET)
			{
				continue;
			}
			//off TIME_WAIT
			struct linger zeroLinger;	
			zeroLinger.l_onoff = 1;	
			zeroLinger.l_linger = 5;

			setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

			int m_nSendTimeout = 6000;
			//set send timeout
			setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));

			// 也可以在这里调用bind函数绑定一个本地地址
			// 否则系统将会自动安排

			// 填写远程地址信息
			sockaddr_in servAddr; 
			servAddr.sin_family = AF_INET;
			servAddr.sin_port = htons(6000);
			// 注意，这里要填写服务器程序所在机器的IP地址
			// 如果你的计算机没有联网，直接使用127.0.0.1即可
			servAddr.sin_addr.S_un.S_addr = inet_addr(m_msg_server_ip[i]);

			//连接socket
			if(::connect(send_socket, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
			{
				::closesocket(send_socket);
				continue;
			}

			//发送数据
			int send_len = (int)strlen(m_send_message);
			int nRecv = ::send(send_socket, m_send_message, send_len,0);
			if(nRecv > 0)
			{
				//发送数据成功
			}
			// 关闭套节字
			::closesocket(send_socket);
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::set_control_osd_show_timer(void)
{
	show_control_osd_timer_identifier = SetTimer(SHOW_CONTROL_OSD_TIMER_EVENT_ID,m_control_osd_show_time*1000,NULL);

	return;
}

void Cflashktv10Wnd::set_bmp_picture_show_timer(int show_time)
{
	show_bmp_picture_timer_identifier = SetTimer(SHOW_BMP_PICTURE_TIMER_EVENT_ID,show_time,NULL);

	return;
}

void Cflashktv10Wnd::set_score_show_timer(int show_time)
{
	show_score_timer_identifier = SetTimer(SHOW_SCORE_TIMER_EVENT_ID,show_time,NULL);

	return;
}
void Cflashktv10Wnd::set_screen_flash_timer(int show_time)
{
	show_screen_timer_identifier = SetTimer(SHOW_SCREEN_FLASH_TIMER_EVENT_ID,show_time,NULL);

	return;
}
void Cflashktv10Wnd::update_flash_control_button(void)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//2011-06-22  屏蔽
		//if (2==m_master_slave_control_flag)
		//{
			//被控机，不采用该方式更新，而是有主控机发送过来
		//	return;
		//}

		//组织字符串
		result = m_player_manager.make_panel_list_xml(data);
		if (!result)
		{
			return;
		}
		//传递给flash
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"pubMainBtn",data);
		if (result)
		{
			flash_player_call_function(request);
			if (1==m_master_slave_control_flag)
			{
				TCHAR send_data[1024];

				memset(send_data,0x0,sizeof(send_data));

				swprintf(send_data,L"PANELINFO%s",request);
				//发送更新面板信息给被控机
				send_master_slave_data(send_data,NULL);
			}
		}
		
		//更新控制条的按钮状态
		if (m_controlbar_flash_player_exist && m_show_screen_saver_state && m_controlbar_flash_player.IsWindowVisible())
		{
			//显示视频屏保状态，要同时更新浮动的控制面板状态
			memset(data,0x0,sizeof(data));
			memset(request,0x0,sizeof(request));
			//组织按钮状态字符串
			result = m_player_manager.make_control_bar_list_xml(data);
			if (result)
			{
				result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"panel_info",data);
				if (result)
				{
					m_controlbar_flash_player.CallFunction(request);
				}
			}
		}
		//更新演唱台的按钮状态
		if (m_slave_parent_window_exist&&m_slave_window_flash_player_exist&&m_slave_window_flash_player.IsWindowVisible())
		{
			memset(data,0x0,sizeof(data));
			memset(request,0x0,sizeof(request));

			result = m_player_manager.make_control_bar_list_xml(data);
			if(result)
			{
				result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"panel_info",data);
				if (result)
				{
					m_slave_window_flash_player.CallFunction(request);
				}
			}
		}//end if
		//更新墙面板的按钮状态
		if (m_wall_panel_window_exist && m_wall_panel_flash_player_exist&&m_wall_panel_flash_player.IsWindowVisible())
		{
			memset(data,0x0,sizeof(data));
			memset(request,0x0,sizeof(request));

			result = m_player_manager.make_control_bar_list_xml(data);
			if(result)
			{
				result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"panel_info",data);
				if (result)
				{
					m_wall_panel_flash_player.CallFunction(request);
				}
			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::update_flash_audio_info(void)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		/*
		if (2==m_master_slave_control_flag)
		{
			//被控机，不采用该方式更新，而是有主控机发送过来
			return;
		}*/

		//组织字符串
		result = m_player_manager.make_volume_list_xml(data);
		if (!result)
		{
			return;
		}
		//传递给flash，更新声音的数值
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"pubAudioInfo",data);
		if (result)
		{
			flash_player_call_function(request);
			if (1==m_master_slave_control_flag)
			{
				TCHAR send_data[1024];

				memset(send_data,0x0,sizeof(send_data));

				swprintf(send_data,L"AUDIOINFO%s",request);
				//发送更新面板信息给被控机
				send_master_slave_data(send_data,NULL);
			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

bool Cflashktv10Wnd::play_osd_text(TCHAR *text,enum OSD_PLAY_MODE scroll_mode,int scroll_count)
{
	try
	{
		TCHAR background_path[256];
		bool result=false;
		text_osd_info text_info;
		play_variable text_play_variable;

		memset(background_path,0x0,sizeof(background_path));

		if (!m_tv_osd_allow_cut)
		{
			//如果不允许切掉就要检测一下
			result = tv_osd_play_finish();
			if (!result)
			{
				//没有播放完成就不要切掉
				return false;
			}
		}

		//设置要播放的文字
		result = m_osd_play_manager.set_osd_text(text);
		if (!result)
		{
			return false;
		}
		//设置播放模式
		result = m_osd_play_manager.m_osd_text_picture.set_scroll_mode(scroll_mode,MESSAGE_TEXT);
		if (!result)
		{
			return false;
		}
		//修改滚动次数为1次
		result = m_osd_play_manager.m_osd_text_picture.set_scroll_count(scroll_count);
		if (!result)
		{
			return false;
		}
		//得到背景路径
		result = m_osd_play_manager.get_background_path(background_path);
		if (!result)
		{
			return false;
		}
		result = m_osd_play_manager.m_osd_text_picture.get_text_info(text_info);
		if (!result)
		{
			return false;
		}
		result = m_osd_play_manager.m_osd_text_picture.get_text_play_variable(text_play_variable);
		if(!result)
		{
			return false;
		}
		//播放osd text
		result = m_player_manager.play_text_osd(background_path,text_info,text_play_variable);
		if (!result)
		{
			return false;
		}

		//发送过来的消息允许切掉
		m_tv_osd_allow_cut = true;

		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::show_quit_video_screen_saver(void)
{
	try
	{
		int page_index=0;
		int video_player_state=PLAYER_STATE_INIT;

		if (m_show_screen_saver_state)
		{
			//现在是视频屏保状态，取消视频屏保2014-04-09
			pc_show_video_window();

			//隐藏视频屏保
			m_start_video_screen_saver=false;
		}
		else
		{
			//得到播放器状态
			video_player_state = m_player_manager.get_player_state();
			//得到页面索引
			page_index = m_flash_manage.get_last_page_index();
			if ((page_preview==page_index)||(page_game==page_index)||(PLAYER_STATE_CLOSED==video_player_state)||(PLAYER_STATE_INIT==video_player_state)||(m_audio_effect_window.IsWindowVisible()))
			{
				//预览和游戏页面、音效窗口不允许视频窗口放大
				//break;
			}
			else
			{
				//显示视频屏保
				show_video_screen_saver();
				m_start_video_screen_saver=true;
			}
		}

		return;
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::open_preview_audio(void)
{
	try
	{
		config_file_manager config_file;
		bool preview_song_open_audio=false;        //预览歌曲是否打开音频，true：打开 false：不打开

		//预览歌曲是否打开音频
		preview_song_open_audio = config_file.read_boolean(L"preview_song",L"open_audio",false);
		//设置预览声音 
		if (!m_soft_decode_window_exist&&preview_song_open_audio)
		{
			//打开音频，软解不能打开音频
			m_player_manager.Set(SD_PREVIEW_AUDIO_ONOFF,1);
		}
		else
		{
			//不打开音频
			m_player_manager.Set(SD_PREVIEW_AUDIO_ONOFF,0);
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::pc_show_video_window(void)
{
	try
	{
		if (!m_screen_show_video)   //不显示屏切
		{
			return;
		}
		//得到当前页面索引
		int page_index = m_flash_manage.get_last_page_index();
		if (page_video == page_index)
		{
			//如果是屏切页面回到屏切窗口的视频播放位置
			switch_screen_show_video_window();
		}
		else if (page_preview == page_index)
		{
			//显示预览窗口 
			preview_screen_show_video_window();
		}
		else
		{
			//回到主界面的视频播放窗口
			return_select_song_window();
		}
	}
	catch (...)
	{
		
	}
	return;
}
void Cflashktv10Wnd::preview_screen_show_video_window(void)
{
	try
	{
		int page_index = m_flash_manage.get_last_page_index();

		//显示
		if (m_screen_show_window_exist && (VIDEO_TYPE_SONG==pc_play_video_type))
		{
			//显示主面板，就显示
			m_screen_show_window.MoveWindow(CRect(m_video_left_top_x,m_video_left_top_y,m_video_right_button_x,m_video_right_button_y));
			m_preview_window.MoveWindow(CRect(m_preview_left_top_x,m_preview_left_top_y,m_preview_right_bottom_x,m_preview_right_bottom_y));
			if (SCREEN_TYPE_VERTICAL==m_interface_type)
			{
				CRect window_rect;
				m_screen_show_window.GetClientRect(&window_rect);
				m_sub_screen_show_window.MoveWindow(window_rect);
			}
#ifdef DON_GUAN_K_PLUS
			m_screen_show_window.show_window(false);
			m_player_manager.show_screen_video(false);
#else
			m_screen_show_window.show_window(true);
			m_player_manager.show_screen_video(true);			
#endif //DON_GUAN_K_PLUS
			
			//隐藏其他窗口，增加软件自我恢复功能
			m_lobby_live_window.show_window(false);
			m_tv_window.show_window(false);
			m_preview_window.show_window(true);
		}
		else if (m_lobby_live_window_exist && (VIDEO_TYPE_LOBBY_LIVE==pc_play_video_type))
		{
			m_lobby_live_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y),TRUE);
			m_lobby_live_window.show_window(true);
			//隐藏其他窗口，增加软件自我恢复功能
			m_screen_show_window.show_window(false);
			m_tv_window.show_window(false);
			m_preview_window.show_window(false);
		}
		else if (m_tv_window_exist && (VIDEO_TYPE_TV==pc_play_video_type))
		{
			m_tv_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y),TRUE);
			m_tv_window.show_window(true);
			//隐藏其他窗口，增加软件自我恢复功能
			m_screen_show_window.show_window( false);
			m_lobby_live_window.show_window(false);
			m_preview_window.show_window(false);
		}
		else if (m_preview_window_exist && (VIDEO_TYPE_PREVIEW_SONG==pc_play_video_type))
		{
			m_preview_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y),TRUE);
			m_preview_window.show_window(true);
			//隐藏其他窗口，增加软件自我恢复功能
			m_screen_show_window.show_window(false);
			m_lobby_live_window.show_window(false);
			m_tv_window.show_window(false);
		}

		//隐藏控制面板
		if (m_controlbar_flash_player_exist)
		{
			m_controlbar_flash_player.ShowWindow(SW_HIDE);
		}
		//游戏窗口
		if (m_local_game_flash_player_exist)
		{
			m_local_game_flash_player.ShowWindow(SW_HIDE);
		}

		//发送屏保结束消息
		PostMessage(DM_SCREEN_SAVER_END,NULL,NULL);
	}
	catch (...)
	{
	}
	return;
}

void Cflashktv10Wnd::return_select_song_window(void)
{
	try
	{
		int page_index = m_flash_manage.get_last_page_index();

		if ((SCREEN_TYPE_HORIZON==m_interface_type && page_homepage==page_index)||!m_screen_show_video)
		{
			//辅助页面、首页或者竖版，都不显示视频窗口，隐藏
			if (m_screen_show_window_exist && m_screen_show_window.IsWindowVisible())
			{
				m_screen_show_window.show_window(false);
			}
			if (m_lobby_live_window_exist && m_lobby_live_window.IsWindowVisible())
			{
				m_lobby_live_window.show_window(false);
			}
			if (m_tv_window_exist && m_tv_window.IsWindowVisible())
			{
				m_tv_window.show_window(false);
			}
			if (m_preview_window_exist && m_preview_window.IsWindowVisible())
			{
				m_preview_window.show_window(false);
			}
		}
		else
		{
			if (m_screen_show_window_exist && m_screen_show_window.IsWindowVisible()&&page_singer_song!=page_index)
			{
				m_screen_show_window.show_window(false);
#ifndef DON_GUAN_K_PLUS
				if (!m_song_show_video_picture)
				{
					m_screen_show_window_exist = false;
				}
#endif // DON_GUAN_K_PLUS							
			}
			if (m_lobby_live_window_exist && m_lobby_live_window.IsWindowVisible())
			{
				m_lobby_live_window.show_window(false);
			}
			if (m_tv_window_exist && m_tv_window.IsWindowVisible())
			{
				m_tv_window.show_window(false);
			}
			if (m_preview_window_exist && m_preview_window.IsWindowVisible())
			{
				m_preview_window.show_window(false);
			}

			
			switch(page_index)
			{
			case page_homepage:   //没有屏切页面，就隐藏
			case page_assist:
			case page_earth:
			case page_search_song:
			case page_secondary_song:
			//case page_new_song:
			//case page_top_song:
			case page_movieMeun:
			case page_ktvExplain:
			case page_movie:
			case page_place_video:
			case page_concert:
			//case page_opera:
			//case page_singer:
			//case page_custom_song:
			case page_recording:
			case page_kala_share:     //K歌分享
			case page_dekaron_maiba:  //挑战麦霸
			case page_find_maiba:	 //发现麦霸
			case page_help:            //
			case page_maiba_login:    //麦霸登录、注册
			case page_consumer:       //消费查询
			case page_wechat:		  //微信点歌
			case page_encode:
			//case page_title:
			case page_home_song:
			case page_enterainment: //首页的娱乐互动
			case page_place_raiders: //首页的场所攻
			case page_aider_function: //首页的辅助功能
			case page_home_theme_song: //首页主题点歌
			case page_system_manager:
			case page_theme:
			case page_entertainment_programme:
			case page_music_enjoy:
			//case page_kugou_music:
			//case page_kuwo_music:
			//case page_qq_music:
			//case page_baidu_music:
			case page_system_info:
			case page_language_change:
			case page_phone_push:
			case page_yule_news:
			case page_change_skin:
			//case page_number_song:
			case page_drinks:
			case page_proposal:
			case page_fire:
			case page_guide:
			case page_video_dating:
			case page_singing_contest:
			case page_free_pk_view_list:
			case page_challenge_pk_view_list:
			case page_movie_detail:
			case page_trend_list:
			case page_challenge_star:
			case page_across_pass:
			case page_video_show:
			case page_listen_knowledge_song:
			case page_picture_mv:
			case page_active_game:
			case page_wechat_barrage:
				{
					if (m_screen_show_window_exist && m_screen_show_window.IsWindowVisible())
					{
						m_screen_show_window.show_window(false);
					}
					if (m_lobby_live_window_exist && m_lobby_live_window.IsWindowVisible())
					{
						m_lobby_live_window.show_window(false);
					}
					if (m_tv_window_exist && m_tv_window.IsWindowVisible())
					{
						m_tv_window.show_window(false);
					}
					if (m_preview_window_exist && m_preview_window.IsWindowVisible())
					{
						m_preview_window.show_window(false);
					}
#ifdef SICHUAN_M
					if (m_screen_msquare_window_exist && m_screen_msquare_window.IsWindowVisible())
					{
							m_screen_msquare_window.show_window(false);
					}			
#endif    
				}
				break;
			default:
				{
					//只有使用了软解才能显示视频窗口
					if ((page_index==page_qq_music||page_index==page_kugou_music||page_index==page_kuwo_music||page_index==page_baidu_music)&&(SCREEN_TYPE_VERTICAL==m_interface_type))
					{
						if (m_screen_show_window_exist && m_screen_show_window.IsWindowVisible())
						{
							m_screen_show_window.show_window(false);
						}
						if (m_lobby_live_window_exist && m_lobby_live_window.IsWindowVisible())
						{
							m_lobby_live_window.show_window(false);
						}
						if (m_tv_window_exist && m_tv_window.IsWindowVisible())
						{
							m_tv_window.show_window(false);
						}
						if (m_preview_window_exist && m_preview_window.IsWindowVisible())
						{
							m_preview_window.show_window(false);
						}
#ifdef SICHUAN_M
						if (m_screen_msquare_window_exist && m_screen_msquare_window.IsWindowVisible())
						{
							m_screen_msquare_window.show_window(false);
						}			
#endif    
					}
					else if (m_screen_show_window_exist && (VIDEO_TYPE_SONG==pc_play_video_type))
					{
						//显示主面板，就显示
						m_screen_show_window.MoveWindow(CRect(m_video_left_top_x,m_video_left_top_y,m_video_right_button_x,m_video_right_button_y));
						if (SCREEN_TYPE_VERTICAL==m_interface_type)
						{
							CRect window_rect;
							m_screen_show_window.GetClientRect(&window_rect);
							m_sub_screen_show_window.MoveWindow(window_rect);
						}
						m_player_manager.show_screen_video(true);
						
						//m_screen_show_window.show_window(true); 2014-04-09
#ifdef SLAVE_NO_PLAY_VIDEO
						if (2==m_master_slave_control_flag)
						{
							m_screen_show_window.show_window(false);
						}
						else
						{
							m_screen_show_window.show_window(m_song_show_video_picture);
						}
#else
						//2015-6-17 17:42:32---在歌曲页面显示小视频窗口
						if (m_song_show_video_picture && !m_show_screen_saver_state_activity)
						{
							m_screen_show_window.show_window(true);
						}
						else
						{
							m_screen_show_window.show_window(false);
						}
#endif

						m_player_manager.show_screen_video(true);
						//隐藏其他窗口，增加软件自我恢复功能
						m_lobby_live_window.show_window(false);
						m_tv_window.show_window(false);
						m_preview_window.show_window(false);
#ifdef SICHUAN_M
						m_screen_msquare_window.show_window(false);
#endif
					}
					else if (m_lobby_live_window_exist && (VIDEO_TYPE_LOBBY_LIVE==pc_play_video_type))
					{
						m_lobby_live_window.MoveWindow(CRect(m_video_left_top_x,m_video_left_top_y,m_video_right_button_x,m_video_right_button_y),TRUE);
						m_lobby_live_window.show_window(true);
						//隐藏其他窗口，增加软件自我恢复功能
						m_screen_show_window.show_window( false);
						m_tv_window.show_window(false);
						m_preview_window.show_window(false);
					}
					else if (m_tv_window_exist && (VIDEO_TYPE_TV==pc_play_video_type))
					{
						m_tv_window.MoveWindow(CRect(m_video_left_top_x,m_video_left_top_y,m_video_right_button_x,m_video_right_button_y),TRUE);
						m_tv_window.show_window(true);
						//隐藏其他窗口，增加软件自我恢复功能
						m_screen_show_window.show_window( false);
						m_lobby_live_window.show_window(false);
						m_preview_window.show_window(false);				
					}
					else if (m_preview_window_exist && (VIDEO_TYPE_PREVIEW_SONG==pc_play_video_type))
					{
						m_preview_window.MoveWindow(CRect(m_video_left_top_x,m_video_left_top_y,m_video_right_button_x,m_video_right_button_y),TRUE);
						m_preview_window.show_window(true);
						//隐藏其他窗口，增加软件自我恢复功能
						m_screen_show_window.show_window( false);
						m_lobby_live_window.show_window(false);
						m_tv_window.show_window(false);
					}
				}
			}
		}

#ifdef DON_GUAN_K_PLUS
		if (m_screen_show_window_exist && page_homepage==page_index && !m_creen_to_flash_show)
		{
			m_screen_show_window.MoveWindow(CRect(m_video_left_top_x,m_video_left_top_y,m_video_right_button_x,m_video_right_button_y));
			
			CRect window_rect;
			m_screen_show_window.GetClientRect(&window_rect);
			m_sub_screen_show_window.MoveWindow(window_rect);

			m_screen_show_window.show_window(true);
			m_player_manager.show_screen_video(true);
		}else{
			m_screen_show_window.show_window(false);
			m_player_manager.show_screen_video(false);
		}
#endif //DON_GUAN_K_PLUS

		//隐藏控制面板
		if (m_controlbar_flash_player_exist && m_controlbar_flash_player.IsWindowVisible())
		{
			m_controlbar_flash_player.ShowWindow(SW_HIDE);
		}
		//游戏窗口
		if (m_local_game_flash_player_exist)
		{
			m_local_game_flash_player.ShowWindow(SW_HIDE);
		}

		if (page_yule_news==page_index/*||page_index == page_drinks||page_index==page_consumer*/)
		{
			m_html_ctrl.ShowWindow(SW_SHOW);
			m_html_ctrl.UpdateWindow();
			m_show_html_ctrl = true;
		}

		//手写窗口
		if(m_handwriting_window_exist && m_show_handwriting_window)
		{
			m_handwriting_window.BringWindowToTop();
			m_handwriting_window.ShowWindow(SW_SHOW);
			m_handwriting_window.UpdateWindow();
		}

		if (m_show_screen_saver_state)
		{
			//发送屏保结束消息
			PostMessage(DM_SCREEN_SAVER_END,NULL,NULL);
		}

		if (!m_song_show_video_picture)
		{
			m_screen_show_window_exist = true;
		}		
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::hide_sub_window(void)
{
	try
	{
		if (m_screen_show_window_exist && m_screen_show_window.IsWindowVisible())
		{
			m_screen_show_window.show_window(false);
		}
		if (m_lobby_live_window_exist && m_lobby_live_window.IsWindowVisible())
		{
			m_lobby_live_window.show_window(false);
		}
		if (m_tv_window_exist && m_tv_window.IsWindowVisible())
		{
			m_tv_window.show_window(false);
		}
		if (m_preview_window_exist && m_preview_window.IsWindowVisible())
		{
			m_preview_window.show_window(false);
		}
		//隐藏控制面板
		if (m_controlbar_flash_player_exist && m_controlbar_flash_player.IsWindowVisible())
		{
			m_controlbar_flash_player.ShowWindow(SW_HIDE);
		}
		//游戏窗口
		if (m_local_game_flash_player_exist)
		{
			m_local_game_flash_player.ShowWindow(SW_HIDE);
		}
		//手写窗口
		if(m_handwriting_window_exist)
		{
			m_handwriting_window.ShowWindow(SW_HIDE);
			m_show_handwriting_window = false;
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::switch_screen_show_video_window(void)
{
	try
	{
		int page_index = m_flash_manage.get_last_page_index();

		//显示
		if (m_screen_show_window_exist && (VIDEO_TYPE_SONG==pc_play_video_type))
		{
			//显示主面板，就显示
			m_screen_show_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y));
			if (SCREEN_TYPE_VERTICAL==m_interface_type)
			{
				CRect window_rect;
				m_screen_show_window.GetClientRect(&window_rect);
				m_sub_screen_show_window.MoveWindow(window_rect);
			}
#ifdef SLAVE_NO_PLAY_VIDEO
			if (2==m_master_slave_control_flag)
			{
				m_screen_show_window.show_window(false);
			}
			else
			{
				m_screen_show_window.show_window(true);
			}
#else
			//2015-6-17 17:42:32---在ú歌è曲ú页?面?显?示?小?视酣?频μ窗洹?口ú
			//if (m_song_show_video_picture)
			if (!m_show_screen_saver_state_activity)
			{
				m_screen_show_window.show_window(true);
			}
#endif
			m_player_manager.show_screen_video(true);
			//隐藏其他窗口，增加软件自我恢复功能
			m_lobby_live_window.show_window(false);
			m_tv_window.show_window(false);
			m_preview_window.show_window(false);
#ifdef SICHUAN_M
			m_screen_msquare_window.show_window(false);
#endif
			
		}
		else if (m_lobby_live_window_exist && (VIDEO_TYPE_LOBBY_LIVE==pc_play_video_type))
		{
			m_lobby_live_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y),TRUE);
			m_lobby_live_window.show_window(true);
			//隐藏其他窗口，增加软件自我恢复功能
			m_screen_show_window.show_window(false);
			m_tv_window.show_window(false);
			m_preview_window.show_window(false);
		}
		else if (m_tv_window_exist && (VIDEO_TYPE_TV==pc_play_video_type))
		{
			/*
			m_tv_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y),TRUE);
			m_tv_window.show_window(true);
			//隐藏其他窗口，增加软件自我恢复功能
			m_screen_show_window.show_window( false);
			m_lobby_live_window.show_window(false);
			m_preview_window.show_window(false);*/

			m_tv_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y),TRUE);
			m_tv_window.show_window(true);
			m_player_manager.show_screen_video(true);
			//隐藏其他窗口，增加软件自我恢复功能
			m_screen_show_window.show_window( false);
			m_lobby_live_window.show_window(false);
			m_preview_window.show_window(false);
		}
		else if (m_preview_window_exist && (VIDEO_TYPE_PREVIEW_SONG==pc_play_video_type))
		{
			m_preview_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y),TRUE);
			m_preview_window.show_window(true);
			//隐藏其他窗口，增加软件自我恢复功能
			m_screen_show_window.show_window(false);
			m_lobby_live_window.show_window(false);
			m_tv_window.show_window(false);
		}

		//隐藏控制面板
		if (m_controlbar_flash_player_exist)
		{
			m_controlbar_flash_player.ShowWindow(SW_HIDE);
		}
		//游戏窗口
		if (m_local_game_flash_player_exist)
		{
			m_local_game_flash_player.ShowWindow(SW_HIDE);
		}

		//发送屏保结束消息
		PostMessage(DM_SCREEN_SAVER_END,NULL,NULL);
	}
	catch (...)
	{
	}
	return;
}

void Cflashktv10Wnd::ktv_open_room(void)
{
	try
	{
		
		int  player_state=0;
		bool have_selected_song=false;
		
		if (m_lock_window)
		{
			//如果是出现异常，锁定窗口，不能开房
			m_pc_state = CLOSE_ROOM_STATE;
			return;
		}
		//请求微信点歌数据
		config_file_manager config_file;
		config_file.write_string(L"ipad",L"wechat_song",L"");
		//启动线程 发送给盒子请求微信点歌数据
		thread_send_to_box_tcp_function(L"WECHATSONG",9999);
		//电影好评次数
		m_nFilePraiseCnt = config_file.read_integer(L"room", L"film_praise_count", 10);
		//百秒夺奖关卡重新计算
		int nSize = m_vec_pass.size();
		if (nSize > 0)
		{
			m_vec_pass[0].SetState(READY_ACROSS);
			for(int i=1; i<nSize; ++i)
			{
				m_vec_pass[i].SetState(UN_ACROSS);
			}
		}
//#ifdef DALIAN_MATSA_EK_PLUS
		//活动奖励是否已领取
		m_bCSGetAward = false;
		m_bAPGetAward = false;
		m_bLSGetAward = false;
//#endif
		//发送活动请求
		REQUEST_BOX_DATA *request_rule_data = new REQUEST_BOX_DATA;
		request_rule_data->pThis = this;
		_tcscpy(request_rule_data->request_data,L"RequestMaibaRule");
		AfxBeginThread(send_data_to_maiba_rule_thread,request_rule_data);
		
		//请求点歌挑战麦霸的规则
		//send_msg_to_set_maiba_rule(L"RequestMaibaRule");

		//生成二维码
		if (((0 == _tcscmp(m_ipad_login_code,L"")) || m_ipad_ecode_again) && m_use_mobile_vod)  //没有验证码和再次生成时
		{
			//生成验证二维码
			Generate_function_encode();
		}

		//设置为选歌状态
		m_pc_state = SELECT_SONG_STATE;

		//add 2012-09-26 FOR ZHEN
		send_room_state_to_ipad_server();

		//如果正在显示测机界面就要隐藏
		if (m_use_test_function && m_test_flash_player_exist && m_test_flash_player.IsWindowVisible())
		{
			m_test_flash_player.ShowWindow(SW_HIDE);
		}
		//清空录音表
		m_db_query.exec_sql(L"delete from song_recorder");
		//清空会员信息
		m_http_service.clear_user_info();
		//清空选择歌曲
		m_video_play_manager.clear_select_song(true);

		//从服务器上得到备份的已选歌曲
		if(m_save_selected_song_to_server && (0!=_tcscmp(m_save_song_file_path,L"")))
		{
			have_selected_song = get_select_song_from_server(m_save_song_file_path);
		}

		//得到播放器的状态
		player_state = m_player_manager.get_player_state();
		if (((PLAYER_STATE_PLAYING!=player_state)||have_selected_song)&&(2!=m_master_slave_control_flag))
		{
			//没有播放歌曲，开始播放
			flash_message_call_function(SONG_NEXT);
		}
		
		//更新选择歌曲的数目
		update_select_song_count();

		//开房时主动请求活动信息
		TCHAR data[256] = {0x00};
		swprintf(data, L"REQUESTMAIBARULEINFO");
		REQUEST_BOX_DATA *request_box_data = new REQUEST_BOX_DATA;
		_tcscpy(request_box_data->request_data, data);
		request_box_data->nPort = 6666;
		request_box_data->pThis = this;
		AfxBeginThread(send_server_msg_tcp_thread,request_box_data);
	}
	catch (...)
	{
		
	}
}

void Cflashktv10Wnd::send_test_song_info(void)
{
	try
	{
		TCHAR data[1024];
		TCHAR request[1024];
		TCHAR cur_song_name[128];
		TCHAR next_song_name[128];
		int music_volume=0;
		int microphone_volume=0;
		int tune=0;
		bool result=false;

		memset(data,0x0,sizeof(data));
		memset(request,0x0,sizeof(request));
		memset(cur_song_name,0x0,sizeof(cur_song_name));
		memset(next_song_name,0x0,sizeof(next_song_name));

		m_video_play_manager.get_test_song_name(cur_song_name,next_song_name);
		m_player_manager.get_volume_tune(music_volume,microphone_volume,tune);
		swprintf(data,L"<data><info cur=\"%s\" next=\"%s\"/><id txt=\"\"/><sound mic=\"%d\" music=\"%d\" mute=\"%d\"/></data>",cur_song_name,next_song_name,microphone_volume,music_volume,tune);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"txtInfo",data);
		if (result)
		{
			m_test_flash_player.CallFunction(request);
		}
	}
	catch (...) {
	}
	return;
}

void Cflashktv10Wnd::flash_message_call_save_test_song(void)
{
	try
	{
		song_info test_song_info;
		bool result = false;
		TCHAR song_number[256];

		for (int i=0;i<TEST_PAGE_SHOW_ROW_COUNT;i++)
		{
			memset(song_number,0x0,sizeof(song_number));

			result = m_query_song_manager.get_test_or_select_song_info(i,test_song_info,true);
			if (!result)
			{
				break;
			}
			result = test_song_info.get_song_id(song_number);
			if (result && (0!=_tcscmp(song_number,L"")))
			{
				m_video_play_manager.add_select_song(test_song_info,false);
			}
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::auto_test_software(void)
{
	try
	{
		static int repeat_number=0;
		TCHAR data[1024];
		TCHAR request[1024];
		bool result=false;

		memset(data,0x0,sizeof(data));
		memset(request,0x0,sizeof(request));

		switch(m_auto_test_number)
		{
		case 1:  //麦克风减
			{
				flash_message_call_function(MICROPHONE_VOLUME_DOWN);
				flash_message_call_function(MICROPHONE_VOLUME_DOWN);
				repeat_number++;
				if (repeat_number>=3)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 2:  //麦克风加
			{
				flash_message_call_function(MICROPHONE_VOLUME_UP);
				flash_message_call_function(MICROPHONE_VOLUME_UP);
				repeat_number++;
				if (repeat_number>=3)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 3:  //音乐减
			{
				flash_message_call_function(MUSIC_VOLUME_DOWN);
				flash_message_call_function(MUSIC_VOLUME_DOWN);
				repeat_number++;
				if (repeat_number>=3)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 4:  //音乐加
			{
				flash_message_call_function(MUSIC_VOLUME_UP);
				flash_message_call_function(MUSIC_VOLUME_UP);
				repeat_number++;
				if (repeat_number>=3)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 5:  //音调减
			{
				flash_message_call_function(TUNE_DOWN);
				flash_message_call_function(TUNE_DOWN);
				repeat_number++;
				if (repeat_number>=2)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 6:  //音调加
			{
				flash_message_call_function(TUNE_UP);
				flash_message_call_function(TUNE_UP);
				repeat_number++;
				if (repeat_number>=2)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 7:  //原调
			{
				flash_message_call_function(TUNE_ORIGINAL);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 8:  //掌声
			{
				flash_message_call_function(ATMOSPHERE_APPLAUSE);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 9:  //欢呼声
			{
				flash_message_call_function(ATMOSPHERE_CHEER);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 10:  //催眠
			{
				flash_message_call_function(ATMOSPHERE_OUTCRY);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 11:  //狂汗
			{
				flash_message_call_function(ATMOSPHERE_WHISTLE);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;

		case 12:  //标准
			{
				flash_message_call_function(AUDIO_EFFECT_STANDARD);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 13:  //剧场
			{
				flash_message_call_function(AUDIO_EFFECT_THEATER);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 14:  //唱将
			{
				flash_message_call_function(AUDIO_EFFECT_PROFESSIONAL);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 15:  //魔音
			{
				flash_message_call_function(AUDIO_EFFECT_MAGIC);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 16://原伴唱
			{
				flash_message_call_function(SONG_ACCOMPANY_ORIGINAL);
				repeat_number++;
				if (repeat_number>=3)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 17:  //播放暂停
			{
				flash_message_call_function(SONG_PLAY_PAUSE);
				repeat_number++;
				if (repeat_number>=2)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 18:  //重播
			{
				if (0==repeat_number)
				{
					flash_message_call_function(SONG_REPLAY);
				}
				repeat_number++;
				if (repeat_number>=3)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 19:  //切歌曲
			{
				if (0==repeat_number%2)
				{
					WriteLog(__FL__, L"测机播放下一首");
					flash_message_call_function(SONG_NEXT);
				}
				repeat_number++;
				if (repeat_number>=4)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 20: //静音
			{
				flash_message_call_function(SONG_MUTE_UNMUTE);
				repeat_number++;
				if (repeat_number>=2)
				{
					swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
					repeat_number=0;
					m_auto_test_number++;
				}
			}
			break;
		case 21:  //灯光标准
			{
				flash_message_call_function(LIGHT_STANDARD);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 22:  //灯光背景
			{
				flash_message_call_function(LIGHT_BACKGROUND);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 23:  //灯光舞台
			{
				flash_message_call_function(LIGHT_STAGE);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 24:  //灯光屏闪
			{
				flash_message_call_function(LIGHT_SCINTILLATION);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 25:  //关闭灯光
			{
				flash_message_call_function(LIGHT_CLOSE);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 26:  //会议中
			{
				flash_message_call_function(ENVIRONMENT_AUDIO_MEETING);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 27:  //飞机场
			{
				flash_message_call_function(ENVIRONMENT_AUDIO_AIRPORT);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 28:  //马路上
			{
				flash_message_call_function(ENVIRONMENT_AUDIO_ROAD);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 29:  //火车站
			{
				flash_message_call_function(ENVIRONMENT_AUDIO_STATION);
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		case 30:  //关闭环境音
			{
				//打开环境音
				flash_message_call_function(ENVIRONMENT_AUDIO_CLOSE);
				Sleep(1000);
				//关闭环境音
				flash_message_call(L"environment_audio",L"0");
				swprintf(data,L"<data><item id=\"%d\" result=\"1\"/></data>",m_auto_test_number);
				m_auto_test_number++;
			}
			break;
		default:
			{
				//最后杀死该定时器
				KillTimer(auto_test_timer_identifier);
				auto_test_timer_identifier=0;
				m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"tooltip",L"自动测机完成");
				m_test_flash_player.CallFunction(request);
			}
			break;
		}

		//显示测试结果
		if (0!=_tcscmp(data,L""))
		{
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"showResult",data);
			if (result)
			{
				m_test_flash_player.CallFunction(request);
			}
		}
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::flash_message_call_save_test_result(const TCHAR *args)
{
	try
	{
		config_file_manager config_file;
		TCHAR test_result[1024];
		bool result=false;
		int temp_result[30];

		memset(test_result,0x0,sizeof(test_result));
		memset(temp_result,0x0,sizeof(temp_result));

		config_file.init(L"test_result.ini");

		_tcscpy(test_result,args);

		swscanf(test_result,L"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",  \
			&temp_result[0],&temp_result[1],&temp_result[2],&temp_result[3],&temp_result[4],&temp_result[5],&temp_result[6],&temp_result[7],&temp_result[8],  \
			&temp_result[9],&temp_result[10],&temp_result[11],&temp_result[12],&temp_result[13],&temp_result[14],&temp_result[15],&temp_result[16],&temp_result[17],  \
			&temp_result[18],&temp_result[19],&temp_result[20],&temp_result[21],&temp_result[22],&temp_result[23],&temp_result[24],&temp_result[25],&temp_result[26],  \
			&temp_result[27],&temp_result[28],&temp_result[29]);

		//按照配置文件的方式输出
		if (1==temp_result[0])
		{
			config_file.write_string(L"测机结果",L"麦克-",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"麦克-",L"异常");
		}
		if (1==temp_result[1])
		{
			config_file.write_string(L"测机结果",L"麦克+",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"麦克+",L"异常");
		}
		if (1==temp_result[2])
		{
			config_file.write_string(L"测机结果",L"音乐-",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"音乐-",L"异常");
		}
		if (1==temp_result[3])
		{
			config_file.write_string(L"测机结果",L"音乐+",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"音乐+",L"异常");
		}
		if (1==temp_result[4])
		{
			config_file.write_string(L"测机结果",L"音调-",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"音调-",L"异常");
		}
		if (1==temp_result[5])
		{
			config_file.write_string(L"测机结果",L"音调+",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"音调+",L"异常");
		}
		if (1==temp_result[6])
		{
			config_file.write_string(L"测机结果",L"原调",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"原调",L"异常");
		}
		if (1==temp_result[7])
		{
			config_file.write_string(L"测机结果",L"掌声",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"掌声",L"异常");
		}
		if (1==temp_result[8])
		{
			config_file.write_string(L"测机结果",L"欢呼",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"欢呼",L"异常");
		}
		if (1==temp_result[9])
		{
			config_file.write_string(L"测机结果",L"催眠",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"催眠",L"异常");
		}
		if (1==temp_result[10])
		{
			config_file.write_string(L"测机结果",L"狂汗",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"狂汗",L"异常");
		}
		if (1==temp_result[11])
		{
			config_file.write_string(L"测机结果",L"音效标准",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"音效标准",L"异常");
		}
		if (1==temp_result[12])
		{
			config_file.write_string(L"测机结果",L"音效剧场",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"音效剧场",L"异常");
		}
		if (1==temp_result[13])
		{
			config_file.write_string(L"测机结果",L"音效唱将",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"音效唱将",L"异常");
		}
		if (1==temp_result[14])
		{
			config_file.write_string(L"测机结果",L"音效魔音",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"音效魔音",L"异常");
		}
		if (1==temp_result[15])
		{
			config_file.write_string(L"测机结果",L"原唱/伴唱",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"原唱/伴唱",L"异常");
		}
		if (1==temp_result[16])
		{
			config_file.write_string(L"测机结果",L"播放/暂停",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"播放/暂停",L"异常");
		}
		if (1==temp_result[17])
		{
			config_file.write_string(L"测机结果",L"重播",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"重播",L"异常");
		}
		if (1==temp_result[18])
		{
			config_file.write_string(L"测机结果",L"切歌",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"切歌",L"异常");
		}
		if (1==temp_result[19])
		{
			config_file.write_string(L"测机结果",L"静音",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"静音",L"异常");
		}

		if (1==temp_result[20])
		{
			config_file.write_string(L"测机结果",L"灯光标准",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"灯光标准",L"异常");
		}
		if (1==temp_result[21])
		{
			config_file.write_string(L"测机结果",L"灯光背景",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"灯光背景",L"异常");
		}
		if (1==temp_result[22])
		{
			config_file.write_string(L"测机结果",L"灯光舞台",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"灯光舞台",L"异常");
		}
		if (1==temp_result[23])
		{
			config_file.write_string(L"测机结果",L"灯光屏闪",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"灯光屏闪",L"异常");
		}
		if (1==temp_result[24])
		{
			config_file.write_string(L"测机结果",L"关闭灯光",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"关闭灯光",L"异常");
		}
		if (1==temp_result[25])
		{
			config_file.write_string(L"测机结果",L"会议中",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"会议中",L"异常");
		}
		if (1==temp_result[26])
		{
			config_file.write_string(L"测机结果",L"飞机场",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"飞机场",L"异常");
		}
		if (1==temp_result[27])
		{
			config_file.write_string(L"测机结果",L"马路上",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"马路上",L"异常");
		}
		if (1==temp_result[28])
		{
			config_file.write_string(L"测机结果",L"火车站",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"火车站",L"异常");
		}
		if (1==temp_result[29])
		{
			config_file.write_string(L"测机结果",L"关闭环境音",L"正常");
		}
		else
		{
			config_file.write_string(L"测机结果",L"关闭环境音",L"异常");
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::play_environment_audio(int audio_number,bool show_logo)
{
	try
	{
		TCHAR audio_path[256];
		bool result=false;
		TCHAR send_data[256];

		memset(send_data,0x0,sizeof(send_data));
		memset(audio_path,0x0,sizeof(audio_path));

		switch(audio_number)
		{
		case FLASH_SEND_ENVIRONMENT_AUDIO_MEETING:
			{
				result = m_video_play_manager.get_environment_wave_info(audio_number,audio_path);
				if (result)
				{
					m_player_manager.play_wave_mixer_audio(audio_path,1,0);
				}
				if (show_logo)
				{
					//显示控制osd
					result = show_control_osd(CONTROL_OSD_ENVIRONMENT_AUDIO_MEETING);
					//启动定时器5秒之后，停止播放该控制osd
					set_control_osd_show_timer();
				}
				m_select_environment_button_number=2;
			}
			break;
		case FLASH_SEND_ENVIRONMENT_AUDIO_AIRPORT:
			{
				result = m_video_play_manager.get_environment_wave_info(audio_number,audio_path);
				if (result)
				{
					m_player_manager.play_wave_mixer_audio(audio_path,1,0);
				}
				if (show_logo)
				{
					//显示控制osd
					result = show_control_osd(CONTROL_OSD_ENVIRONMENT_AUDIO_AIRPORT);
					//启动定时器5秒之后，停止播放该控制osd
					set_control_osd_show_timer();
				}
				m_select_environment_button_number=0;
			}
			break;
		case FLASH_SEND_ENVIRONMENT_AUDIO_ROAD:
			{
				result = m_video_play_manager.get_environment_wave_info(audio_number,audio_path);
				if (result)
				{
					m_player_manager.play_wave_mixer_audio(audio_path,1,0);
				}
				if (show_logo)
				{
					//显示控制osd
					result = show_control_osd(CONTROL_OSD_ENVIRONMENT_AUDIO_ROAD);
					//启动定时器5秒之后，停止播放该控制osd
					set_control_osd_show_timer();
				}
				m_select_environment_button_number=3;
			}
			break;
		case FLASH_SEND_ENVIRONMENT_AUDIO_STATION:
			{
				result = m_video_play_manager.get_environment_wave_info(audio_number,audio_path);
				if (result)
				{
					m_player_manager.play_wave_mixer_audio(audio_path,1,0);
				}
				if (show_logo)
				{
					//显示控制osd
					result = show_control_osd(CONTROL_OSD_ENVIRONMENT_AUDIO_STATION);
					//启动定时器5秒之后，停止播放该控制osd
					set_control_osd_show_timer();
				}
				m_select_environment_button_number=6;
			}
			break;
		case FLASH_SEND_ENVIRONMENT_AUDIO_MAHJONG:
			{
				result = m_video_play_manager.get_environment_wave_info(audio_number,audio_path);
				if (result)
				{
					m_player_manager.play_wave_mixer_audio(audio_path,1,0);
				}
				if (show_logo)
				{
					//显示控制osd
					result = show_control_osd(CONTROL_OSD_ENVIRONMENT_AUDIO_MAHJONG);
					//启动定时器5秒之后，停止播放该控制osd
					set_control_osd_show_timer();
				}
				m_select_environment_button_number=1;
			}
			break;
		case FLASH_SEND_ENVIRONMENT_AUDIO_RAIN:
			{
				result = m_video_play_manager.get_environment_wave_info(audio_number,audio_path);
				if (result)
				{
					m_player_manager.play_wave_mixer_audio(audio_path,1,0);
				}
				if (show_logo)
				{
					//显示控制osd
					result = show_control_osd(CONTROL_OSD_ENVIRONMENT_AUDIO_RAIN);
					//启动定时器5秒之后，停止播放该控制osd
					set_control_osd_show_timer();
				}
				m_select_environment_button_number=4;
			}
			break;
		case FLASH_SEND_ENVIRONMENT_AUDIO_CLOSE:
		default:
			{
				m_player_manager.stop_wave_mixer_audio();
				if (show_logo)
				{
					//显示控制osd
					result = show_control_osd(CONTROL_OSD_LIGHT_CLOSE);
					//启动定时器5秒之后，停止播放该控制osd
					set_control_osd_show_timer();
				}
				m_select_environment_button_number=5;
			}
			break;
		}

		//设置环境音的按钮状态
		send_environment_audio_button_state();
		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::send_accompany_original_button_state(void)
{
	try
	{
		TCHAR request[256];
		TCHAR data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		if (1 == m_select_song_accompany_original || 3 == m_select_song_accompany_original || -1 == m_select_song_accompany_original)
		{
			
			if (m_player_manager.get_channel())
			{
				//原唱
				m_select_song_accompany_original = 3; //原唱
			}
			else
			{
				//伴唱
				m_select_song_accompany_original = 1; //原版伴奏
			}
		}

		swprintf(data,L"%d",m_select_song_accompany_original);
	 
		//改变环境音效按钮高亮状态
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"accompany_original_button",data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	} 

	return;
}

void Cflashktv10Wnd::send_environment_audio_button_state(void)
{
	try
	{
		TCHAR request[256];
		TCHAR data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		swprintf(data,L"%d",m_select_environment_button_number);

		//改变环境音效按钮高亮状态
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"environment_audio_button",data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::change_room_light(int light_number,bool recv_msg)
{
	try
	{
		bool result=false;
		TCHAR send_data[256];
		
		memset(send_data,0x0,sizeof(send_data));
		memset(m_select_ligth_buttom,0x0,sizeof(m_select_ligth_buttom));
		m_inherit_com.set_light_value(true);
		m_inherit_three_com.set_light_value(true);
#ifdef VICE_SCREEN_GUANGXI
		if (_tcscmp(m_GxShine_dll[0], L"") != 0)
		{
			//广西视翰灯光插件 - 关闭
			if(!m_PluginsEx.OnClickEx(m_GxShine_dll[0], false))
			{
				WriteLog(__FL__, L"设置灯管接口关闭失败!");
			}
		}
#endif // VICE_SCREEN_GUANGXI	
		//取消自动高亮yzg
		m_song_light_lock = true;
						
		switch(light_number)
		{
		case FLASH_SEND_LIGHT1:              //灯光1
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT1, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT1);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 0;
#else
					m_song_light_lock_value = 6;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"6");
			}
			break;
		case FLASH_SEND_LIGHT2:              //灯光2
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT2, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT2);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 1;
#else
					m_song_light_lock_value = 7;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"7");
			}
			break;
		case FLASH_SEND_LIGHT3:              //灯光3
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT3, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT3);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 2;
#else
					m_song_light_lock_value = 8;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"8");
			}
			break;
		case FLASH_SEND_LIGHT4:              //灯光4
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT4, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT4);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 3;
#else
					m_song_light_lock_value = 9;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"9");
			}
			break;
		case FLASH_SEND_LIGHT5:              //灯光5
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT5, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT5);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 4;
#else
					m_song_light_lock_value = 10;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"10");
			}
			break;
		case FLASH_SEND_LIGHT6:              //灯光6
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT6, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT6);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 5;
#else
					m_song_light_lock_value = 11;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"11");
			}
			break;
		case FLASH_SEND_LIGHT7:              //灯光6
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT7, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT7);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 6;
#else
					m_song_light_lock_value = 12;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"12");
			}
			break;
		case FLASH_SEND_LIGHT8:              //灯光6
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT8, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT8);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 7;
#else
					m_song_light_lock_value = 13;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"13");
			}
			break;
		case FLASH_SEND_LIGHT_STANDARD:      //灯光标准
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT_STANDARD, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT_STANDARD);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 8;
#else
					m_song_light_lock_value = 2;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"2");
			}
			break;
		case FLASH_SEND_LIGHT_BACKGROUND:     //灯光 背景
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT_BACKGROUND, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT__BACKGROUND);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 9;
#else
					m_song_light_lock_value = 3;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"3");
			}
			break;
		case FLASH_SEND_LIGHT_STAGE:          //灯光 舞台
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT_STAGE, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT__STAGE);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 10;
#else
					m_song_light_lock_value = 4;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"4");
			}
			break;
		case FLASH_SEND_LIGHT_SCINTILLATION:  //灯光 屏闪
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT_SCINTILLATION, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT__SCINTILLATION);

#ifdef VICE_SCREEN_GUANGXI
				if (_tcscmp(m_GxShine_dll[0], L"") != 0)
				{
					//广西视翰灯光调用 - 动感才开启
					if(!m_PluginsEx.OnClickEx(m_GxShine_dll[0], true))
					{
						WriteLog(__FL__, L"设置灯管接口关闭失败!");
					}
				}
#endif // VICE_SCREEN_GUANGXI

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 11;
#else
					m_song_light_lock_value = 5;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"5");
			}
			break;
		case FLASH_SEND_LIGHT_OPEN:           //灯光 全开
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT_OPEN, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT_OPEN);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 12;
#else
					m_song_light_lock_value = 1;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"1");
			}
			break;
		case FLASH_SEND_LIGHT_CLOSE:          //灯光 关闭
			{
				if (m_recv_no_send_light_code&&recv_msg)
				{
					//接受的不发送
				}
				else
				{
					write_com_data(COM_SEND_LIGHT_CLOSE, 0 , true, light_number);
				}
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_LIGHT_CLOSE);

				//高亮的灯光按钮
				if (m_song_light_lock)
				{
#ifdef DON_GUAN_K_PLUS
					m_song_light_lock_value = 13;
#else
					m_song_light_lock_value = 0;
#endif // DON_GUAN_K_PLUS
				}

				//高亮的灯光按钮
				_tcscpy(m_select_ligth_buttom,L"0");
			}
			break;
		default:
			return;
		}
		//启动定时器5秒之后，停止播放该控制osd
		set_control_osd_show_timer();
		//设置灯光高亮按钮状态
		send_light_button_state();

		return;
		
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::send_light_button_state(void)
{
	try
	{
		TCHAR request[256];
		bool result=false;
		TCHAR data[256];

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		if (!m_memory_light_state)
		{
			//不记忆
			return;
		}
#ifdef DON_GUAN_K_PLUS
		swprintf(data,L"<data><info light=\"%s\" lock=\"%d\" /></data>",m_select_ligth_buttom,m_song_light_lock_value);

		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"light_button",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		if (result)
		{
			//flash_player_call_function(request);

			if (m_controlbar_flash_player_exist && m_show_screen_saver_state && m_controlbar_flash_player.IsWindowVisible())
			{
				//控制条显示状态，也要更新
				m_controlbar_flash_player.CallFunction(request);
			}
			if (m_slave_parent_window_exist&&m_slave_window_flash_player_exist&&m_slave_window_flash_player.IsWindowVisible())
			{
				//演唱台显示状态，也要更新
				m_slave_window_flash_player.CallFunction(request);
			}
		}
#else
		//改变灯光按钮高亮状态
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"light_button",m_select_ligth_buttom);
		if (result)
		{
			flash_player_call_function(request);

			if (!m_song_light_lock)
			{
				result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"light_auto_button", L"1");
			}else{
				result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"light_auto_button", L"0");
			}
			flash_player_call_function(request);

			if (m_controlbar_flash_player_exist && m_show_screen_saver_state && m_controlbar_flash_player.IsWindowVisible())
			{
				//控制条显示状态，也要更新
				m_controlbar_flash_player.CallFunction(request);
			}
			if (m_slave_parent_window_exist&&m_slave_window_flash_player_exist&&m_slave_window_flash_player.IsWindowVisible())
			{
				//演唱台显示状态，也要更新
				m_slave_window_flash_player.CallFunction(request);
			}
		}
#endif //DON_GUAN_K_PLUS
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::change_air_condition_function(int air_condition)
{
	try
	{
		bool result=false;

		switch(air_condition)
		{
		case AIR_CONDITION_STRONG:       //空调强
			{
				write_com_data(COM_SEND_AIR_CONDITION_STRONG);
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_AIR_CONDITION_STRONG);
			}
			break;
		case AIR_CONDITION_MID:          //空调中
			{
				write_com_data(COM_SEND_AIR_CONDITION_MID);
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_AIR_CONDITION_MID);
			}
			break;
		case AIR_CONDITION_WEAK:         //空调弱
			{
				write_com_data(COM_SEND_AIR_CONDITION_WEAK);
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_AIR_CONDITION_WEAK);
			}
			break;
		case AIR_CONDITION_CLOSE:        //空调关闭
			{
				write_com_data(COM_SEND_AIR_CONDITION_CLOSE);
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_AIR_CONDITION_CLOSE);
			}
			break;
		case DISCHARGE_AIR_FUNCTION:     //排风
			{
				write_com_data(COM_SEND_DISCHARGE_AIR_FUNCTION);
				//显示控制osd
				result = show_control_osd(CONTROL_OSD_DISCHARGE_AIR_FUNCTION);
			}
			break;
		}

		//启动定时器5秒之后，停止播放该控制osd
		set_control_osd_show_timer();

		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::change_music_sound(int music_sound)
{
	try
	{
		bool result=false;

		switch(music_sound)
		{
		case MUSIC_SOUND_STANDARD:  //标准
			{
				result = write_com_data(COM_SEND_MUSIC_SOUND_STANDARD);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_MUSIC_SOUND_STANDARD);
				//高亮的按钮
				m_cur_music_sound_value=0;
			}
			break;
		case MUSIC_SOUND_THEATER:  //剧场
			{
				result = write_com_data(COM_SEND_MUSIC_SOUND_THEATER);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_MUSIC_SOUND_THEATER);
				//高亮的按钮
				m_cur_music_sound_value=1;
			}
			break;
		case MUSIC_SOUND_PROFESSIONAL:  //唱将
			{
				result = write_com_data(COM_SEND_MUSIC_SOUND_PROFESSIONAL);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_MUSIC_SOUND_PROFESSIONAL);
				//高亮的按钮
				m_cur_music_sound_value=2;
			}
			break;
		case MUSIC_SOUND_MAGIC:  //魔音
			{
				result = write_com_data(COM_SEND_MUSIC_SOUND_MAGIC);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_MUSIC_SOUND_MAGIC);
				//高亮的按钮
				m_cur_music_sound_value=3;
			}
			break;
		case MUSIC_SOUND_RESERVE1:  //预留
			{
				result = write_com_data(COM_SEND_MUSIC_SOUND_RESERVE1);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_MUSIC_SOUND_RESERVE1);
				//高亮的按钮
				m_cur_music_sound_value=4;
			}
			break;
		case MUSIC_SOUND_RESERVE2:  //预留
			{
				result = write_com_data(COM_SEND_MUSIC_SOUND_RESERVE2);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_MUSIC_SOUND_MAGIC);
				//高亮的按钮
				m_cur_music_sound_value=5;
			}
			break;
		case MUSIC_SOUND_RESERVE3:  //预留
			{
				result = write_com_data(COM_SEND_MUSIC_SOUND_RESERVE3);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_MUSIC_SOUND_MAGIC);
				//高亮的按钮
				m_cur_music_sound_value=6;
			}
			break;
		case MUSIC_SOUND_RESERVE4:  //预留
			{
				result = write_com_data(COM_SEND_MUSIC_SOUND_RESERVE4);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_MUSIC_SOUND_MAGIC);
				//高亮的按钮
				m_cur_music_sound_value=7;
			}
			break;
		default:
			return;
		}
		//启动控制osd播放时间的定时器
		set_control_osd_show_timer();
		//设置音效按钮的高亮状态
		send_music_sound_button_state();

		return;		
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::change_audio_effect(int audio_effect)
{
	try
	{
		bool result=false;


		switch(audio_effect)
		{
		case AUDIO_EFFECT_STANDARD:  //标准
			{
				result = write_com_data(COM_SEND_AUDIO_EFFECT_STANDARD);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_AUDIO_EFFECT_STANDARD);
				//高亮的按钮
				m_cur_audio_effect_value=0;
				if (m_lock_function_code_value == audio_effect)
				{
					m_lock_audio_effect_value = m_cur_audio_effect_value;
				}
			}
			break;
		case AUDIO_EFFECT_THEATER:  //剧场
			{
				result = write_com_data(COM_SEND_AUDIO_EFFECT_THEATER);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_AUDIO_EFFECT_THEATER);
				//高亮的按钮
				m_cur_audio_effect_value=1;
				if (m_lock_function_code_value == audio_effect)
				{
					m_lock_audio_effect_value = m_cur_audio_effect_value;
				}
			}
			break;
		case AUDIO_EFFECT_PROFESSIONAL:  //唱将
			{
				result = write_com_data(COM_SEND_AUDIO_EFFECT_PROFESSIONAL);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_AUDIO_EFFECT_PROFESSIONAL);
				//高亮的按钮
				m_cur_audio_effect_value=2;
				if (m_lock_function_code_value == audio_effect)
				{
					m_lock_audio_effect_value = m_cur_audio_effect_value;
				}
			}
			break;
		case AUDIO_EFFECT_MAGIC:  //魔音
			{
				result = write_com_data(COM_SEND_AUDIO_EFFECT_MAGIC);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_AUDIO_EFFECT_MAGIC);
				//高亮的按钮
				m_cur_audio_effect_value=3;
				if (m_lock_function_code_value == audio_effect)
				{
					m_lock_audio_effect_value = m_cur_audio_effect_value;
				}
			}
			break;
		case AUDIO_EFFECT_RESERVE1:  //预留
			{
				result = write_com_data(COM_SEND_AUDIO_EFFECT_RESERVE1);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_AUDIO_EFFECT);
				//高亮的按钮
				m_cur_audio_effect_value=4;
				if (m_lock_function_code_value == audio_effect)
				{
					m_lock_audio_effect_value = m_cur_audio_effect_value;
				}
			}
			break;
		case AUDIO_EFFECT_RESERVE2:  //预留
			{
				result = write_com_data(COM_SEND_AUDIO_EFFECT_RESERVE2);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_AUDIO_EFFECT_RESERVE2);
				//高亮的按钮
				m_cur_audio_effect_value=5;
				if (m_lock_function_code_value == audio_effect)
				{
					m_lock_audio_effect_value = m_cur_audio_effect_value;
				}
			}
			break;
		case AUDIO_EFFECT_RESERVE3:  //预留
			{
				result = write_com_data(COM_SEND_AUDIO_EFFECT_RESERVE3);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_AUDIO_EFFECT_RESERVE3);
				//高亮的按钮
				m_cur_audio_effect_value=6;
				if (m_lock_function_code_value == audio_effect)
				{
					m_lock_audio_effect_value = m_cur_audio_effect_value;
				}
			}
			break;
		case AUDIO_EFFECT_RESERVE4:  //预留
			{
				result = write_com_data(COM_SEND_AUDIO_EFFECT_RESERVE4);
				if (!result)
				{
					//发送失败
				}
				//显示服务控制osd
				result = show_control_osd(CONTROL_OSD_AUDIO_EFFECT_RESERVE4);
				//高亮的按钮
				m_cur_audio_effect_value=7;

			}
			break;
		default:
			return;
		}
		//启动控制osd播放时间的定时器
		set_control_osd_show_timer();
		//设置音效按钮的高亮状态
		send_audio_effect_button_state();

		return;		
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::send_music_sound_button_state(void)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		swprintf(data,L"%d",m_cur_music_sound_value);

		//是选中的按钮高亮
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"music_sound_button",data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::send_audio_effect_button_state(void)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

#ifdef DON_GUAN_K_PLUS
		swprintf(data,L"<data><info light=\"%d\" lock=\"%d\" /></data>",m_cur_audio_effect_value,m_lock_audio_effect_value);
#else
		swprintf(data,L"%d",m_cur_audio_effect_value);
#endif // DON_GUAN_K_PLUS		

		//是选中的按钮高亮
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"audio_effect_button",data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::play_atmosphere_audio(int wave_type)
{
	try
	{
		TCHAR wave_path[256];
		TCHAR picture_path[256];
		bool result=false;

		memset(wave_path,0x0,sizeof(wave_path));
		memset(picture_path,0x0,sizeof(picture_path));

		//得到气氛音频和图片路径
		result = m_video_play_manager.get_atmosphere_wave_info(wave_type,wave_path,picture_path,m_soft_decode_window_exist);
		if (!result)
		{
			return;
		}
		//播放音频
		if (m_soft_decode_window_exist)
		{
#ifdef LOOP_PLAY_BG_SONG
			//循环播放背景声音的时候，必须用控件播放
			m_player_manager.play_wave_mixer_audio(wave_path,0,1);
#else
			//软解，直接播放，没有延迟
			PlaySound(wave_path, NULL, SND_FILENAME|SND_NOWAIT|SND_ASYNC);
#endif
		}
		else
		{
			//硬解码，必须有控件播放
			m_player_manager.play_wave_mixer_audio(wave_path,0,1);
		}
		if ((0!=_tcscmp(picture_path,L""))&&PathFileExists(picture_path))
		{
			//显示图片
			//2012-10-24  屏保播放图片
			show_picture_on_tv(picture_path,OSDAlignmentCenter,6000,false,false);
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::stop_environment_audio(void)
{
	try
	{
		//播放音频
		if (m_soft_decode_window_exist)
		{
#ifdef LOOP_PLAY_BG_SONG
			//循环播放背景声音的时候，必须用控件播放
			m_player_manager.stop_wave_mixer_audio();
#else
			//软解，直接播放，没有延迟
			PlaySound(NULL, NULL, SND_FILENAME|SND_NOWAIT|SND_ASYNC);
#endif
		}
		else
		{
			//硬解码，必须有控件播放
			m_player_manager.stop_wave_mixer_audio();
		}
	}
	catch (...)
	{

	}

	return;
}

bool Cflashktv10Wnd::parse_coordinate_string(const TCHAR *coordinate,int &x,int &y,int &width,int &height)
{
	try
	{
		if (NULL==coordinate)
		{
			return false;
		}
		float x_position=0.0;
		float y_position=0.0;
		float window_width=0.0;
		float window_height=0.0;

		//解析出来坐标位置和宽高
		swscanf(coordinate,L"%f;%f;%f;%f",&x_position,&y_position,&window_width,&window_height);
		//转成整形
		x = (int)x_position;
		y = (int)y_position;
		width = (int)window_width;
		height = (int)window_height;

		return true;
		//自适应分辨率
		if (SCREEN_TYPE_VERTICAL==m_interface_type)
		{
			//竖版
			x = x*m_first_display_width/1080;
			y = y*m_first_display_height/1920;
			width = width*m_first_display_width/1080;
			height = height*m_first_display_height/1920;
		}
		else
		{
			//横版
			x = x*m_first_display_width/1920;
			y = y*m_first_display_height/1080;
			width = width*m_first_display_width/1920;
			height = height*m_first_display_height/1080;
		}
		
		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::flash_message_call_query_board_change(const TCHAR *args)
{
	try
	{
		int page_index = 0;
		page_index = m_flash_manage.get_last_page_index();

		if (m_handwriting_window_exist && (0==_tcscmp(args,L"handwriting_show")))
		{
			m_handwriting_window.BringWindowToTop();
			m_handwriting_window.ShowWindow(SW_SHOW);
			m_handwriting_window.UpdateWindow();
			m_show_handwriting_window = true;
			//默认中文识别  2011-11-29 modify
			flash_message_call_change_handwriting_language(L"1");
			//m_ink_language_button_number=0;
			//设置手写识别语言的按钮状态
			//send_ink_language_button_state();
			flash_message_call_surver_tip_message(L"6");
			show_handwrite_select_result();
		}
		else if (m_handwriting_window_exist && (0==_tcscmp(args,L"handwriting_hide")))
		{
			m_handwriting_window.ShowWindow(SW_HIDE);
			m_show_handwriting_window = false;
			set_button_highlight_state(false);
			flash_message_call_surver_tip_message(L"7");
			if (page_index == page_write)
			{
				show_handwrite_select_result();
			}
			else
			{
				show_pinyin_select_result();
			}
			
		}
		else if (0==_tcscmp(args,L"pinyin_show"))
		{
			show_pinyin_select_result();
		}
		else if (0==_tcscmp(args,L"pinyin_hide"))
		{
			//show_handwrite_select_result();
			show_pinyin_select_result();
		}

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::clear_handwriting_recognizer_word(void)
{
	try
	{
		TCHAR request[1024];
		bool result = false;
		int index_page = 0;

		memset(request,0x0,sizeof(request));

		if (0==_tcscmp(m_cur_interface_version,L"YYC"))
		{
			//8个
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"wordlist",L"<data><item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/>   \
												 <item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/></data>");
		}
		else
		{
			//10个
			if (index_page == page_custom_song || index_page == page_proposal)
			{
				result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"wordlist2",L"<data><item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/>   \
																										<item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/></data>");
			}
			else
			{
				result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"wordlist",L"<data><item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/>   \
																										<item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/><item word=\"\"/></data>");
			}
			
		}
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::clear_handwriting_select_word(void)
{
	try
	{
		TCHAR request[1024];
		bool result = false;

		memset(request,0x0,sizeof(request));

		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"selectedResult_handwriting",L"<data><info str=\"\"/></data>");
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}
	return;
}


bool Cflashktv10Wnd::get_handwriting_assocition_word(std::wstring result_string[],int array_size,const TCHAR *query_word)
{
	try
	{
		if (NULL==query_word)
		{
			return false;
		}
		TCHAR word[16];
		TCHAR result_word[128];
		bool exist=false;
		int letter_count=0;
		const TCHAR *first_query_word=NULL;

		//初始化
		m_association_word_count = 0;
		for (int i=0;i<HANDWRITING_ASSOCIATION_WORD_COUNT;i++)
		{
			memset(m_handwriting_association_word[i],0x0,sizeof(m_handwriting_association_word[i]));
		}

		for (int i=0;i<array_size;i++)
		{
			if (m_use_obscure_query)  //2011-04-08 add
			{
				//启用模糊查询
				first_query_word = _tcsstr(result_string[i].c_str(),query_word);
				if (NULL==first_query_word)
				{
					continue;
				}
				//计算起始字符数
				letter_count = first_query_word-result_string[i].c_str()+_tcslen(query_word);
			}
			else
			{
				//不启用模糊查询
				letter_count = _tcslen(query_word);
			}
			if (result_string[i].length()<=letter_count)
			{
				continue;
			}
			memset(word,0x0,sizeof(word));
			memset(result_word,0x0,sizeof(result_word));
			_tcscpy(result_word,result_string[i].c_str());
			//得到联想的字,unicode编码每个字占用两个字节
			memcpy(word,&result_word[letter_count],2);
			exist = false;
			for (int j=0;j<m_association_word_count;j++)
			{
				//使用小写进行比较
				if (0==_tcscmp(m_handwriting_association_word[j],word))
				{
					//已经存在
					exist = true;
					break;
				}
			}
			if (!exist)
			{
				//如果不存在就加入
				memset(m_handwriting_association_word[m_association_word_count],0x0,sizeof(m_handwriting_association_word[m_association_word_count]));
				_tcscpy(m_handwriting_association_word[m_association_word_count],word);
				m_association_word_count++;
			}
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::show_association_word(int page_operate)
{
	try
	{
		TCHAR data[1024];
		TCHAR request[1024];
		bool result=false;
		int page_count=0;
		int show_word_count=0;

		memset(data,0x0,sizeof(data));
		memset(request,0x0,sizeof(request));
		
		int page_index = 0;

		page_index = m_flash_manage.get_last_page_index();

		if (m_association_word_count<=0)
		{
			//没有联想字直接返回
			return;
		}
		if (0==_tcscmp(m_cur_interface_version,L"YYC"))
		{
			show_word_count = 8;
		}
		else
		{
			show_word_count = INK_RECOGNIZE_ALTERNATE_NUMS;
		}
		page_count = m_association_word_count/show_word_count;
		if (0!=m_association_word_count%show_word_count)
		{
			page_count++;
		}
		switch(page_operate)
		{
		case FIRST_PAGE_OPERATE: //第一页
			{
				m_cur_association_word_page = 0;
			}
			break;
		case NEXT_PAGE_OPERATE: //下一页
			{
				m_cur_association_word_page++;
				if (m_cur_association_word_page>=page_count)
				{
					m_cur_association_word_page=0;
				}
			}
			break;
		case PRE_PAGE_OPERATE:  //上一页
			{
				m_cur_association_word_page--;
				if (m_cur_association_word_page<0)
				{
					m_cur_association_word_page = page_count-1;
				}
			}
			break;
		default:  //默认
			{
				m_cur_association_word_page = 0;
			}
			break;
		}

		//得到要显示的字
		for (int i=0;i<show_word_count;i++)
		{
			m_recognition_result[i].Format(L"%s",m_handwriting_association_word[m_cur_association_word_page*show_word_count+i]);
		}

		//显示识别的结果
		if (0==_tcscmp(m_cur_interface_version,L"YYC"))
		{
			//8个
			swprintf(data,L"<data><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/></data>",
				m_recognition_result[0].GetBuffer(0),m_recognition_result[1].GetBuffer(0), m_recognition_result[2].GetBuffer(0),m_recognition_result[3].GetBuffer(0),   \
				m_recognition_result[4].GetBuffer(0),m_recognition_result[5].GetBuffer(0), m_recognition_result[6].GetBuffer(0),m_recognition_result[7].GetBuffer(0));
		}
		else
		{
			//10个
			swprintf(data,L"<data><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/><item word=\"%s\"/></data>",
				m_recognition_result[0].GetBuffer(0),m_recognition_result[1].GetBuffer(0), m_recognition_result[2].GetBuffer(0),m_recognition_result[3].GetBuffer(0),   \
				m_recognition_result[4].GetBuffer(0),m_recognition_result[5].GetBuffer(0), m_recognition_result[6].GetBuffer(0),m_recognition_result[7].GetBuffer(0),   \
				m_recognition_result[8].GetBuffer(0),m_recognition_result[9].GetBuffer(0));
		}
		//识别的字
		if (page_index == page_custom_song || page_index == page_proposal)
		{
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"wordlist2",data);
		}
		else
		{
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"wordlist",data);
		}
		
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::show_letter_window(const TCHAR *letter)
{
	try
	{
		TCHAR request[256];
		TCHAR input_char[256];
		TCHAR command[256];
		int page_index=0;
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(input_char,0x0,sizeof(input_char));
		memset(command,0x0,sizeof(command));

		page_index = m_flash_manage.get_last_page_index();
		if (page_number_song==page_index)
		{
			//编号点歌
			_tcscpy(command,L"NumberSelectSong");
			swprintf(input_char,L"<data><info number=\"%s\" /></data>",letter);
		}
		else
		{
			if (SONG_LANGUAGE_JAPANESE==m_query_panel_language)
			{
				//日语
				_tcscpy(command,L"selectedResultForKoreanJapan");
				swprintf(input_char,L"<data><info language=\"1\" str=\"%s\"/></data>",letter);
			}
			else if (SONG_LANGUAGE_KOREAN==m_query_panel_language)
			{
				//韩语
				_tcscpy(command,L"selectedResultForKoreanJapan");
				swprintf(input_char,L"<data><info language=\"2\" str=\"%s\"/></data>",letter);
			}
			else
			{
				//其他
				_tcscpy(command,L"selectedResult");
				swprintf(input_char,L"<data><info str=\"%s\"/></data>",letter);
			}
		}
		//字母显示
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,input_char);
		if (result)
		{
			flash_player_call_function(request);
		}
		if ((NULL==letter)||(0==_tcscmp(letter,L"")))
		{
			//清空字幕时，要使所有字符都可以选择
			flash_yinpin_show_all_letter();
		}

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::show_query_letter(const TCHAR *letter,SONG_LANGUAGE query_language)
{
	try
	{
		TCHAR request[256];
		TCHAR command[256];
		TCHAR input_char[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(command,0x0,sizeof(command));
		memset(input_char,0x0,sizeof(input_char));

		swprintf(input_char,L"<data><info str=\"%s\"/></data>",letter);

		if (SONG_LANGUAGE_ZHUYIN==query_language)
		{
			_tcscpy(command,L"selectedResultForZhu");
		}
		else if (SONG_LANGUAGE_MONGOLIA==query_language)
		{
			_tcscpy(command,L"selectedResultForMenggu");
		}
		else
		{
			return;
		}
		//字母显示
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,input_char);
		if (result)
		{
			flash_player_call_function(request);
		}
		if ((NULL==letter)||(0==_tcscmp(letter,L"")))
		{
			//清空字幕时，要使所有字符都可以选择
			flash_yinpin_show_all_letter();
		}

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::show_no_match_result_tip(bool back_tip)
{
	try
	{
		//做没有符合条件的查询提示
		flash_show_tip_message(2,back_tip);
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::send_local_ip_name_to_server(void)
{
	try
	{
		char ip_name[256];
		bool result=false;

		memset(ip_name,0x0,sizeof(ip_name));

		//得到IP和机器名
		if (2==m_master_slave_control_flag)
		{
			//被控机发送主控机的IP，咨询是否已经开房间
			sprintf(ip_name,"%s %s",m_master_control_ip,m_send_room_name);
		}
		else
		{
			//主控机发送本机器的IP
			sprintf(ip_name,"%s %s",m_send_room_ip,m_send_room_name);
		}

		//发送数据,本机器IP和名字
		result = send_msg_to_back_server(ip_name);
		if (!result)
		{
			WriteLog(__FL__, L"发送本机IP和机器名失败");
		}

		return result;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::send_request_open_room_to_server(void)
{
	try
	{
		char open_room_msg[256];
		bool result=false;

		memset(open_room_msg,0x0,sizeof(open_room_msg));

		//得到IP和机器名
		if (2==m_master_slave_control_flag)
		{
			//被控机发送主控机的IP，咨询是否已经开房间
			sprintf(open_room_msg,"<message name=\"RequestOpenRoom\"><data IP=\"%s\" ComputerName=\"%s\" /></message>",m_master_control_ip,m_send_room_name);
		}
		else
		{
			//主控机发送本机器的IP
			sprintf(open_room_msg,"<message name=\"RequestOpenRoom\"><data IP=\"%s\" ComputerName=\"%s\" /></message>",m_send_room_ip,m_send_room_name);
		}

		//发送数据,本机器IP和名字
		result = send_msg_to_back_server(open_room_msg);
		if (!result)
		{
			WriteLog(__FL__, L"发送请求开房消息失败");
		}

		return result;
	}
	catch (...)
	{

	}
	return false;
}


UINT Cflashktv10Wnd::send_data_to_maiba_rule_thread(LPVOID pParam)
{
	try
	{
		//Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);
		REQUEST_BOX_DATA *rquest_data = (REQUEST_BOX_DATA*)pParam;
		rquest_data->pThis->send_msg_to_set_maiba_rule(rquest_data->request_data);

		if (rquest_data)
		{
			delete rquest_data;
			rquest_data = NULL;
		}
	}
	catch (...)
	{

	} 

	return 0;
}

bool Cflashktv10Wnd::send_msg_to_set_maiba_rule(TCHAR *msg)
{
	try
	{
		char  send_data[1024];
		string_conversion string_con;

		if (0 == strcmp(m_set_maiba_rule_ip,""))
		{
			WriteLog(__FL__, L"没有配置设置规则的服务器ip");
			return false;
		}

		// 创建套节字
		SOCKET send_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(send_socket == INVALID_SOCKET)
		{
			return false;
		}
		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;

		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		int m_nSendTimeout = 6000;
		//set send timeout
		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in servAddr; 
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(6666);
		// 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址
		// 如果你的计算机没有联网，直接使用127.0.0.1即可
		servAddr.sin_addr.S_un.S_addr = inet_addr(m_set_maiba_rule_ip);

		if(::connect(send_socket, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		{
			closesocket(send_socket);
			m_connect_rule_server_count++;
			return false;
		}

		//string_con.widechar_to_multibyte(msg,send_data,sizeof(send_data));
		string_con.widechar_to_utf8(msg,send_data,sizeof(send_data));

		int send_len = (int)strlen(send_data);

		int nRecv = ::send(send_socket, send_data, send_len, 0);
		if(nRecv > 0)
		{
			//发送数据成功
			WriteLog(__FL__, L"发送给设置规则服务器的数据成功");
			WriteLog(__FL__, msg);
		}
		// 关闭套节字
		::closesocket(send_socket);

		return true;

	}
	catch (...)
	{
		
	} 
	return false;
}

bool Cflashktv10Wnd::send_msg_to_back_server(char *msg)
{
	try
	{
		if (0==strcmp(m_back_server_ip,""))
		{
			return false;
		}
		// 创建套节字
		SOCKET send_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(send_socket == INVALID_SOCKET)
		{
			return false;
		}
		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;

		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		int m_nSendTimeout = 6000;
		//set send timeout
		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in servAddr; 
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(6500);
		// 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址
		// 如果你的计算机没有联网，直接使用127.0.0.1即可
		servAddr.sin_addr.S_un.S_addr = inet_addr(m_back_server_ip);

		if(::connect(send_socket, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		{
			closesocket(send_socket);
			return false;
		}

		int send_len = (int)strlen(msg);
		int nRecv = ::send(send_socket, msg, send_len, 0);
		if(nRecv > 0)
		{
			//发送数据成功
			WriteLog(__FL__, L"发送给后台开关房服务器的数据成功");
		}
		// 关闭套节字
		::closesocket(send_socket);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

UINT Cflashktv10Wnd::recv_server_msg_udp_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);

		return pThis->recv_server_msg_udp();
	}
	catch (...)
	{

	}
	return -1;
}

UINT Cflashktv10Wnd::recv_server_msg_tcp_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);

		return pThis->recv_server_msg_tcp();
	}
	catch (...)
	{

	}
	return -1;
}

UINT Cflashktv10Wnd::recv_server_msg_udp(void)
{
	try
	{
		fd_set socket_set;
		timeval overtime;
		overtime.tv_sec = 0;
		overtime.tv_usec = 10000;
		int result=0;

		//清0
		FD_ZERO(&socket_set);

		//create socket
		SOCKET list_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (list_socket < 0) 
		{
			//终止线程
			if (m_upd_msg_thread_event_handle)
			{
				SetEvent(m_upd_msg_thread_event_handle);
			}
			return -1;
		}
		/*
		//设置socket属性
		struct linger zerolinger;
		zerolinger.l_onoff = 1;
		zerolinger.l_linger = 5;
		setsockopt(list_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));
		int recv_timeout=60000;
		setsockopt(list_socket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&recv_timeout,sizeof(recv_timeout));
		*/

		//bind local addr
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		addr.sin_port = ntohs(6000);
		memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
		if (SOCKET_ERROR==bind(list_socket, (struct sockaddr*)&addr, sizeof(sockaddr_in)))
		{
			//终止线程
			if (m_upd_msg_thread_event_handle)
			{
				SetEvent(m_upd_msg_thread_event_handle);
			}
			WriteLog(__FL__, L"接受服务器消息的socket绑定端口失败");
			return -1;
		}
		
		char recv_data[204800] = {0x00};
		int recv_len=0;
		sockaddr_in send_addr;
		int nLen = sizeof(send_addr);

		while(m_thread_run)
		{
			try
			{
				SLEEP_FOR; //增加sleep

				memset(recv_data, 0x00, sizeof(recv_data));
				recv_len = 0;

				recv_len = ::recvfrom(list_socket, recv_data,sizeof(recv_data),0,(sockaddr*)&send_addr, &nLen);			

				if (recv_len>0)                     //(2)接受到数据
				{
					if (0!=_strnicmp(recv_data,"OUTLETSSERVERIP",15))
					{
						TCHAR szTmp[1024*100] = {0x00};
						TCHAR szlog[1024*100] = {0x00};
						string_conversion str_conv;
						str_conv.multibyte_to_widechar(recv_data, szTmp, sizeof(szTmp));
						swprintf(szlog, L"SendMessageUdp收到：%s", szTmp);
						//WriteLog(__FL__, szlog);
						//WriteLog(__FL__, L"SendMessageUdp");
						//必须用sendmessage()函数
						SendMessage(DM_RECV_SERVER_MSG,(WPARAM)recv_data,NULL);
					}
				}//end if
			}
			catch (...)
			{
			}
		}

		/*
		//加入监听组
		FD_SET(list_socket,&socket_set);
		while (m_thread_run)
		{
			try
			{
				//将fdSocket集合的一个拷贝fdRead传递给select函数，
				// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回
				fd_set fdRead_set = socket_set;
				result = ::select(0,&fdRead_set,NULL,NULL,&overtime);
				if (result<=0)
				{
					continue;
				}
				//通过将原来fdSocket集合与select处理过的fdRead集合比较，
				// 确定都有哪些套节字有未决I/O，并进一步处理这些I/O。
				for(int i=0; i<(int)socket_set.fd_count; i++)
				{
					if (FD_ISSET(socket_set.fd_array[i],&fdRead_set))
					{
						//recv data
						char recv_data[2048];
						int recv_len=0;
						sockaddr_in send_addr;
						int nLen = sizeof(send_addr);

						memset(recv_data,0x0,sizeof(recv_data));

						recv_len = ::recvfrom(socket_set.fd_array[i],recv_data,sizeof(recv_data),0,(sockaddr*)&send_addr, &nLen);
						if (recv_len>0)                     //(2)接受到数据
						{
							//必须用sendmessage()函数
							SendMessage(DM_RECV_SERVER_MSG,(WPARAM)recv_data,NULL);
						}//end if
					}
				}//end for()
			}
			catch (...)
			{

			}
		}*/

		//终止线程
		if (m_upd_msg_thread_event_handle)
		{
			SetEvent(m_upd_msg_thread_event_handle);
		}
		return 1;
	}
	catch (...)
	{

	}
	//终止线程
	if (m_upd_msg_thread_event_handle)
	{
		SetEvent(m_upd_msg_thread_event_handle);
	}
	return -1;
}

UINT Cflashktv10Wnd::recv_server_msg_tcp(void)
{
	try
	{
		fd_set socket_set;
		timeval overtime;
		overtime.tv_sec = 0;
		overtime.tv_usec = 10000;
		int result=0;

		//清0
		FD_ZERO(&socket_set);

		//create socket
		SOCKET list_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (list_socket < 0) 
		{
			//终止线程
			if (m_tcp_msg_thread_event_handle)
			{
				SetEvent(m_tcp_msg_thread_event_handle);
			}
			return -1;
		}
		//bind local addr
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		addr.sin_port = ntohs(6000);
		memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
		if (SOCKET_ERROR==bind(list_socket, (struct sockaddr*)&addr, sizeof(sockaddr_in)))
		{
			//终止线程
			if (m_tcp_msg_thread_event_handle)
			{
				SetEvent(m_tcp_msg_thread_event_handle);
			}
			WriteLog(__FL__, L"socket绑定端口失败");
			return -1;
		}
		//监听
		if (SOCKET_ERROR==listen(list_socket,SOMAXCONN))
		{
			//终止线程
			if (m_tcp_msg_thread_event_handle)
			{
				SetEvent(m_tcp_msg_thread_event_handle);
			}
			WriteLog(__FL__, L"启动监听端口失败");
			return -1;
		}
		//加入监听组
		FD_SET(list_socket,&socket_set);
		while (m_thread_run)
		{
			try
			{
				SLEEP_FOR; //增加sleep

				//将fdSocket集合的一个拷贝fdRead传递给select函数，
				// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回
				fd_set fdRead_set = socket_set;
				result = ::select(0,&fdRead_set,NULL,NULL,&overtime);
				if (result<=0)
				{
					continue;
				}
				//通过将原来fdSocket集合与select处理过的fdRead集合比较，
				// 确定都有哪些套节字有未决I/O，并进一步处理这些I/O。
				for(int i=0; i<(int)socket_set.fd_count; i++)
				{
					if (FD_ISSET(socket_set.fd_array[i],&fdRead_set))
					{
						if (socket_set.fd_array[i]==list_socket)  // （1）监听套节字接收到新连接
						{
							if(socket_set.fd_count < FD_SETSIZE)
							{
								//accept socket
								SOCKET accept_socket;
								sockaddr_in accept_sockaddr;
								int sockaddr_len=0;
								int timeout = 60000;
								linger accept_linger;
								accept_linger.l_onoff = 1;  // (在closesocket()调用,但是还有数据没发送完毕的时候容许逗留)
								accept_linger.l_linger = 5; // (容许逗留的时间为0秒)

								sockaddr_len = sizeof(accept_sockaddr);
								accept_socket = ::accept(socket_set.fd_array[i],(struct sockaddr*)&accept_sockaddr,&sockaddr_len);
								//设置接受超时
								::setsockopt(accept_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));
								//设置关闭之后马上断开
								::setsockopt(accept_socket,	SOL_SOCKET,	SO_LINGER,(const char*)&accept_linger,sizeof(accept_linger));
								//加入到socket_set中
								FD_SET(accept_socket,&socket_set);
							}
							else
							{
								WriteLog(__FL__, L"有太多的socket连接，不能接受新的连接");
								continue;
							}
						}
						else
						{
							//recv data
							char recv_data[2048*100] = {0x00};
							int recv_len=0;

							memset(recv_data,0x0,sizeof(recv_data));

							recv_len = ::recv(socket_set.fd_array[i],recv_data,sizeof(recv_data),0);

							if (recv_len>0)                     //(2)接受到数据
							{
								if (0==_strnicmp(recv_data,"GETDBLOADMESSAGE",16))  //如果是盒子来请求数据库信息
								{
									//启动线程给盒子发送数据
									m_load_song_db_socket = socket_set.fd_array[i];
									m_load_song_db_addr = addr;
									AfxBeginThread(Cflashktv10Wnd::send_data_to_box_thread,this);
								}
								else
								{
									TCHAR szTmp[1024*100] = {0x00};
									TCHAR szlog[1024*100] = {0x00};
									string_conversion str_conv;
									str_conv.multibyte_to_widechar(recv_data, szTmp, sizeof(szTmp));
									swprintf(szlog, L"SendMessageTCp收到：%s", szTmp);
									//WriteLog(__FL__, szlog);
									//必须用sendmessage()函数
									SendMessage(DM_RECV_SERVER_MSG,(WPARAM)recv_data,NULL);
								}
							}
							else								// （3）连接关闭、重启或者中断
							{
								::closesocket(socket_set.fd_array[i]);
								FD_CLR(socket_set.fd_array[i], &socket_set);
							}
						}
					}
				}//end for()
			}
			catch (...)
			{

			}
		}
		//终止线程
		if (m_tcp_msg_thread_event_handle)
		{
			SetEvent(m_tcp_msg_thread_event_handle);
		}
		return 1;
	}
	catch (...)
	{

	}
	//终止线程
	if (m_tcp_msg_thread_event_handle)
	{
		SetEvent(m_tcp_msg_thread_event_handle);
	}
	return -1;
}

bool Cflashktv10Wnd::shutdown_computer(void)
{
	try
	{

		//启动外调程序
		start_software_on_close();
		_sleep(1000);

		WriteLog(__FL__, L"接受到关机指令");
		//关机预处理
		exit_window_pretreat();
		WriteLog(__FL__, L"开始正常关机");
		return force_exit_window(EWX_POWEROFF|EWX_SHUTDOWN|EWX_FORCE);
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::reboot_computer(void)
{
	try
	{
		WriteLog(__FL__, L"接受到重启指令");
		//关机预处理
		exit_window_pretreat();
		WriteLog(__FL__, L"开始正常重启机器");
		return force_exit_window(EWX_REBOOT|EWX_FORCE);
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::tv_osd_play_finish(void)
{
	if (0==m_player_manager.get_text_osd_play_state())
	{
		//播放完成
		return true;
	}

	//没有播放完成
	return false;
}

bool Cflashktv10Wnd::show_picture_screen_save(TCHAR *path)
{
	try
	{
		if (!m_screen_saver_window_exist)
		{
			//屏保窗口不存在
			return false;
		}
		if (m_show_screen_saver_state)
		{
			//先退出原有屏保状态
			quit_screen_save();
		}

		//启动新的屏保
		m_screen_saver_window.set_ad_screen_saver_path(path);
		m_screen_saver_window.show_screen_saver();
		m_screen_saver_window.BringWindowToTop();
		m_show_screen_saver_state = true;

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void Cflashktv10Wnd::quit_screen_save(void)
{
	try
	{
		if(!m_show_screen_saver_state)
		{
			//不是屏保状态就不用退出屏保了
			return;
		}
		if (m_pc_show_screen_saver)
		{
			if (m_show_video_screen_saver)
			{
				//视频屏保
				if (SCREEN_TYPE_VERTICAL==m_interface_type)
				{
					//竖版不弹
				}
				else
				{

					show_quit_video_screen_saver();
				}
			}
			else
			{
				//图片屏保
				if (m_screen_saver_window_exist && !m_start_video_screen_saver)
				{
					m_screen_saver_window.hide_screen_saver();
				}
				else
				{
					//用户单击视频启动的屏保
					if (SCREEN_TYPE_VERTICAL==m_interface_type)
					{
						//竖版不弹
					}
					else
					{

						show_quit_video_screen_saver();
					}
				}
			}
		}
		else
		{
			//用户单击视频启动的屏保
			if (SCREEN_TYPE_VERTICAL==m_interface_type)
			{
				//竖版不弹
			}
			else
			{

				show_quit_video_screen_saver();
			}
		}

		return;
	}
	catch (...)
	{
	}
	return;
}

void Cflashktv10Wnd::play_pc_AD_picture(void)
{
	try
	{
		TCHAR path[256];
		bool result=false;
		TCHAR request[1024];
		TCHAR data[1024];
		int page_index=0;

		memset(path,0x0,sizeof(path));
		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//显示广告，重新计时
		m_play_AD_timer.start();

		//得到页面索引
		page_index = m_flash_manage.get_last_page_index();
		switch(page_index)
		{
			case page_title:          //歌名点歌
			case page_lyric:          //歌词点歌
			case page_top_song:       //金曲排行
			case page_new_song:       //新歌推荐
			case page_opera:          //经典戏曲
			case page_language:       //语种点歌
			case page_selected:       //已选歌曲
			case page_singed:         //已唱歌曲
			case page_member_song:    //会员歌曲
			case page_theme_song:          //主题点歌
			case page_new_theme_song:
			case page_class:          //分类点歌
			case page_recording:      //录音页面
			case page_movie_song:     //影视金曲
			case page_era_song:       //年代金曲
			case page_number_song:    //编号点歌
			case page_write:        //手写点歌
			case page_word_count:
			case page_hdmi:         //高清专区
				{
					if ((SCREEN_TYPE_HORIZON==m_interface_type)&&(SONG_SHOW_MODE_CARD==m_song_show_mode))
					{
						//卡片方式，不能显示广告图片
						break;
					}
				}
			//下面两个只有列表
			case page_movie:          //电影页面
			case page_concert:  //演唱会
			case page_place_video:  //场所视频
			case page_U_disk:         //U盘播歌
			{
				//得到要播放的图片路径
				result = m_pc_AD_manager.get_next_play_ad_picture(path);
			}
			break;
			default:
			{
				if (SCREEN_TYPE_VERTICAL==m_interface_type)
				{
					//竖版所有界面都有广告位
					result = m_pc_AD_manager.get_next_play_ad_picture(path);
				}
			}
			break;
		}
		//显示广告图片
		if (0!=_tcscmp(path,L""))
		{
			//有图片路径就显示
			swprintf(data,L"<data><info url=\"%s\"/></data>",path);
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"Poster",data);
			if (result)
			{
				//flash_player_call_function(request);
			}
		}

		if (m_game_flash_player_exist&&(0!=_tcscmp(m_interactive_game_page,L"")))
		{
			//启动了互动游戏，游戏界面上的图片也要更换
			memset(path,0x0,sizeof(path));
			result = m_game_AD_manager.get_next_play_ad_picture(path);
			if (result)
			{
				memset(request,0x0,sizeof(request));
				m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"GameADImage",path);
				m_game_flash_player.CallFunction(request);
			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::play_wall_panel_AD_picture(void)
{
	try
	{
		if (m_wall_panel_window_exist&&(WALL_PANEL_IMAGE_FLASH==m_wall_panel_show_mode))
		{
			TCHAR path[256];
			bool result=false;

			memset(path,0x0,sizeof(path));
			//启动了墙面板图片背景功能
			result = m_wall_panel_AD_manager.get_next_play_ad_picture(path);
			if (result)
			{
				//显示图片
				m_wall_panel_window.set_show_image(path);
			}
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::set_play_progress_bar_pos(void)
{
	try
	{
		long result=0;
		TCHAR request[1024];
		TCHAR data[1024];
		long total_time=0;
		long play_time=0;
		bool ret=false;
		int page_index=0;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//得到播放进度
		//直接得到百分比
		//result = m_player_manager.get_cur_play_pos();
		//自己计算百分比
		total_time = m_player_manager.get_total_time_length();
		if (total_time<=0)
		{
			return;
		}
		play_time = m_player_manager.get_play_time_length();
		if (play_time<0)
		{
			return;
		}
		result = play_time*100/total_time;
		if (result<0)
		{
			result = 0;
		}
		else if (result>=99)
		{
			result = 100;
		}

		m_n_Syn_count++;
		if (m_n_Syn_count > 15)
		{
			m_n_Syn_count = 0;
		}
		//发给对方进行同步
		if (m_b_pk_invitation && 15 == m_n_Syn_count)
		{
			//发送消息给连接的ip
			TCHAR send_ip[2048];
			TCHAR send_pos[10];
			TCHAR send_data[256];
			
			memset(send_data,0x0,sizeof(send_data));
			memset(send_pos,0x0,sizeof(send_pos));
			memset(send_ip,0x0,sizeof(send_ip));

			if (0 != _tcscmp(m_pk_invitationIP,L""))
			{
				_tcscpy(send_ip,m_pk_invitationIP);
			}
			if (0 != _tcscmp(m_pk_acceptIP,L""))
			{
				_tcscpy(send_ip,m_pk_acceptIP);
			}
			swprintf(send_pos,_T("%d"),play_time);
			_tcscpy(send_data,_T("pk_pos"));
			_tcscat(send_data,send_pos);
		
			connect_inviation(send_ip,send_data);
			m_n_Syn_count = 0;
		}

		if (m_use_test_function && (CLOSE_ROOM_STATE==m_pc_state)&&m_start_test&&(m_pre_play_pos!=result))
		{
			//测试状态下也要发
			memset(request,0x0,sizeof(request));
			memset(data,0x0,sizeof(data));

			swprintf(data,L"%d",result);
			ret = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"songslider",data);
			if (ret)
			{
				m_test_flash_player.CallFunction(request);
			}
		}
		//得到当前页面索引
		page_index = m_flash_manage.get_last_page_index();
		//首页和辅助页面不发送
		if ((page_homepage!=page_index)&&(page_assist!=page_index)&&(m_pre_play_pos!=result))
		{
			//播放位置不同时，在进行改变
			swprintf(data,L"<data><progress percent=\"%d\"/></data>",result);
			ret = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"SongPlayProgress",data);
		
			if (ret)
			{
				flash_player_call_function(request);
			}
			//记录下前一个播放位置
			m_pre_play_pos = result;
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::set_preview_song_play_progress(void)
{
	try
	{
		long song_total_time=0;
		long song_play_time=0;
		long play_percent=0;
		TCHAR data[256];
		TCHAR request[1024];
		bool result=false;
		int page_index=0;

		memset(data,0x0,sizeof(data));
		memset(request,0x0,sizeof(request));

		//determine whether the preview page
		page_index = m_flash_manage.get_last_page_index();
		if (page_preview!=page_index)
		{
			return;
		}

		//get preview song total time length
		song_total_time = m_player_manager.preview_control(PVC_GET_DURATION,0,0);
		if (song_total_time<=0)
		{
			return;
		}
		//get song play time length
		song_play_time = m_player_manager.preview_control(PVC_GET_POSITION,0,0);
		if (song_play_time<=0)
		{
			return;
		}
		//compute play percent
		play_percent = song_play_time*100/song_total_time;
		if (play_percent<0)
		{
			play_percent = 0;
		}
		else if(play_percent>100)
		{
			play_percent = 100;
		}
		if(m_preview_pre_play_pos!=play_percent)
		{
			//播放位置不同时，在进行改变
			swprintf(data,L"%d",play_percent);
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"PreviewSongSlider",data);
			if (result)
			{
				flash_player_call_function(request);
			}
			//记录下前一个播放位置
			m_preview_pre_play_pos = play_percent;
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::flash_message_call_recommend_select_song(const TCHAR* args)
{
	try
	{
		bool result = false;
		int number=0;
		int play_number=0;
		song_info song_info_class;
		TCHAR song_id[256];
		int page_index = 0; 
		TCHAR song_local_path[256];   //得到当前歌曲的状态 0：本地歌曲  1：下载歌曲  2：更新歌曲

		memset(song_id,0x0,sizeof(song_id));


		page_index = m_flash_manage.get_last_page_index();

		//得到选中的歌曲信息 
		result = get_song_info_by_id(args,song_info_class,PLAY_SONG_TYPE_SELECT_SONG);
		if (!result)
		{
			return;
		}

		song_info_class.get_song_id(song_id);

		//得到本地是否有这首歌曲
		song_info_class.get_local_path(song_local_path);
		if (0==_tcscmp(song_local_path,L"1"))
		{
			//需要下载当前歌曲
			dwon_song_file_to_server(song_id,1);

			///标示为下载歌曲
			song_info_class.set_down_update_song(1);
		}			
 
		/*
		//查看是否存在
		result = m_video_play_manager.query_select_song_by_id(song_id,play_number);

		//存在，允许重复选歌，必须要切换页面
		if(result && repeat_select_song(song_id,page_index))
		{
			return;
		}
		*/
		 
		//if (result && !m_allow_repeat_select_song && (m_select_page_index != page_index))
		//{
		//	//保存基本信息
		//	m_select_song_info=song_info_class;
		//	m_select_song_priority=false;
		//	m_select_song_number = number;
		//	//存在，显示复选提示
		//	//show_check_window(true);
		//	return;
		//}


		result = play_or_insert_select_list(song_info_class,false);
		if (!result)
		{
			return;
		}
		 
		repeat_select_song(song_id,page_index);
		//刷新互动场景屏信息
		flash_message_call_selected_song_list();
		//重新显示上下首歌名
		show_song_name();
	}
	catch (...)
	{
		
	} 

	return;
}

void Cflashktv10Wnd::flash_message_call_recorder_select_song(const TCHAR* args,bool priority)
{
	try
	{ 
		song_info song_info_class;
		bool result=false;
		int select_song_count=0;
		TCHAR song_id[128];
		TCHAR wave_path[256];
		int play_number=0;
		int  page_index=0;
		TCHAR down_mp3_path[256];
		string_conversion str_con;
		char szSubscript[256] = {0x00};

		memset(song_id,0x0,sizeof(song_id));
		memset(wave_path,0x0,sizeof(wave_path));
		memset(down_mp3_path,0x0,sizeof(down_mp3_path));

		page_index = m_flash_manage.get_last_page_index();

		if (args==NULL)
		{
			return;
		}

		_tcscpy(song_id,args);

		//得到选中的歌曲信息
		//result = m_query_song_manager.get_recorder_song_info(song_id,song_info_class);
		str_con.widechar_to_multibyte(song_id, szSubscript, 256);
		result = m_query_song_manager.get_song_info(atol(szSubscript),song_info_class);
		if (!result)
		{
			return;
		}

		//得到歌曲编号
		result = song_info_class.get_song_id(song_id);
		song_info_class.set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);

//		song_info_class.set_recorder_wave_path(wave_path);
		song_info_class.get_wave_path(wave_path);

		if (!PathFileExists(wave_path))   
		{ 
			//flash_show_tip_message(115);
			//return;
		}		 

		if (!priority)
		{ 
			//查看是否存在
			result = m_video_play_manager.query_select_song_by_id(song_id,play_number);

			if (result && repeat_select_song(song_id,page_index))
			{
				//不让重复点歌
				return;
			} 
		}

		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(song_info_class,priority);
		if (!result)
		{
			return;
		}

		//添加
		repeat_select_song(song_id,page_index); 
		show_song_name();
	}
	catch (...)
	{
		
	}
	
	return;
}

void Cflashktv10Wnd::get_dekaron_song_url_id(const TCHAR* args,TCHAR* url_id)
{
	try
	{
		TCHAR URL[256];
		bool result = false;
		MAIBA_HEIGHT_RANKING maiba_song_info;
		memset(&maiba_song_info,0x0,sizeof(maiba_song_info));
		memset(URL,0x0,sizeof(URL));

		for (int i=0;i<48;i++)
		{
			if (0 ==  _tcscmp(m_maiba_song_list[i].voice_id,args))
			{
				memcpy(&maiba_song_info,&m_maiba_song_list[i],sizeof(MAIBA_HEIGHT_RANKING));
				_tcscpy(url_id,m_maiba_song_list[i].voice_code);
				result = true;
				break;
			}
		}

	}
	catch (...)
	{
		
	} 

	return;
}

void Cflashktv10Wnd::flash_message_call_dekaron_song(const TCHAR *args,bool priority,bool singed_page)
{
	try
	{
		TCHAR request_data[1024];
		bool result = false;
		MAIBA_HEIGHT_RANKING maiba_song_info;
		memset(&maiba_song_info,0x0,sizeof(maiba_song_info));

		for (int i=0;i<48;i++)
		{
			if (0 ==  _tcscmp(m_maiba_song_list[i].voice_id,args))
			{
				memcpy(&maiba_song_info,&m_maiba_song_list[i],sizeof(MAIBA_HEIGHT_RANKING));
				result = true;
				break;
			}
		}

		if (result && !m_request_arena_one_song)
		{
			//分享
			flash_message_call_share_area_recorder_audio(maiba_song_info);
			memset(m_request_arena_song_id,0x0,sizeof(m_request_arena_song_id));
		}
		else
		{
			//发送数据给规则服务器 
			swprintf(request_data,L"REQUESTMAIBAONEDATA{\"voiceid\":\"%s\"}",args);

			REQUEST_BOX_DATA *request_box_data = new REQUEST_BOX_DATA;

			_tcscpy(request_box_data->request_data,request_data);
			request_box_data->nPort = 6666;
			request_box_data->pThis = this;
			AfxBeginThread(send_server_msg_tcp_thread,request_box_data);
		}
		
	}
	catch (...)
	{
		
	}
	
	return;
}
/*
void Cflashktv10Wnd::flash_message_call_dekaron_song(const TCHAR *args,bool priority,bool singed_page)
{
	try
	{
		int number=0;
		song_info song_info_class;
		bool result=false;
		int select_song_count=0;
		TCHAR voice_id[128];  //录音歌曲id
		TCHAR wave_path[256];
		int  play_number = 0;
		TCHAR song_id[128];
		int  page_index=0; 

		memset(voice_id,0x0,sizeof(voice_id));
		memset(wave_path,0x0,sizeof(wave_path));
		memset(song_id,0x0,sizeof(song_id));

		page_index = m_flash_manage.get_last_page_index();

		if (args==NULL)
		{
			return;
		}

		for (int i=0;i<48;i++)
		{
			if (0 == _tcscmp(args,m_maiba_song_list[i].voice_id))
			{
				_tcscpy(song_id,m_maiba_song_list[i].song_id);
				_tcscpy(wave_path,m_maiba_song_list[i].wave_path); 
				_tcscpy(voice_id,m_maiba_song_list[i].voice_id);
				break;
			}
		}

		 
		//得到选中的歌曲信息
		//result = m_query_song_manager.get_song_info(number,song_info_class);
		result = get_song_info_by_id(song_id,song_info_class,PLAY_SONG_TYPE_RECORDER_SONG);
		if (!result)
		{
			return;
		}

		//得到歌曲编号
		result = song_info_class.get_song_id(song_id);

		//song_info_class.get_wave_path(wave_path);
		song_info_class.set_recorder_wave_path(wave_path);

		if (!PathFileExists(wave_path))   
		{ 
			//flash_show_tip_message(115);
			//return;
		}		 

		if (!priority)
		{ 
			//查看是否存在
			result = m_video_play_manager.query_select_song_by_id(song_id,play_number);

			if (result && repeat_select_song(song_id,page_index))
			{
				//不让重复点歌
				return;
			} 
		}

		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(song_info_class,priority);
		if (!result)
		{
			return;
		}

		//添加
		repeat_select_song(song_id,page_index); 
		show_song_name();
	}
	catch (...)
	{
		
	}
	
	return;
}
*/
void Cflashktv10Wnd::flash_message_call_get_web_select_song(const TCHAR* args)
{
	try
	{
		TCHAR request_data[1024];
		bool result = false;
		TCHAR URL[256];
		memset(URL,0x0,sizeof(URL));

		//得到网络的
		for (int i =0;i<48;i++)
		{
			if (0 == _tcscmp(args,m_maiba_song_info[i].voice_id))
			{
				_tcscpy(URL,L"http://www.joyk.com.cn/");
				_tcscat(URL,m_maiba_song_info[i].song_down_addrss);
				result = true;
				break;
			}				
		}

		if (result && !m_request_arena_one_song)
		{
			//找到了
			send_share_url_image_to_flash(URL);
			memset(m_request_arena_song_id,0x0,sizeof(m_request_arena_song_id));
		}
		else
		{
			//向盒子请求这条数据PLACEVERSION/GETVOICEINFO?VoiceId=12323
			swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/GETVOICEINFO?VoiceId=%s",args);
			WriteLog(__FL__, request_data);

			//发送当前歌曲验证码
			thread_send_to_box_tcp_function(request_data,18007);
		}			
	}
	catch (...)
	{
		
	}
	
	return;
}

void Cflashktv10Wnd::parse_message_call_arena_one_song(char* recv_data)
{
	try
	{
		bool result = false;
		CMarkup parse_xml_doc;
		TCHAR maiba_data[2048];
		const TCHAR *parse_msg=NULL;
		const TCHAR *temp=NULL; 
		std::wstring item_value;
		string_conversion string_con; 

		MAIBA_HEIGHT_RANKING maiba_song_info;

		memset(maiba_data,0x0,sizeof(maiba_data));
		memset(&maiba_song_info,0x0,sizeof(maiba_song_info));

		string_con.utf8_to_widechar(recv_data,maiba_data,sizeof(maiba_data));

		parse_msg = maiba_data;

		result =parse_xml_doc.SetDoc(parse_msg);
		if (!result)
		{
			return;
		}
		parse_xml_doc.ResetPos();   //list
		result = parse_xml_doc.FindChildElem(); 
		if (!result)
		{
			return;
		}

		WriteLog(__FL__, L"接受到单条规则数据!");
		parse_xml_doc.IntoElem();  
		result = parse_xml_doc.FindChildElem(); //<item>

		if (!result)
		{
			return;
		}
		parse_xml_doc.IntoElem(); 
		item_value = parse_xml_doc.GetData(); 
		_tcscpy(maiba_song_info.voice_id,item_value.c_str());
		if (!item_value.c_str())
		{
			return;
		}

		parse_xml_doc.FindElem();
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.song_id,item_value.c_str());

		parse_xml_doc.FindElem();  
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.song_name,item_value.c_str());

		parse_xml_doc.FindElem();   
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.singer_name,item_value.c_str());

		parse_xml_doc.FindElem();   
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.score,item_value.c_str());

		parse_xml_doc.FindElem();    
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.member_pic,item_value.c_str());

		parse_xml_doc.FindElem();     
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.wave_path,item_value.c_str());

		parse_xml_doc.FindElem();   
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.video_path,item_value.c_str());

		//返回<item>
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem();  
		
		if (m_request_arena_one_song)
		{
			//点歌
			flash_message_call_arena_song(maiba_song_info);
		}
		else
		{
			//如果当前发过来的是我点击分享的id，则进行分享
			if (0 == _tcscmp(maiba_song_info.song_id,m_request_arena_song_id))
			{
				//分享
				flash_message_call_share_area_recorder_audio(maiba_song_info);
			}
		}
	}
	catch (...)
	{ 
		
	}
	return;
}

void Cflashktv10Wnd::flash_message_call_arena_song(MAIBA_HEIGHT_RANKING &maiba_song_info)
{
	try
	{
		song_info song_info_class; 
		bool result = false;
		bool bFlags=false;
		int play_number = 0;
		int page_index= 0;
		 
		page_index = m_flash_manage.get_last_page_index();
		
		song_info_class.set_song_relative_path(maiba_song_info.video_path);
		song_info_class.set_recorder_video_path(maiba_song_info.video_path);
		song_info_class.set_song_id(maiba_song_info.voice_id);
		song_info_class.set_song_name(maiba_song_info.song_name);
		song_info_class.set_singer_name(maiba_song_info.singer_name);
		song_info_class.set_culture_code(maiba_song_info.song_id);
		song_info_class.set_recorder_wave_path(maiba_song_info.wave_path);
		song_info_class.set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);

		//查看是否存在
		result = m_video_play_manager.query_select_song_by_id(maiba_song_info.voice_id,play_number);

		if (result && repeat_select_song(maiba_song_info.voice_id,page_index))
		{
			//不让重复点歌
			return;
		} 

		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(song_info_class,false);
		if (!result)
		{
			return;
		}

		//添加
		repeat_select_song(maiba_song_info.voice_id,page_index); 
		show_song_name();

		return;
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::parse_message_call_maiba_song(char* recv_data)
{
	try
	{
		bool result = false;
		CMarkup parse_xml_doc;
		TCHAR maiba_data[2048];
		const TCHAR *parse_msg=NULL;
		const TCHAR *temp=NULL; 
		std::wstring item_value;
		string_conversion string_con;

		MAIBA_SONG_INFO_STU maiba_song_info;

		memset(maiba_data,0x0,sizeof(maiba_data));
		memset(&maiba_song_info,0x0,sizeof(maiba_song_info));

		string_con.utf8_to_widechar(recv_data,maiba_data,sizeof(maiba_data));

		parse_msg = maiba_data;
		//解析xml文档
		result =parse_xml_doc.SetDoc(parse_msg);
		if (!result)
		{
			return;
		}
		parse_xml_doc.ResetPos();   //list
		result = parse_xml_doc.FindChildElem(); 
		if (!result)
		{
			return;
		}
		 /*<song_list><item ><song_id>10000112</song_id><song_name>ni shi wo de yan</song_name><singer_name>linyoujia</singer_name>
			<song_score>98</song_score><listen_count>1000</listen_count><flowers_count>15222</flowers_count><user_id>1455577</user_id>
			<voice_id>111444</voice_id><song_down_addrss>http:\\</song_down_addrss><member_add>http:\\</member_add> 
			</item><nick_name>昵称<nick_name></song_list>*/

		 
		parse_xml_doc.IntoElem();  
		result = parse_xml_doc.FindChildElem(); //<item>

		if (!result)
		{
			return;
		}
		parse_xml_doc.IntoElem();  //song_id
		item_value = parse_xml_doc.GetData(); 
		_tcscpy(maiba_song_info.song_id,item_value.c_str());

		parse_xml_doc.FindElem(); //song_name
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.song_name,item_value.c_str());
			
		parse_xml_doc.FindElem();  //singer_name
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.singer_name,item_value.c_str());
		
		parse_xml_doc.FindElem();   //song_score
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.song_score,item_value.c_str());
			
		parse_xml_doc.FindElem();   //listen_count
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.listen_count,item_value.c_str());

		parse_xml_doc.FindElem();    //flowers_count
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.flowers_count,item_value.c_str());
		
		parse_xml_doc.FindElem();     //user_id
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.user_id,item_value.c_str());

		parse_xml_doc.FindElem();   //voice_id
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.voice_id,item_value.c_str());

		//parse_xml_doc.FindElem();     //song_dwon_name
		//item_value = parse_xml_doc.GetData();
		//_tcscpy(m_maiba_song_info[nPos].song_down_name,item_value.c_str());
						
		parse_xml_doc.FindElem();   //song_down_addrss
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.song_down_addrss,item_value.c_str());
		parse_memeber_head_picture_name(item_value.c_str(),maiba_song_info.recorder_video,1);

		parse_xml_doc.FindElem();   //member_add
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.member_addr,item_value.c_str());
		parse_memeber_head_picture_name(item_value.c_str(),maiba_song_info.member_pic,2);

		parse_xml_doc.FindElem();   //nick_name
		item_value = parse_xml_doc.GetData();
		_tcscpy(maiba_song_info.nick_name,item_value.c_str()); 

		//返回<item>
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem();
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem(); 
		parse_xml_doc.OutOfElem(); 

		result = parse_xml_doc.FindChildElem();
	 
		if (m_request_arena_one_song)
		{
			//点歌
			flash_message_call_maiba_song(maiba_song_info);
		}
		else
		{
			if (0 == _tcscmp(maiba_song_info.voice_id,m_request_arena_song_id))
			{
				//分享
				flash_message_call_share_web_song(maiba_song_info);
			}
		}
		
	}
	catch (...)
	{
		
	}
	
	return;
}

void Cflashktv10Wnd::flash_message_call_maiba_song(MAIBA_SONG_INFO_STU &maiba_song_info)
{
	try
	{
		song_info song_info_class; 
		bool result = false;
		TCHAR recorder_video_path[256];
		TCHAR recorde_video_temp[256];
		TCHAR send_data[1024];
		bool bFlags=false;
		int play_number = 0;
		int page_index= 0;

		memset(recorder_video_path,0x0,sizeof(recorder_video_path));
		memset(recorde_video_temp,0x0,sizeof(recorde_video_temp));

		page_index = m_flash_manage.get_last_page_index();
		result = get_song_info_by_id(maiba_song_info.song_id,song_info_class,PLAY_SONG_TYPE_RECORDER_SONG);
		song_info_class.get_song_relative_path(recorder_video_path);

		if (!result)
		{
			WriteLog(__FL__, L"本场所没有这这首麦霸的视频歌曲!");
			WriteLog(__FL__, maiba_song_info.song_id);
			//flash_show_tip_message(L"本场所没有这这首歌曲的视频信息!");
			//return;
			
		}

		bFlags = false;
		for (int i=0; i<6;i++)
		{
			memset(recorde_video_temp,0x0,sizeof(recorde_video_temp));
			swprintf(recorde_video_temp,L"\\\\%s%s",m_server_ip[i],recorder_video_path);
			if (PathFileExists(recorde_video_temp))
			{
				//找到了
				memset(recorder_video_path,0x0,sizeof(recorder_video_path));
				_tcscpy(recorder_video_path,recorde_video_temp);
				bFlags = true;
				break;
			}
		}

		if (!bFlags)
		{
			WriteLog(__FL__, L"没有找到这首歌的视频文件,歌曲id为:");
			WriteLog(__FL__, recorder_video_path);
			//flash_show_tip_message(L"本场所没有这这首歌曲的视频文件!");
			//return;
			//设置为mp3文件
			song_info_class.set_recorder_exist_video_path(false);
			song_info_class.set_recorder_video_path(maiba_song_info.recorder_video);
		}
		else
		{
			//设置为本场所的歌曲视频路径
			song_info_class.set_recorder_video_path(recorder_video_path);
			song_info_class.set_recorder_exist_video_path(true);
		}

		song_info_class.set_song_id(maiba_song_info.voice_id);
		song_info_class.set_song_name(maiba_song_info.song_name);
		song_info_class.set_singer_name(maiba_song_info.singer_name);
		song_info_class.set_culture_code(maiba_song_info.song_id);
		song_info_class.set_recorder_wave_path(maiba_song_info.recorder_video);
		song_info_class.set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);

		memset(send_data,0x0,sizeof(send_data));
		//判断当前服务器是否有
		if (!PathFileExists(maiba_song_info.recorder_video))
		{
			swprintf(send_data,L"Message&DOWN_FILE_FROM_BOX;GET_MP3_DOWN:%s",maiba_song_info.song_down_addrss);
			WriteLog(__FL__, L"服务器上没有这首歌，要进行下载：");
			WriteLog(__FL__, send_data);

			//下载数据服务端
			send_data_to_service_udp(send_data);
		}
		else
		{
			WriteLog(__FL__, L"服务器上有这首歌，不需要进行下载：");
			WriteLog(__FL__, maiba_song_info.song_down_addrss);
		}
	 
		//查看是否存在
		result = m_video_play_manager.query_select_song_by_id(maiba_song_info.voice_id,play_number);

		if (result && repeat_select_song(maiba_song_info.voice_id,page_index))
		{
			//不让重复点歌
			return;
		} 
	 
		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(song_info_class,false);
		if (!result)
		{
			return;
		}

		//添加
		repeat_select_song(maiba_song_info.voice_id,page_index); 
		show_song_name();

	}
	catch (...)
	{
		
	}
	
	return;
}

void Cflashktv10Wnd::flash_message_call_maiba_song(const TCHAR *args,bool priority,bool singed_page)
{
	try
	{
		int number=0;
		song_info song_info_class; 
		bool result=false;
		int select_song_count=0;
		TCHAR song_id[128];
		TCHAR wave_path[256];
		int play_number=0;
		int  page_index=0;
		TCHAR send_data[256];
		TCHAR down_mp3_path[256];
		TCHAR recorder_video_path[256];
		int nPos_number=-1;
		TCHAR recorde_video_temp[256];

		bool bFlags = false;    //标示是否含有这首歌曲

		memset(song_id,0x0,sizeof(song_id));
		memset(wave_path,0x0,sizeof(wave_path));
		memset(down_mp3_path,0x0,sizeof(down_mp3_path));
		memset(recorder_video_path,0x0,sizeof(recorder_video_path));

		page_index = m_flash_manage.get_last_page_index();

		if (args==NULL)
		{
			return;
		}

		for (int i=0;i<48;i++)
		{
			if (0 == _tcscmp(args,m_maiba_song_info[i].voice_id))
			{
				_tcscpy(song_id,m_maiba_song_info[i].song_id);
				_tcscpy(wave_path,m_maiba_song_info[i].recorder_video);
				_tcscpy(down_mp3_path,m_maiba_song_info[i].song_down_addrss);
				bFlags = true;
				nPos_number = i;
				break;
			}
		}

		if (!bFlags)
		{
			//如果没有这首歌
			WriteLog(__FL__, L"没有这首麦霸pk歌曲！！");
			WriteLog(__FL__, args);
			return;
		}

		result = get_song_info_by_id(song_id,song_info_class,PLAY_SONG_TYPE_RECORDER_SONG);
		song_info_class.get_song_relative_path(recorder_video_path);

		if (!result)
		{
			WriteLog(__FL__, L"本场所没有这这首麦霸的视频歌曲!");
			WriteLog(__FL__, song_id);
			return;
		}

		//_tcscpy(recorder_video_path,L"\\\\10.0.3.12\\JP002\\896369.MPG");
		bFlags = false;
		for (int i=0; i<6;i++)
		{
			memset(recorde_video_temp,0x0,sizeof(recorde_video_temp));
			swprintf(recorde_video_temp,L"\\\\%s%s",m_server_ip[i],recorder_video_path);
			if (PathFileExists(recorde_video_temp))
			{
				//找到了
				memset(recorder_video_path,0x0,sizeof(recorder_video_path));
				_tcscpy(recorder_video_path,recorde_video_temp);
				bFlags = true;
				break;
			}
		}
		if (!bFlags)
		{
			WriteLog(__FL__, L"没有找到这首歌的视频文件,歌曲id为:");
			WriteLog(__FL__, recorder_video_path);
		}
		
		song_info_class.set_song_id(m_maiba_song_info[nPos_number].voice_id);
		song_info_class.set_song_name(m_maiba_song_info[nPos_number].song_name);
		song_info_class.set_singer_name(m_maiba_song_info[nPos_number].singer_name);
		song_info_class.set_recorder_video_path(recorder_video_path);
		song_info_class.set_culture_code(m_maiba_song_info[nPos_number].song_id);
		song_info_class.set_recorder_wave_path(m_maiba_song_info[nPos_number].recorder_video);
		song_info_class.set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);
	
		//得到歌曲编号
		if (!PathFileExists(wave_path))   
		{ 
			//flash_show_tip_message(115);
			//return;
		}	

		memset(send_data,0x0,sizeof(send_data));
		 //判断当前服务器是否有
		if (!PathFileExists(wave_path))
		{
			swprintf(send_data,L"Message&DOWN_FILE_FROM_BOX;GET_MP3_DOWN:%s",down_mp3_path);
			WriteLog(__FL__, L"服务器上没有这首歌，要进行下载：");
			WriteLog(__FL__, send_data);

			//下载数据服务端
			send_data_to_service_udp(send_data);
		}

		if (!priority)
		{ 
			//查看是否存在
			result = m_video_play_manager.query_select_song_by_id(m_maiba_song_info[nPos_number].voice_id,play_number);

			if (result && repeat_select_song(m_maiba_song_info[nPos_number].voice_id,page_index))
			{
				//不让重复点歌
				return;
			} 
		}

		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(song_info_class,priority);
		if (!result)
		{
			return;
		}

		//添加
		repeat_select_song(m_maiba_song_info[nPos_number].voice_id,page_index); 
		show_song_name();
	}
	catch (...)
	{
		
	}
	
	return;
}

void Cflashktv10Wnd::flash_message_call_music_enjoy(int page_code, const TCHAR *args){
	try
	{
		song_info song_info_class; 
		string_conversion string_conv;
		if (args==NULL)
		{
			return;
		}

		int index = -1;
		char szIndex[16] = {0x00};
		string_conv.widechar_to_multibyte(args, szIndex, 16);
		sscanf(szIndex, "%d", &index);

		if (index >= 100 || index < 0)
		{
			return;
		}

		ST_MUSIC_ENJOY stme = m_music_enjoy[index];

		song_info_class.set_song_id(stme.song_id);
		song_info_class.set_singer_name(stme.singer_name);
		song_info_class.set_singer_id1(stme.singer_id);
		song_info_class.set_song_name(stme.song_name);
		song_info_class.set_song_relative_path(stme.song_cloud_path);
		song_info_class.set_song_bk_path(stme.song_bk_path);
		song_info_class.set_music_enjoy(1);
		song_info_class.set_video_type(PLAY_MUSIC_ENJOY);
		
		switch(stme.song_type){
			case 1001: //百度音乐
				song_info_class.set_song_version(L"13");
				song_info_class.set_song_type(L"1001");
				break;
			case 1002: //QQ音乐
				song_info_class.set_song_version(L"14");
				song_info_class.set_song_type(L"1002");
				break;
			case 1003: //酷狗音乐
				song_info_class.set_song_version(L"15");
				song_info_class.set_song_type(L"1003");
				break;
			case 1004: //酷我音乐
				song_info_class.set_song_version(L"16");
				song_info_class.set_song_type(L"1004");
				break;
		}

		//根据播放器状态，播放或插入已选歌曲中
		bool result = play_or_insert_select_list(song_info_class,false);
		if (!result)
		{
			return;
		}
		//发码给flash
		flash_message_call_music_enjoy_data(page_code, false);
		//重新显示上下首歌名
		show_song_name();
	}
	catch (...)
	{
	}

	return;
}

bool Cflashktv10Wnd::flash_message_call_select_film()
{
	//获取电影信息
	access_record_set_sql *pFilmInfo = m_film_manager.get_film_by_id(m_film_manager.m_strfilm_id_current.c_str());
	if(pFilmInfo == NULL)
		return false;

	//生成电影信息
	song_info song;
	song.set_song_id(pFilmInfo->GetRecordData(L"film_id"));
	song.set_song_name(pFilmInfo->GetRecordData(L"film_name"));
	song.set_server_path1(pFilmInfo->GetRecordData(L"server_path1"));
	song.set_server_path2(pFilmInfo->GetRecordData(L"server_path2"));
	song.set_server_path3(pFilmInfo->GetRecordData(L"server_path3"));
	song.set_song_relative_path(pFilmInfo->GetRecordData(L"movie_relative_path"));
	CString csActorName = pFilmInfo->GetRecordData(L"film_director");
	song.set_singer_name(m_film_manager.ActorToString(csActorName));
	song.set_video_type(PLAY_MOVIE);
	bool result = play_or_insert_select_list(song,false);
	
	refresh_screen_list();

	//释放
	delete pFilmInfo;
	pFilmInfo = NULL;

	return result;

}

void Cflashktv10Wnd::flash_message_call_select_song(const TCHAR *args,bool priority,bool singed_page,bool priority_type,int number_type)
{
	try
	{
		int number=0;
		song_info song_info_class;
		bool result=false;
		int select_song_count=0;
		TCHAR song_id[128];
		TCHAR wave_path[256];
		int play_number=0;
		int  page_index=0;
		TCHAR song_local_path[256];   //得到当前歌曲的状态 0：本地歌曲  1：下载歌曲  2：更新歌曲
		 
		memset(song_id,0x0,sizeof(song_id));
		memset(wave_path,0x0,sizeof(wave_path));
		memset(song_local_path,0x0,sizeof(song_local_path));

		page_index = m_flash_manage.get_last_page_index();

		if (args==NULL)
		{
			return;
		}
		
		// mod by yzg 2015-12-05
		select_song_count = m_video_play_manager.get_select_song_count(0);
		if (select_song_count>=SELECT_SONG_MAX_COUNT)
		{
			flash_show_tip_message(25);
			return;
		}

		//得到选择的编号
		swscanf(args,L"%d",&number);
		if ((number<0)||(number>=m_page_show_row_count))
		{
			return;
		}

		if (singed_page)   //已唱页面
		{
			//得到选中的歌曲
			result = m_video_play_manager.get_sing_song_information(song_info_class,number,true);
			if (!result)
			{
				return;
			}
		}
		else
		{
			//这里不要清空查询条件，因为上下翻页还用，下次检索时在清空
			//清空字母显示窗口
			show_letter_window(L"");
			//调用智能拼音,让所有字符都可以查询
			flash_yinpin_show_all_letter();
			//清空手写选择的歌词
			m_ink_song_lyric.clear();
			//清空选择的字
			clear_handwriting_select_word();
			//清空手写的字
			clear_handwriting_recognizer_word();
			for (int i=0;i<INK_RECOGNIZE_ALTERNATE_NUMS;i++)
			{
				m_recognition_result[i].Empty();
			}		
			//清空手写区域
			m_handwriting_window.clear_ink_window();

			//得到选中的歌曲信息
			result = m_query_song_manager.get_song_info(number,song_info_class);
			//result = get_song_info_by_id(args,song_info_class,PLAY_SONG_TYPE_SELECT_SONG);
			if (!result)
			{
				return;
			}
		}			

		//表示用户已经选择过歌曲了，下次查询前要清空条件
		m_user_select_song = true;
		
		//得到歌曲编号
		result = song_info_class.get_song_id(song_id); 

		//得到推荐歌曲 //yzg
		if (!priority_type)
		{ 
			//推送歌曲不进行歌曲推荐
			if(!priority)
			{
				//点歌时出现推荐
				memset(m_recommedn_song_id,0x0,sizeof(m_recommedn_song_id));
				_tcscpy(m_recommedn_song_id,song_id);
				m_bBubble = true;
				AfxBeginThread(Cflashktv10Wnd::query_recommend_song_thread,(LPVOID)this);
			}
		}

		//设置歌曲从哪个页面来
		song_info_class.set_flash_page_code(page_index);
		
		//判断是否是录音页面
		if (page_recording == page_index)
		{
			//得到当前存储的路径
			song_info_class.get_wave_path(wave_path);
			if (!PathFileExists(wave_path) && m_master_slave_control_flag != 2)
			{ 
				flash_show_tip_message(115);
				return;
			}
		}

		//得到本地是否有这首歌曲
		song_info_class.get_local_path(song_local_path);
		if (0==_tcscmp(song_local_path,L"1"))
		{
			//需要下载当前歌曲
			dwon_song_file_to_server(song_id,1);

			///标示为下载歌曲
			song_info_class.set_down_update_song(1);
		}
		else if (0 == _tcscmp(song_local_path,L"2"))
		{
			if (2 == number_type)
			{
				//需要下载当前歌曲
				dwon_song_file_to_server(song_id,2);

				song_info_class.set_down_update_song(2);
			}			
		}	
		
		if (!priority)
		{ 
			//查看是否存在
			result = m_video_play_manager.query_select_song_by_id(song_id,play_number);
#ifdef DON_GUAN_K_PLUS
			if (result && !m_allow_repeat_select_song)
			{
				//保存基本信息
				m_select_song_info=song_info_class;
				m_select_song_priority=priority;
				m_select_song_number = number;
				//存在，显示复选提示
				show_check_window(true);
				return;
			}
#endif // DON_GUAN_K_PLUS
			
			 //可以选择多次
			/*
			if (result && repeat_select_song(song_id,page_index))
			{
				//不让重复点歌
				return;
			}
			*/

			///切换页面时
			/*
			if (m_select_page_index != page_index)
			{
				m_allow_repeat_select_song = false;
				//存在，允许重复选歌，必须要切换页面
				if (result && !m_allow_repeat_select_song)
				{
					//保存基本信息
					m_select_song_info=song_info_class;
					m_select_song_priority=priority;
					m_select_song_number = number;
					//存在，显示复选提示
					show_check_window(true);

					return;
				}
			}
			else
			{
				if (!m_allow_repeat_select_song)
				{
					return;
				}
			}
			*/
		}

		//判断是否给对方同步歌曲
		if (m_b_pk_connect)
		{
			//发送消息给连接的ip
			TCHAR send_ip[256]; 
			TCHAR send_sync_songs[256];
		 
			if (0 != _tcscmp(m_pk_invitationIP,L""))
			{
				_tcscpy(send_ip,m_pk_invitationIP);
			}
			if (0 != _tcscmp(m_pk_acceptIP,L""))
			{
				_tcscpy(send_ip,m_pk_acceptIP);
			}
			//m_query_song_manager.get_song_info(number,song_info_class);

			//得到歌曲编号
			song_info_class.get_song_id(song_id);
			if (priority)
			{
				_tcscpy(send_sync_songs,_T("priority_song1"));   //优先其他歌曲
			}
			else
			{
				_tcscpy(send_sync_songs,_T("sync_songs"));
			}
			_tcscat(send_sync_songs,song_id);
			connect_inviation(send_ip,send_sync_songs);  //同步点歌
		}

		//显示选歌动画
		//show_select_song_animation();

		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(song_info_class,priority);

		if (!result)
		{
			return;
		}

		TCHAR msg[MAX_PATH] = {0x00};
		TCHAR song_path[MAX_PATH] = {0x00};
		song_info_class.get_song_relative_path(song_path);
		swprintf(msg, L"插入到已选歌曲成功 path = %s", song_path);
		WriteLog(__FL__, msg);
		
		//添加
		repeat_select_song(song_id,page_index);
		
		//得到显示的编号，然后改变显示颜色，必须先把歌曲插入已选中，然后在改变颜色，因为涉及到刷屏
		chang_select_song_color(song_info_class,number,priority);
		//重新显示上下首歌名
		show_song_name();
		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_message_call_U_disk_select_song(const TCHAR *args)
{
	try
	{
		int number=0;
		int select_song_count=0;
		song_info U_disk_song_info;
		bool result=false;
		TCHAR song_id[128];
		int play_number=0;

		memset(song_id,0x0,sizeof(song_id));

		U_disk_song_info.initialized_variables();

		//得到已经选择的歌曲数
		select_song_count = m_video_play_manager.get_select_song_count();
		if (select_song_count>=SELECT_SONG_MAX_COUNT)
		{
			flash_show_tip_message(25);
			return;
		}

		//得到选择的编号
		swscanf(args,L"%d",&number);
		if ((number<0)||(number>=m_page_show_row_count))
		{
			return;
		}

		//得到选中的歌曲信息
		result = m_play_U_disk_song.get_U_disk_song_info(U_disk_song_info,number);
		if(!result)
		{
			return;
		}
		//表示用户已经选择过歌曲了，下次查询前要清空条件
		m_user_select_song = true;

		//得到歌曲编号
		result = U_disk_song_info.get_song_id(song_id);
		//查看是否存在
		result = m_video_play_manager.query_select_song_by_id(song_id,play_number);
		if (result && !m_allow_repeat_select_song)
		{
			//保存基本信息
			m_select_song_info=U_disk_song_info;
			m_select_song_priority=true;
			m_select_song_number = number;
			//存在，显示复选提示
			show_check_window(true);

			return;
		}

		//显示选歌动画
		//show_select_song_animation();

		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(U_disk_song_info,true);
		if (!result)
		{
			return;
		}
		//必须先把歌曲插入已选中，然后在改变颜色，因为涉及到刷屏
		//由于U盘播放歌曲不同于其他页面，所以直接刷屏
		refresh_screen_list();
		//重新显示上下首歌名
		show_song_name();

	}
	catch (...)
	{
		
	}
	return;
}

bool Cflashktv10Wnd::play_or_insert_select_list(song_info &song_information,bool priority,bool recv_msg)
{
	try
	{
		enum PLAYER_PLAY_STATE player_state;
		int select_song_count=0;
		bool result=false;
		TCHAR song_id[128];
		TCHAR send_data[1024];
		PLAY_SONG_TYPE video_type;
		TCHAR select_type[256];
		int link_server_number=0;
		bool is_muisc_enjoy = false;

		memset(song_id,0x0,sizeof(song_id));
		memset(send_data,0x0,sizeof(send_data));
		memset(select_type,0x0,sizeof(select_type));

		//得到选择的视频类型
		video_type = song_information.get_video_type();
		if (PLAY_MOVIE==video_type)
		{
			//电影
			_tcscpy(select_type,L"M");
		}
		else if (PLAY_MUSIC_ENJOY == video_type)
		{
			//音乐欣赏
			is_muisc_enjoy = true;
			ST_MUSIC_ENJOY stme;
			song_information.get_song_id(stme.song_id);
			song_information.get_song_name(stme.song_name);
			song_information.get_singer_id1(stme.singer_id);
			song_information.get_singer_name(stme.singer_name);
			song_information.get_song_relative_path(stme.song_cloud_path);
			song_information.get_song_bk_path(stme.song_bk_path);//add by yzg 2015-12-08 背景视频
			TCHAR value_version[MAX_PATH] = {0x00};
			int version = -1;
			song_information.get_song_version(value_version, version);
			TCHAR value_song_type[MAX_PATH] = {0x00};
			song_information.get_song_type(value_song_type);
			swprintf(send_data,L"SELECTSONG&1&%s&%s&%s&%s&%s&%s&%d&%s", stme.song_id, stme.song_name, stme.singer_id, stme.singer_name,
								stme.song_cloud_path, stme.song_bk_path, version, value_song_type);
		}else if (PLAY_SONG_TYPE_RECORDER_SONG == video_type)
		{
			//电影
			_tcscpy(select_type,L"R");
		}else
		{
			//歌曲
			_tcscpy(select_type,L"S");
		}

		if (!recv_msg && 1==m_master_slave_control_flag)
		{
			//主控机
			if (is_muisc_enjoy)
			{				
				send_master_slave_data(send_data,NULL);
			}else{				
				result = song_information.get_song_id(song_id);
				if (result)
				{
					if (priority)
					{
						//优先
						swprintf(send_data,L"SELECTSONG%s1%s",select_type,song_id);
					}
					else
					{
						swprintf(send_data,L"SELECTSONG%s0%s",select_type,song_id);
					}
					send_master_slave_data(send_data,NULL);
				}
			}
		}
		else if (!recv_msg && (2==m_master_slave_control_flag))
		{
			//被控机，客户点击的
			if (is_muisc_enjoy)
			{
				send_master_slave_data(send_data,NULL);
			}else{
				result = song_information.get_song_id(song_id);
				if (result)
				{
					if (priority)
					{
						//优先
						swprintf(send_data,L"SELECTSONG%s1%s",select_type,song_id);
					}
					else
					{
						swprintf(send_data,L"SELECTSONG%s0%s",select_type,song_id);
					}
					send_master_slave_data(send_data,NULL);
				}
			}
			//空闲歌曲改为false//防止被控点第一首歌曲切歌
			m_idless_song_switching = false;

			//返回false，就不在改变颜色，等被控机接受到数据之后直接刷屏
			//return false; 被控机需要播放录音
		}

		//得到目前系统所处的状态
		player_state = m_video_play_manager.get_player_cur_state();
		result = m_player_manager.is_play_video_ad();
		if (result)
		{
			//如果现在是播放广告状态，需要判断是否可以切换
			result = m_video_play_manager.video_allow_cut();
			if (!result)
			{
				//不允许切换，改变状态
				player_state = PLAY_SONG_STATE;
			}
			else
			{
				//允许切，改变状态
				player_state = IDLESSE_STATE;
			}
		}
		if ((VIDEO_TYPE_LOBBY_LIVE==tv_play_video_type)||(VIDEO_TYPE_TV==tv_play_video_type))
		{
			//如果现在是大厅或电视直播，不能切掉
			player_state = PLAY_SONG_STATE;
		}
		//得到正播放歌曲的视频类型
		video_type = m_player_manager.get_playing_video_type();
		if (PLAY_MSG_VIDEO_FIRE_ALARYM==video_type)
		{
			//如果现在是火警，不能切掉
			player_state = PLAY_SONG_STATE;
		}

		//如果正在播放用户点的歌曲，那么把该歌曲放到已选歌曲中
		result = m_video_play_manager.add_select_song(song_information,priority);
		if (!result)
		{
			return false;
		}

		//改变播放器的状态
		result = m_video_play_manager.set_player_next_state(PLAY_SONG_STATE);
		//更新选择的歌曲数目
		result = update_select_song_count();
		//同步已选列表
		if (m_master_slave_control_flag == 1)
		{
			TCHAR syn_song_id[1024*50] = {0x00};
			//得到播放器的下一个状态
			enum PLAYER_PLAY_STATE player_next_state = m_video_play_manager.get_player_next_state();
			result = get_select_song_number(syn_song_id);

			if (result && (0!=_tcscmp(syn_song_id,L"")))
			{
				//同步已选歌曲
				swprintf(send_data,L"SYN_SELECT_SONG%d$%s",player_next_state,syn_song_id);
			}
			else
			{
				//发送给被控机当前空闲歌曲的索引
				int index = m_video_play_manager.get_cur_idlesse_video_number(); //空闲的索引
				swprintf(send_data, L"SET_IDLESSE_INDEX&%d", index);
				//发送给被控机
				send_master_slave_data(send_data,NULL);

				//没有已选歌曲就不用同步
				swprintf(send_data,L"SYN_SELECT_SONG%d",player_next_state);
			}
			//发送给被控机
			send_master_slave_data(send_data,NULL);
		}
		//如果当前歌曲时空闲歌曲，并且点了云歌曲，则不跳歌
		TCHAR local_path[MAX_PATH] = {0x00};
		song_information.get_local_path(local_path);
		if (_tcscmp(local_path, L"1") == 0 && player_state == IDLESSE_STATE)
		{
			return true;
		}
		//如果当前歌曲是空闲歌曲，并且是空闲状态，则不跳歌
		bool bPlaying = m_player_manager.is_playing();
		if (!bPlaying && player_state == IDLESSE_STATE)
		{
			return true;
		}

		switch(player_state)
		{
		default:
		case BEGIN_STATE:
		case END_STATE:
		case IDLESSE_STATE:
			{
				/*
				CTime cur_time = CTime::GetCurrentTime();

				//系统目前处于空闲状态，那么开始播放用户点的歌曲
				link_server_number = m_link_server_number;
				memset(m_music_wave_path,0x0,sizeof(m_music_wave_path));
				memset(m_voice_wave_path,0x0,sizeof(m_voice_wave_path));
				if (m_need_record_flag)  //增加判断 FOR ZHEN 2013-05-29
				{
					swprintf(m_music_wave_path,L"%s\\log\\shplayer-%02d%02d%02d.log",m_work_path,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
					if (m_set_free_pk)
					{
						//只要开启自由pk，都保存到服务器路径
						swprintf(m_voice_wave_path,L"%s\\%s-%02d%02d%02d.wav",m_recorder_web_dir.c_str(),m_show_room_name,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
					} 
					else if (m_set_dekaron_pk)
					{
						//如果只有擂台pk时，只有歌曲id相同的才能保存到服务器上
						memset(song_id,0x0,sizeof(song_id));
						song_information.get_song_id(song_id);
						if (0 == _tcscmp(song_id,m_maiba_rule_arena_info[1].song_id))
						{
							swprintf(m_voice_wave_path,L"%s\\%s-%02d%02d%02d.wav",m_recorder_web_dir.c_str(),m_show_room_name,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
						}
						else
						{
							swprintf(m_voice_wave_path,L"%s\\%s-%02d%02d%02d.wav",m_recorder_dir.c_str(),m_show_room_name,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
						}	
					}
					else
					{
						swprintf(m_voice_wave_path,L"%s\\%s-%02d%02d%02d.wav",m_recorder_dir.c_str(),m_show_room_name,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
					}		
					//swprintf(m_music_wave_path,L"%s\\log\\shplayer-%02d%02d%02d.log",m_work_path,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
					//swprintf(m_voice_wave_path,L"%s\\%s-%02d%02d%02d.wav",m_recorder_dir.c_str(),m_show_room_name,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
				}
				result = m_player_manager.set_video_file(song_information,link_server_number,m_music_wave_path,m_voice_wave_path,m_is_scoring);
				if (result)
				{
					//改变播放器的状态
					result = m_video_play_manager.set_player_cur_state(PLAY_SONG_STATE);
					//设置正在播放的视频
					result = m_video_play_manager.set_playing_video(song_information);
					//改变连接服务器编号
					change_link_server_number(link_server_number);
				}
				else
				{
					//改变播放器状态,设置为播放歌曲状态，防止快速点击
					result = m_video_play_manager.set_player_next_state(PLAY_SONG_STATE);
					//设置失败，播放下一首，必须用postmessage()函数
					PostMessage(WM_PLAYER_NOTIFY,PN_MEDIA_PLAY_FINISHED,NULL);
				}
				//把该歌曲放到已唱歌曲中
				m_video_play_manager.add_sing_song(song_information);
				*/

				//只有在空闲歌曲的时候，才会切歌-------By_v.cai_2015/02/05 15:26
				if (m_idless_song_switching || m_b_challenging)
				{
					if (song_information.get_video_type() == PLAY_SONG_TYPE_RECORDER_SONG)
					{
						flash_message_call_function(SONG_NEXT, 0, true);
					}else{
						flash_message_call_function(SONG_NEXT);
					}					
					m_idless_song_switching = true;
				}		
			}
			break;
		case PLAY_SONG_STATE:
		case TEST_SONG_STATE:
			{
				/*
				//如果正在播放用户点的歌曲，那么把该歌曲放到已选歌曲中
				result = m_video_play_manager.add_select_song(song_information,priority);
				if (!result)
				{
					return false;
				}
				//改变播放器的状态
				result = m_video_play_manager.set_player_next_state(PLAY_SONG_STATE);
				//更新选择的歌曲数目
				result = update_select_song_count();
				*/
			}
			break;
		case PLAY_DJ_STATE:  //播放DJ
			{
				//如果正在播放DJ歌曲，那么把该歌曲放到已选歌曲中
				result = m_video_play_manager.add_select_song(song_information,priority);
				if (!result)
				{
					return false;
				}
				//更新选择的歌曲数目
				result = update_select_song_count();
			}
			break;
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::send_socre_data_to_room_udp(int score,song_info &video_info)
{
	try
	{
		BOOL opt=true;
		int iTimeOut = 60000;
		int tRet;
		char send_data[1024];
		TCHAR msg_data[1024];
		TCHAR song_name[256];
		TCHAR singer_name[256];
		std::wstring broadcase_score;

		string_conversion string_conv;
		config_file_manager config_file;

		memset(send_data,0x0,sizeof(send_data));
		memset(song_name,0x0,sizeof(song_name));
		memset(singer_name,0x0,sizeof(singer_name)); 

		//创建套节字
		SOCKET  send_socket = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		if (send_socket == INVALID_SOCKET)
		{
			return ;
		}

		//得到歌曲名称和歌星名称
		video_info.get_song_name(song_name);
		video_info.get_singer_name(singer_name);
		/*
		60-65  唱的还可以哦！还需要再努力一点！
		65-70  唱的不错呢！要继续加油啊！
		70-75  唱的很好啦！有人能超越他么？
		75-80  唱的太好了！有没有人发起挑战？
		80-85  唱的非常好！传说中的麦霸现身了！
		85-90  唱的如此动听！余音绕梁有木有？
		90-95  唱的太给力了！有种独孤求败的感觉！
		95-100 唱的近乎完美！是歌神来了吗？
		*/

		//得到评语的语句
		if (score>=95)
		{
			broadcase_score = config_file.read_string(L"broadcase_score",L"score_95",L"唱的近乎完美！是歌神来了吗？");
		}
		else if (score >= 90)
		{
			broadcase_score = config_file.read_string(L"broadcase_score",L"score_90",L"唱的太给力了！有种独孤求败的感觉！");
		}
		else if (score >= 85)
		{
			broadcase_score = config_file.read_string(L"broadcase_score",L"score_85",L"唱的如此动听！余音绕梁有木有？");
		}
		else if (score >= 80)
		{
			broadcase_score = config_file.read_string(L"broadcase_score",L"score_80",L"唱的非常好！传说中的麦霸现身了！");
		}
		else if (score >= 75)
		{
			broadcase_score = config_file.read_string(L"broadcase_score",L"score_75",L"唱的太好了！有没有人发起挑战？");
		}
		else if (score >= 70)
		{
			broadcase_score = config_file.read_string(L"broadcase_score",L"score_70",L"唱的很好啦！有人能超越他么？");
		}
		else if (score >= 65)
		{
			broadcase_score = config_file.read_string(L"broadcase_score",L"score_65",L"唱的不错呢！要继续加油啊！");
		}
		else if (score >= 60)
		{
			broadcase_score = config_file.read_string(L"broadcase_score",L"score_60",L"唱的还可以哦！还需要再努力一点！");
		}

		//设置该套接字为广播类型，
		tRet = ::setsockopt(send_socket,SOL_SOCKET,SO_BROADCAST,(char FAR *)&opt,sizeof(opt));
		if (tRet != 0)
		{
			return;
		}
		//设置接受超时
		::setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(char *)&iTimeOut,sizeof(iTimeOut));

		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;
		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		//填写远程地址
		sockaddr_in ServerAddr;
		ServerAddr.sin_family = AF_INET;
		ServerAddr.sin_port = htons(6000);
		//本网络的广播地址
		ServerAddr.sin_addr.S_un.S_addr = INADDR_BROADCAST;
	
		swprintf(msg_data,L"PLACENOTICE: %s包房刚刚唱了【%s】(原唱%s)最终得分！%s",m_show_room_name,song_name,singer_name,broadcase_score.c_str());

		string_conv.widechar_to_multibyte(msg_data,send_data,sizeof(send_data));
		
		//发送数据
		::sendto(send_socket,send_data,strlen(send_data)*sizeof(char),0,(sockaddr*)&ServerAddr,sizeof(ServerAddr));
		//关闭socket
		::closesocket(send_socket);
	}
	catch (...)
	{
		
	} 

	return;
}

void Cflashktv10Wnd::send_data_to_service_udp(TCHAR *data)
{
	try
	{
		if ((NULL==data)||(0==strcmp(m_service_server_ip,"")))
		{
			return;
		}

		struct linger zerolinger;
		int nSendTimeout = 6000;
		bool result=false;

		SOCKET send_socket = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		if (send_socket<0)
		{
			//创建socket失败
			return;
		}

		//设置socket属性
		zerolinger.l_onoff = 1;
		zerolinger.l_linger = 5;
		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));

		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&nSendTimeout,sizeof(nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in service_addr;
		service_addr.sin_family = AF_INET;
		service_addr.sin_addr.S_un.S_addr = inet_addr(m_service_server_ip);
		service_addr.sin_port = htons(62425);

		size_t len = _tcslen(data)*sizeof(TCHAR);

		//发送数据
		len = ::sendto(send_socket,(char *)data,len,0,(sockaddr *)&service_addr,sizeof(service_addr));
		if(len>0)
		{
			//发送成功
		}
		//关闭socket
		::closesocket(send_socket);
		send_socket = -1;

	}
	catch (...)
	{
		
	}
	return;
}


void Cflashktv10Wnd::flash_message_call_change_handwriting_language(const TCHAR *args)
{
	try
	{
		int language=0;

		swscanf(args,L"%d",&language);

		switch(language)
		{
		case 1:  //简体中文
			{
				m_handwriting_window.change_ink_recognize_language(INK_RECOGNIZER_LANGUAGE_SIMPLIFIED_CHINESE);
				m_handwriting_window.clear_ink_window();
				//语言按钮编号
				m_ink_language_button_number = 0;
			}
			break;
		case 2:  //英
			{
				m_handwriting_window.change_ink_recognize_language(INK_RECOGNIZER_LANGUAGE_US_ENGLISH);
				m_handwriting_window.clear_ink_window();
				//语言按钮编号
				m_ink_language_button_number = 3;
			}
			break;
		case 3:  //韩
			{
				m_handwriting_window.change_ink_recognize_language(INK_RECOGNIZER_LANGUAGE_KOREA);
				m_handwriting_window.clear_ink_window();
				//语言按钮编号
				m_ink_language_button_number =1;
			}
			break;
		case 4:  //日
			{
				m_handwriting_window.change_ink_recognize_language(INK_RECOGNIZER_LANGUAGE_JAPANESE);
				m_handwriting_window.clear_ink_window();
				//语言按钮编号
				m_ink_language_button_number = 2;
			}
			break;
		default:
			{
				if (language>100)
				{
					language-=100;
				}
				m_handwriting_window.change_ink_recognize_language(language);
				m_handwriting_window.clear_ink_window();
				//语言按钮编号
				m_ink_language_button_number = 0;
			}
			break;
		}

		//设置按钮状态，进入的时候设置一次就行了。点击之后，有flash记录
		send_ink_language_button_state();

		return;
	}
	catch (...)
	{

	}
	return;
}
//
//void Cflashktv10Wnd::flash_message_call_change_handwriting_language(const TCHAR *args)
//{
//	try
//	{
//		int language=0;
//		int MajorVersion=0;
//
//		swscanf(args,L"%d",&language);
//
//		//得到window的主版本号
//		MajorVersion = m_window_version.GetMajorVersion();
//
//		switch(language)
//		{
//		case 1:  //简体中文
//			{
//				m_handwriting_window.change_ink_recognize_language(INK_RECOGNIZER_LANGUAGE_SIMPLIFIED_CHINESE);
//				m_handwriting_window.clear_ink_window();
//				//语言按钮编号
//				m_ink_language_button_number = 0;
//			}
//			break;
//		case 2:  //英
//			{
//				m_handwriting_window.change_ink_recognize_language(INK_RECOGNIZER_LANGUAGE_US_ENGLISH);
//				m_handwriting_window.clear_ink_window();
//				//语言按钮编号
//				m_ink_language_button_number = 1;
//			}
//			break;
//		case 3:  //韩
//			{
//				m_handwriting_window.change_ink_recognize_language(INK_RECOGNIZER_LANGUAGE_KOREA);
//				m_handwriting_window.clear_ink_window();
//				//语言按钮编号
//				m_ink_language_button_number = 2;
//			}
//			break;
//		case 4:  //日
//			{
//				m_handwriting_window.change_ink_recognize_language(INK_RECOGNIZER_LANGUAGE_JAPANESE);
//				m_handwriting_window.clear_ink_window();
//				//语言按钮编号
//				m_ink_language_button_number = 3;
//			}
//			break;
//		default:
//			{
//				if (language>100)
//				{
//					language-=100;
//				}
//				m_handwriting_window.change_ink_recognize_language((enum INK_RECOGNIZER_LANGUAGE)(language));
//				m_handwriting_window.clear_ink_window();
//				//语言按钮编号
//				m_ink_language_button_number = 0;
//			}
//			break;
//		}
//		//设置按钮状态，进入的时候设置一次就行了。点击之后，有flash记录
//		send_ink_language_button_state();
//
//		return;
//	}
//	catch (...)
//	{
//
//	}
//	return;
//}

void Cflashktv10Wnd::send_ink_language_button_state(void)
{
	try
	{
		TCHAR request[256];
		TCHAR data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		swprintf(data,L"%d",m_ink_language_button_number);

		//改变手写语言的高亮状态
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"ink_language_button",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch (...)
	{

	}
	return;
}
void Cflashktv10Wnd::flash_message_call_www_music(const TCHAR *preview_path)
{
	bool result=false;
	//改变到预览页面
	result = page_change(page_phone_push_preview);
	if (!result||!m_preview_window_exist)
	{
		return;
	}
	//关闭预览
	m_player_manager.preview_close();
	//打开预览，播放预览视频
	m_player_manager.preview_open(preview_path,(long)(m_preview_window.m_hWnd));
	//设置声道
	m_player_manager.preview_control(PVC_SET_INIT_AUDIO,-1,0);
	//移动窗口位置
	//m_preview_window.MoveWindow(CRect(m_preview_left_top_x,m_preview_left_top_y,m_preview_right_bottom_x,m_preview_right_bottom_y),TRUE);
	//现在先隐藏，打开成功之后在显示，主要是为了显示背景
	m_preview_window.show_window(true);

	//preview_screen_show_video_window();
}
void Cflashktv10Wnd::flash_message_call_preview_song(const TCHAR *args)
{
	try
	{
		int preview_number=0;
		bool result=false;
		TCHAR preview_path[1024]; //预览歌曲路径
		TCHAR song_name[256];
		TCHAR singer_name[256];
		TCHAR song_id[128];
		TCHAR request[10*1024];
		TCHAR lyric_path[256];
		TCHAR lyric_index_path[256];
		TCHAR song_lyric[10*1024];
		TCHAR lyric_data[10*1024];
		byte song_channel=-1;
		int page_index=0;
		TCHAR show_song_name[256];
		int link_server_number=0;

		memset(show_song_name,0x0,sizeof(show_song_name));
		memset(preview_path,0x0,sizeof(preview_path));
		memset(song_name,0x0,sizeof(song_name));
		memset(request,0x0,sizeof(request));
		memset(song_id,0x0,sizeof(song_id));
		memset(lyric_path,0x0,sizeof(lyric_path));
		memset(lyric_index_path,0x0,sizeof(lyric_index_path));
		memset(song_lyric,0x0,sizeof(song_lyric));
		memset(lyric_data,0x0,sizeof(lyric_data));
		memset(singer_name,0x0,sizeof(singer_name));

		swscanf(args,L"%d",&preview_number);

		//得到页面索引
		page_index = m_flash_manage.get_last_page_index();
		//switch(page_index)
		//{
		//case page_selected:   //选择的歌曲
		//	{
		//		result = m_video_play_manager.get_select_song_information(m_preview_song_info,preview_number,true);
		//		if (!result)
		//		{
		//			return;
		//		}
		//	}
		//	break;
		//case page_singed:   //已唱的歌曲
		//	{
		//		result = m_video_play_manager.get_sing_song_information(m_preview_song_info,preview_number,true);
		//		if (!result)
		//		{
		//			return;
		//		}
		//	}
		//	break;
		//default:
		//	{
		//		result = m_query_song_manager.get_song_info(preview_number,m_preview_song_info);
		//		if (!result)
		//		{
		//			return;
		//		}
		//		
		//	}
		//	break;
		//}

		//result = get_song_info_by_id(args,m_preview_song_info,PLAY_SONG_TYPE_SELECT_SONG);
		result = m_query_song_manager.get_song_info(preview_number,m_preview_song_info);
		if (!result)
		{
			return;
		}
		//首先选择预览路径
		result = m_preview_song_info.get_preview_path(preview_path);
		if (0==_tcscmp(preview_path,L""))
		{
			if (m_preview_allow_play_song_db)
			{
				//预览路径不存在，选择服务器路径
				link_server_number = m_link_server_number;
				result = m_preview_song_info.get_path(preview_path,m_check_video_file_exist,link_server_number);
				if (0==_tcscmp(preview_path,L""))
				{
					flash_show_tip_message(31);
					return;
				}
			}
			else
			{
				//预览路径不存在直接返回
				flash_show_tip_message(31);
				return;
			}			
		}

		//改变到预览页面
		result = page_change(page_preview);
		if (!result||!m_preview_window_exist)
		{
			return;
		}
		//得到预览声道
		m_preview_song_info.get_preview_channel_track(true,song_channel);
		if (VIDEO_TYPE_SONG!=pc_play_video_type)
		{
			//pc端播放的视频类型不是歌曲，返回到歌曲
			switch_screen_play_song_video();
		}
		//关闭预览
		m_player_manager.preview_close();
		//打开预览，播放预览视频
		m_player_manager.preview_open(preview_path,(long)(m_preview_window.m_hWnd));
		//设置声道
		m_player_manager.preview_control(PVC_SET_INIT_AUDIO,song_channel,0);
		//移动窗口位置
		//m_preview_window.MoveWindow(CRect(m_preview_left_top_x,m_preview_left_top_y,m_preview_right_bottom_x,m_preview_right_bottom_y),TRUE);
		//现在先隐藏，打开成功之后在显示，主要是为了显示背景
		m_preview_window.show_window(false);
		//显示歌词
		result = m_preview_song_info.get_song_id(song_id);
		if (result)
		{
			result = m_lyricSrarch.SearchLyric(song_id,song_lyric);
			if (result)
			{
				//删除歌词中的双引号
				song_lyric_replace(song_lyric);
				memset(request,0x0,sizeof(request));
				swprintf(lyric_data,L"<data><info lyric=\"%s\"/></data>",song_lyric);
				result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"lyric_show",lyric_data);
				if (result)
				{
					flash_player_call_function(request);
				}
			}
		}

		//显示预览歌曲的名字
		result = m_preview_song_info.get_song_name(song_name);
		if (result)
		{
			memset(request,0x0,sizeof(request));

			//get singer name
			result = m_preview_song_info.get_singer_name(singer_name);
			if (!result)
			{
				memset(singer_name,0x0,sizeof(singer_name));
			}

			swprintf(show_song_name,L"<data><info song_name=\"%s\" singer_name=\"%s\" /></data>",song_name,singer_name);
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"previewSongName",show_song_name);
			if (result)
			{
				flash_player_call_function(request);
			}
		}
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::decrypt_song_lyric(const TCHAR *in_lyric_path,const TCHAR *in_lyric_index_path,const TCHAR *in_song_id,TCHAR *out_lyric)
{
	try
	{
		//6组密钥
		char all_key[6][24]=  {
			{30,-84,58,37,95,57,41,35,-122,-45,-55,-21,13,-50,-127,-41,-22,-53,52,98,-87,-59,-64,-34},
			{-122,96,-114,-62,-111,89,126,-44,84,57,30,24,-100,-13,-20,104,29,10,58,13,15,44,59,-28},
			{-82,123,-117,-82,-83,-44,94,-4,60,61,84,95,-25,-12,98,69,-26,62,-86,29,-11,80,-78,77},
			{126,-109,-37,105,33,-101,-118,92,78,-11,-31,-42,35,77,125,-56,21,-26,8,46,-77,16,41,-16},
			{26,109,-96,56,42,-50,0,-46,97,119,-26,39,61,108,53,72,3,-36,-5,-97,-18,17,-53,-38},
			{-101,2,3,100,-111,25,-61,68,-27,20,88,-104,-29,-87,101,127,112,-22,-9,-82,99,-30,-82,-25},
		};
		//文件每个字节的意思：第几个加密算法，密钥多少位，实际使用的密钥位数，年份，月份，最后是三个字节的随即位
		unsigned char szFileHead[8];
		FILE *fp=NULL;
		FILE *fp_index=NULL;
		unsigned char pDataBuffer[200*1024];
		const char *song_number=NULL;
		const char *offset=NULL;
		char key[24];
		int offset_start=0;
		int song_byte_size=0;
		char offset_byte_size[32];
		string_conversion string_conv;
		char song_id[128];

		memset(key,0x0,sizeof(key));
		memset(szFileHead,0x0,sizeof(szFileHead));
		memset(offset_byte_size,0x0,sizeof(offset_byte_size));
		memset(song_id,0x0,sizeof(song_id));

		//open index file
		fp_index = _wfopen(in_lyric_index_path,L"rb");
		if (NULL==fp_index)
		{
			return false;
		}
		string_conv.widechar_to_multibyte(in_song_id,song_id,sizeof(song_id));
		strcat(song_id,"#");
		//读出全部歌曲编号和偏移数据
		while (1)
		{
			memset(pDataBuffer,0x0,sizeof(pDataBuffer));
			if(fread(pDataBuffer,0x1,sizeof(pDataBuffer),fp_index)<=0)
			{
				break;
			}
			//防止歌曲编号和偏移重复，前后加了分隔符
			song_number = strstr((const char *)pDataBuffer,song_id);
			if (song_number)
			{
				break;
			}
		}

		if (NULL==song_number)
		{
			if (fp_index)
			{
				fclose(fp_index);
				fp = NULL;
			}
			return false;
		}
		offset = strstr(song_number,"#");
		if (NULL==offset)
		{
			if (fp_index)
			{
				fclose(fp_index);
				fp = NULL;
			}
			return false;
		}
		offset++;
		song_number = strstr(offset,"$");
		if (NULL==song_number)
		{
			if (fp_index)
			{
				fclose(fp_index);
				fp = NULL;
			}
			return false;

		}
		memcpy(offset_byte_size,offset,song_number-offset);
		sscanf(offset_byte_size,"%d-%d",&offset_start,&song_byte_size);

		if (fp_index)
		{
			fclose(fp_index);
			fp_index = NULL;
		}

		//open lyric file
		fp = _wfopen(in_lyric_path,L"rb");
		if (NULL==fp)
		{
			return false;
		}
		fseek(fp,offset_start,SEEK_SET);
		//read head
		fread(szFileHead,0x1,sizeof(szFileHead),fp);
		//选择密钥
		memcpy(key,all_key[szFileHead[0]],sizeof(key));
		//修改密钥
		key[3] = szFileHead[3] & szFileHead[4];
		key[7] = szFileHead[5] | szFileHead[6];
		key[11] = szFileHead[7] | szFileHead[0];


		memset(pDataBuffer,0x0,sizeof(pDataBuffer));
		fseek(fp,offset_start+8,SEEK_SET);
		fread(pDataBuffer,0x1,song_byte_size,fp);
		if (fp)
		{
			fclose(fp);
			fp=NULL;
		}
		//decrypt data
		Des_Go((char *)pDataBuffer,(char *)pDataBuffer,song_byte_size,key,szFileHead[2],DECRYPT);
		//save DECRYPT data
		int byte_size = string_conv.get_byte_size_of_widechar((const char *)pDataBuffer);
		string_conv.multibyte_to_widechar((const char *)pDataBuffer,out_lyric,byte_size);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::song_lyric_replace(TCHAR *lyric)
{
	try
	{
		TCHAR * head=lyric;

		if (NULL==head)
		{
			return false;
		}

		while(*head!='\0')
		{
			if((','== *head) || ('.'==*head)|| ('!'==*head))
			{
				*head='\n';
			}
			head++;
		}
		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::write_com_data(COM_SEND_VALUE_FLAG com_send_flag, int adjust_count/* =0 */, bool auto_light /* = true */, int light /* = -1 */)
{
	try
	{
		bool result=false;
		bool ret=false;
		int music_volume=0;
		int microphone_volume=0;
		int tune=0;
		song_info video_info;
		TCHAR song_id[128];
		TCHAR light_info[128];

		memset(song_id,0x0,sizeof(song_id));
		memset(light_info, 0x0, sizeof(light_info));

		//得到正播放的歌曲ID
		result = m_player_manager.get_playing_video(video_info);
		if (result && auto_light)
		{
			video_info.get_song_id(song_id);
			if (0 == _tcscmp(song_id, L""))
			{
				//空闲歌曲，默认40路灯光
				_tcscpy(light_info, L"9876543:40");
			}
			else
			{
				int light_val = 0;
				if (light < 0)
				{
					light_val = video_info.get_light_control_set();
				}else{
					light_val = light;
				}
				if (light_val > 0)
				{
					swprintf_s(light_info, sizeof(light_info)/sizeof(TCHAR), L"%s:%d", song_id, light_val);
				}
				else
				{
					_tcscpy(light_info, song_id);
				}
			}
		}
		//得到音量和音调
		result = m_player_manager.get_volume_tune(music_volume,microphone_volume,tune);
		//写串口数据
		ret = m_inherit_com.write_data(com_send_flag,L"com.ini",light_info,music_volume,microphone_volume,tune,adjust_count);
		if (ret)
		{
			result = true;
		}
		ret = m_inherit_bak_com.write_data(com_send_flag,L"com_second.ini",light_info,music_volume,microphone_volume,tune,adjust_count);
		if (ret)
		{
			result = true;
		}
		ret = m_inherit_three_com.write_data(com_send_flag,L"com_three.ini",light_info,music_volume,microphone_volume,tune,adjust_count);
		if (ret)
		{
			result = true;
		}

		return result;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::get_image_resolution(TCHAR *image_path,int &width,int &height)
{
	try
	{
		Image *src_image=NULL;

		src_image = Image::FromFile(image_path);
		if (src_image)
		{
			width = src_image->GetWidth();
			height = src_image->GetHeight();

			delete src_image;
			src_image=NULL;

			return true;
		}
		return false;
	}
	catch (...)
	{
		
	}
	return false;
}

bool Cflashktv10Wnd::show_wall_panel_image(void)
{
	try
	{
		config_file_manager config_file;
		TCHAR picture_path[256];
		int picture_number=0;

		memset(picture_path,0x0,sizeof(picture_path));

		switch(m_wall_panel_show_mode)
		{
		case WALL_PANEL_VIDEO_IMAGE:
			{
				//得到要显示的图片编号
				picture_number = config_file.read_integer(L"wall_panel",L"wall_panel_picture_number",1);
				//显示图片
				swprintf(picture_path,L"%s\\%s\\wall_panel%d.png",m_work_path,g_folder_name[15],picture_number);
				m_player_manager.show_wall_panel_picture(picture_path);
			}
			break;
		case WALL_PANEL_VIDEO_FLASH:
		case WALL_PANEL_IMAGE_FLASH:
		default:
			{
				//显示flash界面
				m_wall_panel_flash_player.BringWindowToTop();
				m_wall_panel_flash_player.ShowWindow(SW_SHOW);
			}
			break;
		}
		//设置标示显示
		m_wall_panel_image_show = true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool Cflashktv10Wnd::decrypt_star_picture(TCHAR *picture_path,bool flag)
{
	try
	{
		decrypt_picture decrypt_picture_class;
		TCHAR decrypt_path[256];
		int file_number=0;
		bool result=false;

		if (NULL==picture_path)
		{
			return false;
		}
		
		memset(decrypt_path,0x0,sizeof(decrypt_path));

		//编号是固定的
		if (flag)
		{
			//歌星图片
			file_number = 233;
		}
		else
		{
			//歌星介绍
			file_number = 333;
		}

		//解密歌星图片或资料		
		result = decrypt_picture_class.decrypt_picture_file(picture_path,decrypt_path,file_number);
		if (result)
		{
			picture_path[0] = '\0';
			_tcscpy(picture_path,decrypt_path);
		}

		return result;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::show_singer_introduction(const TCHAR *star_name)
{
	try
	{
		TCHAR *singer_introduction = NULL;
		TCHAR *request = NULL;
		bool result=false;
		TCHAR path[256];
		file singer_intro_file;
		DWORD read_byte=0;
		string_conversion string_conv;
		TCHAR request_data[256];

		memset(path,0x0,sizeof(path));
		memset(request_data,0x0,sizeof(request_data));

		//先清空原有的歌星介绍
		result = m_flash_manage.make_request(request_data,sizeof(request_data)/sizeof(TCHAR),L"SingerIntro",L"");
		if (result)
		{
			flash_player_call_function(request_data);
		}

		//歌星介绍的文件路径
		swprintf(path,L"%s\\%s\\%s.txt",m_work_path,g_folder_name[16],star_name);
		//不存在直接返回
		if (!PathFileExists(path))
		{
			return;
		}

		//解密歌星介绍
		result = decrypt_star_picture(path,false);
		if (!result)
		{
			return;
		}

		//打开歌星介绍文件
		result = singer_intro_file.open_file(path,FILE_READ);
		if (!result)
		{
			//打开文件失败
			return;
		}
		//得到文件大小
		DWORD file_size = singer_intro_file.get_file_size();
		if (file_size<=0)
		{
			//没有歌星介绍
			singer_intro_file.close_file();
			return;
		}
		if (file_size>10*1024)
		{
			//大于10K最多取10K
			file_size = 10*1024;
		}

		char *temp_introduce = new char[file_size+1];
		if (NULL==temp_introduce)
		{
			singer_intro_file.close_file();
			return;			
		}
		memset(temp_introduce,0x0,file_size+1);
		//读取文件
		result = singer_intro_file.read_file(temp_introduce,file_size,&read_byte);
		if (result)
		{
			//转化成unicode
			int use_byte = string_conv.get_byte_size_of_widechar(temp_introduce);
			//分配空间
			singer_introduction = new TCHAR[use_byte];
			if (singer_introduction)
			{
				memset(singer_introduction,0x0,use_byte*sizeof(TCHAR));
				string_conv.multibyte_to_widechar(temp_introduce,singer_introduction,use_byte);
				//删除特殊字符
				flash_replace_special_char(singer_introduction);
				//分配空间
				request = new TCHAR[use_byte+1024];
				if (request)
				{
					memset(request,0x0,(use_byte+1024)*sizeof(TCHAR));
					result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"SingerIntro",singer_introduction);
					if (result)
					{
						flash_player_call_function(request);
					}
					//释放空间
					delete []request;
					request = NULL;
				}
				//释放空间
				delete []singer_introduction;
				singer_introduction = NULL;
			}
		}
		//释放空间
		delete []temp_introduce;
		temp_introduce = NULL;
		//关闭文件
		singer_intro_file.close_file();
	}
	catch (...)
	{

	}
}

void Cflashktv10Wnd::flash_message_call_song_singer(const TCHAR *args)
{
	try
	{
		int singer_suffix=0;
		bool result=false;
		song_info song_info_class;
		TCHAR singer_name[256];

		memset(singer_name,0x0,sizeof(singer_name));

		//得到歌星下标
		swscanf(args,L"%d",&singer_suffix);

		//改变页面
		result = page_change(page_singer_song);
		if(!result)
		{
			return;
		}
		//得到选中的歌曲信息
		result = m_query_song_manager.get_song_info(singer_suffix,song_info_class);
		if (!result)
		{
			return;
		}
		//得到选中的歌星名字
		result = song_info_class.get_singer_name(singer_name);
		if (!result || (0==_tcscmp(singer_name,L"")))
		{
			return;
		}
		//_tcscpy_s(singer_name,args);
		//根据歌星名字显示歌星歌曲和资料
		result = show_singer_song_introduction(singer_name,NULL,NULL);

		TCHAR request[1024];
		TCHAR singer_info[1024] = {0x00};
		swprintf(singer_info,L"<data><info singer_name=\"%s\" /></data>",singer_name);

		memset(request,0x0,sizeof(request));
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"singer_name_info",singer_info);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_message_call_singer_select(const TCHAR *args)
{
	try
	{
		bool result=false;
		int select_singer_suffix=0;
		singer_info singer_info_class;
		TCHAR singer_name[256];
		TCHAR singer_type[256];
		TCHAR singer_sex[256];
		TCHAR singer_id[256];
		
		memset(singer_name,0x0,sizeof(singer_name));
		memset(singer_type,0x0,sizeof(singer_type));
		memset(singer_sex,0x0,sizeof(singer_sex));
		memset(singer_id,0x00,sizeof(singer_id));
		
		//改变页面
		result = page_change(page_singer_song);
		//得到歌星编号
		swscanf(args,L"%d",&select_singer_suffix);
		
		//得到歌手的信息
		singer_info_class = m_query_singer_manager.get_singer_info(select_singer_suffix);
		//得到歌手名字
		result = singer_info_class.get_singer_name(singer_name);
		if (!result)
		{
			return;
		}
		//得到歌星区域
		singer_info_class.get_singer_region(singer_type);
		//得到歌星性别
		singer_info_class.get_singer_sex(singer_sex);		

		//歌星名字
		//_tcscpy_s(singer_name,args);
		singer_info_class.get_singer_id(singer_id);

		//根据歌星名字显示歌星歌曲和资料
		result = show_singer_song_introduction(singer_name,singer_sex,singer_type);

		TCHAR request[1024];
		TCHAR singer_info[1024] = {0x00};
		swprintf(singer_info,L"<data><info singer_name=\"%s\" /></data>",singer_name);

		memset(request,0x0,sizeof(request));
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"singer_name_info",singer_info);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;

	}
	catch(...)
	{

	}
	return;
}

bool Cflashktv10Wnd::flash_message_call_select_sing_page_to_singer(const TCHAR *args,bool select_song_page)
{
	try
	{
		int singer_suffix=0;
		bool result=false;
		song_info song_info_class;
		TCHAR singer_name[128];
		
		memset(singer_name,0x0,sizeof(singer_name));
		
		//得到歌星下标
		swscanf(args,L"%d",&singer_suffix);
		//改变页面
		result = page_change(page_singer_song);
		if (!result)
		{
			return false;
		}

		//得到歌手名字
		if (select_song_page)
		{
			//已选页面
			result = m_video_play_manager.get_select_song_information(song_info_class,singer_suffix,true);
		}
		else
		{
			//已唱页面
			result = m_video_play_manager.get_sing_song_information(song_info_class,singer_suffix,true);
		}
		if (!result)
		{
			return false;
		}
		result = song_info_class.get_singer_name(singer_name);
		if (!result||(0==_tcscmp(singer_name,L"")))
		{
			return false;
		}
		//_tcscpy_s(singer_name,args);
		//根据歌星名字显示歌星歌曲和资料
		result = show_singer_song_introduction(singer_name,NULL,NULL);

		TCHAR request[1024];
		TCHAR singer_info[1024] = {0x00};
		swprintf(singer_info,L"<data><info singer_name=\"%s\" /></data>",singer_name);

		memset(request,0x0,sizeof(request));
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"singer_name_info",singer_info);
		if (result)
		{
			flash_player_call_function(request);
		}

		return result;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::flash_message_call_preview_control(const TCHAR *args)
{
	try
	{
		int play_control=0;
		long cur_play_position=0;
		long total_time_len=0;
		bool result=false;

		swscanf(args,L"%d",&play_control);

		switch(play_control)
		{
		case PLAY_CONTROL_PAGE_CLOSE:      //预览页面关闭
			{
				m_player_manager.preview_close();
				if (m_preview_window_exist)
				{
					m_preview_window.show_window(false);
				}
				//返回前一个页面
				flash_message_call_function(PAGE_BACK);
			}
			break;
		case PLAY_CONTROL_SONG_PRIORITY:   //预览优先
			{
				flash_message_call_preview_select_song(true);
			}
			break;
		case PLAY_CONTROL_SONG_MEMBER:     //歌曲收藏
			{
				if (m_member_already_login)
				{
					if (m_member_song_count>=MEMBER_MAX_SONG_COUNT)
					{
						//提示会员歌曲数已经达到最大值
						flash_show_tip_message(27);
					}
					else
					{
						//如果会员已经登录加入到会员歌曲中
						flash_message_call_person_song(NULL,true);
					}
				}
				else
				{
					//没有登录，做提示
					flash_show_tip_message(26);
				}
			}
			break;
		case PLAY_CONTROL_SONG_SELECT:     //点播歌曲
			{
				flash_message_call_preview_select_song(false);
			}
			break;
		case PLAY_CONTROL_FAST_FORWARD:  //快进
			{
				//防止频繁操作
				double last_time = m_preview_control_timer.last_time();
				if (last_time<PREVIEW_CONTROL_MIN_TIME_LENGTH)
				{
					break;
				}
				m_preview_control_timer.start();

				//得到当前播放位置，单位：秒
				cur_play_position = m_player_manager.preview_control(PVC_GET_POSITION,0,0);
				//加20秒
				cur_play_position += 10;
				//得到总的时长
				total_time_len = m_player_manager.preview_control(PVC_GET_DURATION,0,0);
				if (cur_play_position>=total_time_len)
				{
					cur_play_position = total_time_len-5;
				}
				m_player_manager.preview_control(PVC_SET_POSITION,cur_play_position,0);
			}
			break;
		case PLAY_CONTROL_FAST_BACKWARD:   //快退
			{
				//防止频繁操作
				double last_time = m_preview_control_timer.last_time();
				if (last_time<PREVIEW_CONTROL_MIN_TIME_LENGTH)
				{
					break;
				}
				m_preview_control_timer.start();

				//得到当前播放位置，单位：秒
				cur_play_position = m_player_manager.preview_control(PVC_GET_POSITION,0,0);
				//加20秒
				cur_play_position -= 10;
				if (cur_play_position<0)
				{
					cur_play_position = 0;
				}
				m_player_manager.preview_control(PVC_SET_POSITION,cur_play_position,0);
			}
			break;
		default:
			break;
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_message_call_preview_change_play_pos(const TCHAR *args)
{
	try
	{
		int play_pos=0;
		int total_time=0;

		if (NULL==args)
		{
			return;
		}

		swscanf(args,L"%d",&play_pos);
		if (play_pos<0)
		{
			play_pos = 0;
		}
		else if (play_pos>100)
		{
			play_pos = 100;
		}
		//得到总的时长
		total_time = m_player_manager.preview_control(PVC_GET_DURATION,0,0);
		//设置播放位置
		m_player_manager.preview_control(PVC_SET_POSITION,total_time*play_pos/100,0);

		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::flash_message_call_preview_select_song(bool priority)
{
	try
	{
		int select_song_count=0;
		TCHAR song_id[128];
		int play_number=0;
		bool result=false;
		bool iSelectSong=false;   //判断是否已选列表中有只首歌曲

		memset(song_id,0x0,sizeof(song_id));

		if (!m_find_dog_success)
		{
			//没有找到加密狗
			if (0==_tcscmp(m_dog_tip_info,L""))
			{
				flash_show_tip_message(17);
			}
			else
			{
				flash_show_tip_message(m_dog_tip_info);
			}
			return;
		}
		if (CLOSE_ROOM_STATE==m_pc_state)
		{
			//关房状态，不能选歌曲
			flash_show_tip_message(16);
			return;
		}
		
		//get select song count
		select_song_count = m_video_play_manager.get_select_song_count();
		if (select_song_count>=SELECT_SONG_MAX_COUNT)
		{
			flash_show_tip_message(25);
			return;
		}

		//得到歌曲编号
		result = m_preview_song_info.get_song_id(song_id);
		//查看是否存在
		result = m_video_play_manager.query_select_song_by_id(song_id,play_number);
		
		if (result && !m_allow_repeat_select_song)
		{
			//保存基本信息
			m_select_song_info=m_preview_song_info;
			m_select_song_priority=priority;
			m_select_song_number = -1;
			//预览默认不允许重复选
			//存在，显示选择提示
			//show_check_window(true);
			if (priority)
			{
				//如果是优先，就把已选歌曲中的该歌曲优先
				m_video_play_manager.priority_select_song(play_number-1,false);
			}

			iSelectSong = true;
		}

		//如果是在pk中选择优先或者点播时
		if (m_b_pk_connect)
		{
			//发送消息给连接的ip
			TCHAR send_ip[256]; 
			TCHAR send_sync_songs[256];

			if (0 != _tcscmp(m_pk_invitationIP,L""))
			{
				_tcscpy(send_ip,m_pk_invitationIP);
			}
			if (0 != _tcscmp(m_pk_acceptIP,L""))
			{
				_tcscpy(send_ip,m_pk_acceptIP);
			}
		  
		
			_tcscpy(send_sync_songs,_T("priority_song3"));   //点播歌曲同步
			if (priority)
			{
				_tcscat(send_sync_songs,L"1");
			}
			else
			{
				_tcscat(send_sync_songs,L"0");
			}
		
			_tcscat(send_sync_songs,song_id);
			connect_inviation(send_ip,send_sync_songs);  //发送给服务器
		}


		if (iSelectSong)   
		{
			return;
		}
		//显示选歌动画提示
		//show_select_song_animation();

		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(m_preview_song_info,priority);
		if (!result)
		{
			return;
		}
		//重新显示上下首歌名
		show_song_name();
	}
	catch (...)
	{
		
	}
	return;
}

bool Cflashktv10Wnd::flash_message_call_priority_select_song(const TCHAR *args,bool recv_msg)
{
	try
	{
		int song_number=0;
		int result=false;
		TCHAR send_data[256];

		memset(send_data,0x0,sizeof(send_data));

		//得到要优先的歌曲编号
		swscanf(args,L"%d",&song_number);

		if ((0==m_master_slave_control_flag)||(1==m_master_slave_control_flag))
		{
			//主控机
			if (!recv_msg)
			{
				//客户点击优先，相对编号
				result = m_video_play_manager.priority_select_song(song_number,true);
			}
			else
			{
				//接受的被控消息，绝对编号
				result = m_video_play_manager.priority_select_song(song_number,false);
			}
			if (result>=0)
			{
				//刷新歌曲列表
				refresh_screen_list();
				//重新显示上下首歌名
				show_song_name();
			}
			if ((result>=0)&&(1==m_master_slave_control_flag))
			{
				//发送给被控机，使用返回值，返回值是优先的歌曲的歌曲的绝对编号
				swprintf(send_data,L"PSELECTSONG%d",result);
				send_master_slave_data(send_data,NULL);
			}
		}
		else if(2==m_master_slave_control_flag)
		{
			//被控机
			if (!recv_msg)
			{
				//客户点击，发送给主控机
				//得到绝对编号
				result = m_video_play_manager.get_select_song_absolute_position(song_number);
				//发送给主控机
				swprintf(send_data,L"PSELECTSONG%d",result);
				send_master_slave_data(send_data,NULL);
			}
			else
			{
				//接受的主控消息，绝对编号
				result = m_video_play_manager.priority_select_song(song_number,false);
				if (result>=0)
				{
					//刷新歌曲列表
					refresh_screen_list();
					//重新显示上下首歌名
					show_song_name();
				}
			}
		}		

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::flash_message_call_drag_sort_select_song(int nOrigin, int nDestination, bool recv_msg/*=false*/)
{
	try
	{
		int result=0;
		TCHAR send_data[256];

		memset(send_data,0x0,sizeof(send_data));

		if ((0==m_master_slave_control_flag)||(1==m_master_slave_control_flag))
		{
			//主控机
			result = m_video_play_manager.drag_sort_select_song(nOrigin, nDestination, false);
			if (result>=0)
			{
				//刷新歌曲列表
				refresh_screen_list();
				//重新显示上下首歌名
				show_song_name();
			}
			if (!recv_msg && (result>=0)&&(1==m_master_slave_control_flag))
			{
				//发送给被控机，使用返回值，返回值是优先的歌曲的歌曲的绝对编号
				swprintf(send_data, L"PDRAGSORTSONG%d|%d", nOrigin, nDestination);
				send_master_slave_data(send_data,NULL);
			}
		}
		else if(2==m_master_slave_control_flag)
		{
			result = m_video_play_manager.drag_sort_select_song(nOrigin, nDestination, false);
			if (result>=0)
			{
				//刷新歌曲列表
				refresh_screen_list();
				//重新显示上下首歌名
				show_song_name();
			}
			//被控机
			if (!recv_msg)
			{
				//客户点击，发送给主控机
				//得到绝对编号
				//result = m_video_play_manager.get_select_song_absolute_position(nOrigin);
				//发送给主控机
				swprintf(send_data, L"PDRAGSORTSONG%d|%d", nOrigin, nDestination);
				send_master_slave_data(send_data,NULL);
			}
		}
		return true;
	}
	catch(...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_random_sort_select_song()
{
	try
	{
		bool result = false;

		result = m_video_play_manager.random_sort_select_song();
		if (result)
		{
			//刷新歌曲列表
			refresh_screen_list();
			//重新显示上下首歌名
			show_song_name();
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}
unsigned long Cflashktv10Wnd::FirstDriveFromMask (DWORD mask)
{
	unsigned long i=0;

	for (i = 0; i<26; ++i)
	{
		if (mask & 0x1)
			break;
		mask = mask >> 1;
	}

	return (i + 'A');
}

void Cflashktv10Wnd::clear_query_condition_by_page_and_init(bool clear_list)
{
	//按照页面清空条件
	clear_query_condition_by_page();
	//检索面板初始化
	query_board_init();
	if (clear_list)
	{
		//清空页面列表
		clear_show_list();
	}
}

void Cflashktv10Wnd::flash_message_call_maiba(enum MAIBA_TYPE maiba_type,const TCHAR *args)
{
	try
	{
		bool result=false;
		int start_pos =0;
		int end_pos = 0;
		int maiba_page=0;   //页码
		int maiba_number=0;  //高亮按钮
		TCHAR request_data[256]; 
		TCHAR user_identitycard[256];  //用户唯一标识码
		std::wstring song_list_xml;
		TCHAR request[1024];


		swscanf(args,L"%d:%d",&maiba_number,&maiba_page);

		memset(request_data,0x0,sizeof(request_data));
		memset(user_identitycard,0x0,sizeof(user_identitycard));
		memset(request,0x0,sizeof(request));
		 
		end_pos = maiba_page*m_page_show_row_count;   //结束位置
		start_pos = (maiba_page -1)*m_page_show_row_count;  //起始位置
		if (start_pos<0)
		{
			start_pos = 0;
		}

		m_maiba_request_page = maiba_page;
		m_web_current_page_number = maiba_page;

		
		m_maiba_current_request_type = maiba_type;

		switch (maiba_type)
		{
		case MAIBA_SHARE:   //K歌分享
			{
				if (0 == maiba_number)
				{
					//我的录音  room_ip
					//swprintf(request_data,L"PLACEVERSION/MYRECORDVOCE?start_pos=%d&end_pos=%d",start_pos,end_pos);
					//song_recorder_query_show_data();
					m_request_song_type = REQUEST_NO;
					song_recorder_query_all_show_data();
					m_maiba_number_button = maiba_number;
					set_flash_button_state(L"maiba_number_button",m_maiba_number_button);
					return;
				}
				else if(1 == maiba_number)
				{
					m_request_song_type = MYRECORDSHARE;

					if (-1 == m_activate_vip_button)
					{
						//弹出登录框
						m_activate_vip_button = 0;
						flash_message_call_page_jump(page_maiba_login);
						return;
					}

					m_memeber_manage[m_activate_vip_button].get_user_identitycard(user_identitycard);
					//我的分享
					swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/MYRECORDSHARE?start_pos=%d&end_pos=%d&identitycard=%s",start_pos,end_pos,user_identitycard);
				}
			}
			break;
		case MAIBA_FIND:   //发现麦霸
			{
				if (0 == maiba_number)
				{
					//全国最火
					swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/COUNTRYHOT?start_pos=%d&end_pos=%d",start_pos,end_pos);

					m_request_song_type = COUNTRYHOT;
				}
				else if (1 == maiba_number)
				{
						//全国最新
					swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/COUNTRYNEW?start_pos=%d&end_pos=%d",start_pos,end_pos);

					m_request_song_type = COUNTRYNEW;
				}
				else if (2 == maiba_number)
				{
					//本场最火
					swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/PLACEHOT?start_pos=%d&end_pos=%d",start_pos,end_pos);
					m_request_song_type = PLACEHOT;
				}
				else if (3 == maiba_number)
				{
					//本场最新
					swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/PLACENEW?start_pos=%d&end_pos=%d",start_pos,end_pos);
					m_request_song_type = PLACENEW;
				}
				else if (4 == maiba_number)
				{
					if (-1 == m_activate_vip_button)
					{
						flash_show_tip_message(26);
						break;
					}
					//我的收藏
					m_memeber_manage[m_activate_vip_button].get_user_identitycard(user_identitycard);
					swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/MYCOLLECTION?start_pos=%d&end_pos=%d&identitycard=%s",start_pos,end_pos,user_identitycard);
					//thread_send_to_box_tcp_function(request_data,18007);
					m_request_song_type = MYCOLLECTION;
				}
			}
			break;
		case MAIBA_DEKARON:   //挑战麦霸
			{
				if (0 == maiba_number)
				{
					//自由pk
					m_maiba_pk_type = 1;
					end_pos = 10;
					//swprintf(request_data,L"MAIBAREQUESTINFO&FREEPK?start_pos=0&end_pos=%d",MAIBA_HEIGHT_RANKING_LIST);
					swprintf(request_data,L"RequestMaibaFree{\"start_pos\":\"%d\",\"end_pos\":\"%d\"}",start_pos,end_pos);
					m_request_song_type = FREEPK;
				}
				else if (1 == maiba_number)
				{
					//擂台pk
					m_maiba_pk_type = 2;
					end_pos = 10;
					//swprintf(request_data,L"MAIBAREQUESTINFO&DEKARONPK?start_pos=0&end_pos=%d",MAIBA_HEIGHT_RANKING_LIST);
					swprintf(request_data,L"RequestMaibaArea{\"start_pos\":\"%d\",\"end_pos\":\"%d\"}",start_pos,end_pos);
					m_request_song_type = AREAPK;
				}
				else if (2 == maiba_number)
				{
					//上榜有礼
					m_maiba_pk_type = 3;
					//swprintf(request_data,L"MAIBAREQUESTINFO&DEKARONPK?start_pos=0&end_pos=%d",MAIBA_HEIGHT_RANKING_LIST);
					swprintf(request_data,L"RequestMaibaSrea{\"start_pos\":\"%d\",\"end_pos\":\"%d\"}",start_pos,end_pos);
					m_request_song_type = RANKING_POLITE;
				}
			}
			break;
		case PRIVATE_SONG:  //私房歌曲
			{
				m_memeber_manage[m_activate_vip_button].get_user_identitycard(user_identitycard);
					swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/MYPRIVATESONG?start_pos=%d&end_pos=%d&identitycard=%s",start_pos,end_pos,user_identitycard);
					//thread_send_to_box_tcp_function(request_data,18007);
					m_request_song_type = MYPRIVATESONG;
			}
			break;
		default:
			break;
		}

		if (maiba_type == MAIBA_DEKARON)
		{
			
			//发送数据给规则服务器 
			REQUEST_BOX_DATA *request_box_data = new REQUEST_BOX_DATA;
			
			_tcscpy(request_box_data->request_data,request_data);
			request_box_data->nPort = 6666;
			request_box_data->pThis = this;
			AfxBeginThread(send_server_msg_tcp_thread,request_box_data);

			//标示是发送规则消息
			//parse_arena_rule_info("1",m_maiba_pk_type,1); 

		}
		else
		{
			//去网络去数据 数据端口

			//启动线程 发送给盒子请求微信点歌数据
			thread_send_to_box_tcp_function(request_data,18007);

			memset(m_request_data,0x0,sizeof(m_request_data));
			_tcscpy(m_request_data,request_data);
			//SetEvent(m_box_thread_event_handle);
			//flash_message_call_maiba_pk_data(FIRST_PAGE_OPERATE);


			//maiba_pk_data_test();
			//flash_message_call_maiba_pk_data(L"",FIRST_PAGE_OPERATE);
		}

		//发送数麦霸数据给前台
		//开始发一次空数据 
		if (PRIVATE_SONG == maiba_type)
		{
			if(1 == maiba_page)
			{
				//先发空数据
				song_query_member_data_by_id(L"");
			}
		}
		else
		{
			if (1 == maiba_page)
			{
				int page_index = m_flash_manage.get_last_page_index();
				song_list_xml += L"<song_list></song_list>";

				//组织歌曲字符串 
				result = m_flash_manage.make_maiba_song_request(request,sizeof(request)/sizeof(TCHAR),song_list_xml.c_str(),true,page_index,FIRST_PAGE_OPERATE);
				if (!result)
				{
					return;
				}
				flash_player_call_function(request);
			}		
		}

		m_maiba_number_button = maiba_number;
		set_flash_button_state(L"maiba_number_button",m_maiba_number_button);
	
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::flash_message_call_service(const TCHAR *args)
{
	try
	{
		bool result=false;
		int service_type=0;
		config_file_manager config_file;
		TCHAR folder_name[256];
		TCHAR picture_dir[256];
		int fire_picture_folder_type=0;
		TCHAR interface_name[MAX_PATH] = {0x00};

		memset(folder_name,0x0,sizeof(folder_name));
		memset(picture_dir,0x0,sizeof(picture_dir));

		swscanf(args,L"%d",&service_type);

		switch(service_type)
		{
		case 1:  //场所介绍
			{
				_tcscpy(folder_name,g_folder_name[20]);
			}
			break;
		case 2:  //促销活动 包厢使用手册
			{
				_tcscpy(folder_name,g_folder_name[21]);
			}
			break;
		case 3:  //消防图解
			{
				//得到消防图解的文件夹类型
				fire_picture_folder_type = config_file.read_integer(L"room",L"fire_picture_folder_type",0);
				switch(fire_picture_folder_type)
				{
				case 1:  //IP命名的文件夹
					{
						_tcscpy(folder_name,m_room_ip);
					}
					break;
				case 2:  //包房名命名的文件夹
					{
						_tcscpy(folder_name,m_show_room_name);
					}
					break;
				case 0:
				default:  //固定的fire_picture文件夹
					{
						_tcscpy(folder_name,g_folder_name[22]);
					}
					break;
				}	
			}
			break;
		case 4:  //使用帮助   消防指南
			{
				_tcscpy(folder_name,g_folder_name[23]);
			}
			break;
		case 5:
			{
				_tcscpy(folder_name,g_folder_name[21]);
			}
			break;
		case 6:
			{
				_tcscpy(folder_name, g_folder_name[38]);
				_tcscpy(interface_name, L"screen_image_path");
			}
			break;
		case PAGE_UP:    //前一页
			{
				show_service_image(SERVICE_PICTRUE_PRE_PAGE);
			}
			return;
		case PAGE_DOWN:   //下一页
			{
				show_service_image(SERVICE_PICTRUE_NEXT_PAGE);
			}
			return;
		default:
			return;
		}
		//竖版
		if(SCREEN_TYPE_VERTICAL==m_interface_type)
		{
			if (0 == _tcscmp(m_cur_interface_version, L"ek800") || 0 == _tcscmp(m_cur_interface_version, L"face800"))
			{

				swprintf(picture_dir,L"%s\\%s\\v800",m_work_path,folder_name);
			}else{
				swprintf(picture_dir,L"%s\\%s\\v720",m_work_path,folder_name);
			}
		}
		//横版
		else{
			if (0 == _tcscmp(m_cur_interface_version, L"ek800") || 0 == _tcscmp(m_cur_interface_version, L"face800"))
			{

				swprintf(picture_dir,L"%s\\%s\\h800",m_work_path,folder_name);
			}else{
				swprintf(picture_dir,L"%s\\%s\\h720",m_work_path,folder_name);
			}
		}
		
		if (!PathFileExists(picture_dir))
		{
			return ;
		}
		//初始化
		result = m_show_service_picture.initiate(picture_dir);
		if (!result)
		{
			return;
		}

		if (_tcscmp(interface_name, L"") != 0)
		{
			show_service_image(SERVICE_PICTRUE_CUR_PAGE, interface_name);
		}else
		{
			//显示图片
			show_service_image(SERVICE_PICTRUE_CUR_PAGE);
		}
	}
	catch (...)
	{

	}
	return;
}
void Cflashktv10Wnd::flash_message_call_consume(void)
{
	try
	{
		//页面改变，直接回到首页
		page_change_function(page_homepage);
		//外挂消费
		config_file_manager config_file;
		std::wstring software_path;
		bool consume_control = false;
		//消费是否需要开关房控制
		consume_control = config_file.read_boolean(L"drinks",L"consume_open_close_control",true);
		if (consume_control&&CLOSE_ROOM_STATE==m_pc_state)
		{
			WriteLog(__FL__, L"后台没有开房，不能点消费查询");
			return;
		}
		//得到酒水软件路径
		software_path = config_file.read_string(L"drinks",L"consume_software_path",L"");
		if (software_path.empty())
		{
			WriteLog(__FL__, L"消费查询外挂路径为空");
			return;
		}
		bool start_consume_flag = start_plug_in_process(software_path.c_str(),SW_SHOW,m_consume_process_id);
		if (start_consume_flag)
		{
			WriteLog(__FL__, L"启用消费查询外挂成功");
		}
	}
	catch(...)
	{

	}
	return;
}
void Cflashktv10Wnd::flash_message_call_drinks(void)
{
	try
	{
		//页面改变，直接回到首页
		page_change_function(page_homepage);
		//加载酒水
		if (m_use_plug_in_drinks)
		{
			TCHAR path[256];

			memset(path,0x0,sizeof(path));

			//内嵌酒水
			if (m_drinks_flash_player_exist)
			{
				if (SCREEN_TYPE_HORIZON==m_interface_type)
				{
					//横版
					swprintf(path,L"%s\\%s\\doorplate_h.swf",m_work_path,g_folder_name[34]);
				}
				else
				{
					//竖版
					swprintf(path,L"%s\\%s\\doorplate_v.swf",m_work_path,g_folder_name[34]);
				}
				if (PathFileExists(path))
				{
					//文件存在，在加载
					m_drinks_flash_player.LoadMovie(0,path);
					m_drinks_flash_player.BringWindowToTop();
					m_drinks_flash_player.ShowWindow(SW_SHOW);
					//设置内嵌酒水状态
					m_show_drinks_state=true;
				}
			}
		}
		else
		{
			//外挂酒水
			config_file_manager config_file;
			std::wstring software_path;
			bool drinks_control=false;

			//酒水是否需要开关房控制
			drinks_control = config_file.read_boolean(L"drinks",L"drinks_open_close_control",true);
			if (drinks_control && !m_open_drinks)
			{
				WriteLog(__FL__, L"后台没有开房，不能点酒水");
				return;
			}
			//得到酒水软件路径
			software_path = config_file.read_string(L"drinks",L"drinks_software_path",L"");
			if (software_path.empty())
			{
				WriteLog(__FL__, L"酒水路径为空");
				return;
			}
			//启动酒水软件
			m_show_drinks_state = start_plug_in_process(software_path.c_str(),SW_SHOW,m_drinks_process_id);
			if(m_show_drinks_state&&m_ktv_software_min)
			{
				//酒水启动成功，并且需要软件最小化，就最小化
				ShowWindow(SW_SHOWMINIMIZED);
			}
		}

		return;
	}
	catch (...)
	{

	}
	return;
}
bool Cflashktv10Wnd::start_plug_in_process(const TCHAR *path,WORD show_flag,DWORD &process_id)
{
	try
	{
		STARTUPINFO start_info;
		PROCESS_INFORMATION process_info;
		TCHAR command_line[256];
		BOOL result=FALSE;
		TCHAR paramter[256];
		TCHAR work_path[256];

		memset(command_line,0x0,sizeof(command_line));
		memset(paramter,0x0,sizeof(paramter));
		memset(work_path,0x0,sizeof(work_path));

		//启动软件
		ZeroMemory( &start_info, sizeof(start_info) );
		start_info.cb = sizeof(start_info);
		start_info.dwFlags = STARTF_USESHOWWINDOW;
		//start_info.dwFlags = STARTF_USESHOWWINDOW|STARTF_RUNFULLSCREEN|STARTF_USEPOSITION|STARTF_USESIZE;
		//start_info.dwX = 0;
		//start_info.dwY = 0;
		//start_info.dwXSize = m_first_display_width;
		//start_info.dwYSize = m_first_display_height;

		start_info.wShowWindow = show_flag;
		ZeroMemory( &process_info, sizeof(process_info) );

		//组成命令行
#ifdef CHANGCHUN_DRINKS_VERSION
		swprintf(command_line,L"%s %d",path,m_hWnd);
#else
		swprintf(command_line,L"%s",path);
#endif
		// Start the child process.
		result = CreateProcess(NULL, command_line,NULL,NULL,FALSE,0,NULL,NULL,&start_info, &process_info); 
		if (!result)
		{
			//启动失败
			return false;
		}
		else
		{
			//启动成功
			//save process id
			process_id = process_info.dwProcessId;
			// Close process and thread handles. 
			CloseHandle( process_info.hProcess );
			CloseHandle( process_info.hThread );
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::start_plug_in_processEx(const TCHAR *path,WORD show_flag,DWORD &process_id, PROCESS_INFORMATION &process_info,
						DWORD flag /* = STARTF_USESHOWWINDOW */, DWORD dwX /* = 0 */, DWORD dwY /* = 0 */, 
						DWORD dwWidth /* = 0 */, DWORD dwHeight /* = 0 */)
{
	try
	{
		STARTUPINFO start_info;
		TCHAR command_line[256];
		BOOL result=FALSE;
		TCHAR paramter[256];
		TCHAR work_path[256];

		memset(command_line,0x0,sizeof(command_line));
		memset(paramter,0x0,sizeof(paramter));
		memset(work_path,0x0,sizeof(work_path));

		//启动软件
		ZeroMemory( &start_info, sizeof(start_info) );
		start_info.cb = sizeof(start_info);
		start_info.dwFlags = flag;

		if (dwX != 0)
			start_info.dwX = dwX;
		if (dwY != 0)
			start_info.dwY = dwY;
		if (dwWidth != 0)
			start_info.dwXSize = dwWidth;
		if (dwHeight != 0)
			start_info.dwYSize = dwHeight;

		start_info.wShowWindow = show_flag;
		ZeroMemory( &process_info, sizeof(process_info) );

		//组成命令行
#ifdef CHANGCHUN_DRINKS_VERSION
		swprintf(command_line,L"%s %d",path,m_hWnd);
#else
		swprintf(command_line,L"%s",path);
#endif
		// Start the child process.
		result = CreateProcess(NULL, command_line,NULL,NULL,FALSE,0,NULL,NULL,&start_info, &process_info); 
		if (!result)
		{
			//启动失败
			return false;
		}
		else
		{
			//启动成功
			//save process id
			process_id = process_info.dwProcessId;
			// Close process and thread handles. 
			//CloseHandle( process_info.hProcess );
			//CloseHandle( process_info.hThread );
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::check_process_run_state(TCHAR *process_name,DWORD process_id)
{
	try
	{
		HANDLE         hProcessSnap = NULL; 
		bool           bRet = false; 
		PROCESSENTRY32 pe32 = {0}; 

		try
		{
			hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
			if (hProcessSnap == INVALID_HANDLE_VALUE) 
			{
				return false; 
			}
			pe32.dwSize = sizeof(PROCESSENTRY32); 
			if (Process32First(hProcessSnap, &pe32)) 
			{ 
				do 
				{ 
					if((NULL!=process_name)&&(0==_tcsicmp(pe32.szExeFile, process_name)))
					{
						bRet = true;
						break;
					}
					if ((process_id>0)&&(process_id==pe32.th32ProcessID))
					{
						bRet = true;
						break;
					}
				} while (Process32Next(hProcessSnap, &pe32)); 
			}
			CloseHandle (hProcessSnap);
		}
		catch(...)
		{

		}

		return bRet;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::teminate_process(TCHAR *process_name,DWORD process_id)
{
	HANDLE hProcessSnap = NULL; 
	bool result  = false; 
	PROCESSENTRY32 pe32; 

	try
	{
		memset(&pe32,0x0,sizeof(PROCESSENTRY32));

		//  Take a snapshot of all processes in the system. 
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 

		if (hProcessSnap == INVALID_HANDLE_VALUE) 
			return false; 

		//  Fill in the size of the structure before using it. 
		pe32.dwSize = sizeof(PROCESSENTRY32); 

		//  Walk the snapshot of the processes, and for each process, 
		//  display information. 
		if (Process32First(hProcessSnap, &pe32)) 
		{ 
			do 
			{ 
				if(((NULL!=process_name)&&(0==_tcsicmp(pe32.szExeFile, process_name)))
					||((process_id>0)&&(process_id==pe32.th32ProcessID)))
				{
					HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE,pe32.th32ProcessID);
					// 检测句柄的有效性,如有效则终止该进程
					if (hProcess) 
					{
						TerminateProcess(hProcess,0); 
						result = true; 
					}
				}
			} 
			while (Process32Next(hProcessSnap, &pe32)); 
		} 

		// Do not forget to clean up the snapshot object. 
		CloseHandle (hProcessSnap); 
		hProcessSnap = NULL;

	}
	catch (...)
	{
	}
	return result;
}

void Cflashktv10Wnd::show_U_disk_song(void)
{
	try
	{
		if(!m_have_device_insert)
		{
			//没有插入U盘
			//清空显示列表
			clear_show_list();
			//提示
			flash_show_tip_message(37);
			return;
		}

		TCHAR U_disk_path[256];
		bool result=false;
		std::wstring song_xml_list;
		TCHAR request[10240];
		int page_index=0;
		int row=0;
		int cur_page_number=0;
		int page_count=0;

		memset(U_disk_path,0x0,sizeof(U_disk_path));
		memset(request,0x0,sizeof(request));

		swprintf(U_disk_path,L"%c:",m_logical_disk_drive);
		
		//搜索U盘内歌曲
		result = m_play_U_disk_song.search_U_disk_song(U_disk_path,m_page_show_row_count);
		if (!result)
		{
			//清空显示列表
			clear_show_list();
			//提示
			flash_show_tip_message(38);
			return;
		}
		result = m_play_U_disk_song.make_U_disk_song_xml_list(song_xml_list,m_video_play_manager,FIRST_PAGE_OPERATE,m_default_song_name_color,m_select_song_name_color,m_playing_song_name_color);
		if (!result)
		{
			//清空显示列表
			clear_show_list();
			//提示
			flash_show_tip_message(38);
			return;
		}
		//显示到界面
		page_index = m_flash_manage.get_last_page_index();
		result = m_flash_manage.make_song_request(request,sizeof(request)/sizeof(TCHAR),song_xml_list.c_str(),true,page_index,0,SONG_SHOW_MODE_LIST);
		if (result)
		{
			flash_player_call_function(request);
		}
		//得到页码
		result = m_play_U_disk_song.get_song_row_and_page_count(row,page_count,cur_page_number);
		if (result)
		{
			//显示页码
			show_row_and_page_count(L"true",row,page_count,cur_page_number);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::U_disk_song_pre_next_page(PAGE_OPERATE page_operate,int operate_type)
{
	try
	{
		if(!m_have_device_insert)
		{
			//没有插入U盘
			return;
		}

		bool result=false;
		std::wstring song_xml_list;
		TCHAR request[10240];
		int page_index=0;
		int row=0;
		int cur_page_number=0;
		int page_count=0;

		memset(request,0x0,sizeof(request));

		result = m_play_U_disk_song.make_U_disk_song_xml_list(song_xml_list,m_video_play_manager,page_operate,m_default_song_name_color,m_select_song_name_color,m_playing_song_name_color);
		if (!result)
		{
			flash_show_tip_message(38);
			return;
		}
		//显示到界面
		page_index = m_flash_manage.get_last_page_index();
		if (CUR_PAGE_OPERATE==page_operate)
		{
			result = m_flash_manage.make_song_request(request,sizeof(request)/sizeof(TCHAR),song_xml_list.c_str(),true,page_index,0,SONG_SHOW_MODE_LIST);
		}
		else
		{
			result = m_flash_manage.make_song_request(request,sizeof(request)/sizeof(TCHAR),song_xml_list.c_str(),false,page_index,operate_type,SONG_SHOW_MODE_LIST);
		}
		if (result)
		{
			flash_player_call_function(request);
		}
		//得到页码
		result = m_play_U_disk_song.get_song_row_and_page_count(row,page_count,cur_page_number);
		if (result)
		{
			//显示页码
			show_row_and_page_count(L"false",row,page_count,cur_page_number);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::play_select_game(const TCHAR *args)
{
	try
	{
		int game_number=0;
		TCHAR game_path[256];
		bool result=false;
		TCHAR request[1024];
		TCHAR data[1024];

		memset(game_path,0x0,sizeof(game_path));
		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//得到选中的游戏编号
		swscanf(args,L"%d",&game_number);
		if ((1==game_number)||(2==game_number))
		{
			//前两个是钢琴和架子鼓，不用发任何信息
			if (m_local_game_flash_player_exist)
			{
				//隐藏窗口
				m_local_game_flash_player.ShowWindow(SW_HIDE);
			}
			return;
		}
		//从第一个开始取游戏
		game_number -= 3;
		//得到选中的游戏路径
		result = m_game_manager.get_select_game_path(game_path,game_number);
		if (!result)
		{
			if (m_local_game_flash_player_exist)
			{
				//隐藏窗口
				m_local_game_flash_player.ShowWindow(SW_HIDE);
			}
			flash_show_tip_message(39);
			return;
		}
		//开始播放游戏
		if (m_local_game_flash_player_exist)
		{
			m_local_game_flash_player.LoadMovie(0,game_path);
			m_local_game_flash_player.BringWindowToTop();
			m_local_game_flash_player.ShowWindow(SW_SHOW);
		}
		//swprintf(data,L"<data><info path=\"%s\"/></data>",game_path);
		//result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"GameList",data);
		//if (result)
		//{
		//	flash_player_call_function(request);
		//}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::flash_message_call_switch_screen_pc(const TCHAR *args,bool time_protect)
{
	try
	{
		int video_type=0;
		bool result=false;
		config_file_manager config_file;

		if (CLOSE_ROOM_STATE==m_pc_state)
		{
			//关房状态，不允许切换视频
			return;
		}
		if (time_protect)
		{
			//防止频繁切换
			double last_time = video_switch_timer.last_time();
			if (last_time<PLAY_VIDEO_MIN_TIME_LENGTH)
			{
				return;
			}
			//重新计时
			video_switch_timer.start();
		} 

		//消取静音处理
		result = DealMuteState(true);

		//得到视频类型
		swscanf(args,L"%d",&video_type);
		switch(video_type)
		{
		case 1:  //歌曲视频
			{
				if ((VIDEO_TYPE_LOBBY_LIVE==pc_play_video_type)&&m_lobby_live_window_exist)
				{
					//停止大厅视频
					m_player_manager.preview_close();
					m_lobby_live_window.show_window(false);
				}

				if((VIDEO_TYPE_TV==pc_play_video_type)&&m_tv_window_exist)
				{
					//停止电视直播
					m_player_manager.preview_close();
					m_tv_window.show_window(false);
				}

				//简K版本所有的直接同步 2013-1-17 yangzhenglun
				//if ((VIDEO_TYPE_SONG!=pc_play_video_type)&&(VIDEO_TYPE_SONG!=tv_play_video_type))
				if (VIDEO_TYPE_SONG!=tv_play_video_type)
				{
					//显示预览
					pc_play_video_type = VIDEO_TYPE_SONG;
					tv_play_video_type = VIDEO_TYPE_SONG;

					m_bInPageVideo = false;
					//播放歌曲
					flash_message_call_function(SONG_NEXT);

					pc_show_video_window();
				}

			}
			break;
		case 2:  //大厅直播
			{
				//2013-1-17 yangzhenglun
				if (VIDEO_TYPE_LOBBY_LIVE!=pc_play_video_type)
				{
					song_info internet_video_info;
					std::wstring server_ip;
					std::wstring server_port;
					TCHAR live_path[64];
					int link_server_number=0;
					bool result=false;

					memset(live_path,0x0,sizeof(live_path));

					result = m_player_manager.is_playing();
					if (!result)
					{
						//如果是暂停状态改成播放状态
						flash_message_call_function(SONG_PLAY_PAUSE);
					}

					//改变电视端播放视频类型
					tv_play_video_type=VIDEO_TYPE_LOBBY_LIVE;
					//pc端回到播放预览歌曲
					flash_message_call_switch_screen_pc(L"1",false);
					
					//设置歌曲播放类型
					internet_video_info.set_video_type(PLAY_LOBBY_LIVE);
					//add by yzg 2015-12-07
					internet_video_info.set_flash_page_code(page_video);
					internet_video_info.set_song_name(L"大厅直播");
					//add end
					//读取配置文件
					server_ip = config_file.read_string(L"lobby_live",L"server_ip",L"234.1.1.1");
					server_port = config_file.read_string(L"lobby_live",L"server_port",L"1234");
					//swprintf(live_path,L"udp://%s:",server_ip.c_str());
					//直播IP必须赋值到六个服务器路径中
					//internet_video_info.set_server_path1(live_path);
					//直播的端口号必须赋值给歌曲的相对路径
					//internet_video_info.set_song_relative_path(server_port.c_str()); 
					if (m_tv_topbox_mode)
					{
						//机顶盒方式  改成单播方式  FOR ZHEN 2012-11-29
						if (TV_GROUP_PLAY_MODE == m_tv_play_mode)
						{
							swprintf(live_path,L"shn://%s:%s",server_ip.c_str(),server_port.c_str());
						}
						else
						{
							swprintf(live_path,L"shn://%s@%s:4360",server_port.c_str(),server_ip.c_str());
						}

					}
					else
					{
						//vlc方式
						swprintf(live_path,L"udp://%s:%s",server_ip.c_str(),server_port.c_str());
					}

					internet_video_info.set_local_path(live_path);

					//设置给控件
					result = m_player_manager.set_video_file(internet_video_info,link_server_number,m_music_wave_path,m_voice_wave_path,m_is_scoring);
					if (result)
					{
						m_bInPageVideo = true;
						//显示提示字幕
						result = play_osd_text(L"即将播放大厅视频，请等待......",OSD_RIGHT_TO_LEFT,10);

						tv_play_video_type=VIDEO_TYPE_LOBBY_LIVE;
						pc_play_video_type=VIDEO_TYPE_SONG;

						WriteLog(__FL__, L"电视上，开始播放大厅直播");
					}
					else
					{
						//如果是大厅直播，要求回到歌曲视频
						flash_message_call_switch_screen_pc(L"1",false);
					}
				}

			}
			break;
#ifdef OLD_TV_PLAY_MODE   //旧的电视卡方式
		case 3:
			{
				if((VIDEO_TYPE_TV!=pc_play_video_type) && (VIDEO_TYPE_TV!=tv_play_video_type))
				{
					//第一次要打开
					result = m_player_manager.TV_open(NULL,0,SD_TVSTANDARD_AUTO);
					if (1!=result)
					{
						WriteLog(__FL__, L"电视卡打开失败");
						break;
					}
				}
				if (VIDEO_TYPE_TV==tv_play_video_type)
				{
					//输出到电视机和pc
					result = m_player_manager.TV_control(TVC_SET_TVOUT,1,1);
				}
				else if (m_pip_show)
				{
					result = m_player_manager.TV_control(TVC_SET_TVOUT,2,1);
				}
				else
				{
					//只输出到pc
					result = m_player_manager.TV_control(TVC_SET_TVOUT,0,1);
				}
				if (VIDEO_TYPE_TV!=pc_play_video_type)
				{
					if (m_lobby_live_window_exist&& m_lobby_live_window.IsWindowVisible())
					{
						//停止大厅视频
						m_player_manager.preview_close();
						m_lobby_live_window.show_window(false);
					}
					if (m_screen_show_window_exist && m_screen_show_window.IsWindowVisible())
					{
						//停止歌曲播放
						m_screen_show_window.show_window(false);
					}
					if (m_preview_window_exist && m_preview_window.IsWindowVisible())
					{
						//预览歌曲
						m_player_manager.preview_close();
						m_preview_window.show_window(false);
					}
					//显示大厅直播窗口
					m_tv_window.MoveWindow(CRect(m_switch_screen_left_top_x,m_switch_screen_left_top_y,m_switch_screen_right_button_x,m_switch_screen_right_button_y),TRUE);
					m_tv_window.BringWindowToTop();
					m_tv_window.show_window(true);
					pc_play_video_type = VIDEO_TYPE_TV;
				}
			}
			break;
		case 5:  //频道加
			{
				if ((VIDEO_TYPE_TV==pc_play_video_type) || (VIDEO_TYPE_TV==tv_play_video_type))
				{
					result = m_player_manager.TV_control(TVC_SET_CHL_INCREASE,0,0);
				}
			}
			break;
		case 6:   //频道减
			{
				if ((VIDEO_TYPE_TV==pc_play_video_type) || (VIDEO_TYPE_TV==tv_play_video_type))
				{
					result = m_player_manager.TV_control(TVC_SET_CHL_DECREASE,0,0);
				}
			}
			break;
#else                      //服务器组播方式
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:  //电视节目
			{
				//所有的直接同步 2013-1-17 yangzhenglun
				if(m_soft_decode_window_exist)
				{
					song_info internet_video_info;
					int link_server_number=0;
					bool result=false;

					result = m_player_manager.is_playing();
					if (!result)
					{
						//如果是暂停状态改成播放状态
						flash_message_call_function(SONG_PLAY_PAUSE);
					}
					//改变电视端播放视频类型
					tv_play_video_type=VIDEO_TYPE_TV;
					pc_play_video_type=VIDEO_TYPE_SONG;
					//设置歌曲播放类型
					internet_video_info.set_video_type(PLAY_TV); 
					internet_video_info.set_flash_page_code(page_video);
					internet_video_info.set_song_name(L"电视节目");
					if (m_tv_topbox_mode)
					{
						//机顶盒方式 改成单播方式  FOR ZHEN 2012-11-29
						if (TV_GROUP_PLAY_MODE == m_tv_play_mode)
						{
							swprintf(m_tv_live_url,L"shn://%s:%d",m_tv_server_ip[video_type-3].c_str(),m_tv_channel[video_type-3]);
						}
						else
						{
							swprintf(m_tv_live_url,L"shn://%d@%s:4360",m_tv_channel[video_type-3],m_tv_server_ip[video_type-3].c_str());
						}

					}
					else
					{
						//采集卡方式
						swprintf(m_tv_live_url,L"hik://%d@%s",m_tv_channel[video_type-3],m_tv_server_ip[video_type-3].c_str());
					}

					//直播TV必须赋值到本地路径中
					internet_video_info.set_local_path(m_tv_live_url);
					//设置给控件 
					result = m_player_manager.set_video_file(internet_video_info,link_server_number,m_music_wave_path,m_voice_wave_path,m_is_scoring);
					if (result)
					{
						m_bInPageVideo = true;
						//显示提示字幕
						result = play_osd_text(L"即将播放电视视频，请等待......",OSD_RIGHT_TO_LEFT,10);
 
					}
					else
					{
						WriteLog(__FL__, L"如果是TV直播，要求回到歌曲视频");
						//如果是TV直播，要求回到歌曲视频					 
						flash_message_call_switch_screen_pc(L"1",false);
					}
				}
			}
			break;
#endif
		default:
			break;
		}
		//设置高亮按钮状态
		m_video_button_number = video_type-1;
		set_flash_button_state(L"video_button",m_video_button_number);
		//显示提示文字
		show_video_page_tip_msg();
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::video_synchro_to_TV(const TCHAR *args)
{
	try
	{
		int select_number=0;
		config_file_manager config_file;
		bool result=false;

		//得到选中的编号
		swscanf(args,L"%d",&select_number);
		switch(select_number)
		{
		case 1:  //全屏欣赏
			{
				PostMessage(DM_SCREEN_VIDEO_CLICK);
			}
			break;
		case 2:    //同步到电视
			{
				switch(pc_play_video_type)
				{
				case VIDEO_TYPE_PREVIEW_SONG:
				case VIDEO_TYPE_SONG:        //电视同步播放歌曲
					{
#ifdef OLD_TV_PLAY_MODE     //旧的电视卡方式
						if (VIDEO_TYPE_TV==tv_play_video_type)
						{
							//关闭电视
							m_player_manager.TV_close();
						}
#endif
						if (VIDEO_TYPE_SONG!=tv_play_video_type)
						{
							//改变视频播放类型
							tv_play_video_type = VIDEO_TYPE_SONG;
							//设置播放状态
							m_video_play_manager.set_player_cur_state(PLAY_SONG_STATE);
							m_video_play_manager.set_player_next_state(PLAY_SONG_STATE);

							//下一首歌曲
							WriteLog(__FL__, L"屏切页面，播放下一首歌曲");
							flash_message_call_function(SONG_NEXT);

							WriteLog(__FL__, L"电视上，开始播放歌曲");
						}
						if (m_preview_window_exist && (VIDEO_TYPE_PREVIEW_SONG==pc_play_video_type))
						{
							//关闭预览
							m_player_manager.preview_close();
							m_preview_window.show_window(false);
							//先置状态，在显示视频
							pc_play_video_type = VIDEO_TYPE_SONG;
							//播放电视同步歌曲
							pc_show_video_window();
						}
					}
					break;
				case VIDEO_TYPE_LOBBY_LIVE:
					{
#ifdef OLD_TV_PLAY_MODE   //旧的电视卡方式
						if (VIDEO_TYPE_TV==tv_play_video_type)
						{
							//关闭电视
							m_player_manager.TV_close();
						}
#endif
						if(VIDEO_TYPE_LOBBY_LIVE!=tv_play_video_type)
						{
							song_info internet_video_info;
							std::wstring server_ip;
							std::wstring server_port;
							TCHAR live_path[64];
							int link_server_number=0;
							bool result=false;

							memset(live_path,0x0,sizeof(live_path));

							result = m_player_manager.is_playing();
							if (!result)
							{
								//如果是暂停状态改成播放状态
								flash_message_call_function(SONG_PLAY_PAUSE);
							}
							//改变电视端播放视频类型
							tv_play_video_type=VIDEO_TYPE_LOBBY_LIVE;
							//pc端回到播放预览歌曲
							flash_message_call_switch_screen_pc(L"1",false);
							//设置歌曲播放类型
							internet_video_info.set_video_type(PLAY_LOBBY_LIVE);
							//读取配置文件
							server_ip = config_file.read_string(L"lobby_live",L"server_ip",L"234.1.1.1");
							server_port = config_file.read_string(L"lobby_live",L"server_port",L"1234");
							//swprintf(live_path,L"udp://%s:",server_ip.c_str());
							//直播IP必须赋值到六个服务器路径中
							//internet_video_info.set_server_path1(live_path);
							//直播的端口号必须赋值给歌曲的相对路径
							//internet_video_info.set_song_relative_path(server_port.c_str());
							if (m_tv_topbox_mode)
							{
								//机顶盒方式
								if (TV_GROUP_PLAY_MODE == m_tv_play_mode)
								{
									swprintf(live_path,L"shn://%s:%s",server_ip.c_str(),server_port.c_str());
								}
								else
								{
									swprintf(live_path,L"shn://%s@%s:4360",server_port.c_str(),server_ip.c_str());
								}
							}
							else
							{
								//vlc方式
								swprintf(live_path,L"udp://%s:%s",server_ip.c_str(),server_port.c_str());
							}
							internet_video_info.set_local_path(live_path);
							result = m_player_manager.set_video_file(internet_video_info,link_server_number,m_music_wave_path,m_voice_wave_path,m_is_scoring);
							if (result)
							{
								//显示提示字幕
								result = play_osd_text(L"即将播放大厅视频，请等待......",OSD_RIGHT_TO_LEFT,10);

								tv_play_video_type=VIDEO_TYPE_LOBBY_LIVE;

								WriteLog(__FL__, L"电视上，开始播放大厅直播");
							}
							else
							{
								//如果是大厅直播，要求回到歌曲视频
								switch_screen_play_song_video();
							}
						}
					}
					break;
				case VIDEO_TYPE_TV:
					{
#ifdef OLD_TV_PLAY_MODE	   //旧的电视卡方式
						if (VIDEO_TYPE_TV!=tv_play_video_type)
						{
							//同时输出到电视和pc
							m_player_manager.TV_control(TVC_SET_TVOUT,1,1);
							//设置播放电视标示
							tv_play_video_type = VIDEO_TYPE_TV;
							//滚动字幕
							show_song_name();
							WriteLog(__FL__, L"电视上，开始播放电视节目");
						}
#else
						if(m_soft_decode_window_exist)
						{
							song_info internet_video_info;
							int link_server_number=0;
							bool result=false;

							result = m_player_manager.is_playing();
							if (!result)
							{
								//如果是暂停状态改成播放状态
								flash_message_call_function(SONG_PLAY_PAUSE);
							}
							//改变电视端播放视频类型
							tv_play_video_type=VIDEO_TYPE_TV;
							//pc端回到播放预览歌曲
							flash_message_call_switch_screen_pc(L"1",false);
							//设置歌曲播放类型
							internet_video_info.set_video_type(PLAY_TV);
							//直播TV必须赋值到本地路径中
							internet_video_info.set_local_path(m_tv_live_url);
							//设置给控件
							result = m_player_manager.set_video_file(internet_video_info,link_server_number,m_music_wave_path,m_voice_wave_path,m_is_scoring);
							if (result)
							{
								//显示提示字幕
								result = play_osd_text(L"即将播放电视视频，请等待......",OSD_RIGHT_TO_LEFT,10);

								WriteLog(__FL__, L"电视上，开始播放电视直播");
							}
							else
							{
								//如果是TV直播，要求回到歌曲视频
								switch_screen_play_song_video();
							}
						}
#endif
					}
					break;
				default:
					break;
				}
			}
			break;
		case 3:  //画中画
			{
#ifdef OLD_TV_PLAY_MODE   //旧的电视卡方式
				if (!m_soft_decode_window_exist)
				{
					//只有软解支持画中画
					break;
				}
				
				if (!m_pip_show && (VIDEO_TYPE_TV==pc_play_video_type) && (VIDEO_TYPE_TV!=tv_play_video_type))
				{
					//标记画中画打开
					m_pip_show = true;
					//同时输出到电视和pc
					m_player_manager.TV_control(TVC_SET_TVOUT,2,1);
				}
				else if (m_pip_show)
				{
					m_pip_show = false;
					//显示中，需要关闭
					if(VIDEO_TYPE_TV!=pc_play_video_type)
					{
						//关闭电视
						m_player_manager.TV_control(TVC_SET_TVOUT,0,0);
						m_player_manager.TV_close();
					}
					else
					{
						m_player_manager.TV_control(TVC_SET_TVOUT,0,1);
					}
				}
#else
				if (!m_pip_show && (VIDEO_TYPE_TV==pc_play_video_type) && (VIDEO_TYPE_TV!=tv_play_video_type))
				{
					//pc端是电视就画中画
					m_player_manager.preview_control(PVC_SET_TVOUT,2,0);
					//改变标示
					m_pip_show = true;
				}
				else if (m_pip_show)
				{
					m_player_manager.preview_control(PVC_SET_TVOUT,0,0);
					//改变标示
					m_pip_show = false;
				}
#endif
			}
			break;
		default:
			break;
		}
		//显示提示文字
		show_video_page_tip_msg();
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::switch_screen_play_song_video(void)
{
	try
	{
		//pc端回到播放歌曲
		flash_message_call_switch_screen_pc(L"1",false);
		//电视也同步成歌曲
		//video_synchro_to_TV(L"2");
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::preview_next_song(void)
{
	try
	{
		song_info preview_song_info;
		TCHAR song_path[256];
		int link_server_number=0;
		bool result=false;

		memset(song_path,0x0,sizeof(song_path));
		//设置播放状态
		m_video_play_manager.set_player_cur_state(TEST_SONG_STATE);
		m_video_play_manager.set_player_next_state(TEST_SONG_STATE);
		//得到预览歌曲
		int ret = m_video_play_manager.get_next_play_video(preview_song_info,NULL,false);
		if (1!=ret)
		{
			m_video_play_manager.set_player_cur_state(IDLESSE_STATE);
			m_video_play_manager.set_player_next_state(IDLESSE_STATE);
			ret = m_video_play_manager.get_next_play_video(preview_song_info,NULL,false);
		}
		//得到服务器路径
		link_server_number = m_link_server_number;
		result = preview_song_info.get_path(song_path,m_check_video_exist,link_server_number);
		//返回失败，不能打开
		if (m_preview_window_exist&&result)
		{
			//改变选择的服务器编号
			change_link_server_number(link_server_number);
			//关闭预览
			m_player_manager.preview_close();
			//改变标示
			m_pip_show = false;
			//打开预览
			m_player_manager.preview_open(song_path,(long)m_preview_window.m_hWnd);
		}
		//显示视频窗口
		pc_show_video_window();

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::flash_show_custom_song(const TCHAR* data,int song_nmuber,bool focus)
{
	try
	{
		TCHAR request[1024];
		TCHAR opinion[1024];
		TCHAR custom_song[256];
		bool result=false;

		if (NULL==data)
		{
			return;
		}

		memset(request,0x0,sizeof(request));
		memset(opinion,0x0,sizeof(opinion));
		memset(custom_song,0x0,sizeof(custom_song));

		swprintf(custom_song,L"custom_song%d",song_nmuber);

		if (focus)
		{
			swprintf(opinion,L"<data><info custom_song=\"%s\" focus=\"true\" /></data>",data);
		}
		else
		{
			swprintf(opinion,L"<data><info custom_song=\"%s\" focus=\"false\" /></data>",data);
		}

		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),custom_song,opinion);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}
	 
	return;
}

void Cflashktv10Wnd::flash_show_others_opinion(const TCHAR *data,bool focus)
{
	try
	{
		TCHAR request[1024];
		TCHAR opinion[1024];
		bool result=false;

		if (NULL==data)
		{
			return;
		}

		memset(request,0x0,sizeof(request));
		memset(opinion,0x0,sizeof(opinion));

		if (focus)
		{
			swprintf(opinion,L"<data><info opinion=\"%s\" focus=\"true\" /></data>",data);
		}
		else
		{
			swprintf(opinion,L"<data><info opinion=\"%s\" focus=\"false\" /></data>",data);
		}
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"others_opinion",opinion);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_show_custom_phone(const TCHAR *data,bool focus)
{
	try
	{
		TCHAR request[1024];
		TCHAR telphone[1024];
		bool result=false;

		if (NULL==data)
		{
			return;
		}

		memset(request,0x0,sizeof(request));
		memset(telphone,0x0,sizeof(telphone));

		if (focus)
		{
			swprintf(telphone,L"<data><info phone=\"%s\" focus=\"true\" /></data>",data);
		}
		else
		{
			swprintf(telphone,L"<data><info phone=\"%s\" focus=\"false\" /></data>",data);
		}
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"custom_phone",telphone);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_show_contact_phone(const TCHAR *data,bool focus)
{
	try
	{
		TCHAR request[1024];
		TCHAR telphone[1024];
		bool result=false;

		if (NULL==data)
		{
			return;
		}

		memset(request,0x0,sizeof(request));
		memset(telphone,0x0,sizeof(telphone));

		if (focus)
		{
			swprintf(telphone,L"<data><info phone=\"%s\" focus=\"true\" /></data>",data);
		}
		else
		{
			swprintf(telphone,L"<data><info phone=\"%s\" focus=\"false\" /></data>",data);
		}
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"contact_phone",telphone);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::flash_clear_surver_result(void)
{
	try
	{
		TCHAR request[1024];
		bool result=false;

		
		memset(request,0x0,sizeof(request));
		
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"surver_result",L"clear");
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_message_call_custom_phone(const TCHAR* args)
{
	try
	{
		size_t len=0; 
		if (NULL==args)
		{
			return;
		}

		if (0==_tcscmp(args,L"enter"))
		{
			//回删
			len = m_custom_phone.length();
			if (len<=0)
			{
				return;
			}
			m_custom_phone = m_custom_phone.substr(0,len-1);
		}
		else if (0==_tcscmp(args,L"delete"))
		{
			//清空
			m_custom_phone.clear();
		}
		else
		{
			//写联系方式
			m_custom_phone += args;
			len = m_custom_phone.length();
			if (len>12)
			{
				m_custom_phone.clear();
			}
		}
		//显示到界面
		flash_show_custom_phone(m_custom_phone.c_str(),true);
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_message_call_write_phone(const TCHAR *args)
{
	try
	{
		size_t len=0; 
		if (NULL==args)
		{
			return;
		}
 
		if (0==_tcscmp(args,L"enter"))
		{
			//回删
			len = m_contact_phone.length();
			if (len<=0)
			{
				return;
			}
			m_contact_phone = m_contact_phone.substr(0,len-1);
		}
		else if (0==_tcscmp(args,L"delete"))
		{
			//清空
			m_contact_phone.clear();
		}
		else
		{
			//写联系方式
			m_contact_phone += args;
			len = m_contact_phone.length();
			if (len>11)
			{
				//m_contact_phone.clear();
				m_contact_phone = m_contact_phone.substr(0,len-1);
			}
		}
		//显示到界面
		m_input_box_show_help[1]=false;
		flash_show_contact_phone(m_contact_phone.c_str(),true);
	}
	catch (...)
	{
		
	}
	return;
}
 


void Cflashktv10Wnd::flash_message_call_member_manager(const TCHAR *args)
{
		try
	{
		int number=0;
		bool result=false;
		int page_index=0;

		if (NULL==args)
		{
			return;
		}
		//得到页面索引
		page_index = m_flash_manage.get_last_page_index();

		swscanf(args,L"%d",&number);
		switch(number)
		{
		case 1:  //会员登录
			{
				if(page_member_manager==page_index)
				{
					change_member_manage_state(MEMBER_LOGIN_STATE);
				}
				else
				{
					flash_show_tip_message(44);
				}
			}
			break;
		case 2:   //会员注册
			{
				if(page_member_manager==page_index)
				{
					change_member_manage_state(MEMBER_REGISTER_STATE);
				}
				else
				{
					flash_show_tip_message(44);
				}
			}
			break;
		case 3:  //会员修改密码
			{
				if(page_member_manager==page_index)
				{
					change_member_manage_state(MEMBER_CHANGE_PSW_STATE);
				}
				else
				{
					flash_show_tip_message(44);
				}
			}
			break;
		case 4:  //退出会员
			{
				if (m_member_already_login)
				{
					//修改标示
					m_member_already_login = false;
					//改状态
					if (m_video_dating_info.nstatus == VD_BUSY)
					{
						flash_message_call_ex(L"quit_video_dating", L""); //退出视频
					}
					send_server_video_dating_data(VD_CLOSE_ROOM);
					send_server_video_dating_data(VD_IDLE);
					//回到辅助功能页面
					result = page_change(page_member_manager);
					if (result)
					{
						//改变会员状态
						change_member_manage_state(MEMBER_LOGIN_STATE);
						//清空文本中输入的内容
						clear_member_manage_input_text();
					}
				}
				else
				{
					flash_show_tip_message(45);
				}
			}
			break;
		default:
			break;
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::member_register_dialog_page_jump(TCHAR* command,TCHAR* tip_message,bool jump_state)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//改变会员管理状态
		if (jump_state)
		{
			swprintf(data,L"<data><info tip=\"%s\" state=\"true\" /></data>",tip_message);
		}
		else
		{
			swprintf(data,L"<data><info tip=\"%s\" state=\"false\" /></data>",tip_message);
		}
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}
	
	return;
}

void Cflashktv10Wnd::change_member_manage_state(int state)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//改变会员管理状态
		swprintf(data,L"<data><info state=\"%d\" /></data>",state);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"vip_manage_state",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		show_member_manager_input_text(1, L"");

		//记录会员管理状态
		m_member_manage_state=state;
		//默认是输入会员号
		m_member_input_type=1;
		//清空文本中输入的内容
		clear_member_manage_input_text();
		//改变帮助内容
		//show_help_info();
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::clear_member_manage_input_text(void)
{
	try
	{
		//默认是输入会员号
		m_member_input_type=1;

		//清空所有密码
		memset(m_member_name,0x0,sizeof(m_member_name));                        //会员的名字
		memset(m_member_password,0x0,sizeof(m_member_password));                //会员的密码
		memset(m_member_old_password,0x0,sizeof(m_member_old_password));        //会员旧密码
		memset(m_member_ok_password,0x0,sizeof(m_member_ok_password));          //会员的确认密码

		//清空输入框中显示的内容
		switch(m_member_manage_state)
		{
		case MEMBER_LOGIN_STATE:    //登录状态
			{
				show_member_manager_input_text(2,L"");
				show_member_manager_input_text(1,L"");
			}
			break;
		case MEMBER_REGISTER_STATE:   //会员注册状态
			{
				show_member_manager_input_text(2,L"");
				show_member_manager_input_text(3,L"");
				show_member_manager_input_text(1,L"");				
			}
			break;
		case MEMBER_CHANGE_PSW_STATE:  //改变密码
			{
				show_member_manager_input_text(2,L"");
				show_member_manager_input_text(3,L"");
				show_member_manager_input_text(4,L"");
				show_member_manager_input_text(1,L"");
			}
			break;
		default:
			break;
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::show_member_manager_input_text(int textbox_number,TCHAR *text)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[1024];
		bool result=false;
		TCHAR show_data[256];

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		memset(show_data,0x0,sizeof(show_data));

		/*
		if (1==textbox_number)
		{
			_tcscpy(show_data,text);
		}
		else
		{
			if ((MEMBER_REGISTER_STATE == m_member_manage_state) && (2 == textbox_number))
			{
				_tcscpy(show_data,text);
			}
			else
			{
				for (int i=0;i<_tcslen(text);i++)    //密码显示星号
				{
					_tcscat(show_data,L"*");
				}
			}
		}
		*/
		swprintf(data,L"<data><info textbox=\"%d\" text=\"%s\" /></data>",textbox_number-1,text);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"vip_manage_text",data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::flash_message_call_recorder_audio_type(const TCHAR *args,bool recv_msg)
{
	try
	{
		int recorder_msg=0;
		bool result=false;
		song_info playing_song_info;
		enum PLAY_SONG_TYPE song_type;
		TCHAR send_data[256];

		memset(send_data,0x0,sizeof(send_data));

		//得到选择的编号
		swscanf(args,L"%d",&recorder_msg);

		if (recv_msg&&(2==m_master_slave_control_flag))
		{
			switch(recorder_msg)
			{
			case FLASH_SEND_TAPE_START:         //开始录音
				{
					m_is_recording = true;
				}
				break;
			case FLASH_SEND_TAPE_STOP:          //停止录音
				{
					m_is_recording = false;
				}
				break;
			}

			//设置按钮状态 ZHEN 2013-09-06
			set_button_show_state(TAPE_BUTTON_STATE,m_is_recording);

			return;
		}

		switch(recorder_msg)
		{
		case FLASH_SEND_TAPE_START:         //开始录音
			{
				if (m_is_recording)
				{
					break;
				}
				//	if (m_enter_guide_song && m_show_guide_osd)
				//  {
				//		flash_show_tip_message(86);
				//		break;
				//	}
				if (VIDEO_TYPE_SONG!=tv_play_video_type)
				{
					//只有选择的正常播放的歌曲，才可以录音
					flash_show_tip_message(48);
					break;
				}

				result = m_player_manager.is_play_video_ad();
				if (result)
				{
					//正在播放广告，不启动录音功能
					flash_show_tip_message(48);
					break;
				}
				result = m_video_play_manager.get_playing_video(playing_song_info);
				if (result)
				{
					song_type = playing_song_info.get_video_type();
					if (PLAY_SONG_TYPE_SELECT_SONG!=song_type)
					{
						//只有选择的正常播放的歌曲，才可以录音
						flash_show_tip_message(48);
						break;
					}
				}
				//改为录音状态
				m_is_recording=true;

				//发送给主控
				swprintf(send_data,L"RECORDING%d",recorder_msg);
				send_master_slave_data(send_data,NULL);
				if (2!=m_master_slave_control_flag)
				{ 
					CTime cur_time = CTime::GetCurrentTime();
					memset(m_music_wave_path,0x0,sizeof(m_music_wave_path));
					memset(m_voice_wave_path,0x0,sizeof(m_voice_wave_path));
					swprintf(m_music_wave_path,L"%s\\log\\shplayer-%02d%02d%02d.log",m_work_path,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
					swprintf(m_voice_wave_path,L"%s\\%s-%02d%02d%02d.wav",m_recorder_dir.c_str(),m_show_room_name,cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());

					//开始录音 zhen 2013-08-14
					start_recorder_audio();
				}

				//回放当前歌曲，1表示必须回放
				flash_message_call_function(SONG_REPLAY,1);
			}
			break;
		case FLASH_SEND_TAPE_STOP:          //停止录音
			{
				stop_recorder_audio(true,true,false);

			}
			break;
		default:
			break;
		}
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::flash_message_call_recorder_audio(const TCHAR *args)
{
	try
	{
		int recorder_msg=0;
		bool result=false;
		song_info playing_song_info;
		enum PLAY_SONG_TYPE song_type;
		TCHAR send_data[256];

		memset(send_data,0x0,sizeof(send_data));

		//得到选择的编号
		swscanf(args,L"%d",&recorder_msg);

		switch(recorder_msg)
		{
		case FLASH_SEND_TAPE_START:         //开始录音
			{
				if (m_is_recording)
				{
					break;
				}
				/*
				if (m_enter_guide_song && m_show_guide_osd)
				 {
					flash_show_tip_message(86);
					break;
				}
				if (VIDEO_TYPE_SONG!=tv_play_video_type)
				{
					//只有选择的正常播放的歌曲，才可以录音
					flash_show_tip_message(48);
					break;
				}
				*/

				result = m_player_manager.is_play_video_ad();
				if (result)
				{
					//正在播放广告，不启动录音功能
					flash_show_tip_message(48);
					break;
				}
				result = m_video_play_manager.get_playing_video(playing_song_info);
				if (result)
				{
					song_type = playing_song_info.get_video_type();
					if (PLAY_SONG_TYPE_SELECT_SONG!=song_type)
					{
						//只有选择的正常播放的歌曲，才可以录音
						//flash_show_tip_message(48);
						break;
					}
				}
				//改为录音状态
				m_is_recording=true;
				
				//发送给主控
				swprintf(send_data,L"RECORDING%d",recorder_msg);
				send_master_slave_data(send_data,NULL);
				if (2!=m_master_slave_control_flag)
				{
					//开始录音 zhen 2013-08-14
					//start_recorder_audio();
					//回放当前歌曲，1表示必须回放
					flash_message_call_function(SONG_REPLAY,1);
				}
			}
			break;
		case FLASH_SEND_TAPE_STOP:          //停止录音
			{
				stop_recorder_audio(true,true,false);
			}
			break;
		default:
			break;
		}
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::flash_message_call_system_manager(const TCHAR *args)
{
	try
	{
		int number=0;
		size_t len=0;

		if (NULL==args)
		{
			return;
		}
		
		swscanf(args,L"%d",&number);
		switch(number)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			{
				m_input_code += args;
				len = m_input_code.length();
				if (len>16)
				{
					m_input_code.clear();
				}

				//显示密码
				show_system_manage_code(m_input_code.c_str());
			}
			break;
		case 10:  //回删
			{
				len = m_input_code.length();
				if (len>0)
				{
					m_input_code = m_input_code.substr(0,len-1);
				}

				//显示密码
				show_system_manage_code(m_input_code.c_str());
			}
			break;
		case 11:   //确定
			{
				password_function_judgement(m_input_code.c_str());
#ifdef DON_GUAN_K_PLUS
				m_input_code.clear();
#endif // DON_GUAN_K_PLUS				
			}
			break;
		default:
			break;
		}
	}
	catch (...)
	{
		
	}
	return;
}

bool Cflashktv10Wnd::show_system_manage_code(const TCHAR *text)
{
	try
	{
		TCHAR request[256];
		TCHAR data[256];
		TCHAR Asterisk[128];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		memset(Asterisk,0x0,sizeof(Asterisk));

		//转成*号显示
		for(int i=0;i<m_input_code.length();i++)
		{
			_tcscat(Asterisk,L"*");
		}

		swprintf(data,L"<data><info code=\"%s\"/></data>",Asterisk);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"system_code",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void Cflashktv10Wnd::show_password_window(void)
{
	try
	{
		double click_elapse=0;

		if (m_click_count<=0)
		{
			m_password_timer.start();
			m_click_count++;
		}
		else
		{
			click_elapse = m_password_timer.last_time();
			if (click_elapse<2.0)
			{
				m_click_count++;
			}
			else
			{
				m_click_count = 1;
			}
			m_password_timer.start();
		}
		if (5==m_click_count)
		{
			//显示密码框
			flash_message_call_page_jump(page_system_manager);
		}
	}
	catch (...)
	{

	}
	return;
}


bool Cflashktv10Wnd::show_drawing_image_to_tv(void)
{
	try
	{
		CDC memory_dc;
		TCHAR path[256];
		bool result=false;
		Status return_status;
		int des_width=0;
		int des_height=0;
		BitmapData bitmapData;

		memset(path,0x0,sizeof(path));

		//得到要保存的图片宽度和高度
		if (m_soft_decode_window_exist&&m_full_screen_show)
		{
			//软解，并且全屏显示
			des_height = m_sencond_display_height-250;
			des_width = des_height*m_sencond_display_width/m_sencond_display_height;

			//不拉伸绘图区域
		//	if (m_painting_area_bottom_y-m_painting_area_top_y<des_height)
	/*		{
				des_height = m_painting_area_bottom_y-m_painting_area_top_y;
				des_width = m_painting_area_right_x-m_painting_area_left_x;
			}*/
		}
		else
		{
			des_width = 320;
			des_height = 240;
		}

		//get desktop window
		CWnd *desktop_wnd = GetDesktopWindow();
		//desktop dc
		CClientDC desktop_dc(desktop_wnd);
		//创建一个和桌面DC兼容的DC
		memory_dc.CreateCompatibleDC(&desktop_dc); 
		//创建兼容桌面的位图
		HBITMAP  desktop_bitmap = ::CreateCompatibleBitmap(desktop_dc.m_hDC, des_width,des_height);
		//选择和桌面DC兼容的位图
		HBITMAP old_bitmap = (HBITMAP)::SelectObject(memory_dc,desktop_bitmap);
		//从桌面DC拷贝
		memory_dc.StretchBlt(0, 0, des_width,des_height,&desktop_dc, m_painting_area_left_x,m_painting_area_top_y,m_painting_area_right_x,m_painting_area_bottom_y, SRCCOPY); 
		//选择原来的位图
		SelectObject(memory_dc,old_bitmap);  
		{
			//创建bitmap位图
			Bitmap save_bitmap(des_width,des_height,PixelFormat32bppARGB),paint_bitmap(desktop_bitmap,NULL);
			Graphics  graphics(&save_bitmap);  
			graphics.DrawImage(&paint_bitmap, 0, 0,0,0,des_width,des_height,UnitPixel);  

			CLSID              encoderClsid;  
			EncoderParameters  encoderParameters;  

			int qurity = 100;

			encoderParameters.Count  =  1;  
			encoderParameters.Parameter[0].Guid  =  EncoderQuality;  
			encoderParameters.Parameter[0].Type  =  EncoderParameterValueTypeLong;  
			encoderParameters.Parameter[0].NumberOfValues  =  1;  
			encoderParameters.Parameter[0].Value  =  &qurity; 

			result = GetEncoderClsid(L"image/bmp",  &encoderClsid);  
			if (!result)
			{
				return false;
			}
			//得到路径
			swprintf(path,L"%s\\draw_image.bmp",m_work_path);
			//delete src picture
			DeleteFile(path);
			//做半透处理
			//lock the data of bitmap
			save_bitmap.LockBits(&Rect(0,0,des_width,des_height),ImageLockModeWrite,PixelFormat32bppARGB,&bitmapData);
			// Write to the temporary buffer provided by LockBits.
			UINT* pixels = (UINT*)bitmapData.Scan0;

			for(UINT row=0; row<des_height; ++row)
			{
				for(UINT col=0; col<des_width; ++col)
				{
					UINT temp_value = pixels[row*bitmapData.Stride/4 + col];
					pixels[row * bitmapData.Stride/4 + col] = (temp_value==0xFF000000)?(temp_value&0x00FFFFFF):temp_value;
				}
			}
			//Commit the changes, and unlock the bitmap.
			save_bitmap.UnlockBits(&bitmapData);

			//保存文件
			return_status = save_bitmap.Save(path,  &encoderClsid,  &encoderParameters);  
		}  
		::DeleteObject(desktop_bitmap); 

		if (Ok==return_status)
		{
			show_image_to_tv(path);

			if (2==m_master_slave_control_flag)
			{
				//发送文件到文件到主控机
				send_master_slave_file(path);
			}
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::show_image_to_tv(TCHAR *path)
{
	try
	{
		//显示到电视上
		if (m_soft_decode_window_exist)
		{
			//软解
			show_picture_on_tv(path,OSDAlignmentCenter,6000,false,false);
		}
		else
		{
			//硬解
			rgb_conv c_rgb_conv;
			TCHAR index_path[256];

			memset(index_path,0x0,sizeof(index_path));

			//得到8位索引图的路径
			swprintf(index_path,L"%s\\draw_image8.bmp",m_work_path);
			//转化成8为索引图
			c_rgb_conv.rgb32torgb8(path,index_path);
			//显示8位索引图
			show_picture_on_tv(index_path,OSDAlignmentCenter,6000,false,false);
		}

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool  Cflashktv10Wnd::GetEncoderClsid(LPCWSTR  format,  CLSID*  pClsid)  
{  
	UINT    num  =  0;  
	UINT    size  =  0;  
	Status result=Ok;

	ImageCodecInfo*  pImageCodecInfo  =  NULL;  

	//得到图片编码类型种类
	result = GetImageEncodersSize(&num,  &size);  
	if ((Ok!=result)||(size<=0)) 
	{
		return false;  
	}
	//分配空间
	pImageCodecInfo  =  (ImageCodecInfo*)(malloc(size));  
	if (NULL==pImageCodecInfo) 
	{
		return false;  
	}
	//得到所有格式的图片编码信息
	result = GetImageEncoders(num,  size,  pImageCodecInfo);  
	if (Ok!=result)
	{
		return false;
	}
	for (UINT  j  =  0;  j  <  num;  ++j)  
	{  
		if (0==wcscmp(pImageCodecInfo[j].MimeType, format))  
		{  
			*pClsid  =  pImageCodecInfo[j].Clsid;  
			
			break;
		}  
	}  

	//释放空间
	free(pImageCodecInfo);
	pImageCodecInfo = NULL;

	return  true;  
}  


void Cflashktv10Wnd::show_picture_on_tv(TCHAR* path,OSDAlignment alignment_mode,int show_time,bool lyric_link,bool song_tip)
{
	try
	{
		play_variable play_var;
		bool result=false;
		
		if (m_show_song_tip_osd)
		{
			//正在播放，下一首提示不能播放其他的
			return;
		}
		//设置标志
		m_show_song_tip_osd = song_tip;
		if(!PathFileExists(path))
		{
			//文件不存在直接返回
			WriteLog(__FL__, L"gis动画路径不存在!!!");
			return;
		}
		//初始化播放图片的变量
		play_var.nRepeat = 10;
		play_var.play_mode = OSD_STATIC;
		play_var.iHSpeed = 0;
		play_var.iVSpeed = 0;
		play_var.nDelayTime = 0;

		//播放气氛图片
		result = m_player_manager.play_bmp_osd(path,play_var,alignment_mode);

		//启动显示定时器
		if (m_show_song_tip_osd&&(SCORE_SYSTEM_NONE!=m_use_score_system))
		{
		}
		else
		{
			set_bmp_picture_show_timer(show_time);
		}
 
		//设置标志
		m_start_lyric_link = lyric_link;

		return;
	}
	catch (...)
	{

	}
}

bool Cflashktv10Wnd::flash_message_call_delete_select_song(const TCHAR *song_number,bool recv_msg)
{
	try
	{
		int result=0;
		int select_song_number=0;
		TCHAR send_data[256];

		memset(send_data,0x0,sizeof(send_data));

		//得到删除的歌曲编号
		swscanf(song_number,L"%d",&select_song_number);

		if ((0==m_master_slave_control_flag)||(1==m_master_slave_control_flag))
		{
			//主控机
			if (!recv_msg)
			{
				//客户点击
				//删除选择的歌曲，相对编号
				result = m_video_play_manager.delete_select_song(select_song_number,true);
			}
			else
			{
				//接受的
				//删除选择的歌曲，绝对编号
				result = m_video_play_manager.delete_select_song(select_song_number,false);
			}
			if (result>=0)
			{
				refresh_screen_list();
				//更新已选歌曲数目
				update_select_song_count();
				//重新显示上下首歌名
				show_song_name();
			}
			if ((1==m_master_slave_control_flag)&&(result>=0))
			{
				//客户点击，发送被控数据，绝对位置
				swprintf(send_data,L"DSELECTSONG%d",result);
				send_master_slave_data(send_data,NULL);
			}
		}
		else if(2==m_master_slave_control_flag)
		{
			//被控机
			if(!recv_msg)
			{
				//得到绝对位置
				result = m_video_play_manager.get_select_song_absolute_position(select_song_number);
				//客户点击，发送主控数据，绝对下标
				swprintf(send_data,L"DSELECTSONG%d",result);
				send_master_slave_data(send_data,NULL);
			}
			else
			{
				//删除选择的歌曲，绝对位置
				result = m_video_play_manager.delete_select_song(select_song_number,false);
				if (result>=0)
				{
					refresh_screen_list();
					//更新已选歌曲数目
					update_select_song_count();
					//重新显示上下首歌名
					show_song_name();
				}
			}
		}	

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool Cflashktv10Wnd::flash_message_call_delete_recorder_song_by_id(const TCHAR *song_number)
{
	try
	{
		bool result=false;
		TCHAR sql[1024];
		int page_index=0;

		memset(sql,0x0,sizeof(sql));

		if (NULL==song_number)
		{
			return false;
		}

		//从数据库中删除该记录
		swprintf(sql,L"DELETE FROM song_recorder WHERE song_id=\"%s\"",song_number);
		result = m_db_query.exec_sql(sql);
		if (!result)
		{
		}
		//得到当前页面编号
		page_index = m_flash_manage.get_last_page_index();
		if (page_recording==page_index)
		{
			//显示第一页
			result = song_recorder_query_show_data();
			//song_recorder_query_all_show_data();
		}
		//发送给移动设备
		send_tape_song_to_pad();

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool Cflashktv10Wnd::flash_message_call_delete_recorder_song(const TCHAR *song_number)
{
	try
	{
		int select_song_number=0;
		bool result=false;
		song_info select_song_info;
		TCHAR song_id[128];
		TCHAR sql[1024];
		string_conversion str_con;
		char song_num[128] = {0x00};

		memset(song_id,0x0,sizeof(song_id));
		memset(sql,0x0,sizeof(sql));
		
		_tcscpy(song_id,song_number);
		
		str_con.widechar_to_multibyte(song_number, song_num, 128);

		//result = m_query_song_manager.get_recorder_song_info(song_id,select_song_info);
		//result = m_query_song_manager.get_recorder_song_info(atol(song_num), select_song_info);
		result = m_query_song_manager.get_song_info(atol(song_num), select_song_info);
		if (!result)
		{
			return false;
		}
		//得到歌曲的编号
		result = select_song_info.get_song_id(song_id);
		if (!result)
		{
			return false;
		}

		TCHAR send_data[1024];

		memset(send_data,0x0,sizeof(send_data));

		swprintf(send_data,L"DRECORDSONG%s",song_id);
		//发送更新面板信息给被控机
		send_master_slave_data(send_data,NULL);

		//从数据库中删除该记录
		swprintf(sql,L"DELETE FROM song_recorder WHERE song_id=\"%s\"",song_id);
		result = m_db_query.exec_sql(sql);

		//显示第一页
		result = song_recorder_query_show_data(CUR_PAGE_OPERATE);
		//song_recorder_pre_next_page_change(CUR_PAGE_OPERATE,0);

		//发送给移动设备
		send_tape_song_to_pad();


		return true;
	}
	catch (...)
	{

	}
	return false;
}

/*
bool Cflashktv10Wnd::flash_message_call_delete_recorder_song(const TCHAR *song_number)
{
	try
	{
		int select_song_number=0;
		bool result=false;
		song_info select_song_info;
		TCHAR song_id[128];
		TCHAR sql[1024];

		memset(song_id,0x0,sizeof(song_id));
		memset(sql,0x0,sizeof(sql));

		swscanf(song_number,L"%d",&select_song_number);
		if ((select_song_number<0)||(select_song_number>m_page_show_row_count))
		{
			return false;
		}

		result = m_query_song_manager.get_song_info(select_song_number,select_song_info);
		if (!result)
		{
			return false;
		}
		//得到歌曲的编号
		result = select_song_info.get_song_id(song_id);
		if (!result)
		{
			return false;
		}
		//从数据库中删除该记录
		swprintf(sql,L"DELETE FROM song_recorder WHERE song_id=\"%s\"",song_id);
		result = m_db_query.exec_sql(sql);
		//显示第一页
		result = song_recorder_query_show_data();

		//发送给移动设备
		send_tape_song_to_pad();


		return true;
	}
	catch (...)
	{

	}
	return false;
}*/

void Cflashktv10Wnd::flash_message_call_delete_private_song(const TCHAR* args)
{
	try
	{
		TCHAR user_identitycard[128];
		TCHAR request_data[1024];


		memset(user_identitycard,0x0,sizeof(user_identitycard));
		memset(request_data,0x0,sizeof(request_data));

		//PLACEVERSION/DELETESONG?songid=1123&identitycard=12345
		m_memeber_manage[m_activate_vip_button].get_user_identitycard(user_identitycard);
		//我的分享
		swprintf(request_data,L"SDEND_ORDER:PLACEVERSION/DELETESONG?songid=%s&identitycard=%s",args,user_identitycard);
		//启动线程 发送给盒子请求微信点歌数据
		thread_send_to_box_tcp_function(request_data,18007);
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::flash_message_call_delete_person_song(const TCHAR *args)
{
	try
	{
		TCHAR sql[1024];
		int number=0;
		song_info person_song_info;
		TCHAR song_id[128];
		bool result=false;

		memset(sql,0x0,sizeof(sql));
		memset(song_id,0x0,sizeof(song_id));
		
		swscanf(args,L"%d",&number);

		result = m_query_song_manager.get_song_info(number,person_song_info);
		if (!result)
		{
			return;
		}
		result = person_song_info.get_song_id(song_id);
		if (!result)
		{
			return;
		}
		//删除选中的记录
		swprintf(sql,L"DELETE FROM member_song WHERE song_id=\'%s\' and member_name=\'%s\'",song_id,m_member_name);
		result = m_db_query.exec_sql(sql);
		if (result)
		{
			//改变总行数和总的页数，总歌曲数减一
			m_db_query.change_total_row(-1,m_page_show_row_count);
			//刷新列表
			refresh_screen_list();
			//执行成功，会员歌曲数减一
			m_member_song_count--;
			//发送给后台服务器
			memset(sql,0x0,sizeof(sql));
			swprintf(sql,L"Message&MEMBERSONGID;SUB:%s:%s$END",m_member_name,song_id);
			send_data_to_service_udp(sql);
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_message_call_clear_person_song(void)
{
	try
	{
		TCHAR sql[1024];
		bool result=false;

		memset(sql,0x0,sizeof(sql));
	
		//删除全部会员歌曲
		swprintf(sql,L"DELETE FROM member_song WHERE member_name=\'%s\'",m_member_name);
		result = m_db_query.exec_sql(sql);
		if (result)
		{
			member_song_query_show_data();
			//发送给后台服务器
			memset(sql,0x0,sizeof(sql));
			swprintf(sql,L"Message&MEMBERSONGID;CLEAR:%s$END",m_member_name);
			send_data_to_service_udp(sql);
		}
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::screen_show_visible(bool show)
{
	try
	{
		TCHAR request[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));

		if (show)
		{
			//显示形象页
			m_show_start_image = true;
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"xxy_visible",L"true");
			if (result)
			{
				flash_player_call_function(request);
			}
		}
		else if(m_show_start_image)
		{
			//隐藏形象页
			m_show_start_image = false;
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"xxy_visible",L"false");
			if (result)
			{
				flash_player_call_function(request);
			}
		}

		return;		
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::get_master_slave_function(void)
{
	try
	{
		config_file_manager config_file;
		std::wstring master_slave_control_ip;
		string_conversion string_conv;

		config_file.init(L"master_slave.ini");

		memset(m_master_control_ip,0x0,sizeof(m_master_control_ip));

		//得到主被控标示。默认不启用主被控(默认为主控 2013-1-28 yangzhenglun)
		m_master_slave_control_flag = config_file.read_integer(m_room_ip,L"flag",1);
		if (1==m_master_slave_control_flag)
		{
			//主控机
			master_slave_control_ip = config_file.read_string(m_room_ip,L"ip",L"");
			//被控机IP通过socket自动提取
			WriteLog(__FL__, L"启用了主被控，该机器是主控机");
		}
		else if (2==m_master_slave_control_flag)
		{
			//被控机
			master_slave_control_ip = config_file.read_string(m_room_ip,L"ip",L"");
			if (!master_slave_control_ip.empty())
			{
				//得到主控机IP
				string_conv.widechar_to_multibyte(master_slave_control_ip.c_str(),m_master_control_ip,sizeof(m_master_control_ip));
			}
			else
			{
				WriteLog(__FL__, L"该机器是被控机，主控机的IP地址不存在，请填写");
			}
			WriteLog(__FL__, L"启用了主被控，该机器是被控机");
		}
		else
		{
			//没有启用主被控
			m_master_slave_control_flag = 0;
			WriteLog(__FL__, L"没有启用主被控");
		} 

		return true;
	}
	catch (...)
	{

	}
	return false;
}

UINT Cflashktv10Wnd::master_slave_control_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);

		return pThis->recv_master_slave_control_data();
	}
	catch (...)
	{

	}
	return -1;
}

UINT Cflashktv10Wnd::recv_master_slave_control_data(void)
{
	try
	{
		fd_set socket_set;
		timeval overtime;
		overtime.tv_sec = 0;
		overtime.tv_usec = 10000;
		int result=0;

		//清0
		FD_ZERO(&socket_set);

		//create socket
		SOCKET list_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (list_socket < 0) 
		{
			//终止线程
			if (m_master_slave_event_handle)
			{
				SetEvent(m_master_slave_event_handle);
			}
			return -1;
		}
		//bind local addr
		sockaddr_in addr;
		addr.sin_family = AF_INET;
#ifdef SLAVE_NO_PLAY_VIDEO
		addr.sin_addr.S_un.S_addr = inet_addr(m_send_room_ip);
#else
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
#endif
		if (1==m_master_slave_control_flag)
		{
			//主控机
			addr.sin_port = ntohs(6511);
		}
		else
		{
			//被控机
			addr.sin_port = ntohs(6512);
		}
		memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
		if (SOCKET_ERROR==bind(list_socket, (struct sockaddr*)&addr, sizeof(sockaddr_in)))
		{
			DWORD dwError = GetLastError();
			//终止线程
			if (m_master_slave_event_handle)
			{
				SetEvent(m_master_slave_event_handle);
			}
			WriteLog(__FL__, L"主被控的socket绑定端口失败");
			return -1;
		}
		//加入监听组
		FD_SET(list_socket,&socket_set);
		while (m_thread_run)
		{
			try
			{
				SLEEP_FOR; //增加sleep

				//将fdSocket集合的一个拷贝fdRead传递给select函数，
				// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回
				fd_set fdRead_set = socket_set;
				result = ::select(0,&fdRead_set,NULL,NULL,&overtime);
				if (result<=0)
				{
					continue;
				}
				//通过将原来fdSocket集合与select处理过的fdRead集合比较，
				// 确定都有哪些套节字有未决I/O，并进一步处理这些I/O。
				for(int i=0; i<(int)socket_set.fd_count; i++)
				{
					if (FD_ISSET(socket_set.fd_array[i],&fdRead_set))
					{
						//recv data
						char recv_data[10240];
						int recv_len=0;
						sockaddr_in send_addr;
						char recv_ip[256];

						int nLen = sizeof(send_addr);

						memset(recv_data,0x0,sizeof(recv_data));
						memset(recv_ip,0x0,sizeof(recv_ip));

						recv_len = ::recvfrom(socket_set.fd_array[i],recv_data,sizeof(recv_data),0,(sockaddr*)&send_addr, &nLen);

						if (recv_len>0)                     //(2)接受到数据
						{
							if(1==m_master_slave_control_flag)
							{
								//主控机，要得到被控机的IP地址，并保存
								strcpy(recv_ip,inet_ntoa(send_addr.sin_addr));
								for(int m=0;m<SLAVE_COMPUTER_MAX_COUNT;m++)
								{
									if (0==strcmp(m_slave_control_ip[m],recv_ip))
									{
										//已经存在就跳出
										break;
									}
									else if (0==strcmp(m_slave_control_ip[m],""))
									{
										//不存在就加入
										strcpy(m_slave_control_ip[m],recv_ip);
										break;
									}
								}
							}

							if (0==strcmp(recv_data,"SLAVECOMPUTERCHECKIN"))
							{
								//被控机报到,主控机把房间状态发送给被控机 2012-09-03 add ZHEN
								send_room_state_to_ipad_server();

								//移动点歌验证码 2015-2-9 17:55:39--LTL
								send_mobile_code_to_slave(0); //移动点歌
								send_mobile_code_to_slave(1); //微信点歌
								break;
							}

							if (0==strcmp(recv_data,"SLAVECOMPUTERCHECKIN"))
							{
								//被控机报到
								//被控机报到,主控机把房间状态发送给被控机 2012-09-03 add ZHEN
								send_room_state_to_ipad_server();
								break;
							}
							if ((0==strncmp(recv_data,"QUERYSINGERINFO",15))||(0==strncmp(recv_data,"QUERYSONGINFO",13))||(0==strncmp(recv_data,"PLAYINGSONGINFO",15))||(0==strncmp(recv_data,"SELECTSONGINFO",14))||(0==strncmp(recv_data,"SINGSONGINFO",12)))
							{
								//手持设备的
								break;
							}
							//主控时，如果是活动进行中，则放弃消息
							if (m_master_slave_control_flag == 1)
							{
								if (0 == strncmp(recv_data, "ACTIVE_GAME_JOIN", 16) || 0 == strncmp(recv_data, "ACTIVE_GAME_QUIT", 16) ||
									0 == strncmp(recv_data, "ACTIVE_GAME_HIGH_LIGHT", 22) || 0 == strncmp(recv_data, "ACTIVE_GAME_DICE", 16) ||
									0 == strncmp(recv_data, "BARRAGE_INFO", 12) || 0 == strncmp(recv_data, "ACTIVE_GAME_SCENE", 17))
								{
									goto __DMMSM__;
								}
								bool bBreak = false;
								switch(m_nCurPageCode)
								{
								case page_challenge_star:
								case page_across_pass:
								case page_listen_knowledge_song:
								//case page_picture_mv:
								case page_active_game:
									bBreak = true;
									break;
								}
								if (bBreak)
								{
									break;
								}
							}
__DMMSM__:
							//必须用sendmessage()函数，否则传递的参数就会丢失
							SendMessage(DM_MASTER_SLAVE_MESSAGE,(WPARAM)recv_data,recv_len);
						}
					}//end if
				}//end for
			}
			catch (...) {
			}
		}
	}
	catch (...)
	{

	}
	//终止线程
	if (m_master_slave_event_handle)
	{
		SetEvent(m_master_slave_event_handle);
	}
	return 0;
}

void Cflashktv10Wnd::inform_flash_show_select_or_sing_text(int page_code)
{
	try
	{
		TCHAR request[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));

		if (page_selected==page_code)
		{
			//已选页面显示已唱
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"show_selected",L"false");
		}
		else
		{
			//其他页面都是显示已选
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"show_selected",L"true");
		}
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::clear_show_list(void)
{
	try
	{
		TCHAR request[1024];
		int page_index=0;
		bool result=false;

		memset(request,0x0,sizeof(request));

		page_index = m_flash_manage.get_last_page_index();
		//设置页面为0
		show_row_and_page_count(L"true",0,0,1);
		switch(page_index)
		{
		case page_singer:
		case page_custom_singer:  //场所歌星
		case page_voice_china_singer:
			{
				//把页面初始化成空
				result = m_flash_manage.make_singer_request(request,sizeof(request)/sizeof(TCHAR),L"SingerPhotoList",L"",true,page_index,0);
				if (result)
				{
					flash_player_call_function(request);
				}
			}
			break;
		default:
			{
				//组织歌曲字符串   直接显示数据页操作码是0，把列表清空
				result = m_flash_manage.make_song_request(request,sizeof(request)/sizeof(TCHAR),L"",true,page_index,0,m_song_show_mode);
				if (result)
				{
					flash_player_call_function(request);
				}
			}
			break;
		}
	}
	catch (...)
	{
		
	}
	return;
}

UINT Cflashktv10Wnd::save_data_to_U_disk_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd *pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);
		if (pThis)
		{
			pThis->save_data_to_U_disk();
		}
	}
	catch (...)
	{
		
	}
	return 0;
}


void Cflashktv10Wnd::save_data_to_U_disk(void)
{
	try
	{
		song_info recording_song_info;
		TCHAR path[256];
		TCHAR U_path[256];
		bool result=false;
		TCHAR file_name[256];
		TCHAR *temp_pointer=NULL;
		int copy_result=0;
		TCHAR mp3_path[256];

		memset(path,0x0,sizeof(path));
		memset(U_path,0x0,sizeof(U_path));
		memset(file_name,0x0,sizeof(file_name));
		memset(mp3_path,0x0,sizeof(mp3_path));

		if ((m_select_save_song_number<0)||(m_select_save_song_number>=m_page_show_row_count))
		{
			m_is_saving_audio = false;
			return;
		}
		//得到选中的歌曲信息
		result = m_query_song_manager.get_song_info(m_select_save_song_number,recording_song_info);
		if (!result)
		{
			m_is_saving_audio = false;
			return;
		}
		//得到录音音频文件路径
		result = recording_song_info.get_wave_path(path);
		if (!result || !PathFileExists(path))
		{
			m_is_saving_audio = false;

			copy_result = 4;
			
			//发送消息通知,正在合成中...
			PostMessage(DM_SAVE_U_DISK_SONG,NULL,copy_result);

			return;
		}
		//mp3文件路径 
		if (NULL!=_tcsstr(path,L".mp3"))
		{
			//不用转换，本身就是mp3
			_tcscpy(mp3_path,path);
		}
		else //转成mp3
		{
			swprintf(mp3_path,L"%s.mp3",path);
			if (!PathFileExists(mp3_path))
			{
				result = m_http_service.PCM_to_mp3(path,mp3_path);
				if (!result)
				{
					m_is_saving_audio = false;
					return;
				}
			}
		}

		temp_pointer = _tcsrchr(mp3_path,'\\');
		_tcscpy(file_name,temp_pointer+1);
		//拷贝数据到U盘
		swprintf(U_path,L"%c:\\%s",m_logical_disk_drive,file_name);
		//改变标示
		m_is_saving_audio=true;
		//拷贝之前发送消息
		copy_result = 1;
		PostMessage(DM_SAVE_U_DISK_SONG,NULL,copy_result);
		//开始拷贝
		result = CopyFile(mp3_path,U_path,FALSE);
		if (result)
		{
			//成功
			copy_result = 2;
			PostMessage(DM_SAVE_U_DISK_SONG,NULL,copy_result);
		}
		else
		{
			//失败
			copy_result = 3;
			PostMessage(DM_SAVE_U_DISK_SONG,NULL,copy_result);

		}
		m_is_saving_audio = false;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_message_call_submit_recorder_song(const TCHAR *args)
{
	try
	{
		config_file_manager config_file;
		int recorder_number=0;
		song_info recorder_song_info;
		bool result=false;
		TCHAR wave_path[256];
		std::wstring server_path;
		TCHAR upload_path[256];
		TCHAR *file_name=NULL;

		memset(wave_path,0x0,sizeof(wave_path));
		memset(upload_path,0x0,sizeof(upload_path));

		swscanf(args,L"%d",&recorder_number);

		if ((recorder_number<0)||(recorder_number>=m_page_show_row_count))
		{
			return;
		}

		//得到要上传的录音歌曲信息
		result = m_query_song_manager.get_song_info(recorder_number,recorder_song_info);
		if (!result)
		{
			flash_show_tip_message(57);
			return;
		}
		//得到录音路径
		result = recorder_song_info.get_wave_path(wave_path);
		if (!result)
		{
			flash_show_tip_message(57);
			return;
		}
		//得到服务器路径
		server_path = config_file.read_string(L"server",L"server_path",L"");
		if (server_path.empty()|| !PathFileExists(server_path.c_str()))
		{
			flash_show_tip_message(57);
			return;
		}
		//按照包房分开录音文件
		swprintf(upload_path,L"%s\\recorder_song\\%s",server_path.c_str(),m_show_room_name);
		if (!PathFileExists(upload_path))
		{
			//创建录音文件保存路径
			SuperMkDir(upload_path);
		}
		file_name = _tcsrchr(wave_path,'\\');
		if (NULL==file_name)
		{
			return;
		}
		_tcscat(upload_path,file_name);
		//上传到服务器
		result = CopyFile(wave_path,upload_path,FALSE);
		if (!result)
		{
			flash_show_tip_message(57);
			return;
		}
		flash_show_tip_message(58);

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::flash_message_call_share_area_recorder_audio(MAIBA_HEIGHT_RANKING &maiba_share_info)
{
	try
	{
		int recorder_number=0;
		bool result=false;
		int value = 0;
		TCHAR song_number[36];
		TCHAR URL[256];
		TCHAR wave_path[256];
		TCHAR send_data[256];
		
		memset(song_number,0x0,sizeof(song_number));
		memset(wave_path,0x0,sizeof(wave_path));
		memset(URL,0x0,sizeof(URL));
		memset(send_data, 0x0, sizeof(send_data));

		int page_index = m_flash_manage.get_last_page_index();


		//分析xml，得到歌曲信息
		m_share_audio_info.set_song_id(maiba_share_info.voice_id);
		m_share_audio_info.set_song_name(maiba_share_info.song_name);
		m_share_audio_info.set_singer_name(maiba_share_info.singer_name);
		m_share_audio_info.set_recorder_video_path(maiba_share_info.video_path);
		m_share_audio_info.set_culture_code(maiba_share_info.song_id);
		m_share_audio_info.set_recorder_wave_path(maiba_share_info.wave_path);
		value = 0;
		//swscanf(result_set[6].c_str(),L"%d",&value);
		m_share_audio_info.set_recorder_start_time(value);
		m_share_audio_info.set_recorder_datatime(maiba_share_info.datetime);
		m_share_audio_info.set_video_type(PLAY_SONG_TYPE_RECORDER_SONG);

		result = m_share_audio_info.get_song_id(song_number);
		if (!result)
		{
			return;
		}

		if (2 == m_master_slave_control_flag)
		{
			//主控分享，被控只是显示，得到分享的URL
			result = m_http_service.get_web_url(song_number,URL,NULL);
			if (result&&(0!=_tcscmp(URL,L"")))
			{
				//分享URL显示到界面
				send_share_url_image_to_flash(URL);
			}
			else
			{
				//通知主控分享该歌曲
				swprintf(send_data,L"SHARERECORD%s", song_number);
				send_master_slave_data(send_data, NULL);
			}
		}
		else
		{
			//检测文件是否合成完
			result = m_share_audio_info.get_wave_path(wave_path);
			if (!result||!PathFileExists(wave_path))
			{
				flash_show_tip_message(109);
				return;
			}
			//得到分享的URL
			result = m_http_service.get_web_url(song_number,URL,NULL);
			if (result&&(0!=_tcscmp(URL,L"")))
			{
				//分享URL显示到界面
				send_share_url_image_to_flash(URL);
			}
			else
			{
				//采用线程方式，防止阻塞
				AfxBeginThread(Cflashktv10Wnd::share_audio_file_thread,this);
			}
		}

	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::flash_message_call_share_web_song(MAIBA_SONG_INFO_STU &maiba_song_info)
{
	try
	{
		TCHAR URL[256];
		memset(URL,0x0,sizeof(URL));
		
		_tcscpy(URL,L"http://www.joyk.com.cn/");
		_tcscat(URL,maiba_song_info.song_down_addrss);
			 
		send_share_url_image_to_flash(URL);
	}
	catch (...)
	{
		
	} 

	return;
}

void Cflashktv10Wnd::flash_message_call_share_recorder_audio(const TCHAR *args, bool recv_msg)
{
	try
	{
		int recorder_number=0;
		bool result=false;
		TCHAR song_number[36];
		TCHAR URL[256];
		TCHAR wave_path[256];
		TCHAR send_data[256];

		memset(song_number,0x0,sizeof(song_number));
		memset(wave_path,0x0,sizeof(wave_path));
		memset(URL,0x0,sizeof(URL));
		memset(send_data, 0x0, sizeof(send_data));


		swscanf(args,L"%d",&recorder_number);
		int page_index = m_flash_manage.get_last_page_index();

		if ((recorder_number<0)/*||(recorder_number>=m_page_show_row_count)*/)
		{
			return;
		}

		//得到要分享的录音歌曲信息
		memset(&m_share_audio_info,0x0,sizeof(m_share_audio_info));
		if (recv_msg)
		{
			//被控发送过来的是歌曲编号
			result = get_record_song_info_by_id(args, m_share_audio_info, PLAY_SONG_TYPE_RECORDER_SONG);
		}
		else
		{
			//界面发送过来的是相对编号
			result = m_query_song_manager.get_song_info(recorder_number,m_share_audio_info);
		}

		/*
		//通过歌曲编号歌曲编号
		switch (page_index)
		{
		case page_recording:
			{
				if (0 == m_maiba_number_button)
				{
					//录音歌曲列表
					result = get_record_song_info_by_id(args, m_share_audio_info, PLAY_SONG_TYPE_RECORDER_SONG);
				}
				else if (1 == m_maiba_number_button)
				{
					//得到网络的
					for (int i =0;i<48;i++)
					{
						if (0 == _tcscmp(args,m_maiba_song_info[i].voice_id))
						{
							_tcscpy(URL,L"http://www.joyk.com.cn/");
							_tcscat(URL,m_maiba_song_info[i].song_down_addrss);
							result = true;
							break;
						}				
					}

					if (!result)
					{
						WriteLog(__FL__, L"没有找到这个URL的路径");
						WriteLog(__FL__, args);
						return;
					}
					send_share_url_image_to_flash(URL);
					
					//memset(request_data,0x0,sizeof(request_data));
					//PLACEVERSION/SHAREVOICE?Id=1232123332311&type=5&text=分享&identitycard=12345
					//发送分享给网络
					//thread_send_to_box_tcp_function(request_data,18007);
					return ;
				}
			}
			break;
		default:
			{
				//得到网络的
				for (int i =0;i< 48;i++)
				{
					if (0 == _tcscmp(args,m_maiba_song_info[i].voice_id))
					{
						_tcscpy(URL,L"http://www.joyk.com.cn/");
						_tcscat(URL,m_maiba_song_info[i].song_down_addrss);
						break;
					}				
				}
				send_share_url_image_to_flash(URL);

				//memset(request_data,0x0,sizeof(request_data));
				//PLACEVERSION/SHAREVOICE?Id=1232123332311&type=5&text=分享&identitycard=12345
				//发送分享给网络
				//thread_send_to_box_tcp_function(request_data,18007);
				return ;
			}
			break;
		}
		
		
		if (!result)
		{
			return;
		}
		*/
		result = m_share_audio_info.get_song_id(song_number);
		if (!result)
		{
			return;
		}

		//验证是否是阳光秀吧
		if (page_index == page_voice_china)
		{
			SHOW_CUBE_SONG_VEC::iterator it = m_show_cube_song_vec.begin();
			while(it != m_show_cube_song_vec.end())
			{
				LP_SHOW_CUBE_SONG lpscs = *it;
				if (_tcscmp(lpscs->song_id.c_str(), song_number) == 0)
				{
					TCHAR szBuf[MAX_PATH] = {0x00};
					_tcscpy(szBuf, lpscs->song_wechat_url.c_str());
					send_share_url_image_to_flash(szBuf);
					break;
				}
				it++;
			}
			return;
		}

		if (2 == m_master_slave_control_flag)
		{
			//主控分享，被控只是显示，得到分享的URL
			result = m_http_service.get_web_url(song_number,URL,NULL);
			if (result&&(0!=_tcscmp(URL,L"")))
			{
				//分享URL显示到界面
				send_share_url_image_to_flash(URL);

				//发送给规则服务器
				share_song_to_rale_server(song_number,URL);
			}
			else
			{
				//记录下被控分享时的ID
				m_str_slave_recorder_song_id = song_number;
				//通知主控分享该歌曲
				swprintf(send_data,L"SHARERECORD%s", song_number);
				send_master_slave_data(send_data, NULL);
			}
		}
		else if(recv_msg)
		{
			m_b_share_recv_msg = recv_msg;
			//采用线程方式，防止阻塞
			AfxBeginThread(Cflashktv10Wnd::share_audio_file_thread,this);
		}
		else
		{
			//检测文件是否合成完
			result = m_share_audio_info.get_wave_path(wave_path);
			if (!result||!PathFileExists(wave_path))
			{
				flash_show_tip_message(109);
				return;
			}

			//得到分享的URL
			result = m_http_service.get_web_url(song_number,URL,NULL);
			if (result&&(0!=_tcscmp(URL,L"")))
			{
				//分享URL显示到界面
				send_share_url_image_to_flash(URL);

				//发送给规则服务器
				share_song_to_rale_server(song_number,URL);
			}
			else
			{
				//采用线程方式，防止阻塞
				AfxBeginThread(Cflashktv10Wnd::share_audio_file_thread,this);
			}
		}

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::send_share_url_image_to_flash(TCHAR *url)
{
	try
	{

		TCHAR image_path[256];
		string_conversion string_conv;
		char web_url[256];
		bool result=false;
		TCHAR request[1024];
		TCHAR data[1024];

		if (NULL==url)
		{
			return;
		}

		memset(web_url,0x0,sizeof(web_url));
		memset(image_path,0x0,sizeof(image_path));
		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		string_conv.widechar_to_utf8(url,web_url,sizeof(web_url));

		swprintf(image_path,L"%s\\UrlImage.png",m_work_path);
		DeleteFile(image_path);

		/*WriteLog(__FL__, L"二维码的路径");
		WriteLog(__FL__, url);*/
		//生成二维码图片
		result = Generate_encode_picture(web_url,image_path);
		if (result)
		{
			//缩放图片
			zoom_image(image_path,145,145,image_path,L"image/png",0,0);
			//显示到界面
			swprintf(data,L"<data><image_path isShow=\"true\">%s</image_path></data>",image_path);
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"share_url",data);
			//swprintf(data,L"<data><image_path isShow=\"true\">E:\\project\\flashktv10.4\\flashktv10_4\\Debug\\UrlImage.png</image_path></data>");
			//result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"share_url",data);
			//WriteLog(__FL__, request);
			if (result)
			{
				flash_player_call_function(request);
			}
		}

		return;
	}
	catch (...)
	{

	}

	return;
}

UINT Cflashktv10Wnd::share_audio_file_thread(LPVOID pPara)
{
	try
	{
		Cflashktv10Wnd *pThis = reinterpret_cast<Cflashktv10Wnd *>(pPara);
		return pThis->share_audio_file_to_internet();
	}
	catch (...)
	{

	}
	return 0;
}

UINT Cflashktv10Wnd::share_audio_file_to_internet(void)
{
	try
	{
		TCHAR web_url[256];
		TCHAR song_number[128];
		bool result=false;
		TCHAR data[2048];
		wstring user_info_xml;
		TCHAR one_info[1024];
		TCHAR memeber_info[256];
		TCHAR member_pwd[256];

		memset(web_url,0x0,sizeof(web_url));
		memset(song_number,0x0,sizeof(song_number));
		memset(data,0x0,sizeof(data)); 
		memset(one_info,0x0,sizeof(one_info));
		memset(memeber_info,0x0,sizeof(memeber_info));
		memset(member_pwd,0x0,sizeof(member_pwd));

		result = m_share_audio_info.get_song_id(song_number);
		if (!result)
		{
			return false;
		}
		//得到二维码
		result = m_http_service.get_url_from_server(song_number,web_url);
		if (!result)
		{
			if (!m_b_share_recv_msg)
			{
				flash_show_tip_message(108);
			}
			WriteLog(__FL__, L"得到分享URL失败");
			return false;
		}
		if (m_b_share_recv_msg)
		{
			//分享成功之后，推送给被控机
			send_tape_song_to_pad();
			m_b_share_recv_msg = false;
			return 0;
		}
		//显示到界面
		send_share_url_image_to_flash(web_url);

		//发送给规则服务器
		share_song_to_rale_server(song_number,web_url);

		if (-1 != m_activate_vip_button)
		{
			m_memeber_manage[m_activate_vip_button].get_user_name(memeber_info);
			m_memeber_manage[m_activate_vip_button].get_user_password(member_pwd);
		}
		else
		{
			_tcscpy(memeber_info,L"");
			_tcscpy(member_pwd,L"");
		}
		
		//设置当前的用户 
		user_info_xml += L"[";
		swprintf(one_info,L"{\"username\":\"%s\",\"password\":\"%s\",\"type\":\"2\"}",memeber_info,member_pwd);
		user_info_xml+=one_info;
		user_info_xml+= L"]";

		WriteLog(__FL__, user_info_xml.c_str());

		m_http_service.set_current_user_info(user_info_xml.c_str(),0);
		
		//推送到场所服务器
		result = m_http_service.upload_file_to_server(m_share_audio_info);
		if (result)
		{
			//发送分享成功给服务端
			share_success_send_to_server(song_number);

// 			//分享成功之后，推送给被控机
// 			send_tape_song_to_pad();
		}
		else
		{
			flash_show_tip_message(108);
			WriteLog(__FL__, L"上传分享的音频到场所服务器失败");
		}

		return 0;
	}
	catch (...)
	{

	}
	return -1;
}

void Cflashktv10Wnd::share_success_send_to_server(TCHAR* song_number)
{
	try
	{
		TCHAR data[2048];

		memset(data,0x0,sizeof(data));
		//long rule_

		//得到当前的总秒数s
		long long time_last;
		time_last = time(NULL);     //总秒数


		//分享成功后，发送给后台标示为分享成功，可以作为擂台pk,还是自由pk
		if (0 == _tcscmp(m_maiba_rule_arena_info[1].song_id,song_number))
		{
			//为擂台pk
			//swprintf(data,L"Message&SONG_SHARE_SUCCESS;UPDATE song_recorder SET is_share=\"1\",pk_flags=\"1\" where song_id=\"%s\" ",song_number);
		}

		swprintf(data,L"Message&SONG_SHARE_SUCCESS;%s",song_number);
		//通过udp协议发送给服务程序
		send_data_to_service_udp(data);
		
		//发送给规则服务器
		//share_song_to_rale_server(song_number);
		 
		/*
		if (0 != strcmp(m_set_maiba_rule_ip,""))
		{
			memset(data,0x0,sizeof(data));

			swprintf(data,L"SONG_SHARE_SUCCESS{\"song_id\":\"%s\"}",song_number);

			//send_msg_to_set_maiba_rule(data);

			//AfxBeginThread(send_data_to_maiba_rule_thread,data);
			REQUEST_BOX_DATA *request_rule_data = new REQUEST_BOX_DATA();
			request_rule_data->pThis = this;
			_tcscpy(request_rule_data->request_data,data);
			AfxBeginThread(send_data_to_maiba_rule_thread,request_rule_data);
		}*/
	}
	catch (...)
	{
		
	}
	
	return;
}

void Cflashktv10Wnd::show_control_sub_window()
{
	try
	{
		TCHAR request[1024];
		int page_index=0;
		bool result=false;

		memset(request,0x0,sizeof(request));

		//得到页面索引
		page_index = m_flash_manage.get_last_page_index();
		if (page_video==page_index)
		{
			//不显示
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"show_sub_window",L"false");
		}
		else
		{
			//显示
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"show_sub_window",L"true");
		}
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::show_check_window(bool show)
{
	try
	{
		TCHAR request[1024];
		bool result=false;
		
		memset(request,0x0,sizeof(request));

		if (show)
		{
			//显示复选框
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"check_window_2",L"show");
			if (result)
			{
				flash_player_call_function(request);
				m_check_window_state = true;
				//启动定时器用于隐藏窗口
				hide_check_window_timer_identifier = SetTimer(HIDE_CHECT_WINDOW_TIMER_EVENT_ID,3000,NULL);
			}
		}
		else
		{
			//隐藏复选框
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"check_window_2",L"hide");
			if (result)
			{
				flash_player_call_function(request);
				m_check_window_state = false;
			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::flash_message_call_select_song_tip(const TCHAR *args)
{
	try
	{
		TCHAR request[1024];
		bool result=false;
		TCHAR song_number[128];

		memset(request,0x0,sizeof(request));
		memset(song_number,0x0,sizeof(song_number));

		//记录当前页面的值 

		//隐藏提示框
		show_check_window(false);

		if (0==_tcscmp(args,L"no"))
		{
			//不允许重复选歌曲
			return;
		}
		else if (0==_tcscmp(args,L"delete"))
		{
			//得到歌曲ID
			result = m_select_song_info.get_song_id(song_number);
		
			if (result)
			{
				//判断是否给对方删除歌曲
				if (m_b_pk_connect)
				{
					//发送消息给连接的ip
					TCHAR send_ip[256];
					TCHAR send_delete_song[256];
					memset(send_delete_song,0x0,sizeof(send_delete_song));	


					if (0 != _tcscmp(m_pk_invitationIP,L""))
					{
						_tcscpy(send_ip,m_pk_invitationIP);
					}
					if (0 != _tcscmp(m_pk_acceptIP,L""))
					{
						_tcscpy(send_ip,m_pk_acceptIP);
					}

					//得到当前歌曲的绝对位置
					//得到当前的页数

					_tcscpy(send_delete_song,_T("delete_songs_2"));
					_tcscat(send_delete_song,song_number); 

					connect_inviation(send_ip,send_delete_song);  //删除歌曲
				}

				//通过ID删除选择的歌曲
				m_video_play_manager.delete_select_song_by_id(song_number);

				//刷新屏幕
				//refresh_screen_list();
				//更新选择歌曲数目
				//update_select_song_count();
			}			
			return;
		}
		else if (0==_tcscmp(args,L"all_yes"))
		{
			m_allow_repeat_select_song = true;
		}

		//允许重复选择
		//m_allow_repeat_select_song = true;

		//判断是否给对方同步歌曲
		if (m_b_pk_connect)
		{
			//发送消息给连接的ip
			TCHAR send_ip[256];
			song_info song_info_class;
			TCHAR song_id[128]; 
			TCHAR send_sync_songs[256];

			memset(song_id,0x0,sizeof(song_id));
			memset(send_ip,0x0,sizeof(send_ip));
			memset(send_sync_songs,0x0,sizeof(send_sync_songs));

	 
			if (0 != _tcscmp(m_pk_invitationIP,L""))
			{
				_tcscpy(send_ip,m_pk_invitationIP);
			}
			if (0 != _tcscmp(m_pk_acceptIP,L""))
			{
				_tcscpy(send_ip,m_pk_acceptIP);
			} 

			//得到歌曲编号
			m_select_song_info.get_song_id(song_id);
			if (m_select_song_priority)
			{
				_tcscpy(send_sync_songs,_T("priority_song1"));   //优先其他歌曲
			}
			else
			{
				_tcscpy(send_sync_songs,_T("sync_songs"));
			}
			_tcscat(send_sync_songs,song_id);
			connect_inviation(send_ip,send_sync_songs);  //同步点歌
		}

		//显示选歌动画提示
		//show_select_song_animation();

		//根据播放器状态，播放或插入已选歌曲中
		result = play_or_insert_select_list(m_select_song_info,m_select_song_priority);
		if (!result)
		{
			return;
		}
		//得到显示的编号，然后改变显示颜色，必须先把歌曲插入已选中，然后在改变颜色，因为涉及到刷屏
		if (m_select_song_number>=0)
		{
			chang_select_song_color(m_select_song_info,m_select_song_number,m_select_song_priority);
		}
		//重新显示上下首歌名
		show_song_name();
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::change_system_info(const TCHAR *args)
{
	try
	{
		int number=0;
		bool result=false;
		config_file_manager config_file;

		swscanf(args,L"%d",&number);
		switch(number)
		{
		case 1:  //修改房间名
			{
				if (0!=_tcscmp(m_local_computer_name,L""))
				{
					result = SetComputerNameEx(ComputerNamePhysicalDnsHostname,m_local_computer_name);
					if (result)
					{
						flash_show_tip_message(59);
					}
					else
					{
						flash_show_tip_message(60);
					}
				}
			}
			break;
		case 2:  //修改IP地址
			{
				if (!m_adapter_info.strIP.empty())
				{
					result = modify_computer_ip(m_adapter_info.strName.c_str(),0,m_adapter_info.strIP.c_str(),m_adapter_info.strNetMask.c_str(),m_adapter_info.strNetGate.c_str());
					if (result)
					{
						//修改IP地址成功
						flash_show_tip_message(61);
					}
					else
					{
						//修改IP地址失败
						flash_show_tip_message(62);
					}
				}
			}
			break;
		case 3:  //网络测试
			{
				check_net_status();
			}
			break;
		case 4:  //关机
			{
				shutdown_computer();
			}
			break;
		case 5:   //重启
			{
				reboot_computer();
			}
			break;
		case 6:  //退出软件
			{
				PostMessage(WM_CLOSE);
			}
			break;
		case 7:  //开房
			{
				SendMessage(DM_RECV_SERVER_DATA,(WPARAM)"open0",NULL);
				set_button_show_state(ROOM_BUTTON_STATE, true);
				if (m_close_room_timer_identifier > 0)
				{
					KillTimer(m_close_room_timer_identifier);
					m_close_room_timer_identifier = 0;
				}

				if (m_nCloseRoomTimeSpace > 0)
					m_close_room_timer_identifier = SetTimer(CLOSE_ROOM_TIME_SPACE_TIME_EVENT_ID,m_nCloseRoomTimeSpace*60*1000,NULL);
			}
			break;
		case 8: //锁房
			{
				SendMessage(DM_RECV_SERVER_DATA,(WPARAM)"close",NULL);
				set_button_show_state(ROOM_BUTTON_STATE, false);
			}
			break;
		case 9:  //DJ开
			{
				TCHAR send_data[1024] = {0x00};
				swprintf(send_data, L"dj:%d", 1);
				if (1==m_master_slave_control_flag)
				{
					//主控机
					send_master_slave_data(send_data,NULL);
				}
				else if (2==m_master_slave_control_flag)
				{
					//被控机，客户点击的
					send_master_slave_data(send_data,NULL);
				}
				m_allow_play_dj = true;
				set_button_show_state(DJ_BUTTON_STATE, true);
			}
			break;
		case 10:  //dj关
			{
				TCHAR send_data[1024] = {0x00};
				swprintf(send_data, L"dj:%d", 0);
				if (1==m_master_slave_control_flag)
				{
					//主控机
					send_master_slave_data(send_data,NULL);
				}
				else if (2==m_master_slave_control_flag)
				{
					//被控机，客户点击的
					send_master_slave_data(send_data,NULL);
				}
				m_allow_play_dj = false;
				set_button_show_state(DJ_BUTTON_STATE, false);
			}
			break;
		case 11:  //电影功能开
			{
				m_allow_play_movie = true;
			}
			break;
		case 12:  //电影功能关
			{
				m_allow_play_movie = false;
			}
			break;
		case 13: //清洁完成
			{

			}
			break;
		case 14:  //关闭火警
			{
				//设置正播放歌曲的视频类型
				m_player_manager.set_playing_video_type(PLAY_SONG_TYPE_SELECT_SONG);
				//设置播放器状态
				m_video_play_manager.set_player_cur_state(PLAY_SONG_STATE);
				m_video_play_manager.set_player_next_state(PLAY_SONG_STATE);
				//播放下一首
				flash_message_call_function(SONG_NEXT);
				//回到首页   2014-08-13修改不返回首页
				//page_change(page_homepage);
			}
			break;
		case 15:  //音效控制
			{
				std::wstring audio_effect;

				//回到首页   2014-08-13修改不返回首页 
				//page_change(page_homepage);
				//检测是否有外挂音效器控制软件
				audio_effect = config_file.read_string(L"amplifier",L"plug_in_audio_effect",L"");
				if (audio_effect.empty())
				{
					//显示内嵌调音窗口
					if (m_audio_effect_window_exist)
					{
						m_audio_effect_window.BringWindowToTop();
						m_audio_effect_window.ShowWindow(SW_SHOW);
					}
				}
				else
				{
					//启用外挂音效器
					result = check_process_run_state(NULL,m_audio_effect_progress_id);
					if (result)
					{
						//终止原来的
						teminate_process(NULL,m_audio_effect_progress_id);
					}
					//重新启动
					start_plug_in_process(audio_effect.c_str(),SW_SHOW,m_audio_effect_progress_id);
				}
			}
			break;
		case 16:
			{
				//弹出服务开
				m_server_pop_up_window = true;
				set_button_show_state(OPEN_SERVER_WINDOW, true);
			}
			break;
		case 17:
			{
				//弹出服务关
				m_server_pop_up_window = false;
				set_button_show_state(OPEN_SERVER_WINDOW, false);
			}
			break;
		case 18:
			{
				config_file.write_boolean(L"room", L"video_dating_show", true);
				m_video_dating_show = true;
				send_server_video_dating_data(VD_IDLE, true);
				set_button_show_state(VIDEO_DATING_STATE, m_video_dating_show);
			}
			break;
		case 19:
			{
				config_file.write_boolean(L"room", L"video_dating_show", false);
				m_video_dating_show = false;
				send_server_video_dating_data(VD_CLOSE_ROOM);
				set_button_show_state(VIDEO_DATING_STATE, m_video_dating_show);
			}
			break;
		case 20:   //选择了计算机名输入框
			{
				m_system_info_input_type = 0;
			}
			break;
		case 21:   //选择了IP地址输入框
			{
				m_system_info_input_type = 1;
			}
			break;
		case 22:
			{
				m_allow_show_cloud_song = true;
				set_button_show_state(SHOW_CLOUD_SONG_STATE, m_allow_show_cloud_song);
			}
			break;
		case 23:
			{
				m_allow_show_cloud_song = false;
				set_button_show_state(SHOW_CLOUD_SONG_STATE, m_allow_show_cloud_song);
			}
			break;
		default:
			break;
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::show_system_info_input_text(int textbox_number,const TCHAR *text)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[1024];
		bool result=false;

		if (NULL==text)
		{
			return;
		}

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(request));

		swprintf(data,L"<data><info textbox=\"%d\" text=\"%s\" /></data>",textbox_number,text);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"system_info_text",data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::show_local_computer_name_IP(void)
{
	try
	{
		bool result=false;
		DWORD len=0;

		memset(m_local_computer_name,0x0,sizeof(m_local_computer_name));
	
		//显示计算机名
		len = sizeof(m_local_computer_name)/sizeof(TCHAR);
		result = GetComputerNameEx(ComputerNamePhysicalDnsHostname,m_local_computer_name,&len);
		if (result)
		{
			show_system_info_input_text(0,m_local_computer_name);
		}
		//显示IP地址
		result = GetAdapterInfo(&m_adapter_info);
		if (result)
		{
			show_system_info_input_text(1,m_adapter_info.strIP.c_str());
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::system_info_keyboard_input(const TCHAR *agrs)
{
	try
	{
		TCHAR recv_string[256];
		size_t len=0;

		memset(recv_string,0x0,sizeof(recv_string));

		if (NULL==agrs)
		{
			return;
		}
		_tcscpy(recv_string,agrs);

		switch(m_system_info_input_type)
		{
		case 0:  //计算机名
			{
				if (0==_tcscmp(recv_string,L"del"))         //回删
				{
					len = _tcslen(m_local_computer_name);
					if (len>0)
					{
						m_local_computer_name[len-1]='\0';
					}
				}
				else if (0==_tcscmp(recv_string,L"enter"))  //确定
				{
					change_system_info(L"1");  //修改计算机名
				}
				else if (0==_tcscmp(recv_string,L"dot"))   //点
				{
					_tcscat(m_local_computer_name,L".");
				}
				else  //其他输入的字符
				{
					_tcscat(m_local_computer_name,recv_string);
				}
				//防止计算机名过长
				len = _tcslen(m_local_computer_name);
				if (len>15)
				{
					memset(m_local_computer_name,0x0,sizeof(m_local_computer_name));
				}
				//显示到界面
				show_system_info_input_text(0,m_local_computer_name);
			}
			break;
		case 1:   //IP地址
			{
				if (0==_tcscmp(recv_string,L"del"))         //回删
				{
					len = m_adapter_info.strIP.length();
					if (len>0)
					{
						m_adapter_info.strIP = m_adapter_info.strIP.substr(0,len-1);
					}
				}
				else if (0==_tcscmp(recv_string,L"enter"))  //确定
				{
					change_system_info(L"2");  //修改IP地址
				}
				else if (0==_tcscmp(recv_string,L"dot"))   //点
				{
					m_adapter_info.strIP += L".";
				}
				else  //其他输入的字符
				{
					m_adapter_info.strIP += recv_string;
				}
				//防止IP地址越界
				len = m_adapter_info.strIP.length();
				if (len>15)
				{
					m_adapter_info.strIP.clear();
				}
				//显示到界面上
				show_system_info_input_text(1,m_adapter_info.strIP.c_str());
			}
			break;
		default:
			break;
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::change_flash_skin(const TCHAR *args)
{
	try
	{
		if (NULL==args)
		{
			return;
		}
		//换肤之前初始化
		change_skin_init();
		//记录当前界面的版本
		memset(m_cur_interface_version,0x0,sizeof(m_cur_interface_version));
		_tcscpy(m_cur_interface_version,args);
		//改变手写板颜色
		change_handwriting_window_color();
		//改变手写窗口的位置
		move_handwriting_window_pos();

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::change_skin_init(void)
{
	try
	{
		//换肤过程，把界面初始化标示赋值成false，这样就不会给flash发码
		m_flash_screen_init_finish = false;
		//隐藏视频窗口
		if (m_screen_show_window_exist && m_screen_show_window.IsWindowVisible())
		{
			m_screen_show_window.show_window(false);
		}
		if (m_lobby_live_window_exist && m_lobby_live_window.IsWindowVisible())
		{
			m_lobby_live_window.show_window(false);
		}
		if (m_tv_window_exist && m_tv_window.IsWindowVisible())
		{
			m_tv_window.show_window(false);
		}
		if (m_preview_window_exist && m_preview_window.IsWindowVisible())
		{
			m_preview_window.show_window(false);
		}
		if (m_handwriting_window_exist && m_handwriting_window.IsWindowVisible())
		{
			m_handwriting_window.ShowWindow(SW_HIDE);
			m_show_handwriting_window = false;
		}
		
		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::change_handwriting_window_color(void)
{
	try
	{
		COLORREF foreground_color=0;
		COLORREF background_color=0;
		long pen_color=0;


		if (0==_tcscmp(m_cur_interface_version,L"red")) //红版
		{
			foreground_color = 4792714;
			background_color = 2363714;
			pen_color = 187622;
		}
		else if (0==_tcscmp(m_cur_interface_version,L"green")) //绿版
		{
			foreground_color = 0xFFFFFF;
			background_color = 0x848a40;
			pen_color = 187622;
		}
		else if (0==_tcscmp(m_cur_interface_version,L"christmas"))  //圣诞版
		{
			foreground_color = 187622;
			background_color = 0x0a0a6f;
			pen_color = 0xFFFFFF;
		}
		else if (0==_tcscmp(m_cur_interface_version,L"black"))  //黑板
		{
			foreground_color = 0x808080;
			background_color = 0x131212;
			pen_color = 0x0000FF;
		}
		else if (0==_tcscmp(m_cur_interface_version,L"oriental"))  //欧兰特
		{
			foreground_color = 0x1209b1;
			background_color = 0x0b0741;
			pen_color = 187622;
		}
		else if (0==_tcscmp(m_cur_interface_version,L"passion"))   //燃情
		{
			foreground_color = 0x3b0d9c;
			background_color = 0x06052c;
			pen_color = 187622;
		}
		else if (0==_tcscmp(m_cur_interface_version,L"popcorn"))  //爆米花
		{
			foreground_color = 0x3b0d9c;
			background_color = 2363714; 
			pen_color = 187622;
		}
		else if (0==_tcscmp(m_cur_interface_version,L"china"))   //中国风
		{
			foreground_color = 0x01C8FF;
			background_color = 0x4d575a; 
			pen_color = 230;
		}
		else if (0 == _tcscmp(m_cur_interface_version,L"win8"))
		{
			foreground_color = 0x302f37;
			background_color = 0x302f37; 
			pen_color = 187622;
		}
		else
		{
			//foreground_color = 0x00deff;
			foreground_color = 000000;
			background_color = 000000;
			pen_color = 187622;
		}
		//改变手写板的颜色
		m_handwriting_window.change_handwriting_board_color(foreground_color,background_color,pen_color);
		//刷新一下窗口
		m_handwriting_window.UpdateWindow();

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::move_handwriting_window_pos(void)
{
	try
	{
		if (0==_tcscmp(m_cur_interface_version,L"red"))
		{
			//红版
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x,m_handwriting_window_top_y,m_handwriting_window_right_x,m_handwriting_window_bottom_y));
		}
		else if (0==_tcscmp(m_cur_interface_version,L"green"))
		{
			//绿版
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x,m_handwriting_window_top_y-10,m_handwriting_window_right_x,m_handwriting_window_bottom_y-10));
		}
		else if (0==_tcscmp(m_cur_interface_version,L"christmas"))
		{
			//圣诞版
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x,m_handwriting_window_top_y-5,m_handwriting_window_right_x,m_handwriting_window_bottom_y-5));
		}
		else if (0==_tcscmp(m_cur_interface_version,L"black"))
		{
			//黑板
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x-2,m_handwriting_window_top_y,m_handwriting_window_right_x,m_handwriting_window_bottom_y+2));
		}
		else if (0==_tcscmp(m_cur_interface_version,L"oriental"))  
		{
			//欧兰特
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x,m_handwriting_window_top_y,m_handwriting_window_right_x,m_handwriting_window_bottom_y));
		}
		else if (0==_tcscmp(m_cur_interface_version,L"passion")) 
		{
			//燃情
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x-1,m_handwriting_window_top_y-2,m_handwriting_window_right_x-1,m_handwriting_window_bottom_y-2));
		}
		else if (0==_tcscmp(m_cur_interface_version,L"popcorn"))
		{
			//爆米花
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x,m_handwriting_window_top_y,m_handwriting_window_right_x,m_handwriting_window_bottom_y));
		}
		else if (0==_tcscmp(m_cur_interface_version,L"china"))
		{
			//中国风
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x-4,m_handwriting_window_top_y-6,m_handwriting_window_right_x-2,m_handwriting_window_bottom_y-5));
		}
		else
		{
			//默认
			m_handwriting_window.MoveWindow(CRect(m_handwriting_window_left_x,m_handwriting_window_top_y,m_handwriting_window_right_x,m_handwriting_window_bottom_y));
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::show_screen_top_image(void)
{
	try
	{
		TCHAR request[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));

		//增加屏显，并显示
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"xxy_url",m_image_page_path);
		if (result)
		{
			m_flash_player.CallFunction(request);
			//显示形象页
			screen_show_visible(true);
			//2011-05-04 modify
			m_show_start_image = true;
		}

		return;
	}
	catch(...)
	{

	}
	return;
}

void Cflashktv10Wnd::show_select_song_animation(void)
{
	try
	{
		TCHAR request[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));

		//显示选歌曲动画提示
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"SelectSongAnimation",L"show");
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::change_link_server_number(int server_number)
{
	try
	{
		TCHAR send_msg[1024];

		memset(send_msg,0x0,sizeof(send_msg));

		if (!m_use_load_balance)
		{
			//没有使用负载均衡就不要发送
			return;
		}
		
		//删除前一个连接
		if (m_pre_link_server_number>=0)
		{
			swprintf(send_msg,L"Message&SERVERLINKSUB;%d$END",m_pre_link_server_number);
			send_data_to_service_udp(send_msg);
			//前一个连接的服务器编号改成-1
			m_pre_link_server_number = -1;
		}

		if((server_number>=0)&&(server_number<6))
		{
			//增加新的连接
			swprintf(send_msg,L"Message&SERVERLINKADD;%d$END",server_number);
			send_data_to_service_udp(send_msg);
			//保存当前的连接
			m_pre_link_server_number = server_number;
		}		

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::send_playing_song_to_handheld(void)
{
	try
	{
		song_info playing_song_info;
		TCHAR song_id[256];
		TCHAR send_data[1024];
		bool result=false;

		//得到正播放的歌曲信息
		result = m_video_play_manager.get_playing_video(playing_song_info);
		if (result)
		{
			memset(song_id,0x0,sizeof(song_id));
			memset(send_data,0x0,sizeof(send_data));

			//得到歌曲ID
			result = playing_song_info.get_song_id(song_id);
			//组织发送的字符串
			swprintf(send_data,L"PLAYINGSONGINFO%s",song_id);
			//发送给手持设备
			send_master_slave_data(send_data,NULL);			
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::send_select_song_to_handheld(void)
{
	try
	{
		TCHAR send_data[10240];
		char  data_utf[10240];
		TCHAR temp_data[1024];
		song_info select_song_info;
		int select_song_count=0;
		bool result=false;
		string_conversion string_conv;

		memset(send_data,0x0,sizeof(send_data));

		//标示符号
		_tcscpy(send_data,L"SELECTSONGINFO<data>");

		//得到选择的歌曲数
		select_song_count = m_video_play_manager.get_select_song_count();
		for(int i=0;i<select_song_count;i++)
		{
			//得到选择的歌曲
			select_song_info.initialized_variables();
			result = m_video_play_manager.get_select_song_information(select_song_info,i,false);
			if (result)
			{
				//成功
				memset(temp_data,0x0,sizeof(temp_data));
				//组织一条xml信息
				result = make_send_handheld_song_info(select_song_info,i,temp_data);
				if (result)
				{
					//连接
					_tcscat(send_data,temp_data);	
				}				
			}
		}
		//结束符
		_tcscat(send_data,L"</data>");
		
		//转成utf-8 多字节不支持韩文 2013-03-25 zlg
		memset(data_utf,0x0,sizeof(data_utf));
		string_conv.widechar_to_utf8(send_data,data_utf,sizeof(data_utf));
		//发送已选歌曲信息到手持设备
		send_master_slave_data(NULL,data_utf);

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::send_sing_song_to_handheld(void)
{
	try
	{
		TCHAR send_data[10240*3];
		char  data_utf[10240*3];
		TCHAR temp_data[1024];
		song_info sing_song_info;
		int sing_song_count=0;
		bool result=false;
		string_conversion string_conv;

		memset(send_data,0x0,sizeof(send_data));

		//标示符号
		_tcscpy(send_data,L"SINGSONGINFO<data>");

		//得到选择的歌曲数
		sing_song_count = m_video_play_manager.get_sing_song_count();
		for(int i=0;i<sing_song_count;i++)
		{
			//得到选择的歌曲
			sing_song_info.initialized_variables();
			result = m_video_play_manager.get_sing_song_information(sing_song_info,i,false);
			if (result)
			{
				//成功
				memset(temp_data,0x0,sizeof(temp_data));
				//组织一条xml信息
				result = make_send_handheld_song_info(sing_song_info,i,temp_data);
				if (result)
				{
					//连接
					_tcscat(send_data,temp_data);	
				}		
			}
		}
		//结束符
		_tcscat(send_data,L"</data>");

		//转成utf-8 多字节不支持韩文 2013-03-25 zlg
		memset(data_utf,0x0,sizeof(data_utf));
		string_conv.widechar_to_utf8(send_data,data_utf,sizeof(data_utf));
		//发送已选歌曲信息到手持设备
		send_master_slave_data(NULL,data_utf);

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::send_query_song_to_handheld(int page_operate,int page_row_count)
{
	try
	{
		TCHAR send_data[8192];
		TCHAR temp_data[1024];
		song_info query_song_info;
		bool result=false;

		memset(send_data,0x0,sizeof(send_data));

		//标示符号
		swprintf(send_data,L"QUERYSONGINFO%d#%d|<data>",page_operate,page_row_count);

		for(int i=0;i<HANDHELD_PAGE_SHOW_ROW_COUNT;i++)
		{
			//得到选择的歌曲
			query_song_info.initialized_variables();
			result = m_query_song_manager.get_handheld_song_info(i,query_song_info);
			if (result)
			{
				//成功
				memset(temp_data,0x0,sizeof(temp_data));
				//组织一条xml信息
				result = make_send_handheld_song_info(query_song_info,i,temp_data);
				if (result)
				{
					//连接
					_tcscat(send_data,temp_data);	
				}		
			}
		}
		//结束符
		_tcscat(send_data,L"</data>");

		//发送已选歌曲信息到手持设备
		send_master_slave_data(send_data,NULL);

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::send_query_movie_to_handheld(int page_operate,int page_row_count)
{
	try
	{
		TCHAR send_data[8192];
		TCHAR temp_data[1024];
		song_info query_song_info;
		bool result=false;

		memset(send_data,0x0,sizeof(send_data));

		//标示符号
		swprintf(send_data,L"QUERYMOVIEINFO%d#%d|<data>",page_operate,page_row_count);

		for(int i=0;i<HANDHELD_PAGE_SHOW_ROW_COUNT;i++)
		{
			//得到选择的歌曲
			query_song_info.initialized_variables();
			result = m_query_song_manager.get_handheld_song_info(i,query_song_info);
			if (result)
			{
				//成功
				memset(temp_data,0x0,sizeof(temp_data));
				//组织一条xml信息
				result = make_send_handheld_movie_info(query_song_info,i,temp_data);
				if (result)
				{
					//连接
					_tcscat(send_data,temp_data);	
				}		
			}
		}
		//结束符
		_tcscat(send_data,L"</data>");

		//发送已选歌曲信息到手持设备
		send_master_slave_data(send_data,NULL);

		return;
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::make_send_handheld_song_info(song_info &send_song_info,int song_number,TCHAR *send_data)
{
	try
	{
		if (NULL==send_data)
		{
			return false;
		}
		TCHAR song_id[128];
		TCHAR song_name[256];
		TCHAR song_language[32];
		TCHAR song_version[32];
		TCHAR singer_name[128];
		TCHAR video_flag[32];
		PLAY_SONG_TYPE video_type;
		bool result=false;
		int nVersion = 0;

		memset(song_id,0x0,sizeof(song_id));
		memset(song_name,0x0,sizeof(song_name));
		memset(song_language,0x0,sizeof(song_language));
		memset(song_version,0x0,sizeof(song_version));
		memset(singer_name,0x0,sizeof(singer_name));
		memset(video_flag,0x0,sizeof(video_flag));

		//得到歌曲信息
		result = send_song_info.get_song_id(song_id);
		if (!result)
		{
			return false;
		}
		send_song_info.get_song_name(song_name);
		if (!result)
		{
			return false;
		}
		//得到视频类型
		video_type = send_song_info.get_video_type();
		if (PLAY_MOVIE==video_type)
		{
			//电影
			send_song_info.get_movie_region(song_language);
			send_song_info.get_movie_story(song_version);
			_tcscpy(video_flag,L"M");
		}
		else
		{
			//歌曲
			send_song_info.get_handheld_song_language(song_language);
			send_song_info.get_song_version(song_version,nVersion);
			send_song_info.get_singer_name(singer_name);
			_tcscpy(video_flag,L"S");
		}

		//组织一条记录
		swprintf(send_data,L"<song%02d id=\"%s\" name=\"%s\" language=\"%s\" version=\"%s\" singer=\"%s\" flag=\"%s\" />",song_number,song_id,song_name,song_language,song_version,singer_name,video_flag);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool Cflashktv10Wnd::make_send_handheld_movie_info(song_info &send_song_info,int movie_number,TCHAR *send_data)
{
	try
	{
		if (NULL==send_data)
		{
			return false;
		}
		TCHAR movie_id[128];
		TCHAR movie_name[256];
		TCHAR movie_region[256];
		TCHAR movie_story[256];
		bool result=false;

		memset(movie_id,0x0,sizeof(movie_id));
		memset(movie_name,0x0,sizeof(movie_name));
		memset(movie_region,0x0,sizeof(movie_region));
		memset(movie_story,0x0,sizeof(movie_story));

		//得到歌曲信息
		result = send_song_info.get_song_id(movie_id);
		if (!result)
		{
			return false;
		}
		send_song_info.get_song_name(movie_name);
		if (!result)
		{
			return false;
		}
		send_song_info.get_movie_region(movie_region);
		send_song_info.get_movie_story(movie_story);

		//组织一条记录
		swprintf(send_data,L"<movie%02d id=\"%s\" name=\"%s\" region=\"%s\" story=\"%s\" />",movie_number,movie_id,movie_name,movie_region,movie_story);

		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::send_query_singer_to_handheld(int page_operate,int page_row_count)
{
	try
	{
		TCHAR send_data[8192];
		TCHAR singer_name[256];
		TCHAR singer_sex[32];
		TCHAR singer_region[32];
		TCHAR temp_data[1024];
		singer_info query_singer_info;
		bool result=false;

		memset(send_data,0x0,sizeof(send_data));

		//标示符号
		swprintf(send_data,L"QUERYSINGERINFO%d#%d|<data>",page_operate,page_row_count);

		for(int i=0;i<singer_page_show_row_count;i++)
		{
			//得到选择的歌曲
			memset(singer_name,0x0,sizeof(singer_name));
			memset(singer_sex,0x0,sizeof(singer_sex));
			memset(singer_region,0x0,sizeof(singer_region));
			memset(temp_data,0x0,sizeof(temp_data));

			query_singer_info.initialized_variables();
			query_singer_info = m_query_singer_manager.get_handheld_singer_info(i);
			
			//得到歌星信息
			result = query_singer_info.get_singer_name(singer_name);
			if (!result || (0==_tcscmp(singer_name,L"")))
			{
				continue;
			}
			query_singer_info.get_singer_sex(singer_sex);
			query_singer_info.get_singer_region(singer_region);

			//组织一条记录XML方式
			swprintf(temp_data,L"<singer%02d name=\"%s\" sex=\"%s\" region=\"%s\" />",i,singer_name,singer_sex,singer_region);
			//连接
			_tcscat(send_data,temp_data);
		}
		//结束符
		_tcscat(send_data,L"</data>");

		//发送已选歌曲信息到手持设备
		send_master_slave_data(send_data,NULL);

		return;
	}
	catch (...)
	{

	}
	return;
}
void Cflashktv10Wnd::show_pop_up_dj_window()
{
	try
	{
		bool result = false;
		TCHAR request[1024];
		memset(request,0x0,sizeof(request));

		if (!m_allow_play_dj)
		{
			//清空输入的密码
			m_input_code.clear();
			show_system_manage_code(L"");

			//弹出对话框
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"show_pop_up_dj_window",L"true");
			if (result)
			{
				flash_player_call_function(request);
			}
		}
	}
	catch (...)
	{
	}

	return;
}

void Cflashktv10Wnd::show_pop_up_page(const TCHAR *args)
{
	try
	{
		int page_index = 0;
		bool result = false;
		TCHAR request[1024];

		if ((NULL==args)||(0==_tcscmp(m_cur_interface_version,L"YYC")))
		{
			return;
		}

		if (0==_tcscmp(args,L"10"))
		{
			memset(request,0x0,sizeof(request));
			if (m_server_pop_up_window)
			{
				if (m_pc_allow_cancel_service)
				{
					//允许取消呼叫
					if (m_call_service_state)
					{
						//呼叫服务状态，取消呼叫
						//cancel_call_service();
					}
					else
					{
						//弹出对话框
						result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"show_popup_page",L"true");
						if (result)
						{
							flash_player_call_function(request);
							m_screen_show_window.show_window(false); 
						}
					}				

				}
				else
				{
					//呼叫服务状态，取消呼叫
					cancel_call_service();
					m_screen_show_window.show_window(false); 

				}
			}
			else
			{
				if (page_index == page_yule_news||page_index == page_drinks||page_index == page_consumer)
				{
					if (m_html_ctrl_exist/* && m_html_ctrl.IsWindowVisible()*/)
					{
						m_html_ctrl.ShowWindow(SW_HIDE);
						m_html_ctrl.UpdateWindow();
						m_show_html_ctrl = false;
					}
				}
				flash_message_call_function(CALL_ATTENDANT);

				//return;
			}
		}

		//得到当前页面索引
		page_index = m_flash_manage.get_last_page_index();
		if (((page_video==page_index)||(page_game==page_index)||((SCREEN_TYPE_VERTICAL==m_interface_type)&&m_song_show_video_picture))  && (0 != _tcscmp(args,L"close")))
		{
			//如果是屏切页面，返回前一个页面在显示弹出页面

			//flash_message_call_function(PAGE_BACK);
			if (0==_tcscmp(args,L"10")&&page_video!=page_index)
			{

			}
			else
				m_screen_show_window.show_window(false); 
			//add by yzg 2015-12-09
			if (m_handwriting_window_exist && m_show_handwriting_window && !m_handwriting_window_show_hide) //隐藏手写
			{
				m_handwriting_window.ShowWindow(SW_HIDE);
				m_handwriting_window_show_hide = true;
			}
			//add end
			/*
			int page_index_flag = m_flash_manage.get_last_page_index();
			switch(page_index_flag)
			{
			case page_write:
			{
			m_handwriting_window.ShowWindow(SW_HIDE);
			m_handwriting_window_show_hide = true;
			}
			break;
			default:
			{

			m_handwriting_window_show_hide = false;
			}
			break;
			}*/

			//记录当前选择
			//memset(m_select_popup_window_number,0x0,sizeof(m_select_popup_window_number));
			//_tcscpy(m_select_popup_window_number,args);

			
			//启动定时器显示弹出页面
			//show_popup_window_timer_identifier = SetTimer(SHOW_POPUP_WINDOW_TIMER_EVENT_ID,300,NULL);
		}
		else if (m_handwriting_window_exist && m_show_handwriting_window && !m_handwriting_window_show_hide) //隐藏手写
		{
// 			m_handwriting_window.ShowWindow(SW_HIDE);
			m_handwriting_window_show_hide = true;
		}
		else if (m_handwriting_window_exist && m_show_handwriting_window && m_handwriting_window_show_hide && (0 == _tcscmp(args,L"close")))
		{
				m_handwriting_window.ShowWindow(SW_SHOW);
				m_handwriting_window_show_hide = false;
		}
		if (0 == _tcscmp(args,L"close")&&((page_video==page_index)||
			(page_game==page_index) || m_song_show_video_picture))
		{
			if (page_yule_news==page_index||page_index == page_drinks||page_index==page_consumer)
			{
				m_html_ctrl.ShowWindow(SW_SHOW);
				m_html_ctrl.UpdateWindow();
				m_show_html_ctrl = true;
			}
			pc_show_video_window();
		}
// 		else if (0 == _tcscmp(args,L"10"))
// 		{
// 			if (m_call_service_state)
// 			{
// 				pc_show_video_window();
// 			}
// 			else
// 			{
// 				if (m_server_pop_up_window )
// 				{
// 					if (page_index==page_video)
// 					{
// 						m_screen_show_window.show_window(false); 
// 					}
// 				}
// 				else
// 					pc_show_video_window();
// 			}
// 		}


		if (0 == _tcscmp(args,L"2"))
		{
			if (page_index == page_yule_news||page_index == page_drinks||page_index == page_consumer)
			{
				if (m_html_ctrl_exist/* && m_html_ctrl.IsWindowVisible()*/)
				{
					m_html_ctrl.ShowWindow(SW_HIDE);
					m_html_ctrl.UpdateWindow();
					m_show_html_ctrl = false;
				}
			}
			send_accompany_original_button_state();
		}
		else if (0==_tcscmp(args,L"3"))
		{
			if (page_index == page_yule_news||page_index == page_drinks||page_index == page_consumer)
			{
				if (m_html_ctrl_exist/* && m_html_ctrl.IsWindowVisible()*/)
				{
					m_html_ctrl.ShowWindow(SW_HIDE);
					m_html_ctrl.UpdateWindow();
					m_show_html_ctrl = false;
				}
			}
			//是否为欣赏状态
			result = m_player_manager.is_enjoyment();
			if (result)
			{
				//设置欣赏按钮状态
				set_button_show_state(ENJOY_BUTTON_STATE,true);
			}
		}
		else if (0==_tcscmp(args,L"9"))
		{
			//设置按钮状态
			set_button_show_state(GUID_BUTTON_STATE,m_enter_guide_song);
			set_button_show_state(TAPE_BUTTON_STATE,m_is_recording);
			set_button_show_state(SCORE_BUTTON_STATE,m_is_scoring);
			//显示录音歌曲数
			send_tape_audio_count_to_flash();
		} 
		else if (0==_tcscmp(args,L"1"))
		{
			if (page_index == page_yule_news||page_index == page_drinks||page_index == page_consumer)
			{
				if (m_html_ctrl_exist/* && m_html_ctrl.IsWindowVisible()*/)
				{
					m_html_ctrl.ShowWindow(SW_HIDE);
					m_html_ctrl.UpdateWindow();
					m_show_html_ctrl = false;
				}
			}
		}
		else if (0==_tcscmp(args,L"4"))//四音轨按钮
		{
			if (page_index == page_yule_news||page_index == page_drinks||page_index == page_consumer)
			{
				if (m_html_ctrl_exist/* && m_html_ctrl.IsWindowVisible()*/)
				{
					m_html_ctrl.ShowWindow(SW_HIDE);
					m_html_ctrl.UpdateWindow();
					m_show_html_ctrl = false;
				}
			}
			if (m_handwriting_window_exist && m_show_handwriting_window)
			{
				m_handwriting_window.ShowWindow(SW_HIDE);
			}
		}

		return;
	}
	catch (...)
	{

	}
	return;
}

bool Cflashktv10Wnd::protect_control_operate(int operate_code)
{
	try
	{
		bool result=false;

		switch(operate_code)
		{
		case SONG_PREVIOUS:
		case SONG_NEXT:
			{
				result = m_player_manager.is_play_video_ad();
				if (result)
				{
					//是在播放广告，在判断是否可以切换，歌曲都可以切换
					result = m_video_play_manager.video_allow_cut();
					if (!result)
					{
						//不允许切掉
						return true;
					}
				}
				//防止频繁切换
				double last_time = m_cut_song_timer.last_time();
				if (last_time<PLAY_VIDEO_MIN_TIME_LENGTH)
				{
					return true;
				}
				//重新开始计时
				m_cut_song_timer.start();
			}
			break;
		case SONG_REPLAY: //重唱
			{
				//防止频繁切换
				double last_time = m_cut_song_timer.last_time();
				if (last_time<PLAY_VIDEO_MIN_TIME_LENGTH)
				{
					return true;
				}
				//重新开始计时
				m_cut_song_timer.start();
			}
			break;
		case SONG_ACCOMPANY_ORIGINAL: //原伴唱
		case SONG_PLAY_PAUSE:         //播放暂停
		case MUSIC_VOLUME_UP:   //音乐的音量加
		case MUSIC_VOLUME_DOWN: //音乐的音量减
		case MICROPHONE_VOLUME_UP: //麦克风的音量加
		case MICROPHONE_VOLUME_DOWN://麦克风的音量减
		case TUNE_UP:               //音调增
		case TUNE_DOWN:             //音调减
		case TUNE_ORIGINAL:         //原调
		case ATMOSPHERE_APPLAUSE:    //鼓掌
		case ATMOSPHERE_CHEER:       //欢呼
		case ATMOSPHERE_OUTCRY:      //催眠
		case ATMOSPHERE_WHISTLE:     //狂汗

		case	ATMOSPHERE_HAOZAN: //好赞
		case	ATMOSPHERE_SHIHUA ://石化
		case	ATMOSPHERE_XIANHUA://献花
		case	ATMOSPHERE_TUXUE : //吐血
		case	ATMOSPHERE_FEIWEN ://飞吻
		case	ATMOSPHERE_XINSUI ://心碎
		case	ATMOSPHERE_HAIXIU ://害羞
		case	ATMOSPHERE_ZADAN ://砸蛋

		case AUDIO_EFFECT_STANDARD:      //标准
		case AUDIO_EFFECT_THEATER:       //剧场
		case AUDIO_EFFECT_PROFESSIONAL:  //唱将
		case AUDIO_EFFECT_MAGIC:         //魔音
		case AUDIO_EFFECT_RESERVE1:
		case AUDIO_EFFECT_RESERVE2:

		case SONG_MUTE_UNMUTE:                  //静音
		case REVERBERATION_DOWN:        //混响减
		case REVERBERATION_UP:          //混响加
		case PAGE_BACK:                 //页面返回
			//环境音
		case ENVIRONMENT_AUDIO_CLOSE:  //关闭环境音
		case ENVIRONMENT_AUDIO_MEETING:  //会议
		case ENVIRONMENT_AUDIO_AIRPORT:  //飞机场
		case ENVIRONMENT_AUDIO_ROAD:  //马路上
		case ENVIRONMENT_AUDIO_STATION:  //火车站
		case ENVIRONMENT_AUDIO_MAHJONG:  //麻将
		case ENVIRONMENT_AUDIO_RAIN:     //雨中
			//灯光
		case LIGHT_OPEN:   //灯光 开
		case LIGHT_CLOSE:  //灯光 关闭
		case LIGHT_STANDARD:  //灯光 标准
		case LIGHT_BACKGROUND:  //灯光 背景
		case LIGHT_STAGE:  //灯光 舞台
		case LIGHT_SCINTILLATION: //灯光 屏闪
		case LIGHT_OPEN1:        //灯光1
		case LIGHT_OPEN2:        //灯光1
		case LIGHT_OPEN3:        //灯光1
		case LIGHT_OPEN4:        //灯光1
		case LIGHT_OPEN5:        //灯光1
		case LIGHT_OPEN6:        //灯光1
		case LIGHT_OPEN7:   //灯光1
		case LIGHT_OPEN8:   //灯光1
		case LYRIC_LINK:                //歌词接龙
		case AIR_CONDITION_STRONG:      //空调强
		case AIR_CONDITION_MID:         //空调中
		case AIR_CONDITION_WEAK:        //空调弱
		case AIR_CONDITION_CLOSE:       //空调关闭
		case DISCHARGE_AIR_FUNCTION:    //排风

		case MUSIC_SOUND_STANDARD:  //音乐音效标准
		case MUSIC_SOUND_THEATER:  //音乐音效剧场
		case MUSIC_SOUND_PROFESSIONAL:  //音乐音效唱将
		case MUSIC_SOUND_MAGIC:  //音乐音效魔音
		case MUSIC_SOUND_RESERVE1:  //音乐音效自动
		case MUSIC_SOUND_RESERVE2:  //音乐音效预留
		case MUSIC_SOUND_RESERVE3:  //音乐音效预留
		case MUSIC_SOUND_RESERVE4:  //音乐音效预留
			{
				double last_time = m_avoid_cut_timer.last_time();
				if (last_time<AVOID_CUT_MIN_TIME_LENGTH)
				{
					return true;
				}
				//重新开始计时
				m_avoid_cut_timer.start();
			}
			break;
		case ATMOSPHERE_PIANO_BLACK1:       //钢琴黑键（左起，共15个）
		case ATMOSPHERE_PIANO_BLACK2:
		case ATMOSPHERE_PIANO_BLACK3:
		case ATMOSPHERE_PIANO_BLACK4:
		case ATMOSPHERE_PIANO_BLACK5:
		case ATMOSPHERE_PIANO_BLACK6:
		case ATMOSPHERE_PIANO_BLACK7:
		case ATMOSPHERE_PIANO_BLACK8:
		case ATMOSPHERE_PIANO_BLACK9:
		case ATMOSPHERE_PIANO_BLACK10:
		case ATMOSPHERE_PIANO_BLACK11:
		case ATMOSPHERE_PIANO_BLACK12:
		case ATMOSPHERE_PIANO_BLACK13:
		case ATMOSPHERE_PIANO_BLACK14:
		case ATMOSPHERE_PIANO_BLACK15:
		case ATMOSPHERE_PIANO_WHITE1: //钢琴白键（左起，共21个）
		case ATMOSPHERE_PIANO_WHITE2:
		case ATMOSPHERE_PIANO_WHITE3:
		case ATMOSPHERE_PIANO_WHITE4:
		case ATMOSPHERE_PIANO_WHITE5:
		case ATMOSPHERE_PIANO_WHITE6:
		case ATMOSPHERE_PIANO_WHITE7:
		case ATMOSPHERE_PIANO_WHITE8:
		case ATMOSPHERE_PIANO_WHITE9:
		case ATMOSPHERE_PIANO_WHITE10:
		case ATMOSPHERE_PIANO_WHITE11:
		case ATMOSPHERE_PIANO_WHITE12:
		case ATMOSPHERE_PIANO_WHITE13:
		case ATMOSPHERE_PIANO_WHITE14:
		case ATMOSPHERE_PIANO_WHITE15:
		case ATMOSPHERE_PIANO_WHITE16:
		case ATMOSPHERE_PIANO_WHITE17:
		case ATMOSPHERE_PIANO_WHITE18:
		case ATMOSPHERE_PIANO_WHITE19:
		case ATMOSPHERE_PIANO_WHITE20:
		case ATMOSPHERE_PIANO_WHITE21:
			{
				static int pre_button_number=0;

				double last_time = m_avoid_cut_timer.last_time();
				if ((pre_button_number==operate_code)&&(last_time<AVOID_CUT_MIN_TIME_LENGTH))
				{
					return true;
				}
				//重新开始计时
				m_avoid_cut_timer.start();
				//记录按钮编号
				pre_button_number = operate_code;
			}
			break;
		case PAGE_UP:    //上一页
		case PAGE_DOWN:  //下一页
			{
				//这些项有界面控制，为了防止快点。也要重新计时
				m_avoid_cut_timer.start();
			}
			break;
		default:
			break;
		}

		return false;
	}
	catch (...)
	{
		
	}

	return false;
}

void Cflashktv10Wnd::start_IE_software(void)
{
	try
	{
		TCHAR window_path[256];
		bool result=false;

		result = check_process_run_state(L"explorer.exe",0);
		if (result)
		{
			//在运行状态
			return;
		}
		//得到window路径
		GetSystemDirectory(window_path,sizeof(window_path)/sizeof(TCHAR));
		//得到window路径
		_tcsrchr(window_path,'\\')[0] = '\0';
		//启动IE
		ShellExecute(NULL,L"open",L"explorer.exe",NULL, window_path,SW_SHOW);
	}
	catch (...)
	{
		
	}
	return;
}


bool Cflashktv10Wnd::make_mark_for_singer(int mark_score)
{
	try
	{
		TCHAR score_video_path[256];
		song_info score_video_info;
		int music_volume=0;
		int micro_volume=0;
		int tune=0;
		int link_server_number=-1;
		bool result=false;

		memset(score_video_path,0x0,sizeof(score_video_path));

		if (mark_score<80)
		{
			mark_score = 80;
		}
		else
		{
			mark_score = (mark_score/2)*2;
		}
		if (mark_score>100)
		{
			mark_score = 100;
		}

		//分数视频路径  采用默认背景视频 ZHEN 2013-08-29 modify
		//swprintf(score_video_path,L"%s\\%s\\%df.mpg",m_work_path,g_folder_name[31],mark_score);
		swprintf(score_video_path,L"%s\\%s\\bg.mpg",m_work_path,g_folder_name[31]);
		if (!PathFileExists(score_video_path))
		{
			//不存在
			WriteLog(__FL__, L"分数视频不存在");
			return false;
		}

		//设置分数视频的本地路径
		result = score_video_info.set_local_path(score_video_path);
		if (!result)
		{
			WriteLog(__FL__, L"设置分数视频的本地路径错误");
			return false;
		}

		m_player_manager.get_volume_tune(music_volume,micro_volume,tune);
		if (music_volume<0)
		{
			music_volume = 0;
		}
		else if (music_volume>100)
		{
			music_volume = 100;
		}
		//设置音量
		score_video_info.set_accompany_volume(music_volume);
		score_video_info.set_karaoke_volume(music_volume);
		//设置视频类型
		score_video_info.set_video_type(PLAY_SCORE_VIDEO);
		//赋值给控件进行播放
		result = m_player_manager.set_video_file(score_video_info,link_server_number,m_music_wave_path,m_voice_wave_path,m_is_scoring);
		if (!result)
		{
			WriteLog(__FL__, L"设置分数视频出错");
			return false;
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

void Cflashktv10Wnd::use_file_open_room(void)
{
	try
	{
		BOOL result=FALSE;
		char buffer[256];
		file room_file; 
		DWORD read_byte=0;

		memset(buffer,0x0,sizeof(buffer));

		//检测文件是否存在
		result = PathFileExists(m_room_file_path);
		if (!result)
		{
			//文件不存在，直接退出软件
			PostMessage(WM_CLOSE,NULL,NULL);
			return;
		}
		//打开文件
		result = room_file.open_file(m_room_file_path,FILE_READ);
		if (result)
		{
			//读取文件
			result = room_file.read_file(buffer,sizeof(buffer),&read_byte);
			if (result)
			{
				//判断房间状态
				if ((CLOSE_ROOM_STATE==m_pc_state) && (0==strncmp(buffer,"开房",4)))
				{
					//发送开房指令
					SendMessage(DM_RECV_SERVER_DATA,(WPARAM)"open0",NULL);
					//回到首页
					page_change(page_homepage);
				}
				else if((CLOSE_ROOM_STATE!=m_pc_state) && (0==strncmp(buffer,"关房",4)))
				{
					//发送关房指令
					SendMessage(DM_RECV_SERVER_DATA,(WPARAM)"close",NULL);
					//回到首页
					page_change(page_homepage);
				}
			}
			//关闭文件
			room_file.close_file();
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::create_osd_image(void)
{
	try
	{
		TCHAR image_path[256];
		config_file_manager config_file;

		memset(image_path,0x0,sizeof(image_path));
		m_song_tip_image = NULL;
		m_number_image = NULL;

		//加载图片
		if (SCORE_SYSTEM_NONE!=m_use_score_system)  //启用评分
		{
			swprintf(image_path,L"%s\\score_image\\bg.png",m_work_path);
		}
		else
		{
			swprintf(image_path,L"%s\\%s\\NextSongTip.jpg",m_work_path,g_folder_name[6]);
		}
		if (PathFileExists(image_path))
		{
			//图片存在就加载
			m_song_tip_image = Image::FromFile(image_path);
		}

		memset(image_path,0x0,sizeof(image_path));
		swprintf(image_path, L"%s\\score_flash\\image\\number.png", m_work_path);
		if (PathFileExists(image_path))
		{
			m_number_image = Image::FromFile(image_path);
		}

		return;
	}
	catch (...)
	{
		
	}
	return;
}


bool Cflashktv10Wnd::save_score_tip_osd(int total_score,int average_similarity,int average_intact,int average_stability,int total_calories)
{
	try
	{
		//设置标识
		m_show_song_tip_osd = false;
		//判断图片是否存在
		if (NULL==m_song_tip_image)
		{
			return false;
		}
		Status last_status = m_song_tip_image->GetLastStatus();
		if (Ok!=last_status)
		{
			return false;
		}
		//背景图片存在在显示
		CLSID              encoderClsid;  
		EncoderParameters  encoderParameters; 
		TCHAR path[256];
		bool result=false;
		song_info playing_song;
		song_info next_song;
		TCHAR song_name[256];
		TCHAR singer_name[256];
		RectF text_rect;
		StringFormat text_format;
		Font myFont(L"微软雅黑",34,FontStyleBold);
		Font score_font(L"微软雅黑",120,FontStyleBold);
		Font score1_font(L"微软雅黑",20,FontStyleRegular);
		Font score2_font(L"微软雅黑",42,FontStyleBold);
		Font song_font(L"微软雅黑",15,FontStyleBold);
		SolidBrush text_brush(Color(255,46,0,22));
		Image *show_image=NULL;
		TCHAR show_text[256];
		RectF des_rect;
		REAL width=0.0f;
		REAL height=0.0f;


		memset(path,0x0,sizeof(path));
		memset(song_name,0x0,sizeof(song_name));
		memset(singer_name,0x0,sizeof(singer_name));


		//克隆一个图片
		Image *clone_image = m_song_tip_image->Clone();
		if (NULL==clone_image)
		{
			return false;
		}
		Graphics image_graphics(clone_image);

		int qurity = 100;

		//设置图片编码参数
		encoderParameters.Count  =  1;  
		encoderParameters.Parameter[0].Guid  =  EncoderQuality;  
		encoderParameters.Parameter[0].Type  =  EncoderParameterValueTypeLong;  
		encoderParameters.Parameter[0].NumberOfValues  =  1;  
		encoderParameters.Parameter[0].Value  =  &qurity; 

		//得到位图的clsid
		result = GetEncoderClsid(L"image/bmp",  &encoderClsid);  
		if (!result)
		{
			return false;
		}
		//得到当前播放的歌曲
		result = m_player_manager.get_playing_video(playing_song);
		if (!result)
		{
			return false;
		}
		//得到歌曲名字
		playing_song.get_song_name(song_name);
		if (0==_tcscmp(song_name,L""))
		{
			return false;
		}
		//显示当前歌曲名
		draw_text_to_image(image_graphics,247,234,800,50,StringAlignmentNear,Color(255,255,255,255),myFont,song_name);
		memset(m_score_song_info,0x0,sizeof(m_score_song_info));
		_tcscpy(m_score_song_info,song_name);

		//显示分数
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"%d",total_score);
		draw_text_to_image(image_graphics,690,300,260,210,StringAlignmentCenter,Color(255,00,0xC3,0xD0),score_font,show_text);
		for (int i=0;i<(total_score+10)/20;i++)
		{
			memset(path,0x0,sizeof(path));
			swprintf(path,L"%s\\score_image\\star.png",m_work_path);
			draw_image_to_offscreen(image_graphics,400+i*100,61,path);
		}

		//得到下一首播放的歌曲
		memset(song_name,0x0,sizeof(song_name));
		memset(singer_name,0x0,sizeof(singer_name));
		result = m_video_play_manager.get_select_song_information(next_song,0,false);
		if (result)
		{
			next_song.get_song_name(song_name);
			next_song.get_singer_name(singer_name);
		}
		else
		{
			_tcscpy(song_name,L"空闲歌曲");
		}
		//显示下一首歌曲名、歌星名
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"%s    %s",song_name,singer_name);
		draw_text_to_image(image_graphics,574,646,600,42,StringAlignmentNear,Color(255,255,255,255),song_font,show_text);
		memset(m_next_song_info,0x0,sizeof(m_next_song_info));
		_tcscpy(m_next_song_info,show_text);

		//显示相似度
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\score_image\\%02d.png",m_work_path,(average_similarity/10)*10);
		show_image = Image::FromFile(path);
		if (show_image&&(Ok==show_image->GetLastStatus()))
		{
			RectF des_rect;

			des_rect.X = 339.0;
			des_rect.Y = 364.0;
			des_rect.Width = show_image->GetWidth()*1.0;
			des_rect.Height = show_image->GetHeight()*1.0;
			image_graphics.DrawImage(show_image,des_rect,0,0,show_image->GetWidth()*1.0,show_image->GetHeight()*1.0,UnitPixel);
			delete show_image;
			show_image = NULL;
		}
		//显示分数
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"%d",average_similarity);
		draw_text_to_image(image_graphics,555,360,50,28,StringAlignmentNear,Color(255,0x97,0xF1,0xFF),score1_font,show_text);

		//完整度
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\score_image\\%02d.png",m_work_path,(average_intact/10)*10);
		show_image = Image::FromFile(path);
		if (show_image&&(Ok==show_image->GetLastStatus()))
		{
			RectF des_rect;

			des_rect.X = 339.0;
			des_rect.Y = 406.0;
			des_rect.Width = show_image->GetWidth()*1.0;
			des_rect.Height = show_image->GetHeight()*1.0;
			image_graphics.DrawImage(show_image,des_rect,0,0,show_image->GetWidth(),show_image->GetHeight(),UnitPixel);
			delete show_image;
			show_image = NULL;
		}
		//显示分数
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"%d",average_intact);
		draw_text_to_image(image_graphics,555,405,50,28,StringAlignmentNear,Color(255,0x97,0xF1,0xFF),score1_font,show_text);

		//稳定度
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\score_image\\%02d.png",m_work_path,(average_stability/10)*10);
		show_image = Image::FromFile(path);
		if (show_image&&(Ok==show_image->GetLastStatus()))
		{
			RectF des_rect;

			des_rect.X = 339.0;
			des_rect.Y = 452.0;
			des_rect.Width = show_image->GetWidth()*1.0;
			des_rect.Height = show_image->GetHeight()*1.0;
			image_graphics.DrawImage(show_image,des_rect,0,0,show_image->GetWidth(),show_image->GetHeight(),UnitPixel);
			delete show_image;
			show_image = NULL;
		}
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"%d",average_stability);
		draw_text_to_image(image_graphics,555,451,50,28,StringAlignmentNear,Color(255,0x97,0xF1,0xFF),score1_font,show_text);

		//卡路里
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"%d",total_calories);
		draw_text_to_image(image_graphics,800,530,139,55,StringAlignmentCenter,Color(255,0xff,0xf6,0x00),score2_font,show_text);

		//得到保存路径
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\SongIipImage.bmp",m_work_path);
		//delete src picture
		DeleteFile(path);

		//创建bitmap位图
		Bitmap save_bitmap(m_sencond_display_width,m_sencond_display_height,PixelFormat24bppRGB);
		//根据bitmap构造graphics
		Graphics  draw_graphics(&save_bitmap);  
		//目标区域
		des_rect.X = 0.0f;
		des_rect.Y = 0.0f;
		des_rect.Width = m_sencond_display_width*1.0f;
		des_rect.Height = m_sencond_display_height*1.0f;
		width = clone_image->GetWidth()*1.0f;
		height = clone_image->GetHeight()*1.0f;
		//缩放绘制到目标bitmap上
		draw_graphics.DrawImage(clone_image,des_rect, 0,0,width,height,UnitPixel);  
		//保存图片
		Status return_status = save_bitmap.Save(path,  &encoderClsid,  &encoderParameters);
		if (Ok!=return_status)
		{
			//换一种方式保存
			clone_image->Save(path,&encoderClsid,&encoderParameters);
		}
		//释放内存
		delete clone_image;
		clone_image = NULL;

		return true;
	}
	catch (...)
	{

	}

	return false;
}

bool Cflashktv10Wnd::save_music_enjoy_osd(const TCHAR* src_path, TCHAR* des_path)
{
	try
	{
		Image  *music_enjoy_img;
		music_enjoy_img = Image::FromFile(src_path);
		
		//判断图片是否存在
		if (NULL==music_enjoy_img)
		{
			return false;
		}
		Status last_status = music_enjoy_img->GetLastStatus();
		if (Ok!=last_status)
		{
			return false;
		}
		//背景图片存在在显示
		CLSID              encoderClsid;  
		EncoderParameters  encoderParameters; 
		bool result=false;
		song_info playing_song;
		TCHAR song_name[256];
		TCHAR singer_name[256];
		TCHAR song_id[256];
		RectF text_rect;
		StringFormat text_format;
		Font myFont(L"微软雅黑",5,FontStyleBold);
		SolidBrush text_brush(Color(255,46,0,22));
		Image *show_image=NULL;
		decrypt_picture decrypt_song_image;
		TCHAR show_text[256];
		RectF des_rect;
		REAL width=0.0f;
		REAL height=0.0f;

		memset(song_name,0x0,sizeof(song_name));
		memset(singer_name,0x0,sizeof(singer_name));
		memset(song_id,0x0,sizeof(song_id));

		//得到下一个播放的歌曲
		result = m_player_manager.get_playing_video(playing_song);
		if (!result)
		{
			return false;
		}
		//得到歌曲名字
		playing_song.get_song_name(song_name);
		if (0==_tcscmp(song_name,L""))
		{
			return false;
		}
		playing_song.get_singer_name(singer_name);
		playing_song.get_song_id(song_id);

		//克隆一个图片
		Image *clone_image = music_enjoy_img->Clone();
		if (NULL==clone_image)
		{
			return false;
		}
		Graphics image_graphics(clone_image);

		int qurity = 100;

		//设置图片编码参数
		encoderParameters.Count  =  1;  
		encoderParameters.Parameter[0].Guid  =  EncoderQuality;  
		encoderParameters.Parameter[0].Type  =  EncoderParameterValueTypeLong;  
		encoderParameters.Parameter[0].NumberOfValues  =  1;  
		encoderParameters.Parameter[0].Value  =  &qurity; 

		//得到位图的clsid
		result = GetEncoderClsid(L"image/bmp",  &encoderClsid);  
		if (!result)
		{
			return false;
		}
		//显示歌曲名
		text_rect.X = 250.0f;
		text_rect.Y = 300.0f;
		text_rect.Width = 900.0f;
		text_rect.Height = 85.0f;
		text_format.SetAlignment(StringAlignmentNear);
		text_format.SetLineAlignment(StringAlignmentCenter);
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"正在播放：%s",song_name);
		image_graphics.DrawString(show_text,-1,&myFont,text_rect,&text_format,&text_brush);
		//显示歌星名
		text_rect.X = 250.0f;
		text_rect.Y = 340.0f;
		text_rect.Width = 900.0f;
		text_rect.Height = 85.0f;
		text_format.SetAlignment(StringAlignmentNear);
		text_format.SetLineAlignment(StringAlignmentCenter);
		text_brush.SetColor(Color(255,246,229,237));
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"歌星名：%s",singer_name);
		image_graphics.DrawString(show_text,-1,&myFont,text_rect,&text_format,&text_brush);

		//得到保存路径
		memset(des_path,0x0,sizeof(des_path));
		swprintf(des_path,L"%s\\%s\\osd.bmp",m_work_path,g_folder_name[39]);
		//delete src picture
		DeleteFile(des_path);

		//创建bitmap位图
		Bitmap save_bitmap(m_sencond_display_width/3,m_sencond_display_height/3,PixelFormat24bppRGB);
		//根据bitmap构造graphics
		Graphics  draw_graphics(&save_bitmap);  
		//目标区域
		des_rect.X = 0.0f;
		des_rect.Y = 0.0f;
		des_rect.Width = m_sencond_display_width*1.0f/3;
		des_rect.Height = m_sencond_display_height*1.0f/3;
		width = clone_image->GetWidth()*1.0f;
		height = clone_image->GetHeight()*1.0f;
		//缩放绘制到目标bitmap上
		draw_graphics.DrawImage(clone_image,des_rect, 0,0,width,height,UnitPixel);  
		//保存图片
		Status return_status = save_bitmap.Save(des_path,  &encoderClsid,  &encoderParameters);
		if (Ok!=return_status)
		{
			//换一种方式保存
			clone_image->Save(des_path,&encoderClsid,&encoderParameters);
		}
		//释放内存
		delete clone_image;
		clone_image = NULL;

		return true;
	}
	catch (...)
	{

	}

	return false;
}

bool Cflashktv10Wnd::save_song_tip_osd(void)
{
	try
	{
		//设置标识
		m_show_song_tip_osd = false;
		//判断图片是否存在
		if (NULL==m_song_tip_image)
		{
			return false;
		}
		Status last_status = m_song_tip_image->GetLastStatus();
		if (Ok!=last_status)
		{
			return false;
		}
		//背景图片存在在显示
		CLSID              encoderClsid;  
		EncoderParameters  encoderParameters; 
		TCHAR path[256];
		bool result=false;
		song_info playing_song;
		TCHAR song_name[256];
		TCHAR singer_name[256];
		TCHAR song_id[256];
		TCHAR song_image_path[256];
		RectF text_rect;
		StringFormat text_format;
		Font myFont(L"微软雅黑",32,FontStyleBold);
		SolidBrush text_brush(Color(255,46,0,22));
		Image *show_image=NULL;
		decrypt_picture decrypt_song_image;
		TCHAR show_text[256];
		RectF des_rect;
		REAL width=0.0f;
		REAL height=0.0f;


		memset(path,0x0,sizeof(path));
		memset(song_name,0x0,sizeof(song_name));
		memset(singer_name,0x0,sizeof(singer_name));
		memset(song_id,0x0,sizeof(song_id));

		//得到下一个播放的歌曲
		result = m_player_manager.get_playing_video(playing_song);
		if (!result)
		{
			return false;
		}
		//得到歌曲名字
		playing_song.get_song_name(song_name);
		if (0==_tcscmp(song_name,L""))
		{
			return false;
		}
		playing_song.get_singer_name(singer_name);
		playing_song.get_song_id(song_id);

		//克隆一个图片
		Image *clone_image = m_song_tip_image->Clone();
		if (NULL==clone_image)
		{
			return false;
		}
		Graphics image_graphics(clone_image);

		int qurity = 100;

		//设置图片编码参数
		encoderParameters.Count  =  1;  
		encoderParameters.Parameter[0].Guid  =  EncoderQuality;  
		encoderParameters.Parameter[0].Type  =  EncoderParameterValueTypeLong;  
		encoderParameters.Parameter[0].NumberOfValues  =  1;  
		encoderParameters.Parameter[0].Value  =  &qurity; 

		//得到位图的clsid
		result = GetEncoderClsid(L"image/bmp",  &encoderClsid);  
		if (!result)
		{
			return false;
		}
		//显示歌曲名
		text_rect.X = 320.0f;
		text_rect.Y = 20.0f;
		text_rect.Width = 900.0f;
		text_rect.Height = 85.0f;
		text_format.SetAlignment(StringAlignmentNear);
		text_format.SetLineAlignment(StringAlignmentCenter);
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"歌名：%s",song_name);
		image_graphics.DrawString(show_text,-1,&myFont,text_rect,&text_format,&text_brush);
		//显示歌星名
		text_rect.X = 320.0f;
		text_rect.Y = 105.0f;
		text_rect.Width = 900.0f;
		text_rect.Height = 85.0f;
		text_format.SetAlignment(StringAlignmentNear);
		text_format.SetLineAlignment(StringAlignmentCenter);
		text_brush.SetColor(Color(255,246,229,237));
		memset(show_text,0x0,sizeof(show_text));
		swprintf(show_text,L"歌星：%s",singer_name);
		image_graphics.DrawString(show_text,-1,&myFont,text_rect,&text_format,&text_brush);
		//显示歌星图片
		memset(path,0x0,sizeof(path));
		//得到歌星图片路径
		result = get_singer_image_path(singer_name,NULL,NULL,path);
		show_image = Image::FromFile(path);
		if (show_image)
		{
			text_rect.X = 223.0f;
			text_rect.Y = 245.0f;
			text_rect.Width = 299.0f;
			text_rect.Height = 360.0f;
			width = show_image->GetWidth()*1.0f;
			height = show_image->GetHeight()*1.0f;
			image_graphics.DrawImage(show_image,text_rect,0.0f,0.0f,width,height,UnitPixel);
			//释放内存
			delete show_image;
			show_image = NULL;
		}
		//解密歌曲图片
		memset(song_image_path,0x0,sizeof(song_image_path));
		swprintf(song_image_path,L"%s\\%s",m_work_path,g_folder_name[25]);
		result = decrypt_song_image.decrypt_song_picture(song_id,444,song_image_path,path);
		if (!result || !PathFileExists(path))
		{
			//采用默认图片
			memset(path,0x0,sizeof(path));
			swprintf(path,L"%s\\default.jpg",song_image_path);
		}
		//显示歌曲图片
		show_image = Image::FromFile(path);
		if (show_image)
		{
			text_rect.X = 768.0f;
			text_rect.Y = 360.0f;
			text_rect.Width = 248.0f;
			text_rect.Height = 136.0f;
			width = show_image->GetWidth()*1.0f;
			height = show_image->GetHeight()*1.0f;
			image_graphics.DrawImage(show_image,text_rect,0.0f,0.0f,width,height,UnitPixel);
			//释放内存
			delete show_image;
			show_image = NULL;
		}

		//得到保存路径
		memset(path,0x0,sizeof(path));
		swprintf(path,L"%s\\SongIipImage.bmp",m_work_path);
		//delete src picture
		DeleteFile(path);

		//创建bitmap位图
		Bitmap save_bitmap(m_sencond_display_width,m_sencond_display_height,PixelFormat24bppRGB);
		//根据bitmap构造graphics
		Graphics  draw_graphics(&save_bitmap);  
		//目标区域
		des_rect.X = 0.0f;
		des_rect.Y = 0.0f;
		des_rect.Width = m_sencond_display_width*1.0f;
		des_rect.Height = m_sencond_display_height*1.0f;
		width = clone_image->GetWidth()*1.0f;
		height = clone_image->GetHeight()*1.0f;
		//缩放绘制到目标bitmap上
		draw_graphics.DrawImage(clone_image,des_rect, 0,0,width,height,UnitPixel);  
		//保存图片
		Status return_status = save_bitmap.Save(path,  &encoderClsid,  &encoderParameters);
		if (Ok!=return_status)
		{
			//换一种方式保存
			clone_image->Save(path,&encoderClsid,&encoderParameters);
		}
		//释放内存
		delete clone_image;
		clone_image = NULL;

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool Cflashktv10Wnd::show_song_tip_osd(void)
{
	try
	{
		TCHAR image_path[256];

		memset(image_path,0x0,sizeof(image_path));
		//图片路径
		swprintf(image_path,L"%s\\SongIipImage.bmp",m_work_path);
		if (PathFileExists(image_path))
		{
			//存在，显示到电视屏幕上
			show_picture_on_tv(image_path,OSDAlignmentCenter,3000,false,true);
		}

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

void Cflashktv10Wnd::set_video_play_pos(const TCHAR *args)
{
	try
	{
		int play_pos=0;
		int total_time_length=0;
		int cur_time_lenght=0;
		int play_time_length=0;

		if (NULL==args)
		{
			return;
		}
		swscanf(args,L"%d",&play_pos);
		//得到播放时长
		total_time_length = m_player_manager.get_total_time_length();
		cur_time_lenght = m_player_manager.get_play_time_length();
		//计算播放位置
		if (0==_tcscmp(args,L"101"))  //快进
		{
			play_time_length = cur_time_lenght-10;
		}
		else if (0==_tcscmp(args,L"102"))  //快退
		{
			play_time_length = cur_time_lenght+10;
		}
		else   //拖动定位
		{
			play_time_length = total_time_length*play_pos/100;
		}
		if (play_time_length<0)
		{
			play_time_length = 0;
		}
		else if (play_time_length>total_time_length)
		{
			play_time_length = total_time_length-5;
		}
		//设置播放位置
		m_player_manager.seek(play_time_length);

		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::send_keybd_code_to_game(int keybd_code)
{
	try
	{
		if (!m_game_flash_player_exist)
		{
			return;
		}

		TCHAR request[256];
		TCHAR data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//重新计时
		m_interative_game_timer.start();

		if (117==keybd_code)
		{
			//转化成键盘的左
			keybd_code = 37;
		}
		else if (33==keybd_code)
		{
			//转化成键盘的上
			keybd_code = 38;
		}
		else if (119==keybd_code)
		{
			//转化成键盘的右
			keybd_code = 39;
		}
		else if (34==keybd_code)
		{
			//转化成键盘的下
			keybd_code = 40;
		}

		if ((0!=m_show_game_window_number)&&('M'==keybd_code))  //M==77
		{
			//游戏显示在软解窗口或墙面板中，需要显示和隐藏
			if (m_game_window.IsWindowVisible())
			{
				//显示，就隐藏
				m_game_window.ShowWindow(SW_HIDE);
			}
			else
			{
				//隐藏，就显示
				m_game_window.BringWindowToTop();
				m_game_window.ShowWindow(SW_SHOW);
			}
			//焦点定位到主窗口
			SetFocus();
		}
		else if ((0!=m_show_game_window_number)&&(0==_tcscmp(m_interactive_game_page,L"main"))&&(27==keybd_code))
		{
			//如果是首页，在返回，就隐藏
			m_game_window.ShowWindow(SW_HIDE);
			//焦点定位到主窗口
			SetFocus();
		}
		else if ((0!=m_show_game_window_number)&&(!m_game_window.IsWindowVisible())&&(13==keybd_code))
		{
			//隐藏的时候点击开始按钮就显示
			m_game_window.BringWindowToTop();
			m_game_window.ShowWindow(SW_SHOW);
			//焦点定位到主窗口
			SetFocus();

			return;
		}

		if (m_game_window.IsWindowVisible())
		{
			//显示状态在发送键值码给游戏
			//键盘码值
			swprintf(data,L"%d",keybd_code);
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"keybd_code",data);
			if (result)
			{
				//启动了互动游戏，要把ps2码传递给flash
				m_game_flash_player.CallFunction(request);
			}
			//聚焦到当前页面
			SetFocus();
		}

		return;
	}
	catch (...)
	{
		
	}
	
	return;
}


void Cflashktv10Wnd::send_query_panel_to_flash(void)
{
	try
	{
		TCHAR folder_name[256];
		TCHAR request[10240];
		TCHAR data[10240];
		TCHAR path[256];
		TCHAR item_data[256];
		int image_count=0;
		bool result=false;

		memset(folder_name,0x0,sizeof(folder_name));
		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		memset(item_data,0x0,sizeof(item_data));

		_tcscpy(data,L"<data>");

		for (int i=0;i<9;i++)
		{
			switch (i)
			{
			case 0:   //年代金曲
				{
					_tcscpy(folder_name,L"btn_era");
					image_count=8;
				}
				break;
			case 1:    //电影
				{
					_tcscpy(folder_name,L"btn_film");
					image_count=8;
				}
				break;
			case 2:   //游戏
				{
					_tcscpy(folder_name,L"btn_game");
					image_count=8;
				}
				break;
			case 3:   //主题
				{
					_tcscpy(folder_name,L"btn_new_theme");
					image_count=8;
				}
				break;
			case 4:   //分类
				{
					_tcscpy(folder_name,L"btn_theme");
					image_count=8;
				}
				break;
			case 5:  //戏曲
				{
					_tcscpy(folder_name,L"btn_opera");
					image_count=8;
				}
				break;
			case 6:  //屏切
				{
					_tcscpy(folder_name,L"btn_video");
					image_count=10;
				}
				break;
			case  7:  //会员管理
				{
					_tcscpy(folder_name,L"btn_vip");
					image_count=4;
				}
				break;
			case 8:     //场所介绍
				{
					_tcscpy(folder_name,L"place");
					image_count=4;
				}
				break;
			default:
				break;;
			}

			//组织路径
			memset(path,0x0,sizeof(path));
			swprintf(path,L"<path src=\"%s\">",folder_name);
			_tcscat(data,path);
			
			for (int j=0;j<image_count;j++)
			{
				memset(path,0x0,sizeof(path));
				memset(item_data,0x0,sizeof(item_data));

				swprintf(path,L"%s\\%s\\%s\\%s\\image%d.png",m_work_path,g_folder_name[32],m_cur_interface_version,folder_name,j);
				if (PathFileExists(path))
				{
					swprintf(item_data,L"<info image=\"%s\" />",path);
					_tcscat(data,item_data);
				}
			}
			_tcscat(data,L"</path>");
		}
		_tcscat(data,L"</data>");
		//组织xml字符串
		result = m_flash_manage.make_request(request,sizeof(request)/2,L"QueryPanelImage",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::send_big_help_image_to_flash(void)
{
	try
	{
		TCHAR request[10240];
		TCHAR data[10240];
		TCHAR path[256];
		TCHAR item_data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		memset(item_data,0x0,sizeof(item_data));

		_tcscpy(data,L"<data>");
		for (int j=0;j<10;j++)
		{
			memset(path,0x0,sizeof(path));
			memset(item_data,0x0,sizeof(item_data));

			swprintf(path,L"%s\\%s\\0%d.png",m_work_path,g_folder_name[38],j);
			if (PathFileExists(path))
			{
				swprintf(item_data,L"<img url=\"%s\" />",path);
				_tcscat(data,item_data);
			}
		}
		_tcscat(data,L"</data>");
		//组织xml字符串
		result = m_flash_manage.make_request(request,sizeof(request)/2,L"tvImage",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::send_pinqie_image_to_flash(void)
{
	try
	{
		TCHAR request[10240];
		TCHAR data[10240];
		TCHAR path[256];
		TCHAR item_data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		memset(item_data,0x0,sizeof(item_data));

		_tcscpy(data,L"<data>");
		for (int j=0;j<10;j++)
		{
			memset(path,0x0,sizeof(path));
			memset(item_data,0x0,sizeof(item_data));

			swprintf(path,L"%s\\%s\\%s\\btn_video\\image%d.png",m_work_path,g_folder_name[32],m_cur_interface_version,j);
			if (PathFileExists(path))
			{
				swprintf(item_data,L"<img url=\"%s\" />",path);
				_tcscat(data,item_data);
			}
		}
		_tcscat(data,L"</data>");
		//组织xml字符串
		result = m_flash_manage.make_request(request,sizeof(request)/2,L"tvImage",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::send_national_flag_to_flash(void)
{
	try
	{
		TCHAR path[256];
		TCHAR data[1024];
		TCHAR request[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		_tcscpy(data,L"<data><path>");
		for (int i=0;i<5;i++)
		{
			memset(path,0x0,sizeof(path));
			swprintf(path,L"<info image=\"%s\\%s\\National_flag\\image%d.png\" />",m_work_path,g_folder_name[32],i);
			_tcscat(data,path);
		}
		_tcscat(data,L"</path></data>");
		//组织xml字符串
		result = m_flash_manage.make_request(request,sizeof(request)/2,L"NationalFlagImage",data);
		if (result)
		{
			flash_player_call_function(request);
		}

	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::send_opinion_image_to_flash(void)
{
	try
	{
		TCHAR path[256];
		TCHAR data[1024];
		TCHAR request[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		_tcscpy(data,L"<data><path>");
		for (int i=0;i<7;i++)
		{
			memset(path,0x0,sizeof(path));
			swprintf(path,L"<info image=\"%s\\%s\\opinion\\image%d.png\" />",m_work_path,g_folder_name[32],i);
			_tcscat(data,path);
		}
		_tcscat(data,L"</path></data>");
		//组织xml字符串
		result = m_flash_manage.make_request(request,sizeof(request)/2,L"OpinionImage",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch (...)
	{

	}
	return;
}

void Cflashktv10Wnd::cancel_call_service(void)
{
	try
	{
		TCHAR message[1024];

		memset(message,0x0,sizeof(message));
		//设置标识
		m_call_service_state = false;
		//发送给中控盒
		write_com_data(COM_SEND_CANCEL_SERVER);
		if (CLOSE_ROOM_STATE==m_pc_state)
		{
			//关房状态，熄灭服务灯
			write_com_data(COM_SEND_CLOSE_SERVICE_LIGHT);
		}
		//取消呼叫的字符串
		swprintf(message,L"Message^&cancel取消呼叫^&%s^&%s^&0",_tcsupr(m_show_room_name),_tcslwr(m_show_room_name));
		//发送给消息服务器
		send_message_to_msg_server(message);
		//设置服务按钮状态
		send_service_button_state(m_click_service_button_number,0);
		//发送给门牌机
		send_service_state_to_doorplate(false);

		return;
	}
	catch (...)
	{
		
	}

	return;
}


void Cflashktv10Wnd::send_service_button_state(int button_number,int button_state)
{
	try
	{
		if (!m_pc_allow_cancel_service)
		{
			//不允许取消呼叫，就不用发送状态了。
			return;
		}
		TCHAR data[1024];
		TCHAR request[1024];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//发送服务按钮状态给flash
		swprintf(data,L"<data><info button=\"%d\" state=\"%d\" /></data>",button_number,button_state);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"ServiceButtonState",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::hide_plug_in_drinks(void)
{
	try
	{
		if (m_drinks_flash_player_exist)
		{
			m_drinks_flash_player.ShowWindow(SW_HIDE);
		}
		//设置内嵌酒水状态
		m_show_drinks_state=false;

		return;
	}
	catch (...)
	{
		
	}

	return;
}

bool Cflashktv10Wnd::get_room_info(TCHAR *room_info)
{
	try
	{
		if (NULL==room_info)
		{
			return false;
		}
		config_file_manager room_file_manager;
		std::wstring  room_type;

		//初始化配置文件
		room_file_manager.init(L"room_type.ini");
		//得到包房类型
		room_type = room_file_manager.read_string(L"room_type",m_show_room_name,L"");
		//组织字符串
		swprintf(room_info,L"<data><info name=\"%s\" type=\"%s\" open_time=\"\" people_count=\"\" consume_length=\"\" consume_money=\"\"/></data>",m_show_room_name,room_type.c_str());

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

void Cflashktv10Wnd::doorplate_show_scroll_text(TCHAR *scroll_text,int scroll_count)
{
	try
	{
		if (m_doorplate_show_scroll_text&&m_doorplate_window_exist&&m_doorplate_init_success)
		{
			TCHAR request[2048];
			TCHAR data[2048];
			bool result=false;

			memset(request,0x0,sizeof(request));
			memset(data,0x0,sizeof(data));

			//组织
			swprintf(data,L"<info><text>%s</text><scrollNumber>%d</scrollNumber></info>",scroll_text,scroll_count);
			//发送给门牌机
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"set_scroll_text",data);
			if (result)
			{
				m_doorplate_flash_player.CallFunction(request);
			}
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::send_service_state_to_doorplate(bool service_state)
{
	try
	{
		if (!m_doorplate_init_success)
		{
			return;
		}

		TCHAR request[256];
		bool result=false;

		memset(request,0x0,sizeof(request));

		if (service_state)
		{
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"set_isShowServicesBtn",L"true");
		}
		else
		{
			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"set_isShowServicesBtn",L"false");
		}
		if (result)
		{
			m_doorplate_flash_player.CallFunction(request);
		}
	}
	catch (...)
	{
		
	}
	return;
}

void Cflashktv10Wnd::set_guid_song_button_state(bool show_state)
{
	try
	{
		TCHAR request[256];
		TCHAR data[256];
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		if (show_state)
		{
			//高亮
			_tcscpy(data,L"<data><is_guide>true</is_guide></data>");
		}
		else
		{
			//取消高亮
			_tcscpy(data,L"<data><is_guide>false</is_guide></data>");
		}
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"guide_button",data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::update_sort_button_state(void)
{
	try
	{
		TCHAR request[1024];
		TCHAR data[1024];
		bool result=false;
		int page_index=0;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		//得到当前页面索引
		page_index = m_flash_manage.get_last_page_index();
		switch(page_index)
		{
		case page_selected:   //不存在排序的页面
		case page_singed:
		case page_new_song:
		case page_lyric:
		case page_U_disk:
		case page_recording:
		case page_movie_song:
		case page_movie:        
		case page_concert:  //演唱会
		case page_place_video:  //场所视频
		case  page_voice_china:  //好声音
			{
				_tcscpy(data,L"<data><showbtn>disable</showbtn></data>");
			}
			break;
		default:
			{
				swprintf(data,L"<data><showbtn>%s</showbtn></data>",m_show_sort_mode);
			}
			break;
		}
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"sort",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}


void Cflashktv10Wnd::set_button_show_state(enum BUTTON_STATE button_flag,bool show_state)
{
	try
	{
		TCHAR request[256];
		TCHAR data[256];
		bool result=false;
		TCHAR command[256];

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		memset(command,0x0,sizeof(command));

		switch(button_flag)
		{
		case GUID_BUTTON_STATE:   //导唱按钮状态
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_guide>true</is_guide></data>");
				}
				else
				{
					//取消高亮
					_tcscpy(data,L"<data><is_guide>false</is_guide></data>");
				}
				_tcscpy(command,L"guide_button");
			}
			break;
		case SCORE_BUTTON_STATE: //评分按钮状态
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_score>true</is_score></data>");
				}
				else
				{
					//取消高亮
					_tcscpy(data,L"<data><is_score>false</is_score></data>");
				}
				_tcscpy(command,L"score_button");
			}
			break;
		case TAPE_BUTTON_STATE:  //录音按钮状态
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_tape>true</is_tape></data>");
				}
				else
				{
					//取消高亮
					_tcscpy(data,L"<data><is_tape>false</is_tape></data>");
				}
				_tcscpy(command,L"tape_button");
			}
			break;
		case ENJOY_BUTTON_STATE:  //欣赏按钮状态
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_guide>true</is_guide></data>");
				}
				else
				{
					//取消高亮
					_tcscpy(data,L"<data><is_guide>false</is_guide></data>");
				}
				_tcscpy(command,L"guide_button");
			}
			break;
		case ROOM_BUTTON_STATE:
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_room>false</is_room></data>");
				}
				else
				{
					//取消高亮
					_tcscpy(data,L"<data><is_room>true</is_room></data>");
				}
				_tcscpy(command,L"room_button");
			}
			break;
		case MOVIE_BUTTON_STATE:
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_movie>true</is_movie></data>");
				}
				else
				{

					//取消高亮
					_tcscpy(data,L"<data><is_movie>false</is_movie></data>");
				}
				_tcscpy(command,L"movie_button");
			}
			break;
		case DJ_BUTTON_STATE:
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_DJ>true</is_DJ></data>");
				}
				else
				{ 
					//取消高亮
					_tcscpy(data,L"<data><is_DJ>false</is_DJ></data>");
				}
				_tcscpy(command,L"dj_button");
			}
			break;
		case OPEN_SERVER_WINDOW:
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_server>true</is_server></data>");
				}
				else
				{ 
					//取消高亮
					_tcscpy(data,L"<data><is_server>false</is_server></data>");
				}
				_tcscpy(command,L"server_button");
			}
			break;
		case VIDEO_DATING_STATE:
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_video_dating>true</is_video_dating></data>");
				}
				else
				{ 
					//取消高亮
					_tcscpy(data,L"<data><is_video_dating>false</is_video_dating></data>");
				}
				_tcscpy(command,L"video_dating_button");
			}
			break;
		case SHOW_CLOUD_SONG_STATE:
			{
				if (show_state)
				{
					//高亮
					_tcscpy(data,L"<data><is_yunadd>true</is_yunadd></data>");
				}
				else
				{ 
					//取消高亮
					_tcscpy(data,L"<data><is_yunadd>false</is_yunadd></data>");
				}
				_tcscpy(command,L"yunadd_button");
			}
			break;
		default:
			break;
		}

		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}

	return;
}


void Cflashktv10Wnd::send_tape_audio_count_to_flash(void)
{
	try
	{
		TCHAR request[256];
		TCHAR data[256];
		int row = 0;
		bool result=false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		row = m_db_query.get_row_count("select count(song_id) from song_recorder");
		swprintf(data,L"<data><record row=\"%d\" /></data>",row);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"tape_count",data);
		if(result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{

	}

	return ;
}

void Cflashktv10Wnd::set_query_sort_mode()
{
	try
	{
		int page_index=0;

		memset(m_db_order_item,0x0,sizeof(m_db_order_item));
		//得到页面索引
		page_index = m_flash_manage.get_last_page_index();
		switch (page_index)
		{
		case page_new_song:  //新歌
			{
				_tcscpy(m_db_order_item,L"new_song_date desc");
			}
			break;
		case page_title:  //歌名页面
		case page_singer_song:
		case page_theme_song:
		case page_new_theme_song:
		case page_class:
		case page_opera:
		case page_language:
		case page_era_song:
		case page_write:        //手写点歌
		case page_word_count:
		case page_hdmi:         //高清专区
		case page_voice_china:  //好声音
			{
				if (0!=_tcscmp(m_show_sort_mode,L"pinyin"))
				{
					//热度排序
					_tcscpy(m_db_order_item,L"sing_number desc");
				}
				else
				{
					//拼音排序
					_tcscpy(m_db_order_item,L"song_name_word_count asc");
				}
			}
			break;
		case page_top_song: //排行
			{
				_tcscpy(m_db_order_item,L"sing_number desc,song_name_word_count asc");
			}
			break;
		case page_singer:  //歌星
		case page_voice_china_singer:
			{
				if (0!=_tcscmp(m_show_sort_mode,L"pinyin"))
				{
					//按照热度、字数、拼音排序
					_tcscpy(m_db_order_item,L"singer_hot_rank desc,singer_name_word_count asc,singer_name asc");
					//_tcscpy(m_db_order_item,L"singer_name_word_count asc,singer_name asc,spell_first_letter_abbreviation asc");
				}
				else
				{
					//按照热度、字数、拼音排序
					_tcscpy(m_db_order_item,L"singer_name_word_count asc,singer_name asc,spell_first_letter_abbreviation asc");
					//_tcscpy(m_db_order_item,L"singer_hot_rank desc,singer_name_word_count asc,singer_name asc");
				}
			}
			break;
		//不排序的
		case page_movie_song:  //影视金曲
		default:
			break;
		}

		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::judge_soft_window_move(void)
{
	try
	{
		CString csTmp = _T("");

		int left_x = 0;
		int top_y=0;
		int width = 0;
		int height = 0;
		bool result=false;
		
		if (!m_soft_decode_window_exist)
		{
			//不是软解就不用判断了
			return;
		}
		
		//启用软解，判断第二个显卡是否存在
		result = get_display_device_settings(m_second_display_number,left_x,top_y,width,height);
		if (result)
		{
			csTmp.Format(_T("[judge_soft_window_move]:检测电视关闭 = 获得第二显卡成功"));
			//WriteLog(__FL__, csTmp);

			//根据微博调整窗口位置
			if (1 == m_weibo_version_number)
			{
				adjust_soft_window_width(left_x,width);
			}
			else if (2 == m_weibo_version_number)
			{
				adjust_soft_window_width(left_x,width,height);
				top_y += m_weibo_image_top_height;
			}

			//根据微博调整窗口位置
			//adjust_soft_window_width(left_x,width);


			//存在
			if (!m_second_display_exist ||(m_sencond_display_x!=left_x)||(m_sencond_display_y!=top_y)||(m_sencond_display_width!=width)||(m_sencond_display_height!=height))
			{
				csTmp.Format(_T("[judge_soft_window_move]:检测电视关闭 = 调整位置，并重启shplaysrv.exe"));
				//WriteLog(__FL__, csTmp);

				m_sencond_display_x = left_x;
				m_sencond_display_y = top_y;
				m_sencond_display_width = width;
				m_sencond_display_height = height;
				//移动软解窗口位置
				m_soft_decode_window.MoveWindow(m_sencond_display_x,m_sencond_display_y,m_sencond_display_width,m_sencond_display_height,TRUE);
				//重新启动控件
				teminate_process(L"ShPlaySrv.exe");
				csTmp.Format(_T("[judge_soft_window_move]:检测电视关闭 = 播放控件重启成功"));
				//WriteLog(__FL__, csTmp);
			}
			m_second_display_exist = true;
		}
		else
		{
			csTmp.Format(_T("[judge_soft_window_move]:检测电视关闭 = 获取第二块电视分辨率失败!"));
			//WriteLog(__FL__, csTmp);
			if (m_second_display_exist)
			{
				teminate_process(L"ShPlaySrv.exe");
				csTmp.Format(_T("[judge_soft_window_move]:检测电视关闭 = 第二块电视不存在，播放控件重启成功"));
				//WriteLog(__FL__, csTmp);
			}
			m_second_display_exist = false;
		}
		return;
	}
	catch (...)
	{
		
	}

	return;
}

void Cflashktv10Wnd::send_ktv_logo_to_flash(void)
{
	try
	{
		TCHAR path[256];
		TCHAR request[1024];
		bool result=false;

		memset(path,0x0,sizeof(path));
		memset(request,0x0,sizeof(request));

		//得到logo文件夹路径
		if (SCREEN_TYPE_VERTICAL==m_interface_type)
		{
			//竖版
			swprintf(path,L"%s\\%s\\logo_v.jpg",m_work_path,g_folder_name[8]);
		}
		else
		{
			//横版
			swprintf(path,L"%s\\%s\\logo_h.jpg",m_work_path,g_folder_name[8]);
		}
		if (!PathFileExists(path))
		{
			//logo文件不存在，使用旧的命名，为了和以前版本兼容
			swprintf(path,L"%s\\%s\\logo.jpg",m_work_path,g_folder_name[8]);
		}

		//发送给flash
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"LogoURL",path);
		if (result)
		{
			flash_player_call_function(request);
		}

		return;
	}
	catch(...)
	{

	}

	return;
}

void Cflashktv10Wnd::set_keyboard_type(int keyboard_type)
{
	try
	{
		TCHAR data[256];
		TCHAR request[1024];
		bool result=false;

		memset(data,0x0,sizeof(data));
		memset(request,0x0,sizeof(request));

		switch(keyboard_type)
		{
		case KEYBOARD_TYPE_CHINESE:   //中文键盘
			{
				_tcscpy(data,L"pinyin");
			}
			break;
		case KEYBOARD_TYPE_KOREAN:    //韩文键盘
			{
				_tcscpy(data,L"korean");
			}
			break;
		case KEYBOARD_TYPE_JAPANESE:  //日文键盘
			{
				_tcscpy(data,L"jap");
			}
			break;
		default:
			break;
		}

		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"showLanguageKeyboard",data);
		if (result)
		{
			flash_player_call_function(request);
		}

		if (m_handwriting_window_exist && m_show_handwriting_window) //隐藏手写
		{
			m_handwriting_window.ShowWindow(SW_HIDE);
		}

		return;
	}
	catch(...)
	{

	}
	return;
}

void Cflashktv10Wnd::show_weibo_system(void)
{
	try
	{
		config_file_manager config_file;
		bool result=false;
		TCHAR weibo_sys_path[256];

		//检测是否启用微博
		m_weibo_display_number = config_file.read_integer(L"weibo",L"weibo_show_screen_number",0);

#ifdef _DEBUG
		if (m_weibo_display_number<1)
#else
		if (m_weibo_display_number<2)
#endif
		{
			m_weibo_display_number = 0;
			return;
		}
		//启用微博系统
		memset(weibo_sys_path,0x0,sizeof(weibo_sys_path));
		swprintf(weibo_sys_path,L"%s\\ShineWeiBo%d.exe",m_work_path,m_weibo_version_number);
		start_plug_in_process(weibo_sys_path,SW_SHOW,m_weibo_process_id);
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::adjust_soft_window_width(int &left_pos,int &width)
{
	try
	{
		switch(m_weibo_show_mode)
		{
		case WEIBO_SHOW_MODE_LEFT:   //左边显示
			{
				if (m_weibo_display_number==m_second_display_number)
				{
					//在电视窗口中，半屏显示
					left_pos += m_weibo_image_width;
					width -= m_weibo_image_width;
				}
			}
			break;
		case WEIBO_SHOW_MODE_RIGHT: //右边显示
			{
				if (m_weibo_display_number==m_second_display_number)
				{
					//在电视窗口中，半屏显示
					width -= m_weibo_image_width;
				}
			}
			break;
		default:
			break;
		}

		return;
	}
	catch (...)
	{

	}

	return;
}


void Cflashktv10Wnd::adjust_soft_window_width(int &left_pos,int &width,int &height)
{
	try
	{
		if (2 == m_weibo_version_number)
		{
			m_weibo_show_mode = WEIBO_SHOW_MODE_RIGHT;
		}
		//只有一种方式
		switch(m_weibo_show_mode)
		{
		case WEIBO_SHOW_MODE_LEFT:   //左边显示
		case WEIBO_SHOW_MODE_RIGHT: //右边显示
			{
				if (m_weibo_display_number==m_second_display_number)
				{
					//在电视窗口中，半屏显示
					width -= m_weibo_image_width;
					height -= m_weibo_image_top_height;
				}
			}
			break;
		default:
			break;
		}

		return;
	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::Get_weibo_image_width(void)
{
	try
	{
		//判断是否启用微博，如果没有启动微博，直接返回
		config_file_manager config_file;
		int weibo_display_number = 0;
		weibo_display_number = config_file.read_integer(L"weibo",L"weibo_show_screen_number",0);

		//得到微博的版本号
		m_weibo_version_number = config_file.read_integer(L"weibo",L"weibo_version_number",1);

		if (0 == weibo_display_number)
		{
			return;
		}

		TCHAR image_path[256];
		Image *weibo_image=NULL;

		memset(image_path,0x0,sizeof(image_path));

		//微博图片路径
		swprintf(image_path,L"%s\\weibo_image%d\\image%d.png",m_work_path,m_weibo_version_number,m_weibo_show_mode);
		//得到微博图片宽度
		weibo_image = Image::FromFile(image_path);
		if (Ok==weibo_image->GetLastStatus())
		{
			m_weibo_image_width = (int)weibo_image->GetWidth();
		}

		if (2 == m_weibo_version_number)
		{
			memset(image_path,0x0,sizeof(image_path));
			//微博图片路径
			swprintf(image_path,L"%s\\weibo_image%d\\child_bg.png",m_work_path,m_weibo_version_number);
			//得到微博电视屏幕上图片高度
			weibo_image = Image::FromFile(image_path);
			if (Ok==weibo_image->GetLastStatus())
			{
				m_weibo_image_top_height = (int)weibo_image->GetHeight();
			}
		}
		
		delete weibo_image;
		weibo_image = NULL;
	}
	catch (...)
	{

	}

	return;
}


bool Cflashktv10Wnd::GetHostIP(char *local_ip)
{
	char host_name[256];
	struct hostent  *hp; 

	if (NULL==local_ip)
	{
		return false;
	}

	memset(host_name,0x0,sizeof(host_name));

	//得到计算机名字
	int nRet = gethostname(host_name,sizeof(host_name));
	//得到计算机IP
	hp = gethostbyname(host_name);
	if (hp && hp->h_addr_list[0])
	{
		//多字节IP
		strcpy(local_ip,inet_ntoa(*((struct in_addr *)hp->h_addr_list[0])));

		return true;
	}

	return false;
}

bool Cflashktv10Wnd::get_use_video_dating_function()
{
	bool result = false;
	char localHostIp[256];
	TCHAR wlocalHostIP[256];
	config_file_manager config_file;
	string_conversion str_cov;
	std::wstring itemvalue;

	result = GetHostIP(localHostIp);

	if (!result)
	{
		return false;
	}

	str_cov.multibyte_to_widechar(localHostIp,wlocalHostIP,sizeof(localHostIp));
	//是否启用pk
	config_file.init(L"video_box.ini");

	//得到音量
	m_audio_volume = config_file.read_integer(wlocalHostIP,L"audio_volume",60);
	//是否显示自己的视频
	m_pk_show_video = config_file.read_boolean(wlocalHostIP,L"show_video",true);

	//;对方视频的坐标，x,y,width,height
	//读取视频交友的坐标
	int m_rPositoin_myself_x=config_file.read_integer(wlocalHostIP,L"m_rPositoin_myself_x",302);//302;
	int m_rPositoin_myself_y=config_file.read_integer(wlocalHostIP,L"m_rPositoin_myself_y",240);//163;
	int m_rPositoin_myself_width=config_file.read_integer(wlocalHostIP,L"m_rPositoin_myself_width",490);//490;
	int m_rPositoin_myself_height=config_file.read_integer(wlocalHostIP,L"m_rPositoin_myself_height",273);//273;

	int m_rPositoin_otherside_x=config_file.read_integer(wlocalHostIP,L"m_rPositoin_otherside_x",802);//802;
	int m_rPositoin_otherside_y=config_file.read_integer(wlocalHostIP,L"m_rPositoin_otherside_y",417);//340;
	int m_rPositoin_otherside_width=config_file.read_integer(wlocalHostIP,L"m_rPositoin_otherside_width",176);//176;
	int m_rPositoin_otherside_height=config_file.read_integer(wlocalHostIP,L"m_rPositoin_otherside_height",96);//96;

	m_rectPosition_myself.left = m_rPositoin_myself_x;
	m_rectPosition_myself.top = m_rPositoin_myself_y;
	m_rectPosition_myself.right = m_rPositoin_myself_x + m_rPositoin_myself_width;
	m_rectPosition_myself.bottom = m_rPositoin_myself_y + m_rPositoin_myself_height; 

	m_rectPosition_otherside.left = m_rPositoin_otherside_x;
	m_rectPosition_otherside.top = m_rPositoin_otherside_y;
	m_rectPosition_otherside.right = m_rPositoin_otherside_x + m_rPositoin_otherside_width;
	m_rectPosition_otherside.bottom = m_rPositoin_otherside_y + m_rPositoin_otherside_height;
	return true;
}

bool Cflashktv10Wnd::get_use_pk_function()
{
	bool result = false;
	char localHostIp[256];
	TCHAR wlocalHostIP[256];
	config_file_manager config_file;
	string_conversion str_cov;
	std::wstring itemvalue;
	
	result = GetHostIP(localHostIp);
	
	if (!result)
	{
		return false;
	}
	
	str_cov.multibyte_to_widechar(localHostIp,wlocalHostIP,sizeof(localHostIp));
	
	//是否启用pk
	config_file.init(L"video_box.ini");
	result = config_file.read_boolean(wlocalHostIP,L"open_pk",L"false");
	if (!result)
	{
		return false;
	}
	
	//视频ip
	itemvalue = config_file.read_string(wlocalHostIP,L"video_ip",L"");
	swprintf(m_pk_local_video_ip,L"%s",itemvalue.c_str());
	if (0 == _tcscmp(m_pk_local_video_ip,L""))
	{
		return false;
	}

	//得到音量
	m_audio_volume = config_file.read_integer(wlocalHostIP,L"audio_volume",60);
	//是否显示自己的视频
	m_pk_show_video = config_file.read_boolean(wlocalHostIP,L"show_video",true);

	//读出视频的矩形位置
	//CRect rPosition0(302,163,792,436);
	//CRect rPosition1(802,340,978,436);

	//;对方视频的坐标，x,y,width,height
	int m_rPositoin0_x=config_file.read_integer(wlocalHostIP,L"m_rPositoin0_x",302);//302;
	int m_rPositoin0_y=config_file.read_integer(wlocalHostIP,L"m_rPositoin0_y",163);//163;
	int m_rPositoin0_width=config_file.read_integer(wlocalHostIP,L"m_rPositoin0_width",490);//490;
	int m_rPositoin0_height=config_file.read_integer(wlocalHostIP,L"m_rPositoin0_height",273);//273;
	
	//;自己视频的坐标，x,y,width,height
	int m_rPositoin1_x=config_file.read_integer(wlocalHostIP,L"m_rPositoin1_x",802);//802;
	int m_rPositoin1_y=config_file.read_integer(wlocalHostIP,L"m_rPositoin1_y",340);//340;
	int m_rPositoin1_width=config_file.read_integer(wlocalHostIP,L"m_rPositoin1_width",176);//176;
	int m_rPositoin1_height=config_file.read_integer(wlocalHostIP,L"m_rPositoin1_height",96);//96;
	
	m_rectPosition0.left = m_rPositoin0_x;
	m_rectPosition0.top = m_rPositoin0_y;
	m_rectPosition0.right = m_rPositoin0_x + m_rPositoin0_width;
	m_rectPosition0.bottom = m_rPositoin0_y + m_rPositoin0_height; 

	m_rectPosition1.left = m_rPositoin1_x;
	m_rectPosition1.top = m_rPositoin1_y;
	m_rectPosition1.right = m_rPositoin1_x + m_rPositoin1_width;
	m_rectPosition1.bottom = m_rPositoin1_y + m_rPositoin1_height;
	return true;
}


bool Cflashktv10Wnd::judge_generate_encode()
{
	try
	{
		config_file_manager config_file;

		m_ipad_ecode_again = config_file.read_boolean(L"ipad",L"ecode_again",true);
		if (m_ipad_ecode_again)
		{
			//清空IPAD的验证码
			config_file.write_string(L"ipad",L"login_password",L"");
			return true;
		}
		else
		{ 
			TCHAR tempIP[256];   //得到二维码的ip
			TCHAR ip_code0[3];
			TCHAR ip_code1[3];
			TCHAR ip_code2[3];
			TCHAR ip_code3[3];
			TCHAR ip_code4[3];
			int number0 = 0;
			int number1 = 0;
			int number2 = 0;
			int number3 = 0;
			int number4 = 0;

			memset(tempIP,0x0,sizeof(tempIP));

			memset(ip_code0,0x0,sizeof(ip_code0));
			memset(ip_code1,0x0,sizeof(ip_code1));
			memset(ip_code2,0x0,sizeof(ip_code2));
			memset(ip_code3,0x0,sizeof(ip_code3));
			memset(ip_code4,0x0,sizeof(ip_code4));

			_tcscpy(m_encode_picture_path,m_work_path);
			_tcscat(m_encode_picture_path,L"\\qr_picture\\ipad_encode.png");
			std::wstring ipad_login_code;

			ipad_login_code = config_file.read_string(L"ipad",L"login_password",L"");
			swprintf(m_ipad_login_code,L"%s",ipad_login_code.c_str());

			//Modify 2012-8-31 增加生成二维码IP判断
			_tcsncpy(ip_code0,m_ipad_login_code,2);
			_tcsncpy(ip_code1,&m_ipad_login_code[2],2);
			_tcsncpy(ip_code2,&m_ipad_login_code[4],2);
			_tcsncpy(ip_code3,&m_ipad_login_code[6],2);
			_tcsncpy(ip_code4,&m_ipad_login_code[8],2);

			_stscanf(ip_code0,L"%x",&number0); 
			_stscanf(ip_code1,L"%x",&number1); 
			_stscanf(ip_code2,L"%x",&number2); 
			_stscanf(ip_code3,L"%x",&number3); 
			_stscanf(ip_code4,L"%x",&number4);


			swprintf(tempIP,L"%d.%d.%d.%d",number0^number1,number0^number2,number0^number3,number0^number4);

			if (0 != _tcscmp(tempIP,m_room_ip))
			{
				//生成
				memset(m_ipad_login_code,0x0,sizeof(m_ipad_login_code));
				return true;
			}

			return false;
		}
	}
	catch (...)
	{

	}

	return false;
}

void Cflashktv10Wnd::set_music_enjoy_osd()
{
	song_info Video_info;
	//得到正播放视频
	m_player_manager.get_playing_video(Video_info);
	//显示osd
	TCHAR sztmp[256] = {0x00};
	Video_info.get_song_type(sztmp);

	if (_tcscmp(sztmp, L"1001") == 0) //百度
	{
//		m_osd_play_manager.set_osd_text(L"来源：百度音乐");
		m_player_manager.play_control_text_osd(L"来源：百度音乐", RGB(210,210,0), 50,200, 10);
	}else if (_tcscmp(sztmp, L"1002") == 0) //QQ音乐
	{
		m_player_manager.play_control_text_osd(L"来源：QQ音乐", RGB(210,210,0), 50,200, 10);
	}else if (_tcscmp(sztmp, L"1003") == 0) //酷狗
	{
		m_player_manager.play_control_text_osd(L"来源：酷狗音乐", RGB(210,210,0), 50,200, 10);
	}else if (_tcscmp(sztmp, L"1004") == 0) //酷我
	{
		m_player_manager.play_control_text_osd(L"来源：酷我音乐", RGB(210,210,0), 50,200, 10);
	}
	TCHAR szsong[256] = {0x00};
	Video_info.get_song_name(szsong);
	swprintf(sztmp,L"正在播放：%s",szsong);
	m_player_manager.play_control_text_osd(sztmp, RGB(210,210,0), 50,250, 11);

	Video_info.get_singer_name(szsong);
	swprintf(sztmp,L"演唱：%s",szsong);

	m_player_manager.play_control_text_osd(sztmp, RGB(210,210,0), 50,300, 12);
}

void Cflashktv10Wnd::stop_music_enjoy_osd()
{
	if(show_music_enjoy_lyric_timer_identifier > 0)
	{
		KillTimer(SHOW_MUSIC_ENJOY_LYRIC_TIME_EVENT_ID);
		m_music_enjoy_lyric_timer.stop();
		m_lyricManager.m_nLyricIndex=0;
		show_music_enjoy_lyric_timer_identifier = 0;
		m_dLyricLastTime = 0;
		m_bFlag = true;
	}
	m_player_manager.stop_play_control_text_osd(10);//来源
	m_player_manager.stop_play_control_text_osd(11);//歌曲名称
	m_player_manager.stop_play_control_text_osd(12);//演唱
	m_player_manager.stop_play_control_text_osd(8);//上歌词
	m_player_manager.stop_play_control_text_osd(9);//下歌词
}

void Cflashktv10Wnd::set_music_enjoy_osd_by_songinfo()
{
	song_info Video_info;
	//得到正播放视频
	m_player_manager.get_playing_video(Video_info);

	//显示osd
	TCHAR szsong_type[256] = {0x00};
	Video_info.get_song_type(szsong_type);
	if (_tcscmp(szsong_type, L"1001") == 0) //百度
	{
		set_music_enjoy_osd_show(0);
	}else if (_tcscmp(szsong_type, L"1002") == 0) //QQ音乐
	{
		set_music_enjoy_osd_show(1);
	}else if (_tcscmp(szsong_type, L"1003") == 0) //酷狗
	{
		set_music_enjoy_osd_show(2);
	}else if (_tcscmp(szsong_type, L"1004") == 0) //酷我
	{
		set_music_enjoy_osd_show(3);
	}
}

void Cflashktv10Wnd::set_music_enjoy_osd_show(int flag)
{
	TCHAR osd_path[256];
	TCHAR des_path[256];
	memset(osd_path,0x0,sizeof(osd_path));
	memset(des_path,0x0,sizeof(des_path));

	osd_text_picture osd_msg;
	play_variable play_var;

	switch(flag)
	{
	case 0:
		swprintf(des_path,L"%s\\%s\\baidu_default.jpg",m_work_path,g_folder_name[39]);
		break;
	case 1:
		swprintf(des_path,L"%s\\%s\\qq_default.jpg",m_work_path,g_folder_name[39]);
		break;
	case 2:
		swprintf(des_path,L"%s\\%s\\kugou_default.jpg",m_work_path,g_folder_name[39]);
		break;
	case 3:
		swprintf(des_path,L"%s\\%s\\kuwo_default.jpg",m_work_path,g_folder_name[39]);
		break;
	}

	if(save_music_enjoy_osd(des_path, osd_path))
	{
		//电视上显示图片
		bool ret = osd_msg.get_picture_play_variable(play_var);
		if (ret)
		{
			m_show_song_tip_osd = false;
			m_player_manager.play_bmp_osd(osd_path,play_var,OSDAlignmentTop);
		}
	}	
}

void Cflashktv10Wnd::set_pk_video_osd_picture()
{
	TCHAR osd_path[256];
	memset(osd_path,0x0,sizeof(osd_path));

	osd_text_picture osd_msg;
	play_variable play_var;

	swprintf(osd_path,L"%s\\%s\\bg.png",m_work_path,g_folder_name[37]);
	//电视上显示图片
	bool ret = osd_msg.get_picture_play_variable(play_var);
	if (ret)
	{

		m_player_manager.play_bmp_osd(osd_path,play_var,OSDPK);
	}
}


void Cflashktv10Wnd::send_song_name_data_to_weibo(TCHAR* play_song,TCHAR* next_song)
{
	try
	{
		TCHAR data[1024];
		memset(data,0x0,sizeof(data));

		struct linger zerolinger;
		int nSendTimeout = 6000;
		bool result=false;

		SOCKET send_socket = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		if (send_socket<0)
		{
			//创建socket失败
			return;
		}

		//设置socket属性
		zerolinger.l_onoff = 1;
		zerolinger.l_linger = 5;
		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));

		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&nSendTimeout,sizeof(nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in service_addr;
		service_addr.sin_family = AF_INET;
		service_addr.sin_addr.S_un.S_addr = inet_addr(m_send_room_ip);
		service_addr.sin_port = htons(2327);


		//Message&SHINEWERBO_SONGINFO;song_play:song_next$END
		//发送数据
		swprintf(data,L"Message&SHINEWERBO_SONGINFO;%s:%s$END",play_song,next_song);
		size_t len = _tcslen(data)*sizeof(TCHAR);

		len = ::sendto(send_socket,(char *)data,len,0,(sockaddr *)&service_addr,sizeof(service_addr));
		if(len>0)
		{
			//发送成功
		}
		//关闭socket
		::closesocket(send_socket);
		send_socket = -1;

	}
	catch (...)
	{

	}
	return;
}


void Cflashktv10Wnd::send_ad_data_to_weibo(TCHAR* ad_text)
{
	try
	{
		TCHAR data[1024];
		memset(data,0x0,sizeof(data));

		struct linger zerolinger;
		int nSendTimeout = 6000;
		bool result=false;

		SOCKET send_socket = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		if (send_socket<0)
		{
			//创建socket失败
			return;
		}

		//设置socket属性
		zerolinger.l_onoff = 1;
		zerolinger.l_linger = 5;
		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));

		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&nSendTimeout,sizeof(nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in service_addr;
		service_addr.sin_family = AF_INET;
		service_addr.sin_addr.S_un.S_addr = inet_addr(m_send_room_ip);
		service_addr.sin_port = htons(2327);


		//Message&SHINEWERBO_AD;ad_text$END
		//发送数据
		swprintf(data,L"Message&SHINEWERBO_AD;%s$END",ad_text);
		size_t len = _tcslen(data)*sizeof(TCHAR);

		len = ::sendto(send_socket,(char *)data,len,0,(sockaddr *)&service_addr,sizeof(service_addr));
		if(len>0)
		{
			//发送成功
		}
		//关闭socket
		::closesocket(send_socket);
		send_socket = -1;

	}
	catch (...)
	{

	}
	return;
}


bool Cflashktv10Wnd::draw_image_to_offscreen(Graphics &draw_handle,int x,int y,TCHAR *path)
{
	try
	{
		Image *show_image=NULL;
		RectF des_rect;

		show_image = Image::FromFile(path);
		if (show_image&&(Ok==show_image->GetLastStatus()))
		{
			RectF des_rect;

			des_rect.X = x*1.0f;
			des_rect.Y = y*1.0f;
			des_rect.Width = show_image->GetWidth()*1.0f;
			des_rect.Height = show_image->GetHeight()*1.0f;
			draw_handle.DrawImage(show_image,des_rect,0,0,show_image->GetWidth()*1.0f,show_image->GetHeight()*1.0f,UnitPixel);
			delete show_image;
			show_image = NULL;
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool Cflashktv10Wnd::show_wall_panel_interface(void)
{
	try
	{
		double last_time=0.0;

		//时间保护
		last_time = m_wall_panel_timer.last_time();
		if (last_time<0.5)
		{
			return false;
		}
		//重新计时
		m_wall_panel_timer.start();
		if(!m_wall_panel_image_show)
		{
			//如果墙面板图片隐藏状态，显示
			show_wall_panel_image();
		}

		return true;
	}
	catch (...)
	{

	}

	return false;
}


bool Cflashktv10Wnd::zoom_image(TCHAR *des_path,int des_width,int des_height,TCHAR *src_path,TCHAR *format,int cut_width,int cut_height)
{
	try
	{
		RectF des_rect;
		Image *src_image;
		int width=0;
		int height=0;
		Status return_status;
		CLSID              encoderClsid;  
		EncoderParameters  encoderParameters;
		bool result=false;
		//创建bitmap位图
		Bitmap save_bitmap(des_width,des_height,PixelFormat24bppRGB);
		//根据bitmap构造graphics
		Graphics  draw_graphics(&save_bitmap);
		int qurity = 100;

		//设置图片编码参数
		encoderParameters.Count  =  1;  
		encoderParameters.Parameter[0].Guid  =  EncoderQuality;  
		encoderParameters.Parameter[0].Type  =  EncoderParameterValueTypeLong;  
		encoderParameters.Parameter[0].NumberOfValues  =  1;  
		encoderParameters.Parameter[0].Value  =  &qurity; 

		//得到位图的clsid
		result = GetEncoderClsid(format,&encoderClsid);  
		if (!result)
		{
			return false;
		}

		//加载图片
		src_image = Image::FromFile(src_path);
		if (Ok!=src_image->GetLastStatus())
		{
			return false;
		}
		//目标区域
		des_rect.X = 0.0f;
		des_rect.Y = 0.0f;
		des_rect.Width = des_width*1.0f;
		des_rect.Height = des_height*1.0f;
		width = src_image->GetWidth()*1.0f-cut_width;
		height = src_image->GetHeight()*1.0f-cut_height;
		//缩放绘制到目标bitmap上
		draw_graphics.DrawImage(src_image,des_rect, cut_width/2,cut_height/2,width,height,UnitPixel);

		//释放内存
		delete src_image;
		src_image = NULL;
		//删除原有文件
		DeleteFile(des_path);
		//保存图片
		return_status = save_bitmap.Save(des_path, &encoderClsid, &encoderParameters);
		if (Ok!=return_status)
		{
			return false;
		}

		return true;
	}
	catch (...)
	{

	}

	return false;
}

UINT Cflashktv10Wnd::query_data_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd *pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);
		//pThis->flash_message_call_change_show_page();
		Sleep(100);
	}
	catch (...)
	{

	}
	return 0;
}



void Cflashktv10Wnd::get_wechat_song_encode_number(char * wechat_data)
{
	try
	{
		string_conversion string_con;
		config_file_manager config_file;
		TCHAR log_txt[256];
		//TCHAR wechat_path[256];
		bool result = false;

		memset(m_wechat_song_encode,0x0,sizeof(m_wechat_song_encode));
		//memset(wechat_path,0x0,sizeof(wechat_path));
		memset(log_txt,0x0,sizeof(log_txt));
		memset(m_wechat_song_path,0x0,sizeof(m_wechat_song_path));

		//数字显示到屏幕区域
		if (wechat_data==NULL)
		{
			return;
		}

		string_con.multibyte_to_widechar(wechat_data,m_wechat_song_encode,sizeof(m_wechat_song_encode));

		config_file.write_string(L"ipad",L"wechat_song",m_wechat_song_encode);

		swprintf(m_wechat_song_path,L"%s\\qr_picture\\wechat_song.png",m_work_path);

		//生成二维码
		result = Generate_encode_picture(wechat_data,m_wechat_song_path);
		if (result)
		{
			zoom_image(m_wechat_song_path,160,160,m_wechat_song_path,L"image/png",20,20);
		}

		return;
	}
	catch (...)
	{

	} 
	return;
}


UINT Cflashktv10Wnd::send_data_to_box_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);
		pThis->send_db_to_box();
	}
	catch (...)
	{

	}
	return 0;
}

void Cflashktv10Wnd::send_db_to_box()
{
	try
	{
		TCHAR source_db[256];
		TCHAR des_db[256];
		TCHAR log_txt[256];
		char  des_path[256];
		char  md5_value[256];
		char  send_buff[1024*16];
		DB_Query db_query;

		int nSendTimeout = 6000; 

		FILE *fp_read_file=NULL;                      //保存文件指针
		long file_size = 0;
		long read_size = 0;
		string_conversion string_con;


		memset(source_db,0x0,sizeof(source_db));
		memset(des_db,0x0,sizeof(des_db));
		memset(log_txt,0x0,sizeof(log_txt));
		memset(des_path,0x0,sizeof(des_path));
		memset(md5_value,0x0,sizeof(md5_value));

		//拷贝一份数据库
		swprintf(source_db,L"%s\\ktv10.db",m_work_path);
		swprintf(des_db,L"%s\\ktvtemp10.db",m_work_path);

		//拷贝数据临时库
		if (0 == ::CopyFile(source_db,des_db,FALSE))
		{
			WriteLog(__FL__, L"拷贝歌曲ktv10.db失败!");
			return;
		}

		string_con.widechar_to_multibyte(des_db,des_path,sizeof(des_path));

	//	if (db_query.open_DB(des_db,false))
		{
			//清空不需要的表数据
			/*		db_query.exec_sql(L"delete from game");
			db_query.exec_sql(L"delete from member");
			db_query.exec_sql(L"delete from member_song");
			db_query.exec_sql(L"delete from sing_song");
			db_query.exec_sql(L"delete from singer_backup");
			db_query.exec_sql(L"delete from song_backup");
			db_query.exec_sql(L"delete from song_recorder");
			db_query.exec_sql(L"VACUUM");
			db_query.close_DB();*/
		} 

		file_size = get_filesize(des_path);
		//得到文件的MD5值
		get_file_md5(des_path,md5_value);

		//打开并创建文件
		fp_read_file = fopen(des_path,"rb");
		if (fp_read_file==NULL)
		{
			memset(log_txt,0x0,sizeof(log_txt)); 
			swprintf(log_txt,L"%s，文件打开失败!");
			WriteLog(__FL__, log_txt);
		} 
		
		//定位到文件头 
		fseek(fp_read_file,0L,SEEK_SET);

		////发送数据给盒子
		//SOCKET send_socket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
		//if (send_socket<0)
		//{
		//	//创建socket失败
		//	if (fp_read_file)
		//	{
		//		fclose(fp_read_file);
		//		fp_read_file=NULL;
		//	}

		//	//删除临时的歌库
		//	::DeleteFile(des_db);

		//	return;
		//}

		////设置socket属性
		//zerolinger.l_onoff = 1;
		//zerolinger.l_linger = 5;
		//setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));

		//setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&nSendTimeout,sizeof(nSendTimeout));

		//// 也可以在这里调用bind函数绑定一个本地地址
		//// 否则系统将会自动安排

		//// 填写远程地址信息
		//sockaddr_in service_addr;
		//service_addr.sin_family = AF_INET;
		//service_addr.sin_addr.S_un.S_addr = inet_addr("10.0.3.83");
		//service_addr.sin_port = htons(9999);

		//if(::connect(send_socket, (sockaddr*)&service_addr, sizeof(service_addr)) == -1)
		//{
		//	WriteLog(__FL__, L"连接失败");
		//	//发送当前的状态
		//	int error = WSAGetLastError();
		//	closesocket(send_socket);

		//	if (fp_read_file)
		//	{
		//		fclose(fp_read_file);
		//		fp_read_file=NULL;
		//	}
		//	//删除临时的歌库
		//	::DeleteFile(des_db);
		//	return;
		//} 
		
		//filename=文件名称&size=大小&md5=md5值&file=内容
		memset(send_buff,0x0,sizeof(send_buff)); 
		sprintf(send_buff,"filename=ktvtemp10.db&size=%d&md5=%s&file=",file_size,md5_value);
		size_t len = strlen(send_buff)*sizeof(char);
		len = ::sendto(m_load_song_db_socket,send_buff,len,0,(sockaddr *)&m_load_song_db_addr,sizeof(m_load_song_db_addr));

		if(len>0)
		{
			//发送成功
		}

		while(file_size>read_size)
		{
			memset(send_buff,0x0,sizeof(send_buff));
			
			if (file_size-read_size>1024*16)
			{
				//读出2048个字节
				len = fread(send_buff,1,1024*16,fp_read_file);
			}
			else
			{
				len =  fread(send_buff,1,file_size-read_size,fp_read_file);
			}
			 
			//size_t len = strlen(send_buff)*sizeof(char);
			//发送数据
			len = ::sendto(m_load_song_db_socket,send_buff,len,0,(sockaddr *)&m_load_song_db_addr,sizeof(m_load_song_db_addr));
			if(len>0)
			{
				//发送成功
			}
			else
			{
				break;
			}

			read_size+=len;
		}


		if (fp_read_file)
		{
			fclose(fp_read_file);
			fp_read_file=NULL;
		}

		//关闭socket
		::closesocket(m_load_song_db_socket);
		m_load_song_db_socket = -1;

		//删除临时的歌库
		::DeleteFile(des_db);

		return;
	}
	catch (...)
	{
		
	} 
	return;
}

void Cflashktv10Wnd::thread_send_to_box_tcp_function(const TCHAR* request_data,int nPort)
{
	try
	{
		REQUEST_BOX_DATA *request_bax_data = new REQUEST_BOX_DATA;
		_tcscpy(request_bax_data->request_data,request_data);
		request_bax_data->nPort = nPort;
		request_bax_data->pThis = this;
		AfxBeginThread(send_order_data_thread,request_bax_data);
	}
	catch (...)
	{
		
	}
	
	return;
}

UINT Cflashktv10Wnd::send_order_data_thread(LPVOID pParam)
{
	try
	{
		REQUEST_BOX_DATA *rquest_data = (REQUEST_BOX_DATA*)pParam;

		rquest_data->pThis->send_order_data_function_data(rquest_data->request_data,rquest_data->nPort);

		delete rquest_data;
		rquest_data = NULL;
	}
	catch (...)
	{
		
	}
	 
	return 0;
}

void Cflashktv10Wnd::send_order_data_function_data(TCHAR *request_data,int nPort)
{
	try
	{
		std::wstring wechat_service_ip;
		config_file_manager config_file;
		string_conversion string_con;
		int recv_len = 0;
		int total_len = 0;
		char server_box_ip[256];
		char send_data[256];
		char recv_data[1024*50];
		std::string recv_data_list;
		memset(send_data,0x0,sizeof(send_data));
		memset(server_box_ip,0x0,sizeof(server_box_ip));

		//读出盒子ip
		wechat_service_ip = config_file.read_string(L"ipad",L"wechat_service_ip",L"");

		if (wechat_service_ip.empty())
		{
			WriteLog(__FL__, L"微信点歌的盒子ip为空！！");
			return;
		}

		string_con.widechar_to_multibyte(wechat_service_ip.c_str(),server_box_ip,sizeof(server_box_ip));

		struct linger zerolinger;
		int nSendTimeout = 10000;
		bool result=false;

		SOCKET send_socket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 

		if (send_socket<0)
		{
			//创建socket失败
			return;
		}

		//设置socket属性
		zerolinger.l_onoff = 1;
		zerolinger.l_linger = 5;
		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));

		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&nSendTimeout,sizeof(nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in service_addr;
		service_addr.sin_family = AF_INET;
		service_addr.sin_addr.S_un.S_addr = inet_addr(server_box_ip);
		service_addr.sin_port = htons(nPort);

		if(::connect(send_socket, (sockaddr*)&service_addr, sizeof(service_addr)) == -1)
		{
			closesocket(send_socket);
			return;
		}

		//打印日志
		WriteLog(__FL__, L"给双双盒子发送指令数据如下:");
		WriteLog(__FL__, request_data);

		string_con.widechar_to_multibyte(request_data,send_data,sizeof(send_data));

		size_t len = strlen(send_data)*sizeof(char);

		len =  ::send(send_socket, send_data, len, 0);

		if(len>0)
		{
			//发送成功
		} 

		if (0==_strnicmp(send_data,"SDEND_ORDER",11))  //如果是指令就接受数据
		{
			memset(recv_data,0x0,sizeof(recv_data));
			//WriteLog(__FL__, request_data);
			recv_len = ::recv(send_socket,recv_data,sizeof(recv_data),0);	

			recv_data_list+=recv_data;
			nSendTimeout = 1000;
			::setsockopt(send_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&nSendTimeout,sizeof(nSendTimeout)); 
			while(true)
			{
				SLEEP_FOR;

				memset(recv_data,0x0,sizeof(recv_data));
				total_len += recv_len;
				recv_len = ::recv(send_socket,recv_data,sizeof(recv_data),0);		

				recv_data_list += recv_data;

				if (recv_len <= 0)
				{
					break;
				}
			}

			if (total_len>0)                     //(2)接受到数据
			{
				WriteLog(__FL__, L"=========接受到双双发过来的数据并进入消息函数DM_RECV_SERVER_MSG==========");
				SendMessage(DM_RECV_SERVER_MSG,(WPARAM)recv_data_list.c_str(),NULL);
				//进行解析
				//if (0 == _strnicmp(recv_data,"MAIBASONGINFO",13))
				//{
					//解析得到歌曲(是网络数据)
					//parse_maiba_song_info(recv_data+14);
				//}

			} 
		}
		else
		{

		}
		
		//关闭socket
		::closesocket(send_socket);
		send_socket = -1;
	}
	catch (...)
	{

	}


	return;
}

UINT Cflashktv10Wnd::send_data_to_box_tcp_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);
		pThis->send_data_to_box_tcp();
	}
	catch (...)
	{
		
	} 

	return 0;
}


UINT Cflashktv10Wnd::recv_date_from_box_tcp_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);
		pThis->recv_data_from_box_tcp();
	}
	catch (...)
	{

	} 

	return 0;
}

void Cflashktv10Wnd::recv_data_from_box_tcp()
{
	try
	{
		int result = 0;
		fd_set socket_set;

		//清0
		FD_ZERO(&socket_set);

		timeval overtime;
		overtime.tv_sec = 0;
		overtime.tv_usec = 1000;

		//加入监听组
		FD_SET(m_box_send_socket,&socket_set);

		while(m_thread_run)
		{
			SLEEP_FOR; //增加sleep

			//将fdSocket集合的一个拷贝fdRead传递给select函数，
			// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回
			fd_set fdRead_set = socket_set;
			result = ::select(0,&fdRead_set,NULL,NULL,&overtime);
			if (result<=0)
			{
				continue;
			}

			//recv data
			char recv_data[1024*52];
			int recv_len=0;

			memset(recv_data,0x0,sizeof(recv_data));

			recv_len = ::recv(m_box_send_socket,recv_data,sizeof(recv_data),0);

			if (recv_len>0)                     //(2)接受到数据
			{
				//解析数据
				/*while(1)
				{
					::recv(m_box_send_socket,recv_data,sizeof(recv_data),0);
				}*/
				SendMessage(DM_RECV_SERVER_MSG,(WPARAM)recv_data,NULL);
			}
			else		// （3）连接关闭、重启或者中断
			{
				::closesocket(m_box_send_socket);
				FD_CLR(m_box_send_socket, &socket_set);
			}
		}	
	
	}
	catch (...)
	{	
	}
	
	return;
}

void Cflashktv10Wnd::send_data_to_box_tcp()
{ 
	try
	{
		
		std::wstring wechat_service_ip;
		config_file_manager config_file;
		string_conversion string_con;
		 
		char server_box_ip[256];
		char send_data[256];

		memset(send_data,0x0,sizeof(send_data));
		memset(server_box_ip,0x0,sizeof(server_box_ip)); 
		
		//读出盒子ip
		wechat_service_ip = config_file.read_string(L"ipad",L"wechat_service_ip",L"");

		if (wechat_service_ip.empty())
		{
			WriteLog(__FL__, L"微信点歌的盒子ip为空！！");
			return;
		}

		string_con.widechar_to_multibyte(wechat_service_ip.c_str(),server_box_ip,sizeof(server_box_ip));

		struct linger zerolinger;
		int nSendTimeout = 6000;
		bool result=false;

		m_box_send_socket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 

		if (m_box_send_socket<0)
		{
			//创建socket失败
			return;
		}

		//设置socket属性
		zerolinger.l_onoff = 1;
		zerolinger.l_linger = 5;
		setsockopt(m_box_send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));

		setsockopt(m_box_send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&nSendTimeout,sizeof(nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in service_addr;
		service_addr.sin_family = AF_INET;
		service_addr.sin_addr.S_un.S_addr = inet_addr(server_box_ip);
		service_addr.sin_port = htons(18007);

		if(::connect(m_box_send_socket, (sockaddr*)&service_addr, sizeof(service_addr)) == -1)
		{
			closesocket(m_box_send_socket);
			return;
		}

		AfxBeginThread(recv_date_from_box_tcp_thread,this);
	
		while (m_thread_run)
		{
			try
			{
				SLEEP_FOR; //增加sleep

				if (WAIT_OBJECT_0  ==  WaitForSingleObject(m_box_thread_event_handle,1000))
				{
					string_con.widechar_to_multibyte(m_request_data,send_data,sizeof(send_data));

					size_t len = strlen(send_data)*sizeof(char);

					len = ::sendto(m_box_send_socket,send_data,len,0,(sockaddr *)&service_addr,sizeof(service_addr));
					if(len>0)
					{
						//发送成功
						ResetEvent(m_box_thread_event_handle);
					}

				}
				
			}
			catch (...)
			{

			}
		}
		
		//关闭socket
		::closesocket(m_box_send_socket);
		m_box_send_socket = -1;
	}
	catch (...)
	{

	}
	 

	return;
}

int Cflashktv10Wnd::get_file_md5(char *name,char *md5_buff)
{
	static FILE *fp;
	static unsigned flen[2],len,i;
	if (!(fp=fopen(name,"rb"))) {
		return -1;;
	} 
	fseek(fp, 0, SEEK_END); 
	if((len=ftell(fp))==-1) {
		fclose(fp);
		return -1;
	}  
	rewind(fp);  
	A=0x67452301,B=0xefcdab89,C=0x98badcfe,D=0x10325476;
	flen[1]=len/0x20000000;    
	flen[0]=(len%0x20000000)*8;
	memset(x,0,64); 
	fread(x,4,16,fp); 
	for(i=0;i<len/64;i++){    
		md5();
		memset(x,0,64);
		fread(x,4,16,fp);
	}
	((char*)x)[len%64]=(char)128;  
	if(len%64>55)
	md5(),
	memset(x,0,64);
	memcpy(x+14,flen,8);   
	md5();
	fclose(fp);
	sprintf(md5_buff,"%08x%08x%08x%08x",PP(A),PP(B),PP(C),PP(D));
	return 0;
}


bool Cflashktv10Wnd::parse_arena_rule_info(char* recv_data,int rule_falgs,int nFalgs)
{
	try
	{
		TCHAR data[1024*100];
		TCHAR request[1024*100];
		string_conversion string_con;
		std::wstring item_value;  
		CMarkup parse_xml_doc;
		int nPos = 0;
		 
		memset(request,0x0,sizeof(request));

		if ((0 == strcmp(recv_data,"")) && 0 == nFalgs)
		{
			return false;
		}

		//CMarkup parse_xml_doc;
		bool result=false;
		memset(data,0x0,sizeof(data));

		if (0 == nFalgs)
		{
			string_con.utf8_to_widechar(recv_data,data,sizeof(data));
			for (int i = 0; i < MAIBA_RULE_COUNT; i++)
			{
//				memset(&m_maiba_rule_arena_info[i],0x0,sizeof(MAIBA_RULE_INFO)); 
			}
		}

		//解析xml文档
		result =parse_xml_doc.SetDoc(data);
		if (!result)
		{
			return false;
		}
		parse_xml_doc.ResetPos();   //list
		result = parse_xml_doc.FindChildElem(); 
		if (!result)
		{
			return false;
		}

		MAIBA_RULE_INFO maiba_rule_info;

		 while(true)
		 {
			memset(&maiba_rule_info,0x0,sizeof(maiba_rule_info));

			parse_xml_doc.IntoElem();  
			result = parse_xml_doc.FindChildElem(); //<data>

			if (!result)
			{
				break;
			}
	
			parse_xml_doc.IntoElem();  //activity_id
			item_value = parse_xml_doc.GetData(); 
			_tcscpy(maiba_rule_info.activity_id,item_value.c_str());

			parse_xml_doc.FindElem();  //song_id
			item_value = parse_xml_doc.GetData(); 
			_tcscpy(maiba_rule_info.song_id,item_value.c_str());

			parse_xml_doc.FindElem();  //activity_type
			item_value = parse_xml_doc.GetData(); 
			_tcscpy(maiba_rule_info.activity_type,item_value.c_str());
		
			parse_xml_doc.FindElem(); //start_time
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.start_time,item_value.c_str());
			
			parse_xml_doc.FindElem();  //end_time
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.end_time,item_value.c_str());
		
			parse_xml_doc.FindElem();   //participation_type1
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.participation_type1,item_value.c_str());
			
			parse_xml_doc.FindElem();   //participation_song
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.participation_song,item_value.c_str());

			if (_tcscmp(maiba_rule_info.activity_type, L"4") == 0)	//挑战大咖
			{
				int nSongCount = 0;	//歌曲个数
				CHALLENGE_STAR_IFNO info;
				//parse_xml_doc.IntoElem();
				result = parse_xml_doc.FindChildElem();
				parse_xml_doc.IntoElem();
				while (result)
				{
					memset(&info, 0x00, sizeof(CHALLENGE_STAR_IFNO));

					item_value = parse_xml_doc.GetAttrib((CString)"SongId");
					_tcscpy(info.original_song_id, item_value.c_str());

					item_value = parse_xml_doc.GetAttrib((CString)"SongName");
					_tcscpy(info.song_name, item_value.c_str());

					item_value = parse_xml_doc.GetAttrib((CString)"Singer");
					_tcscpy(info.singer_name, item_value.c_str());

					item_value = parse_xml_doc.GetAttrib((CString)"Score");
					_tcscpy(info.goal_score, item_value.c_str());

					m_vec_challenge_star_info.push_back(info);

					nSongCount++ ;	//
					result = parse_xml_doc.FindElem();
				}
				
				m_nChallengeSongCount = nSongCount;

				parse_xml_doc.OutOfElem();
			}
			else if (_tcscmp(maiba_rule_info.activity_type, L"5") == 0)//百秒夺奖
			{
				int nPassCount = 0;	//关卡个数
				CPassManager pPass;
				m_vec_pass_tmp.clear();
				
				result = parse_xml_doc.FindChildElem();
				parse_xml_doc.IntoElem();

				while (result)
				{
					pPass.InitVariable();
					int nSongCount = 0;//歌曲个数
					HUNDRED_SECONDS_PRIZE_SONG info;
					bool bRet = parse_xml_doc.FindChildElem();
					parse_xml_doc.IntoElem();

					while(bRet)
					{
						memset(&info, 0x00, sizeof(HUNDRED_SECONDS_PRIZE_SONG));

						item_value = parse_xml_doc.GetAttrib((CString)"SongId");
						_tcscpy(info.song_id, item_value.c_str());

						item_value = parse_xml_doc.GetAttrib((CString)"SongName");
						_tcscpy(info.song_name, item_value.c_str());

						item_value = parse_xml_doc.GetAttrib((CString)"Singer");
						_tcscpy(info.singer_name, item_value.c_str());

						nSongCount++;

						pPass.m_vec_song.push_back(info);

						bRet = parse_xml_doc.FindElem();
					}
					parse_xml_doc.OutOfElem();

					pPass.SetSongCount(nSongCount);

					item_value = parse_xml_doc.GetAttrib((CString)"Value");//关卡索引1到n
					pPass.SetIndex(_wtoi(item_value.c_str()) - 1);//0到(n-1)

					item_value = parse_xml_doc.GetAttrib((CString)"RewardInfo");//奖励
					pPass.SetPrize(item_value.c_str());

					item_value = parse_xml_doc.GetAttrib((CString)"goal_score");//每句目标分数
					pPass.SetGoalScore(_wtoi(item_value.c_str()));

					item_value = parse_xml_doc.GetAttrib((CString)"continue_count");//连续达到指定分数次数，可扔锤子
					pPass.SetContinueCount(_wtoi(item_value.c_str()));
					
					item_value = parse_xml_doc.GetAttrib((CString)"ice_init_count");//冰块初始数量
					pPass.SetIceInitCount(_wtoi(item_value.c_str()));

					item_value = parse_xml_doc.GetAttrib((CString)"ice_add_second");//冰块增长的时间间隔，单位秒
					pPass.SetIceAddSecond(_wtoi(item_value.c_str()));

					pPass.SetState(UN_ACROSS);

					nPassCount++ ;	//

					m_vec_pass_tmp.push_back(pPass);

					result = parse_xml_doc.FindElem();
				}
				parse_xml_doc.OutOfElem();
			}
			else if (_tcscmp(maiba_rule_info.activity_type, L"6") == 0)//听音识曲
			{
				int nPassCount = 0;	//关卡个数
				m_listen_reward_vec.clear();

				result = parse_xml_doc.FindChildElem();
				parse_xml_doc.IntoElem();

				while (result)
				{
					item_value = parse_xml_doc.GetAttrib((CString)"RewardInfo");//奖励
					m_listen_reward_vec.push_back(item_value);

					nPassCount++ ;	//

					result = parse_xml_doc.FindElem();
				}
				if (nPassCount > 0)
				{
					m_nListenPassCount = nPassCount;
				}
				parse_xml_doc.OutOfElem();
			}

			parse_xml_doc.FindElem();    //participation_type2
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.participation_type2,item_value.c_str());
		
			parse_xml_doc.FindElem();     //rating_methods
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.rating_methods,item_value.c_str());
		
			parse_xml_doc.FindElem();   //activities_award1
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.activities_award1,item_value.c_str());
			
			parse_xml_doc.FindElem();   //activities_award2
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.activities_award2,item_value.c_str());
			
			parse_xml_doc.FindElem();   //activities_award3
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.activities_award3,item_value.c_str());

			parse_xml_doc.FindElem();   //activities_award4
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.activities_award4,item_value.c_str());

			parse_xml_doc.FindElem();   //activities_award5
			item_value = parse_xml_doc.GetData();
			_tcscpy(maiba_rule_info.activities_award5,item_value.c_str());
			
			//返回<item>
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem();

			result = parse_xml_doc.FindChildElem();

			if (0 == _tcscmp(maiba_rule_info.activity_type,L"1"))
			{
				//自由pk
				m_set_free_pk=true;         //是否启用了自由pK
				memcpy(&m_maiba_rule_arena_info[0],&maiba_rule_info,sizeof(maiba_rule_info));
			}
			else if (0 == _tcscmp(maiba_rule_info.activity_type,L"2"))
			{
				//麦霸pk
				m_set_dekaron_pk=true;           //是否启用了挑战麦霸
				memcpy(&m_maiba_rule_arena_info[1],&maiba_rule_info,sizeof(maiba_rule_info));
			}
			else if (0 == _tcscmp(maiba_rule_info.activity_type,L"3"))
			{
				//上榜有礼
				m_set_ranking_plite=true;           //是否启用了上榜有礼
				memcpy(&m_maiba_rule_arena_info[2],&maiba_rule_info,sizeof(maiba_rule_info));
			}
			else if (0 == _tcscmp(maiba_rule_info.activity_type,L"4"))
			{
				//挑战大咖
				m_set_challenge_star=true;           //是否启用了挑战大咖
				memcpy(&m_maiba_rule_arena_info[3],&maiba_rule_info,sizeof(maiba_rule_info));
			}
			else if (0 == _tcscmp(maiba_rule_info.activity_type,L"5"))
			{
				//百秒夺奖
				m_set_across_pass = true;
				memcpy(&m_maiba_rule_arena_info[4],&maiba_rule_info,sizeof(maiba_rule_info));
			}
			else if (0 == _tcscmp(maiba_rule_info.activity_type,L"6"))
			{
				//听音识曲
				//m_set_across_pass = true;
				memcpy(&m_maiba_rule_arena_info[5],&maiba_rule_info,sizeof(maiba_rule_info));
			}
			nPos++;
			if (nPos>=MAIBA_RULE_COUNT || !result)
			{
				break;
			}
		 } 

		 if ((m_set_free_pk || m_set_dekaron_pk) && m_vice_screen_flash_show)
		 {
			 if (m_vice_screen_flash_player.GetSafeHwnd() != NULL && m_slave_video_window.GetSafeHwnd() != NULL)
			 {
				m_vice_screen_flash_player.BringWindowToTop();
				//m_vice_screen_flash_player.Play();
				m_vice_screen_flash_player.ShowWindow(SW_SHOW);

				m_slave_video_window.MoveWindow(CRect(m_vice_screen_left_top_x,m_vice_screen_left_top_y,m_vice_screen_right_button_x,m_vice_screen_right_button_y));
				m_slave_video_window.BringWindowToTop();
				m_slave_video_window.ShowWindow(SW_SHOW);

				m_vice_screen_flash_show = FALSE;
			 }
		 }
		
		 /*活动发布注释掉了yzg
		int page_code = m_flash_manage.get_last_page_index();
		 //如果返回到活动页面，则在次发一次码
		 if (page_code == page_singing_contest)
		 {
			 TCHAR log[256] = {0x00};
			 swprintf(log, L"m_set_free_pk=%d,m_set_dekaron_pk=%d,m_set_ranking_plite=%d", m_set_free_pk, m_set_dekaron_pk, m_set_ranking_plite);
			 if(m_set_free_pk)
			 {
				 WriteLog(__FL__, L"parse_arena_rule_info_ex1");
				 parse_arena_rule_info_ex("1", 1);
			 }
			 if(m_set_dekaron_pk)
			 {
				 WriteLog(__FL__, L"parse_arena_rule_info_ex2");
				 parse_arena_rule_info_ex("1", 2);
			 }
			 if(m_set_ranking_plite)
			 {
				 WriteLog(__FL__, L"parse_arena_rule_info_ex3");
				 parse_arena_rule_info_ex("1", 3);
			 }
		 }*/
		
		return true;
	}
	catch (...)
	{
		WriteLog(__FL__, L"catch parse_arena_rule_info");
	}

	return false;
}

bool Cflashktv10Wnd::parse_arena_rule_info_ex(char* recv_data,int rule_falgs)
{
	WriteLog(__FL__, L"enter parse_arena_rule_info_ex");
	try
	{
		TCHAR data[1024*100];
		TCHAR request[1024*100];
		string_conversion string_con;
		std::wstring item_value;  
		CMarkup parse_xml_doc;
		int nPos = 0;
		 
		memset(request,0x0,sizeof(request));

		if (0 == strcmp(recv_data,""))
		{
			return false;
		}

		//CMarkup parse_xml_doc;
		bool result=false;
		memset(data,0x0,sizeof(data));

		//如果没有请求到规则
		if (0 == _tcscmp(m_maiba_rule_arena_info[rule_falgs-1].activity_id,L""))
		{
			swprintf(data,L"<data></data>");
		}
		else
		{
			swprintf(data,L"<data><activity_type>%s</activity_type><start_time>%s</start_time><end_time>%s</end_time><participation_type1>%s</participation_type1>\
							<participation_song>%s</participation_song><participation_type2>%s</participation_type2><rating_methods>%s</rating_methods><activities_award1>%s</activities_award1>\
							<activities_award2>%s</activities_award2><activities_award3>%s</activities_award3><activities_award4>%s</activities_award4><activities_award5>%s</activities_award5></data>",
							m_maiba_rule_arena_info[rule_falgs-1].activity_type,m_maiba_rule_arena_info[rule_falgs-1].start_time,m_maiba_rule_arena_info[rule_falgs-1].end_time,
							m_maiba_rule_arena_info[rule_falgs-1].participation_type1,m_maiba_rule_arena_info[rule_falgs-1].participation_song,m_maiba_rule_arena_info[rule_falgs-1].participation_type2,
							m_maiba_rule_arena_info[rule_falgs-1].rating_methods,m_maiba_rule_arena_info[rule_falgs-1].activities_award1,m_maiba_rule_arena_info[rule_falgs-1].activities_award2,
							m_maiba_rule_arena_info[rule_falgs-1].activities_award3,m_maiba_rule_arena_info[rule_falgs-1].activities_award4,m_maiba_rule_arena_info[rule_falgs-1].activities_award5);

		}

		//直接组织歌曲字符串 
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"maiba_rule",data);
		if (!result)
		{
			return false;
		}

		flash_player_call_function(request);

		WriteLog(__FL__, L"leave parse_arena_rule_info_ex");
		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool Cflashktv10Wnd::organise_arena_rule_info(TCHAR *command,int rule_falgs)
{
	try
	{
		TCHAR data[1024*10];
		TCHAR request[1024*10];
		string_conversion string_con;
		std::wstring item_value;  
		CMarkup parse_xml_doc;
		int nPos = 0;

		memset(request,0x0,sizeof(request));

		if (0 == wcscmp(command, L""))
		{
			return false;
		}

		bool result=false;
		memset(data,0x0,sizeof(data));

		//如果没有请求到规则
		if (0 == _tcscmp(m_maiba_rule_arena_info[rule_falgs-1].activity_id,L""))
		{
			if (rule_falgs == 1)
				swprintf(data,L"<data><info defaultURL=\"%s\\%s\"></info></data>", m_work_path, L"inter_screen\\activity_pic\\自由pk.png");
			else if (rule_falgs == 2)
				swprintf(data,L"<data><info defaultURL=\"%s\\%s\"></info></data>", m_work_path, L"inter_screen\\activity_pic\\擂台pk.png");
		}
		else
		{
			swprintf(data,L"<data><info defaultURL=\"\"><activity_type>%s</activity_type><start_time>%s</start_time><end_time>%s</end_time><participation_type1>%s</participation_type1>\
						   <participation_song>%s</participation_song><participation_type2>%s</participation_type2><rating_methods>%s</rating_methods><activities_award1>%s</activities_award1>\
						   <activities_award2>%s</activities_award2><activities_award3>%s</activities_award3><activities_award4>%s</activities_award4><activities_award5>%s</activities_award5></info></data>",
						   m_maiba_rule_arena_info[rule_falgs-1].activity_type,m_maiba_rule_arena_info[rule_falgs-1].start_time,m_maiba_rule_arena_info[rule_falgs-1].end_time,
						   m_maiba_rule_arena_info[rule_falgs-1].participation_type1,m_maiba_rule_arena_info[rule_falgs-1].participation_song,m_maiba_rule_arena_info[rule_falgs-1].participation_type2,
						   m_maiba_rule_arena_info[rule_falgs-1].rating_methods,m_maiba_rule_arena_info[rule_falgs-1].activities_award1,m_maiba_rule_arena_info[rule_falgs-1].activities_award2,
						   m_maiba_rule_arena_info[rule_falgs-1].activities_award3,m_maiba_rule_arena_info[rule_falgs-1].activities_award4,m_maiba_rule_arena_info[rule_falgs-1].activities_award5);
		}

		//直接组织歌曲字符串 
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR), command, data);
		if (!result)
		{
			return false;
		}
		if (m_inter_screen_window.m_hWnd != NULL)
		{
			if (m_inter_screen_flash_player.m_hWnd != NULL)
			{
				m_inter_screen_flash_player.CallFunction(request);
			}
		}


		return true;
	}
	catch (...)
	{

	}

	return false;
}
bool Cflashktv10Wnd::parse_server_arena_song(char* recv_data, int flag)
{
	try
	{
		TCHAR maiba_data[1024*100];
		TCHAR maiba_count_data[256];
		string_conversion string_con;
		int maiba_count = 0;
		int nSize = 0;
		CMarkup parse_xml_doc;
		bool result = false;
		int nCount = 0;
		std::wstring item_value;
		TCHAR msg_item[256]; //得到当前发过来的类型 
		const TCHAR *parse_msg=NULL;
		const TCHAR *temp=NULL; 

		if (0 == strcmp(recv_data,""))
		{
			return false;
		}
		memset(maiba_data,0x0,sizeof(maiba_data));
		memset(maiba_count_data,0x0,sizeof(maiba_count_data)); 
 
		//初始化
		for(int i=0;i<MAIBA_HEIGHT_RANKING_LIST;i++)
		{  
			memset(&m_maiba_song_list[i],0x0,sizeof(MAIBA_HEIGHT_RANKING));
		}
		

		string_con.utf8_to_widechar(recv_data,maiba_data,sizeof(maiba_data));

		WriteLog(__FL__, L"接受到的麦霸规则服务器发过来的数据列表");

		parse_msg = maiba_data;
		//REQUESTMAIBADATA$COUNT=100$FREEPK(AREAPK)$ 
		memset(msg_item,0x0,sizeof(msg_item));
		temp = _tcschr(parse_msg,'$');
		if (temp && (temp-parse_msg)*sizeof(TCHAR) < 50)
		{

		}
		else 
		{
			WriteLog(__FL__, L"数据错误!");
			WriteLog(__FL__, parse_msg);
			return false;
		}
		memset(msg_item,0x0,sizeof(msg_item));
		memcpy(msg_item,parse_msg,(temp-parse_msg)*sizeof(TCHAR));
		swscanf(msg_item,L"COUNT=%d",&m_maiba_song_list_count);
		if (m_maiba_song_list_count%48)
		{
			m_maiba_total_page_number = m_maiba_song_list_count/48 + 1;
		}
		else
		{
			m_maiba_total_page_number = m_maiba_song_list_count/48;
		}

		WriteLog(__FL__, msg_item);

		parse_msg = temp+1;
		temp = _tcschr(parse_msg,'$');
		if (temp && (temp-parse_msg)*sizeof(TCHAR) < 50)
		{
		}
		else 
		{
			WriteLog(__FL__, L"数据错误!");
			WriteLog(__FL__, parse_msg);
			return false;
		}
		parse_msg = temp+1;
		/*
		if (!judge_parse_request_web_data(msg_item))
		{
		m_web_total_page_nmuber = 0;
		m_web_song_total_count = 0;
		flash_message_call_maiba_pk_data(FIRST_PAGE_OPERATE);
		return false;
		}

		*/

		/* 
		<item>
		<voice_id>111444<voice_id>
		<song_id>10000112</song_id>
		<song_name>你是我的眼<song_name>
		<singer_name>林宥嘉<singer_name>
		<song_score>98<song_score>  
		<member_pic>C:\\a.jpg<member_pic>
		<wave_path >\\10.0.3.45\\ <wave_path >
		<video_path >\\10.0.3.45\\ <video_path>
		<nick_name>adfadfa</nick_name>
		<voice_code>fdafdaf</voice_code>
		</item>
		*/
		//解析数据 
		result =parse_xml_doc.SetDoc(parse_msg);
		if (!result)
		{
			return false;
		}
		parse_xml_doc.ResetPos();   //list
		result = parse_xml_doc.FindChildElem(); 
		if (!result)
		{
			return false;
		}

		while(true)
		{
			parse_xml_doc.IntoElem();  
			result = parse_xml_doc.FindChildElem(); //<item>

			if (!result)
			{
				break;
			}
			parse_xml_doc.IntoElem();  //voice_id
			item_value = parse_xml_doc.GetData(); 
			_tcscpy(m_maiba_song_list[nCount].voice_id,item_value.c_str());

			parse_xml_doc.FindElem(); //song_id
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].song_id,item_value.c_str());

			parse_xml_doc.FindElem();  //singer_name
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].song_name,item_value.c_str());

			parse_xml_doc.FindElem();   //singer_name
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].singer_name,item_value.c_str());

			parse_xml_doc.FindElem();   //score
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].score,item_value.c_str());

			parse_xml_doc.FindElem();    //member_pic
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].member_pic,item_value.c_str());

			parse_xml_doc.FindElem();     //wave_path
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].wave_path,item_value.c_str());

			parse_xml_doc.FindElem();   //video_path
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].video_path,item_value.c_str());

			parse_xml_doc.FindElem();   //nick_name
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].nick_name,item_value.c_str());

			
			parse_xml_doc.FindElem();   //voice_code
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].voice_code,item_value.c_str()); 

			parse_xml_doc.FindElem();   //room_name
			item_value = parse_xml_doc.GetData();
			_tcscpy(m_maiba_song_list[nCount].room_name,item_value.c_str()); 

			//返回<item>
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem();
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem();  
			parse_xml_doc.OutOfElem(); 
			parse_xml_doc.OutOfElem();  
			parse_xml_doc.OutOfElem(); 

			result = parse_xml_doc.FindChildElem();
			nCount++;
			if (nCount>=48 || !result)
			{
				break;
			}
		}

		//发送给flash
		show_recorder_arena_song(FIRST_PAGE_OPERATE,0,flag);
		return true;
	}
	catch (...)
	{
		
	} 

	return false;
}


UINT Cflashktv10Wnd::send_server_msg_tcp_thread(LPVOID pParam)
{
	try
	{
		REQUEST_BOX_DATA *rquest_data = (REQUEST_BOX_DATA*)pParam;
		//Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);
		rquest_data->pThis->send_server_msg_tcp(rquest_data->request_data);

		delete rquest_data;
		rquest_data = NULL;
	}
	catch (...)
	{

	}

	return 0;
}


UINT Cflashktv10Wnd::send_server_msg_tcp(TCHAR* msg)
{
	try
	{
		char send_buff[1024*100];
		string_conversion string_con;
		char service_server_ip[256];
		std::wstring server_ip;
		config_file_manager config_file;

		//得到规则服务器ip
		server_ip = config_file.read_string(L"server",L"set_maiba_rule_ip",L"");
		if (!server_ip.empty())
		{
			memset(service_server_ip,0x0,sizeof(service_server_ip));
			string_con.widechar_to_multibyte(server_ip.c_str(),service_server_ip,sizeof(service_server_ip));
		}

		if (0==strcmp(service_server_ip,""))
		{
			return 0;
		}
		// 创建套节字
		SOCKET send_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(send_socket == INVALID_SOCKET)
		{
			return 0;
		}
		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;

		setsockopt(send_socket,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		int m_nSendTimeout = 16000;
		//set send timeout
		setsockopt(send_socket,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_nSendTimeout,sizeof(m_nSendTimeout));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		// 填写远程地址信息
		sockaddr_in servAddr; 
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(6666);
		// 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址
		// 如果你的计算机没有联网，直接使用127.0.0.1即可
		servAddr.sin_addr.S_un.S_addr = inet_addr(service_server_ip);

		if(::connect(send_socket, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		{
			closesocket(send_socket);
			return 0;
		}
		WriteLog(__FL__, L"=============规则服务器请求数据==================");
		WriteLog(__FL__, msg);
		memset(send_buff,0x0,sizeof(send_buff));
		string_con.widechar_to_multibyte(msg,send_buff,sizeof(send_buff));

		int send_len = (int)strlen(send_buff);
		int nRecv = ::send(send_socket, send_buff, send_len, 0);

		if(nRecv > 0)
		{
			//发送数据成功
			WriteLog(__FL__, L"发送给规则服务器请求麦霸录音歌曲的数据成功");
		}

		//接受数据
		//memset(send_buff,0x0,sizeof(send_buff));
		//m_maiba_song_list_count = MAIBA_HEIGHT_RANKING_LIST;

		int maibaType = -1;
		if (0 == _strnicmp(send_buff,"RequestMaibaFree",16) || 0 == _strnicmp(send_buff,"RequestMaibaArea",16) 
			|| 0 == _strnicmp(send_buff,"GetSongID",9) || 0 == _strnicmp(send_buff, "RequestMaibaSrea", 16))
		{
			if (0 == _strnicmp(send_buff,"RequestMaibaFree",16))
			{
				maibaType = 0;
			}else if (0 == _strnicmp(send_buff,"RequestMaibaArea",16))
			{
				maibaType = 1;
			}
			
			memset(send_buff,0x0,sizeof(send_buff));
			
			nRecv = ::recv(send_socket,(char*)send_buff,sizeof(send_buff),0);

			if (nRecv <= 0)
			{
				WriteLog(__FL__, L"========没有收到规则服务器的数据！==============");			 
			}
			else
			{
				if (0 == _strnicmp(send_buff,"GetSongID",9))
				{
					TCHAR szSongIDs[102400] = {0x00};
					string_con.multibyte_to_widechar(send_buff, szSongIDs, sizeof(szSongIDs));
					//song_query_show_data_by_id(&szSongIDs[10]);
					song_recorder_query_show_data_by_id(&szSongIDs[10]);
					WriteLog(__FL__, &szSongIDs[10]);
				}else{
					//处理数据 
					parse_server_arena_song(send_buff+17, maibaType);
				}
			}		
		}
		
		/*for (int i=0;i<MAIBA_HEIGHT_RANKING_LIST;i++)
		{
			if (0 == _tcscmp(m_maiba_song_list[i].song_id,L""))
			{
				m_maiba_song_list_count = i;
				break;
			}
		}*/

		// 关闭套节字
		::closesocket(send_socket);
		
		//show_recorder_arena_song(FIRST_PAGE_OPERATE,0);

	}
	catch (...)
	{

	}
	return 0;
}

bool Cflashktv10Wnd::repeat_select_song(TCHAR* song_number,int page_index)
{
	try
	{
		wstring songValue;
		int value_index = -1;

		songValue.assign(song_number);
		map<wstring,int>::iterator songIter;	 //Map迭代器 

		songIter=m_select_page_Map.find(songValue);

		if(songIter == m_select_page_Map.end())
		{
			//没有找到,进行添加
			m_select_page_Map.insert(pair<wstring,int>(songValue,page_index));
			return false;
		}
		else
		{
			//找到
			value_index = songIter->second;
			if (value_index == page_index)
			{
				return true;
			}
			else
			{
				//进行赋值
				songIter->second = page_index;
				return false;
			}
			//_tcscpy(lyric,lyricIter->second.c_str());
		}
		
	}
	catch (...)
	{
		
	}

	return false;
}

void Cflashktv10Wnd::delete_repeat_select_song(song_info &select_song_info)
{
	try
	{
		bool result = true;
		int play_number = 0;
		TCHAR song_number[256];
		wstring songValue; 

		memset(song_number,0x0,sizeof(song_number));
		
		select_song_info.get_song_id(song_number);

		songValue.assign(song_number);

		result = m_video_play_manager.query_select_song_by_id(song_number,play_number);
		if (result)
		{
			return;
		}
		
		map<wstring,int>::iterator songIter;	 //Map迭代器 

		songIter=m_select_page_Map.find(songValue);

		if(songIter != m_select_page_Map.end())
		{
			//找到,进行添加,删除map中的数据
			m_select_page_Map.erase(songValue); 
		}
	}
	catch (...)
	{
		
	}
	
	return;
}

void Cflashktv10Wnd::change_repeat_select_song(int page_indxe)
{
	try
	{
		map<wstring,int>::iterator songIter;	 //Map迭代器

		for ( songIter = m_select_page_Map.begin(); songIter != m_select_page_Map.end(); songIter++)
		{
			songIter->second = page_indxe;
		}
	}
	catch (...)
	{
		
	}

	return;
}

bool Cflashktv10Wnd::save_record_info_to_db(TCHAR *record_info)
{
	try
	{
		if (NULL==record_info)
		{
			return false;
		}

		CMarkup parse_xml_doc;
		MCD_STR number;
		MCD_STR song;
		MCD_STR singer;
		MCD_STR path;
		MCD_STR datetime;
		MCD_STR URL;
		MCD_STR video_path;
		MCD_STR culture_code;
		MCD_STR start_time;
		MCD_STR score;
		bool result=false;
		TCHAR sql[1024];

		//解析xml
		result = parse_xml_doc.SetDoc(record_info);
		if (!result)
		{
			return false;
		}
		parse_xml_doc.ResetMainPos();
		while(1)
		{
			//查找歌曲
			result = parse_xml_doc.FindChildElem(L"song");
			if (!result)
			{
				break;
			}
			parse_xml_doc.IntoElem();
			//得到歌曲ID
			number = parse_xml_doc.GetAttrib(L"id");
			if (number.IsEmpty())
			{
				continue;
			}

			//<song id=\"%s\" name=\"%s\" singer=\"%s\" video_path = \"%s\" culture_code=\"%s\" path=\"%s\" start_time=\"%s\" datetime=\"%s\" score=\"%s\" url=\"%s\" />

			//得到歌曲名字
			song = parse_xml_doc.GetAttrib(L"name");
			//演唱者
			singer = parse_xml_doc.GetAttrib(L"singer");
			//原始视频路径
			video_path = parse_xml_doc.GetAttrib(L"video_path");
			//文化码
			culture_code = parse_xml_doc.GetAttrib(L"culture_code");
			//得到音频路径
			path = parse_xml_doc.GetAttrib(L"path");
			//开始录音时间
			start_time = parse_xml_doc.GetAttrib(L"start_time");
			//得到录音时间
			datetime = parse_xml_doc.GetAttrib(L"datetime");
			//得到分数
			score = parse_xml_doc.GetAttrib(L"score");
			//得到分享url
			URL = parse_xml_doc.GetAttrib(L"url");
			//检查是否存在
			memset(sql, 0x0, sizeof(sql));
			swprintf_s(sql, sizeof(sql)/sizeof(TCHAR),L"select count(song_id) from song_recorder \
													   where song_id=\"%s\"",
													   number.GetBuffer(0));
			string_conversion str_conn;
			char szBuf[1024*10] = {0x00};
			str_conn.widechar_to_multibyte(sql, szBuf, sizeof(szBuf));
			int rowcnt = m_db_query.get_row_count(szBuf);
			if (rowcnt <= 0)
			{
				//录入数据库
				memset(sql, 0x0, sizeof(sql));
				swprintf_s(sql, sizeof(sql)/sizeof(TCHAR),L"insert or replace into song_recorder(song_id,song_name,singer_name,wave_path,datetime,video_path,culture_code,start_time,score) values \
																				(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",
							number.GetBuffer(0), song.GetBuffer(0), singer.GetBuffer(0), L"", 
							datetime.GetBuffer(0), video_path.GetBuffer(0), culture_code.GetBuffer(0), 
							start_time.GetBuffer(0), score.GetBuffer(0));
				m_db_query.exec_sql(sql);
			}
			//保存分享的URL
			m_http_service.set_web_url(number.GetBuffer(0), URL.GetBuffer(0));
			if (rowcnt>0 && m_str_slave_recorder_song_id.length()>0 && m_str_slave_recorder_song_id.compare(number) == 0)
			{
				//add yzg 2015年7月1日
				if(URL.GetLength()>0)
				{
					//分享URL显示到界面
					send_share_url_image_to_flash(URL.GetBuffer(0));
					//发送给规则服务器
					share_song_to_rale_server(number.GetBuffer(0),URL.GetBuffer(0));
				}
				break;
			}
			//离开该子节点
			parse_xml_doc.OutOfElem();
		}

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

void Cflashktv10Wnd::flash_message_calll_memeber_info()
{
	try
	{
		TCHAR request[1024];
		TCHAR data[1024];
		TCHAR download_address[256];
		bool result=false;
		MEMBER_FLAG member_flag = MEMBER_FLAG_LOGIN_NO;  //是否登录
		TCHAR is_login[10];
		TCHAR member_list[2048]; //发给被控的列表
		TCHAR user_name[20];	 //用户名称
		TCHAR nick_name[256];    //会员昵称
		TCHAR user_sex[10];      //用户性别
		TCHAR user_head[256];    //用户头像
		TCHAR send_data[1024];    //发送数据
		TCHAR head_download[256];  //下载头像地址

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		memset(download_address,0x0,sizeof(download_address));
		memset(member_list,0x0,sizeof(member_list));
		memset(is_login,0x0,sizeof(is_login));
		memset(nick_name,0x0,sizeof(nick_name));
		memset(user_name,0x0,sizeof(user_name));
		memset(user_sex,0x0,sizeof(user_sex));
		memset(user_head,0x0,sizeof(user_head));
		memset(send_data,0x0,sizeof(send_data));
		memset(head_download,0x0,sizeof(head_download));


		swprintf(download_address,L"%s%s",m_work_path,L"\\qr_picture\\down_load_encode.png");

		//得到是否登录
		member_flag = m_memeber_manage[m_activate_vip_button].get_login_flags();
		if (MEMBER_FLAG_LOGIN_NO == member_flag)
		{
			_tcscpy(is_login,L"false"); 
			//m_activate_vip_button = m_pre_activate_vip_button;
			//swprintf(data,L"<data><is_login>true</is_login><item index=\"%d\" name=\"135987895\" nick=\"你妹\" sex=\"女\" head=\"C:\\a.jpg\" picture=\"%s\"></item></data>",m_activate_vip_button,download_address);
			swprintf(data,L"<data><is_login>%s</is_login><item index=\"-1\" name=\"\" nick=\"\" sex=\"\" head=\"\" picture=\"\"></item></data>",
				is_login);

			member_register_dialog_page_jump(L"register_jump",L"登录(或注册)失败!",false);
		} 
		else if (MEMBER_FLAG_PHONE_CODE_ERROR == member_flag)
		{
			_tcscpy(is_login,L"false"); 
			//m_activate_vip_button = m_pre_activate_vip_button;
			//swprintf(data,L"<data><is_login>true</is_login><item index=\"%d\" name=\"135987895\" nick=\"你妹\" sex=\"女\" head=\"C:\\a.jpg\" picture=\"%s\"></item></data>",m_activate_vip_button,download_address);
			swprintf(data,L"<data><is_login>%s</is_login><item index=\"-1\" name=\"\" nick=\"\" sex=\"\" head=\"\" picture=\"\"></item></data>",
				is_login);

			member_register_dialog_page_jump(L"register_jump",L"手机验证码错误",false);
		}
		else if (MEMBER_FLAG_PHONE_REGISTER == member_flag)
		{
			_tcscpy(is_login,L"false"); 
			//m_activate_vip_button = m_pre_activate_vip_button;
			//swprintf(data,L"<data><is_login>true</is_login><item index=\"%d\" name=\"135987895\" nick=\"你妹\" sex=\"女\" head=\"C:\\a.jpg\" picture=\"%s\"></item></data>",m_activate_vip_button,download_address);
			swprintf(data,L"<data><is_login>%s</is_login><item index=\"-1\" name=\"\" nick=\"\" sex=\"\" head=\"\" picture=\"\"></item></data>",
				is_login);

			member_register_dialog_page_jump(L"register_jump",L"手机号已注册",false);
		}
		else if (MEMBER_FLAG_ERROR == member_flag)
		{
			_tcscpy(is_login,L"false"); 
			//m_activate_vip_button = m_pre_activate_vip_button;
			//swprintf(data,L"<data><is_login>true</is_login><item index=\"%d\" name=\"135987895\" nick=\"你妹\" sex=\"女\" head=\"C:\\a.jpg\" picture=\"%s\"></item></data>",m_activate_vip_button,download_address);
			swprintf(data,L"<data><is_login>%s</is_login><item index=\"-1\" name=\"\" nick=\"\" sex=\"\" head=\"\" picture=\"\"></item></data>",
				is_login);

			member_register_dialog_page_jump(L"register_jump",L"网络连接不正确，稍后再试!",false);
		}
		else
		{
			_tcscpy(is_login,L"true");
			m_memeber_manage[m_activate_vip_button].get_member_down_address(head_download);
			//请求图片数据
			swprintf(send_data,L"Message&DOWN_FILE_FROM_BOX;GET_FACE_DOWN:filelen=%d&strean=%s",_tcslen(head_download),head_download);
			//下载数据服务端
			send_data_to_service_udp(send_data);

			m_memeber_manage[m_activate_vip_button].get_nick_name(nick_name);
			m_memeber_manage[m_activate_vip_button].get_user_name(user_name);
			m_memeber_manage[m_activate_vip_button].get_user_sex(user_sex);
			m_memeber_manage[m_activate_vip_button].get_user_head(user_head);
			m_memeber_manage[m_activate_vip_button].get_member_down_address(head_download);

			//swprintf(data,L"<data><is_login>true</is_login><item index=\"%d\" name=\"135987895\" nick=\"你妹\" sex=\"女\" head=\"C:\\a.jpg\" picture=\"%s\"></item></data>",m_activate_vip_button,download_address);
			swprintf(data,L"<data><is_login>%s</is_login><item index=\"%d\" name=\"%s\" nick=\"%s\" sex=\"%s\" head=\"%s\" picture=\"%s\"></item></data>",
				is_login,m_activate_vip_button,user_name,nick_name,user_sex,user_head,download_address);

			m_pre_activate_vip_button = m_activate_vip_button;

			member_register_dialog_page_jump(L"register_jump",L"",true);

			set_flash_button_state(L"vip_activate_button",m_activate_vip_button);
		}
		
		int page_index = m_flash_manage.get_last_page_index();
		if (0 == _tcscmp(is_login,L"true"))
		{
			//登录成功
			if(page_index == page_member_song)
			{
				//请求会员歌曲私房歌曲
				flash_message_call_maiba(PRIVATE_SONG,L"0:1");
			}
			else if (page_index == page_find_maiba)
			{
				//请求我的收藏
				flash_message_call_maiba(MAIBA_FIND,L"4:1");

				m_request_song_type = MYCOLLECTION;
			}
			else if (page_index == page_recording)
			{
				//请求我的分享
				flash_message_call_maiba(MAIBA_SHARE,L"1:1");
				m_request_song_type = MYRECORDSHARE;
			}

		
			//else if(m_request_song_type == MYCOLLECTION)
			//{
			//	//请求我的收藏
			//	flash_message_call_maiba(MAIBA_FIND,L"4:1");
			//	//m_request_song_type = MYSTOREINFO;
			//}
			//else if (m_request_song_type == MYRECORDSHARE)
			//{
			//	//请求我的分享
			//	flash_message_call_maiba(MAIBA_SHARE,L"1:1");
			//}
			 
		}
		
		//is_login为 true是登录成功
		//m_memeber_manage[m_activate_vip_button].set_login_flags(MEMBER_FLAG_LOGIN);
		
		
		//发送给被控机
		send_master_slave_data_vip_info();
		
		//会员歌曲登录信息
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"login_memeber_info",data);
		if (result)
		{
			flash_player_call_function(request);
		}

	}
	catch (...)
	{
		
	}

	return;
}


void Cflashktv10Wnd::flash_message_call_show_member_vip()
{
	try
	{
		TCHAR request[1024];
		TCHAR user_name[20];	 //用户名称
		TCHAR nick_name[256];    //会员昵称
		TCHAR user_sex[10];      //用户性别
		TCHAR user_head[256];    //用户头像
		TCHAR is_login[10];
		TCHAR data[1024];
		bool result = false;

		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));
		memset(is_login,0x0,sizeof(is_login));
		memset(nick_name,0x0,sizeof(nick_name));
		memset(user_name,0x0,sizeof(user_name));
		memset(user_sex,0x0,sizeof(user_sex));
		memset(user_head,0x0,sizeof(user_head));
		
		for (int i=0; i< MEMBER_LOGIN_COUNT;i++)
		{

		}
		swprintf(data,L"<data><is_login>%s</is_login><item index=\"%d\" name=\"%s\" nick=\"%s\" sex=\"%s\" head=\"%s\" ></item></data>",
			is_login,m_activate_vip_button,user_name,nick_name,user_sex,user_head);

		//会员歌曲登录信息
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"login_memeber_info",data);
		if (result)
		{
			flash_player_call_function(request);
		}


	}
	catch (...)
	{

	}

	return;
}

void Cflashktv10Wnd::parse_master_slave_data_vip_info(TCHAR* recv_data)
{
	try
	{
		//解析得到当前的会员信息并赋值
		CMarkup parse_xml_doc;
		bool result = false;
		std::wstring item_value;
		int nPos = 0;

		result =parse_xml_doc.SetDoc(recv_data);
		if (!result)
		{
			return;
		}
		parse_xml_doc.ResetPos();   //pk_list
		result = parse_xml_doc.FindChildElem(); 
		if (!result)
		{
			return;
		}

		while (true)
		{
			//<item index=\"%d\" is_login=\"%d\" name=\"%s\" password=\"%s\" nick=\"%s\" sex=\"%s\" head=\"%s\" picture=\"%s\" identitycard=\"%s\" />

			result = parse_xml_doc.IntoElem(); //data    
			if (!result)
			{
				break;
			}
			item_value = parse_xml_doc.GetAttrib(L"index");

			item_value = parse_xml_doc.GetAttrib(L"is_login"); 
			m_memeber_manage[nPos].set_login_flags((MEMBER_FLAG)_wtoi(item_value.c_str()));

			item_value = parse_xml_doc.GetAttrib(L"name"); 
			m_memeber_manage[nPos].set_user_name(item_value.c_str());

			item_value = parse_xml_doc.GetAttrib(L"password"); 
			m_memeber_manage[nPos].set_user_password(item_value.c_str());

			item_value = parse_xml_doc.GetAttrib(L"nick");
			m_memeber_manage[nPos].set_nick_name(item_value.c_str());

			item_value = parse_xml_doc.GetAttrib(L"sex");
			m_memeber_manage[nPos].set_user_sex(item_value.c_str());

			item_value = parse_xml_doc.GetAttrib(L"head");
			m_memeber_manage[nPos].set_user_head(item_value.c_str());

			item_value = parse_xml_doc.GetAttrib(L"picture");
			m_memeber_manage[nPos].set_user_head(item_value.c_str());

			item_value = parse_xml_doc.GetAttrib(L"identitycard");
			m_memeber_manage[nPos].set_user_identitycard(item_value.c_str());

			parse_xml_doc.OutOfElem();  
			result = parse_xml_doc.FindChildElem();

			nPos++;
			if (!result || nPos >= MEMBER_LOGIN_COUNT)
			{
				break;
			}	
		}
	}
	catch (...)
	{
		
	}

	return;
}


void Cflashktv10Wnd::send_master_slave_data_vip_info()
{
	try
	{
		std::wstring vip_member_list;
		TCHAR member_info[1024];
		TCHAR member_data[1024*5];
		string_conversion string_con;
		TCHAR vip_name[256];
		TCHAR vip_pwd[256];
		TCHAR vip_nick[256];
		TCHAR vip_sex[256];
		TCHAR vip_head[256];
		TCHAR vip_picture[256];
		TCHAR vip_user_identitycard[256];
		
		memset(member_data,0x0,sizeof(member_data));

		vip_member_list += L"MEMBER_LIST<list>";

		for (int i=0; i< MEMBER_LOGIN_COUNT;i++)
		{
			memset(member_info,0x0,sizeof(member_info));
			memset(vip_name,0x0,sizeof(vip_name));
			memset(vip_pwd,0x0,sizeof(vip_pwd));
			memset(vip_nick,0x0,sizeof(vip_nick));
			memset(vip_sex,0x0,sizeof(vip_sex));
			memset(vip_head,0x0,sizeof(vip_head));
			memset(vip_picture,0x0,sizeof(vip_picture));
			memset(vip_user_identitycard,0x0,sizeof(vip_user_identitycard));
			swprintf(member_info,L"<item index=\"%d\" is_login=\"%d\" name=\"%s\" password=\"%s\" nick=\"%s\" sex=\"%s\" head=\"%s\" picture=\"%s\" identitycard=\"%s\" />",
				i,m_memeber_manage[i].get_login_flags(),vip_name,vip_pwd,vip_nick,vip_sex,vip_head,vip_picture,vip_user_identitycard);
			vip_member_list += member_info;
		}

		vip_member_list += L"</list>";

		_tcscpy(member_data,vip_member_list.c_str());

		//发送给被监控
		send_master_slave_data(member_data,NULL);
	}
	catch (...)
	{
		
	}
	
	return;
}

bool Cflashktv10Wnd::flash_message_call_read_drinks_data()
{
	try
	{
		config_file_manager config_flie;
		string_conversion string_con;
		std::wstring drink_server_path;
		TCHAR des_path[256];
		char des_xml_path[256];
		char read_buff[1024*100];
		
		//\\10.0.3.187\testGongxiang\allWine.xml
		memset(des_path,0x0,sizeof(des_path));
		memset(read_buff,0x0,sizeof(read_buff));
		memset(des_xml_path,0x0,sizeof(des_xml_path));

		drink_server_path = config_flie.read_string(L"drinks",L"server_ip",L"");
		
		if (drink_server_path.empty())
		{
			WriteLog(__FL__, L"酒水服务器路径为空，请配置路径");
			return false;
		}

		swprintf(des_path,L"%s\\allWine.xml",drink_server_path.c_str());


		/*
		string_con.widechar_to_multibyte(des_path,des_xml_path,sizeof(des_xml_path));

		//判断路径是否存在
		if (!PathFileExists(des_path))
		{
			WriteLog(__FL__, L"酒水路径不存在");
			return false;
		}

		FILE* fp_read_file = NULL;
		//打开并创建文件
		fp_read_file = fopen(des_xml_path,"r");
		if (fp_read_file==NULL)
		{		 
			WriteLog(__FL__, L"打开文件失败!");
			return false;
		} 

		fseek(fp_read_file,0L,SEEK_END);
		int file_size = ftell(fp_read_file);

		fseek(fp_read_file,0L,SEEK_SET);
		fread(read_buff,1,file_size,fp_read_file);

		//发送给flash
		*/
		
		flash_message_call_drinks_data(read_buff,des_path);

		//fclose(fp_read_file);

	}
	catch (...)
	{
		
	}
	
	return false;
}

bool Cflashktv10Wnd::flash_message_call_drinks_data(char* read_buff,TCHAR* drink_path)
{
	try
	{
		TCHAR request[1024*100];
		TCHAR data[1024*100];
		string_conversion string_con;
		bool result = false;
		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

	/*	string_con.utf8_to_widechar(read_buff,data,sizeof(data));
		
		if (!data)
		{
			return false;
		}*/
		//result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"drinks_info",data);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"drinks_info",drink_path);
		//WriteLog(__FL__, request);

		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch (...)
	{
		
	}

	return false;
}

bool Cflashktv10Wnd::clear_all_member_show_info()
{
	try
	{
		memset(m_memeber_phone_number,0x0,sizeof(m_memeber_phone_number));		//会员的手机号
		memset(m_member_password,0x0,sizeof(m_member_password));				//会员的密码
		memset(m_member_ok_password,0x0,sizeof(m_member_ok_password));			//会员的确认密码
		memset(m_member_name,0x0,sizeof(m_member_name));						//会员的名字
		memset(m_phone_check_code,0x0,sizeof(m_phone_check_code));				//手机验证码

	}
	catch (...)
	{
		
	}
	
	return false;
}

bool Cflashktv10Wnd::compose_score_image(int nScore, int nSimilarity, int nStability, int nIntact, TCHAR *pImgPath)
{
	try
	{
		bool bRet = false;
		int nHun = 1;	//百位数
		int nDec = 0;	//十位数
		int nUnit = 0;	//个位数
		Image *pImgHun, *pImgDec, *pImgUnit;
		TCHAR szImgPath[256] = {0x00};
		UINT nWidth = 0;
		UINT nHeight = 0;
		UINT nSrcX = 0;
		UINT nSrcY = 0;
		Rect rtDes;
		CLSID              encoderClsid;  
		EncoderParameters  encoderParameters;
		int nQurity = 100;
		RectF text_rect;
		StringFormat text_format;
		Font myFont(L"微软雅黑", 12, FontStyleBold);
		SolidBrush text_brush(Color(255, 255, 255, 255));
		TCHAR show_text[32];
		Status return_status = Ok;

		if (wcslen(pImgPath) == 0)	return false;
		if (nScore > 100)	nScore = 100;
		if (nSimilarity > 100)	nSimilarity = 100;
		if (nStability > 100)	nStability = 100;
		if (nIntact > 100)	nIntact = 100;

		//设置图片编码参数
		encoderParameters.Count  =  1;  
		encoderParameters.Parameter[0].Guid  =  EncoderQuality;  
		encoderParameters.Parameter[0].Type  =  EncoderParameterValueTypeLong;  
		encoderParameters.Parameter[0].NumberOfValues  =  1;  
		encoderParameters.Parameter[0].Value  =  &nQurity; 

		//得到位图的clsid
		bRet = GetEncoderClsid(L"image/png",&encoderClsid);  
		if (bRet)
		{
			nWidth = 210;
			nHeight = 210;
			//创建bitmap位图
			Bitmap save_bitmap(nWidth, nHeight, PixelFormat32bppARGB);
			//根据bitmap构造graphics
			Graphics  draw_graphics(&save_bitmap);

			//总分汉字目标区域
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\TotalScore.png", m_work_path);
			Image *pImgTotalScore = Image::FromFile(szImgPath);
			if (pImgTotalScore != NULL)
			{
				rtDes.X = 0.0f;
				rtDes.Y = 0.0f;
				rtDes.Width = 46*1.0f;
				rtDes.Height = 26*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgTotalScore, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgTotalScore;
					pImgTotalScore = NULL;
					return false;
				}
				//释放内存
				delete pImgTotalScore;
				pImgTotalScore = NULL;
			}

			//汉字“总分”
			text_rect.X = 4.0f;
			text_rect.Y = 4.0f;
			text_rect.Width = 40.0f;
			text_rect.Height = 20.0f;
			text_format.SetAlignment(StringAlignmentNear);
			text_format.SetLineAlignment(StringAlignmentCenter);
			memset(show_text, 0x00, sizeof(show_text));
			swprintf(show_text, L"总分");
			return_status = draw_graphics.DrawString(show_text, -1, &myFont, text_rect, &text_format, &text_brush);
			if (Ok != return_status)
			{
				return false;
			}
			//完整度，相似度，稳定度汉字目标区域
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\SoundEffect.png", m_work_path);
			Image *pImgSoundEffect = Image::FromFile(szImgPath);
			if (pImgSoundEffect != NULL)
			{
				rtDes.X = (nWidth-154)*1.0f;
				rtDes.Y = 0.0f;
				rtDes.Width = 154*1.0f;
				rtDes.Height = 26*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgSoundEffect, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgSoundEffect;
					pImgSoundEffect = NULL;
					return false;
				}
				//释放内存
				delete pImgSoundEffect;
				pImgSoundEffect = NULL;
			}
			//汉字“声准 音准 完整度”
			text_rect.X = (nWidth-154+4)*1.0f;
			text_rect.Y = 4.0f;
			text_rect.Width = 40.0f;
			text_rect.Height = 20.0f;
			text_format.SetAlignment(StringAlignmentNear);
			text_format.SetLineAlignment(StringAlignmentCenter);
			memset(show_text, 0x00, sizeof(show_text));
			swprintf(show_text, L"声准");
			return_status = draw_graphics.DrawString(show_text, -1, &myFont, text_rect, &text_format, &text_brush);
			if (Ok != return_status)
			{
				return false;
			}
			text_rect.X = (nWidth-100)*1.0f;
			text_rect.Y = 4.0f;
			text_rect.Width = 40.0f;
			text_rect.Height = 20.0f;
			text_format.SetAlignment(StringAlignmentNear);
			text_format.SetLineAlignment(StringAlignmentCenter);
			memset(show_text, 0x00, sizeof(show_text));
			swprintf(show_text, L"音准");
			return_status = draw_graphics.DrawString(show_text, -1, &myFont, text_rect, &text_format, &text_brush);
			if (Ok != return_status)
			{
				return false;
			}
			text_rect.X = (nWidth-60)*1.0f;
			text_rect.Y = 4.0f;
			text_rect.Width = 60.0f;
			text_rect.Height = 20.0f;
			text_format.SetAlignment(StringAlignmentNear);
			text_format.SetLineAlignment(StringAlignmentCenter);
			memset(show_text, 0x00, sizeof(show_text));
			swprintf(show_text, L"完整度");
			return_status = draw_graphics.DrawString(show_text, -1, &myFont, text_rect, &text_format, &text_brush);
			if (Ok != return_status)
			{
				return false;
			}
			//红色球
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\RedBall.png", m_work_path);
			Image *pImgRedBall = Image::FromFile(szImgPath);
			if (pImgRedBall != NULL)
			{
				rtDes.X = 0.0f;
				rtDes.Y = (nHeight-47)*1.0f;
				rtDes.Width = 49*1.0f;
				rtDes.Height = 46*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgRedBall, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgRedBall;
					pImgRedBall = NULL;
					return false;
				}
				//释放内存
				delete pImgRedBall;
				pImgRedBall = NULL;
			}
			//红色液体
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\RedLiquids.png", m_work_path);
			Image *pImgRedLiquids = Image::FromFile(szImgPath);
			if (pImgRedLiquids != NULL)
			{
				rtDes.X = 14.0f;
				rtDes.Y = (nHeight-46-120*nScore/100*1.0f)*1.0f;
				rtDes.Width = 22*1.0f;
				rtDes.Height = 120*nScore/100*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgRedLiquids, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgRedLiquids;
					pImgRedLiquids = NULL;
					return false;
				}
				//释放内存
				delete pImgRedLiquids;
				pImgRedLiquids = NULL;
			}
			//红色试管
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\Red.png", m_work_path);
			Image *pImgRed = Image::FromFile(szImgPath);
			if (pImgRed != NULL)
			{
				rtDes.X = 1.0f;
				rtDes.Y = (nHeight-178)*1.0f;
				rtDes.Width = 49*1.0f;
				rtDes.Height = 178*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgRed, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgRed;
					pImgRed = NULL;
					return false;
				}
				//释放内存
				delete pImgRed;
				pImgRed = NULL;
			}
			//总分数
			nHun = nScore/100;	//百位数
			if (nHun != 0)
			{
				memset(szImgPath, 0x00, sizeof(szImgPath));
				swprintf(szImgPath, L"%s\\score_image_new\\numbers\\1.png", m_work_path);
				pImgHun = Image::FromFile(szImgPath);
				if (pImgHun != NULL)
				{
					rtDes.X = 6.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgHun, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgHun;
						pImgHun = NULL;
						return false;
					}
					//释放内存
					delete pImgHun;
					pImgHun = NULL;
				}
				memset(szImgPath, 0x00, sizeof(szImgPath));
				swprintf(szImgPath, L"%s\\score_image_new\\numbers\\0.png", m_work_path);
				pImgDec = Image::FromFile(szImgPath);
				if (pImgDec != NULL)
				{
					rtDes.X = (6+12)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgDec, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgDec;
						pImgDec = NULL;
						return false;
					}
					//释放内存
					delete pImgDec;
					pImgDec = NULL;
				}
				pImgUnit = Image::FromFile(szImgPath);
				if (pImgUnit != NULL)
				{
					rtDes.X = (6+12+12)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
						return false;
					}
					//释放内存
					delete pImgUnit;
					pImgUnit = NULL;
				}
			}
			else
			{
				nDec = nScore/10;	//十位数
				if (nDec != 0)
				{
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nDec);
					pImgDec = Image::FromFile(szImgPath);
					if (pImgDec != NULL)
					{
						rtDes.X = 12.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgDec, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgDec;
							pImgDec = NULL;
							return false;
						}
						//释放内存
						delete pImgDec;
						pImgDec = NULL;
					}
					nUnit = nScore%10;	//个位数
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nUnit);
					pImgUnit = Image::FromFile(szImgPath);
					if (pImgUnit != NULL)
					{
						rtDes.X = (12+12)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgUnit;
							pImgUnit = NULL;
							return false;
						}
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
					}
				}
				else
				{
					nUnit = nScore%10;	//个位数
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nUnit);
					pImgUnit = Image::FromFile(szImgPath);
					if (pImgUnit != NULL)
					{
						rtDes.X = 18*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgUnit;
							pImgUnit = NULL;
							return false;
						}
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
					}
				}
			}
			//蓝色球
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\BlueBall.png", m_work_path);
			Image *pImgBlueBall = Image::FromFile(szImgPath);
			if (pImgBlueBall != NULL)
			{
				rtDes.X = (nWidth-154)*1.0f;
				rtDes.Y = (nHeight-42)*1.0f;
				rtDes.Width = 44*1.0f;
				rtDes.Height = 42*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgBlueBall, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgBlueBall;
					pImgBlueBall = NULL;
					return false;
				}
				//释放内存
				delete pImgBlueBall;
				pImgBlueBall = NULL;
			}
			//蓝色液体
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\BlueLiquids.png", m_work_path);
			Image *pImgBlueLiquids = Image::FromFile(szImgPath);
			if (pImgBlueLiquids != NULL)
			{
				rtDes.X = (nWidth-154+12)*1.0f;
				rtDes.Y = (nHeight-42-110*nSimilarity/100)*1.0f;
				rtDes.Width = 20*1.0f;
				rtDes.Height = 110*nSimilarity/100*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgBlueLiquids, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgBlueLiquids;
					pImgBlueLiquids = NULL;
					return false;
				}
				//释放内存
				delete pImgBlueLiquids;
				pImgBlueLiquids = NULL;
			}
			//蓝色试管
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\Blue.png", m_work_path);
			Image *pImgBlue = Image::FromFile(szImgPath);
			if (pImgBlue != NULL)
			{
				rtDes.X = (nWidth-154)*1.0f;
				rtDes.Y = (nHeight-163)*1.0f;
				rtDes.Width = 45*1.0f;
				rtDes.Height = 163*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgBlue, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgBlue;
					pImgBlue = NULL;
					return false;
				}
				//释放内存
				delete pImgBlue;
				pImgBlue = NULL;
			}
			//声准
			nHun = nSimilarity/100;	//百位数
			if (nHun != 0)
			{
				memset(szImgPath, 0x00, sizeof(szImgPath));
				swprintf(szImgPath, L"%s\\score_image_new\\numbers\\1.png", m_work_path);
				pImgHun = Image::FromFile(szImgPath);
				if (pImgHun != NULL)
				{
					rtDes.X = (nWidth-154+6)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgHun, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgHun;
						pImgHun = NULL;
						return false;
					}
					//释放内存
					delete pImgHun;
					pImgHun = NULL;
				}
				memset(szImgPath, 0x00, sizeof(szImgPath));
				swprintf(szImgPath, L"%s\\score_image_new\\numbers\\0.png", m_work_path);
				pImgDec = Image::FromFile(szImgPath);
				if (pImgDec != NULL)
				{
					rtDes.X = (nWidth-154+6+12)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgDec, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgDec;
						pImgDec = NULL;
						return false;
					}
					//释放内存
					delete pImgDec;
					pImgDec = NULL;
				}
				pImgUnit = Image::FromFile(szImgPath);
				if (pImgUnit != NULL)
				{
					rtDes.X = (nWidth-154+6+12+12)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
						return false;
					}
					//释放内存
					delete pImgUnit;
					pImgUnit = NULL;
				}
			}
			else
			{
				nDec = nSimilarity/10;	//十位数
				if (nDec != 0)
				{
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nDec);
					pImgDec = Image::FromFile(szImgPath);
					if (pImgDec != NULL)
					{
						rtDes.X = (nWidth-154+12)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgDec, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgDec;
							pImgDec = NULL;
							return false;
						}
						//释放内存
						delete pImgDec;
						pImgDec = NULL;
					}
					nUnit = nSimilarity%10;	//个位数
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nUnit);
					pImgUnit = Image::FromFile(szImgPath);
					if (pImgUnit != NULL)
					{
						rtDes.X = (nWidth-154+12+12)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgUnit;
							pImgUnit = NULL;
							return false;
						}
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
					}
				}
				else
				{
					nUnit = nSimilarity%10;	//个位数
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nUnit);
					pImgUnit = Image::FromFile(szImgPath);
					if (pImgUnit != NULL)
					{
						rtDes.X = (nWidth-154+18)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgUnit;
							pImgUnit = NULL;
							return false;
						}
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
					}
				}
			}
			//黄色球
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\YellowBall.png", m_work_path);
			Image *pImgYellowBall = Image::FromFile(szImgPath);
			if (pImgYellowBall != NULL)
			{
				rtDes.X = (nWidth-100)*1.0f;
				rtDes.Y = (nHeight-42)*1.0f;
				rtDes.Width = 44*1.0f;
				rtDes.Height = 42*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgYellowBall, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgYellowBall;
					pImgYellowBall = NULL;
					return false;
				}
				//释放内存
				delete pImgYellowBall;
				pImgYellowBall = NULL;
			}
			//黄色液体
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\YellowLiquids.png", m_work_path);
			Image *pImgYellowLiquids = Image::FromFile(szImgPath);
			if (pImgYellowLiquids != NULL)
			{
				rtDes.X = (nWidth-100+12)*1.0f;
				rtDes.Y = (nHeight-42-110*nStability/100)*1.0f;
				rtDes.Width = 20*1.0f;
				rtDes.Height = 110*nStability/100*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgYellowLiquids, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgYellowLiquids;
					pImgYellowLiquids = NULL;
					return false;
				}
				//释放内存
				delete pImgYellowLiquids;
				pImgYellowLiquids = NULL;
			}
			//黄色试管
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\Yellow.png", m_work_path);
			Image *pImgYellow = Image::FromFile(szImgPath);
			if (pImgYellow != NULL)
			{
				rtDes.X = (nWidth-100)*1.0f;
				rtDes.Y = (nHeight-163)*1.0f;
				rtDes.Width = 45*1.0f;
				rtDes.Height = 163*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgYellow, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgYellow;
					pImgYellow = NULL;
					return false;
				}
				//释放内存
				delete pImgYellow;
				pImgYellow = NULL;
			}
			//音准
			nHun = nStability/100;	//百位数
			if (nHun != 0)
			{
				memset(szImgPath, 0x00, sizeof(szImgPath));
				swprintf(szImgPath, L"%s\\score_image_new\\numbers\\1.png", m_work_path);
				pImgHun = Image::FromFile(szImgPath);
				if (pImgHun != NULL)
				{
					rtDes.X = (nWidth-100+6)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgHun, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgHun;
						pImgHun = NULL;
						return false;
					}
					//释放内存
					delete pImgHun;
					pImgHun = NULL;
				}
				memset(szImgPath, 0x00, sizeof(szImgPath));
				swprintf(szImgPath, L"%s\\score_image_new\\numbers\\0.png", m_work_path);
				pImgDec = Image::FromFile(szImgPath);
				if (pImgDec != NULL)
				{
					rtDes.X = (nWidth-100+6+12)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgDec, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgDec;
						pImgDec = NULL;
						return false;
					}
					//释放内存
					delete pImgDec;
					pImgDec = NULL;
				}
				pImgUnit = Image::FromFile(szImgPath);
				if (pImgUnit != NULL)
				{
					rtDes.X = (nWidth-100+6+12+12)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
						return false;
					}
					//释放内存
					delete pImgUnit;
					pImgUnit = NULL;
				}
			}
			else
			{
				nDec = nStability/10;	//十位数
				if (nDec != 0)
				{
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nDec);
					pImgDec = Image::FromFile(szImgPath);
					if (pImgDec != NULL)
					{
						rtDes.X = (nWidth-100+12)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgDec, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgDec;
							pImgDec = NULL;
							return false;
						}
						//释放内存
						delete pImgDec;
						pImgDec = NULL;
					}
					nUnit = nStability%10;	//个位数
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nUnit);
					pImgUnit = Image::FromFile(szImgPath);
					if (pImgUnit != NULL)
					{
						rtDes.X = (nWidth-100+12+12)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgUnit;
							pImgUnit = NULL;
							return false;
						}
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
					}
				}
				else
				{
					nUnit = nStability%10;	//个位数
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nUnit);
					pImgUnit = Image::FromFile(szImgPath);
					if (pImgUnit != NULL)
					{
						rtDes.X = (nWidth-100+18)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgUnit;
							pImgUnit = NULL;
							return false;
						}
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
					}
				}
			}
			//绿色球
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\GreenBall.png", m_work_path);
			Image *pImgGreenBall = Image::FromFile(szImgPath);
			if (pImgGreenBall != NULL)
			{
				rtDes.X = (nWidth-45)*1.0f;
				rtDes.Y = (nHeight-42)*1.0f;
				rtDes.Width = 44*1.0f;
				rtDes.Height = 42*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgGreenBall, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgGreenBall;
					pImgGreenBall = NULL;
					return false;
				}
				//释放内存
				delete pImgGreenBall;
				pImgGreenBall = NULL;
			}
			//绿色液体
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\GreenLiquids.png", m_work_path);
			Image *pImgGreenLiquids = Image::FromFile(szImgPath);
			if (pImgGreenLiquids != NULL)
			{
				rtDes.X = (nWidth-45+12)*1.0f;
				rtDes.Y = (nHeight-42-110*nIntact/100*1.0f)*1.0f;
				rtDes.Width = 20*1.0f;
				rtDes.Height = 110*nIntact/100*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgGreenLiquids, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgGreenLiquids;
					pImgGreenLiquids = NULL;
					return false;
				}
				//释放内存
				delete pImgGreenLiquids;
				pImgGreenLiquids = NULL;
			}
			//绿色试管
			memset(szImgPath, 0x00, sizeof(szImgPath));
			swprintf(szImgPath, L"%s\\score_image_new\\Green.png", m_work_path);
			Image *pImgGreen = Image::FromFile(szImgPath);
			if (pImgGreen != NULL)
			{
				rtDes.X = (nWidth-45)*1.0f;
				rtDes.Y = (nHeight-163)*1.0f;
				rtDes.Width = 45*1.0f;
				rtDes.Height = 163*1.0f;
				//缩放绘制到目标bitmap上
				return_status = draw_graphics.DrawImage(pImgGreen, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
				if (Ok != return_status)
				{
					//释放内存
					delete pImgGreen;
					pImgGreen = NULL;
					return false;
				}
				//释放内存
				delete pImgGreen;
				pImgGreen = NULL;
			}
			//完整度
			nHun = nIntact/100;	//百位数
			if (nHun != 0)
			{
				memset(szImgPath, 0x00, sizeof(szImgPath));
				swprintf(szImgPath, L"%s\\score_image_new\\numbers\\1.png", m_work_path);
				pImgHun = Image::FromFile(szImgPath);
				if (pImgHun != NULL)
				{
					rtDes.X = (nWidth-45+6)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgHun, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgHun;
						pImgHun = NULL;
						return false;
					}
					//释放内存
					delete pImgHun;
					pImgHun = NULL;
				}
				memset(szImgPath, 0x00, sizeof(szImgPath));
				swprintf(szImgPath, L"%s\\score_image_new\\numbers\\0.png", m_work_path);
				pImgDec = Image::FromFile(szImgPath);
				if (pImgDec != NULL)
				{
					rtDes.X = (nWidth-45+6+12)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgDec, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgDec;
						pImgDec = NULL;
						return false;
					}
					//释放内存
					delete pImgDec;
					pImgDec = NULL;
				}
				pImgUnit = Image::FromFile(szImgPath);
				if (pImgUnit != NULL)
				{
					rtDes.X = (nWidth-45+6+12+12)*1.0f;
					rtDes.Y = (nHeight-35)*1.0f;
					rtDes.Width = 12*1.0f;
					rtDes.Height = 20*1.0f;
					//缩放绘制到目标bitmap上
					return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
					if (Ok != return_status)
					{
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
						return false;
					}
					//释放内存
					delete pImgUnit;
					pImgUnit = NULL;
				}
			}
			else
			{
				nDec = nIntact/10;	//十位数
				if (nDec != 0)
				{
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nDec);
					pImgDec = Image::FromFile(szImgPath);
					if (pImgDec != NULL)
					{
						rtDes.X = (nWidth-45+12)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgDec, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgDec;
							pImgDec = NULL;
							return false;
						}
						//释放内存
						delete pImgDec;
						pImgDec = NULL;
					}
					nUnit = nIntact%10;	//个位数
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nUnit);
					pImgUnit = Image::FromFile(szImgPath);
					if (pImgUnit != NULL)
					{
						rtDes.X = (nWidth-45+12+12)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgUnit;
							pImgUnit = NULL;
							return false;
						}
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
					}
				}
				else
				{
					nUnit = nIntact%10;	//个位数
					memset(szImgPath, 0x00, sizeof(szImgPath));
					swprintf(szImgPath, L"%s\\score_image_new\\numbers\\%d.png", m_work_path, nUnit);
					pImgUnit = Image::FromFile(szImgPath);
					if (pImgUnit != NULL)
					{
						rtDes.X = (nWidth-45+18)*1.0f;
						rtDes.Y = (nHeight-35)*1.0f;
						rtDes.Width = 12*1.0f;
						rtDes.Height = 20*1.0f;
						//缩放绘制到目标bitmap上
						return_status = draw_graphics.DrawImage(pImgUnit, rtDes, nSrcX, nSrcY, rtDes.Width, rtDes.Height, UnitPixel);  
						if (Ok != return_status)
						{
							//释放内存
							delete pImgUnit;
							pImgUnit = NULL;
							return false;
						}
						//释放内存
						delete pImgUnit;
						pImgUnit = NULL;
					}
				}
			}
			//保存图片
			return_status = save_bitmap.Save(pImgPath,  &encoderClsid,  &encoderParameters);
			if (Ok != return_status)
			{
				return false;
			}
		}
		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::show_single_score(int nScore, int nSimilarity, int nStability, int nIntact)
{
	try
	{
		bool bRet = false;
		TCHAR szImgPath[256] = {0x00};

		swprintf(szImgPath, L"%s\\score_image_png.png", m_work_path);
		//合成图片
		bRet = compose_score_image(nScore, nSimilarity, nStability, nIntact, szImgPath);
		if (!bRet)
		{
			WriteLog(__FL__, L"生成单句评分图片失败！");
			return false;
		}

		//显示osd
		play_variable play_var;

		//初始化播放图片的变量
		play_var.nRepeat = 100;
		play_var.play_mode = OSD_STATIC;
		play_var.iHSpeed = 0;
		play_var.iVSpeed = 0;
		play_var.nDelayTime = 0;
		//显示到电视上
		bRet = m_player_manager.play_score_osd(szImgPath, play_var, OSDAlignmentRightTop);
		if (!bRet)
		{
			WriteLog(__FL__, L"显示评分图片osd失败！");
			return false;
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}

void Cflashktv10Wnd::show_sing_score(int score)
{
	try
	{
		TCHAR image_path[256];
		UINT width = 0;
		UINT height = 0;
		Rect des_rect;
		UINT src_x = 0;
		CLSID              encoderClsid;  
		EncoderParameters  encoderParameters;
		int qurity = 100;
		bool result = false;
		static int number = 1;

		if (!m_is_scoring || (m_lyric_total_sentences <= 0))
		{
			return;
		}

		memset(image_path, 0x0, sizeof(image_path));
		if (score ==100)
		{
			score = 99;
		}

		//显示分数
		if (m_number_image)
		{
			//设置图片编码参数
			encoderParameters.Count  =  1;  
			encoderParameters.Parameter[0].Guid  =  EncoderQuality;  
			encoderParameters.Parameter[0].Type  =  EncoderParameterValueTypeLong;  
			encoderParameters.Parameter[0].NumberOfValues  =  1;  
			encoderParameters.Parameter[0].Value  =  &qurity; 

			//得到位图的clsid
			result = GetEncoderClsid(L"image/png",&encoderClsid);  
			if (result)
			{
				width = m_number_image->GetWidth()/11;
				height = m_number_image->GetHeight();

				//创建bitmap位图
				Bitmap save_bitmap(3*width, height, PixelFormat32bppARGB);
				//根据bitmap构造graphics
				Graphics  draw_graphics(&save_bitmap);  
				//目标区域
				des_rect.X = 0.0f;
				des_rect.Y = 0.0f;
				des_rect.Width = width*1.0f;
				des_rect.Height = height*1.0f;
				src_x = (score/10)*width;
				//缩放绘制到目标bitmap上
				draw_graphics.DrawImage(m_number_image,des_rect,src_x,0,width,height ,UnitPixel);  
				des_rect.X = width*1.0f;
				des_rect.Y = 0.0f;
				des_rect.Width = width*1.0f;
				des_rect.Height = height*1.0f;
				src_x = (score%10)*width;
				//缩放绘制到目标bitmap上
				draw_graphics.DrawImage(m_number_image,des_rect,src_x,0,width,height ,UnitPixel);
				des_rect.X = width*2.0f;
				des_rect.Y = 0.0f;
				des_rect.Width = width*1.0f;
				des_rect.Height = height*1.0f;
				src_x = 10*width;
				//缩放绘制到目标bitmap上
				draw_graphics.DrawImage(m_number_image,des_rect,src_x,0,width,height ,UnitPixel);
				//保存图片
				swprintf(image_path, L"%s\\score.png", m_work_path);
				Status return_status = save_bitmap.Save(image_path,  &encoderClsid,  &encoderParameters);
				if (Ok == return_status)
				{
					play_variable play_var;

					//初始化播放图片的变量
					play_var.nRepeat = 10;
					play_var.play_mode = OSD_STATIC;
					play_var.iHSpeed = 0;
					play_var.iVSpeed = 0;
					play_var.nDelayTime = 0;
					//显示到电视上
					result = m_player_manager.play_score_osd(image_path,play_var,OSDAlignmentRightCenter);
					if (result)
					{
						set_score_show_timer(1000);
					}
				}	
			}
		}
		/*
		//显示提示语
		if (score > 90)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score9%d.png", m_work_path, number);
		}
		else if (score > 80)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score8%d.png", m_work_path, number);
		}
		else if (score > 70)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score7%d.png", m_work_path, number);
		}
		else if (score > 60)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score6%d.png", m_work_path, number);
		}
		else if (score > 50)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score5%d.png", m_work_path, number);
		}
		else
		{
			return;
		}*/
		if (score >90)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score9.gif", m_work_path);
		}
		else if (score > 80)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score8.gif", m_work_path);
		}
		else if (score > 70)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score7.gif", m_work_path);
		}
		else if (score > 60)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score6.gif", m_work_path);
		}
		else if (score > 50)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score5.gif", m_work_path);
		}
		else if (score > 40)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score4.gif", m_work_path);
		}
		else if (score > 30)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score3.gif", m_work_path);
		}
		else if (score > 20)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score2.gif", m_work_path);
		}
		else if (score>10)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score1.gif", m_work_path);
		}
		else if (score > 0)
		{
			swprintf_s(image_path, sizeof(image_path)/sizeof(TCHAR), L"%s\\score_flash\\image\\score0.gif", m_work_path);
		}
		else
		{
			return;
		}

		//show_picture_on_tv(image_path,OSDAlignmentCenterTop,3000,false,false);
		//show_picture_on_tv(image_path,OSDSCOREPOS,3000,false,false);
		show_picture_on_tv(image_path,OSDSCOREPOS,6000,false,false);
		if (1 == number)
		{
			number = 2;
		}
		else
		{
			number = 1;
		}
	}
	catch (...)
	{

	}
	return;
}
UINT Cflashktv10Wnd::flash_message_call_service_barrage(LPVOID pParam)
{
	try
	{
		LPBARRAGE_MSG pBarrageMsg = (LPBARRAGE_MSG)pParam;

		Cflashktv10Wnd* pKtvWnd = (Cflashktv10Wnd*)pBarrageMsg->pWnd;
		char szData[2048] = {0x00};
		strcpy(szData, pBarrageMsg->szData);

		delete pBarrageMsg;
		pBarrageMsg = NULL;

		Json::Reader reader;
		Json::Value root;

		//不能解析
		if (!reader.parse(szData, root, false))
		{
			WriteLog(__FL__, L"弹幕json格式错误！");
			return 1;
		}
		
		pKtvWnd->m_barrage_lock.lock();

		TCHAR szTmp[2048] = {0x00};
		string_conversion string_conn;
		LPBARRAGE_INFO pBarrageInfo = new BARRAGE_INFO();

		const char *pGuid = newGUID();
		string_conn.multibyte_to_widechar(pGuid, szTmp, sizeof(szTmp));
		pBarrageInfo->strGUID = szTmp; //设置guid

		if(root.isMember("color"))
		{
			string_conn.multibyte_to_widechar(root["color"].asString().c_str(), szTmp, sizeof(szTmp));
			pBarrageInfo->strColor = szTmp;
		}

		if(root.isMember("speed"))
		{
			pBarrageInfo->nSpeed = root["speed"].asInt();
		}

		if(root.isMember("count"))
		{
			pBarrageInfo->nCount = root["count"].asInt();
		}

		if(root.isMember("content"))
		{
			string_conn.multibyte_to_widechar(root["content"].asString().c_str(), szTmp, sizeof(szTmp));
			pBarrageInfo->strContent = szTmp;
		}

		if (root.isMember("key"))
		{
			Json::Value json_key = root["key"];
			int size = json_key.size();
			for (int i = 0; i < size; i++)
			{
				
			}
		}

		root.toStyledString();

		pKtvWnd->m_barrage_lock.unlock();
	}
	catch (...)
	{

	}
	return 0;
}
void Cflashktv10Wnd::flash_message_call_service_share_success(char * recv_data)
{
	try
	{
		TCHAR song_id[256];
		TCHAR log_text[256];
		std::wstring pop_id; 
		string_conversion string_con;

		memset(song_id,0x0,sizeof(song_id));
		memset(log_text,0x0,sizeof(log_text)); 

		string_con.utf8_to_widechar(recv_data,song_id,sizeof(song_id));
		
		swprintf(log_text,L"接收到规则服务器发过来的分享成功的歌曲id Song_ID=%s",song_id);

		WriteLog(__FL__, log_text);

		if (!m_song_share_success.empty())
		{
			SONG_SHARE_SUCCESS song_share = m_song_share_success.front();

			pop_id = song_share.song_id;

			if (0 == _tcscmp(song_id,pop_id.c_str()))
			{
				//发过来的分享和记录的相同  移除第一个
				m_song_share_success.pop_front(); 
			}
		}		
	}
	catch (...)
	{
		
	} 

	return;
}

void Cflashktv10Wnd::flash_message_call_service_push_song(char* recv_data)
{
	try
	{
		TCHAR push_song[256];
		TCHAR push_flags[256];
		TCHAR data[256];
		string_conversion string_con;
		const TCHAR *parse_msg=NULL;
		const TCHAR *temp=NULL;

		memset(push_song,0x0,sizeof(push_song));
		memset(push_flags,0x0,sizeof(push_flags));
		memset(data,0x0,sizeof(data));

		//1245354&(0：顺序播放，1：立即播放)
		string_con.utf8_to_widechar(recv_data,data,sizeof(data));

		parse_msg = data;
		temp = _tcschr(parse_msg,'&');
		memcpy(push_song,parse_msg,(temp-parse_msg)*sizeof(TCHAR));

		parse_msg = temp+1;
		temp = _tcschr(parse_msg,'$'); 
		memcpy(push_flags,parse_msg,(temp-parse_msg)*sizeof(TCHAR));

		if (0 == _tcscmp(push_flags,L"0"))
		{
			//顺序播放
			flash_message_call_select_song(push_song,false,false,true);
		}
		else if (1 == _tcscmp(push_song,L"1"))
		{
			//立即播放
			flash_message_call_select_song(push_song,true,false,true);
		}

		//发送点播记录统计
		memset(data,0x0,sizeof(data));
		swprintf(data,L"PUSHSONG{\"state\":\"0\"}");

		REQUEST_BOX_DATA *request_rule_data1 = new REQUEST_BOX_DATA;
		request_rule_data1->pThis = this;
		_tcscpy(request_rule_data1->request_data,data);
		AfxBeginThread(send_data_to_maiba_rule_thread,request_rule_data1);
		
	}
	catch (...)
	{
		
	}
	
	return;
}

bool Cflashktv10Wnd::compute_socre_result(void)
{
	try
	{
		song_info video_info;
		TCHAR song_name[256];
		TCHAR singer_name[256];
		bool result = false;

		PLAY_SONG_TYPE video_type =	m_player_manager.get_playing_video_type();

		if (!m_is_scoring || (m_lyric_total_sentences <= 0) ||  (PLAY_SONG_TYPE_SELECT_SONG != video_type))
		{
			TCHAR szMsg[MAX_PATH] = {0x00};
			swprintf(szMsg, L"要返回false,不能显示视频评分![%d]---[%d]--[%d]", m_is_scoring, m_lyric_total_sentences, (int)video_type);
			WriteLog(__FL__, szMsg);
			return false;
		}

		//计算平均值
		m_score_intact /= m_lyric_total_sentences;
		if (m_score_intact>100)
		{
			m_score_intact = 100;
		}
		m_score_similarity /= m_lyric_total_sentences;
		if (m_score_similarity>100)
		{
			m_score_similarity = 100;
		}
		m_score_stability /= m_lyric_total_sentences;
		if (m_score_stability>100)
		{
			m_score_stability = 100;
		}
		//消耗的卡路里
		m_total_calories = 20*m_score_intact/100;

		//计算总分
		if ((m_score_intact<1)||(m_score_similarity<1)||(m_score_stability<1))
		{
			m_shine_total_score = 0;
			m_score_stability = 0;
			m_score_stability = 0;
			m_total_calories = 0;
		}
		else
		{
			m_shine_total_score = m_score_similarity*2/5+m_score_intact/5+m_score_stability*2/5;
		}
		//得到当前播放的歌曲
		memset(m_score_song_info,0x0,sizeof(m_score_song_info));
		memset(&video_info,0x0,sizeof(video_info));
		result = m_player_manager.get_playing_video(video_info);
		if (result)
		{
			//得到歌曲名字
			video_info.get_song_name(m_score_song_info);
		}

		//广播得到分数 2014-07-08 YZL
		if (/*m_shine_total_score*/m_nCurrentScore>=60)
		{
			send_socre_data_to_room_udp(/*m_shine_total_score*/m_nCurrentScore, video_info);
		}

		//得到下一首播放的歌曲
		memset(song_name,0x0,sizeof(song_name));
		memset(singer_name,0x0,sizeof(singer_name));
		memset(&video_info,0x0,sizeof(video_info));
		memset(m_next_song_info,0x0,sizeof(m_next_song_info));
		result = m_video_play_manager.get_select_song_information(video_info,0,false);
		if (result)
		{
			video_info.get_song_name(song_name);
			video_info.get_singer_name(singer_name);
		}
		else
		{
			_tcscpy(song_name,L"空闲歌曲");
		}
		//显示下一首歌曲名、歌星名
		swprintf(m_next_song_info,L"%s    %s",song_name,singer_name);

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

bool Cflashktv10Wnd::play_score_video(void)
{
	try
	{
		PLAY_SONG_TYPE video_type =	m_player_manager.get_playing_video_type();
		bool result = false;

		if ((/*m_shine_total_score*/m_nCurrentScore <= 0) || (PLAY_SONG_TYPE_SELECT_SONG != video_type))
		{
			TCHAR szMsg[256] = {0x00};
			swprintf(szMsg, L"分数小于0或者播放类型不正确 score = %d, type = %d", /*m_shine_total_score*/m_nCurrentScore, (int)video_type);
			WriteLog(__FL__, szMsg);
			return false;
		}

		//显示flash
		if (SCORE_SYSTEM_SHINE==m_use_score_system
			&& m_nCurPageCode != page_picture_mv && m_nCurPageCode != page_challenge_star 
			&& m_nCurPageCode != page_listen_knowledge_song && m_nCurPageCode != page_across_pass)  //阳光评分系统
		{
			if (m_soft_decode_window_exist)
			{
				////分数结果
				m_soft_load_score_flash_success = m_soft_score_flash_player.Create(NULL,WS_CHILD,CRect(0,0,m_sencond_display_width,m_sencond_display_height),&m_soft_decode_window,SCORE_SOFT_FLASH_WINDOW_ID);
				if (m_soft_load_score_flash_success)
				{
					TCHAR score_path[256];

					memset(score_path,0x0,sizeof(score_path));

					swprintf(score_path,L"%s\\score_flash_interface\\Main.swf",m_work_path);
					if (PathFileExists(score_path))
					{
						m_soft_score_flash_player.Stop();
						m_soft_score_flash_player.LoadMovie(0,score_path);
						m_soft_score_flash_player.ShowWindow(SW_SHOW);
						m_soft_score_flash_player.BringWindowToTop();
						m_soft_score_flash_player.put_ScaleMode(2);
						m_bScoring = true;
					}
					else
					{
						m_soft_load_score_flash_success = false;
					}
				}
			}
			if (m_inter_screen_exist)
			{
				m_load_score_flash_success = m_score_flash_player.Create(NULL,WS_CHILD,m_rtRelativeActivityWnd,&m_inter_screen_window,SCORE_FLASH_WINDOW_ID);
				if (m_load_score_flash_success)
				{
					TCHAR score_path[256];
					memset(score_path,0x0,sizeof(score_path));

					swprintf(score_path,L"%s\\score_flash_interface\\Main.swf",m_work_path);
					if (PathFileExists(score_path))
					{
						m_score_flash_player.Stop();
						m_score_flash_player.LoadMovie(0,score_path);
						m_score_flash_player.ShowWindow(SW_SHOW);
						m_score_flash_player.BringWindowToTop();
						m_score_flash_player.put_ScaleMode(2);
						m_bScoring = true;
					}
					else
					{
						m_load_score_flash_success = false;
					}
				}
			}
			//////*/
		}
		if (!m_soft_load_score_flash_success && !m_load_score_flash_success)
			return false;
		//分数大于0，需要打分，就显示分数
		result = make_mark_for_singer(/*m_shine_total_score*/m_nCurrentScore);
		if (!result)
		{
			return false;
		}

#ifdef DON_GUAN_K_PLUS
		if (!m_soft_load_score_flash_success && !m_load_score_flash_success && !m_show_score_in_screen)
#else
		if (!m_soft_load_score_flash_success && !m_load_score_flash_success)
#endif // DON_GUAN_K_PLUS			
		{
			WriteLog(__FL__, L"加载分数失败");
			return false;
		}

		WriteLog(__FL__, L"显示评分结果======play_score_video");
		
		//设置标识
		m_show_song_tip_osd = true;

#ifdef DON_GUAN_K_PLUS //K+需要声音
		TCHAR szAudioPath[MAX_PATH] = {0x00};
		if (m_shine_total_score < 80)
		{
			swprintf(szAudioPath, L"%s\\score_audio\\LessThan80.wav", m_work_path);
		}else if (m_shine_total_score >= 80 && m_shine_total_score < 90)
		{
			swprintf(szAudioPath, L"%s\\score_audio\\Between8090.wav", m_work_path);
		}else if (m_shine_total_score >= 90)
		{
			swprintf(szAudioPath, L"%s\\score_audio\\MoreThan90.wav", m_work_path);
		}
		
		//播放音频
		if (m_soft_decode_window_exist)
		{
			//软解，直接播放，没有延迟
			PlaySound(szAudioPath, NULL, SND_FILENAME|SND_NOWAIT|SND_ASYNC);
		}
		else
		{
			//硬解码，必须有控件播放
			m_player_manager.play_wave_mixer_audio(szAudioPath,0,1);
		}	
#endif // DON_GUAN_K_PLUS

		return true;
	}
	catch (...)
	{
		
	}

	return false;
}

void Cflashktv10Wnd::dwon_song_file_to_server(const TCHAR* args,int down_type)
{
	try
	{
		int number=0;
		bool result = false;
		TCHAR song_local_path[256];   //得到当前歌曲的状态 0：本地歌曲  1：下载歌曲  2：更新歌曲
		song_info song_info_class;
		TCHAR song_id[256];
		TCHAR send_data[256];
		TCHAR request[1024];
		TCHAR data[1024];

		memset(song_local_path,0x0,sizeof(song_local_path));
		memset(song_id,0x0,sizeof(song_id));
		memset(send_data,0x0,sizeof(send_data));
		memset(request,0x0,sizeof(request));
		memset(data,0x0,sizeof(data));

		/*
		//得到选择的编号
		swscanf(args,L"%d",&number);
		if ((number<0)||(number>=m_page_show_row_count))
		{
			return;
		}

		//得到选中的歌曲信息
		result = m_query_song_manager.get_song_info(number,song_info_class);
		*/
		result = get_song_info_by_id(args, song_info_class, PLAY_SONG_TYPE_SELECT_SONG);
		if (!result)
		{
			return;
		}

		//得到歌曲编号
		result = song_info_class.get_song_id(song_id);

		//发送给服务器 DOWNLOADSONGFILE|song_id
		swprintf(send_data,L"DOWNLOADSONGFILE|%s",song_id);

		m_cloud_song_lock.lock();
		//保存到map中
		m_down_song_vec.push_back(song_id);
		m_cloud_song_lock.unlock();

		WriteLog(__FL__, send_data);

		send_data_to_service_udp(send_data);

		////弹出提示框，提交下载
		//if (1 == down_type || 2 == down_type)
		//{
		//	//下载
		//	swprintf(data,L"正在为您下载/更新该歌曲，请稍等...");

		//	//组织歌曲字符串
		//	result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"down_song_dialog",data);
		//	if (result)
		//	{
		//		flash_player_call_function(request);
		//	}
		//}		
	}
	catch (...)
	{

	} 

	return;
}
void Cflashktv10Wnd::send_score_button_state(int state /* = 0 */)
{
	TCHAR data[256] = {0x00};
	TCHAR command[256] = {0x00};
	TCHAR request[1024] = {0x00};
	bool result = false;
	if (state == 1)
	{
		//高亮
		_tcscpy(data,L"<data><score>true</score></data>");
	}
	else if(state == 0)
	{ 
		//取消高亮
		_tcscpy(data,L"<data><score>false</score></data>");
	}
	_tcscpy(command,L"score_drawline_button");

	result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
	if (result)
	{
		flash_player_call_function(request);
	}
}

UINT Cflashktv10Wnd::recv_server_voice_china_udp_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);

		pThis->recv_server_voice_china_udp();
	}
	catch (...)
	{

	}

	return 0;
}

UINT Cflashktv10Wnd::recv_server_voice_china_udp()
{
	try
	{
		fd_set socket_set;
		timeval overtime;
		overtime.tv_sec = 0;
		overtime.tv_usec = 10000;
		int result=0;

		//清0
		FD_ZERO(&socket_set);

		//create socket
		SOCKET list_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (list_socket < 0) 
		{

			return -1;
		}
		//设置socket属性
		struct linger zerolinger;
		zerolinger.l_onoff = 1;
		zerolinger.l_linger = 5;
		setsockopt(list_socket,SOL_SOCKET,SO_LINGER,(const char *)&zerolinger,sizeof(zerolinger));
		int recv_timeout=60000;
		setsockopt(list_socket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&recv_timeout,sizeof(recv_timeout));

		//bind local addr
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		addr.sin_port = ntohs(62012);
		memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
		if (SOCKET_ERROR==bind(list_socket, (struct sockaddr*)&addr, sizeof(sockaddr_in)))
		{

			return -1;
		}
		//加入监听组
		FD_SET(list_socket,&socket_set);
		while (m_thread_run)
		{
			try
			{
				SLEEP_FOR; //增加sleep

				//将fdSocket集合的一个拷贝fdRead传递给select函数，
				// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回
				fd_set fdRead_set = socket_set;
				result = ::select(0,&fdRead_set,NULL,NULL,&overtime);
				if (result<=0)
				{
					continue;
				}
				//通过将原来fdSocket集合与select处理过的fdRead集合比较，
				// 确定都有哪些套节字有未决I/O，并进一步处理这些I/O。
				for(int i=0; i<(int)socket_set.fd_count; i++)
				{
					if (FD_ISSET(socket_set.fd_array[i],&fdRead_set))
					{
						//recv data
						char recv_data[2048*5];
						int recv_len=0;
						sockaddr_in send_addr;
						int nLen = sizeof(send_addr);

						memset(recv_data,0x0,sizeof(recv_data));

						recv_len = ::recvfrom(socket_set.fd_array[i],recv_data,sizeof(recv_data),0,(sockaddr*)&send_addr, &nLen);

						if (recv_len>0)                     //(2)接受到数据
						{
							//
							if (0==_strnicmp(recv_data,"VOICECHINA",10))
							{
								//解析数据	
								shine_parse_voice_china_data(recv_data+11);
							}

						}//end if
					}
				}//end for()
			}
			catch (...)
			{

			}
		}
		//终止线程

		return 1;
	}
	catch (...)
	{

	}


	return -1;
}


bool Cflashktv10Wnd::shine_parse_voice_china_data(char* recv_data)
{
	try
	{
		TCHAR song_data[1024*2];
		TCHAR insert_sql[1024*2];
		TCHAR song_singer_id[256];
		const TCHAR* parse_msg = NULL;
		const TCHAR* temp = NULL;
		string_conversion string_con;
		bool result = false;

		memset(song_data,0x0,sizeof(song_data));
		memset(song_singer_id,0x0,sizeof(song_singer_id));
		memset(insert_sql,0x0,sizeof(insert_sql));

		string_con.multibyte_to_widechar(recv_data,song_data,sizeof(song_data));

		if (0 == _tcsncmp(song_data,L"song",4))
		{
			//歌曲
			//插入到数据库中 song|975878|sql
			parse_msg = song_data + 5;
			temp = _tcschr(parse_msg,'|');
			if (NULL == temp)
			{
				return false;
			}  

			memcpy(song_singer_id,parse_msg,(temp-parse_msg)*sizeof(TCHAR));
			_tcscpy(insert_sql,temp+1);
			result = m_db_query.exec_sql(insert_sql);
			if (!result)
			{
				WriteLog(__FL__, L"插入失败！");
				WriteLog(__FL__, insert_sql);
			}
		}
		else if (0 == _tcsncmp(insert_sql,L"singer",6))
		{
			//歌星
			//singer|41000831|sql
			parse_msg = insert_sql + 7;
			temp = _tcschr(parse_msg,'|');
			if (NULL == temp)
			{
				return false;
			} 

			memcpy(song_singer_id,parse_msg,(temp-parse_msg)*sizeof(TCHAR));
			_tcscpy(insert_sql,temp+1);
			result = m_db_query.exec_sql(insert_sql);
			if (!result)
			{
				WriteLog(__FL__, L"插入失败！");
				WriteLog(__FL__, insert_sql);
			}
		}

		return true;
	}
	catch (...)
	{

	} 

	return false;
}

void Cflashktv10Wnd::show_tv_picture_path(int tvcount)
{
	try{
		TCHAR *inint_path=NULL;
		TCHAR tv_picture_path[MAX_PATH];
		TCHAR path[1024*10];
		TCHAR tmp_path[256];
		TCHAR folder_name[256];
		TCHAR data[1024*10];
		TCHAR request[1024*10];
		TCHAR picture_name[256];
		TCHAR command[256];
		bool result;
		memset(command,0x0,sizeof(command));
		memset(picture_name,0x0,sizeof(picture_name));
		memset(tv_picture_path,0x0,sizeof(tv_picture_path));
		memset(path,0x0,sizeof(path));
		memset(tmp_path,0x0,sizeof(tmp_path));
		memset(folder_name,0x0,sizeof(folder_name));
		memset(data,0x0,sizeof(data));
		memset(request,0x0,sizeof(request));

		set_flash_button_state(L"film_video_button",m_film_video_button_state);
		_tcscpy(folder_name,L"\\tv_picture");
		GetModuleFileName(NULL, tv_picture_path, sizeof(tv_picture_path));
		inint_path = _tcsrchr(tv_picture_path, _T('\\'));
		if (inint_path)
		{
			inint_path[0] = '\0';
		}
		_tcscat(tv_picture_path,folder_name);
		_tcscat(tv_picture_path,L"\\video");
		for (int i = 1; i <= tvcount; i++)
		{
			memset(tmp_path,0x0,sizeof(tmp_path));
			swprintf(tmp_path,L"<item item_path=\"%s\\%d.png\" name=\"%s\" />",tv_picture_path,i,m_tv_name[i-1].c_str());
			_tcscat(path,tmp_path);
		}
		swprintf(data,L"<data>%s</data>",path);
		_tcscpy(command,L"tv_path");
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
		if (result)
		{
			flash_player_call_function(request);
		}
	}
	catch(...)
	{

	}
	return;
}
/*播放flash*/
bool Cflashktv10Wnd::PlayScreenFlash(CTransparentWnd * pWnd, CWnd *pParent, TCHAR *pwFlashPath, CRect rtWnd, CRect rtFlash, UINT wndId /*= NULL*/, UINT flashId /*= NULL*/)
{
	bool bRet = false;

	bRet = pWnd->Create((CString)"",(CString)"",WS_POPUP|WS_VISIBLE|WS_OVERLAPPED, rtWnd, NULL, wndId);

	if (bRet)
	{
		pWnd->set_message_handle(m_hWnd);

		pWnd->SetWindowPos(&CWnd::wndTopMost,rtWnd.left,rtWnd.top,rtWnd.Width(),rtWnd.Height(),NULL);

		pWnd->ShowWindow(SW_SHOW);

		pWnd->UpdateWindow();

		bRet = pWnd->PlayFlash(pwFlashPath, rtFlash, flashId);

//		m_vecTransparentWnd.push_back(m_StarTransparentWnd);
	}
	return bRet;
}
/*停止flash*/
bool Cflashktv10Wnd::destroy_screen_flash_wnd()
{
	vector<CTransparentWnd*>::iterator iter = m_vecTransparentWnd.begin();
	for (; iter != m_vecTransparentWnd.end(); )
	{
		if ((*iter != NULL) && ((*iter)->m_nState == FLASH_OVER))
		{
			delete *iter;

			*iter = NULL;

			iter = m_vecTransparentWnd.erase(iter);
		}
		else
			++iter;
	}
	return true;
}

/*/////////挑战大咖///////////////*/
//开始挑战
bool Cflashktv10Wnd::start_challenge_star(int nIndex, const TCHAR* pSongIndex)
{
	try
	{
		bool bRet = false;
		song_info info;
		enum PLAYER_PLAY_STATE player_state;
		TCHAR wszFlashPath[256] = {0x00};
		int page_index = page_challenge_star;

		//得到选择的编号
		if ((nIndex<0) || (nIndex >= m_nChallengeSongCount))
		{
			return false;
		}
		//得到选中的歌曲信息
		bRet = get_song_info_by_id(m_vec_challenge_star_info[nIndex].original_song_id, info, PLAY_SONG_TYPE_SELECT_SONG);
		if (!bRet)
		{
			return false;
		}
		TCHAR singer_sex[256]={0x00}, singer_id[256]={0x00}, singer_path[256] = {0x00};
		info.get_singer_sex(singer_sex);
		info.get_singer_id1(singer_id);
		swprintf(singer_path,L"%s\\%s\\%s.jpg",m_work_path, L"singer_picture", singer_id);
		if (!PathFileExists(singer_path))
		{
			swprintf(singer_path,L"%s\\%s\\default.jpg",m_work_path, L"singer_picture");
		}
		//设置歌曲从哪个页面来
		info.set_flash_page_code(page_index);
		//得到目前系统所处的状态
		player_state = m_video_play_manager.get_player_cur_state();
		//如果正在播放用户点的歌曲，那么把该歌曲放到已选歌曲中
		bRet = m_video_play_manager.add_select_song(info, true);
		if (!bRet)
		{
			return bRet;
		}
		//改变播放器的状态
		bRet = m_video_play_manager.set_player_next_state(PLAY_SONG_STATE);
		//更新选择的歌曲数目
		bRet = update_select_song_count();
		//发送歌曲信息
		bRet = flash_message_call_current_challenge_song(singer_path, nIndex);
		//切歌
		flash_message_call_function(SONG_NEXT);

		return bRet;
	}
	catch (...)
	{
	}

	return false;	
}

bool Cflashktv10Wnd::flash_message_call_challenge_star()
{
	try
	{
		bool bRet = false;
		
		// 发送规则信息
		bRet = flash_message_call_challenge_star_rule();

		// 页码信息
		flash_message_call_challenge_star_page_info(FIRST_PAGE_OPERATE, true);

		// 发送歌曲信息
		bRet = flash_message_call_challenge_star_song(FIRST_PAGE_OPERATE, true);

		return true;
	}
	catch (...)
	{
	}

	return false;
}

bool Cflashktv10Wnd::flash_message_call_challenge_star_rule()
{
	try
	{
		bool bRet = false;
		TCHAR request[1024*10] = {0x00}, data[1024*100] = {0x00};

		//如果没有请求到规则
		if (0 == _tcscmp(m_maiba_rule_arena_info[3].activity_id, L""))
		{
			swprintf(data,L"<data><info></info></data>");
		}
		else
		{
			swprintf(data,L"<data><info><activity_type>%s</activity_type><start_time>%s</start_time><end_time>%s</end_time><participation_type1>%s</participation_type1>\
						   <participation_song>%s</participation_song><participation_type2>%s</participation_type2><rating_methods>%s</rating_methods><activities_award1>%s</activities_award1>\
						   <activities_award2>%s</activities_award2><activities_award3>%s</activities_award3><activities_award4>%s</activities_award4><activities_award5>%s</activities_award5></info></data>",
						   m_maiba_rule_arena_info[3].activity_type,m_maiba_rule_arena_info[3].start_time,m_maiba_rule_arena_info[3].end_time,
						   m_maiba_rule_arena_info[3].participation_type1,m_maiba_rule_arena_info[3].participation_song,m_maiba_rule_arena_info[3].participation_type2,
						   m_maiba_rule_arena_info[3].rating_methods,m_maiba_rule_arena_info[3].activities_award1,m_maiba_rule_arena_info[3].activities_award2,
						   m_maiba_rule_arena_info[3].activities_award3,m_maiba_rule_arena_info[3].activities_award4,m_maiba_rule_arena_info[3].activities_award5);
		}

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR), L"challenge_star_rule", data);
		if (!bRet)
		{
			return false;
		}

		flash_player_call_function(request);

		return bRet;
	}
	catch (...)
	{
	}

	return false;
}

bool Cflashktv10Wnd::flash_message_call_challenge_star_page_info(enum PAGE_OPERATE page_operate, bool bInit)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024*100] = {0x00}, data[1024*100] = {0x00};

		if(m_nChallengeSongCount <=0)
		{
			//没有数据
			return false;
		}
		//改变页码
		switch(page_operate)
		{
		case FIRST_PAGE_OPERATE: //第一页
			{
				m_nCurrentChallengeSongPage=1;
				m_nChallengeSongPageCount = m_nChallengeSongCount/m_page_show_row_count+((m_nChallengeSongCount%m_page_show_row_count!=0)?1:0);	 
			}
			break;
		case PRE_PAGE_OPERATE:
			{
				m_nCurrentChallengeSongPage--;
				if (m_nCurrentChallengeSongPage<=0)
				{
					m_nCurrentChallengeSongPage = m_nChallengeSongPageCount;
				}
			}
			break;
		case NEXT_PAGE_OPERATE:
			{
				m_nCurrentChallengeSongPage++;
				if (m_nCurrentChallengeSongPage>m_nChallengeSongPageCount)
				{
					m_nCurrentChallengeSongPage=1;
				}
			}
			break;
		case CUR_PAGE_OPERATE:
			{
				//显示当前页，页码不变
				m_nChallengeSongPageCount = m_nChallengeSongCount/m_page_show_row_count+((m_nChallengeSongCount%m_page_show_row_count!=0)?1:0);

				if (m_nChallengeSongPageCount>m_nChallengeSongPageCount)
				{
					m_nChallengeSongPageCount = m_nChallengeSongPageCount;
				}
				if (m_nChallengeSongPageCount<1)
				{
					m_nChallengeSongPageCount = 1;
				}
			}
			break;
		default:
			return false;
		}

		swprintf(data,L"<data><pageinfo bInit=\"%s\" total=\"%d\" pagenum=\"%d/%d\"/></data>", bInit?L"true":L"false", 
			m_nChallengeSongPageCount, m_nCurrentChallengeSongPage, m_nChallengeSongPageCount);
		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"challenge_page_info", data);
		if (!bRet)
		{
			return false;
		}

		flash_player_call_function(request);

		return true;
	}
	catch (...)
	{
		
	}
	return true;
}
bool Cflashktv10Wnd::flash_message_call_challenge_star_song(enum PAGE_OPERATE page_operate, bool bInit)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024*100] = {0x00}, data[1024*100] = {0x00};
		string_conversion string_con;
		int nPos = 0;

		//得到最后一页的索引
		int page_index = m_flash_manage.get_last_page_index();

		if (page_index != page_challenge_star)
		{
			return false;
		}
		//如果没有请求到规则
		if (0 == m_nChallengeSongCount)
		{
			swprintf(data,L"<data></data>");
		}
		else
		{
			make_challenge_star_song_sub_xml(data, page_operate, bInit);
		}

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"challenge_star_song", data);
		if (!bRet)
		{
			return false;
		}

		flash_player_call_function(request);

		return bRet;
	}
	catch (...)
	{
	}

	return false;
}

bool Cflashktv10Wnd::make_challenge_star_song_sub_xml(TCHAR* pSubData, enum PAGE_OPERATE page_operate, bool bInit)
{
	try
	{
		bool bRet = false;
		wstring strSub = L"", strTmp = L"";
		TCHAR szTmp[1024*100] = {0x00};

		//组织xml字符串
		int start_suffix = 0, end_suffix = 0, page_number = 0;
		//上一页
		page_number = m_nCurrentChallengeSongPage;
		if(page_number == 1)
		{
			start_suffix = (m_nChallengeSongPageCount-1)*m_page_show_row_count;
			end_suffix = m_nChallengeSongCount - 1;
		}
		else
		{
			start_suffix = (page_number-2)*m_page_show_row_count;
			end_suffix = (page_number-1)*m_page_show_row_count-1;
			if (end_suffix>=m_nChallengeSongCount)
			{
				end_suffix = m_nChallengeSongCount-1;
			}
		}

		strTmp += L"<pre_list>";
		for (int i=start_suffix;i<=end_suffix;i++)
		{
			memset(szTmp, 0x00, sizeof(szTmp));

			swprintf(szTmp, L"<item songid=\"%s\" songname=\"%s\" singername=\"%s\" goalscore=\"%s\"/>", m_vec_challenge_star_info[i].original_song_id, 
				m_vec_challenge_star_info[i].song_name, m_vec_challenge_star_info[i].singer_name, m_vec_challenge_star_info[i].goal_score);

			strTmp += (wstring)szTmp;
		}
		strTmp += L"</pre_list>";

		//组织当前页

		page_number = m_nCurrentChallengeSongPage;
		start_suffix = (page_number-1)*m_page_show_row_count;
		if (start_suffix<0)
		{
			start_suffix = 0;
		}
		
		end_suffix = page_number*m_page_show_row_count-1;
		if (end_suffix>=m_nChallengeSongCount)
		{
			end_suffix = m_nChallengeSongCount-1;
		}
		strTmp += L"<cur_list>";
		for (int i=start_suffix;i<=end_suffix;i++)
		{
			memset(szTmp, 0x00, sizeof(szTmp));

			swprintf(szTmp, L"<item songid=\"%s\" songname=\"%s\" singername=\"%s\" goalscore=\"%s\"/>", m_vec_challenge_star_info[i].original_song_id, 
				m_vec_challenge_star_info[i].song_name, m_vec_challenge_star_info[i].singer_name, m_vec_challenge_star_info[i].goal_score);

			strTmp += (wstring)szTmp;
		}
		strTmp += L"</cur_list>";
		//下一页
		page_number = m_nCurrentChallengeSongPage;
		if(page_number == m_nChallengeSongPageCount)
		{
			start_suffix = 0;
			end_suffix = m_page_show_row_count-1;
			if (end_suffix>=m_nChallengeSongCount)
			{
				end_suffix = m_nChallengeSongCount - 1;
			}
		}
		else
		{
			start_suffix = page_number*m_page_show_row_count;
			end_suffix = start_suffix+m_page_show_row_count-1;
			if (end_suffix > m_nChallengeSongCount)
			{
				end_suffix = m_nChallengeSongCount - 1;
			}
		}

		strTmp += L"<next_list>";
		for (int i=start_suffix;i<=end_suffix;i++)
		{
			memset(szTmp, 0x00, sizeof(szTmp));

			swprintf(szTmp, L"<item songid=\"%s\" songname=\"%s\" singername=\"%s\" goalscore=\"%s\"/>", m_vec_challenge_star_info[i].original_song_id, 
				m_vec_challenge_star_info[i].song_name, m_vec_challenge_star_info[i].singer_name, m_vec_challenge_star_info[i].goal_score);

			strTmp += (wstring)szTmp;
		}
		strTmp += L"</next_list>";

		swprintf(pSubData, L"<data>%s</data>", strTmp.c_str());
		
		return true;
	}
	catch (...)
	{
	}

	return false;
}

// 互动场景屏开始倒计时
bool Cflashktv10Wnd::flash_message_call_challenge_count_down(int nFlag/* = 0*/)
{
	try
	{
		bool bRet = false;
		TCHAR szRequese[1024] = {0x00}, szData[1024] = {0x00};

		swprintf(szData, L"<data><pageinfo pagename=\"challenge_count_down\" logo_url=\"\" page_title=\"挑战倒计时\"/></data>");

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(szRequese, sizeof(szRequese)/sizeof(TCHAR), L"challenge_count_down", szData);
		if (!bRet)
		{
			return false;
		}
		if (nFlag == 0)
		{
			if (m_StarTransparentWnd != NULL)
			{
				if (m_StarTransparentWnd->m_pFlash->m_hWnd != NULL)
				{
					CString str = m_StarTransparentWnd->m_pFlash->CallFunction(szRequese);
				}
			}
			if (m_StarSoftTransparentWnd != NULL)
			{
				if (m_StarSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
				{
					CString str = m_StarSoftTransparentWnd->m_pFlash->CallFunction(szRequese);
				}
			}
		}
		else if (nFlag == 1)
		{
			if (m_StarTransparentWnd != NULL)
			{
				if (m_StarTransparentWnd->m_pFlash->m_hWnd != NULL)
				{
					CString str = m_StarTransparentWnd->m_pFlash->CallFunction(szRequese);
				}
			}
		}
		else if (nFlag == 2)
		{
			if (m_StarSoftTransparentWnd != NULL)
			{
				if (m_StarSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
				{
					CString str = m_StarSoftTransparentWnd->m_pFlash->CallFunction(szRequese);
				}
			}
		}

		return true;
	}
	catch (...)
	{
		int n =0;
		DWORD dw = GetLastError();
	}

	return false;
}
// 开始播放挑战成功/失败动画 bResult:true成功
bool  Cflashktv10Wnd::flash_message_call_start_result(bool bResult)
{
	try
	{
		bool bRet = false;
		TCHAR szRequese[1024] = {0x00}, szData[1024] = {0x00};

		if (bResult)
		{
			swprintf(szData, L"<data><pageinfo pagename=\"challenge_success\" logo_url=\"\" page_title=\"挑战成功\"/></data>");

			//直接组织歌曲字符串 
			bRet = m_flash_manage.make_request(szRequese, sizeof(szRequese)/sizeof(TCHAR), L"challenge_success", szData);
			if (!bRet)
			{
				return false;
			}
//#ifdef DALIAN_MATSA_EK_PLUS
			if (!m_bCSGetAward)
			{
//#endif
				WriteLog(__FL__, L"发送挑战大咖奖励信息");
				REQUEST_BOX_DATA *request_box_data = new REQUEST_BOX_DATA;
				TCHAR requse_data[2048] = {0x00};
				swprintf(requse_data,L"SONG_RECORDER_YK{\"activity_id\":\"%s\",\"song_id\":\"%s\",\"song_name\":\"%s\",\"singer_name\":\"%s\",\"video_path\":\"\",\"culture_code\":\"\",\"wave_path\":\"\",\"start_time\":\"\",\"datetime\":\"\",\"is_share\":\"0\",\"room_name\":\"%s\",\"score\":\"%d\",\"user_name\":\"\",\"nick_name\":\"\",\"wave_exist\":\"0\",\"pk_flags\":\"0\",\"song_language\":\"\",\"song_version\":\"\",\"member_pic\":\"\" }",
					m_maiba_rule_arena_info[3].activity_id, m_vec_challenge_star_info[m_nChallengeIndex].original_song_id, m_vec_challenge_star_info[m_nChallengeIndex].song_name,
					m_vec_challenge_star_info[m_nChallengeIndex].singer_name, m_show_room_name, m_nCurrentScore); 

				_tcscpy(request_box_data->request_data, requse_data);
				request_box_data->nPort = 6666;
				request_box_data->pThis = this;
				AfxBeginThread(send_data_to_maiba_rule_thread, request_box_data);
//#ifdef DALIAN_MATSA_EK_PLUS
				//设置挑战大咖领取奖励标志为true
				m_bCSGetAward = true;
			}
//#endif
		}
		else
		{
			swprintf(szData, L"<data><pageinfo pagename=\"challenge_fail\" logo_url=\"\" page_title=\"挑战失败\"/></data>");

			//直接组织歌曲字符串 
			bRet = m_flash_manage.make_request(szRequese, sizeof(szRequese)/sizeof(TCHAR), L"challenge_fail", szData);
			if (!bRet)
			{
				return false;
			}
			//向活动软件发送挑战失败的消息
			REQUEST_BOX_DATA *request_box_data = new REQUEST_BOX_DATA;
			TCHAR requse_data[2048] = {0x00};
			swprintf(requse_data,L"SONG_RECORDER_YK{\"activity_id\":\"%s\",\"song_id\":\"%s\",\"song_name\":\"%s\",\"singer_name\":\"%s\",\"video_path\":\"\",\"culture_code\":\"\",\"wave_path\":\"\",\"start_time\":\"\",\"datetime\":\"\",\"is_share\":\"0\",\"room_name\":\"%s\",\"score\":\"%d\",\"user_name\":\"\",\"nick_name\":\"\",\"wave_exist\":\"0\",\"pk_flags\":\"0\",\"song_language\":\"\",\"song_version\":\"\",\"member_pic\":\"\" }",
				m_maiba_rule_arena_info[3].activity_id, m_vec_challenge_star_info[m_nChallengeIndex].original_song_id, m_vec_challenge_star_info[m_nChallengeIndex].song_name,
				m_vec_challenge_star_info[m_nChallengeIndex].singer_name, m_show_room_name, m_nCurrentScore); 

			_tcscpy(request_box_data->request_data, requse_data);
			request_box_data->nPort = 6666;
			request_box_data->pThis = this;
			AfxBeginThread(send_data_to_maiba_rule_thread, request_box_data);
		}

		if (m_StarTransparentWnd != NULL)
		{
			if (m_StarTransparentWnd->m_pFlash->m_hWnd != NULL)
			{
				try
				{
					CString str = m_StarTransparentWnd->m_pFlash->CallFunction(szRequese);
				}
				catch (...)
				{
					int i = 0;					
				}
			}
		}
		if (m_StarSoftTransparentWnd != NULL)
		{
			if (m_StarSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
			{
				try
				{
					CString str = m_StarSoftTransparentWnd->m_pFlash->CallFunction(szRequese);
				}
				catch (...)
				{
					int i = 0;
				}
			}
		}
		return bRet;
	}
	catch (...)
	{
	}

	return false;
}
// 发送当前挑战歌曲信息给flash
bool  Cflashktv10Wnd::flash_message_call_current_challenge_song(TCHAR *singer_path, int nIndex)
{
	try
	{
		bool bRet = false;
		TCHAR szRequese[1024] = {0x00}, szData[1024] = {0x00};

		swprintf(szData, L"<data><info song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\" singer_path=\"%s\" goal_score = \"%s\"/></data>", 
			m_vec_challenge_star_info[nIndex].original_song_id, m_vec_challenge_star_info[nIndex].song_name, 
			m_vec_challenge_star_info[nIndex].singer_name, singer_path, m_vec_challenge_star_info[nIndex].goal_score);
		
		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(szRequese, sizeof(szRequese)/sizeof(TCHAR), L"current_challenge_song", szData);
		if (!bRet)
		{
			return false;
		}

		if (m_StarTransparentWnd != NULL)
		{
			if (m_StarTransparentWnd->m_pFlash->m_hWnd != NULL)
			{
				CString str = m_StarTransparentWnd->m_pFlash->CallFunction(szRequese);
			}
		}
		if (m_StarSoftTransparentWnd != NULL)
		{
			if (m_StarSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
			{
				CString str = m_StarSoftTransparentWnd->m_pFlash->CallFunction(szRequese);
			}
		}
		return bRet;
	}
	catch (...)
	{
	}

	return false;
}

// 互动场景屏跳转到挑战歌曲flash页面
bool  Cflashktv10Wnd::flash_message_call_challenging()
{
	try
	{
		bool bRet = false;
		TCHAR szRequese[1024*10] = {0x00}, szData[1024*10] = {0x00};

		swprintf(szData, L"<data><info name=\"challenging_score\" score=\"0\"/></data>");

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(szRequese, sizeof(szRequese)/sizeof(TCHAR), L"challenging", szData);
		if (!bRet)
		{
			return false;
		}

		if (m_StarTransparentWnd != NULL)
		{
			if (m_StarTransparentWnd->m_pFlash->m_hWnd != NULL)
			{
				CString str = m_StarTransparentWnd->m_pFlash->CallFunction(szRequese);
			}
		}
		if (m_StarSoftTransparentWnd != NULL)
		{
			if (m_StarSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
			{
				CString str = m_StarSoftTransparentWnd->m_pFlash->CallFunction(szRequese);
			}
		}
		return bRet;
	}
	catch (...)
	{
	}

	return false;
}

bool Cflashktv10Wnd::flash_message_call_challenging_score(int score)
{
	try
	{
		bool bRet = false;
		TCHAR szRequese[1024*10] = {0x00}, szData[1024*10] = {0x00};

		swprintf(szData, L"<data><info name=\"challenging_score\" score=\"%d\"/></data>", score);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(szRequese, sizeof(szRequese)/sizeof(TCHAR), L"challenging_score", szData);
		if (!bRet)
		{
			return false;
		}

		if (m_StarTransparentWnd != NULL)
		{
			if (m_StarTransparentWnd->m_pFlash->m_hWnd != NULL)
			{
				CString str = m_StarTransparentWnd->m_pFlash->CallFunction(szRequese);
			}
		}
		if (m_StarSoftTransparentWnd != NULL)
		{
			if (m_StarSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
			{
				CString str = m_StarSoftTransparentWnd->m_pFlash->CallFunction(szRequese);
			}
		}
		return bRet;
	}
	catch (...)
	{
	}

	return false;
}
/************************百秒夺奖************************************************/
bool Cflashktv10Wnd::copy_pass_info()
{
	try
	{
		if (m_vec_pass_tmp.size() == 0)	return false;

		for (int i=0; i<m_vec_pass.size(); ++i)
		{
			m_pass_state[i] = m_vec_pass[i].GetState();
		}

		m_vec_pass.clear();
		m_vec_pass.assign(m_vec_pass_tmp.begin(), m_vec_pass_tmp.end());//

		m_nTotalPassCount = m_vec_pass.size();
		for (int i=0; i<m_nTotalPassCount; ++i)
		{
			m_vec_pass[i].SetState(m_pass_state[i]);
		}
		for (int i=0; i<m_nTotalPassCount; ++i)
		{
			if (m_vec_pass[i].GetState() == READY_ACROSS)
			{
				break;
			}
			if (m_vec_pass[i].GetState() == UN_ACROSS)
			{
				m_vec_pass[i].SetState(READY_ACROSS);
				break;
			}
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_across_pass_count()
{
	try
	{
		bool bRet = false;
		TCHAR request[1024*5] = {0x00}, tmp[1024*5] = {0x00};
		int nIndex = 0;

		swprintf(tmp, L"<data><info across_pass_count=\"%d\"></info></data>", m_nTotalPassCount);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"across_pass_count", tmp);
		if (!bRet)
		{
			return false;
		}

		bRet = flash_player_call_function(request);

		return bRet;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_main_pass_pc(bool bBgMusic)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024*5] = {0x00}, tmp[1024*5] = {0x00};
		wstring strData = L"";
		int nIndex = 0;

		vector<CPassManager>::iterator iter = m_vec_pass.begin();
		for (;iter != m_vec_pass.end(); ++iter)
		{
			swprintf(tmp, L"<item index=\"%d\" prize=\"%s\" flag=\"%d\"/>", nIndex, (*iter).GetPrize(), (*iter).GetState());
			
			nIndex++;
			strData += tmp;
			memset(tmp, 0x00, sizeof(tmp));
		}
		swprintf(tmp, L"<data><info totalpass=\"%d\" curpass=\"%d\" bgmusic=\"%s\">%s</info></data>", m_nTotalPassCount, m_nCurPassIndex, bBgMusic?L"1":L"0", strData.c_str());

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"main_pass_pc", tmp);
		if (!bRet)
		{
			return false;
		}

		bRet = flash_player_call_function(request);

		return bRet;
	}
	catch (...)
	{
	}
	return false;
}

bool Cflashktv10Wnd::flash_message_call_select_pass_song_pc(enum PAGE_OPERATE page_operate, bool bInit)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024*50] = {0x00}, sub[1024*50] = {0x00}, data[1024*50] = {0x00}, tmp[256] = {0x00};
		wstring strData = L"";
		int nSongCount = 0;

		if (m_vec_pass.size() == 0)	return false;
		//
		CPassManager pPass = m_vec_pass[m_nCurPassIndex];
		nSongCount = pPass.m_vec_song.size();

		bRet = make_pass_song_sub_xml(sub, page_operate);
		if (!bRet)	return false;

		switch(m_nCurPassIndex)
		{
		case 0:
			{
				swprintf(tmp, L"第一关");
			}
			break;
		case 1:
			{
				swprintf(tmp, L"第二关");
			}
			break;
		case 2:
			{
				swprintf(tmp, L"第三关");
			}
			break;
		case 3:
			{
				swprintf(tmp, L"第四关");
			}
			break;
		case 4:
			{
				swprintf(tmp, L"第五关");
			}
			break;
		case 5:
			{
				swprintf(tmp, L"第六关");
			}
			break;
		}
		
		swprintf(data, L"<data><info init = \"%s\" highlight=\"%s\" cur_pass=\"%d\"  show_cur_pass=\"%s\" song_count=\"%d\" prize=\"%s\" flag=\"%d\">%s</info></data>", 
			bInit?L"true":L"false", bInit?L"0":L"", m_nCurPassIndex, tmp, nSongCount, pPass.GetPrize(), pPass.GetState(), sub);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"select_pass_song_pc", data);
		if (!bRet)
		{
			return false;
		}

		bRet = flash_player_call_function(request);

		return bRet;
	}
	catch (...)
	{
	}
	return false;
}

/*组织3页歌曲信息的xml数据*/
bool Cflashktv10Wnd::make_pass_song_sub_xml(TCHAR* pSubData, enum PAGE_OPERATE page_operate)
{
	try
	{
		bool bRet = false, bInit = false;
		int nSongCount = 0, nPageCount = 0, nCurPage = 0, nBegin = 0, nEnd = 0, nEachPageCount = 5;//每页5条数据
		TCHAR tmp[1024*50] = {0x00};
		wstring strData = L"";

		nSongCount = m_vec_pass[m_nCurPassIndex].GetSongCount();		
		nPageCount = nSongCount/nEachPageCount+(nSongCount%nEachPageCount?1:0);	 
		nCurPage = m_vec_pass[m_nCurPassIndex].GetCurPage();

		//改变页码
		switch(page_operate)
		{
		case FIRST_PAGE_OPERATE: //第一页
			{
				nCurPage=1;
				bInit = true;
			}
			break;
		case PRE_PAGE_OPERATE:
			{
				nCurPage--;
				if (nCurPage<=0)
				{
					nCurPage = nPageCount;
				}
			}
			break;
		case NEXT_PAGE_OPERATE:
			{
				nCurPage++;
				if (nCurPage>nPageCount)
				{
					nCurPage=1;
				}
			}
			break;
		case CUR_PAGE_OPERATE:
			{
				//显示当前页，页码不变
				nPageCount = nSongCount/nEachPageCount+(nSongCount%nEachPageCount?1:0);

				if (nPageCount>nPageCount)
				{
					nPageCount = nPageCount;
				}
				if (nPageCount<1)
				{
					nPageCount = 1;
				}
			}
			break;
		default:
			return false;
		}
		//总页数
		m_vec_pass[m_nCurPassIndex].SetPageCount(nPageCount);
		//当前页
		m_vec_pass[m_nCurPassIndex].SetCurPage(nCurPage);
		//当前歌曲索引
		m_nCurSongIndex = (m_vec_pass[m_nCurPassIndex].GetCurPage()-1)*5;//每页5首歌//默认每页第一首

		//上一页
		if(nCurPage == 1)
		{
			nBegin = (nPageCount-1)*nEachPageCount;
			nEnd = nSongCount - 1;
		}
		else
		{
			nBegin = (nCurPage-2)*nEachPageCount;
			nEnd = (nCurPage-1)*nEachPageCount-1;
			if (nEnd >= nSongCount)
			{
				nEnd = nSongCount-1;
			}
		}
		strData += L"<pre_list>";
		for (int i=nBegin;i<=nEnd;i++)
		{
			memset(tmp, 0x00, sizeof(tmp));

			swprintf(tmp, L"<item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\"/>", 
				m_vec_pass[m_nCurPassIndex].m_vec_song[i].song_id, m_vec_pass[m_nCurPassIndex].m_vec_song[i].song_name, m_vec_pass[m_nCurPassIndex].m_vec_song[i].singer_name);

			strData += (wstring)tmp;
		}
		strData += L"</pre_list>";

		//组织当前页
		nBegin = (nCurPage-1)*nEachPageCount;
		if (nBegin<0)
		{
			nBegin = 0;
		}
		nEnd = nCurPage*nEachPageCount-1;
		if (nEnd >= nSongCount)
		{
			nEnd = nSongCount-1;
		}
		strData += L"<cur_list>";
		for (int i=nBegin; i<=nEnd; i++)
		{
			memset(tmp, 0x00, sizeof(tmp));

			swprintf(tmp, L"<item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\" />", 
				m_vec_pass[m_nCurPassIndex].m_vec_song[i].song_id, m_vec_pass[m_nCurPassIndex].m_vec_song[i].song_name, m_vec_pass[m_nCurPassIndex].m_vec_song[i].singer_name);

			strData += (wstring)tmp;
		}
		strData += L"</cur_list>";
		//下一页
		if(nCurPage == nPageCount)
		{
			nBegin = 0;
			nEnd = nEachPageCount-1;
			if (nEnd >= nSongCount)
			{
				nEnd = nSongCount - 1;
			}
		}
		else
		{
			nBegin = nCurPage*nEachPageCount;
			nEnd = nBegin + nEachPageCount - 1;
			if (nEnd >= nSongCount)
			{
				nEnd = nSongCount - 1;
			}
		}
		strData += L"<next_list>";
		for (int i=nBegin;i<=nEnd;i++)
		{
			memset(tmp, 0x00, sizeof(tmp));

			swprintf(tmp, L"<item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\"/>", 
				m_vec_pass[m_nCurPassIndex].m_vec_song[i].song_id, m_vec_pass[m_nCurPassIndex].m_vec_song[i].song_name, m_vec_pass[m_nCurPassIndex].m_vec_song[i].singer_name);

			strData += (wstring)tmp;
		}
		strData += L"</next_list>";

		//返回xml
		swprintf(pSubData, L"%s", strData.c_str());

		return true;
	}
	catch(...)
	{

	}
	return false;
};
/*下一页信息*/
bool Cflashktv10Wnd::flash_message_call_pass_song_next_page_pc(int nIndex)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00}, tmp[1024] = {0x00};

		m_nCurSongIndex = nIndex + (m_vec_pass[m_nCurPassIndex].GetCurPage()-1)*5;//每页5首歌
		m_vec_pass[m_nCurPassIndex].SetCurSongIndex(m_nCurSongIndex);	//
		m_vec_pass[m_nCurPassIndex].SetState(READY_ACROSS);
		HUNDRED_SECONDS_PRIZE_SONG *song = m_vec_pass[m_nCurPassIndex].GetSongByIndex(m_nCurSongIndex);

		swprintf(data, L"<data><info cur_pass=\"%d\" prize=\"%s\" flag=\"%d\"><item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\"/></info></data>",
			m_nCurPassIndex, m_vec_pass[m_nCurPassIndex].GetPrize(), m_vec_pass[m_nCurPassIndex].GetState(), song->song_id, song->song_name, song->singer_name);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"pass_song_next_page_pc", data);
		if (!bRet)
		{
			return false;
		}

		bRet = flash_player_call_function(request);
		return bRet;
	}
	catch(...)
	{

	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_start_pass_pc()
{
	try
	{
		bool bRet = false;
		int nSongCount = 0;
		//
		CPassManager *pPass = &m_vec_pass[m_nCurPassIndex];
		nSongCount = pPass->m_vec_song.size();
		
		if (!m_bAcrossPassing)
		{
			pPass->SetState(ACROSSING);
		}
		
		flash_message_call_main_pass_pc(false);

		return bRet;
	}
	catch (...)
	{
	}
	return false;
}

bool Cflashktv10Wnd::flash_message_call_start_countdown()
{
	try
	{
		bool bRet = false;
		TCHAR request[256] = {0x00}, data[256] = {0x00};

		swprintf(data, L"<data><info name=\"start_countdown\"/></data>");
		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"start_countdown", data);
		if (!bRet)
		{
			return false;
		}
		if (m_bAcrossPassFlashPlayerExist)
		{
			m_AcrossPassFlashPlayer.CallFunction(request);
		}
		if (m_bAcrossPassSoftFlashPlayerExist)
		{
			m_AcrossPassSoftFlashPlayer.CallFunction(request);
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_main_pass_tv(int nFlag/* = 0*/)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00};
		wstring strData = L"";
		int nSongCount = 0;

		swprintf(data, L"<data><info name=\"main_pass_tv\"></info></data>");

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"main_pass_tv", data);
		if (!bRet)
		{
			return false;
		}

// 		if (m_PassTransparentWnd != NULL)
// 		{
// 			if (m_PassTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
// 		if (m_PassSoftTransparentWnd != NULL)
// 		{
// 			if (m_PassSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassSoftTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
		if (nFlag == 0)
		{
			if (m_bAcrossPassFlashPlayerExist)
			{
				m_AcrossPassFlashPlayer.CallFunction(request);
			}
			if (m_bAcrossPassSoftFlashPlayerExist)
			{
				m_AcrossPassSoftFlashPlayer.CallFunction(request);
			}
		}
		else if (nFlag == 1)
		{
			if (m_bAcrossPassFlashPlayerExist)
			{
				m_AcrossPassFlashPlayer.CallFunction(request);
			}
		}
		else if (nFlag == 2)
		{
			if (m_bAcrossPassSoftFlashPlayerExist)
			{
				m_AcrossPassSoftFlashPlayer.CallFunction(request);
			}
		}
		return true;
	}
	catch (...)
	{
	}
	return false;
}

/*下一页提示*/
bool Cflashktv10Wnd::flash_message_call_pass_next_page_tv()
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00};

		CPassManager *pPass = &m_vec_pass[m_nCurPassIndex];
		HUNDRED_SECONDS_PRIZE_SONG *song = pPass->GetSongByIndex(m_nCurSongIndex);
		int nIceInitCount = pPass->GetIceInitCount();
		int nIceAddSecond = pPass->GetIceAddSecond();

		swprintf(data, L"<data><info name=\"pass_next_page_tv\" cur_pass=\"%d\" prize=\"%s\" flag=\"%d\" intact=\"0\" similarity=\"0\" stability=\"0\" ice_count=\"%d\" ice_add_second=\"%d\"><item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\"/></info></data>",
			m_nCurPassIndex, pPass->GetPrize(), pPass->GetState(), nIceInitCount, nIceAddSecond, song->song_id, song->song_name, song->singer_name);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"pass_next_page_tv", data);
		if (!bRet)
		{
			return false;
		}

// 		if (m_PassTransparentWnd != NULL)
// 		{
// 			if (m_PassTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
// 		if (m_PassSoftTransparentWnd != NULL)
// 		{
// 			if (m_PassSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassSoftTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
		if (m_bAcrossPassFlashPlayerExist)
		{
			m_AcrossPassFlashPlayer.CallFunction(request);
		}
		if (m_bAcrossPassSoftFlashPlayerExist)
		{
			m_AcrossPassSoftFlashPlayer.CallFunction(request);
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}
/*电视端倒计时*/
bool Cflashktv10Wnd::flash_message_call_pass_count_down()
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00};

		CPassManager *pPass = &m_vec_pass[m_nCurPassIndex];
		HUNDRED_SECONDS_PRIZE_SONG *song = pPass->GetSongByIndex(m_nCurSongIndex);

		swprintf(data, L"<data><info name=\"pass_count_down\" cur_pass=\"%d\" prize=\"%s\" flag=\"%d\" intact=\"0\" similarity=\"0\" stability=\"0\" ice_count=\"%d\" ice_add_second=\"%d\"><item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\"/></info></data>",
			m_nCurPassIndex, pPass->GetPrize(), pPass->GetState(), pPass->GetIceInitCount(), pPass->GetIceAddSecond(), song->song_id, song->song_name, song->singer_name);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"pass_count_down", data);
		if (!bRet)
		{
			return false;
		}

// 		if (m_PassTransparentWnd != NULL)
// 		{
// 			if (m_PassTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
// 		if (m_PassSoftTransparentWnd != NULL)
// 		{
// 			if (m_PassSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassSoftTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
		if (m_bAcrossPassFlashPlayerExist)
		{
			m_AcrossPassFlashPlayer.CallFunction(request);
		}
		if (m_bAcrossPassSoftFlashPlayerExist)
		{
			m_AcrossPassSoftFlashPlayer.CallFunction(request);
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_start_pass_tv()
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00};

		CPassManager *pPass = &m_vec_pass[m_nCurPassIndex];
		HUNDRED_SECONDS_PRIZE_SONG *song = pPass->GetSongByIndex(m_nCurSongIndex);

		//设置当前关卡的冰块数量及增长间隔
		m_nIceInitCount = pPass->GetIceInitCount();
		m_nIceAddSecond = pPass->GetIceAddSecond();
		m_nGoalScore = pPass->GetGoalScore();
		m_nContinueCount = pPass->GetContinueCount();

		swprintf(data, L"<data><info name=\"start_pass_tv\" cur_pass=\"%d\" prize=\"%s\" flag=\"%d\" intact=\"0\" similarity=\"0\" stability=\"0\" ice_count=\"%d\" ice_add_second=\"%d\"><item song_id=\"%s\" song_name=\"%s\" singer_name=\"%s\"/></info></data>",
			m_nCurPassIndex, pPass->GetPrize(), pPass->GetState(), m_nIceInitCount, m_nIceAddSecond, song->song_id, song->song_name, song->singer_name);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"start_pass_tv", data);
		if (!bRet)
		{
			return false;
		}

// 		if (m_PassTransparentWnd != NULL)
// 		{
// 			if (m_PassTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
// 		if (m_PassSoftTransparentWnd != NULL)
// 		{
// 			if (m_PassSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassSoftTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
		if (m_bAcrossPassFlashPlayerExist)
		{
			m_AcrossPassFlashPlayer.CallFunction(request);
		}
		if (m_bAcrossPassSoftFlashPlayerExist)
		{
			m_AcrossPassSoftFlashPlayer.CallFunction(request);
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}
/*播放闯关歌曲*/
bool Cflashktv10Wnd::start_pass_tv()
{
	try
	{
		bool bRet = false;
		song_info info;
		enum PLAYER_PLAY_STATE player_state;
		TCHAR wszFlashPath[256] = {0x00};
		int page_index = page_across_pass;

		if (m_nTotalPassCount <= 0 || m_nCurPassIndex < 0)	return false;
		CPassManager *pass = &m_vec_pass[m_nCurPassIndex];
		if (pass->GetSongCount() <= 0 || m_nCurSongIndex < 0)	return false;
		
		//得到选中的歌曲信息
		bRet = get_song_info_by_id(pass->m_vec_song[m_nCurSongIndex].song_id, info, PLAY_SONG_TYPE_SELECT_SONG);
		if (!bRet)
		{
			return false;
		}
		//设置歌曲从哪个页面来
		info.set_flash_page_code(page_index);
		//得到目前系统所处的状态
		player_state = m_video_play_manager.get_player_cur_state();
		//如果正在播放用户点的歌曲，那么把该歌曲放到已选歌曲中
		bRet = m_video_play_manager.add_select_song(info, true);
		if (!bRet)
		{
			return false;
		}
		//改变播放器的状态
		bRet = m_video_play_manager.set_player_next_state(PLAY_SONG_STATE);
		//更新选择的歌曲数目
		bRet = update_select_song_count();
		//切歌
		flash_message_call_function(SONG_NEXT);

		return true;
	}
	catch (...)
	{
	}
	return false;
}
/*发送给flash 声准 音准 完整度*/
bool Cflashktv10Wnd::flash_message_call_sound_effect(int nIntact, int nSimilarity, int nStability)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00};
		int nIntactCount = m_nIntactCount, nSimilarityCount = m_nSimilarityCount, nStabilityCount = m_nStabilityCount;
		int nIntactFlag = 0, nSimilarityFlag = 0, nStabilityFlag = 0;//是否可以扔锤子的标志
		int nIntactRate = 0, nSimilarityRate = 0, nStabilityRate = 0;//进度条数值
		int nIncrease = 0, nFlag = 0, nIndex = -1;//每次增长的进度//

		if (m_nContinueCount <= 0 || m_nGoalScore <= 0)	return false;

		nIncrease = 100/m_nContinueCount;//每次增幅分数（100为满分）
		
		// 完整度
		if (nIntact >= m_nGoalScore)
		{
			nIntactCount++;
			if (nIntactCount >= m_nContinueCount)
				nIntactFlag = 1;//为1时扔锤子
			else
				m_nIntactCount = nIntactCount;
		}
		else
			m_nIntactCount = 0;

		// 相似度
		if (nSimilarity >= m_nGoalScore)
		{
			nSimilarityCount++;
			if (nSimilarityCount >= m_nContinueCount)
				nSimilarityFlag = 2;//10
			else
				m_nSimilarityCount = nSimilarityCount;
		}
		else
			m_nSimilarityCount = 0;
		
		// 稳定度
		if (nStability >= m_nGoalScore)
		{
			nStabilityCount++;
			if (nStabilityCount >= m_nContinueCount)
				nStabilityFlag = 4;//100
			else
				m_nStabilityCount = nStabilityCount;
		}
		else
			m_nStabilityCount = 0;

		nFlag = nIntactFlag | nSimilarityFlag | nStabilityFlag;
		nIndex = get_sound_effect_index(nFlag);
		if (nIndex == 0)//完整度
		{
			m_nIntactCount = 0;
			nIntactRate = 100;
		}
		else if (nIndex == 1)//相似度
		{
			m_nSimilarityCount = 0;
			nSimilarityRate = 100;
		}
		else if (nIndex == 2)//稳定度
		{
			m_nStabilityCount = 0;	
			nStabilityRate = 100;
		}
		else
		{
			nIntactRate = m_nIntactCount * nIncrease;
			nSimilarityRate = m_nSimilarityCount * nIncrease;
			nStabilityRate = m_nStabilityCount * nIncrease;
		}

		swprintf(data, L"<data><info><item name=\"intact\" score=\"%d\" flag=\"%d\" rate=\"%d\"/><item name=\"similarity\" score=\"%d\" flag=\"%d\" rate=\"%d\"/><item name=\"stability\" score=\"%d\" flag=\"%d\" rate=\"%d\"/></info></data>",
			nIntact, nIndex==0?1:0, nIntactRate, nSimilarity, nIndex==1?1:0, nSimilarityRate, nStability, nIndex==2?1:0, nStabilityRate);

		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"sound_effect", data); 

		if (bRet)
		{
// 			if (m_PassTransparentWnd != NULL)
// 			{
// 				if (m_PassTransparentWnd->m_pFlash->m_hWnd != NULL)
// 				{
// 					m_PassTransparentWnd->m_pFlash->CallFunction(request);
// 				}
// 			}
// 			if (m_PassSoftTransparentWnd != NULL)
// 			{
// 				if (m_PassSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
// 				{
// 					m_PassSoftTransparentWnd->m_pFlash->CallFunction(request);
// 				}
// 			}
			if (m_bAcrossPassFlashPlayerExist)
			{
				m_AcrossPassFlashPlayer.CallFunction(request);
			}
			if (m_bAcrossPassSoftFlashPlayerExist)
			{
				m_AcrossPassSoftFlashPlayer.CallFunction(request);
			}
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}
int Cflashktv10Wnd::get_sound_effect_index(int nSource)
{
	int nIndex = -1;
	srand((unsigned int)time((time_t *)NULL));
	if (nSource == 7)
	{
		nIndex = rand()%3;
	}
	else if (nSource == 3)
	{
		nIndex = rand()%2;
	}
	else if (nSource == 5)
	{
		nIndex = rand()%2;
		if (nIndex == 1)
			nIndex = 2;
	}
	else if (nSource == 6)
	{
		nIndex = rand()%2 + 1;
	}
	else if (nSource == 1)
	{
		nIndex = 0;
	}
	else if (nSource == 2)
	{
		nIndex = 1;
	}
	else if (nSource == 4)
	{
		nIndex = 2;
	}

	return nIndex;
}

bool  Cflashktv10Wnd::flash_message_call_across_pass_result(bool bResult)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024*10] = {0x00}, data[1024*10] = {0x00};

		if (bResult)
		{
			swprintf(data, L"<data><pageinfo pagename=\"across_pass_success\" cur_pas=\"%d\" page_title=\"挑战成功\"/></data>", m_nCurPassIndex);

			//直接组织歌曲字符串 
			bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"across_pass_success", data);
			if (!bRet)
			{
				return false;
			}
		}
		else
		{
			swprintf(data, L"<data><pageinfo pagename=\"across_pass_fail\" cur_pas=\"%d\"  page_title=\"挑战失败\"/></data>", m_nCurPassIndex);

			//直接组织歌曲字符串 
			bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"across_pass_fail", data);
			if (!bRet)
			{
				return false;
			}
		}

// 		if (m_PassTransparentWnd != NULL)
// 		{
// 			if (m_PassTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
// 		if (m_PassSoftTransparentWnd != NULL)
// 		{
// 			if (m_PassSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassSoftTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
		if (m_bAcrossPassFlashPlayerExist)
		{
			m_AcrossPassFlashPlayer.CallFunction(request);
		}
		if (m_bAcrossPassSoftFlashPlayerExist)
		{
			m_AcrossPassSoftFlashPlayer.CallFunction(request);
		}

		return bRet;
	}
	catch (...)
	{
	}

	return false;
}
bool Cflashktv10Wnd::falsh_message_call_exit_across_pass_tv()
{
	try
	{
		bool bRet = false;
		TCHAR request[1024*10] = {0x00}, data[1024*10] = {0x00};

		swprintf(data, L"<data><info name=\"exit_across_pass_tv\"/></data>", m_nCurPassIndex);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"exit_across_pass_tv", data);
		if (!bRet)
		{
			return false;
		}

// 		if (m_PassTransparentWnd != NULL)
// 		{
// 			if (m_PassTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
// 		if (m_PassSoftTransparentWnd != NULL)
// 		{
// 			if (m_PassSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
// 			{
// 				m_PassSoftTransparentWnd->m_pFlash->CallFunction(request);
// 			}
// 		}
		if (m_bAcrossPassFlashPlayerExist)
		{
			m_AcrossPassFlashPlayer.CallFunction(request);
		}
		if (m_bAcrossPassSoftFlashPlayerExist)
		{
			m_AcrossPassSoftFlashPlayer.CallFunction(request);
		}

		return bRet;
	}
	catch (...)
	{
	}

	return false;
}
/************************************************************************/
/*互动游戏*/
bool Cflashktv10Wnd::generate_active_game_encode()
{
	try
	{
		bool bRet = false;
		string_conversion string_con;
		char szUrl[256] = {0x00}, szUrlPath[256] = {0x00};

		if (wcslen(m_szActiveGameUrl) == 0)	return false;

		string_con.widechar_to_multibyte(m_szActiveGameUrl, szUrl, sizeof(szUrl));
		//根据本机ip得到全地址
		sprintf(szUrlPath, "%s%s", szUrl, m_send_room_ip);

		//图片保存路径
		swprintf(m_szPicFilePath, L"%s\\active_game_img\\active_game_encode.png", m_work_path);
		if (PathFileExists(m_szPicFilePath))
		{
			DeleteFile(m_szPicFilePath);
		}
		//生成二维码
		bRet = Generate_encode_picture(szUrlPath, m_szPicFilePath);
		if (!bRet)	return false;

		//缩放图片
		bRet = zoom_image(m_szPicFilePath, 160, 160, m_szPicFilePath, L"image/png", 0, 0);
		if (!bRet)	return false;

		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::parse_active_game_player_info(const char *pInfo)
{
	try
	{
		if (strlen(pInfo) == 0)		return false;

		//{"clientIp":"10.0.3.109","headimgurl":"http:\/\/wx.qlogo.cn\/mmopen\/cpW9WzM8pQDadJmNNyia6bpjC3w462VibNUK2hgPoRtbO7sx2iaku7icc9tPcibIiadiaoZlYdZtztWIXYZOgGg2lBtRSQsWmPtlQZW\/0","isLaunch":0,"nickname":"王文仲","open_id":"o2_wAj8KtfZyVRU1UsE89VKXErLk"}
		//json解析
		string_conversion str_conv;
		Json::Reader reader;
		Json::Value root;

		//不能解析
		if (!reader.parse(pInfo, root, false))
		{
			WriteLog(__FL__, L"json格式错误！");
			return false;
		}

		if (root.size() == 0)	return false;

		GAME_PLAYER_INFO playerInfo;
		TCHAR szTmp[1024];
		char szHeadPic[256] = {0x00};
		memset(&playerInfo, 0x00, sizeof(GAME_PLAYER_INFO));
		memset(szTmp, 0x00, sizeof(szTmp));

		string strClientIp = root["clientIp"].asString();
		str_conv.multibyte_to_widechar(strClientIp.c_str(), szTmp, sizeof(szTmp));//ip
		string strHeadImgUrl = root["headimgurl"].asString();
		str_conv.multibyte_to_widechar(strHeadImgUrl.c_str(), playerInfo.szHeadImgUrl, sizeof(playerInfo.szHeadImgUrl));//头像URL
		bool bIsLaunch = root["isLaunch"].asBool();
		playerInfo.bIsLaunch = bIsLaunch;//是否是发起人
		string strNickName = root["nickname"].asString();
		str_conv.multibyte_to_widechar(strNickName.c_str(), playerInfo.szNickName, sizeof(playerInfo.szNickName));//昵称
		string strOpenId = root["open_id"].asString();
		str_conv.multibyte_to_widechar(strOpenId.c_str(), playerInfo.szOpenId, sizeof(playerInfo.szOpenId));//唯一id
		swprintf(playerInfo.szHeadImgPath, L"%s\\active_game_img\\%s.jpg", m_work_path, playerInfo.szOpenId);//头像本地保存路径
		str_conv.widechar_to_multibyte(playerInfo.szHeadImgPath, szHeadPic, sizeof(szHeadPic));
		if (!PathFileExists(playerInfo.szHeadImgPath))
		{
			//下载微信头像图片
			//if (down(strHeadImgUrl.c_str(), szHeadPic) < 0)
			if(m_http_obj.download_file((char*)strHeadImgUrl.c_str(), playerInfo.szHeadImgPath))
			{
				//提供默认头像路径
				swprintf(playerInfo.szHeadImgPath, L"%s\\wechat_default_img\\default_head.png", m_work_path);
				WriteLog(__FL__, L"下载微信头像失败！");
			}
		}
		string strOpenTime = root["open_time"].asString();
		str_conv.multibyte_to_widechar(strOpenTime.c_str(), playerInfo.szOpenTime, sizeof(playerInfo.szOpenTime));//加入时间
		bool bIsSelf = root["isSelf"].asBool();
		playerInfo.bIsSelf = bIsSelf;//是否正在摇骰子

		m_vecGamePlayer.push_back(playerInfo);
		//向flash发送玩家信息
		bool bRet = flash_message_call_player_info();

		return true;
	}
	catch(...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_player_info(int nFlag/* = 0*/)
{
	try
	{
		bool bRet = false;
		int nSize = 0;
		TCHAR request[1024*3] = {0x00}, tmp[1024] = {0x00};
		wstring strdata = L"";
		GAME_PLAYER_INFO Info = {0x00};

		nSize = m_vecGamePlayer.size();
		if (nSize >= 6)//最多6个人参与
		{
			nSize = 6;
		}
		strdata += L"<data><info>";
		for (int i=0; i<nSize; ++i)
		{
			memset(tmp, 0x00, sizeof(tmp));
			memset(&Info, 0x00, sizeof(GAME_PLAYER_INFO));
			Info = m_vecGamePlayer[i];

			swprintf(tmp, L"<item launch=\"%s\" self=\"%s\" head_img_path=\"%s\" nick_name=\"%s\" open_id=\"%s\" open_time=\"%s\"/>", 
				Info.bIsLaunch?L"1":L"0", Info.bIsSelf?L"1":L"0", Info.szHeadImgPath, Info.szNickName, Info.szOpenId, Info.szOpenTime);

			strdata += tmp;
		}
		strdata += L"</info></data>";

		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"player_info", strdata.c_str());
		if (bRet)
		{
			if (nFlag == 0)
			{
				active_game_flash_call_function(request);
				active_game_soft_flash_call_function(request);
			}
			else if(nFlag == 1)
			{
				active_game_flash_call_function(request);
			}
			else if (nFlag == 2)
			{
				active_game_soft_flash_call_function(request);
			}
		}
		else
			return false;

		return true;
	}
	catch(...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_player_high_light(TCHAR* pInfo)
{
	try
	{
		bool bRet = false;
		int nIndex = -1;
		TCHAR request[256] = {0x00}, data[256] = {0x00};

		for (int i=0; i<m_vecGamePlayer.size(); ++i)
		{
			if (_tcscmp(m_vecGamePlayer[i].szOpenId, pInfo) == 0)
			{
				nIndex = i;
				break;
			}
		}

		if (nIndex >= 0)
		{
			swprintf(data, L"<data><info high_light=\"%d\"></info></data>", nIndex);
		}
		else
		{
			swprintf(data, L"<data><info></info></data>");
		}
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"player_high_light", data);
		if (bRet)
		{
			active_game_flash_call_function(request);
			active_game_soft_flash_call_function(request);
		}
		else
			return false;

		return true;
	}
	catch(...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::get_dice_result_sound(int nDice, TCHAR *pResult)
{
	try
	{
		int nRand = 0;
		switch(nDice)
		{
		case 7:
			{
				//加酒
				_tcscpy(pResult, L"加酒");
			}
			break;
		case 8:
			{
				//加酒
				_tcscpy(pResult, L"喝一半");
			}
			break;
		case 9:
			{
				//加酒
				_tcscpy(pResult, L"喝光");
			}
			break;
		default:
			{
				srand((unsigned int)time((time_t *)NULL));
				nRand = rand()%3;
				switch(nRand)
				{
				case 0:
					{
						//加酒
						_tcscpy(pResult, L"没事");
					}
					break;
				case 1:
					{
						//加酒
						_tcscpy(pResult, L"下一位");
					}
					break;
				case 2:
					{
						//加酒
						_tcscpy(pResult, L"放你一马");
					}
					break;
				default:
					{
						//加酒
						_tcscpy(pResult, L"下一位");
					}
					break;
				}
			}
			break;
		}
		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_dice_number(int nNumber1, int nNumber2)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00}, temp[64] = {0x00};

		if (nNumber1+nNumber2>=2 && nNumber1+nNumber2<=12)
		{
			get_dice_result_sound(nNumber1+nNumber2, temp);
			swprintf(data, L"<data><info dice_number=\"%d,%d\" result=\"%s\"/></data>", nNumber1, nNumber2, temp);
		}
		else
		{
			swprintf(data, L"<data><info dice_number=\"2,3\" result=\"下一位\"/></data>");
		}
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"dice_number", data);
		if (bRet)
		{
			active_game_flash_call_function(request);
			active_game_soft_flash_call_function(request);
		}
		else
			return false;

		return true;
	}
	catch(...)
	{
	}
	return false;
}

bool Cflashktv10Wnd::active_game_flash_call_function(TCHAR *request)
{
	try
	{
		if (wcslen(request) == 0)	return false;

		if (m_active_game_flash_player_exist)
		{
			m_active_game_flash_player.CallFunction(request);
			return true;
		}
	}
	catch(...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::active_game_soft_flash_call_function(TCHAR *request)
{
	try
	{
		if (wcslen(request) == 0)	return false;

		if (m_soft_decode_window_exist && m_active_game_soft_flash_player_exist)
		{
			m_active_game_soft_flash_player.CallFunction(request);
			return true;
		}
	}
	catch(...)
	{
	}
	return false;
}

bool Cflashktv10Wnd::flash_message_call_active_game_tv(int nFlag/* = 0*/)
{
	try
	{
		bool bRet = false;
		TCHAR request[256] = {0x00}, data[256] = {0x00};
		
		swprintf(data, L"<data><info name=\"active_game_tv\" pic_path=\"%s\"></info></data>", m_szPicFilePath);

		//直接组织歌曲字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"active_game_tv", data);
		if (!bRet)	return false;

		if (nFlag == 0)
		{
			active_game_flash_call_function(request);
			active_game_soft_flash_call_function(request);
		}
		else if (nFlag == 1)
		{
			bRet = active_game_flash_call_function(request);
		}
		else if (nFlag == 2)
		{
			bRet = active_game_soft_flash_call_function(request);
		}

		return true;
	}
	catch (...)
	{
	}
	return false;
}
//////

int Cflashktv10Wnd::parse_video_show_data(const TCHAR* local_path)
{
	//json解析文件
	Json::Reader reader;
	Json::Value root;
	string_conversion str_con;
	TCHAR args[2048*10] = {0x00};
	TCHAR request[2048*10] = {0x00};
	char local_dir[MAX_PATH] = {0x00};
	char local[MAX_PATH] = {0x00};

	ifstream ifs;
	ifs.open(local_path);

	//不能解析
	if (!reader.parse(ifs, root, false))
	{
		WriteLog(__FL__, L"爱秀直播:解析json数据错误");
		return 1; //数据结构性不完整
	}

	int nCount = root.size();

	/*
	if (m_st_video_show_vec.size() > 0)
	{
		for (int i = 0; i < m_st_video_show_vec.size(); i++)
		{
			delete m_st_video_show_vec[i];
			m_st_video_show_vec[i] = NULL;
		}
	}
	*/

	int page_count = nCount/m_video_show_count_page;
	if (nCount%m_video_show_count_page > 0)
		page_count++;

	show_row_and_page_count(L"true", nCount, page_count, m_video_show_current_page);

	//sprintf(local, "%s", m_work_path);
	str_con.widechar_to_multibyte(m_work_path, local_dir, sizeof(local_dir));
	strcat(local_dir, "\\video_show_pic");

	vector<ST_VIDEO_SHOW*> video_show_tmp_vec;
	video_show_tmp_vec.clear();

	TCHAR szUid[MAX_PATH] = {0x00};
	for (int i = 0; i < nCount; i++)
	{
		string struid = root[i]["uid"].asString();
		str_con.utf8_to_widechar(struid.c_str(), szUid, sizeof(szUid));

		WriteLog(__FL__, L"爱秀直播:开始添加主播，id = %s", szUid);

		//检测是否存在
		if (m_st_video_show_vec.size() > 0)
		{
			bool bflag = false;
			for (int m = 0; m < m_st_video_show_vec.size(); m++)
			{
				if (_tcscmp(m_st_video_show_vec[m]->uid, szUid) == 0)
				{
					video_show_tmp_vec.push_back(m_st_video_show_vec[m]);
					m_st_video_show_vec.erase(m_st_video_show_vec.begin() + m);
					bflag = true;
					break;
				}
			}
			if (bflag)	continue;
		}

		ST_VIDEO_SHOW *vs = new ST_VIDEO_SHOW();
		_tcscpy(vs->uid, szUid);

		string strPicPath = root[i]["picpath"].asString().c_str();
		sprintf(local, "%s\\%s.jpg", local_dir, struid.c_str());

		TCHAR szLocal[MAX_PATH] = {0x00};
		str_con.multibyte_to_widechar(local, szLocal, sizeof(szLocal));

		TCHAR szUrl[1024] = {0x00};
		str_con.multibyte_to_widechar(strPicPath.c_str(), szUrl, sizeof(szUrl));
		//WriteLog(__FL__, L"爱秀直播主播头像下载地址:%s", szUrl);
		m_http_obj.download_file((char*)strPicPath.c_str(), szLocal);

		str_con.multibyte_to_widechar(local, vs->picpath, sizeof(vs->picpath));

		string strTitle = root[i]["title"].asString();
		strTitle = str_con.Encode((const unsigned char*)strTitle.c_str(), strTitle.length());
		str_con.multibyte_to_widechar(strTitle.c_str(), vs->title, sizeof(vs->title));

		string strToproomid = root[i]["toproomid"].asString();
		str_con.utf8_to_widechar(strToproomid.c_str(), vs->toproomid, sizeof(vs->toproomid));

		string strRoomid = root[i]["roomid"].asString();
		str_con.utf8_to_widechar(strRoomid.c_str(), vs->roomid, sizeof(vs->roomid));

		string strPopularity = root[i]["popularity"].asString();
		str_con.utf8_to_widechar(strPopularity.c_str(), vs->popularity, sizeof(vs->popularity));

		string strShowRoomID = root[i]["showroomid"].asString();
		str_con.utf8_to_widechar(strShowRoomID.c_str(), vs->showroomid, sizeof(vs->showroomid));

		string strChannelName = root[i]["channelname"].asString();
		str_con.utf8_to_widechar(strChannelName.c_str(), vs->channelname, sizeof(vs->channelname));

		video_show_tmp_vec.push_back(vs);
	}

	if (m_st_video_show_vec.size() > 0)
	{
		for (int m = 0; m < m_st_video_show_vec.size(); m++)
		{
			delete m_st_video_show_vec[m];
			m_st_video_show_vec[m] = NULL;
		}
	}

	m_st_video_show_vec.swap(video_show_tmp_vec);

	ifs.close();

	bool result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"video_show", make_video_show_flash_list(m_video_show_current_page).c_str());
	if (result)
	{
		try
		{
			int nRet = flash_player_call_function(request);
		}
		catch(...)
		{

		}
	}
	return 0;
}

wstring Cflashktv10Wnd::make_video_show_flash_list(const int curr_page)
{
	wstring strData = L"<data>";
	TCHAR szItem[1024] = {0x00};
	int nCount = m_st_video_show_vec.size(); //获得总个数
	if (nCount > 0) //代表有数据
	{
		//计算共多少页
		int page_count = nCount/m_video_show_count_page;
		if (nCount%m_video_show_count_page > 0)
			page_count++;
		int begin_index = 0, end_index = 0;
		/*******************************获得上一页*****************************************/
		switch(curr_page)
		{
		case 1: //第一页
			{
				begin_index = (page_count - 1) * m_video_show_count_page; //获得到最后一页数据
				end_index = nCount - 1;
			}
			break;
		default:
			{
				begin_index = (curr_page - 2) * m_video_show_count_page; //获得到上一页数据
				end_index = begin_index + m_video_show_count_page -1;
				if (end_index >= nCount)
				{
					end_index = nCount - 1;
				}
			}
			break;
		}
		strData += L"<pre_list>";
		for (int i = begin_index; i <= end_index; i++)
		{
			swprintf(szItem, L"<item picpath=\"%s\" title=\"%s\" popularity=\"%s\" channelname=\"%s\" showroomid=\"%s\"/>", 
				m_st_video_show_vec[i]->picpath, m_st_video_show_vec[i]->title, m_st_video_show_vec[i]->popularity, 
				m_st_video_show_vec[i]->channelname, m_st_video_show_vec[i]->showroomid);
			strData += szItem;
		}
		strData += L"</pre_list><cur_list>";
		/*******************************获得当前页*****************************************/
		switch(curr_page)
		{
		case 1: //第一页
			{
				begin_index = 0;
				if (nCount <= m_video_show_count_page)
				{
					end_index = nCount - 1;
				}else
				{
					end_index = begin_index + m_video_show_count_page;
				}
			}
			break;
		default:
			{
				begin_index = (curr_page - 1) * m_video_show_count_page; //获得到当前页第一个索引
				end_index = begin_index + m_video_show_count_page - 1;
				if (end_index >= nCount)
				{
					end_index = nCount - 1;
				}
			}
			break;
		}
		
		for (int i = begin_index; i <= end_index; i++)
		{
			swprintf(szItem, L"<item picpath=\"%s\" title=\"%s\" popularity=\"%s\" channelname=\"%s\" showroomid=\"%s\"/>", 
				m_st_video_show_vec[i]->picpath, m_st_video_show_vec[i]->title, m_st_video_show_vec[i]->popularity, 
				m_st_video_show_vec[i]->channelname, m_st_video_show_vec[i]->showroomid);
			strData += szItem;
		}

		strData += L"</cur_list><next_list>";
		/*******************************获得下一页*****************************************/
		if (curr_page == page_count) //如果当前页等于最后一页
		{
			begin_index = 0;
			if (nCount <= m_video_show_count_page)
			{
				end_index = nCount - 1;
			}else
			{
				end_index = m_video_show_count_page - 1;
			}

		}else
		{
			begin_index = curr_page * m_video_show_count_page; //获得到当前页第一个索引
			end_index = begin_index + m_video_show_count_page - 1;
			if (end_index >= nCount)
			{
				end_index = nCount -1;
			}
		}

		for (int i = begin_index; i <= end_index; i++)
		{
			swprintf(szItem, L"<item picpath=\"%s\" title=\"%s\" popularity=\"%s\" channelname=\"%s\" showroomid=\"%s\"/>", 
				m_st_video_show_vec[i]->picpath, m_st_video_show_vec[i]->title, m_st_video_show_vec[i]->popularity, 
				m_st_video_show_vec[i]->channelname, m_st_video_show_vec[i]->showroomid);
			strData += szItem;
		}

		strData += L"</next_list>";
	}else{
		strData = L"<pre_list></pre_list><cur_list></cur_list><next_list></next_list>";
	}
	strData += L"</data>";
	return strData;
}

void Cflashktv10Wnd::flash_message_call_listen_know_song(int args)
{
	//发送消息给电视端初始化
	TCHAR data[2048] = {0x00};
	TCHAR command[256] = {0x00};
	TCHAR request[1024];

	m_iCurrent_pass = 0;

	if (m_listen_reward_vec.size() == m_nListenPassCount)
	{
		swprintf(data,L"<data><info time=\"%d\"/></data>", m_iCount_down);
		_tcscpy(command, L"listen_time");

		bool result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
		if (result)
		{
			//发送给点歌系统端
			flash_player_call_function(request);

			if (m_listen_flash_page_tv_exist && m_inter_screen_exist && args == 1)
			{
				m_listen_flash_page_tv.ShowWindow(SW_SHOW);
				m_listen_flash_page_tv.BringWindowToTop();
			}
			if (m_listen_flash_page_tv_soft_exist && m_use_soft_active_flash && args == 0)
			{
				m_listen_flash_page_tv_soft.ShowWindow(SW_SHOW);
				m_listen_flash_page_tv_soft.BringWindowToTop();
			}
		}
	}	
}

void Cflashktv10Wnd::listen_flash_call_function(const TCHAR *request)
{
	try
	{
		if (m_inter_screen_exist)
		{
			m_listen_flash_page_tv.CallFunction(request);
		}
	}	
	catch (COleDispatchException* ex)
	{
		TCHAR   szCause[255];
		CString strFormatted;

		ex->GetErrorMessage(szCause, 255);
		strFormatted = "The program exited because of this error: ";
		strFormatted += szCause;
		//AfxMessageBox(strFormatted);
	}
}
void Cflashktv10Wnd::listen_flash_soft_call_function(const TCHAR *request)
{
	try
	{
		if (m_listen_flash_page_tv_soft_exist && m_use_soft_active_flash)
		{
			m_listen_flash_page_tv_soft.CallFunction(request);
		}
	}	
	catch (COleDispatchException* ex)
	{
		TCHAR   szCause[255];
		CString strFormatted;

		ex->GetErrorMessage(szCause, 255);
		strFormatted = "The program exited because of this error: ";
		strFormatted += szCause;
		AfxMessageBox(strFormatted);
	}
}
bool Cflashktv10Wnd::picture_mv_data_to_flash(const char *data)
{
	Json::Reader reader;
	Json::Value json_root;
	string_conversion string_conv;
	if (!reader.parse(data, json_root, false))
	{
		return false; //载入json文件失败
	}

	ST_PICTURE_MV *sp = new ST_PICTURE_MV();

	//歌曲信息
	if (json_root.isMember("song"))
	{
		TCHAR szSongID[MAX_PATH] = {0x00};
		string_conv.multibyte_to_widechar(json_root["song"].asString().c_str(), szSongID, sizeof(szSongID));
		get_song_info_by_id(szSongID, sp->songInfo, PLAY_SONG_TYPE_SELECT_SONG);
		sp->songInfo.set_flash_page_code(page_picture_mv);
	}

	//是否优先
	if (json_root.isMember("type"))
	{
		sp->priority = json_root["type"].asInt();
	}

	/*//删除服务器照片路径
	if (json_root.isMember("delPicUrl"))
	{
		string_conv.multibyte_to_widechar(json_root["delPicUrl"].asString().c_str(), sp->callDelUrl, sizeof(sp->callDelUrl));
	}//////////////*/

	//模板
	if (json_root.isMember("itemplate"))
	{
		sp->itemplate = atoi(json_root["itemplate"].asString().c_str());
	}else{
		sp->itemplate = 0;
	}

	//照片数组，下载后插入到结构体数组中
	if (json_root.isMember("imagesUrl"))
	{
		sp->imageInfoVec.clear();
		Json::Value json_image = json_root["imagesUrl"];
		int iCount = json_image.size();
		for (int i = 0; i < iCount; i++)
		{
			char szLocal[MAX_PATH] = {0x00};
			TCHAR szwLocal[MAX_PATH] = {0x00};
			const char *szGuid = newGUID();
			TCHAR szwGuid[MAX_PATH] = {0x00};

			string_conv.multibyte_to_widechar(szGuid, szwGuid, sizeof(szwGuid));
			swprintf(szwLocal, L"%s\\picture_mv\\%s.jpg", m_work_path, szwGuid);
			string_conv.widechar_to_multibyte(szwLocal, szLocal, sizeof(szLocal));
			if (PathFileExists(szwLocal))
			{
				DeleteFile(szwLocal);
			}

			CExifTags exif;
			EXIFINFO exifInfo;

			TCHAR szLocalFile[MAX_PATH] = {0x00};
			string_conv.multibyte_to_widechar(szLocal, szLocalFile, sizeof(szLocalFile));
			//if (down(json_image[i].asString().c_str(), szLocal) == 0)
			if(m_http_obj.download_file((char*)json_image[i].asString().c_str(), szLocalFile) == 0)
			{
				Image_Info imageInfo;
				TCHAR szwLocal[MAX_PATH] = {0x00};
				string_conv.multibyte_to_widechar(szLocal, szwLocal, sizeof(szwLocal));
				ZeroMemory(&exifInfo, sizeof(EXIFINFO));
				exif.GetExifRead(szwLocal, &exifInfo);

				TCHAR *szSuffix = _tcsrchr(szwLocal, '.');
				CString strFormat = L"";
				if (_tcscmp(szSuffix, L".jpg") == 0 || _tcscmp(szSuffix, L".jpeg") == 0)
				{
					strFormat = _T("image/jpeg");
				}
				else if (_tcscmp(szSuffix, L".png") == 0)
				{
					strFormat = _T("image/png");
				}
				else if (_tcscmp(szSuffix, L".bmp") == 0)
				{
					strFormat = _T("image/bmp");
				}
				else if (_tcscmp(szSuffix, L".gif") == 0)
				{
					strFormat = _T("image/gif");
				}
				else if (_tcscmp(szSuffix, L".tif") == 0)
				{
					strFormat = _T("image/tiff");
				}
				else
				{
					strFormat = _T("image/jpeg");
				}
				if (exifInfo.Height > 720)
				{
					zoom_image(szwLocal,exifInfo.Width/((float)exifInfo.Height/720),720,szwLocal, strFormat.GetBuffer(), 0, 0);
				}

				imageInfo.imageUrl = szwLocal;
				imageInfo.Orientation = exifInfo.Orientation;

				sp->imageInfoVec.push_back(imageInfo);
			}
		}
	}

	//删除服务器照片路径
	if (json_root.isMember("delPicUrl"))
	{
		//string_conv.multibyte_to_widechar(json_root["delPicUrl"].asString().c_str(), sp->callDelUrl, sizeof(sp->callDelUrl));

		char szUrl[MAX_PATH] = {0x00};
		strcpy(szUrl, json_root["delPicUrl"].asString().c_str());
		//getUrl(szUrl);
		m_http_obj.download_data(szUrl, NULL, 0);
	}

	sp->guid = newGUID(); //歌曲的guid

	m_bInPageVideo = false;

	if (sp->priority == 1) //立即播放
	{
		m_st_picture_mv_vec.insert(m_st_picture_mv_vec.begin(), sp);
		//得到目前系统所处的状态
		PLAYER_PLAY_STATE player_state = m_video_play_manager.get_player_cur_state();
		//如果正在播放用户点的歌曲，那么把该歌曲放到已选歌曲中
		bool bRet = m_video_play_manager.add_select_song(sp->songInfo, true);
		if (!bRet)
		{
			return false;
		}
		//改变播放器的状态
		bRet = m_video_play_manager.set_player_next_state(PLAY_SONG_STATE);
		//更新选择的歌曲数目
		bRet = update_select_song_count();
		//切歌
		flash_message_call_function(SONG_NEXT);
	}
	else
	{
		m_st_picture_mv_vec.push_back(sp);
		//插入到已选
		play_or_insert_select_list(sp->songInfo, false);
	}

	//改变显示颜色，必须先把歌曲插入已选中，然后在改变颜色，因为涉及到刷屏
	refresh_screen_list();
	//重新显示上下首歌名
	show_song_name();
	return true;
}

void Cflashktv10Wnd::picture_mv_play_song(song_info* songinfo, int type)
{
	TCHAR data[1024*20] = {0x00};
	TCHAR item[2048] = {0x00};
	TCHAR command[256] = {0x00};
	TCHAR request[1024*20];

	if (m_st_picture_mv_vec.size() == 0)
		return;

	//当前播放歌曲的guid
	m_picture_mv_curr_guid = m_st_picture_mv_vec.at(0)->guid;

	_tcscat(data, L"<data>");
	swprintf(item,L"<template flag=\"%d\"/>", m_st_picture_mv_vec.at(0)->itemplate);
	_tcscat(data, item);
	for (int i = 0; i < m_st_picture_mv_vec.at(0)->imageInfoVec.size(); i++)
	{
		swprintf(item,L"<item path=\"%s\" orientation=\"%d\"/>", m_st_picture_mv_vec.at(0)->imageInfoVec[i].imageUrl.c_str(), 
													m_st_picture_mv_vec.at(0)->imageInfoVec[i].Orientation);
		_tcscat(data, item);
	}
	_tcscat(data, L"</data>");

	//发送码值到前端
	_tcscpy(command, L"picture_mv_image"); //照片mv接口
	bool result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
	if (result)
	{
		switch(type)
		{
		case 0:
			{
				if (m_picture_mv_wind_exist)
				{
					m_picture_mv_wind.CallFunction(request);
				}
				if (m_picture_mv_wind_soft_exist && m_use_soft_active_flash)
				{
					m_picture_mv_wind_soft.CallFunction(request);
				}
			}
			break;
		case 1:
			{
				if (m_picture_mv_wind_exist)
				{
					m_picture_mv_wind.CallFunction(request);
				}
			}
			break;
		case 2:
			{
				if (m_picture_mv_wind_soft_exist && m_use_soft_active_flash)
				{
					m_picture_mv_wind_soft.CallFunction(request);
				}
			}
			break;
		default:
			{
				if (m_picture_mv_wind_exist)
				{
					m_picture_mv_wind.CallFunction(request);
				}
				if (m_picture_mv_wind_soft_exist && m_use_soft_active_flash)
				{
					m_picture_mv_wind_soft.CallFunction(request);
				}
			}
		}

	}
}

//创建照片mv的窗口函数
long Cflashktv10Wnd::create_picture_mv_wnd()
{
	//挑战大咖设置为false
	m_b_challenging = false;
	if (m_inter_screen_exist && m_StarTransparentWnd != NULL)
	{
		m_StarTransparentWnd->MoveWindow(0,0,0,0);
		m_StarTransparentWnd->ShowFlashWindow(SW_HIDE);
	}
	if (m_soft_decode_window_exist && m_use_soft_active_flash && m_StarSoftTransparentWnd != NULL)
	{
		m_StarSoftTransparentWnd->MoveWindow(0,0,0,0);
		m_StarSoftTransparentWnd->ShowFlashWindow(SW_HIDE);
	}
	destroy_picture_mv_wnd();
	//如果使用软解并打开电视端的flash
	if (m_soft_decode_window_exist && m_use_soft_active_flash && !m_picture_mv_wind_soft_exist)
	{
		m_picture_mv_wind_soft_exist = m_picture_mv_wind_soft.Create(NULL,WS_CHILD,CRect(0,0,m_sencond_display_width,m_sencond_display_height),&m_soft_decode_window,PICTURE_MV_TV_SOFT_ID);
		if (m_picture_mv_wind_soft_exist)
		{
			TCHAR picture_mv_path[256];
			memset(picture_mv_path,0x0,sizeof(picture_mv_path));

			TCHAR path[256];
			memset(path,0x0,sizeof(path));
			if (m_inter_screen_exist)
				swprintf(picture_mv_path, L"%s\\photo_album_interface\\Main1.swf", m_work_path);
			else
				swprintf(picture_mv_path, L"%s\\photo_album_interface\\Main.swf", m_work_path);

			if (PathFileExists(picture_mv_path))
			{										
				m_picture_mv_wind_soft.LoadMovie(0, picture_mv_path);
				m_picture_mv_wind_soft.Play();
				m_picture_mv_wind_soft.ShowWindow(SW_SHOW);
				m_picture_mv_wind_soft.put_ScaleMode(2);
				m_picture_mv_wind_soft.BringWindowToTop();
			}
		}
	}
	//如果启用了场景屏
	if (m_inter_screen_exist && !m_picture_mv_wind_exist)
	{
		////照片mv -- 电视上显示的flash窗口
		m_picture_mv_wind_exist = m_picture_mv_wind.Create(NULL,WS_CHILD,m_rtRelativeActivityWnd,&m_inter_screen_window,PICTURE_MV_TV_ID);
		if (m_picture_mv_wind_exist)
		{
			TCHAR picture_mv_path[256];

			memset(picture_mv_path,0x0,sizeof(picture_mv_path));

			swprintf(picture_mv_path, L"%s\\photo_album_interface\\Main.swf", m_work_path);
			if (PathFileExists(picture_mv_path))
			{
				m_picture_mv_wind.LoadMovie(0, picture_mv_path);
				m_picture_mv_wind.Play();
				m_picture_mv_wind.ShowWindow(SW_SHOW);
				m_picture_mv_wind.put_ScaleMode(2);
				m_picture_mv_wind.BringWindowToTop();
			}
		}
// 		if (m_activity_wnd_full_screen)
// 		{
// 			if (m_show_activity_wnd == 0 || m_inter_screen_mode == 0 || m_inter_screen_mode == 1)
// 			{0
// 				m_master_show_window.MoveWindow(0, 0, m_rtAbsoluteActivityWnd.Width(), m_rtAbsoluteActivityWnd.Height());
// 			}
// 			else
// 			{
// 				m_slave_show_window.MoveWindow(0, 0, m_rtAbsoluteActivityWnd.Width(), m_rtAbsoluteActivityWnd.Height());
// 			}
// 		}
	}

	return 0;
}

//销毁照片mv窗口函数
long Cflashktv10Wnd::destroy_picture_mv_wnd()
{
	//如果创建了 ， 则销毁
	if (m_picture_mv_wind_soft_exist)
	{
		m_picture_mv_wind_soft.DestroyWindow();
		m_picture_mv_wind_soft_exist = false;
	}

	//如果创建了 ， 则销毁
	if (m_picture_mv_wind_exist)
	{
		m_picture_mv_wind.DestroyWindow();
		m_picture_mv_wind_exist = false;
		//全屏显示flash时，还原视频窗口位置
		if (m_activity_wnd_full_screen)
		{
			if (m_show_activity_wnd == 0 || m_inter_screen_mode == 0 || m_inter_screen_mode == 1)
			{
				m_master_show_window.MoveWindow(m_rt_master.left, m_rt_master.top, m_rt_master.Width(), m_rt_master.Height());
			}
			else
			{
				m_slave_show_window.MoveWindow(m_rt_slave.left, m_rt_slave.top, m_rt_slave.Width(), m_rt_slave.Height());
			}
		}
	}
	if (m_picture_mv_wind_soft_exist || m_picture_mv_wind_exist)
	{
		m_bPictureMvFlashFinish = false;
		m_nFlashFinishCnt = 0;
		m_nCurPageCode = 0;
	}
	return 0;
}
void Cflashktv10Wnd::CreateAxBrowse(CString csUrl)
{
	CRect rc(0,0,0,0);
	CWnd *pParentWnd = NULL;
#ifdef VIDEO_SHOW_FULL_SCREEN
	if (m_soft_decode_window_exist)
	{
		rc = m_rt_soft_activity;
		pParentWnd = &m_soft_decode_window;
	}
	else if (m_inter_screen_exist)
	{
		rc = m_rtAbsoluteActivityWnd;
		pParentWnd = &m_inter_screen_window;
	}
#endif // VIDEO_SHOW_FULL_SCREEN

	m_pBrowseWnd = new CWnd;
	m_video_show_exist = m_pBrowseWnd->CreateEx(WS_EX_CLIENTEDGE,
		AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1),NULL), 
		_T("MyPopupWindow"),WS_POPUP | WS_VISIBLE , rc, pParentWnd, NULL, NULL);
	if (!m_video_show_exist)
	{
		DWORD dwError = GetLastError();
		WriteLog(__FL__, L"创建浏览器失败,错误码【%ld】", dwError);
		return;
	}
	m_pBrowseWnd->ShowWindow(SW_SHOW);

	CString csRet, csParam;
	csParam.Format(_T("%d@@%s"), m_pBrowseWnd->m_hWnd, csUrl);
	csRet = m_ocxShAxBrowse.Func(_T("init"), csParam);
}

void Cflashktv10Wnd::DestroyAxBrowse()
{
	if (m_video_show_exist)
	{
		m_pBrowseWnd->DestroyWindow();
		m_video_show_exist = FALSE;
	}
}

void Cflashktv10Wnd::SetAxBrowseUrl(CString csUrl)
{
	if (!m_video_show_exist)
	{
		CreateAxBrowse(csUrl);
	}
	else
	{
		CString csRet(_T(""));
		csRet = m_ocxShAxBrowse.Func(_T("SetUrl"), csUrl);
	}
}

UINT Cflashktv10Wnd::lyrics_Callback(PLAYLYRICSSTATE modeObj)
{
	string_conversion string_conn;
	Cflashktv10Wnd *pWnd = (Cflashktv10Wnd*)modeObj.pWnd;
	TCHAR temp[2048];

	memset(temp, 0x00, sizeof(temp));
	string_conn.multibyte_to_widechar(modeObj.content.c_str(), temp, sizeof(temp));

	TCHAR command[256] = {0x00};
	TCHAR request[2048];
	TCHAR data[1024] = {0x00};

	//处理歌词
	switch (modeObj.elm)
	{
	case LYRICS_MODE_SHOW:	//显示歌词
		{
			_tcscpy(command, L"show_lyrics"); //显示歌词
			swprintf(data,L"<data><info data=\"%s\" location=\"%d\" fontcolor=\"0Xffffff\" strokecolor=\"0X000000\"/></data>", temp, modeObj.location ? 1:0);
			bool result = pWnd->m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
			if (result)
			{
				if (pWnd->m_picture_mv_wind_exist)
				{
					pWnd->m_picture_mv_wind.CallFunction(request);
				}
				if (pWnd->m_picture_mv_wind_soft_exist && pWnd->m_use_soft_active_flash)
				{
					pWnd->m_picture_mv_wind_soft.CallFunction(request);
				}
			}
		}
		break;
	case LYRICS_MODE_BEGIN:	//开唱歌词
		{
			_tcscpy(command, L"sing_lyrics"); //开始唱歌词
			swprintf(data,L"<data><info data=\"%s\" location=\"%d\" fontcolor=\"0X0000CD\" strokecolor=\"0Xffffff\"/></data>", temp, modeObj.location ? 1:0);
			bool result = pWnd->m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
			if (result)
			{
				if (pWnd->m_picture_mv_wind_exist)
				{
					pWnd->m_picture_mv_wind.CallFunction(request);
				}
				if (pWnd->m_picture_mv_wind_soft_exist && pWnd->m_use_soft_active_flash)
				{
					pWnd->m_picture_mv_wind_soft.CallFunction(request);
				}
			}
		}
		break;
	case LYRICS_MODE_HIDE:	//隐藏歌词
		{
			_tcscpy(command, L"delete_lyrics"); //删除歌词
			swprintf(data,L"<data><info location=\"%d\"/></data>", modeObj.location ? 1:0);
			bool result = pWnd->m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),command,data);
			if (result)
			{
				if (pWnd->m_picture_mv_wind_exist)
				{
					pWnd->m_picture_mv_wind.CallFunction(request);
				}
				if (pWnd->m_picture_mv_wind_soft_exist && pWnd->m_use_soft_active_flash)
				{
					pWnd->m_picture_mv_wind_soft.CallFunction(request);
				}			}
		}
		break;
	}
	return 0;
}

bool Cflashktv10Wnd::flash_message_call_flash_volume(int nPageCode)
{
	try
	{
		bool bRet = false;
		int music_volume = 0, microphone_volume = 0, tune = 0;
		TCHAR request[256] = {0x00}, data[256] = {0x00};
		TCHAR mute_request[256] = {0x00}, mute_data[256] = {0x00};
		bool bFlag = false;//哪个flash播放声音标志

		if (m_player_manager.is_mute())
		{
			music_volume = 0;
		}
		else
		{
			m_player_manager.get_volume_tune(music_volume, microphone_volume, tune);
		}
		swprintf(mute_data, L"<data><info music_volume=\"0\"/></data>");
		bRet = m_flash_manage.make_request(mute_request, sizeof(mute_request)/sizeof(TCHAR), L"flash_volume", mute_data);

		swprintf(data, L"<data><info music_volume=\"%f\"/></data>", music_volume*0.01);
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"flash_volume", data);
		if (bRet)
		{
			//PC 端flash音量
			bRet = flash_player_call_function(request);

			switch(nPageCode)
			{
			case page_across_pass:
				{
// 					if (m_PassTransparentWnd != NULL)
// 					{
// 						if (m_PassTransparentWnd->m_pFlash->m_hWnd != NULL)
// 						{
// 							m_PassTransparentWnd->m_pFlash->CallFunction(request);
//							bFlag = true;
// 						}
// 					}
// 					if (m_PassSoftTransparentWnd != NULL)
// 					{
// 						if (m_PassSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
// 						{
// 							if (!bFlag)
// 								m_PassSoftTransparentWnd->m_pFlash->CallFunction(request);
// 							else
// 								m_PassSoftTransparentWnd->m_pFlash->CallFunction(mute_request);
// 						}
// 					}
					if (m_bAcrossPassFlashPlayerExist)
					{
						m_AcrossPassFlashPlayer.CallFunction(request);
						bFlag = true;
					}
					if (m_bAcrossPassSoftFlashPlayerExist)
					{
						if (!bFlag)
							m_AcrossPassSoftFlashPlayer.CallFunction(request);
						else
							m_AcrossPassSoftFlashPlayer.CallFunction(mute_request);
					}
				}
				break;
			case page_listen_knowledge_song:
				{
					if (m_inter_screen_exist)
					{
						m_listen_flash_page_tv.CallFunction(request);
						bFlag = true;
					}
					if (m_listen_flash_page_tv_soft_exist && m_use_soft_active_flash)
					{
						if (!bFlag)
							m_listen_flash_page_tv_soft.CallFunction(request);
						else
							m_listen_flash_page_tv_soft.CallFunction(mute_request);
					}
				}
				break;
			case page_challenge_star:
				{
					if (m_StarTransparentWnd != NULL)
					{
						if (m_StarTransparentWnd->m_pFlash->m_hWnd != NULL)
						{
							m_StarTransparentWnd->m_pFlash->CallFunction(request);
							bFlag = true;
						}
					}
					if (m_StarSoftTransparentWnd != NULL)
					{
						if (m_StarSoftTransparentWnd->m_pFlash->m_hWnd != NULL)
						{
							if (!bFlag)
								m_StarSoftTransparentWnd->m_pFlash->CallFunction(request);
							else
								m_StarSoftTransparentWnd->m_pFlash->CallFunction(mute_request);
						}
					}
				}
				break;
			case page_picture_mv:
				{
					if (m_picture_mv_wind_exist)
					{
						m_picture_mv_wind.CallFunction(request);
						bFlag = true;
					}
					if (m_picture_mv_wind_soft_exist && m_use_soft_active_flash)
					{
						if (!bFlag)
							m_picture_mv_wind_soft.CallFunction(request);
						else
							m_picture_mv_wind_soft.CallFunction(mute_request);
					}
				}
				break;
			case page_active_game:
				{
					if (m_active_game_flash_player_exist)
					{
						m_active_game_flash_player.CallFunction(request);
						bFlag = true;
					}
					if (m_soft_decode_window_exist && m_active_game_soft_flash_player_exist)
					{
						if (!bFlag)
							m_active_game_soft_flash_player.CallFunction(request);
						else
							m_active_game_soft_flash_player.CallFunction(mute_request);
					}
				}
				break;
			default:
				break;
			}
		}
		return bRet;
	}
	catch(...)
	{
	}
	return false;
}

bool Cflashktv10Wnd::create_listen_song()
{
	//关闭视频
	m_player_manager.close_video_file();
	if (m_soft_decode_window_exist && m_use_soft_active_flash)
	{
		if (m_StarSoftTransparentWnd != NULL)
		{
			m_StarSoftTransparentWnd->MoveWindow(0,0,0,0);
			m_StarSoftTransparentWnd->ShowFlashWindow(SW_HIDE);
		}
		////听音识曲 - - 软解电视上的flash显示
		UINT nFlashId = 0;
		TCHAR path[256];
		memset(path,0x0,sizeof(path));

		if (m_inter_screen_exist)
			swprintf(path, L"%s\\sound_hound_interface\\Main1.swf", m_work_path);
		else
			swprintf(path, L"%s\\sound_hound_interface\\Main.swf", m_work_path);
		m_listen_flash_page_tv_soft_exist = m_listen_flash_page_tv_soft.Create(NULL,WS_CHILD,CRect(0,0,m_sencond_display_width,m_sencond_display_height),&m_soft_decode_window,ACTIVE_GAME_SOFT_PLAYER_ID);
		if (m_listen_flash_page_tv_soft_exist)
		{
			if (PathFileExists(path))
			{
				m_listen_flash_page_tv_soft.LoadMovie(0, path);
				m_listen_flash_page_tv_soft.ShowWindow(SW_SHOW);
				m_listen_flash_page_tv_soft.put_ScaleMode(2);
				m_listen_flash_page_tv_soft.BringWindowToTop();
			}
		}
	}
	if (m_inter_screen_exist)
	{
		if (m_StarTransparentWnd != NULL)
		{
			m_StarTransparentWnd->MoveWindow(0,0,0,0);
			m_StarTransparentWnd->ShowFlashWindow(SW_HIDE);
		}
		////听音识曲- - 场景屏上的flash显示
		m_listen_flash_page_tv_exist = m_listen_flash_page_tv.Create(NULL,WS_CHILD,m_rtRelativeActivityWnd,&m_inter_screen_window,ACTIVE_GAME_PLAYER_ID);
		if (m_listen_flash_page_tv_exist)
		{
			TCHAR path[256];
			memset(path,0x0,sizeof(path));

			swprintf(path, L"%s\\sound_hound_interface\\Main.swf", m_work_path);
			if (PathFileExists(path))
			{										
				m_listen_flash_page_tv.LoadMovie(0, path);
				m_listen_flash_page_tv.ShowWindow(SW_SHOW);
				m_listen_flash_page_tv.put_ScaleMode(2);
				m_listen_flash_page_tv.BringWindowToTop();
			}
		}
		////////////////////*/
	}
	return true;
}

void Cflashktv10Wnd::destroy_listen_song()
{
	if (m_listen_flash_page_tv_soft_exist)
	{
		m_listen_flash_page_tv_soft.DestroyWindow();
		m_listen_flash_page_tv_soft_exist = false;
	}

	if (m_listen_flash_page_tv_exist)
	{
		m_listen_flash_page_tv.DestroyWindow();
		m_listen_flash_page_tv_exist = false;
	}
	m_bListenSongFlashFinish = false;
	m_nFlashFinishCnt = 0;
	m_nCurPageCode = 0;
}

void Cflashktv10Wnd::create_wechat_interaction_wnd()
{
	TCHAR path[256] = {0x0};
	swprintf(path,L"%s\\wechat_interaction_interface\\Wechat_barrage.swf",m_work_path);	

	if (m_soft_decode_window_exist && m_use_soft_active_flash)
	{
		CRect rtStarFlash(0,0,m_sencond_display_width, m_sencond_display_height);
		m_pWechatInteractionSoftTransparentWnd = new CTransparentWnd;
		m_wechat_interaction_soft_flash_player_exist = PlayScreenFlash(m_pWechatInteractionSoftTransparentWnd, &m_soft_decode_window_child, path, m_rt_soft_activity, rtStarFlash,SCREEN_FLASH_WND_ID, WECHAT_INTERACTION_SOFT_PLAYER_ID);
		if (m_wechat_interaction_soft_flash_player_exist)
		{
			m_pWechatInteractionSoftTransparentWnd->SetWindowStyle(RGB(0, 0, 0), 150, (LWA_COLORKEY | LWA_ALPHA));
			m_pWechatInteractionSoftTransparentWnd->SetWindowPos(&CWnd::wndTopMost,m_rt_soft_activity.left,m_rt_soft_activity.top+90,m_rt_soft_activity.Width(),m_rt_soft_activity.Height()*11/20,NULL);
			m_pWechatInteractionSoftTransparentWnd->m_pFlash->MoveWindow(0, 0, m_rt_soft_activity.Width(), m_rt_soft_activity.Height()*11/20);
			m_pWechatInteractionSoftTransparentWnd->m_pFlash->put_ScaleMode(2);//可缩放，适应窗口
			m_pWechatInteractionSoftTransparentWnd->ShowWindow(SW_SHOW);
		}
	}
	if (m_inter_screen_exist)
	{
		CRect rtStarFlash(0,0,m_rtAbsoluteActivityWnd.Width(), m_rtAbsoluteActivityWnd.Height());
		m_pWechatInteractionTransparentWnd = new CTransparentWnd;
		m_wechat_interaction_flash_player_exist = PlayScreenFlash(m_pWechatInteractionTransparentWnd, &m_inter_screen_window, path, m_rtAbsoluteActivityWnd, rtStarFlash, SCREEN_FLASH_WND_ID, WECHAT_INTERACTION_PLAYER_ID);
		if (m_wechat_interaction_flash_player_exist)
		{
			m_pWechatInteractionTransparentWnd->SetWindowStyle(RGB(0, 0, 0), 150, (LWA_COLORKEY | LWA_ALPHA));
			m_pWechatInteractionTransparentWnd->SetWindowPos(&CWnd::wndTopMost,m_rtAbsoluteActivityWnd.left,m_rtAbsoluteActivityWnd.top,m_rtAbsoluteActivityWnd.Width(),m_rtAbsoluteActivityWnd.Height()*3/5,NULL);
			m_pWechatInteractionTransparentWnd->m_pFlash->MoveWindow(0, 0, m_rtAbsoluteActivityWnd.Width(), m_rtAbsoluteActivityWnd.Height()*3/5);
			m_pWechatInteractionTransparentWnd->m_pFlash->put_ScaleMode(2);//可缩放，适应窗口
			m_pWechatInteractionTransparentWnd->ShowWindow(SW_SHOW);
		}
	}
	/////*/
}
void Cflashktv10Wnd::destroy_wechat_interaction_wnd()
{
	if (m_soft_decode_window_exist && m_pWechatInteractionSoftTransparentWnd != NULL)
	{
		delete m_pWechatInteractionSoftTransparentWnd;
		m_pWechatInteractionSoftTransparentWnd = NULL;
	}
	if (m_inter_screen_exist && m_pWechatInteractionTransparentWnd != NULL)
	{
		delete m_pWechatInteractionTransparentWnd;
		m_pWechatInteractionTransparentWnd = NULL;
	}
	m_nBarrageFlashFinishCnt = 0;
	m_bWechatInteractionFlashFinish = false;
	m_barrage_lock.lock();
	m_deque_barrage_info.clear();
	m_barrage_lock.unlock();
}

bool Cflashktv10Wnd::generate_wechat_barrage_encode()
{
	try
	{
		bool bRet = false;
		string_conversion string_con;
		char szUrl[256] = {0x00}, szUrlPath[256] = {0x00};

		if (wcslen(m_szWechatBarrageUrl) == 0)	return false;

		string_con.widechar_to_multibyte(m_szWechatBarrageUrl, szUrl, sizeof(szUrl));
		//根据本机ip得到全地址
		sprintf(szUrlPath, "%s%s", szUrl, m_send_room_ip);

		//图片保存路径
		swprintf(m_szWechatBarragePicFilePath, L"%s\\wechat_barrage_img\\wechat_barrage_encode.png", m_work_path);
		if (PathFileExists(m_szWechatBarragePicFilePath))
		{
			DeleteFile(m_szWechatBarragePicFilePath);
		}
		//生成二维码
		bRet = Generate_encode_picture(szUrlPath, m_szWechatBarragePicFilePath);
		if (!bRet)	return false;

		//缩放图片
		bRet = zoom_image(m_szWechatBarragePicFilePath, 160, 160, m_szWechatBarragePicFilePath, L"image/png", 0, 0);
		if (!bRet)	return false;

		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_wechat_barrage_pic_path()
{
	try
	{
		bool bRet = false;
		TCHAR request[256] = {0x00}, data[256] = {0x00};

		swprintf(data, L"<data><info pic_path=\"%s\"/></data>", m_szWechatBarragePicFilePath);

		//直接组织字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"wechat_barrage_pic_path", data);
		if (!bRet)	return false;

		bRet = flash_player_call_function(request);
		if (!bRet)	return false;

		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_wechat_barrage_open(bool bOpen)
{
	try
	{
		bool bRet = false;
		TCHAR request[256] = {0x00}, data[256] = {0x00};
		m_bWechatBarrageOpen = bOpen;//保存开关状态

		swprintf(data, L"<data><info is_open=\"%d\"/></data>", m_bWechatBarrageOpen?1:0);

		//直接组织字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"wechat_barrage_open", data);
		if (!bRet)	return false;

		bRet = flash_player_call_function(request);
		if (!bRet)	return false;

		return true;
	}
	catch (...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_wechat_barrage_mode(int nMode)
{
	try
	{
		bool bRet = false;
		TCHAR request[256] = {0x00}, data[256] = {0x00};
		m_nWechatBarrageMode = nMode;//保存模式

		swprintf(data, L"<data><info mode=\"%d\"/></data>", m_nWechatBarrageMode);

		//直接组织字符串 
		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"wechat_barrage_mode", data);
		if (!bRet)	return false;

		bRet = flash_player_call_function(request);
		if (!bRet)	return false;

		return true;
	}
	catch (...)
	{
	}
	return false;
}
UINT Cflashktv10Wnd::show_wechat_barrage_info_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);

		pThis->show_wechat_barrage_info();

//		AfxEndThread(0);

		return 0;
	}
	catch (...)
	{
	} 
	return -1;
}
UINT Cflashktv10Wnd::show_wechat_barrage_info()
{
	try
	{
		while(m_bWechatBarrageOpen)
		{
			Sleep(100);
			m_wechat_barrage_lock.lock();

			if (!m_deque_barrage_info.empty())
			{
				BARRAGE_INFO barrage_info = m_deque_barrage_info.front();

				flash_message_call_wechat_barrage_info(&barrage_info);

				//发过来的分享和记录的相同  移除第一个
				m_deque_barrage_info.pop_front(); 
			}

			m_wechat_barrage_lock.unlock();

		}
		return 0;
	}
	catch (...)
	{
	}
	return 0;
}

UINT Cflashktv10Wnd::parse_wechat_barrage_info_thread(LPVOID pParam)
{
	try
	{
		LPBARRAGE_MSG pBarrageMsg = (LPBARRAGE_MSG)pParam;

		Cflashktv10Wnd* pKtvWnd = (Cflashktv10Wnd*)pBarrageMsg->pWnd;
		char szData[2048] = {0x00};
		strcpy(szData, pBarrageMsg->szData);

		delete pBarrageMsg;
		pBarrageMsg = NULL;

		Json::Reader reader;
		Json::Value root;

		//不能解析
		if (!reader.parse(szData, root, false))
		{
			WriteLog(__FL__, L"弹幕json格式错误！");
			return 1;
		}

		TCHAR szTmp[2048] = {0x00};
		TCHAR szKey[256], szValue[256], szName[256], wszExpressionPic[256];
		string strTmp("");
		int nMode = 0;
		string_conversion string_conn;
		BARRAGE_INFO barrage_info;

		pKtvWnd->m_wechat_barrage_lock.lock();

		//来源IP
		if (root.isMember("ip"))
		{
			//IP
			string strIp = root["ip"].asString();
			string_conn.multibyte_to_widechar(strIp.c_str(), szTmp, sizeof(szTmp));
			barrage_info.strIp = szTmp;
			//只接受本房间的弹幕时，判断ip
			if (0 != strcmp(pKtvWnd->m_send_room_ip, strIp.c_str()) && pKtvWnd->m_nWechatBarrageMode == 0)
				return 0;
		}
		//微信昵称
		if (root.isMember("nickname"))
		{
			strTmp = root["nickname"].asString();
			string_conn.multibyte_to_widechar(strTmp.c_str(), szTmp, sizeof(szTmp));
			barrage_info.strWechatNickName = szTmp;
		}
		//微信头像路径
		if (root.isMember("headimgurl"))
		{
			TCHAR wszHeadPath[256] = {0x00};
			char szHeadPath[256] = {0x00};
			strTmp = root["headimgurl"].asString();
			string strName = strTmp.substr(strTmp.rfind('/')+1);
			string_conn.multibyte_to_widechar(strName.c_str(), szName, sizeof(szName));
			wsprintf(wszHeadPath, L"%s\\wechat_barrage_img\\%s", pKtvWnd->m_work_path, szName);
			if (!PathFileExists(wszHeadPath))
			{
				string_conn.widechar_to_multibyte(wszHeadPath, szHeadPath, sizeof(szHeadPath));
				//if (pKtvWnd->down(strTmp.c_str(), szHeadPath) != 0)
				if(pKtvWnd->m_http_obj.download_file((char*)strTmp.c_str(), wszHeadPath) != 0)
				{
					wsprintf(wszHeadPath, L"%s\\wechat_default_img\\default_head.png", pKtvWnd->m_work_path);
					_tcscpy(szName, L"default_head.png");
				}
			}

			barrage_info.strWechatHeadPath = wszHeadPath;
			barrage_info.strWechatHeadName = L"[" + (wstring)szName + L"]";
		}
		//颜色//"#0F0F0F"
		if(root.isMember("color"))
		{
			strTmp = root["color"].asString();
			string strHead("0x");
			strTmp.replace(0, 1, strHead.c_str());
			string_conn.multibyte_to_widechar(strTmp.c_str(), szTmp, sizeof(szTmp));
			barrage_info.strColor = szTmp;
		}
		//内容
		if(root.isMember("content"))
		{
			string_conn.multibyte_to_widechar(root["content"].asString().c_str(), szTmp, sizeof(szTmp));
			barrage_info.strContent = szTmp;
		}
		//速度
		if(root.isMember("speed"))
		{
			barrage_info.nSpeed = root["speed"].asInt();
		}
		//次数
		if(root.isMember("count"))
		{
			barrage_info.nCount = root["count"].asInt();
		}
		//字号(随机[min-max])
		srand((unsigned int)time((time_t *)NULL));
		int nSize = rand()%(pKtvWnd->m_nFontSizeMax - pKtvWnd->m_nFontSizeMin + 1) + pKtvWnd->m_nFontSizeMin;
		barrage_info.nSize = nSize;
		//表情集合
		char szExpressionPic[256];
		if (root.isMember("key"))
		{
			Json::Value key = root["key"];
			for (int i = 0; i < key.size(); i++)
			{
				//表情
				memset(szKey, 0x00, sizeof(szKey));
				string strKey = key[i]["Key"].asString();
				string_conn.multibyte_to_widechar(strKey.c_str(), szKey, sizeof(szKey));
				//路径
				memset(szValue, 0x00, sizeof(szValue));
				string strValue = key[i]["Value"].asString();
				string_conn.multibyte_to_widechar(strValue.c_str(), szValue, sizeof(szValue));
				string strName = strValue.substr(strValue.rfind('/')+1);
				string_conn.multibyte_to_widechar(strName.c_str(), szName, sizeof(szName));
				//下载表情图片
				memset(szExpressionPic, 0x00, sizeof(szExpressionPic));
				memset(wszExpressionPic, 0x00, sizeof(wszExpressionPic));
				swprintf(wszExpressionPic, L"%s\\wechat_barrage_img\\%s", pKtvWnd->m_work_path, szName);//头像本地保存路径
				if (!PathFileExists(wszExpressionPic))
				{
					string_conn.widechar_to_multibyte(wszExpressionPic, szExpressionPic, sizeof(szExpressionPic));
					//if (pKtvWnd->down(strValue.c_str(), szExpressionPic) == 0)
					if(pKtvWnd->m_http_obj.download_file((char*)strValue.c_str(), wszExpressionPic) == 0)
					{
						barrage_info.keyImageMap.insert(pair<wstring, wstring>(szKey, wszExpressionPic));
					}
					else
					{
						WriteLog(__FL__, L"下载弹幕表情图片失败");
					}
				}
				else
				{
					barrage_info.keyImageMap.insert(pair<wstring, wstring>(szKey, wszExpressionPic));
				}
			}
		}
		
		root.toStyledString();

		pKtvWnd->m_deque_barrage_info.push_back(barrage_info);
		
		pKtvWnd->m_wechat_barrage_lock.unlock();

//		GetExitCodeThread()
//		AfxEndThread(0);
	}
	catch (...)
	{
	}
	return 0;
}

bool Cflashktv10Wnd::flash_message_call_wechat_barrage_info(BARRAGE_INFO *pInfo)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00}, temp[1024] = {0x00};
		wstring strData(L"");
		string_conversion str_conv;
		int nMode = 0;

		if (pInfo == NULL)	return false;

		//弹幕信息
		swprintf(data, L"<data><info content=\"%s(%s):%s\" color=\"%s\" size=\"%d\" speed=\"%d\" times=\"%d\" >", 
			pInfo->strWechatHeadName.c_str(), pInfo->strWechatNickName.c_str(), pInfo->strContent.c_str(), pInfo->strColor.c_str(), pInfo->nSize, pInfo->nSpeed, pInfo->nCount);
		strData += data;
		//头像信息
		swprintf(temp, L"<item key=\"%s\" url=\"%s\" />", pInfo->strWechatHeadName.c_str(), pInfo->strWechatHeadPath.c_str());
		strData += temp;
		//表情信息
		map<wstring, wstring>::iterator iter = pInfo->keyImageMap.begin();
		for (; iter != pInfo->keyImageMap.end(); ++iter)
		{
			memset(temp, 0x00, sizeof(temp));
			swprintf(temp, L"<item key=\"%s\" url=\"%s\" />", iter->first.c_str(), iter->second.c_str());
			strData += temp;
		}
		strData += L"</info></data>";

		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"wechat_barrage", strData.c_str());
		if (bRet)
		{
			if (m_soft_decode_window_exist && m_pWechatInteractionSoftTransparentWnd != NULL)
			{
				m_pWechatInteractionSoftTransparentWnd->m_pFlash->CallFunction(request);
			}
			if (m_inter_screen_exist && m_pWechatInteractionTransparentWnd != NULL)
			{
				m_pWechatInteractionTransparentWnd->m_pFlash->CallFunction(request);
			}
		}
		return true;
	}
	catch (...)
	{
	}
	return false;
}
void Cflashktv10Wnd::change_light_state(int nState)
{
#ifdef DALIAN_MATSA_EK_PLUS
	//大连麦莎不启用
	return;
#endif
	bool result = false;
	config_file_manager config_file;
	int light_control = 0;
	wstring str;
	config_file.init(L"com.ini");

	if (nState == 1 || nState == 2)
	{
		if (nState == 1)
		{
			str = config_file.read_string(L"send_value", L"light_mute", L"");
			if (str.length() == 0)
			{
				if (m_use_audio_effect)
				{
					light_control = 0;
				}
				else
				{
					light_control = m_default_auto_light;
				}
			}
			else
			{
				light_control = 14;
			}
		}
		else if (nState == 2)
		{
			str = config_file.read_string(L"send_value", L"light_pause", L"");
			if (str.length() == 0)
			{
				if (m_use_audio_effect)
				{
					light_control = 0;
				}
				else
				{
					light_control = m_default_auto_light;
				}
			}
			else
			{
				light_control = 15;
			}
		}
		TCHAR request[256] = {0x00}, data[256] = {0x00};
		swprintf(data, L"%d", light_control);
		result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"light_button", data);
		if (result)
		{
			flash_player_call_function(request);

			result = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"light_auto_button", L"1");
			flash_player_call_function(request);
		}
	}
	else if(nState == 0)
	{
		light_control = _wtoi(m_select_ligth_buttom);
	}

default_light1:
	switch(light_control)
	{
	case 0:    //灯光 全关
		{
			write_com_data(COM_SEND_LIGHT_CLOSE, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 全关");
		}
		break;
	case 1:    //灯光 全开 
		{
			write_com_data(COM_SEND_LIGHT_OPEN, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 全开");
		}
		break;
	case 2:    //灯光 明亮
		{
			write_com_data(COM_SEND_LIGHT_STANDARD, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 明亮");
		}
		break;
	case 3:    //灯光 柔和
		{
			write_com_data(COM_SEND_LIGHT_BACKGROUND, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 柔和");
		}
		break;
	case 4:    //灯光 时尚
		{
			write_com_data(COM_SEND_LIGHT_STAGE, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 时尚");
		}
		break;
	case 5: //动感
		{
			write_com_data(COM_SEND_LIGHT_SCINTILLATION, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 动感");
		}
		break;
	case 6: //温馨
		{
			write_com_data(COM_SEND_LIGHT1, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 温馨");
		}
		break;
	case 7: //浪漫
		{
			write_com_data(COM_SEND_LIGHT2, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 浪漫");
		}
		break;
	case 8: //商务
		{
			write_com_data(COM_SEND_LIGHT3, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 商务");
		}
		break;
	case 9: //绚丽
		{
			write_com_data(COM_SEND_LIGHT4, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 明快");
		}
		break;
	case 10: //梦幻
		{
			write_com_data(COM_SEND_LIGHT5, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 梦幻");
		}
		break;
	case 11: //预留1
		{
			write_com_data(COM_SEND_LIGHT6, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 预留1");
		}
		break;
	case 12: //预留2
		{
			write_com_data(COM_SEND_LIGHT7, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 预留2");
		}
		break;
	case 13: //预留3
		{
			write_com_data(COM_SEND_LIGHT8, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"播放歌曲时需要控制灯光 预留3");
		}
		break;
	case 14:
		{
			write_com_data(COM_SEND_LIGHT_MUTE, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"歌曲静音时需要控制灯光");
		}
		break;
	case 15:
		{
			write_com_data(COM_SEND_LIGHT_PAUSE, 0, true, light_control);
			//高亮的灯光按钮
			WriteLog(__FL__, L"歌曲暂停时需要控制灯光");
		}
		break;
	default:
		{
			if (m_use_audio_effect)
			{
				write_com_data(COM_SEND_LIGHT_CLOSE, 0, true, light_control);
				//高亮的灯光按钮
				WriteLog(__FL__, L"播放歌曲时需要控制灯光 全关");
			}
			else
			{
				light_control = m_default_auto_light;
				goto default_light1;
			}
		}
		break;
	}
}

UINT Cflashktv10Wnd::wechat_message_thread(LPVOID pParam)
{
	try
	{
		LPWECHAT_MESSAGE lpwechat_msg = (LPWECHAT_MESSAGE)pParam;
		WECHAT_MESSAGE wechat_msg;
		memset(&wechat_msg, 0x00, sizeof(WECHAT_MESSAGE));
		memcpy(&wechat_msg, lpwechat_msg, sizeof(WECHAT_MESSAGE));
		Cflashktv10Wnd *fkWnd = (Cflashktv10Wnd*)lpwechat_msg->pWnd;
		string_conversion string_conn;

		//验证下载解压文件夹是否创建
		CString csDirPath = _T("");
		CString csTempPath = _T("");
		GetTempPath(MAX_PATH, csTempPath.GetBuffer(MAX_PATH));
		csDirPath.Format(_T("%s\\WechatDown"), /*csTempPath*/fkWnd->m_work_path);
		if (!PathFileExists(csDirPath))
		{
			_wmkdir(csDirPath);
		}
		//lpwechat_msg->notic_type 0:下载文件准备好 1:通知有礼物过来了 2中转服务器下载失败
		//lpwechat_msg->num 8:动画消息 9:礼物（魔法表情）消息 13:照片推送消息
		switch(wechat_msg.num)
		{
		case WECHAT_ANIMATION: //动画
			{

			}
			break;
		case WECHAT_GIFT: //礼物
			{
				switch(wechat_msg.notice_type)
				{
				case WECHAT_RET_NOTICE: //通知点歌系统，有礼物过来了
					{
						WriteLog(__FL__, L"收到赠送礼物的消息");
						fkWnd->m_wechat_gift_lock.lock();
						CString csDelivery = _T("");
						csDelivery.Format(_T("%s\\WechatDown\\delivery.gif"), fkWnd->m_work_path);
						string_conn.widechar_to_multibyte(csDelivery, wechat_msg.filepath, sizeof(wechat_msg.filepath));

						fkWnd->m_deque_wechat_message.push_back(wechat_msg);
						//fkWnd->show_picture_on_tv(csDelivery.GetBuffer(),OSDAlignmentCenter,1000*15,false,false);
						fkWnd->m_wechat_gift_lock.unlock();
					}
					break;
				case WECHAT_RET_OK: //礼物服务器下载成功
					{
						WriteLog(__FL__, L"收到礼物下载成功的消息");
						fkWnd->m_wechat_gift_lock.lock();

						TCHAR wszHeadPath[256] = {0x00}, szName[256] = {0x00};
						char szHeadPath[256] = {0x00};
						string strTmp = wechat_msg.portrait;
						string strName = strTmp.substr(strTmp.rfind('/')+1);
						string_conn.multibyte_to_widechar(strName.c_str(), szName, sizeof(szName));
						wsprintf(wszHeadPath, L"%s\\WechatDown\\%s", fkWnd->m_work_path, szName);
						string_conn.widechar_to_multibyte(wszHeadPath, szHeadPath, sizeof(szHeadPath));
						if (!PathFileExists(wszHeadPath))
						{
							//if (fkWnd->down(strTmp.c_str(), szHeadPath) != 0)
							if(fkWnd->m_http_obj.download_file((char*)strTmp.c_str(), wszHeadPath) != 0)
							{
								wsprintf(wszHeadPath, L"%s\\wechat_default_img\\default_head.png", fkWnd->m_work_path);
								_tcscpy(szName, L"default_head.png");
								string_conn.widechar_to_multibyte(wszHeadPath, szHeadPath, sizeof(szHeadPath));
							}
						}
						strcpy(wechat_msg.portraitpath, szHeadPath);

						CString csLocalPath = _T("");
						char szLocalPath[MAX_PATH] = {0x00};
						TCHAR szDirName[32] = {0x00};
						char szmDirName[32] = {0x00};
						CString csDirName = _T("");
						//取的文件的名字
						string_conn.multibyte_to_widechar(wechat_msg.filename, szDirName, sizeof(szDirName));
						csDirName.Format(_T("%s"), szDirName);
						int nPos = csDirName.Find('.');
						csDirName = csDirName.Left(nPos);
						string_conn.widechar_to_multibyte(csDirName, szmDirName, sizeof(szmDirName));
						//转换
						csLocalPath.Format(_T("%s\\%s"), csDirPath, csDirName);

						if (!PathFileExists(csLocalPath))
						{
							_wmkdir(csLocalPath);
						}

						string_conn.widechar_to_multibyte(csLocalPath, szLocalPath, sizeof(szLocalPath));
						strcat(szLocalPath, "\\");
						strcat(szLocalPath, wechat_msg.filename);

						TCHAR szLocal[MAX_PATH] = {0x00};
						string_conn.multibyte_to_widechar(szLocalPath, szLocal, sizeof(szLocal));
						//if(fkWnd->down(wechat_msg.url, szLocalPath) == 0) //下载成功
						if(fkWnd->m_http_obj.download_file(wechat_msg.url, szLocal) == 0)
						{
							CString csPath = csLocalPath + _T("\\") + szDirName; 
							CString strFileName = _T("");
							//现对压缩包进行解压
							fkWnd->unzip(csPath, csLocalPath, strFileName);

							string_conn.widechar_to_multibyte(strFileName, wechat_msg.filepath, sizeof(wechat_msg.filepath));
						}
						else
						{
							CString csFilePath = _T("");
							csFilePath.Format(_T("%s\\WechatDown\\lose.gif"), fkWnd->m_work_path);
							string_conn.widechar_to_multibyte(csFilePath, wechat_msg.filepath, sizeof(wechat_msg.filepath));
						}
						if (fkWnd->m_deque_wechat_message.size() > 0)
						{
							deque<WECHAT_MESSAGE>::iterator iter = fkWnd->m_deque_wechat_message.begin();
							for (;iter != fkWnd->m_deque_wechat_message.end();++iter)
							{
								if (strcmp(wechat_msg.guid, iter->guid)==0)
								{
									iter->notice_type = WECHAT_RET_OK;
									strcpy(iter->filepath, wechat_msg.filepath);
									strcpy(iter->portraitpath, wechat_msg.portraitpath);
									break;
								}
							}
						}
						//fkWnd->show_picture_on_tv(csFilePath.GetBuffer(),OSDAlignmentCenter,6000,false,false);
						fkWnd->m_wechat_gift_lock.unlock();
					}
					break;
				case WECHAT_RET_ERROR: //服务器礼物下载失败
					{
						WriteLog(__FL__, L"收到礼物下载失败的消息");
						fkWnd->m_wechat_gift_lock.lock();
						CString csDelivery = _T("");
						csDelivery.Format(_T("%s\\WechatDown\\lose.gif"), fkWnd->m_work_path);
						string_conn.widechar_to_multibyte(csDelivery, wechat_msg.filepath, sizeof(wechat_msg.filepath));
						if (fkWnd->m_deque_wechat_message.size() > 0)
						{
							deque<WECHAT_MESSAGE>::iterator iter = fkWnd->m_deque_wechat_message.begin();
							for (;iter != fkWnd->m_deque_wechat_message.end();++iter)
							{
								if (strcmp(wechat_msg.guid, iter->guid)==0)
								{
									iter->notice_type = WECHAT_RET_ERROR;
									strcpy(iter->filepath, wechat_msg.filepath);
									break;
								}
							}
						}
						//fkWnd->show_picture_on_tv(csDelivery.GetBuffer(),OSDAlignmentCenter,1000*3,false,false);
						fkWnd->m_wechat_gift_lock.unlock();
					}
					break;
				}
			}
			break;
		case WECHAT_PICTURE: //照片推送
			{
				switch(wechat_msg.notice_type)
				{
				case WECHAT_RET_NOTICE: //通知点歌系统，有礼物过来了
					{
						WriteLog(__FL__, L"收到照片推送通知");
					}
					break;
				case WECHAT_RET_OK: //礼物服务器下载成功
					{
						WriteLog(__FL__, L"收到照片推送下载成功通知");
						CString csLocalPath = _T("");
						char szLocalPath[MAX_PATH] = {0x00};
						TCHAR szDirName[128] = {0x00};
						char szmDirName[128] = {0x00};
						CString csDirName = _T(""), csFileName = _T(""), csSuffix = _T("");
						//取的文件的名字
						string_conn.multibyte_to_widechar(wechat_msg.filename, szDirName, sizeof(szDirName));
						csDirName.Format(_T("%s"), szDirName);
						int nPos = csDirName.Find('.');
						csFileName = csDirName.Left(nPos);
						csSuffix = csDirName.Right(nPos);
						string_conn.widechar_to_multibyte(csFileName, szmDirName, sizeof(szmDirName));
						//转换
						csLocalPath.Format(_T("%s\\%s"), csDirPath, csFileName);

						if (!PathFileExists(csLocalPath))
						{
							_wmkdir(csLocalPath);
						}

						string_conn.widechar_to_multibyte(csLocalPath, szLocalPath, sizeof(szLocalPath));
						strcat(szLocalPath, "\\");
						strcat(szLocalPath, wechat_msg.filename);

						TCHAR szLocal[MAX_PATH] = {0x00};
						string_conn.multibyte_to_widechar(szLocalPath, szLocal, sizeof(szLocal));
						//if(fkWnd->down(wechat_msg.url, szLocalPath) == 0) //下载成功
						if(fkWnd->m_http_obj.download_file(wechat_msg.url, szLocal) == 0)
						{
							CString strFormat(_T(""));
							if (csSuffix.CompareNoCase(_T(".jpg")) == 0 || csSuffix.CompareNoCase(_T(".jpeg")) == 0)
							{
								strFormat = _T("image/jpeg");
							}
							else if (csSuffix.CompareNoCase(_T(".png")) == 0)
							{
								strFormat = _T("image/png");
							}
							else if (csSuffix.CompareNoCase(_T(".bmp")) == 0)
							{
								strFormat = _T("image/bmp");
							}
							else if (csSuffix.CompareNoCase(_T(".gif")) == 0)
							{
								strFormat = _T("image/gif");
							}
							else if (csSuffix.CompareNoCase(_T(".tif")) == 0)
							{
								strFormat = _T("image/tiff");
							}
							else
							{
								strFormat = _T("image/jpeg");
							}
							CString csFilePath = csLocalPath + _T("\\") + szDirName;  //显示文件路径
							CExifTags exif;
							EXIFINFO exifInfo;
							int nWidth = 0, nHeight = 0;

							ZeroMemory(&exifInfo, sizeof(EXIFINFO));
							exif.GetExifRead(csFilePath.GetBuffer(), &exifInfo);
							if (exifInfo.Width > exifInfo.Height && exifInfo.Width > 0)
							{
								nWidth = 600;
								nHeight = exifInfo.Height/(float)(exifInfo.Width/600);
							}
							else
							{
								nWidth = exifInfo.Width/(float)(exifInfo.Height/600);
								nHeight = 600;
							}
							if (nWidth > 0 && nHeight > 0)
							{
								fkWnd->zoom_image(csFilePath.GetBuffer(),nWidth,nHeight,csFilePath.GetBuffer(), strFormat.GetBuffer(), 0, 0); 
							}
							play_variable play_var;
							//初始化播放图片的变量
							play_var.nRepeat = 10;
							play_var.play_mode = OSD_STATIC;
							play_var.iHSpeed = 0;
							play_var.iVSpeed = 0;
							play_var.nDelayTime = 0;
							//图片存在就显示
							bool result = fkWnd->m_player_manager.play_bmp_osd(csFilePath.GetBuffer(),play_var,OSDAlignmentCenter);
							if (!result)
							{
								return false;
							}

							fkWnd->show_control_osd_timer_identifier = fkWnd->SetTimer(SHOW_CONTROL_OSD_TIMER_EVENT_ID,fkWnd->m_nPicturePlayTime*1000,NULL);
						}
					}
					break;
				case WECHAT_RET_ERROR: //服务器礼物下载失败
					{
						WriteLog(__FL__, L"收到照片推送下载失败通知");
					}
					break;
				}
			}
			break;
		}
		//释放资源
		delete lpwechat_msg;
		lpwechat_msg = NULL;
	}
	catch (...)
	{
	}
	return 0;
}

bool Cflashktv10Wnd::unzip(CString csPath, CString csDir, CString &strFileName)
{
	CString strTmp(L"");
	strFileName = _T("");
	HZIP  hz = OpenZip((void*)csPath.GetBuffer(), 0, ZIP_FILENAME);
	ZIPENTRYW ze;
	GetZipItem(hz, -1 , &ze);
	int numitems = ze.index;
	for (int i = 0; i < numitems; i++)
	{
		GetZipItem(hz, i, &ze);

		strTmp = csDir;
		strTmp += _T("\\");
		strTmp += ze.name;
		strTmp.Replace(_T("/"), _T("\\"));

		if(ze.attr==0x91)
		{
			_wmkdir(strTmp);
		}

		if(ze.attr==0xa1 || ze.attr==0x81)
		{
			strFileName = strTmp;
		}

		int ret=UnzipItem (hz, i, (void*)strTmp.GetBuffer(), 0, ZIP_FILENAME);
		if(ret!=0)
		{
			CloseZip (hz);
			return false;
		}

// 		if (ze.attr!=145&&SetFileAttributes(ze.name, FILE_ATTRIBUTE_ARCHIVE) == 0)//设置文件属性为存档
// 		{
// 			CloseZip (hz);
// 			return false;
// 			//break;
// 		}
	}

	CloseZip (hz);
	return true;
}

UINT Cflashktv10Wnd::cloud_song_down_progress(LPVOID pParam)
{
	try
	{
		string_conversion string_conn;
		Cflashktv10Wnd *pWnd = (Cflashktv10Wnd*)pParam;
		llock lockObj;
		SOCKADDR_IN addr;
		SOCKADDR_IN from;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = 0;
		addr.sin_port = htons(UDP_PROGREES_RADIO);

		from.sin_family = AF_INET;
		from.sin_addr.S_un.S_addr = INADDR_BROADCAST;
		from.sin_port = htons(UDP_PROGREES_RADIO);
		int len = sizeof(SOCKADDR);

		SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
		if(INVALID_SOCKET == s)
		{
			CString csMsg = _T("");
			csMsg.Format(_T("[cloud_song_down_progress]socket failed with error code: %d"), WSAGetLastError());
			WriteLog(__FL__, csMsg);
			return -1;
		}

		BOOL optval = TRUE;
		setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char FAR *)&optval, sizeof(optval));
		if(SOCKET_ERROR == bind(s, (sockaddr*)&addr, sizeof(sockaddr_in)))
		{
			CString csMsg = _T("");
			csMsg.Format(_T("[cloud_song_down_progress]bind failed with error code: %d"), WSAGetLastError());
			WriteLog(__FL__, csMsg);
			closesocket(s);
			return -1;
		}
		DOWNPROFILE DNotic;
		TCHAR szSongID[64] = {0x00};
		int iProcess = 0;
		while(pWnd->m_thread_run)
		{
			SLEEP_FOR; //增加sleep

			ZeroMemory(&DNotic, sizeof(DOWNPROFILE));
			ZeroMemory(szSongID, sizeof(szSongID));
			iProcess = 0;

			int iRecvLen = recvfrom(s, (char*)&DNotic, sizeof(DOWNPROFILE), 0, (struct sockaddr FAR *)&from, (int FAR *)&len);
			if (iRecvLen > 0 && DNotic.head == 0XAA55AA55)
			{
				lockObj.lock(); //加锁
				if (strcmp(DNotic.name, "") == 0)
				{
					lockObj.unlock(); //解锁
					continue;
				}

				int page_index = pWnd->m_flash_manage.get_last_page_index();
				if(page_index != page_selected)
				{
					lockObj.unlock(); //解锁
					continue;
				}		

				string_conn.multibyte_to_widechar(DNotic.name, szSongID, sizeof(szSongID));
				TCHAR *pSongID = _tcschr(szSongID, '.');
				pSongID[0] = '\0';
				float val = (float)DNotic.done / (float)DNotic.total * 100.;
				iProcess = val;
				if (_tcscmp(szSongID, L"") == 0 || iProcess == 0 || pWnd->m_down_song_vec.size() == 0) //如果没有值，则不显示
				{
					lockObj.unlock(); //解锁
					continue;
				}
				
				//查询id是否在下载中
				vector<wstring>::iterator songIter;	 //Map迭代器 
				songIter = std::find(pWnd->m_down_song_vec.begin(), pWnd->m_down_song_vec.end(), szSongID);
				if(songIter == pWnd->m_down_song_vec.end())
				{
					lockObj.unlock(); //解锁
					continue;	
				}
				
				//获得到这个歌曲的信息
				song_info SongInfo;
				bool bRet = pWnd->get_song_info_by_id(szSongID, SongInfo, PLAY_SONG_TYPE_SELECT_SONG);
				if (!bRet)
				{
					lockObj.unlock(); //解锁
					continue;
				}

				pWnd->send_cloud_song_progress_to_flash(SongInfo, iProcess);
				lockObj.unlock(); //解锁
			}
		}
	}	
	catch (...)
	{
	}
	return 0;
}

#define RECV_FLASH_DATA_PARSE_DATA_PORT 3722
UINT Cflashktv10Wnd::RecvFlashDataParseData(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd *pWnd = (Cflashktv10Wnd*)pParam;

		timeval overtime;
		overtime.tv_sec = 0;
		overtime.tv_usec = 50000;
		int result=0;
		TCHAR log[1024];
		string_conversion string_conv;
		TCHAR wide_string[1024];

		//清0
		FD_ZERO(&g_flash_socket_set);

		SOCKET ListenSocket = INVALID_SOCKET;  
		ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
		if(ListenSocket == INVALID_SOCKET)  
		{  
			return 1;  
		}

		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
		addrSrv.sin_port=ntohs(RECV_FLASH_DATA_PARSE_DATA_PORT);
		addrSrv.sin_family = AF_INET; 
		memset(&addrSrv.sin_zero, 0, sizeof(addrSrv.sin_zero));

		result = bind(ListenSocket, (SOCKADDR*)&addrSrv,sizeof(SOCKADDR));  
		if(result == SOCKET_ERROR)  
		{  
			result = shutdown(ListenSocket, SD_SEND);  
			if(result == SOCKET_ERROR)  
			{  
				closesocket(ListenSocket);  
				return 1;  
			} 
			return 1;  
		}

		// listen on a socket  
		if(listen(ListenSocket, SOMAXCONN))  
		{   
			closesocket(ListenSocket);  
			return 1;  
		} 

		//加入监听组
		FD_SET(ListenSocket,&g_flash_socket_set);
		while (pWnd->m_thread_run)
		{
			try
			{
				SLEEP_FOR; //增加sleep

				//将fdSocket集合的一个拷贝fdRead传递给select函数，
				// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回
				fd_set fdRead_set = g_flash_socket_set;
				result = ::select(0,&fdRead_set,NULL,NULL,&overtime);
				if (result<=0 || !pWnd->m_flash_screen_init_finish)
				{
					continue;
				}
				//通过将原来fdSocket集合与select处理过的fdRead集合比较，
				// 确定都有哪些套节字有未决I/O，并进一步处理这些I/O。
				for(int i=0; i<(int)g_flash_socket_set.fd_count; i++)
				{
					if (FD_ISSET(g_flash_socket_set.fd_array[i],&fdRead_set))
					{
						if (g_flash_socket_set.fd_array[i]==ListenSocket)  // （1）监听套节字接收到新连接
						{
							if(g_flash_socket_set.fd_count < FD_SETSIZE)
							{
								//accept socket
								SOCKET accept_socket;
								sockaddr_in accept_sockaddr;
								int sockaddr_len=0;
								int timeout = 60000;
								linger accept_linger;
								accept_linger.l_onoff = 1;  // (在closesocket()调用,但是还有数据没发送完毕的时候容许逗留)
								accept_linger.l_linger = 5; // (容许逗留的时间为0秒)

								sockaddr_len = sizeof(accept_sockaddr);
								accept_socket = ::accept(g_flash_socket_set.fd_array[i],(struct sockaddr*)&accept_sockaddr,&sockaddr_len);
								//设置接受超时
								::setsockopt(accept_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));
								//设置关闭之后，会保留5秒
								::setsockopt(accept_socket,	SOL_SOCKET,	SO_LINGER,(const char*)&accept_linger,sizeof(accept_linger));
								//加入到g_flash_socket_set中
								FD_SET(accept_socket,&g_flash_socket_set);
								//输出日志
								memset(wide_string,0x0,sizeof(wide_string));
								memset(log,0x0,sizeof(log));

								string_conv.multibyte_to_widechar(inet_ntoa(accept_sockaddr.sin_addr),wide_string,sizeof(wide_string));
								swprintf(log,L"接收到flash的socket连接，IP地址：%s",wide_string);
								WriteLog(__FL__, log);
							}
							else
							{
								WriteLog(__FL__, L"有太多的flash socket连接，不能接受新的连接");
								continue;
							}
						}
						else
						{
							//recv data
							char recv_data[512];
							int recv_len=0;

							memset(recv_data,0x0,sizeof(recv_data));

							recv_len = ::recv(g_flash_socket_set.fd_array[i],(char*)recv_data,sizeof(recv_data),0);			

							if (recv_len>0)                     //(2)接受到数据
							{
								TCHAR szTemp[512] = {0x00};
								string_conv.utf8_to_widechar(recv_data, szTemp, sizeof(szTemp));
								Json::Reader reader;
								Json::Value root;
								
								//不能解析
								if (!reader.parse(recv_data, root, false))
								{
									continue;
								}
								
								string pf = "";
								if (root.isMember("PF"))
								{
									pf = root["PF"].asString();
								}else
									continue;

								string pid = "";
								if (root.isMember("PID"))
								{
									pid = root["PID"].asString();
								}else
									continue;

								TCHAR szPF[512] = {0x00};
								TCHAR szPID[512] = {0x00};
								string_conv.multibyte_to_widechar(pf.c_str(), szPF, sizeof(szPF));
								string_conv.multibyte_to_widechar(pid.c_str(), szPID, sizeof(szPID));
								//flash界面初始化完成才响应界面发送过来的消息
								//处理消息
								pWnd->flash_message_call_ex(szPF, szPID);
							}
							else								// （3）连接关闭、重启或者中断
							{
								::closesocket(g_flash_socket_set.fd_array[i]);
								FD_CLR(g_flash_socket_set.fd_array[i], &g_flash_socket_set);
							}
						}
					}
				}//end for()
			}
			catch (...)
			{

			}
		}
		//关闭socket
		if (ListenSocket)
		{
			::closesocket(ListenSocket);
			ListenSocket = INVALID_SOCKET;
		}
	}
	catch (...)
	{
	}
	return 0;
}

void Cflashktv10Wnd::InitFlashByExe()
{
	TCHAR szwQRUrl[2048] = {0x00};
	char szQRUrl[2048] = {0x00};
	TCHAR szLocalPath[MAX_PATH] = {0x00};

	swprintf(szwQRUrl, L"http://%s/scene?ip=%s", m_picture_mv_server_ip.c_str(), m_room_ip);
	string_conversion str_conn;
	str_conn.widechar_to_multibyte(szwQRUrl, szQRUrl, sizeof(szQRUrl));

	swprintf(szLocalPath,L"%s\\qr_picture\\phone_picture.png",m_work_path);

	Generate_encode_picture(szQRUrl,szLocalPath);

	zoom_image(szLocalPath,145,145,szLocalPath,L"image/png",20,20);

	change_char(szLocalPath);

	TCHAR szTmp[256] = {0x00};
	config_file_manager config_file;
	int background = config_file.read_integer(L"full_screen", L"default_background", 0);
	int quality = config_file.read_integer(L"full_screen", L"quality", 0);
	int screen_number = config_file.read_integer(L"full_screen", L"screen_number", 0);

	int num = config_file.read_integer(L"full_screen", L"display_num", 1);
	int sx = 0, sy = 0, swidth = 0, sheight = 0;
	bool result = get_display_device_settings(num, sx, sy, swidth, sheight);
	if (!result)
	{
		sx = config_file.read_integer(L"full_screen", L"screen_x", 0);
		sy = config_file.read_integer(L"full_screen", L"screen_y", 0);
	}

	swprintf(szTmp, L"{\"TYPE\":\"init\",\"BACKGROUND\":\"%d\",\"QUALITY\":\"%d\",\"SCREENNUMBER\":\"%d\",\"QR\":\"%s\",\"X\":\"%d\",\"Y\":\"%d\"}", 
		background, quality, screen_number, szLocalPath, sx, sy);
	WriteLog(__FL__, szTmp);

	SendFlashDataBySocket(szTmp);
}
void Cflashktv10Wnd::SendFlashDataBySocket(const TCHAR* pStr)
{
	string_conversion strCon;
	char szTemp[10240] = {0x00};
	strCon.widechar_to_multibyte(pStr, szTemp, sizeof(szTemp));
	SendFlashDataBySocket(szTemp);
}

void Cflashktv10Wnd::SendFlashDataBySocket(const char* pStr)
{
	char szSendData[10240] = {0x00};
	sprintf(szSendData, "SHINEFLASHSOCKET@@%s", pStr);
	for (int i = 0; i < g_flash_socket_set.fd_count; i++)
	{
		send(g_flash_socket_set.fd_array[i], szSendData, strlen(szSendData), 0);
	}
}

void Cflashktv10Wnd::flash_message_call_active_game_scene(const TCHAR* pScene)
{
	TCHAR szTempPath[1024] = {0x00};	
	GetTempPath(MAX_PATH, szTempPath);
	
	const TCHAR *pName = _tcsrchr(pScene, '/') + 1;
	_tcscat(szTempPath, pName);

	char szUrl[MAX_PATH] = {0x00};
	string_conversion string_conn;
	string_conn.widechar_to_multibyte(pScene, szUrl, sizeof(szUrl));
	//if (down(pScene, szTempPath) == 0) //下载成功
	if(m_http_obj.download_file(szUrl, szTempPath) == 0)
	{
		CExifTags exif;
		EXIFINFO exifInfo;
		ZeroMemory(&exifInfo, sizeof(EXIFINFO));
		exif.GetExifRead(szTempPath, &exifInfo);

		TCHAR *szSuffix = _tcsrchr(szTempPath, '.');
		CString strFormat = L"";
		if (_tcscmp(szSuffix, L".jpg") == 0 || _tcscmp(szSuffix, L".jpeg") == 0)
		{
			strFormat = _T("image/jpeg");
		}
		else if (_tcscmp(szSuffix, L".png") == 0)
		{
			strFormat = _T("image/png");
		}
		else if (_tcscmp(szSuffix, L".bmp") == 0)
		{
			strFormat = _T("image/bmp");
		}
		else if (_tcscmp(szSuffix, L".gif") == 0)
		{
			strFormat = _T("image/gif");
		}
		else if (_tcscmp(szSuffix, L".tif") == 0)
		{
			strFormat = _T("image/tiff");
		}
		else
		{
			strFormat = _T("image/jpeg");
		}
		if (exifInfo.Height > 800)
		{
			zoom_image(szTempPath,exifInfo.Width/(float)(exifInfo.Height/800),800,szTempPath, strFormat.GetBuffer(), 0, 0);
		}

		TCHAR msg[MAX_PATH] = {0x00};
		change_char(szTempPath);
		swprintf(msg, L"{\"TYPE\":\"img\",\"PATH\":\"%s\",\"ROTATION\":\"%d\"}", szTempPath, exifInfo.Orientation);
		SendFlashDataBySocket(msg);
	}else{
		CString csTmp = _T("");
		csTmp.Format(L"[flash_message_call_active_game_scene]:下载照片场景失败 local path = %s, url = %s", szTempPath, pScene);
		WriteLog(__FL__, csTmp);
	}
}

void Cflashktv10Wnd::create_wechat_gift_wnd()
{
	int nFlashId = 0;
	nFlashId = WECHAT_GIFT_SOFT_PLAYER_ID;
	TCHAR path[256] = {0x0};
	swprintf(path,L"%s\\wechat_interaction_interface\\Wechat_magic_face.swf",m_work_path);	
	CRect rtStarFlash(0,0,m_sencond_display_width,m_sencond_display_height);
	m_pWechatGiftSoftTransparentWnd = new CTransparentWnd;
	m_bWechatGiftFlashPlayerExist = PlayScreenFlash(m_pWechatGiftSoftTransparentWnd, &m_soft_decode_window_child, path, m_rt_soft_activity, rtStarFlash,SCREEN_FLASH_WND_ID, nFlashId);
	if (m_bWechatGiftFlashPlayerExist)
	{
		m_pWechatGiftSoftTransparentWnd->m_pFlash->put_ScaleMode(2);//可缩放，适应窗口
		//m_pWechatGiftSoftTransparentWnd->SetWindowStyle(RGB(0, 0, 0), 150, (LWA_COLORKEY | LWA_ALPHA));
		m_pWechatGiftSoftTransparentWnd->SetWindowStyle(NULL, 150);
		m_pWechatGiftSoftTransparentWnd->SetWindowPos(&CWnd::wndTopMost,m_rt_soft_activity.left,m_rt_soft_activity.top+90,m_rt_soft_activity.Width(),m_rt_soft_activity.Height()*11/20,NULL);
		m_pWechatGiftSoftTransparentWnd->m_pFlash->MoveWindow(0, 0, m_rt_soft_activity.Width(), m_rt_soft_activity.Height()*11/20);
		m_pWechatGiftSoftTransparentWnd->ShowWindow(SW_SHOW);
		m_pWechatGiftSoftTransparentWnd->m_pFlash->ShowWindow(SW_SHOW);
	}
}
void Cflashktv10Wnd::destroy_wechat_gift_wnd()
{
	if (m_pWechatGiftSoftTransparentWnd != NULL)
	{
		delete m_pWechatGiftSoftTransparentWnd;
		m_pWechatGiftSoftTransparentWnd = NULL;
	}
	m_bWechatGiftFlashPlayerExist = false;
	//	m_nFlashFinishCnt = 0;
	m_bWechatGiftFlashFinish = false;
}
UINT Cflashktv10Wnd::show_wechat_gift_info_thread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);

		pThis->show_wechat_gift_info();

		//		AfxEndThread(0);

		return 0;
	}
	catch (...)
	{
	} 
	return -1;
}
UINT Cflashktv10Wnd::show_wechat_gift_info()
{
	try
	{
		while(m_bWechatGiftFlashPlayerExist)
		{
			Sleep(50);
			m_wechat_gift_lock.lock();

			if (!m_deque_wechat_message.empty())
			{
				WECHAT_MESSAGE info = m_deque_wechat_message.front();

				switch (info.notice_type)
				{
				case WECHAT_RET_NOTICE:
					{
						if (!m_bWechatGiftPrepare)
						{
							flash_message_call_wechat_gift_info(&info, false);
							m_bWechatGiftPrepare = true;
						}
					}
					break;
				case WECHAT_RET_OK:
					{
						m_bWechatGiftPrepare = false;
						if (!m_bWechatGiftSending)
						{
							flash_message_call_wechat_gift_info(&info, true);
							m_bWechatGiftSending = true;
						}
					}
					break;
				case WECHAT_RET_ERROR:
					{
						m_bWechatGiftPrepare = false;
						if (!m_bWechatGiftSending)
						{
							flash_message_call_wechat_gift_info(&info, false);
							m_bWechatGiftSending = true;
						}
					}
					break;
				}
			}
			else
			{
				m_destroy_gift_wnd_timer_identifier = SetTimer(DESTROY_GIFT_WND_TIME_EVENT_ID, 100, NULL);
				m_bWechatGiftFlashPlayerExist = false;
//				destroy_wechat_gift_wnd();
			}

			m_wechat_gift_lock.unlock();
		}
		return 0;
	}
	catch (...)
	{
	}
	return 0;
}
bool Cflashktv10Wnd::flash_message_call_wechat_gift_info(WECHAT_MESSAGE *pInfo, bool bFlag/* = false*/)
{
	try
	{
		bool bRet = false;
		TCHAR request[1024] = {0x00}, data[1024] = {0x00};
		char szData[1024] = {0x00};
		string_conversion str_conv;
		int nMode = 0;

		if (pInfo == NULL)	return false;

		//notice_type:0：正在下载礼物 ，显示准备动画1：下载成功，显示礼物动画2：下载失败，显示失败动画
		//信息
		sprintf(szData, "<data><info load_head=\"%d\" nick_name=\"%s\" head_path=\"%s\" gift_path=\"%s\" notice_type=\"%d\" /></data>", 
			bFlag?1:0, pInfo->nickname, pInfo->portraitpath, pInfo->filepath, pInfo->notice_type);

		str_conv.multibyte_to_widechar(szData, data, sizeof(data));

		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"wechat_gift_info", data);
		if (bRet)
		{
			if (m_pWechatGiftSoftTransparentWnd != NULL && m_bWechatGiftFlashPlayerExist)
				m_pWechatGiftSoftTransparentWnd->m_pFlash->CallFunction(request);
		}
		return true;
	}
	catch (...)
	{
	}
	return false;
}

bool Cflashktv10Wnd::DealMuteState(bool bChange/* = false*/)
{
	try
	{
		//是否是静音状态
		bool bMute = m_player_manager.is_mute();
		if (!bMute)
		{
			//非静音时，直接返回
			return true;
		}
		//是否直接取消静音
		if (bChange)
		{
			flash_message_call_function(SONG_MUTE_UNMUTE);
		}
		return true;
	}
	catch (...)
	{
	}
	return false;
}

bool Cflashktv10Wnd::flash_message_call_might_like_button(bool bOpen)
{
	try
	{
		bool bRet = false;
		TCHAR request[256] = {0x00}, data[256] = {0x00};

		if (bOpen)
		{
			swprintf(data, L"<data><info button_state=\"true\"/></data>");
		}
		else
		{
			swprintf(data, L"<data><info button_state=\"false\"/></data>");
		}

		bRet = m_flash_manage.make_request(request, sizeof(request)/sizeof(TCHAR), L"might_like_button", data);
		if (!bRet)
			return false;

		bRet = flash_player_call_function(request);
		if (!bRet)
			return false;
		
		return true;
	}
	catch (...)
	{
	}
	return false;
}

bool Cflashktv10Wnd::ShowOrHideCoverPage(int nPageCode, bool bShow/* = false*/)
{
	try
	{
		bool bRet = false;
		TCHAR szLog[256] = {0x00};

		if (nPageCode <= 0)
		{
			return false;
		}

		switch(nPageCode)
		{
		case page_challenge_star:
			{
			}
			break;
		case page_across_pass:
			{
			}
			break;
		case page_listen_knowledge_song:
			{
			}
			break;
		case page_video_show:
			{
			}
			break;
		case page_picture_mv:
			{
			}
			break;
		case page_active_game:
			{
			}
			break;
		default:
			{
			}
			break;
		}
		//发送图片数据
		bRet = flash_message_call_slave_cover_image(bShow);
		if (!bRet)
		{
			WriteLog(__FL__, L"处理遮挡页面失败");
			return false;
		}

		return true;
	}
	catch(...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::flash_message_call_slave_cover_image(bool bShow /*= true*/)
{
	try
	{
		bool bRet = false;
		TCHAR args[1024] = {0x00};
		TCHAR request[2048] = {0x00};

		if (bShow)
		{
			if (m_show_screen_saver_state_activity)
			{
				return true;
			}
			//隐藏手写
			if (m_handwriting_window_exist && m_show_handwriting_window)
			{
				m_handwriting_window.ShowWindow(SW_HIDE);
			}
			//隐藏小视频和娱乐新闻
			m_screen_show_window.show_window(false);
			//得到页面索引
			int page_index = m_flash_manage.get_last_page_index();
			if (page_index == page_yule_news||page_index == page_drinks||page_index == page_consumer)
			{
				if (m_html_ctrl_exist)
				{
					m_html_ctrl.ShowWindow(SW_HIDE);
					m_html_ctrl.UpdateWindow();
					m_show_html_ctrl = false;
				}
			}
			swprintf(args, L"<data><info  startButton=\"0\" screen=\"%d\"/></data>", m_screen_to_flash_timer);
			bRet = m_flash_manage.make_request(request,sizeof(request)/sizeof(TCHAR),L"screen_to_flash",args);
			if (!bRet)	return false;
			//发送屏保图片文件到flash
			flash_message_call_service(L"6");

			bRet = flash_player_call_function(request);
			if (!bRet)	return false;
			
			m_show_screen_saver_state_activity = true;
		}
		else
		{
			//重新计算屏保时间
			m_start_screen_saver_timer.start();
			//隐藏遮挡图片
			flash_message_call(L"close_screen", L"0");
			m_show_screen_saver_state_activity = false;
		}
		return true;
	}
	catch(...)
	{
	}
	return false;
}
bool Cflashktv10Wnd::send_master_slave_cover_iamge_data(bool bShow, int nPageCode)
{
	try
	{
		bool bRet = false;
		char szData[1024] = {0x00};

		//不是主控端，则返回
		if (m_master_slave_control_flag == 2)
		{
			WriteLog(__FL__, L"被控端不能发送遮挡图片消息");
			return true;
		}

		if (bShow)
		{
			//转化成字符串
			sprintf(szData,"ENTER_ACTIVITY|%d", nPageCode);
			//发送控制码
			bRet = send_master_slave_data(NULL, szData);
			if (!bRet)
			{
				WriteLog(__FL__, L"向被控端发送显示遮挡图片的消息失败");
				return false;
			}
		}
		else
		{
			//转化成字符串
			sprintf(szData,"LEAVE_ACTIVITY|%d", nPageCode);
			//发送控制码
			bRet = send_master_slave_data(NULL, szData);
			if (!bRet)
			{
				WriteLog(__FL__, L"向被控端发送隐藏遮挡图片的消息失败");
				return false;
			}
		}
		return true;
	}
	catch(...)
	{
	}
	return false;
}

UINT Cflashktv10Wnd::DaoqiMovieCommunicateThread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pThis = reinterpret_cast<Cflashktv10Wnd *>(pParam);

		pThis->DaoqiMovieCommunicate();
	}
	catch (...)
	{

	}
	return 0;
}

UINT Cflashktv10Wnd::DaoqiMovieCommunicate()
{
	try
	{
		timeval overtime;
		overtime.tv_sec = 0;
		overtime.tv_usec = 10000;
		int result=0;

		//清0
		FD_ZERO(&m_DaoQiMovieFd_set);

		//create socket
		SOCKET list_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (list_socket < 0) 
		{
			return -1;
		}
		//bind local addr
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		addr.sin_port = ntohs(8463);
		memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
		if (SOCKET_ERROR==bind(list_socket, (struct sockaddr*)&addr, sizeof(sockaddr_in)))
		{
			WriteLog(__FL__, L"socket绑定道奇系统端口失败");
			return -1;
		}
		//监听
		if (SOCKET_ERROR==listen(list_socket,SOMAXCONN))
		{
			WriteLog(__FL__, L"启动监听道奇系统端口失败");
			return -1;
		}
		//加入监听组
		FD_SET(list_socket,&m_DaoQiMovieFd_set);
		while (m_thread_run)
		{
			try
			{
				SLEEP_FOR; //增加sleep

				//将fdSocket集合的一个拷贝fdRead传递给select函数，
				// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回
				fd_set fdRead_set = m_DaoQiMovieFd_set;
				result = ::select(0,&fdRead_set,NULL,NULL,&overtime);
				if (result<=0)
				{
					continue;
				}
				//通过将原来fdSocket集合与select处理过的fdRead集合比较，
				// 确定都有哪些套节字有未决I/O，并进一步处理这些I/O。
				for(int i=0; i<(int)m_DaoQiMovieFd_set.fd_count; i++)
				{
					if (FD_ISSET(m_DaoQiMovieFd_set.fd_array[i],&fdRead_set))
					{
						if (m_DaoQiMovieFd_set.fd_array[i]==list_socket)  // （1）监听套节字接收到新连接
						{
							if(m_DaoQiMovieFd_set.fd_count < FD_SETSIZE)
							{
								//accept socket
								SOCKET accept_socket;
								sockaddr_in accept_sockaddr;
								int sockaddr_len=0;
								int timeout = 60000;
								linger accept_linger;
								accept_linger.l_onoff = 1;  // (在closesocket()调用,但是还有数据没发送完毕的时候容许逗留)
								accept_linger.l_linger = 5; // (容许逗留的时间为0秒)

								sockaddr_len = sizeof(accept_sockaddr);
								accept_socket = ::accept(m_DaoQiMovieFd_set.fd_array[i],(struct sockaddr*)&accept_sockaddr,&sockaddr_len);
								//设置接受超时
								::setsockopt(accept_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));
								//设置关闭之后马上断开
								::setsockopt(accept_socket,	SOL_SOCKET,	SO_LINGER,(const char*)&accept_linger,sizeof(accept_linger));
								//加入到socket_set中
								FD_SET(accept_socket,&m_DaoQiMovieFd_set);
								WriteLog(__FL__, L"道奇系统连接成功!");

								//如果有连接过来，则发送包房状态
								MOVIE_MSG_CONTROL MMCtrl;
								ZeroMemory(&MMCtrl, sizeof(MOVIE_MSG_CONTROL));
								MMCtrl.head = HEAD_FLAG;
								MMCtrl.mmt = MMT_DIAITAL_MSG;

								//判断是否开房了
								if (CLOSE_ROOM_STATE == m_pc_state)
									MMCtrl.mmc = MMCMSG_CLOSE_ROOM;
								else
									MMCtrl.mmc = MMCMSG_OPEN_ROOM;
								
								SendDaoQiSystemMsg(&MMCtrl);
							}
							else
							{
								WriteLog(__FL__, L"8463端口有太多的socket连接，不能接受新的连接");
								continue;
							}
						}
						else
						{
							//recv data
							LPFLASHMOVIEMSG lpFlashMovieMsg = new FLASHMOVIEMSG(); 
							int recv_len=0;
							memset(lpFlashMovieMsg, 0x00, sizeof(FLASHMOVIEMSG));

							recv_len = ::recv(m_DaoQiMovieFd_set.fd_array[i], (char*)&lpFlashMovieMsg->lpMMControl, sizeof(MOVIE_MSG_CONTROL), 0);

							if (recv_len>0)                     //(2)接受到数据
							{
								lpFlashMovieMsg->pWnd = this;								
								if (lpFlashMovieMsg->lpMMControl.head == HEAD_FLAG) //验证是否为道奇消息
								{
									switch(lpFlashMovieMsg->lpMMControl.mmt)
									{
									case MMT_DIAITAL_MSG: //控制消息类型
										{
											AfxBeginThread(DaoQiMsgControlFunc, lpFlashMovieMsg);
										}
										break;
									case MMT_CHARACTER_MSG:	//消息系统类型
										{
											if (lpFlashMovieMsg != NULL)
											{
												delete lpFlashMovieMsg;
												lpFlashMovieMsg = NULL;
											}
										}
										break;
									}
								}
							}
							else								// （3）连接关闭、重启或者中断
							{
								delete lpFlashMovieMsg;
								lpFlashMovieMsg = NULL;

								::closesocket(m_DaoQiMovieFd_set.fd_array[i]);
								FD_CLR(m_DaoQiMovieFd_set.fd_array[i], &m_DaoQiMovieFd_set);
							}
						}
					}
				}//end for()
			}
			catch (...)
			{

			}
		}
		return 1;
	}
	catch (...)
	{

	}
	return -1;
}

UINT Cflashktv10Wnd::DaoQiMsgControlFunc(LPVOID pParam)
{
	try
	{
		LPFLASHMOVIEMSG lpFlashMovieMsg= reinterpret_cast<LPFLASHMOVIEMSG>(pParam);
		Cflashktv10Wnd* pWnd = (Cflashktv10Wnd*)lpFlashMovieMsg->pWnd;

		pWnd->MsgControlFunction(lpFlashMovieMsg->lpMMControl.mmc);
		
		if (lpFlashMovieMsg != NULL)
		{
			delete lpFlashMovieMsg;
			lpFlashMovieMsg = NULL;
		}
		
	}
	catch (...)
	{

	}
	return 0;
}

void Cflashktv10Wnd::MsgControlFunction(enMovieMsgContent enMMC /* = MMCMSG_DEFAULT */)
{
	switch(enMMC)
	{
	case MMCMSG_OPEN_ROOM: //开房
		{
			SendMessage(DM_RECV_SERVER_DATA,(WPARAM)"open0",NULL);
			//set_button_show_state(ROOM_BUTTON_STATE, true);
		}
		break;
	case MMCMSG_CLOSE_ROOM:	//关房
		{
			SendMessage(DM_RECV_SERVER_DATA,(WPARAM)"close",NULL);
			//set_button_show_state(ROOM_BUTTON_STATE, false);
		}
		break;
	case MMCMSG_SERIVCES:	//服务
		{
			flash_message_call_function(CALL_ATTENDANT);
		}
		break;
	case MMCMSG_SHOW:	//显示
		{
			this->ShowWindow(SW_MAXIMIZE);
			if (m_soft_decode_window_exist)
			{
				m_soft_decode_window.ShowWindow(SW_MAXIMIZE);
			}

			if (m_inter_screen_window_exist)
			{
				m_inter_screen_window.ShowWindow(SW_MAXIMIZE);
			}
			flash_message_call_function(SONG_PLAY);
		}
		break;
	case MMCMSG_HIDE:	//隐藏
		{
			flash_message_call_function(SONG_PAUSE);
			this->ShowWindow(SW_MINIMIZE);
			if (m_soft_decode_window_exist)
			{
				m_soft_decode_window.ShowWindow(SW_MINIMIZE);
			}

			if (m_inter_screen_window_exist)
			{
				m_inter_screen_window.ShowWindow(SW_MINIMIZE);
			}
		}
		break;
	case MMSMSG_LIGHT_OPEN: //灯光全开
		{
			change_room_light(FLASH_SEND_LIGHT_OPEN, false);
		}
		break;
	case MMSMSG_LIGHT_CLOSE:	//灯光全关
		{
			change_room_light(FLASH_SEND_LIGHT_CLOSE, false);
		}
		break;
	case MMCMSG_DEFAULT:
	default:
		break;
	}
}

long Cflashktv10Wnd::SendDaoQiSystemMsg(const LPMOVIE_MSG_CONTROL lpMMCtrl)
{
	if ((int)m_DaoQiMovieFd_set.fd_count == 0)
	{
		return -1;
		WriteLog(__FL__, L"不存在道奇的连接，发送道奇电影消息系统消息失败!");
	}
	for(int i=0; i<(int)m_DaoQiMovieFd_set.fd_count; i++)
	{
		SOCKET sSendSocket = m_DaoQiMovieFd_set.fd_array[i];
		int nRecv = ::send(sSendSocket, (const char*)lpMMCtrl, sizeof(MOVIE_MSG_CONTROL), 0);
		if (nRecv > 0)
		{
			WriteLog(__FL__, L"发送道奇电影消息系统消息成功!");
		}else{
			WriteLog(__FL__, L"发送道奇电影消息系统消息失败!");
		}
	}
	return 0;
}
UINT Cflashktv10Wnd::uVideoShowDownFileThread(LPVOID pParam)
{
	try
	{
		Cflashktv10Wnd* pWnd = (Cflashktv10Wnd*)pParam;
		pWnd->VideoShowDownFile();
		return 0;
	}
	catch (...)
	{
	}
	return 0;
}

void Cflashktv10Wnd::VideoShowDownFile()
{
	m_video_show_current_page = 1; //当前页为第一页
	//设置下载路径
	TCHAR szLocalPicPath[MAX_PATH] = {0x00};
	TCHAR szTmpDir[MAX_PATH] = {0x00};
	char szLPP[MAX_PATH] = {0x00};
	GetTempPath(MAX_PATH, szTmpDir);
	swprintf(szLocalPicPath, L"%s\\videoshow.json", szTmpDir);
	string_conversion str_conn;
	str_conn.widechar_to_multibyte(szLocalPicPath, szLPP, sizeof(szLPP));

	int ret = m_http_obj.download_file("http://live.ispeak.cn/api/ktv/onlineanchor?key=p91Yg6oB4Lu3!2Fb", szLocalPicPath);
	//if(down("http://live.ispeak.cn/api/ktv/onlineanchor?key=p91Yg6oB4Lu3!2Fb", szLPP) == 0) //下载成功
	if(ret == 0)
	{
		parse_video_show_data(szLocalPicPath);
	}
}
